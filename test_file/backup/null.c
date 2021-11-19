/*
 * =====================================================================================
 *
 *       Filename:  null.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018년 11월 02일 22시 49분 37초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdio.h>

int main (void)
{
	char temp[16] = "";

	if (temp == NULL)
	{
		printf ("temp is NULL\n");
	}
	else
	{
		printf ("temp is not NULL\n");
	}
	if ("" == NULL)
	{
		printf ("\"\" is NULL\n");
	}
	else
	{
		printf ("\"\" is not NULL\n");
	}
	return 0;
}
