/*************************************************************
 * Module:								 (BuildNum : 0002-20110619)
 *        AdkBase64.h
 *
 * Author:
 *        DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Histroy:
 *        Dec 31,2005,Nanjing (created)
 *
 * Description:
 *
 *       Base64编码:Base64是网络上最常见的用于传输8Bit字节代码的编码方式之一。
 *
 *       Base64要求把每三个8Bit的字节转换为四个6Bit的字节（3*8 = 4*6 = 24），然后把6Bit再添两位高位0，组成四个8Bit的字节。
 * 　　  关于这个编码的规则： 　　
 *			① 把3个字符变成4个字符.. 　　
 *			② 每76个字符加一个换行符.. 　　
 *			③ 最后的结束符也要处理.. 　　
 *
 *		标准的Base64并不适合直接放在URL里传输，因此产生了很多的变形:
 *			标准Base 64					+ / =
 *			URL Base64					* _
 *			正则表达式 Base64			! -
 *			..		
 *		注:当前只实现了标准的Base64编码
 *
 * Usage:
 *
 *		标准Base64编解码函数
 *
 *		  需要事先分配内存
 *			int AdkBase64Encode(unsigned char  *lpbyPlainBuf, 
 *								int				nPlainBufLen, 
 *								PCHAR			lpszEncodeBuf, 
 *								int				nEncodeBufSize)
 *
 *			int AdkBase64Decode(PCHAR			lpszBase64Buf,
 *								int				nBase64BufLen,
 *								unsigned char  *lpbyDecodeBuf,
 *								int				nDecodeBufSize);
 *
 *		  不需要事先分配内存
 *			PCHAR AdkBase64EncodeEx(unsigned char  *lpszPlainBuf,
 *									int				nPlainBufLen,
 *									int			   *lpnEncodeLen);
 *
 *			PVOID AdkBase64DecodeEx(PCHAR		lpszBase64Buf,
 *									int			nBase64Len,
 *									int		   *lpnDecodeLen);
 *
 *	TODO:
 *		
 *		1. 目前标准编码还有一点没做 - 每76个字节增加分行符
 *		2. 实现其它变形的Base64编码
 *		
 *
 */

#ifndef _ADK_TUOJIE_BASE64_H_
#define _ADK_TUOJIE_BASE64_H_

#define BASE64_INVALID_CHAR        (unsigned long)-2
#define BASE64_IGNORE_CHAR         (unsigned long)-1

/**************************************************************
 * binary_from_ASCII
 *
 */
__inline
unsigned long binary_from_ASCII(char alpha)
{
	switch (alpha)
	{
	case '+':
		return 62;

	case '/': 
		return 63;

	case ' ':
	case '\t':
	case '\n':
	case '\r':

		return (BASE64_IGNORE_CHAR);

	default:

		if (  ('A' <= alpha) && ('Z' >= alpha) )
		{
			return (int)(alpha - 'A');
		}
		else if ( ('a' <= alpha) && ('z' >= alpha) )
		{
			return (int)(26 + (int)(alpha - 'a'));
		}
		else if ( ('0' <= alpha) && ('9' >= alpha) )
		{
			return (52  + (int)(alpha - '0'));
		}
	}

	return BASE64_INVALID_CHAR;
}

/**************************************************************
 * AdkBase64Decode
 *
 * 参数说明：
 *		lpszBase64Buf		- 指向Base64编码的内容
 *		nBase64BufLen		- Base64编码长度
 *		lpbyDecodeBuf		- 指向解码后的空间
 *		nDecodeBufSize		- lpbyDecodeBuf所指向的内存长度
 *
 * 返回值：
 *		若返回值>0, 说明是解码后的长度
 *		若返回为=0, 说明lpszBase64Buf指向的空间包含非法字符
 *
 * 注意：
 *		当lpbyDecodeBuf空间长度不够的时候，是解码多少算多少
 *
 */
__inline
int AdkBase64Decode(const char*		lpszBase64Buf,
					int				nBase64BufLen,
					unsigned char * lpbyDecodeBuf,
					int				nDecodeBufSize)
{
	int           i     = 0;
	int           shift = 0;
	unsigned long accum = 0;
	unsigned long value;

	xASSERT((lpszBase64Buf));
	xASSERT((lpbyDecodeBuf));

    nDecodeBufSize--;

	for ( ; ; ++lpszBase64Buf)
	{
		value = binary_from_ASCII(*lpszBase64Buf);

		if (value < 64)
		{
			accum <<= 6;
			shift  += 6;
			accum  |= value;

			if (shift >= 8)
			{
				shift -= 8;
				value  = accum >> shift;

				lpbyDecodeBuf[i++] = (unsigned char)value & 0xFF;
				if (i >= nDecodeBufSize)
				{
					break;
				}
			}
		}
		else if ( BASE64_IGNORE_CHAR == value)
		{
			continue;
		}
		else
		{
			break;
		}
	}
	
	if (i > 0)
	{
		lpbyDecodeBuf[i] = '\0';
	}

	return i;
}

