/*
 * =====================================================================================
 *
 *       Filename:  setup_enc_dec.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 12월 17일 15시 04분 40초
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

int main(int argc, char** argv)
{
	if(argc < 3) {
		printf("[%s:%d] argument is few(%d)\n", __FILE__, __LINE__, argc);
		return -1;
	}

	//const char* filename = "DVRSETUP.DAT";
	//const char* filename_dst = "DVRSETUP_DST.DAT";
	// original file
	char* filename = argv[1];
	// cropped file
	char* filename_dst = argv[2];

	FILE *setup_fp = fopen(filename, "rb");
	FILE *setup_fp_dst = fopen(filename_dst, "wb");
	enum { BUF_SIZE = 1, HEADER_SIZE = 12, };
	char buffer[BUF_SIZE];

	if((setup_fp == NULL) || (setup_fp_dst == NULL)) {
		if(setup_fp == NULL) {
			printf("[%s:%d] Failed to open DVRSETUP.DAT\n", __FILE__, __LINE__);
		}
		if(setup_fp_dst == NULL) {
			printf("[%s:%d] Failed to open DVRSETUP_DST.DAT\n", __FILE__, __LINE__);
		}
		return -1;
	}

	fseek(setup_fp, 0, SEEK_END);
	int srcFilesize = ftell(setup_fp);
	printf("[%s:%d] srcFilesize = %d(%d)\n", __FILE__, __LINE__, srcFilesize, srcFilesize - HEADER_SIZE);
	if(srcFilesize <= 0) {
		printf("[%s:%d] Program Exit\n", __FILE__, __LINE__);
		goto close;
	}
	srcFilesize -= HEADER_SIZE;
	fseek(setup_fp, HEADER_SIZE, SEEK_SET);
	int read_sz = 0;
	int write_sz = 0;
	int total_read_sz = 0;
	int total_write_sz = 0;

	while(total_read_sz < srcFilesize) {
		memset(buffer, 0, BUF_SIZE);
		read_sz = fread(buffer, BUF_SIZE, 1, setup_fp);
		if(read_sz > 0) {
			write_sz = fwrite(buffer, BUF_SIZE, 1, setup_fp_dst);
		}
		else {
			printf("[%s:%d] nothing to read data\n", __FILE__, __LINE__);
			break;
		}
		total_read_sz += read_sz;
		total_write_sz += write_sz;
		//printf("[%s:%d] write size = %d(%d); read size = %d(%d)\n", __FILE__, __LINE__, write_sz, total_write_sz, read_sz, total_read_sz);
	}
	printf("[%s:%d] total write size = %d; total read size = %d\n", __FILE__, __LINE__, total_write_sz, total_read_sz);

close:
	fclose(setup_fp);
	fclose(setup_fp_dst);

	printf("[%s:%d] hello world!!!\n", __FILE__, __LINE__);
	return 0;
}

