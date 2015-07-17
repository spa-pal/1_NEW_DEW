;/* Abfragbare Variablen in der interfaces/at/ip/icmp/tcp/udp/transmission grp*/
;/* alle cntr etc stehen in einem Array */
  extrn _S_vars:BYTE
IF1_Spe  equ  0
IF1_IOct equ  1       ; netblk
IF1_IUC  equ  2       ; netblk
IF1_IBC  equ  3       ; netblk
IF1_IDi  equ  4       ; netblk
IF1_IErr equ  5
IF1_IUnP equ  6
IF1_OOct equ  7       ; netblk
IF1_OUC  equ  8       ; netblk
IF1_OBC  equ  9       ; netblk
IF1_ODi  equ  10
UDP_IN   equ  11
UDP_INP  equ  12
UDP_OUT  equ  13
IP_IN    equ  14
IP_Rou   equ  15
IP_UPr   equ  16
IP_Del   equ  17
IP_OUT   equ  18
IC_DU    equ  19
IC_SQ    equ  20
IC_RE    equ  21
IC_ER    equ  22
IC_TE    equ  23
IC_PP    equ  24
IC_TR    equ  25
IC_OE    equ  26
IC_IN    equ  27
IC_IE    equ  28
IC_ONP   equ  29

SVARADD macro %1,%2
        add   word ptr DGROUP:[_S_vars+4*%1],%2
        adc   word ptr DGROUP:[_S_vars+4*%1+2],0
        endm

