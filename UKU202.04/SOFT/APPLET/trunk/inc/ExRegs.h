/* +++=>>> * %n   Edition: %v  Last changed: %f  By: %w */
/* DstExStd.h Edition: 1  Last changed: 10-12-2002,12:00:00  By: WESDO */
/* +++=>>> '%l' */
/* Currently extracted for edit by: '***_NOBODY_***' */
/*
   Copyright (C) 2002 By Lantronix
   15353 Barranca Parkway
   Irvine, California 92618
   http://www.Lantronix.com
   949.453.3990

   DstExStd.h  This header file defines the "standard" constant
               values used for all DSTni-EX module code development.


   This software is furnished under a license and may be used
   and copied only in accordance with the terms of such license
   and with the inclusion of the above copyright notice.
   This software or any other copies thereof may not be provided
   or otherwise made available to any other person.  No title to
   and ownership of the software is hereby transferred.

   The information in this software is subject to change without
   notice and should not be construed as a commitment by Lantronix.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

  MODIFICATION HISTORY:

DD-MON-YYYY    INITIALS    Comment

10-DEC-2002    WD          Author, creation. Revision 1.00

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#if !defined(DSTEXSTD_H)
#define DSTEXSTD_H

//#include "DstExConfig.h"

#if !defined(DST_REG_PCB)
	#define DST_REG_PCB		0xFF00
#endif

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Peripheral Control Block register addresses
** Base address defined in DstLxConfig.h
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
/* System control and configuration registers*/
#define DST_REG_RELREG     (DST_REG_PCB + 0x00FE) /* Relocation Register     */
#define DST_REG_DCR        (DST_REG_PCB + 0x00F8) /* DSTni Configuration Reg */
#define DST_REG_RCR        (DST_REG_PCB + 0x00F6) /* Reset Configuration Reg */
#define DST_REG_PRL        (DST_REG_PCB + 0x00F4) /* Processor Release Reg   */
#define DST_REG_AUXCON     (DST_REG_PCB + 0x00F2) /* Auxiliary Configuarion  */
#define DST_REG_SYSCON     (DST_REG_PCB + 0x00F0) /* System Configuration    */

/* Chip select registers */
#define DST_REG_CAR        (DST_REG_PCB + 0x00AE) /* Checksum Adder           */
#define DST_REG_CDR        (DST_REG_PCB + 0x00AC) /* Checksum Data            */
#define DST_REG_PRCS       (DST_REG_PCB + 0x00AA) /* Page Chip Select         */
#define DST_REG_MPCS       (DST_REG_PCB + 0x00A8) /* Memory / Peripheral Ctrl */
#define DST_REG_MMCS       (DST_REG_PCB + 0x00A6) /* Mid Memory Chip Select   */
#define DST_REG_PACS       (DST_REG_PCB + 0x00A4) /* Peripheral Chip Select   */
#define DST_REG_LMCS       (DST_REG_PCB + 0x00A2) /* Lower Memeory Chip Select*/
#define DST_REG_UMCS       (DST_REG_PCB + 0x00A0) /* Upper Memory Chip Select */

/* Phase lock loop, CPU clock and SPI control */
#define DST_REG_PLLCLKUSB  (DST_REG_PCB + 0x006E)

/* Watchdog timer register */
#define DST_REG_WDTCON     (DST_REG_PCB + 0x006C)

/* Random number generator / Linear counter */
#define DST_REG_RNG        (DST_REG_PCB + 0x006A)

/* SDRAM control */
#define DST_REG_SDRAMCTRL  (DST_REG_PCB + 0x0068) /* Control register */
#define DST_REG_REFMAX     (DST_REG_PCB + 0x0064) /* Refresh maxcount */

/* Timer 2 registers */
#define DST_REG_T2CON      (DST_REG_PCB + 0x0066) /* Control             */
#define DST_REG_T2CMPA     (DST_REG_PCB + 0x0062) /* Compare A           */
                                                  /* No Compare B for T2 */
#define DST_REG_T2CNT      (DST_REG_PCB + 0x0060) /* Count               */

/* Timer 1 Registers */
#define DST_REG_T1CON      (DST_REG_PCB + 0x005E) /* Control   */
#define DST_REG_T1CMPB     (DST_REG_PCB + 0x005C) /* Compare B */
#define DST_REG_T1CMPA     (DST_REG_PCB + 0x005A) /* Compare A */
#define DST_REG_T1CNT      (DST_REG_PCB + 0x0058) /* Count     */

/* Timer 0 Registers */
#define DST_REG_T0CON      (DST_REG_PCB + 0x0056) /* Control   */
#define DST_REG_T0CMPB     (DST_REG_PCB + 0x0054) /* Compare B */
#define DST_REG_T0CMPA     (DST_REG_PCB + 0x0052) /* Compare A */
#define DST_REG_T0CNT      (DST_REG_PCB + 0x0050) /* Count     */

/* Interrupt controller Master Mode registers */
#define DST_REG_MAC1CON     (DST_REG_PCB + 0x004C) /* MAC1 interrupt control  */
#define DST_REG_DMA3CON     (DST_REG_PCB + 0x004A) /* DMA 3 interrupt control */
#define DST_REG_DMA2CON     (DST_REG_PCB + 0x0048) /* DMA 2 interrupt control */
#define DST_REG_SP3CON      (DST_REG_PCB + 0x0046) /* SP3 interrupt control   */
#define DST_REG_SP0CON      (DST_REG_PCB + 0x0044) /* Serial Port 0 int ctrl  */
#define DST_REG_SP1CON      (DST_REG_PCB + 0x0042) /* Serial Port 1 int ctrl  */
#define DST_REG_SP2CON      (DST_REG_PCB + 0x0040) /* Serial Port 2 int ctrl  */
#define DST_REG_I3CON       (DST_REG_PCB + 0x003E) /* INT3 interrupt control  */
#define DST_REG_USBCON      (DST_REG_PCB + 0x003E) /* USB interrupt control   */
#define DST_REG_SPICON      (DST_REG_PCB + 0x003C) /* SPI interrupt control   */
#define DST_REG_I2CCON      (DST_REG_PCB + 0x003C) /* I2C interrupt control   */
#define DST_REG_I1CON       (DST_REG_PCB + 0x003A) /* INT1 interrupt control  */
#define DST_REG_CANCON      (DST_REG_PCB + 0x003A) /* CAN 1 & 0 int control   */
#define DST_REG_MAC0CON     (DST_REG_PCB + 0x0038) /* MAC0 interrupt control  */
#define DST_REG_DMA1CON     (DST_REG_PCB + 0x0036) /* DMA 1 interrupt control */
#define DST_REG_DMA0CON     (DST_REG_PCB + 0x0034) /* DMA 0 interrupt control */
#define DST_REG_TCUCON      (DST_REG_PCB + 0x0032) /* Timer/Counter Unit      */
#define DST_REG_INTSTS      (DST_REG_PCB + 0x0030) /* Interrupt Status        */
#define DST_REG_REQST       (DST_REG_PCB + 0x002E) /* Interrupt Request       */
#define DST_REG_INSERV      (DST_REG_PCB + 0x002C) /* In-Service              */
#define DST_REG_PRIMSK      (DST_REG_PCB + 0x002A) /* Priority mask           */
#define DST_REG_IMASK       (DST_REG_PCB + 0x0028) /* Interrupt mask          */
#define DST_REG_POLLST      (DST_REG_PCB + 0x0026) /* Interrupt poll status   */
#define DST_REG_POLL        (DST_REG_PCB + 0x0024) /* Interrupt poll          */
#define DST_REG_EOI         (DST_REG_PCB + 0x0022) /* End Of Interrupt        */

/* DMA 0 control registers */
#define DST_REG_D0CON      (DST_REG_PCB + 0x00CA) /* Control */
#define DST_REG_D0TC       (DST_REG_PCB + 0x00C8) /* Terminal Count */
#define DST_REG_D0DSTH     (DST_REG_PCB + 0x00C6) /* Destination hi byte */
#define DST_REG_D0DSTL     (DST_REG_PCB + 0x00C4) /* Destination lo byte */
#define DST_REG_D0SRCH     (DST_REG_PCB + 0x00C2) /* Source hi byte */
#define DST_REG_D0SRCL     (DST_REG_PCB + 0x00C0) /* Source lo byte */

/* DMA 1 control registers */
#define DST_REG_D1CON      (DST_REG_PCB + 0x00DA) /* Control */
#define DST_REG_D1TC       (DST_REG_PCB + 0x00D8) /* Terminal Count */
#define DST_REG_D1DSTH     (DST_REG_PCB + 0x00D6) /* Destination hi byte */
#define DST_REG_D1DSTL     (DST_REG_PCB + 0x00D4) /* Destination lo byte */
#define DST_REG_D1SRCH     (DST_REG_PCB + 0x00D2) /* Source hi byte */
#define DST_REG_D1SRCL     (DST_REG_PCB + 0x00D0) /* Source lo byte */

/* DMA 2 control registers */
#define DST_REG_D2CON       (DST_REG_PCB + 0x009A)   /* Control */
#define DST_REG_D2TC        (DST_REG_PCB + 0x0098)   /* Terminal Count */
#define DST_REG_D2DSTH      (DST_REG_PCB + 0x0096)   /* Destination hi byte */
#define DST_REG_D2DSTL      (DST_REG_PCB + 0x0094)   /* Destination lo byte */
#define DST_REG_D2SRCH      (DST_REG_PCB + 0x0092)   /* Source hi byte */
#define DST_REG_D2SRCL      (DST_REG_PCB + 0x0090)   /* Source lo byte */

/* DMA 3 control registers */
#define DST_REG_D3CON       (DST_REG_PCB + 0x00BA)   /* Control */
#define DST_REG_D3TC        (DST_REG_PCB + 0x00B8)   /* Terminal Count */
#define DST_REG_D3DSTH      (DST_REG_PCB + 0x00B6)   /* Destination hi byte */
#define DST_REG_D3DSTL      (DST_REG_PCB + 0x00B4)   /* Destination lo byte */
#define DST_REG_D3SRCH      (DST_REG_PCB + 0x00B2)   /* Source hi byte */
#define DST_REG_D3SRCL      (DST_REG_PCB + 0x00B0)   /* Source lo byte */

