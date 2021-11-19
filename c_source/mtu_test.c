#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <arpa/inet.h>

enum {
	SHOW,
	SET,
	GET,
	COMMAND_MAX,
};

const char* str_command[] = {
	"show",
	"set",
	"get",
};

const char* cmd_link = "ip link";
const char* cmd_dev = "eth0";

void print_help (void)
{
	printf ("=============================================================\n");
	printf (" mtu_test show - show device status\n");
	printf (" mtu_test set [MTU_VALUE] - set mtu of device\n");
	printf ("=============================================================\n");
}

void set_mtu (char* mtu)
{
	char buf[64];
	memset (buf, 0, sizeof (buf));
	snprintf (buf, sizeof (buf), "%s set %s mtu %s", cmd_link, cmd_dev, mtu);
	printf ("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
	popen (buf, "w");
}

void show_device_status (void)
{
	char buf[64];
	memset (buf, 0, sizeof (buf));
	snprintf (buf, sizeof (buf), "%s show %s", cmd_link, cmd_dev);
	printf ("[%s:%d] buf = %s\n", __FILE__, __LINE__, buf);
	popen (buf, "w");
}

void get_mtu (void)
{
    struct ifreq *ifr;
    struct sockaddr_in *sin;
    struct sockaddr *sa;

    struct ifconf ifcfg;
    int fd;
    int n;
    int numreqs = 30;
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&ifcfg, 0, sizeof(ifcfg));
    ifcfg.ifc_buf = NULL;
    ifcfg.ifc_len = sizeof(struct ifreq) * numreqs;
    ifcfg.ifc_buf = malloc(ifcfg.ifc_len);

    for(;;)
    {
        ifcfg.ifc_len = sizeof(struct ifreq) * numreqs;
        if (ioctl(fd, SIOCGIFCONF, (char *)&ifcfg) < 0)
        {
            perror("SIOCGIFCONF ");
            return;
        }
        printf("%d : %d \n", ifcfg.ifc_len, sizeof(struct ifreq));
        break;
    }

    printf("address %d\n", &ifcfg.ifc_req);
    printf("address %d\n", &ifcfg.ifc_buf);

    ifr = ifcfg.ifc_req;
    for (n = 0; n < ifcfg.ifc_len; n+= sizeof(struct ifreq))
    {
        printf("[%s]\n", ifr->ifr_name);
		if (strncmp (cmd_dev, ifr->ifr_name, strlen(cmd_dev) > strlen(ifr->ifr_name)?strlen(cmd_dev):strlen(ifr->ifr_name)) != 0)
		{
			printf ("skip\n");
			ifr++;
			continue;
		}

        ioctl(fd, SIOCGIFMTU, (char *)ifr);
        printf("MTU   %d\n", ifr->ifr_mtu);
        printf("\n");
        ifr++;
    }
}

int main (int argc, char **argv)
{
	int index = -1;
	int i;
	const char* cmd = argv[1];

	if (argc < 2 || argc > 3)
	{
		if (argc < 1)
		{
			printf ("[%s:%d] There are too few argument\n", __FILE__, __LINE__);
		}
		if (argc > 3)
		{
			printf ("[%s:%d] There are too many argument\n", __FILE__, __LINE__);
		}
		print_help ();
		return -1;
	}

	for (i = SHOW;i < COMMAND_MAX;i++)
	{
		if (strncmp (str_command[i], cmd, strlen(str_command[i])) == 0)
		{
			index = i;
			break;
		}
	}

	if (index < 0)
	{
		printf ("[%s:%d] argument is incorrect (%s)\n", __FILE__, __LINE__, cmd);
		print_help ();
		return -1;
	}

	if (index == SET)
	{
		if (argv[2] == NULL)
		{
			printf ("[%s:%d] There are too few argument\n", __FILE__, __LINE__);
			print_help ();
			return -1;
		}

		int mtu_value = atoi(argv[2]);
		if (mtu_value < 1280 || mtu_value > 1500)
		{
			printf ("[%s:%d] Value is invalid (1280 ~ 1500)\n", __FILE__, __LINE__);
			return -2;
		}
	}

	printf ("[%s:%d] value = %s\n", __FILE__, __LINE__, argv[2]);

	switch (index)
	{
		case SHOW:
		{
			show_device_status ();
			break;
		}
		case SET:
		{
			set_mtu (argv[2]);
			break;
		}
		case GET:
		{
			get_mtu ();
			break;
		}
	}
	printf ("[%s:%d] Exit program\n", __FILE__, __LINE__);

	return 0;
}
