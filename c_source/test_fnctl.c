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

#include <pthread.h>

#include "debug_print.h"

typedef struct _FILE_INFO {
    int fd;
} FILE_INFO;

enum {
    FILE_LOCK_TIMEOUT = 10,
    FILE_LOCK_TEST = 15,
};

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

void* openfile(void *arg)
{
    FILE_INFO* pFInfo = (FILE_INFO*)arg;
    int ret = 0;
    int count = FILE_LOCK_TEST;

    _DBG_R("pFInfo->fd = %d\n", pFInfo->fd);
    while(count > 0) {
        ret = fd_lock(pFInfo->fd);
        if(ret < 0) {
            _DBG_R("Failed to lock fd(%d) count:%d\n", pFInfo->fd, count);
        }
        else {
            _DBG_R("Success to lock fd(%d) count:%d\n", pFInfo->fd, count);
        }
        count--;
        sleep(1);
    }

    return (void *)&pFInfo->fd;
}

int main(int argc, char **argv)
{
    /* pthread */
   	pthread_t t1;
	int n = 10;
	int *ret;

    /* file lock */
    int fd;
    int id;
    int i;
    FILE_INFO fInfo;

    const char *file_name = "./lock.file";
	if(argc < 2) {
		perror("few parameter");
		exit(0);
	}

    id = atoi(argv[1]);
    fd = open(file_name, O_RDWR | O_CREAT, 0644);
    if(fd < 0) {
        perror("open failure");
        exit(0);
    }

    fInfo.fd = fd;
    _DBG_G("fd = %d(%d)\n", fd, fInfo.fd);

    if (fd_lock(fd) == -1) {
        perror("fd lock error");
        exit(0);
    }

	pthread_create(&t1, NULL, openfile, &fInfo);
	pthread_detach(t1);
    for (i = 0; i < FILE_LOCK_TIMEOUT; i++) {
        lseek(fd, 0, SEEK_SET);
        read(fd, )
        printf("file lock %d : %d\n", id, i);
        sleep(1);
    }
	pthread_join(t1, (void**)&ret);
    _DBG_R("*ret = %d\n", *ret);

    if (fd_unlock(fd) == -1) {
        perror("fd unlock error");
        exit(0);
    }
    close(fd);
}


