/*
 * =====================================================================================
 *
 *       Filename:  debug.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018년 09월 10일 15시 49분 15초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DH. Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus HFocus HFocus HFocus HFocus HFocus HFocus HFocus HFocus HFocus H|COMPANY|SSSSSSSSSS
 *
 * =====================================================================================
 */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int write_debug(int line, char* log)
{
	int fd = -1;
	char buf[256];

	fd = open("debug.txt", O_CREAT | O_RDWR | O_TRUNC);
	if (fd == -1)
	{
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	lseek(fd, 0, SEEK_END);

	sprintf(buf, "[%d]", line);
	if (strlen(log) > 0 && log != NULL)
	{
		strncat(buf, log, strlen(log));
	}
	strcat(buf, "\0");

	if (write(fd, buf, sizeof(buf)) == -1)
	{
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}

int main(void)
{
	write_debug(__LINE__, "hello world");
	return 0;
}
