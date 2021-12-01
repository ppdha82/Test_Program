/*
 * =====================================================================================
 *
 *       Filename:  dirent.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 10일 15시 46분 39초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "debug_print.h"

enum {
	TYPE_DIRECTORY = 4,
};

void print_help(int argc)
{
	if(argc < 2) {
		_DBG_R("too few argument (%d)\n", argc);
	}
	else {
		_DBG_R("too many argument (%d)\n", argc);
	}
}

int check_valid_filename(char* fname)
{
	int ret = 0;
	if(fname[0] == '.') {
		ret = -1;
	}
	else if(strlen(fname) == 2 && strstr(fname, "..") != 0) {
		ret = -1;
	}

	return ret;
}

int find_character_in_string(char* src, char target)
{
	char* ptr;
	int found_char = 0;
	ptr = strchr(src, target);
	if (ptr == NULL) {
		goto find_char_out;
	}

	do {
		found_char++;
		ptr = strchr(ptr + 1, target);
	} while (ptr != NULL);

find_char_out:
	return found_char;
}

int list_dir(const char* path)
{
    struct dirent *entry;
	int file_count = 0;

    DIR *dir = opendir(path);
    if (dir == NULL) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
		char* fname = entry->d_name;
		if(0 != check_valid_filename(fname) || entry->d_type == TYPE_DIRECTORY) {
			continue;
		}
		file_count++;
        _DBG_Y("%s(%d)\n", entry->d_name, entry->d_type);
    }

    closedir(dir);
	return file_count;
}

int find_file_in_dir(const char *path, const char* target)
{
	struct dirent *entry;
	int foundCount = 0;
	char* pStr = NULL;
	enum {
		CMD_BUF_SIZE = 128,
	};
	char cmd[CMD_BUF_SIZE];

    DIR *dir = opendir(path);
    if (dir == NULL) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
		char* fname = entry->d_name;
		if(0 != check_valid_filename(fname) || entry->d_type == TYPE_DIRECTORY) {
			continue;
		}
		pStr = fname + strlen(fname) - strlen(target);
		if(strstr(pStr, target) != NULL) {
			_DBG_C("fname = %s(%s)\n", fname, pStr);
			memset(cmd, 0, CMD_BUF_SIZE);
			snprintf(cmd, CMD_BUF_SIZE, "./analysis_ai_metadata %s", fname);
			system(cmd);
			foundCount++;
		}
    }
	_DBG_G("file_count(%s) = %d\n", target, foundCount);

    closedir(dir);
	return foundCount;
}

int main(int argc, char** argv)
{
	if(argc != 2 && argc != 3) {
		print_help(argc);
		return -1;
	}
	_DBG_G("argv[1] = %s\n", argv[1]);
	int file_count =  0;
	if(argc == 2) {
		file_count = list_dir(argv[1]);
	}
	else if(argc == 3) {
		_DBG_G("argv[2] = %s\n", argv[2]);
		file_count = find_file_in_dir(argv[1], argv[2]);
	}
	_DBG_G("file count = %d\n", file_count);
	return 0;
}
