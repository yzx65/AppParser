/***********************************************************************************
 * Module:												(BuildNum:0008-20100307)
 *       AdkDebug.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		提供两种层次的调试语句输出
 *
 *		 - 以使用场景来区分调试语句
 *
 *			AdkTRACEA(W)	- 显示一般调试语句
 *			AdkWARNINGA(W)	- 显示警告
 *			AdkERRORA(W)	- 出现错误
 *			AdkPANICA(W)	- 出现异常错误
 *
 *		 - 以用户自定义的功能来区分调试语句，方便用户打开和关闭某种功能的调试信息
 *
 *			例如定义了两种类型的调试语句，一种用于TCP相关，一种用于UDP，首先需要在文件头部定义
 *			#define TCP_DEBUG	ADK_DBG_ON
 *			#define UDP_DEBUG	ADK_DBG_OFF
 *
 *			接下来，就可以输出调试语句，参见示例
 *
 *		提供了基于MessageBox的消息报告窗口，和传统的消息窗口相比的优点是可以带参数
 *			AdkMsgBoxA(W)
 *			AdkMsgBoxExA(W)
 *			AdkMsgBoxByWndA(W)
 *
 * Example:
 *			xTRACEW((L"[Project] Function : Load %s\r\n", uniPath.Buffer));
 *			xERRORW((L"[Project] Function : ZwSetSystemInformation FAILED 0x%08x\r\n", ntStatus));
 *
 *			xTRACEExA(TCP_DEBUG, ("[Project] Function : Connected To %s:%d ERROR",  szIpAddr, IpPort));
 *			xERRORExA(UDP_DEBUG, ("[Project] Function : Connected To %s:%d FAILED", szIpAddr, IpPort));
 *
 *			AdkMsgBoxEx(this->Handle, "提示", MB_OK | MB_ICONWARNING, "植入模块\"%s\"文件不存在", this->edtTrajonPath->Text.c_str());
 *
 * Histroy:
 *      1. 2013.10.09 xieb
 *          将vsprintf系列函数，改为StringCch系列函数，避免可能出现的栈溢出，增强程序的稳定性
 */

#ifndef __ADK_DEBUG_H__
#define __ADK_DEBUG_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <strsafe.h>

////
// 调试语句的Buffer长度
// 如果需要打印特别长的语句，在包含本头文件之前声明一个ADK_DBG_TRACE_BUFLEN
//

#ifndef ADK_DBG_TRACE_BUFLEN
#define ADK_DBG_TRACE_BUFLEN	2048
#endif // ! ADK_DBG_TRACE_BUFLEN

////
// 过滤显示不同级别的调试语句
// 如果需要进行调整，在包含本头文件之前声明一个ADK_DBG_MIN_LEVEL
//

#ifndef ADK_DBG_MIN_LEVEL
#define ADK_DBG_MIN_LEVEL		ADK_DBG_LEVEL_OFF
#endif

// Lower three bits indicate debug level
//

#define ADK_DBG_LEVEL_OFF		0x00
#define ADK_DBG_LEVEL_TRACE		0x01
#define ADK_DBG_LEVEL_WARNING	0x02
#define ADK_DBG_LEVEL_ERROR		0x03
#define ADK_DBG_LEVEL_PANIC		0x04

#define ADK_DBG_MASK_LEVEL		0x07	// 111

/***************************************************************
 * _AdkCheckDbgLevel
 *
 */
