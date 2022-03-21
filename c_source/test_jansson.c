#include <stdio.h>
#include <string.h>
#include <time.h>

#include "jansson.h"
#include "debug_print.h"

enum {
	LOGIN_FAIL,
	LOGIN_SUCCESS,
	SHOW_LOGIN_LIST,
	SHOW_ACCOUNT_LIST,
	CHECK_ACCOUNT,
	QUIT,
	COMMAND_MAX,
};

enum {
	NOT_FOUND_ACCOUNT,
	FOUND_ACCOUNT,
};

enum {
	ERROR_CNT_MAX = 5,
};

const char* command[COMMAND_MAX] = {
	"fail",
	"success",
	"showlogin",
	"showaccount",
	"checkaccount",
	"quit",
};

const char* loginFilename = "./loginFail.json";
const char* rootKey = "restrictList";

int write_json_to_file(const char *filename, json_t* writeData)
{
	if(filename == NULL) {
		filename = loginFilename;
	}

	_DBG_R("[WRITE-jsonData] = %s\n", json_dumps(writeData, JSON_ENCODE_ANY));
	json_dump_file(writeData, filename, JSON_ENCODE_ANY);

	return 0;
}

json_t *load_data_from_json(const char *filename)
{
	if (filename == NULL) {
		filename = loginFilename;
	}

	json_error_t error;
	json_t *jData = json_load_file(filename, JSON_DECODE_ANY, &error);
	// _DBG_Y("[JSON] error = %d\n", json_error_code(&error));
	// _DBG_Y("[JSON] jData = %s\n", json_dumps(jData, JSON_ENCODE_ANY));

	return jData;
}

void print_help(void)
{
	_DBG_R("===============================================================================\n");
	_DBG_R(" command list\n");
	_DBG_R(" %s <= login fail\n", command[LOGIN_FAIL]);
	_DBG_R(" %s <= login success\n", command[LOGIN_SUCCESS]);
	_DBG_R(" %s <= show current restrict list\n", command[SHOW_LOGIN_LIST]);
	_DBG_R(" %s <= show account list\n", command[SHOW_ACCOUNT_LIST]);
	_DBG_R(" %s <= check same username with account\n", command[CHECK_ACCOUNT]);
	_DBG_R(" %s <= quit program\n", command[QUIT]);
	_DBG_R("===============================================================================\n");
}

enum {
	NONE,
	UPDATE,
};

enum {
	USER_ADD,
	USER_KEEP,
};

json_t* existRootKey(json_t* jsonData)
{
	if(jsonData == NULL) {
		_DBG_R("jsonData is NULL\n");
		return NULL;
	}

	json_t* jRoot = NULL;
	jRoot = json_object_get(jsonData, rootKey);

	// check whether jUserArray is array type
	if(json_is_array(jRoot) == JSON_FALSE) {
		_DBG_R("jRoot is NOT array type\n");
		return NULL;
	}
	return jRoot;
}

int compareRestrictedLogin(json_t* jsonData, time_t *timestamp)
{
	if(jsonData == NULL || timestamp == NULL) {
		if(jsonData == NULL) {
			_DBG_R("jsonData is NULL\n");
		}
		if(timestamp == NULL) {
			_DBG_R("timestamp is NULL\n");
		}
		else if(*timestamp <= 0) {
			_DBG_R("Invalid timestamp(%ld)\n", *timestamp);
		}
		return -1;
	}

	json_t* jTimestamp = NULL;
	time_t oldTimestamp = 0;

	jTimestamp = json_object_get(jsonData, "timestamp");
	if(jTimestamp != NULL) {
		oldTimestamp = json_integer_value(jTimestamp);
		if(oldTimestamp > 0) {
			if(oldTimestamp + 300 > *timestamp) {
				_DBG_C("restricting login (oldTimestamp: %ld; timestamp: %ld; diff = %ld)\n", oldTimestamp, *timestamp, *timestamp - oldTimestamp);
				return 1;
			}
		}
	}

	return 0;
}

