/*****************************************************************************/
/*                                                                           */
/* File         bitsXP.h                                                     */
/*                                                                           */
/* Description  Contains defines & variables specific to bitsXP.c            */
/*                                                                           */
/*****************************************************************************/
/* Revision History                                                          */
/*                                                                           */
/* 2002-8-02 doris: created to "clean up" source/header files                */
/*                                                                           */
/*****************************************************************************/

#define  NIOBITS     35		/* MUST be defined before digio include to override the 'default' value */

/* hardware specific PIO pin numbers */
#define  CP0_PIOPIN  20		/* physical pin # for corresponding config IO */
#define  CP1_PIOPIN   1		/* physical pin # for corresponding config IO */
#define  CP2_PIOPIN  23		/* physical pin # for corresponding config IO */

/* indices into array, must match the configPins_strings -- For Link Status*/
#define CP_CTS      0
#define CP_RTS      1
#define CP_DCD      2
#define CP_DTR      3
#define CP_IN0      4
#define CP_OUT0     5
#define CP_IN1      6
#define CP_OUT1     7
#define CP_IN2      8
#define CP_OUT2     9
#define CP_LED1     10
#define CP_LED3     11
#define CP_RS485_OE 12
#define CP_LINK	   13
#define CP_LAST	   14


/* application specific bits, start after the 'standard' bits */
#define  CP0 	32
#define  CP1 	33
#define  CP2 	34
#define  CPS   3

#define  USER1 CP0
#define  USER2 CP1
#define  USER3 CP2
#define  USERS CPS