INLINE
BOOL _AdkCheckDbgLevel(BYTE debug)
{
	if ((debug & ADK_DBG_MASK_LEVEL) >= ADK_DBG_MIN_LEVEL)
	{
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------------
//	ASSERT 
//

#ifdef __KERNEL__
#define AdkASSERT         ASSERT
#else
#define AdkASSERT         assert
#endif // !__KERNEL__

/***************************************************************
 * _AdkDebuggerTraceA
 *
 */
INLINE
void _AdkDebuggerTraceA(PSTR p_szFormat,...)
{	
	CHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	HRESULT hResult;

	va_list marker;
	va_start(marker, p_szFormat);
	hResult = StringCchVPrintfA(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, marker);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(marker);

#ifdef __KERNEL__

	DbgPrint(szmsg);

#else	// USER

#ifdef _CONSOLE
	printf(szmsg);
#else
	OutputDebugStringA(szmsg);
#endif

#endif	// ! __KERNEL__

	return ;
}

/***************************************************************
 * _AdkDebuggerTraceW
 *
 */
INLINE
void _AdkDebuggerTraceW(PWSTR lpwzFormat,...)
{
	WCHAR	wzmsg[ADK_DBG_TRACE_BUFLEN];
	HRESULT hResult;

	va_list args;
	va_start(args, lpwzFormat);
	hResult = StringCchVPrintfW(wzmsg, sizeof(wzmsg)/sizeof(wzmsg[0]), lpwzFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

#ifdef __KERNEL__

	DbgPrint("%S",wzmsg);			// DbgPrint 只支持Ansi的字符串

#else	// USER

#ifdef _CONSOLE
	wprintf(wzmsg);
#else
	OutputDebugStringW(wzmsg);
#endif

#endif // ! __KERNEL__

	return ;
}


//----------------------------------------------------------------
//	Debug Trace Function 
//

#ifdef _DEBUG

#define AdkTRACEA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_TRACE)) \
									_AdkDebuggerTraceA _x_ ; \
							} while(FALSE);

#define AdkTRACEW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_TRACE)) \
									_AdkDebuggerTraceW _x_ ; \
							}while(FALSE);

#define AdkWARNINGA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_WARNING)) \
									_AdkDebuggerTraceA _x_ ; \
							} while(FALSE);

#define AdkWARNINGW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_WARNING)) \
									_AdkDebuggerTraceW _x_ ; \
							}while(FALSE);

#define AdkERRORA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_ERROR)) {\
									_AdkDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkDebuggerTraceA _x_ ; \
								}\
							} while(FALSE);

#define AdkERRORW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_ERROR)) {\
									_AdkDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkDebuggerTraceW _x_ ; \
								}\
							}while(FALSE);

#define AdkPANICA(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_PANIC)) {\
									_AdkDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkDebuggerTraceA _x_ ; \
									AdkASSERT(FALSE);	\
								}\
							} while(FALSE);

#define AdkPANICW(_x_)		do {\
								if (_AdkCheckDbgLevel(ADK_DBG_LEVEL_PANIC)) {\
									_AdkDebuggerTraceA("*******file:%s lineno:%d******\r\n",__FILE__,__LINE__);\
									_AdkDebuggerTraceW _x_ ; \
									AdkASSERT(FALSE);	\
								}\
							} while(FALSE);

#else	// RELEASE

#define AdkTRACEA(_x_)
#define AdkTRACEW(_x_)
#define	AdkWARNINGA(_x_)
#define AdkWARNINGW(_x_)
#define AdkERRORA(_x_)
#define AdkERRORW(_x_)
#define AdkPANICA(_x_)
#define AdkPANICW(_x_)

#endif // !_DEBUG

//----------------------------------------------------------------
//	Advanced Debug Trace Function 
//

// flag to enable that debug message 
//
#define ADK_DBG_ON            0x80U

// flag to disable that debug message
//
#define ADK_DBG_OFF           0x00U

#ifdef _DEBUG

#define AdkTRACEExA(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkTRACEA(_x_);		\
								} while(FALSE);

#define AdkTRACEExW(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkTRACEW(_x_);		\
								} while(FALSE);

#define AdkWARNINGExA(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkWARNINGA(_x_);	\
								} while(FALSE);

#define AdkWARNINGExW(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkWARNINGW(_x_);	\
								} while(FALSE);

#define AdkERRORExA(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkERRORA(_x_);		\
								} while(FALSE);

#define AdkERRORExW(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkERRORW(_x_);		\
								} while(FALSE);

#define AdkPANICExA(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkPANICA(_x_);		\
								} while(FALSE);

#define AdkPANICExW(_t_, _x_)	do {\
									if (_t_ == ADK_DBG_ON)	\
										AdkPANICW(_x_);		\
								} while(FALSE);

#else

#define AdkTRACEExA(_t_, _x_)
#define AdkTRACEExW(_t_, _x_)
#define	AdkWARNINGExA(_t_, _x_)
#define AdkWARNINGExW(_t, _x_)
#define AdkERRORExA(_t_, _x_)
#define AdkERRORExW(_t_, _x_)
#define AdkPANICExA(_t_, _x_)
#define AdkPANICExW(_t_, _x_)

#endif // ! _DEBUG

//----------------------------------------------------------------
// Surport UNICODE And ANSI Compile Options
//
#ifdef UNICODE

