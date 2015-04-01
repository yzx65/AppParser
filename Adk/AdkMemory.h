/********************************************************************
 * Module:									(BuildNum:0012-2011111)
 *       AdkMemory.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		提供基本的内存访问函数
 *
 *			AdkMalloc				-- (分配后会自动对内存区域清0)
 *			AdkFree
 *
 *			AdkZeroMemory
 *			AdkFillMemory
 *			AdkCopyMemory
 *			AdkMoveMemory
 * 			AdkXorMemory			-- 内存和某个值进行异或
 *			AdkXorMemoryEx			-- 两段内存之间进行异或
 *			AdkCompareMemory		-- 比较内存
 *			AdkMemoryFind			-- 内存查找
 *
 */

#ifndef __ADK_TUOJIE_MEMORY_H__
#define __ADK_TUOJIE_MEMORY_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

//
// 文件分配的前缀和后缀
//

#define ADK_MEM_PREFIX                 0x12345678
#define ADK_MEM_POSTFIX                0x87654321

//----------------------------------------------------------------
// 内存分配释放函数 Memory Allocate And Free Function
//
//

#ifdef _DEBUG

#ifdef __KERNEL__

/**************************************************************
 * AdkMalloc
 * 
 */
__inline 
PVOID NTAPI AdkMalloc(IN POOL_TYPE	PoolType,
					  IN ULONG		Size)
{
	PBYTE Ptr = NULL;

	if (Size == 0)
	{
		return NULL;
	}

	xASSERT(((1024*1024*256) > Size && Size));

	Ptr  = (PBYTE)ExAllocatePool(PoolType,(SIZE_T)(Size + 12));
	if (Ptr)
	{
		RtlZeroMemory(Ptr, (SIZE_T)(Size + 12));

		*(ULONG*)&Ptr[0]        = Size;
		*(ULONG*)&Ptr[4]        = ADK_MEM_PREFIX;
		*(ULONG*)&Ptr[Size + 8]	= ADK_MEM_POSTFIX;

		Ptr += 8;
	}

	return Ptr;
}

/**************************************************************
 * AdkFree
 * 
 */
__inline 
VOID NTAPI AdkFree(PVOID Ptr)
{
	PBYTE aPtr = (PBYTE)Ptr;

	AdkASSERT(Ptr);

	AdkASSERT(ADK_MEM_PREFIX  == *(ULONG*)&aPtr[-4]);
	AdkASSERT(ADK_MEM_POSTFIX == *(ULONG*)&aPtr[*(ULONG*)&aPtr[-8]]);

	aPtr -= 8;
	Ptr   = aPtr;

	ExFreePool(Ptr);

	return ;
}

#else	// USER

/**************************************************************
 * AdkMalloc:
 * 
 */
__inline 
PVOID WINAPI AdkMalloc(IN ULONG	 Size)
{
	PBYTE Ptr = NULL;

	if (Size == 0)
	{
		return NULL;
	}

	AdkASSERT(((1024*1024*256) > Size && Size));

	Ptr = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY , (SIZE_T)(Size + 12));
	if (Ptr)
	{
		*(ULONG*)&Ptr[4]           = ADK_MEM_PREFIX;
		*(ULONG*)&Ptr[0]           = Size;
		*(ULONG*)&Ptr[Size + 8] = ADK_MEM_POSTFIX;

		Ptr += 8;
	}

	return Ptr;
}

/**************************************************************
 * AdkFree:
 * 
 */
__inline
VOID WINAPI AdkFree(PVOID Ptr)
{
	PBYTE aPtr = (PBYTE)Ptr;

	AdkASSERT(NULL != Ptr);

	AdkASSERT(ADK_MEM_PREFIX  == *(ULONG*)&aPtr[-4]);

	if (ADK_MEM_POSTFIX != *(ULONG*)&aPtr[*(ULONG*)&aPtr[-8]])
	{
		aPtr = (PBYTE)Ptr;
	}

	AdkASSERT(ADK_MEM_POSTFIX == *(ULONG*)&aPtr[*(ULONG*)&aPtr[-8]]);

	aPtr -= 8;
	Ptr   = aPtr;	

	HeapFree(GetProcessHeap(), 0, Ptr);

	return ;
}

