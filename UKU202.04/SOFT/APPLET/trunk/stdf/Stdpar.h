/*****************************************************************************/
/* History of Change :                                                       */
/*****************************************************************************/
/* 01.12.00 jl added in the standard parameters the DHCP device name for     */
/*          the DCHP naming option                                           */
/* 13.02.01 jl changed the getip() routine in newly created getip2(), which  */
/*			does not preset everything to 0 if the first number is set to 0  */
/*			This was nasty when using the new DHCP functionality with 0.0.0.5*/
/*			for example. After entering again the setup this was preset to 0 */
/* 18.07.02 jb C-020325-16212 16 chr DHCP name								 */
/*****************************************************************************/
#include <ip.h>
#include <tcp.h>

extern int set_netmode();
extern void show_netmode();

void SSetStd(void) {
  int i,j;
  char name[17];

#ifdef WF
  i = set_netmode();
  if (i != 2)
  {
#endif

    if (HW_ETH_NSel()) {
      if (!(ProConf&PRO_ADE)) {
        i=SETUPVAR[5]&0x40;
        printf("\r\nEthernet Interface AUI");
        i=getynt(i);
        if (i) SETUPVAR[5]|=0x40; else SETUPVAR[5]&=~0x40;
      } else SETUPVAR[5]|=0x40;
    }
    printf("\r\nIP Address : "); getip2(SETUPVAR);
    printf("\r\nSet Gateway IP Address");
    if (getynt(SETUPVAR[PR.gw])) {
      printf("Gateway "); printf("IP Address : ");
      getip(SETUPVAR+PR.gw);
      printf("\r\n");
    } else memset(SETUPVAR+PR.gw,0,4);

    if (SETUPVAR[PR.nm]>31) SETUPVAR[PR.nm]=0;
    printf("Netmask: Number of Bits for Host Part (0=default) (");
    printf("%u) ",SETUPVAR[PR.nm]);
    getint8(SETUPVAR+PR.nm,(void*)0);
    if (PR.pass) {
      printf("\r\nChange telnet config password");
      if (getynt(0)) {
        memset(SETUPVAR+PR.pass,0,4);
        printf("Enter new Password: ");
        for (j=PR.pass; j<(PR.pass+PR.plen); j++) {
          while (((i=getch0())<0x20) && (i!=0x0d)) ;
          putch(i);
          if (i==0x0d) break;
          SETUPVAR[j]=i;
        }
        printf("\r\n");
      }
    }
#ifndef NANO
    if ((nethw.Net_HW_Typ==0x600) && PR.tra){
      printf("Use Tokenring administered address");
      if (getynt(SETUPVAR[PR.tra])) {
        printf("Enter address as 6 hex pairs: ");
        for (j=PR.tra; j<PR.tra+6; j++) {
          printf("(%2x)",SETUPVAR[j]);
          gethex8(SETUPVAR+j,(void*)0); putch(' ');
        }
        if ((SETUPVAR[PR.tra]&0xc0)!=0x40) {
          printf("\r\n - Invalid address - using physical ");
          memset(SETUPVAR+PR.tra,0,6);
        }
        printf("\r\n");
      } else memset(SETUPVAR+PR.tra,0,6);
    }
    else if((nethw.Net_HW_Typ!=0x600) && (((WORD *)SETUPVAR)[0]==0)) {/* not TR and IP with 0.0.x.x which means DHCP enabled */
#else
    if(((WORD *)SETUPVAR)[0]==0) {/* not TR and IP with 0.0.x.x which means DHCP enabled */
#endif
     /* no Tokenring, so use this area + following 2 bytes for the customised name */
     /* for DHCP naming option */
        memset(name,0,17);
        memcpy(name,SETUPVAR+112,8);
#ifdef COBOX
		memcpy(name+8,SETUPVAR4+102,8);	 /* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
#endif
        printf("Change DHCP device name (%s) ?",name[0]?name:"not set");
        if (getynt(0)) {
         printf("Enter new DHCP device Name : ");
         memset(name,0,17);
#ifdef COBOX
         if(HW.eeprom)
         {
            getstr(name,17);				 /* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
		    memcpy( SETUPVAR4+102,name+8,8);/* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
         }
         else
            getstr(name,9);				 /* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
#else
         getstr(name,9);				 /* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
#endif
		 memcpy(SETUPVAR+112,name,8);
        }
    }
#ifdef WF
  }
#endif
}

void SShoStd(void) {
  long x;
  int i;
  char name[17];

  printf("\r\n\n*** basic parameters \n\rHardware: ");
#ifndef NANO
  if (nethw.Net_HW_Typ!=0x600) {
#endif
    printf("Ethernet ");
    if (HWSeries()>=10) {
      if (ProConf&PRO_ADE) {
        printf("Autodetect ");
      } else printf((SETUPVAR[5]&0x40)?"AUI":
             (HW_ETH_NBnc()?"BNC":"TPI")
            );
    }
#ifdef WF
#ifdef MARVELL
    printf(", WLAN 802.11bg");
#else
    printf(", WLAN 802.11b");
#endif
#endif
#ifndef NANO
  } else {
    printf("Token Ring ");
    if (PR.tra && ((SETUPVAR[112]&0xc0)==0x40)) {
      printf(" ring address ");
      printf("%1H",SETUPVAR+PR.tra);
    }
  }
#endif

#ifdef WF
  show_netmode();
#endif

  printf("\r\nIP addr "); putipd(SETUPVAR);
  if (SETUPVAR[PR.gw]) {
      printf(", gateway "); putip(SETUPVAR+PR.gw);
  } else printf(", no gateway set");
  if (SETUPVAR[PR.nm]) {
    printf(",netmask ");
    netmask((BYTE *)&x,(int)SETUPVAR[PR.nm]);
    putip((void *)&x);
  }
  if (PR.pass && SETUPVAR[PR.pass]) printf("\r\nTelnet config password set");
  printf("\r\n");

#ifndef NANO
  if((nethw.Net_HW_Typ!=0x600) && (((WORD *)SETUPVAR)[0]==0)) { /* not TR and IP with 0.0.x.x which means DHCP enabled */
#else
    if(((WORD *)SETUPVAR)[0]==0) {/* not TR and IP with 0.0.x.x which means DHCP enabled */
#endif
      memset(name,0,17);
      memcpy(name,SETUPVAR+112,8);
#ifdef COBOX
      memcpy(name+8,SETUPVAR4+102,8);	/* 18.07.02 jb C-020325-16212 16 chr DHCP name  */
#endif
/*      name[8]=0; */
      printf("DHCP device name : %s\n\r",name[0]?name:"not set");
  }
}
