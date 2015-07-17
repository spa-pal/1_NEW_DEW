#pragma inline

#include "..\inc\style.h"
#include "snmp.h"
#include "snmpvar.h"

GLOBAL DWORD S_tick;
GLOBAL DWORD S_vars[S_varanz];
extern BYTE S_name[], S_obj[];

LOCAL char sysContact [18]  = "\020";
LOCAL char sysName [18]     = "\020";
LOCAL char sysLocation [18] = "\020";

GLOBAL WORD snmp_tbl()
{
   asm jmp ENDE

asm extrn priv_mib
asm extrn mib2_2
asm extrn mib2_33

asm X_: dw 1,43
asm dw S_LEER,42
asm dw S_SEQU,X_43

asm X_43: dw 1,6
asm dw S_LEER,5
asm dw S_SEQU,X_43_6

asm X_43_6: dw 0,1
asm dw S_SEQU,X_43_6_1

asm X_43_6_1: dw 0,4
asm dw S_LEER,1
asm dw S_SEQU,X_43_6_1_2
asm dw S_LEER,1
asm dw S_SEQU,X_43_6_1_4

asm X_43_6_1_2: dw 0,1
asm dw S_SEQU,mib2

asm mib2: dw 1,33
asm dw S_SEQU,mib2_1            /* 1 System      */
asm dw S_SEQU,mib2_2            /* 2 Interface   */
asm dw S_LEER,1
asm dw S_SEQU,mib2_4            /* 4 IP          */
asm dw S_LEER,2
asm dw S_SEQU,mib2_7            /* 7 udp         */
asm dw S_LEER,25
asm dw S_SEQU,mib2_33           /* 33 ups        */

asm mib2_1: dw 0,7
asm dw S_OCTSTR+S_RAM,S_name
asm dw S_OBJECT+S_RAM,S_obj
asm dw S_TTICK+S_RAM+S_LONG,S_tick
asm dw S_OCTSTR+S_RAM+S_SET,sysContact+1
asm dw S_OCTSTR+S_RAM+S_SET,sysName+1
asm dw S_OCTSTR+S_RAM+S_SET,sysLocation+1
asm dw S_INT,12

asm mib2_4: dw 0,2
asm dw S_INT,2                          /* 4.1 ipForwarding */
asm dw S_INT,31                         /* 4.2 ipDefaultTTL */

asm mib2_7: dw 0,4
asm dw S_TCTR+S_LONG+S_RAM,S_vars+UDP_IN    /* UDP In Blocks */
asm dw S_TCTR+S_LONG+S_RAM,S_vars+UDP_INP   /* no ports */
asm dw S_TCTR+S_INT,0                      /* in err */
asm dw S_TCTR+S_LONG+S_RAM,S_vars+UDP_OUT   /* outs */

asm X_43_6_1_4: dw 0,0
asm dw S_SEQU,priv_mib


ENDE: asm mov ax,offset X_
   return _AX;
}