/* Serial Port 3 registers */
#define DST_REG_SP3AUX      (DST_REG_PCB + 0x00EA)   /* Auxilary control */
#define DST_REG_SP3BAUD     (DST_REG_PCB + 0x00E8)   /* Baud rate divisor */
#define DST_REG_SP3RD       (DST_REG_PCB + 0x00E6)   /* Receive Data */
#define DST_REG_SP3TD       (DST_REG_PCB + 0x00E4)   /* Transmit Data */
#define DST_REG_SP3STS      (DST_REG_PCB + 0x00E2)   /* Status */
#define DST_REG_SP3CT       (DST_REG_PCB + 0x00E0)   /* Control */

/* Serial Port 0 registers */
#define DST_REG_SP0AUX      (DST_REG_PCB + 0x008A)   /* Auxilary control */
#define DST_REG_SP0BAUD     (DST_REG_PCB + 0x0088)   /* Baud rate divisor */
#define DST_REG_SP0RD       (DST_REG_PCB + 0x0086)   /* Receive Data */
#define DST_REG_SP0TD       (DST_REG_PCB + 0x0084)   /* Transmit Data */
#define DST_REG_SP0STS      (DST_REG_PCB + 0x0082)   /* Status */
#define DST_REG_SP0CT       (DST_REG_PCB + 0x0080)   /* Control */

/* Serial Port 1 registers */
#define DST_REG_SP1AUX      (DST_REG_PCB + 0x001A)   /* RS422/RS485 Control */
#define DST_REG_SP1BAUD     (DST_REG_PCB + 0x0018)   /* Baud rate divisor */
#define DST_REG_SP1RD       (DST_REG_PCB + 0x0016)   /* Receive Data */
#define DST_REG_SP1TD       (DST_REG_PCB + 0x0014)   /* Transmit Data */
#define DST_REG_SP1STS      (DST_REG_PCB + 0x0012)   /* Status */
#define DST_REG_SP1CT       (DST_REG_PCB + 0x0010)   /* Control */

/* Serial Port 2 registers */
#define DST_REG_SP2AUX      (DST_REG_PCB + 0x000A)   /* Auxilary control */
#define DST_REG_SP2BAUD     (DST_REG_PCB + 0x0008)   /* Baud rate divisor */
#define DST_REG_SP2RD       (DST_REG_PCB + 0x0006)   /* Receive Data */
#define DST_REG_SP2TD       (DST_REG_PCB + 0x0004)   /* Transmit Data */
#define DST_REG_SP2STS      (DST_REG_PCB + 0x0002)   /* Status */
#define DST_REG_SP2CT       (DST_REG_PCB + 0x0000)   /* Control */

/* LED Control Register */
#define DST_REG_LEDC        (DST_REG_PCB + 0x007E)

/* Programmable I/O Bank 1 (bits 31-16) registers */
#define DST_REG_PIODATA1    (DST_REG_PCB + 0x007A)   /* Input / Output Data */
#define DST_REG_PIODIR1     (DST_REG_PCB + 0x0078)   /* Direction Select */
#define DST_REG_PIOMODE1    (DST_REG_PCB + 0x0076)   /* Mode Select */

/* Programmable I/O Bank 0 (bits 15-0) registers */
#define DST_REG_PIODATA0    (DST_REG_PCB + 0x0074)   /* Input / Output Data */
#define DST_REG_PIODIR0     (DST_REG_PCB + 0x0072)   /* Direction Select */
#define DST_REG_PIOMODE0    (DST_REG_PCB + 0x0070)   /* Mode Select */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Peripheral device I/O addresses
** These are the peripheral devices not part of the Peripheral Control Block
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Ethernet Controller Registers
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define DST_ETH0_BASE        0x9000
#define DST_ETH1_BASE        0x9100

#define DST_REG_ETH0_RDP     (DST_ETH0_BASE + 0x0010)  /* Register Data Port */
#define DST_REG_ETH0_RAP     (DST_ETH0_BASE + 0x0012)  /* Register Access Port */
#define DST_REG_ETH0_RST     (DST_ETH0_BASE + 0x0014)  /* Reset Port */
#define DST_REG_ETH0_MII     (DST_ETH0_BASE + 0x0018)  /* MII Port */

#define DST_REG_ETH1_RDP     (DST_ETH1_BASE + 0x0010)  /* Register Data Port */
#define DST_REG_ETH1_RAP     (DST_ETH1_BASE + 0x0012)  /* Register Access Port */
#define DST_REG_ETH1_RST     (DST_ETH1_BASE + 0x0014)  /* Reset Port */
#define DST_REG_ETH1_MII     (DST_ETH1_BASE + 0x0018)  /* MII Port */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** CAN 0 Registers
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define DST_CAN0_BASE             0xA800
#define DST_CAN1_BASE             0xA900

/* Transmit message 0 */
#define DST_REG_CAN0_TX0_ID28_13  (DST_CAN0_BASE + 0x00)  /* Hi ID bits */
#define DST_REG_CAN0_TX0_ID12_00  (DST_CAN0_BASE + 0x02)  /* Lo ID bits */
#define DST_REG_CAN0_TX0_D63_48   (DST_CAN0_BASE + 0x04)  /* Hi Data bits */
#define DST_REG_CAN0_TX0_D47_32   (DST_CAN0_BASE + 0x06)  /* .... */
#define DST_REG_CAN0_TX0_D31_16   (DST_CAN0_BASE + 0x08)  /* .... */
#define DST_REG_CAN0_TX0_D15_00   (DST_CAN0_BASE + 0x0A)  /* Lo Data bits */
#define DST_REG_CAN0_TX0_LEN      (DST_CAN0_BASE + 0x0C)  /* Length */
#define DST_REG_CAN0_TX0_CTRL     (DST_CAN0_BASE + 0x0E)  /* Control */

/* Transmit message 1 */
#define DST_REG_CAN0_TX1_ID28_13  (DST_CAN0_BASE + 0x10)  /* Hi ID bits */
#define DST_REG_CAN0_TX1_ID12_00  (DST_CAN0_BASE + 0x12)  /* Lo ID bits */
#define DST_REG_CAN0_TX1_D63_48   (DST_CAN0_BASE + 0x14)  /* Hi Data bits */
#define DST_REG_CAN0_TX1_D47_32   (DST_CAN0_BASE + 0x16)  /* .... */
#define DST_REG_CAN0_TX1_D31_16   (DST_CAN0_BASE + 0x18)  /* .... */
#define DST_REG_CAN0_TX1_D15_00   (DST_CAN0_BASE + 0x1A)  /* Lo Data bits */
#define DST_REG_CAN0_TX1_LEN      (DST_CAN0_BASE + 0x1C)  /* Length */
#define DST_REG_CAN0_TX1_CTRL     (DST_CAN0_BASE + 0x1E)  /* Control */

/* Transmit message 2 */
#define DST_REG_CAN0_TX2_ID28_13  (DST_CAN0_BASE + 0x20)  /* Hi ID bits */
#define DST_REG_CAN0_TX2_ID12_00  (DST_CAN0_BASE + 0x22)  /* Lo ID bits */
#define DST_REG_CAN0_TX2_D63_48   (DST_CAN0_BASE + 0x24)  /* Hi Data bits */
#define DST_REG_CAN0_TX2_D47_32   (DST_CAN0_BASE + 0x26)  /* .... */
#define DST_REG_CAN0_TX2_D31_16   (DST_CAN0_BASE + 0x28)  /* .... */
#define DST_REG_CAN0_TX2_D15_00   (DST_CAN0_BASE + 0x2A)  /* Lo Data bits */
#define DST_REG_CAN0_TX2_LEN      (DST_CAN0_BASE + 0x2C)  /* Length */
#define DST_REG_CAN0_TX2_CTRL     (DST_CAN0_BASE + 0x2E)  /* Control */

/* Receive */
#define DST_REG_CAN0_RX_ID28_13   (DST_CAN0_BASE + 0x30)  /* Hi ID bit */
#define DST_REG_CAN0_RX_ID12_00   (DST_CAN0_BASE + 0x32)  /* Lo ID bits */
#define DST_REG_CAN0_RX_D63_48    (DST_CAN0_BASE + 0x34)  /* Hi Data bits */
#define DST_REG_CAN0_RX_D47_32    (DST_CAN0_BASE + 0x36)  /* .... */
#define DST_REG_CAN0_RX_D31_16    (DST_CAN0_BASE + 0x38)  /* .... */
#define DST_REG_CAN0_RX_D15_00    (DST_CAN0_BASE + 0x3A)  /* Lo Data bits */
#define DST_REG_CAN0_RX_LEN       (DST_CAN0_BASE + 0x3C)  /* Length */
#define DST_REG_CAN0_RX_FLAGS     (DST_CAN0_BASE + 0x3E)  /* Control */

/* Status/IRQ registers */
#define DST_REG_CAN0_ERR_CNT      (DST_CAN0_BASE + 0x40)  /* Rx/Tx err count  */
#define DST_REG_CAN0_ERR_STAT_CNT (DST_CAN0_BASE + 0x42)  /* Err Status count */
#define DST_REG_CAN0_MSG_LEVEL    (DST_CAN0_BASE + 0x44)  /* Msg Level Thresh */
#define DST_REG_CAN0_IRQ_FLAGS    (DST_CAN0_BASE + 0x46)  /* Interrupt Flags */
#define DST_REG_CAN0_IRQ_ENABLE   (DST_CAN0_BASE + 0x48)  /* Interrupt enable */

/* CAN Configuration */
#define DST_REG_CAN0_MODE         (DST_CAN0_BASE + 0x4A)  /* Operating mode */
#define DST_REG_CAN0_BITRATE      (DST_CAN0_BASE + 0x4C)  /* */
#define DST_REG_CAN0_TIMING       (DST_CAN0_BASE + 0x4E)  /* */

/* Acceptance Mask and Code registers */
#define DST_REG_CAN0_FILTER_ENA   (DST_CAN0_BASE + 0x50)  /* Filter enables */

#define DST_REG_CAN0_AMR0_ID28_13 (DST_CAN0_BASE + 0x52)  /* Acceptance mask 0*/
#define DST_REG_CAN0_AMR0_ID12_00 (DST_CAN0_BASE + 0x54)  /* .. */
#define DST_REG_CAN0_AMR0_D63_48  (DST_CAN0_BASE + 0x56)  /* .. */
#define DST_REG_CAN0_ACR0_ID28_13 (DST_CAN0_BASE + 0x58)  /* Acceptance code 0*/
#define DST_REG_CAN0_ACR0_ID12_00 (DST_CAN0_BASE + 0x5A)  /* .. */
#define DST_REG_CAN0_ACR0_D63_48  (DST_CAN0_BASE + 0x5C)  // ..

