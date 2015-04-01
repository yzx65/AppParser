/***********************************************************************************
 * Module:												(BuildNum:0001-20080603)
 *       AdkCommDataType.h
 *
 * Author:
 *		DING ZHAOKUN(dzkad@hotmail.com)
 *
 * Notes:
 *		定义常用数据类型
 *
 */

#ifndef __ADK_TUOJIE_DATATYPE_H__
#define __ADK_TUOJIE_DATATYPE_H__

#ifdef __cplusplus

#define INLINE              inline

#else // !__cplusplus

#ifdef _WIN32
#define INLINE              __inline
#else
#define INLINE			    inline
#endif // ! _WIN32

#endif // ! __cplusplus


#ifndef PUBLIC
#define PUBLIC
#endif  // ! PUBLIC

#ifndef PRIVATE
#define PRIVATE               static
#endif  // ! PRIVATE

#ifndef LOCAL
#define LOCAL                 static
#endif  // ! LOCAL

#ifndef CONST
#define CONST                 const
#endif  // ! CONST

#ifndef FALSE
#define FALSE               0
#endif  // ! FALSE

#ifndef TRUE
#define TRUE                1
#endif	// ! TRUE

#ifndef IN
#define IN
#endif	// ! IN

#ifndef OUT
#define OUT
#endif	// ! OUT

#ifndef OPTIONAL
#define OPTIONAL
#endif	// ! OPTIONAL

#ifndef _WIN32

typedef char            CHAR;

typedef unsigned char   BYTE;
typedef unsigned char   *LPBYTE;
typedef unsigned char   *PBYTE;

typedef unsigned char   UCHAR;
typedef unsigned char   *LPUCHAR;
typedef unsigned char   *PUCHAR;

typedef BYTE             BOOLEAN;
typedef BYTE            *LPBOOLEAN;
typedef BYTE            *PBOOLEAN;

typedef short           SHORT;
typedef short           *LPSHORT;
typedef short           *PSHORT;

typedef unsigned short  USHORT;
typedef unsigned short  *LPUSHORT;
typedef unsigned short  *PUSHORT;

typedef unsigned short   WORD;
typedef unsigned short   *LPWORD;
typedef unsigned short   *LWORD;

typedef int              INT;
typedef int             *LPINT;
typedef int             *PINT;

typedef int              BOOL;
typedef int              *LPBOOL;
typedef int              *PBOOL;

typedef unsigned int     UINT;
typedef unsigned int     *LPUINT;
typedef unsigned int     *PUINT;

typedef unsigned int     SIZE_T,*PSIZE_T,*LPSIZE_T;

typedef long             LONG;
typedef long             *LPLONG;
typedef long             *PLONG;

typedef unsigned long    ULONG;
typedef unsigned long    *LPULONG;
typedef unsigned long    *PULONG;

typedef unsigned long    DWORD;
typedef unsigned long    *LPDWORD;
typedef unsigned long    *PDWORD;

typedef void             *LPVOID;
typedef void             *PVOID;

typedef int              INT_PTR,*PINT_PTR,*LPINT_PTR;
typedef long             LONG_PTR,*PLONG_PTR,*LPLONG_PTR;

typedef unsigned int     UINT_PTR,*PUINT_PTR,*LPUINT_PTR;
typedef unsigned long    ULONG_PTR,*PULONG_PTR,*LPULONG_PTR;

typedef ULONG_PTR        DWORD_PTR;
typedef PULONG_PTR       PDWORD_PTR;
typedef LPULONG_PTR      LPDWORD_PTR;

#endif  // !_WIN32

#define _LONGLONG		__int64
#define _ULONGLONG		unsigned __int64

typedef _LONGLONG		_Longlong;
typedef _ULONGLONG		_ULonglong;

#define _STOINT_SIGNED		0x1
#define _STOINT_LLONG		0x2

#ifndef LLONG_MAX
#define LLONG_MAX     0x7fffffffffffffff  /*maximum signed __int64 value */
#endif // LLONG_MAX

#ifndef LLONG_MIN
#define LLONG_MIN     0x8000000000000000  /*minimum signed __int64 value */
#endif //LLONG_MIN

#ifndef ULLONG_MAX
#define ULLONG_MAX    0xffffffffffffffff  /*maximum unsigned __int64 value */
#endif // ULLONG_MAX

#endif // ! __ADK_TUOJIE_DATATYPE_H__

 /*
 * Revision:
 *
 *		1. 随着64位系统的出现，专门增加一个数据类型的头文件来统一处理数据类型问题
 *			从_precomp.h中移动相应的内容					(0001-20080603)
 *
 *****************************************************************************/