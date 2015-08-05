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
  36  0006               _bTX_FREE:
  37  0006 01            	dc.b	1
  38  0007               _bCAN_RX:
  39  0007 00            	dc.b	0
  40  0008               _led_ind:
  41  0008 05            	dc.b	5
  42  0009               _adr_drv_stat:
  43  0009 00            	dc.b	0
  44  000a               _rs485_cnt:
  45  000a 00            	dc.b	0
 104                     ; 111 void gran_char(signed char *adr, signed char min, signed char max)
 104                     ; 112 {
 106                     	switch	.text
 107  0000               _gran_char:
 109  0000 89            	pushw	x
 110       00000000      OFST:	set	0
 113                     ; 113 if (*adr<min) *adr=min;
 115  0001 9c            	rvf
 116  0002 f6            	ld	a,(x)
 117  0003 1105          	cp	a,(OFST+5,sp)
 118  0005 2e05          	jrsge	L73
 121  0007 7b05          	ld	a,(OFST+5,sp)
 122  0009 1e01          	ldw	x,(OFST+1,sp)
 123  000b f7            	ld	(x),a
 124  000c               L73:
 125                     ; 114 if (*adr>max)  *adr=max; 
 127  000c 9c            	rvf
 128  000d 1e01          	ldw	x,(OFST+1,sp)
 129  000f f6            	ld	a,(x)
 130  0010 1106          	cp	a,(OFST+6,sp)
 131  0012 2d05          	jrsle	L14
 134  0014 7b06          	ld	a,(OFST+6,sp)
 135  0016 1e01          	ldw	x,(OFST+1,sp)
 136  0018 f7            	ld	(x),a
 137  0019               L14:
 138                     ; 115 }
 141  0019 85            	popw	x
 142  001a 81            	ret
 195                     ; 118 void gran(signed short *adr, signed short min, signed short max)
 195                     ; 119 {
 196                     	switch	.text
 197  001b               _gran:
 199  001b 89            	pushw	x
 200       00000000      OFST:	set	0
 203                     ; 120 if (*adr<min) *adr=min;
 205  001c 9c            	rvf
 206  001d 9093          	ldw	y,x
 207  001f 51            	exgw	x,y
 208  0020 fe            	ldw	x,(x)
 209  0021 1305          	cpw	x,(OFST+5,sp)
 210  0023 51            	exgw	x,y
 211  0024 2e03          	jrsge	L17
 214  0026 1605          	ldw	y,(OFST+5,sp)
 215  0028 ff            	ldw	(x),y
 216  0029               L17:
 217                     ; 121 if (*adr>max)  *adr=max; 
 219  0029 9c            	rvf
 220  002a 1e01          	ldw	x,(OFST+1,sp)
 221  002c 9093          	ldw	y,x
 222  002e 51            	exgw	x,y
 223  002f fe            	ldw	x,(x)
 224  0030 1307          	cpw	x,(OFST+7,sp)
 225  0032 51            	exgw	x,y
 226  0033 2d05          	jrsle	L37
 229  0035 1e01          	ldw	x,(OFST+1,sp)
 230  0037 1607          	ldw	y,(OFST+7,sp)
 231  0039 ff            	ldw	(x),y
 232  003a               L37:
 233                     ; 122 }
 236  003a 85            	popw	x
 237  003b 81            	ret
 260                     ; 128 void uart1_init (void)
 260                     ; 129 {
 261                     	switch	.text
 262  003c               _uart1_init:
 266                     ; 131 GPIOA->DDR&=~(1<<4);
 268  003c 72195002      	bres	20482,#4
 269                     ; 132 GPIOA->CR1|=(1<<4);
 271  0040 72185003      	bset	20483,#4
 272                     ; 133 GPIOA->CR2&=~(1<<4);
 274  0044 72195004      	bres	20484,#4
 275                     ; 136 GPIOA->DDR|=(1<<5);
 277  0048 721a5002      	bset	20482,#5
 278                     ; 137 GPIOA->CR1|=(1<<5);
 280  004c 721a5003      	bset	20483,#5
 281                     ; 138 GPIOA->CR2&=~(1<<5);	
 283  0050 721b5004      	bres	20484,#5
 284                     ; 141 GPIOB->DDR|=(1<<6);
 286  0054 721c5007      	bset	20487,#6
 287                     ; 142 GPIOB->CR1|=(1<<6);
 289  0058 721c5008      	bset	20488,#6
 290                     ; 143 GPIOB->CR2&=~(1<<6);
 292  005c 721d5009      	bres	20489,#6
 293                     ; 144 GPIOB->ODR|=(1<<6);		//—разу в 1
 295  0060 721c5005      	bset	20485,#6
 296                     ; 147 GPIOB->DDR|=(1<<7);
 298  0064 721e5007      	bset	20487,#7
 299                     ; 148 GPIOB->CR1|=(1<<7);
 301  0068 721e5008      	bset	20488,#7
 302                     ; 149 GPIOB->CR2&=~(1<<7);
 304  006c 721f5009      	bres	20489,#7
 305                     ; 151 UART1->CR1&=~UART1_CR1_M;					
 307  0070 72195234      	bres	21044,#4
 308                     ; 152 UART1->CR3|= (0<<4) & UART1_CR3_STOP;  	
 310  0074 c65236        	ld	a,21046
 311                     ; 153 UART1->BRR2= 0x09;
 313  0077 35095233      	mov	21043,#9
 314                     ; 154 UART1->BRR1= 0x20;
 316  007b 35205232      	mov	21042,#32
 317                     ; 155 UART1->CR2|= UART1_CR2_TEN | UART1_CR2_REN | UART1_CR2_RIEN/*| UART2_CR2_TIEN*/ ;	
 319  007f c65235        	ld	a,21045
 320  0082 aa2c          	or	a,#44
 321  0084 c75235        	ld	21045,a
 322                     ; 156 }
 325  0087 81            	ret
 362                     ; 159 void putchar1(char c)
 362                     ; 160 {
 363                     	switch	.text
 364  0088               _putchar1:
 366  0088 88            	push	a
 367       00000000      OFST:	set	0
 370  0089               L521:
 371                     ; 161 while (tx_counter1 == TX_BUFFER_SIZE1);
 373  0089 be93          	ldw	x,_tx_counter1
 374  008b a3012c        	cpw	x,#300
 375  008e 27f9          	jreq	L521
 376                     ; 163 if (tx_counter1 || ((UART1->SR & UART1_SR_TXE)==0))
 378  0090 be93          	ldw	x,_tx_counter1
 379  0092 2607          	jrne	L331
 381  0094 c65230        	ld	a,21040
 382  0097 a580          	bcp	a,#128
 383  0099 2627          	jrne	L131
 384  009b               L331:
 385                     ; 165    tx_buffer1[tx_wr_index1]=c;
 387  009b 7b01          	ld	a,(OFST+1,sp)
 388  009d be91          	ldw	x,_tx_wr_index1
 389  009f d70000        	ld	(_tx_buffer1,x),a
 390                     ; 166    if (++tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
 392  00a2 be91          	ldw	x,_tx_wr_index1
 393  00a4 1c0001        	addw	x,#1
 394  00a7 bf91          	ldw	_tx_wr_index1,x
 395  00a9 a3012c        	cpw	x,#300
 396  00ac 2603          	jrne	L531
 399  00ae 5f            	clrw	x
 400  00af bf91          	ldw	_tx_wr_index1,x
 401  00b1               L531:
 402                     ; 167    ++tx_counter1;
 404  00b1 be93          	ldw	x,_tx_counter1
 405  00b3 1c0001        	addw	x,#1
 406  00b6 bf93          	ldw	_tx_counter1,x
 408  00b8               L731:
 409                     ; 171 UART1->CR2|= UART1_CR2_TIEN | UART1_CR2_TCIEN;
 411  00b8 c65235        	ld	a,21045
 412  00bb aac0          	or	a,#192
 413  00bd c75235        	ld	21045,a
 414                     ; 172 }
 417  00c0 84            	pop	a
 418  00c1 81            	ret
 419  00c2               L131:
 420                     ; 169 else UART1->DR=c;
 422  00c2 7b01          	ld	a,(OFST+1,sp)
 423  00c4 c75231        	ld	21041,a
 424  00c7 20ef          	jra	L731
 480                     ; 176 void uart1_out_adr(char *ptr, short len)
 480                     ; 177 {
 481                     	switch	.text
 482  00c9               _uart1_out_adr:
 484  00c9 89            	pushw	x
 485  00ca 89            	pushw	x
 486       00000002      OFST:	set	2
 489                     ; 183 GPIOB->ODR|=(1<<7);
 491  00cb 721e5005      	bset	20485,#7
 492                     ; 194 tx_stat=tsON;
 494  00cf 35010005      	mov	_tx_stat,#1
 495                     ; 196 for (i=0;i<len;i++)
 497  00d3 5f            	clrw	x
 498  00d4 1f01          	ldw	(OFST-1,sp),x
 500  00d6 200f          	jra	L371
 501  00d8               L761:
 502                     ; 198 	putchar1(ptr[i]);
 504  00d8 1e01          	ldw	x,(OFST-1,sp)
 505  00da 72fb03        	addw	x,(OFST+1,sp)
 506  00dd f6            	ld	a,(x)
 507  00de ada8          	call	_putchar1
 509                     ; 196 for (i=0;i<len;i++)
 511  00e0 1e01          	ldw	x,(OFST-1,sp)
 512  00e2 1c0001        	addw	x,#1
 513  00e5 1f01          	ldw	(OFST-1,sp),x
 514  00e7               L371:
 517  00e7 9c            	rvf
 518  00e8 1e01          	ldw	x,(OFST-1,sp)
 519  00ea 1307          	cpw	x,(OFST+5,sp)
 520  00ec 2fea          	jrslt	L761
 521                     ; 201 rs485_cnt++;
 523  00ee 3c0a          	inc	_rs485_cnt
 524                     ; 202 }
 527  00f0 5b04          	addw	sp,#4
 528  00f2 81            	ret
 531                     .const:	section	.text
 532  0000               L771_temp:
 533  0000 00            	dc.b	0
 534  0001 00            	dc.b	0
 535  0002 00            	dc.b	0
 536  0003 00            	dc.b	0
 537  0004 00            	dc.b	0
 538  0005 00            	dc.b	0
 539  0006 00            	dc.b	0
 540  0007 00            	dc.b	0
 541  0008 00            	dc.b	0
 542  0009 00            	ds.b	1
 623                     ; 205 int str2int(char *ptr, char len)
 623                     ; 206 {
 624                     	switch	.text
 625  00f3               _str2int:
 627  00f3 89            	pushw	x
 628  00f4 5210          	subw	sp,#16
 629       00000010      OFST:	set	16
 632                     ; 210 @near char temp[10]={0,0,0,0,0,0,0,0,0};
 634  00f6 96            	ldw	x,sp
 635  00f7 1c0005        	addw	x,#OFST-11
 636  00fa 90ae0000      	ldw	y,#L771_temp
 637  00fe a60a          	ld	a,#10
 638  0100 cd0000        	call	c_xymvx
 640                     ; 211 @near int temp_out=0;
 642  0103 5f            	clrw	x
 643  0104 1f03          	ldw	(OFST-13,sp),x
 644                     ; 215 for (i=0;i<len;i++)
 646  0106 0f10          	clr	(OFST+0,sp)
 648  0108 ac990199      	jpf	L742
 649  010c               L342:
 650                     ; 217 	tt=*(ptr+i);
 652  010c 7b11          	ld	a,(OFST+1,sp)
 653  010e 97            	ld	xl,a
 654  010f 7b12          	ld	a,(OFST+2,sp)
 655  0111 1b10          	add	a,(OFST+0,sp)
 656  0113 2401          	jrnc	L02
 657  0115 5c            	incw	x
 658  0116               L02:
 659  0116 02            	rlwa	x,a
 660  0117 f6            	ld	a,(x)
 661  0118 6b0f          	ld	(OFST-1,sp),a
 662                     ; 219 	if(isalnum(tt/**(ptr+i)*/))
 664  011a 7b0f          	ld	a,(OFST-1,sp)
 665  011c cd0000        	call	_isalnum
 667  011f 4d            	tnz	a
 668  0120 2775          	jreq	L352
 669                     ; 221 		if(isdigit(tt/**(ptr+i)*/))
 671  0122 7b0f          	ld	a,(OFST-1,sp)
 672  0124 a130          	cp	a,#48
 673  0126 2517          	jrult	L552
 675  0128 7b0f          	ld	a,(OFST-1,sp)
 676  012a a13a          	cp	a,#58
 677  012c 2411          	jruge	L552
 678                     ; 223 		temp[i]=tt/**(ptr+i)*/-'0';
 680  012e 96            	ldw	x,sp
 681  012f 1c0005        	addw	x,#OFST-11
 682  0132 9f            	ld	a,xl
 683  0133 5e            	swapw	x
 684  0134 1b10          	add	a,(OFST+0,sp)
 685  0136 2401          	jrnc	L22
 686  0138 5c            	incw	x
 687  0139               L22:
 688  0139 02            	rlwa	x,a
 689  013a 7b0f          	ld	a,(OFST-1,sp)
 690  013c a030          	sub	a,#48
 691  013e f7            	ld	(x),a
 692  013f               L552:
 693                     ; 225 		if(islower(tt/**(ptr+i)*/))
 695  013f 7b0f          	ld	a,(OFST-1,sp)
 696  0141 a161          	cp	a,#97
 697  0143 2517          	jrult	L752
 699  0145 7b0f          	ld	a,(OFST-1,sp)
 700  0147 a17b          	cp	a,#123
 701  0149 2411          	jruge	L752
 702                     ; 227 		temp[i]=tt/**(ptr+i)*/-'a'+10;
 704  014b 96            	ldw	x,sp
 705  014c 1c0005        	addw	x,#OFST-11
 706  014f 9f            	ld	a,xl
 707  0150 5e            	swapw	x
 708  0151 1b10          	add	a,(OFST+0,sp)
 709  0153 2401          	jrnc	L42
 710  0155 5c            	incw	x
 711  0156               L42:
 712  0156 02            	rlwa	x,a
 713  0157 7b0f          	ld	a,(OFST-1,sp)
 714  0159 a057          	sub	a,#87
 715  015b f7            	ld	(x),a
 716  015c               L752:
 717                     ; 229 		if(isupper(tt/**(ptr+i)*/))
 719  015c 7b0f          	ld	a,(OFST-1,sp)
 720  015e a141          	cp	a,#65
 721  0160 2535          	jrult	L352
 723  0162 7b0f          	ld	a,(OFST-1,sp)
 724  0164 a15b          	cp	a,#91
 725  0166 242f          	jruge	L352
 726                     ; 231 		temp[i]=tt;
 728  0168 96            	ldw	x,sp
 729  0169 1c0005        	addw	x,#OFST-11
 730  016c 9f            	ld	a,xl
 731  016d 5e            	swapw	x
 732  016e 1b10          	add	a,(OFST+0,sp)
 733  0170 2401          	jrnc	L62
 734  0172 5c            	incw	x
 735  0173               L62:
 736  0173 02            	rlwa	x,a
 737  0174 7b0f          	ld	a,(OFST-1,sp)
 738  0176 f7            	ld	(x),a
 739                     ; 232 		temp[i]-=/**(ptr+i)*/'A';
 741  0177 96            	ldw	x,sp
 742  0178 1c0005        	addw	x,#OFST-11
 743  017b 9f            	ld	a,xl
 744  017c 5e            	swapw	x
 745  017d 1b10          	add	a,(OFST+0,sp)
 746  017f 2401          	jrnc	L03
 747  0181 5c            	incw	x
 748  0182               L03:
 749  0182 02            	rlwa	x,a
 750  0183 f6            	ld	a,(x)
 751  0184 a041          	sub	a,#65
 752  0186 f7            	ld	(x),a
 753                     ; 233 		temp[i]+=10;
 755  0187 96            	ldw	x,sp
 756  0188 1c0005        	addw	x,#OFST-11
 757  018b 9f            	ld	a,xl
 758  018c 5e            	swapw	x
 759  018d 1b10          	add	a,(OFST+0,sp)
 760  018f 2401          	jrnc	L23
 761  0191 5c            	incw	x
 762  0192               L23:
 763  0192 02            	rlwa	x,a
 764  0193 f6            	ld	a,(x)
 765  0194 ab0a          	add	a,#10
 766  0196 f7            	ld	(x),a
 767  0197               L352:
 768                     ; 215 for (i=0;i<len;i++)
 770  0197 0c10          	inc	(OFST+0,sp)
 771  0199               L742:
 774  0199 7b10          	ld	a,(OFST+0,sp)
 775  019b 1115          	cp	a,(OFST+5,sp)
 776  019d 2403          	jruge	L63
 777  019f cc010c        	jp	L342
 778  01a2               L63:
 779                     ; 239 for(i=len;i;i--)
 781  01a2 7b15          	ld	a,(OFST+5,sp)
 782  01a4 6b10          	ld	(OFST+0,sp),a
 784  01a6 2045          	jra	L762
 785  01a8               L362:
 786                     ; 241 	temp_out+= ((int)pow(16,len-i))*temp[i-1]; 
 788  01a8 7b15          	ld	a,(OFST+5,sp)
 789  01aa 5f            	clrw	x
 790  01ab 1010          	sub	a,(OFST+0,sp)
 791  01ad 2401          	jrnc	L43
 792  01af 5a            	decw	x
 793  01b0               L43:
 794  01b0 02            	rlwa	x,a
 795  01b1 cd0000        	call	c_itof
 797  01b4 be02          	ldw	x,c_lreg+2
 798  01b6 89            	pushw	x
 799  01b7 be00          	ldw	x,c_lreg
 800  01b9 89            	pushw	x
 801  01ba ce000c        	ldw	x,L772+2
 802  01bd 89            	pushw	x
 803  01be ce000a        	ldw	x,L772
 804  01c1 89            	pushw	x
 805  01c2 cd0000        	call	_pow
 807  01c5 5b08          	addw	sp,#8
 808  01c7 cd0000        	call	c_ftoi
 810  01ca 9096          	ldw	y,sp
 811  01cc 72a90005      	addw	y,#OFST-11
 812  01d0 1701          	ldw	(OFST-15,sp),y
 813  01d2 7b10          	ld	a,(OFST+0,sp)
 814  01d4 905f          	clrw	y
 815  01d6 9097          	ld	yl,a
 816  01d8 905a          	decw	y
 817  01da 72f901        	addw	y,(OFST-15,sp)
 818  01dd 90f6          	ld	a,(y)
 819  01df 905f          	clrw	y
 820  01e1 9097          	ld	yl,a
 821  01e3 cd0000        	call	c_imul
 823  01e6 72fb03        	addw	x,(OFST-13,sp)
 824  01e9 1f03          	ldw	(OFST-13,sp),x
 825                     ; 239 for(i=len;i;i--)
 827  01eb 0a10          	dec	(OFST+0,sp)
 828  01ed               L762:
 831  01ed 0d10          	tnz	(OFST+0,sp)
 832  01ef 26b7          	jrne	L362
 833                     ; 246 return temp_out;
 835  01f1 1e03          	ldw	x,(OFST-13,sp)
 838  01f3 5b12          	addw	sp,#18
 839  01f5 81            	ret
 865                     ; 250 void rx485_in_an(void)
 865                     ; 251 {
 866                     	switch	.text
 867  01f6               _rx485_in_an:
 871                     ; 254 	if(bRX485==1)
 873  01f6 b601          	ld	a,_bRX485
 874  01f8 a101          	cp	a,#1
 875  01fa 2703          	jreq	L24
 876  01fc cc02f6        	jp	L313
 877  01ff               L24:
 878                     ; 256 	GPIOD->DDR|=(1<<7);
 880  01ff 721e5011      	bset	20497,#7
 881                     ; 257 	GPIOD->CR1|=(1<<7);
 883  0203 721e5012      	bset	20498,#7
 884                     ; 258 	GPIOD->CR2&=~(1<<7);	
 886  0207 721f5013      	bres	20499,#7
 887                     ; 259 	GPIOD->ODR^=(1<<7);
 889  020b c6500f        	ld	a,20495
 890  020e a880          	xor	a,	#128
 891  0210 c7500f        	ld	20495,a
 892                     ; 261 	rs485_out_buff[0]=0x7e;
 894  0213 357e0000      	mov	_rs485_out_buff,#126
 895                     ; 262 	rs485_out_buff[1]=0x31;
 897  0217 35310001      	mov	_rs485_out_buff+1,#49
 898                     ; 263 	rs485_out_buff[2]=0x31;
 900  021b 35310002      	mov	_rs485_out_buff+2,#49
 901                     ; 264 	rs485_out_buff[3]=0x30;
 903  021f 35300003      	mov	_rs485_out_buff+3,#48
 904                     ; 265 	rs485_out_buff[4]=0x31;
 906  0223 35310004      	mov	_rs485_out_buff+4,#49
 907                     ; 266 	rs485_out_buff[5]=0x44;
 909  0227 35440005      	mov	_rs485_out_buff+5,#68
 910                     ; 267 	rs485_out_buff[6]=0x30;
 912  022b 35300006      	mov	_rs485_out_buff+6,#48
 913                     ; 268 	rs485_out_buff[7]=0x30;
 915  022f 35300007      	mov	_rs485_out_buff+7,#48
 916                     ; 269 	rs485_out_buff[8]=0x30;
 918  0233 35300008      	mov	_rs485_out_buff+8,#48
 919                     ; 270 	rs485_out_buff[9]=0x36;
 921  0237 35360009      	mov	_rs485_out_buff+9,#54
 922                     ; 271 	rs485_out_buff[10]=0x31;
 924  023b 3531000a      	mov	_rs485_out_buff+10,#49
 925                     ; 272 	rs485_out_buff[11]=0x31;
 927  023f 3531000b      	mov	_rs485_out_buff+11,#49
 928                     ; 273 	rs485_out_buff[12]=0x38;
 930  0243 3538000c      	mov	_rs485_out_buff+12,#56
 931                     ; 275 	rs485_out_buff[13]=0x30;
 933  0247 3530000d      	mov	_rs485_out_buff+13,#48
 934                     ; 276 	rs485_out_buff[14]=0x44;
 936  024b 3544000e      	mov	_rs485_out_buff+14,#68
 937                     ; 277 	rs485_out_buff[15]=0x37;
 939  024f 3537000f      	mov	_rs485_out_buff+15,#55
 940                     ; 278 	rs485_out_buff[16]=0x41;
 942  0253 35410010      	mov	_rs485_out_buff+16,#65
 943                     ; 279 	rs485_out_buff[17]=0x30;
 945  0257 35300011      	mov	_rs485_out_buff+17,#48
 946                     ; 280 	rs485_out_buff[18]=0x44;
 948  025b 35440012      	mov	_rs485_out_buff+18,#68
 949                     ; 281 	rs485_out_buff[19]=0x33;
 951  025f 35330013      	mov	_rs485_out_buff+19,#51
 952                     ; 282 	rs485_out_buff[20]=0x43;
 954  0263 35430014      	mov	_rs485_out_buff+20,#67
 955                     ; 283 	rs485_out_buff[21]=0x31;
 957  0267 35310015      	mov	_rs485_out_buff+21,#49
 958                     ; 284 	rs485_out_buff[22]=0x38;
 960  026b 35380016      	mov	_rs485_out_buff+22,#56
 961                     ; 285 	rs485_out_buff[23]=0x31;
 963  026f 35310017      	mov	_rs485_out_buff+23,#49
 964                     ; 286 	rs485_out_buff[24]=0x38;
 966  0273 35380018      	mov	_rs485_out_buff+24,#56
 967                     ; 287 	rs485_out_buff[25]=0x31;
 969  0277 35310019      	mov	_rs485_out_buff+25,#49
 970                     ; 288 	rs485_out_buff[26]=0x34;
 972  027b 3534001a      	mov	_rs485_out_buff+26,#52
 973                     ; 289 	rs485_out_buff[27]=0x31;
 975  027f 3531001b      	mov	_rs485_out_buff+27,#49
 976                     ; 290 	rs485_out_buff[28]=0x32;
 978  0283 3532001c      	mov	_rs485_out_buff+28,#50
 979                     ; 291 	rs485_out_buff[29]=0x30;
 981  0287 3530001d      	mov	_rs485_out_buff+29,#48
 982                     ; 292 	rs485_out_buff[30]=0x30;
 984  028b 3530001e      	mov	_rs485_out_buff+30,#48
 985                     ; 293 	rs485_out_buff[31]=0x30;
 987  028f 3530001f      	mov	_rs485_out_buff+31,#48
 988                     ; 294 	rs485_out_buff[32]=0x30;
 990  0293 35300020      	mov	_rs485_out_buff+32,#48
 991                     ; 295 	rs485_out_buff[33]=0x30;
 993  0297 35300021      	mov	_rs485_out_buff+33,#48
 994                     ; 296 	rs485_out_buff[34]=0x30;
 996  029b 35300022      	mov	_rs485_out_buff+34,#48
 997                     ; 297 	rs485_out_buff[35]=0x35;
 999  029f 35350023      	mov	_rs485_out_buff+35,#53
1000                     ; 298 	rs485_out_buff[36]=0x35;
1002  02a3 35350024      	mov	_rs485_out_buff+36,#53
1003                     ; 299 	rs485_out_buff[37]=0x36;
1005  02a7 35360025      	mov	_rs485_out_buff+37,#54
1006                     ; 300 	rs485_out_buff[38]=0x33;
1008  02ab 35330026      	mov	_rs485_out_buff+38,#51
1009                     ; 301 	rs485_out_buff[39]=0x31;
1011  02af 35310027      	mov	_rs485_out_buff+39,#49
1012                     ; 302 	rs485_out_buff[40]=0x44;
1014  02b3 35440028      	mov	_rs485_out_buff+40,#68
1015                     ; 303 	rs485_out_buff[41]=0x34;
1017  02b7 35340029      	mov	_rs485_out_buff+41,#52
1018                     ; 304 	rs485_out_buff[42]=0x43;
1020  02bb 3543002a      	mov	_rs485_out_buff+42,#67
1021                     ; 305 	rs485_out_buff[43]=0x46;
1023  02bf 3546002b      	mov	_rs485_out_buff+43,#70
1024                     ; 306 	rs485_out_buff[44]=0x46;
1026  02c3 3546002c      	mov	_rs485_out_buff+44,#70
1027                     ; 307 	rs485_out_buff[45]=0x30;
1029  02c7 3530002d      	mov	_rs485_out_buff+45,#48
1030                     ; 308 	rs485_out_buff[46]=0x45;
1032  02cb 3545002e      	mov	_rs485_out_buff+46,#69
1033                     ; 309 	rs485_out_buff[47]=0x41;
1035  02cf 3541002f      	mov	_rs485_out_buff+47,#65
1036                     ; 310 	rs485_out_buff[48]=0x36;
1038  02d3 35360030      	mov	_rs485_out_buff+48,#54
1039                     ; 311 	rs485_out_buff[49]=0x36;
1041  02d7 35360031      	mov	_rs485_out_buff+49,#54
1042                     ; 312 	rs485_out_buff[50]=0x34;
1044  02db 35340032      	mov	_rs485_out_buff+50,#52
1045                     ; 313 	rs485_out_buff[51]=0x30;
1047  02df 35300033      	mov	_rs485_out_buff+51,#48
1048                     ; 314 	rs485_out_buff[52]=0x31;	
1050  02e3 35310034      	mov	_rs485_out_buff+52,#49
1051                     ; 568 	uart1_out_adr(rs485_out_buff,100);
1053  02e7 ae0064        	ldw	x,#100
1054  02ea 89            	pushw	x
1055  02eb ae0000        	ldw	x,#_rs485_out_buff
1056  02ee cd00c9        	call	_uart1_out_adr
1058  02f1 85            	popw	x
1060  02f2 ac3e073e      	jpf	L513
1061  02f6               L313:
1062                     ; 575 	else if(bRX485==2)
1064  02f6 b601          	ld	a,_bRX485
1065  02f8 a102          	cp	a,#2
1066  02fa 2703          	jreq	L44
1067  02fc cc073e        	jp	L513
1068  02ff               L44:
1069                     ; 577 	GPIOD->DDR|=(1<<7);
1071  02ff 721e5011      	bset	20497,#7
1072                     ; 578 	GPIOD->CR1|=(1<<7);
1074  0303 721e5012      	bset	20498,#7
1075                     ; 579 	GPIOD->CR2&=~(1<<7);	
1077  0307 721f5013      	bres	20499,#7
1078                     ; 580 	GPIOD->ODR^=(1<<7);
1080  030b c6500f        	ld	a,20495
1081  030e a880          	xor	a,	#128
1082  0310 c7500f        	ld	20495,a
1083                     ; 582 	rs485_out_buff[0]=0x7e;
1085  0313 357e0000      	mov	_rs485_out_buff,#126
1086                     ; 583 	rs485_out_buff[1]=0x31;
1088  0317 35310001      	mov	_rs485_out_buff+1,#49
1089                     ; 584 	rs485_out_buff[2]=0x31;
1091  031b 35310002      	mov	_rs485_out_buff+2,#49
1092                     ; 585 	rs485_out_buff[3]=0x30;
1094  031f 35300003      	mov	_rs485_out_buff+3,#48
1095                     ; 586 	rs485_out_buff[4]=0x31;
1097  0323 35310004      	mov	_rs485_out_buff+4,#49
1098                     ; 587 	rs485_out_buff[5]=0x44;
1100  0327 35440005      	mov	_rs485_out_buff+5,#68
1101                     ; 588 	rs485_out_buff[6]=0x30;
1103  032b 35300006      	mov	_rs485_out_buff+6,#48
1104                     ; 589 	rs485_out_buff[7]=0x30;
1106  032f 35300007      	mov	_rs485_out_buff+7,#48
1107                     ; 590 	rs485_out_buff[8]=0x30;
1109  0333 35300008      	mov	_rs485_out_buff+8,#48
1110                     ; 591 	rs485_out_buff[9]=0x36;
1112  0337 35360009      	mov	_rs485_out_buff+9,#54
1113                     ; 592 	rs485_out_buff[10]=0x31;
1115  033b 3531000a      	mov	_rs485_out_buff+10,#49
1116                     ; 593 	rs485_out_buff[11]=0x31;
1118  033f 3531000b      	mov	_rs485_out_buff+11,#49
1119                     ; 594 	rs485_out_buff[12]=0x38;
1121  0343 3538000c      	mov	_rs485_out_buff+12,#56
1122                     ; 596 	rs485_out_buff[13]=0x30;
1124  0347 3530000d      	mov	_rs485_out_buff+13,#48
1125                     ; 597 	rs485_out_buff[14]=0x31;
1127  034b 3531000e      	mov	_rs485_out_buff+14,#49
1128                     ; 598 	rs485_out_buff[15]=0x30;
1130  034f 3530000f      	mov	_rs485_out_buff+15,#48
1131                     ; 599 	rs485_out_buff[16]=0x36;
1133  0353 35360010      	mov	_rs485_out_buff+16,#54
1134                     ; 600 	rs485_out_buff[17]=0x31;
1136  0357 35310011      	mov	_rs485_out_buff+17,#49
1137                     ; 601 	rs485_out_buff[18]=0x31;
1139  035b 35310012      	mov	_rs485_out_buff+18,#49
1140                     ; 602 	rs485_out_buff[19]=0x31;
1142  035f 35310013      	mov	_rs485_out_buff+19,#49
1143                     ; 603 	rs485_out_buff[20]=0x31;	
1145  0363 35310014      	mov	_rs485_out_buff+20,#49
1146                     ; 605 	rs485_out_buff[21]=0x30;
1148  0367 35300015      	mov	_rs485_out_buff+21,#48
1149                     ; 606 	rs485_out_buff[22]=0x30;
1151  036b 35300016      	mov	_rs485_out_buff+22,#48
1152                     ; 607 	rs485_out_buff[23]=0x30;
1154  036f 35300017      	mov	_rs485_out_buff+23,#48
1155                     ; 608 	rs485_out_buff[24]=0x30;
1157  0373 35300018      	mov	_rs485_out_buff+24,#48
1158                     ; 609 	rs485_out_buff[25]=0x30;
1160  0377 35300019      	mov	_rs485_out_buff+25,#48
1161                     ; 610 	rs485_out_buff[26]=0x30;
1163  037b 3530001a      	mov	_rs485_out_buff+26,#48
1164                     ; 611 	rs485_out_buff[27]=0x30;
1166  037f 3530001b      	mov	_rs485_out_buff+27,#48
1167                     ; 612 	rs485_out_buff[28]=0x30;
1169  0383 3530001c      	mov	_rs485_out_buff+28,#48
1170                     ; 613 	rs485_out_buff[29]=0x30;
1172  0387 3530001d      	mov	_rs485_out_buff+29,#48
1173                     ; 614 	rs485_out_buff[30]=0x30;
1175  038b 3530001e      	mov	_rs485_out_buff+30,#48
1176                     ; 615 	rs485_out_buff[31]=0x30;
1178  038f 3530001f      	mov	_rs485_out_buff+31,#48
1179                     ; 616 	rs485_out_buff[32]=0x30;
1181  0393 35300020      	mov	_rs485_out_buff+32,#48
1182                     ; 617 	rs485_out_buff[33]=0x30;
1184  0397 35300021      	mov	_rs485_out_buff+33,#48
1185                     ; 618 	rs485_out_buff[34]=0x30;
1187  039b 35300022      	mov	_rs485_out_buff+34,#48
1188                     ; 619 	rs485_out_buff[35]=0x30;
1190  039f 35300023      	mov	_rs485_out_buff+35,#48
1191                     ; 620 	rs485_out_buff[36]=0x30;
1193  03a3 35300024      	mov	_rs485_out_buff+36,#48
1194                     ; 621 	rs485_out_buff[37]=0x30;
1196  03a7 35300025      	mov	_rs485_out_buff+37,#48
1197                     ; 622 	rs485_out_buff[38]=0x30;
1199  03ab 35300026      	mov	_rs485_out_buff+38,#48
1200                     ; 623 	rs485_out_buff[39]=0x30;
1202  03af 35300027      	mov	_rs485_out_buff+39,#48
1203                     ; 624 	rs485_out_buff[40]=0x30;
1205  03b3 35300028      	mov	_rs485_out_buff+40,#48
1206                     ; 625 	rs485_out_buff[41]=0x30;
1208  03b7 35300029      	mov	_rs485_out_buff+41,#48
1209                     ; 626 	rs485_out_buff[42]=0x30;
1211  03bb 3530002a      	mov	_rs485_out_buff+42,#48
1212                     ; 627 	rs485_out_buff[43]=0x30;
1214  03bf 3530002b      	mov	_rs485_out_buff+43,#48
1215                     ; 628 	rs485_out_buff[44]=0x30;
1217  03c3 3530002c      	mov	_rs485_out_buff+44,#48
1218                     ; 629 	rs485_out_buff[45]=0x30;
1220  03c7 3530002d      	mov	_rs485_out_buff+45,#48
1221                     ; 630 	rs485_out_buff[46]=0x30;
1223  03cb 3530002e      	mov	_rs485_out_buff+46,#48
1224                     ; 631 	rs485_out_buff[47]=0x30;
1226  03cf 3530002f      	mov	_rs485_out_buff+47,#48
1227                     ; 632 	rs485_out_buff[48]=0x30;
1229  03d3 35300030      	mov	_rs485_out_buff+48,#48
1230                     ; 633 	rs485_out_buff[49]=0x30;
1232  03d7 35300031      	mov	_rs485_out_buff+49,#48
1233                     ; 634 	rs485_out_buff[50]=0x30;
1235  03db 35300032      	mov	_rs485_out_buff+50,#48
1236                     ; 635 	rs485_out_buff[51]=0x30;
1238  03df 35300033      	mov	_rs485_out_buff+51,#48
1239                     ; 636 	rs485_out_buff[52]=0x30;
1241  03e3 35300034      	mov	_rs485_out_buff+52,#48
1242                     ; 637 	rs485_out_buff[53]=0x30;
1244  03e7 35300035      	mov	_rs485_out_buff+53,#48
1245                     ; 638 	rs485_out_buff[54]=0x31;	
1247  03eb 35310036      	mov	_rs485_out_buff+54,#49
1248                     ; 640 	rs485_out_buff[21+34]=0x30;
1250  03ef 35300037      	mov	_rs485_out_buff+55,#48
1251                     ; 641 	rs485_out_buff[22+34]=0x30;
1253  03f3 35300038      	mov	_rs485_out_buff+56,#48
1254                     ; 642 	rs485_out_buff[23+34]=0x30;
1256  03f7 35300039      	mov	_rs485_out_buff+57,#48
1257                     ; 643 	rs485_out_buff[24+34]=0x30;
1259  03fb 3530003a      	mov	_rs485_out_buff+58,#48
1260                     ; 644 	rs485_out_buff[25+34]=0x30;
1262  03ff 3530003b      	mov	_rs485_out_buff+59,#48
1263                     ; 645 	rs485_out_buff[26+34]=0x30;
1265  0403 3530003c      	mov	_rs485_out_buff+60,#48
1266                     ; 646 	rs485_out_buff[27+34]=0x30;
1268  0407 3530003d      	mov	_rs485_out_buff+61,#48
1269                     ; 647 	rs485_out_buff[28+34]=0x30;
1271  040b 3530003e      	mov	_rs485_out_buff+62,#48
1272                     ; 648 	rs485_out_buff[29+34]=0x30;
1274  040f 3530003f      	mov	_rs485_out_buff+63,#48
1275                     ; 649 	rs485_out_buff[30+34]=0x30;
1277  0413 35300040      	mov	_rs485_out_buff+64,#48
1278                     ; 650 	rs485_out_buff[31+34]=0x30;
1280  0417 35300041      	mov	_rs485_out_buff+65,#48
1281                     ; 651 	rs485_out_buff[32+34]=0x30;
1283  041b 35300042      	mov	_rs485_out_buff+66,#48
1284                     ; 652 	rs485_out_buff[33+34]=0x30;
1286  041f 35300043      	mov	_rs485_out_buff+67,#48
1287                     ; 653 	rs485_out_buff[34+34]=0x30;
1289  0423 35300044      	mov	_rs485_out_buff+68,#48
1290                     ; 654 	rs485_out_buff[35+34]=0x30;
1292  0427 35300045      	mov	_rs485_out_buff+69,#48
1293                     ; 655 	rs485_out_buff[36+34]=0x30;
1295  042b 35300046      	mov	_rs485_out_buff+70,#48
1296                     ; 656 	rs485_out_buff[37+34]=0x30;
1298  042f 35300047      	mov	_rs485_out_buff+71,#48
1299                     ; 657 	rs485_out_buff[38+34]=0x30;
1301  0433 35300048      	mov	_rs485_out_buff+72,#48
1302                     ; 658 	rs485_out_buff[39+34]=0x30;
1304  0437 35300049      	mov	_rs485_out_buff+73,#48
1305                     ; 659 	rs485_out_buff[40+34]=0x30;
1307  043b 3530004a      	mov	_rs485_out_buff+74,#48
1308                     ; 660 	rs485_out_buff[41+34]=0x30;
1310  043f 3530004b      	mov	_rs485_out_buff+75,#48
1311                     ; 661 	rs485_out_buff[42+34]=0x30;
1313  0443 3530004c      	mov	_rs485_out_buff+76,#48
1314                     ; 662 	rs485_out_buff[43+34]=0x30;
1316  0447 3530004d      	mov	_rs485_out_buff+77,#48
1317                     ; 663 	rs485_out_buff[44+34]=0x30;
1319  044b 3530004e      	mov	_rs485_out_buff+78,#48
1320                     ; 664 	rs485_out_buff[45+34]=0x30;
1322  044f 3530004f      	mov	_rs485_out_buff+79,#48
1323                     ; 665 	rs485_out_buff[46+34]=0x30;
1325  0453 35300050      	mov	_rs485_out_buff+80,#48
1326                     ; 666 	rs485_out_buff[47+34]=0x30;
1328  0457 35300051      	mov	_rs485_out_buff+81,#48
1329                     ; 667 	rs485_out_buff[48+34]=0x30;
1331  045b 35300052      	mov	_rs485_out_buff+82,#48
1332                     ; 668 	rs485_out_buff[49+34]=0x30;
1334  045f 35300053      	mov	_rs485_out_buff+83,#48
1335                     ; 669 	rs485_out_buff[50+34]=0x30;
1337  0463 35300054      	mov	_rs485_out_buff+84,#48
1338                     ; 670 	rs485_out_buff[51+34]=0x30;
1340  0467 35300055      	mov	_rs485_out_buff+85,#48
1341                     ; 671 	rs485_out_buff[52+34]=0x30;
1343  046b 35300056      	mov	_rs485_out_buff+86,#48
1344                     ; 672 	rs485_out_buff[53+34]=0x30;
1346  046f 35300057      	mov	_rs485_out_buff+87,#48
1347                     ; 673 	rs485_out_buff[54+34]=0x32;
1349  0473 35320058      	mov	_rs485_out_buff+88,#50
1350                     ; 675 	rs485_out_buff[21+68]=0x30;
1352  0477 35300059      	mov	_rs485_out_buff+89,#48
1353                     ; 676 	rs485_out_buff[22+68]=0x30;
1355  047b 3530005a      	mov	_rs485_out_buff+90,#48
1356                     ; 677 	rs485_out_buff[23+68]=0x30;
1358  047f 3530005b      	mov	_rs485_out_buff+91,#48
1359                     ; 678 	rs485_out_buff[24+68]=0x30;
1361  0483 3530005c      	mov	_rs485_out_buff+92,#48
1362                     ; 679 	rs485_out_buff[25+68]=0x30;
1364  0487 3530005d      	mov	_rs485_out_buff+93,#48
1365                     ; 680 	rs485_out_buff[26+68]=0x30;
1367  048b 3530005e      	mov	_rs485_out_buff+94,#48
1368                     ; 681 	rs485_out_buff[27+68]=0x30;
1370  048f 3530005f      	mov	_rs485_out_buff+95,#48
1371                     ; 682 	rs485_out_buff[28+68]=0x30;
1373  0493 35300060      	mov	_rs485_out_buff+96,#48
1374                     ; 683 	rs485_out_buff[29+68]=0x30;
1376  0497 35300061      	mov	_rs485_out_buff+97,#48
1377                     ; 684 	rs485_out_buff[30+68]=0x30;
1379  049b 35300062      	mov	_rs485_out_buff+98,#48
1380                     ; 685 	rs485_out_buff[31+68]=0x30;
1382  049f 35300063      	mov	_rs485_out_buff+99,#48
1383                     ; 686 	rs485_out_buff[32+68]=0x30;
1385  04a3 35300064      	mov	_rs485_out_buff+100,#48
1386                     ; 687 	rs485_out_buff[33+68]=0x30;
1388  04a7 35300065      	mov	_rs485_out_buff+101,#48
1389                     ; 688 	rs485_out_buff[34+68]=0x30;
1391  04ab 35300066      	mov	_rs485_out_buff+102,#48
1392                     ; 689 	rs485_out_buff[35+68]=0x30;
1394  04af 35300067      	mov	_rs485_out_buff+103,#48
1395                     ; 690 	rs485_out_buff[36+68]=0x30;
1397  04b3 35300068      	mov	_rs485_out_buff+104,#48
1398                     ; 691 	rs485_out_buff[37+68]=0x30;
1400  04b7 35300069      	mov	_rs485_out_buff+105,#48
1401                     ; 692 	rs485_out_buff[38+68]=0x30;
1403  04bb 3530006a      	mov	_rs485_out_buff+106,#48
1404                     ; 693 	rs485_out_buff[39+68]=0x30;
1406  04bf 3530006b      	mov	_rs485_out_buff+107,#48
1407                     ; 694 	rs485_out_buff[40+68]=0x30;
1409  04c3 3530006c      	mov	_rs485_out_buff+108,#48
1410                     ; 695 	rs485_out_buff[41+68]=0x30;
1412  04c7 3530006d      	mov	_rs485_out_buff+109,#48
1413                     ; 696 	rs485_out_buff[42+68]=0x30;
1415  04cb 3530006e      	mov	_rs485_out_buff+110,#48
1416                     ; 697 	rs485_out_buff[43+68]=0x30;
1418  04cf 3530006f      	mov	_rs485_out_buff+111,#48
1419                     ; 698 	rs485_out_buff[44+68]=0x30;
1421  04d3 35300070      	mov	_rs485_out_buff+112,#48
1422                     ; 699 	rs485_out_buff[45+68]=0x30;
1424  04d7 35300071      	mov	_rs485_out_buff+113,#48
1425                     ; 700 	rs485_out_buff[46+68]=0x30;
1427  04db 35300072      	mov	_rs485_out_buff+114,#48
1428                     ; 701 	rs485_out_buff[47+68]=0x30;
1430  04df 35300073      	mov	_rs485_out_buff+115,#48
1431                     ; 702 	rs485_out_buff[48+68]=0x30;
1433  04e3 35300074      	mov	_rs485_out_buff+116,#48
1434                     ; 703 	rs485_out_buff[49+68]=0x30;
1436  04e7 35300075      	mov	_rs485_out_buff+117,#48
1437                     ; 704 	rs485_out_buff[50+68]=0x30;
1439  04eb 35300076      	mov	_rs485_out_buff+118,#48
1440                     ; 705 	rs485_out_buff[51+68]=0x30;
1442  04ef 35300077      	mov	_rs485_out_buff+119,#48
1443                     ; 706 	rs485_out_buff[52+68]=0x30;
1445  04f3 35300078      	mov	_rs485_out_buff+120,#48
1446                     ; 707 	rs485_out_buff[53+68]=0x30;
1448  04f7 35300079      	mov	_rs485_out_buff+121,#48
1449                     ; 708 	rs485_out_buff[54+68]=0x33;	
1451  04fb 3533007a      	mov	_rs485_out_buff+122,#51
1452                     ; 710 	rs485_out_buff[21+102]=0x30;
1454  04ff 3530007b      	mov	_rs485_out_buff+123,#48
1455                     ; 711 	rs485_out_buff[22+102]=0x30;
1457  0503 3530007c      	mov	_rs485_out_buff+124,#48
1458                     ; 712 	rs485_out_buff[23+102]=0x30;
1460  0507 3530007d      	mov	_rs485_out_buff+125,#48
1461                     ; 713 	rs485_out_buff[24+102]=0x30;
1463  050b 3530007e      	mov	_rs485_out_buff+126,#48
1464                     ; 714 	rs485_out_buff[25+102]=0x30;
1466  050f 3530007f      	mov	_rs485_out_buff+127,#48
1467                     ; 715 	rs485_out_buff[26+102]=0x30;
1469  0513 35300080      	mov	_rs485_out_buff+128,#48
1470                     ; 716 	rs485_out_buff[27+102]=0x30;
1472  0517 35300081      	mov	_rs485_out_buff+129,#48
1473                     ; 717 	rs485_out_buff[28+102]=0x30;
1475  051b 35300082      	mov	_rs485_out_buff+130,#48
1476                     ; 718 	rs485_out_buff[29+102]=0x30;
1478  051f 35300083      	mov	_rs485_out_buff+131,#48
1479                     ; 719 	rs485_out_buff[30+102]=0x30;
1481  0523 35300084      	mov	_rs485_out_buff+132,#48
1482                     ; 720 	rs485_out_buff[31+102]=0x30;
1484  0527 35300085      	mov	_rs485_out_buff+133,#48
1485                     ; 721 	rs485_out_buff[32+102]=0x30;
1487  052b 35300086      	mov	_rs485_out_buff+134,#48
1488                     ; 722 	rs485_out_buff[33+102]=0x30;
1490  052f 35300087      	mov	_rs485_out_buff+135,#48
1491                     ; 723 	rs485_out_buff[34+102]=0x30;
1493  0533 35300088      	mov	_rs485_out_buff+136,#48
1494                     ; 724 	rs485_out_buff[35+102]=0x30;
1496  0537 35300089      	mov	_rs485_out_buff+137,#48
1497                     ; 725 	rs485_out_buff[36+102]=0x30;
1499  053b 3530008a      	mov	_rs485_out_buff+138,#48
1500                     ; 726 	rs485_out_buff[37+102]=0x30;
1502  053f 3530008b      	mov	_rs485_out_buff+139,#48
1503                     ; 727 	rs485_out_buff[38+102]=0x30;
1505  0543 3530008c      	mov	_rs485_out_buff+140,#48
1506                     ; 728 	rs485_out_buff[39+102]=0x30;
1508  0547 3530008d      	mov	_rs485_out_buff+141,#48
1509                     ; 729 	rs485_out_buff[40+102]=0x30;
1511  054b 3530008e      	mov	_rs485_out_buff+142,#48
1512                     ; 730 	rs485_out_buff[41+102]=0x30;
1514  054f 3530008f      	mov	_rs485_out_buff+143,#48
1515                     ; 731 	rs485_out_buff[42+102]=0x30;
1517  0553 35300090      	mov	_rs485_out_buff+144,#48
1518                     ; 732 	rs485_out_buff[43+102]=0x30;
1520  0557 35300091      	mov	_rs485_out_buff+145,#48
1521                     ; 733 	rs485_out_buff[44+102]=0x30;
1523  055b 35300092      	mov	_rs485_out_buff+146,#48
1524                     ; 734 	rs485_out_buff[45+102]=0x30;
1526  055f 35300093      	mov	_rs485_out_buff+147,#48
1527                     ; 735 	rs485_out_buff[46+102]=0x30;
1529  0563 35300094      	mov	_rs485_out_buff+148,#48
1530                     ; 736 	rs485_out_buff[47+102]=0x30;
1532  0567 35300095      	mov	_rs485_out_buff+149,#48
1533                     ; 737 	rs485_out_buff[48+102]=0x30;
1535  056b 35300096      	mov	_rs485_out_buff+150,#48
1536                     ; 738 	rs485_out_buff[49+102]=0x30;
1538  056f 35300097      	mov	_rs485_out_buff+151,#48
1539                     ; 739 	rs485_out_buff[50+102]=0x30;
1541  0573 35300098      	mov	_rs485_out_buff+152,#48
1542                     ; 740 	rs485_out_buff[51+102]=0x30;
1544  0577 35300099      	mov	_rs485_out_buff+153,#48
1545                     ; 741 	rs485_out_buff[52+102]=0x30;
1547  057b 3530009a      	mov	_rs485_out_buff+154,#48
1548                     ; 742 	rs485_out_buff[53+102]=0x30;
1550  057f 3530009b      	mov	_rs485_out_buff+155,#48
1551                     ; 743 	rs485_out_buff[54+102]=0x34;
1553  0583 3534009c      	mov	_rs485_out_buff+156,#52
1554                     ; 745 	rs485_out_buff[21+136]=0x30;
1556  0587 3530009d      	mov	_rs485_out_buff+157,#48
1557                     ; 746 	rs485_out_buff[22+136]=0x30;
1559  058b 3530009e      	mov	_rs485_out_buff+158,#48
1560                     ; 747 	rs485_out_buff[23+136]=0x30;
1562  058f 3530009f      	mov	_rs485_out_buff+159,#48
1563                     ; 748 	rs485_out_buff[24+136]=0x30;
1565  0593 353000a0      	mov	_rs485_out_buff+160,#48
1566                     ; 749 	rs485_out_buff[25+136]=0x30;
1568  0597 353000a1      	mov	_rs485_out_buff+161,#48
1569                     ; 750 	rs485_out_buff[26+136]=0x30;
1571  059b 353000a2      	mov	_rs485_out_buff+162,#48
1572                     ; 751 	rs485_out_buff[27+136]=0x30;
1574  059f 353000a3      	mov	_rs485_out_buff+163,#48
1575                     ; 752 	rs485_out_buff[28+136]=0x30;
1577  05a3 353000a4      	mov	_rs485_out_buff+164,#48
1578                     ; 753 	rs485_out_buff[29+136]=0x30;
1580  05a7 353000a5      	mov	_rs485_out_buff+165,#48
1581                     ; 754 	rs485_out_buff[30+136]=0x30;
1583  05ab 353000a6      	mov	_rs485_out_buff+166,#48
1584                     ; 755 	rs485_out_buff[31+136]=0x30;
1586  05af 353000a7      	mov	_rs485_out_buff+167,#48
1587                     ; 756 	rs485_out_buff[32+136]=0x30;
1589  05b3 353000a8      	mov	_rs485_out_buff+168,#48
1590                     ; 757 	rs485_out_buff[33+136]=0x30;
1592  05b7 353000a9      	mov	_rs485_out_buff+169,#48
1593                     ; 758 	rs485_out_buff[34+136]=0x30;
1595  05bb 353000aa      	mov	_rs485_out_buff+170,#48
1596                     ; 759 	rs485_out_buff[35+136]=0x30;
1598  05bf 353000ab      	mov	_rs485_out_buff+171,#48
1599                     ; 760 	rs485_out_buff[36+136]=0x30;
1601  05c3 353000ac      	mov	_rs485_out_buff+172,#48
1602                     ; 761 	rs485_out_buff[37+136]=0x30;
1604  05c7 353000ad      	mov	_rs485_out_buff+173,#48
1605                     ; 762 	rs485_out_buff[38+136]=0x30;
1607  05cb 353000ae      	mov	_rs485_out_buff+174,#48
1608                     ; 763 	rs485_out_buff[39+136]=0x30;
1610  05cf 353000af      	mov	_rs485_out_buff+175,#48
1611                     ; 764 	rs485_out_buff[40+136]=0x30;
1613  05d3 353000b0      	mov	_rs485_out_buff+176,#48
1614                     ; 765 	rs485_out_buff[41+136]=0x30;
1616  05d7 353000b1      	mov	_rs485_out_buff+177,#48
1617                     ; 766 	rs485_out_buff[42+136]=0x30;
1619  05db 353000b2      	mov	_rs485_out_buff+178,#48
1620                     ; 767 	rs485_out_buff[43+136]=0x30;
1622  05df 353000b3      	mov	_rs485_out_buff+179,#48
1623                     ; 768 	rs485_out_buff[44+136]=0x30;
1625  05e3 353000b4      	mov	_rs485_out_buff+180,#48
1626                     ; 769 	rs485_out_buff[45+136]=0x30;
1628  05e7 353000b5      	mov	_rs485_out_buff+181,#48
1629                     ; 770 	rs485_out_buff[46+136]=0x30;
1631  05eb 353000b6      	mov	_rs485_out_buff+182,#48
1632                     ; 771 	rs485_out_buff[47+136]=0x30;
1634  05ef 353000b7      	mov	_rs485_out_buff+183,#48
1635                     ; 772 	rs485_out_buff[48+136]=0x30;
1637  05f3 353000b8      	mov	_rs485_out_buff+184,#48
1638                     ; 773 	rs485_out_buff[49+136]=0x30;
1640  05f7 353000b9      	mov	_rs485_out_buff+185,#48
1641                     ; 774 	rs485_out_buff[50+136]=0x30;
1643  05fb 353000ba      	mov	_rs485_out_buff+186,#48
1644                     ; 775 	rs485_out_buff[51+136]=0x30;
1646  05ff 353000bb      	mov	_rs485_out_buff+187,#48
1647                     ; 776 	rs485_out_buff[52+136]=0x30;
1649  0603 353000bc      	mov	_rs485_out_buff+188,#48
1650                     ; 777 	rs485_out_buff[53+136]=0x30;
1652  0607 353000bd      	mov	_rs485_out_buff+189,#48
1653                     ; 778 	rs485_out_buff[54+136]=0x35;	
1655  060b 353500be      	mov	_rs485_out_buff+190,#53
1656                     ; 780 	rs485_out_buff[21+170]=0x30;
1658  060f 353000bf      	mov	_rs485_out_buff+191,#48
1659                     ; 781 	rs485_out_buff[22+170]=0x30;
1661  0613 353000c0      	mov	_rs485_out_buff+192,#48
1662                     ; 782 	rs485_out_buff[23+170]=0x30;
1664  0617 353000c1      	mov	_rs485_out_buff+193,#48
1665                     ; 783 	rs485_out_buff[24+170]=0x30;
1667  061b 353000c2      	mov	_rs485_out_buff+194,#48
1668                     ; 784 	rs485_out_buff[25+170]=0x30;
1670  061f 353000c3      	mov	_rs485_out_buff+195,#48
1671                     ; 785 	rs485_out_buff[26+170]=0x30;
1673  0623 353000c4      	mov	_rs485_out_buff+196,#48
1674                     ; 786 	rs485_out_buff[27+170]=0x30;
1676  0627 353000c5      	mov	_rs485_out_buff+197,#48
1677                     ; 787 	rs485_out_buff[28+170]=0x30;
1679  062b 353000c6      	mov	_rs485_out_buff+198,#48
1680                     ; 788 	rs485_out_buff[29+170]=0x30;
1682  062f 353000c7      	mov	_rs485_out_buff+199,#48
1683                     ; 789 	rs485_out_buff[30+170]=0x30;
1685  0633 353000c8      	mov	_rs485_out_buff+200,#48
1686                     ; 790 	rs485_out_buff[31+170]=0x30;
1688  0637 353000c9      	mov	_rs485_out_buff+201,#48
1689                     ; 791 	rs485_out_buff[32+170]=0x30;
1691  063b 353000ca      	mov	_rs485_out_buff+202,#48
1692                     ; 792 	rs485_out_buff[33+170]=0x30;
1694  063f 353000cb      	mov	_rs485_out_buff+203,#48
1695                     ; 793 	rs485_out_buff[34+170]=0x30;
1697  0643 353000cc      	mov	_rs485_out_buff+204,#48
1698                     ; 794 	rs485_out_buff[35+170]=0x30;
1700  0647 353000cd      	mov	_rs485_out_buff+205,#48
1701                     ; 795 	rs485_out_buff[36+170]=0x30;
1703  064b 353000ce      	mov	_rs485_out_buff+206,#48
1704                     ; 796 	rs485_out_buff[37+170]=0x30;
1706  064f 353000cf      	mov	_rs485_out_buff+207,#48
1707                     ; 797 	rs485_out_buff[38+170]=0x30;
1709  0653 353000d0      	mov	_rs485_out_buff+208,#48
1710                     ; 798 	rs485_out_buff[39+170]=0x30;
1712  0657 353000d1      	mov	_rs485_out_buff+209,#48
1713                     ; 799 	rs485_out_buff[40+170]=0x30;
1715  065b 353000d2      	mov	_rs485_out_buff+210,#48
1716                     ; 800 	rs485_out_buff[41+170]=0x30;
1718  065f 353000d3      	mov	_rs485_out_buff+211,#48
1719                     ; 801 	rs485_out_buff[42+170]=0x30;
1721  0663 353000d4      	mov	_rs485_out_buff+212,#48
1722                     ; 802 	rs485_out_buff[43+170]=0x30;
1724  0667 353000d5      	mov	_rs485_out_buff+213,#48
1725                     ; 803 	rs485_out_buff[44+170]=0x30;
1727  066b 353000d6      	mov	_rs485_out_buff+214,#48
1728                     ; 804 	rs485_out_buff[45+170]=0x30;
1730  066f 353000d7      	mov	_rs485_out_buff+215,#48
1731                     ; 805 	rs485_out_buff[46+170]=0x30;
1733  0673 353000d8      	mov	_rs485_out_buff+216,#48
1734                     ; 806 	rs485_out_buff[47+170]=0x30;
1736  0677 353000d9      	mov	_rs485_out_buff+217,#48
1737                     ; 807 	rs485_out_buff[48+170]=0x30;
1739  067b 353000da      	mov	_rs485_out_buff+218,#48
1740                     ; 808 	rs485_out_buff[49+170]=0x30;
1742  067f 353000db      	mov	_rs485_out_buff+219,#48
1743                     ; 809 	rs485_out_buff[50+170]=0x30;
1745  0683 353000dc      	mov	_rs485_out_buff+220,#48
1746                     ; 810 	rs485_out_buff[51+170]=0x30;
1748  0687 353000dd      	mov	_rs485_out_buff+221,#48
1749                     ; 811 	rs485_out_buff[52+170]=0x30;
1751  068b 353000de      	mov	_rs485_out_buff+222,#48
1752                     ; 812 	rs485_out_buff[53+170]=0x30;
1754  068f 353000df      	mov	_rs485_out_buff+223,#48
1755                     ; 813 	rs485_out_buff[54+170]=0x36;
1757  0693 353600e0      	mov	_rs485_out_buff+224,#54
1758                     ; 815 	rs485_out_buff[21+204]=0x30;
1760  0697 353000e1      	mov	_rs485_out_buff+225,#48
1761                     ; 816 	rs485_out_buff[22+204]=0x30;
1763  069b 353000e2      	mov	_rs485_out_buff+226,#48
1764                     ; 817 	rs485_out_buff[23+204]=0x30;
1766  069f 353000e3      	mov	_rs485_out_buff+227,#48
1767                     ; 818 	rs485_out_buff[24+204]=0x30;
1769  06a3 353000e4      	mov	_rs485_out_buff+228,#48
1770                     ; 819 	rs485_out_buff[25+204]=0x30;
1772  06a7 353000e5      	mov	_rs485_out_buff+229,#48
1773                     ; 820 	rs485_out_buff[26+204]=0x30;
1775  06ab 353000e6      	mov	_rs485_out_buff+230,#48
1776                     ; 821 	rs485_out_buff[27+204]=0x30;
1778  06af 353000e7      	mov	_rs485_out_buff+231,#48
1779                     ; 822 	rs485_out_buff[28+204]=0x30;
1781  06b3 353000e8      	mov	_rs485_out_buff+232,#48
1782                     ; 823 	rs485_out_buff[29+204]=0x30;
1784  06b7 353000e9      	mov	_rs485_out_buff+233,#48
1785                     ; 824 	rs485_out_buff[30+204]=0x30;
1787  06bb 353000ea      	mov	_rs485_out_buff+234,#48
1788                     ; 825 	rs485_out_buff[31+204]=0x30;
1790  06bf 353000eb      	mov	_rs485_out_buff+235,#48
1791                     ; 826 	rs485_out_buff[32+204]=0x30;
1793  06c3 353000ec      	mov	_rs485_out_buff+236,#48
1794                     ; 827 	rs485_out_buff[33+204]=0x30;
1796  06c7 353000ed      	mov	_rs485_out_buff+237,#48
1797                     ; 828 	rs485_out_buff[34+204]=0x30;
1799  06cb 353000ee      	mov	_rs485_out_buff+238,#48
1800                     ; 829 	rs485_out_buff[35+204]=0x30;
1802  06cf 353000ef      	mov	_rs485_out_buff+239,#48
1803                     ; 830 	rs485_out_buff[36+204]=0x30;
1805  06d3 353000f0      	mov	_rs485_out_buff+240,#48
1806                     ; 831 	rs485_out_buff[37+204]=0x30;
1808  06d7 353000f1      	mov	_rs485_out_buff+241,#48
1809                     ; 832 	rs485_out_buff[38+204]=0x30;
1811  06db 353000f2      	mov	_rs485_out_buff+242,#48
1812                     ; 833 	rs485_out_buff[39+204]=0x30;
1814  06df 353000f3      	mov	_rs485_out_buff+243,#48
1815                     ; 834 	rs485_out_buff[40+204]=0x30;
1817  06e3 353000f4      	mov	_rs485_out_buff+244,#48
1818                     ; 835 	rs485_out_buff[41+204]=0x30;
1820  06e7 353000f5      	mov	_rs485_out_buff+245,#48
1821                     ; 836 	rs485_out_buff[42+204]=0x30;
1823  06eb 353000f6      	mov	_rs485_out_buff+246,#48
1824                     ; 837 	rs485_out_buff[43+204]=0x30;
1826  06ef 353000f7      	mov	_rs485_out_buff+247,#48
1827                     ; 838 	rs485_out_buff[44+204]=0x30;
1829  06f3 353000f8      	mov	_rs485_out_buff+248,#48
1830                     ; 839 	rs485_out_buff[45+204]=0x30;
1832  06f7 353000f9      	mov	_rs485_out_buff+249,#48
1833                     ; 840 	rs485_out_buff[46+204]=0x30;
1835  06fb 353000fa      	mov	_rs485_out_buff+250,#48
1836                     ; 841 	rs485_out_buff[47+204]=0x30;
1838  06ff 353000fb      	mov	_rs485_out_buff+251,#48
1839                     ; 842 	rs485_out_buff[48+204]=0x30;
1841  0703 353000fc      	mov	_rs485_out_buff+252,#48
1842                     ; 843 	rs485_out_buff[49+204]=0x30;
1844  0707 353000fd      	mov	_rs485_out_buff+253,#48
1845                     ; 844 	rs485_out_buff[50+204]=0x30;
1847  070b 353000fe      	mov	_rs485_out_buff+254,#48
1848                     ; 845 	rs485_out_buff[51+204]=0x30;
1850  070f 353000ff      	mov	_rs485_out_buff+255,#48
1851                     ; 846 	rs485_out_buff[52+204]=0x30;
1853  0713 35300100      	mov	_rs485_out_buff+256,#48
1854                     ; 847 	rs485_out_buff[53+204]=0x30;
1856  0717 35300101      	mov	_rs485_out_buff+257,#48
1857                     ; 848 	rs485_out_buff[54+204]=0x37;	
1859  071b 35370102      	mov	_rs485_out_buff+258,#55
1860                     ; 850 	rs485_out_buff[259]=0x43;
1862  071f 35430103      	mov	_rs485_out_buff+259,#67
1863                     ; 851 	rs485_out_buff[260]=0x46;
1865  0723 35460104      	mov	_rs485_out_buff+260,#70
1866                     ; 852 	rs485_out_buff[261]=0x31;
1868  0727 35310105      	mov	_rs485_out_buff+261,#49
1869                     ; 853 	rs485_out_buff[262]=0x39;
1871  072b 35390106      	mov	_rs485_out_buff+262,#57
1872                     ; 854 	rs485_out_buff[263]=0x0d;
1874  072f 350d0107      	mov	_rs485_out_buff+263,#13
1875                     ; 856 	uart1_out_adr(rs485_out_buff,264);
1877  0733 ae0108        	ldw	x,#264
1878  0736 89            	pushw	x
1879  0737 ae0000        	ldw	x,#_rs485_out_buff
1880  073a cd00c9        	call	_uart1_out_adr
1882  073d 85            	popw	x
1883  073e               L513:
1884                     ; 859 bRX485=0;	
1886  073e 3f01          	clr	_bRX485
1887                     ; 860 }
1890  0740 81            	ret
1913                     ; 863 void init_CAN(void) {
1914                     	switch	.text
1915  0741               _init_CAN:
1919                     ; 864 	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
1921  0741 72135420      	bres	21536,#1
1922                     ; 865 	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
1924  0745 72105420      	bset	21536,#0
1926  0749               L333:
1927                     ; 866 	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
1929  0749 c65421        	ld	a,21537
1930  074c a501          	bcp	a,#1
1931  074e 27f9          	jreq	L333
1932                     ; 868 	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
1934  0750 72185420      	bset	21536,#4
1935                     ; 870 	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
1937  0754 35025427      	mov	21543,#2
1938                     ; 879 	CAN->Page.Filter01.F0R1= MY_MESS_STID>>3;			// 16 bits mode
1940  0758 35135428      	mov	21544,#19
1941                     ; 880 	CAN->Page.Filter01.F0R2= MY_MESS_STID<<5;
1943  075c 35c05429      	mov	21545,#192
1944                     ; 881 	CAN->Page.Filter01.F0R5= MY_MESS_STID_MASK>>3;
1946  0760 357f542c      	mov	21548,#127
1947                     ; 882 	CAN->Page.Filter01.F0R6= MY_MESS_STID_MASK<<5;
1949  0764 35e0542d      	mov	21549,#224
1950                     ; 885 	CAN->PSR= 6;									// set page 6
1952  0768 35065427      	mov	21543,#6
1953                     ; 890 	CAN->Page.Config.FMR1&=~3;								//mask mode
1955  076c c65430        	ld	a,21552
1956  076f a4fc          	and	a,#252
1957  0771 c75430        	ld	21552,a
1958                     ; 896 	CAN->Page.Config.FCR1= ((3<<1) & (CAN_FCR1_FSC00 | CAN_FCR1_FSC01));		//16 bit scale
1960  0774 35065432      	mov	21554,#6
1961                     ; 899 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
1963  0778 72105432      	bset	21554,#0
1964                     ; 902 	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
1966  077c 35065427      	mov	21543,#6
1967                     ; 904 	CAN->Page.Config.BTR1= 9;					// CAN_BTR1_BRP=9, 	tq= fcpu/(9+1)
1969  0780 3509542c      	mov	21548,#9
1970                     ; 905 	CAN->Page.Config.BTR2= (1<<7)|(6<<4) | 7; 		// BS2=8, BS1=7, 		
1972  0784 35e7542d      	mov	21549,#231
1973                     ; 907 	CAN->IER|=(1<<1);
1975  0788 72125425      	bset	21541,#1
1976                     ; 910 	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
1978  078c 72115420      	bres	21536,#0
1980  0790               L143:
1981                     ; 911 	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
1983  0790 c65421        	ld	a,21537
1984  0793 a501          	bcp	a,#1
1985  0795 26f9          	jrne	L143
1986                     ; 912 }
1989  0797 81            	ret
2097                     ; 915 void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
2097                     ; 916 {
2098                     	switch	.text
2099  0798               _can_transmit:
2101  0798 89            	pushw	x
2102       00000000      OFST:	set	0
2105                     ; 918 if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>4))can_buff_wr_ptr=0;
2107  0799 b627          	ld	a,_can_buff_wr_ptr
2108  079b a105          	cp	a,#5
2109  079d 2502          	jrult	L324
2112  079f 3f27          	clr	_can_buff_wr_ptr
2113  07a1               L324:
2114                     ; 920 can_out_buff[can_buff_wr_ptr][0]=(char)(id_st>>6);
2116  07a1 b627          	ld	a,_can_buff_wr_ptr
2117  07a3 97            	ld	xl,a
2118  07a4 a610          	ld	a,#16
2119  07a6 42            	mul	x,a
2120  07a7 1601          	ldw	y,(OFST+1,sp)
2121  07a9 a606          	ld	a,#6
2122  07ab               L25:
2123  07ab 9054          	srlw	y
2124  07ad 4a            	dec	a
2125  07ae 26fb          	jrne	L25
2126  07b0 909f          	ld	a,yl
2127  07b2 e728          	ld	(_can_out_buff,x),a
2128                     ; 921 can_out_buff[can_buff_wr_ptr][1]=(char)(id_st<<2);
2130  07b4 b627          	ld	a,_can_buff_wr_ptr
2131  07b6 97            	ld	xl,a
2132  07b7 a610          	ld	a,#16
2133  07b9 42            	mul	x,a
2134  07ba 7b02          	ld	a,(OFST+2,sp)
2135  07bc 48            	sll	a
2136  07bd 48            	sll	a
2137  07be e729          	ld	(_can_out_buff+1,x),a
2138                     ; 923 can_out_buff[can_buff_wr_ptr][2]=data0;
2140  07c0 b627          	ld	a,_can_buff_wr_ptr
2141  07c2 97            	ld	xl,a
2142  07c3 a610          	ld	a,#16
2143  07c5 42            	mul	x,a
2144  07c6 7b05          	ld	a,(OFST+5,sp)
2145  07c8 e72a          	ld	(_can_out_buff+2,x),a
2146                     ; 924 can_out_buff[can_buff_wr_ptr][3]=data1;
2148  07ca b627          	ld	a,_can_buff_wr_ptr
2149  07cc 97            	ld	xl,a
2150  07cd a610          	ld	a,#16
2151  07cf 42            	mul	x,a
2152  07d0 7b06          	ld	a,(OFST+6,sp)
2153  07d2 e72b          	ld	(_can_out_buff+3,x),a
2154                     ; 925 can_out_buff[can_buff_wr_ptr][4]=data2;
2156  07d4 b627          	ld	a,_can_buff_wr_ptr
2157  07d6 97            	ld	xl,a
2158  07d7 a610          	ld	a,#16
2159  07d9 42            	mul	x,a
2160  07da 7b07          	ld	a,(OFST+7,sp)
2161  07dc e72c          	ld	(_can_out_buff+4,x),a
2162                     ; 926 can_out_buff[can_buff_wr_ptr][5]=data3;
2164  07de b627          	ld	a,_can_buff_wr_ptr
2165  07e0 97            	ld	xl,a
2166  07e1 a610          	ld	a,#16
2167  07e3 42            	mul	x,a
2168  07e4 7b08          	ld	a,(OFST+8,sp)
2169  07e6 e72d          	ld	(_can_out_buff+5,x),a
2170                     ; 927 can_out_buff[can_buff_wr_ptr][6]=data4;
2172  07e8 b627          	ld	a,_can_buff_wr_ptr
2173  07ea 97            	ld	xl,a
2174  07eb a610          	ld	a,#16
2175  07ed 42            	mul	x,a
2176  07ee 7b09          	ld	a,(OFST+9,sp)
2177  07f0 e72e          	ld	(_can_out_buff+6,x),a
2178                     ; 928 can_out_buff[can_buff_wr_ptr][7]=data5;
2180  07f2 b627          	ld	a,_can_buff_wr_ptr
2181  07f4 97            	ld	xl,a
2182  07f5 a610          	ld	a,#16
2183  07f7 42            	mul	x,a
2184  07f8 7b0a          	ld	a,(OFST+10,sp)
2185  07fa e72f          	ld	(_can_out_buff+7,x),a
2186                     ; 929 can_out_buff[can_buff_wr_ptr][8]=data6;
2188  07fc b627          	ld	a,_can_buff_wr_ptr
2189  07fe 97            	ld	xl,a
2190  07ff a610          	ld	a,#16
2191  0801 42            	mul	x,a
2192  0802 7b0b          	ld	a,(OFST+11,sp)
2193  0804 e730          	ld	(_can_out_buff+8,x),a
2194                     ; 930 can_out_buff[can_buff_wr_ptr][9]=data7;
2196  0806 b627          	ld	a,_can_buff_wr_ptr
2197  0808 97            	ld	xl,a
2198  0809 a610          	ld	a,#16
2199  080b 42            	mul	x,a
2200  080c 7b0c          	ld	a,(OFST+12,sp)
2201  080e e731          	ld	(_can_out_buff+9,x),a
2202                     ; 932 can_buff_wr_ptr++;
2204  0810 3c27          	inc	_can_buff_wr_ptr
2205                     ; 933 if(can_buff_wr_ptr>4)can_buff_wr_ptr=0;
2207  0812 b627          	ld	a,_can_buff_wr_ptr
2208  0814 a105          	cp	a,#5
2209  0816 2502          	jrult	L524
2212  0818 3f27          	clr	_can_buff_wr_ptr
2213  081a               L524:
2214                     ; 934 } 
2217  081a 85            	popw	x
2218  081b 81            	ret
2247                     ; 937 void can_tx_hndl(void)
2247                     ; 938 {
2248                     	switch	.text
2249  081c               _can_tx_hndl:
2253                     ; 939 if(bTX_FREE)
2255  081c 3d06          	tnz	_bTX_FREE
2256  081e 2757          	jreq	L734
2257                     ; 941 	if(can_buff_rd_ptr!=can_buff_wr_ptr)
2259  0820 b626          	ld	a,_can_buff_rd_ptr
2260  0822 b127          	cp	a,_can_buff_wr_ptr
2261  0824 275f          	jreq	L544
2262                     ; 943 		bTX_FREE=0;
2264  0826 3f06          	clr	_bTX_FREE
2265                     ; 945 		CAN->PSR= 0;
2267  0828 725f5427      	clr	21543
2268                     ; 946 		CAN->Page.TxMailbox.MDLCR=8;
2270  082c 35085429      	mov	21545,#8
2271                     ; 947 		CAN->Page.TxMailbox.MIDR1=can_out_buff[can_buff_rd_ptr][0];
2273  0830 b626          	ld	a,_can_buff_rd_ptr
2274  0832 97            	ld	xl,a
2275  0833 a610          	ld	a,#16
2276  0835 42            	mul	x,a
2277  0836 e628          	ld	a,(_can_out_buff,x)
2278  0838 c7542a        	ld	21546,a
2279                     ; 948 		CAN->Page.TxMailbox.MIDR2=can_out_buff[can_buff_rd_ptr][1];
2281  083b b626          	ld	a,_can_buff_rd_ptr
2282  083d 97            	ld	xl,a
2283  083e a610          	ld	a,#16
2284  0840 42            	mul	x,a
2285  0841 e629          	ld	a,(_can_out_buff+1,x)
2286  0843 c7542b        	ld	21547,a
2287                     ; 950 		memcpy(&CAN->Page.TxMailbox.MDAR1, &can_out_buff[can_buff_rd_ptr][2],8);
2289  0846 b626          	ld	a,_can_buff_rd_ptr
2290  0848 97            	ld	xl,a
2291  0849 a610          	ld	a,#16
2292  084b 42            	mul	x,a
2293  084c 01            	rrwa	x,a
2294  084d ab2a          	add	a,#_can_out_buff+2
2295  084f 2401          	jrnc	L65
2296  0851 5c            	incw	x
2297  0852               L65:
2298  0852 5f            	clrw	x
2299  0853 97            	ld	xl,a
2300  0854 bf00          	ldw	c_x,x
2301  0856 ae0008        	ldw	x,#8
2302  0859               L06:
2303  0859 5a            	decw	x
2304  085a 92d600        	ld	a,([c_x],x)
2305  085d d7542e        	ld	(21550,x),a
2306  0860 5d            	tnzw	x
2307  0861 26f6          	jrne	L06
2308                     ; 952 		can_buff_rd_ptr++;
2310  0863 3c26          	inc	_can_buff_rd_ptr
2311                     ; 953 		if(can_buff_rd_ptr>3)can_buff_rd_ptr=0;
2313  0865 b626          	ld	a,_can_buff_rd_ptr
2314  0867 a104          	cp	a,#4
2315  0869 2502          	jrult	L344
2318  086b 3f26          	clr	_can_buff_rd_ptr
2319  086d               L344:
2320                     ; 955 		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;
2322  086d 72105428      	bset	21544,#0
2323                     ; 956 		CAN->IER|=(1<<0);
2325  0871 72105425      	bset	21541,#0
2326  0875 200e          	jra	L544
2327  0877               L734:
2328                     ; 961 	tx_busy_cnt++;
2330  0877 3c25          	inc	_tx_busy_cnt
2331                     ; 962 	if(tx_busy_cnt>=100)
2333  0879 b625          	ld	a,_tx_busy_cnt
2334  087b a164          	cp	a,#100
2335  087d 2506          	jrult	L544
2336                     ; 964 		tx_busy_cnt=0;
2338  087f 3f25          	clr	_tx_busy_cnt
2339                     ; 965 		bTX_FREE=1;
2341  0881 35010006      	mov	_bTX_FREE,#1
2342  0885               L544:
2343                     ; 968 }
2346  0885 81            	ret
2374                     ; 972 void can_in_an(void)
2374                     ; 973 {
2375                     	switch	.text
2376  0886               _can_in_an:
2380                     ; 984 if((mess[6]==19)&&(mess[7]==19)&&(mess[8]==GETTM))	
2382  0886 b69b          	ld	a,_mess+6
2383  0888 a113          	cp	a,#19
2384  088a 2622          	jrne	L154
2386  088c b69c          	ld	a,_mess+7
2387  088e a113          	cp	a,#19
2388  0890 261c          	jrne	L154
2390  0892 b69d          	ld	a,_mess+8
2391  0894 a1ed          	cp	a,#237
2392  0896 2616          	jrne	L154
2393                     ; 986 	GPIOD->DDR|=(1<<7);
2395  0898 721e5011      	bset	20497,#7
2396                     ; 987 	GPIOD->CR1|=(1<<7);
2398  089c 721e5012      	bset	20498,#7
2399                     ; 988 	GPIOD->CR2&=~(1<<7);	
2401  08a0 721f5013      	bres	20499,#7
2402                     ; 989 	GPIOD->ODR^=(1<<7);
2404  08a4 c6500f        	ld	a,20495
2405  08a7 a880          	xor	a,	#128
2406  08a9 c7500f        	ld	20495,a
2407                     ; 990 	can_error_cnt=0;
2409  08ac 3f24          	clr	_can_error_cnt
2410  08ae               L154:
2411                     ; 1013 can_in_an_end:
2411                     ; 1014 bCAN_RX=0;
2413  08ae 3f07          	clr	_bCAN_RX
2414                     ; 1015 }   
2417  08b0 81            	ret
2440                     ; 1019 void t4_init(void){
2441                     	switch	.text
2442  08b1               _t4_init:
2446                     ; 1020 	TIM4->PSCR = 7;
2448  08b1 35075345      	mov	21317,#7
2449                     ; 1021 	TIM4->ARR= 77;
2451  08b5 354d5346      	mov	21318,#77
2452                     ; 1022 	TIM4->IER|= TIM4_IER_UIE;					// enable break interrupt
2454  08b9 72105341      	bset	21313,#0
2455                     ; 1024 	TIM4->CR1=(TIM4_CR1_URS | TIM4_CR1_CEN | TIM4_CR1_ARPE);	
2457  08bd 35855340      	mov	21312,#133
2458                     ; 1026 }
2461  08c1 81            	ret
2496                     ; 1032 @far @interrupt void TIM4_UPD_Interrupt (void) 
2496                     ; 1033 {
2498                     	switch	.text
2499  08c2               f_TIM4_UPD_Interrupt:
2503                     ; 1034 TIM4->SR1&=~TIM4_SR1_UIF;
2505  08c2 72115342      	bres	21314,#0
2506                     ; 1037 if(++t0_cnt0>=10)
2508  08c6 3c00          	inc	_t0_cnt0
2509  08c8 b600          	ld	a,_t0_cnt0
2510  08ca a10a          	cp	a,#10
2511  08cc 253e          	jrult	L705
2512                     ; 1039 	t0_cnt0=0;
2514  08ce 3f00          	clr	_t0_cnt0
2515                     ; 1040 	b100Hz=1;
2517  08d0 72100006      	bset	_b100Hz
2518                     ; 1042 	if(++t0_cnt1>=10)
2520  08d4 3c01          	inc	_t0_cnt1
2521  08d6 b601          	ld	a,_t0_cnt1
2522  08d8 a10a          	cp	a,#10
2523  08da 2506          	jrult	L115
2524                     ; 1044 		t0_cnt1=0;
2526  08dc 3f01          	clr	_t0_cnt1
2527                     ; 1045 		b10Hz=1;
2529  08de 72100005      	bset	_b10Hz
2530  08e2               L115:
2531                     ; 1048 	if(++t0_cnt2>=20)
2533  08e2 3c02          	inc	_t0_cnt2
2534  08e4 b602          	ld	a,_t0_cnt2
2535  08e6 a114          	cp	a,#20
2536  08e8 2506          	jrult	L315
2537                     ; 1050 		t0_cnt2=0;
2539  08ea 3f02          	clr	_t0_cnt2
2540                     ; 1051 		b5Hz=1;
2542  08ec 72100004      	bset	_b5Hz
2543  08f0               L315:
2544                     ; 1055 	if(++t0_cnt4>=50)
2546  08f0 3c04          	inc	_t0_cnt4
2547  08f2 b604          	ld	a,_t0_cnt4
2548  08f4 a132          	cp	a,#50
2549  08f6 2506          	jrult	L515
2550                     ; 1057 		t0_cnt4=0;
2552  08f8 3f04          	clr	_t0_cnt4
2553                     ; 1058 		b2Hz=1;
2555  08fa 72100003      	bset	_b2Hz
2556  08fe               L515:
2557                     ; 1061 	if(++t0_cnt3>=100)
2559  08fe 3c03          	inc	_t0_cnt3
2560  0900 b603          	ld	a,_t0_cnt3
2561  0902 a164          	cp	a,#100
2562  0904 2506          	jrult	L705
2563                     ; 1063 		t0_cnt3=0;
2565  0906 3f03          	clr	_t0_cnt3
2566                     ; 1064 		b1Hz=1;
2568  0908 72100002      	bset	_b1Hz
2569  090c               L705:
2570                     ; 1071 if(tx_stat_cnt)
2572  090c 725d0285      	tnz	_tx_stat_cnt
2573  0910 270c          	jreq	L125
2574                     ; 1073 	tx_stat_cnt--;
2576  0912 725a0285      	dec	_tx_stat_cnt
2577                     ; 1074 	if(tx_stat_cnt==0)tx_stat=tsOFF;
2579  0916 725d0285      	tnz	_tx_stat_cnt
2580  091a 2602          	jrne	L125
2583  091c 3f05          	clr	_tx_stat
2584  091e               L125:
2585                     ; 1089 }
2588  091e 80            	iret
2613                     ; 1092 @far @interrupt void CAN_RX_Interrupt (void) 
2613                     ; 1093 {
2614                     	switch	.text
2615  091f               f_CAN_RX_Interrupt:
2619                     ; 1103 CAN->PSR= 7;									// page 7 - read messsage
2621  091f 35075427      	mov	21543,#7
2622                     ; 1105 memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
2624  0923 ae000e        	ldw	x,#14
2625  0926               L27:
2626  0926 d65427        	ld	a,(21543,x)
2627  0929 e794          	ld	(_mess-1,x),a
2628  092b 5a            	decw	x
2629  092c 26f8          	jrne	L27
2630                     ; 1116 bCAN_RX=1;
2632  092e 35010007      	mov	_bCAN_RX,#1
2633                     ; 1117 CAN->RFR|=(1<<5);
2635  0932 721a5424      	bset	21540,#5
2636                     ; 1119 }
2639  0936 80            	iret
2662                     ; 1122 @far @interrupt void CAN_TX_Interrupt (void) 
2662                     ; 1123 {
2663                     	switch	.text
2664  0937               f_CAN_TX_Interrupt:
2668                     ; 1124 	if((CAN->TSR)&(1<<0))
2670  0937 c65422        	ld	a,21538
2671  093a a501          	bcp	a,#1
2672  093c 2708          	jreq	L545
2673                     ; 1126 	bTX_FREE=1;	
2675  093e 35010006      	mov	_bTX_FREE,#1
2676                     ; 1128 	CAN->TSR|=(1<<0);
2678  0942 72105422      	bset	21538,#0
2679  0946               L545:
2680                     ; 1130 }
2683  0946 80            	iret
2721                     ; 1134 @far @interrupt void UART1TxInterrupt (void) 
2721                     ; 1135 {
2722                     	switch	.text
2723  0947               f_UART1TxInterrupt:
2725       00000001      OFST:	set	1
2726  0947 88            	push	a
2729                     ; 1138 tx_status=UART1->SR;
2731  0948 c65230        	ld	a,21040
2732  094b 6b01          	ld	(OFST+0,sp),a
2733                     ; 1140 if (tx_status & (UART1_SR_TXE))
2735  094d 7b01          	ld	a,(OFST+0,sp)
2736  094f a580          	bcp	a,#128
2737  0951 2730          	jreq	L565
2738                     ; 1142 	if (tx_counter1)
2740  0953 be93          	ldw	x,_tx_counter1
2741  0955 2720          	jreq	L765
2742                     ; 1144 		--tx_counter1;
2744  0957 be93          	ldw	x,_tx_counter1
2745  0959 1d0001        	subw	x,#1
2746  095c bf93          	ldw	_tx_counter1,x
2747                     ; 1145 		UART1->DR=tx_buffer1[tx_rd_index1];
2749  095e be8f          	ldw	x,_tx_rd_index1
2750  0960 d60000        	ld	a,(_tx_buffer1,x)
2751  0963 c75231        	ld	21041,a
2752                     ; 1146 		if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
2754  0966 be8f          	ldw	x,_tx_rd_index1
2755  0968 1c0001        	addw	x,#1
2756  096b bf8f          	ldw	_tx_rd_index1,x
2757  096d a3012c        	cpw	x,#300
2758  0970 2611          	jrne	L565
2761  0972 5f            	clrw	x
2762  0973 bf8f          	ldw	_tx_rd_index1,x
2763  0975 200c          	jra	L565
2764  0977               L765:
2765                     ; 1150 		tx_stat_cnt=3;
2767  0977 35030285      	mov	_tx_stat_cnt,#3
2768                     ; 1151 			bOUT_FREE=1;
2770  097b 35010088      	mov	_bOUT_FREE,#1
2771                     ; 1152 			UART1->CR2&= ~UART1_CR2_TIEN;
2773  097f 721f5235      	bres	21045,#7
2774  0983               L565:
2775                     ; 1156 if (tx_status & (UART1_SR_TC))
2777  0983 7b01          	ld	a,(OFST+0,sp)
2778  0985 a540          	bcp	a,#64
2779  0987 2708          	jreq	L575
2780                     ; 1158 	GPIOB->ODR&=~(1<<7);
2782  0989 721f5005      	bres	20485,#7
2783                     ; 1159 	UART1->SR&=~UART1_SR_TC;
2785  098d 721d5230      	bres	21040,#6
2786  0991               L575:
2787                     ; 1161 }
2790  0991 84            	pop	a
2791  0992 80            	iret
2845                     ; 1164 @far @interrupt void UART1RxInterrupt (void) 
2845                     ; 1165 {
2846                     	switch	.text
2847  0993               f_UART1RxInterrupt:
2849       00000003      OFST:	set	3
2850  0993 5203          	subw	sp,#3
2853                     ; 1168 rx_status=UART1->SR;
2855  0995 c65230        	ld	a,21040
2856  0998 6b02          	ld	(OFST-1,sp),a
2857                     ; 1169 rx_data=UART1->DR;
2859  099a c65231        	ld	a,21041
2860  099d 6b03          	ld	(OFST+0,sp),a
2861                     ; 1171 if (rx_status & (UART1_SR_RXNE))
2863  099f 7b02          	ld	a,(OFST-1,sp)
2864  09a1 a520          	bcp	a,#32
2865  09a3 2734          	jreq	L526
2866                     ; 1174 temp=rx_data;
2868                     ; 1175 rx_buffer[rs485_rx_cnt]=rx_data;
2870  09a5 7b03          	ld	a,(OFST+0,sp)
2871  09a7 be02          	ldw	x,_rs485_rx_cnt
2872  09a9 d7012c        	ld	(_rx_buffer,x),a
2873                     ; 1176 rs485_rx_cnt++;
2875  09ac be02          	ldw	x,_rs485_rx_cnt
2876  09ae 1c0001        	addw	x,#1
2877  09b1 bf02          	ldw	_rs485_rx_cnt,x
2878                     ; 1193 	if((rx_data==0x0d)&&(rs485_rx_cnt==20))
2880  09b3 7b03          	ld	a,(OFST+0,sp)
2881  09b5 a10d          	cp	a,#13
2882  09b7 2617          	jrne	L726
2884  09b9 be02          	ldw	x,_rs485_rx_cnt
2885  09bb a30014        	cpw	x,#20
2886  09be 2610          	jrne	L726
2887                     ; 1195 		if(rx_buffer[8]==0x32){
2889  09c0 c60134        	ld	a,_rx_buffer+8
2890  09c3 a132          	cp	a,#50
2891  09c5 2604          	jrne	L136
2892                     ; 1196 		bRX485=1;
2894  09c7 35010001      	mov	_bRX485,#1
2895  09cb               L136:
2896                     ; 1199 		if(rx_buffer[8]==0x33){
2898  09cb c60134        	ld	a,_rx_buffer+8
2899  09ce a133          	cp	a,#51
2900  09d0               L726:
2901                     ; 1203 	if(rx_data==0x0d)rs485_rx_cnt=0;	
2903  09d0 7b03          	ld	a,(OFST+0,sp)
2904  09d2 a10d          	cp	a,#13
2905  09d4 2603          	jrne	L526
2908  09d6 5f            	clrw	x
2909  09d7 bf02          	ldw	_rs485_rx_cnt,x
2910  09d9               L526:
2911                     ; 1208 }
2914  09d9 5b03          	addw	sp,#3
2915  09db 80            	iret
2951                     ; 1217 main()
2951                     ; 1218 {
2953                     	switch	.text
2954  09dc               _main:
2958                     ; 1219 CLK->ECKR|=1;
2960  09dc 721050c1      	bset	20673,#0
2962  09e0               L156:
2963                     ; 1220 while((CLK->ECKR & 2) == 0);
2965  09e0 c650c1        	ld	a,20673
2966  09e3 a502          	bcp	a,#2
2967  09e5 27f9          	jreq	L156
2968                     ; 1221 CLK->SWCR|=2;
2970  09e7 721250c5      	bset	20677,#1
2971                     ; 1222 CLK->SWR=0xB4;
2973  09eb 35b450c4      	mov	20676,#180
2974                     ; 1225 t4_init();
2976  09ef cd08b1        	call	_t4_init
2978                     ; 1227 		GPIOG->DDR|=(1<<0);
2980  09f2 72105020      	bset	20512,#0
2981                     ; 1228 		GPIOG->CR1|=(1<<0);
2983  09f6 72105021      	bset	20513,#0
2984                     ; 1229 		GPIOG->CR2&=~(1<<0);	
2986  09fa 72115022      	bres	20514,#0
2987                     ; 1232 		GPIOG->DDR&=~(1<<1);
2989  09fe 72135020      	bres	20512,#1
2990                     ; 1233 		GPIOG->CR1|=(1<<1);
2992  0a02 72125021      	bset	20513,#1
2993                     ; 1234 		GPIOG->CR2&=~(1<<1);
2995  0a06 72135022      	bres	20514,#1
2996                     ; 1236 init_CAN();
2998  0a0a cd0741        	call	_init_CAN
3000                     ; 1244 uart1_init();
3002  0a0d cd003c        	call	_uart1_init
3004                     ; 1246 adress=19;
3006  0a10 3513012d      	mov	_adress,#19
3007                     ; 1248 enableInterrupts();
3010  0a14 9a            rim
3012  0a15               L556:
3013                     ; 1252 	if(bRX485)
3015  0a15 3d01          	tnz	_bRX485
3016  0a17 2703          	jreq	L166
3017                     ; 1254 		rx485_in_an();
3019  0a19 cd01f6        	call	_rx485_in_an
3021  0a1c               L166:
3022                     ; 1257 	if(bCAN_RX)
3024  0a1c 3d07          	tnz	_bCAN_RX
3025  0a1e 2702          	jreq	L366
3026                     ; 1259 		bCAN_RX=0;
3028  0a20 3f07          	clr	_bCAN_RX
3029  0a22               L366:
3030                     ; 1266 	if(b100Hz)
3032                     	btst	_b100Hz
3033  0a27 2404          	jruge	L566
3034                     ; 1268 		b100Hz=0;
3036  0a29 72110006      	bres	_b100Hz
3037  0a2d               L566:
3038                     ; 1271 	if(b10Hz)
3040                     	btst	_b10Hz
3041  0a32 2404          	jruge	L766
3042                     ; 1273 		b10Hz=0;
3044  0a34 72110005      	bres	_b10Hz
3045  0a38               L766:
3046                     ; 1281 	if(b2Hz)
3048                     	btst	_b2Hz
3049  0a3d 2404          	jruge	L176
3050                     ; 1283 		b2Hz=0;
3052  0a3f 72110003      	bres	_b2Hz
3053  0a43               L176:
3054                     ; 1288 	if(b1Hz)
3056                     	btst	_b1Hz
3057  0a48 24cb          	jruge	L556
3058                     ; 1290 		b1Hz=0;
3060  0a4a 72110002      	bres	_b1Hz
3061                     ; 1297 		if(rs485_cnt>=10)
3063  0a4e b60a          	ld	a,_rs485_cnt
3064  0a50 a10a          	cp	a,#10
3065  0a52 25c1          	jrult	L556
3066                     ; 1299 			rs485_cnt=10;
3068  0a54 350a000a      	mov	_rs485_cnt,#10
3069                     ; 1300 			bRS485ERR=1;
3071  0a58 72100000      	bset	_bRS485ERR
3072  0a5c 20b7          	jra	L556
3632                     	xdef	_main
3633                     	xdef	f_UART1RxInterrupt
3634                     	xdef	f_UART1TxInterrupt
3635                     	xdef	f_CAN_TX_Interrupt
3636                     	xdef	f_CAN_RX_Interrupt
3637                     	xdef	f_TIM4_UPD_Interrupt
3638                     	xdef	_t4_init
3639                     	xdef	_can_in_an
3640                     	xdef	_can_tx_hndl
3641                     	xdef	_can_transmit
3642                     	xdef	_init_CAN
3643                     	xdef	_rx485_in_an
3644                     	xdef	_str2int
3645                     	xdef	_uart1_out_adr
3646                     	xdef	_putchar1
3647                     	xdef	_uart1_init
3648                     	xdef	_gran
3649                     	xdef	_gran_char
3650                     	switch	.ubsct
3651  0000               _transmit_cnt_number:
3652  0000 00            	ds.b	1
3653                     	xdef	_transmit_cnt_number
3654                     .bit:	section	.data,bit
3655  0000               _bRS485ERR:
3656  0000 00            	ds.b	1
3657                     	xdef	_bRS485ERR
3658                     	xdef	_rs485_cnt
3659                     	switch	.ubsct
3660  0001               _bRX485:
3661  0001 00            	ds.b	1
3662                     	xdef	_bRX485
3663  0002               _rs485_rx_cnt:
3664  0002 0000          	ds.b	2
3665                     	xdef	_rs485_rx_cnt
3666  0004               _plazma_int:
3667  0004 000000000000  	ds.b	6
3668                     	xdef	_plazma_int
3669  000a               _link_cnt:
3670  000a 00            	ds.b	1
3671                     	xdef	_link_cnt
3672  000b               _link:
3673  000b 00            	ds.b	1
3674                     	xdef	_link
3675                     	switch	.bss
3676  0000               _rs485_out_buff:
3677  0000 000000000000  	ds.b	300
3678                     	xdef	_rs485_out_buff
3679  012c               _adress_error:
3680  012c 00            	ds.b	1
3681                     	xdef	_adress_error
3682  012d               _adress:
3683  012d 00            	ds.b	1
3684                     	xdef	_adress
3685  012e               _adr:
3686  012e 000000        	ds.b	3
3687                     	xdef	_adr
3688                     	xdef	_adr_drv_stat
3689                     	xdef	_led_ind
3690                     	switch	.ubsct
3691  000c               _led_ind_cnt:
3692  000c 00            	ds.b	1
3693                     	xdef	_led_ind_cnt
3694  000d               _adc_plazma:
3695  000d 000000000000  	ds.b	10
3696                     	xdef	_adc_plazma
3697  0017               _adc_plazma_short:
3698  0017 0000          	ds.b	2
3699                     	xdef	_adc_plazma_short
3700  0019               _adc_cnt:
3701  0019 00            	ds.b	1
3702                     	xdef	_adc_cnt
3703  001a               _adc_ch:
3704  001a 00            	ds.b	1
3705                     	xdef	_adc_ch
3706                     	switch	.bss
3707  0131               _adc_buff_:
3708  0131 000000000000  	ds.b	20
3709                     	xdef	_adc_buff_
3710  0145               _adc_buff:
3711  0145 000000000000  	ds.b	320
3712                     	xdef	_adc_buff
3713                     	switch	.ubsct
3714  001b               _T:
3715  001b 00            	ds.b	1
3716                     	xdef	_T
3717  001c               _Udb:
3718  001c 0000          	ds.b	2
3719                     	xdef	_Udb
3720  001e               _Ui:
3721  001e 0000          	ds.b	2
3722                     	xdef	_Ui
3723  0020               _Un:
3724  0020 0000          	ds.b	2
3725                     	xdef	_Un
3726  0022               _I:
3727  0022 0000          	ds.b	2
3728                     	xdef	_I
3729  0024               _can_error_cnt:
3730  0024 00            	ds.b	1
3731                     	xdef	_can_error_cnt
3732                     	xdef	_bCAN_RX
3733  0025               _tx_busy_cnt:
3734  0025 00            	ds.b	1
3735                     	xdef	_tx_busy_cnt
3736                     	xdef	_bTX_FREE
3737  0026               _can_buff_rd_ptr:
3738  0026 00            	ds.b	1
3739                     	xdef	_can_buff_rd_ptr
3740  0027               _can_buff_wr_ptr:
3741  0027 00            	ds.b	1
3742                     	xdef	_can_buff_wr_ptr
3743  0028               _can_out_buff:
3744  0028 000000000000  	ds.b	96
3745                     	xdef	_can_out_buff
3746  0088               _bOUT_FREE:
3747  0088 00            	ds.b	1
3748                     	xdef	_bOUT_FREE
3749                     	switch	.bss
3750  0285               _tx_stat_cnt:
3751  0285 00            	ds.b	1
3752                     	xdef	_tx_stat_cnt
3753                     	switch	.ubsct
3754  0089               _rx_rd_index1:
3755  0089 0000          	ds.b	2
3756                     	xdef	_rx_rd_index1
3757  008b               _rx_wr_index1:
3758  008b 0000          	ds.b	2
3759                     	xdef	_rx_wr_index1
3760  008d               _rx_counter1:
3761  008d 0000          	ds.b	2
3762                     	xdef	_rx_counter1
3763                     	xdef	_rx_buffer
3764  008f               _tx_rd_index1:
3765  008f 0000          	ds.b	2
3766                     	xdef	_tx_rd_index1
3767  0091               _tx_wr_index1:
3768  0091 0000          	ds.b	2
3769                     	xdef	_tx_wr_index1
3770  0093               _tx_counter1:
3771  0093 0000          	ds.b	2
3772                     	xdef	_tx_counter1
3773                     	xdef	_tx_buffer1
3774  0095               _mess:
3775  0095 000000000000  	ds.b	14
3776                     	xdef	_mess
3777                     	switch	.bit
3778  0001               _bBAT_REQ:
3779  0001 00            	ds.b	1
3780                     	xdef	_bBAT_REQ
3781  0002               _b1Hz:
3782  0002 00            	ds.b	1
3783                     	xdef	_b1Hz
3784  0003               _b2Hz:
3785  0003 00            	ds.b	1
3786                     	xdef	_b2Hz
3787  0004               _b5Hz:
3788  0004 00            	ds.b	1
3789                     	xdef	_b5Hz
3790  0005               _b10Hz:
3791  0005 00            	ds.b	1
3792                     	xdef	_b10Hz
3793  0006               _b100Hz:
3794  0006 00            	ds.b	1
3795                     	xdef	_b100Hz
3796                     	xdef	_t0_cnt4
3797                     	xdef	_t0_cnt3
3798                     	xdef	_t0_cnt2
3799                     	xdef	_t0_cnt1
3800                     	xdef	_t0_cnt0
3801                     	xref	_pow
3802                     	xref	_isalnum
3803                     	xdef	_tx_stat
3804                     	switch	.const
3805  000a               L772:
3806  000a 41800000      	dc.w	16768,0
3807                     	xref.b	c_lreg
3808                     	xref.b	c_x
3828                     	xref	c_imul
3829                     	xref	c_ftoi
3830                     	xref	c_itof
3831                     	xref	c_xymvx
3832                     	end