#define AdkTRACE			AdkTRACEW
#define AdkWARNING			AdkWARNINGW
#define AdkERROR			AdkERRORW
#define AdkPANIC			AdkPANICW

#define AdkTRACEEx			AdkTRACEExW
#define AdkWARNINGEx		AdkWARNINGExW
#define AdkERROREx			AdkERRORExW
#define AdkPANICEx			AdkPANICExW

#else

#define AdkTRACE			AdkTRACEA
#define AdkWARNING			AdkWARNINGA
#define AdkERROR			AdkERRORA
#define AdkPANIC			AdkPANICA

#define AdkTRACEEx			AdkTRACEExA
#define AdkWARNINGEx		AdkWARNINGExA
#define AdkERROREx			AdkERRORExA
#define AdkPANICEx			AdkPANICExA

#endif // !UNICODE

//----------------------------------------------------------------
// For short using
//

#define xASSERT				AdkASSERT

#define xTRACE				AdkTRACE
#define xTRACEA				AdkTRACEA
#define xTRACEW				AdkTRACEW
#define xTRACEExA			AdkTRACEExA
#define xTRACEExW			AdkTRACEExW

#define xWARNING			AdkWARNING
#define xWARNINGA			AdkWARNINGA
#define xWARNINGW			AdkWARNINGW
#define xWARNINGExA			AdkWARNINGExA
#define xWARNINGExW			AdkWARNINGExW

#define xERROR				AdkERROR
#define xERRORA				AdkERRORA
#define xERRORW				AdkERRORW
#define xERRORExA			AdkERRORExA
#define xERRORExW			AdkERRORExW

#define xPANIC				AdkPANIC
#define xPANICA				AdkPANICA
#define xPANICW				AdkPANICW
#define xPANICExA			AdkPANICExA
#define xPANICExW			AdkPANICExW

/**************************************************************
 *
 *				MessageBox Block:
 * 
 ***************************************************************/

#ifndef __KERNEL__

#ifdef _WIN32

#ifndef ADK_MSG_CAPTION
#define ADK_MSG_CAPTION				"提示"
#endif // ! ADK_MSG_CAPTION

#ifndef ADK_MSG_CAPTION_W
#define ADK_MSG_CAPTION_W			L"提示"
#endif // ! ADK_MSG_CAPTION_W

/**************************************************************
 * AdkMsgBoxA
 *
 */
