/*****************************************************************************/
/* 05.04.01 jl added keepalive timer in TCP struct, preset to previous       */
/*          hardcoded value 45000ms                                          */
/*****************************************************************************/

#define DEFAULT_MTU   1400

#define CLOSED		0
#define LISTEN		1
#define ESTABLISHED	2
#define SYN_SENT	3
#define SYN_RCVED	4
#define FIN_WAIT_1	5
#define FIN_WAIT_2	6
#define FIN_WAIT_3  7
#define CLOSING		8
#define LAST_ACK	9
#define TIME_WAIT	10
#define DRAIN           11              /* like closed, but actively clear input */

typedef struct TCP {
  WORD Port;			/* TCP Port number */
  WORD State;			/* TCP State */
  WORD Rtry,Tout;		/* timeout and retry for states */
  WORD Qsnd;                    /* time when quitt is due -250ms */
  WORD Chnr;                    /* I/O Channel Number (-xx for app) */
  WORD RcvFifo;			/* Fifo Pointer - for Rcv Data */
  WORD XmitFifo;		/* Fifo Pointer - for Xmit Data */
  WORD Opts;			/* TCPIP Options - pack algorithm etc */
#define PACK 1          /* smart packing */
#define CTLDDIS 2       /* ctrl D does disconnect */
#define CLNOTLIS 4      /* closing connection does close not listen */
#define IGNNEWRQ 8      /* do not send reset if conn. busy but let hang */
#define STREAMRTY 16	/* send frequent window update messages to allow for */
			/* full throughput with some block loss */

  struct {			/* Address struct of partner */
    WORD Port;
    BYTE Ip[4];
  } a;

  struct {			/* Receiver struct */
    DWORD Ini,Nxt;
    WORD  Wnd;
    int   (*RcvCall)(struct TCP *, BYTE near *, WORD);
    int   (*StCall)(struct TCP *, ...);
  } r;

  struct {			/* Sender struct */
    DWORD Ini,Nxt,Una;
    WORD Wnd;			/* rcvrs' last window announcement */
    WORD SPos,SLen;             /* start and length */
    BYTE _seg *SBuf;            /* buffer pointer */
    WORD BufMask;               /* 58 buffer size - 1 */
    BYTE BufMethod;             /* 60 Buffering Method */
                                /*    bit 0 : Optimised move from FIFO */
                                /*    bit 1 : Direct, without FIFO */
    BYTE sflg;                  /* 61 'new' flag */
    WORD stout;                 /* 62 send timeout for slow pack alg.*/
    BYTE PAbits;                /* 64 Packing algorithm control */
                                /*    bit 0,1 define waiting time */
                                /*    bit 2,3 define chars to follow sendchar */
#define PA_SEQ  16              /*    bit 4 defines if sendchars interp. in seq */
#define PA_HACK 32              /*    hard send after sequence ! */
#define PA_ALT  128             /*    defines if alt packing enabled */
    BYTE PAstate;               /* 65 packing state */
#define PAS_STD 0               /*    standard, scanning for tout/sendchar */
#define PAS_SND 1               /*    check for 2nd char if sequence */
#define PAS_CNT 2
#define PAS_SW1 3               /*    wait for one more chars */
#define PAS_SW2 4               /*    .. two .. */
#define PAS_SW3 5               /*    .. three .. */
    WORD st;                    /* 66 send timer for retries */
  } s;
  WORD TelBits;                 /* 68 ehem. TelEcho */
#define TELB_AE 1               /*    Bit 0: applikation macht echo (angerufen) */
#define TELB_WES 2              /*    Bit 1: Will echo gesendet */
#define TELB_WEA 4              /* Bit 2: Do echo empfangen */
#define TELB_LE 8               /* Bit 3: lokales echo (anrufer) */
#define TELB_LGA 16             /* Bit 4: 1-i supress go-ahead */
#define TELB_RGA 32             /* Bit 5: der andere supresst go ahead */
#define TELB_UNI 64             /* Bit 6: only std cr - for setup */
#define TELB_TEL 128            /* Bit 7: Telnet aktiv */

#define TELB_LBIN 0x100          /* Bit 8: Binary mode */
#define TELB_RBIN 0x200          /* Bit 9: Binary mode */
#define TELB_LEOR 0x400          /* Bit 10: End-of-Record mode */
#define TELB_REOR 0x800          /* Bit 11: End-of-Record mode */
#define TELB_PHYS 0x1000         /* Bit 12: physical interface ! */
#define TELB_XDIS 0x2000         /* Bit 13: do not send chars,485 echo suppr.*/
#define TELB_DDIS 0x4000         /* Bit 14: check for ^D to disconnect */
#define TELB_REDIR 0x8000       /* Bit 15: LTX redirector */

  int  TelState;                /* 70  -1: keine Telnet Verbindung, sonst 0...x */
  BYTE *TName;                  /* 72  Terminal Name - implies telnet when set */
  AD_T ad;                      /* 74 address structure (resolved once ..) */
  WORD keepalive;				/* Time diffenrece for sending keepalive messages */
  WORD tel2217;			        /* JR1203 flags for redirector rfc2217 implementation */
#define TELB_2217 0x0001	    /* JR1203 Bit 0: rfc2217 negociated and active */
#define TELB_22in 0x0002 	    /* JR1203 Bit 1: set for initial modem info */
  void *context;              /* pointer to app context that can be used in callback from TCP */
} TCP_t;

TCP_t *TCPAlloc();

TCP_t *TCPAlloc( void);
int   TCPOpen( int, TCP_t *, int);

WORD TcpWriteNB(TCP_t *t, void far *s, WORD n);

/* * * * * TCP low level * * * * */
int RSpace(TCP_t *);
void netmask(BYTE *,int);
void pcib(TCP_t *,BYTE);
void T_Discon(TCP_t *);
void T_Disc(TCP_t *t, signed int hardtimeout);

