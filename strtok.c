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

int main (void)
{
	char input[20] = "192.168.0.148";
	char* tmp_addr;
	int dot_cnt = 0;

	tmp_addr = strtok (input, ".");
	while (tmp_addr != NULL) {
		dot_cnt++;
		printf ("[%s:%d] (%d) tmp_addr = %s\n", __FILE__, __LINE__, dot_cnt, tmp_addr);
		tmp_addr = strtok (NULL, ".");
	}
	return 0;
}
