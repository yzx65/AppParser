/***********************************************************************************
 * Module:												(BuildNum:0011-20110825)
 *       AdkBaseFunc.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		基本支撑库, 特别是一些字符串处理函数(其中只使用了API，而没有用C库)
 *
 * History:
 *          1. 2013.01.25
 *             增加AdkUnicodeToUTF8, AdkUTF8ToUnicode, AdkAnsiToUTF8, AdkUTF8ToAnsi
 * Function:
 *
 *			1. 简易字符判断函数
 *				AdkIsDigitA(W), AdkIsXDigitA(W), 
 *				AdkIsUpperA(W), AdkIsLowerA(W), AdkIsSpaceA(W)
 *				AdkToUpperA(W), AdkToLowerA(W)
 *
 *			2. 常用字符操作函数
 *
 *				AdkStrDupW(A)	- strdup
 *
 *				AkStrChr		- strchr
 *				AdkWcsChr		- wcschr
 *				AdkStrRChr		- strrchr
 *				AdkWcsRChr		- wcsrchr
 *				AdkStrStr		- strstr
 *				AdkWcsStr		- wcsstr
 *
 *				*AdkStrCmp		- lstrcmpA
 *				*AdkWcsCmp		- lstrcmpW
 *				AdkStrCmpI		- lstrcmpi
 *				AdkWcsCmpI		
 *				AdkStrCmpN		- strncmp
 *				AdkWcsCmpN		- wcsncmp
 *				AdkStrCmpNI		- StrCmpNIA
 *				AdkWcsCmpNI		- StrCmpNIW
 *
 *				AdkStrlwr		- strlwr
 *				AdkWcslwr		- wcslwr
 *
 *				*AdkStrCpy		- lstrcpyA
 *				*AdkWcsCpy		- lstrcpyW
 *				*AdkStrCat		- lstrcatA
 *				*AdkWcsCat		- lstrcatW
 *
 *				*AdkStrCpyN		- lstrcpynA
 *				*AdkWcsCpyN		- lstrcpynW
 *
 *				AdkStrLen		- strlen
 *				AdkWcsLen		- wcslen
 *
 *			3. 字符转换函数
 *				
 *				*AdkStrToWStr	  - 将Ansi字符转化为WideString, 该函数经常使用在由FuncxxxA调用FuncxxxW
 *				*AdkWStrToStr	  - 将Wide字符转化为AnsiString
 *              *AdkUnicodeToUTF8 - 将Unicode字符转化为UTF8格式
 *              *AdkUTF8ToUnicode - 将UTF8字符转化为Unicode格式
 *              *AdkAnsiToUTF8    - 将Ansi字符转化为UTF8格式
 *              *AdkUTF8ToAnsi    - 将UTF8字符转化为Ansi格式
 *
 *				AdkStrToul		- strtoul
 *				AdkStrToull		- 转到_ULonglong
 *
 * TODO:
 *		函数名前加*的说明只能在用户态使用
 *
 */

#ifndef __ADK_TUOJIE_STRINGFUNC_H__
#define __ADK_TUOJIE_STRINGFUNC_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#pragma warning(disable:4146)
#pragma warning(disable:4018)

// 简易的字符函数
//
#define _adk_InRange(c, lo, up)  ((UCHAR)c >= lo && (UCHAR)c <= up)
#define _adk_InWRange(c, lo, up)  ((USHORT)c >= lo && (USHORT)c <= up)

#define AdkIsDigitA(c)           _adk_InRange(c, '0', '9')
#define AdkIsDigitW(c)           _adk_InWRange(c, L'0', L'9')

#define AdkIsXDigitA(c)          (AdkIsDigit(c) || _adk_InRange(c, 'a', 'f') || _adk_InRange(c, 'A', 'F'))
#define AdkIsXDigitW(c)          (AdkIsWDigit(c) || _adk_InWRange(c, L'a', L'f') || _adk_InWRange(c, L'A', L'F'))

#define AdkIsLowerA(c)           _adk_InRange(c, 'a', 'z')
#define AdkIsLowerW(c)           _adk_InWRange(c, L'a', L'z')

#define AdkIsUpperA(c)           _adk_InRange(c, 'A', 'Z')
#define AdkIsUpperW(c)           _adk_InWRange(c, L'A', L'Z')

