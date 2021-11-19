/*
 * =====================================================================================
 *
 *       Filename:  ascii.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 05월 18일 20시 17분 46초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */


#include <stdio.h>

int main(void)
{
	enum { AES_KEY_BYTE = 16, };

	printf("special character = 21 \n");	// !
	printf("special character = 22 \n");	// !
	printf("special character = 23 \n");	// !
	printf("special character = 24 \n");	// !
	printf("special character = 25 \n");	// !
	printf("special character = 26 \n");	// !
	printf("special character = 27 \n");	// !
	printf("special character = 28 \n");	// !
	printf("special character = 29 \n");	// !
	printf("special character = 30 \n");	// !
	unsigned char aes_key[AES_KEY_BYTE] = "focusipc2018!!!";

	int i;
	for(i = 0;i < AES_KEY_BYTE;i++) {
		printf("[%d] i = %x\n", i, aes_key[i]);
	}
	return 0;
}
