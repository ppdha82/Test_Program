/*
 * =====================================================================================
 *
 *       Filename:  fread.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018년 10월 12일 15시 44분 29초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */




/* fread example: read an entire file */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;
	
	printf("[%s:%d] file name = %s\n", __FILE__, __LINE__, argv[1]);
	//pFile = fopen ( "myfile.bin" , "rb" );
	pFile = fopen ( argv[1] , "rb" );
	if (pFile==NULL) {fputs ("File error\n",stderr); exit (1);}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc (sizeof(char)*lSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	// copy the file into the buffer:
	result = fread (buffer,1,lSize,pFile);
	if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	/* the whole file is now loaded in the memory buffer. */

	// terminate
	fclose (pFile);
	free (buffer);
	return 0;
}