#endif // !__KERNEL__

#else	// RELEASE

#ifdef __KERNEL__

/**************************************************************
 * AdkMalloc - 为了和DEBUG版本的AdkMalloc行为相一致，这里需要进行清0
 * 
 */
__inline 
PVOID NTAPI AdkMalloc(IN POOL_TYPE	PoolType,  IN ULONG		Size)
{
	PBYTE Ptr = (PBYTE)ExAllocatePool(PoolType,(SIZE_T)(Size ));

	if (Ptr)
	{
		RtlZeroMemory(Ptr, (SIZE_T)(Size));
	}

	return Ptr;
}

#define AdkFree(__PTR__)						ExFreePool((__PTR__))

#else // _WIN32_

#define AdkMalloc(__HOWMUCH__)					(PVOID)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY ,(SIZE_T)(__HOWMUCH__));
#define AdkFree(__PTR__)						HeapFree(GetProcessHeap(), 0, __PTR__)

#endif // !__KERNEL__

#endif // !_DEBUG

//----------------------------------------------------------------
// 内存操作函数 Memory Operation Function
//

/**************************************************************
 * AdkFillMemory
 *
 */
INLINE
VOID AdkFillMemory(PVOID	lpBuffer,
				   int		nCount,
				   BYTE		Fill)
{
	PBYTE lpPos = (PBYTE)lpBuffer;

	xASSERT((lpBuffer));

	while (nCount--) 
	{
		*lpPos++ = Fill;	
	}

	return;
}

/**************************************************************
 * AdkZeroMemory
 *
 */
INLINE
VOID AdkZeroMemory(PVOID lpBuffer, int nCount)
{
	xASSERT((lpBuffer));

	AdkFillMemory(lpBuffer, nCount, 0);
}

/**************************************************************
 * AdkCopyMemory
 *
 */
INLINE
VOID AdkCopyMemory(PVOID		lpDest,
				   const PVOID	lpSrc,
				   int			nCount)
{
	PBYTE lpbyDest = (PBYTE)lpDest;
	PBYTE lpbySrc = (PBYTE)lpSrc;

	xASSERT((lpDest));
	xASSERT((lpSrc));

    // copy from lower addresses to higher addresses
    //
    while (nCount--) 
	{
		*lpbyDest++ = *lpbySrc++;
	}

	return;
}

/**************************************************************
 * AdkMoveMemory
 *
 */
INLINE
VOID AdkMoveMemory(PVOID		lpDest,
				   const PVOID	lpSrc,
				   int			nCount)
{
	PBYTE lpbyDest = (PBYTE)lpDest;
	PBYTE lpbySrc = (PBYTE)lpSrc;

	xASSERT((lpDest));
	xASSERT((lpSrc));

	if (lpbyDest <= lpbySrc || lpbyDest >= (lpbySrc + nCount)) 
	{
		//
		// Non-Overlapping Buffers
		// copy from lower addresses to higher addresses
		//
		while (nCount--) 
		{
			*lpbyDest++ = *lpbySrc++;
		}
	}
	else 
	{
		//
		// Overlapping Buffers
		// copy from higher addresses to lower addresses
		//
		lpbyDest = lpbyDest + nCount - 1;
		lpbySrc = lpbySrc + nCount - 1;

		while (nCount--) 
		{
			*lpbyDest-- = *lpbySrc--;
		}
	}
}

/**************************************************************
 * AdkXorMemory
 *
 */
INLINE
VOID AdkXorMemory(PVOID lpBuf, const BYTE byMask, int nCount)
{
	PBYTE lpbyBuf = (PBYTE)lpBuf;
	int i;
	for (i = 0; i < nCount; i++) 
	{
		lpbyBuf[i] ^= byMask;
	}
}

