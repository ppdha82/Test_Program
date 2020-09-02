/*
 * =====================================================================================
 *
 *       Filename:  unicode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 05월 19일 13시 25분 07초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <wchar.h>

int main(void)
{
	wchar_t temp[16];

	swprintf(temp, sizeof(temp), L"°C");
	wprintf(L"[%s:%d] celcius = %S\n", __FILE__, __LINE__, temp);

	return 0;
}
