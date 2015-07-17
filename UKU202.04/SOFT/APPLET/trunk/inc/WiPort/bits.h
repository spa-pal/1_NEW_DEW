/*****************************************************************************/
/*                                                                           */
/* File         bits.h                                                       */
/*                                                                           */
/* Description  Contains defines & variables specific to bits.c              */
/*                                                                           */
/*****************************************************************************/
/* Revision History                                                          */
/*                                                                           */
/* 03-12-03 dam : created for WiPort                                         */
/*****************************************************************************/

#define  NIOBITS     43		/* MUST be defined before digio include to override the 'default' value */
							/* ALSO DEFINED IN HARDWARE.INC !!!! */

/* hardware specific PIO pin numbers */
#define  CP0_PIOPIN  14	
#define  CP1_PIOPIN  15	 
#define  CP2_PIOPIN  18	
#define  CP3_PIOPIN  19	
#define  CP4_PIOPIN  20	
#define  CP5_PIOPIN  24	
#define  CP6_PIOPIN  25	
#define  CP7_PIOPIN  26	
#define  CP8_PIOPIN  27	
#define  CP9_PIOPIN 28	
#define  CP10_PIOPIN 29	

/* application specific bits, start after the 'standard' 32 bits */
#define  CP0 	32
#define  CP1 	33
#define  CP2 	34
#define  CP3 	35
#define  CP4 	36
#define  CP5 	37
#define  CP6 	38
#define  CP7 	39
#define  CP8 	40
#define  CP9	41
#define  CP10	42

#define  CPS 	11



