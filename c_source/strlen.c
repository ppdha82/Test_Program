/*
 * =====================================================================================
 *
 *       Filename:  strlen.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 07월 29일 13시 23분 41초
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

int main(int argc, char** argv)
{
	int i = 0;

	const char* test1 = "TrajEventJpeg";
	const char* test2 = "TrajEvent";

	printf("[%s:%d] test1 == test2 => %d\n", __FILE__, __LINE__, (strlen(test1) == strlen(test2)));
	printf("[%s:%d] test1 == test1 => %d\n", __FILE__, __LINE__, (strlen(test1) == strlen(test1)));

	return 0;
}
