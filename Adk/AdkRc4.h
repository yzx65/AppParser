/*************************************************************
 * Module:
 *        AdkRc4.H
 *
 * Author:
 *        DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Histroy:
 *        Dec 31,2005,Nanjing (created)
 *
 * Limitaion:
 *        The maximum size of buffer should be less than 4GB. In theory
 *        we can crypt/decrypt buffer more than 4GB,but there is recursive
 *        pitfall!
 *          
 * Usage:
 *		RC4加密是一种流式加密，因此需要注意加密时的偏移量
 *
 *		1.通常做法
 *			构建密钥
 *				RC4_KEY	rc4Key;		
 *				AdkBuildRc4Key(lpszKeyData, nKeyLen, &rc4Key);
 *			进行加密
 *				AdkRc4Handler(lpszBuf, nBufLen, &rc4Key);
 *			调整偏移量
 *				AdkSeekRc4Key(offset, &rc4Key);
 *
 *		2. 简便做法 - 只针对单一数据块进行RC4加密
 *			AdkRc4Buffer(lpszBuf, nBufLen, lpszKeyData, nKeyLen);
 *
 *
 */

#ifndef _ADK_TUOJIE_RC4_H_
#define _ADK_TUOJIE_RC4_H_

#include "AdkMemory.h"

typedef struct _RC4_KEY 
{	
	//
	// Only for seek or reset operation 
	//
	unsigned char  init[256];

	//
	// Current Use state
	//
	unsigned char  state[256];

	unsigned char  x;
	unsigned char  y;
	int            off;

}  RC4_KEY,
*LPRC4_KEY;

/**************************************************************
 * rc4_swap_byte
 *
 */
__inline 
static void __stdcall rc4_swap_byte(unsigned char *a,unsigned char *b)
{
	unsigned char  c  = *a;
	*a  = *b;
	*b  = c;
	return ;
}

/**************************************************************
 * AdkBuildRc4Key
 *
 */
__inline 
void __stdcall AdkBuildRc4Key(unsigned char *key_data,
							  int			key_len,
							  RC4_KEY		*aKey)
{
	unsigned char	index1;
	unsigned char	index2;
	unsigned char*	state;
	short			counter;     

	AdkZeroMemory(aKey, sizeof(RC4_KEY));

	state = &aKey->state[0];
	for(counter = 0; counter < 256; counter++)
	{
		state[counter] = (unsigned char)counter;               
	}

	aKey->x   = 0;
	aKey->y   = 0;  
	aKey->off = 0;

	index1    = 0;
	index2    = 0;
	for(counter = 0; counter < 256; counter++)
	{	
		index2 = (key_data[index1] + state[counter] + index2) % 256;
		rc4_swap_byte(&state[counter], &state[index2]);            
		index1 = (index1 + 1) % key_len;
	}

	//
	// Save them for seek & reset operation 
	//
	AdkCopyMemory(&aKey->init[0],&aKey->state[0],256);

	return ;
}

/**************************************************************
 * AdkSeekRc4Key
 *
 */
__inline 
void __stdcall AdkSeekRc4Key(int off, RC4_KEY *aKey)
{ 	
	unsigned char	x;
	unsigned char	y;
	unsigned char*	state;
	int 			counter;

	if (aKey->off > off)
	{
		xTRACEW((L"[seek_rc4_key] From 0 to %d NowOffset %d\r\n", off, aKey->off));

		counter = 0;

		AdkCopyMemory(&aKey->state[0], &aKey->init[0], 256);

		aKey->x  = 0;
		aKey->y  = 0;
	}
	else	// aKey->off <= off
	{
		if (aKey->off < off)
		{
			xTRACEW((L"[seek_rc4_key] From %d to %d\r\n", aKey->off, off));
		}

		counter = aKey->off;
	}

	x     = aKey->x;
	y     = aKey->y;
	state = &aKey->state[0];

	for(; counter < off; counter ++)
	{               	
		x = (x + 1) % 256;
		y = (state[x] + y) % 256;

		rc4_swap_byte(&state[x], &state[y]);
	}

	aKey->x = x;
	aKey->y = y;
	aKey->off = off;

	return ;
}

/**************************************************************
 * AdkRc4Handler
 *
 *    If this buffer is not sequentail by message stream, the 
 * call must call seek_rc4_key to seek aKey's offset correctly
 * before calling this routine!!!
 *
 */
__inline 
void __stdcall AdkRc4Handler(unsigned char	*buffer_ptr, 
							 int			buffer_len, 
							 RC4_KEY		*aKey)
{ 	
	unsigned char	x;
	unsigned char	y;
	unsigned char*	state;
	unsigned char	xorIndex;
	int 			counter;

	x     = aKey->x;
	y     = aKey->y;
	state = &aKey->state[0];

	for(counter = 0; counter < buffer_len; counter ++)
	{               	
		x = (x + 1) % 256;
		y = (state[x] + y) % 256;

		rc4_swap_byte(&state[x], &state[y]);
		
		xorIndex			 = (state[x] + state[y]) % 256; 
		buffer_ptr[counter] ^= state[xorIndex];
		++aKey->off;
	}

	aKey->x = x;
	aKey->y = y;

	return;
}

/*********************************************************************
 * AdkRc4Buffer	
 *
 *
 */
__inline 
void __stdcall AdkRc4Buffer(unsigned char	*lpszBuf, 
							int				nBufLen, 
							unsigned char	*lpszKeyData, 
							int				nKeyLen)
{
	RC4_KEY	rc4Key;

	xASSERT((lpszBuf));
	xASSERT((lpszKeyData));

	AdkBuildRc4Key(lpszKeyData, nKeyLen, &rc4Key);
	AdkRc4Handler(lpszBuf, nBufLen, &rc4Key);
	return;
}

#endif // ! _ADK_TUOJIE_RC4_H_

/*
 * Revision:
 *
 *		2. XIEBO:增加了函数AdkRc4Buffer (0002-20100903)
 *
 *		1. DZK:继承原有的AdkRc4.h (0001-20100601)
 *
 *****************************************************************************/