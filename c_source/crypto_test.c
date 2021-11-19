/*
 * =====================================================================================
 *
 *       Filename:  crypto_test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 08월 21일 11시 09분 38초
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
#include <openssl/aes.h>

  
 static const unsigned char key32[32]=
{0x12,0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,
0x34,0x56,0x78,0x9a,0xbc,0xde,0xf0,0x12,
0x56,0x78,0x9a,0xbc,0xde,0xf0,0x12,0x34,
0x78,0x9a,0xbc,0xde,0xf0,0x12,0x34,0x56};

#define BLOCK_SIZE 16
#define FREAD_COUNT 4096
#define KEY_BIT 256
#define IV_SIZE 16
#define RW_SIZE 1
#define SUCC 0
#define FAIL -1

AES_KEY aes_ks3;
unsigned char iv[IV_SIZE];

int fs_encrypt_aes(char *in_file,char *out_file)
{
    int i=0;
    int len=0;
    int padding_len=0;
    char buf[FREAD_COUNT+BLOCK_SIZE];

    FILE *fp=fopen(in_file,"rb");
    if( fp == NULL ){
        fprintf(stderr,"[ERROR] %d can not fopen('%s')\n",__LINE__,in_file);
        return FAIL;
    }

    FILE *wfp=fopen(out_file,"wb");
    if( wfp == NULL ){
        fprintf(stderr,"[ERROR] %d can not fopen('%s')\n",__LINE__,out_file);
        return FAIL;
    }

    memset(iv,0,sizeof(iv)); // init iv
    AES_set_encrypt_key(key32 ,KEY_BIT ,&aes_ks3);
    while( len = fread( buf ,RW_SIZE ,FREAD_COUNT, fp) ){
        if( FREAD_COUNT != len ){
            break;
        }

        AES_cbc_encrypt(buf ,buf ,len ,&aes_ks3 ,iv ,AES_ENCRYPT);
        fwrite(buf ,RW_SIZE ,len ,wfp);
    }


    // padding  : pkcs5? pkcs7?? http://wiki.dgoon.net/doku.php?id=ssl:pkcs_5
    padding_len=BLOCK_SIZE - len % BLOCK_SIZE;
    printf("enc padding len:%d\n",padding_len);
    memset(buf+len, padding_len, padding_len);
/**
    for(i=len; i < len+padding_len ;i++){
        buf[i]=padding_len;
    }
**/
    AES_cbc_encrypt(buf ,buf ,len+padding_len ,&aes_ks3, iv,AES_ENCRYPT);
    fwrite(buf ,RW_SIZE ,len+padding_len ,wfp);

    fclose(wfp);
    fclose(fp);

    return SUCC;
}

int fs_decrypt_aes(char *in_file,char *out_file)
{
    char buf[FREAD_COUNT+BLOCK_SIZE];
    int len=0;
    int total_size=0;
    int save_len=0;
    int w_len=0;

    FILE *fp=fopen(in_file,"rb");
    if( fp == NULL ){
        fprintf(stderr,"[ERROR] %d can not fopen('%s')\n",__LINE__,in_file);
        return FAIL;
    }

    FILE *wfp=fopen(out_file,"wb");
    if( wfp == NULL ){
        fprintf(stderr,"[ERROR] %d can not fopen('%s')\n",__LINE__,out_file);
        return FAIL;
    }

    memset(iv,0,sizeof(iv)); // the same iv
    AES_set_decrypt_key(key32 ,KEY_BIT ,&aes_ks3);

    fseek(fp ,0 ,SEEK_END);
    total_size=ftell(fp);
    fseek(fp ,0 ,SEEK_SET);
    printf("total_size %d\n",total_size);

    while( len = fread( buf ,RW_SIZE ,FREAD_COUNT ,fp) ){
        if( FREAD_COUNT == 0 ){
            break;
        }
        save_len+=len;
        w_len=len;

        AES_cbc_encrypt(buf ,buf ,len ,&aes_ks3 ,iv ,AES_DECRYPT);
        if( save_len == total_size ){ // check last block
            w_len=len - buf[len-1];
            printf("dec padding size %d\n" ,buf[len-1]);
        }

        fwrite(buf ,RW_SIZE ,w_len ,wfp);
    }

    fclose(wfp);
    fclose(fp);

    return SUCC;
}
//copyleft @http://suite.tistory.com fs
int main(int argc, char *args[])
{
    if(argc != 2 ){
        printf("[Usage] %s fs_src_file\n",args[0]);
        return FAIL;
    }


    if(fs_encrypt_aes(args[1],"fs_in.file") == SUCC){
        fs_decrypt_aes("fs_in.file","fs_out.file");
        printf("result:[fs_out.file]\n");
    }

    return 0;
}


