/*
 * =====================================================================================
 *
 *       Filename:  memalloc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 03월 29일 18시 50분 11초
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

#define	C_RED					"\033[31m"
#define	C_END					"\033[0m"
#define DBG_R(fmt, arg...)		fprintf(stderr, C_RED "%s:%d>" C_END fmt, __FILE__, __LINE__, ##arg)

static int write_file(char* writeFilename, char* readFilename)
{
	enum {
		TEST_WRITE_SIZE = 17 * 1024 * 1024,
		WRITE_UNIT = 1024,
	};
	FILE* fp;
	FILE* readFp;
	char buffer[WRITE_UNIT];
	char fname[128];
	char readFname[128];
	int ret = 0;
	int length;

	snprintf(fname, sizeof(fname), "%s", writeFilename);
	fp = fopen(fname, "wb");
	if(fp == NULL) {
		DBG_R("fp is NULL\n");
		return 0;
	}

	snprintf(readFname, sizeof(readFname), "%s", readFilename);
	readFp = fopen(readFname, "rb");
	if(readFp == NULL) {
		DBG_R("readFp is NULL\n");
		return 0;
	}

	while(1)
	{
		length = fread(buffer, 1, WRITE_UNIT, readFp);
		if(length <= 0)
		{
			break;
		}
		fwrite (buffer, 1, length, fp);
		ret += length;
		if(ret > TEST_WRITE_SIZE) {
			DBG_R("ret = %d\n", ret);
			break;
		}
	}

	fclose(fp);

	return ret;
}


int main(int argc, char** argv)
{
	if(argc < 3) {
		DBG_R("argc is too few(%d)\n", argc);
		return -1;
	}

	int result = write_file(argv[1], argv[2]);
	DBG_R("result = %d\n", result);

	return 0;
}
