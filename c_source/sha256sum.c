/*
 * =====================================================================================
 *
 *       Filename:  sha256sum.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020년 08월 14일 10시 46분 07초
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Deuk Hyun Park (ppdha82), ppdha82@focushns.com
 *        Company:  Focus H&S
 *
 * =====================================================================================
 */

#include "openssl/opensslconf.h"
#include "openssl/crypto.h"
#include "openssl/blowfish.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/objects.h"
#include "openssl/aes.h"

#include <string.h>
#include <stdio.h>

typedef struct tag_t_cm_sha256_ctx
{
	unsigned int	total[2];
	unsigned int	state[8];
	unsigned char	buffer[64];
} t_cm_sha256_ctx, *pt_cm_sha256_ctx;

#define	FN_GET_UINT32(n,b,i) \
{ \
	(n) = ( (unsigned int) (b)[(i) ] << 24 ) \
	| ( (unsigned int) (b)[(i) + 1] << 16 ) \
	| ( (unsigned int) (b)[(i) + 2] << 8 ) \
	| ( (unsigned int) (b)[(i) + 3] ); \
}

#define FN_PUT_UINT32(n,b,i) \
{ \
	(b)[(i) ] = (unsigned char) ( (n) >> 24 ); \
	(b)[(i) + 1] = (unsigned char) ( (n) >> 16 ); \
	(b)[(i) + 2] = (unsigned char) ( (n) >> 8 ); \
	(b)[(i) + 3] = (unsigned char) ( (n) ); \
}


void cm_sha256_starts(pt_cm_sha256_ctx ctx)
{
	ctx->total[0] = 0;
	ctx->total[1] = 0;
 
	ctx->state[0] = 0x6A09E667;
	ctx->state[1] = 0xBB67AE85;
	ctx->state[2] = 0x3C6EF372;
	ctx->state[3] = 0xA54FF53A;
	ctx->state[4] = 0x510E527F;
	ctx->state[5] = 0x9B05688C;
	ctx->state[6] = 0x1F83D9AB;
	ctx->state[7] = 0x5BE0CD19;
}

