/***************************************************************************
 * Module:
 *      AdkLicense.h
 *
 * Author:
 *		XieBo(1557360050@qq.com)
 *
 * Time:
 *		2014-2,Nanjing
 *
 * Notes:
 *		与试用期控制相关的一些函数
 *
 * Functions:
 *
 *      1. 2014-04
 *			1. 获取时间函数，提供获取主机时间和从网络获取当前日期的函数
 *				AdkGetCurrentTime()             获取系统的当前时间，返回的是一个DWORD值
 *              AdkGetTmFromDword()             由一个DWORD值得到年月日等信息，输出是一个time.h中定义的数据结构struct tm
 *				AdkGetTimeFromInternet          由互联网获取时间信息，输出是一个time.h中定义的数据结构struct tm
 *              AdkGetTmFromFileTime            由一个文件时间，得到struct tm时间
 *		
 *          2. License相关函数
 *              AdkVerifyLicense0()             由一个DWORD时间与License信息比较，验证其是否过期
 *              AdkVerifyLicense1()             由一个struct tm时间与License信息比较，验证其是否过期
 *              AdkGetLicenseInfo()             从License文件获取License信息
 *              AdkGenericLicenseFile()         生成License文件，与AdkGetLicenseInfo对应
 *
 *             用法如下：
 *              需要验证License的程序，使用AdkGetLicenseInfo()从License文件中获取License信息，再使用基准时间调用AdkVerifyLicense验证是否过期
 *                  正式版若服务日期已过，提示用户服务日期已过，但不影响功能使用之类的内容
 *                  试用版若截止日期已过，提示用户试用期已结束，联系技术支持之类的内容
 *              试用时，基准时间的获取有两种方式：
 *                  1.从目标主机获取时间，如T系列，H系列对方开机时，E6
 *                  2.从互联网获取时间，如E7、C4
 *
 *          3. 其它函数
 *              AdkGTMToBJ                      将GMT时间转换为北京时间
 *              AdkGetTmFromGMTStr              由 Fri, 21 Feb 2014 01:32:33 GMT 字符串，得到struct tm时间，输出的tm数据结构中，只填充了年月日时分秒信息
 *
 */

#ifndef __ADK_TUOJIE_LICENSE_H__
#define __ADK_TUOJIE_LICENSE_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#pragma warning(disable:4146)
#pragma warning(disable:4018)

#include "AdkPrecomp.h"
#include <time.h>
#include "AdkSocket.h"
#include "AdkFile.h"
#include "AdkRc4.h"


typedef struct _TUOJIE_LICENSE {

	DWORD    dwLicenseMagic;           // 我公司License的识别码

	DWORD    dwDataKey;                // 每个用户的数据标识，在用户获取的数据时，可采用此值作为加密密钥，或者仅采用此值来标识数据，具体的加密与此值无关。

	WCHAR    wzGuid[64];               // 唯一ID值
	WCHAR    wzUser[64];               // 用户描述

#define TUOJIE_LICENSE_DEMO      0     // 试用版
#define TUOJIE_LICENSE_BUSINESS  1     // 正式版

	DWORD    dwLicenseType;
	int      iLastYear;                // 到期年份
	int      iLastMonth;               // 到期月份
	int      iLastDay;                 // 到期日

#define DOG_NONE                 0
#define DOG_TYPE_GRAND           1
#define DOG_TYPE_FD              2

	DWORD    dwDogType;                // 软件狗类型
	CHAR     szDogName[64];            // 软件狗名称
	CHAR     szDogPass[64];            // 软件狗密钥

	// 用于H6和H2验证硬盘
	//
	BOOL     bCheckDisk;               // 是否检验硬盘
	BYTE     byteMd5Hash[16];          // 检验硬盘的序列号产生的HASH值（AdkMd5.h）文件中的系列函数产生）

} TUOJIE_LICENSE, *LPTUOJIE_LICENSE;


#ifdef UNICODE

#define AdkGetLicenseInfo			AdkGetLicenseInfoW
#define AdkGenericLicenseFile       AdkGenericLicenseFileW

#else

#define AdkGetLicenseInfo			AdkGetLicenseInfoA
#define AdkGenericLicenseFile       AdkGenericLicenseFileW

#endif

VOID AdkGetTmFromDword(IN DWORD dwTime, OUT tm *lpTime);

/***************************************************************
 * AdkVerifyLicense0
 *
 * 返回值说明：
 *    0 ：出错
 *    1 ：在有效期之内
 *    2 ：已过有效期
 *
 */
