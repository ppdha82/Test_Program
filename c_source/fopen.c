/*
 * =====================================================================================
 *
 *       Filename:  fopen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018년 10월 31일 10시 09분 23초
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

#include <fcntl.h>
#include <unistd.h>

#include "debug_print.h"

int write_debug(const char* debug_log_file, const char* file, int line, const char* log)
{
	int fd = -1;
	char buf[256];

	fd = open(debug_log_file, O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1) {
		return -1;
	}

	memset(buf, 0, sizeof(buf));

	sprintf(buf, "[%s:%d]", file, line);
	if (strlen(log) > 0 && log != NULL) {
		strncat(buf, log, strlen(log));
	}
	strcat(buf, "\n\0");

	if (write(fd, buf, sizeof(buf)) == -1) {
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}

int main(int argc, char** argv)
{
	FILE *pf;
	int filename_len = 0;

	if(argc != 2) {
		_DBG_R("Few argument (count: %d)\n", argc);
		return -1;
	}

	if(argv[1] == NULL) {
		_DBG_R("Filename is NULL\n");
		return -1;
	}
	filename_len = strlen(argv[1]);
	if(filename_len <= 0) {
		_DBG_R("Invalid filename(%s)\n", argv[1]);
		return -1;
	}

	_DBG_C("Filename = %s\n", argv[1]);
	pf = fopen(argv[1], "w");
	if (pf != NULL) {
		fputs("fopen example", pf);
		write_debug("debug.log", __FILE__, __LINE__, "test log");
		fclose (pf);
	}

	return 0;
}
