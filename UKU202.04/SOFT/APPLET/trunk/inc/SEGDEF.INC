_TEXT   segment byte public 'CODE'
_TEXT   ends
VECTORS segment para common 'DATA'
VECTORS ends
DRIVERS segment word public 'DATA'
DRIVERS ends
DREND   segment word common 'DATA'
DREND   ends
_DATA   segment word public 'DATA'
_DATA   ends
CDATA   segment word public 'DATA'
CDATA   ends
_BSS    segment word public 'BSS'
_BSS    ends
_DATAP  segment para public 'DATA'
_DATAP  ends
EXTDATA segment common
EXTDATA ends
ENDDATA segment word public 'STACK'
ENDDATA ends
DGROUP group VECTORS,DRIVERS,DREND,_DATA,_DATAP,CDATA,_BSS,EXTDATA,ENDDATA

