#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_GLOBAL 0

#define DEBUG_NMI         (DEBUG_GLOBAL && 0)
#define DEBUG_LA          (DEBUG_GLOBAL && 0)
#define DEBUG_TRACE_LA    (DEBUG_GLOBAL && 0)
#define DEBUG_TRACE_INT   (DEBUG_GLOBAL && 0)
#define DEBUG_TRACE_SER   (DEBUG_GLOBAL && 0)
#define DEBUG_HEXDUMP     (DEBUG_GLOBAL && 0)


#define DEBUG_FWARE       (DEBUG_GLOBAL && 0)
#define DEBUG_HWARE       (DEBUG_GLOBAL && 0)
#define DEBUG_EAPOL       (DEBUG_GLOBAL && 0)
#define DEBUG_SUPPLICANT  (DEBUG_GLOBAL && 0)
#define DEBUG_MARVELL     (DEBUG_GLOBAL && 0)
#define DEBUG_WPA         (DEBUG_GLOBAL && 0)
#define DEBUG_IPROC       (DEBUG_GLOBAL && 0)
#define DEBUG_HSII        (DEBUG_GLOBAL && 0)
#define DEBUG_STARTUP     (DEBUG_GLOBAL && 0)
#define DEBUG_WEBSETUP    (DEBUG_GLOBAL && 0)
#define DEBUG_TFTP        (DEBUG_GLOBAL && 0)
#define DEBUG_MAPPING     (DEBUG_GLOBAL && 0)
#define DEBUG_MAIN        (DEBUG_GLOBAL && 0)
#define DEBUG_NETDRV      (DEBUG_GLOBAL && 0)
#define DEBUG_MBUF        (DEBUG_GLOBAL && 0)
#define DEBUG_WEB         (DEBUG_GLOBAL && 0)
#define DEBUG_CIPHER      (DEBUG_GLOBAL && 0)
#define DEBUG_STACK       (DEBUG_GLOBAL && 0)
#define DEBUG_TCP         (DEBUG_GLOBAL && 0)
#define DEBUG_DHCP        (DEBUG_GLOBAL && 0)
#define DEBUG_TEST        (DEBUG_GLOBAL && 0)


#if   DEBUG_TRACE_LA  || DEBUG_TRACE_INT || DEBUG_TRACE_SER
void debug_trace(BYTE stage, WORD value);
#define DEBUG_TRACE(stage, value)  debug_trace(stage, (WORD)(value));
#else
#define DEBUG_TRACE(stage, value) 
#endif


#if DEBUG_NMI
void debug_init(void);
#define DEBUG_INIT   debug_init();
#else
#define DEBUG_INIT
#endif

#if   DEBUG_TRACE_INT  || DEBUG_NMI
void debug_dump(void);
#define DEBUG_DUMP  debug_dump();
#else
#define DEBUG_DUMP
#endif


#if DEBUG_HEXDUMP
void hexdump(const char *title, const BYTE *buf, WORD len);
#else
#define hexdump(a,b,c);
#endif


#endif /* DEBUG_H */