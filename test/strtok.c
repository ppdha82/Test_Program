/*
 * =====================================================================================
 *
 *       Filename:  strtok.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019년 10월 24일 15시 13분 51초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int print_help(int argc, char** argv)
{
	if(argc < 3) {
		printf("[%s:%d] too few argument\n", __FILE__, __LINE__);
	}
	else {
		printf("[%s:%d] too many argument\n", __FILE__, __LINE__);
	}
	printf("[%s:%d] %s [ORIGINAL_STRING] [TOKEN_STRING]\n", __FILE__, __LINE__, argv[0]);
	return 0;
}

int main (int argc, char** argv)
{
	if(argc != 3) {
		return print_help(argc, argv);
	}

#if 1
	char buf[1024];
	int tokenCount = 0;
	char* tmp_pos = buf;

	memset(buf, 0, sizeof(buf));
	memcpy(buf, argv[1], sizeof(buf));
	printf("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
	tmp_pos = strtok(tmp_pos, argv[2]);
	while(tmp_pos != NULL) {
		printf("[%s:%d] (%d) tmp_pos = %s(%p)\n", __FILE__, __LINE__, tokenCount, tmp_pos, tmp_pos);
		tmp_pos = strtok(NULL, argv[2]);
		tokenCount++;
	}
	printf("[%s:%d] (%d) tmp_pos = %s; buf = %s\n", __FILE__, __LINE__, tokenCount, tmp_pos, buf);
#else
	//char input[24] = "192.168.0.148";
	char input[24] = "192.168.0.148.50200";
	char buf[24];
	char* tmp_addr;
	int dot_cnt = 0;
	char ipAddr[16];
	memset(buf, 0, sizeof(buf));
	memset(ipAddr, 0, sizeof(ipAddr));

	memcpy(buf, input, sizeof(input));
	printf("[%s:%d] input = %s(%p)\n", __FILE__, __LINE__, input, input);
	tmp_addr = strtok (input, ".");
	printf("[%s:%d] input = %s(%p)\n", __FILE__, __LINE__, input, input);

	while (tmp_addr != NULL) {
		printf("[%s:%d] (%d) tmp_addr = %s(%p)\n", __FILE__, __LINE__, dot_cnt, tmp_addr, tmp_addr);
		tmp_addr = strtok (NULL, ".");
		if(dot_cnt == 3) {
			memcpy(ipAddr, buf, tmp_addr - input - 1);
			printf("[%s:%d] ipAddr = %s\n", __FILE__, __LINE__, ipAddr);
			printf("[%s:%d] port = %d\n", __FILE__, __LINE__, atoi(tmp_addr));
		}
		dot_cnt++;
	}
#endif
	return 0;
}
