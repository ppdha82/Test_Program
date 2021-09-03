/*
 * =====================================================================================
 *
 *       Filename:  conYuv2Rgb.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2021년 01월 19일 20시 13분 23초
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

#include "debug_print.h"

typedef unsigned char UINT8;
typedef unsigned int UINT16;

enum { SIZE = 256, };

long int tab_76309[SIZE];
long int crv_tab[SIZE];
long int cbu_tab[SIZE];
long int cgu_tab[SIZE];
long int cgv_tab[SIZE];

long int bilevel_tab_76309[SIZE];
UINT8 *clp;

void convert(UINT8 *src0, UINT8 *src1, UINT8 *src2, UINT8 *dst_ori, int width, int height, int imtype)
{
	int i;
	int j;
	int k;
	int u;
	int v;
	int u2g;
	int u2b;
	int v2g;
	int v2r;
	int y11;
	int y12;
	int y21;
	int y22;

	int width4 = width + (4 - (width % 4)) % 4;
	UINT8 *pucY0;
	UINT8 *pucY1;
	UINT8 *pucU;
	UINT8 *pucV;
	UINT8 *pucRaster0;
	UINT8 *pucRaster1;

	pucY0 = src0;
	pucY1 = src0 + width;
	pucU = src1;
	pucV = src2;
	pucRaster0 = dst_ori + width4 * (height - 1) * 3;
	pucRaster1 = pucRaster0 - width4 * 3;

	switch(imtype) {
		case 444:
			for(i = 0;i < height;i++) {
				for(j = 0;j < width;j++) {
					y11 = tab_76309[*pucY0++];
					u = *pucU++;
					v = *pucV++;

					u2g = cgu_tab[u];
					u2b = cbu_tab[u];
					v2g = cgv_tab[v];
					v2r = crv_tab[v];

					*pucRaster0++ = clp[(y11 + u2b) >> 16];
					*pucRaster0++ = clp[(y11 - u2g - v2g) >> 16];
					*pucRaster0++ = clp[(y11 + v2r) >> 16];
				}

				for(;j < width4;j++) {
					for(k = 0;k < 3;k++) {
						*pucRaster0++ = 0;
					}
				}

				pucRaster0 = pucRaster0 - 2 * width4 * 3;
			}
			break;
		case 422:
			for(i = 0;i < height;i++) {
				for(j = 0;j < width;j++) {
					y11 = tab_76309[*pucY0++];
					y12 = tab_76309[*pucY0++];
					u = *pucU++;
					v = *pucV++;

					u2g = cgu_tab[u];
					u2b = cbu_tab[u];
					v2g = cgv_tab[v];
					v2r = crv_tab[v];

					*pucRaster0++ = clp[(y11 + u2b) >> 16];
					*pucRaster0++ = clp[(y11 - u2g - v2g) >> 16];
					*pucRaster0++ = clp[(y11 + v2r) >> 16];

					*pucRaster1++ = clp[(y12 + u2b) >> 16];
					*pucRaster1++ = clp[(y12 - u2g - v2g) >> 16];
					*pucRaster1++ = clp[(y12 + v2r) >> 16];
				}

				for(;j < width4;j++) {
					for(k = 0;k < 3;k++) {
						*pucRaster0++ = 0;
					}
				}

				pucRaster0 = pucRaster0 - 2 * width4 * 3;
			}
			break;
		case 420:
			for(i = 0;i < height;i++) {
				for(j = 0;j < width;j++) {
					y11 = tab_76309[*pucY0++];
					y12 = tab_76309[*pucY0++];
					y21 = tab_76309[*pucY1++];
					y22 = tab_76309[*pucY1++];
					u = *pucU++;
					v = *pucV++;

					u2g = cgu_tab[u];
					u2b = cbu_tab[u];
					v2g = cgv_tab[v];
					v2r = crv_tab[v];

					*pucRaster0++ = clp[(y11 + u2b) >> 16];
					*pucRaster0++ = clp[(y11 - u2g - v2g) >> 16];
					*pucRaster0++ = clp[(y11 + v2r) >> 16];
					*pucRaster0++ = clp[(y12 + u2b) >> 16];
					*pucRaster0++ = clp[(y12 - u2g - v2g) >> 16];
					*pucRaster0++ = clp[(y12 + v2r) >> 16];

					*pucRaster1++ = clp[(y12 + u2b) >> 16];
					*pucRaster1++ = clp[(y12 - u2g - v2g) >> 16];
					*pucRaster1++ = clp[(y12 + v2r) >> 16];
					*pucRaster1++ = clp[(y22 + u2b) >> 16];
					*pucRaster1++ = clp[(y22 - u2g - v2g) >> 16];
					*pucRaster1++ = clp[(y22 + v2r) >> 16];
				}

				for(;j < width4;j++) {
					for(k = 0;k < 3;k++) {
						*pucRaster0++ = 0;
						*pucRaster1++ = 0;
					}
				}

				pucRaster0 = pucRaster0 - 3 * width4 * 3;
				pucRaster1 = pucRaster1 - 3 * width4 * 3;
				pucY0 += width;
				pucY1 += width;
			}
			break;
		case 24:
			for(i = 0;i < height;i++) {
				for(j = 0;j < width;j++) {
					y11 = *pucY0++;
					u = *pucU++;
					v = *pucV++;

					*pucRaster0++ = v;
					*pucRaster0++ = u;
					*pucRaster0++ = y11;
				}

				for(;j < width4;j++) {
					for(k = 0;k < 3;k++) {
						*pucRaster0++ = 0;
					}
				}

				pucRaster0 = pucRaster0 - 3 * width4 * 3;
			}
			break;
		case 256:
			for(i = 0;i < height;i++) {
				for(j = 0;j < width;j++) {
					y11 = clp[tab_76309[*pucY0++] >> 16];

					*pucRaster0++ = y11;
					*pucRaster0++ = y11;
					*pucRaster0++ = y11;
				}

				for(;j < width4;j++) {
					for(k = 0;k < 3;k++) {
						*pucRaster0++ = 0;
					}
				}

				pucRaster0 = pucRaster0 - 2 * width4 * 3;
			}
			break;
	}
}

void init_clp(void)
{
	int i;
	clp = (UINT8*)malloc(1024);
	clp += 384;

	for(i = -384;i < 640;i++) {
		clp[i] = (i < 0) ? 0:((i > 255)? 255:i);
	}
}

void init_dither_tab(void)
{
	int i;
	long int crv;
	long int cbu;
	long int cgu;
	long int cgv;

	crv = 104597;
	cbu = 132201;
	cgu = 25675;
	cgv = 53279;

	for(i = 0;i < 256;i++) {
		crv_tab[i] = (i - 128) * crv;
		cbu_tab[i] = (i - 128) * cbu;
		cgu_tab[i] = (i - 128) * cgu;
		cgv_tab[i] = (i - 128) * cgv;
		tab_76309[i] = 76309 * (i - 16);
	}

	bilevel_tab_76309[0] = tab_76309[0];
	for(i = 1;i < 256;i++) {
		bilevel_tab_76309[i] = tab_76309[255];
	}
}


int main(int argc, char** argv)
{
	if(argc < 3) {
		// print_help();
		DBG_R("argc is invalid (%d)\n", argc);
	}

	enum { WIDTH = 128, HEIGHT = 128, DEPTH = 3, };
	FILE *in;
	FILE *out;
	const char* INPUT_FILE = "nalbi_dump_1";
	const char* OUTPUT_FILE = "nalbi_dump_1.rgb";

	UINT16 pic_size = WIDTH * HEIGHT;
	UINT8 *buffer = (UINT8*)malloc(pic_size * DEPTH);
	UINT8 *y_data = (UINT8*)malloc(pic_size);
	UINT8 *u_data = (UINT8*)malloc(pic_size / 4);
	UINT8 *v_data = (UINT8*)malloc(pic_size / 4);

	in = fopen(INPUT_FILE, "rb");
	out = fopen(OUTPUT_FILE, "wb");

	fread(y_data, 1, pic_size, in);
	fread(u_data, 1, pic_size / 4, in);
	fread(v_data, 1, pic_size / 4, in);

	init_dither_tab();
	init_clp();

	convert(y_data, u_data, v_data, buffer, WIDTH, HEIGHT, 420);

	fwrite(buffer, sizeof(UINT8), WIDTH * HEIGHT * 3, out);

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


