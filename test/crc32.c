/*
 * =====================================================================================
 *
 *       Filename:  crc32.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 13일 13시 30분 52초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef unsigned int __u32;
enum { K = 1024, };

unsigned int crc32 (char * buffer, int length, unsigned int oldcrc)
{
    /* indices */
    int perByte;
    int perBit;

    /* crc polynomial for Ethernet */
    const unsigned int poly = 0xedb88320;

    /* crc value - preinitialized to all 1's */
    unsigned int crc_value = (oldcrc ? oldcrc : 0xffffffff);

    for (perByte = 0; perByte < length; perByte++) {
        unsigned char c = (unsigned char)(*(buffer++));

        for (perBit = 0; perBit < 8; perBit++) {
            crc_value = (crc_value >> 1) ^ (((crc_value ^ c) & 0x01) ? poly : 0);
            c >>= 1;
        }
    }

    return  crc_value;
}


// Check CRC32 checksum of given file.
//	@fname : Full path name of image file.
//
//	return
//		32 bit CRC value.
//
//	NOTE
//		CRC is calcualted from current file pointer to the
//		end of file.
__u32 crc32_file (int fd)
{
	__u32 crc, sz;
	int res;
	char buf [4*K];

	crc = 0;
	sz  = 0;
	do {
		res = read (fd, buf, sizeof (buf));

		if (res < 0) {
			perror ("read");
			return 0;
		}

		crc  = crc32 (buf, res, crc);
		sz += res;
	} while (res > 0);

	return crc;
}

int print_help(int argc, char** argv)
{
	if(argc < 2) {
		printf("[%s:%d] too few argument\n", __FILE__, __LINE__);
	}
	else {
		printf("[%s:%d] too many argument\n", __FILE__, __LINE__);
	}
	printf("[%s:%d] %s [FILE_PATH/FILE_NAME]\n", __FILE__, __LINE__, argv[0]);
	return 0;
}

int main(int argc, char** argv)
{
	if(argc != 2) {
		return print_help(argc, argv);
	}

	int fd = -1;
	__u32 crc32 = 0;
	if ((fd = open (argv[1], O_RDONLY, 0)) < 0) {
		printf ("Can't open file -> [%s]\n", argv[1]);
		return -1;
	}

	lseek (fd, 0, SEEK_SET);
	crc32 = crc32_file(fd);
	printf("[%s:%d] crc32 = %u\n", __FILE__, __LINE__, crc32);

	return 0;
}
