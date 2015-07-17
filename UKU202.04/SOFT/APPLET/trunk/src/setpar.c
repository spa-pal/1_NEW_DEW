/*****************************************************************************/
/* setpar : sets SETUP parameters                                            */
/*                                                                           */
/* Parameters: entry way 0 - Telnet / 1 - COM1                               */
/* Returncode: requested external service (e.g. ProMon) or 0                 */
/*****************************************************************************/
#include "bldflags.h"
#include <style.h>               /* definitions for programming style */
#include <proconf.h>               /* defines some Network parameters */
#include <proj.h>             /* defines structure for password, etc. */
#include <nethw.h>       /* hardware definitions for Network * CPK430 */
#include <hwstruc.h>
#include <string.h>
#include <kernel.h>
#include <io.h>
#include "security.h"
#include "snmpdef.h"

#ifdef WF
#include <WiFi.h>
#endif

#define SETUPVAR Setup /* K4.3 -> K4.5 */
#define SETUPVAR4 Setup4	/* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
#define SETUPVAR5 Setup5	/* 08.08.09 strange_bear EEPROM DEVICE info     */
BYTE Setup4[126];         /*ak temporary copy of Setup4[] */
BYTE Setup5[126];         /*ak Setup5[] */
#define getch0( ) getch( )            /* defines macro for getch0() function */
#define COBOX           /* this define is needed for enhanced setup features instdpar.h : DHCPname =16char */

extern BYTE Setup[ ];                  /* defines array for SETUP parameters */
extern BYTE Nchan;             /* defines variable for serial channal number */
extern WORD ProConf;              /* defines Network configuration parameter */
extern BYTE SWTyp;                     /* defines Set Version Type parameter */
extern HWST HW;                            /* hardware structure */

/*	EEPROM SECTIOB FOR DEVICE INFO	*/

GLOBAL BYTE Location_EEPROM[STRLEN];

/*	EEPROM SECTION END	*/


GLOBAL PRST PR = { 8, 4, 12, 6, 112 }; /* see proj.h: pwpos,len,gw,nw,traddr */

static WORD cbdef[ ]= { 0x024c, 0 };  /* defs default serial port parameters */
/* "0"-No flow control,"2"-9600 Baud, "4c"-RS232C,8 bit,No Parity,1 stop bit */

static BYTE *baudratestrings[] = {
    "38400","19200","9600","4800","2400","1200","600","300","115200","57600",
#ifdef BAUD_230K
    "230400",
#endif
#ifdef BAUD_920K
    "460800", "921600",
#endif
    0};

/* prototypes */
void factory_defaults( void );  /* defs function to reset default parameters */
void default_setup(int type);
void save_settings(void);
void setup_restore(void);
void SShoStd( void );  /* defs function to show basic parms, HW/Gateway, etc */
void SSetStd( void );   /* defs function to set basic parms, HW/Gateway, etc */
void SShoSec(void);
void SSetSec(void);
int  SetParStart( int d );
void SSetChan(BYTE *sp,WORD);		/* jb, 18.11.02: second chan disconnectible */
void SShoChan( int i, BYTE * sp );
void SSetNTP(void);
void gethex8k(unsigned char *v);
void putst_pde(char *str_const, BYTE flag);
void Device_Info_Parameters(void);

#ifdef DEMO11
void SSetSNMP(void);
void SShoSNMP(void);
#endif
#ifdef DEMO15
void SSetNTP(void);
#endif
#ifdef DEVICE_INFO_EEPROM
void SShoDeviceInfo(void);
#endif
#include <stdf\stdpar.h>
#ifdef WF
#include <stdf\WiFi.c>
#endif
	/* keep in sync with WiFi.c */
#define DEFAULT2FACTORY 0
#define DEFAULT2MENU    1