#define AdkIsSpaceA(c)           (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
#define AdkIsSpaceW(c)           (c == L' ' || c == L'\f' || c == L'\n' || c == L'\r' || c == L'\t' || c == L'\v')

	
#ifdef UNICODE

#define AdkStrDup			AdkStrDupW
#define AdkIsDigit			AdkIsDigitW
#define AdkIsXDigit			AdkIsXDigitW
#define AdkIsSpace			AdkIsSpaceW
#define AdkIsUpper			AdkIsUpperW
#define AdkIsLower			AdkIsLowerW
#define AdkToUpper			AdkToUpperW
#define AdkToLower			AdkToLowerW

#else

#define AdkStrDup			AdkStrDupA
#define AdkIsDigit			AdkIsDigitA
#define AdkIsXDigit			AdkIsXDigitA
#define AdkIsSpace			AdkIsSpaceA
#define AdkIsUpper			AdkIsUpperA
#define AdkIsLower			AdkIsLowerA
#define AdkToUpper			AdkToUpperA
#define AdkToLower			AdkToLowerA

#endif // !UNICODE

/***************************************************************
 * _adk_Stoint
 *
 */
INLINE
_ULonglong _adk_Stoint(const char *nptr, char **endptr, int base, int flags) 
{
	int					neg, overflow, once;
	const char			*p;
	_ULonglong			ll_cutoff, ll_cutlim;
	unsigned long		l_cutoff, l_cutlim;
	_ULonglong			ll_value;
	unsigned long		l_value;
	int					n;

	// Part 1, skip white space characters
	//
	p = nptr;
	while(AdkIsSpaceA(*p)) 
	{
		p++;
	}

	// Part 2, Optional sign
	//
	neg = 0;
	if(*p == '+') 
	{
		p++;
	} 
	else if(*p == '-') 
	{
		neg = 1;
		p++;
	}

	// start with 0 for octal, 0x or 0X for hex, rest is decimal 
	//
	if(base == 0) 
	{
		if(*p == '0') 
		{
			if(*(p+1) == 'x' || *(p+1) == 'X') 
			{
				p += 2;
				base = 16;
			} 
			else 
			{
				base = 8;
			}

		}
		else 
		{
			base = 10;
		}
	} 
	else if(base == 16 && *p == '0' && (*(p+1) == 'x' || *(p+1) == 'X')) 
	{
		// Base 16 is allowed to start with 0x or 0X if there
		//
		p += 2;
	}

	ll_cutoff = ll_cutlim = 0;
	l_cutoff = l_cutlim = 0;
	if (flags & _STOINT_LLONG) 
	{
		if(flags & _STOINT_SIGNED) 
		{
			ll_cutoff = neg ? -(_ULonglong)LLONG_MIN : LLONG_MAX;
		} 
		else 
		{
			ll_cutoff = (_ULonglong)ULLONG_MAX;
		}

		ll_cutlim = ll_cutoff % (_ULonglong)(_Longlong) base;
		ll_cutoff = ll_cutoff / (_ULonglong)(_Longlong) base;
	} 
	else 
	{
		if(flags & _STOINT_SIGNED) 
		{
			l_cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
		}
		else 
		{
			l_cutoff = (_ULonglong)ULONG_MAX;
		}

		l_cutlim = l_cutoff % (unsigned long) base;
		l_cutoff = l_cutoff / (unsigned long) base;
	}

	ll_value = 0;
	l_value = 0;
	once = overflow = 0;

	// Only valid bases are 2 to 36
	//
	if(base >= 2 && base <= 36) 
	{
		while((n = *p)) 
		{
			_ULonglong					ll_save;
			unsigned long				l_save;

			/* Adjust character to from a char to an integer */
			if(n >= '0' && n <= '9') 
			{
				n -= '0';
			} 
			else if(n >= 'a' && n <= 'z') 
			{
				n -= 'a' - 10;
			} 
			else if(n >= 'A' && n <= 'Z') 
			{
				n -= 'A' - 10;
			} 
			else 
			{
				// Unknown, done
				break;
			}

			if(n >= base) 
			{
				// Out of radix range, done
				break;
			}

			// Character is valid
			//
			p++;

			// Scale, and add digit, check for overflow
			if (flags & _STOINT_LLONG) 
			{
				if (ll_value > ll_cutoff || (ll_value == ll_cutoff && n > ll_cutlim)) 
				{
					overflow = 1;
				}
				ll_save = ll_value;
				ll_value = ll_value * base + n;
				if(ll_value < ll_save) 
				{
					overflow = 1;
				}
			}
			else 
			{
				if (l_value > l_cutoff || (l_value == l_cutoff && n > l_cutlim)) 
				{
					overflow = 1;
				}
				l_save = l_value;
				l_value = l_value * base + n;
				if(l_value < l_save) 
				{
					overflow = 1;
				}
			}
			once = 1;
		}

		// Check for a signed number overflow
		if(flags & _STOINT_SIGNED) 
		{
		   if(flags & _STOINT_LLONG) 
		   {
			  if(((_Longlong)ll_value < 0) && !(neg && (ll_value == -(_ULonglong)LLONG_MIN))) 
			  {
				 overflow = 1;
			  }
		   } 
		   else 
		   {
			  if(((long)l_value < 0) && !(neg && (l_value == -(unsigned long)LONG_MIN))) 
			  {
				 overflow = 1;
			  }
		   }
		}
	}

	// Store the end of part 2, so caller can get to part 3
	if(endptr) 
	{
		*endptr = (char *)(once ? p : nptr);
	}

	// If base not supported or no conversion was done, return 0 setting errno to EINVAL (UNIX98)
	if(!once) 
	{
		return 0;
	}

	// If no conversion was done, return respective max setting errno to ERANGE (UNIX98)
	//
	if(overflow) 
	{
		if (flags & _STOINT_LLONG) 
		{
			return (flags & _STOINT_SIGNED) ? (neg ? LLONG_MIN : LLONG_MAX) : ULLONG_MAX;
		} 
		else 
		{
			return (flags & _STOINT_SIGNED) ? (neg ? LONG_MIN : LONG_MAX) : ULONG_MAX;
		}
	}

	// Everything OK, return the number
	if (flags & _STOINT_LLONG) 
	{
		return neg ? -ll_value : ll_value;
	} 
	else 
	{
		return neg ? -l_value : l_value;
	}
}

