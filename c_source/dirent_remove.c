/*
 * =====================================================================================
 *
 *       Filename:  dirent_remove.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 28일 17시 20분 45초
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
#include <stdarg.h>
#include <unistd.h>

enum { ARGC_MIN = 2, ARGC_MAX = 2, };

typedef enum {
	TVMC_GET_LOGS_SYSTEM,
	TVMC_GET_LOGS_ACCESS,
	TVMC_GET_LOGS_EVENT,
	TVMC_GET_LOGS_MAX,
} TVMC_LOG_TYPE_E;

const char* tvmc_log_category[TVMC_GET_LOGS_MAX] = { "system", "access", "event" };

void PRINT_DBG(char* file, int line, char* fmt, ...)
{
	printf("\033[32m[%s:%d]", file, line);
	va_list arg;
	va_start(arg, fmt);
	vprintf(fmt, arg);
	va_end(arg);
	printf("\033[0m\n");
}

void print_help(int argc)
{
	if(argc < ARGC_MIN) {
		PRINT_DBG(__FILE__, __LINE__, "too few argument\n");
	}
	else if(argc > ARGC_MAX) {
		PRINT_DBG(__FILE__, __LINE__, "too many argument\n");
	}
	else {
		PRINT_DBG(__FILE__, __LINE__, "HELP\n");
	}
}

void list_dir(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n",entry->d_name);
    }

    closedir(dir);
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

int check_filename_rule(char *fname, const char *ext_target)
{
	int ret = 0;
	if(fname == NULL || ext_target == NULL) {
		if(fname == NULL) {
			PRINT_DBG(__FILE__, __LINE__,"fname is NULL\n");
		}
		if(ext_target == NULL) {
			PRINT_DBG(__FILE__, __LINE__,"ext_target is NULL\n");
		}
		ret = -1;
		goto check_rule_out;
	}

	// start time & end time
	char *ptr_1st = strchr(fname, '_');
	if(ptr_1st == NULL) {
		PRINT_DBG(__FILE__, __LINE__,"This file is not matched with file name rule\n");
		ret = -1;
		goto check_rule_out;
	}

	const int TIME_SIZE_RULE = 12;
	int fname_size = ptr_1st - fname;
	if(fname_size != TIME_SIZE_RULE) {
		PRINT_DBG(__FILE__, __LINE__,"This file is not matched with file name rule(length = %d)\n", fname_size);
		ret = -1;
		goto check_rule_out;
	}

	char *ptr_2nd = strchr(ptr_1st + 1, '.');
	fname_size = ptr_2nd - ptr_1st - 1; // -1 은 '_' 의 위치가 포함되어 적용함
	if(fname_size != TIME_SIZE_RULE) {
		PRINT_DBG(__FILE__, __LINE__,"This file is not matched with file name rule(length = %d)\n", fname_size);
		ret = -1;
		goto check_rule_out;
	}

	// MP4 file
	//const char* validExtName = ".mp4";
	if(strstr(ptr_2nd, ext_target) == NULL) {
		PRINT_DBG(__FILE__, __LINE__,"%s is not \"%s\" file\n", ptr_2nd, ext_target);
		ret = -1;
	}

check_rule_out:
	return ret;
}

int clean_invalid_mp4_file(const char* path)
{
	const char* target = ".mp4";
	struct dirent *entry;
	int invalid_file_count = 0;
	int ret = -1;
	char cmd[128];
	char inputLine[1024];

	DIR *dir = opendir(path);

	if (dir == NULL) {
		return 0;
	}

	while((entry = readdir(dir)) != NULL) {
		char *fname = entry->d_name;
		if(0 != check_valid_filename(fname)) {
			continue;
		}
		ret = check_filename_rule(fname, target);
		if(ret < 0) {
			printf("[%s:%d] invalid_file(\"%s\") = %s\n", __FILE__, __LINE__, target, fname);
			invalid_file_count++;
			FILE* fp = NULL;
			memset(cmd, 0, sizeof(cmd));
			snprintf(cmd, sizeof(cmd), "rm -f %s/%s", path, fname);
			PRINT_DBG(__FILE__, __LINE__, "%s", cmd);
			fp = popen(cmd, "w");
			while(fgets(inputLine, sizeof(inputLine), fp) != NULL) {
				sleep(1);
				PRINT_DBG(__FILE__, __LINE__, "running to remove file %s", fname);
			}
			fclose(fp);
		}
	}
	printf("[%s:%d] invalid_file_count(\"%s\") = %d\n", __FILE__, __LINE__, target, invalid_file_count);

find_file_out:
	closedir(dir);
	return invalid_file_count;
}

int check_tview_log_filename_rule(char *fname, const char *ext_target)
{
	int ret = -1;
	if(fname == NULL || ext_target == NULL) {
		if(fname == NULL) {
			PRINT_DBG(__FILE__, __LINE__,"fname is NULL\n");
		}
		if(ext_target == NULL) {
			PRINT_DBG(__FILE__, __LINE__,"ext_target is NULL\n");
		}
		goto check_log_rule_out;
	}

	// start time & end time
	char *ptr_1st = strchr(fname, '_');
	if(ptr_1st == NULL) {
		PRINT_DBG(__FILE__, __LINE__,"This file is not matched with file name rule\n");
		goto check_log_rule_out;
	}

	const int TIME_SIZE_RULE = 12;
	int fname_size = ptr_1st - fname;
	if(fname_size != TIME_SIZE_RULE) {
		PRINT_DBG(__FILE__, __LINE__,"This file is not matched with file name rule(length = %d)\n", fname_size);
		goto check_log_rule_out;
	}

	char *ptr_2nd = strchr(ptr_1st + 1, '.');
	PRINT_DBG(__FILE__, __LINE__, "ptr_1st + 1 = %s; ptr_2nd = %s\n", ptr_1st + 1, ptr_2nd);
	int i = 0;
	for(i = TVMC_GET_LOGS_SYSTEM;i < TVMC_GET_LOGS_MAX;i++) {
		if(strstr(ptr_1st + 1, tvmc_log_category[i]) != 0) {
			PRINT_DBG(__FILE__, __LINE__, "ptr_1st + 1 = %s; category[%d] = %s\n", ptr_1st + 1, i, tvmc_log_category[i]);
			break;
		}
	}
	
	PRINT_DBG(__FILE__, __LINE__,"i = %d\n", i);

	if(i == TVMC_GET_LOGS_MAX) {
		PRINT_DBG(__FILE__, __LINE__,"This file is not matched with naming rule\n");
		goto check_log_rule_out;
	}

	// log file
	if(strstr(ptr_2nd, ext_target) == NULL) {
		PRINT_DBG(__FILE__, __LINE__,"%s is not \"%s\" file\n", ptr_2nd, ext_target);
	}
	ret = 0;

check_log_rule_out:
	return ret;
}

int find_tview_log_file_in_dir(const char *path, const char *target, char *filename, int size)
{
	struct dirent *entry;
	int file_count = 0;
	int invalid_file_count = 0;
	int ret = -1;
	DIR *dir = opendir(path);

	if (dir == NULL) {
		PRINT_DBG(__FILE__, __LINE__,"dir is NULL\n");
		return 0;
	}

	while((entry = readdir(dir)) != NULL) {
		char *fname = entry->d_name;
		if(0 != check_valid_filename(fname)) {
			continue;
		}
		ret = check_tview_log_filename_rule(fname, target);
		if(ret < 0) {
			PRINT_DBG(__FILE__, __LINE__,"invalid_file(\"%s\") = %s\n", target, fname);
			invalid_file_count++;
			continue;
		}

		file_count++;
		printf("%s\n", entry->d_name);
	}
	PRINT_DBG(__FILE__, __LINE__,"invalid_file_count(\"%s\") = %d\n", target, invalid_file_count);

find_file_out:
	closedir(dir);
	return file_count;
}

int getargs(int argc, char **argv)
{
    int ch, i, r, reflag;
#if 0
    if ((g.progname = strrchr(argv[0], '/')) != NULL) {
        ++g.progname;
    } else {
        g.progname = argv[0];
    }

#endif
	PRINT_DBG(__FILE__, __LINE__, "argc = %d; MIN = %d; MAX = %d\n", argc, ARGC_MIN, ARGC_MAX);
    if ((argc < ARGC_MIN) || (argc > ARGC_MAX) || (strcmp("--help", argv[1]) == 0)) {
        print_help(argc);
		return -1;
    }
    /*
     * If the first character of optstring is '+' or the environment variable
     * POSIXLY_CORRECT is set, then option processing stops as soon as a
     * nonoption argument is encountered.
     */
    while ((ch = getopt(argc, argv, "+:c:Chil:L:np:P:t:Ty")) != -1) {
        switch (ch) {
            case 'c':
                //g.opt.tries = atoi(optarg);
                break;
#if 0
            case 'C':
                g.opt.fatal_more_tries = true;
                break;
            case 'h':
                usage(0);

            case 'i':
                g.opt.ignore_case = true;
                break;

            case 'l':
                g.opt.log_to_pty = optarg;
                break;

            case 'L':
                g.opt.log_from_pty = optarg;
                break;

            case 'n':
                g.opt.nohup_child = true;
                break;

            case 'p':
                g.opt.password = arg2pass(optarg);
                for (i = 0; i < strlen(optarg); ++i) {
                    optarg[i] = '*';
                }
                if (g.opt.password == NULL) {
                    fatal(PRINT_DBGOR_USAGE, "Error: failed to get password");
                }
                break;
            case 'P':
                g.opt.passwd_prompt = optarg;
                break;

            case 't':
                g.opt.timeout = atoi(optarg);
                break;

            case 'T':
                g.opt.fatal_no_prompt = true;
                break;

            case 'y':
                g.opt.auto_yesno = true;
                break;
#if 0
            case 'Y':
                g.opt.yesno_prompt = optarg;
                break;
#endif
#endif

            case '?':
            default:
                PRINT_DBG(__FILE__, __LINE__, "Error: unknown option '-%c'", ch);
        }
    }