#define DST_REG_CAN0_AMR1_ID28_13 (DST_CAN0_BASE + 0x5E)  /* Acceptance mask 1*/
#define DST_REG_CAN0_AMR1_ID12_00 (DST_CAN0_BASE + 0x60)  /* .. */
#define DST_REG_CAN0_AMR1_D63_48  (DST_CAN0_BASE + 0x62)  /* .. */
#define DST_REG_CAN0_ACR1_ID28_13 (DST_CAN0_BASE + 0x64)  /* Acceptance code 1*/
#define DST_REG_CAN0_ACR1_ID12_00 (DST_CAN0_BASE + 0x66)  /* .. */
#define DST_REG_CAN0_ACR1_D63_48  (DST_CAN0_BASE + 0x68)  /* .. */

#define DST_REG_CAN0_AMR2_ID28_13 (DST_CAN0_BASE + 0x6A)  /* Acceptance mask 2*/
#define DST_REG_CAN0_AMR2_ID12_00 (DST_CAN0_BASE + 0x6C)  /* .. */
#define DST_REG_CAN0_AMR2_D63_48  (DST_CAN0_BASE + 0x6E)  /* .. */
#define DST_REG_CAN0_ACR2_ID28_13 (DST_CAN0_BASE + 0x70)  /* Acceptance code 2*/
#define DST_REG_CAN0_ACR2_ID12_00 (DST_CAN0_BASE + 0x72)  /* .. */
#define DST_REG_CAN0_ACR2_D63_48  (DST_CAN0_BASE + 0x74)  /* .. */

/* Analysis registers */
#define DST_REG_CAN0_ALCR         (DST_CAN0_BASE + 0x76)  /* Arb. Lost Cap.Reg*/
#define DST_REG_CAN0_ECR          (DST_CAN0_BASE + 0x78)  /* Error Capture Reg*/
#define DST_REG_CAN0_FRR          (DST_CAN0_BASE + 0x7A)  /* Frame Refer Reg  */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** CAN 1 Registers
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/* Transmit message 0 */
#define DST_REG_CAN1_TX0_ID28_13  (DST_CAN1_BASE + 0x00)  /* Hi ID bits */
#define DST_REG_CAN1_TX0_ID12_00  (DST_CAN1_BASE + 0x02)  /* Lo ID bits */
#define DST_REG_CAN1_TX0_D63_48   (DST_CAN1_BASE + 0x04)  /* Hi Data bits */
#define DST_REG_CAN1_TX0_D47_32   (DST_CAN1_BASE + 0x06)  /* .... */
#define DST_REG_CAN1_TX0_D31_16   (DST_CAN1_BASE + 0x08)  /* .... */
#define DST_REG_CAN1_TX0_D15_00   (DST_CAN1_BASE + 0x0A)  /* Lo Data bits */
#define DST_REG_CAN1_TX0_LEN      (DST_CAN1_BASE + 0x0C)  /* Length */
#define DST_REG_CAN1_TX0_CTRL     (DST_CAN1_BASE + 0x0E)  /* Control */

/* Transmit message 1 */
#define DST_REG_CAN1_TX1_ID28_13  (DST_CAN1_BASE + 0x10)  /* Hi ID bits */
#define DST_REG_CAN1_TX1_ID12_00  (DST_CAN1_BASE + 0x12)  /* Lo ID bits */
#define DST_REG_CAN1_TX1_D63_48   (DST_CAN1_BASE + 0x14)  /* Hi Data bits */
#define DST_REG_CAN1_TX1_D47_32   (DST_CAN1_BASE + 0x16)  /* .... */
#define DST_REG_CAN1_TX1_D31_16   (DST_CAN1_BASE + 0x18)  /* .... */
#define DST_REG_CAN1_TX1_D15_00   (DST_CAN1_BASE + 0x1A)  /* Lo Data bits */
#define DST_REG_CAN1_TX1_LEN      (DST_CAN1_BASE + 0x1C)  /* Length */
#define DST_REG_CAN1_TX1_CTRL     (DST_CAN1_BASE + 0x1E)  /* Control */

/* Transmit message 2 */
#define DST_REG_CAN1_TX2_ID28_13  (DST_CAN1_BASE + 0x20)  /* Hi ID bits */ 
#define DST_REG_CAN1_TX2_ID12_00  (DST_CAN1_BASE + 0x22)  /* Lo ID bits */
#define DST_REG_CAN1_TX2_D63_48   (DST_CAN1_BASE + 0x24)  /* Hi Data bits */
#define DST_REG_CAN1_TX2_D47_32   (DST_CAN1_BASE + 0x26)  /* .... */
#define DST_REG_CAN1_TX2_D31_16   (DST_CAN1_BASE + 0x28)  /* .... */
#define DST_REG_CAN1_TX2_D15_00   (DST_CAN1_BASE + 0x2A)  /* Lo Data bits */
#define DST_REG_CAN1_TX2_LEN      (DST_CAN1_BASE + 0x2C)  /* Length */
#define DST_REG_CAN1_TX2_CTRL     (DST_CAN1_BASE + 0x2E)  /* Control */

/* Receive */
#define DST_REG_CAN1_RX_ID28_13   (DST_CAN1_BASE + 0x30)  /* Hi ID bit */
#define DST_REG_CAN1_RX_ID12_00   (DST_CAN1_BASE + 0x32)  /* Lo ID bits */
#define DST_REG_CAN1_RX_D63_48    (DST_CAN1_BASE + 0x34)  /* Hi Data bits */
#define DST_REG_CAN1_RX_D47_32    (DST_CAN1_BASE + 0x36)  /* .... */
#define DST_REG_CAN1_RX_D31_16    (DST_CAN1_BASE + 0x38)  /* .... */
#define DST_REG_CAN1_RX_D15_00    (DST_CAN1_BASE + 0x3A)  /* Lo Data bits */
#define DST_REG_CAN1_RX_LEN       (DST_CAN1_BASE + 0x3C)  /* Length */
#define DST_REG_CAN1_RX_FLAGS     (DST_CAN1_BASE + 0x3E)  /* Control */

/* Status/IRQ registers */
#define DST_REG_CAN1_TX_ERR_CNT   (DST_CAN1_BASE + 0x40)  /* Rx/Tx err count  */
#define DST_REG_CAN1_ERR_STAT_CNT (DST_CAN1_BASE + 0x42)  /* Error Stat count */
#define DST_REG_CAN1_MSG_LEVEL    (DST_CAN1_BASE + 0x44)  /* Msg Level Thresh */
#define DST_REG_CAN1_IRQ_FLAGS    (DST_CAN1_BASE + 0x46)  /* Interrupt Flags  */
#define DST_REG_CAN1_IRQ_ENABLE   (DST_CAN1_BASE + 0x48)  /* Interrupt enable */

/* CAN Configuration */
#define DST_REG_CAN1_MODE         (DST_CAN1_BASE + 0x4A)  /* Operating mode */
#define DST_REG_CAN1_BITRATE      (DST_CAN1_BASE + 0x4C)  /* */
#define DST_REG_CAN1_TIMING       (DST_CAN1_BASE + 0x4E)  /* */

/* Acceptance mask and code registers */
#define DST_REG_CAN1_FILTER_ENA   (DST_CAN1_BASE + 0x50)  /* Filter enables */

#define DST_REG_CAN1_AMR0_ID28_13 (DST_CAN1_BASE + 0x52)  /* Acceptance mask 0*/
#define DST_REG_CAN1_AMR0_ID12_00 (DST_CAN1_BASE + 0x54)  /* .. */
#define DST_REG_CAN1_AMR0_D63_48  (DST_CAN1_BASE + 0x56)  /* .. */
#define DST_REG_CAN1_ACR0_ID28_13 (DST_CAN1_BASE + 0x58)  /* Acceptance code 0*/
#define DST_REG_CAN1_ACR0_ID12_00 (DST_CAN1_BASE + 0x5A)  /* .. */
#define DST_REG_CAN1_ACR0_D63_48  (DST_CAN1_BASE + 0x5C)  /* .. */

#define DST_REG_CAN1_AMR1_ID28_13 (DST_CAN1_BASE + 0x5E)  /* Acceptance mask 1*/
#define DST_REG_CAN1_AMR1_ID12_00 (DST_CAN1_BASE + 0x60)  /* .. */
#define DST_REG_CAN1_AMR1_D63_48  (DST_CAN1_BASE + 0x62)  /* .. */
#define DST_REG_CAN1_ACR1_ID28_13 (DST_CAN1_BASE + 0x64)  /* Acceptance code 1*/
#define DST_REG_CAN1_ACR1_ID12_00 (DST_CAN1_BASE + 0x66)  /* .. */
#define DST_REG_CAN1_ACR1_D63_48  (DST_CAN1_BASE + 0x68)  /* .. */

#define DST_REG_CAN1_AMR2_ID28_13 (DST_CAN1_BASE + 0x6A)  /* Acceptance mask 2*/
#define DST_REG_CAN1_AMR2_ID12_00 (DST_CAN1_BASE + 0x6C)  /* .. */
#define DST_REG_CAN1_AMR2_D63_48  (DST_CAN1_BASE + 0x6E)  /* .. */
#define DST_REG_CAN1_ACR2_ID28_13 (DST_CAN1_BASE + 0x70)  /* Acceptance code 2*/
#define DST_REG_CAN1_ACR2_ID12_00 (DST_CAN1_BASE + 0x72)  /* .. */
#define DST_REG_CAN1_ACR2_D63_48  (DST_CAN1_BASE + 0x74)  /* .. */

/* Analysis registers */
#define DST_REG_CAN1_ALCR         (DST_CAN1_BASE + 0x76)  /* Arb. Lost Cap Reg*/
#define DST_REG_CAN1_ECR          (DST_CAN1_BASE + 0x78)  /* Error Capture Reg*/
#define DST_REG_CAN1_FRR          (DST_CAN1_BASE + 0x7A)  /* Frame Ref. Reg. */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Serial Peripheral Inteface registers
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define DST_SPI0_BASE       0xB800

