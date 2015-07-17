/*****************************************************************************/
/* Main Module :                                                             */
/* Initialize HW, read setup for serial and network interface                */
/* Start customer specific functionality                                     */
/*****************************************************************************/
/* Version  X0.00  demo template                                             */
/*****************************************************************************/
/* History:                                                                  */
/* 1998-11-18  jl  first beta version with all functionality                 */
/* 1999-10-29  as  beautified for template project                           */
/* 2002-10-14  gm  Modified for CPK500                                       */
/* 2003-06-05  gm  Modified for CPK520 XPort additions                       */
/* 2004-02-11  gm  Modified for CPK550 Micro100, UDS200 additions            */
/* 2004-07-01  gm  Modified for CPK551 XPortEX, SDS additions                */
/* 2004-09-01  gm  Modified for CPK560 WiPort additions                      */
/* 2006-02-03  gm  Modified for CPK6101 additions                            */
/* 2006-07-26  gm  Removed WBX cp settings in VersionInit                    */
/*****************************************************************************/

/* Definitions */
#define  DEF_VARS       /* defines what set variables from GLOBALS.H is used */

/* Included files */
#include "bldFlags.h"
#include <style.h>      /* defines main data types - BYTE, WORD, etc. */
#include <proconf.h>    /* defines some variables of configuration */
#include <proj.h>       /* defines structure for password, etc. */
#include <globals.h>    /* defines global variables */
#include <hwstruc.h>	/* defines the hardware structure */
#include <nethw.h>		/* defines the network structure - CPK6101 added */
#include <io.h>			/* defines the IO functions - printf, getXXX, putXXX, etc. */
#include <ip.h>			/* defines the IP structure */
#include <tcp.h>		/* defines the TCP structure - CPK6101 added */
#include <udp.h>		/* defines the UDP structure */
#include <string.h>		/* defines string functions */
#include <kernel.h>		/* define kernel functions - EE_Read, EE_Write, spawn, etc. */
#include <mbuf.h>		/* defines buffer pool functions */
#ifdef WEB
#include <web.h>		/* defines web functions */
#endif

#include "security.h"	/* defines the setup locations for record 1 features */
#include "demo.h"		/* defines in "demo.h" true or false DEBUG mode is set */

#ifdef WF
#include <\wiport\bits.h>		/* defines configurable bits */
#include <WiFi.h>				/* defines wireless structure & functions */
#else
#if defined (XPORT) || defined (M100)
#ifdef XPORT
#include <\XPort\bitsXP.h>		/* defines configurable bits */
#endif	/* XPORT */
#include <\SerFl\ECtypes.h>		/* defines serial flash return types */
#include <\SerFl\serflash.h>	/* defines serial flash functions */
#endif	/* defined (XPORT) || defined (M100) */
#endif	/* WF */

#include <digio.h>				/* defines configurable bits digital IO structure */

/* External variables & functions */
extern HWST HW;						/* Hardware struct */
extern NET_HW_T nethw;
extern IP_T ip;						/* IP struct */
extern PRST PR;						/* Password */
extern BYTE Setup4[];				/* GDM - setup record 3, declared in setpar.c */
extern WORD mtuSize;
extern BYTE net_mode;
extern BYTE num_intfs;
#if defined (CPCFG)
extern BYTE S_tmpRec7[];			/* temp copy of setup record 7 */
extern void defaultCP_settings(void);
extern void SaveCPsettings(void);
#endif
extern void demo(void);


/* Global variables */
GLOBAL BYTE ethmode;				/* Ethernet mode - CPK6101 added */
GLOBAL BYTE SetupOEM[126];			/* new OEM record */
GLOBAL BYTE InitChar = 0;           /* Setup Init Char - none, could be any char */
GLOBAL WORD ProConf  = PRO_NET;     /* Network support */
GLOBAL WORD TCPSPort = 9999;        /* TCP Setup Port No. */
void   *sioptr;						/* defines I/O pointers of TCB for channel 1 */

/* Required buffer for kernel - must be declared!!!  To be removed in the future */
GLOBAL BYTE scr_run[6];
/* Required buffer for hostlist - must be declared!!!  To be removed in the future */
BYTE hls[75];
/* SNMP Variables - must be given! */
/* S_name[] MUST have 12 spaces at the end (or declared 12  bytes larger) */
#ifndef BJB_SNMP
GLOBAL char S_name[] = "SPA Monitoring Unit            ";
GLOBAL char S_obj[]  = { 10, 0x2b, 6, 1, 4, 1, 141, 59, 2, 1, 2 };
#endif

/* Defines */
#define SETSSIZE 384+PROXYSTACK	/* defines stack size of SETUP process thru COM/Telnet */
#define CONSSIZE 256+PROXYSTACK /* defines stack size of SETUP process thru UDP-client */
#ifdef WEB
#define WEBSSIZE 384+PROXYSTACK /* defines stack size of each Web Manager process */
#endif