/***************************************************************
 * AdkStrToul
 *
 */
INLINE
unsigned long int AdkStrToul(const char *nptr, char **endptr, int base) 
{
	return (ULONG)_adk_Stoint(nptr, endptr, base, 0);
}

/***************************************************************
 * AdkStrToull
 *
 */
INLINE
_ULonglong AdkStrToull(const char *nptr, char **endptr, int base) 
{
	return (_ULonglong)_adk_Stoint(nptr, endptr, base, _STOINT_LLONG);
}

/***************************************************************
 * AdkToUpperA
 *
 */
INLINE
int AdkToUpperA(int c)
{
	if ((unsigned int)c > 255)
	{
		return(c);
	}

	if (AdkIsLowerA(c))
	{
		return c - 0x20;
	}

	return c;
}

/***************************************************************
 * AdkToUpperW
 *
 */
INLINE
int AdkToUpperW(int c)
{
	if ((unsigned int)c > 255)
	{
		return(c);
	}

	if ( AdkIsLowerW(c))
	{
		return c - 0x20;
	}

	return c;
}

/***************************************************************
 * AdkToLowerA
 *
 */
INLINE
int AdkToLowerA(int c)
{
	if ((unsigned int)c > 255)
	{
		return(c);
	}

	if (AdkIsUpperA(c))
	{
		// A -- Z
		//
		return c + 0x20;
	}

	return c;
}

/***************************************************************
 * AdkToLowerW
 *
 */
INLINE
int AdkToLowerW(int c)
{
	if ((unsigned int)c > 255)
	{
		return(c);
	}

	if (AdkIsUpperW(c))
	{
		// A -- Z
		//
		return c + 0x20;
	}

	return c;
}

#ifndef __KERNEL__

