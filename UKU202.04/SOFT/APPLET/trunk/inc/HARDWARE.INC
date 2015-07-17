; VERS ist Hardware-Version:
; 10=ProtoSeriell  11=Akt.Seriell 20=Doppel 30=Hilfschnitt 40=Parallel
; 50=Hispeed 60=8fach
; 100=Ethernet 1.0

VERS	equ	100

      .186

RAM_MAX	equ	0000h	; max. 64k RAM

	IF	(VERS EQ 10) OR (VERS EQ 11) OR (VERS EQ 30) OR (VERS EQ 40)
RAM_SIZE	equ	2000h
	ENDIF

	IF	(VERS EQ 20) OR (VERS EQ 50) OR (VERS EQ 60) OR (VERS EQ 100)
RAM_SIZE	equ	8000h	; 32k
	ENDIF


; <<< DMA >>>

	IF	(VERS EQ 100)
DMAU	equ	0c0h
	ELSE
DMAU    equ       080h
	ENDIF
  DMA_CH   equ      DMAU+1
  DMA_CNT  equ      DMAU+2
  DMA_ADR  equ      DMAU+4
  DMA_HIA  equ      DMAU+6
  DMA_DCR  equ      DMAU+8
  DMA_MOD  equ      DMAU+0ah
  DMA_STA  equ      DMAU+0bh
  DMA_MSK  equ      DMAU+0fh

ChanTrans equ 0
ChanInp equ 1
ChanOut equ 2

DmaSelect macro channel
  mov al,channel
  out DMA_CH,al
endm

DmaLoad macro addr,count
  mov ax,addr
  out DMA_ADR,ax
  mov ax,count-1
  out DMA_CNT,ax
endm

DmaInit macro mode
  xor al,al
  out DMA_HIA,al
  mov al,mode
  out DMA_MOD,al
endm


; <<< Interrupt >>>

ICU     equ       090h
  ICU_MSK  equ      ICU+1

I_LDP  equ  80h    ; LCA d/p readback
I_RDAT equ  40h    ; SETUP RAM data readback

BaseIntNum equ 8
LevelLocIo equ 1
LevelNic   equ 2
LevelNetTx equ 3
LevelNetRx equ 5

; <<< Net LCA >>>

	IF	(VERS LT 100)

NetTxFake macro
mov     al,HOLDBIT+PASSBIT+FAKEBIT
        out     LCAPORT,al
        mov     al,HOLDBIT+PASSBIT
        out     LCAPORT,al
endm
	ELSE
NetTxFake macro
endm
	ENDIF

; <<< Counter >>>

TCU     equ       0a0h
  TCU_0   equ       TCU
  TCU_1   equ       TCU+1
  TCU_2   equ       TCU+2
  TCU_MODE equ      TCU+3


; <<< Serial >>>

SCU     equ       0b0h
  SCU_DAT  equ      SCU+0
  SCU_CMD  equ      SCU+1
  SCU_STAT equ      SCU+1
  SCU_MODE equ      SCU+2
  SCU_MSK  equ      SCU+3

; <<< SCC Hispeed + Double >>>

	IF	VERS EQ 20		; Double
SCC     equ     0f0h
  SCC_AC   equ      SCC+2
  SCC_AD   equ      SCC+3
  SCC_BC   equ      SCC+0
  SCC_BD   equ      SCC+1
	ENDIF
	IF	(VERS EQ 30) or (VERS EQ 50) or (VERS EQ 60)
SCC	equ     020h
  SCC_AC   equ      SCC+2
  SCC_AD   equ      SCC+3
  SCC_BC   equ      SCC+0
  SCC_BD   equ      SCC+1
	ENDIF
	IF	(VERS GE 100)		; Ethernet
SCC     equ     080h
  SCC_AC   equ      SCC+2
  SCC_AD   equ      SCC+3
  SCC_BC   equ      SCC+0
  SCC_BD   equ      SCC+1
	ENDIF

SerIntVec  equ    9      ; vector for serial interrupt


; <<< LCA >>>
	IF (VERS EQ 100)
LCAPORT equ 40h
HOLDBIT equ 80h
PASSBIT equ 40h
FAKEBIT equ 02h
LCARTS  equ 10h
LCADTR  equ 40h
X_MON   equ 80h
	ENDIF
; <<< Sonstiges >>>

OUTLATCH equ 00H

OVAL = 0

	IF	(VERS EQ 10)