__inline
INT AdkMsgBoxA(LPCSTR p_szFormat, ...)
{
	CHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	va_list args;
	HRESULT hResult;

	va_start(args, p_szFormat);
	hResult = StringCchVPrintfA(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	return MessageBoxA(NULL, szmsg, ADK_MSG_CAPTION, MB_OK | MB_ICONINFORMATION);
}

/**************************************************************
 * AdkMsgBoxW
 *
 */
__inline 
INT AdkMsgBoxW(LPCWSTR p_szFormat, ...)
{
	WCHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	va_list args;
	HRESULT hResult;

	va_start(args, p_szFormat);
	hResult = StringCchVPrintfW(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	return MessageBoxW(NULL, szmsg, ADK_MSG_CAPTION_W, MB_OK | MB_ICONINFORMATION);
}


/**************************************************************
 * AdkMsgBoxByWndA
 *
 */
__inline
INT AdkMsgBoxByWndA(HWND	hWnd, LPCSTR p_szFormat, ...)
{
	CHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	va_list args;
	HRESULT hResult;

	va_start(args, p_szFormat);
	hResult = StringCchVPrintfA(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	return MessageBoxA(hWnd, szmsg, ADK_MSG_CAPTION, MB_OK | MB_ICONINFORMATION);
}

/**************************************************************
 * AdkMsgBoxByWndW
 *
 */
__inline 
INT AdkMsgBoxByWndW(HWND	hWnd, LPCWSTR p_szFormat, ...)
{
	WCHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	va_list args;
	HRESULT hResult;

	va_start(args, p_szFormat);
	hResult = StringCchVPrintfW(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	return MessageBoxW(hWnd, szmsg, ADK_MSG_CAPTION_W, MB_OK | MB_ICONINFORMATION);
}

/**************************************************************
 * AdkMsgBoxExA
 *
 */
__inline
INT AdkMsgBoxExA(HWND		hWnd,
				 LPCSTR		lpCaption,
				 UINT		uType,
				 PCHAR		p_szFormat, ...)
{
	CHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	va_list args;
	HRESULT hResult;

	va_start(args, p_szFormat);
	hResult = StringCchVPrintfA(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	return MessageBoxA(hWnd, szmsg, lpCaption, uType);
}

/**************************************************************
 * AdkMsgBoxExW
 *
 */
__inline
INT AdkMsgBoxExW(HWND		hWnd,
				 LPCWSTR	lpCaption,
				 UINT		uType,
				 PWCHAR		p_szFormat, ...)
{
	WCHAR	szmsg[ADK_DBG_TRACE_BUFLEN];
	va_list args;
	HRESULT hResult;

	va_start(args, p_szFormat);
	hResult = StringCchVPrintfW(szmsg, sizeof(szmsg)/sizeof(szmsg[0]), p_szFormat, args);
	if ( STRSAFE_E_INSUFFICIENT_BUFFER == hResult )
	{
		AdkASSERT((!"STRSAFE_E_INSUFFICIENT_BUFFER"));
	}
	va_end(args);

	return MessageBoxW(hWnd, szmsg, lpCaption, uType);
}

#ifdef UNICODE
#define AdkMsgBox			AdkMsgBoxW
#define AdkMsgBoxEx			AdkMsgBoxExW
#define AdkMsgBoxByWnd		AdkMsgBoxByWndW
#else
#define AdkMsgBox			AdkMsgBoxA
#define AdkMsgBoxEx			AdkMsgBoxExA
#define AdkMsgBoxByWnd		AdkMsgBoxByWndA
#endif // !UNICODE

// For short using
//
#define xMsgBox				AdkMsgBox
#define xMsgBoxA			AdkMsgBoxA
#define xMsgBoxW			AdkMsgBoxW

#define xMsgBoxByWnd		AdkMsgBoxByWnd
#define xMsgBoxByWndA		AdkMsgBoxByWndA
#define xMsgBoxByWndW		AdkMsgBoxByWndW

#define xMsgBoxEx			AdkMsgBoxEx
#define xMsgBoxExA			AdkMsgBoxExA
#define xMsgBoxExW			AdkMsgBoxExW

#endif // _WIN32

#endif // ! __KERNEL__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __ADK_DEBUG_H__

/*
 * Revision:
 *
 *		9.[DZK] 将ADKMsgBoxXX的函数中的szmsg由动态分配，改为数组，这样就不需要使用AdkMalloc和AdkFree,以外相互嵌套	(0008-20100307)
 *
 *		8.[DZK] 发现ADKMsgBox的一个潜在错误，当目标窗口使用对话框时，传入的HANDLE为NULL，而不是父窗口的句柄
 *		这就导致并没有将父窗口消息中断，这里增加了函数AdkMsgBoxByWnd						(0007-20090516)
 *
 *		7.[DZK] 增加了MessageBox相关的几个函数		(0006-20090511)
 *
 *		6.[DZK] 测试并修订了无法使用的BUG (0005-20081003)
 *
 *		5. 针对复杂应用，增加自定义分类调试语句AdkXXXEx，用户可以按功能自由定义调试语句的类型,
 *		并通过将类型打开(ADK_DBG_ON)和关闭(ADK_DBG_OFF)来控制各类语句的显示与否		(0005-20081003)
 *
 *		4. 文件名改为AdkDebug.h，重构了部分内容，增加了Debug Level的支持	(0004-20081002)
 *				AdkTRACEA(W)
 *				AdkWARNINGA(W)
 *				AdkERRORA(W)
 *				AdkPANICA(W)
 *
 *		3. 对于AdkMsgBox，增加了ADK_MSG_CAPTION,这样调用程序可以在AdkPrecomp.h头文件前定义
 *		   自己的ADK_MSG_CAPTION											(0003-20080828)
 *
 *
 *		2. 增加一些简单的的调试语句输出函数(常用于Adk的头文件内联函数中)	(0002-20080221)
 *			策略：
 *				对于内核程序,直接输出DbgPrint
 *				对于控制台程序,直接输出print
 *				对于Windows程序,直接输出OutputDebugString
 *			函数：
 *				AdkTRACEA(W) -- 只在Debug情况下有作用
 *				AdkPANICA(W) -- 只在Debug情况下有作用
 *				AdkPRINTA(W) -- 全部起作用
 *
 *		1. base function extracted from AdkTrace.h (0001-20080126)
 *
 *****************************************************************************/