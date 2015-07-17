#ifndef BYTE
#include "..\inc\style.h"
#endif

#if 0
#ifndef VERS
#include "..\kernel\hardware.h"
#endif
#endif

#include <CCBDEF.H>
#include <TCBDEF.H>

#ifdef DEF_VARS /* set in MAIN */
#define NCMAX 2
  GLOBAL BYTE Nchan;    /* #channels for that node */
  GLOBAL DWORD ti_msecs;         /* seconds fraction 0..65535 */
  GLOBAL WORD  ti_secs;         /* seconds for timing */
  GLOBAL WORD ti_pps;
  GLOBAL WORD WatchCnt;
  GLOBAL char rdate[] = __DATE__;
  GLOBAL CCB  AllCCB[NCMAX];
  GLOBAL CCB  *ActCCB;
  GLOBAL TCB  *ActPro;
  GLOBAL BYTE InitFlg;
  GLOBAL void *SendAdr=0, *RecPakAnf, *RecPakEnd;
  GLOBAL BYTE Startup = 0xff;
  GLOBAL BYTE c_serie = 0;
  GLOBAL WORD IdleCount;
  GLOBAL BYTE Setup[120+2+126]; /* Standard Setup + len of enhanced setup + enhanced Setup */
  extern BYTE LatchVal,LatchV01;
  extern DWORD time;
  extern DWORD ticks;
  extern BYTE Disable_Mon;
  GLOBAL WORD http_port_num = 80;
  GLOBAL WORD smtp_port_num = 25;
  GLOBAL SPORT SPStatus;			/* Serial Port status; chuck */
#else
  extern BYTE Nchan;
  extern DWORD ticks;
  extern DWORD time;
  extern WORD BlinkRWord;
  extern WORD BlinkGWord[];
  extern BYTE LatchVal,LatchV01;
  extern WORD WatchCnt;
  extern char rdate[];
  extern CCB  AllCCB[];
  extern CCB  *ActCCB;
  extern TCB  *ActPro;
  extern BYTE InitFlg;
  extern void *SendAdr, *RecPakAnf, *RecPakEnd;
  extern BYTE ChanTbl[];
  extern BYTE Startup;
  extern BYTE c_serie;
  extern WORD IdleCount;
  extern BYTE Setup[];
  extern BYTE Disable_Mon;	// defined in kernel\startup.c
  extern WORD http_port_num;
  extern WORD smtp_port_num;
  extern SPORT SPStatus;			/* Serial Port status; chuck */
#endif

extern DWORD get_ticks();
extern DWORD get_time();

