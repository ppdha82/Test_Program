/*
 * =====================================================================================
 *
 *       Filename:  mfz_pos_test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 21일 10시 24분 35초
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

typedef enum {
	STOP = 0,
	RUN,
} MOTOR_STATUS;

typedef struct {
	int pos_current;
	int pos_min;
	int pos_max;
	int speed;
	MOTOR_STATUS status; // 0: stop, 1: run
	int target_pos;
}st_pos;

typedef struct {
	int fval;
}st_iris;

const char* SAVE_FILE = "/mnt/ipm/mfz_pos";

/**
 *	@brief		read last position of motor from saved file
 *	@param		void
 *	@return		0 (always)
 */
int _read_position_to(st_pos* p_zoom, st_pos* p_focus, st_iris* p_iris)
{
	char buf[256], tmp[0xff];
	FILE* fp = fopen(SAVE_FILE, "r");

	if (p_zoom == NULL || p_focus == NULL || p_iris == NULL) {
		printf("[%s:%d]Error : invalid parameters \n", __FILE__, __LINE__);
		return -1;
	}

	if (fp == NULL) {
		printf("[%s:%d]Error : save position \n", __FILE__, __LINE__);
		return -1;
	}
	else {
		fgets(buf, 255, fp);
		fclose(fp);

		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, buf, 4);
		p_zoom->pos_current = atoi(tmp);

		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, &buf[5], 4);
		p_focus->pos_current = atoi(tmp);

		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, &buf[10], 4);
		p_zoom->speed = atoi(tmp);

		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, &buf[15], 4);
		p_focus->speed = atoi(tmp);

		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, &buf[20], 4);
		p_iris->fval = atoi(tmp);
	}

	return 0;
}

/**
 *	@brief		read last position of motor from saved file
 *	@param		void
 *	@return		0 (always)
 */
int read_position(st_pos* zoom, st_pos* focus)
{
	st_iris iris;

	if (0 != _read_position_to(zoom, focus, &iris))
	{
		printf("[%s:%d]Failed to read file\n", __FILE__, __LINE__);
		return -1;
	}

	printf("[%s:%d][0:restore pos : zoom pos %d, speed %d | focus pos %d, speed %d | iris %d]\n", __FILE__, __LINE__,
			zoom->pos_current, zoom->speed, focus->pos_current, focus->speed, iris.fval);

	return 0;
}

int main(int argc, char** argv)
{
	char buf[128];
	char cmd[1024];
	char inputLine[10240];
	st_pos zoom;
	st_pos focus;
	static int zoom_pos = 0;
	static int focus_pos = 0;
	FILE* fp = NULL;

	while(1) {
		read_position(&zoom, &focus);
		if(zoom_pos != zoom.pos_current || focus_pos != focus.pos_current) {
			snprintf(buf, sizeof(buf), "zoom.pos = %d; focus.pos = %d", zoom.pos_current, focus.pos_current);
			printf(buf);
			printf("zoom_pos = %d; focus_pos = %d\n", zoom_pos, focus_pos);
			zoom_pos = zoom.pos_current;
			focus_pos = focus.pos_current;
			snprintf(cmd, sizeof(cmd), "date;echo \"%s\" >> /mnt/ipm/mfz_pos_hist;", buf);
			fp = popen(cmd, "r");
			while(fgets(inputLine, 10240, fp) != NULL) {
				printf("inputLine = \n%s\n", inputLine);
			}
			pclose(fp);
		}
		sleep(2);
	}

	return 0;
}