/***************************************************************
 * AdkStrToWStr
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPWSTR AdkStrToWStr(PCSTR lpszString)
{
	PWSTR	lpwzString;
	DWORD	dwWCharNum;

	if (lpszString == NULL)
	{
		xASSERT((FALSE));
		return NULL;
	}

	dwWCharNum = MultiByteToWideChar(CP_ACP, 0, lpszString, -1, NULL, 0);
	if (dwWCharNum == 0)
	{
		return NULL;
	}

	lpwzString = (PWSTR)AdkMalloc(sizeof(WCHAR) * dwWCharNum + 2);
	if (dwWCharNum == MultiByteToWideChar(CP_ACP, 0, lpszString, -1, lpwzString, dwWCharNum))
	{
		return lpwzString;
	}

	AdkFree(lpwzString);

	return NULL;
}

/***************************************************************
 * AdkWStrToStr
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPSTR AdkWStrToStr(PCWSTR lpwzString)
{
	PSTR	lpszString;
	DWORD	dwCharNum;

	if (lpwzString == NULL)
	{
		xASSERT((FALSE));
		return NULL;
	}

	dwCharNum = WideCharToMultiByte(CP_ACP, 0, lpwzString, -1, NULL, 0, NULL, NULL);
	if (dwCharNum == 0)
	{
		return NULL;
	}

	lpszString = (PCHAR)AdkMalloc(sizeof(CHAR) * dwCharNum + 2);
	if (dwCharNum == WideCharToMultiByte(CP_ACP, 0, lpwzString, -1, lpszString, dwCharNum, NULL, NULL))
	{
		return lpszString;
	}
	
	AdkFree(lpszString);

	return NULL;
}

/***************************************************************
 * AdkUnicodeToUTF8
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPSTR AdkUnicodeToUTF8(PCWSTR lpwzString)
{
	PSTR	lpszString;
	DWORD	dwCharNum;

	if (lpwzString == NULL)
	{
		xASSERT((FALSE));
		return NULL;
	}

	dwCharNum = WideCharToMultiByte(CP_UTF8, 0, lpwzString, -1, NULL, 0, NULL, NULL);
	if (dwCharNum == 0)
	{
		return NULL;
	}

	lpszString = (PCHAR)AdkMalloc(sizeof(CHAR) * dwCharNum + 2);
	if (dwCharNum == WideCharToMultiByte(CP_UTF8, 0, lpwzString, -1, lpszString, dwCharNum, NULL, NULL))
	{
		return lpszString;
	}
	
	AdkFree(lpszString);

	
	return NULL;
}


/***************************************************************
 * AdkUTF8ToUnicode
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPWSTR AdkUTF8ToUnicode(PCSTR lpszString)
{
	PWSTR	lpwzString;
	DWORD	dwWCharNum;

	if (lpszString == NULL)
	{
		xASSERT((FALSE));
		return NULL;
	}

	dwWCharNum = MultiByteToWideChar(CP_UTF8, 0, lpszString, -1, NULL, 0);
	if (dwWCharNum == 0)
	{
		return NULL;
	}

	lpwzString = (PWSTR)AdkMalloc(sizeof(WCHAR) * dwWCharNum + 2);
	if (dwWCharNum == MultiByteToWideChar(CP_UTF8, 0, lpszString, -1, lpwzString, dwWCharNum))
	{
		return lpwzString;
	}

	AdkFree(lpwzString);

	return NULL;
}

/***************************************************************
 * AdkAnsiToUTF8
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPSTR AdkAnsiToUTF8(PCSTR lpszString)
{
	LPWSTR lpwzTmp = AdkStrToWStr(lpszString);
	if ( !lpwzTmp )
	{
		return NULL;
	}
	LPSTR lpszTmp = AdkUnicodeToUTF8(lpwzTmp );
	AdkFree(lpwzTmp);

	return lpszTmp;
}
/***************************************************************
 * AdkUTF8ToAnsi
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPSTR AdkUTF8ToAnsi(PCSTR lpszString)
{
	LPWSTR lpwzTmp = AdkUTF8ToUnicode(lpszString);
	if ( !lpwzTmp )
	{
		return NULL;
	}
	LPSTR lpszTmp = AdkWStrToStr((LPCWSTR)lpwzTmp);
	AdkFree(lpwzTmp);

	return lpszTmp;
}

/***************************************************************
 * AdkStrCpy
 *
 */
INLINE
LPSTR AdkStrCpy(LPSTR lpDstString, LPCSTR lpSrcString)
{
	return lstrcpyA(lpDstString, lpSrcString);
}

/***************************************************************
 * AdkWcsCpy
 *
 */
INLINE
LPWSTR AdkWcsCpy(LPWSTR lpDstString, LPCWSTR lpSrcString)
{
	return lstrcpyW(lpDstString, lpSrcString);
}

/***************************************************************
 * AdkStrCat
 *
 */
INLINE
LPSTR AdkStrCat(LPSTR lpDstString, LPSTR lpSrcString)
{
	return lstrcatA(lpDstString, lpSrcString);
}