#define DST_REG_SPICTRHI    (DST_SPI0_BASE + 0x0A)   /* High byte of counter */
#define DST_REG_SPICTRLO    (DST_SPI0_BASE + 0x08)   /* Low byte of counter */
#define DST_REG_SPISSEL     (DST_SPI0_BASE + 0x06)   /* Slave Select */
#define DST_REG_SPISTAT     (DST_SPI0_BASE + 0x04)   /* Status */
#define DST_REG_SPICTRL     (DST_SPI0_BASE + 0x02)   /* Control */
#define DST_REG_SPIDATA     (DST_SPI0_BASE + 0x00)   /* Write / Read data */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** USB Controller Registers
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define DST_USB0_BASE        0x9800

#define DST_REG_USB_INT_STAT	(DST_USB0_BASE + 0x00)	/* Interrupt status */
#define DST_REG_USB_INT_ENB 	(DST_USB0_BASE + 0x01)	/* Interrupt enable */
#define DST_REG_USB_ERR_STAT	(DST_USB0_BASE + 0x02)	/* Error Int. status */
#define DST_REG_USB_ERR_ENB 	(DST_USB0_BASE + 0x03)	/* Error Int. enable */
#define DST_REG_USB_STAT    	(DST_USB0_BASE + 0x04)	/* Status */
#define DST_REG_USB_CTL     	(DST_USB0_BASE + 0x05)	/* Control */
#define DST_REG_USB_ADDR    	(DST_USB0_BASE + 0x06)	/* Address */
#define DST_REG_USB_BDT_PAGE	(DST_USB0_BASE + 0x07)	/* Buf descriptor table */
#define DST_REG_USB_FRM_NUML	(DST_USB0_BASE + 0x08)	/* Frame number 7:0 */
#define DST_REG_USB_FRM_NUMH	(DST_USB0_BASE + 0x09)	/* Frame number 10:8 */
#define DST_REG_USB_TOKEN   	(DST_USB0_BASE + 0x0A)	/* Token */
#define DST_REG_USB_SOF_THLDL (DST_USB0_BASE + 0x0B)	/* SOF Threshold 15:8 */
#define DST_REG_USB_SOF_THLDH (DST_USB0_BASE + 0x0C)	/* SOF Threshold 7:0 */

#define DST_REG_USB_ENDPT0  	(DST_USB0_BASE + 0x10)	/* Endpoint 0 control */
#define DST_REG_USB_ENDPT1  	(DST_USB0_BASE + 0x11)	/* Endpoint 1 control */
#define DST_REG_USB_ENDPT2  	(DST_USB0_BASE + 0x12)	/* Endpoint 2 control */
#define DST_REG_USB_ENDPT3  	(DST_USB0_BASE + 0x13)	/* Endpoint 3 control */
#define DST_REG_USB_ENDPT4  	(DST_USB0_BASE + 0x14)	/* Endpoint 4 control */
#define DST_REG_USB_ENDPT5  	(DST_USB0_BASE + 0x15)	/* Endpoint 5 control */
#define DST_REG_USB_ENDPT6  	(DST_USB0_BASE + 0x16)	/* Endpoint 6 control */
#define DST_REG_USB_ENDPT7  	(DST_USB0_BASE + 0x17)	/* Endpoint 7 control */
#define DST_REG_USB_ENDPT8  	(DST_USB0_BASE + 0x18)	/* Endpoint 8 control */
#define DST_REG_USB_ENDPT9  	(DST_USB0_BASE + 0x19)	/* Endpoint 9 control */
#define DST_REG_USB_ENDPT10 	(DST_USB0_BASE + 0x1A)	/* Endpoint 10 control */
#define DST_REG_USB_ENDPT11 	(DST_USB0_BASE + 0x1B)	/* Endpoint 11 control */
#define DST_REG_USB_ENDPT12 	(DST_USB0_BASE + 0x1C)	/* Endpoint 12 control */
#define DST_REG_USB_ENDPT13 	(DST_USB0_BASE + 0x1D)	/* Endpoint 13 control */
#define DST_REG_USB_ENDPT14 	(DST_USB0_BASE + 0x1E)	/* Endpoint 14 control */
#define DST_REG_USB_ENDPT15 	(DST_USB0_BASE + 0x1F)	/* Endpoint 15 control */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** I2C Controller Registers
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define DST_I2C0_BASE        0xD000

#define DST_REG_I2CSRST      (DST_I2C0_BASE + 0x0E)   /* Software Reset */
#define DST_REG_I2CXADDR     (DST_I2C0_BASE + 0x08)   /* Extended Slave Addr */
#define DST_REG_I2CCCR       (DST_I2C0_BASE + 0x06)   /* Clock Control */
#define DST_REG_I2CSTAT      (DST_I2C0_BASE + 0x06)   /* Status */
#define DST_REG_I2CCNTR      (DST_I2C0_BASE + 0x04)   /* Control */
#define DST_REG_I2CDATA      (DST_I2C0_BASE + 0x02)   /* Data */
#define DST_REG_I2CADDR      (DST_I2C0_BASE + 0x00)   /* Address */


/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Register field defines and masks
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/* PCB/RELREG - Relocation Register */
#define DST_RELREG_PCB_IN_MEM 0x1000   /* Puts PCB in memory space */
#define DST_RELREG_PCB_IN_IO  0x0000   /* Puts PCB in I/O space */

/* PRL - Processor Revision Level */
#define DST_PRL_MSK_REV       0xFF00   /* Revision Number */
#define DST_PRL_MSK_CPU       0x00FF   /* CPU number */

/* PCB/AUXCON - Auxiliary Configuration */
#define DST_AUXCON_ENRX3      0x0400   /* Selects ENRX mode SP3 CTS/ENRX pin */
#define DST_AUXCON_DTE3       0x0200   /* Selects RTS mode SP3 RTR/RTS pin */
#define DST_AUXCON_ENRX2      0x0100   /* Selects ENRX mode SP2 CTS/ENRX pin */
#define DST_AUXCON_DTE2       0x0080   /* Selects RTS mode SP2 RTR/RTS pin */
#define DST_AUXCON_ENRX1      0x0040   /* Selects ENRX mode SP1 CTS/ENRX pin */
#define DST_AUXCON_DTE1       0x0020   /* Selects RTS mode SP1 RTR/RTS pin */
#define DST_AUXCON_ENRX0      0x0010   /* Selects ENRX mode SP0 CTS/ENRX pin */
#define DST_AUXCON_DTE0       0x0008   /* Selects RTS mode SP0 RTR/RTS pin */

/* PCB/SYSCON - System Configration (read-only) */
#define DST_SYSCON_MCS0			0x4000	/* Enable MSC0 over entire MCS range */
#define DST_SYSCON_CD			0x0100	/* Disable clock output */

/* DCR - DSTni Configuration Register */
#define DST_DCR_BROMEN			0x4000	/* Boot ROM enabled */
#define DST_DCR_ADDR24			0x2000	/* Extended address mode enabled */
#define DST_DCR_WDOGEN			0x1000	/* Watchdog enabled */
#define DST_DCR_SPIBOOY			0x0800	/* Boot from SPI enabled */
#define DST_DCR_SPIEN			0x0400	/* SPI pins enabled in PIO */
#define DST_DCR_ETHBOOT			0x0200	/* Ethernet boot enabled */
#define DST_DCR_ETHCHAN			0x0100	/* Ethernet channel 1 selected */
#define DST_DCR_BICOLOR			0x0080	/* Using encoded LEDs */
#define DST_DCR_PARBOOT			0x0040	/* Boot from parallel flash enabled */
#define DST_DCR_PHYBYPASS		0x0020	/* Do not access Ethernet PHY via MII */
#define DST_DCR_BYTEMODE		0x0010	/* Select hi/lo byte read */
#define DST_DCR_SERBOOT			0x0008	/* Enable boot via serial port */
#define DST_DCR_SERCHAN			0x0004	/* Select serial port 0 or 1 for boot */
#define DST_DCR_SERSPEED		0x0002	/* Select 9600 baud serial speed */
#define DST_DCR_DEBUG			0x0001	/* Enable boot debug messages */

/* PCB/WDTCON - Watchdog control */
#define DST_WDTCON_ENA        0x8000   /* Enable timer */
#define DST_WDTCON_WRST       0x4000   /* Cause a reset upon timeout */
#define DST_WDTCON_RSTFLAG    0x2000   /* Set if a WD reset has happened */
#define DST_WDTCON_NMIFLAG    0x1000   /* Set if a NMI event occurred */
#define DST_WDTCON_UNLOCK     0x0800	/* Unlock reg for further writes */
#define DST_WDTCON_EXP_10     0x0001   /* Set WDT timer exponent to 10 */
#define DST_WDTCON_EXP_20     0x0002   /* Set WDT timer exponent to 20 */
#define DST_WDTCON_EXP_21     0x0004   /* Set WDT timer exponent to 21 */
#define DST_WDTCON_EXP_22     0x0008   /* Set WDT timer exponent to 22 */
#define DST_WDTCON_EXP_23     0x0010   /* Set WDT timer exponent to 23 */
#define DST_WDTCON_EXP_24     0x0020   /* Set WDT timer exponent to 24 */
#define DST_WDTCON_EXP_25     0x0040   /* Set WDT timer exponent to 25 */
#define DST_WDTCON_EXP_26     0x0080   /* Set WDT timer exponent to 26 */
#define DST_WDTCON_EXP_27     0x0100   /* Set WDT timer exponent to 27 */
#define DST_WDTCON_EXP_28     0x0200   /* Set WDT timer exponent to 28 */
#define DST_WDTCON_EXP_29     0x0400   /* Set WDT timer exponent to 29 */
#define DST_WDTCON_RESET_1    0xAAAA   /* First of 2 reset steps */
#define DST_WDTCON_RESET_2    0x5555   /* Second of 2 reset steps */
#define DST_WDTCON_OPEN_1     0x3333   /* First of 2 open-for-write steps */
#define DST_WDTCON_OPEN_2     0xCCCC   /* Second of 2 open-for-write steps */

/* PCB/T0CON - Timer 0 Control */
#define DST_T0CON_ENABLE      0xC000   /* Enables Timer */
#define DST_T0CON_DISABLE     0x4000   /* Disables Timer */
#define DST_T0CON_INT_ENABLE  0x2000   /* Enable interrupts */
#define DST_T0CON_RIU         0x1000   /* 0 = maxcount A in use,else maxcnt B*/
#define DST_T0CON_MC          0x0020   /* If 1, maxcount has been reached */
#define DST_T0CON_RTG         0x0010   /* Use TMRIN0 to reset count */
#define DST_T0CON_P           0x0008   /* Use Timer 2 as prescale */
#define DST_T0CON_EXT         0x0004   /* Use TMRIN0 as external clock source */
#define DST_T0CON_ALT         0x0002   /* Alternate between Maxcount A and B */
#define DST_T0CON_CONT        0x0001   /* Run in continuous mode */

