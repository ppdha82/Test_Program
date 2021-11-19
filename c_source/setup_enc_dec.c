/*
 * =====================================================================================
 *
 *       Filename:  setup_enc_dec.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 12월 18일 08시 03분 57초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "openssl/aes.h"

#define AES_KEY_BIT 	128

#define AES_KEY_BYTE 	16
#define ENCSETSIZE(sz) ((((sz)/AES_BLOCK_SIZE)+1)*AES_BLOCK_SIZE)
//static unsigned char aes_key[AES_KEY_BYTE] = "focusipc2018!!!";
static unsigned char aes_key[AES_KEY_BYTE];

static void dump_data(char *title, char *src, char *dst, int size)
{
#if 1
	int i;
	printf("==================================================================\n");
	printf("==================================================================\n");
	printf("==================================================================\n");
	printf("%s :: ", title);
	for(i = 0; i < size; i++) {
		printf("%02x ", src[i]);
	}
	printf(" ---> ");
	for(i = 0; i < size; i++) {
		printf("%02x ", dst[i]);
	}
	printf("\n");
	printf("==================================================================\n");
	printf("==================================================================\n");
	printf("==================================================================\n");
#endif
}

static int __setup_decryption(void *src, void *dst, int size)
{
	AES_KEY key;
	unsigned char iv_aes[AES_BLOCK_SIZE] = {0, };

	memset(aes_key, 0, sizeof(aes_key));
	memset(iv_aes, 0, sizeof(iv_aes));
	//snprintf(aes_key, sizeof(aes_key), "0");
	int i;
	printf("[%s:%d]", __FILE__, __LINE__);
	for(i = 0;i < AES_KEY_BYTE;i++) {
		printf("%02x", aes_key[i]);
	}
	printf("\n");
	int ret = AES_set_decrypt_key(aes_key, AES_KEY_BIT, &key);
	printf("[%s:%d] dec key ret = %d\n", __FILE__, __LINE__, ret);
	AES_cbc_encrypt(src, dst, size, &key, iv_aes, AES_DECRYPT);
	//dump_data("dec", src, dst, 16);

	return 0;
}

static int __setup_encryption(void *src, void *dst, int size)
{
	AES_KEY key;
	unsigned char iv_aes[AES_BLOCK_SIZE];

	memset(iv_aes, 0, sizeof(iv_aes));
	memset(aes_key, 0, sizeof(aes_key));
	//snprintf(aes_key, sizeof(aes_key), "0");
	int i;
	printf("[%s:%d]", __FILE__, __LINE__);
	for(i = 0;i < AES_KEY_BYTE;i++) {
		printf("%02x", aes_key[i]);
	}
	printf("\n");
	int ret = AES_set_encrypt_key(aes_key, AES_KEY_BIT, &key);
	printf("[%s:%d] enc key ret = %d\n", __FILE__, __LINE__, ret);
	AES_cbc_encrypt(src, dst, size, &key, iv_aes, AES_ENCRYPT);
	//dump_data("enc", src, dst, 16);

	return 0;
}

int generate_file(const char* filename, void* data, int size)
{
	FILE *fp = fopen(filename, "wb");
	if(fp == NULL) {
		printf("[%s:%d] fp is NULL\n", __FILE__, __LINE__);
		return -1;
	}

	int total_write_sz = 0;
	int write_sz = 0;
	enum { BUF_SIZE = 1, };
	unsigned char buffer[BUF_SIZE];
	unsigned char* buf_data = (unsigned char*)data;
	printf("[%s:%d] size = %d\n", __FILE__, __LINE__, size);
	while(size > total_write_sz) {
		memset(buffer, 0, BUF_SIZE);
		int i;
		for(i = 0;i < BUF_SIZE;i++) {
			buffer[i] = buf_data[total_write_sz + i];
		}
		write_sz = fwrite(buffer, BUF_SIZE, 1, fp);
		if(write_sz <= 0) {
			printf("[%s:%d] write size is invalid(%d)\n", __FILE__, __LINE__, write_sz);
			break;
		}
		total_write_sz += write_sz;
		//printf("[%s:%d] write_sz = %d; total_write_sz = %d\n", __FILE__, __LINE__, write_sz, total_write_sz);
	}
	printf("[%s:%d] total_write_sz = %d\n", __FILE__, __LINE__, total_write_sz);
	fclose(fp);
	return 0;
}

int get_file_size(FILE *fp)
{
	if(fp == NULL) {
		printf("[%s:%d] fp is NULL\n", __FILE__, __LINE__);
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	int srcFilesize = ftell(fp);
	printf("[%s:%d] file size = %d\n", __FILE__, __LINE__, srcFilesize);

	return srcFilesize;
}

int load_data_from_file(FILE *fp, void* data, int size)
{
	enum { BUF_SIZE = 1, };
	unsigned char buffer[BUF_SIZE];

	if((fp == NULL) || (data == NULL) || (size <= 0)) {
		if(fp == NULL) {
			printf("[%s:%d] fp is NULL\n", __FILE__, __LINE__);
		}
		if(data == NULL) {
			printf("[%s:%d] data is NULL\n", __FILE__, __LINE__);
		}
		if(size <= 0) {
			printf("[%s:%d] size is invalid(%d)\n", __FILE__, __LINE__, size);
		}

		return -1;
	}

	int total_read_sz = 0;
	int read_sz = 0;
	unsigned char* buf_data = (unsigned char*)data;

	fseek(fp, 0, SEEK_SET);
	while(total_read_sz < size) {
		memset(buffer, 0, BUF_SIZE);
		read_sz = fread(buffer, BUF_SIZE, 1, fp);
		if(read_sz <= 0) {
			printf("[%s:%d] nothing to read data\n", __FILE__, __LINE__);
			break;
		}
		int i; 
		for(i = 0;i < BUF_SIZE;i++) {
			buf_data[total_read_sz + i] = buffer[i];
		}
		total_read_sz += read_sz;
		//printf("[%s:%d] read size = %d(/%d)\n", __FILE__, __LINE__, read_sz, total_read_sz);
	}
	printf("[%s:%d] total read size = %d\n", __FILE__, __LINE__, total_read_sz);

	fclose(fp);
	return total_read_sz;
}

int main(int argc, char** argv)
{
	if(argc < 4) {
		printf("[%s:%d] argument is few(%d)\n", __FILE__, __LINE__, argc);
		return -1;
	}

	if(strncmp(argv[1], "enc", strlen(argv[1]) > strlen("enc")?strlen(argv[1]):strlen("enc")) == 0) {
		// enc
		FILE *fp = fopen(argv[2], "rb");
		void* data;
		void* enc_data;
		if(fp == NULL) {
			printf("[%s:%d] fp is NULL\n", __FILE__, __LINE__);
			return -1;
		}

		int size = get_file_size(fp);
		if(size <= 0) {
			printf("[%s:%d] size is invalid(%d)\n", __FILE__, __LINE__, size);
			return -1;
		}
		printf("[%s:%d] file size = %d\n", __FILE__, __LINE__, size);
		data = (void*)malloc(size);

		size = load_data_from_file(fp, data, size);
		if(size <= 0) {
			printf("[%s:%d] size is invalid(%d)\n", __FILE__, __LINE__, size);
			return -1;
		}
		printf("[%s:%d] data size = %d\n", __FILE__, __LINE__, size);

		enc_data = (void*)malloc(size);
		__setup_encryption(data, enc_data, size);
		printf("[%s:%d] enc size = %d\n", __FILE__, __LINE__, size);
		int ret = generate_file(argv[3], enc_data, size);
		if(ret < 0) {
			printf("[%s:%d] Failed to write enc file\n", __FILE__, __LINE__);
		}
		else {
			printf("[%s:%d] Success to write enc file\n", __FILE__, __LINE__);
		}
	}
	else if(strncmp(argv[1], "dec", strlen(argv[1]) > strlen("dec")?strlen(argv[1]):strlen("dec")) == 0) {
		// dec
		FILE *fp = fopen(argv[2], "rb");
		void* enc_data;
		void* data;
		if(fp == NULL) {
			printf("[%s:%d] fp is NULL\n", __FILE__, __LINE__);
			return -1;
		}

		int size = get_file_size(fp);
		if(size <= 0) {
			printf("[%s:%d] size is invalid(%d)\n", __FILE__, __LINE__, size);
			return -1;
		}
		printf("[%s:%d] file size = %d\n", __FILE__, __LINE__, size);
		enc_data = (void*)malloc(size);

		size = load_data_from_file(fp, enc_data, size);
		if(size <= 0) {
			printf("[%s:%d] size is invalid(%d)\n", __FILE__, __LINE__, size);
			return -1;
		}
		printf("[%s:%d] enc data size = %d\n", __FILE__, __LINE__, size);

		data = (void*)malloc(size);
		__setup_decryption(enc_data, data, size);
		int ret = generate_file(argv[3], data, size);
		if(ret < 0) {
			printf("[%s:%d] Failed to write dec file\n", __FILE__, __LINE__);
		}
		else {
			printf("[%s:%d] Success to write dec file\n", __FILE__, __LINE__);
		}
	}
	else if(strncmp(argv[1], "enc_dec", strlen(argv[1]) > strlen("enc_dec")?strlen(argv[1]):strlen("enc_dec")) == 0) {
		// dec after enc
	}
	else if(strncmp(argv[1], "test", strlen(argv[1]) > strlen("test")?strlen(argv[1]):strlen("test")) == 0) {
		enum { DATA_SIZE = 128, };

		char srcData[DATA_SIZE];
		char dstData[DATA_SIZE];
		char decData[DATA_SIZE];

		const char* encFilename = "SETUP_ENC.DAT";
		const char* origFilename = "SETUP.DAT";
		const char* decFilename = "SETUP_DEC.DAT";

		int i;
		for(i = 0;i < DATA_SIZE;i++) {
			srcData[i] = (i * 3) % 128;
		}
		int ret = generate_file(origFilename, srcData, DATA_SIZE);
		if(ret < 0) {
			printf("[%s:%d] Failed to write original file\n", __FILE__, __LINE__);
		}
		else {
			printf("[%s:%d] Success to write original file\n", __FILE__, __LINE__);
		}

		int enc_size = __setup_encryption((void*)srcData, (void*)dstData, DATA_SIZE);
		ret = generate_file(encFilename, dstData, enc_size);
		if(ret < 0) {
			printf("[%s:%d] Failed to write enc file\n", __FILE__, __LINE__);
		}
		else {
			printf("[%s:%d] Success to write enc file\n", __FILE__, __LINE__);
		}

		__setup_decryption((void*)dstData, (void*)decData, DATA_SIZE);
		ret = generate_file(decFilename, decData, DATA_SIZE);
		if(ret < 0) {
			printf("[%s:%d] Failed to write dec file\n", __FILE__, __LINE__);
		}
		else {
			printf("[%s:%d] Success to write dec file\n", __FILE__, __LINE__);
		}
	}

	return 0;
}
