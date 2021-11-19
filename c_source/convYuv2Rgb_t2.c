/*
 * =====================================================================================
 *
 *       Filename:  convYuv2Rgb_t2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 01월 19일 21시 08분 07초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __DEBUG_ON__
#include "debug_print.h"

typedef unsigned char UINT8;
typedef unsigned char BYTE;
typedef unsigned int UINT16;

enum { SIZE = 256, };

int clip(int seed)
{
	if(seed < 0){
		seed = 0;
	}
	else if(seed > 255) {
		seed = 255;
	}

	return seed;
}

void YUV4202RGB(UINT8 *src0, UINT8 *src1, UINT8 *src2, UINT8 *rgbframe, int width, int height)
{
	const int RGBBufferSize = 3 * height * width;
	const int YBufferSize = height * width;
	const int UVBufferSize = height * width / 4;
	UINT8 *RGBBuffer = (UINT8*)malloc(RGBBufferSize);
	BYTE *YBuffer = src0;
	BYTE *UBuffer = src1;
	BYTE *VBuffer = src2;

	DBG_R("Alive Check\n");
	const int UVHeight = height + 2;
	const int UVWidth = width + 2;
	const int UVImageSize = UVHeight * UVWidth;
	// int *UImage = (new int[UVImageSize])+UVWidth+1;
	// int *VImage = (new int[UVImageSize])+UVWidth+1;
	int *UImage = (int*)malloc(UVImageSize + UVWidth + 1);
	int *VImage = (int*)malloc(UVImageSize + UVWidth + 1);
	int R, G, B;
	int Y, U, V;

	// fill_n(&UImage[-(UVWidth + 1)], UVImageSize, 0);
	// fill_n(&VImage[-(UVWidth + 1)], UVImageSize, 0);
	memset(UImage, 0, UVImageSize + UVWidth + 1);
	memset(VImage, 0, UVImageSize + UVWidth + 1);

	DBG_R("Alive Check\n");
	int line;
	//Copy (sub-sampled) UV components to image buffer.
	for (line = 0;line < height; line += 2) {
		int UVIndex = width * line / 4;
		int pixel;
		for (pixel = 0;pixel < width;pixel += 2) {
#if 0
			UImage[line * UVWidth + pixel] = UBuffer[UVIndex] - 128;
			VImage[line * UVWidth + pixel] = VBuffer[UVIndex++] - 128;
#endif
		}
	}
	DBG_R("Alive Check\n");
	//Vertically interpolate the UV samples
	for (line = 1;line < height;line += 2) {
		int pixel;
		for (pixel = 0;pixel < width;pixel += 2) {
			UImage[line * UVWidth + pixel] = ((UImage[(line - 1) * UVWidth + pixel] + 2 * UImage[line * UVWidth + pixel] + UImage[(line + 1) * UVWidth + pixel] + 1) >> 1);
			VImage[line * UVWidth + pixel] = ((VImage[(line - 1) * UVWidth + pixel] + 2 * VImage[line * UVWidth + pixel] + VImage[(line + 1) * UVWidth + pixel] + 1) >> 1);
		}
	}
	DBG_R("Alive Check\n");

	for (line = 0;line < height;++line) {
		int YIndex = width*line;
		int RGBIndex = 3 * width * line;
		int pixel;
		for (pixel = 0;pixel < width;++pixel) {
			//Copy Y value and  filter UV values.
			Y = YBuffer[YIndex++] - 16;
			U = (UImage[line * UVWidth + pixel - 1] + 2 * UImage[line * UVWidth + pixel] + UImage[line * UVWidth + pixel + 1] + 1) >> 1;
			V = (VImage[line * UVWidth + pixel - 1] + 2 * VImage[line * UVWidth + pixel] + VImage[line * UVWidth + pixel + 1] + 1) >> 1;

			//Matrix YUV to RGB
			R = ((298 * Y           + 409 * V + 128) >> 8);
			G = ((298 * Y - 100 * U - 208 * V + 128) >> 8);
			B = ((298 * Y + 516 * U           + 128) >> 8);

			//Clip RGB Values
			RGBBuffer[RGBIndex++] = (UINT8)clip(R);	//static_cast<unsigned char>( (R<0) ? 0 : ((R>255) ? 255 : R) )
			RGBBuffer[RGBIndex++] = (UINT8)clip(G);	//static_cast<unsigned char>( (G<0) ? 0 : ((G>255) ? 255 : G) );
			RGBBuffer[RGBIndex++] = (UINT8)clip(B);  //static_cast<unsigned char>( (B<0) ? 0 : ((B>255) ? 255 : B) );
		}
	}

	DBG_R("Alive Check\n");
	// memcpy(rgbframe, RGBBuffer, RGBBufferSize);

	DBG_R("Alive Check\n");
	if(VImage != NULL) {
		// free(VImage);
		VImage = NULL;
	}

	DBG_R("Alive Check\n");
	if(UImage != NULL) {
		// free(UImage);
		UImage = NULL;
	}

	DBG_R("Alive Check\n");
	if(RGBBuffer != NULL) {
		// free(RGBBuffer);
		RGBBuffer = NULL;
	}

	DBG_R("Alive Check\n");
	if(VBuffer != NULL) {
		// free(VBuffer);
		VBuffer = NULL;
	}

	DBG_R("Alive Check\n");
	if(UBuffer != NULL) {
		// free(UBuffer);
		UBuffer = NULL;
	}

	DBG_R("Alive Check\n");
	if(YBuffer != NULL) {
		// free(YBuffer);
		YBuffer = NULL;
	}
	DBG_R("Alive Check\n");
}

int main(int argc, char** argv)
{
	if(argc < 3) {
		// print_help();
		DBG_R("argc is invalid (%d)\n", argc);
	}

	enum { WIDTH = 128, HEIGHT = 128, DEPTH = 3, };
	FILE *in = NULL;
	FILE *out = NULL;
	const char* INPUT_FILE = "nalbi_dump_1";
	const char* OUTPUT_FILE = "nalbi_dump_1_t2.rgb";

	UINT16 pic_size = WIDTH * HEIGHT;
	UINT8 *buffer = (UINT8*)malloc(pic_size * DEPTH);
	UINT8 *y_data = (UINT8*)malloc(pic_size);
	UINT8 *u_data = (UINT8*)malloc(pic_size / 4);
	UINT8 *v_data = (UINT8*)malloc(pic_size / 4);

	in = fopen(INPUT_FILE, "rb");
	if(in == NULL) {
		DBG_C("Alive Check\n");
		return -1;
	}

	out = fopen(OUTPUT_FILE, "wb");
	if(out == NULL) {
		DBG_C("Alive Check\n");
		return -1;
	}

	fread(y_data, 1, pic_size, in);
	fread(u_data, 1, pic_size / 4, in);
	fread(v_data, 1, pic_size / 4, in);

	YUV4202RGB(y_data, u_data, v_data, buffer, WIDTH, HEIGHT);

	DBG_R("Alive Check\n");
	fwrite(buffer, 1, WIDTH * HEIGHT * DEPTH, out);
	// fwrite(data, 1, strlen(data), out);
	DBG_R("Alive Check\n");

	fclose(in);
	fclose(out);

	if(buffer != NULL) {
		free(buffer);
		buffer = NULL;
	}

	if(y_data != NULL) {
		free(y_data);
		y_data = NULL;
	}

	if(u_data != NULL) {
		free(u_data);
		u_data = NULL;
	}

	if(v_data != NULL) {
		free(v_data);
		v_data = NULL;
	}

	return 0;
}