void recordTimestamp(json_t* jsonData, time_t* timestamp)
{
	if(jsonData == NULL || timestamp == NULL) {
		if(jsonData == NULL) {
			_DBG_R("jsonData is NULL\n");
		}
		if(timestamp == NULL) {
			_DBG_R("timestamp is NULL\n");
		}
		else if(*timestamp <= 0) {
			_DBG_R("Invalid timestamp(%ld)\n", *timestamp);
		}
		return;
	}

	enum {
		TMP_BUF_SIZE = 32,
	};
	char strTmp[TMP_BUF_SIZE];
	struct tm* tm_timestamp = NULL;

	json_object_set_new(jsonData, "timestamp", json_integer(*timestamp));
	tm_timestamp = (struct tm*)localtime(timestamp);
	snprintf(strTmp, TMP_BUF_SIZE, "%04d/%02d/%02d-%02d:%02d:%02d", tm_timestamp->tm_year + 1900, tm_timestamp->tm_mon + 1, tm_timestamp->tm_mday, tm_timestamp->tm_hour, tm_timestamp->tm_min, tm_timestamp->tm_sec);
	_DBG_C("YYYY/MM/DD-hh:mm:ss = %s\n", strTmp);
	json_object_set_new(jsonData, "timestamp_tm", json_string(strTmp));
}

int findAccount(const char* username);

int login_fail_proc(char* username)
{
	_DBG_C("username = %s\n", username);
	json_t* jLoginFailList = NULL;
	json_t* jUserArray = NULL;
	json_t* jValue = NULL;
	json_t* jTmp = NULL;
	json_t* jCount = NULL;
	json_t* jUserAdd = NULL;
	const char* cTmp = NULL;
	int ret = 0;
	int index = 0;
	int userSize = 0;
	int tmpSize = 0;
	int cmpSize = 0;
	int count_tmp = 0;
	int action = NONE;
	int userAction = USER_ADD;
	time_t timestamp = 0;

	if(username == NULL) {
		_DBG_R("username is NULL\n");
		return -1;
	}

	userSize = strlen(username);
	if(userSize <= 0) {
		_DBG_R("Invalid username(%s)\n", username);
		return -1;
	}

	// load json file
	jLoginFailList = load_data_from_json(NULL);
	if(jLoginFailList == NULL) {
		// empty or not found json file 
		_DBG_R("jLoginFailList is NULL\n");
		// TODO: generate empty file & record fail count
		return -1;
	}

	// find key "restrictList"
	jUserArray = existRootKey(jLoginFailList);
	if(jUserArray == NULL) {
		_DBG_R("jUserArray is NULL\n");
		json_decref(jLoginFailList);
		return -1;
	}

	// find key username for loop
	json_array_foreach(jUserArray, index, jValue) {
		_DBG_C("index = %d; jValue = %s\n", index, json_dumps(jValue, JSON_ENCODE_ANY));
		jTmp = json_object_get(jValue, "username");
		if(jTmp == NULL) {
			_DBG_R("[%d] jTmp is NULL\n", index);
			continue;
		}

		cTmp = json_string_value(jTmp);
		if(cTmp == NULL) {
			_DBG_R("[%d] cTmp is NULL (jTmp is not char type)\n", index);
			continue;
		}

		tmpSize = strlen(cTmp);
		if(tmpSize <= 0) {
			_DBG_R("[%d] Invalid cTmp(%s)\n", index, cTmp);
			continue;
		}

		cmpSize = tmpSize > userSize ? tmpSize:userSize;
		// find same username in restrictList
		if(strncmp(cTmp, username, cmpSize) == 0) {
			// find key "count"
			jCount = json_object_get(jValue, "count");
			if(jCount == NULL) {
				_DBG_R("[%d] jTmp is NULL\n", index);
				continue;
			}
			count_tmp = json_integer_value(jCount);
			if(count_tmp < 0) {
				count_tmp = 0;
			}

			time(&timestamp);
			_DBG_C("timestamp = %ld\n", timestamp);
			if(count_tmp >= ERROR_CNT_MAX) {
				// TODO: check timestamp for restricting login
				_DBG_C("[%d] count is over %d\n", index, ERROR_CNT_MAX);
				// check whether "count" value is over 5
				ret = compareRestrictedLogin(jValue, &timestamp);
				if(ret == 1) {
					json_decref(jLoginFailList);
					return 1;
				}
				else {
					count_tmp = 0;
				}
			}
			else {
				// check whether "count" value should increase
				_DBG_C("[%d] count should increase (%d => %d)\n", index, count_tmp, count_tmp + 1);
				count_tmp++;
			}
			json_object_set_new(jValue, "count", json_integer(count_tmp));
			recordTimestamp(jValue, &timestamp);

			_DBG_C("[%d] jValue = %s\n", index, json_dumps(jValue, JSON_ENCODE_ANY));
			action = UPDATE;
			userAction = USER_KEEP;
			break;
		}
	}

	if(userAction == USER_ADD) {
		// USER_ADD: not found same username
		action = UPDATE;
		jUserAdd = json_object();
		time(&timestamp);
		json_object_set_new(jUserAdd, "username", json_string(username));
		json_object_set_new(jUserAdd, "count", json_integer(1));
		// TODO: timestamp value should be current time
		recordTimestamp(jUserAdd, &timestamp);
		json_array_append_new(jUserArray, jUserAdd);
	}

	if(action == UPDATE) {
		ret = findAccount(username);
		if(ret == NOT_FOUND_ACCOUNT) {
			_DBG_C("username is not registered\n");
			return -1;
		}
		else {
			_DBG_C("write json data to file\n");
			write_json_to_file(NULL, jLoginFailList);
		}
	}

	json_decref(jLoginFailList);

	return ret;
}