/* PCB/T1CON - Timer 1 Control */
#define DST_T1CON_ENABLE      0xC000   /* Enables Timer */
#define DST_T1CON_DISABLE     0x4000   /* Disables Timer */
#define DST_T1CON_INT_ENABLE  0x2000   /* Enable interrupts */
#define DST_T1CON_RIU         0x1000   /* 0 = maxcount A in use, else maxcnt B*/
#define DST_T1CON_MC          0x0020   /* If 1, maxcount has been reached */
#define DST_T1CON_RTG         0x0010   /* Use TMRIN0 to reset count */
#define DST_T1CON_P           0x0008   /* Use Timer 2 as prescale */
#define DST_T1CON_EXT         0x0004   /* Use TMRIN0 as external clock source */
#define DST_T1CON_ALT         0x0002   /* Alternate between Maxcount A and B */
#define DST_T1CON_CONT        0x0001   /* Run in continuous mode */

/* PCB/T2CON - Timer 2 Control */
#define DST_T2CON_ENABLE      0xC000   /* Enables Timer */
#define DST_T2CON_DISABLE     0x4000   /* Disables Timer */
#define DST_T2CON_INT_ENABLE  0x2000   /* Enable interrupts */
#define DST_T2CON_MC          0x0020   /* If 1, maxcount has been reached */
#define DST_T2CON_CONT        0x0001   /* Run in continuous mode */

/* PCB/INSERV - Interrupt in-service */
#define DST_INSERV_MAC1       0x4000   /* I6: Ethernet MAC1 */
#define DST_INSERV_DMA3       0x2000   /* DMA channel 3 */
#define DST_INSERV_DMA2       0x1000   /* DMA channel 2 */
#define DST_INSERV_SP3        0x0800   /* I5: serial port 3 */
#define DST_INSERV_INT5       0x0800   /* I5: Extneral INT5 pin */
#define DST_INSERV_SP0        0x0400   /* Serial Port 0 */
#define DST_INSERV_SP1        0x0200   /* Serial Port 1 */
#define DST_INSERV_SP2        0x0100   /* Serial Port 2 */
#define DST_INSERV_USB        0x0080   /* I3: USB */
#define DST_INSERV_INT3       0x0080   /* I3: External INT 3 pin */
#define DST_INSERV_SPI        0x0040   /* I2: SPI */
#define DST_INSERV_I2C        0x0040   /* I2: I2C */
#define DST_INSERV_CAN        0x0020   /* I1: CAN channels 1 and 0 */
#define DST_INSERV_INT1       0x0020   /* I1: External INT1 pin */
#define DST_INSERV_MAC0       0x0010   /* I0: Ethernet MAC0 */
#define DST_INSERV_DMA1       0x0008   /* DMA channel 1 */
#define DST_INSERV_DMA0       0x0004   /* DMA channel 0 */
#define DST_INSERV_TMR        0x0001   /* Timer (0, 1 or 2) */

/* PCB/REQST - Interrupt request */
#define DST_REQST_MAC1        0x4000   /* I6: Ethernet MAC1 */
#define DST_REQST_DMA3       	0x2000   /* DMA channel 3 */
#define DST_REQST_DMA2       	0x1000   /* DMA channel 2 */
#define DST_REQST_SP3        	0x0800   /* I5: serial port 3 */
#define DST_REQST_INT5        0x0800   /* I5: Extneral INT5 pin */
#define DST_REQST_SP0        	0x0400   /* Serial Port 0 */
#define DST_REQST_SP1        	0x0200   /* Serial Port 1 */
#define DST_REQST_SP2        	0x0100   /* Serial Port 2 */
#define DST_REQST_USB        	0x0080   /* I3: USB */
#define DST_REQST_INT3       	0x0080   /* I3: External INT 3 pin */
#define DST_REQST_SPI        	0x0040   /* I2: SPI */
#define DST_REQST_I2C        	0x0040   /* I2: I2C */
#define DST_REQST_CAN        	0x0020   /* I1: CAN channels 1 and 0 */
#define DST_REQST_INT1       	0x0020   /* I1: External INT1 pin */
#define DST_REQST_MAC0       	0x0010   /* I0: Ethernet MAC0 */
#define DST_REQST_DMA1       	0x0008   /* DMA channel 1 */
#define DST_REQST_DMA0       	0x0004   /* DMA channel 0 */
#define DST_REQST_TMR        	0x0001   /* Timer (0, 1 or 2) */

/* PCB/IMASK - Interrupt mask */
#define DST_IMASK_MAC1        0x4000   /* I6: Ethernet MAC1 */
#define DST_IMASK_DMA3       	0x2000   /* DMA channel 3 */
#define DST_IMASK_DMA2       	0x1000   /* DMA channel 2 */
#define DST_IMASK_SP3        	0x0800   /* I5: serial port 3 */
#define DST_REQST_INT5        0x0800   /* I5: Extneral INT5 pin */
#define DST_IMASK_SP0        	0x0400   /* Serial Port 0 */
#define DST_IMASK_SP1        	0x0200   /* Serial Port 1 */
#define DST_IMASK_SP2        	0x0100   /* Serial Port 2 */
#define DST_IMASK_USB        	0x0080   /* I3: USB */
#define DST_IMASK_INT3       	0x0080   /* I3: External INT 3 pin */
#define DST_IMASK_SPI        	0x0040   /* I2: SPI */
#define DST_IMASK_I2C        	0x0040   /* I2: I2C */
#define DST_IMASK_CAN        	0x0020   /* I1: CAN channels 1 and 0 */
#define DST_IMASK_INT1       	0x0020   /* I1: External INT1 pin */
#define DST_IMASK_MAC0       	0x0010   /* I0: Ethernet MAC0 */
#define DST_IMASK_DMA1       	0x0008   /* DMA channel 1 */
#define DST_IMASK_DMA0       	0x0004   /* DMA channel 0 */
#define DST_IMASK_TMR        	0x0001   /* Timer (0, 1 or 2) */
#define DST_IMASK_ALL         0x7FFD   /* Mask all interrupt sources */

/* PCB/PRIMSK - Interrupt priority mask */
#define DST_PRIMSK_L7         0x0007   /* Enable all priority levels (0 - 7) */
#define DST_PRIMSK_L6         0x0006   /* Enable levels 0 through 6 */
#define DST_PRIMSK_L5         0x0005   /* Enable levels 0 through 5 */
#define DST_PRIMSK_L4         0x0004   /* Enable levels 0 through 4 */
#define DST_PRIMSK_L3         0x0003   /* Enable levels 0 through 3 */
#define DST_PRIMSK_L2         0x0002   /* Enable levels 0 through 2 */
#define DST_PRIMSK_L1         0x0001   /* Enable levels 0 through 1 */
#define DST_PRIMSK_L0         0x0000   /* Enable level 0 */

/* PCB/INSTS - Interrupt status */
#define DST_INTSTS_DHLT       0x8000   /* Halts DMA activity when set */
#define DST_INTSTS_TMR2       0x0004   /* Timer 2 is requesting an interrupt */
#define DST_INTSTS_TMR1       0x0002   /* Timer 1 is requesting an interrupt */
#define DST_INTSTS_TMR0       0x0001   /* Timer 0 is requesting an interrupt */

/* PCB/xxxCON - Peripheral interrupt control (timer, serial, dma, spi) */
#define DST_PERCON_MSK        0x0008   /* Mask this interrupt */
#define DST_PERCON_PRI_L7     0x0007   /* Set interrupt priority 7 (lowest) */
#define DST_PERCON_PRI_L6     0x0006   /* Set interrupt priority 6 */
#define DST_PERCON_PRI_L5     0x0005   /* Set interrupt priority 5 */
#define DST_PERCON_PRI_L4     0x0004   /* Set interrupt priority 4 */
#define DST_PERCON_PRI_L3     0x0003   /* Set interrupt priority 3 */
#define DST_PERCON_PRI_L2     0x0002   /* Set interrupt priority 2 */
#define DST_PERCON_PRI_L1     0x0001   /* Set interrupt priority 1 */
#define DST_PERCON_PRI_L0     0x0000   /* Set interrupt priority 0 (highest) */

/* PCB/IxCON - Interrupt 5-0 control */
#define DST_IXCON_LTM         0x0010   /* Select level triggering */
#define DST_IXCON_MSK         0x0008   /* Mask this interrupt */
#define DST_IXCON_PRI_L7      0x0007   /* Set interrupt priority 7 (lowest) */
#define DST_IXCON_PRI_L6      0x0006   /* Set interrupt priority 6 */
#define DST_IXCON_PRI_L5      0x0005   /* Set interrupt priority 5 */
#define DST_IXCON_PRI_L4      0x0004   /* Set interrupt priority 4 */
#define DST_IXCON_PRI_L3      0x0003   /* Set interrupt priority 3 */
#define DST_IXCON_PRI_L2      0x0002   /* Set interrupt priority 2 */
#define DST_IXCON_PRI_L1      0x0001   /* Set interrupt priority 1 */
#define DST_IXCON_PRI_L0      0x0000   /* Set interrupt priority 0 (highest) */

/* PCB/EOI - End of interrupt */
#define DST_EOI_NONSPEC       0x8000   /* Non-specific end of interrupt */

/* PCB/POLL/POLLST - Interrupt Poll and Poll Status */
#define DST_POLL_IRQ          0x8000   /* Set if interrupt is pending */
#define DST_POLL_VECTOR_MSK   0x001F   /* Mask off the interrupt vector */

/* Interrupt vectors - devices */
#define DST_IVECT_MAC1        24       /* I6: Ethernet MAC1 */
#define DST_IVECT_DMA3        23       /* DMA channel 3 */
#define DST_IVECT_DMA2        22       /* DMA channel 2 */
#define DST_IVECT_SP3         21       /* I5: Serial port 3 */
#define DST_IVECT_INT5        21       /* I5: External INT5 pin */
#define DST_IVECT_SP0         20       /* Serial Port 0 */
#define DST_IVECT_TMR2        19       /* Timer 2 */
#define DST_IVECT_TMR1        18       /* Timer 1 */
#define DST_IVECT_SP1         17       /* Serial Port 1 */
#define DST_IVECT_SP2         16       /* Serial port 2 */
#define DST_IVECT_USB         15       /* I3: USB controller */
#define DST_IVECT_INT3        15       /* I3: External INT3 pin */
#define DST_IVECT_SPI         14       /* I2: SPI controller */
#define DST_IVECT_I2C         14       /* I2: I2C controller */
#define DST_IVECT_CAN         13       /* I1: CAN channels 1 and 0 */
#define DST_IVECT_INT1        13       /* I1: External INT1 pin */
#define DST_IVECT_MAC0        12       /* INT0: Ethernet MAC0 */
#define DST_IVECT_DMA1        11       /* DMA channel 1 */
#define DST_IVECT_DMA0        10       /* DMA channel 0 */
#define DST_IVECT_TMR0        8        /* Timer 0 */