/**************************************************************
 * AdkBase64DecodeEx
 *
 * 参数说明：
 *		lpszBase64Buf		- 指向Base64编码的内容
 *		nBase64BufLen		- Base64编码长度
 *		lpnDecodeLen		- 解码后的长度（指针）
 *
 * 返回值：
 *		返回为NULL，说明包含非法字符
 *		否则为包含解码后的空间 (注：不使用时，需要手工调用AdkFree进行释放)
 *
 */
__inline
PVOID AdkBase64DecodeEx(PCHAR		lpszBase64Buf,
						int			nBase64BufLen,
						int			*lpnDecodeLen)
{
	int		nDecodeLen = nBase64BufLen + 2;			// BASE64解码的长度会小一点
	PVOID	lpDecodeBuf = AdkMalloc(nDecodeLen);		

	if (lpDecodeBuf)
	{
		nDecodeLen = AdkBase64Decode(lpszBase64Buf, nBase64BufLen, (PUCHAR)lpDecodeBuf, nDecodeLen);
		if (nDecodeLen == 0)
		{
			AdkFree(lpDecodeBuf);
			return NULL;
		}

		if (lpnDecodeLen)
		{
			*lpnDecodeLen = nDecodeLen;
		}
	}

	return lpDecodeBuf;
}

/**************************************************************
 * AdkBase64Encode
 *
 * 参数说明：
 *		lpbyPlainBuf		- 指向原文内容
 *		nPlainBufLen		- 需要编码的长度
 *		lpszEncodeBuf		- 指向编码后的空间
 *		nEncodeBufSize		- lpszEncodeBuf所指向的内存长度
 *
 * 返回值：
 *		若返回值为编码后的长度
 *		若返回值为0,说明编码失败
 *
 */
__inline
int AdkBase64Encode(unsigned char  *lpbyPlainBuf, 
					int				nPlainBufLen, 
					PCHAR			lpszEncodeBuf, 
					int				nEncodeBufSize)
{
	static char const alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int			      i          = 0;
	int               shift      = 0;
    int               save_shift = 0;
    unsigned long     accum      = 0;
    unsigned char     blivit	;
    unsigned long     value		;
    int               quit       = 0;

	xASSERT((lpbyPlainBuf));
	xASSERT((lpszEncodeBuf));

	nEncodeBufSize -= 3;

    while ( ( nPlainBufLen ) || (shift != 0) )
    {
        if ( ( nPlainBufLen ) && ( quit == 0 ) )
        {
            blivit = *lpbyPlainBuf++;
            --nPlainBufLen;
        }
        else
        {
            quit = 1;
            save_shift = shift;
            blivit = 0;
        }

        if ( (quit == 0) || (shift != 0) )
        {
            value = (unsigned long)blivit;
            accum <<= 8;
            shift += 8;
            accum |= value;
        }

        while ( shift >= 6 )
        {
            shift -= 6;
            value = (accum >> shift) & 0x3Fl;
            blivit = alphabet[value];
            lpszEncodeBuf[i++] = blivit;
            if ( quit != 0 )
            {
                shift = 0;
            }
        }
    }

    if ( save_shift == 2 )
    {
        lpszEncodeBuf[i++] = '=';
        lpszEncodeBuf[i++] = '=';
    }
    else if ( save_shift == 4 )
    {
       lpszEncodeBuf[i++] = '=';
    }

    lpszEncodeBuf[i] = '\0';

    return i;
}

/**************************************************************
 * AdkBase64EncodeEx
 *
 * 参数说明：
 *		lpszPlainBuf		- 指向原文的指针
 *		nPlainBufLen		- 原文长度
 *		lpnEncodeLen		- 编码后的长度（指针）
 *
 * 返回值：
 *		返回为NULL，说明编码失败
 *		否则为包含编码后的空间 (注：不使用时，需要手工调用AdkFree进行释放)
 *
 * History
 * 1. 2014.03.20
 */
__inline
PCHAR AdkBase64EncodeEx(unsigned char  *lpszPlainBuf,
						int				nPlainBufLen,
						int				*lpnEncodeLen)
{
	int		nBase64Len = nPlainBufLen * 3 + 8;		// 2014.03.20：3倍的空间不够
	PCHAR   lpszBase64Buf = (PCHAR)AdkMalloc(nBase64Len);

	if (lpszBase64Buf)
	{
		nBase64Len = AdkBase64Encode(lpszPlainBuf, nPlainBufLen, lpszBase64Buf, nBase64Len);
		if (nBase64Len == 0)
		{
			AdkFree(lpszBase64Buf);
			return NULL;
		}

		if (lpnEncodeLen)
		{
			*lpnEncodeLen = nBase64Len;
		}
	}
	
	return lpszBase64Buf;
}


#endif // ! _ADK_TUOJIE_BASE64_H_

/*
 * Revision:
 *
 *		2. 更正了几个BUG (0002-20110619)
 *
 *		1. 第一次成型,包含标准Base64的四个函数 (0001-20100914)
 *
 *****************************************************************************/
