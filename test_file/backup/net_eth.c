/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019년 05월 30일 19시 56분 10초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */


#include <net/if.h>
#include <sys/ioctl.h>

typedef unsigned char	uint8;

int main(void)
{
	int i;
    int sockfd = -1;
    uint8 *pdata = NULL;
    struct ifreq  ifr;
    int ret = -1;
	const char* dev = "eth0";
	char buff[6];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf ("[%s:%d] failed to socket\n", __FILE__, __LINE__);
		return 0;
	}

    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    ifr.ifr_hwaddr.sa_family = AF_INET;

    if (ioctl (sockfd, SIOCGIFHWADDR, &ifr) < 0)
	{
		printf ("[%s:%d] failed to ioctl\n", __FILE__, __LINE__);
		return 0;
	}

    pdata = (uint8*)ifr.ifr_hwaddr.sa_data;

    for (i = 0; i < 6; i++)
	{
		buff[i] = *pdata++;
		printf ("[%s:%d] buff = 0x%x(0x%x == 0x%x)\n", __FILE__, __LINE__, buff[i], *pdata, *(ifr.ifr_hwaddr.sa_data + i));
	}


	return 0;
}