/***************************************************************
 * AdkWcsCat
 *
 */
INLINE
LPWSTR AdkWcsCat(LPWSTR lpDstString, LPWSTR lpSrcString)
{
	return lstrcatW(lpDstString, lpSrcString);
}

/***************************************************************
 * AdkStrCmp
 *
 */
INLINE
int AdkStrCmp(LPCSTR lpString1, LPCSTR lpString2)
{
	return lstrcmpA(lpString1, lpString2);
}

/***************************************************************
 * AdkWcsCmp
 *
 */
INLINE
int AdkWcsCmp(LPCWSTR lpString1, LPCWSTR lpString2)
{
	return lstrcmpW(lpString1, lpString2);
}

/***************************************************************
 * AdkStrCpyN
 *
 */
INLINE
LPSTR AdkStrCpyN(LPSTR lpString1, LPCSTR lpString2, int iMaxLength)
{
	return lstrcpynA(lpString1, lpString2, iMaxLength);
}

/***************************************************************
 * AdkWcsCpyN
 *
 */
INLINE 
LPWSTR AdkWcsCpyN(LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength)
{
	return lstrcpynW(lpString1, lpString2, iMaxLength);
}

#endif // !__KERNEL

/***************************************************************
 * AdkStrCmpI
 *
 */
INLINE
int AdkStrCmpI(const char *s1, const char *s2)
{
	const unsigned char *p1 = (const unsigned char *) s1;
	const unsigned char *p2 = (const unsigned char *) s2;
	unsigned char c1, c2;

	xASSERT((s1));
	xASSERT((s2));

	if (p1 == p2)
	{
		return 0;
	}

	do
    {
		c1 = AdkToLowerA(*p1++);
		c2 = AdkToLowerA(*p2++);
		if (c1 == '\0')
		{
			break;
		}

	} while (c1 == c2);

	return c1 - c2;
}

/***************************************************************
 * AdkStrCmpN
 *
 */
INLINE
int AdkStrCmpN(const char * s1, const char * s2, int n)
{
	unsigned char u1, u2;

	xASSERT((s1));
	xASSERT((s2));

	while(n-- > 0)
	{
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;

		if (u1 != u2)
		{
			return u1 - u2;
		}

		// 这是一种情况： s1和s2是相等的字符串，但N值给得特别大，就会从下一个判断中离开
		//
		if (u1 == '\0')
		{
			return 0;
		}
	}

	return 0;
}

/***************************************************************
 * AdkStrCmpNI
 *
 */
INLINE
int AdkStrCmpNI(const char * s1, const char * s2, int n)
{
	const unsigned char *p1 = (const unsigned char *) s1;
	const unsigned char *p2 = (const unsigned char *) s2;
	unsigned char c1, c2;

	xASSERT((s1));
	xASSERT((s2));

	if ((p1 == p2) || (n == 0))
	{
		return 0;
	}

	do
    {
		c1 = AdkToLowerA (*p1++);
		c2 = AdkToLowerA (*p2++);

		if (c1 == '\0')
		{
			break;
		}

    } while ((c1 == c2) && --n);

	return c1 - c2;
}

/***************************************************************
 * AdkWcsCmpI
 *
 */
INLINE
int AdkWcsCmpI(const wchar_t *s1, const wchar_t *s2)
{
	const unsigned short *p1 = (const unsigned short *) s1;
	const unsigned short *p2 = (const unsigned short *) s2;
	unsigned short c1, c2;

	xASSERT((s1));
	xASSERT((s2));

	if (p1 == p2)
	{
		return 0;
	}

	do
    {
		c1 = AdkToLowerW(*p1++);
		c2 = AdkToLowerW(*p2++);
		if (c1 == L'\0')
		{
			break;
		}

	} while (c1 == c2);

	return c1 - c2;
}

/***************************************************************
 * AdkWcsCmpN
 *
 */
INLINE
int AdkWcsCmpN(const wchar_t * s1, const wchar_t * s2, int n)
{
	unsigned short u1, u2;

	xASSERT((s1));
	xASSERT((s2));

	while(n-- > 0)
	{
		u1 = (unsigned short) *s1++;
		u2 = (unsigned short) *s2++;

		if (u1 != u2)
		{
			return u1 - u2;
		}

		// 这是一种情况： s1和s2是相等的字符串，但N值给得特别大，就会从下一个判断中离开
		//
		if (u1 == L'\0')
		{
			return 0;
		}
	}

	return 0;
}

