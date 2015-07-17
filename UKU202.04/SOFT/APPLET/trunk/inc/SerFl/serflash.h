/******************************************************************************
 *
 *	FILE:	      serflash.h
 *
 *  DESCRIPTION:  This header file defines constants and data types used by the
 *                Serial Peripheral Interface (SPI) I/O functions
 *
 ******************************************************************************
 *
 *  REVISION HISTORY:
 *							
 *  2002-01-25	dam: initial revision based on the file provided by Wes Dodd. 
 *       10-24  dam: removed unused items, just clean-up, added define for the
 *                   starting SPI flash page number of WEB1
 *
 ******************************************************************************/

/********************
 *  Defines Section
 ********************/

/* Serial flash specifics for 4MBit part */
#define EC_SERFL_PAGE_SIZE	           264
#define NUM_SERFL_PAGES_PER64K         248
#define NUM_SERFL_BYTES_LEFT_PER64K    64

// from 6.1.x.x onwards. (for platform specific values refer to hware.c)
//#define FW1_START_PAGE                 7


/************************
 *  Function Prototypes
 ************************/

/* Serial flash driver functions */
void        vEcSppSerFlashInit(void);
void        vEcSppSerFlashSel(U16 u16State);
void        vEcSppSerFlashDelay(void);

EC_STATUS tEcSppSerFlashRead(U16 u16Page,
                             U16 u16Start,
                             U32 u32Len,
                             U8 far *fpu8Buff);

EC_STATUS tEcSppSerFlashWrite(U16 u16Page,
                              U16 u16Start,
                              U32 u32Len,
                              U8 far *fpu8Buff);
                             
EC_STATUS   tEcSppSerFlashPageRead(U16 u16PageNo,
                                   U16 u16Start,
                                   U16 u16Len,
                                   U8 far *fpu8Buff);
                                   
EC_STATUS   tEcSppSerFlashPageWrite(U16 u16PageNo,
                                    U16 u16Start,
                                    U16 u16Len,
                                    U8 far *fpu8Buff);
                                    
/* SPI functions */
void        vEcSppSpiInit(void);
EC_STATUS   tEcSppSpiOut(U8 far *fpu8Data, U32 u32Count);
EC_STATUS   tEcSppSpiIn (U8 far *fpu8Data, U32 u32Count);


