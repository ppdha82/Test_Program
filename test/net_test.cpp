/*
 * =====================================================================================
 *
 *       Filename:  net_test.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2018년 09월 18일 16시 11분 55초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  DH. Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus HFocus HFocus HFocus HFocus HFocus HFocus HFocus HFocus HFocus H|COMPANY|SSSSSSSSSS
 *
 * =====================================================================================
 */


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char buf[256];
    struct in_addr laddr;
    int stat;

    while(1)
    {
        // 인터넷 주소를 입력 받는다.
        printf("INPUT ADDRESS : ");
        fgets(buf, 255, stdin);
		if (strncmp(buf, "q", strlen(buf)) == 0)
		{
			break;
		}
        buf[strlen(buf) -1] = 0x00;
        if (strcmp(buf, "quit") == 0)
		{
			printf("[%s:%d] quit away application\n", __FILE__, __LINE__);
			break;
		}

        stat = inet_aton(buf, &laddr);
        if (!stat)
        {
            printf("Format Error\n");
        }
        else
        {
			int addr = laddr.s_addr;
			printf("ip_addr	: %d.%d.%d.%d\n", (addr >> 24) & 0xff, (addr >> 16) & 0xff, (addr >> 8) & 0xff, addr & 0xff);
            printf("inet_addr    : %s => %d\n", buf, laddr.s_addr);
            printf("inet_ntoa    : %d => %s\n", laddr.s_addr, inet_ntoa(laddr));
        }
    }
    return 0;
}
