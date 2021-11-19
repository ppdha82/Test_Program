/*
 * =====================================================================================
 *
 *       Filename:  strstr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 13일 16시 26분 15초
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
#include <stdlib.h>

#define	__DEBUG_ON__
#include "debug_print.h"

enum { ARG_CNT = 3, };

int print_help(int argc, char **argv)
{
	if(argc < ARG_CNT) {
		printf("[%s:%d] too few argument\n", __FILE__, __LINE__);
	}
	else {
		printf("[%s:%d] too many argument\n", __FILE__, __LINE__);
	}
	printf("[%s:%d] %s [ORIGINAL_STRING][TOKEN]\n", __FILE__, __LINE__, argv[0]);

	return 0;
}

void test1(char** argv)
{
	char buf[1024];
	char target[1024];
	snprintf(buf, sizeof(buf), "%s", argv[1]);
	char* src = buf;
	char* ret;
	printf("[%s:%d] ORIGINAL_STRING = %s(%s); TOKEN = %s(%ld)\n", __FILE__, __LINE__, argv[1], buf, argv[2], strlen(argv[2]));

	do {
		ret = strstr(src, argv[2]);
		printf("[%s:%d] ret : %s(%p); src : %s(%p)(size = %ld)\n", __FILE__, __LINE__, ret, ret, src, src, ret - src);
		snprintf(target, ret - src + 1, "%s", src);
		printf("[%s:%d] target : %s\n", __FILE__, __LINE__, target);
		src = (ret + strlen(argv[2]));
	} while(ret != NULL || strlen(src) > 0);
}

void test2(const char* strTarget)
{
	const char* STR_REF = "UTC";
	const char* PLUS = "+";
	const char* MINUS = "-";

	char* strUtc;
	int direction = 0;	// 1: +, -1: -
	int hour = 0;
	int minute = 0;

	DBG_C("####################################\n");
	DBG_B("strTarget = %s\n", strTarget);
	strUtc = strstr(strTarget, STR_REF) + strlen(STR_REF);
	DBG_R("strUtc = %s\n", strUtc);
	if(strncmp(strUtc, PLUS, strlen(PLUS)) == 0) {
		DBG_G("calculate = %c\n", strUtc[0]);
		direction = 1;
		//strUtc += strlen(PLUS);
		strUtc++;
	}
	else if(strncmp(strUtc, MINUS, strlen(MINUS)) == 0) {
		DBG_G("calculate = %c\n", strUtc[0]);
		direction = -1;
		//strUtc += strlen(MINUS);
		strUtc++;
	}
	else if(strlen(strUtc) <= 0) {
		DBG_Y("This is UTC\n");
		goto End;
	}
	else {
		DBG_Y("This is Error\n");
		goto End;
	}

	if(strUtc[0] >= '1' && strUtc[0] <= '9') {
		char tmp = strUtc[0];
		hour = tmp - '0';
		strUtc++;
		if(strUtc[0] >= '1' && strUtc[0] <= '9') {
			char tmp = strUtc[0];
			hour = hour * 10 + (tmp - '0');
			strUtc++;
		}
		DBG_R("hour = %d\n", hour);
	}

	if(strUtc[0] == ':') {
		strUtc++;
		char tmp = strUtc[0];
		char tmp1 = strUtc[1];
		minute = (tmp - '0') * 10 + (tmp1 - '0');
		DBG_R("minute = %d\n", minute);
	}
End:
	DBG_C("####################################\n");
}

int main(int argc, char **argv)
{
	if(argc != ARG_CNT) {
		//return print_help(argc, argv);
	}

	//test1(argv);
	const char* STR_TEST1 = "UTC+9:30";
	const char* STR_TEST2 = "UTC-3:30";
	const char* STR_TEST3 = "UTC";
	const char* STR_TEST4 = "UTC-11";
	const char* STR_TEST5 = "UTC1";
	test2(STR_TEST1);
	test2(STR_TEST2);
	test2(STR_TEST3);
	test2(STR_TEST4);
	test2(STR_TEST5);

	return 0;
}
