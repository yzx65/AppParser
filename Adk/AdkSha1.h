/**************************************************************
 * Module:
 *        AdkSha1.h
 *
 * Author:
 *       DING ZHAOKUN (dzkad@hotmail.com)
 *
 * Revision Histroy:
 *       Dec 19 2005, Nanjing
 *
 * Dedication:
 *       FOR Happy Life !!!
 *
 * Usage:
 *
 *		BYTE passHash[20];		// // MD5输出160位的摘要长度
 *		SHA_CTX context;
 *		AdkSHA1Init(&context);
 *		AdkSHA1Update(&context, lpData, dwLen);
 *		AdkSHA1Final(&context, passHash);
 */

 #ifndef _ADK_TUOJIE_SHA1_H_
 #define _ADK_TUOJIE_SHA1_H_

typedef struct {
	unsigned int	H[5];
	unsigned int	W[80];
	int				lenW;
	unsigned int	sizeHi;
	unsigned int	sizeLo;

} SHA_CTX;

#define SHA_ROTL(X,n) ((((X) << (n)) | ((X) >> (32-(n)))) & 0xffffffffL)

/**************************************************************
 * SHA1HashBlock
 *
 */
__inline 
static void __stdcall AdkSHA1Transform(SHA_CTX *ctx) 
{
	int t;
	unsigned long A,B,C,D,E,TEMP;

	for (t = 16; t <= 79; t++)
	{
		ctx->W[t] = SHA_ROTL(ctx->W[t-3] ^ ctx->W[t-8] ^ ctx->W[t-14] ^ ctx->W[t-16], 1);
	}

	A = ctx->H[0];
	B = ctx->H[1];
	C = ctx->H[2];
	D = ctx->H[3];
	E = ctx->H[4];

	for (t = 0; t <= 19; t++) 
	{
		TEMP = (SHA_ROTL(A,5) + (((C^D)&B)^D) + E + ctx->W[t] + 0x5a827999L) & 0xffffffffL;
		E = D; 
		D = C; 
		C = SHA_ROTL(B, 30); 
		B = A;
		A = TEMP;
	}

	for (t = 20; t <= 39; t++) 
	{
		TEMP = (SHA_ROTL(A,5) + (B^C^D) + E + ctx->W[t] + 0x6ed9eba1L) & 0xffffffffL;
		E = D;
		D = C; 
		C = SHA_ROTL(B, 30);
		B = A; 
		A = TEMP;
	}

	for (t = 40; t <= 59; t++) 
	{
		TEMP = (SHA_ROTL(A,5) + ((B&C)|(D&(B|C))) + E + ctx->W[t] + 0x8f1bbcdcL) & 0xffffffffL;
		E = D; 
		D = C; 
		C = SHA_ROTL(B, 30);
		B = A;
		A = TEMP;
	}

	for (t = 60; t <= 79; t++) 
	{
		TEMP = (SHA_ROTL(A,5) + (B^C^D) + E + ctx->W[t] + 0xca62c1d6L) & 0xffffffffL;
		E = D; 
		D = C; 
		C = SHA_ROTL(B, 30);
		B = A; 
		A = TEMP;
	}

	ctx->H[0] += A;
	ctx->H[1] += B;
	ctx->H[2] += C;
	ctx->H[3] += D;
	ctx->H[4] += E;
}


/**************************************************************
 * SHA1Init
 *
 */
__inline 
void __stdcall AdkSHA1Init(SHA_CTX *ctx) 
{
	int i;

	ctx->lenW = 0;
	ctx->sizeHi = ctx->sizeLo = 0;

	// Initialize H with the magic constants (see FIPS180 for constants)
	//
	ctx->H[0] = 0x67452301L;
	ctx->H[1] = 0xefcdab89L;
	ctx->H[2] = 0x98badcfeL;
	ctx->H[3] = 0x10325476L;
	ctx->H[4] = 0xc3d2e1f0L;

	for (i = 0; i < 80; i++)
	{
		ctx->W[i] = 0;
	}
}

/**************************************************************
 * SHA1Update
 *
 */
__inline 
void __stdcall AdkSHA1Update(SHA_CTX *ctx, unsigned char *dataIn, int len) 
{
	int i;

	// Read the data into W and process blocks as they get full
	//
	for (i = 0; i < len; i++) 
	{
		ctx->W[ctx->lenW / 4] <<= 8;
		ctx->W[ctx->lenW / 4] |= (unsigned long)dataIn[i];
		if ((++ctx->lenW) % 64 == 0) 
		{
			AdkSHA1Transform(ctx);
			ctx->lenW = 0;
		}

		ctx->sizeLo += 8;
		ctx->sizeHi += (ctx->sizeLo < 8);
	}
}

/**************************************************************
 * SHA1Final
 *
 */
__inline 
void __stdcall AdkSHA1Final(SHA_CTX *ctx, unsigned char hashout[20]) 
{
	unsigned char pad0x80 = 0x80;
	unsigned char pad0x00 = 0x00;
	unsigned char padlen[8];
	int			  i;

	//
	// Pad with a binary 1 (e.g. 0x80), then zeroes, then length
	//

	padlen[0] = (unsigned char)((ctx->sizeHi >> 24) & 255);
	padlen[1] = (unsigned char)((ctx->sizeHi >> 16) & 255);
	padlen[2] = (unsigned char)((ctx->sizeHi >> 8) & 255);
	padlen[3] = (unsigned char)((ctx->sizeHi >> 0) & 255);
	padlen[4] = (unsigned char)((ctx->sizeLo >> 24) & 255);
	padlen[5] = (unsigned char)((ctx->sizeLo >> 16) & 255);
	padlen[6] = (unsigned char)((ctx->sizeLo >> 8) & 255);
	padlen[7] = (unsigned char)((ctx->sizeLo >> 0) & 255);

	SHA1Update(ctx, &pad0x80, 1);

	while (ctx->lenW != 56)
	{
		SHA1Update(ctx, &pad0x00, 1);
	}

	SHA1Update(ctx, padlen, 8);

	// Output hash
	//
	for (i = 0; i < 20; i++) {

		hashout[i] = (unsigned char)(ctx->H[i / 4] >> 24);
		ctx->H[i / 4] <<= 8;
	}

	//
	//  Re-initialize the context (also zeroizes contents)
	//
	SHA1Init(ctx); 

	return;
}

#endif //_ADK_TUOJIE_SHA1_H_