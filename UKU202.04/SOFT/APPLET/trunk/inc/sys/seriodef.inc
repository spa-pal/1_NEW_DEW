
; definitions for the offsets in the HW table:
; 04.04.01 JL added H_RVA

H_CPU   EQU   0     ; CPU indicator, NZ for 188ES
H_HWINI EQU   2     ; HW dependent initialisation
H_CREQ  EQU   4     ; connect request/dtr inquiry
                    ;   par bx:ActCCB, dx:port
H_DCD   EQU   6     ; set DCD output
                    ;   par bx:ActCCB, dx:port, al:0-inactive 1-active
H_RTS   EQU   8     ; inquire RTS, where applicable
                    ;   par bx:ActCCB, dx:port
H_CTS   EQU   10    ; set CTS, where applicable
                    ;   par bx:ActCCB, dx:port, al:0-inactive 1-active
H_LOUT  EQU   12    ; control output driver (on/off)
                    ;   par bx:ActCCB, dx:port, al:0-inactive 1-active
H_CBRK  EQU   14    ; check for break
                    ;   par bx:ActCCB, dx:port
                    ;   ret nz in ax if break
H_FLOUT EQU   16    ; hardware flush output
H_FLIN  EQU   18    ; hardware flush input
H_1PEN  EQU   20    ; 1pps enable, where applicable
H_1PDIS EQU   22    ; 1pps disable, where applicable
H_1PSTA EQU   24    ; 1pps status (0: not enabled)
H_1PMIS EQU   26    ; 1pps miss counter, incremented by tmr
H_OEMPT EQU   28    ; check for output drained
H_TMR   EQU   30    ; timer tick
H_KICK  EQU   32    ; kick the xmitter to restart it
H_MBRK  EQU   34    ; set/reset break xmission state
                    ;   par bx:ActCCB, dx:Port, al:0-reset,1-set
H_RVA   EQU   36  ; switch r/v/a on/off 
H_RES2  EQU   38
H_RES3  EQU   40
H_RES4  EQU   42
H_RES5  EQU   44
H_RES6  EQU   46
H_RES7  EQU   48

H_IOANZ EQU   24    ; 24 vectors so far
H_CPUCLK EQU   56
H_PAGE_SIZE EQU   58
H_FWE_START EQU   60
H_FWU_START EQU   62
H_RFW_PAGES  EQU   64
H_F_BUF     EQU   66
H_WEB_START EQU   68
H_WEB_PAGES EQU   70
H_PARTWEB_PAGES EQU 72
H_MAX_PORTS EQU   73
H_INT_NUMBER EQU  74

PAGE_SIZE EQU 0100h


XOFFLevel  equ   150  ; if less than .. space left, send XOFF
XONLevel   equ   500  ; XON is sent if more than .. space

ASC_XON  equ    11h     ; xon char
ASC_XOFF equ    13h     ; xoff char

; Definitionen fÅr V24 - Flags
F_TXOFF  equ    80h     ; stop xmit request
F_XXP    equ    40h     ; xon/xoff pass through ?
F_BRK    equ    20h     ; BREAK Flag
F_XX     equ    10h     ; xon/xoff used
F_STRIP  equ    08h     ; hi for 7 bit mode
F_TSTOP  equ    04h     ; if xmit disabled
F_RSTOP  equ    02h     ; if rx stop set
F_RXOFF  equ    01h     ; request xon/xoff sending, depends on RSTOP

ifdef C_LoRxVars    ; jb 18.11.02: was not able to assemble time.asm in module ec1    
C_LoRxPutPtr equ        C_LoRxVars+0
C_LoRxGetPtr equ        C_LoRxVars+2
C_LoRxS equ     C_LoRxVars+4
C_LoRxB equ     C_LoRxVars+6
V24Flags   equ  C_LoRxVars+8
RTSVal     equ  C_LoRxVars+9            ; value to and/or for rts
DCDVal     equ  C_LoRxVars+10           ; val for dcd
DTRVal     equ  C_LoRxVars+11           ; val for dtr input
V24Port    equ  C_LoRxVars+12   ; WORD
DMABuf     equ  C_LoRxVars+14           ; dma buffer start for this chan

C_LoTxPutPtr equ        C_LoTxVars+0
C_LoTxGetPtr equ        C_LoTxVars+2
C_LoTxS    equ  C_LoTxVars+4
C_LoTxB    equ  C_LoTxVars+6
V24Run     equ  C_LoTxVars+8
RSCC_A5    equ  C_LoTxVars+9
DMAPort    equ  C_LoTxVars+10            ; used by AMD
;TxIntRut   equ  C_LoTxVars+10   ; Word
TxBrkTim  equ  C_LoTxVars+12   ; Word
TxTmr  equ  C_LoTxVars+14    ; transmit timer (to fix 2 stop bits)
;TxTmr1  equ  C_LoTxVars+14    ; transmit using timer (only chan0 amd to fix 2 stop bits)
;TxTmr2  equ  C_LoTxVars+15
; C_LoRxFifo und C_LoTxFifo pointer werden als OFFSET gefÅhrt (0...NMAX-1)
endif