#if DEBUG
int    Chan2Stack[400+32+PROXYSTACK];         /* defines stack of DEBUG process thru COM2 */
void   *dioptr;       			/* defines I/O pointers of TCB for channel 2 */

/*****************************************************************************/
/* Debug channel                                                             */
/* - Starts a process for channel 2 which can be used as debug monitor       */
/*****************************************************************************/
void Chan2()
{
  extern void Monitor(void);

  /* function of DEBUG process thru COM2 */
  ActCCB->V24_mode  = Setup[16+48];   /* assigns COM2 mode from SETUP to CCB */
  ActCCB->V24_speed = Setup[16+48+1];/* assigns COM2 speed from SETUP to CCB */
  ActCCB->FlowCtl   = Setup[16+48+2];    /* assigns COM2 flow control to CCB */
  InitLocalChan();                                       /* initializes COM2 */
  dioptr = ActPro->IO_Ptr; /* This stores an I/O pointer for access to COM2; */
                  /* necessary for access and reference by the main process! */
  while(1) {      /* starts infinite loop; nice() function inside Monitor(0) */
	putstr("\r\nCoBox demo template - DEBUG Port\r\n");      /* First prompt */
    Monitor();  /* Start ProMon (library procedure) for debug channel COM2; */
  }
}

/*****************************************************************************/
/* Call this function directly before sending data to debug port             */
/*****************************************************************************/
void startdebug(void)                             /* switches output to COM2 */
{
 ActPro->IO_Ptr = dioptr;         /* assigns pointer to use for I/O the COM2 */
}

/*****************************************************************************/
/* Call this function directly after sending data to debug port              */
/*****************************************************************************/
void stopdebug(void)                         /* switches output to COM1 back */
{
 ActPro->IO_Ptr = sioptr;         /* assigns pointer to use for I/O the COM1 */
}
#endif /* DEBUG */

/* network driver definitions */
#ifdef N0
extern int N0_DRV;
#endif
#ifdef N1
extern int N1_DRV;
#endif
#ifdef N2
extern int N2_DRV;
#endif
#ifdef N3
extern int N3_DRV;
#endif
#ifdef ND
extern int ND_DRV;
#endif
#ifdef WF
extern int NW_DRV;
#endif

extern void SetProcess(void);   /* defines/starts SETUP process thru Telnet */
extern void ConfProcess(void); /* defs/starts SETUP process thru TCP-client */
#ifdef WEB
#ifdef WSET
extern int Init_Config(BYTE);
					/* web manager handler functions */
extern int ProcSetupConfig();
extern int GetSetupRecs();
extern int GetUnitInfo();
#endif /* WSET */
extern void WebProcess(void);             /* defines/starts mini WEB-server */
#endif	/* WEB */



