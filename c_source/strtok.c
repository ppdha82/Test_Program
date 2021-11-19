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

void test_code_1(char** argv)
{
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
}

void test_code_2(void)
{
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
}

void test_code_3(void)
{
	int i;
	const char* test_str = "001ff87ffff87ffff87ffff87ffff87ffff87ffff87ffff87ffff83ffff83ffff83ffff83ffff83ffff83e0000000000000000000000";
	char* p = (char *)test_str;
	enum { STR_OFFSET = 6, };
	char buf[STR_OFFSET];
	int size = strlen(test_str) / STR_OFFSET;

	printf("[%s:%d] size = %d\n", __FILE__, __LINE__, size);
	for(i = 0;i < size;i++) {
		strncpy(buf, p, STR_OFFSET);
		printf("[%s:%d] [i = %d] p = 0x%lx(0x%s)\n", __FILE__, __LINE__, i, strtol(buf, NULL, 16), buf);
		p += sizeof(char) * STR_OFFSET;
	}
}

int main (int argc, char** argv)
{
	if(argc != 3) {
		return print_help(argc, argv);
	}

#if 0
	test_code_1(argv);
	test_code_2();
#endif
	test_code_3();

	return 0;
}