/* Interrupt vectors - software */
#define DST_IVECT_DIVIDE      0        /* Divide error */
#define DST_IVECT_SSTEP       1        /* Single Step */
#define DST_IVECT_NMI         2        /* Non-Maskable Interrupt */
#define DST_IVECT_BREAKPT     3        /* Software breakpoint */
#define DST_IVECT_INTO        4        /* INTO instruction + OF flag set */
#define DST_IVECT_BOUNDS      5        /* Array bounds exception */
#define DST_IVECT_INV_OP      6        /* Unused opcode */
#define DST_IVECT_ESC_OP      7        /* Escape (ESC) trap */

/* PCB/DMA - DMA control */
#define DST_DMA_DST_MEM       0x8000   /* Destination is in memory space */
#define DST_DMA_DST_IO        0x0000   /* Destination is in I/O space */
#define DST_DMA_DST_DEC       0x4000   /* Decrement dst pointer */
#define DST_DMA_DST_INC       0x2000   /* Increment dst pointer */
#define DST_DMA_SRC_MEM       0x1000   /* Source is in memory space */
#define DST_DMA_SRC_IO        0x0000   /* Source is in I/O space */
#define DST_DMA_SRC_DEC       0x0800   /* Decrement src pointer */
#define DST_DMA_SRC_INC       0x0400   /* Increment src pointer */
#define DST_DMA_TC            0x0200   /* Stop DMA when count reaches 0 */
#define DST_DMA_INT_ENABLE    0x0100   /* Generate interrupt on termination */
#define DST_DMA_SYNC_NO       0x0000   /* No synchronization */
#define DST_DMA_SYNC_DST      0x0080   /* Destination sync */
#define DST_DMA_SYNC_SRC      0x0040   /* Source sync */
#define DST_DMA_PRI_HI        0x0020   /* Select high priority */
#define DST_DMA_PRI_LO        0x0000   /* Select low priority */
#define DST_DMA_TDRQ          0x0010   /* Timer 2 provides request */
#define DST_DMA_START         0x0006   /* Start DMA operation */
#define DST_DMA_STOP          0x0004   /* Stop DMA operation */
#define DST_DMA_XFER_WORD     0x0001   /* Select word transfers */
#define DST_DMA_XFER_BYTE     0x0000   /* Select byte transfers */

/* PCB/SPxCT - Serial port control */
#define DST_SPXCT_DMA_MODE_0  0x0000   /* DMA Mode 0 */
#define DST_SPXCT_DMA_MODE_1  0x2000   /* DMA Mode 1 */
#define DST_SPXCT_DMA_MODE_2  0x4000   /* DMA Mode 2 */
                                         /* No DMA mode 3 */
#define DST_SPXCT_DMA_MODE_4  0x8000   /* DMA Mode 4 */
#define DST_SPXCT_DMA_MODE_5  0xA000   /* DMA Mode 5 */
#define DST_SPXCT_DMA_MODE_6  0xC000   /* DMA Mode 6 */
#define DST_SPXCT_DMA_MODE_7  0xE000   /* DMA Mode 7 */
#define DST_SPXCT_RSIE        0x1000   /* Receive Status Interrupt Enable */
#define DST_SPXCT_BRK         0x0800   /* Generate Break */
#define DST_SPXCT_TB8         0x0400   /* Transmit Bit 8 */
#define DST_SPXCT_FC_EN       0x0200   /* Enable flow control */
#define DST_SPXCT_TXIE        0x0100   /* Transmitter empty interrupt enable */
#define DST_SPXCT_RXIE        0x0080   /* Receive data interrupt enable */
#define DST_SPXCT_TMOD        0x0040   /* Enable transmitter */
#define DST_SPXCT_RMOD        0x0020   /* Enable receiver */
#define DST_SPXCT_PARITY_EVN  0x0018   /* Select even parity */
#define DST_SPXCT_PARITY_ODD  0x0008   /* Select odd parity */
#define DST_SPXCT_PARITY_NONE 0x0000   /* Select no parity */
#define DST_SPXCT_MODE_1      0x0001   /* Select mode 1 */
#define DST_SPXCT_MODE_2      0x0002   /* Select mode 2 */
#define DST_SPXCT_MODE_3      0x0003   /* Select mode 3 */
#define DST_SPXCT_MODE_4      0x0004   /* Select mode 4 */
#define DST_SPXCT_MODE_5      0x0005   /* Select mode 4 */

/* PCB/SPxSTS - Serial port status */
#define DST_SPXSTS_BRK1       0x0400   /* Long break detected */
#define DST_SPXSTS_BRK0       0x0200   /* Short break detected */
#define DST_SPXSTS_RB8        0x0100   /* Receive bit 8 */
#define DST_SPXSTS_RDR        0x0080   /* Receive data ready */
#define DST_SPXSTS_THRE       0x0040   /* Transmit holding register empty */
#define DST_SPXSTS_FER        0x0020   /* Framing error */
#define DST_SPXSTS_OER        0x0010   /* Overrun error */
#define DST_SPXSTS_PER        0x0008   /* Parity error */
#define DST_SPXSTS_TEMT       0x0004   /* Transmitter empty */
#define DST_SPXSTS_HS0        0x0002   /* Handshake 0 (CTS) active */

/* PCB/SPxAUX - Serial port Aux control */
#define DST_SPXAUX_BRGO			0x0800	/* Connect RTS out to baud generator */
#define DST_SPXAUX_FIFO_1		0x0000	/* Set FIFO depth to 1 byte */
#define DST_SPXAUX_FIFO_2		0x0020	/* Set FIFO depth to 2 bytes */
#define DST_SPXAUX_FIFO_3		0x0040	/* Set FIFO depth to 3 bytes */
#define DST_SPXAUX_FIFO_4		0x0060	/* Set FIFO depth to 4 bytes */
#define DST_SPXAUX_RTSZ			0x0010	/* Forcr RTS inactive */
#define DST_SPXAUX_RTS      	0x0008   /* Force RTS active */
#define DST_SPXAUX_RXM      	0x0004   /* Force receiver to half-duplex */
#define DST_SPXAUX_CTSM     	0x0002   /* Force CTS active internally */
#define DST_SPXAUX_RTSP     	0x0001   /* Invert RTS polarity */

/* PCB/SPICTRL - Serial peripheral interface control */
#define DST_SPICTRL_IRQEN     0x0080   /* Enable interrupt */
#define DST_SPICTRL_AUTODRV   0x0040   /* Enable Autodrv */
#define DST_SPICTRL_INVCS     0x0020   /* Invert Chip Select */
#define DST_SPICTRL_PHASE_0   0x0000   /* Select Phase 0 */
#define DST_SPICTRL_PHASE_1   0x0010   /* Select Phase 1 */
#define DST_SPICTRL_CKPOL_HI  0x0008   /* Select 'high' clock idle */
#define DST_SPICTRL_CKPOL_LO  0x0000   /* Select 'low' clock idle */
#define DST_SPICTRL_WOR_EN    0x0004   /* Enable wire-or operation */
#define DST_SPICTRL_MSTEN     0x0002   /* Assert mastery of bus */
#define DST_SPICTRL_ALT     	0x0001   /* Select alternate I/O pinout */

/* PCB/SPISTAT - Serial peripheral interface status */
#define DST_SPISTAT_IRQ       0x0080   /* Interrupt has occurred */
#define DST_SPISTAT_OVERRUN   0x0040   /* Transmit overrun */
#define DST_SPISTAT_COL       0x0020   /* Collision between bus masters */
#define DST_SPISTAT_TXRUN     0x0002   /* Master mode operation in progress */
#define DST_SPISTAT_SLVSEL    0x0001   /* External master is active on bus */

/* PCB/SPISSEL - Serial peripheral interface slave select */
#define DST_SPISSEL_SHIFT_8   0x0000   /* Select 8 bit transfer */
#define DST_SPISSEL_SHIFT_7   0x00E0   /* Select 7 bit transfer */
#define DST_SPISSEL_SHIFT_6   0x00C0   /* Select 6 bit transfer */
#define DST_SPISSEL_SHIFT_5   0x00A0   /* Select 5 bit transfer */
#define DST_SPISSEL_SHIFT_4   0x0080   /* Select 4 bit transfer */
#define DST_SPISSEL_SHIFT_3   0x0060   /* Select 3 bit transfer */
#define DST_SPISSEL_SHIFT_2   0x0040   /* Select 2 bit transfer */
#define DST_SPISSEL_SHIFT_1   0x0020   /* Select 1 bit transfer */
#define DST_SPISSEL_SELECTO   0x0001   /* Drive SLVSEL pin active */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Ethernet Controller Constants
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
/* Ethernet/RAP - Register Address Port */
/* Here are the registers accessible via RAP/RDP */
#define DST_ETHRAP_STATUS     0        /* CSR0 - Status */
#define DST_ETHRAP_IADR_L     1        /* CSR1 - initialization addr low word */
#define DST_ETHRAP_IADR_H     2        /* CSR2 - initialization addr high word*/
#define DST_ETHRAP_INTMSK     3        /* CSR3 - interrupt mask */
#define DST_ETHRAP_FEATURE    4        /* CSR4 - features control */
#define DST_ETHRAP_PADR_15_00 12       /* CSR12 - MAC address bits 15-0 */
#define DST_ETHRAP_PADR_31_16 13       /* CSR13 - MAC address bits 31-16 */
#define DST_ETHRAP_PADR_47_32 14       /* CSR14 - MAC address bits 47-32 */
#define DST_ETHRAP_MODE       15       /* CSR15 - Mode control */
#define DST_ETHRAP_RXBASE_L   24       /* CSR24 - RX ring base addr low word */
#define DST_ETHRAP_RXBASE_H   25       /* CSR25 - RX ring base addr high word */
#define DST_ETHRAP_TXBASE_L   30       /* CSR30 - TX ring base addr low word */
#define DST_ETHRAP_TXBASE_H   31       /* CSR31 - TX ring base addr high word */
#define DST_ETHRAP_POLL_TIME  46       /* CSR46 - Poll time counter */
#define DST_ETHRAP_POLL_INTVL 47       /* CSR47 - Poll interval */
#define DST_ETHRAP_RXLEN      76       /* CSR76 - Receive ring length */
#define DST_ETHRAP_TXLEN      78       /* CSR78 - Transmit length */
#define DST_ETHRAP_CHIP_ID_L  88       /* CSR88 - Chip ID low word */
#define DST_ETHRAP_CHIP_ID_H  89       /* CSR89 - Chip ID high word */
#define DST_ETHRAP_MISSD_FRM  112      /* CSR112 - Missed frame count */
#define DST_ETHRAP_RCV_COL    114      /* CSR114 - Received collision count */

