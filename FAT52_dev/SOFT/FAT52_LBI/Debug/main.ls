   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  15                     	bsct
  16  0000               _t0_cnt0:
  17  0000 00            	dc.b	0
  18  0001               _t0_cnt1:
  19  0001 00            	dc.b	0
  20  0002               _t0_cnt2:
  21  0002 00            	dc.b	0
  22  0003               _t0_cnt3:
  23  0003 00            	dc.b	0
  24  0004               _t0_cnt4:
  25  0004 00            	dc.b	0
  26                     	switch	.data
  27  0000               _tx_buffer1:
  28  0000 00            	dc.b	0
  29  0001 000000000000  	ds.b	49
  30  0032               _rx_buffer:
  31  0032 00            	dc.b	0
  32  0033 000000000000  	ds.b	299
  33                     	bsct
  34  0005               _tx_stat:
  35  0005 00            	dc.b	0
  36  0006               _tx_wd_cnt:
  37  0006 64            	dc.b	100
  38  0007               _bTX_FREE:
  39  0007 01            	dc.b	1
  40  0008               _bCAN_RX:
  41  0008 00            	dc.b	0
  42  0009               _led_ind:
  43  0009 05            	dc.b	5
  44  000a               _adr_drv_stat:
  45  000a 00            	dc.b	0
  46  000b               _rs485_cnt:
  47  000b 00            	dc.b	0
 106                     ; 109 void gran_char(signed char *adr, signed char min, signed char max)
 106                     ; 110 {
 108                     	switch	.text
 109  0000               _gran_char:
 111  0000 89            	pushw	x
 112       00000000      OFST:	set	0
 115                     ; 111 if (*adr<min) *adr=min;
 117  0001 9c            	rvf
 118  0002 f6            	ld	a,(x)
 119  0003 1105          	cp	a,(OFST+5,sp)
 120  0005 2e05          	jrsge	L73
 123  0007 7b05          	ld	a,(OFST+5,sp)
 124  0009 1e01          	ldw	x,(OFST+1,sp)
 125  000b f7            	ld	(x),a
 126  000c               L73:
 127                     ; 112 if (*adr>max)  *adr=max; 
 129  000c 9c            	rvf
 130  000d 1e01          	ldw	x,(OFST+1,sp)
 131  000f f6            	ld	a,(x)
 132  0010 1106          	cp	a,(OFST+6,sp)
 133  0012 2d05          	jrsle	L14
 136  0014 7b06          	ld	a,(OFST+6,sp)
 137  0016 1e01          	ldw	x,(OFST+1,sp)
 138  0018 f7            	ld	(x),a
 139  0019               L14:
 140                     ; 113 }
 143  0019 85            	popw	x
 144  001a 81            	ret
 197                     ; 116 void gran(signed short *adr, signed short min, signed short max)
 197                     ; 117 {
 198                     	switch	.text
 199  001b               _gran:
 201  001b 89            	pushw	x
 202       00000000      OFST:	set	0
 205                     ; 118 if (*adr<min) *adr=min;
 207  001c 9c            	rvf
 208  001d 9093          	ldw	y,x
 209  001f 51            	exgw	x,y
 210  0020 fe            	ldw	x,(x)
 211  0021 1305          	cpw	x,(OFST+5,sp)
 212  0023 51            	exgw	x,y
 213  0024 2e03          	jrsge	L17
 216  0026 1605          	ldw	y,(OFST+5,sp)
 217  0028 ff            	ldw	(x),y
 218  0029               L17:
 219                     ; 119 if (*adr>max)  *adr=max; 
 221  0029 9c            	rvf
 222  002a 1e01          	ldw	x,(OFST+1,sp)
 223  002c 9093          	ldw	y,x
 224  002e 51            	exgw	x,y
 225  002f fe            	ldw	x,(x)
 226  0030 1307          	cpw	x,(OFST+7,sp)
 227  0032 51            	exgw	x,y
 228  0033 2d05          	jrsle	L37
 231  0035 1e01          	ldw	x,(OFST+1,sp)
 232  0037 1607          	ldw	y,(OFST+7,sp)
 233  0039 ff            	ldw	(x),y
 234  003a               L37:
 235                     ; 120 }
 238  003a 85            	popw	x
 239  003b 81            	ret
 262                     ; 126 void uart1_init (void)
 262                     ; 127 {
 263                     	switch	.text
 264  003c               _uart1_init:
 268                     ; 129 GPIOA->DDR&=~(1<<4);
 270  003c 72195002      	bres	20482,#4
 271                     ; 130 GPIOA->CR1|=(1<<4);
 273  0040 72185003      	bset	20483,#4
 274                     ; 131 GPIOA->CR2&=~(1<<4);
 276  0044 72195004      	bres	20484,#4
 277                     ; 134 GPIOA->DDR|=(1<<5);
 279  0048 721a5002      	bset	20482,#5
 280                     ; 135 GPIOA->CR1|=(1<<5);
 282  004c 721a5003      	bset	20483,#5
 283                     ; 136 GPIOA->CR2&=~(1<<5);	
 285  0050 721b5004      	bres	20484,#5
 286                     ; 139 GPIOB->DDR|=(1<<6);
 288  0054 721c5007      	bset	20487,#6
 289                     ; 140 GPIOB->CR1|=(1<<6);
 291  0058 721c5008      	bset	20488,#6
 292                     ; 141 GPIOB->CR2&=~(1<<6);
 294  005c 721d5009      	bres	20489,#6
 295                     ; 142 GPIOB->ODR|=(1<<6);		//—разу в 1
 297  0060 721c5005      	bset	20485,#6
 298                     ; 145 GPIOB->DDR|=(1<<7);
 300  0064 721e5007      	bset	20487,#7
 301                     ; 146 GPIOB->CR1|=(1<<7);
 303  0068 721e5008      	bset	20488,#7
 304                     ; 147 GPIOB->CR2&=~(1<<7);
 306  006c 721f5009      	bres	20489,#7
 307                     ; 149 UART1->CR1&=~UART1_CR1_M;					
 309  0070 72195234      	bres	21044,#4
 310                     ; 150 UART1->CR3|= (0<<4) & UART1_CR3_STOP;  	
 312  0074 c65236        	ld	a,21046
 313                     ; 151 UART1->BRR2= 0x09;
 315  0077 35095233      	mov	21043,#9
 316                     ; 152 UART1->BRR1= 0x20;
 318  007b 35205232      	mov	21042,#32
 319                     ; 153 UART1->CR2|= UART1_CR2_TEN | UART1_CR2_REN | UART1_CR2_RIEN/*| UART2_CR2_TIEN*/ ;	
 321  007f c65235        	ld	a,21045
 322  0082 aa2c          	or	a,#44
 323  0084 c75235        	ld	21045,a
 324                     ; 154 }
 327  0087 81            	ret
 364                     ; 157 void putchar1(char c)
 364                     ; 158 {
 365                     	switch	.text
 366  0088               _putchar1:
 368  0088 88            	push	a
 369       00000000      OFST:	set	0
 372  0089               L521:
 373                     ; 159 while (tx_counter1 == TX_BUFFER_SIZE1);
 375  0089 b6bb          	ld	a,_tx_counter1
 376  008b a132          	cp	a,#50
 377  008d 27fa          	jreq	L521
 378                     ; 161 if (tx_counter1 || ((UART1->SR & UART1_SR_TXE)==0))
 380  008f 3dbb          	tnz	_tx_counter1
 381  0091 2607          	jrne	L331
 383  0093 c65230        	ld	a,21040
 384  0096 a580          	bcp	a,#128
 385  0098 2622          	jrne	L131
 386  009a               L331:
 387                     ; 163    tx_buffer1[tx_wr_index1]=c;
 389  009a 5f            	clrw	x
 390  009b b6ba          	ld	a,_tx_wr_index1
 391  009d 2a01          	jrpl	L41
 392  009f 53            	cplw	x
 393  00a0               L41:
 394  00a0 97            	ld	xl,a
 395  00a1 7b01          	ld	a,(OFST+1,sp)
 396  00a3 d70000        	ld	(_tx_buffer1,x),a
 397                     ; 164    if (++tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
 399  00a6 3cba          	inc	_tx_wr_index1
 400  00a8 b6ba          	ld	a,_tx_wr_index1
 401  00aa a132          	cp	a,#50
 402  00ac 2602          	jrne	L531
 405  00ae 3fba          	clr	_tx_wr_index1
 406  00b0               L531:
 407                     ; 165    ++tx_counter1;
 409  00b0 3cbb          	inc	_tx_counter1
 411  00b2               L731:
 412                     ; 169 UART1->CR2|= UART1_CR2_TIEN | UART1_CR2_TCIEN;
 414  00b2 c65235        	ld	a,21045
 415  00b5 aac0          	or	a,#192
 416  00b7 c75235        	ld	21045,a
 417                     ; 170 }
 420  00ba 84            	pop	a
 421  00bb 81            	ret
 422  00bc               L131:
 423                     ; 167 else UART1->DR=c;
 425  00bc 7b01          	ld	a,(OFST+1,sp)
 426  00be c75231        	ld	21041,a
 427  00c1 20ef          	jra	L731
 502                     ; 174 void uart1_out_adr(char *ptr, char len)
 502                     ; 175 {
 503                     	switch	.text
 504  00c3               _uart1_out_adr:
 506  00c3 89            	pushw	x
 507  00c4 5220          	subw	sp,#32
 508       00000020      OFST:	set	32
 511                     ; 177 @near char i,t=0;
 513  00c6 0f01          	clr	(OFST-31,sp)
 514                     ; 181 GPIOB->ODR|=(1<<7);
 516  00c8 721e5005      	bset	20485,#7
 517                     ; 184 for(i=0;i<len;i++)
 519  00cc 0f20          	clr	(OFST+0,sp)
 521  00ce 201d          	jra	L302
 522  00d0               L771:
 523                     ; 186 	UOB1[i]=ptr[i];
 525  00d0 96            	ldw	x,sp
 526  00d1 1c0002        	addw	x,#OFST-30
 527  00d4 9f            	ld	a,xl
 528  00d5 5e            	swapw	x
 529  00d6 1b20          	add	a,(OFST+0,sp)
 530  00d8 2401          	jrnc	L02
 531  00da 5c            	incw	x
 532  00db               L02:
 533  00db 02            	rlwa	x,a
 534  00dc 89            	pushw	x
 535  00dd 7b23          	ld	a,(OFST+3,sp)
 536  00df 97            	ld	xl,a
 537  00e0 7b24          	ld	a,(OFST+4,sp)
 538  00e2 1b22          	add	a,(OFST+2,sp)
 539  00e4 2401          	jrnc	L22
 540  00e6 5c            	incw	x
 541  00e7               L22:
 542  00e7 02            	rlwa	x,a
 543  00e8 f6            	ld	a,(x)
 544  00e9 85            	popw	x
 545  00ea f7            	ld	(x),a
 546                     ; 184 for(i=0;i<len;i++)
 548  00eb 0c20          	inc	(OFST+0,sp)
 549  00ed               L302:
 552  00ed 7b20          	ld	a,(OFST+0,sp)
 553  00ef 1125          	cp	a,(OFST+5,sp)
 554  00f1 25dd          	jrult	L771
 555                     ; 192 tx_stat=tsON;
 557  00f3 35010005      	mov	_tx_stat,#1
 558                     ; 194 for (i=0;i<len;i++)
 560  00f7 0f20          	clr	(OFST+0,sp)
 562  00f9 2012          	jra	L312
 563  00fb               L702:
 564                     ; 196 	putchar1(UOB1[i]);
 566  00fb 96            	ldw	x,sp
 567  00fc 1c0002        	addw	x,#OFST-30
 568  00ff 9f            	ld	a,xl
 569  0100 5e            	swapw	x
 570  0101 1b20          	add	a,(OFST+0,sp)
 571  0103 2401          	jrnc	L42
 572  0105 5c            	incw	x
 573  0106               L42:
 574  0106 02            	rlwa	x,a
 575  0107 f6            	ld	a,(x)
 576  0108 cd0088        	call	_putchar1
 578                     ; 194 for (i=0;i<len;i++)
 580  010b 0c20          	inc	(OFST+0,sp)
 581  010d               L312:
 584  010d 7b20          	ld	a,(OFST+0,sp)
 585  010f 1125          	cp	a,(OFST+5,sp)
 586  0111 25e8          	jrult	L702
 587                     ; 199 rs485_cnt++;
 589  0113 3c0b          	inc	_rs485_cnt
 590                     ; 200 }
 593  0115 5b22          	addw	sp,#34
 594  0117 81            	ret
 597                     .const:	section	.text
 598  0000               L712_temp:
 599  0000 00            	dc.b	0
 600  0001 00            	dc.b	0
 601  0002 00            	dc.b	0
 602  0003 00            	dc.b	0
 603  0004 00            	dc.b	0
 604  0005 00            	dc.b	0
 605  0006 00            	dc.b	0
 606  0007 00            	dc.b	0
 607  0008 00            	dc.b	0
 608  0009 00            	ds.b	1
 689                     ; 203 int str2int(char *ptr, char len)
 689                     ; 204 {
 690                     	switch	.text
 691  0118               _str2int:
 693  0118 89            	pushw	x
 694  0119 5210          	subw	sp,#16
 695       00000010      OFST:	set	16
 698                     ; 208 @near char temp[10]={0,0,0,0,0,0,0,0,0};
 700  011b 96            	ldw	x,sp
 701  011c 1c0005        	addw	x,#OFST-11
 702  011f 90ae0000      	ldw	y,#L712_temp
 703  0123 a60a          	ld	a,#10
 704  0125 cd0000        	call	c_xymvx
 706                     ; 209 @near int temp_out=0;
 708  0128 5f            	clrw	x
 709  0129 1f03          	ldw	(OFST-13,sp),x
 710                     ; 213 for (i=0;i<len;i++)
 712  012b 0f10          	clr	(OFST+0,sp)
 714  012d acbe01be      	jpf	L762
 715  0131               L362:
 716                     ; 215 	tt=*(ptr+i);
 718  0131 7b11          	ld	a,(OFST+1,sp)
 719  0133 97            	ld	xl,a
 720  0134 7b12          	ld	a,(OFST+2,sp)
 721  0136 1b10          	add	a,(OFST+0,sp)
 722  0138 2401          	jrnc	L03
 723  013a 5c            	incw	x
 724  013b               L03:
 725  013b 02            	rlwa	x,a
 726  013c f6            	ld	a,(x)
 727  013d 6b0f          	ld	(OFST-1,sp),a
 728                     ; 217 	if(isalnum(tt/**(ptr+i)*/))
 730  013f 7b0f          	ld	a,(OFST-1,sp)
 731  0141 cd0000        	call	_isalnum
 733  0144 4d            	tnz	a
 734  0145 2775          	jreq	L372
 735                     ; 219 		if(isdigit(tt/**(ptr+i)*/))
 737  0147 7b0f          	ld	a,(OFST-1,sp)
 738  0149 a130          	cp	a,#48
 739  014b 2517          	jrult	L572
 741  014d 7b0f          	ld	a,(OFST-1,sp)
 742  014f a13a          	cp	a,#58
 743  0151 2411          	jruge	L572
 744                     ; 221 		temp[i]=tt/**(ptr+i)*/-'0';
 746  0153 96            	ldw	x,sp
 747  0154 1c0005        	addw	x,#OFST-11
 748  0157 9f            	ld	a,xl
 749  0158 5e            	swapw	x
 750  0159 1b10          	add	a,(OFST+0,sp)
 751  015b 2401          	jrnc	L23
 752  015d 5c            	incw	x
 753  015e               L23:
 754  015e 02            	rlwa	x,a
 755  015f 7b0f          	ld	a,(OFST-1,sp)
 756  0161 a030          	sub	a,#48
 757  0163 f7            	ld	(x),a
 758  0164               L572:
 759                     ; 223 		if(islower(tt/**(ptr+i)*/))
 761  0164 7b0f          	ld	a,(OFST-1,sp)
 762  0166 a161          	cp	a,#97
 763  0168 2517          	jrult	L772
 765  016a 7b0f          	ld	a,(OFST-1,sp)
 766  016c a17b          	cp	a,#123
 767  016e 2411          	jruge	L772
 768                     ; 225 		temp[i]=tt/**(ptr+i)*/-'a'+10;
 770  0170 96            	ldw	x,sp
 771  0171 1c0005        	addw	x,#OFST-11
 772  0174 9f            	ld	a,xl
 773  0175 5e            	swapw	x
 774  0176 1b10          	add	a,(OFST+0,sp)
 775  0178 2401          	jrnc	L43
 776  017a 5c            	incw	x
 777  017b               L43:
 778  017b 02            	rlwa	x,a
 779  017c 7b0f          	ld	a,(OFST-1,sp)
 780  017e a057          	sub	a,#87
 781  0180 f7            	ld	(x),a
 782  0181               L772:
 783                     ; 227 		if(isupper(tt/**(ptr+i)*/))
 785  0181 7b0f          	ld	a,(OFST-1,sp)
 786  0183 a141          	cp	a,#65
 787  0185 2535          	jrult	L372
 789  0187 7b0f          	ld	a,(OFST-1,sp)
 790  0189 a15b          	cp	a,#91
 791  018b 242f          	jruge	L372
 792                     ; 229 		temp[i]=tt;
 794  018d 96            	ldw	x,sp
 795  018e 1c0005        	addw	x,#OFST-11
 796  0191 9f            	ld	a,xl
 797  0192 5e            	swapw	x
 798  0193 1b10          	add	a,(OFST+0,sp)
 799  0195 2401          	jrnc	L63
 800  0197 5c            	incw	x
 801  0198               L63:
 802  0198 02            	rlwa	x,a
 803  0199 7b0f          	ld	a,(OFST-1,sp)
 804  019b f7            	ld	(x),a
 805                     ; 230 		temp[i]-=/**(ptr+i)*/'A';
 807  019c 96            	ldw	x,sp
 808  019d 1c0005        	addw	x,#OFST-11
 809  01a0 9f            	ld	a,xl
 810  01a1 5e            	swapw	x
 811  01a2 1b10          	add	a,(OFST+0,sp)
 812  01a4 2401          	jrnc	L04
 813  01a6 5c            	incw	x
 814  01a7               L04:
 815  01a7 02            	rlwa	x,a
 816  01a8 f6            	ld	a,(x)
 817  01a9 a041          	sub	a,#65
 818  01ab f7            	ld	(x),a
 819                     ; 231 		temp[i]+=10;
 821  01ac 96            	ldw	x,sp
 822  01ad 1c0005        	addw	x,#OFST-11
 823  01b0 9f            	ld	a,xl
 824  01b1 5e            	swapw	x
 825  01b2 1b10          	add	a,(OFST+0,sp)
 826  01b4 2401          	jrnc	L24
 827  01b6 5c            	incw	x
 828  01b7               L24:
 829  01b7 02            	rlwa	x,a
 830  01b8 f6            	ld	a,(x)
 831  01b9 ab0a          	add	a,#10
 832  01bb f7            	ld	(x),a
 833  01bc               L372:
 834                     ; 213 for (i=0;i<len;i++)
 836  01bc 0c10          	inc	(OFST+0,sp)
 837  01be               L762:
 840  01be 7b10          	ld	a,(OFST+0,sp)
 841  01c0 1115          	cp	a,(OFST+5,sp)
 842  01c2 2403          	jruge	L64
 843  01c4 cc0131        	jp	L362
 844  01c7               L64:
 845                     ; 237 for(i=len;i;i--)
 847  01c7 7b15          	ld	a,(OFST+5,sp)
 848  01c9 6b10          	ld	(OFST+0,sp),a
 850  01cb 2045          	jra	L703
 851  01cd               L303:
 852                     ; 239 	temp_out+= ((int)pow(16,len-i))*temp[i-1]; 
 854  01cd 7b15          	ld	a,(OFST+5,sp)
 855  01cf 5f            	clrw	x
 856  01d0 1010          	sub	a,(OFST+0,sp)
 857  01d2 2401          	jrnc	L44
 858  01d4 5a            	decw	x
 859  01d5               L44:
 860  01d5 02            	rlwa	x,a
 861  01d6 cd0000        	call	c_itof
 863  01d9 be02          	ldw	x,c_lreg+2
 864  01db 89            	pushw	x
 865  01dc be00          	ldw	x,c_lreg
 866  01de 89            	pushw	x
 867  01df ce000c        	ldw	x,L713+2
 868  01e2 89            	pushw	x
 869  01e3 ce000a        	ldw	x,L713
 870  01e6 89            	pushw	x
 871  01e7 cd0000        	call	_pow
 873  01ea 5b08          	addw	sp,#8
 874  01ec cd0000        	call	c_ftoi
 876  01ef 9096          	ldw	y,sp
 877  01f1 72a90005      	addw	y,#OFST-11
 878  01f5 1701          	ldw	(OFST-15,sp),y
 879  01f7 7b10          	ld	a,(OFST+0,sp)
 880  01f9 905f          	clrw	y
 881  01fb 9097          	ld	yl,a
 882  01fd 905a          	decw	y
 883  01ff 72f901        	addw	y,(OFST-15,sp)
 884  0202 90f6          	ld	a,(y)
 885  0204 905f          	clrw	y
 886  0206 9097          	ld	yl,a
 887  0208 cd0000        	call	c_imul
 889  020b 72fb03        	addw	x,(OFST-13,sp)
 890  020e 1f03          	ldw	(OFST-13,sp),x
 891                     ; 237 for(i=len;i;i--)
 893  0210 0a10          	dec	(OFST+0,sp)
 894  0212               L703:
 897  0212 0d10          	tnz	(OFST+0,sp)
 898  0214 26b7          	jrne	L303
 899                     ; 244 return temp_out;
 901  0216 1e03          	ldw	x,(OFST-13,sp)
 904  0218 5b12          	addw	sp,#18
 905  021a 81            	ret
 948                     ; 248 void rx485_in_an(void)
 948                     ; 249 {
 949                     	switch	.text
 950  021b               _rx485_in_an:
 954                     ; 250 	if(bRX485==1)
 956  021b b62b          	ld	a,_bRX485
 957  021d a101          	cp	a,#1
 958  021f 2703          	jreq	L25
 959  0221 cc0677        	jp	L333
 960  0224               L25:
 961                     ; 252 			GPIOD->DDR|=(1<<7);
 963  0224 721e5011      	bset	20497,#7
 964                     ; 253 	GPIOD->CR1|=(1<<7);
 966  0228 721e5012      	bset	20498,#7
 967                     ; 254 	GPIOD->CR2&=~(1<<7);	
 969  022c 721f5013      	bres	20499,#7
 970                     ; 255 	GPIOD->ODR^=(1<<7);
 972  0230 c6500f        	ld	a,20495
 973  0233 a880          	xor	a,	#128
 974  0235 c7500f        	ld	20495,a
 975                     ; 257 		max_cell_volt[0]=str2int(&rx_buffer[13],4);
 977  0238 4b04          	push	#4
 978  023a ae003f        	ldw	x,#_rx_buffer+13
 979  023d cd0118        	call	_str2int
 981  0240 84            	pop	a
 982  0241 cf008c        	ldw	_max_cell_volt,x
 983                     ; 258 		min_cell_volt[0]=str2int(&rx_buffer[17],4);
 985  0244 4b04          	push	#4
 986  0246 ae0043        	ldw	x,#_rx_buffer+17
 987  0249 cd0118        	call	_str2int
 989  024c 84            	pop	a
 990  024d cf007e        	ldw	_min_cell_volt,x
 991                     ; 259 		max_cell_temp[0]=str2int(&rx_buffer[21],2);
 993  0250 4b02          	push	#2
 994  0252 ae0047        	ldw	x,#_rx_buffer+21
 995  0255 cd0118        	call	_str2int
 997  0258 84            	pop	a
 998  0259 cf0070        	ldw	_max_cell_temp,x
 999                     ; 260 		min_cell_temp[0]=str2int(&rx_buffer[23],2);
1001  025c 4b02          	push	#2
1002  025e ae0049        	ldw	x,#_rx_buffer+23
1003  0261 cd0118        	call	_str2int
1005  0264 84            	pop	a
1006  0265 cf0062        	ldw	_min_cell_temp,x
1007                     ; 261 		tot_bat_volt[0]=str2int(&rx_buffer[25],4);
1009  0268 4b04          	push	#4
1010  026a ae004b        	ldw	x,#_rx_buffer+25
1011  026d cd0118        	call	_str2int
1013  0270 84            	pop	a
1014  0271 cf0054        	ldw	_tot_bat_volt,x
1015                     ; 262 		ch_curr[0]=str2int(&rx_buffer[29],4);
1017  0274 4b04          	push	#4
1018  0276 ae004f        	ldw	x,#_rx_buffer+29
1019  0279 cd0118        	call	_str2int
1021  027c 84            	pop	a
1022  027d cf0046        	ldw	_ch_curr,x
1023                     ; 263 		dsch_curr[0]=str2int(&rx_buffer[33],4);
1025  0280 4b04          	push	#4
1026  0282 ae0053        	ldw	x,#_rx_buffer+33
1027  0285 cd0118        	call	_str2int
1029  0288 84            	pop	a
1030  0289 cf0038        	ldw	_dsch_curr,x
1031                     ; 264 		s_o_c[0]=str2int(&rx_buffer[37],2);
1033  028c 4b02          	push	#2
1034  028e ae0057        	ldw	x,#_rx_buffer+37
1035  0291 cd0118        	call	_str2int
1037  0294 84            	pop	a
1038  0295 cf002a        	ldw	_s_o_c,x
1039                     ; 265 		rat_cap[0]=str2int(&rx_buffer[39],4);
1041  0298 4b04          	push	#4
1042  029a ae0059        	ldw	x,#_rx_buffer+39
1043  029d cd0118        	call	_str2int
1045  02a0 84            	pop	a
1046  02a1 cf001c        	ldw	_rat_cap,x
1047                     ; 266 		r_b_t[0]=str2int(&rx_buffer[43],2);
1049  02a4 4b02          	push	#2
1050  02a6 ae005d        	ldw	x,#_rx_buffer+43
1051  02a9 cd0118        	call	_str2int
1053  02ac 84            	pop	a
1054  02ad cf000e        	ldw	_r_b_t,x
1055                     ; 267 		c_c_l_v[0]=str2int(&rx_buffer[45],4);
1057  02b0 4b04          	push	#4
1058  02b2 ae005f        	ldw	x,#_rx_buffer+45
1059  02b5 cd0118        	call	_str2int
1061  02b8 84            	pop	a
1062  02b9 cf0000        	ldw	_c_c_l_v,x
1063                     ; 268 		s_o_h[0]=str2int(&rx_buffer[49],2);
1065  02bc 4b02          	push	#2
1066  02be ae0063        	ldw	x,#_rx_buffer+49
1067  02c1 cd0118        	call	_str2int
1069  02c4 84            	pop	a
1070  02c5 bf1d          	ldw	_s_o_h,x
1071                     ; 269 		b_p_ser_num[0]=str2int(&rx_buffer[51],2);
1073  02c7 4b02          	push	#2
1074  02c9 ae0065        	ldw	x,#_rx_buffer+51
1075  02cc cd0118        	call	_str2int
1077  02cf 84            	pop	a
1078  02d0 bf0f          	ldw	_b_p_ser_num,x
1079                     ; 271 		max_cell_volt[1]=str2int(&rx_buffer[13+40],4);
1081  02d2 4b04          	push	#4
1082  02d4 ae0067        	ldw	x,#_rx_buffer+53
1083  02d7 cd0118        	call	_str2int
1085  02da 84            	pop	a
1086  02db cf008e        	ldw	_max_cell_volt+2,x
1087                     ; 272 		min_cell_volt[1]=str2int(&rx_buffer[17+40],4);
1089  02de 4b04          	push	#4
1090  02e0 ae006b        	ldw	x,#_rx_buffer+57
1091  02e3 cd0118        	call	_str2int
1093  02e6 84            	pop	a
1094  02e7 cf0080        	ldw	_min_cell_volt+2,x
1095                     ; 273 		max_cell_temp[1]=str2int(&rx_buffer[21+40],2);
1097  02ea 4b02          	push	#2
1098  02ec ae006f        	ldw	x,#_rx_buffer+61
1099  02ef cd0118        	call	_str2int
1101  02f2 84            	pop	a
1102  02f3 cf0072        	ldw	_max_cell_temp+2,x
1103                     ; 274 		min_cell_temp[1]=str2int(&rx_buffer[23+40],2);
1105  02f6 4b02          	push	#2
1106  02f8 ae0071        	ldw	x,#_rx_buffer+63
1107  02fb cd0118        	call	_str2int
1109  02fe 84            	pop	a
1110  02ff cf0064        	ldw	_min_cell_temp+2,x
1111                     ; 275 		tot_bat_volt[1]=str2int(&rx_buffer[25+40],4);
1113  0302 4b04          	push	#4
1114  0304 ae0073        	ldw	x,#_rx_buffer+65
1115  0307 cd0118        	call	_str2int
1117  030a 84            	pop	a
1118  030b cf0056        	ldw	_tot_bat_volt+2,x
1119                     ; 276 		ch_curr[1]=str2int(&rx_buffer[29+40],4);
1121  030e 4b04          	push	#4
1122  0310 ae0077        	ldw	x,#_rx_buffer+69
1123  0313 cd0118        	call	_str2int
1125  0316 84            	pop	a
1126  0317 cf0048        	ldw	_ch_curr+2,x
1127                     ; 277 		dsch_curr[1]=str2int(&rx_buffer[33+40],4);
1129  031a 4b04          	push	#4
1130  031c ae007b        	ldw	x,#_rx_buffer+73
1131  031f cd0118        	call	_str2int
1133  0322 84            	pop	a
1134  0323 cf003a        	ldw	_dsch_curr+2,x
1135                     ; 278 		s_o_c[1]=str2int(&rx_buffer[37+40],2);
1137  0326 4b02          	push	#2
1138  0328 ae007f        	ldw	x,#_rx_buffer+77
1139  032b cd0118        	call	_str2int
1141  032e 84            	pop	a
1142  032f cf002c        	ldw	_s_o_c+2,x
1143                     ; 279 		rat_cap[1]=str2int(&rx_buffer[39+40],4);
1145  0332 4b04          	push	#4
1146  0334 ae0081        	ldw	x,#_rx_buffer+79
1147  0337 cd0118        	call	_str2int
1149  033a 84            	pop	a
1150  033b cf001e        	ldw	_rat_cap+2,x
1151                     ; 280 		r_b_t[1]=str2int(&rx_buffer[43+40],2);
1153  033e 4b02          	push	#2
1154  0340 ae0085        	ldw	x,#_rx_buffer+83
1155  0343 cd0118        	call	_str2int
1157  0346 84            	pop	a
1158  0347 cf0010        	ldw	_r_b_t+2,x
1159                     ; 281 		c_c_l_v[1]=str2int(&rx_buffer[45+40],4);
1161  034a 4b04          	push	#4
1162  034c ae0087        	ldw	x,#_rx_buffer+85
1163  034f cd0118        	call	_str2int
1165  0352 84            	pop	a
1166  0353 cf0002        	ldw	_c_c_l_v+2,x
1167                     ; 282 		s_o_h[1]=str2int(&rx_buffer[49+40],2);
1169  0356 4b02          	push	#2
1170  0358 ae008b        	ldw	x,#_rx_buffer+89
1171  035b cd0118        	call	_str2int
1173  035e 84            	pop	a
1174  035f bf1f          	ldw	_s_o_h+2,x
1175                     ; 283 		b_p_ser_num[1]=str2int(&rx_buffer[51+40],2);
1177  0361 4b02          	push	#2
1178  0363 ae008d        	ldw	x,#_rx_buffer+91
1179  0366 cd0118        	call	_str2int
1181  0369 84            	pop	a
1182  036a bf11          	ldw	_b_p_ser_num+2,x
1183                     ; 285 		max_cell_volt[2]=str2int(&rx_buffer[13+80],4);
1185  036c 4b04          	push	#4
1186  036e ae008f        	ldw	x,#_rx_buffer+93
1187  0371 cd0118        	call	_str2int
1189  0374 84            	pop	a
1190  0375 cf0090        	ldw	_max_cell_volt+4,x
1191                     ; 286 		min_cell_volt[2]=str2int(&rx_buffer[17+80],4);
1193  0378 4b04          	push	#4
1194  037a ae0093        	ldw	x,#_rx_buffer+97
1195  037d cd0118        	call	_str2int
1197  0380 84            	pop	a
1198  0381 cf0082        	ldw	_min_cell_volt+4,x
1199                     ; 287 		max_cell_temp[2]=str2int(&rx_buffer[21+80],2);
1201  0384 4b02          	push	#2
1202  0386 ae0097        	ldw	x,#_rx_buffer+101
1203  0389 cd0118        	call	_str2int
1205  038c 84            	pop	a
1206  038d cf0074        	ldw	_max_cell_temp+4,x
1207                     ; 288 		min_cell_temp[2]=str2int(&rx_buffer[23+80],2);
1209  0390 4b02          	push	#2
1210  0392 ae0099        	ldw	x,#_rx_buffer+103
1211  0395 cd0118        	call	_str2int
1213  0398 84            	pop	a
1214  0399 cf0066        	ldw	_min_cell_temp+4,x
1215                     ; 289 		tot_bat_volt[2]=str2int(&rx_buffer[25+80],4);
1217  039c 4b04          	push	#4
1218  039e ae009b        	ldw	x,#_rx_buffer+105
1219  03a1 cd0118        	call	_str2int
1221  03a4 84            	pop	a
1222  03a5 cf0058        	ldw	_tot_bat_volt+4,x
1223                     ; 290 		ch_curr[2]=str2int(&rx_buffer[29+80],4);
1225  03a8 4b04          	push	#4
1226  03aa ae009f        	ldw	x,#_rx_buffer+109
1227  03ad cd0118        	call	_str2int
1229  03b0 84            	pop	a
1230  03b1 cf004a        	ldw	_ch_curr+4,x
1231                     ; 291 		dsch_curr[2]=str2int(&rx_buffer[33+80],4);
1233  03b4 4b04          	push	#4
1234  03b6 ae00a3        	ldw	x,#_rx_buffer+113
1235  03b9 cd0118        	call	_str2int
1237  03bc 84            	pop	a
1238  03bd cf003c        	ldw	_dsch_curr+4,x
1239                     ; 292 		s_o_c[2]=str2int(&rx_buffer[37+80],2);
1241  03c0 4b02          	push	#2
1242  03c2 ae00a7        	ldw	x,#_rx_buffer+117
1243  03c5 cd0118        	call	_str2int
1245  03c8 84            	pop	a
1246  03c9 cf002e        	ldw	_s_o_c+4,x
1247                     ; 293 		rat_cap[2]=str2int(&rx_buffer[39+80],4);
1249  03cc 4b04          	push	#4
1250  03ce ae00a9        	ldw	x,#_rx_buffer+119
1251  03d1 cd0118        	call	_str2int
1253  03d4 84            	pop	a
1254  03d5 cf0020        	ldw	_rat_cap+4,x
1255                     ; 294 		r_b_t[2]=str2int(&rx_buffer[43+80],2);
1257  03d8 4b02          	push	#2
1258  03da ae00ad        	ldw	x,#_rx_buffer+123
1259  03dd cd0118        	call	_str2int
1261  03e0 84            	pop	a
1262  03e1 cf0012        	ldw	_r_b_t+4,x
1263                     ; 295 		c_c_l_v[2]=str2int(&rx_buffer[45+80],4);
1265  03e4 4b04          	push	#4
1266  03e6 ae00af        	ldw	x,#_rx_buffer+125
1267  03e9 cd0118        	call	_str2int
1269  03ec 84            	pop	a
1270  03ed cf0004        	ldw	_c_c_l_v+4,x
1271                     ; 296 		s_o_h[2]=str2int(&rx_buffer[49+80],2);
1273  03f0 4b02          	push	#2
1274  03f2 ae00b3        	ldw	x,#_rx_buffer+129
1275  03f5 cd0118        	call	_str2int
1277  03f8 84            	pop	a
1278  03f9 bf21          	ldw	_s_o_h+4,x
1279                     ; 297 		b_p_ser_num[2]=str2int(&rx_buffer[51+80],2);		
1281  03fb 4b02          	push	#2
1282  03fd ae00b5        	ldw	x,#_rx_buffer+131
1283  0400 cd0118        	call	_str2int
1285  0403 84            	pop	a
1286  0404 bf13          	ldw	_b_p_ser_num+4,x
1287                     ; 299 		max_cell_volt[3]=str2int(&rx_buffer[13+120],4);
1289  0406 4b04          	push	#4
1290  0408 ae00b7        	ldw	x,#_rx_buffer+133
1291  040b cd0118        	call	_str2int
1293  040e 84            	pop	a
1294  040f cf0092        	ldw	_max_cell_volt+6,x
1295                     ; 300 		min_cell_volt[3]=str2int(&rx_buffer[17+120],4);
1297  0412 4b04          	push	#4
1298  0414 ae00bb        	ldw	x,#_rx_buffer+137
1299  0417 cd0118        	call	_str2int
1301  041a 84            	pop	a
1302  041b cf0084        	ldw	_min_cell_volt+6,x
1303                     ; 301 		max_cell_temp[3]=str2int(&rx_buffer[21+120],2);
1305  041e 4b02          	push	#2
1306  0420 ae00bf        	ldw	x,#_rx_buffer+141
1307  0423 cd0118        	call	_str2int
1309  0426 84            	pop	a
1310  0427 cf0076        	ldw	_max_cell_temp+6,x
1311                     ; 302 		min_cell_temp[3]=str2int(&rx_buffer[23+120],2);
1313  042a 4b02          	push	#2
1314  042c ae00c1        	ldw	x,#_rx_buffer+143
1315  042f cd0118        	call	_str2int
1317  0432 84            	pop	a
1318  0433 cf0068        	ldw	_min_cell_temp+6,x
1319                     ; 303 		tot_bat_volt[3]=str2int(&rx_buffer[25+120],4);
1321  0436 4b04          	push	#4
1322  0438 ae00c3        	ldw	x,#_rx_buffer+145
1323  043b cd0118        	call	_str2int
1325  043e 84            	pop	a
1326  043f cf005a        	ldw	_tot_bat_volt+6,x
1327                     ; 304 		ch_curr[3]=str2int(&rx_buffer[29+120],4);
1329  0442 4b04          	push	#4
1330  0444 ae00c7        	ldw	x,#_rx_buffer+149
1331  0447 cd0118        	call	_str2int
1333  044a 84            	pop	a
1334  044b cf004c        	ldw	_ch_curr+6,x
1335                     ; 305 		dsch_curr[3]=str2int(&rx_buffer[33+120],4);
1337  044e 4b04          	push	#4
1338  0450 ae00cb        	ldw	x,#_rx_buffer+153
1339  0453 cd0118        	call	_str2int
1341  0456 84            	pop	a
1342  0457 cf003e        	ldw	_dsch_curr+6,x
1343                     ; 306 		s_o_c[3]=str2int(&rx_buffer[37+120],2);
1345  045a 4b02          	push	#2
1346  045c ae00cf        	ldw	x,#_rx_buffer+157
1347  045f cd0118        	call	_str2int
1349  0462 84            	pop	a
1350  0463 cf0030        	ldw	_s_o_c+6,x
1351                     ; 307 		rat_cap[3]=str2int(&rx_buffer[39+120],4);
1353  0466 4b04          	push	#4
1354  0468 ae00d1        	ldw	x,#_rx_buffer+159
1355  046b cd0118        	call	_str2int
1357  046e 84            	pop	a
1358  046f cf0022        	ldw	_rat_cap+6,x
1359                     ; 308 		r_b_t[3]=str2int(&rx_buffer[43+120],2);
1361  0472 4b02          	push	#2
1362  0474 ae00d5        	ldw	x,#_rx_buffer+163
1363  0477 cd0118        	call	_str2int
1365  047a 84            	pop	a
1366  047b cf0014        	ldw	_r_b_t+6,x
1367                     ; 309 		c_c_l_v[3]=str2int(&rx_buffer[45+120],4);
1369  047e 4b04          	push	#4
1370  0480 ae00d7        	ldw	x,#_rx_buffer+165
1371  0483 cd0118        	call	_str2int
1373  0486 84            	pop	a
1374  0487 cf0006        	ldw	_c_c_l_v+6,x
1375                     ; 310 		s_o_h[3]=str2int(&rx_buffer[49+120],2);
1377  048a 4b02          	push	#2
1378  048c ae00db        	ldw	x,#_rx_buffer+169
1379  048f cd0118        	call	_str2int
1381  0492 84            	pop	a
1382  0493 bf23          	ldw	_s_o_h+6,x
1383                     ; 311 		b_p_ser_num[3]=str2int(&rx_buffer[51+120],2);
1385  0495 4b02          	push	#2
1386  0497 ae00dd        	ldw	x,#_rx_buffer+171
1387  049a cd0118        	call	_str2int
1389  049d 84            	pop	a
1390  049e bf15          	ldw	_b_p_ser_num+6,x
1391                     ; 313 		max_cell_volt[4]=str2int(&rx_buffer[13+160],4);
1393  04a0 4b04          	push	#4
1394  04a2 ae00df        	ldw	x,#_rx_buffer+173
1395  04a5 cd0118        	call	_str2int
1397  04a8 84            	pop	a
1398  04a9 cf0094        	ldw	_max_cell_volt+8,x
1399                     ; 314 		min_cell_volt[4]=str2int(&rx_buffer[17+160],4);
1401  04ac 4b04          	push	#4
1402  04ae ae00e3        	ldw	x,#_rx_buffer+177
1403  04b1 cd0118        	call	_str2int
1405  04b4 84            	pop	a
1406  04b5 cf0086        	ldw	_min_cell_volt+8,x
1407                     ; 315 		max_cell_temp[4]=str2int(&rx_buffer[21+160],2);
1409  04b8 4b02          	push	#2
1410  04ba ae00e7        	ldw	x,#_rx_buffer+181
1411  04bd cd0118        	call	_str2int
1413  04c0 84            	pop	a
1414  04c1 cf0078        	ldw	_max_cell_temp+8,x
1415                     ; 316 		min_cell_temp[4]=str2int(&rx_buffer[23+160],2);
1417  04c4 4b02          	push	#2
1418  04c6 ae00e9        	ldw	x,#_rx_buffer+183
1419  04c9 cd0118        	call	_str2int
1421  04cc 84            	pop	a
1422  04cd cf006a        	ldw	_min_cell_temp+8,x
1423                     ; 317 		tot_bat_volt[4]=str2int(&rx_buffer[25+160],4);
1425  04d0 4b04          	push	#4
1426  04d2 ae00eb        	ldw	x,#_rx_buffer+185
1427  04d5 cd0118        	call	_str2int
1429  04d8 84            	pop	a
1430  04d9 cf005c        	ldw	_tot_bat_volt+8,x
1431                     ; 318 		ch_curr[4]=str2int(&rx_buffer[29+160],4);
1433  04dc 4b04          	push	#4
1434  04de ae00ef        	ldw	x,#_rx_buffer+189
1435  04e1 cd0118        	call	_str2int
1437  04e4 84            	pop	a
1438  04e5 cf004e        	ldw	_ch_curr+8,x
1439                     ; 319 		dsch_curr[4]=str2int(&rx_buffer[33+160],4);
1441  04e8 4b04          	push	#4
1442  04ea ae00f3        	ldw	x,#_rx_buffer+193
1443  04ed cd0118        	call	_str2int
1445  04f0 84            	pop	a
1446  04f1 cf0040        	ldw	_dsch_curr+8,x
1447                     ; 320 		s_o_c[4]=str2int(&rx_buffer[37+160],2);
1449  04f4 4b02          	push	#2
1450  04f6 ae00f7        	ldw	x,#_rx_buffer+197
1451  04f9 cd0118        	call	_str2int
1453  04fc 84            	pop	a
1454  04fd cf0032        	ldw	_s_o_c+8,x
1455                     ; 321 		rat_cap[4]=str2int(&rx_buffer[39+160],4);
1457  0500 4b04          	push	#4
1458  0502 ae00f9        	ldw	x,#_rx_buffer+199
1459  0505 cd0118        	call	_str2int
1461  0508 84            	pop	a
1462  0509 cf0024        	ldw	_rat_cap+8,x
1463                     ; 322 		r_b_t[4]=str2int(&rx_buffer[43+160],2);
1465  050c 4b02          	push	#2
1466  050e ae00fd        	ldw	x,#_rx_buffer+203
1467  0511 cd0118        	call	_str2int
1469  0514 84            	pop	a
1470  0515 cf0016        	ldw	_r_b_t+8,x
1471                     ; 323 		c_c_l_v[4]=str2int(&rx_buffer[45+160],4);
1473  0518 4b04          	push	#4
1474  051a ae00ff        	ldw	x,#_rx_buffer+205
1475  051d cd0118        	call	_str2int
1477  0520 84            	pop	a
1478  0521 cf0008        	ldw	_c_c_l_v+8,x
1479                     ; 324 		s_o_h[4]=str2int(&rx_buffer[49+160],2);
1481  0524 4b02          	push	#2
1482  0526 ae0103        	ldw	x,#_rx_buffer+209
1483  0529 cd0118        	call	_str2int
1485  052c 84            	pop	a
1486  052d bf25          	ldw	_s_o_h+8,x
1487                     ; 325 		b_p_ser_num[4]=str2int(&rx_buffer[51+160],2);
1489  052f 4b02          	push	#2
1490  0531 ae0105        	ldw	x,#_rx_buffer+211
1491  0534 cd0118        	call	_str2int
1493  0537 84            	pop	a
1494  0538 bf17          	ldw	_b_p_ser_num+8,x
1495                     ; 327 		max_cell_volt[5]=str2int(&rx_buffer[13+200],4);
1497  053a 4b04          	push	#4
1498  053c ae0107        	ldw	x,#_rx_buffer+213
1499  053f cd0118        	call	_str2int
1501  0542 84            	pop	a
1502  0543 cf0096        	ldw	_max_cell_volt+10,x
1503                     ; 328 		min_cell_volt[5]=str2int(&rx_buffer[17+200],4);
1505  0546 4b04          	push	#4
1506  0548 ae010b        	ldw	x,#_rx_buffer+217
1507  054b cd0118        	call	_str2int
1509  054e 84            	pop	a
1510  054f cf0088        	ldw	_min_cell_volt+10,x
1511                     ; 329 		max_cell_temp[5]=str2int(&rx_buffer[21+200],2);
1513  0552 4b02          	push	#2
1514  0554 ae010f        	ldw	x,#_rx_buffer+221
1515  0557 cd0118        	call	_str2int
1517  055a 84            	pop	a
1518  055b cf007a        	ldw	_max_cell_temp+10,x
1519                     ; 330 		min_cell_temp[5]=str2int(&rx_buffer[23+200],2);
1521  055e 4b02          	push	#2
1522  0560 ae0111        	ldw	x,#_rx_buffer+223
1523  0563 cd0118        	call	_str2int
1525  0566 84            	pop	a
1526  0567 cf006c        	ldw	_min_cell_temp+10,x
1527                     ; 331 		tot_bat_volt[5]=str2int(&rx_buffer[25+200],4);
1529  056a 4b04          	push	#4
1530  056c ae0113        	ldw	x,#_rx_buffer+225
1531  056f cd0118        	call	_str2int
1533  0572 84            	pop	a
1534  0573 cf005e        	ldw	_tot_bat_volt+10,x
1535                     ; 332 		ch_curr[5]=str2int(&rx_buffer[29+200],4);
1537  0576 4b04          	push	#4
1538  0578 ae0117        	ldw	x,#_rx_buffer+229
1539  057b cd0118        	call	_str2int
1541  057e 84            	pop	a
1542  057f cf0050        	ldw	_ch_curr+10,x
1543                     ; 333 		dsch_curr[5]=str2int(&rx_buffer[33+200],4);
1545  0582 4b04          	push	#4
1546  0584 ae011b        	ldw	x,#_rx_buffer+233
1547  0587 cd0118        	call	_str2int
1549  058a 84            	pop	a
1550  058b cf0042        	ldw	_dsch_curr+10,x
1551                     ; 334 		s_o_c[5]=str2int(&rx_buffer[37+200],2);
1553  058e 4b02          	push	#2
1554  0590 ae011f        	ldw	x,#_rx_buffer+237
1555  0593 cd0118        	call	_str2int
1557  0596 84            	pop	a
1558  0597 cf0034        	ldw	_s_o_c+10,x
1559                     ; 335 		rat_cap[5]=str2int(&rx_buffer[39+200],4);
1561  059a 4b04          	push	#4
1562  059c ae0121        	ldw	x,#_rx_buffer+239
1563  059f cd0118        	call	_str2int
1565  05a2 84            	pop	a
1566  05a3 cf0026        	ldw	_rat_cap+10,x
1567                     ; 336 		r_b_t[5]=str2int(&rx_buffer[43+200],2);
1569  05a6 4b02          	push	#2
1570  05a8 ae0125        	ldw	x,#_rx_buffer+243
1571  05ab cd0118        	call	_str2int
1573  05ae 84            	pop	a
1574  05af cf0018        	ldw	_r_b_t+10,x
1575                     ; 337 		c_c_l_v[5]=str2int(&rx_buffer[45+200],4);
1577  05b2 4b04          	push	#4
1578  05b4 ae0127        	ldw	x,#_rx_buffer+245
1579  05b7 cd0118        	call	_str2int
1581  05ba 84            	pop	a
1582  05bb cf000a        	ldw	_c_c_l_v+10,x
1583                     ; 338 		s_o_h[5]=str2int(&rx_buffer[49+200],2);
1585  05be 4b02          	push	#2
1586  05c0 ae012b        	ldw	x,#_rx_buffer+249
1587  05c3 cd0118        	call	_str2int
1589  05c6 84            	pop	a
1590  05c7 bf27          	ldw	_s_o_h+10,x
1591                     ; 339 		b_p_ser_num[5]=str2int(&rx_buffer[51+200],2);
1593  05c9 4b02          	push	#2
1594  05cb ae012d        	ldw	x,#_rx_buffer+251
1595  05ce cd0118        	call	_str2int
1597  05d1 84            	pop	a
1598  05d2 bf19          	ldw	_b_p_ser_num+10,x
1599                     ; 341 		max_cell_volt[6]=str2int(&rx_buffer[13+240],4);
1601  05d4 4b04          	push	#4
1602  05d6 ae012f        	ldw	x,#_rx_buffer+253
1603  05d9 cd0118        	call	_str2int
1605  05dc 84            	pop	a
1606  05dd cf0098        	ldw	_max_cell_volt+12,x
1607                     ; 342 		min_cell_volt[6]=str2int(&rx_buffer[17+240],4);
1609  05e0 4b04          	push	#4
1610  05e2 ae0133        	ldw	x,#_rx_buffer+257
1611  05e5 cd0118        	call	_str2int
1613  05e8 84            	pop	a
1614  05e9 cf008a        	ldw	_min_cell_volt+12,x
1615                     ; 343 		max_cell_temp[6]=str2int(&rx_buffer[21+240],2);
1617  05ec 4b02          	push	#2
1618  05ee ae0137        	ldw	x,#_rx_buffer+261
1619  05f1 cd0118        	call	_str2int
1621  05f4 84            	pop	a
1622  05f5 cf007c        	ldw	_max_cell_temp+12,x
1623                     ; 344 		min_cell_temp[6]=str2int(&rx_buffer[23+240],2);
1625  05f8 4b02          	push	#2
1626  05fa ae0139        	ldw	x,#_rx_buffer+263
1627  05fd cd0118        	call	_str2int
1629  0600 84            	pop	a
1630  0601 cf006e        	ldw	_min_cell_temp+12,x
1631                     ; 345 		tot_bat_volt[6]=str2int(&rx_buffer[25+240],4);
1633  0604 4b04          	push	#4
1634  0606 ae013b        	ldw	x,#_rx_buffer+265
1635  0609 cd0118        	call	_str2int
1637  060c 84            	pop	a
1638  060d cf0060        	ldw	_tot_bat_volt+12,x
1639                     ; 346 		ch_curr[6]=str2int(&rx_buffer[29+240],4);
1641  0610 4b04          	push	#4
1642  0612 ae013f        	ldw	x,#_rx_buffer+269
1643  0615 cd0118        	call	_str2int
1645  0618 84            	pop	a
1646  0619 cf0052        	ldw	_ch_curr+12,x
1647                     ; 347 		dsch_curr[6]=str2int(&rx_buffer[33+240],4);
1649  061c 4b04          	push	#4
1650  061e ae0143        	ldw	x,#_rx_buffer+273
1651  0621 cd0118        	call	_str2int
1653  0624 84            	pop	a
1654  0625 cf0044        	ldw	_dsch_curr+12,x
1655                     ; 348 		s_o_c[6]=str2int(&rx_buffer[37+240],2);
1657  0628 4b02          	push	#2
1658  062a ae0147        	ldw	x,#_rx_buffer+277
1659  062d cd0118        	call	_str2int
1661  0630 84            	pop	a
1662  0631 cf0036        	ldw	_s_o_c+12,x
1663                     ; 349 		rat_cap[6]=str2int(&rx_buffer[39+240],4);
1665  0634 4b04          	push	#4
1666  0636 ae0149        	ldw	x,#_rx_buffer+279
1667  0639 cd0118        	call	_str2int
1669  063c 84            	pop	a
1670  063d cf0028        	ldw	_rat_cap+12,x
1671                     ; 350 		r_b_t[6]=str2int(&rx_buffer[43+240],2);
1673  0640 4b02          	push	#2
1674  0642 ae014d        	ldw	x,#_rx_buffer+283
1675  0645 cd0118        	call	_str2int
1677  0648 84            	pop	a
1678  0649 cf001a        	ldw	_r_b_t+12,x
1679                     ; 351 		c_c_l_v[6]=str2int(&rx_buffer[45+240],4);
1681  064c 4b04          	push	#4
1682  064e ae014f        	ldw	x,#_rx_buffer+285
1683  0651 cd0118        	call	_str2int
1685  0654 84            	pop	a
1686  0655 cf000c        	ldw	_c_c_l_v+12,x
1687                     ; 352 		s_o_h[6]=str2int(&rx_buffer[49+240],2);
1689  0658 4b02          	push	#2
1690  065a ae0153        	ldw	x,#_rx_buffer+289
1691  065d cd0118        	call	_str2int
1693  0660 84            	pop	a
1694  0661 bf29          	ldw	_s_o_h+12,x
1695                     ; 353 		b_p_ser_num[6]=str2int(&rx_buffer[51+240],2);
1697  0663 4b02          	push	#2
1698  0665 ae0155        	ldw	x,#_rx_buffer+291
1699  0668 cd0118        	call	_str2int
1701  066b 84            	pop	a
1702  066c bf1b          	ldw	_b_p_ser_num+12,x
1703                     ; 355 		rs485_cnt=0;
1705  066e 3f0b          	clr	_rs485_cnt
1706                     ; 356 		bRS485ERR=0;
1708  0670 72110000      	bres	_bRS485ERR
1710  0674 cc0700        	jra	L533
1711  0677               L333:
1712                     ; 359 	else if(bRX485==2)
1714  0677 b62b          	ld	a,_bRX485
1715  0679 a102          	cp	a,#2
1716  067b 26f7          	jrne	L533
1717                     ; 361 			GPIOD->DDR|=(1<<7);
1719  067d 721e5011      	bset	20497,#7
1720                     ; 362 	GPIOD->CR1|=(1<<7);
1722  0681 721e5012      	bset	20498,#7
1723                     ; 363 	GPIOD->CR2&=~(1<<7);	
1725  0685 721f5013      	bres	20499,#7
1726                     ; 364 	GPIOD->ODR^=(1<<7);
1728  0689 c6500f        	ld	a,20495
1729  068c a880          	xor	a,	#128
1730  068e c7500f        	ld	20495,a
1731                     ; 366 		flags_byte0[0]=str2int(&rx_buffer[49],2);
1733  0691 4b02          	push	#2
1734  0693 ae0063        	ldw	x,#_rx_buffer+49
1735  0696 cd0118        	call	_str2int
1737  0699 84            	pop	a
1738  069a 01            	rrwa	x,a
1739  069b b708          	ld	_flags_byte0,a
1740  069d 02            	rlwa	x,a
1741                     ; 367 		flags_byte1[0]++;//=str2int(&rx_buffer[51],2);
1743  069e 3c01          	inc	_flags_byte1
1744                     ; 369 		flags_byte0[1]=str2int(&rx_buffer[49+34],2);
1746  06a0 4b02          	push	#2
1747  06a2 ae0085        	ldw	x,#_rx_buffer+83
1748  06a5 cd0118        	call	_str2int
1750  06a8 84            	pop	a
1751  06a9 01            	rrwa	x,a
1752  06aa b709          	ld	_flags_byte0+1,a
1753  06ac 02            	rlwa	x,a
1754                     ; 370 		flags_byte1[1]++;//=str2int(&rx_buffer[51],2);
1756  06ad 3c02          	inc	_flags_byte1+1
1757                     ; 372 		flags_byte0[2]=str2int(&rx_buffer[49+68],2);
1759  06af 4b02          	push	#2
1760  06b1 ae00a7        	ldw	x,#_rx_buffer+117
1761  06b4 cd0118        	call	_str2int
1763  06b7 84            	pop	a
1764  06b8 01            	rrwa	x,a
1765  06b9 b70a          	ld	_flags_byte0+2,a
1766  06bb 02            	rlwa	x,a
1767                     ; 373 		flags_byte1[2]++;//=str2int(&rx_buffer[51],2);
1769  06bc 3c03          	inc	_flags_byte1+2
1770                     ; 375 		flags_byte0[3]=str2int(&rx_buffer[49+102],2);
1772  06be 4b02          	push	#2
1773  06c0 ae00c9        	ldw	x,#_rx_buffer+151
1774  06c3 cd0118        	call	_str2int
1776  06c6 84            	pop	a
1777  06c7 01            	rrwa	x,a
1778  06c8 b70b          	ld	_flags_byte0+3,a
1779  06ca 02            	rlwa	x,a
1780                     ; 376 		flags_byte1[3]++;//=str2int(&rx_buffer[51],2);
1782  06cb 3c04          	inc	_flags_byte1+3
1783                     ; 378 		flags_byte0[4]=str2int(&rx_buffer[49+136],2);
1785  06cd 4b02          	push	#2
1786  06cf ae00eb        	ldw	x,#_rx_buffer+185
1787  06d2 cd0118        	call	_str2int
1789  06d5 84            	pop	a
1790  06d6 01            	rrwa	x,a
1791  06d7 b70c          	ld	_flags_byte0+4,a
1792  06d9 02            	rlwa	x,a
1793                     ; 379 		flags_byte1[4]++;//=str2int(&rx_buffer[51],2);
1795  06da 3c05          	inc	_flags_byte1+4
1796                     ; 381 		flags_byte0[5]=str2int(&rx_buffer[49+170],2);
1798  06dc 4b02          	push	#2
1799  06de ae010d        	ldw	x,#_rx_buffer+219
1800  06e1 cd0118        	call	_str2int
1802  06e4 84            	pop	a
1803  06e5 01            	rrwa	x,a
1804  06e6 b70d          	ld	_flags_byte0+5,a
1805  06e8 02            	rlwa	x,a
1806                     ; 382 		flags_byte1[5]++;//=str2int(&rx_buffer[51],2);
1808  06e9 3c06          	inc	_flags_byte1+5
1809                     ; 384 		flags_byte0[6]=str2int(&rx_buffer[49+204],2);
1811  06eb 4b02          	push	#2
1812  06ed ae012f        	ldw	x,#_rx_buffer+253
1813  06f0 cd0118        	call	_str2int
1815  06f3 84            	pop	a
1816  06f4 01            	rrwa	x,a
1817  06f5 b70e          	ld	_flags_byte0+6,a
1818  06f7 02            	rlwa	x,a
1819                     ; 385 		flags_byte1[6]++;//=str2int(&rx_buffer[51],2);		
1821  06f8 3c07          	inc	_flags_byte1+6
1822                     ; 386 		rs485_cnt=0;
1824  06fa 3f0b          	clr	_rs485_cnt
1825                     ; 387 		bRS485ERR=0;
1827  06fc 72110000      	bres	_bRS485ERR
1828  0700               L533:
1829                     ; 390 bRX485=0;	
1831  0700 3f2b          	clr	_bRX485
1832                     ; 391 }
1835  0702 81            	ret
1858                     ; 394 void init_CAN(void) {
1859                     	switch	.text
1860  0703               _init_CAN:
1864                     ; 395 	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
1866  0703 72135420      	bres	21536,#1
1867                     ; 396 	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
1869  0707 72105420      	bset	21536,#0
1871  070b               L353:
1872                     ; 397 	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
1874  070b c65421        	ld	a,21537
1875  070e a501          	bcp	a,#1
1876  0710 27f9          	jreq	L353
1877                     ; 399 	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
1879  0712 72185420      	bset	21536,#4
1880                     ; 401 	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
1882  0716 35025427      	mov	21543,#2
1883                     ; 410 	CAN->Page.Filter01.F0R1= MY_MESS_STID>>3;			// 16 bits mode
1885  071a 35135428      	mov	21544,#19
1886                     ; 411 	CAN->Page.Filter01.F0R2= MY_MESS_STID<<5;
1888  071e 35c05429      	mov	21545,#192
1889                     ; 412 	CAN->Page.Filter01.F0R5= MY_MESS_STID_MASK>>3;
1891  0722 357f542c      	mov	21548,#127
1892                     ; 413 	CAN->Page.Filter01.F0R6= MY_MESS_STID_MASK<<5;
1894  0726 35e0542d      	mov	21549,#224
1895                     ; 416 	CAN->PSR= 6;									// set page 6
1897  072a 35065427      	mov	21543,#6
1898                     ; 421 	CAN->Page.Config.FMR1&=~3;								//mask mode
1900  072e c65430        	ld	a,21552
1901  0731 a4fc          	and	a,#252
1902  0733 c75430        	ld	21552,a
1903                     ; 427 	CAN->Page.Config.FCR1= ((3<<1) & (CAN_FCR1_FSC00 | CAN_FCR1_FSC01));		//16 bit scale
1905  0736 35065432      	mov	21554,#6
1906                     ; 430 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
1908  073a 72105432      	bset	21554,#0
1909                     ; 433 	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
1911  073e 35065427      	mov	21543,#6
1912                     ; 435 	CAN->Page.Config.BTR1= 9;					// CAN_BTR1_BRP=9, 	tq= fcpu/(9+1)
1914  0742 3509542c      	mov	21548,#9
1915                     ; 436 	CAN->Page.Config.BTR2= (1<<7)|(6<<4) | 7; 		// BS2=8, BS1=7, 		
1917  0746 35e7542d      	mov	21549,#231
1918                     ; 438 	CAN->IER|=(1<<1);
1920  074a 72125425      	bset	21541,#1
1921                     ; 441 	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
1923  074e 72115420      	bres	21536,#0
1925  0752               L163:
1926                     ; 442 	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
1928  0752 c65421        	ld	a,21537
1929  0755 a501          	bcp	a,#1
1930  0757 26f9          	jrne	L163
1931                     ; 443 }
1934  0759 81            	ret
2042                     ; 446 void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
2042                     ; 447 {
2043                     	switch	.text
2044  075a               _can_transmit:
2046  075a 89            	pushw	x
2047       00000000      OFST:	set	0
2050                     ; 449 if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>4))can_buff_wr_ptr=0;
2052  075b b651          	ld	a,_can_buff_wr_ptr
2053  075d a105          	cp	a,#5
2054  075f 2502          	jrult	L344
2057  0761 3f51          	clr	_can_buff_wr_ptr
2058  0763               L344:
2059                     ; 451 can_out_buff[can_buff_wr_ptr][0]=(char)(id_st>>6);
2061  0763 b651          	ld	a,_can_buff_wr_ptr
2062  0765 97            	ld	xl,a
2063  0766 a610          	ld	a,#16
2064  0768 42            	mul	x,a
2065  0769 1601          	ldw	y,(OFST+1,sp)
2066  076b a606          	ld	a,#6
2067  076d               L06:
2068  076d 9054          	srlw	y
2069  076f 4a            	dec	a
2070  0770 26fb          	jrne	L06
2071  0772 909f          	ld	a,yl
2072  0774 e752          	ld	(_can_out_buff,x),a
2073                     ; 452 can_out_buff[can_buff_wr_ptr][1]=(char)(id_st<<2);
2075  0776 b651          	ld	a,_can_buff_wr_ptr
2076  0778 97            	ld	xl,a
2077  0779 a610          	ld	a,#16
2078  077b 42            	mul	x,a
2079  077c 7b02          	ld	a,(OFST+2,sp)
2080  077e 48            	sll	a
2081  077f 48            	sll	a
2082  0780 e753          	ld	(_can_out_buff+1,x),a
2083                     ; 454 can_out_buff[can_buff_wr_ptr][2]=data0;
2085  0782 b651          	ld	a,_can_buff_wr_ptr
2086  0784 97            	ld	xl,a
2087  0785 a610          	ld	a,#16
2088  0787 42            	mul	x,a
2089  0788 7b05          	ld	a,(OFST+5,sp)
2090  078a e754          	ld	(_can_out_buff+2,x),a
2091                     ; 455 can_out_buff[can_buff_wr_ptr][3]=data1;
2093  078c b651          	ld	a,_can_buff_wr_ptr
2094  078e 97            	ld	xl,a
2095  078f a610          	ld	a,#16
2096  0791 42            	mul	x,a
2097  0792 7b06          	ld	a,(OFST+6,sp)
2098  0794 e755          	ld	(_can_out_buff+3,x),a
2099                     ; 456 can_out_buff[can_buff_wr_ptr][4]=data2;
2101  0796 b651          	ld	a,_can_buff_wr_ptr
2102  0798 97            	ld	xl,a
2103  0799 a610          	ld	a,#16
2104  079b 42            	mul	x,a
2105  079c 7b07          	ld	a,(OFST+7,sp)
2106  079e e756          	ld	(_can_out_buff+4,x),a
2107                     ; 457 can_out_buff[can_buff_wr_ptr][5]=data3;
2109  07a0 b651          	ld	a,_can_buff_wr_ptr
2110  07a2 97            	ld	xl,a
2111  07a3 a610          	ld	a,#16
2112  07a5 42            	mul	x,a
2113  07a6 7b08          	ld	a,(OFST+8,sp)
2114  07a8 e757          	ld	(_can_out_buff+5,x),a
2115                     ; 458 can_out_buff[can_buff_wr_ptr][6]=data4;
2117  07aa b651          	ld	a,_can_buff_wr_ptr
2118  07ac 97            	ld	xl,a
2119  07ad a610          	ld	a,#16
2120  07af 42            	mul	x,a
2121  07b0 7b09          	ld	a,(OFST+9,sp)
2122  07b2 e758          	ld	(_can_out_buff+6,x),a
2123                     ; 459 can_out_buff[can_buff_wr_ptr][7]=data5;
2125  07b4 b651          	ld	a,_can_buff_wr_ptr
2126  07b6 97            	ld	xl,a
2127  07b7 a610          	ld	a,#16
2128  07b9 42            	mul	x,a
2129  07ba 7b0a          	ld	a,(OFST+10,sp)
2130  07bc e759          	ld	(_can_out_buff+7,x),a
2131                     ; 460 can_out_buff[can_buff_wr_ptr][8]=data6;
2133  07be b651          	ld	a,_can_buff_wr_ptr
2134  07c0 97            	ld	xl,a
2135  07c1 a610          	ld	a,#16
2136  07c3 42            	mul	x,a
2137  07c4 7b0b          	ld	a,(OFST+11,sp)
2138  07c6 e75a          	ld	(_can_out_buff+8,x),a
2139                     ; 461 can_out_buff[can_buff_wr_ptr][9]=data7;
2141  07c8 b651          	ld	a,_can_buff_wr_ptr
2142  07ca 97            	ld	xl,a
2143  07cb a610          	ld	a,#16
2144  07cd 42            	mul	x,a
2145  07ce 7b0c          	ld	a,(OFST+12,sp)
2146  07d0 e75b          	ld	(_can_out_buff+9,x),a
2147                     ; 463 can_buff_wr_ptr++;
2149  07d2 3c51          	inc	_can_buff_wr_ptr
2150                     ; 464 if(can_buff_wr_ptr>4)can_buff_wr_ptr=0;
2152  07d4 b651          	ld	a,_can_buff_wr_ptr
2153  07d6 a105          	cp	a,#5
2154  07d8 2502          	jrult	L544
2157  07da 3f51          	clr	_can_buff_wr_ptr
2158  07dc               L544:
2159                     ; 465 } 
2162  07dc 85            	popw	x
2163  07dd 81            	ret
2192                     ; 468 void can_tx_hndl(void)
2192                     ; 469 {
2193                     	switch	.text
2194  07de               _can_tx_hndl:
2198                     ; 470 if(bTX_FREE)
2200  07de 3d07          	tnz	_bTX_FREE
2201  07e0 2757          	jreq	L754
2202                     ; 472 	if(can_buff_rd_ptr!=can_buff_wr_ptr)
2204  07e2 b650          	ld	a,_can_buff_rd_ptr
2205  07e4 b151          	cp	a,_can_buff_wr_ptr
2206  07e6 275f          	jreq	L564
2207                     ; 474 		bTX_FREE=0;
2209  07e8 3f07          	clr	_bTX_FREE
2210                     ; 476 		CAN->PSR= 0;
2212  07ea 725f5427      	clr	21543
2213                     ; 477 		CAN->Page.TxMailbox.MDLCR=8;
2215  07ee 35085429      	mov	21545,#8
2216                     ; 478 		CAN->Page.TxMailbox.MIDR1=can_out_buff[can_buff_rd_ptr][0];
2218  07f2 b650          	ld	a,_can_buff_rd_ptr
2219  07f4 97            	ld	xl,a
2220  07f5 a610          	ld	a,#16
2221  07f7 42            	mul	x,a
2222  07f8 e652          	ld	a,(_can_out_buff,x)
2223  07fa c7542a        	ld	21546,a
2224                     ; 479 		CAN->Page.TxMailbox.MIDR2=can_out_buff[can_buff_rd_ptr][1];
2226  07fd b650          	ld	a,_can_buff_rd_ptr
2227  07ff 97            	ld	xl,a
2228  0800 a610          	ld	a,#16
2229  0802 42            	mul	x,a
2230  0803 e653          	ld	a,(_can_out_buff+1,x)
2231  0805 c7542b        	ld	21547,a
2232                     ; 481 		memcpy(&CAN->Page.TxMailbox.MDAR1, &can_out_buff[can_buff_rd_ptr][2],8);
2234  0808 b650          	ld	a,_can_buff_rd_ptr
2235  080a 97            	ld	xl,a
2236  080b a610          	ld	a,#16
2237  080d 42            	mul	x,a
2238  080e 01            	rrwa	x,a
2239  080f ab54          	add	a,#_can_out_buff+2
2240  0811 2401          	jrnc	L46
2241  0813 5c            	incw	x
2242  0814               L46:
2243  0814 5f            	clrw	x
2244  0815 97            	ld	xl,a
2245  0816 bf00          	ldw	c_x,x
2246  0818 ae0008        	ldw	x,#8
2247  081b               L66:
2248  081b 5a            	decw	x
2249  081c 92d600        	ld	a,([c_x],x)
2250  081f d7542e        	ld	(21550,x),a
2251  0822 5d            	tnzw	x
2252  0823 26f6          	jrne	L66
2253                     ; 483 		can_buff_rd_ptr++;
2255  0825 3c50          	inc	_can_buff_rd_ptr
2256                     ; 484 		if(can_buff_rd_ptr>3)can_buff_rd_ptr=0;
2258  0827 b650          	ld	a,_can_buff_rd_ptr
2259  0829 a104          	cp	a,#4
2260  082b 2502          	jrult	L364
2263  082d 3f50          	clr	_can_buff_rd_ptr
2264  082f               L364:
2265                     ; 486 		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;
2267  082f 72105428      	bset	21544,#0
2268                     ; 487 		CAN->IER|=(1<<0);
2270  0833 72105425      	bset	21541,#0
2271  0837 200e          	jra	L564
2272  0839               L754:
2273                     ; 492 	tx_busy_cnt++;
2275  0839 3c4f          	inc	_tx_busy_cnt
2276                     ; 493 	if(tx_busy_cnt>=100)
2278  083b b64f          	ld	a,_tx_busy_cnt
2279  083d a164          	cp	a,#100
2280  083f 2506          	jrult	L564
2281                     ; 495 		tx_busy_cnt=0;
2283  0841 3f4f          	clr	_tx_busy_cnt
2284                     ; 496 		bTX_FREE=1;
2286  0843 35010007      	mov	_bTX_FREE,#1
2287  0847               L564:
2288                     ; 499 }
2291  0847 81            	ret
2339                     ; 503 void can_in_an(void)
2339                     ; 504 {
2340                     	switch	.text
2341  0848               _can_in_an:
2345                     ; 515 if((mess[6]==19)&&(mess[7]==19)&&(mess[8]==GETTM))	
2347  0848 b6d6          	ld	a,_mess+6
2348  084a a113          	cp	a,#19
2349  084c 2703          	jreq	L27
2350  084e cc0978        	jp	L174
2351  0851               L27:
2353  0851 b6d7          	ld	a,_mess+7
2354  0853 a113          	cp	a,#19
2355  0855 2703          	jreq	L47
2356  0857 cc0978        	jp	L174
2357  085a               L47:
2359  085a b6d8          	ld	a,_mess+8
2360  085c a1ed          	cp	a,#237
2361  085e 2703          	jreq	L67
2362  0860 cc0978        	jp	L174
2363  0863               L67:
2364                     ; 517 	GPIOD->DDR|=(1<<7);
2366  0863 721e5011      	bset	20497,#7
2367                     ; 518 	GPIOD->CR1|=(1<<7);
2369  0867 721e5012      	bset	20498,#7
2370                     ; 519 	GPIOD->CR2&=~(1<<7);	
2372  086b 721f5013      	bres	20499,#7
2373                     ; 520 	GPIOD->ODR^=(1<<7);
2375  086f c6500f        	ld	a,20495
2376  0872 a880          	xor	a,	#128
2377  0874 c7500f        	ld	20495,a
2378                     ; 521 	can_error_cnt=0;
2380  0877 3f4e          	clr	_can_error_cnt
2381                     ; 529 	can_transmit(0x18e,PUT_LB_TM1,transmit_cnt_number,*(((char*)&max_cell_volt[transmit_cnt_number])+1),*((char*)&max_cell_volt[transmit_cnt_number]),*(((char*)&min_cell_volt[transmit_cnt_number])+1),*((char*)&min_cell_volt[transmit_cnt_number]),*(((char*)&tot_bat_volt[transmit_cnt_number])+1),*((char*)&tot_bat_volt[transmit_cnt_number]));
2383  0879 b600          	ld	a,_transmit_cnt_number
2384  087b 5f            	clrw	x
2385  087c 97            	ld	xl,a
2386  087d 58            	sllw	x
2387  087e d60054        	ld	a,(_tot_bat_volt,x)
2388  0881 88            	push	a
2389  0882 b600          	ld	a,_transmit_cnt_number
2390  0884 5f            	clrw	x
2391  0885 97            	ld	xl,a
2392  0886 58            	sllw	x
2393  0887 d60055        	ld	a,(_tot_bat_volt+1,x)
2394  088a 88            	push	a
2395  088b b600          	ld	a,_transmit_cnt_number
2396  088d 5f            	clrw	x
2397  088e 97            	ld	xl,a
2398  088f 58            	sllw	x
2399  0890 d6007e        	ld	a,(_min_cell_volt,x)
2400  0893 88            	push	a
2401  0894 b600          	ld	a,_transmit_cnt_number
2402  0896 5f            	clrw	x
2403  0897 97            	ld	xl,a
2404  0898 58            	sllw	x
2405  0899 d6007f        	ld	a,(_min_cell_volt+1,x)
2406  089c 88            	push	a
2407  089d b600          	ld	a,_transmit_cnt_number
2408  089f 5f            	clrw	x
2409  08a0 97            	ld	xl,a
2410  08a1 58            	sllw	x
2411  08a2 d6008c        	ld	a,(_max_cell_volt,x)
2412  08a5 88            	push	a
2413  08a6 b600          	ld	a,_transmit_cnt_number
2414  08a8 5f            	clrw	x
2415  08a9 97            	ld	xl,a
2416  08aa 58            	sllw	x
2417  08ab d6008d        	ld	a,(_max_cell_volt+1,x)
2418  08ae 88            	push	a
2419  08af 3b0000        	push	_transmit_cnt_number
2420  08b2 4bd1          	push	#209
2421  08b4 ae018e        	ldw	x,#398
2422  08b7 cd075a        	call	_can_transmit
2424  08ba 5b08          	addw	sp,#8
2425                     ; 530 	can_transmit(0x18e,PUT_LB_TM2,transmit_cnt_number,*(((char*)&ch_curr[transmit_cnt_number])+1),*((char*)&ch_curr[transmit_cnt_number]),*(((char*)&dsch_curr[transmit_cnt_number])+1),*((char*)&dsch_curr[transmit_cnt_number]),*(((char*)&rat_cap[transmit_cnt_number])+1),*((char*)&rat_cap[transmit_cnt_number]));
2427  08bc b600          	ld	a,_transmit_cnt_number
2428  08be 5f            	clrw	x
2429  08bf 97            	ld	xl,a
2430  08c0 58            	sllw	x
2431  08c1 d6001c        	ld	a,(_rat_cap,x)
2432  08c4 88            	push	a
2433  08c5 b600          	ld	a,_transmit_cnt_number
2434  08c7 5f            	clrw	x
2435  08c8 97            	ld	xl,a
2436  08c9 58            	sllw	x
2437  08ca d6001d        	ld	a,(_rat_cap+1,x)
2438  08cd 88            	push	a
2439  08ce b600          	ld	a,_transmit_cnt_number
2440  08d0 5f            	clrw	x
2441  08d1 97            	ld	xl,a
2442  08d2 58            	sllw	x
2443  08d3 d60038        	ld	a,(_dsch_curr,x)
2444  08d6 88            	push	a
2445  08d7 b600          	ld	a,_transmit_cnt_number
2446  08d9 5f            	clrw	x
2447  08da 97            	ld	xl,a
2448  08db 58            	sllw	x
2449  08dc d60039        	ld	a,(_dsch_curr+1,x)
2450  08df 88            	push	a
2451  08e0 b600          	ld	a,_transmit_cnt_number
2452  08e2 5f            	clrw	x
2453  08e3 97            	ld	xl,a
2454  08e4 58            	sllw	x
2455  08e5 d60046        	ld	a,(_ch_curr,x)
2456  08e8 88            	push	a
2457  08e9 b600          	ld	a,_transmit_cnt_number
2458  08eb 5f            	clrw	x
2459  08ec 97            	ld	xl,a
2460  08ed 58            	sllw	x
2461  08ee d60047        	ld	a,(_ch_curr+1,x)
2462  08f1 88            	push	a
2463  08f2 3b0000        	push	_transmit_cnt_number
2464  08f5 4bd2          	push	#210
2465  08f7 ae018e        	ldw	x,#398
2466  08fa cd075a        	call	_can_transmit
2468  08fd 5b08          	addw	sp,#8
2469                     ; 531 	can_transmit(0x18e,PUT_LB_TM3,transmit_cnt_number,(unsigned char)s_o_h[transmit_cnt_number],(unsigned char)s_o_c[transmit_cnt_number],*(((char*)&c_c_l_v[transmit_cnt_number])+1),*((char*)&c_c_l_v[transmit_cnt_number]),(unsigned char)r_b_t[transmit_cnt_number],(unsigned char)flags_byte0[transmit_cnt_number]);
2471  08ff b600          	ld	a,_transmit_cnt_number
2472  0901 5f            	clrw	x
2473  0902 97            	ld	xl,a
2474  0903 e608          	ld	a,(_flags_byte0,x)
2475  0905 88            	push	a
2476  0906 b600          	ld	a,_transmit_cnt_number
2477  0908 5f            	clrw	x
2478  0909 97            	ld	xl,a
2479  090a 58            	sllw	x
2480  090b d6000f        	ld	a,(_r_b_t+1,x)
2481  090e 88            	push	a
2482  090f b600          	ld	a,_transmit_cnt_number
2483  0911 5f            	clrw	x
2484  0912 97            	ld	xl,a
2485  0913 58            	sllw	x
2486  0914 d60000        	ld	a,(_c_c_l_v,x)
2487  0917 88            	push	a
2488  0918 b600          	ld	a,_transmit_cnt_number
2489  091a 5f            	clrw	x
2490  091b 97            	ld	xl,a
2491  091c 58            	sllw	x
2492  091d d60001        	ld	a,(_c_c_l_v+1,x)
2493  0920 88            	push	a
2494  0921 b600          	ld	a,_transmit_cnt_number
2495  0923 5f            	clrw	x
2496  0924 97            	ld	xl,a
2497  0925 58            	sllw	x
2498  0926 d6002b        	ld	a,(_s_o_c+1,x)
2499  0929 88            	push	a
2500  092a b600          	ld	a,_transmit_cnt_number
2501  092c 5f            	clrw	x
2502  092d 97            	ld	xl,a
2503  092e 58            	sllw	x
2504  092f e61e          	ld	a,(_s_o_h+1,x)
2505  0931 88            	push	a
2506  0932 3b0000        	push	_transmit_cnt_number
2507  0935 4bd3          	push	#211
2508  0937 ae018e        	ldw	x,#398
2509  093a cd075a        	call	_can_transmit
2511  093d 5b08          	addw	sp,#8
2512                     ; 532 	can_transmit(0x18e,PUT_LB_TM4,transmit_cnt_number,(unsigned char)bRS485ERR,(unsigned char)rs485_cnt,(unsigned char)max_cell_temp[transmit_cnt_number],(unsigned char)min_cell_temp[transmit_cnt_number],(unsigned char)flags_byte1[transmit_cnt_number],0);
2514  093f 4b00          	push	#0
2515  0941 b600          	ld	a,_transmit_cnt_number
2516  0943 5f            	clrw	x
2517  0944 97            	ld	xl,a
2518  0945 e601          	ld	a,(_flags_byte1,x)
2519  0947 88            	push	a
2520  0948 b600          	ld	a,_transmit_cnt_number
2521  094a 5f            	clrw	x
2522  094b 97            	ld	xl,a
2523  094c 58            	sllw	x
2524  094d d60063        	ld	a,(_min_cell_temp+1,x)
2525  0950 88            	push	a
2526  0951 b600          	ld	a,_transmit_cnt_number
2527  0953 5f            	clrw	x
2528  0954 97            	ld	xl,a
2529  0955 58            	sllw	x
2530  0956 d60071        	ld	a,(_max_cell_temp+1,x)
2531  0959 88            	push	a
2532  095a 3b000b        	push	_rs485_cnt
2533  095d 4f            	clr	a
2534                     	btst	_bRS485ERR
2535  0963 49            	rlc	a
2536  0964 88            	push	a
2537  0965 3b0000        	push	_transmit_cnt_number
2538  0968 4bd4          	push	#212
2539  096a ae018e        	ldw	x,#398
2540  096d cd075a        	call	_can_transmit
2542  0970 5b08          	addw	sp,#8
2543                     ; 533      link_cnt=0;
2545  0972 3f34          	clr	_link_cnt
2546                     ; 534      link=ON;
2548  0974 35550035      	mov	_link,#85
2549  0978               L174:
2550                     ; 544 can_in_an_end:
2550                     ; 545 bCAN_RX=0;
2552  0978 3f08          	clr	_bCAN_RX
2553                     ; 546 }   
2556  097a 81            	ret
2579                     ; 550 void t4_init(void){
2580                     	switch	.text
2581  097b               _t4_init:
2585                     ; 551 	TIM4->PSCR = 7;
2587  097b 35075345      	mov	21317,#7
2588                     ; 552 	TIM4->ARR= 77;
2590  097f 354d5346      	mov	21318,#77
2591                     ; 553 	TIM4->IER|= TIM4_IER_UIE;					// enable break interrupt
2593  0983 72105341      	bset	21313,#0
2594                     ; 555 	TIM4->CR1=(TIM4_CR1_URS | TIM4_CR1_CEN | TIM4_CR1_ARPE);	
2596  0987 35855340      	mov	21312,#133
2597                     ; 557 }
2600  098b 81            	ret
2635                     ; 563 @far @interrupt void TIM4_UPD_Interrupt (void) 
2635                     ; 564 {
2637                     	switch	.text
2638  098c               f_TIM4_UPD_Interrupt:
2642                     ; 565 TIM4->SR1&=~TIM4_SR1_UIF;
2644  098c 72115342      	bres	21314,#0
2645                     ; 568 if(++t0_cnt0>=10)
2647  0990 3c00          	inc	_t0_cnt0
2648  0992 b600          	ld	a,_t0_cnt0
2649  0994 a10a          	cp	a,#10
2650  0996 253e          	jrult	L725
2651                     ; 570 	t0_cnt0=0;
2653  0998 3f00          	clr	_t0_cnt0
2654                     ; 571 	b100Hz=1;
2656  099a 72100006      	bset	_b100Hz
2657                     ; 573 	if(++t0_cnt1>=10)
2659  099e 3c01          	inc	_t0_cnt1
2660  09a0 b601          	ld	a,_t0_cnt1
2661  09a2 a10a          	cp	a,#10
2662  09a4 2506          	jrult	L135
2663                     ; 575 		t0_cnt1=0;
2665  09a6 3f01          	clr	_t0_cnt1
2666                     ; 576 		b10Hz=1;
2668  09a8 72100005      	bset	_b10Hz
2669  09ac               L135:
2670                     ; 579 	if(++t0_cnt2>=20)
2672  09ac 3c02          	inc	_t0_cnt2
2673  09ae b602          	ld	a,_t0_cnt2
2674  09b0 a114          	cp	a,#20
2675  09b2 2506          	jrult	L335
2676                     ; 581 		t0_cnt2=0;
2678  09b4 3f02          	clr	_t0_cnt2
2679                     ; 582 		b5Hz=1;
2681  09b6 72100004      	bset	_b5Hz
2682  09ba               L335:
2683                     ; 586 	if(++t0_cnt4>=50)
2685  09ba 3c04          	inc	_t0_cnt4
2686  09bc b604          	ld	a,_t0_cnt4
2687  09be a132          	cp	a,#50
2688  09c0 2506          	jrult	L535
2689                     ; 588 		t0_cnt4=0;
2691  09c2 3f04          	clr	_t0_cnt4
2692                     ; 589 		b2Hz=1;
2694  09c4 72100003      	bset	_b2Hz
2695  09c8               L535:
2696                     ; 592 	if(++t0_cnt3>=100)
2698  09c8 3c03          	inc	_t0_cnt3
2699  09ca b603          	ld	a,_t0_cnt3
2700  09cc a164          	cp	a,#100
2701  09ce 2506          	jrult	L725
2702                     ; 594 		t0_cnt3=0;
2704  09d0 3f03          	clr	_t0_cnt3
2705                     ; 595 		b1Hz=1;
2707  09d2 72100002      	bset	_b1Hz
2708  09d6               L725:
2709                     ; 602 if(tx_stat_cnt)
2711  09d6 725d01f3      	tnz	_tx_stat_cnt
2712  09da 270c          	jreq	L145
2713                     ; 604 	tx_stat_cnt--;
2715  09dc 725a01f3      	dec	_tx_stat_cnt
2716                     ; 605 	if(tx_stat_cnt==0)tx_stat=tsOFF;
2718  09e0 725d01f3      	tnz	_tx_stat_cnt
2719  09e4 2602          	jrne	L145
2722  09e6 3f05          	clr	_tx_stat
2723  09e8               L145:
2724                     ; 620 }
2727  09e8 80            	iret
2752                     ; 623 @far @interrupt void CAN_RX_Interrupt (void) 
2752                     ; 624 {
2753                     	switch	.text
2754  09e9               f_CAN_RX_Interrupt:
2758                     ; 634 CAN->PSR= 7;									// page 7 - read messsage
2760  09e9 35075427      	mov	21543,#7
2761                     ; 636 memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
2763  09ed ae000e        	ldw	x,#14
2764  09f0               L601:
2765  09f0 d65427        	ld	a,(21543,x)
2766  09f3 e7cf          	ld	(_mess-1,x),a
2767  09f5 5a            	decw	x
2768  09f6 26f8          	jrne	L601
2769                     ; 647 bCAN_RX=1;
2771  09f8 35010008      	mov	_bCAN_RX,#1
2772                     ; 648 CAN->RFR|=(1<<5);
2774  09fc 721a5424      	bset	21540,#5
2775                     ; 650 }
2778  0a00 80            	iret
2801                     ; 653 @far @interrupt void CAN_TX_Interrupt (void) 
2801                     ; 654 {
2802                     	switch	.text
2803  0a01               f_CAN_TX_Interrupt:
2807                     ; 655 	if((CAN->TSR)&(1<<0))
2809  0a01 c65422        	ld	a,21538
2810  0a04 a501          	bcp	a,#1
2811  0a06 2708          	jreq	L565
2812                     ; 657 	bTX_FREE=1;	
2814  0a08 35010007      	mov	_bTX_FREE,#1
2815                     ; 659 	CAN->TSR|=(1<<0);
2817  0a0c 72105422      	bset	21538,#0
2818  0a10               L565:
2819                     ; 661 }
2822  0a10 80            	iret
2860                     ; 665 @far @interrupt void UART1TxInterrupt (void) 
2860                     ; 666 {
2861                     	switch	.text
2862  0a11               f_UART1TxInterrupt:
2864       00000001      OFST:	set	1
2865  0a11 88            	push	a
2868                     ; 669 tx_status=UART1->SR;
2870  0a12 c65230        	ld	a,21040
2871  0a15 6b01          	ld	(OFST+0,sp),a
2872                     ; 671 if (tx_status & (UART1_SR_TXE))
2874  0a17 7b01          	ld	a,(OFST+0,sp)
2875  0a19 a580          	bcp	a,#128
2876  0a1b 272b          	jreq	L506
2877                     ; 673 	if (tx_counter1)
2879  0a1d 3dbb          	tnz	_tx_counter1
2880  0a1f 271b          	jreq	L706
2881                     ; 675 		--tx_counter1;
2883  0a21 3abb          	dec	_tx_counter1
2884                     ; 676 		UART1->DR=tx_buffer1[tx_rd_index1];
2886  0a23 5f            	clrw	x
2887  0a24 b6b9          	ld	a,_tx_rd_index1
2888  0a26 2a01          	jrpl	L411
2889  0a28 53            	cplw	x
2890  0a29               L411:
2891  0a29 97            	ld	xl,a
2892  0a2a d60000        	ld	a,(_tx_buffer1,x)
2893  0a2d c75231        	ld	21041,a
2894                     ; 677 		if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
2896  0a30 3cb9          	inc	_tx_rd_index1
2897  0a32 b6b9          	ld	a,_tx_rd_index1
2898  0a34 a132          	cp	a,#50
2899  0a36 2610          	jrne	L506
2902  0a38 3fb9          	clr	_tx_rd_index1
2903  0a3a 200c          	jra	L506
2904  0a3c               L706:
2905                     ; 681 		tx_stat_cnt=3;
2907  0a3c 350301f3      	mov	_tx_stat_cnt,#3
2908                     ; 682 			bOUT_FREE=1;
2910  0a40 350100b2      	mov	_bOUT_FREE,#1
2911                     ; 683 			UART1->CR2&= ~UART1_CR2_TIEN;
2913  0a44 721f5235      	bres	21045,#7
2914  0a48               L506:
2915                     ; 687 if (tx_status & (UART1_SR_TC))
2917  0a48 7b01          	ld	a,(OFST+0,sp)
2918  0a4a a540          	bcp	a,#64
2919  0a4c 2708          	jreq	L516
2920                     ; 689 	GPIOB->ODR&=~(1<<7);
2922  0a4e 721f5005      	bres	20485,#7
2923                     ; 690 	UART1->SR&=~UART1_SR_TC;
2925  0a52 721d5230      	bres	21040,#6
2926  0a56               L516:
2927                     ; 692 }
2930  0a56 84            	pop	a
2931  0a57 80            	iret
2986                     ; 695 @far @interrupt void UART1RxInterrupt (void) 
2986                     ; 696 {
2987                     	switch	.text
2988  0a58               f_UART1RxInterrupt:
2990       00000003      OFST:	set	3
2991  0a58 5203          	subw	sp,#3
2994                     ; 699 rx_status=UART1->SR;
2996  0a5a c65230        	ld	a,21040
2997  0a5d 6b02          	ld	(OFST-1,sp),a
2998                     ; 700 rx_data=UART1->DR;
3000  0a5f c65231        	ld	a,21041
3001  0a62 6b03          	ld	(OFST+0,sp),a
3002                     ; 702 if (rx_status & (UART1_SR_RXNE))
3004  0a64 7b02          	ld	a,(OFST-1,sp)
3005  0a66 a520          	bcp	a,#32
3006  0a68 2738          	jreq	L546
3007                     ; 705 temp=rx_data;
3009                     ; 706 rx_buffer[rs485_rx_cnt]=rx_data;
3011  0a6a 7b03          	ld	a,(OFST+0,sp)
3012  0a6c be2c          	ldw	x,_rs485_rx_cnt
3013  0a6e d70032        	ld	(_rx_buffer,x),a
3014                     ; 707 rs485_rx_cnt++;
3016  0a71 be2c          	ldw	x,_rs485_rx_cnt
3017  0a73 1c0001        	addw	x,#1
3018  0a76 bf2c          	ldw	_rs485_rx_cnt,x
3019                     ; 723 	if((rx_data==0x0d)&&(rs485_rx_cnt==20))
3021  0a78 7b03          	ld	a,(OFST+0,sp)
3022  0a7a a10d          	cp	a,#13
3023  0a7c 261b          	jrne	L746
3025  0a7e be2c          	ldw	x,_rs485_rx_cnt
3026  0a80 a30014        	cpw	x,#20
3027  0a83 2614          	jrne	L746
3028                     ; 725 		if(rs485_out_buff[8]==0x32)bRX485=1;
3030  0a85 b6c4          	ld	a,_rs485_out_buff+8
3031  0a87 a132          	cp	a,#50
3032  0a89 2604          	jrne	L156
3035  0a8b 3501002b      	mov	_bRX485,#1
3036  0a8f               L156:
3037                     ; 726 		if(rs485_out_buff[8]==0x33)bRX485=2;
3039  0a8f b6c4          	ld	a,_rs485_out_buff+8
3040  0a91 a133          	cp	a,#51
3041  0a93 2604          	jrne	L746
3044  0a95 3502002b      	mov	_bRX485,#2
3045  0a99               L746:
3046                     ; 729 	if(rx_data==0x0d)rs485_rx_cnt=0;	
3048  0a99 7b03          	ld	a,(OFST+0,sp)
3049  0a9b a10d          	cp	a,#13
3050  0a9d 2603          	jrne	L546
3053  0a9f 5f            	clrw	x
3054  0aa0 bf2c          	ldw	_rs485_rx_cnt,x
3055  0aa2               L546:
3056                     ; 734 }
3059  0aa2 5b03          	addw	sp,#3
3060  0aa4 80            	iret
3101                     ; 743 main()
3101                     ; 744 {
3103                     	switch	.text
3104  0aa5               _main:
3108                     ; 745 CLK->ECKR|=1;
3110  0aa5 721050c1      	bset	20673,#0
3112  0aa9               L176:
3113                     ; 746 while((CLK->ECKR & 2) == 0);
3115  0aa9 c650c1        	ld	a,20673
3116  0aac a502          	bcp	a,#2
3117  0aae 27f9          	jreq	L176
3118                     ; 747 CLK->SWCR|=2;
3120  0ab0 721250c5      	bset	20677,#1
3121                     ; 748 CLK->SWR=0xB4;
3123  0ab4 35b450c4      	mov	20676,#180
3124                     ; 751 t4_init();
3126  0ab8 cd097b        	call	_t4_init
3128                     ; 753 		GPIOG->DDR|=(1<<0);
3130  0abb 72105020      	bset	20512,#0
3131                     ; 754 		GPIOG->CR1|=(1<<0);
3133  0abf 72105021      	bset	20513,#0
3134                     ; 755 		GPIOG->CR2&=~(1<<0);	
3136  0ac3 72115022      	bres	20514,#0
3137                     ; 758 		GPIOG->DDR&=~(1<<1);
3139  0ac7 72135020      	bres	20512,#1
3140                     ; 759 		GPIOG->CR1|=(1<<1);
3142  0acb 72125021      	bset	20513,#1
3143                     ; 760 		GPIOG->CR2&=~(1<<1);
3145  0acf 72135022      	bres	20514,#1
3146                     ; 762 init_CAN();
3148  0ad3 cd0703        	call	_init_CAN
3150                     ; 770 uart1_init();
3152  0ad6 cd003c        	call	_uart1_init
3154                     ; 772 adress=19;
3156  0ad9 3513009b      	mov	_adress,#19
3157                     ; 774 enableInterrupts();
3160  0add 9a            rim
3162  0ade               L576:
3163                     ; 778 	if(bRX485)
3165  0ade 3d2b          	tnz	_bRX485
3166  0ae0 2703          	jreq	L107
3167                     ; 780 		rx485_in_an();
3169  0ae2 cd021b        	call	_rx485_in_an
3171  0ae5               L107:
3172                     ; 783 	if(bCAN_RX)
3174  0ae5 3d08          	tnz	_bCAN_RX
3175  0ae7 2705          	jreq	L307
3176                     ; 785 		bCAN_RX=0;
3178  0ae9 3f08          	clr	_bCAN_RX
3179                     ; 786 		can_in_an();
3181  0aeb cd0848        	call	_can_in_an
3183  0aee               L307:
3184                     ; 792 	if(b100Hz)
3186                     	btst	_b100Hz
3187  0af3 2404          	jruge	L507
3188                     ; 794 		b100Hz=0;
3190  0af5 72110006      	bres	_b100Hz
3191  0af9               L507:
3192                     ; 797 	if(b10Hz)
3194                     	btst	_b10Hz
3195  0afe 2407          	jruge	L707
3196                     ; 799 		b10Hz=0;
3198  0b00 72110005      	bres	_b10Hz
3199                     ; 801 			can_tx_hndl();
3201  0b04 cd07de        	call	_can_tx_hndl
3203  0b07               L707:
3204                     ; 807 	if(b2Hz)
3206                     	btst	_b2Hz
3207  0b0c 2503          	jrult	L221
3208  0b0e cc0bd8        	jp	L117
3209  0b11               L221:
3210                     ; 809 		b2Hz=0;
3212  0b11 72110003      	bres	_b2Hz
3213                     ; 811 		if(bBAT_REQ)
3215                     	btst	_bBAT_REQ
3216  0b1a 245f          	jruge	L317
3217                     ; 813 			bBAT_REQ=0;
3219  0b1c 72110001      	bres	_bBAT_REQ
3220                     ; 815 			rs485_out_buff[0]=0x7e;
3222  0b20 357e00bc      	mov	_rs485_out_buff,#126
3223                     ; 816 			rs485_out_buff[1]=0x31;
3225  0b24 353100bd      	mov	_rs485_out_buff+1,#49
3226                     ; 817 			rs485_out_buff[2]=0x31;
3228  0b28 353100be      	mov	_rs485_out_buff+2,#49
3229                     ; 818 			rs485_out_buff[3]=0x30;
3231  0b2c 353000bf      	mov	_rs485_out_buff+3,#48
3232                     ; 819 			rs485_out_buff[4]=0x31;
3234  0b30 353100c0      	mov	_rs485_out_buff+4,#49
3235                     ; 820 			rs485_out_buff[5]=0x44;
3237  0b34 354400c1      	mov	_rs485_out_buff+5,#68
3238                     ; 821 			rs485_out_buff[6]=0x30;
3240  0b38 353000c2      	mov	_rs485_out_buff+6,#48
3241                     ; 822 			rs485_out_buff[7]=0x38;
3243  0b3c 353800c3      	mov	_rs485_out_buff+7,#56
3244                     ; 823 			rs485_out_buff[8]=0x32;
3246  0b40 353200c4      	mov	_rs485_out_buff+8,#50
3247                     ; 824 			rs485_out_buff[9]=0x45;
3249  0b44 354500c5      	mov	_rs485_out_buff+9,#69
3250                     ; 825 			rs485_out_buff[10]=0x30;
3252  0b48 353000c6      	mov	_rs485_out_buff+10,#48
3253                     ; 826 			rs485_out_buff[11]=0x30;
3255  0b4c 353000c7      	mov	_rs485_out_buff+11,#48
3256                     ; 827 			rs485_out_buff[12]=0x32;
3258  0b50 353200c8      	mov	_rs485_out_buff+12,#50
3259                     ; 828 			rs485_out_buff[13]=0x30;
3261  0b54 353000c9      	mov	_rs485_out_buff+13,#48
3262                     ; 829 			rs485_out_buff[14]=0x31;
3264  0b58 353100ca      	mov	_rs485_out_buff+14,#49
3265                     ; 830 			rs485_out_buff[15]=0x46;
3267  0b5c 354600cb      	mov	_rs485_out_buff+15,#70
3268                     ; 831 			rs485_out_buff[16]=0x44;
3270  0b60 354400cc      	mov	_rs485_out_buff+16,#68
3271                     ; 832 			rs485_out_buff[17]=0x32;
3273  0b64 353200cd      	mov	_rs485_out_buff+17,#50
3274                     ; 833 			rs485_out_buff[18]=0x37;
3276  0b68 353700ce      	mov	_rs485_out_buff+18,#55
3277                     ; 834 			rs485_out_buff[19]=0x0d;
3279  0b6c 350d00cf      	mov	_rs485_out_buff+19,#13
3280                     ; 836 			uart1_out_adr(rs485_out_buff,20);
3282  0b70 4b14          	push	#20
3283  0b72 ae00bc        	ldw	x,#_rs485_out_buff
3284  0b75 cd00c3        	call	_uart1_out_adr
3286  0b78 84            	pop	a
3288  0b79 205d          	jra	L117
3289  0b7b               L317:
3290                     ; 840 			bBAT_REQ=1;
3292  0b7b 72100001      	bset	_bBAT_REQ
3293                     ; 842 			rs485_out_buff[0]=0x7e;
3295  0b7f 357e00bc      	mov	_rs485_out_buff,#126
3296                     ; 843 			rs485_out_buff[1]=0x31;
3298  0b83 353100bd      	mov	_rs485_out_buff+1,#49
3299                     ; 844 			rs485_out_buff[2]=0x31;
3301  0b87 353100be      	mov	_rs485_out_buff+2,#49
3302                     ; 845 			rs485_out_buff[3]=0x30;
3304  0b8b 353000bf      	mov	_rs485_out_buff+3,#48
3305                     ; 846 			rs485_out_buff[4]=0x31;
3307  0b8f 353100c0      	mov	_rs485_out_buff+4,#49
3308                     ; 847 			rs485_out_buff[5]=0x44;
3310  0b93 354400c1      	mov	_rs485_out_buff+5,#68
3311                     ; 848 			rs485_out_buff[6]=0x30;
3313  0b97 353000c2      	mov	_rs485_out_buff+6,#48
3314                     ; 849 			rs485_out_buff[7]=0x38;
3316  0b9b 353800c3      	mov	_rs485_out_buff+7,#56
3317                     ; 850 			rs485_out_buff[8]=0x33;
3319  0b9f 353300c4      	mov	_rs485_out_buff+8,#51
3320                     ; 851 			rs485_out_buff[9]=0x45;
3322  0ba3 354500c5      	mov	_rs485_out_buff+9,#69
3323                     ; 852 			rs485_out_buff[10]=0x30;
3325  0ba7 353000c6      	mov	_rs485_out_buff+10,#48
3326                     ; 853 			rs485_out_buff[11]=0x30;
3328  0bab 353000c7      	mov	_rs485_out_buff+11,#48
3329                     ; 854 			rs485_out_buff[12]=0x32;
3331  0baf 353200c8      	mov	_rs485_out_buff+12,#50
3332                     ; 855 			rs485_out_buff[13]=0x30;
3334  0bb3 353000c9      	mov	_rs485_out_buff+13,#48
3335                     ; 856 			rs485_out_buff[14]=0x31;
3337  0bb7 353100ca      	mov	_rs485_out_buff+14,#49
3338                     ; 857 			rs485_out_buff[15]=0x46;
3340  0bbb 354600cb      	mov	_rs485_out_buff+15,#70
3341                     ; 858 			rs485_out_buff[16]=0x44;
3343  0bbf 354400cc      	mov	_rs485_out_buff+16,#68
3344                     ; 859 			rs485_out_buff[17]=0x32;
3346  0bc3 353200cd      	mov	_rs485_out_buff+17,#50
3347                     ; 860 			rs485_out_buff[18]=0x36;
3349  0bc7 353600ce      	mov	_rs485_out_buff+18,#54
3350                     ; 861 			rs485_out_buff[19]=0x0d;
3352  0bcb 350d00cf      	mov	_rs485_out_buff+19,#13
3353                     ; 863 			uart1_out_adr(rs485_out_buff,20);
3355  0bcf 4b14          	push	#20
3356  0bd1 ae00bc        	ldw	x,#_rs485_out_buff
3357  0bd4 cd00c3        	call	_uart1_out_adr
3359  0bd7 84            	pop	a
3360  0bd8               L117:
3361                     ; 867 	if(b1Hz)
3363                     	btst	_b1Hz
3364  0bdd 2503          	jrult	L421
3365  0bdf cc0ade        	jp	L576
3366  0be2               L421:
3367                     ; 869 		b1Hz=0;
3369  0be2 72110002      	bres	_b1Hz
3370                     ; 876 		if(rs485_cnt>=10)
3372  0be6 b60b          	ld	a,_rs485_cnt
3373  0be8 a10a          	cp	a,#10
3374  0bea 2403          	jruge	L621
3375  0bec cc0ade        	jp	L576
3376  0bef               L621:
3377                     ; 878 			rs485_cnt=10;
3379  0bef 350a000b      	mov	_rs485_cnt,#10
3380                     ; 879 			bRS485ERR=1;
3382  0bf3 72100000      	bset	_bRS485ERR
3383  0bf7 acde0ade      	jpf	L576
4102                     	xdef	_main
4103                     	xdef	f_UART1RxInterrupt
4104                     	xdef	f_UART1TxInterrupt
4105                     	xdef	f_CAN_TX_Interrupt
4106                     	xdef	f_CAN_RX_Interrupt
4107                     	xdef	f_TIM4_UPD_Interrupt
4108                     	xdef	_t4_init
4109                     	xdef	_can_in_an
4110                     	xdef	_can_tx_hndl
4111                     	xdef	_can_transmit
4112                     	xdef	_init_CAN
4113                     	xdef	_rx485_in_an
4114                     	xdef	_str2int
4115                     	xdef	_uart1_out_adr
4116                     	xdef	_putchar1
4117                     	xdef	_uart1_init
4118                     	xdef	_gran
4119                     	xdef	_gran_char
4120                     	switch	.ubsct
4121  0000               _transmit_cnt_number:
4122  0000 00            	ds.b	1
4123                     	xdef	_transmit_cnt_number
4124                     .bit:	section	.data,bit
4125  0000               _bRS485ERR:
4126  0000 00            	ds.b	1
4127                     	xdef	_bRS485ERR
4128                     	xdef	_rs485_cnt
4129                     	switch	.ubsct
4130  0001               _flags_byte1:
4131  0001 000000000000  	ds.b	7
4132                     	xdef	_flags_byte1
4133  0008               _flags_byte0:
4134  0008 000000000000  	ds.b	7
4135                     	xdef	_flags_byte0
4136  000f               _b_p_ser_num:
4137  000f 000000000000  	ds.b	14
4138                     	xdef	_b_p_ser_num
4139  001d               _s_o_h:
4140  001d 000000000000  	ds.b	14
4141                     	xdef	_s_o_h
4142                     	switch	.bss
4143  0000               _c_c_l_v:
4144  0000 000000000000  	ds.b	14
4145                     	xdef	_c_c_l_v
4146  000e               _r_b_t:
4147  000e 000000000000  	ds.b	14
4148                     	xdef	_r_b_t
4149  001c               _rat_cap:
4150  001c 000000000000  	ds.b	14
4151                     	xdef	_rat_cap
4152  002a               _s_o_c:
4153  002a 000000000000  	ds.b	14
4154                     	xdef	_s_o_c
4155  0038               _dsch_curr:
4156  0038 000000000000  	ds.b	14
4157                     	xdef	_dsch_curr
4158  0046               _ch_curr:
4159  0046 000000000000  	ds.b	14
4160                     	xdef	_ch_curr
4161  0054               _tot_bat_volt:
4162  0054 000000000000  	ds.b	14
4163                     	xdef	_tot_bat_volt
4164  0062               _min_cell_temp:
4165  0062 000000000000  	ds.b	14
4166                     	xdef	_min_cell_temp
4167  0070               _max_cell_temp:
4168  0070 000000000000  	ds.b	14
4169                     	xdef	_max_cell_temp
4170  007e               _min_cell_volt:
4171  007e 000000000000  	ds.b	14
4172                     	xdef	_min_cell_volt
4173  008c               _max_cell_volt:
4174  008c 000000000000  	ds.b	14
4175                     	xdef	_max_cell_volt
4176                     	switch	.ubsct
4177  002b               _bRX485:
4178  002b 00            	ds.b	1
4179                     	xdef	_bRX485
4180  002c               _rs485_rx_cnt:
4181  002c 0000          	ds.b	2
4182                     	xdef	_rs485_rx_cnt
4183  002e               _plazma_int:
4184  002e 000000000000  	ds.b	6
4185                     	xdef	_plazma_int
4186  0034               _link_cnt:
4187  0034 00            	ds.b	1
4188                     	xdef	_link_cnt
4189  0035               _link:
4190  0035 00            	ds.b	1
4191                     	xdef	_link
4192                     	switch	.bss
4193  009a               _adress_error:
4194  009a 00            	ds.b	1
4195                     	xdef	_adress_error
4196  009b               _adress:
4197  009b 00            	ds.b	1
4198                     	xdef	_adress
4199  009c               _adr:
4200  009c 000000        	ds.b	3
4201                     	xdef	_adr
4202                     	xdef	_adr_drv_stat
4203                     	xdef	_led_ind
4204                     	switch	.ubsct
4205  0036               _led_ind_cnt:
4206  0036 00            	ds.b	1
4207                     	xdef	_led_ind_cnt
4208  0037               _adc_plazma:
4209  0037 000000000000  	ds.b	10
4210                     	xdef	_adc_plazma
4211  0041               _adc_plazma_short:
4212  0041 0000          	ds.b	2
4213                     	xdef	_adc_plazma_short
4214  0043               _adc_cnt:
4215  0043 00            	ds.b	1
4216                     	xdef	_adc_cnt
4217  0044               _adc_ch:
4218  0044 00            	ds.b	1
4219                     	xdef	_adc_ch
4220                     	switch	.bss
4221  009f               _adc_buff_:
4222  009f 000000000000  	ds.b	20
4223                     	xdef	_adc_buff_
4224  00b3               _adc_buff:
4225  00b3 000000000000  	ds.b	320
4226                     	xdef	_adc_buff
4227                     	switch	.ubsct
4228  0045               _T:
4229  0045 00            	ds.b	1
4230                     	xdef	_T
4231  0046               _Udb:
4232  0046 0000          	ds.b	2
4233                     	xdef	_Udb
4234  0048               _Ui:
4235  0048 0000          	ds.b	2
4236                     	xdef	_Ui
4237  004a               _Un:
4238  004a 0000          	ds.b	2
4239                     	xdef	_Un
4240  004c               _I:
4241  004c 0000          	ds.b	2
4242                     	xdef	_I
4243  004e               _can_error_cnt:
4244  004e 00            	ds.b	1
4245                     	xdef	_can_error_cnt
4246                     	xdef	_bCAN_RX
4247  004f               _tx_busy_cnt:
4248  004f 00            	ds.b	1
4249                     	xdef	_tx_busy_cnt
4250                     	xdef	_bTX_FREE
4251  0050               _can_buff_rd_ptr:
4252  0050 00            	ds.b	1
4253                     	xdef	_can_buff_rd_ptr
4254  0051               _can_buff_wr_ptr:
4255  0051 00            	ds.b	1
4256                     	xdef	_can_buff_wr_ptr
4257  0052               _can_out_buff:
4258  0052 000000000000  	ds.b	96
4259                     	xdef	_can_out_buff
4260  00b2               _bOUT_FREE:
4261  00b2 00            	ds.b	1
4262                     	xdef	_bOUT_FREE
4263                     	xdef	_tx_wd_cnt
4264                     	switch	.bss
4265  01f3               _tx_stat_cnt:
4266  01f3 00            	ds.b	1
4267                     	xdef	_tx_stat_cnt
4268                     	switch	.ubsct
4269  00b3               _rx_rd_index1:
4270  00b3 0000          	ds.b	2
4271                     	xdef	_rx_rd_index1
4272  00b5               _rx_wr_index1:
4273  00b5 0000          	ds.b	2
4274                     	xdef	_rx_wr_index1
4275  00b7               _rx_counter1:
4276  00b7 0000          	ds.b	2
4277                     	xdef	_rx_counter1
4278                     	xdef	_rx_buffer
4279  00b9               _tx_rd_index1:
4280  00b9 00            	ds.b	1
4281                     	xdef	_tx_rd_index1
4282  00ba               _tx_wr_index1:
4283  00ba 00            	ds.b	1
4284                     	xdef	_tx_wr_index1
4285  00bb               _tx_counter1:
4286  00bb 00            	ds.b	1
4287                     	xdef	_tx_counter1
4288                     	xdef	_tx_buffer1
4289  00bc               _rs485_out_buff:
4290  00bc 000000000000  	ds.b	20
4291                     	xdef	_rs485_out_buff
4292  00d0               _mess:
4293  00d0 000000000000  	ds.b	14
4294                     	xdef	_mess
4295                     	switch	.bit
4296  0001               _bBAT_REQ:
4297  0001 00            	ds.b	1
4298                     	xdef	_bBAT_REQ
4299  0002               _b1Hz:
4300  0002 00            	ds.b	1
4301                     	xdef	_b1Hz
4302  0003               _b2Hz:
4303  0003 00            	ds.b	1
4304                     	xdef	_b2Hz
4305  0004               _b5Hz:
4306  0004 00            	ds.b	1
4307                     	xdef	_b5Hz
4308  0005               _b10Hz:
4309  0005 00            	ds.b	1
4310                     	xdef	_b10Hz
4311  0006               _b100Hz:
4312  0006 00            	ds.b	1
4313                     	xdef	_b100Hz
4314                     	xdef	_t0_cnt4
4315                     	xdef	_t0_cnt3
4316                     	xdef	_t0_cnt2
4317                     	xdef	_t0_cnt1
4318                     	xdef	_t0_cnt0
4319                     	xref	_pow
4320                     	xref	_isalnum
4321                     	xdef	_tx_stat
4322                     	switch	.const
4323  000a               L713:
4324  000a 41800000      	dc.w	16768,0
4325                     	xref.b	c_lreg
4326                     	xref.b	c_x
4346                     	xref	c_imul
4347                     	xref	c_ftoi
4348                     	xref	c_itof
4349                     	xref	c_xymvx
4350                     	end