int login_success_proc(char* username)
{
	enum {
		TMP_BUF_SIZE = 32,
	};
	_DBG_C("username = %s\n", username);
	json_t* jLoginFailList = NULL;
	json_t* jUserArray = NULL;
	json_t* jValue = NULL;
	json_t* jTmp = NULL;
	json_t* jCount = NULL;
	const char* cTmp = NULL;
	int index = 0;
	int userSize = 0;
	int tmpSize = 0;
	int cmpSize = 0;
	int action = NONE;
	int count_tmp = 0;
	time_t timestamp = 0;
	struct tm* tm_timestamp = NULL;
	char strTmp[TMP_BUF_SIZE];
	int ret = -1;

	if(username == NULL) {
		_DBG_R("username is NULL\n");
		return -1;
	}

	userSize = strlen(username);
	if(userSize <= 0) {
		_DBG_R("Invalid username(%s)\n", username);
		return -1;
	}

	// load json file
	jLoginFailList = load_data_from_json(NULL);
	if(jLoginFailList == NULL) {
		// empty or not found json file 
		_DBG_R("jLoginFailList is NULL\n");
		// TODO: generate empty file & record fail count
		return -1;
	}

	// find key "restrictList"
	jUserArray = existRootKey(jLoginFailList);
	if(jUserArray == NULL) {
		_DBG_R("jUserArray is NULL\n");
		json_decref(jLoginFailList);
		return -1;
	}

	// find key username for loop
	json_array_foreach(jUserArray, index, jValue) {
		_DBG_C("index = %d; jValue = %s\n", index, json_dumps(jValue, JSON_ENCODE_ANY));
		jTmp = json_object_get(jValue, "username");
		if(jTmp == NULL) {
			_DBG_R("[%d] jTmp is NULL\n", index);
			continue;
		}

		cTmp = json_string_value(jTmp);
		if(cTmp == NULL) {
			_DBG_R("[%d] cTmp is NULL (jTmp is not char type)\n", index);
			continue;
		}

		tmpSize = strlen(cTmp);
		if(tmpSize <= 0) {
			_DBG_R("[%d] Invalid cTmp(%s)\n", index, cTmp);
			continue;
		}

		cmpSize = tmpSize > userSize ? tmpSize:userSize;
		// find same username in restrictList
		if(strncmp(cTmp, username, cmpSize) == 0) {
			// find key "count"
			jCount = json_object_get(jValue, "count");
			if(jCount == NULL) {
				_DBG_R("[%d] jTmp is NULL\n", index);
				continue;
			}

			// TODO: check timestamp for restricting login
			jCount = json_object_get(jValue, "count");
			if(jCount == NULL) {
				_DBG_R("[%d] jTmp is NULL\n", index);
			}
			else {
				count_tmp = json_integer_value(jCount);
				if(count_tmp == ERROR_CNT_MAX) {
					time(&timestamp);
					ret = compareRestrictedLogin(jValue, &timestamp);
					if(ret == 1) {
						json_decref(jLoginFailList);
						return 1;
					}
				}
			}

			time(&timestamp);
			json_object_set_new(jValue, "count", json_integer(0));
			recordTimestamp(jValue, &timestamp);

			_DBG_C("[%d] jValue = %s\n", index, json_dumps(jValue, JSON_ENCODE_ANY));
			action = UPDATE;
			break;
		}
	}

	if(action == UPDATE) {
		// TODO: filter whether id is registered
		ret = findAccount(username);
		if(ret == NOT_FOUND_ACCOUNT) {
			_DBG_C("username is not registered\n");
			return -1;
		}
		else {
			_DBG_C("write json data to file\n");
			write_json_to_file(NULL, jLoginFailList);
		}
	}

	json_decref(jLoginFailList);

	return ret;
}

