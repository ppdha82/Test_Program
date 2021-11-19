#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG_ON__
#include "debug_print.h"

int check_valid_filename(char* fname)
{
	int ret = 0;
	if(strlen(fname) == 1 && fname[0] == '.') {
		ret = -1;
	}
	else if(strlen(fname) == 2 && strstr(fname, "..") != 0) {
		ret = -1;
	}

	return ret;
}

int list_dir(const char* path)
{
    struct dirent *entry;
	int file_count = 0;
	int ret = -1;

    DIR *dir = opendir(path);
    if (dir == NULL) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
		char* fname = entry->d_name;
		if(0 != check_valid_filename(fname)) {
			continue;
		}
		file_count++;
        DBG_Y("%s\n",entry->d_name);
    }

    closedir(dir);
	return file_count;
}

void get_file_size(char* param)
{
    int size = 0;
    FILE *fp = NULL;
    FILE *fp_result = NULL;
    char tmp[1024 * 1024];
    int readSize = 0;
    const char *result_filename = "result.jpg";

    fp = fopen(param, "r");
    if(fp == NULL) {
        DBG_R("Failed to open file(%s)\n", param);
        return;
    }
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    readSize = fread(tmp, 1, size, fp);
    DBG_B("size/readSize = %d/%d\n", size, readSize);
    fp_result = fopen(result_filename, "wb");
    if(fp_result == NULL) {
        DBG_R("Failed to open file(%s)\n", result_filename);
        fclose(fp);
        return;
    }
    fwrite(tmp, 1, size, fp_result);
    fclose(fp);
    fclose(fp_result);
}

int main(int argc, char** argv)
{

    if(argc < 2) {
        DBG_R("argument is too few(argc = %d)\n", argc);
        return -1;
    }
    else if(argc > 3) {
        DBG_R("argument is too many(argc = %d)\n", argc);
        return -1;
    }

    if(argc == 2) {
        get_file_size(argv[1]);
    }
    if(argc == 3) {
        int count = 0;
        count = list_dir(argv[2]);
        DBG_B("count = %d\n", count);
    }

    return 0;
}