/* Ethernet Status register bits (CSR0) */
#define DST_ETHSTAT_ERR       0x8000   /* Logical or of CERR, MISS */
#define DST_ETHSTAT_CERR      0x2000   /* SQE test error */
#define DST_ETHSTAT_MISS      0x1000   /* Incoming frame was lost */
#define DST_ETHSTAT_RINT      0x0400   /* Frame received in RX ring */
#define DST_ETHSTAT_TINT      0x0200   /* Frame has been transmitted */
#define DST_ETHSTAT_IDON      0x0100   /* Initialization block read */
#define DST_ETHSTAT_INSTR     0x0080   /* Logical or of MISS, MFCO, RCVCCO, */
                                       /* RINT, TINT, IDON, TXSTRT, PAUSE */
#define DST_ETHSTAT_IENA      0x0040   /* Interrupt enable */
#define DST_ETHSTAT_RXON      0x0020   /* Enable receiver */
#define DST_ETHSTAT_TXON      0x0010   /* Enable transmitter */
#define DST_ETHSTAT_TDMD      0x0008   /* Force poll of RX & TX rings */
#define DST_ETHSTAT_STOP      0x0004   /* Stop activity */
#define DST_ETHSTAT_STRT      0x0002   /* Start activity */
#define DST_ETHSTAT_INIT      0x0001   /* Load initialization block */

/* Ethernet Interrupt mask (CSR3) */
#define DST_ETHIMSK_MISSM     0x1000   /* Mask missed frame interrupt */
#define DST_ETHIMSK_RINTM     0x0400   /* Mask received frame interrupt */
#define DST_ETHIMSK_TINTM     0x0200   /* Mask transmit done interrput */
#define DST_ETHIMSK_IDONM     0x0100   /* Mask initialization done interrupt */
#define DST_ETHIMSK_DTX2PD    0x0010   /* Disable transmit 2 part deferral */

/* Ethernet Features control (CSR4) */
#define DST_ETHFEAT_DPOLL     0x1000   /* Disable transmit polling */
#define DST_ETHFEAT_APADTX    0x0800   /* Pad frames shorter than 64 bytes */
#define DST_ETHFEAT_MFCO      0x0200   /* Missed frame counter overflow */
#define DST_ETHFEAT_MFCOM     0x0100   /* Mask MFCO interrupt */
#define DST_ETHFEAT_RPA       0x0080   /* Enable runt packet reception */
#define DST_ETHFEAT_RCVCCO    0x0020   /* Receive collision counter overflow */
#define DST_ETHFEAT_RCVCCOM   0x0010   /* Mask RCVCCO interrupt */
#define DST_ETHFEAT_TXSTRT    0x0008   /* Transmit has started */
#define DST_ETHFEAT_TXSTRTM   0x0004   /* Mask TXSTRT interrupt */
#define DST_ETHFEAT_PAUSE     0x0002   /* Pause control frame received */
#define DST_ETHFEAT_PAUSEM    0x0001   /* Mask PAUSE interrupt */

/* Ethernet Mode (CSR15) */
#define DST_ETHMODE_PROM      0x8000   /* Enable promiscuous mode */
#define DST_ETHMODE_DRXBC     0x4000   /* Disable multicast receive */
#define DST_ETHMODE_DRXPA     0x2000   /* Disable receive physical address */
#define DST_ETHMODE_DPAUSE    0x0800   /* Disable automatic pause */
#define DST_ETHMODE_DRTY      0x0020   /* Disable transmit retries */
#define DST_ETHMODE_DTXFCS    0x0008   /* Disable CRC generation */
#define DST_ETHMODE_DTX       0x0002   /* Disable transmit operation */
#define DST_ETHMODE_DRX       0x0001   /* Disable receive operation */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** Ethernet Media Independant Interface (MII) constants
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
#define DST_ETHMII_FDEN       0x8000   /* Full-duplex enable */
#define DST_ETHMII_MDI        0x0100   /* Managment data in bit */
#define DST_ETHMII_MDOE       0x0080   /* MDIO pin output enable */
#define DST_ETHMII_MDC        0x0002   /* Management data clock */
#define DST_ETHMII_MDO        0x0001   /* Management data out bit */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** CAN Register Constants
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
/* CAN Transmit message data length & control */
#define DST_CAN_TXMSG_IDE     0x0010   /* Extended identifier bit */
#define DST_CAN_TXMSG_RTR     0x0020   /* Remote bit */

/* CAN Transmit control flags */
#define DST_CAN_TXFL_TRX         0x0001   /* Initiate transmit */
#define DST_CAN_TXFL_TXAB        0x0002   /* Abort transmit */

/* CAN Receive status masks */
#define DST_CAN_RXST_DLC         0x000F   /* Data length code */
#define DST_CAN_RXST_IDE         0x0010   /* Extended identifier bit */
#define DST_CAN_RXST_RTR         0x0020   /* Remote bit */
#define DST_CAN_RXST_AFI_0       0x0100   /* Acceptance filter 0 indicator */
#define DST_CAN_RXST_AFI_1       0x0200   /* Acceptance filter 1 indicator */
#define DST_CAN_RXST_AFI_2       0x0400   /* Acceptance filter 2 indicator */

/* CAN Error status register */
#define DST_CAN_ERST_STATE_BOFF  0x0002   /* Bus off, bit 0 is don't care */
#define DST_CAN_ERST_STATE_ACT   0x0000   /* Error active normal operation */
#define DST_CAN_ERST_STATE_PAS   0x0001   /* Error passive */
#define DST_CAN_ERST_TXGTE96     0x0004   /* Tx error count exceeds 96 */
#define DST_CAN_ERST_RXGTE96     0x0008   /* Rx error count exceeds 96 */

/* CAN Transmit Fifo interrupt levels */
#define DST_CAN_TXFIFO_LVL0      0x0000   /* Interrupt when all tx buffers MT */
#define DST_CAN_TXFIFO_LVL1      0x0001   /* . when at least 2 buffers empty */
#define DST_CAN_TXFIFO_LVL2      0x0002   /* . when at least 3 buffers empty */

/* CAN Receive Fifo interrupt levels */
#define DST_CAN_RXFIFO_LVL0      0x0000   /* Interrupt when at least 1 msg */
#define DST_CAN_RXFIFO_LVL1      0x0004   /* .. when at least 2 messages */
#define DST_CAN_RXFIFO_LVL2      0x0008   /* .. when at least 3 messages */
#define DST_CAN_RXFIFO_LVL3      0x000C   /* .. when at least 4 messages */

/* CAN Interrupt requests */
#define DST_CAN_IRQ_ARBLOSS      0x0004   /* Arbitration lost during tx */
#define DST_CAN_IRQ_OVRLOAD      0x0008   /* Overload condition */
#define DST_CAN_IRQ_RX_OVR       0x0010   /* Receiver overrun */
#define DST_CAN_IRQ_BIT_ERR      0x0020   /* Bit error during tx or rx */
#define DST_CAN_IRQ_STUF_ERR     0x0040   /* Stuffing error during tx or rx */
#define DST_CAN_IRQ_ACK_ERR      0x0080   /* Ack error during tx or rx */
#define DST_CAN_IRQ_FORM_ERR     0x0100   /* Format error during tx or rx */
#define DST_CAN_IRQ_CRC_ERR      0x0200   /* CRC error during tx or rx */
#define DST_CAN_IRQ_BUS_OFF      0x0400   /* CAN is in bus off state */
#define DST_CAN_IRQ_TX_XMIT0     0x0800   /* Message 0 sent */
#define DST_CAN_IRQ_TX_XMIT1     0x1000   /* Message 1 sent */
#define DST_CAN_IRQ_TX_XMIT2     0x2000   /* Message 2 sent */
#define DST_CAN_IRQ_TX_DONE      0x4000   /* At least 1 tx buffer empty */
#define DST_CAN_IRQ_RX_DONE      0x8000   /* At least 1 rx message available */

/* CAN Interrupt enable */
#define DST_CAN_IEN_GENRL        0x0001   /* General enable */
#define DST_CAN_IEN_ARBLOSS      0x0004   /* Arbitration lost during tx */
#define DST_CAN_IEN_OVRLOAD      0x0008   /* Overload condition */
#define DST_CAN_IEN_RX_OVR       0x0010   /* Receiver overrun */
#define DST_CAN_IEN_BIT_ERR      0x0020   /* Bit error during tx or rx */
#define DST_CAN_IEN_STUF_ERR     0x0040   /* Stuffing error during tx or rx */
#define DST_CAN_IEN_ACK_ERR      0x0080   /* Ack error during tx or rx */
#define DST_CAN_IEN_FORM_ERR     0x0100   /* Format error during tx or rx */
#define DST_CAN_IEN_CRC_ERR      0x0200   /* CRC error during tx or rx */
#define DST_CAN_IEN_BUS_OFF      0x0400   /* CAN is in bus off state */
#define DST_CAN_IEN_TX_XMIT0     0x0800   /* Message 0 sent */
#define DST_CAN_IEN_TX_XMIT1     0x1000   /* Message 1 sent */
#define DST_CAN_IEN_TX_XMIT2     0x2000   /* Message 2 sent */
#define DST_CAN_IEN_TX_DONE      0x4000   /* At least 1 tx buffer empty */
#define DST_CAN_IEN_RX_DONE      0x8000   /* At least 1 rx message available */

/* CAN operating mode */
#define DST_CAN_OPMOD_RUN        0x0001   /* Place controller to RUN mode */
#define DST_CAN_OPMOD_PAS        0x0002   /* Place controller to passive mode */
#define DST_CAN_OPMOD_LOOP       0x0004   /* Internal loopback mode */

