/*****************************************************************************/
/*                                                                           */
/* File         bits.h                                                       */
/*                                                                           */
/* Description  Contains defines & variables specific to DIO_S related init  */
/*                                                                           */
/*****************************************************************************/
/* Revision History                                                          */
/*                                                                           */
/* vmk  08/16/2004 Initial Revision for Micro100                             */
/*****************************************************************************/

#define  NIOBITS     32		/* MUST be defined before digio include to override the 'default' value */

/* hardware specific PIO pin numbers */
#define  CP0_PIOPIN  14		/* physical pin # for corresponding config IO */
#define  CP1_PIOPIN  15		/* physical pin # for corresponding config IO */
#define  CP2_PIOPIN  18		/* physical pin # for corresponding config IO */
#define  CP3_PIOPIN  19		/* physical pin # for corresponding config IO */
#define  CP4_PIOPIN  20		/* physical pin # for corresponding config IO */
#define  CP5_PIOPIN  24   	/* physical pin # for corresponding config IO */
#define  CP6_PIOPIN  25   	/* physical pin # for corresponding config IO */
#define  CP7_PIOPIN  26   	/* physical pin # for corresponding config IO */
#define  CP8_PIOPIN  28   	/* physical pin # for corresponding config IO */
#define  CP9_PIOPIN  29   	/* physical pin # for corresponding config IO */

