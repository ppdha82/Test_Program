/*
 * =====================================================================================
 *
 *       Filename:  analysis_ai_metadata.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 11월 25일 14시 15분 35초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug_print.h"

int main(int argc, char** argv)
{
	enum { PARAM_COUNT = 2, };
	enum { STR_SIZE = 64, BUF_SIZE = 1024, CMD_SIZE = 128, };

	if(argc != PARAM_COUNT) {
		_DBG_R("Invalid argc(%d)\n", argc);
		return -1;
	}

	int i = 0;
	int readSize = 0;
	char buf[BUF_SIZE];
	char filename[STR_SIZE];
	char jpegFilename[STR_SIZE];
	char cmd[CMD_SIZE];
	int fileSize = 0;
	char* buff = NULL;
	char* bigBuffer = NULL;
	int bufSize = 0;
	char* buf1 = NULL;
	char *jsonBuf = NULL;
	int metaSize = 0;
	char *jpegBuf = NULL;
	int* pInt = NULL;
	FILE *fp = NULL;
	FILE *jpegFp = NULL;
	int writeSize = 0;

	snprintf(filename, STR_SIZE, "./%s", argv[1]);
	_DBG_G("filename = %s\n", filename);

	fp = fopen(filename, "rb");

	if(fp == NULL) {
		_ERR("fp is NULL\n");
		return -1;
	}
	// filesize
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	_DBG_R("fileSize = %d\n", fileSize);

	if(fileSize <= 0) {
		_ERR("Invalid fileSize(%d)\n", fileSize);
		return -1;
	}
	bufSize = fileSize;
	if(fileSize <= BUF_SIZE) {
		buff = buf;
	}
	else {
		bigBuffer = (char*)malloc(fileSize);
		if(bigBuffer == NULL) {
			_ERR("Failed to allocate memory for bigBuffer\n");
			fclose(fp);
			return -1;
		}
		buff = bigBuffer;
	}
	snprintf(cmd, CMD_SIZE, "ls -l %s", filename);
	system(cmd);

	readSize = fread(buff, bufSize, 1, fp);
	if(readSize <= 0) {
		_DBG_G("Invalid readSize (%d)\n", readSize);
		fclose(fp);
		return -1;
	}

	pInt = (int*)buff;
	// XEVENT_META_S: Header
	_DBG_B("version = %d\n", *pInt);
	_DBG_B("meta_count = %d\n", *(pInt + 1));
	// XEVENT_META_ITEM_S: JSON
	_DBG_B("meta_type = %d\n", *(pInt + 2));
	_DBG_B("meta_size = %d\n", *(pInt + 3));
	metaSize = *(pInt + 3);
	buf1 = (char*)(pInt + 4);
	jsonBuf = (char*)malloc(*(pInt + 3));
	if(jsonBuf == NULL) {
		_ERR("Failed to allocate memory for jsonBuf\n");
		if(bigBuffer != NULL) {
			free(bigBuffer);
			bigBuffer = NULL;
		}
		fclose(fp);
		return -1;
	}
	memcpy(jsonBuf, buf1, metaSize);
	_DBG_R("jsonBuf = %s\n", jsonBuf);

	buf1 += metaSize;
	// XEVENT_META_ITEM_S: JPEG
	pInt = (int*)buf1;
	_DBG_B("meta_type = %d\n", *(pInt));
	_DBG_B("meta_size = %d\n", *(pInt + 1));
	metaSize = *(pInt + 1);
	buf1 = (char*)(pInt + 2);

	i = 0;
	snprintf(jpegFilename, STR_SIZE, "%s_%d.jpg", filename, i);
	jpegFp = fopen(jpegFilename, "wb");
	if(jpegFp == NULL) {
		_ERR("Failed to open file(%s)\n", jpegFilename);
		if(jsonBuf != NULL) {
			free(jsonBuf);
			jsonBuf = NULL;
		}

		if(bigBuffer != NULL) {
			free(bigBuffer);
			bigBuffer = NULL;
		}
		fclose(fp);
		return -1;
	}
	jpegBuf = (char*)malloc(metaSize);
	if(jpegBuf == NULL) {
		_ERR("Failed to allocate memory for jpeg Dump\n");
		if(jsonBuf != NULL) {
			free(jsonBuf);
			jsonBuf = NULL;
		}

		if(bigBuffer != NULL) {
			free(bigBuffer);
			bigBuffer = NULL;
		}
		fclose(jpegFp);
		fclose(fp);
		return -1;
	}
	memcpy(jpegBuf, buf1, metaSize);
	writeSize = fwrite(jpegBuf, metaSize, 1, jpegFp);
	if(writeSize <= 0) {
		_ERR("Failed to write jpegBuf to jpegFp(%s)\n", jpegFilename);
	}

	fclose(fp);
	fclose(jpegFp);

	if(jpegBuf != NULL) {
		free(jpegBuf);
		jpegBuf = NULL;
	}

	if(jsonBuf != NULL) {
		free(jsonBuf);
		jsonBuf = NULL;
	}

	if(bigBuffer != NULL) {
		free(bigBuffer);
		bigBuffer = NULL;
	}

	return 0;
}