   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
   4                     ; Optimizer V4.3.3 - 10 Feb 2010
  58                     ; 75 void delay_loop(u16 wt) {
  60                     	switch	.text
  61  0000               _delay_loop:
  63  0000 89            	pushw	x
  64       00000000      OFST:	set	0
  67  0001               L13:
  68                     ; 76 	while(wt--);
  70  0001 1e01          	ldw	x,(OFST+1,sp)
  71  0003 5a            	decw	x
  72  0004 1f01          	ldw	(OFST+1,sp),x
  73  0006 5c            	incw	x
  74  0007 26f8          	jrne	L13
  75                     ; 77 }
  78  0009 85            	popw	x
  79  000a 81            	ret	
 116                     ; 85 void write_message(u8 *msg) {
 117                     	switch	.text
 118  000b               _write_message:
 120  000b 89            	pushw	x
 121       00000000      OFST:	set	0
 124                     ; 86 	tbuf = Tx_buff;
 126  000c ae0018        	ldw	x,#_Tx_buff
 128  000f 2007          	jra	L75
 129  0011               L35:
 130                     ; 88 		*tbuf++ = *msg++;					// copy string to transmit buffer
 132  0011 5c            	incw	x
 133  0012 1f01          	ldw	(OFST+1,sp),x
 134  0014 be05          	ldw	x,_tbuf
 135  0016 f7            	ld	(x),a
 136  0017 5c            	incw	x
 137  0018               L75:
 138  0018 bf05          	ldw	_tbuf,x
 139                     ; 87 	while(tbuf < &Tx_buff[MAX_BUFFER-1]  &&  *msg != NUL)
 141  001a a30026        	cpw	x,#_Tx_buff+14
 142  001d 2407          	jruge	L36
 144  001f 1e01          	ldw	x,(OFST+1,sp)
 145  0021 f6            	ld	a,(x)
 146  0022 26ed          	jrne	L35
 147  0024 be05          	ldw	x,_tbuf
 148  0026               L36:
 149                     ; 89 	*tbuf++ = NUL;							// including the last byte
 151  0026 7f            	clr	(x)
 152  0027 5c            	incw	x
 153  0028 bf05          	ldw	_tbuf,x
 154                     ; 90 }
 157  002a 85            	popw	x
 158  002b 81            	ret	
 183                     ; 98 void read_message(void) {
 184                     	switch	.text
 185  002c               _read_message:
 189                     ; 99 	rbuf = Rx_buff;
 191  002c ae0009        	ldw	x,#_Rx_buff
 193  002f 2002          	jra	L101
 194  0031               L57:
 195                     ; 101 		*rbuf++ = NUL;						// clear receive buffer
 197  0031 7f            	clr	(x)
 198  0032 5c            	incw	x
 199  0033               L101:
 200  0033 bf07          	ldw	_rbuf,x
 201                     ; 100 	while(rbuf < &Rx_buff[MAX_BUFFER-1]  &&  *rbuf != NUL)
 203  0035 a30017        	cpw	x,#_Rx_buff+14
 204  0038 2405          	jruge	L501
 206  003a 92c607        	ld	a,[_rbuf.w]
 207  003d 26f2          	jrne	L57
 208  003f               L501:
 209                     ; 102 	*rbuf = NUL;							// including the last byte
 211  003f 923f07        	clr	[_rbuf.w]
 212                     ; 103 }
 215  0042 81            	ret	
 240                     ; 112 @far @interrupt void UARTTxInterrupt (void) {
 242                     	switch	.text
 243  0043               f_UARTTxInterrupt:
 247                     ; 116 	if(tbuf_ < tbuf)								// end of transmition checking
 249  0043 be01          	ldw	x,_tbuf_
 250  0045 b305          	cpw	x,_tbuf
 251  0047 2408          	jruge	L711
 252                     ; 117 		UART3->DR= *tbuf_++;
 254  0049 f6            	ld	a,(x)
 255  004a 5c            	incw	x
 256  004b bf01          	ldw	_tbuf_,x
 257  004d c75241        	ld	21057,a
 260  0050 80            	iret	
 261  0051               L711:
 262                     ; 119 		UART3->CR2&=~UART3_CR2_TIEN;
 264  0051 721f5245      	bres	21061,#7
 265                     ; 120 }
 268  0055 80            	iret	
 294                     ; 129 @far @interrupt void UARTRxInterrupt (void) {
 295                     	switch	.text
 296  0056               f_UARTRxInterrupt:
 300                     ; 133 	Rx_error|= (UART3->SR & 0x0F);			// read and save status register
 302  0056 c65240        	ld	a,21056
 303  0059 a40f          	and	a,#15
 304  005b ba00          	or	a,_Rx_error
 305  005d b700          	ld	_Rx_error,a
 306                     ; 134 	if((*rbuf_= UART3->DR) == NUL) {		// read a data byte - end of message?
 308  005f c65241        	ld	a,21057
 309  0062 92c703        	ld	[_rbuf_.w],a
 310  0065 2608          	jrne	L331
 311                     ; 135 		UART3->CR2&=~UART3_CR2_RIEN;			// YES - disable Rx interrupt
 313  0067 721b5245      	bres	21061,#5
 314                     ; 136 		RxBufRdy= TRUE;								// flag for main loop
 316  006b 72100000      	bset	_RxBufRdy
 317  006f               L331:
 318                     ; 138 	if(rbuf_ < &Rx_buff[MAX_BUFFER-1])		// Rx buffer overun checking
 321  006f be03          	ldw	x,_rbuf_
 322  0071 a30017        	cpw	x,#_Rx_buff+14
 323  0074 2404          	jruge	L531
 324                     ; 139 		++rbuf_;
 326  0076 5c            	incw	x
 327  0077 bf03          	ldw	_rbuf_,x
 330  0079 80            	iret	
 331  007a               L531:
 332                     ; 141 		Rx_error|= Rx_BUFF_OVFL;				// Rx buffer overflow
 334  007a 72180000      	bset	_Rx_error,#4
 335                     ; 142 }
 338  007e 80            	iret	
 372                     ; 150 void main(void) {
 374                     	switch	.text
 375  007f               _main:
 379                     ; 152 	GPIOH->ODR&=~ALL_LEDs; 				// LEDs - as push-pull outputs, all off
 381  007f c65023        	ld	a,20515
 382  0082 a4f0          	and	a,#240
 383  0084 c75023        	ld	20515,a
 384                     ; 153 	GPIOH->DDR|= ALL_LEDs; 
 386  0087 c65025        	ld	a,20517
 387  008a aa0f          	or	a,#15
 388  008c c75025        	ld	20517,a
 389                     ; 154 	GPIOH->CR1|= ALL_LEDs;
 391  008f c65026        	ld	a,20518
 392  0092 aa0f          	or	a,#15
 393  0094 c75026        	ld	20518,a
 394                     ; 157 	UART3->CR1&=~UART3_CR1_M;					// 8 data bits
 396  0097 72195244      	bres	21060,#4
 397                     ; 158 	UART3->CR3|= (0<<4) & UART3_CR3_STOP;	// 1 stop bit
 399  009b c65246        	ld	a,21062
 400                     ; 159 	UART3->BRR2= 3 & UART3_BRR2_DIVF;		//57600 Bd
 402  009e 35035243      	mov	21059,#3
 403                     ; 160 	UART3->BRR1= 2;
 405  00a2 35025242      	mov	21058,#2
 406                     ; 161 	UART3->CR2|= UART3_CR2_TEN | UART3_CR2_REN; // transmit & receive enable
 408  00a6 c65245        	ld	a,21061
 409  00a9 aa0c          	or	a,#12
 410  00ab c75245        	ld	21061,a
 411                     ; 163 	enableInterrupts();							// all interrupts enable
 414  00ae 9a            	rim	
 416  00af               L151:
 417                     ; 167 		switch_all_LEDs_on;									// LEDs on
 419  00af c65023        	ld	a,20515
 420  00b2 aa0f          	or	a,#15
 421  00b4 c75023        	ld	20515,a
 422                     ; 168 		write_message("Hello world!");					// prepare transmit buffer
 425  00b7 ae0000        	ldw	x,#L551
 426  00ba cd000b        	call	_write_message
 428                     ; 169 		init_receiving;
 430  00bd ae0009        	ldw	x,#_Rx_buff
 431  00c0 bf07          	ldw	_rbuf,x
 432  00c2 bf03          	ldw	_rbuf_,x
 435  00c4 3f00          	clr	_Rx_error
 438  00c6 72110000      	bres	_RxBufRdy
 441                     ; 170 		init_transmition;
 444  00ca 721a5245      	bset	21061,#5
 445  00ce ae0018        	ldw	x,#_Tx_buff
 448  00d1 f6            	ld	a,(x)
 449  00d2 5c            	incw	x
 450  00d3 bf01          	ldw	_tbuf_,x
 451  00d5 c75241        	ld	21057,a
 454                     ; 171 		delay_loop(1000);
 457  00d8 ae03e8        	ldw	x,#1000
 458  00db 721e5245      	bset	21061,#7
 459  00df cd0000        	call	_delay_loop
 461                     ; 172 		if(RxBufRdy != TRUE  ||  Rx_error != 0 || strcmp(Tx_buff, Rx_buff) != 0) // Message is received correctly?
 463  00e2 7201000013    	btjf	_RxBufRdy,L161
 465  00e7 b600          	ld	a,_Rx_error
 466  00e9 260f          	jrne	L161
 468  00eb ae0009        	ldw	x,#_Rx_buff
 469  00ee 89            	pushw	x
 470  00ef ae0018        	ldw	x,#_Tx_buff
 471  00f2 cd0000        	call	_strcmp
 473  00f5 5b02          	addw	sp,#2
 474  00f7 5d            	tnzw	x
 475  00f8 2710          	jreq	L751
 476  00fa               L161:
 477                     ; 173 			switch_all_LEDs_off								// LEDs off if the data byte isn't correctly received
 479  00fa c65023        	ld	a,20515
 480  00fd a4f0          	and	a,#240
 481  00ff c75023        	ld	20515,a
 483  0102               L561:
 484                     ; 176 		delay_loop(10000);									// let the LEDs indication be observed
 486  0102 ae2710        	ldw	x,#10000
 487  0105 cd0000        	call	_delay_loop
 490  0108 20a5          	jra	L151
 491  010a               L751:
 492                     ; 175 			read_message();									// received message processing
 494  010a cd002c        	call	_read_message
 496  010d 20f3          	jra	L561
 599                     	xdef	_main
 600                     	xdef	f_UARTRxInterrupt
 601                     	xdef	f_UARTTxInterrupt
 602                     	xdef	_read_message
 603                     	xdef	_write_message
 604                     	xdef	_delay_loop
 605                     .bit:	section	.data,bit
 606  0000               _RxBufRdy:
 607  0000 00            	ds.b	1
 608                     	xdef	_RxBufRdy
 609                     	switch	.ubsct
 610  0000               _Rx_error:
 611  0000 00            	ds.b	1
 612                     	xdef	_Rx_error
 613  0001               _tbuf_:
 614  0001 0000          	ds.b	2
 615                     	xdef	_tbuf_
 616  0003               _rbuf_:
 617  0003 0000          	ds.b	2
 618                     	xdef	_rbuf_
 619  0005               _tbuf:
 620  0005 0000          	ds.b	2
 621                     	xdef	_tbuf
 622  0007               _rbuf:
 623  0007 0000          	ds.b	2
 624                     	xdef	_rbuf
 625  0009               _Rx_buff:
 626  0009 000000000000  	ds.b	15
 627                     	xdef	_Rx_buff
 628  0018               _Tx_buff:
 629  0018 000000000000  	ds.b	15
 630                     	xdef	_Tx_buff
 631  0027               _sts:
 632  0027 00            	ds.b	1
 633                     	xdef	_sts
 634                     	xref	_strcmp
 635                     .const:	section	.text
 636  0000               L551:
 637  0000 48656c6c6f20  	dc.b	"Hello world!",0
 657                     	end