#if 0
    argc -= optind;
    argv += optind;

    if (0 == argc) {
        fatal(PRINT_DBGOR_USAGE, "Error: no command specified");
    }
    g.opt.command = argv;

    if (0 == strlen(g.opt.passwd_prompt) ) {
        fatal(PRINT_DBGOR_USAGE, "Error: empty prompt");
    }
    /* Password: */
    reflag = 0;
    reflag |= g.opt.ignore_case ? REG_ICASE : 0;
    r = regcomp(&g.opt.re_prompt, g.opt.passwd_prompt, reflag);
    if (r != 0) {
        fatal(PRINT_DBGOR_USAGE, "Error: invalid RE for password prompt");
    }
    /* (yes/no)? */
    r = regcomp(&g.opt.re_yesno, g.opt.yesno_prompt, reflag);
    if (r != 0) {
        fatal(PRINT_DBGOR_USAGE, "Error: invalid RE for yes/no prompt");
    }
#endif
	return 0;
}



int main(int argc, char** argv)
{
	if(getargs(argc, argv) < 0) {
		return -1;
	}
	printf("[%s:%d] directory = %s\n", __FILE__, __LINE__, argv[1]);
	int fileCount =  0;
#if 0
	if(argc == ARGC_MIN) {
		int invalid_file_count = clean_invalid_mp4_file(argv[1]);
		PRINT_DBG(__FILE__, __LINE__, "invalid_file_count = %d\n", invalid_file_count);
	}
#else
	const char* PATH_LOG = "/mnt/sda1/log";
	const char* LOG_EXT = ".log";

	fileCount = find_tview_log_file_in_dir(PATH_LOG, LOG_EXT, NULL, 0);
	PRINT_DBG(__FILE__, __LINE__, "fileCount = %d\n", fileCount);
#endif

	return 0;
}