int login_proc(int command_index)
{
	enum {
		USERNAME_BUF_SIZE = 64,
	};
	char username[USERNAME_BUF_SIZE];
	int username_len = 0;
	int ret = 0;

	_DBG_C("enter username: ");
	fgets(username, USERNAME_BUF_SIZE, stdin);
	username_len = strlen(username) - 1;
	if(username_len <= 0) {
		_DBG_C("username is empty\n");
		return -1;
	}
	username[username_len] = 0;		// fgets 에 의한 enter 입력 제거

	switch(command_index) {
		case LOGIN_FAIL:
			ret = login_fail_proc(username);
			break;
		case LOGIN_SUCCESS:
			ret = login_success_proc(username);
			break;
		default:
			_DBG_C("Invalid index(%d)\n", command_index);
			return -1;
	}

	return ret;
}

void showList(void)
{
	json_t* jLoginFailList = NULL;

	jLoginFailList = load_data_from_json(NULL);
	if(jLoginFailList == NULL) {
		// empty or not found json file 
		_DBG_R("jLoginFailList is NULL\n");
		return;
	}

	_DBG_C("jLoginFailList = %s\n", json_dumps(jLoginFailList, JSON_ENCODE_ANY));

	json_decref(jLoginFailList);
}

const char* HTDIGEST_FILE = "./lighttpd-htdigest.user";

int findAccount(const char* username)
{
	enum {
		ACCOUNT_BUF_SIZE = 1024,
		ID_BUF_SIZE = 32,
	};
	char *readBigBuf = NULL;
	char *readBuf = NULL;
	char readSmallBuf[ACCOUNT_BUF_SIZE];
	char *readCutPtr = NULL;
	char *idCutPtr = NULL;
	char idCutBuf[ID_BUF_SIZE];
	FILE *fp = NULL;
	int bufSize = 0;
	int fileSize = 0;
	int readSize = 0;
	int cutCount = 0;
	int readCutSize = 0;
	int idSize = 0;
	int found = NOT_FOUND_ACCOUNT;
	int cmpSize = 0;
	int usernameSize = 0;

	fp = fopen(HTDIGEST_FILE, "r");
	if(fp == NULL) {
		_DBG_R("fp is NULL(%s)\n", HTDIGEST_FILE);
		return NOT_FOUND_ACCOUNT;
	}
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	if(fileSize > ACCOUNT_BUF_SIZE) {
		readBigBuf = (char*)malloc(fileSize);
		if(readBigBuf != NULL) {
			readBuf = readBigBuf;
			bufSize = fileSize;
		}
		else {
			_DBG_R("Failed to create readBigBuffer (%d)\n", fileSize);
			fclose(fp);
			return NOT_FOUND_ACCOUNT;
		}
	}
	else {
		readBuf = readSmallBuf;
		bufSize = ACCOUNT_BUF_SIZE;
		_DBG_G("readSmallBuf is assigned to readBuf\n");
	}
	memset(readBuf, 0, bufSize);

	_DBG_G("fileSize = %d; bufSize = %d\n", fileSize, bufSize);
	fseek(fp, 0, SEEK_SET);
	readSize = fread(readBuf, 1, fileSize, fp);
	_DBG_G("read_file(%d) = %s\n", readSize, readBuf);

	if(username != NULL) {
		usernameSize = strlen(username);
	}
	_DBG_G("readBuf = %s\n", readBuf);
	readCutPtr = strtok(readBuf, "\n");
	while(readCutPtr != NULL) {
		memset(idCutBuf, 0, ID_BUF_SIZE);
		readCutSize = 0;
		cutCount++;
		readCutSize = strlen(readCutPtr);
		_DBG_G("readCutPtr[%d] = %s(%d)\n", cutCount, readCutPtr, readCutSize);
		idCutPtr = readCutPtr;
		idSize = 0;
		while(*idCutPtr != ':') {
			idSize++;
			idCutPtr++;
		}

		strncpy(idCutBuf, readCutPtr, idSize);
		if(username == NULL) {	// SHOW_ACCOUNT_LIST
			_DBG_G("idSize[%d] = %s(%d)\n", cutCount, idCutBuf, idSize);
		}
		else {	// CHECK_ACCOUNT
			cmpSize = idSize > usernameSize ? idSize : usernameSize;
			_DBG_G("idSize[%d] = %s(%d); cmpSize = %d; usernameSize = %d\n", cutCount, idCutBuf, idSize, cmpSize, usernameSize);
			if(strncmp(username, idCutBuf, cmpSize) == 0) {
				found = FOUND_ACCOUNT;
				_DBG_G("Found same username[%d]: %s; idCutBuf = %s\n", cutCount, username, idCutBuf);
				break;
			}
		}
		readCutPtr = strtok(NULL, "\n");
	}

	if(readBigBuf != NULL) {
		free(readBigBuf);
		readBigBuf = NULL;
	}
	fclose(fp);
	return found;
}