L_CTS   equ    2     ; ClearToSend and Done/PGM Bit
L_LDP   equ    2     ; LCA Done/Pgm
L_LRES  equ    1     ; LCA Reset
L_WATCH equ    40h   ; watchdog bit
L_LEDR  equ    10h   ; Led Rot
L_LEDG  equ    20h   ; Led Gr］
L_LDAT  equ    8     ; LCA data line
L_LCLK  equ    80h   ; LCA clock line
L_RDAT  equ    8     ; SETUPRAM data line
L_RCLK  equ    80h   ; SETUPRAM clock line
L_DCD	equ	0    ; gibt es nicht !
L_LEDY	equ	0
	ENDIF

	IF	(VERS EQ 11) OR (VERS EQ 20) OR (VERS EQ 30) OR (VERS EQ 50)
L_CTS   equ    8     ; ClearToSend
L_DCD   equ    40h   ; DataSetReady Bit
L_LDP   equ    2     ; LCA Done/Pgm
L_LRES  equ    1     ; LCA Reset
L_LEDR  equ    10h   ; Led Rot
L_LEDG  equ    20h   ; Led Gr］
L_LDAT  equ    20h   ; LCA data line
L_LCLK  equ    80h   ; LCA clock line
L_RDAT  equ    10h   ; SETUPRAM data line
L_RCLK  equ    80h   ; SETUPRAM clock line
L_LEDY	equ	0
WATCHPORT equ  00h
        ENDIF

	IF	(VERS EQ 60)
L_CTS   equ    8     ; ClearToSend
L_DCD   equ    40h   ; DataSetReady Bit
L_LDP   equ    2     ; LCA Done/Pgm
L_LRES  equ    1     ; LCA Reset
L_LEDR  equ    10h   ; Led Rot
L_LEDG  equ    20h   ; Led Gr］
L_LEDY	equ    40h   ; Led Gelb
L_LDAT  equ    20h   ; LCA data line
L_LCLK  equ    80h   ; LCA clock line
L_RDAT  equ    10h   ; SETUPRAM data line
L_RCLK  equ    80h   ; SETUPRAM clock line
WATCHPORT equ  00h
        ENDIF

	IF	(VERS EQ 40)
L_PO16  equ    8     ; ClearToSend
L_LRE2	equ    8     ; LCA 2 Reset
L_LDP   equ    2     ; LCA Done/Pgm
L_LRES  equ    1     ; LCA Reset
L_LEDR  equ    10h   ; Led Rot
L_LEDG  equ    20h   ; Led Gr］
L_LDAT  equ    20h   ; LCA data line
L_LDA2	equ    40h   ; LCA 2 data line
L_LCLK  equ    80h   ; LCA clock line
L_RDAT  equ    10h   ; SETUPRAM data line
L_RCLK  equ    80h   ; SETUPRAM clock line
L_LEDY	equ	0
WATCHPORT equ  00h
        ENDIF

	IF	(VERS EQ 100)
L_LDP   equ    2     ; LCA Done/Pgm
L_LRES  equ    1     ; LCA Reset
L_LEDG  equ    01h   ; Led Gr］
L_LEDR  equ    02h   ; Led Rot
L_RDAT  equ    20h   ; SETUPRAM data line
L_RCLK  equ    80h   ; SETUPRAM clock line
L_RCS	equ    10h   ; SETUPRAM CS line
L_RCS2	equ     0h   ; SETUPRAM CS line (RAM #2)
L_LEDY  equ    40h   ; dritte LED
L_WATCH	equ    80h  ; watchdog is same as setupram clock !
L_XORIT	equ    (L_LEDG OR L_LEDR)
WATCHPORT equ  0F0h
        ENDIF

; OPCN Register - LocIOInt intern oder extern ?
	IF	(VERS EQ 20) OR (VERS EQ 30) OR (VERS EQ 50) OR (VERS EQ 60)
R_OPCN	equ	01h
R_OPSEL	equ	0fh
	ENDIF
	IF	(VERS EQ 10) OR (VERS EQ 11) OR (VERS EQ 40)
R_OPCN	equ	07h
R_OPSEL	equ	0fh
	ENDIF
	IF	(VERS EQ 100)
R_OPCN	equ	03h
R_OPSEL	equ	0fh
	ENDIF

; TIMCTL timer control register (baud rate cntr ...)
	IF	(VERS EQ 50)
TIMCTL	equ	18h	; timer 0 at clk/2 timer 1,2 ext clk
	ELSE
TIMCTL	equ	00h	; all timers at clk/2
	ENDIF

EEPR_SEG	equ	08000h
CODE_SEG	equ	0c000h


	IF	(VERS EQ 10)
watch0  macro
        mov       al,L_WATCH or OVAL
        out       OUTLATCH,al
        xor       al,L_WATCH
        out       OUTLATCH,al
        endm
	ELSE
watch0  macro
	in        al,WATCHPORT
        endm
        ENDIF