extern void cm_sha256_process(pt_cm_sha256_ctx ctx, const unsigned char data[64]);
void cm_sha256_process(pt_cm_sha256_ctx ctx, const unsigned char data[64])
{
	unsigned int temp1, temp2, W[64];
	unsigned int _A, _B, _C, _D, _E, _F, _G, _H;

	FN_GET_UINT32( W[0], data, 0 );
	FN_GET_UINT32( W[1], data, 4 );
	FN_GET_UINT32( W[2], data, 8 );
	FN_GET_UINT32( W[3], data, 12 );
	FN_GET_UINT32( W[4], data, 16 );
	FN_GET_UINT32( W[5], data, 20 );
	FN_GET_UINT32( W[6], data, 24 );
	FN_GET_UINT32( W[7], data, 28 );
	FN_GET_UINT32( W[8], data, 32 );
	FN_GET_UINT32( W[9], data, 36 );
	FN_GET_UINT32( W[10], data, 40 );
	FN_GET_UINT32( W[11], data, 44 );
	FN_GET_UINT32( W[12], data, 48 );
	FN_GET_UINT32( W[13], data, 52 );
	FN_GET_UINT32( W[14], data, 56 );
	FN_GET_UINT32( W[15], data, 60 );

#define SHR(x,n) ((x & 0xFFFFFFFF) >> n)
#define ROTR(x,n) (SHR(x,n) | (x << (32 - n)))

#define S0(x) (ROTR(x, 7) ^ ROTR(x,18) ^ SHR(x, 3))
#define S1(x) (ROTR(x,17) ^ ROTR(x,19) ^ SHR(x,10))

#define S2(x) (ROTR(x, 2) ^ ROTR(x,13) ^ ROTR(x,22))
#define S3(x) (ROTR(x, 6) ^ ROTR(x,11) ^ ROTR(x,25))

#define F0(x,y,z) ((x & y) | (z & (x | y)))
#define F1(x,y,z) (z ^ (x & (y ^ z)))

#define R(t) \
	( \
	W[t] = S1(W[t - 2]) + W[t - 7] + \
	S0(W[t - 15]) + W[t - 16] \
	)

#define P(a,b,c,d,e,f,g,h,x,K) \
	{ \
	temp1 = h + S3(e) + F1(e,f,g) + K + x; \
	temp2 = S2(a) + F0(a,b,c); \
	d += temp1; h = temp1 + temp2; \
	}

	_A = ctx->state[0];
	_B = ctx->state[1];
	_C = ctx->state[2];
	_D = ctx->state[3];
	_E = ctx->state[4];
	_F = ctx->state[5];
	_G = ctx->state[6];
	_H = ctx->state[7];

	P( _A, _B, _C, _D, _E, _F, _G, _H, W[ 0], 0x428A2F98 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, W[ 1], 0x71374491 );
	P( _G, _H, _A, _B, _C, _D, _E, _F, W[ 2], 0xB5C0FBCF );
	P( _F, _G, _H, _A, _B, _C, _D, _E, W[ 3], 0xE9B5DBA5 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, W[ 4], 0x3956C25B );
	P( _D, _E, _F, _G, _H, _A, _B, _C, W[ 5], 0x59F111F1 );
	P( _C, _D, _E, _F, _G, _H, _A, _B, W[ 6], 0x923F82A4 );
	P( _B, _C, _D, _E, _F, _G, _H, _A, W[ 7], 0xAB1C5ED5 );
	P( _A, _B, _C, _D, _E, _F, _G, _H, W[ 8], 0xD807AA98 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, W[ 9], 0x12835B01 );
	P( _G, _H, _A, _B, _C, _D, _E, _F, W[10], 0x243185BE );
	P( _F, _G, _H, _A, _B, _C, _D, _E, W[11], 0x550C7DC3 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, W[12], 0x72BE5D74 );
	P( _D, _E, _F, _G, _H, _A, _B, _C, W[13], 0x80DEB1FE );
	P( _C, _D, _E, _F, _G, _H, _A, _B, W[14], 0x9BDC06A7 );
	P( _B, _C, _D, _E, _F, _G, _H, _A, W[15], 0xC19BF174 );
	P( _A, _B, _C, _D, _E, _F, _G, _H, R(16), 0xE49B69C1 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, R(17), 0xEFBE4786 );
	P( _G, _H, _A, _B, _C, _D, _E, _F, R(18), 0x0FC19DC6 );
	P( _F, _G, _H, _A, _B, _C, _D, _E, R(19), 0x240CA1CC );
	P( _E, _F, _G, _H, _A, _B, _C, _D, R(20), 0x2DE92C6F );
	P( _D, _E, _F, _G, _H, _A, _B, _C, R(21), 0x4A7484AA );
	P( _C, _D, _E, _F, _G, _H, _A, _B, R(22), 0x5CB0A9DC );
	P( _B, _C, _D, _E, _F, _G, _H, _A, R(23), 0x76F988DA );
	P( _A, _B, _C, _D, _E, _F, _G, _H, R(24), 0x983E5152 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, R(25), 0xA831C66D );
	P( _G, _H, _A, _B, _C, _D, _E, _F, R(26), 0xB00327C8 );
	P( _F, _G, _H, _A, _B, _C, _D, _E, R(27), 0xBF597FC7 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, R(28), 0xC6E00BF3 );
	P( _D, _E, _F, _G, _H, _A, _B, _C, R(29), 0xD5A79147 );
	P( _C, _D, _E, _F, _G, _H, _A, _B, R(30), 0x06CA6351 );
	P( _B, _C, _D, _E, _F, _G, _H, _A, R(31), 0x14292967 );
	P( _A, _B, _C, _D, _E, _F, _G, _H, R(32), 0x27B70A85 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, R(33), 0x2E1B2138 );
	P( _G, _H, _A, _B, _C, _D, _E, _F, R(34), 0x4D2C6DFC );
	P( _F, _G, _H, _A, _B, _C, _D, _E, R(35), 0x53380D13 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, R(36), 0x650A7354 );
	P( _D, _E, _F, _G, _H, _A, _B, _C, R(37), 0x766A0ABB );
	P( _C, _D, _E, _F, _G, _H, _A, _B, R(38), 0x81C2C92E );
	P( _B, _C, _D, _E, _F, _G, _H, _A, R(39), 0x92722C85 );
	P( _A, _B, _C, _D, _E, _F, _G, _H, R(40), 0xA2BFE8A1 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, R(41), 0xA81A664B );
	P( _G, _H, _A, _B, _C, _D, _E, _F, R(42), 0xC24B8B70 );
	P( _F, _G, _H, _A, _B, _C, _D, _E, R(43), 0xC76C51A3 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, R(44), 0xD192E819 );
	P( _D, _E, _F, _G, _H, _A, _B, _C, R(45), 0xD6990624 );
	P( _C, _D, _E, _F, _G, _H, _A, _B, R(46), 0xF40E3585 );
	P( _B, _C, _D, _E, _F, _G, _H, _A, R(47), 0x106AA070 );
	P( _A, _B, _C, _D, _E, _F, _G, _H, R(48), 0x19A4C116 );
	P( _H, _A, _B, _C, _D, _E, _F, _G, R(49), 0x1E376C08 );
	P( _G, _H, _A, _B, _C, _D, _E, _F, R(50), 0x2748774C );
	P( _F, _G, _H, _A, _B, _C, _D, _E, R(51), 0x34B0BCB5 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, R(52), 0x391C0CB3 );
	P( _D, _E, _F, _G, _H, _A, _B, _C, R(53), 0x4ED8AA4A );
	P( _C, _D, _E, _F, _G, _H, _A, _B, R(54), 0x5B9CCA4F );
	P( _B, _C, _D, _E, _F, _G, _H, _A, R(55), 0x682E6FF3 );
	P( _A, _B, _C, _D, _E, _F, _G, _H, R(56), 0x748F82EE );
	P( _H, _A, _B, _C, _D, _E, _F, _G, R(57), 0x78A5636F );
	P( _G, _H, _A, _B, _C, _D, _E, _F, R(58), 0x84C87814 );
	P( _F, _G, _H, _A, _B, _C, _D, _E, R(59), 0x8CC70208 );
	P( _E, _F, _G, _H, _A, _B, _C, _D, R(60), 0x90BEFFFA );
	P( _D, _E, _F, _G, _H, _A, _B, _C, R(61), 0xA4506CEB );
	P( _C, _D, _E, _F, _G, _H, _A, _B, R(62), 0xBEF9A3F7 );
	P( _B, _C, _D, _E, _F, _G, _H, _A, R(63), 0xC67178F2 );

	ctx->state[0] += _A;
	ctx->state[1] += _B;
	ctx->state[2] += _C;
	ctx->state[3] += _D;
	ctx->state[4] += _E;
	ctx->state[5] += _F;
	ctx->state[6] += _G;
	ctx->state[7] += _H;
}