/***************************************************************
 * AdkWcsCmpNI
 *
 */
INLINE
int AdkWcsCmpNI(const wchar_t * s1, const wchar_t * s2, int n)
{
	const unsigned short *p1 = (const unsigned short *) s1;
	const unsigned short *p2 = (const unsigned short *) s2;
	unsigned short c1, c2;

	xASSERT((s1));
	xASSERT((s2));

	if ((p1 == p2) || (n == 0))
	{
		return 0;
	}

	do
    {
		c1 = AdkToLowerW (*p1++);
		c2 = AdkToLowerW (*p2++);

		if (c1 == L'\0')
		{
			break;
		}

    } while ((c1 == c2) && --n);

	return c1 - c2;
}

/***************************************************************
 * AdkStrLen
 *
 */
INLINE
int AdkStrLen(const char *lpszStr)
{
	const  char *s;

	xASSERT((lpszStr));

	if (lpszStr == NULL)
	{
		return 0;
	}

	for (s = lpszStr; *s; ++s)
	{
		;
	}

	return (int)(s - lpszStr);
}

/***************************************************************
 * AdkWcsLen
 *
 */
INLINE
int AdkWcsLen(const wchar_t * lpwzStr)
{
	const wchar_t *s;

	xASSERT((lpwzStr));

	if (lpwzStr == NULL)
	{
		return 0;
	}

	for (s = lpwzStr; *s; ++s)
	{
		;
	}

	return (int)(s - lpwzStr);
}

/***************************************************************
 * AdkStrDupW
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPWSTR AdkStrDupW(PCWSTR lpwzStr)
{
	PWSTR	lpwzDupStr;

	if (lpwzStr == NULL)
	{
		xASSERT((FALSE));
		return NULL;
	}

#ifdef __KERNEL__
	lpwzDupStr = (PWSTR)AdkMalloc(NonPagedPool, sizeof(WCHAR) * AdkWcsLen(lpwzStr) + 2);
#else
	lpwzDupStr = (PWSTR)AdkMalloc(sizeof(WCHAR) * AdkWcsLen(lpwzStr) + 2);
#endif // ! __KERNEL__

	if (lpwzDupStr)
	{
		AdkCopyMemory(lpwzDupStr, (PVOID)lpwzStr, sizeof(WCHAR) * AdkWcsLen(lpwzStr));
	}

	return lpwzDupStr;
}

/***************************************************************
 * AdkStrDupA
 *
 *		需要对返回结果进行AdkFree
 *
 */
INLINE
LPSTR AdkStrDupA(PCSTR lpszStr)
{
	PSTR	lpszDupStr;

	if (lpszStr == NULL)
	{
		xASSERT((FALSE));
		return NULL;
	}

#ifdef __KERNEL__
	lpszDupStr = (PSTR)AdkMalloc(NonPagedPool, sizeof(CHAR) * AdkStrLen(lpszStr) + 1);
#else
	lpszDupStr = (PSTR)AdkMalloc(sizeof(CHAR) * AdkStrLen(lpszStr) + 1);
#endif // ! __KERNEL__

	if (lpszDupStr)
	{
		AdkCopyMemory(lpszDupStr, (PVOID)lpszStr, sizeof(CHAR) * AdkStrLen(lpszStr) + 1);
	}

	return lpszDupStr;
}

/***************************************************************
 * AdkStrlwr
 *
 */
INLINE 
PCHAR AdkStrlwr(PCHAR lpszStr)
{
	PCHAR p_itr = lpszStr;

	xASSERT((lpszStr));

	while (*p_itr)
	{
		if (AdkIsUpperA(*p_itr))
		{
			*p_itr = *p_itr + 0x20;
		}

		++p_itr;
	}

	return lpszStr;
}

/***************************************************************
 * AdkWcslwr
 *
 */
INLINE 
PWCHAR AdkWcslwr(PWCHAR lpwzStr)
{
	PWCHAR p_itr = lpwzStr;

	xASSERT((lpwzStr));

	while (*p_itr)
	{
		if (AdkIsUpperW(*p_itr))
		{
			*p_itr = *p_itr + 0x20;
		}

		++p_itr;
	}

	return lpwzStr;
}

/***************************************************************
 * AdkStrChr
 *
 */
