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
#define ONVIF_SETUP_FILE	"test.txt"

#include <fcntl.h>
#include <unistd.h>

int write_debug(const char* file, int line, const char* log)
{
	int fd = -1;
	char buf[256];

	fd = open("debug.txt", O_CREAT | O_RDWR | O_APPEND);
	if (fd == -1)
	{
		return -1;
	}

	memset(buf, 0, sizeof(buf));

	sprintf(buf, "[%s:%d]", file, line);
	if (strlen(log) > 0 && log != NULL)
	{
		strncat(buf, log, strlen(log));
	}
	strcat(buf, "\n\0");

	if (write(fd, buf, sizeof(buf)) == -1)
	{
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}

int _create_onvif_setup (void)
{
	const char* error_msg = "Failed to create file";
	FILE* _fp = fopen (ONVIF_SETUP_FILE, "w");
	if (_fp == NULL)
	{
		write_debug(__FILE__, __LINE__, error_msg);
		return -1;
	}
	fclose(_fp);
	write_debug (__FILE__, __LINE__, "Here I am");

	return 0;
}

FILE* _open_onvif_setup (int* isExist)
{
	write_debug (__FILE__, __LINE__, "Here I am");
	FILE* _fp = fopen (ONVIF_SETUP_FILE, "r");
	write_debug (__FILE__, __LINE__, "Here I am");
	//return NULL;
	write_debug (__FILE__, __LINE__, "Here I am");
	if (_fp == NULL)
	{
		write_debug (__FILE__, __LINE__, "Here I am");
		int result = _create_onvif_setup();
		write_debug (__FILE__, __LINE__, "Here I am");
		if (result == -1)
		{
			return NULL;
		}
		_fp = fopen (ONVIF_SETUP_FILE, "r");
		if (isExist != NULL)
		{
			*isExist = 1;
		}
		write_debug (__FILE__, __LINE__, "Here I am");
		return _fp;
	}

	if (isExist != NULL)
	{
		*isExist = 0;
	}

	write_debug (__FILE__, __LINE__, "Here I am");
	return _fp;
}

int _load_onvif_setup_file(int* isExist)
{
	write_debug (__FILE__, __LINE__, "Here I am");
	FILE* _fp = _open_onvif_setup (isExist);
	if (_fp != NULL)
	{
		fclose(_fp);
	}
	write_debug (__FILE__, __LINE__, "Here I am");
	return -1;
	write_debug (__FILE__, __LINE__, "Here I am");

	if (_fp == NULL)
	{
		write_debug(__FILE__, __LINE__, "Failed to open xml file");
		return NULL;
	}
	write_debug (__FILE__, __LINE__, "Here I am");
	return -1;
	write_debug (__FILE__, __LINE__, "Here I am");

	fclose (_fp);
	return 0;
}

int main(void)
{
	FILE *pf;
	pf = fopen("myfile.txt", "r+");
	if (pf != NULL)
	{
		fputs("fopen example", pf);
		fclose (pf);
	}

	int a = -1;
	int result = -1;
	result = _load_onvif_setup_file(&a);
	printf ("result = %d\n", result);

	return 0;
}