void cm_sha256_update(pt_cm_sha256_ctx ctx, const unsigned char *input, unsigned int length)
{
	unsigned int left, fill;

	if (!length) 
		return;

	left = ctx->total[0] & 0x3F; // 현재까지 컨텍스트에 남아 있는 잔여 데이터
	fill = 64 - left; // 잔여 데이터에 더하여, 채워야 할 데이터 양.

	ctx->total[0] += length; // 전체 양에 새로운 길이를 더하고, 
	ctx->total[0] &= 0xFFFFFFFF;

	// 오버플로우(데이터양 오버) total[1]의 값을 1 증가한다.
	if (ctx->total[0] < length) ctx->total[1]++;

	// 기존 잔여 데이터가 존재하고, 새로운 데이터의 길이가 채워야 할 데이터보다 많은 경우...
	if (left && length >= fill) 
	{
		// 새로운 데이터를 부족한 데이터양 만큼 기존 데이터의 뒤에 채운다.
		memcpy((void *) (ctx->buffer + left), (const void *) input, fill);

		cm_sha256_process(ctx, ctx->buffer);

		length -= fill; // 입력데이터의 길이는 줄이고
		input += fill; // 입력데이터의 포인터는 뒤로 이동한다.
		left = 0; // 
	}

	// 잔여 데이터가 64바이트 이상일 경우, 처리하고 크기와 포인터를 이동한다.
	while (length >= 64)
	{
		cm_sha256_process(ctx, input);
		length -= 64;
		input += 64;
	}

	// 잔여데이터가 있는 경우, 기존 데이터의 뒤에 붙인다.
	if (length)
	{
		memcpy((void *) (ctx->buffer + left), (const void *) input, length );
	}
}

