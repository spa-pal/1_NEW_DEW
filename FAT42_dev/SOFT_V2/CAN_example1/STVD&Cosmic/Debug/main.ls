   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
   4                     ; Optimizer V4.3.3 - 10 Feb 2010
  19                     .const:	section	.text
  20  0000               _MY_MESS:
  21  0000 04            	dc.b	4
  22  0001 01            	dc.b	1
  23  0002 40            	dc.b	64
  24  0003 00            	dc.b	0
  25  0004 00            	dc.b	0
  26  0005 aa            	dc.b	170
  27  0006 cc            	dc.b	204
  28  0007 55            	dc.b	85
  29  0008 33            	dc.b	51
  69                     ; 92 void delay_loop(u32 wt) {
  71                     	switch	.text
  72  0000               _delay_loop:
  74       00000000      OFST:	set	0
  77  0000               L13:
  78                     ; 93 	while(wt--);
  80  0000 96            	ldw	x,sp
  81  0001 1c0003        	addw	x,#OFST+3
  82  0004 cd0000        	call	c_ltor
  84  0007 96            	ldw	x,sp
  85  0008 1c0003        	addw	x,#OFST+3
  86  000b a601          	ld	a,#1
  87  000d cd0000        	call	c_lgsbc
  89  0010 cd0000        	call	c_lrzmp
  91  0013 26eb          	jrne	L13
  92                     ; 94 }
  95  0015 81            	ret	
 118                     ; 96 void init_CAN(void) {
 119                     	switch	.text
 120  0016               _init_CAN:
 124                     ; 97 	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
 126  0016 72135420      	bres	21536,#1
 127                     ; 98 	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
 129  001a 72105420      	bset	21536,#0
 131  001e               L74:
 132                     ; 99 	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
 134  001e 72015421fb    	btjf	21537,#0,L74
 135                     ; 101 	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
 137  0023 72185420      	bset	21536,#4
 138                     ; 103 	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
 140  0027 35025427      	mov	21543,#2
 141                     ; 107 	CAN->Page.Filter01.F0R1= MY_MESS_STID>>3;			// 8 bits mode
 143  002b 350a5428      	mov	21544,#10
 144                     ; 128 	CAN->PSR= 6;									// set page 6
 146  002f 35065427      	mov	21543,#6
 147                     ; 130 	CAN->Page.Config.FMR1|= 3;								//list mode
 149  0033 c65430        	ld	a,21552
 150  0036 aa03          	or	a,#3
 151  0038 c75430        	ld	21552,a
 152                     ; 136 	CAN->Page.Config.FCR1&= ~(CAN_FCR1_FSC00 | CAN_FCR1_FSC01);			//8 bit scale 
 154  003b c65432        	ld	a,21554
 155  003e a4f9          	and	a,#249
 156  0040 c75432        	ld	21554,a
 157                     ; 142 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
 159  0043 72105432      	bset	21554,#0
 160                     ; 145 	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
 162  0047 35065427      	mov	21543,#6
 163                     ; 147 	CAN->Page.Config.BTR1= 4;					// CAN_BTR1_BRP=4, 	tq= fcpu/(4+1)
 165  004b 3504542c      	mov	21548,#4
 166                     ; 148 	CAN->Page.Config.BTR2= (2<<4) | 3; 		// BS2=4, BS1=3, 		Tbit= (1+(BS2+1)+(BS1+1))*tq ~50 Kbit/s
 168  004f 3523542d      	mov	21549,#35
 169                     ; 151 	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
 171  0053 72115420      	bres	21536,#0
 173  0057               L55:
 174                     ; 152 	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
 176  0057 72005421fb    	btjt	21537,#0,L55
 177                     ; 153 }
 180  005c 81            	ret	
 230                     ; 155 void main(void) {
 231                     	switch	.text
 232  005d               _main:
 234  005d 5203          	subw	sp,#3
 235       00000003      OFST:	set	3
 238                     ; 159 	GPIOH->ODR&=~ALL_LEDs; 						// LEDs - as push-pull outputs, all off
 240  005f c65023        	ld	a,20515
 241  0062 a4f0          	and	a,#240
 242  0064 c75023        	ld	20515,a
 243                     ; 160 	GPIOH->DDR|= ALL_LEDs;
 245  0067 c65025        	ld	a,20517
 246  006a aa0f          	or	a,#15
 247  006c c75025        	ld	20517,a
 248                     ; 161 	GPIOH->CR1|= ALL_LEDs;
 250  006f c65026        	ld	a,20518
 251  0072 aa0f          	or	a,#15
 252  0074 c75026        	ld	20518,a
 253                     ; 163 	init_CAN();
 255  0077 ad9d          	call	_init_CAN
 257                     ; 164 	CAN->DGR|= CAN_DGR_LBKM;					// set CAN in loop back mode
 259  0079 72105426      	bset	21542,#0
 260                     ; 166 	leds= 0;											// utility variables
 262  007d 3f00          	clr	_leds
 263                     ; 167 	id_offset= -1;
 265  007f 35ff0010      	mov	_id_offset,#255
 266  0083               L301:
 267                     ; 171 		CAN->PSR= 0;								// send my message
 269  0083 725f5427      	clr	21543
 270                     ; 172 		memcpy(&CAN->Page.TxMailbox.MDLCR, &MY_MESS[0], MY_MESS_DLC + 5);
 272  0087 ae0009        	ldw	x,#9
 273  008a               L41:
 274  008a d6ffff        	ld	a,(_MY_MESS-1,x)
 275  008d d75428        	ld	(21544,x),a
 276  0090 5a            	decw	x
 277  0091 26f7          	jrne	L41
 278                     ; 173 		id_offset= ++id_offset & 0x0F;
 280  0093 3c10          	inc	_id_offset
 281  0095 b610          	ld	a,_id_offset
 282  0097 a40f          	and	a,#15
 283  0099 b710          	ld	_id_offset,a
 284                     ; 174 		CAN->Page.TxMailbox.MIDR2+= (id_offset<<2);
 286  009b 48            	sll	a
 287  009c 48            	sll	a
 288  009d cb542b        	add	a,21547
 289  00a0 c7542b        	ld	21547,a
 290                     ; 175 		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;		// transmit request
 292                     ; 176 		tout= 50000;
 294  00a3 aec350        	ldw	x,#50000
 295  00a6 72105428      	bset	21544,#0
 296  00aa 1f02          	ldw	(OFST-1,sp),x
 298  00ac               L311:
 299                     ; 177 		while((CAN->TSR & CAN_TSR_TXOK0) == 0  &&  --tout > 0);	// wait for transmition OK
 301  00ac 7208542203    	btjt	21538,#4,LC001
 303  00b1 5a            	decw	x
 304  00b2 26f8          	jrne	L311
 305  00b4               LC001:
 306  00b4 1f02          	ldw	(OFST-1,sp),x
 307                     ; 178 		if(tout) {
 309  00b6 2714          	jreq	L121
 310                     ; 179 			set_Tx_LEDs();
 312  00b8 b610          	ld	a,_id_offset
 313  00ba 2606          	jrne	L321
 316  00bc 72165023      	bset	20515,#3
 318  00c0 2004          	jra	L521
 319  00c2               L321:
 322  00c2 72145023      	bset	20515,#2
 323  00c6               L521:
 324                     ; 180 			CAN->TSR|= CAN_TSR_RQCP0;
 327  00c6 72105422      	bset	21538,#0
 329  00ca 2009          	jra	L721
 330  00cc               L121:
 331                     ; 183 			if(CAN->Page.TxMailbox.MCSR & CAN_MCSR_TERR)
 333  00cc 720b542804    	btjf	21544,#5,L721
 334                     ; 184 				CAN->Page.TxMailbox.MCSR|= CAN_MCSR_ABRQ;
 336  00d1 72125428      	bset	21544,#1
 337  00d5               L721:
 338                     ; 186 		tout= 50000;
 340  00d5 aec350        	ldw	x,#50000
 341  00d8 1f02          	ldw	(OFST-1,sp),x
 343  00da               L731:
 344                     ; 187 		while((CAN->RFR & CAN_RFR_FMP01) == 0 &&  --tout > 0);		// wait for any CAN receive message
 346  00da c65424        	ld	a,21540
 347  00dd a503          	bcp	a,#3
 348  00df 2603          	jrne	LC002
 350  00e1 5a            	decw	x
 351  00e2 26f6          	jrne	L731
 352  00e4               LC002:
 353  00e4 1f02          	ldw	(OFST-1,sp),x
 354                     ; 189 		if(tout) {
 356  00e6 2748          	jreq	L541
 357                     ; 190 			CAN->PSR= 7;									// page 7 - read messsage
 359  00e8 35075427      	mov	21543,#7
 361  00ec 203b          	jra	L351
 362  00ee               L741:
 363                     ; 192 				memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
 365  00ee ae000e        	ldw	x,#14
 366  00f1               L61:
 367  00f1 d65427        	ld	a,(21543,x)
 368  00f4 e701          	ld	(_mess-1,x),a
 369  00f6 5a            	decw	x
 370  00f7 26f8          	jrne	L61
 371                     ; 193 				for(i=5; i<MY_MESS_DLC+5; ++i)
 373  00f9 a605          	ld	a,#5
 374  00fb 6b01          	ld	(OFST-2,sp),a
 375  00fd               L751:
 376                     ; 194 					if(mess[i+1]!=MY_MESS[i]) { tout= 0; break;	};
 378  00fd 5f            	clrw	x
 379  00fe 97            	ld	xl,a
 380  00ff 905f          	clrw	y
 381  0101 9097          	ld	yl,a
 382  0103 90e603        	ld	a,(_mess+1,y)
 383  0106 d10000        	cp	a,(_MY_MESS,x)
 384  0109 2705          	jreq	L561
 387  010b 5f            	clrw	x
 388  010c 1f02          	ldw	(OFST-1,sp),x
 391  010e 2008          	jra	L361
 392  0110               L561:
 393                     ; 193 				for(i=5; i<MY_MESS_DLC+5; ++i)
 395  0110 0c01          	inc	(OFST-2,sp)
 398  0112 7b01          	ld	a,(OFST-2,sp)
 399  0114 a109          	cp	a,#9
 400  0116 25e5          	jrult	L751
 401  0118               L361:
 402                     ; 195 				if(tout)
 405  0118 1e02          	ldw	x,(OFST-1,sp)
 406  011a 2704          	jreq	L761
 407                     ; 196 					set_Rx_LEDs();
 409  011c 72105023      	bset	20515,#0
 410  0120               L761:
 411                     ; 197 				CAN->RFR|= CAN_RFR_RFOM;				// release received message
 414  0120 721a5424      	bset	21540,#5
 416  0124               L371:
 417                     ; 198 				while(CAN->RFR & CAN_RFR_RFOM);		// wait until the current message is released
 419  0124 720a5424fb    	btjt	21540,#5,L371
 420  0129               L351:
 421                     ; 191 			while (CAN->RFR & CAN_RFR_FMP01) {				// make up all received messages
 423  0129 c65424        	ld	a,21540
 424  012c a503          	bcp	a,#3
 425  012e 26be          	jrne	L741
 427  0130               L541:
 428                     ; 203 		delay_loop((u32)( 5000));
 431  0130 ae1388        	ldw	x,#5000
 432  0133 89            	pushw	x
 433  0134 5f            	clrw	x
 434  0135 89            	pushw	x
 435  0136 cd0000        	call	_delay_loop
 437  0139 5b04          	addw	sp,#4
 438                     ; 204 		switch_LEDs_off();
 440  013b c65023        	ld	a,20515
 441  013e a4f0          	and	a,#240
 442  0140 c75023        	ld	20515,a
 443                     ; 205 		delay_loop((u32)(15000));
 446  0143 ae3a98        	ldw	x,#15000
 447  0146 89            	pushw	x
 448  0147 5f            	clrw	x
 449  0148 89            	pushw	x
 450  0149 cd0000        	call	_delay_loop
 452  014c 5b04          	addw	sp,#4
 454  014e cc0083        	jra	L301
 516                     	xdef	_main
 517                     	xdef	_init_CAN
 518                     	xdef	_delay_loop
 519                     	xdef	_MY_MESS
 520                     	switch	.ubsct
 521  0000               _leds:
 522  0000 00            	ds.b	1
 523                     	xdef	_leds
 524  0001               _byte_counter:
 525  0001 00            	ds.b	1
 526                     	xdef	_byte_counter
 527  0002               _mess:
 528  0002 000000000000  	ds.b	14
 529                     	xdef	_mess
 530  0010               _id_offset:
 531  0010 00            	ds.b	1
 532                     	xdef	_id_offset
 552                     	xref	c_lrzmp
 553                     	xref	c_lgsbc
 554                     	xref	c_ltor
 555                     	end