/*****************************************************************************/
int SetParms( int d ) /* entry point from kernel; d=0-Telnet/1-COM1-entry way*/
/*****************************************************************************/
{
    WORD i;
    BYTE * sp;

    i = SetParStart( d ); /* shows node type, version, waits for enter "CR/M"*/
    if( i ) return i;  /* if "M" pressed, returns !=0 for starting Monitor() */

#ifdef DEVICE_INFO_EEPROM
			SShoDeviceInfo();
#endif	
	
start:
    SShoStd( );                        /* shows basic parms, HW/Gateway, etc */
	if(HW.eeprom) /* only for 24LCx EEprom with more setup memory */
		SShoSec();            /* Show Security settings */


    for( i = 0; i < Nchan; i++ )
        SShoChan( i + 1, Setup + 16 + i * 48 ); /* shows cur COMs parameters */

#ifdef WF
	 ShowWiFiSettings();
#endif
#ifdef DEMO11
	SShoSNMP();
#endif

    do                                                 /* main loop of SETUP */
    {
      	nice();							/* jb, 03.06.02, escal C020618-20058 */
        i = 99;                     /* initial value then shows request text */
        printf("\r\n\r\nChange Setup:\r\n  0 Server configuration");
        printf("\r\n  1 Channel 1 configuration");
        if( ( Nchan > 1 ) && ( SWTyp != 2 ) )    /* bypasses if only one COM */
            printf("\r\n  2 Channel 2 configuration");
#ifdef DEMO11
        printf("\r\n  3 SNMP configuration");
#endif
#ifdef DEMO15
		printf("\r\n  3 NTP Setup");
#endif
#ifdef WF
		printf("\r\n  4 WLAN");
#endif
		printf("\r\n  6 Device Info");
        printf("\r\n  7 factory defaults");
        printf("\r\n  8 exit without save");
        printf("\r\n  9 save and exit                Your choice ? ");
        getint( &i, (void *) 0 );                             /* gets choice */
    		putch(10);
        switch( i )                               /* checks variant of reply */
        {
        case 0:
            SSetStd( ); /* starts external function of Network configuration */
            break;
        case 2:
            if( Nchan < 2 ) goto start; /* if accidentally press 2 for one COM */
        case 1:
            SSetChan( Setup + 16 + ( i - 1 ) * 48,i );    /* starts COM config */
            printf("\r\n");                /* just jumps to next line */
            break;
#ifdef DEMO11
        case 3:
            SSetSNMP();
            putstr("\r\n");
            break;
#endif
#ifdef DEMO15
		case 3:
			SSetNTP();   /* NTP Server Setup; */
            putstr("\r\n");
            break;
#endif
#ifdef WF
		case 4:
			EnterWiFiSettings();
			break;
#endif
		case 6:

#ifdef DEVICE_INFO_EEPROM
			Device_Info_Parameters();
			break;
#endif
	
		/*if(HW.eeprom) /* only for 24LCx EEprom with more setup memory */
				//SSetSec();*/
			break;
        case 7:
	        default_setup(DEFAULT2MENU);
		//	factory_defaults( );  /* restores factory default parameters */
			printf("\r\n");
			break;
        case 8:
			setup_restore(); //ak
			printf("\r\nExiting without save !\r\n");
	        sdelay(100);
			return 9999;     /*ak imitates normal return after calling nmon(), but without real calling */
        case 9:
			goto setexit;   /* abandons this loop to save new parameters */
        default:
			continue;         /* any other key just continues this loop */
        }
        goto start; /* shows again basic parameters and returns to this loop */
    }
    while( 1 );                                        /* endless SETUP loop */

setexit:
	save_settings();

	printf("\r\nParameters stored ...\r\n");     /* and finishes SETUP */
	sdelay(1000);
    return( 0 );
}

void Device_Info_Parameters(){
  /* Init location */
   printf("\r\nВведите местоположение устройства (%s): ", Setup5 + 33);
   getstr(Setup5 + 33, STRLEN);
   printf("\r\n");
   Setup5[33 + STRLEN] = 0x00;
   
  
}

