/*
 * =====================================================================================
 *
 *       Filename:  get_eth_ipaddr.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 03월 31일 17시 54분 07초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int getHostAddress(char *str, const char* ethernet)
{
    int             sock, ret;
    struct ifreq    ifr;
 
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        printf("%s: IP Address Get socket() Create error\n", __FUNCTION__);
        return -1;
    }
 
 	ifr.ifr_addr.sa_family = AF_INET;
    sprintf(ifr.ifr_name, "%s", (char*)ethernet ); 
 
    // Get IP Adress
    ret = ioctl(sock, SIOCGIFADDR, &ifr);
    if (ret < 0) {
        printf("%s: IP not found\n", __FUNCTION__);
        close(sock);
        return -1;
    }
    close(sock);
 
    strcpy(str, inet_ntoa ( ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr )); 

    return 0;
}

int main(void)
{
	char buf[128];
	getHostAddress(buf, "eth0");
	printf("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
	memset(buf, 0, sizeof(buf)); 
	getHostAddress(buf, "enp3s0");
	printf("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
	memset(buf, 0, sizeof(buf));
	getHostAddress(buf, "enp6s0");
	printf("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
	return 0;
}
