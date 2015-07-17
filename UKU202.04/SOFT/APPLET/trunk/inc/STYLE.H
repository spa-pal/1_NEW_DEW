#ifndef BYTE

#define LOCAL static
#define GLOBAL
#define IMPORT extern
#define BOOL unsigned char
#define TRUE 1
#define FALSE 0

#define BYTE  unsigned char
#define WORD  unsigned short
#define DWORD unsigned long
#define UINT4 unsigned long
#define NULL (BYTE *)0
#endif

#ifndef PTF
typedef void (*PTF)();
#endif