/* CAN Configuration */
#define DST_CAN_CFG_SYNC_RTOD    0x0000   /* Sync on recessive to dom edge*/
#define DST_CAN_CFG_SYNC_BOTH    0x0001   /* Sync on both edges */
#define DST_CAN_CFG_SAMPL_0      0x0000   /* Sample mode 0: 1 point */
#define DST_CAN_CFG_SAMPL_1      0x0002   /* Sample mode 1: 3 points */
#define DST_CAN_CFG_SJW_1        0x0000   /* Sync Jump width 1 */
#define DST_CAN_CFG_SJW_2        0x0004   /* Sync Jump width 2 */
#define DST_CAN_CFG_SJW_3        0x0008   /* Sync Jump width 3 */
#define DST_CAN_CFG_SJW_4        0x000C   /* Sync Jump width 4 */
#define DST_CAN_CFG_AUTO_RES     0x0010   /* Auto restart */
#define DST_CAN_CFG_OVR_MSG      0x8000   /* Overwrite last message */

/* CAN acceptance filter enable */
#define DST_CAN_FILT_EN_0        0x0001   /* Enable filter 0 */
#define DST_CAN_FILT_EN_1        0x0002   /* Enable filter 1 */
#define DST_CAN_FILT_EN_2        0x0004   /* Enable filter 2 */

/* CAN arbitration lost capture */
#define DST_CAN_ALCR_FRAME_MSK   0x1F00   /* Frame reference field mask */
#define DST_CAN_ALCR_BIT_MSK     0x003F   /* Mask bit vector */

/* CAN Error capture */
#define DST_CAN_ECR_BIT_MSK      0x003F   /* Mask bit vector */
#define DST_CAN_ECR_RXMOD        0x0040   /* Receiving data */
#define DST_CAN_ECR_TXMOD        0x0080   /* Transmitting data */
#define DST_CAN_ECR_FRAME_MSK    0x1F00   /* Frame reference field mask */
#define DST_CAN_ECR_ERRCOD_MSK   0xE000   /* Error code field mask */

/* CAN frame reference */
#define DST_CAN_FRR_BIT_MSK      0x003F   /* Mask bit vector */
#define DST_CAN_FRR_TXMOD        0x0040   /* Transmitting data */
#define DST_CAN_FRR_RXMOD        0x0080   /* Receiving data */
#define DST_CAN_FRR_FRAME_MSK    0x1F00   /* Frame reference field mask */
#define DST_CAN_FRR_TXBIT        0x2000   /* Current bit state on trans line*/
#define DST_CAN_FRR_RXBIT        0x4000   /* Current bit state on rec line */
#define DST_CAN_FRR_STUFIND      0x8000   /* Stuff bit inserted */

/* Frame reference field definitions - used in ALCR, ECR & FRR */
#define DST_CAN_FRAMREF_STOP     0x0000   /* Stopped */
#define DST_CAN_FRAMREF_SYNC     0x0001   /* Synchronize */
#define DST_CAN_FRAMREF_IFRAME   0x0005   /* Interframe */
#define DST_CAN_FRAMREF_BUSIDL   0x0006   /* Bus Idle */
#define DST_CAN_FRAMREF_SOF      0x0007   /* Start of frame */
#define DST_CAN_FRAMREF_ARB      0x0008   /* Arbitration */
#define DST_CAN_FRAMREF_CTRL     0x0009   /* Control */
#define DST_CAN_FRAMREF_DATA     0x000A   /* Data */
#define DST_CAN_FRAMREF_CRC      0x000B   /* CRC */
#define DST_CAN_FRAMREF_ACK      0x000C   /* Acknowledge */
#define DST_CAN_FRAMREF_EOF      0x000D   /* End of frame */
#define DST_CAN_FRAMREF_ERRF     0x0010   /* Error flag */
#define DST_CAN_FRAMREF_ERRECH   0x0011   /* Error echo */
#define DST_CAN_FRAMREF_ERRDEL   0x0012   /* Error Delay */
#define DST_CAN_FRAMREF_OVRF     0x0018   /* Overload flag */
#define DST_CAN_FRAMREF_OVRECH   0x0019   /* Overload echo */
#define DST_CAN_FRAMREF_OVRDEL   0x001A   /* Overload delay */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** I2C Register Constants
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/* Control Register */
#define DST_I2C_CNTR_IEN			0x80		/* Interrupt Enable */
#define DST_I2C_CNTR_ENAB			0x40		/* I2C Enable */
#define DST_I2C_CNTR_STA			0x20		/* Send start condition */
#define DST_I2C_CNTR_STP			0x10		/* Send stop condition */
#define DST_I2C_CNTR_IFLG			0x08		/* Interrupt flag */
#define DST_I2C_CNTR_AAK			0x04		/* Send acknowledge */

/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
** USB Register Constants
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

/* USB Interrupt Status */
#define DST_USB_INT_STAT_STALL		0x80	/* Transaction completed or stalled */
#define DST_USB_INT_STAT_ATTACH		0x40	/* USB peripheral attached */
#define DST_USB_INT_STAT_RESUME		0x20	/* */
#define DST_USB_INT_STAT_SLEEP		0x10	/* USB bus idle for 3 ms */
#define DST_USB_INT_STAT_TOK_DNE		0x08	/* Current token processing done */
#define DST_USB_INT_STAT_SOF_TOK		0x04	/* Start of frame token received */
#define DST_USB_INT_STAT_ERROR		0x02	/* Error - see ERR_STAT register */
#define DST_USB_INT_STAT_USB_RST		0x01	/* USB reset decoded */

/* USB Interrupt Enable */
#define DST_USB_INT_ENB_STALL			0x80	/* Enable stall interrupt */
#define DST_USB_INT_ENB_ATTACH		0x40	/* Enable attach interrupt */
#define DST_USB_INT_ENB_RESUME		0x20	/* Enable resume interrupt */
#define DST_USB_INT_ENB_SLEEP			0x10	/* Enable sleep interrupt */
#define DST_USB_INT_ENB_TOK_DNE		0x08	/* Enable token done interrupt */
#define DST_USB_INT_ENB_SOF_TOK		0x04	/* Enable start of frame interrupt */
#define DST_USB_INT_ENB_ERROR			0x02	/* Enable error interrupt */
#define DST_USB_INT_ENB_USB_RST		0x01	/* Enable reset interrupt */

/* USB Error Interrupt Status */
#define DST_USB_ERR_STAT_BTS_ERR		0x80	/* Bit stuff error */
														/* Bit 6 is reserved */
#define DST_USB_ERR_STAT_DMA_ERR		0x20	/* DMA error */
#define DST_USB_ERR_STAT_BTO_ERR		0x10	/* Bus turn around timeout */
#define DST_USB_ERR_STAT_DFN8			0x08	/* Data field not 8 bits */
#define DST_USB_ERR_STAT_CRC16		0x04	/* CRC16 error */
#define DST_USB_ERR_STAT_CRC5			0x02	/* CRC5 error (host mode only) */
#define DST_USB_ERR_STAT_EOF			0x02	/* EOF error (peripheral mode only) */
#define DST_USB_ERR_STAT_PID_ERR		0x01	/* PID check failed */

/* USB Error Interrupt Enable */
#define DST_USB_ERR_ENB_BTS_ERR		0x80	/* Enable int on BTS error */
/* Bit 6 is reserved */
#define DST_USB_ERR_ENB_DMA_ERR		0x20	/* Enable int on DMA error */
#define DST_USB_ERR_ENB_BTO_ERR		0x10	/* Enable int on Bus timeout */
#define DST_USB_ERR_ENB_DFN8			0x08	/* Enable int on data not 8 bits */
#define DST_USB_ERR_ENB_CRC16			0x04	/* Enable int on CRC16 failure */
#define DST_USB_ERR_ENB_CRC5			0x02	/* Enable int on CRC5 error */
#define DST_USB_ERR_ENB_EOF			0x02	/* Enable int on EOF error */
#define DST_USB_ERR_ENB_PID_ERR		0x01	/* Enable int on PID check error */

/* USB Status */
#define DST_USB_STAT_ENDP_MSK			0xF0	/* Mask the endpoint bits */
#define DST_USB_STAT_ENDP_TX			0x08	/* Buf desc table updated by TX */
#define DST_USB_STAT_ENDP_ODD			0x04	/* Buf desc updated in odd bank */

/* USB Control */
#define DST_USB_CTL_JSTATE				0x80	/* Live differential receiver */
#define DST_USB_CTL_SE0					0x40	/* Single ended zero */
#define DST_USB_CTL_TXD_SUSPEND		0x20	/* (Target) packet TX/RX disabled */
#define DST_USB_CTL_TOKEN_BUSY		0x20	/* (Host) executing USB token */
#define DST_USB_CTL_RESET				0x10	/* Generate USB reset */
#define DST_USB_CTL_HOST_MODE_EN		0x08	/* Enable host mode */
#define DST_USB_CTL_RESUME				0x04	/* Resume signalling */
#define DST_USB_CTL_ODD_RST			0x02	/* Reset all BDT to even bank */
#define DST_USB_CTL_USB_EN				0x01	/* Enable USB */

/* USB Address */
#define DST_USB_ADDR_LS_EN				0x80	/* Low speed enable */
#define DST_USB_ADDR_MASK				0x7F	/* Address in low 7 bits */

/* USB Token */
#define DST_USB_TOKEN_PID_OUT			0x10	/* Perform out transaction */
#define DST_USB_TOKEN_PID_IN			0x90	/* Perform in transaction */
#define DST_USB_TOKEN_PID_SETUP		0xD0	/* Perform setup */

/* USB Endpoint control */
#define DST_USB_EP_CTL_HOST_WO_HUB	0x80	/* Enable low speed w/o hub */
#define DST_USB_EP_CTL_RETRY_DIS		0x40	/* Do not retry NAK'd transact */
														/* Bit 5 is reserved */
#define DST_USB_EP_CTL_EP_CTL_DIS	0x10	/* Disable control transfers */
#define DST_USB_EP_CTL_EP_RX_EN		0x08	/* Enable RX transfers */
#define DST_USB_EP_CTL_EP_TX_EN		0x04	/* enable TX transfers */
#define DST_USB_EP_CTL_EP_STALL		0x02	/* The endpoint is stalled */
#define DST_USB_EP_CTL_EP_HSHK		0x01	/* Perform handshaking */

#endif
/*
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
**                         END
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/