/**************************************************************
 * AdkXorMemoryEx
 *
 */
INLINE
VOID AdkXorMemoryEx(PVOID lpBuf, const PBYTE lpMask, int nCount)
{
	PBYTE lpbyBuf = (PBYTE)lpBuf;
	int i;

	for (i = 0; i < nCount; i++) 
	{
		lpbyBuf[i] ^= lpMask[i];
	}
}

/*********************************************************************
 * AdkCompareMemory
 *
 */
INLINE
int AdkCompareMemory(const PVOID lpBuf1,
					 const PVOID lpBuf2,
					 int		 nCount)
{
	PBYTE lpbyBuf1 = (PBYTE)lpBuf1;
	PBYTE lpbyBuf2 = (PBYTE)lpBuf2;

	if (nCount == 0)
	{
		return(0);
	}

	while ( --nCount && *lpbyBuf1 == *lpbyBuf2 ) 
	{
		lpbyBuf1++;
		lpbyBuf2++;
	}

	return ( *((unsigned char *)lpbyBuf1) - *((unsigned char *)lpbyBuf2) );
}

/*********************************************************************
 * AdkMemoryFind
 *
 *	返回值是第一个找到内存块的偏移值，-1说明没有找到
 *	
 *
 */
INLINE
int AdkMemoryFind(const char *mem,	 
				  const char *str, 
				  int		 sizem,		// 内存空间的长度
				  int		 sizes)		// 查找的匹配内存块长度,为0,返回失败
{   
	int  i,j; 

	if (sizes == 0) 
	{
		return -1;
	}

	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < sizes; j ++)
		{
			if (mem[i+j] != str[j])	
			{
				break;
			}

			if (j + 1 == sizes) 
			{
				return i;
			}
		}
	} 

	return -1;
}

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // ! __ADK_TUOJIE_MEMORY_H__

/*
 * Revision:
 *
 *		11. 由于RtlZeroMemory等Rtl开关的函数还是依赖于C库，故重新实现了AdkZeroMemory等函数			(BuildNum:0012-2011111)
 *				AdkZeroMemory / AdkFillMemory / AdkCopyMemory / AdkMoveMemory
 *			去掉了AdkSecureZeroMemory
 *
 *		10. 更正了AdkMemoryFind的一个BUG，if (j == sizes) 改为if (j + 1 == sizes)					(BuildNum:0011-20110919)
 *
 *		9. 增加了AdkMemoryFind,以便于在给定的内存空间中查找一个给定的内存块，对于报文/协议分析(可能包含0)的效果特别好		(BuildNum:0010-20110825)
 *
 *		8. AdkMalloc函数中没有对分配长度是否为0进行检查				(BuildNum:0009-20110630)
 *
 *		7. 增加了AdkCompareMemory函数								(BuildNum:0008-20100917)
 *
 *		6. 重构了AdkXorMemory, 增加了AdkXorMemoryEx					(BuildNum:0007-20100524)
 *
 *		5. 简单重构，并增加AdkFillMemory							(BuildNum:0006-20081003)
 *
 *		4. 增加常用内存拷贝等函数的统一ADK形式
 *		   增加AdkXorMemory，可以异或一段内存空间					(BuildNum:0005-20080707)
 *
 *		3. 发现一个潜在的错误,在KERNEL情况下Debug版和Release版有一个明显的区别, Debug版会将内存区清0, 而Release版则不会
 *			这会以上层用户造成为认知问题,现将其统一为清0			(BuildNum:0004-20080105)
 *
 *		2. Remove AdkGetModuleBase and AdkGetKernelProcAddress, 
 *		   Keep adkmemory to simplest 
 *																	(BuildNum:0003-20070729)
 *
 *		1. Found a potential bug, In kernel mode, debug AdkMalloc zero memory, but realse AdkMalloc
 *			don't zero memory. So we see AdkMalloc as ExAllocatePool, and should call RtlZeroMemory after AdkMalloc. 
 *
 *
 ******************************************************************************************************************/
