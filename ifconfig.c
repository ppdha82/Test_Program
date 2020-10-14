#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <arpa/inet.h>

int main(void)
{
    struct ifreq ifr;
    char ipstr[40];
    char netmaskStr[40];
    int s;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);

    if (ioctl(s, SIOCGIFADDR, &ifr) < 0) {
        printf("Error");
    }
	else {
        inet_ntop(AF_INET, ifr.ifr_addr.sa_data + 2, ipstr, sizeof(struct sockaddr));
        inet_ntop(AF_INET, ifr.ifr_netmask.sa_data + 2, netmaskStr, sizeof(struct sockaddr));
        printf("myOwn IP Address is %s\n", ipstr);
        printf("myOwn subnet mask is %s\n", netmaskStr);
    }

    return 0;
}
