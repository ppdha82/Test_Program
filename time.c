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

#include "debug_print.h"

int main (void)
{
	struct tm tm;
	time_t t;
	struct timeval now;

	gettimeofday (&now, NULL);
	t = now.tv_sec;
	localtime_r (&t, &tm);

	DBG_R("year %04d month %02d day %02d time %02d:%02d:%02d.%03ld; wday = %d; yday = %d; isdst = %d\n", \
	tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, now.tv_usec / 1000, tm.tm_wday, tm.tm_yday, tm.tm_isdst);
	return 0;
}
