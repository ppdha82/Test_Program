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

int main(int argc, char **argv)
{
	if(argc != ARG_CNT) {
		return print_help(argc, argv);
	}
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
	return 0;
}