static unsigned char vs_cm_sha256_padding[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


void cm_sha256_finish(pt_cm_sha256_ctx ctx, unsigned char digest[32])
{
	unsigned int last, padn;
	unsigned int high, low;
	unsigned char msglen[8];

	high = (ctx->total[0] >> 29) | (ctx->total[1] << 3);
	low = (ctx->total[0] << 3);

	FN_PUT_UINT32(high, msglen, 0);
	FN_PUT_UINT32(low, msglen, 4);

	last = ctx->total[0] & 0x3F;
	padn = (last < 56) ? (56 - last) : (120 - last);

	cm_sha256_update(ctx, vs_cm_sha256_padding, padn);
	cm_sha256_update(ctx, msglen, 8);

	FN_PUT_UINT32(ctx->state[0], digest, 0);
	FN_PUT_UINT32(ctx->state[1], digest, 4);
	FN_PUT_UINT32(ctx->state[2], digest, 8);
	FN_PUT_UINT32(ctx->state[3], digest, 12);
	FN_PUT_UINT32(ctx->state[4], digest, 16);
	FN_PUT_UINT32(ctx->state[5], digest, 20);
	FN_PUT_UINT32(ctx->state[6], digest, 24);
	FN_PUT_UINT32(ctx->state[7], digest, 28);
}




//-------------------------- OPENSSL을 이용한 SHA256 --------------------------

// Generate digest for given data.
// @digest : Generated digest will be stored here.
void
SHA256_digest (char *data, int datsz, char digest [SHA256_DIGEST_LENGTH])
{
	SHA256_CTX	ctx;

	SHA256_Init (& ctx);
	SHA256_Update (& ctx, data, datsz);
	SHA256_Final ((unsigned char *)digest, & ctx);
}


// Generate digest and get as string format.
void
SHA256_digest_string (char *data, int datsz, char str [128])
{
	char	digest [SHA256_DIGEST_LENGTH];
	int		i = 0;

	SHA256_digest (data, datsz, digest);

	for (i = 0; i < SHA256_DIGEST_LENGTH; i ++) {
		snprintf (& str [i * 2], 3, "%02x", (unsigned int) digest [i]);
	}

	printf("DIGEST STR=%s\n", str);
}

void SHA256_digest_string_sz (char *data, int datsz, char str [], int sz)
{
	char	digest [SHA256_DIGEST_LENGTH];
	int		i = 0;

	SHA256_digest (data, datsz, digest);

	for (i = 0; i < sz && i < SHA256_DIGEST_LENGTH; i ++) {
		str[i] = digest[i];
	}
}

#if 0
void
SHA256_sample (void)
{
	char	usrid [32] = "11qqaa";
	char	usrpwd [32] = "11qqaa..";

	char	sha256_id [128];
	char	sha256_pwd [128];

	SHA256_digest_string (usrid, strlen (usrid), sha256_id);
	SHA256_digest_string (usrpwd, strlen (usrpwd), sha256_pwd);

	printf ("id:%s  SHA256:%s\n", usrid, sha256_id);
	printf ("pwd:%s  SHA256:%s\n", usrpwd, sha256_pwd);
}
#endif

#define BEGIN_SYSTEM(fp, cmd, buf)\
	do {\
		printf("### Execute : %s ###\n", cmd);\
		pthread_mutex_lock (& system_lock);\
		if ((fp = popen (cmd, "r")) == NULL) {\
			perror ("popen");\
			pthread_mutex_unlock (& system_lock);\
			break;\
		}\
		pthread_mutex_unlock (& system_lock);\
		while (fgets (buf, sizeof (buf), fp)) {\
			if(strstr(buf, "bad") != NULL) {\
				perror("bad execution");\
				pthread_mutex_unlock (& system_lock);\
				break;\
			}\
			printf(buf);

#define END_SYSTEM\
		}\
		pclose (fp);\
		fp = NULL;\
		printf("### done ###\n");\
	} while (0);

#include <pthread.h>
pthread_mutex_t		system_lock;

#define _USE_PIPE	1
#if defined(SHA256SUM_TEST)
int main(void)
{
	char temp[256];
	char data[256];
	snprintf(temp, sizeof(temp), "v4.08.19");
	SHA256_digest_string (temp, strlen(temp), data);
	printf("data = %s\n", data);

	char cmd[256];
	const char* src_file = "/edvr/loadbin";
	const char* enc_file = "/edvr/loadbin.enc";
	const char* dec_file = "/edvr/loadbin.dec";
	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);
	snprintf(cmd, sizeof(cmd), "openssl aes-256-cbc -salt -in %s -out %s -pass pass:1%s", src_file, enc_file, data);
#if _USE_PIPE
	char input_line[1024];
	int inputSize = sizeof(input_line);
	FILE* fp;
	BEGIN_SYSTEM(fp, cmd, input_line)
	END_SYSTEM
	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);
