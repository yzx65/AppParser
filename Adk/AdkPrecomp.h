/****************************************************************
 * Module:								(BuildNum: 0004-20081003)
 *      AdkPrecomp.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Note:
 *		包含各种所需的必要头文件
 *
 */

#pragma once

#ifndef __ADK_PRECOMP_H__
#define __ADK_PRECOMP_H__

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

// Support OS Upper Win2k (include Win2k)
//
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif 

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // ! WIN32_LEAN_AND_MEAN

#ifdef __KERNEL__

#ifdef _WIN32		// Windows Kernel

#include <wdm.h>
#include <ntddk.h>
#include <ntdef.h>
#include <ndis.h>
#include <windef.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

#else				// Linux kernel

#include <linux/config.h>
#include <linux/module.h>
#include <linux/version.h>

#include <linux/byteorder/generic.h>
#include <linux/netdevice.h>
#include <linux/net.h>
#include <net/sock.h>
#include <net/protocol.h>
#include <net/pkt_sched.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/skbuff.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/locks.h>
#include <linux/smp_lock.h>
#include <asm/string.h>
#include <linux/string.h>

#endif // !_WIN32

#else			// Application

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <process.h>

#ifdef _WIN32				// Windows application

#include <windows.h>
#include <winioctl.h>
#include <wincrypt.h>

//#if _WIN32_WINNT < 0x0600			// Vista和WIN7 下不需要包含Winternl.h
//#include <Winternl.h>
//#endif 

#else			// linux application

#include <unistd.h>

#include <sys/ioctl.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/socket.h>

#endif // !_WIN32

#endif // !__KERNEL__

//
// Base Adk Header
//

#include "AdkDataType.h"
#include "AdkDebug.h"
#include "AdkMemory.h"
#include "AdkString.h"

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ! __ADK_PRECOMP_H__

/*
 * Revision:
 *
 *		4. 简单重构，去掉各种ADK的附加头文件		(BuildNum: 0004-20081003)
 *
 *		3. 增加包含AdkNtDllHelper.h					(BuildNum: 0003-20080305)
 *
 *		2. 增加Prototype 头文件和_WIN32_WINNT宏定义	(BuildNum: 0002-20080304)
 *
 *		1. Wrapper _precomp.h						(BuildNum: 0001-20080227)
 *
 *****************************************************************************/
