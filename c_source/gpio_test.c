/*
 * =====================================================================================
 *
 *       Filename:  gpio_test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018년 10월 04일 21시 58분 53초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define	MOTORDRV_IOC_MAGIC	'x'
#define	MOTORDRV_IOC_GPIO_TEST		_IOW(MOTORDRV_IOC_MAGIC, 20, int)

int main(void)
{
	int fd = open("/dev/motordrv", O_RDWR);
	int test = 0;

	if (fd < 0)
	{
		mknod("/dev/motordrv", S_IFCHR|0666, ((243<<8)|(0&0xff)));
		fd = open("/dev/motordrv", O_RDWR);
		if (fd < 0)
		{
			printf("open failed\n");
			return 0;
		}
	}

	ioctl(fd, MOTORDRV_IOC_GPIO_TEST, &test);
	close(fd);
	return 0;
}
