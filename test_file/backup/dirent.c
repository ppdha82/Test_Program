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

void print_help(int argc)
{
	if(argc < 2) {
		printf("[%s:%d] too few argument\n", __FILE__, __LINE__);
	}
	else {
		printf("[%s:%d] too many argument\n", __FILE__, __LINE__);
	}
}

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

int check_filename_rule(char* fname, const char* target)
{
	int ret = 0;
	if(fname == NULL || target == NULL) {
		if(fname == NULL) {
			printf("[%s:%d] fname is NULL\n", __FILE__, __LINE__);
		}
		if(target == NULL) {
			printf("[%s:%d] target is NULL\n", __FILE__, __LINE__);
		}
		ret = -1;
		goto check_rule_out;
	}

	// start time & end time
	char* ptr_1st = strchr(fname, '_');
	if(ptr_1st == NULL) {
		printf("[%s:%d] This file is not matched with file name rule\n", __FILE__, __LINE__);
		ret = -1;
		goto check_rule_out;
	}

	const int TIME_SIZE_RULE = 12;
	int fname_size = ptr_1st - fname;
	if(fname_size != TIME_SIZE_RULE) {
		printf("[%s:%d] This file is not matched with file name rule(length = %d)\n", __FILE__, __LINE__, fname_size);
		ret = -1;
		goto check_rule_out;
	}
	char* ptr_2nd = strchr(ptr_1st + 1, '.');
	fname_size = ptr_2nd - ptr_1st - 1;	// -1 은 '_' 의 위치가 포함되어 적용함
	if(fname_size != TIME_SIZE_RULE) {
		printf("[%s:%d] This file is not matched with file name rule(length = %d)\n", __FILE__, __LINE__, fname_size);
		ret = -1;
		goto check_rule_out;
	}

	// MP4 file
	//const char* validExtName = ".mp4";
	if(strstr(ptr_2nd, target) == NULL) {
		printf("[%s:%d] %s is not \"%s\" file\n", __FILE__, __LINE__, ptr_2nd, target);
		ret = -1;
	}
check_rule_out:
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
        printf("%s\n",entry->d_name);
    }

    closedir(dir);
	return file_count;
}

int find_file_in_dir(const char *path, const char* target, char* filename, int size)
{
	enum { GET_ONE_FILE, FILE_COUNT };
    struct dirent *entry;
	int file_count = 0;
	int invalid_file_count = 0;
	int ret = -1;
	int mode = GET_ONE_FILE;
	if(filename == NULL) {
		mode = FILE_COUNT;
	}

    DIR *dir = opendir(path);
    if (dir == NULL) {
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
		char* fname = entry->d_name;
		if(0 != check_valid_filename(fname)) {
			continue;
		}
		ret = check_filename_rule(fname, target);
		if(ret < 0) {
			printf("[%s:%d] invalid_file(\"%s\") = %s\n", __FILE__, __LINE__, target, fname);
			invalid_file_count++;
			continue;
		}

		if(mode == GET_ONE_FILE) {
			int d_name_len = strlen(entry->d_name);
			if(size > d_name_len) {
				memcpy(filename, entry->d_name, d_name_len);
				filename[d_name_len] = '\0';
				file_count++;
				printf("%s\n",entry->d_name);
			}
			goto find_file_out;
		}
		else {
			file_count++;
			printf("%s\n",entry->d_name);
		}
    }
	printf("[%s:%d] invalid_file_count(\"%s\") = %d\n", __FILE__, __LINE__, target, invalid_file_count);

find_file_out:
    closedir(dir);
	return file_count;
}

int main(int argc, char** argv)
{
	if(argc != 2 && argc != 3) {
		print_help(argc);
		return -1;
	}
	printf("[%s:%d] argv[1] = %s\n", __FILE__, __LINE__, argv[1]);
	int file_count =  0;
	if(argc == 2) {
		file_count = list_dir(argv[1]);
	}
	else if(argc == 3) {
		printf("[%s:%d] argv[2] = %s\n", __FILE__, __LINE__, argv[2]);
		//file_count = find_file_in_dir(argv[1], argv[2], NULL, 0);
		char mp4File[32];
		file_count = find_file_in_dir(argv[1], argv[2], mp4File, sizeof(mp4File));
		printf("[%s:%d] mp4File = %s\n", __FILE__, __LINE__, mp4File);
	}
	printf("[%s:%d] file count = %d\n", __FILE__, __LINE__, file_count);
	return 0;
}
