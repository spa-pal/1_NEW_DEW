/*                                               
 * Copyright (c) 2004, Lantronix Inc. All rights reserved.
 *
 * File: supplicant_i.h
 *
 * Purpose: Common definitions across supplicant modules.
 *          
 * Created By: Vishal Kakkad
 *
 * History:
 *     09/24/2004	VMK		Initial Creation
 * 
 */

#ifndef NETDRV_H
#define NETDRV_H

/****************************************************************************
 *
 *                                 CONSTANTS
 *
 ****************************************************************************/
 

/****************************************************************************
 *                                                                            
 *                               MACROS
 *                                                                            
 ****************************************************************************/
#ifndef ND
#define ND          0x4e44
#endif
#ifndef NW
#define NW          0x4e57
#endif
 
#define MAX_PORTS   2
#define NUM_TXBUFS  2   // per interface Tx Bufs

#define RING_SIZE	    0x0600

// Used in BHDR flags
#define BSS_WRAP        0x01
#define ADVBUF          0x02        // this causes the app to just advance buffer without
                                    // processing it. Included to provide ability to use buf
                                    // as scratchpad (eg. MIC Calc) and then just discard it.
#define BRIDGED_MODE    0x80        // legacy setting.. not used currently
#define LOCAL_PROC_ONLY 0x40

/* SBFLAG Definitions for DRV_IOCB SBFLAG*/
#define SB_ALLOC1	0x10
#define SB_SENDP1	0x20
#define SB_ALLOC2	(SB_ALLOC1 >> 4)
#define SB_SENDP2	(SB_SENDP1 >> 4)

#define IF_UP       1
#define IF_DOWN     0

// Definition for operational mode of the network interfaces
#define WIRED_ENABLED       0x01
#define WIRELESS_ENABLED    0x02
#define BRIDGE_PASS_THRU    0x04
#define BRIDGE_PROXY_ARP    0x08

#define MODE_BRIDGE_PASS_THRU   0x07
#define MODE_BRIDGE_PROXY_ARP   0x0b
#define MODE_WIRELESS_ONLY      0x02
#define MODE_WIRED_ONLY         0x01

// Net IOCTL Commands - Generic.
#define DRV_SETMODE         0x00
#define DRV_CHKBUF          0x01
#define DRV_LINKSTAT        0x02
#define DRV_MACCTRL         0x03

#define DRV_PORT_CONTROL    0xf0
#define DRV_SET_HW_INFO     0xf1
#define DRV_DISCARD_EAPOL   0xf2
#define DRV_TEST_EAPOL      0xf3

// Ether Types in host byte order
#define ETHER_TYPE_EAPOL  0x8e88
#define ETHER_TYPE_IP     0x0008
#define ETHER_TYPE_ARP    0x0608

// Preview packet sizes
#define MIN_PACKET_SIZE   42
#define PREVIEW_SIZE      44

/****************************************************************************
 *
 *                               DATA STRUCTURES
 *
 ****************************************************************************/
typedef WORD (*PTFw)(void);
typedef WORD *(*PTFwp)(void);
typedef int  (* PTFi)(BYTE far *, WORD);
typedef BYTE *(* PTFb)(WORD, WORD);

/* Message Header Stucture */
typedef struct BHDR {
  unsigned portNum:4;
  unsigned portRemainder:4;
	BYTE flags;
	WORD len;
} BHDR;

/* Static Driver Specific Information - compile time*/
typedef struct driver_entry_t
{
	WORD type;
	BYTE *name;
	int  (*chk)(void);
	int  (*ini)(PTFwp funtbl[], WORD *iocb);
	int  (*ioc)(int i, BYTE *b);
	int  (*snd)(BYTE *buf, int len);
	int  priority;
  int  (*poff)(void);   // function added during 6.1 for getting status from phy
} DSTR;

/* Driver Instance Control Block */
typedef struct drv_iocb_t
{
  WORD portNum; 
  WORD NWTyp;
  WORD STIME;
  BYTE lPortNum;               // lportNum used as combo with dp->type to get eg. ND0, NW0, ND1
  BYTE SBFLAG;
  BYTE *SBufs[NUM_TXBUFS];     // 2 Tx Bufs per network interface.
  DSTR *dp;
  NET_HW_T *hw;
  unsigned adminStatus:2;      // interface status at runtime (0 = down; 1 = up)
  unsigned portControl:1;      // port control bit (0 = not authorized; 1 = authorized)
  unsigned unused:5;
} DRV_IOCB;

/* Work Area for global reference to the DRV_IOCB */
typedef struct netdrv_cb_t
{
  WORD numPorts;
  DRV_IOCB *drv[MAX_PORTS];
} NETDRV_CB;

enum ioctl_commands { 
  MLME_SCAN_request=0x10,                 
  MLME_ASSOCIATE_request,
  MLME_DISASSOCIATE_request,
  MLME_DELETEKEYS_request,
  MLME_SETKEYS_request,
//  MLME_GetAssociationInfo,
  MM_Scan_request,                 // scan the air and print the list
  MM_Associate_request,             // associate to particular AP in the scan list
  MM_Set_Power,
  MM_ContTX,
  MM_ContRX,
  MM_Print_Status,
  MM_KeyToggle
  };




#endif