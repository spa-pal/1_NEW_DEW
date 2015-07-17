/*
********************************************************************************
* FILENAME:   ECtypes.h
* AUTHOR:     SYNERGETIC
*
* REVISION HISTORY:
*    REV LEVEL:   1.00
*    DATE:        02-06-01
*    REASON:      Initial Release version of the module.
*
*    REV LEVEL:   1.01
*    DATE:        03-23-01
*    REASON:      Added EC_STATUS type
*
*    DATE:        1/25/02
*    REASON:      Removed BOOL type, conflicts with existing Cobos
*
* MODULE DESCRIPTION: This header file defines the "standard" data types
*                     that are to be used for all EmbeddedCom module code
*                     development.
*
* COPYRIGHT 2001 Synergetic Micro Systems Inc.
* All Rights Reserved
* Redistribution or unauthorized use without expressed written agreement
* from Synergetic Micro Systems is forbidden.
*
********************************************************************************
*/
#if !defined(ECTYPES_H)

#define ECTYPES_H

/*
********************************************************************************
*  Adjust the EC_BASE_TYPE_xxxx values appropriately
*  for your target platform.  Note: Do not
*  modify the "typedefs" in the next block,
*  make all adjustments here in this block.
********************************************************************************
*/
#define EC_BASE_TYPE_CHAR    char            // 8-bit signed byte
#define EC_BASE_TYPE_UCHAR   unsigned char   // 8-bit unsigned byte
#define EC_BASE_TYPE_SHORT   short           // 16-bit signed integer
#define EC_BASE_TYPE_USHORT  unsigned short  // 16-bit unsigned integer
#define EC_BASE_TYPE_LONG    long            // 32-bit signed integer
#define EC_BASE_TYPE_ULONG   unsigned long   // 32-bit unsigned integer


/*
********************************************************************************
*        EC Standard Types
********************************************************************************
*/
typedef EC_BASE_TYPE_CHAR     S8;            // 8-bit signed byte
typedef EC_BASE_TYPE_UCHAR    U8;            // 8-bit unsigned byte
typedef EC_BASE_TYPE_SHORT    S16;           // 16-bit signed integer
typedef EC_BASE_TYPE_USHORT   U16;           // 16-bit unsigned integer
typedef EC_BASE_TYPE_LONG     S32;           // 32-bit signed integer
typedef EC_BASE_TYPE_ULONG    U32;           // 32-bit unsigned integer
//typedef EC_BASE_TYPE_UCHAR    BOOL;          // True/False
typedef EC_BASE_TYPE_LONG     EC_STATUS;     // 32 bit signed status

#endif
/*
********************************************************************************
*                                  END
********************************************************************************
*/