#if 0
	fp = popen(cmd, "r");
	if(fp == NULL) {
		printf("err cmd = %s\n", cmd);
		return -1;
	}

	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);

	do{
		printf("[%s:%d] waiting = %s\n", __FILE__, __LINE__, input_line);
		if(strstr(input_line, "bad") != NULL) {
			printf("[%s:%d] failed to decrypt\n", __FILE__, __LINE__);
			goto out;
		}
	}while(fgets(input_line, inputSize, fp) != NULL);
	pclose(fp);
	fp = NULL;
#endif
#else
	int ret = system(cmd);
	if(ret == -1 || ret == 0) {
		printf("[%s:%d] err cmd(%d) = %s\n", __FILE__, __LINE__, ret, cmd);
		return -1;
	}
#endif

	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);

	memset(cmd, 0, sizeof(cmd));
	snprintf(cmd, sizeof(cmd), "openssl aes-256-cbc -d -in %s -out %s -pass pass:%s", enc_file, dec_file, data);
#if _USE_PIPE
	BEGIN_SYSTEM(fp, cmd, input_line)
	END_SYSTEM
	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);
#if 0

	fp = popen(cmd, "r");
	if(fp == NULL) {
		printf("err cmd = %s\n", cmd);
		return -1;
	}
	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);

	while(fgets(input_line, inputSize, fp) != NULL) {
		printf("[%s:%d] waiting = %s\n", __FILE__, __LINE__, input_line);
		if(strstr(input_line, "bad") != NULL) {
			printf("[%s:%d] failed to decrypt\n", __FILE__, __LINE__);
			goto out;
		}
	}
	pclose(fp);
	fp = NULL;
#endif
#else
	ret = system(cmd);
	if(ret == -1 || ret == 0) {
		printf("[%s:%d] err cmd(%d) = %s\n", __FILE__, __LINE__, ret, cmd);
		return -1;
	}
#endif

	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);

#if _USE_PIPE
out:
	pclose(fp);
	fp = NULL;

	printf("[%s:%d] step!!!\n", __FILE__, __LINE__);
#endif

	return 0;
}
#endif