/*****************************************************************************/
GLOBAL void newmain() {
/*****************************************************************************/

#pragma warn -eff
#ifdef N0
   N0_DRV;
#endif
#ifdef N1
   N1_DRV;
#endif
#ifdef N2
   N2_DRV;
#endif
#ifdef N3
   N3_DRV;
#endif
#ifdef ND
   ND_DRV;
#endif
#ifdef WF
   NW_DRV;
#endif
#pragma warn +eff

	if(HW.eeprom)  {/* only for 24LCx EEprom with more setup memory */
		/* check for valid settings, unused is 0xFF !!! which would activate all possible security features */
		if(DISSNMP) /* if SNMP is disabled, unregister SNMP-Functionality */
			udp_reregister(161,(PTF)NULL);
		if(DISTFTP) /* if TFTP is disabled, unregister TFTP-Functionality */
			udp_reregister(69,(PTF)NULL);
		if(DIS77FE)
			udp_reregister(0x77FE,(PTF)NULL);
		else
			spawn(ConfProcess,kalloc(CONSSIZE),CONSSIZE,0,"Conf");   /* Config SERVER */
		if(ENHPASSWD) {
			PR.pass = 139		/*Setup - P_ENHPWD*/;   /* offset in Setup for enhanced passwd */
			PR.plen = 16;    /* max. len of enhanced passwd is 16 */
		}
	}
	if (!DISTELNET)
		spawn(SetProcess,kalloc(SETSSIZE),SETSSIZE,0,"Setup");   /* Setup */

#ifdef WEB
	if(!DISWEBS) {
		/* setup the configurable HTTP port number here */
		SetServicePort((WORD *)HTTP_PORT, 80);
		spawn(WebProcess,kalloc(WEBSSIZE),WEBSSIZE,0,"Web1");   /* WEB SERVER */
		spawn(WebProcess,kalloc(WEBSSIZE),WEBSSIZE,0,"Web2");   /* WEB SERVER */
		spawn(WebProcess,kalloc(WEBSSIZE),WEBSSIZE,0,"Web3");   /* WEB SERVER */
#ifndef WSET
#else
		if(!DISCGIS) {
				/* Initialization function for web based setup */
			Init_Config(HW.eeprom);
				/* register the handler functions for dynamic web pages used by the web manager */
			WebMethRegister("GET",GetSetupRecs,"secure/setuprec.xml");
			WebMethRegister("GET",GetUnitInfo,"secure/unitinfo.xml");
			WebMethRegister("POST",ProcSetupConfig,"secure/setup.cgi");
			WebMethRegister("GET",GetSetupRecs,"setuprec.xml");
			WebMethRegister("GET",GetUnitInfo,"unitinfo.xml");
			WebMethRegister("POST",ProcSetupConfig,"setup.cgi");
		}
#endif
	}
#endif

/* sets LED state */
	BlinkRWord    = 0;                                        /* red LED: OFF */
	BlinkGWord[0] = 0xffff;                           /* green LED: always ON */
	BlinkGWord[1] = 0;                                     /* yellow LED: OFF */

#if DEBUG
		   /* Init debugging for channel 2 */
	spawn(Chan2,Chan2Stack,sizeof(Chan2Stack),1,"C2");      /* starts process */
	sdelay(500);      /* Wait 500 msec for proper initialization of channel 2 */
#endif

    	/* give tasks time to get memory - yes - 3 nice()s */
    nice();
    nice();
    nice();
    MBufInit();      /* ready with initialization, now use rest as buffers */

/* switches pointers of active TCB & CCB to parameters of first serial port  */
	ActCCB = AllCCB;        /* assigns address AllCCB[0] (COM1) to active CCB */
	ActPro->Chan_Nr = 0;       /* points to use COM1 (number 0) in active TCB */
	ActPro->CCB_Ptr = AllCCB;  /* changes pointer to active CCB in active TCB */

/* sets all necessary line parameters for first serial port */
	AllCCB[0].V24_mode  = Setup[16];   /* assigns COM1 mode from SETUP to CCB */
	AllCCB[0].V24_speed = Setup[16+1];/* assigns COM1 speed from SETUP to CCB */
	AllCCB[0].FlowCtl   = Setup[16+2];    /* assigns COM1 flow control to CCB */
	AllCCB[0].Flags     = 0;   /* sets for COM1 Response mode, flushing, etc. */

	InitLocalChan();                    /* ... and initializes interface COM1 */

	sioptr=ActPro->IO_Ptr; /* THIS STORES AN I/O POINTER; NECESSARY FOR ACCESS*/

	demo();                                               /* Start CoBox Demo */
}

void VersionInit(void)
{
	extern BYTE fw_type[];
	extern WORD firmwarecheck;

#ifdef FW_TYP
	strcpy(fw_type,FW_TYP);
#endif

#ifdef FW_CHECK
	firmwarecheck=*(WORD *)FW_CHECK;
#else
#error No matching target system defined!  Check bldFlags.h.
#endif

#ifdef PHY
	ethmode = Setup4[77];		/* Ethernet connection type - configurable */
#endif
	mtuSize = (*(WORD *)(Setup4+78)) ? (*(WORD *)(Setup4+78)) : DEFAULT_MTU;
	ip.arpcachetime = *((WORD *)(Setup4+100));
	if((ip.arpcachetime  > 600) || (ip.arpcachetime == 0) )
	{
		ip.arpcachetime = 600;
	}

	if(nethw.Net_HW_Typ != 0x600){ /* not Tokenring and DHCP device name set */
		memcpy(nethw.DHName,   Setup +112, 8);
		memcpy(nethw.DHName+8, Setup4+102, 8);
	}

	/* read OEM setup record 4 */
	if (EE_Read(SetupOEM,512,126)){
		memset(SetupOEM,0,126);
		EE_Write(SetupOEM,512,126);
	}

#ifdef CPCFG
#ifndef STATIC_CPCFG
			/* Init Record 7 for Configurable Pins */
	if ( EE_Read(S_tmpRec7,896,126) )		/* read setup record 7 (126 bytes, not the chksum) */
	{ /* some error */
		defaultCP_settings();				/* factory default values */
		EE_Write(S_tmpRec7, 896, 126);		/* store "new" record 7 data in non-volatile memory */
	}
#endif /* !STATIC_CPCFG */

	/* initializae the digital I/O struct based on setup record 7 */
	SaveCPsettings();
	dio_vbit_init();		/* low-level setup of all the digital I/O bits */
#endif /* CPCFG */

  num_intfs = 1;
#ifdef WF
	loadWiFiSettings();
	net_mode = (WiFiCfg.enabled) ? 2 : 1;
#else
	net_mode = 1;
#endif /* WF */

}
/* main.c ends here */
