/*
 * =====================================================================================
 *
 *       Filename:  strcmp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 08월 04일 20시 22분 12초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>

#define XISAPI_SYSTEM_VIDEO_PRIVACYMASK				"/ISAPI/System/Video/Inputs/channels/1/privacyMask"			// GET, PUT
#define XISAPI_SYSTEM_VIDEO_PRIVACYMASK_REGION_1	"/ISAPI/System/Video/Inputs/channels/1/privacyMask/regions/1"			// GET, PUT

int main(int argc, char** argv)
{
	printf("[%s:%d] strcmp result = %d\n", __FILE__, __LINE__, strcmp(XISAPI_SYSTEM_VIDEO_PRIVACYMASK, XISAPI_SYSTEM_VIDEO_PRIVACYMASK_REGION_1));
	return 0;
}