INLINE
char *AdkStrChr(const char *s, int c)
{
	for (;;)
    {
		if (*s == c)
		{
			return (char *) s;
		}

		if (*s == 0)
		{
			break;
		}

		s++;
    }

	return 0;
}

/***************************************************************
 * AdkWcsChr
 *
 */
INLINE
wchar_t * AdkWcsChr(const wchar_t *s, wchar_t c)
{	
	for (;;)
	{
		if ( *s == c)
		{
			return (wchar_t *) s;
		}

		if (*s == L'\0')
		{
			break;
		}

		s++;
	}

	return 0;
}

/***************************************************************
 * AdkStrRChr
 *
 */
INLINE
char *AdkStrRChr(const char *s, int c)
{
	int i = 0;

	while (s[i] != 0)
	{
		i++;
	}

	do
	{
		if (s[i] == c)
		{
			return (char *) s + i;
		}

	} while (i-- != 0);

	return 0;
}

/***************************************************************
 * AdkWcsRChr
 *
 */
INLINE
wchar_t *AdkWcsRChr(const wchar_t *s, int c)
{
	int i = 0;

	while (s[i] != L'\0')
	{
		i++;
	}

	do
	{
		if (s[i] == c)
		{
			return (wchar_t *) s + i;
		}

	} while (i-- != 0);

	return 0;
}

/***************************************************************
 * AdkStrStr
 *
 */
INLINE
char * AdkStrStr(const char *s1, const char *s2)
{
	const char *p, *q;

	if (s1 == NULL || s2 == NULL)
	{
		return NULL;
	}

	// deliberately dumb algorithm 
	//
	for (; *s1; s1++)
    {
		p = s1, q = s2;
		while (*q && *p)
		{
			if (*q != *p)
			{
				break;
			}

			p++, q++;
		}

		if (*q == 0)
		{
			return (char *)s1;
		}
	}

	return NULL;
}

/***************************************************************
 * AdkWcsStr
 *
 */
INLINE
wchar_t * AdkWcsStr(const wchar_t *s1, const wchar_t *s2)
{
	const wchar_t *p, *q;

	if (s1 == NULL || s2 == NULL)
	{
		return NULL;
	}

	// deliberately dumb algorithm 
	//
	for (; *s1; s1++)
    {
		p = s1, q = s2;
		while (*q && *p)
		{
			if (*q != *p)
			{
				break;
			}

			p++, q++;
		}

		if (*q == L'\0')
		{
			return (wchar_t *)s1;
		}
	}

	return 0;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // ! __ADK_TUOJIE_STRINGFUNC_H__

/*
 * Revision:
 *
 *		11. 增加了AdkStrCpyN, AdkWcsCpyN两个函数							(0011-20110825)
 *
 *		10. 增加了AdkStrCmp, AdkWcsCmp两个函数								(0010-20110721)
 *
 *		9. 增加了AdkStrLwr,AdkWcsLwr两个函数								(0009-20110716)
 *
 *		8. 增加了AdkIsUpperA(W)、AdkToLowerA(W)、AdkToUpperA(W)				(0008-20110711)
 *				AdkStrCmpI、AdkStrCmpNI、AdkWcsCmpI、AdkWcsCmpNI
 *				AdkStrStr和AdkWscStr增加了对参数的检查
 *
 *		7. 更正了AdkWStrToStr的一个BUG	(0007-20110630)
 *
 *		6. 增加了四个函数				(0006-20100914)
 *			AdkStrCpy, AdkWcsCpy、AdkStrCat、AdkWcsCat
 *
 *		5. 增加了两个函数				(0005-20100802)
 *			AdkStrLen, AdkWcsLen
 *
 *		4. 增加了两个函数				(0004-20100801)
 *			AdkStrCmpN, AdkWcsCmpN
 *
 *		3. 增加了下列函数或预定义变量	(0003-20100624)
 *			AdkIsDigitA(W), AdkIsXDigitA(W), AdkIsLowerA(W), AdkIsSpaceA(W)
 *			AdkStrChr, AdkWcsChr、AdkStrRChr、AdkWcsRChr、AdkStrStr、AdkWcsStr
 *			AdkStrToul, AdkStrToull
 *
 *		2. 增加了三个函数				(0002-20100416)
 *			AdkWStrToStr、AdkStrDupW、AdkStrDupA
 *
 *		1. AdkStrToWStr (0001-20100326)
 *
 *****************************************************************************/