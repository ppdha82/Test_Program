/*
 * =====================================================================================
 *
 *       Filename:  md5sum.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 03월 25일 14시 26분 27초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE* fp;
	char buf[1024];
	char tmp[1024];
	char md5hash[64];
	char filename[64];
	char* ref;

	fp = popen("/edvr/md5sum fopen", "r");
	if (fp == NULL) {
		printf("[%s:%d] fp is NULL\n", __FILE__, __LINE__);
		return -1;
	}

	do {
		fgets(buf, sizeof(buf), fp);
		printf("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
		memcpy(tmp, buf, sizeof(tmp));
		ref = strtok(tmp, " ");
		printf("[%s:%d] ref = %s\n", __FILE__, __LINE__, ref);
		snprintf(md5hash, sizeof(md5hash), "%s", ref);
		ref = strtok(NULL, " ");
		printf("[%s:%d] ref = %s\n", __FILE__, __LINE__, ref);
		snprintf(filename, sizeof(filename), "%s", ref);
	} while(0);
	if(strncmp("fopen", filename, strlen("fopen")) == 0) {
		printf("[%s:%d] filename is same(%s)\n", __FILE__, __LINE__, filename);
	}
	else {
		printf("[%s:%d] filename is NOT same(filename = %s)(%s)\n", __FILE__, __LINE__, filename, "fopen");
	}
	printf("[%s:%d] program is finished\n", __FILE__, __LINE__);

	return 0;
}
