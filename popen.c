/*
 * =====================================================================================
 *
 *       Filename:  popen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 10일 19시 32분 47초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>

enum { ARG_CNT = 4, };
enum { FALSE, TRUE };

typedef unsigned int boolean;

boolean file_exist(const char *filename)
{
	struct stat st;

	if (lstat(filename, &st) < 0)
		return FALSE;

	return TRUE;
}

int print_help(int argc, char **argv)
{
	if(argc < ARG_CNT) {
		printf("[%s:%d] too few argument\n", __FILE__, __LINE__);
	}
	else {
		printf("[%s:%d] too many argument\n", __FILE__, __LINE__);
	}
	printf("[%s:%d] %s [FILE_NAME] [FILE_PATH] [ENC_KEY]\n", __FILE__, __LINE__, argv[0]);

	return 0;
}

int main(int argc, char** argv)
{
	if(argc != ARG_CNT) {
		return print_help(argc, argv);
	}
#if 1
	char* sdBackupFile = argv[1];
	char* filePath = argv[2];
	char* authKey = argv[3];
	char* encOutFile = strstr(sdBackupFile, ".");
	char encOutputFile[128];
	char mp4File[128];
	const char* openssl_cmd = "openssl aes-256-cbc -salt";
	char str_enc_cmd[512];
	int encResult = -1;
	FILE* fp;
	char inputLine[1024];
	int inputSize = sizeof(inputLine);

	if(encOutFile != NULL) {
		snprintf(encOutputFile, encOutFile - sdBackupFile + 1, "%s", sdBackupFile);
		printf("[%s:%d] encOutFile = %s(%ld)\n", __FILE__, __LINE__, encOutputFile, encOutFile - sdBackupFile + 1);
	}
	else {
		printf("[%s:%d] sdBackupFile has not .(dot)\n", __FILE__, __LINE__);
		return -1;
	}

	snprintf(mp4File, sizeof(mp4File), "%s/%s", filePath, sdBackupFile);
	printf("[%s:%d] mp4File = %s\n", __FILE__, __LINE__, mp4File);
	snprintf(str_enc_cmd, sizeof(str_enc_cmd), "%s -in %s -out %s -k %s", openssl_cmd, mp4File, encOutputFile, authKey);
	fp = popen(str_enc_cmd, "r");
	while(fgets(inputLine, inputSize, fp) != NULL) {
	}
	if(file_exist(encOutputFile) == TRUE) {
		encResult = 0;
	}
	printf("[%s:%d] encResult = %d\n", __FILE__, __LINE__, encResult);
#else
	char cmd[128];
	char line[10240];
	FILE* fp;
	snprintf(cmd, sizeof(cmd), "./passh -p vhzjtm scp null ppdha82@192.168.0.163:");
	//snprintf(cmd, sizeof(cmd), "scp linuxmint-19.3-mate-64bit.iso ppdha82@192.168.0.163:");
	fp = popen(cmd, "r");
	//popen("ls -l", "w");
	
	while(fgets(line, 10240, fp) != NULL) {
		//printf("%s", line);
		if(strstr(line, "null") != NULL && strstr(line, "0%") != NULL) {
			printf("[%s:%d] start!!!\n", __FILE__, __LINE__);
		}
		if(strstr(line, "100%") != NULL) {
			printf("[%s:%d] complete!!!\n", __FILE__, __LINE__);
			break;
		}
	}
	pclose(fp);
#endif

	return 0;
}
