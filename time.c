/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019년 12월 12일 14시 42분 09초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>

int main (void)
{
	struct tm tm;
	time_t t;
	struct timeval now;

	gettimeofday (&now, NULL);
	t = now.tv_sec;
	localtime_r (&t, &tm);

	printf ("[%s:%d] time = %2d:%2d:%2d\n", __FILE__, __LINE__, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return 0;
}