INLINE
DWORD AdkVerifyLicense0(IN CONST LPTUOJIE_LICENSE lpTjLicense, IN CONST DWORD dwTime)
{
	DWORD  dwRet = 0;
	struct tm tmTime;

	AdkGetTmFromDword(dwTime, &tmTime);

	do
	{
		// 判断年
		//
		if ( tmTime.tm_year < lpTjLicense->iLastYear )
		{
			dwRet = 1;
			break;
		}
		if ( tmTime.tm_year == lpTjLicense->iLastYear )
		{
			// 判断月
			//
			if ( tmTime.tm_mon < lpTjLicense->iLastMonth )
			{
				dwRet = 1;
				break;
			}
			if ( tmTime.tm_mon == lpTjLicense->iLastMonth )
			{
				// 判断日
				//
				if ( tmTime.tm_mday < lpTjLicense->iLastDay )
				{
					dwRet = 1;
					break;
				}
				dwRet = 2;
			}
			dwRet = 2;
		}

		dwRet = 2;

	} while (FALSE);

	return dwRet;
}

/***************************************************************
 * AdkVerifyLicense1
 *
 * 返回值说明：
 *    0 ：出错
 *    1 ：在有效期之内
 *    2 ：已过有效期
 *
 */
INLINE
DWORD AdkVerifyLicense1(IN CONST LPTUOJIE_LICENSE lpTjLicense, IN CONST struct tm *lpTime)
{
	DWORD dwRet = 0;

	do
	{
		// 判断年
		//
		if ( lpTime->tm_year < lpTjLicense->iLastYear )
		{
			dwRet = 1;
			break;
		}
		if ( lpTime->tm_year == lpTjLicense->iLastYear )
		{
			// 判断月
			//
			if ( lpTime->tm_mon < lpTjLicense->iLastMonth )
			{
				dwRet = 1;
				break;
			}
			if ( lpTime->tm_mon == lpTjLicense->iLastMonth )
			{
				// 判断日
				//
				if ( lpTime->tm_mday < lpTjLicense->iLastDay )
				{
					dwRet = 1;
					break;
				}
				dwRet = 2;
			}
			dwRet = 2;
		}

		dwRet = 2;

	} while (FALSE);

	return dwRet;
}


/***************************************************************
 * AdkGetLicenseInfoW
 *
 * lpTjLicense为调用者分配的不小于sizeof(TUOJIE_LICENSE)的内存空间，可定义变量TUOJIE_LICENSE ttt，以&ttt为参数传入
 *
 */
