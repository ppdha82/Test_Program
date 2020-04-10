/*
 * =====================================================================================
 *
 *       Filename:  size_check.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 03월 12일 18시 49분 13초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

typedef struct _RANGE{
	int use[6];
	int temp[8];
	int humi[8];
	int pm2p5[4];
	int pm10p0[4];
	int tvoc[4];
	int co2[4];
}RANGE;  

typedef struct _EVENT_ENV{
	// led
	int led_use;
	int moral_use;

	int led_select[6]; 	   // 1: temp, 2: humi, 3: pm 2.5, 4: pm 10.0, 5: tvoc, 6: co2
	int led_normal;        // 1: red, 2: blue, 3: green, 4: yellow, 5: pupple

	int buz_use;
	// buzzer
	int buz_select[6]; 	// 1: temp, 2: humi, 3: pm 2.5, 4: pm 10.0, 5: tvoc, 6: co2
	int buz_level; 	 	// 1:Red  2:Puple  3:Yellow  4:Green  5:Blue"

	int buz_delay;
	int buz_mode;
	int buz_off_flag;
	// osd
	int osd_on_off;

	// range
	RANGE range;

}	EVENT_ENV; //68

static size_t get_file_size (const char * file_name)
{
    struct stat sb;
    if (stat (file_name, & sb) != 0) {
        fprintf (stderr, "'stat' failed for '%s': %s.\n", file_name, strerror (errno));
		return -1;
    }
    return sb.st_size;
}

int main (int argc, char** argv)
{
	printf ("size struct RANGE = %d\n", (int)(sizeof(RANGE)/sizeof(int)));
	printf ("size struct EVENT_ENV = %d\n", (int)(sizeof(EVENT_ENV)/sizeof(int)));

    const char * file_name;
    size_t size;

    file_name = argv[1];
    size = get_file_size (file_name);
    printf ("%20s has %d bytes.\n", file_name, (int)size);

	return 0;
}