int findSameAccount(void)
{
	enum {
		USERNAME_BUF_SIZE = 64,
	};
	char username[USERNAME_BUF_SIZE];
	int username_len = 0;
	int ret = 0;

	_DBG_C("enter username: ");
	fgets(username, USERNAME_BUF_SIZE, stdin);
	username_len = strlen(username) - 1;
	if(username_len <= 0) {
		_DBG_C("username is empty\n");
		return -1;
	}
	username[username_len] = 0;		// fgets 에 의한 enter 입력 제거
	ret = findAccount(username);
	_DBG_R("ret = %d\n", ret);

	return ret;
}

void showAccount(void)
{
	findAccount(NULL);
}

int main(int argc, char** argv)
{
	_DBG_R("test!!!!\n");
	enum {
		CMD_BUF_SIZE = 128,
	};
	char cmd_str[CMD_BUF_SIZE];
	int idx = 0;
	int len = 0;
	int usr_cmd_len = 0;
	int command_len = 0;
	int ret = -1;

	_DBG_R("Start Appliaction\n");

	while (1) {
		_DBG_R("enter command : ");
		fgets (cmd_str, CMD_BUF_SIZE, stdin);

		for (idx = 0;idx < COMMAND_MAX;idx++) {
			usr_cmd_len = strlen(cmd_str) - 1;	// enter 입력 추가되어 size -1 이 필요함
			command_len = strlen(command[idx]);
			len = usr_cmd_len > command_len?usr_cmd_len:command_len;
			if (strncmp(cmd_str, command[idx], len) == 0) {
				break;
			}
		}

		switch(idx) {
			case QUIT:
				goto out;
				break;
			case LOGIN_FAIL:
				_DBG_C("RUN LOGIN_FAIL\n");
				ret = login_proc(idx);
				break;
			case LOGIN_SUCCESS:
				_DBG_C("RUN LOGIN_SUCCESS\n");
				ret = login_proc(idx);
				break;
			case SHOW_LOGIN_LIST:
				_DBG_C("RUN SHOW_LOGIN_FAIL_LIST\n");
				showList();
				break;
			case SHOW_ACCOUNT_LIST:
				_DBG_C("RUN ACCOUNT_LIST\n");
				showAccount();
				break;
			case CHECK_ACCOUNT:
				_DBG_C("RUN CHECK_ACCOUNT\n");
				ret = findSameAccount();
				break;
			default:
				print_help();
				break;
		}
	}

out:

	_DBG_R("Finish Application\n");

	return 0;
} 