INLINE
BOOL AdkGetLicenseInfoW(IN LPCWSTR lpwzLicenseFile, OUT CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	if ( !lpTjLicense )
	{
		return FALSE;
	}

	szKey[7] = '\0';
	szKey[5] = 'w';

	AdkZeroMemory(lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[2] = '9';
	do
	{
		// 读取License
		//
		dwFileSize = AdkGetFileSizeFromNameW(lpwzLicenseFile);
		szKey[3] = 'x';
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			break;
		}
		
		szKey[0] = 'g';
		szKey[6] = 'y';

		if ( !AdkFileReaderW(lpwzLicenseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			break;
		}
		szKey[4] = 's';
		szKey[1] = 'n';

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		AdkCopyMemory(lpTjLicense, &szBuf[1024], sizeof(TUOJIE_LICENSE));

		if ( lpTjLicense->dwLicenseMagic != 19820702 )
		{
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGetLicenseInfoA
 *
 * lpTjLicense为调用者分配的不小于sizeof(TUOJIE_LICENSE)的内存空间，可定义变量TUOJIE_LICENSE ttt，以&ttt为参数传入
 *
 */
INLINE
BOOL AdkGetLicenseInfoA(IN LPCSTR lpszLicenseFile, OUT CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	if ( !lpTjLicense )
	{
		return FALSE;
	}

	szKey[7] = '\0';
	szKey[5] = 'w';

	AdkZeroMemory(lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[2] = '9';
	do
	{
		// 读取License
		//
		dwFileSize = AdkGetFileSizeFromNameA(lpszLicenseFile);
		szKey[3] = 'x';
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			break;
		}
		
		szKey[0] = 'g';
		szKey[6] = 'y';

		if ( !AdkFileReaderA(lpszLicenseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			break;
		}
		szKey[4] = 's';
		szKey[1] = 'n';

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		AdkCopyMemory(lpTjLicense, &szBuf[1024], sizeof(TUOJIE_LICENSE));

		if ( lpTjLicense->dwLicenseMagic != 19820702 )
		{
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGenericLicenseFileW
 *
 * 生成License文件
 *
 */
INLINE
BOOL AdkGenericLicenseFileW(IN LPCWSTR lpwzBaseFile, IN LPCWSTR lpwzLicenseFile, IN CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	TUOJIE_LICENSE tjLicenseInfo;
	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	AdkCopyMemory(&tjLicenseInfo, lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[7] = '\0';
	szKey[1] = 'n';
	
	do
	{
		szKey[2] = '9';
		szKey[0] = 'g';

		// 生成License
		//
		dwFileSize = AdkGetFileSizeFromNameW(lpwzBaseFile);
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			AdkMsgBoxW(L"0 - 未能访问基础文件 with %u", GetLastError());
			break;
		}
		szKey[4] = 's';
		szKey[6] = 'y';
		if ( !AdkFileReaderW(lpwzBaseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			AdkMsgBoxW(L"1 - 未能访问基础文件 with %u", GetLastError());
			break;
		}
		szKey[5] = 'w';
		szKey[3] = 'x';

		AdkCopyMemory(&szBuf[1024], &tjLicenseInfo, sizeof(TUOJIE_LICENSE));

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		if ( !AdkFileWriterW(lpwzLicenseFile, szBuf, dwFileSize) )
		{
			AdkMsgBoxW(L"2 - Internal error with %u", GetLastError());
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGenericLicenseFileA
 *
 * 生成License文件
 *
 */
INLINE
BOOL AdkGenericLicenseFileA(IN LPCSTR lpszBaseFile, IN LPCSTR lpszLicenseFile, IN CONST LPTUOJIE_LICENSE lpTjLicense)
{
	BOOL bRet = FALSE;

	TUOJIE_LICENSE tjLicenseInfo;
	CHAR           szBuf[2048];
	DWORD          dwFileSize;
	DWORD          dwRead;
	CHAR           szKey[16];

	AdkCopyMemory(&tjLicenseInfo, lpTjLicense, sizeof(TUOJIE_LICENSE));

	szKey[7] = '\0';
	szKey[1] = 'n';
	
	do
	{
		szKey[2] = '9';
		szKey[0] = 'g';

		// 生成License
		//
		dwFileSize = AdkGetFileSizeFromNameA(lpszBaseFile);
		if ( dwFileSize < 1200 || dwFileSize > 2000)
		{
			AdkMsgBoxW(L"0 - 未能访问基础文件 with %u", GetLastError());
			break;
		}
		szKey[4] = 's';
		szKey[6] = 'y';
		if ( !AdkFileReaderA(lpszBaseFile, dwFileSize, &dwRead, szBuf, 2048) )
		{
			AdkMsgBoxW(L"1 - 未能访问基础文件 with %u", GetLastError());
			break;
		}
		szKey[5] = 'w';
		szKey[3] = 'x';

		AdkCopyMemory(&szBuf[1024], &tjLicenseInfo, sizeof(TUOJIE_LICENSE));

		AdkRc4Buffer((unsigned char*)szBuf, dwFileSize, (unsigned char*)szKey, lstrlenA(szKey));

		if ( !AdkFileWriterA(lpszLicenseFile, szBuf, dwFileSize) )
		{
			AdkMsgBoxW(L"2 - Internal error with %u", GetLastError());
			break;
		}

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}

/***************************************************************
 * AdkGTMtoBJ
 *
 * 将GMT时间转换为BJ时间
 * tmGTM中的tm_mon的取值范围为 1 - 12
 *
 */
INLINE
VOID AdkGTMtoBJ(tm *tmGTM)
{
	tmGTM->tm_hour += 8;

	if ( tmGTM->tm_hour > 23 )
	{
		tmGTM->tm_mday += 1;
		tmGTM->tm_wday = (tmGTM->tm_wday + 1) % 7;
		tmGTM->tm_yday += 1;
		tmGTM->tm_hour -= 24;

		if ( tmGTM->tm_mon == 1
			|| tmGTM->tm_mon == 3
			|| tmGTM->tm_mon == 5 
			|| tmGTM->tm_mon == 7 
			|| tmGTM->tm_mon == 8 
			|| tmGTM->tm_mon == 10 
			|| tmGTM->tm_mon == 12
			) //1,3,5,7,8,10,12月份
		{
			if ( tmGTM->tm_mday > 31 )
			{
				tmGTM->tm_mon  += 1;
				tmGTM->tm_mday -= 31;

				if ( tmGTM->tm_mon > 11 )
				{
					tmGTM->tm_year += 1;
					tmGTM->tm_mon  -= 11;
				}
			}
		}
		else if ( tmGTM->tm_mon == 4
				  || tmGTM->tm_mon == 6
				  || tmGTM->tm_mon == 9
				  || tmGTM->tm_mon == 11
				  ) //4,6,9,11月份
		{
			if ( tmGTM->tm_mday > 30 )
			{
				tmGTM->tm_mon  += 1;
				tmGTM->tm_mday -= 30;
			}
		}
		else //2月份
		{
			if ( (tmGTM->tm_year %4 == 0 && tmGTM->tm_year % 100 != 0) 
				|| (tmGTM->tm_year % 400 == 0)
				) //如果是闰年
			{
				if ( tmGTM->tm_mday > 29 )
				{
					tmGTM->tm_mon  += 1;
					tmGTM->tm_mday -= 29;
				}
			}
			else
			{
				if ( tmGTM->tm_mday > 28 )
				{
					tmGTM->tm_mon  += 1;
					tmGTM->tm_mday -= 28;
				}
			}
		}
	}

}

/***************************************************************
 * AdkGetTmFromGMTStr
 *
 * 由 Fri, 21 Feb 2014 01:32:33 GMT得到时间
 *
 * 输出的tm数据结构中，只填充了年月日时分秒信息
 * 
 */
INLINE
BOOL AdkGetTmFromGMTStr(PCHAR lpszDate, DWORD dwDateLen, OUT tm *lpTime)
{
	BOOL   bRet = FALSE;
	PCHAR  lpszBegin;
	PCHAR  lpszEnd;
	DWORD  dwMonth = 0;

	if ( dwDateLen > 64 || !lpTime )
	{
		return bRet;
	}
	memset(lpTime, 0, sizeof(struct tm));

	// Date: Fri, 21 Feb 2014 01:32:33 GMT
	//
	do
	{
		// 日信息
		// 找到,
		//
		lpszBegin = AdkStrChr(lpszDate, ',');
		if ( !lpszBegin )
		{
			break;
		}
		lpszBegin++;
		// 跳过,后的空格，得到日的位置
		//
		while ( ' ' == *lpszBegin )
		{
			lpszBegin++;
		}
		// 找到日的结尾处
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_mday = atoi(lpszBegin);

		// 月份信息
		// 得到月的位置
		lpszBegin = lpszEnd + 1;
		// 找到月的结尾处
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 3 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		if ( 0 == AdkStrCmpI(lpszBegin, "Jan") )
		{
			dwMonth = 1;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Feb") )
		{
			dwMonth = 2;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Mar") )
		{
			dwMonth = 3;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Apr") )
		{
			dwMonth = 4;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "May") )
		{
			dwMonth = 5;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Jun") )
		{
			dwMonth = 6;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Jul") )
		{
			dwMonth = 7;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Aug") )
		{
			dwMonth = 8;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Sept") )
		{
			dwMonth = 9;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Oct") )
		{
			dwMonth = 10;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Nov") )
		{
			dwMonth = 11;
		}
		if ( 0 == AdkStrCmpI(lpszBegin, "Dec") )
		{
			dwMonth = 12;
		}
		AdkASSERT((dwMonth));
		lpTime->tm_mon = dwMonth;

		// 年份信息
		// 得到年的位置
		lpszBegin = lpszEnd + 1;
		// 找到年的结尾处
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 4 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_year = atoi(lpszBegin);

		// 小时信息
		// 得到小时的位置
		lpszBegin = lpszEnd + 1;
		// 找到小时的结尾处
		//
		lpszEnd = AdkStrStr(lpszBegin, ":");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 2 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_hour = atoi(lpszBegin);

		// 分钟信息
		// 得到分钟的位置
		lpszBegin = lpszEnd + 1;
		// 找到分钟的结尾处
		//
		lpszEnd = AdkStrStr(lpszBegin, ":");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 2 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_min = atoi(lpszBegin);

		// 秒信息
		// 得到秒的位置
		lpszBegin = lpszEnd + 1;
		// 找到秒的结尾处
		//
		lpszEnd = AdkStrStr(lpszBegin, " ");
		if ( !lpszEnd )
		{
			break;
		}
		if ( 2 != lpszEnd - lpszBegin )
		{
			break;
		}
		*lpszEnd = '\0';
		lpTime->tm_sec = atoi(lpszBegin);

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGetTimeFromInternet
 *
 * lpTime为调用者分配的不小于sizeof(tm)的内存空间，可定义变量struct tm ttt，以&ttt为参数传入
 *
 */
INLINE
BOOL AdkGetTimeFromInternet(OUT tm *lpTime)
{
	BOOL   bRet       = FALSE;
	PCHAR  lpszHeader = NULL;
	PCHAR  lpszDate   = NULL;
	struct tm gmtTime ;

	AdkASSERT((lpTime));
	if ( !lpTime )
	{
		return FALSE;
	}

	do
	{
		// 从Microsoft得到
		//
		lpszHeader = AdkGetResHeaderFromHost("time.windows.com");
		if ( lpszHeader )
		{
			lpszDate = AdkQueryDateInResHeaders(lpszHeader);
			if ( lpszDate )
			{
				if ( AdkGetTmFromGMTStr(lpszDate, strlen(lpszDate), &gmtTime) )
				{
					bRet = TRUE;
					break;
				}
			}
		}

		// 从Google得到
		//
		lpszHeader = AdkGetResHeaderFromHost("www.google.com");
		if ( lpszHeader )
		{
			lpszDate = AdkQueryDateInResHeaders(lpszHeader);
			if ( lpszDate )
			{
				if ( AdkGetTmFromGMTStr(lpszDate, strlen(lpszDate), &gmtTime) )
				{
					bRet = TRUE;
					break;
				}
			}
		}

		// 从Wikipedia得到
		//
		lpszHeader = AdkGetResHeaderFromHost("www.wikipedia.org");
		if ( lpszHeader )
		{
			lpszDate = AdkQueryDateInResHeaders(lpszHeader);
			if ( lpszDate )
			{
				if ( AdkGetTmFromGMTStr(lpszDate, strlen(lpszDate), &gmtTime) )
				{
					bRet = TRUE;
					break;
				}
			}
		}

	} while (FALSE);

	if ( bRet )
	{
		AdkGTMtoBJ(&gmtTime);

		AdkCopyMemory(lpTime, &gmtTime, sizeof(struct tm));
	}
	if ( lpszHeader )
	{
		free(lpszHeader);
	}
	if ( lpszDate )
	{
		free(lpszDate);
	}

	return bRet;
}


/***************************************************************
 * AdkGetTmFromFileTime
 *
 * lpTime为调用者分配的不小于sizeof(tm)的内存空间，可定义变量struct tm ttt，以&ttt为参数传入
 *
 *
 */
INLINE
BOOL AdkGetTmFromFileTime(IN FILETIME *lpFileTime, OUT tm *lpTime)
{
	AdkASSERT((lpTime));
	if ( !lpTime )
	{
		return FALSE;
	}
	FILETIME   localTime ;
	SYSTEMTIME sysTime   ;
	BOOL       bRet      = FALSE;

	do
	{
		if ( !FileTimeToLocalFileTime(lpFileTime, &localTime) )
		{
			break;
		}

		if ( !FileTimeToSystemTime(&localTime, &sysTime) )
		{
			break;
		}
		lpTime->tm_hour  = sysTime.wHour;
		lpTime->tm_min   = sysTime.wMinute;
		lpTime->tm_mday  = sysTime.wDay;
		lpTime->tm_mon   = sysTime.wMonth;
		lpTime->tm_year  = sysTime.wYear;
		lpTime->tm_sec   = sysTime.wSecond;
		lpTime->tm_wday  = sysTime.wDay;
		lpTime->tm_yday  = sysTime.wYear;
		lpTime->tm_isdst = 0;

		bRet = TRUE;

	} while (FALSE);

	return bRet;
}


/***************************************************************
 * AdkGetTmFromDword
 *
 * lpTime为调用者分配的不小于sizeof(tm)的内存空间，可定义变量struct tm ttt，以&ttt为参数传入
 *
 */
INLINE
VOID AdkGetTmFromDword(IN DWORD dwTime, OUT tm *lpTime)
{
	AdkASSERT((lpTime));
	if ( !lpTime )
	{
		return;
	}

	time_t  aclock = dwTime;

	localtime_s(lpTime, &aclock);

	lpTime->tm_year += 1900;
	lpTime->tm_mon  += 1;

	return;
}

/***************************************************************
 * AdkGetCurrentTime
 *
 */
INLINE
DWORD AdkGetCurrentTime()
{
	return (DWORD)time(NULL);
}


#ifdef __cplusplus
}
#endif //__cplusplus

#endif // ! __ADK_TUOJIE_LICENSE_H__