/* 4.57 JL 12.06.01 renamed two unused vars for storing the Xon/xoff chars, for making it flexible for other characters besides 11h & 13h */

#include <sizedef.h>

typedef struct {
   BYTE
      PakHardCt, PakTyp, PakSoftCt, PakLen,
      PakFrom, PakTo, PakRes1, PakRes2;
   WORD
      PakCheck;
} PaketHead;

typedef struct {
   unsigned Zeit;
   PaketHead head;
   unsigned char rest[TxEntrySize-sizeof(unsigned)-sizeof(PaketHead)];
   } TxEntry;

typedef struct CCB {
  BYTE	V24_mode;     /* local line mode */
  BYTE	V24_speed;    /* local line speed */
  BYTE	Name[8];      /* node name */
  BYTE	Adr;          /* node adress */
  BYTE	Group;        /* group, if existent, 0xff if not */
  BYTE	Cmode;        /* connect mode */
  BYTE	Cid;          /* autodest id, if any */
  BYTE	Dmode;        /* disconnect mode */
  BYTE	Dstring[8];   /* disconnect string, if any */
  BYTE	Dt1,Dt2;      /* timeout to disconnect, if any */
  BYTE	QuLen;        /* Length of queue (0..31) */
  BYTE	FlowCtl;      /* Flow control mode */
  BYTE	Flags;        /* Response mode, flushing etc. */
  BYTE	chksum;
  BYTE	ichksum;      /* inverse of checksum */
				/* bis hierher 30 chars */
  WORD  DisConTim;	/* Dt1,Dt2 umgerechnet auf secs */
  BYTE	SetupValid;
  BYTE	Xonchar;	/* JLJLJL Character representing XON;  default = 11h */
  BYTE	Xoffchar;	/* JLJLJL Character representing XOFF; default = 13h */
  BYTE	DGramResCode,DGramWaitPar;
  BYTE	QuittFlg;
  BYTE	TxPutNum,TxGetNum,ErwPakNum;
  WORD  LatestPiep,ConZeit;
  BYTE	Queued,Busy;
  BYTE	ConResult,DicResult;
  BYTE	VerbActive;
  BYTE	DisConFlg;
  WORD	LocAct;
  BYTE	InitFlg;      /* bis hierher 38 chars */
  WORD  IOPtrs[2];
  BYTE  LoTxFifo[LoTxFifoSize];
  BYTE  LoTxVars[16];
  BYTE  LoRxFifo[LoRxFifoSize];
  BYTE  LoRxVars[16];
//  BYTE  BPABuf[256+2+1];
} CCB;

// -------------------------------------
//  Serial Port status for OCP_HP: Chuck
// -------------------------------------
typedef struct SPORT {
	WORD	SP_RxBytes;
	WORD	SP_RxDMACount;
	WORD	SP_RxFramError;
	WORD 	SP_RxOvrnError;
	WORD	SP_RxPrtyError;
	WORD	SP_RxErrStatus;
	WORD	SP_TxBytes;
	WORD	SP_TxCount;
	WORD	SP_TxErrCount;
	WORD	SP_TxErrStatus;
	WORD    SP_RxErrPassThru;
}SPORT;
#define FLSHIN  0x10
#define FLSHOUT 0x20

#define C-> ActCCB->
