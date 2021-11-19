/*
 * =====================================================================================
 *
 *       Filename:  system.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 22일 19시 49분 43초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i = 0;
	int retval;
    retval = system("curl");
    printf("Exit Status %d\n", retval);
	return 0;
}