/*****************************************************************************/
void SShoTyp( )                /* shows the first prompt; called from kernel */
/*****************************************************************************/
{
    printf("\r\n*** Lantronix SPA Server ***");
}

void setup_restore(void)
{
  EE_Read(Setup,6,120);  /* read standard setup (120 bytes + chksum) */
    if(HW.eeprom) {
       *((WORD *)(Setup+120))=126;
       EE_Read(Setup+122,128,126);  /* enhanced setup, should already be valid */
       EE_Read(Setup4,384,126);     /* enhanced setup, should already be valid */
	   EE_Read(Setup5,512,126);     /* enhanced setup, should already be valid */
  }
}

void save_settings(void)
{
   StoreCMOS();
   if (HW.eeprom){
     EE_Write(Setup4,384,126);
	 EE_Write(Setup5,512,126);
	 }
#ifdef WF
   saveWiFiSettings();
#endif
}

void putAESvers(void)
{
}

#ifndef getch0
getch0( )
{
    int i;
    while( !( i = getch( ) ) );
    return i;
}
#endif

/* Needed for encryption and WiFi */
void gethex8k(unsigned char *v)
{
  int i=0,b,ic,xflag=0;

again:
  while ((ic=getch()) != 0) {
   if ('0' <= ic && ic <= '9') b=ic-'0';
   else if ('A' <= ic && ic <= 'F') b=ic-'A'+10;
   else if ('a' <= ic && ic <= 'f') b=ic-'a'+10;
   else goto again;
   xflag++;
   i=(i<<4)+b;
   putch('*');
   if(xflag==2) {
    *v=(BYTE) i;
    return;
   }
  }
}

/*****************************************************************************/
void factory_defaults(void)  /* restores factory default parameters of ports */
/*****************************************************************************/
{
    memset( Setup + 4, 0, 116 );  /* drops SETUP, except the CoBox's IP-addr */
    memcpy( Setup + 16, cbdef, sizeof( cbdef ) );
                                          /* restores default values of COM1 */
    memcpy( Setup + 16 + 48, cbdef, sizeof( cbdef ) );
	                                      /* restores default values of COM2 */
}

#pragma argsused
void default_setup(int type)
{
	Setup[4] = 0;
	Setup[7]=45;         /* Set keepalive timer to 45, which was the original value before we made this configurable */
	memset(&Setup[8], 0, 246-8);
	*((WORD *)(Setup+120)) = 126; /* length of enhanced parameter has to be here */
    memcpy(Setup + 16, 		cbdef, sizeof(cbdef)); /* restores COM1 */
    memcpy(Setup + 16 + 48, cbdef, sizeof(cbdef)); /* restores COM2 */
	strcpy(&Setup[156], "public"); /* SNMP Community name + Null terminator */
	*((WORD *) &Setup4[100]) = 600;/* ARP cache timeout default = 600s */

#ifdef WF
	defaultWiFiSettings(type, 2);
#endif
}

