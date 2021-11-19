/*
 * =====================================================================================
 *
 *       Filename:  test_fnctl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 07월 30일 18시 22분 59초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// 파일이 잠겨 있는지 확인해서 잠금을 얻고 
// 잠겨 있을 경우 잠금이 풀릴 때까지 
// 기다린다.  
int fd_lock(int fd)
{
    struct flock lock;

    lock.l_type = F_RDLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    return fcntl(fd, F_SETLKW, &lock);
}

// 파일 잠금을 얻은후 모든 작업이 끝났다면 
// 이 함수를 호출해서 잠금을 되돌려준다.
int fd_unlock(int fd)
{
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    return fcntl(fd, F_SETLK, &lock);
}

int main(int argc, char **argv)
{
    int fd;
    int id;
    int i;

    char *file_name = "lock.file";
	if(argc < 2) {
		perror("few parameter");
		exit(0);
	}

    id = atoi(argv[1]);
    if ((fd = open(file_name, O_RDWR)) < 0)
    {
        perror("open failure");
        exit(0);
    }
    if (fd_lock(fd) == -1)
    {
        perror("fd lock error");
        exit(0);
    }
    for (i = 0; i < 10; i++)
    {
        printf("file lock %d : %d\n", id, i);
        sleep(1);
    }
    if (fd_unlock(fd) == -1)
    {
        perror("fd unlock error");
        exit(0);
    }
    close(fd);
}


