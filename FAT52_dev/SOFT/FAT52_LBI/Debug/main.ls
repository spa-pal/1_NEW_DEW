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
  29  0001 000000000000  	ds.b	299
  30  012c               _rx_buffer:
  31  012c 00            	dc.b	0
  32  012d 000000000000  	ds.b	49
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
 372                     ; 161 if (tx_counter1 || ((UART1->SR & UART1_SR_TXE)==0))
 374  0089 3d91          	tnz	_tx_counter1
 375  008b 2607          	jrne	L521
 377  008d c65230        	ld	a,21040
 378  0090 a580          	bcp	a,#128
 379  0092 261a          	jrne	L321
 380  0094               L521:
 381                     ; 163    tx_buffer1[tx_wr_index1]=c;
 383  0094 5f            	clrw	x
 384  0095 b690          	ld	a,_tx_wr_index1
 385  0097 2a01          	jrpl	L41
 386  0099 53            	cplw	x
 387  009a               L41:
 388  009a 97            	ld	xl,a
 389  009b 7b01          	ld	a,(OFST+1,sp)
 390  009d d70000        	ld	(_tx_buffer1,x),a
 391                     ; 164    if (++tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
 393  00a0 3c90          	inc	_tx_wr_index1
 395                     ; 165    ++tx_counter1;
 398  00a2 3c91          	inc	_tx_counter1
 400  00a4               L131:
 401                     ; 169 UART1->CR2|= UART1_CR2_TIEN | UART1_CR2_TCIEN;
 403  00a4 c65235        	ld	a,21045
 404  00a7 aac0          	or	a,#192
 405  00a9 c75235        	ld	21045,a
 406                     ; 170 }
 409  00ac 84            	pop	a
 410  00ad 81            	ret
 411  00ae               L321:
 412                     ; 167 else UART1->DR=c;
 414  00ae 7b01          	ld	a,(OFST+1,sp)
 415  00b0 c75231        	ld	21041,a
 416  00b3 20ef          	jra	L131
 491                     ; 174 void uart1_out_adr(char *ptr, char len)
 491                     ; 175 {
 492                     	switch	.text
 493  00b5               _uart1_out_adr:
 495  00b5 89            	pushw	x
 496  00b6 5220          	subw	sp,#32
 497       00000020      OFST:	set	32
 500                     ; 177 @near char i,t=0;
 502  00b8 0f01          	clr	(OFST-31,sp)
 503                     ; 181 GPIOB->ODR|=(1<<7);
 505  00ba 721e5005      	bset	20485,#7
 506                     ; 184 for(i=0;i<len;i++)
 508  00be 0f20          	clr	(OFST+0,sp)
 510  00c0 201d          	jra	L571
 511  00c2               L171:
 512                     ; 186 	UOB1[i]=ptr[i];
 514  00c2 96            	ldw	x,sp
 515  00c3 1c0002        	addw	x,#OFST-30
 516  00c6 9f            	ld	a,xl
 517  00c7 5e            	swapw	x
 518  00c8 1b20          	add	a,(OFST+0,sp)
 519  00ca 2401          	jrnc	L02
 520  00cc 5c            	incw	x
 521  00cd               L02:
 522  00cd 02            	rlwa	x,a
 523  00ce 89            	pushw	x
 524  00cf 7b23          	ld	a,(OFST+3,sp)
 525  00d1 97            	ld	xl,a
 526  00d2 7b24          	ld	a,(OFST+4,sp)
 527  00d4 1b22          	add	a,(OFST+2,sp)
 528  00d6 2401          	jrnc	L22
 529  00d8 5c            	incw	x
 530  00d9               L22:
 531  00d9 02            	rlwa	x,a
 532  00da f6            	ld	a,(x)
 533  00db 85            	popw	x
 534  00dc f7            	ld	(x),a
 535                     ; 184 for(i=0;i<len;i++)
 537  00dd 0c20          	inc	(OFST+0,sp)
 538  00df               L571:
 541  00df 7b20          	ld	a,(OFST+0,sp)
 542  00e1 1125          	cp	a,(OFST+5,sp)
 543  00e3 25dd          	jrult	L171
 544                     ; 192 tx_stat=tsON;
 546  00e5 35010005      	mov	_tx_stat,#1
 547                     ; 194 for (i=0;i<len;i++)
 549  00e9 0f20          	clr	(OFST+0,sp)
 551  00eb 2011          	jra	L502
 552  00ed               L102:
 553                     ; 196 	putchar1(UOB1[i]);
 555  00ed 96            	ldw	x,sp
 556  00ee 1c0002        	addw	x,#OFST-30
 557  00f1 9f            	ld	a,xl
 558  00f2 5e            	swapw	x
 559  00f3 1b20          	add	a,(OFST+0,sp)
 560  00f5 2401          	jrnc	L42
 561  00f7 5c            	incw	x
 562  00f8               L42:
 563  00f8 02            	rlwa	x,a
 564  00f9 f6            	ld	a,(x)
 565  00fa ad8c          	call	_putchar1
 567                     ; 194 for (i=0;i<len;i++)
 569  00fc 0c20          	inc	(OFST+0,sp)
 570  00fe               L502:
 573  00fe 7b20          	ld	a,(OFST+0,sp)
 574  0100 1125          	cp	a,(OFST+5,sp)
 575  0102 25e9          	jrult	L102
 576                     ; 199 rs485_cnt++;
 578  0104 3c0b          	inc	_rs485_cnt
 579                     ; 200 }
 582  0106 5b22          	addw	sp,#34
 583  0108 81            	ret
 586                     .const:	section	.text
 587  0000               L112_temp:
 588  0000 00            	dc.b	0
 589  0001 00            	dc.b	0
 590  0002 00            	dc.b	0
 591  0003 00            	dc.b	0
 592  0004 00            	dc.b	0
 593  0005 00            	dc.b	0
 594  0006 00            	dc.b	0
 595  0007 00            	dc.b	0
 596  0008 00            	dc.b	0
 597  0009 00            	ds.b	1
 678                     ; 203 int str2int(char *ptr, char len)
 678                     ; 204 {
 679                     	switch	.text
 680  0109               _str2int:
 682  0109 89            	pushw	x
 683  010a 5210          	subw	sp,#16
 684       00000010      OFST:	set	16
 687                     ; 208 @near char temp[10]={0,0,0,0,0,0,0,0,0};
 689  010c 96            	ldw	x,sp
 690  010d 1c0005        	addw	x,#OFST-11
 691  0110 90ae0000      	ldw	y,#L112_temp
 692  0114 a60a          	ld	a,#10
 693  0116 cd0000        	call	c_xymvx
 695                     ; 209 @near int temp_out=0;
 697  0119 5f            	clrw	x
 698  011a 1f03          	ldw	(OFST-13,sp),x
 699                     ; 213 for (i=0;i<len;i++)
 701  011c 0f10          	clr	(OFST+0,sp)
 703  011e acaf01af      	jpf	L162
 704  0122               L552:
 705                     ; 215 	tt=*(ptr+i);
 707  0122 7b11          	ld	a,(OFST+1,sp)
 708  0124 97            	ld	xl,a
 709  0125 7b12          	ld	a,(OFST+2,sp)
 710  0127 1b10          	add	a,(OFST+0,sp)
 711  0129 2401          	jrnc	L03
 712  012b 5c            	incw	x
 713  012c               L03:
 714  012c 02            	rlwa	x,a
 715  012d f6            	ld	a,(x)
 716  012e 6b0f          	ld	(OFST-1,sp),a
 717                     ; 217 	if(isalnum(tt/**(ptr+i)*/))
 719  0130 7b0f          	ld	a,(OFST-1,sp)
 720  0132 cd0000        	call	_isalnum
 722  0135 4d            	tnz	a
 723  0136 2775          	jreq	L562
 724                     ; 219 		if(isdigit(tt/**(ptr+i)*/))
 726  0138 7b0f          	ld	a,(OFST-1,sp)
 727  013a a130          	cp	a,#48
 728  013c 2517          	jrult	L762
 730  013e 7b0f          	ld	a,(OFST-1,sp)
 731  0140 a13a          	cp	a,#58
 732  0142 2411          	jruge	L762
 733                     ; 221 		temp[i]=tt/**(ptr+i)*/-'0';
 735  0144 96            	ldw	x,sp
 736  0145 1c0005        	addw	x,#OFST-11
 737  0148 9f            	ld	a,xl
 738  0149 5e            	swapw	x
 739  014a 1b10          	add	a,(OFST+0,sp)
 740  014c 2401          	jrnc	L23
 741  014e 5c            	incw	x
 742  014f               L23:
 743  014f 02            	rlwa	x,a
 744  0150 7b0f          	ld	a,(OFST-1,sp)
 745  0152 a030          	sub	a,#48
 746  0154 f7            	ld	(x),a
 747  0155               L762:
 748                     ; 223 		if(islower(tt/**(ptr+i)*/))
 750  0155 7b0f          	ld	a,(OFST-1,sp)
 751  0157 a161          	cp	a,#97
 752  0159 2517          	jrult	L172
 754  015b 7b0f          	ld	a,(OFST-1,sp)
 755  015d a17b          	cp	a,#123
 756  015f 2411          	jruge	L172
 757                     ; 225 		temp[i]=tt/**(ptr+i)*/-'a'+10;
 759  0161 96            	ldw	x,sp
 760  0162 1c0005        	addw	x,#OFST-11
 761  0165 9f            	ld	a,xl
 762  0166 5e            	swapw	x
 763  0167 1b10          	add	a,(OFST+0,sp)
 764  0169 2401          	jrnc	L43
 765  016b 5c            	incw	x
 766  016c               L43:
 767  016c 02            	rlwa	x,a
 768  016d 7b0f          	ld	a,(OFST-1,sp)
 769  016f a057          	sub	a,#87
 770  0171 f7            	ld	(x),a
 771  0172               L172:
 772                     ; 227 		if(isupper(tt/**(ptr+i)*/))
 774  0172 7b0f          	ld	a,(OFST-1,sp)
 775  0174 a141          	cp	a,#65
 776  0176 2535          	jrult	L562
 778  0178 7b0f          	ld	a,(OFST-1,sp)
 779  017a a15b          	cp	a,#91
 780  017c 242f          	jruge	L562
 781                     ; 229 		temp[i]=tt;
 783  017e 96            	ldw	x,sp
 784  017f 1c0005        	addw	x,#OFST-11
 785  0182 9f            	ld	a,xl
 786  0183 5e            	swapw	x
 787  0184 1b10          	add	a,(OFST+0,sp)
 788  0186 2401          	jrnc	L63
 789  0188 5c            	incw	x
 790  0189               L63:
 791  0189 02            	rlwa	x,a
 792  018a 7b0f          	ld	a,(OFST-1,sp)
 793  018c f7            	ld	(x),a
 794                     ; 230 		temp[i]-=/**(ptr+i)*/'A';
 796  018d 96            	ldw	x,sp
 797  018e 1c0005        	addw	x,#OFST-11
 798  0191 9f            	ld	a,xl
 799  0192 5e            	swapw	x
 800  0193 1b10          	add	a,(OFST+0,sp)
 801  0195 2401          	jrnc	L04
 802  0197 5c            	incw	x
 803  0198               L04:
 804  0198 02            	rlwa	x,a
 805  0199 f6            	ld	a,(x)
 806  019a a041          	sub	a,#65
 807  019c f7            	ld	(x),a
 808                     ; 231 		temp[i]+=10;
 810  019d 96            	ldw	x,sp
 811  019e 1c0005        	addw	x,#OFST-11
 812  01a1 9f            	ld	a,xl
 813  01a2 5e            	swapw	x
 814  01a3 1b10          	add	a,(OFST+0,sp)
 815  01a5 2401          	jrnc	L24
 816  01a7 5c            	incw	x
 817  01a8               L24:
 818  01a8 02            	rlwa	x,a
 819  01a9 f6            	ld	a,(x)
 820  01aa ab0a          	add	a,#10
 821  01ac f7            	ld	(x),a
 822  01ad               L562:
 823                     ; 213 for (i=0;i<len;i++)
 825  01ad 0c10          	inc	(OFST+0,sp)
 826  01af               L162:
 829  01af 7b10          	ld	a,(OFST+0,sp)
 830  01b1 1115          	cp	a,(OFST+5,sp)
 831  01b3 2403          	jruge	L64
 832  01b5 cc0122        	jp	L552
 833  01b8               L64:
 834                     ; 237 for(i=len;i;i--)
 836  01b8 7b15          	ld	a,(OFST+5,sp)
 837  01ba 6b10          	ld	(OFST+0,sp),a
 839  01bc 2045          	jra	L103
 840  01be               L572:
 841                     ; 239 	temp_out+= ((int)pow(16,len-i))*temp[i-1]; 
 843  01be 7b15          	ld	a,(OFST+5,sp)
 844  01c0 5f            	clrw	x
 845  01c1 1010          	sub	a,(OFST+0,sp)
 846  01c3 2401          	jrnc	L44
 847  01c5 5a            	decw	x
 848  01c6               L44:
 849  01c6 02            	rlwa	x,a
 850  01c7 cd0000        	call	c_itof
 852  01ca be02          	ldw	x,c_lreg+2
 853  01cc 89            	pushw	x
 854  01cd be00          	ldw	x,c_lreg
 855  01cf 89            	pushw	x
 856  01d0 ce000c        	ldw	x,L113+2
 857  01d3 89            	pushw	x
 858  01d4 ce000a        	ldw	x,L113
 859  01d7 89            	pushw	x
 860  01d8 cd0000        	call	_pow
 862  01db 5b08          	addw	sp,#8
 863  01dd cd0000        	call	c_ftoi
 865  01e0 9096          	ldw	y,sp
 866  01e2 72a90005      	addw	y,#OFST-11
 867  01e6 1701          	ldw	(OFST-15,sp),y
 868  01e8 7b10          	ld	a,(OFST+0,sp)
 869  01ea 905f          	clrw	y
 870  01ec 9097          	ld	yl,a
 871  01ee 905a          	decw	y
 872  01f0 72f901        	addw	y,(OFST-15,sp)
 873  01f3 90f6          	ld	a,(y)
 874  01f5 905f          	clrw	y
 875  01f7 9097          	ld	yl,a
 876  01f9 cd0000        	call	c_imul
 878  01fc 72fb03        	addw	x,(OFST-13,sp)
 879  01ff 1f03          	ldw	(OFST-13,sp),x
 880                     ; 237 for(i=len;i;i--)
 882  0201 0a10          	dec	(OFST+0,sp)
 883  0203               L103:
 886  0203 0d10          	tnz	(OFST+0,sp)
 887  0205 26b7          	jrne	L572
 888                     ; 244 return temp_out;
 890  0207 1e03          	ldw	x,(OFST-13,sp)
 893  0209 5b12          	addw	sp,#18
 894  020b 81            	ret
 921                     ; 248 void rx485_in_an(void)
 921                     ; 249 {
 922                     	switch	.text
 923  020c               _rx485_in_an:
 927                     ; 252 	if(bRX485==1)
 929  020c b601          	ld	a,_bRX485
 930  020e a101          	cp	a,#1
 931  0210 2703          	jreq	L25
 932  0212 cc04e5        	jp	L523
 933  0215               L25:
 934                     ; 254 	GPIOD->DDR|=(1<<7);
 936  0215 721e5011      	bset	20497,#7
 937                     ; 255 	GPIOD->CR1|=(1<<7);
 939  0219 721e5012      	bset	20498,#7
 940                     ; 256 	GPIOD->CR2&=~(1<<7);	
 942  021d 721f5013      	bres	20499,#7
 943                     ; 257 	GPIOD->ODR^=(1<<7);
 945  0221 c6500f        	ld	a,20495
 946  0224 a880          	xor	a,	#128
 947  0226 c7500f        	ld	20495,a
 948                     ; 259 	tx_buffer1[0]=0x7e;
 950  0229 357e0000      	mov	_tx_buffer1,#126
 951                     ; 260 	tx_buffer1[1]=0x31;
 953  022d 35310001      	mov	_tx_buffer1+1,#49
 954                     ; 261 	tx_buffer1[2]=0x31;
 956  0231 35310002      	mov	_tx_buffer1+2,#49
 957                     ; 262 	tx_buffer1[3]=0x30;
 959  0235 35300003      	mov	_tx_buffer1+3,#48
 960                     ; 263 	tx_buffer1[4]=0x31;
 962  0239 35310004      	mov	_tx_buffer1+4,#49
 963                     ; 264 	tx_buffer1[5]=0x44;
 965  023d 35440005      	mov	_tx_buffer1+5,#68
 966                     ; 265 	tx_buffer1[6]=0x30;
 968  0241 35300006      	mov	_tx_buffer1+6,#48
 969                     ; 266 	tx_buffer1[7]=0x30;
 971  0245 35300007      	mov	_tx_buffer1+7,#48
 972                     ; 267 	tx_buffer1[8]=0x30;
 974  0249 35300008      	mov	_tx_buffer1+8,#48
 975                     ; 268 	tx_buffer1[9]=0x36;
 977  024d 35360009      	mov	_tx_buffer1+9,#54
 978                     ; 269 	tx_buffer1[10]=0x31;
 980  0251 3531000a      	mov	_tx_buffer1+10,#49
 981                     ; 270 	tx_buffer1[11]=0x31;
 983  0255 3531000b      	mov	_tx_buffer1+11,#49
 984                     ; 271 	tx_buffer1[12]=0x38;
 986  0259 3538000c      	mov	_tx_buffer1+12,#56
 987                     ; 273 	tx_buffer1[13]=0x30;
 989  025d 3530000d      	mov	_tx_buffer1+13,#48
 990                     ; 274 	tx_buffer1[14]=0x44;
 992  0261 3544000e      	mov	_tx_buffer1+14,#68
 993                     ; 275 	tx_buffer1[15]=0x37;
 995  0265 3537000f      	mov	_tx_buffer1+15,#55
 996                     ; 276 	tx_buffer1[16]=0x41;
 998  0269 35410010      	mov	_tx_buffer1+16,#65
 999                     ; 277 	tx_buffer1[17]=0x30;
1001  026d 35300011      	mov	_tx_buffer1+17,#48
1002                     ; 278 	tx_buffer1[18]=0x44;
1004  0271 35440012      	mov	_tx_buffer1+18,#68
1005                     ; 279 	tx_buffer1[19]=0x33;
1007  0275 35330013      	mov	_tx_buffer1+19,#51
1008                     ; 280 	tx_buffer1[20]=0x43;
1010  0279 35430014      	mov	_tx_buffer1+20,#67
1011                     ; 281 	tx_buffer1[21]=0x31;
1013  027d 35310015      	mov	_tx_buffer1+21,#49
1014                     ; 282 	tx_buffer1[22]=0x38;
1016  0281 35380016      	mov	_tx_buffer1+22,#56
1017                     ; 283 	tx_buffer1[23]=0x31;
1019  0285 35310017      	mov	_tx_buffer1+23,#49
1020                     ; 284 	tx_buffer1[24]=0x38;
1022  0289 35380018      	mov	_tx_buffer1+24,#56
1023                     ; 285 	tx_buffer1[25]=0x31;
1025  028d 35310019      	mov	_tx_buffer1+25,#49
1026                     ; 286 	tx_buffer1[26]=0x34;
1028  0291 3534001a      	mov	_tx_buffer1+26,#52
1029                     ; 287 	tx_buffer1[27]=0x31;
1031  0295 3531001b      	mov	_tx_buffer1+27,#49
1032                     ; 288 	tx_buffer1[28]=0x32;
1034  0299 3532001c      	mov	_tx_buffer1+28,#50
1035                     ; 289 	tx_buffer1[29]=0x30;
1037  029d 3530001d      	mov	_tx_buffer1+29,#48
1038                     ; 290 	tx_buffer1[30]=0x30;
1040  02a1 3530001e      	mov	_tx_buffer1+30,#48
1041                     ; 291 	tx_buffer1[31]=0x30;
1043  02a5 3530001f      	mov	_tx_buffer1+31,#48
1044                     ; 292 	tx_buffer1[32]=0x30;
1046  02a9 35300020      	mov	_tx_buffer1+32,#48
1047                     ; 293 	tx_buffer1[33]=0x30;
1049  02ad 35300021      	mov	_tx_buffer1+33,#48
1050                     ; 294 	tx_buffer1[34]=0x30;
1052  02b1 35300022      	mov	_tx_buffer1+34,#48
1053                     ; 295 	tx_buffer1[35]=0x35;
1055  02b5 35350023      	mov	_tx_buffer1+35,#53
1056                     ; 296 	tx_buffer1[36]=0x35;
1058  02b9 35350024      	mov	_tx_buffer1+36,#53
1059                     ; 297 	tx_buffer1[37]=0x36;
1061  02bd 35360025      	mov	_tx_buffer1+37,#54
1062                     ; 298 	tx_buffer1[38]=0x33;
1064  02c1 35330026      	mov	_tx_buffer1+38,#51
1065                     ; 299 	tx_buffer1[39]=0x31;
1067  02c5 35310027      	mov	_tx_buffer1+39,#49
1068                     ; 300 	tx_buffer1[40]=0x44;
1070  02c9 35440028      	mov	_tx_buffer1+40,#68
1071                     ; 301 	tx_buffer1[41]=0x34;
1073  02cd 35340029      	mov	_tx_buffer1+41,#52
1074                     ; 302 	tx_buffer1[42]=0x43;
1076  02d1 3543002a      	mov	_tx_buffer1+42,#67
1077                     ; 303 	tx_buffer1[43]=0x46;
1079  02d5 3546002b      	mov	_tx_buffer1+43,#70
1080                     ; 304 	tx_buffer1[44]=0x46;
1082  02d9 3546002c      	mov	_tx_buffer1+44,#70
1083                     ; 305 	tx_buffer1[45]=0x30;
1085  02dd 3530002d      	mov	_tx_buffer1+45,#48
1086                     ; 306 	tx_buffer1[46]=0x45;
1088  02e1 3545002e      	mov	_tx_buffer1+46,#69
1089                     ; 307 	tx_buffer1[47]=0x41;
1091  02e5 3541002f      	mov	_tx_buffer1+47,#65
1092                     ; 308 	tx_buffer1[48]=0x36;
1094  02e9 35360030      	mov	_tx_buffer1+48,#54
1095                     ; 309 	tx_buffer1[49]=0x36;
1097  02ed 35360031      	mov	_tx_buffer1+49,#54
1098                     ; 310 	tx_buffer1[50]=0x34;
1100  02f1 35340032      	mov	_tx_buffer1+50,#52
1101                     ; 311 	tx_buffer1[51]=0x30;
1103  02f5 35300033      	mov	_tx_buffer1+51,#48
1104                     ; 312 	tx_buffer1[52]=0x31;	
1106  02f9 35310034      	mov	_tx_buffer1+52,#49
1107                     ; 314 	tx_buffer1[13+40]=0x30;
1109  02fd 35300035      	mov	_tx_buffer1+53,#48
1110                     ; 315 	tx_buffer1[14+40]=0x44;
1112  0301 35440036      	mov	_tx_buffer1+54,#68
1113                     ; 316 	tx_buffer1[15+40]=0x37;
1115  0305 35370037      	mov	_tx_buffer1+55,#55
1116                     ; 317 	tx_buffer1[16+40]=0x41;
1118  0309 35410038      	mov	_tx_buffer1+56,#65
1119                     ; 318 	tx_buffer1[17+40]=0x30;
1121  030d 35300039      	mov	_tx_buffer1+57,#48
1122                     ; 319 	tx_buffer1[18+40]=0x44;
1124  0311 3544003a      	mov	_tx_buffer1+58,#68
1125                     ; 320 	tx_buffer1[19+40]=0x33;
1127  0315 3533003b      	mov	_tx_buffer1+59,#51
1128                     ; 321 	tx_buffer1[20+40]=0x43;
1130  0319 3543003c      	mov	_tx_buffer1+60,#67
1131                     ; 322 	tx_buffer1[21+40]=0x31;
1133  031d 3531003d      	mov	_tx_buffer1+61,#49
1134                     ; 323 	tx_buffer1[22+40]=0x38;
1136  0321 3538003e      	mov	_tx_buffer1+62,#56
1137                     ; 324 	tx_buffer1[23+40]=0x31;
1139  0325 3531003f      	mov	_tx_buffer1+63,#49
1140                     ; 325 	tx_buffer1[24+40]=0x38;
1142  0329 35380040      	mov	_tx_buffer1+64,#56
1143                     ; 326 	tx_buffer1[25+40]=0x31;
1145  032d 35310041      	mov	_tx_buffer1+65,#49
1146                     ; 327 	tx_buffer1[26+40]=0x34;
1148  0331 35340042      	mov	_tx_buffer1+66,#52
1149                     ; 328 	tx_buffer1[27+40]=0x31;
1151  0335 35310043      	mov	_tx_buffer1+67,#49
1152                     ; 329 	tx_buffer1[28+40]=0x32;
1154  0339 35320044      	mov	_tx_buffer1+68,#50
1155                     ; 330 	tx_buffer1[29+40]=0x30;
1157  033d 35300045      	mov	_tx_buffer1+69,#48
1158                     ; 331 	tx_buffer1[30+40]=0x30;
1160  0341 35300046      	mov	_tx_buffer1+70,#48
1161                     ; 332 	tx_buffer1[31+40]=0x30;
1163  0345 35300047      	mov	_tx_buffer1+71,#48
1164                     ; 333 	tx_buffer1[32+40]=0x30;
1166  0349 35300048      	mov	_tx_buffer1+72,#48
1167                     ; 334 	tx_buffer1[33+40]=0x30;
1169  034d 35300049      	mov	_tx_buffer1+73,#48
1170                     ; 335 	tx_buffer1[34+40]=0x30;
1172  0351 3530004a      	mov	_tx_buffer1+74,#48
1173                     ; 336 	tx_buffer1[35+40]=0x35;
1175  0355 3535004b      	mov	_tx_buffer1+75,#53
1176                     ; 337 	tx_buffer1[36+40]=0x35;
1178  0359 3535004c      	mov	_tx_buffer1+76,#53
1179                     ; 338 	tx_buffer1[37+40]=0x36;
1181  035d 3536004d      	mov	_tx_buffer1+77,#54
1182                     ; 339 	tx_buffer1[38+40]=0x33;
1184  0361 3533004e      	mov	_tx_buffer1+78,#51
1185                     ; 340 	tx_buffer1[39+40]=0x31;
1187  0365 3531004f      	mov	_tx_buffer1+79,#49
1188                     ; 341 	tx_buffer1[40+40]=0x44;
1190  0369 35440050      	mov	_tx_buffer1+80,#68
1191                     ; 342 	tx_buffer1[41+40]=0x34;
1193  036d 35340051      	mov	_tx_buffer1+81,#52
1194                     ; 343 	tx_buffer1[42+40]=0x43;
1196  0371 35430052      	mov	_tx_buffer1+82,#67
1197                     ; 344 	tx_buffer1[43+40]=0x46;
1199  0375 35460053      	mov	_tx_buffer1+83,#70
1200                     ; 345 	tx_buffer1[44+40]=0x46;
1202  0379 35460054      	mov	_tx_buffer1+84,#70
1203                     ; 346 	tx_buffer1[45+40]=0x30;
1205  037d 35300055      	mov	_tx_buffer1+85,#48
1206                     ; 347 	tx_buffer1[46+40]=0x45;
1208  0381 35450056      	mov	_tx_buffer1+86,#69
1209                     ; 348 	tx_buffer1[47+40]=0x41;
1211  0385 35410057      	mov	_tx_buffer1+87,#65
1212                     ; 349 	tx_buffer1[48+40]=0x36;
1214  0389 35360058      	mov	_tx_buffer1+88,#54
1215                     ; 350 	tx_buffer1[49+40]=0x36;
1217  038d 35360059      	mov	_tx_buffer1+89,#54
1218                     ; 351 	tx_buffer1[50+40]=0x34;
1220  0391 3534005a      	mov	_tx_buffer1+90,#52
1221                     ; 352 	tx_buffer1[51+40]=0x30;
1223  0395 3530005b      	mov	_tx_buffer1+91,#48
1224                     ; 353 	tx_buffer1[52+40]=0x32;	
1226  0399 3532005c      	mov	_tx_buffer1+92,#50
1227                     ; 355 	tx_buffer1[13+80]=0x30;
1229  039d 3530005d      	mov	_tx_buffer1+93,#48
1230                     ; 356 	tx_buffer1[14+80]=0x44;
1232  03a1 3544005e      	mov	_tx_buffer1+94,#68
1233                     ; 357 	tx_buffer1[15+80]=0x37;
1235  03a5 3537005f      	mov	_tx_buffer1+95,#55
1236                     ; 358 	tx_buffer1[16+80]=0x41;
1238  03a9 35410060      	mov	_tx_buffer1+96,#65
1239                     ; 359 	tx_buffer1[17+80]=0x30;
1241  03ad 35300061      	mov	_tx_buffer1+97,#48
1242                     ; 360 	tx_buffer1[18+80]=0x44;
1244  03b1 35440062      	mov	_tx_buffer1+98,#68
1245                     ; 361 	tx_buffer1[19+80]=0x33;
1247  03b5 35330063      	mov	_tx_buffer1+99,#51
1248                     ; 362 	tx_buffer1[20+80]=0x43;
1250  03b9 35430064      	mov	_tx_buffer1+100,#67
1251                     ; 363 	tx_buffer1[21+80]=0x31;
1253  03bd 35310065      	mov	_tx_buffer1+101,#49
1254                     ; 364 	tx_buffer1[22+80]=0x38;
1256  03c1 35380066      	mov	_tx_buffer1+102,#56
1257                     ; 365 	tx_buffer1[23+80]=0x31;
1259  03c5 35310067      	mov	_tx_buffer1+103,#49
1260                     ; 366 	tx_buffer1[24+80]=0x38;
1262  03c9 35380068      	mov	_tx_buffer1+104,#56
1263                     ; 367 	tx_buffer1[25+80]=0x31;
1265  03cd 35310069      	mov	_tx_buffer1+105,#49
1266                     ; 368 	tx_buffer1[26+80]=0x34;
1268  03d1 3534006a      	mov	_tx_buffer1+106,#52
1269                     ; 369 	tx_buffer1[27+80]=0x31;
1271  03d5 3531006b      	mov	_tx_buffer1+107,#49
1272                     ; 370 	tx_buffer1[28+80]=0x32;
1274  03d9 3532006c      	mov	_tx_buffer1+108,#50
1275                     ; 371 	tx_buffer1[29+80]=0x30;
1277  03dd 3530006d      	mov	_tx_buffer1+109,#48
1278                     ; 372 	tx_buffer1[30+80]=0x30;
1280  03e1 3530006e      	mov	_tx_buffer1+110,#48
1281                     ; 373 	tx_buffer1[31+80]=0x30;
1283  03e5 3530006f      	mov	_tx_buffer1+111,#48
1284                     ; 374 	tx_buffer1[32+80]=0x30;
1286  03e9 35300070      	mov	_tx_buffer1+112,#48
1287                     ; 375 	tx_buffer1[33+80]=0x30;
1289  03ed 35300071      	mov	_tx_buffer1+113,#48
1290                     ; 376 	tx_buffer1[34+80]=0x30;
1292  03f1 35300072      	mov	_tx_buffer1+114,#48
1293                     ; 377 	tx_buffer1[35+80]=0x35;
1295  03f5 35350073      	mov	_tx_buffer1+115,#53
1296                     ; 378 	tx_buffer1[36+80]=0x35;
1298  03f9 35350074      	mov	_tx_buffer1+116,#53
1299                     ; 379 	tx_buffer1[37+80]=0x36;
1301  03fd 35360075      	mov	_tx_buffer1+117,#54
1302                     ; 380 	tx_buffer1[38+80]=0x33;
1304  0401 35330076      	mov	_tx_buffer1+118,#51
1305                     ; 381 	tx_buffer1[39+80]=0x31;
1307  0405 35310077      	mov	_tx_buffer1+119,#49
1308                     ; 382 	tx_buffer1[40+80]=0x44;
1310  0409 35440078      	mov	_tx_buffer1+120,#68
1311                     ; 383 	tx_buffer1[41+80]=0x34;
1313  040d 35340079      	mov	_tx_buffer1+121,#52
1314                     ; 384 	tx_buffer1[42+80]=0x43;
1316  0411 3543007a      	mov	_tx_buffer1+122,#67
1317                     ; 385 	tx_buffer1[43+80]=0x46;
1319  0415 3546007b      	mov	_tx_buffer1+123,#70
1320                     ; 386 	tx_buffer1[44+80]=0x46;
1322  0419 3546007c      	mov	_tx_buffer1+124,#70
1323                     ; 387 	tx_buffer1[45+80]=0x30;
1325  041d 3530007d      	mov	_tx_buffer1+125,#48
1326                     ; 388 	tx_buffer1[46+80]=0x45;
1328  0421 3545007e      	mov	_tx_buffer1+126,#69
1329                     ; 389 	tx_buffer1[47+80]=0x41;
1331  0425 3541007f      	mov	_tx_buffer1+127,#65
1332                     ; 390 	tx_buffer1[48+80]=0x36;
1334  0429 35360080      	mov	_tx_buffer1+128,#54
1335                     ; 391 	tx_buffer1[49+80]=0x36;
1337  042d 35360081      	mov	_tx_buffer1+129,#54
1338                     ; 392 	tx_buffer1[50+80]=0x34;
1340  0431 35340082      	mov	_tx_buffer1+130,#52
1341                     ; 393 	tx_buffer1[51+80]=0x30;
1343  0435 35300083      	mov	_tx_buffer1+131,#48
1344                     ; 394 	tx_buffer1[52+80]=0x33;
1346  0439 35330084      	mov	_tx_buffer1+132,#51
1347                     ; 396 	tx_buffer1[13+120]=0x30;
1349  043d 35300085      	mov	_tx_buffer1+133,#48
1350                     ; 397 	tx_buffer1[14+120]=0x44;
1352  0441 35440086      	mov	_tx_buffer1+134,#68
1353                     ; 398 	tx_buffer1[15+120]=0x37;
1355  0445 35370087      	mov	_tx_buffer1+135,#55
1356                     ; 399 	tx_buffer1[16+120]=0x41;
1358  0449 35410088      	mov	_tx_buffer1+136,#65
1359                     ; 400 	tx_buffer1[17+120]=0x30;
1361  044d 35300089      	mov	_tx_buffer1+137,#48
1362                     ; 401 	tx_buffer1[18+120]=0x44;
1364  0451 3544008a      	mov	_tx_buffer1+138,#68
1365                     ; 402 	tx_buffer1[19+120]=0x33;
1367  0455 3533008b      	mov	_tx_buffer1+139,#51
1368                     ; 403 	tx_buffer1[20+120]=0x43;
1370  0459 3543008c      	mov	_tx_buffer1+140,#67
1371                     ; 404 	tx_buffer1[21+120]=0x31;
1373  045d 3531008d      	mov	_tx_buffer1+141,#49
1374                     ; 405 	tx_buffer1[22+120]=0x38;
1376  0461 3538008e      	mov	_tx_buffer1+142,#56
1377                     ; 406 	tx_buffer1[23+120]=0x31;
1379  0465 3531008f      	mov	_tx_buffer1+143,#49
1380                     ; 407 	tx_buffer1[24+120]=0x38;
1382  0469 35380090      	mov	_tx_buffer1+144,#56
1383                     ; 408 	tx_buffer1[25+120]=0x31;
1385  046d 35310091      	mov	_tx_buffer1+145,#49
1386                     ; 409 	tx_buffer1[26+120]=0x34;
1388  0471 35340092      	mov	_tx_buffer1+146,#52
1389                     ; 410 	tx_buffer1[27+120]=0x31;
1391  0475 35310093      	mov	_tx_buffer1+147,#49
1392                     ; 411 	tx_buffer1[28+120]=0x32;
1394  0479 35320094      	mov	_tx_buffer1+148,#50
1395                     ; 412 	tx_buffer1[29+120]=0x30;
1397  047d 35300095      	mov	_tx_buffer1+149,#48
1398                     ; 413 	tx_buffer1[30+120]=0x30;
1400  0481 35300096      	mov	_tx_buffer1+150,#48
1401                     ; 414 	tx_buffer1[31+120]=0x30;
1403  0485 35300097      	mov	_tx_buffer1+151,#48
1404                     ; 415 	tx_buffer1[32+120]=0x30;
1406  0489 35300098      	mov	_tx_buffer1+152,#48
1407                     ; 416 	tx_buffer1[33+120]=0x30;
1409  048d 35300099      	mov	_tx_buffer1+153,#48
1410                     ; 417 	tx_buffer1[34+120]=0x30;
1412  0491 3530009a      	mov	_tx_buffer1+154,#48
1413                     ; 418 	tx_buffer1[35+120]=0x35;
1415  0495 3535009b      	mov	_tx_buffer1+155,#53
1416                     ; 419 	tx_buffer1[36+120]=0x35;
1418  0499 3535009c      	mov	_tx_buffer1+156,#53
1419                     ; 420 	tx_buffer1[37+120]=0x36;
1421  049d 3536009d      	mov	_tx_buffer1+157,#54
1422                     ; 421 	tx_buffer1[38+120]=0x33;
1424  04a1 3533009e      	mov	_tx_buffer1+158,#51
1425                     ; 422 	tx_buffer1[39+120]=0x31;
1427  04a5 3531009f      	mov	_tx_buffer1+159,#49
1428                     ; 423 	tx_buffer1[40+120]=0x44;
1430  04a9 354400a0      	mov	_tx_buffer1+160,#68
1431                     ; 424 	tx_buffer1[41+120]=0x34;
1433  04ad 353400a1      	mov	_tx_buffer1+161,#52
1434                     ; 425 	tx_buffer1[42+120]=0x43;
1436  04b1 354300a2      	mov	_tx_buffer1+162,#67
1437                     ; 426 	tx_buffer1[43+120]=0x46;
1439  04b5 354600a3      	mov	_tx_buffer1+163,#70
1440                     ; 427 	tx_buffer1[44+120]=0x46;
1442  04b9 354600a4      	mov	_tx_buffer1+164,#70
1443                     ; 428 	tx_buffer1[45+120]=0x30;
1445  04bd 353000a5      	mov	_tx_buffer1+165,#48
1446                     ; 429 	tx_buffer1[46+120]=0x45;
1448  04c1 354500a6      	mov	_tx_buffer1+166,#69
1449                     ; 430 	tx_buffer1[47+120]=0x41;
1451  04c5 354100a7      	mov	_tx_buffer1+167,#65
1452                     ; 431 	tx_buffer1[48+120]=0x36;
1454  04c9 353600a8      	mov	_tx_buffer1+168,#54
1455                     ; 432 	tx_buffer1[49+120]=0x36;
1457  04cd 353600a9      	mov	_tx_buffer1+169,#54
1458                     ; 433 	tx_buffer1[50+120]=0x34;
1460  04d1 353400aa      	mov	_tx_buffer1+170,#52
1461                     ; 434 	tx_buffer1[51+120]=0x30;
1463  04d5 353000ab      	mov	_tx_buffer1+171,#48
1464                     ; 435 	tx_buffer1[52+120]=0x31;	
1466  04d9 353100ac      	mov	_tx_buffer1+172,#49
1467                     ; 535 		rs485_cnt=0;
1469  04dd 3f0b          	clr	_rs485_cnt
1470                     ; 536 		bRS485ERR=0;
1472  04df 72110000      	bres	_bRS485ERR
1474  04e3 2020          	jra	L723
1475  04e5               L523:
1476                     ; 539 	else if(bRX485==2)
1478  04e5 b601          	ld	a,_bRX485
1479  04e7 a102          	cp	a,#2
1480  04e9 261a          	jrne	L723
1481                     ; 541 			GPIOD->DDR|=(1<<7);
1483  04eb 721e5011      	bset	20497,#7
1484                     ; 542 	GPIOD->CR1|=(1<<7);
1486  04ef 721e5012      	bset	20498,#7
1487                     ; 543 	GPIOD->CR2&=~(1<<7);	
1489  04f3 721f5013      	bres	20499,#7
1490                     ; 544 	GPIOD->ODR^=(1<<7);
1492  04f7 c6500f        	ld	a,20495
1493  04fa a880          	xor	a,	#128
1494  04fc c7500f        	ld	20495,a
1495                     ; 566 		rs485_cnt=0;
1497  04ff 3f0b          	clr	_rs485_cnt
1498                     ; 567 		bRS485ERR=0;
1500  0501 72110000      	bres	_bRS485ERR
1501  0505               L723:
1502                     ; 570 bRX485=0;	
1504  0505 3f01          	clr	_bRX485
1505                     ; 571 }
1508  0507 81            	ret
1531                     ; 574 void init_CAN(void) {
1532                     	switch	.text
1533  0508               _init_CAN:
1537                     ; 575 	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
1539  0508 72135420      	bres	21536,#1
1540                     ; 576 	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
1542  050c 72105420      	bset	21536,#0
1544  0510               L543:
1545                     ; 577 	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
1547  0510 c65421        	ld	a,21537
1548  0513 a501          	bcp	a,#1
1549  0515 27f9          	jreq	L543
1550                     ; 579 	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
1552  0517 72185420      	bset	21536,#4
1553                     ; 581 	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
1555  051b 35025427      	mov	21543,#2
1556                     ; 590 	CAN->Page.Filter01.F0R1= MY_MESS_STID>>3;			// 16 bits mode
1558  051f 35135428      	mov	21544,#19
1559                     ; 591 	CAN->Page.Filter01.F0R2= MY_MESS_STID<<5;
1561  0523 35c05429      	mov	21545,#192
1562                     ; 592 	CAN->Page.Filter01.F0R5= MY_MESS_STID_MASK>>3;
1564  0527 357f542c      	mov	21548,#127
1565                     ; 593 	CAN->Page.Filter01.F0R6= MY_MESS_STID_MASK<<5;
1567  052b 35e0542d      	mov	21549,#224
1568                     ; 596 	CAN->PSR= 6;									// set page 6
1570  052f 35065427      	mov	21543,#6
1571                     ; 601 	CAN->Page.Config.FMR1&=~3;								//mask mode
1573  0533 c65430        	ld	a,21552
1574  0536 a4fc          	and	a,#252
1575  0538 c75430        	ld	21552,a
1576                     ; 607 	CAN->Page.Config.FCR1= ((3<<1) & (CAN_FCR1_FSC00 | CAN_FCR1_FSC01));		//16 bit scale
1578  053b 35065432      	mov	21554,#6
1579                     ; 610 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
1581  053f 72105432      	bset	21554,#0
1582                     ; 613 	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
1584  0543 35065427      	mov	21543,#6
1585                     ; 615 	CAN->Page.Config.BTR1= 9;					// CAN_BTR1_BRP=9, 	tq= fcpu/(9+1)
1587  0547 3509542c      	mov	21548,#9
1588                     ; 616 	CAN->Page.Config.BTR2= (1<<7)|(6<<4) | 7; 		// BS2=8, BS1=7, 		
1590  054b 35e7542d      	mov	21549,#231
1591                     ; 618 	CAN->IER|=(1<<1);
1593  054f 72125425      	bset	21541,#1
1594                     ; 621 	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
1596  0553 72115420      	bres	21536,#0
1598  0557               L353:
1599                     ; 622 	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
1601  0557 c65421        	ld	a,21537
1602  055a a501          	bcp	a,#1
1603  055c 26f9          	jrne	L353
1604                     ; 623 }
1607  055e 81            	ret
1715                     ; 626 void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
1715                     ; 627 {
1716                     	switch	.text
1717  055f               _can_transmit:
1719  055f 89            	pushw	x
1720       00000000      OFST:	set	0
1723                     ; 629 if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>4))can_buff_wr_ptr=0;
1725  0560 b627          	ld	a,_can_buff_wr_ptr
1726  0562 a105          	cp	a,#5
1727  0564 2502          	jrult	L534
1730  0566 3f27          	clr	_can_buff_wr_ptr
1731  0568               L534:
1732                     ; 631 can_out_buff[can_buff_wr_ptr][0]=(char)(id_st>>6);
1734  0568 b627          	ld	a,_can_buff_wr_ptr
1735  056a 97            	ld	xl,a
1736  056b a610          	ld	a,#16
1737  056d 42            	mul	x,a
1738  056e 1601          	ldw	y,(OFST+1,sp)
1739  0570 a606          	ld	a,#6
1740  0572               L06:
1741  0572 9054          	srlw	y
1742  0574 4a            	dec	a
1743  0575 26fb          	jrne	L06
1744  0577 909f          	ld	a,yl
1745  0579 e728          	ld	(_can_out_buff,x),a
1746                     ; 632 can_out_buff[can_buff_wr_ptr][1]=(char)(id_st<<2);
1748  057b b627          	ld	a,_can_buff_wr_ptr
1749  057d 97            	ld	xl,a
1750  057e a610          	ld	a,#16
1751  0580 42            	mul	x,a
1752  0581 7b02          	ld	a,(OFST+2,sp)
1753  0583 48            	sll	a
1754  0584 48            	sll	a
1755  0585 e729          	ld	(_can_out_buff+1,x),a
1756                     ; 634 can_out_buff[can_buff_wr_ptr][2]=data0;
1758  0587 b627          	ld	a,_can_buff_wr_ptr
1759  0589 97            	ld	xl,a
1760  058a a610          	ld	a,#16
1761  058c 42            	mul	x,a
1762  058d 7b05          	ld	a,(OFST+5,sp)
1763  058f e72a          	ld	(_can_out_buff+2,x),a
1764                     ; 635 can_out_buff[can_buff_wr_ptr][3]=data1;
1766  0591 b627          	ld	a,_can_buff_wr_ptr
1767  0593 97            	ld	xl,a
1768  0594 a610          	ld	a,#16
1769  0596 42            	mul	x,a
1770  0597 7b06          	ld	a,(OFST+6,sp)
1771  0599 e72b          	ld	(_can_out_buff+3,x),a
1772                     ; 636 can_out_buff[can_buff_wr_ptr][4]=data2;
1774  059b b627          	ld	a,_can_buff_wr_ptr
1775  059d 97            	ld	xl,a
1776  059e a610          	ld	a,#16
1777  05a0 42            	mul	x,a
1778  05a1 7b07          	ld	a,(OFST+7,sp)
1779  05a3 e72c          	ld	(_can_out_buff+4,x),a
1780                     ; 637 can_out_buff[can_buff_wr_ptr][5]=data3;
1782  05a5 b627          	ld	a,_can_buff_wr_ptr
1783  05a7 97            	ld	xl,a
1784  05a8 a610          	ld	a,#16
1785  05aa 42            	mul	x,a
1786  05ab 7b08          	ld	a,(OFST+8,sp)
1787  05ad e72d          	ld	(_can_out_buff+5,x),a
1788                     ; 638 can_out_buff[can_buff_wr_ptr][6]=data4;
1790  05af b627          	ld	a,_can_buff_wr_ptr
1791  05b1 97            	ld	xl,a
1792  05b2 a610          	ld	a,#16
1793  05b4 42            	mul	x,a
1794  05b5 7b09          	ld	a,(OFST+9,sp)
1795  05b7 e72e          	ld	(_can_out_buff+6,x),a
1796                     ; 639 can_out_buff[can_buff_wr_ptr][7]=data5;
1798  05b9 b627          	ld	a,_can_buff_wr_ptr
1799  05bb 97            	ld	xl,a
1800  05bc a610          	ld	a,#16
1801  05be 42            	mul	x,a
1802  05bf 7b0a          	ld	a,(OFST+10,sp)
1803  05c1 e72f          	ld	(_can_out_buff+7,x),a
1804                     ; 640 can_out_buff[can_buff_wr_ptr][8]=data6;
1806  05c3 b627          	ld	a,_can_buff_wr_ptr
1807  05c5 97            	ld	xl,a
1808  05c6 a610          	ld	a,#16
1809  05c8 42            	mul	x,a
1810  05c9 7b0b          	ld	a,(OFST+11,sp)
1811  05cb e730          	ld	(_can_out_buff+8,x),a
1812                     ; 641 can_out_buff[can_buff_wr_ptr][9]=data7;
1814  05cd b627          	ld	a,_can_buff_wr_ptr
1815  05cf 97            	ld	xl,a
1816  05d0 a610          	ld	a,#16
1817  05d2 42            	mul	x,a
1818  05d3 7b0c          	ld	a,(OFST+12,sp)
1819  05d5 e731          	ld	(_can_out_buff+9,x),a
1820                     ; 643 can_buff_wr_ptr++;
1822  05d7 3c27          	inc	_can_buff_wr_ptr
1823                     ; 644 if(can_buff_wr_ptr>4)can_buff_wr_ptr=0;
1825  05d9 b627          	ld	a,_can_buff_wr_ptr
1826  05db a105          	cp	a,#5
1827  05dd 2502          	jrult	L734
1830  05df 3f27          	clr	_can_buff_wr_ptr
1831  05e1               L734:
1832                     ; 645 } 
1835  05e1 85            	popw	x
1836  05e2 81            	ret
1865                     ; 648 void can_tx_hndl(void)
1865                     ; 649 {
1866                     	switch	.text
1867  05e3               _can_tx_hndl:
1871                     ; 650 if(bTX_FREE)
1873  05e3 3d07          	tnz	_bTX_FREE
1874  05e5 2757          	jreq	L154
1875                     ; 652 	if(can_buff_rd_ptr!=can_buff_wr_ptr)
1877  05e7 b626          	ld	a,_can_buff_rd_ptr
1878  05e9 b127          	cp	a,_can_buff_wr_ptr
1879  05eb 275f          	jreq	L754
1880                     ; 654 		bTX_FREE=0;
1882  05ed 3f07          	clr	_bTX_FREE
1883                     ; 656 		CAN->PSR= 0;
1885  05ef 725f5427      	clr	21543
1886                     ; 657 		CAN->Page.TxMailbox.MDLCR=8;
1888  05f3 35085429      	mov	21545,#8
1889                     ; 658 		CAN->Page.TxMailbox.MIDR1=can_out_buff[can_buff_rd_ptr][0];
1891  05f7 b626          	ld	a,_can_buff_rd_ptr
1892  05f9 97            	ld	xl,a
1893  05fa a610          	ld	a,#16
1894  05fc 42            	mul	x,a
1895  05fd e628          	ld	a,(_can_out_buff,x)
1896  05ff c7542a        	ld	21546,a
1897                     ; 659 		CAN->Page.TxMailbox.MIDR2=can_out_buff[can_buff_rd_ptr][1];
1899  0602 b626          	ld	a,_can_buff_rd_ptr
1900  0604 97            	ld	xl,a
1901  0605 a610          	ld	a,#16
1902  0607 42            	mul	x,a
1903  0608 e629          	ld	a,(_can_out_buff+1,x)
1904  060a c7542b        	ld	21547,a
1905                     ; 661 		memcpy(&CAN->Page.TxMailbox.MDAR1, &can_out_buff[can_buff_rd_ptr][2],8);
1907  060d b626          	ld	a,_can_buff_rd_ptr
1908  060f 97            	ld	xl,a
1909  0610 a610          	ld	a,#16
1910  0612 42            	mul	x,a
1911  0613 01            	rrwa	x,a
1912  0614 ab2a          	add	a,#_can_out_buff+2
1913  0616 2401          	jrnc	L46
1914  0618 5c            	incw	x
1915  0619               L46:
1916  0619 5f            	clrw	x
1917  061a 97            	ld	xl,a
1918  061b bf00          	ldw	c_x,x
1919  061d ae0008        	ldw	x,#8
1920  0620               L66:
1921  0620 5a            	decw	x
1922  0621 92d600        	ld	a,([c_x],x)
1923  0624 d7542e        	ld	(21550,x),a
1924  0627 5d            	tnzw	x
1925  0628 26f6          	jrne	L66
1926                     ; 663 		can_buff_rd_ptr++;
1928  062a 3c26          	inc	_can_buff_rd_ptr
1929                     ; 664 		if(can_buff_rd_ptr>3)can_buff_rd_ptr=0;
1931  062c b626          	ld	a,_can_buff_rd_ptr
1932  062e a104          	cp	a,#4
1933  0630 2502          	jrult	L554
1936  0632 3f26          	clr	_can_buff_rd_ptr
1937  0634               L554:
1938                     ; 666 		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;
1940  0634 72105428      	bset	21544,#0
1941                     ; 667 		CAN->IER|=(1<<0);
1943  0638 72105425      	bset	21541,#0
1944  063c 200e          	jra	L754
1945  063e               L154:
1946                     ; 672 	tx_busy_cnt++;
1948  063e 3c25          	inc	_tx_busy_cnt
1949                     ; 673 	if(tx_busy_cnt>=100)
1951  0640 b625          	ld	a,_tx_busy_cnt
1952  0642 a164          	cp	a,#100
1953  0644 2506          	jrult	L754
1954                     ; 675 		tx_busy_cnt=0;
1956  0646 3f25          	clr	_tx_busy_cnt
1957                     ; 676 		bTX_FREE=1;
1959  0648 35010007      	mov	_bTX_FREE,#1
1960  064c               L754:
1961                     ; 679 }
1964  064c 81            	ret
1992                     ; 683 void can_in_an(void)
1992                     ; 684 {
1993                     	switch	.text
1994  064d               _can_in_an:
1998                     ; 695 if((mess[6]==19)&&(mess[7]==19)&&(mess[8]==GETTM))	
2000  064d b6ac          	ld	a,_mess+6
2001  064f a113          	cp	a,#19
2002  0651 2622          	jrne	L364
2004  0653 b6ad          	ld	a,_mess+7
2005  0655 a113          	cp	a,#19
2006  0657 261c          	jrne	L364
2008  0659 b6ae          	ld	a,_mess+8
2009  065b a1ed          	cp	a,#237
2010  065d 2616          	jrne	L364
2011                     ; 697 	GPIOD->DDR|=(1<<7);
2013  065f 721e5011      	bset	20497,#7
2014                     ; 698 	GPIOD->CR1|=(1<<7);
2016  0663 721e5012      	bset	20498,#7
2017                     ; 699 	GPIOD->CR2&=~(1<<7);	
2019  0667 721f5013      	bres	20499,#7
2020                     ; 700 	GPIOD->ODR^=(1<<7);
2022  066b c6500f        	ld	a,20495
2023  066e a880          	xor	a,	#128
2024  0670 c7500f        	ld	20495,a
2025                     ; 701 	can_error_cnt=0;
2027  0673 3f24          	clr	_can_error_cnt
2028  0675               L364:
2029                     ; 724 can_in_an_end:
2029                     ; 725 bCAN_RX=0;
2031  0675 3f08          	clr	_bCAN_RX
2032                     ; 726 }   
2035  0677 81            	ret
2058                     ; 730 void t4_init(void){
2059                     	switch	.text
2060  0678               _t4_init:
2064                     ; 731 	TIM4->PSCR = 7;
2066  0678 35075345      	mov	21317,#7
2067                     ; 732 	TIM4->ARR= 77;
2069  067c 354d5346      	mov	21318,#77
2070                     ; 733 	TIM4->IER|= TIM4_IER_UIE;					// enable break interrupt
2072  0680 72105341      	bset	21313,#0
2073                     ; 735 	TIM4->CR1=(TIM4_CR1_URS | TIM4_CR1_CEN | TIM4_CR1_ARPE);	
2075  0684 35855340      	mov	21312,#133
2076                     ; 737 }
2079  0688 81            	ret
2114                     ; 743 @far @interrupt void TIM4_UPD_Interrupt (void) 
2114                     ; 744 {
2116                     	switch	.text
2117  0689               f_TIM4_UPD_Interrupt:
2121                     ; 745 TIM4->SR1&=~TIM4_SR1_UIF;
2123  0689 72115342      	bres	21314,#0
2124                     ; 748 if(++t0_cnt0>=10)
2126  068d 3c00          	inc	_t0_cnt0
2127  068f b600          	ld	a,_t0_cnt0
2128  0691 a10a          	cp	a,#10
2129  0693 253e          	jrult	L125
2130                     ; 750 	t0_cnt0=0;
2132  0695 3f00          	clr	_t0_cnt0
2133                     ; 751 	b100Hz=1;
2135  0697 72100006      	bset	_b100Hz
2136                     ; 753 	if(++t0_cnt1>=10)
2138  069b 3c01          	inc	_t0_cnt1
2139  069d b601          	ld	a,_t0_cnt1
2140  069f a10a          	cp	a,#10
2141  06a1 2506          	jrult	L325
2142                     ; 755 		t0_cnt1=0;
2144  06a3 3f01          	clr	_t0_cnt1
2145                     ; 756 		b10Hz=1;
2147  06a5 72100005      	bset	_b10Hz
2148  06a9               L325:
2149                     ; 759 	if(++t0_cnt2>=20)
2151  06a9 3c02          	inc	_t0_cnt2
2152  06ab b602          	ld	a,_t0_cnt2
2153  06ad a114          	cp	a,#20
2154  06af 2506          	jrult	L525
2155                     ; 761 		t0_cnt2=0;
2157  06b1 3f02          	clr	_t0_cnt2
2158                     ; 762 		b5Hz=1;
2160  06b3 72100004      	bset	_b5Hz
2161  06b7               L525:
2162                     ; 766 	if(++t0_cnt4>=50)
2164  06b7 3c04          	inc	_t0_cnt4
2165  06b9 b604          	ld	a,_t0_cnt4
2166  06bb a132          	cp	a,#50
2167  06bd 2506          	jrult	L725
2168                     ; 768 		t0_cnt4=0;
2170  06bf 3f04          	clr	_t0_cnt4
2171                     ; 769 		b2Hz=1;
2173  06c1 72100003      	bset	_b2Hz
2174  06c5               L725:
2175                     ; 772 	if(++t0_cnt3>=100)
2177  06c5 3c03          	inc	_t0_cnt3
2178  06c7 b603          	ld	a,_t0_cnt3
2179  06c9 a164          	cp	a,#100
2180  06cb 2506          	jrult	L125
2181                     ; 774 		t0_cnt3=0;
2183  06cd 3f03          	clr	_t0_cnt3
2184                     ; 775 		b1Hz=1;
2186  06cf 72100002      	bset	_b1Hz
2187  06d3               L125:
2188                     ; 782 if(tx_stat_cnt)
2190  06d3 725d0159      	tnz	_tx_stat_cnt
2191  06d7 270c          	jreq	L335
2192                     ; 784 	tx_stat_cnt--;
2194  06d9 725a0159      	dec	_tx_stat_cnt
2195                     ; 785 	if(tx_stat_cnt==0)tx_stat=tsOFF;
2197  06dd 725d0159      	tnz	_tx_stat_cnt
2198  06e1 2602          	jrne	L335
2201  06e3 3f05          	clr	_tx_stat
2202  06e5               L335:
2203                     ; 800 }
2206  06e5 80            	iret
2231                     ; 803 @far @interrupt void CAN_RX_Interrupt (void) 
2231                     ; 804 {
2232                     	switch	.text
2233  06e6               f_CAN_RX_Interrupt:
2237                     ; 814 CAN->PSR= 7;									// page 7 - read messsage
2239  06e6 35075427      	mov	21543,#7
2240                     ; 816 memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
2242  06ea ae000e        	ldw	x,#14
2243  06ed               L001:
2244  06ed d65427        	ld	a,(21543,x)
2245  06f0 e7a5          	ld	(_mess-1,x),a
2246  06f2 5a            	decw	x
2247  06f3 26f8          	jrne	L001
2248                     ; 827 bCAN_RX=1;
2250  06f5 35010008      	mov	_bCAN_RX,#1
2251                     ; 828 CAN->RFR|=(1<<5);
2253  06f9 721a5424      	bset	21540,#5
2254                     ; 830 }
2257  06fd 80            	iret
2280                     ; 833 @far @interrupt void CAN_TX_Interrupt (void) 
2280                     ; 834 {
2281                     	switch	.text
2282  06fe               f_CAN_TX_Interrupt:
2286                     ; 835 	if((CAN->TSR)&(1<<0))
2288  06fe c65422        	ld	a,21538
2289  0701 a501          	bcp	a,#1
2290  0703 2708          	jreq	L755
2291                     ; 837 	bTX_FREE=1;	
2293  0705 35010007      	mov	_bTX_FREE,#1
2294                     ; 839 	CAN->TSR|=(1<<0);
2296  0709 72105422      	bset	21538,#0
2297  070d               L755:
2298                     ; 841 }
2301  070d 80            	iret
2339                     ; 845 @far @interrupt void UART1TxInterrupt (void) 
2339                     ; 846 {
2340                     	switch	.text
2341  070e               f_UART1TxInterrupt:
2343       00000001      OFST:	set	1
2344  070e 88            	push	a
2347                     ; 849 tx_status=UART1->SR;
2349  070f c65230        	ld	a,21040
2350  0712 6b01          	ld	(OFST+0,sp),a
2351                     ; 851 if (tx_status & (UART1_SR_TXE))
2353  0714 7b01          	ld	a,(OFST+0,sp)
2354  0716 a580          	bcp	a,#128
2355  0718 2723          	jreq	L775
2356                     ; 853 	if (tx_counter1)
2358  071a 3d91          	tnz	_tx_counter1
2359  071c 2713          	jreq	L106
2360                     ; 855 		--tx_counter1;
2362  071e 3a91          	dec	_tx_counter1
2363                     ; 856 		UART1->DR=tx_buffer1[tx_rd_index1];
2365  0720 5f            	clrw	x
2366  0721 b68f          	ld	a,_tx_rd_index1
2367  0723 2a01          	jrpl	L601
2368  0725 53            	cplw	x
2369  0726               L601:
2370  0726 97            	ld	xl,a
2371  0727 d60000        	ld	a,(_tx_buffer1,x)
2372  072a c75231        	ld	21041,a
2373                     ; 857 		if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
2375  072d 3c8f          	inc	_tx_rd_index1
2377  072f 200c          	jra	L775
2378  0731               L106:
2379                     ; 861 		tx_stat_cnt=3;
2381  0731 35030159      	mov	_tx_stat_cnt,#3
2382                     ; 862 			bOUT_FREE=1;
2384  0735 35010088      	mov	_bOUT_FREE,#1
2385                     ; 863 			UART1->CR2&= ~UART1_CR2_TIEN;
2387  0739 721f5235      	bres	21045,#7
2388  073d               L775:
2389                     ; 867 if (tx_status & (UART1_SR_TC))
2391  073d 7b01          	ld	a,(OFST+0,sp)
2392  073f a540          	bcp	a,#64
2393  0741 2708          	jreq	L706
2394                     ; 869 	GPIOB->ODR&=~(1<<7);
2396  0743 721f5005      	bres	20485,#7
2397                     ; 870 	UART1->SR&=~UART1_SR_TC;
2399  0747 721d5230      	bres	21040,#6
2400  074b               L706:
2401                     ; 872 }
2404  074b 84            	pop	a
2405  074c 80            	iret
2459                     ; 875 @far @interrupt void UART1RxInterrupt (void) 
2459                     ; 876 {
2460                     	switch	.text
2461  074d               f_UART1RxInterrupt:
2463       00000003      OFST:	set	3
2464  074d 5203          	subw	sp,#3
2467                     ; 879 rx_status=UART1->SR;
2469  074f c65230        	ld	a,21040
2470  0752 6b02          	ld	(OFST-1,sp),a
2471                     ; 880 rx_data=UART1->DR;
2473  0754 c65231        	ld	a,21041
2474  0757 6b03          	ld	(OFST+0,sp),a
2475                     ; 882 if (rx_status & (UART1_SR_RXNE))
2477  0759 7b02          	ld	a,(OFST-1,sp)
2478  075b a520          	bcp	a,#32
2479  075d 273a          	jreq	L736
2480                     ; 885 temp=rx_data;
2482                     ; 886 rx_buffer[rs485_rx_cnt]=rx_data;
2484  075f 7b03          	ld	a,(OFST+0,sp)
2485  0761 be02          	ldw	x,_rs485_rx_cnt
2486  0763 d7012c        	ld	(_rx_buffer,x),a
2487                     ; 887 rs485_rx_cnt++;
2489  0766 be02          	ldw	x,_rs485_rx_cnt
2490  0768 1c0001        	addw	x,#1
2491  076b bf02          	ldw	_rs485_rx_cnt,x
2492                     ; 904 	if((rx_data==0x0d)&&(rs485_rx_cnt==20))
2494  076d 7b03          	ld	a,(OFST+0,sp)
2495  076f a10d          	cp	a,#13
2496  0771 261d          	jrne	L146
2498  0773 be02          	ldw	x,_rs485_rx_cnt
2499  0775 a30014        	cpw	x,#20
2500  0778 2616          	jrne	L146
2501                     ; 906 		if(rx_buffer[8]==0x32){
2503  077a c60134        	ld	a,_rx_buffer+8
2504  077d a132          	cp	a,#50
2505  077f 2604          	jrne	L346
2506                     ; 907 		bRX485=1;
2508  0781 35010001      	mov	_bRX485,#1
2509  0785               L346:
2510                     ; 910 		if(rx_buffer[8]==0x33){
2512  0785 c60134        	ld	a,_rx_buffer+8
2513  0788 a133          	cp	a,#51
2514  078a 2604          	jrne	L146
2515                     ; 911 		bRX485=2;
2517  078c 35020001      	mov	_bRX485,#2
2518  0790               L146:
2519                     ; 914 	if(rx_data==0x0d)rs485_rx_cnt=0;	
2521  0790 7b03          	ld	a,(OFST+0,sp)
2522  0792 a10d          	cp	a,#13
2523  0794 2603          	jrne	L736
2526  0796 5f            	clrw	x
2527  0797 bf02          	ldw	_rs485_rx_cnt,x
2528  0799               L736:
2529                     ; 919 }
2532  0799 5b03          	addw	sp,#3
2533  079b 80            	iret
2571                     ; 928 main()
2571                     ; 929 {
2573                     	switch	.text
2574  079c               _main:
2578                     ; 930 CLK->ECKR|=1;
2580  079c 721050c1      	bset	20673,#0
2582  07a0               L366:
2583                     ; 931 while((CLK->ECKR & 2) == 0);
2585  07a0 c650c1        	ld	a,20673
2586  07a3 a502          	bcp	a,#2
2587  07a5 27f9          	jreq	L366
2588                     ; 932 CLK->SWCR|=2;
2590  07a7 721250c5      	bset	20677,#1
2591                     ; 933 CLK->SWR=0xB4;
2593  07ab 35b450c4      	mov	20676,#180
2594                     ; 936 t4_init();
2596  07af cd0678        	call	_t4_init
2598                     ; 938 		GPIOG->DDR|=(1<<0);
2600  07b2 72105020      	bset	20512,#0
2601                     ; 939 		GPIOG->CR1|=(1<<0);
2603  07b6 72105021      	bset	20513,#0
2604                     ; 940 		GPIOG->CR2&=~(1<<0);	
2606  07ba 72115022      	bres	20514,#0
2607                     ; 943 		GPIOG->DDR&=~(1<<1);
2609  07be 72135020      	bres	20512,#1
2610                     ; 944 		GPIOG->CR1|=(1<<1);
2612  07c2 72125021      	bset	20513,#1
2613                     ; 945 		GPIOG->CR2&=~(1<<1);
2615  07c6 72135022      	bres	20514,#1
2616                     ; 947 init_CAN();
2618  07ca cd0508        	call	_init_CAN
2620                     ; 955 uart1_init();
2622  07cd cd003c        	call	_uart1_init
2624                     ; 957 adress=19;
2626  07d0 35130001      	mov	_adress,#19
2627                     ; 959 enableInterrupts();
2630  07d4 9a            rim
2632  07d5               L766:
2633                     ; 963 	if(bRX485)
2635  07d5 3d01          	tnz	_bRX485
2636  07d7 2703          	jreq	L376
2637                     ; 965 		rx485_in_an();
2639  07d9 cd020c        	call	_rx485_in_an
2641  07dc               L376:
2642                     ; 968 	if(bCAN_RX)
2644  07dc 3d08          	tnz	_bCAN_RX
2645  07de 2705          	jreq	L576
2646                     ; 970 		bCAN_RX=0;
2648  07e0 3f08          	clr	_bCAN_RX
2649                     ; 971 		can_in_an();
2651  07e2 cd064d        	call	_can_in_an
2653  07e5               L576:
2654                     ; 977 	if(b100Hz)
2656                     	btst	_b100Hz
2657  07ea 2404          	jruge	L776
2658                     ; 979 		b100Hz=0;
2660  07ec 72110006      	bres	_b100Hz
2661  07f0               L776:
2662                     ; 982 	if(b10Hz)
2664                     	btst	_b10Hz
2665  07f5 2407          	jruge	L107
2666                     ; 984 		b10Hz=0;
2668  07f7 72110005      	bres	_b10Hz
2669                     ; 986 			can_tx_hndl();
2671  07fb cd05e3        	call	_can_tx_hndl
2673  07fe               L107:
2674                     ; 992 	if(b2Hz)
2676                     	btst	_b2Hz
2677  0803 2404          	jruge	L307
2678                     ; 994 		b2Hz=0;
2680  0805 72110003      	bres	_b2Hz
2681  0809               L307:
2682                     ; 999 	if(b1Hz)
2684                     	btst	_b1Hz
2685  080e 24c5          	jruge	L766
2686                     ; 1001 		b1Hz=0;
2688  0810 72110002      	bres	_b1Hz
2689                     ; 1008 		if(rs485_cnt>=10)
2691  0814 b60b          	ld	a,_rs485_cnt
2692  0816 a10a          	cp	a,#10
2693  0818 25bb          	jrult	L766
2694                     ; 1010 			rs485_cnt=10;
2696  081a 350a000b      	mov	_rs485_cnt,#10
2697                     ; 1011 			bRS485ERR=1;
2699  081e 72100000      	bset	_bRS485ERR
2700  0822 20b1          	jra	L766
3269                     	xdef	_main
3270                     	xdef	f_UART1RxInterrupt
3271                     	xdef	f_UART1TxInterrupt
3272                     	xdef	f_CAN_TX_Interrupt
3273                     	xdef	f_CAN_RX_Interrupt
3274                     	xdef	f_TIM4_UPD_Interrupt
3275                     	xdef	_t4_init
3276                     	xdef	_can_in_an
3277                     	xdef	_can_tx_hndl
3278                     	xdef	_can_transmit
3279                     	xdef	_init_CAN
3280                     	xdef	_rx485_in_an
3281                     	xdef	_str2int
3282                     	xdef	_uart1_out_adr
3283                     	xdef	_putchar1
3284                     	xdef	_uart1_init
3285                     	xdef	_gran
3286                     	xdef	_gran_char
3287                     	switch	.ubsct
3288  0000               _transmit_cnt_number:
3289  0000 00            	ds.b	1
3290                     	xdef	_transmit_cnt_number
3291                     .bit:	section	.data,bit
3292  0000               _bRS485ERR:
3293  0000 00            	ds.b	1
3294                     	xdef	_bRS485ERR
3295                     	xdef	_rs485_cnt
3296                     	switch	.ubsct
3297  0001               _bRX485:
3298  0001 00            	ds.b	1
3299                     	xdef	_bRX485
3300  0002               _rs485_rx_cnt:
3301  0002 0000          	ds.b	2
3302                     	xdef	_rs485_rx_cnt
3303  0004               _plazma_int:
3304  0004 000000000000  	ds.b	6
3305                     	xdef	_plazma_int
3306  000a               _link_cnt:
3307  000a 00            	ds.b	1
3308                     	xdef	_link_cnt
3309  000b               _link:
3310  000b 00            	ds.b	1
3311                     	xdef	_link
3312                     	switch	.bss
3313  0000               _adress_error:
3314  0000 00            	ds.b	1
3315                     	xdef	_adress_error
3316  0001               _adress:
3317  0001 00            	ds.b	1
3318                     	xdef	_adress
3319  0002               _adr:
3320  0002 000000        	ds.b	3
3321                     	xdef	_adr
3322                     	xdef	_adr_drv_stat
3323                     	xdef	_led_ind
3324                     	switch	.ubsct
3325  000c               _led_ind_cnt:
3326  000c 00            	ds.b	1
3327                     	xdef	_led_ind_cnt
3328  000d               _adc_plazma:
3329  000d 000000000000  	ds.b	10
3330                     	xdef	_adc_plazma
3331  0017               _adc_plazma_short:
3332  0017 0000          	ds.b	2
3333                     	xdef	_adc_plazma_short
3334  0019               _adc_cnt:
3335  0019 00            	ds.b	1
3336                     	xdef	_adc_cnt
3337  001a               _adc_ch:
3338  001a 00            	ds.b	1
3339                     	xdef	_adc_ch
3340                     	switch	.bss
3341  0005               _adc_buff_:
3342  0005 000000000000  	ds.b	20
3343                     	xdef	_adc_buff_
3344  0019               _adc_buff:
3345  0019 000000000000  	ds.b	320
3346                     	xdef	_adc_buff
3347                     	switch	.ubsct
3348  001b               _T:
3349  001b 00            	ds.b	1
3350                     	xdef	_T
3351  001c               _Udb:
3352  001c 0000          	ds.b	2
3353                     	xdef	_Udb
3354  001e               _Ui:
3355  001e 0000          	ds.b	2
3356                     	xdef	_Ui
3357  0020               _Un:
3358  0020 0000          	ds.b	2
3359                     	xdef	_Un
3360  0022               _I:
3361  0022 0000          	ds.b	2
3362                     	xdef	_I
3363  0024               _can_error_cnt:
3364  0024 00            	ds.b	1
3365                     	xdef	_can_error_cnt
3366                     	xdef	_bCAN_RX
3367  0025               _tx_busy_cnt:
3368  0025 00            	ds.b	1
3369                     	xdef	_tx_busy_cnt
3370                     	xdef	_bTX_FREE
3371  0026               _can_buff_rd_ptr:
3372  0026 00            	ds.b	1
3373                     	xdef	_can_buff_rd_ptr
3374  0027               _can_buff_wr_ptr:
3375  0027 00            	ds.b	1
3376                     	xdef	_can_buff_wr_ptr
3377  0028               _can_out_buff:
3378  0028 000000000000  	ds.b	96
3379                     	xdef	_can_out_buff
3380  0088               _bOUT_FREE:
3381  0088 00            	ds.b	1
3382                     	xdef	_bOUT_FREE
3383                     	xdef	_tx_wd_cnt
3384                     	switch	.bss
3385  0159               _tx_stat_cnt:
3386  0159 00            	ds.b	1
3387                     	xdef	_tx_stat_cnt
3388                     	switch	.ubsct
3389  0089               _rx_rd_index1:
3390  0089 0000          	ds.b	2
3391                     	xdef	_rx_rd_index1
3392  008b               _rx_wr_index1:
3393  008b 0000          	ds.b	2
3394                     	xdef	_rx_wr_index1
3395  008d               _rx_counter1:
3396  008d 0000          	ds.b	2
3397                     	xdef	_rx_counter1
3398                     	xdef	_rx_buffer
3399  008f               _tx_rd_index1:
3400  008f 00            	ds.b	1
3401                     	xdef	_tx_rd_index1
3402  0090               _tx_wr_index1:
3403  0090 00            	ds.b	1
3404                     	xdef	_tx_wr_index1
3405  0091               _tx_counter1:
3406  0091 00            	ds.b	1
3407                     	xdef	_tx_counter1
3408                     	xdef	_tx_buffer1
3409  0092               _rs485_out_buff:
3410  0092 000000000000  	ds.b	20
3411                     	xdef	_rs485_out_buff
3412  00a6               _mess:
3413  00a6 000000000000  	ds.b	14
3414                     	xdef	_mess
3415                     	switch	.bit
3416  0001               _bBAT_REQ:
3417  0001 00            	ds.b	1
3418                     	xdef	_bBAT_REQ
3419  0002               _b1Hz:
3420  0002 00            	ds.b	1
3421                     	xdef	_b1Hz
3422  0003               _b2Hz:
3423  0003 00            	ds.b	1
3424                     	xdef	_b2Hz
3425  0004               _b5Hz:
3426  0004 00            	ds.b	1
3427                     	xdef	_b5Hz
3428  0005               _b10Hz:
3429  0005 00            	ds.b	1
3430                     	xdef	_b10Hz
3431  0006               _b100Hz:
3432  0006 00            	ds.b	1
3433                     	xdef	_b100Hz
3434                     	xdef	_t0_cnt4
3435                     	xdef	_t0_cnt3
3436                     	xdef	_t0_cnt2
3437                     	xdef	_t0_cnt1
3438                     	xdef	_t0_cnt0
3439                     	xref	_pow
3440                     	xref	_isalnum
3441                     	xdef	_tx_stat
3442                     	switch	.const
3443  000a               L113:
3444  000a 41800000      	dc.w	16768,0
3445                     	xref.b	c_lreg
3446                     	xref.b	c_x
3466                     	xref	c_imul
3467                     	xref	c_ftoi
3468                     	xref	c_itof
3469                     	xref	c_xymvx
3470                     	end
