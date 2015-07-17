/*****************************************************************************/
/*                                                                           */
/* Include    kernel.h                                                       */
/*            function prototypes for all kernel functions                   */
/*                                                                           */
/*****************************************************************************/
/* Version    3.6                                                            */
/*            first with header and 188 support                              */
/*****************************************************************************/
/* History                                                                   */
/* 06/02/99   jr                                                             */
/*****************************************************************************/

#ifndef WORD
#include <style.h>
#endif

#ifndef _Cdecl
#include <macros.h>
#endif

/* * * Setup memory, from module sermem.c * * */
void pascal StoreCMOS(void);               /* store setup memory in eeprom */
pascal EE_Write(BYTE *, WORD , WORD ); /* write block to eeprom */
pascal EE_Read(BYTE *buf, WORD adr, WORD len);  /* read block to eeprom */

/* helper functions for I/O and mem access */
WORD InWord(WORD);
void OutWord(WORD,WORD);

/* * * Multitasking functions */
#define nice (*((void(far*_ss*)(void))(0x24*4)))
#define PROXYSTACK 64
void pascal spawn(void (*start)(),void *newtcb,int size,int Chan,char *Name);
void reset(void);
void sdelay(WORD);
void error(WORD);
void *kalloc(WORD);             /* memory allocation in kernel space */
void far *pnorm(void far *);    /* normalize pointer, depends on 20/24bit */

/* * * LED Functions * * */
void pascal BlinkReset(void);
void pascal BlinkSet(void);
void Blinker(void);

/* * * Timer functions * * */
WORD get_trand(void);           /* get timer random value, used for random seed */
DWORD MsGet(void);              /* get actual ms (seconds fractions) */
extern DWORD ticks;
extern DWORD time;
#define sticks ((WORD)ticks)
#define stime ((WORD)time)
DWORD get_ticks();		/* use this to access the ticks */
DWORD get_time();		/* and this to access the time */

/* Monitor and Debug Functions */
nmon(unsigned int);                            /* maintenance monitor, parameter */
                                               /* is actually a char but better */
                                               /* defined as an unsigned int */
void Monitor(void);                            /* debug monitor */

WORD pascal atoi(char *);
long pascal atol(char *); /*ak Declaration of the new kernel function "atoll" (converting string to (un)signed long). */
WORD pascal atoh(char *);
BYTE pascal a2toh(char *);
DWORD pascal longdiv(DWORD,WORD);
DWORD pascal lmul(DWORD,WORD);
WORD pascal lmod(DWORD,WORD);

extern WORD BlinkGWord[];                      /* defined in blink.c */
extern WORD BlinkRWord;                        /* defined in blink.c */

void far *pnorm(void far *);
void FarJump(void far *);                      /* jumps to pointer par. */
WORD CheckSum(WORD);                           /* calculate checksum over */
                                               /* loaded or flash image */
int pascal gethxrec(int *len,WORD max,BYTE far *buf); /* get hex rec from stdin, return */
                                               /* type. max. in len, return act */
int gfware_hex(void);                          /* get firmware from serial port */
                                               /* load in buffer at 2nd 64k ram */
#define HTTP_PORT "HT" 
#define SMTP_PORT "SM" 
void SetServicePort(WORD *Name, WORD portn);	/* configure port numbers */