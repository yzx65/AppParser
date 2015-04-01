/****************************************************************
 * Module:
 *      AdkSocket.h
 *
 * Author:
 *		
 *
 * Note:
 *		与socket相关的一些函数
 *
 * Functions:
 *
 *			1. 基本的socket通信，当前内容较长，待逐步完善
 *				AdkConnectTo()             连接到指定IP和端口，同步模式，超时为默认值
 *              AdkRecvTcpMessage()        从一个连接上接收数据，同步模式，超时由用户设置
 *
 *		
 *          2. HTTP
 *				AdkGetResHeaderFromHost    发送一个请求到指定的网站，获取响应头信息
 *              AdkQueryDateInResHeaders   从HTTP的响应头信息中获取日期信息
 */

#ifndef __ADK_SOCKET_H__
#define __ADK_SOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "AdkPrecomp.h"

#ifdef _WIN32

#include <Winsock.h>
#pragma comment(lib, "ws2_32.lib")

#else

#endif

/* ****************************************************************************
 *
 * AdkConnectTo
 *
 */
INLINE
int AdkConnectTo(unsigned long ipAddr, unsigned short nPort)
{
	struct sockaddr_in saddr;
	int                fd   = -1;

	AdkZeroMemory(&saddr, sizeof saddr);
	
	saddr.sin_port        = htons(nPort);
	saddr.sin_addr.s_addr = ipAddr;
	saddr.sin_family      = AF_INET;

	do
	{
		fd	= socket(AF_INET, SOCK_STREAM, 0);

		if ( 0 >= fd )
		{
			break;
		}

		if ( 0 > connect(fd, (struct sockaddr*)&saddr, sizeof(saddr)) )
		{
#ifdef _WIN32

			closesocket(fd);
#else
			close(fd);
#endif
			break;
		}

	} while (FALSE);

	return fd;
}


/* ****************************************************************************
 *
 * AdkRecvTcpMessage
 *
 */
INLINE
int AdkRecvTcpMessage(int fd, char *p_szBuf, int iBuf, long timeout)
{
	fd_set             wfds ;
	struct timeval     tv[1];

	FD_ZERO(&wfds);
	FD_SET(fd, &wfds);

	tv->tv_sec	= timeout;
	tv->tv_usec = 0;

	if ( 0 >= select(fd+1, &wfds, NULL, NULL, tv) )
	{
		return -1;
	}

	return recv(fd, p_szBuf, iBuf, 0);
}


/**************************************************************
 * AdkGetResHeaderFromHost
 *
 * 发送一个请求到指定的网站，获取响应头信息。
 *
 * 输入HOST的长度不大于64，或大于64，则返回NULL。
 * 返回值若不为NULL，则需要调用者使用free来释放内存
 *
 */
INLINE
PCHAR AdkGetResHeaderFromHost(PCHAR lpszHost)
{
#define MAX_HEADER_LEN  4096

	PCHAR  lpszRet = NULL;
	PCHAR  lpszEnd;
	CHAR   szSendBuf[512];
	CHAR   szRecvBuf[MAX_HEADER_LEN];
	int    iRecv;
	int    iSend;
	int    iSendLen;
	struct hostent *hptr;
	struct sockaddr_in addr;
	int    fd;

	// Host长度不大于64，防止栈溢出
	//
	if ( strlen(lpszHost) > 64 )
	{
		return lpszRet;
	}

	WSADATA wsaData;
	WSAStartup(0x0202,&wsaData);

	// 构造发送数据
	//
	strcpy_s(szSendBuf, sizeof(szSendBuf), "GET / HTTP/1.1\r\n");
	strcat_s(szSendBuf, sizeof(szSendBuf), "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, */*\r\n");
	strcat_s(szSendBuf, sizeof(szSendBuf), "Accept-Language: zh-en\r\n");
	strcat_s(szSendBuf, sizeof(szSendBuf), "Accept-Encoding: gzip, deflate\r\n");
	strcat_s(szSendBuf, sizeof(szSendBuf), "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\r\n");
	strcat_s(szSendBuf, sizeof(szSendBuf), "Host: ");
	strcat_s(szSendBuf, sizeof(szSendBuf), lpszHost);
	strcat_s(szSendBuf, sizeof(szSendBuf), "\r\n");
	strcat_s(szSendBuf, sizeof(szSendBuf), "Connection: Keep-Alive\r\n\r\n");

	do
	{
		// 获取IP地址
		//
		hptr = gethostbyname(lpszHost);
		if ( !hptr )
		{
			break;
		}
		addr.sin_addr = *(struct in_addr*)hptr->h_addr;

		// 连接到服务器
		//
		fd = AdkConnectTo(addr.sin_addr.s_addr, 80);
		if ( 0 > fd )
		{
			break;
		}

		// 发送请求
		// 此处假设一次发送成功所有数据，若未成功，则返回失败。
		// TODO:
		//
		iSendLen = strlen(szSendBuf);
		iSend = send(fd, szSendBuf, iSendLen, 0);
		if ( iSend != iSendLen )
		{
			break;
		}

		// 获取响应信息
		// 此处假设最大的响应头为MAX_HEADER_LEN字节。
		// TODO:
		//
		iRecv = AdkRecvTcpMessage(fd, (PCHAR)&szRecvBuf[0], MAX_HEADER_LEN, 10);
		if ( 0 >= iRecv )
		{
			break;
		}
		lpszEnd = strstr(szRecvBuf, "\r\n\r\n");
		if ( !lpszEnd )
		{
			break;
		}
		*lpszEnd = '\0';

		lpszRet = _strdup(szRecvBuf);

	} while (FALSE);

	return lpszRet;
}


/**************************************************************
 * AdkQueryDateInResHeaders
 *
 * 从HTTP的响应头信息中获取日期信息。
 *
 *
 */
INLINE
PCHAR AdkQueryDateInResHeaders(PCHAR lpszHeaders)
{
	PCHAR  lpszRet  = NULL; 
	PCHAR  lpszDate = NULL;
	PCHAR  lpszEnd;
	
	do
	{
		// 查找其中的时间信息
		//
		lpszDate = strstr(lpszHeaders, "\r\nDate:");
		if ( !lpszDate )
		{
			break;
		}
		lpszDate += 2;
		lpszEnd = strstr(lpszDate, "\r\n");
		if ( !lpszEnd || (lpszEnd - lpszDate > 64) )
		{
			break;
		}
		*lpszEnd = '\0';

		lpszRet = _strdup(lpszDate);

	} while (FALSE);

	return lpszRet;
}



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ! __ADK_SOCKET_H__