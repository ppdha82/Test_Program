/*
 * =====================================================================================
 *
 *       Filename:  system.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 04월 22일 19시 49분 43초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* base_path = "/sys/class/gpio";
const char* func_path[3] = { "export", "direction", "value" };
int gpio[8] = { 59, 60, 61, 62, 40, 41, 65, 66 };

int main(int argc, char **argv)
{
    int i = 0;
	int idx = 0;
	//int retval;
    //retval = system("curl");
    //printf("Exit Status %d\n", retval);

	char cmd[128];
	for(i = 0;i < 8;i++) {
		idx = 0;
		snprintf(cmd, sizeof(cmd), "echo %d > %s/%s", gpio[i], base_path, func_path[idx]);
		printf("[%s:%d] cmd = %s\n", __FILE__, __LINE__, cmd);
		system(cmd);
		idx++;

		memset(cmd, 0, sizeof(cmd));
		snprintf(cmd, sizeof(cmd), "echo out > %s/gpio%d/%s", base_path, gpio[i], func_path[idx]);
		printf("[%s:%d] cmd = %s\n", __FILE__, __LINE__, cmd);
		system(cmd);
		idx++;

		memset(cmd, 0, sizeof(cmd));
		snprintf(cmd, sizeof(cmd), "echo 0 > %s/gpio%d/%s", base_path, gpio[i], func_path[idx]);
		printf("[%s:%d] cmd = %s\n", __FILE__, __LINE__, cmd);
		system(cmd);
		idx++;
	}
	return 0;
}