void SSetSec(void)
{
  WORD i,j;

  /* check for disable SNMP */
  printf("\r\nDisable SNMP");
  if (getynt(DISSNMP)) {
   SECFLAGS |= 0x40;
  }
  else {
   SECFLAGS &= ~0x40;
  }

  /* Check for SNMP Community */
  if(!DISSNMP) {
   printf("\r\nSNMP Community Name (%s): ",P_SNMPCOM);
   getstr(P_SNMPCOM, 14);
  }

  /* check for disable telnet */
  printf("Disable Telnet Setup");
  if (getynt(DISTELNET)) {
   SECFLAGS |= 0x01;
  }
  else {
   //memset(S_tmp+PR.pass,0,4);    // C-031030-41566 telnet password vanishes when security settings
                                   // menu is accessed.
   SECFLAGS &= ~0x01;
  }

  /* check for disable tftp */
  printf("Disable TFTP Firmware Update");
  if (getynt(DISTFTP)) {
   SECFLAGS |= 0x02;
  }
  else {
   SECFLAGS &= ~0x02;
  }

  /* check for disable port 77FE */
  printf("Disable Port 77FEh");
  if (getynt(DIS77FE)) {
   SECFLAGS |= 0x10;
  }
  else {
   SECFLAGS &= ~0x10;
  }

  /* check for disable web Server */
  printf("Disable Web Server");
  if (getynt(DISWEBS)) {
   SECFLAGS |= 0x20;
  }
  else {
   SECFLAGS &= ~0x20;
  }

#ifdef WSET
  /* check for disable CGI setup */
  printf("Disable Web Setup");
  if (getynt(DISCGIS)) {
   SECFLAGS2 |= 0x80;
  }
  else {
   SECFLAGS2 &= ~0x80;
  }
#endif
  /* check for disable ECHO port */
  printf("Disable ECHO ports");
  if (getynt(!DISECHO)) {
      SECFLAGS2 &= ~0x01;
  }
  else {
    SECFLAGS2 |= 0x01;
  }


  /* check for enhanced password */
  printf("Enable Enhanced Password");
  if (getynt(ENHPASSWD)) {
   SECFLAGS |= 0x08;
   printf("Change the Password");
   if(getynt(0))
    printf("Enter Password : "); getstr(P_ENHPWD,17);
  }
  else {
   memset(P_ENHPWD,0,16);
   SECFLAGS &= ~0x08;
  }

}

void SShoSec(void)
{
	printf("*** Security\r\n");
	putst_pde("SNMP is              ",	DISSNMP);
	printf(    "SNMP Community Name: %s\r\n", P_SNMPCOM);
	putst_pde("Telnet Setup is      ",DISTELNET);
	putst_pde("TFTP Download is     ",DISTFTP);
	putst_pde("Port 77FEh is        ",DIS77FE);
	putst_pde("Web Server is        ",DISWEBS);
#ifdef WSET
	putst_pde("Web Setup is         ",DISCGIS);
#endif
	putst_pde("ECHO is              ",!(DISECHO));
	putst_pde("Enhanced Password is ",!(ENHPASSWD));

	printf("\r\n");
}

void putst_pde(char *str_const, BYTE flag)
{
	printf(str_const);
	if(flag)
		printf("disabled\r\n");
	else
		printf("enabled\r\n");
}




/*****************************************************************************/
void SSetChan(sp,chan) BYTE *sp; WORD chan;	/* jb, 18.11.02: second chan disconnectable */
/*****************************************************************************/
{
    WORD i, j;

  BYTE getbaud[7];    /* defines string variable for entering Baudrate value */

  if ((sp[1] != 0xff) && (sp[1] > sizeof(baudratestrings)/sizeof(BYTE *)-1)) sp[1]=2;
                                   /* now setup is definitely in valid range */
  while ( 1 ) {
											    /* shows current Baudrate value */
	if ((sp[1]==0xff)&&(chan==2))			/* jb, 18.11.02: second chan disconnectable */
		printf("\r\nBaudrate (00) ");
	else
		printf("\r\nBaudrate (%s) ", baudratestrings[ sp[ 1 ] ] );
	getbaud[ 0 ]=0; getstr( getbaud, sizeof(getbaud) );       /* gets your new input value */
	if( !getbaud[ 0 ] )                       /* pressed enter - not touched */
		i = sp[ 1 ];                                       /* leaves old value */
	else {                                         /* some value has been entered */
		if ((getbaud[0]==0x30)&&(chan==2)){		/* jb, 18.11.02: second chan disconnectable */
			sp[1]=0xff;
			return;
		}
		for( i = 0; baudratestrings[i]; i++ )
			if(!strcmp(getbaud,baudratestrings[i])) break;  /* comparing with list*/
	}
	if(!baudratestrings[i])
		printf("Invalid Baudrate !!!");
	else {
#ifdef EX
#ifdef VAR_CPUPERF
		if(i>10 && (Setup4[116] & 0x80)==0) {
			printf("\r\nRequires CPU high performance!");
			printf("\r\nEnable High Performance");
			if (getynt((Setup4[116] & 0x80)?1:0)) {
				Setup4[116] |= 0x80;
				break;   /* found correct baudrate in string & supported */
			}
			else {
				Setup4[116] &= 0x7f;
				i = 2;
			}
		}
		else
#endif
#endif
			break;   /* found correct baudrate in string & supported */
	  }
  }
  sp[ 1 ] = i;                                    /* final value of Boudrate */


    printf("I/F Mode");
	gethex8( 0, sp );                          /* requests an interface mode */
#if defined (U200)
   sp[0] &= 0xFC;
#endif
    printf("\r\nFlow");
	gethex8( 0, sp + 2 );                       /* requests new flow control */
    if( ( sp[ 2 ] &3 ) == 3 ) sp[ 2 ] &= 0xfc;
	                                       /* if 2 last bits set, drops them */

   printf("\r\nSource Port (%5u) ", *((WORD *)(Setup + 20)));
    getint((WORD *)(Setup + 20), (void *) 0);   /* requests number of own network port */
	 printf("\r\n");

}

