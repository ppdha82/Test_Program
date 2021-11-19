/*
 * =====================================================================================
 *
 *       Filename:  base64_ver1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018년 10월 10일 15시 33분 25초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include "encode.h"
#include <stdio.h>

int main()
{
   unsigned char *str, *dst;
   char *source = "hello world";
   //char *source = "aGVsbG8gd29ybGQ=";
   //char *source = "jIKA/d48O5/tTg/kLaMeMNSW0vM=";
   //char *source = "UVn1BE4cr4R0UEJFkKlzlA==";
   //char *source = "923A683CC68663DD7DD234B24A38D574193BA310";
   //char *source = "8F205074B88F7CD785A1CD996CF5F62ED0867AE1";
   //char *source = "tuOSpGlFlIXsozq4HFNeeGeFLEI=";
   //char *source = "LKqI6G/AikKCQrN0zqZFlg==";
   int  size;

   str = __base64_encode((unsigned char *)source, strlen(source), &size);
   printf("[enc] %s : %d\n", str, size);
   dst = __base64_decode(str, strlen(str), &size);
   printf("[dec] %s : %d\n", dst, size);

   str = __base64_decode(dst, strlen(dst), &size);
   printf("[dec] %s : %d\n", str, size);

   free(str);
   free(dst);

}