/*****************************************************************************/
void SShoChan( int i, BYTE * sp ) /* shows current parameters of COM port "i"*/
/*****************************************************************************/
{
  printf("\r\n***************** Channel %1d *****************", i);

    printf("\r\nBaudrate %s", baudratestrings[ sp[ 1 ] ] );  /* shows Baudrate value */
    printf(", I/F Mode %2x", sp[ 0 ]);                       /* shows interface mode */
    printf(", Flow %2x", sp[ 2 ]);                           /* shows flow control */
    printf("\r\nSource Port (%5u) ", *((WORD *)(Setup + 20)));
#ifdef EX
#ifdef VAR_CPUPERF
	printf("\r\nCPU performance  : ");
	if(Setup4[116] & 0x80)
        printf("High");
	else
		printf("Standard");
#endif
#endif
    printf("\r\n");
}

void SSetSNMP()
{
    printf("\r\n******** SNMP Configuration ********");
    /* Community names */
    printf("\r\n  SNMP community name for read (%s): ", &(Setup[34]));
    getstr(&(Setup[34]), 13);
    printf("\r\n  SNMP community name for write (%s): ", &(Setup[48]));
    getstr(&(Setup[48]), 13);
    /* Trap IP addresses */
    printf("\r\n  Enter IP addresses for SNMP traps:");
    printf("\r\n    1: "); getip(Setup + 22);
    printf("\r\n    2: "); getip(Setup + 26);
    printf("\r\n    3: "); getip(Setup + 30);
    printf("\r\n");
}

/*****************************************************************************/
/* function SShoSNMP                                                         */
/* - Show connection parameters                                              */
/*****************************************************************************/
void SShoSNMP()
{
    printf("\r\n******** SNMP Configuration ********");
    printf("\r\n  SNMP community name for read: %s", &(Setup[34]));
    printf("\r\n  SNMP community name for write: %s", &(Setup[48]));
    printf("\r\n  Trap IP addresses: ");
    putstr("\r\n  1: "); putip(Setup + 22);
    printf("\r\n  2: "); putip(Setup + 26);
    printf("\r\n  3: "); putip(Setup + 30);
}
/*****************************************************************************/
/* function SShoDeviceInfo                                                   */
/* - Show device info parameters                                             */
/*****************************************************************************/
void SShoDeviceInfo(void)
{
	EE_Read(Setup5, 512, 126);
	
	printf("\r\n\r\n\r\n******** Информация об устройстве ********");
    printf("\r\n  Местоположение устройства: %s", Setup5 + 33);

}


/********************************************* end of SetPar.c ***************/
