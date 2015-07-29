   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2172                     	bsct
2173  0000               _t0_cnt0:
2174  0000 00            	dc.b	0
2175  0001               _t0_cnt1:
2176  0001 00            	dc.b	0
2177  0002               _t0_cnt2:
2178  0002 00            	dc.b	0
2179  0003               _t0_cnt3:
2180  0003 00            	dc.b	0
2181  0004               _t0_cnt4:
2182  0004 00            	dc.b	0
2183                     .const:	section	.text
2184  0000               _DIGISYM:
2185  0000 c0            	dc.b	192
2186  0001 f9            	dc.b	249
2187  0002 a4            	dc.b	164
2188  0003 b0            	dc.b	176
2189  0004 99            	dc.b	153
2190  0005 92            	dc.b	146
2191  0006 82            	dc.b	130
2192  0007 f8            	dc.b	248
2193  0008 80            	dc.b	128
2194  0009 90            	dc.b	144
2195  000a ff            	dc.b	255
2196  000b ff            	dc.b	255
2197  000c ff            	dc.b	255
2198  000d ff            	dc.b	255
2199  000e ff            	dc.b	255
2200                     	bsct
2201  0005               _dig1:
2202  0005 ff            	dc.b	255
2203  0006 ff            	dc.b	255
2204  0007 ff            	dc.b	255
2205  0008 ff            	dc.b	255
2206  0009 00000000      	ds.b	4
2207  000d               _dig2:
2208  000d ff            	dc.b	255
2209  000e ff            	dc.b	255
2210  000f ff            	dc.b	255
2211  0010 ff            	dc.b	255
2212  0011 00000000      	ds.b	4
2213  0015               _dig3:
2214  0015 ff            	dc.b	255
2215  0016 ff            	dc.b	255
2216  0017 ff            	dc.b	255
2217  0018 ff            	dc.b	255
2218  0019 00000000      	ds.b	4
2219  001d               _dig1_:
2220  001d ff            	dc.b	255
2221  001e ff            	dc.b	255
2222  001f ff            	dc.b	255
2223  0020 ff            	dc.b	255
2224  0021 00000000      	ds.b	4
2225  0025               _dig2_:
2226  0025 ff            	dc.b	255
2227  0026 ff            	dc.b	255
2228  0027 ff            	dc.b	255
2229  0028 ff            	dc.b	255
2230  0029 00000000      	ds.b	4
2231  002d               _dig3_:
2232  002d ff            	dc.b	255
2233  002e ff            	dc.b	255
2234  002f ff            	dc.b	255
2235  0030 ff            	dc.b	255
2236  0031 00000000      	ds.b	4
2237  0035               _bTX_FREE:
2238  0035 01            	dc.b	1
2239  0036               _bCAN_RX:
2240  0036 00            	dc.b	0
2241  0037               _ch_en:
2242  0037 00            	dc.b	0
2243  0038               _work_stat:
2244  0038 00            	dc.b	0
2311                     ; 104 long delay_ms(short in)
2311                     ; 105 {
2313                     	switch	.text
2314  0000               _delay_ms:
2316  0000 520c          	subw	sp,#12
2317       0000000c      OFST:	set	12
2320                     ; 108 i=((long)in)*100UL;
2322  0002 90ae0064      	ldw	y,#100
2323  0006 cd0000        	call	c_vmul
2325  0009 96            	ldw	x,sp
2326  000a 1c0005        	addw	x,#OFST-7
2327  000d cd0000        	call	c_rtol
2329                     ; 110 for(ii=0;ii<i;ii++)
2331  0010 ae0000        	ldw	x,#0
2332  0013 1f0b          	ldw	(OFST-1,sp),x
2333  0015 ae0000        	ldw	x,#0
2334  0018 1f09          	ldw	(OFST-3,sp),x
2336  001a 2012          	jra	L7641
2337  001c               L3641:
2338                     ; 112 		iii++;
2340  001c 96            	ldw	x,sp
2341  001d 1c0001        	addw	x,#OFST-11
2342  0020 a601          	ld	a,#1
2343  0022 cd0000        	call	c_lgadc
2345                     ; 110 for(ii=0;ii<i;ii++)
2347  0025 96            	ldw	x,sp
2348  0026 1c0009        	addw	x,#OFST-3
2349  0029 a601          	ld	a,#1
2350  002b cd0000        	call	c_lgadc
2352  002e               L7641:
2355  002e 9c            	rvf
2356  002f 96            	ldw	x,sp
2357  0030 1c0009        	addw	x,#OFST-3
2358  0033 cd0000        	call	c_ltor
2360  0036 96            	ldw	x,sp
2361  0037 1c0005        	addw	x,#OFST-7
2362  003a cd0000        	call	c_lcmp
2364  003d 2fdd          	jrslt	L3641
2365                     ; 115 }
2368  003f 5b0c          	addw	sp,#12
2369  0041 81            	ret
2392                     ; 118 void spi_init(void){
2393                     	switch	.text
2394  0042               _spi_init:
2398                     ; 120 	GPIOE->DDR|=(1<<5);
2400  0042 721a5016      	bset	20502,#5
2401                     ; 121 	GPIOE->CR1|=(1<<5);
2403  0046 721a5017      	bset	20503,#5
2404                     ; 122 	GPIOE->CR2&=~(1<<5);
2406  004a 721b5018      	bres	20504,#5
2407                     ; 123 	GPIOE->ODR|=(1<<5);	
2409  004e 721a5014      	bset	20500,#5
2410                     ; 125 	GPIOC->DDR|=(1<<3);
2412  0052 7216500c      	bset	20492,#3
2413                     ; 126 	GPIOC->CR1|=(1<<3);
2415  0056 7216500d      	bset	20493,#3
2416                     ; 127 	GPIOC->CR2&=~(1<<3);
2418  005a 7217500e      	bres	20494,#3
2419                     ; 128 	GPIOC->ODR|=(1<<3);	
2421  005e 7216500a      	bset	20490,#3
2422                     ; 130 	GPIOC->DDR|=(1<<2);
2424  0062 7214500c      	bset	20492,#2
2425                     ; 131 	GPIOC->CR1|=(1<<2);
2427  0066 7214500d      	bset	20493,#2
2428                     ; 132 	GPIOC->CR2&=~(1<<2);
2430  006a 7215500e      	bres	20494,#2
2431                     ; 133 	GPIOC->ODR|=(1<<2);		
2433  006e 7214500a      	bset	20490,#2
2434                     ; 135 	GPIOC->DDR|=(1<<5);
2436  0072 721a500c      	bset	20492,#5
2437                     ; 136 	GPIOC->CR1|=(1<<5);
2439  0076 721a500d      	bset	20493,#5
2440                     ; 137 	GPIOC->CR2|=(1<<5);
2442  007a 721a500e      	bset	20494,#5
2443                     ; 138 	GPIOC->ODR|=(1<<5);	
2445  007e 721a500a      	bset	20490,#5
2446                     ; 140 	GPIOC->DDR|=(1<<6);
2448  0082 721c500c      	bset	20492,#6
2449                     ; 141 	GPIOC->CR1|=(1<<6);
2451  0086 721c500d      	bset	20493,#6
2452                     ; 142 	GPIOC->CR2|=(1<<6);
2454  008a 721c500e      	bset	20494,#6
2455                     ; 143 	GPIOC->ODR|=(1<<6);	
2457  008e 721c500a      	bset	20490,#6
2458                     ; 150 	SPI->CR1= /*SPI_CR1_LSBFIRST |*/
2458                     ; 151 			SPI_CR1_SPE | 
2458                     ; 152 			( (0<< 3) & SPI_CR1_BR ) |
2458                     ; 153 			SPI_CR1_MSTR |
2458                     ; 154 			SPI_CR1_CPOL |
2458                     ; 155 			SPI_CR1_CPHA; 
2460  0092 35475200      	mov	20992,#71
2461                     ; 157 	SPI->CR2= SPI_CR2_SSM | SPI_CR2_SSI;
2463  0096 35035201      	mov	20993,#3
2464                     ; 158 	SPI->ICR= 0;	
2466  009a 725f5202      	clr	20994
2467                     ; 159 }
2470  009e 81            	ret
2513                     ; 162 char spi(char in){
2514                     	switch	.text
2515  009f               _spi:
2517  009f 88            	push	a
2518  00a0 88            	push	a
2519       00000001      OFST:	set	1
2522  00a1               L7251:
2523                     ; 164 	while(!((SPI->SR)&SPI_SR_TXE));
2525  00a1 c65203        	ld	a,20995
2526  00a4 a502          	bcp	a,#2
2527  00a6 27f9          	jreq	L7251
2528                     ; 165 	SPI->DR=in;
2530  00a8 7b02          	ld	a,(OFST+1,sp)
2531  00aa c75204        	ld	20996,a
2533  00ad               L7351:
2534                     ; 166 	while(!((SPI->SR)&SPI_SR_RXNE));
2536  00ad c65203        	ld	a,20995
2537  00b0 a501          	bcp	a,#1
2538  00b2 27f9          	jreq	L7351
2539                     ; 167 	c=SPI->DR;	
2541  00b4 c65204        	ld	a,20996
2542  00b7 6b01          	ld	(OFST+0,sp),a
2543                     ; 168 	return c;
2545  00b9 7b01          	ld	a,(OFST+0,sp)
2548  00bb 85            	popw	x
2549  00bc 81            	ret
2593                     ; 172 void bin2bcd_int(unsigned int in)
2593                     ; 173 {
2594                     	switch	.text
2595  00bd               _bin2bcd_int:
2597  00bd 89            	pushw	x
2598  00be 88            	push	a
2599       00000001      OFST:	set	1
2602                     ; 175 char i=5;
2604                     ; 176 for(i=0;i<5;i++)
2606  00bf 0f01          	clr	(OFST+0,sp)
2607  00c1               L5651:
2608                     ; 178 	dig[i]=in%10;
2610  00c1 1e02          	ldw	x,(OFST+1,sp)
2611  00c3 90ae000a      	ldw	y,#10
2612  00c7 65            	divw	x,y
2613  00c8 51            	exgw	x,y
2614  00c9 7b01          	ld	a,(OFST+0,sp)
2615  00cb 905f          	clrw	y
2616  00cd 9097          	ld	yl,a
2617  00cf 01            	rrwa	x,a
2618  00d0 90e77b        	ld	(_dig,y),a
2619  00d3 02            	rlwa	x,a
2620                     ; 179 	in/=10;
2622  00d4 1e02          	ldw	x,(OFST+1,sp)
2623  00d6 90ae000a      	ldw	y,#10
2624  00da 65            	divw	x,y
2625  00db 1f02          	ldw	(OFST+1,sp),x
2626                     ; 176 for(i=0;i<5;i++)
2628  00dd 0c01          	inc	(OFST+0,sp)
2631  00df 7b01          	ld	a,(OFST+0,sp)
2632  00e1 a105          	cp	a,#5
2633  00e3 25dc          	jrult	L5651
2634                     ; 181 }
2637  00e5 5b03          	addw	sp,#3
2638  00e7 81            	ret
2676                     ; 184 void bcd2ind_zero()
2676                     ; 185 {
2677                     	switch	.text
2678  00e8               _bcd2ind_zero:
2680  00e8 88            	push	a
2681       00000001      OFST:	set	1
2684                     ; 187 zero_on=1;
2686  00e9 3501007a      	mov	_zero_on,#1
2687                     ; 188 for (i=4;i>0;i--)
2689  00ed a604          	ld	a,#4
2690  00ef 6b01          	ld	(OFST+0,sp),a
2691  00f1               L1161:
2692                     ; 190 	if(zero_on&&(!dig[i-1])&&(i-1))
2694  00f1 3d7a          	tnz	_zero_on
2695  00f3 271e          	jreq	L7161
2697  00f5 7b01          	ld	a,(OFST+0,sp)
2698  00f7 5f            	clrw	x
2699  00f8 97            	ld	xl,a
2700  00f9 5a            	decw	x
2701  00fa 6d7b          	tnz	(_dig,x)
2702  00fc 2615          	jrne	L7161
2704  00fe 7b01          	ld	a,(OFST+0,sp)
2705  0100 5f            	clrw	x
2706  0101 97            	ld	xl,a
2707  0102 5a            	decw	x
2708  0103 a30000        	cpw	x,#0
2709  0106 270b          	jreq	L7161
2710                     ; 192 		ind_out_[i-1]=DIGISYM[10];
2712  0108 7b01          	ld	a,(OFST+0,sp)
2713  010a 5f            	clrw	x
2714  010b 97            	ld	xl,a
2715  010c 5a            	decw	x
2716  010d a6ff          	ld	a,#255
2717  010f e775          	ld	(_ind_out_,x),a
2719  0111 201c          	jra	L1261
2720  0113               L7161:
2721                     ; 196 		ind_out_[i-1]=DIGISYM[dig[i-1]];
2723  0113 7b01          	ld	a,(OFST+0,sp)
2724  0115 5f            	clrw	x
2725  0116 97            	ld	xl,a
2726  0117 5a            	decw	x
2727  0118 7b01          	ld	a,(OFST+0,sp)
2728  011a 905f          	clrw	y
2729  011c 9097          	ld	yl,a
2730  011e 905a          	decw	y
2731  0120 90e67b        	ld	a,(_dig,y)
2732  0123 905f          	clrw	y
2733  0125 9097          	ld	yl,a
2734  0127 90d60000      	ld	a,(_DIGISYM,y)
2735  012b e775          	ld	(_ind_out_,x),a
2736                     ; 197 		zero_on=0;
2738  012d 3f7a          	clr	_zero_on
2739  012f               L1261:
2740                     ; 188 for (i=4;i>0;i--)
2742  012f 0a01          	dec	(OFST+0,sp)
2745  0131 0d01          	tnz	(OFST+0,sp)
2746  0133 26bc          	jrne	L1161
2747                     ; 200 }
2750  0135 84            	pop	a
2751  0136 81            	ret
2788                     ; 203 void bcd2ind()
2788                     ; 204 {
2789                     	switch	.text
2790  0137               _bcd2ind:
2792  0137 88            	push	a
2793       00000001      OFST:	set	1
2796                     ; 207 for (i=4;i>0;i--)
2798  0138 a604          	ld	a,#4
2799  013a 6b01          	ld	(OFST+0,sp),a
2800  013c               L1461:
2801                     ; 209 	ind_out_[i-1]=DIGISYM[dig[i-1]];
2803  013c 7b01          	ld	a,(OFST+0,sp)
2804  013e 5f            	clrw	x
2805  013f 97            	ld	xl,a
2806  0140 5a            	decw	x
2807  0141 7b01          	ld	a,(OFST+0,sp)
2808  0143 905f          	clrw	y
2809  0145 9097          	ld	yl,a
2810  0147 905a          	decw	y
2811  0149 90e67b        	ld	a,(_dig,y)
2812  014c 905f          	clrw	y
2813  014e 9097          	ld	yl,a
2814  0150 90d60000      	ld	a,(_DIGISYM,y)
2815  0154 e775          	ld	(_ind_out_,x),a
2816                     ; 207 for (i=4;i>0;i--)
2818  0156 0a01          	dec	(OFST+0,sp)
2821  0158 0d01          	tnz	(OFST+0,sp)
2822  015a 26e0          	jrne	L1461
2823                     ; 211 }
2826  015c 84            	pop	a
2827  015d 81            	ret
2932                     ; 214 void int2ind_slkuf1(unsigned short in, char start, char len, char komma, char unzero, char fl, char fad)
2932                     ; 215 {
2933                     	switch	.text
2934  015e               _int2ind_slkuf1:
2936  015e 89            	pushw	x
2937  015f 88            	push	a
2938       00000001      OFST:	set	1
2941                     ; 218 bin2bcd_int(in);
2943  0160 cd00bd        	call	_bin2bcd_int
2945                     ; 219 if(unzero)bcd2ind_zero();
2947  0163 0d09          	tnz	(OFST+8,sp)
2948  0165 2705          	jreq	L1271
2951  0167 cd00e8        	call	_bcd2ind_zero
2954  016a 2002          	jra	L3271
2955  016c               L1271:
2956                     ; 220 else bcd2ind();
2958  016c adc9          	call	_bcd2ind
2960  016e               L3271:
2961                     ; 221 if(komma)
2963  016e 0d08          	tnz	(OFST+7,sp)
2964  0170 271c          	jreq	L5271
2965                     ; 223 	if(ind_out_[komma]==DIGISYM[10])ind_out_[komma]=DIGISYM[0];
2967  0172 7b08          	ld	a,(OFST+7,sp)
2968  0174 5f            	clrw	x
2969  0175 97            	ld	xl,a
2970  0176 e675          	ld	a,(_ind_out_,x)
2971  0178 a1ff          	cp	a,#255
2972  017a 2608          	jrne	L7271
2975  017c 7b08          	ld	a,(OFST+7,sp)
2976  017e 5f            	clrw	x
2977  017f 97            	ld	xl,a
2978  0180 a6c0          	ld	a,#192
2979  0182 e775          	ld	(_ind_out_,x),a
2980  0184               L7271:
2981                     ; 224 	ind_out_[komma]&=0b01111111;
2983  0184 7b08          	ld	a,(OFST+7,sp)
2984  0186 5f            	clrw	x
2985  0187 97            	ld	xl,a
2986  0188 e675          	ld	a,(_ind_out_,x)
2987  018a a47f          	and	a,#127
2988  018c e775          	ld	(_ind_out_,x),a
2989  018e               L5271:
2990                     ; 226 if(fl&&bFL5)
2992  018e 0d0a          	tnz	(OFST+9,sp)
2993  0190 2718          	jreq	L1371
2995  0192 3d6f          	tnz	_bFL5
2996  0194 2714          	jreq	L1371
2997                     ; 228 	for(i=0;i<len;i++)
2999  0196 0f01          	clr	(OFST+0,sp)
3001  0198 200a          	jra	L7371
3002  019a               L3371:
3003                     ; 230 		ind_out_[i]=DIGISYM[10];
3005  019a 7b01          	ld	a,(OFST+0,sp)
3006  019c 5f            	clrw	x
3007  019d 97            	ld	xl,a
3008  019e a6ff          	ld	a,#255
3009  01a0 e775          	ld	(_ind_out_,x),a
3010                     ; 228 	for(i=0;i<len;i++)
3012  01a2 0c01          	inc	(OFST+0,sp)
3013  01a4               L7371:
3016  01a4 7b01          	ld	a,(OFST+0,sp)
3017  01a6 1107          	cp	a,(OFST+6,sp)
3018  01a8 25f0          	jrult	L3371
3019  01aa               L1371:
3020                     ; 234 for(i=0;i<len;i++)
3022  01aa 0f01          	clr	(OFST+0,sp)
3024  01ac 2016          	jra	L7471
3025  01ae               L3471:
3026                     ; 236 		dig1[start+i]=ind_out_[i];
3028  01ae 7b06          	ld	a,(OFST+5,sp)
3029  01b0 5f            	clrw	x
3030  01b1 1b01          	add	a,(OFST+0,sp)
3031  01b3 2401          	jrnc	L22
3032  01b5 5c            	incw	x
3033  01b6               L22:
3034  01b6 02            	rlwa	x,a
3035  01b7 7b01          	ld	a,(OFST+0,sp)
3036  01b9 905f          	clrw	y
3037  01bb 9097          	ld	yl,a
3038  01bd 90e675        	ld	a,(_ind_out_,y)
3039  01c0 e705          	ld	(_dig1,x),a
3040                     ; 234 for(i=0;i<len;i++)
3042  01c2 0c01          	inc	(OFST+0,sp)
3043  01c4               L7471:
3046  01c4 7b01          	ld	a,(OFST+0,sp)
3047  01c6 1107          	cp	a,(OFST+6,sp)
3048  01c8 25e4          	jrult	L3471
3049                     ; 238 if(len==0)
3051  01ca 0d07          	tnz	(OFST+6,sp)
3052  01cc 2610          	jrne	L3571
3053                     ; 240 	dig1[0]=0xff;
3055  01ce 35ff0005      	mov	_dig1,#255
3056                     ; 241 	dig1[1]=0xff;
3058  01d2 35ff0006      	mov	_dig1+1,#255
3059                     ; 242 	dig1[2]=0xff;
3061  01d6 35ff0007      	mov	_dig1+2,#255
3062                     ; 243 	dig1[3]=0xff;
3064  01da 35ff0008      	mov	_dig1+3,#255
3065  01de               L3571:
3066                     ; 245 dig1_[0]=dig1[0];
3068  01de 45051d        	mov	_dig1_,_dig1
3069                     ; 246 dig1_[1]=dig1[1];
3071  01e1 45061e        	mov	_dig1_+1,_dig1+1
3072                     ; 247 dig1_[2]=dig1[2];
3074  01e4 45071f        	mov	_dig1_+2,_dig1+2
3075                     ; 248 dig1_[3]=dig1[3];
3077  01e7 450820        	mov	_dig1_+3,_dig1+3
3078                     ; 249 if(fad)
3080  01ea 0d0b          	tnz	(OFST+10,sp)
3081  01ec 2710          	jreq	L5571
3082                     ; 251 	dig1[0]=0xff;
3084  01ee 35ff0005      	mov	_dig1,#255
3085                     ; 252 	dig1[1]=0xff;
3087  01f2 35ff0006      	mov	_dig1+1,#255
3088                     ; 253 	dig1[2]=0xff;
3090  01f6 35ff0007      	mov	_dig1+2,#255
3091                     ; 254 	dig1[3]=0xff;
3093  01fa 35ff0008      	mov	_dig1+3,#255
3094  01fe               L5571:
3095                     ; 256 }
3098  01fe 5b03          	addw	sp,#3
3099  0200 81            	ret
3204                     ; 259 void int2ind_slkuf2(unsigned short in, char start, char len, char komma, char unzero, char fl, char fad)
3204                     ; 260 {
3205                     	switch	.text
3206  0201               _int2ind_slkuf2:
3208  0201 89            	pushw	x
3209  0202 88            	push	a
3210       00000001      OFST:	set	1
3213                     ; 263 	dig2[0]=0xff;
3215  0203 35ff000d      	mov	_dig2,#255
3216                     ; 264 	dig2[1]=0xff;
3218  0207 35ff000e      	mov	_dig2+1,#255
3219                     ; 265 	dig2[2]=0xff;
3221  020b 35ff000f      	mov	_dig2+2,#255
3222                     ; 266 	dig2[3]=0xff;
3224  020f 35ff0010      	mov	_dig2+3,#255
3225                     ; 267 	dig2_[0]=0xff;
3227  0213 35ff0025      	mov	_dig2_,#255
3228                     ; 268 	dig2_[1]=0xff;
3230  0217 35ff0026      	mov	_dig2_+1,#255
3231                     ; 269 	dig2_[2]=0xff;
3233  021b 35ff0027      	mov	_dig2_+2,#255
3234                     ; 270 	dig2_[3]=0xff;
3236  021f 35ff0028      	mov	_dig2_+3,#255
3237                     ; 271 bin2bcd_int(in);
3239  0223 cd00bd        	call	_bin2bcd_int
3241                     ; 272 if(unzero)bcd2ind_zero();
3243  0226 0d09          	tnz	(OFST+8,sp)
3244  0228 2705          	jreq	L1302
3247  022a cd00e8        	call	_bcd2ind_zero
3250  022d 2003          	jra	L3302
3251  022f               L1302:
3252                     ; 273 else bcd2ind();
3254  022f cd0137        	call	_bcd2ind
3256  0232               L3302:
3257                     ; 274 if(komma)
3259  0232 0d08          	tnz	(OFST+7,sp)
3260  0234 271c          	jreq	L5302
3261                     ; 276 	if(ind_out_[komma]==DIGISYM[10])ind_out_[komma]=DIGISYM[0];
3263  0236 7b08          	ld	a,(OFST+7,sp)
3264  0238 5f            	clrw	x
3265  0239 97            	ld	xl,a
3266  023a e675          	ld	a,(_ind_out_,x)
3267  023c a1ff          	cp	a,#255
3268  023e 2608          	jrne	L7302
3271  0240 7b08          	ld	a,(OFST+7,sp)
3272  0242 5f            	clrw	x
3273  0243 97            	ld	xl,a
3274  0244 a6c0          	ld	a,#192
3275  0246 e775          	ld	(_ind_out_,x),a
3276  0248               L7302:
3277                     ; 277 	ind_out_[komma]&=0b01111111;
3279  0248 7b08          	ld	a,(OFST+7,sp)
3280  024a 5f            	clrw	x
3281  024b 97            	ld	xl,a
3282  024c e675          	ld	a,(_ind_out_,x)
3283  024e a47f          	and	a,#127
3284  0250 e775          	ld	(_ind_out_,x),a
3285  0252               L5302:
3286                     ; 279 if(fl&&bFL5)
3288  0252 0d0a          	tnz	(OFST+9,sp)
3289  0254 2718          	jreq	L1402
3291  0256 3d6f          	tnz	_bFL5
3292  0258 2714          	jreq	L1402
3293                     ; 281 	for(i=0;i<len;i++)
3295  025a 0f01          	clr	(OFST+0,sp)
3297  025c 200a          	jra	L7402
3298  025e               L3402:
3299                     ; 283 		ind_out_[i]=DIGISYM[10];
3301  025e 7b01          	ld	a,(OFST+0,sp)
3302  0260 5f            	clrw	x
3303  0261 97            	ld	xl,a
3304  0262 a6ff          	ld	a,#255
3305  0264 e775          	ld	(_ind_out_,x),a
3306                     ; 281 	for(i=0;i<len;i++)
3308  0266 0c01          	inc	(OFST+0,sp)
3309  0268               L7402:
3312  0268 7b01          	ld	a,(OFST+0,sp)
3313  026a 1107          	cp	a,(OFST+6,sp)
3314  026c 25f0          	jrult	L3402
3315  026e               L1402:
3316                     ; 287 for(i=0;i<len;i++)
3318  026e 0f01          	clr	(OFST+0,sp)
3320  0270 2016          	jra	L7502
3321  0272               L3502:
3322                     ; 289 		dig2[start+i]=ind_out_[i];
3324  0272 7b06          	ld	a,(OFST+5,sp)
3325  0274 5f            	clrw	x
3326  0275 1b01          	add	a,(OFST+0,sp)
3327  0277 2401          	jrnc	L62
3328  0279 5c            	incw	x
3329  027a               L62:
3330  027a 02            	rlwa	x,a
3331  027b 7b01          	ld	a,(OFST+0,sp)
3332  027d 905f          	clrw	y
3333  027f 9097          	ld	yl,a
3334  0281 90e675        	ld	a,(_ind_out_,y)
3335  0284 e70d          	ld	(_dig2,x),a
3336                     ; 287 for(i=0;i<len;i++)
3338  0286 0c01          	inc	(OFST+0,sp)
3339  0288               L7502:
3342  0288 7b01          	ld	a,(OFST+0,sp)
3343  028a 1107          	cp	a,(OFST+6,sp)
3344  028c 25e4          	jrult	L3502
3345                     ; 291 if(len==0)
3347  028e 0d07          	tnz	(OFST+6,sp)
3348  0290 2610          	jrne	L3602
3349                     ; 293 	dig2[0]=0xff;
3351  0292 35ff000d      	mov	_dig2,#255
3352                     ; 294 	dig2[1]=0xff;
3354  0296 35ff000e      	mov	_dig2+1,#255
3355                     ; 295 	dig2[2]=0xff;
3357  029a 35ff000f      	mov	_dig2+2,#255
3358                     ; 296 	dig2[3]=0xff;
3360  029e 35ff0010      	mov	_dig2+3,#255
3361  02a2               L3602:
3362                     ; 298 dig2_[0]=dig2[0];
3364  02a2 450d25        	mov	_dig2_,_dig2
3365                     ; 299 dig2_[1]=dig2[1];
3367  02a5 450e26        	mov	_dig2_+1,_dig2+1
3368                     ; 300 dig2_[2]=dig2[2];
3370  02a8 450f27        	mov	_dig2_+2,_dig2+2
3371                     ; 301 dig2_[3]=dig2[3];
3373  02ab 451028        	mov	_dig2_+3,_dig2+3
3374                     ; 302 if(fad)
3376  02ae 0d0b          	tnz	(OFST+10,sp)
3377  02b0 2710          	jreq	L5602
3378                     ; 304 	dig2[0]=0xff;
3380  02b2 35ff000d      	mov	_dig2,#255
3381                     ; 305 	dig2[1]=0xff;
3383  02b6 35ff000e      	mov	_dig2+1,#255
3384                     ; 306 	dig2[2]=0xff;
3386  02ba 35ff000f      	mov	_dig2+2,#255
3387                     ; 307 	dig2[3]=0xff;
3389  02be 35ff0010      	mov	_dig2+3,#255
3390  02c2               L5602:
3391                     ; 309 }
3394  02c2 5b03          	addw	sp,#3
3395  02c4 81            	ret
3500                     ; 311 void int2ind_slkuf3(unsigned short in, char start, char len, char komma, char unzero, char fl, char fad)
3500                     ; 312 {
3501                     	switch	.text
3502  02c5               _int2ind_slkuf3:
3504  02c5 89            	pushw	x
3505  02c6 88            	push	a
3506       00000001      OFST:	set	1
3509                     ; 315 bin2bcd_int(in);
3511  02c7 cd00bd        	call	_bin2bcd_int
3513                     ; 316 if(unzero)bcd2ind_zero();
3515  02ca 0d09          	tnz	(OFST+8,sp)
3516  02cc 2705          	jreq	L1412
3519  02ce cd00e8        	call	_bcd2ind_zero
3522  02d1 2003          	jra	L3412
3523  02d3               L1412:
3524                     ; 317 else bcd2ind();
3526  02d3 cd0137        	call	_bcd2ind
3528  02d6               L3412:
3529                     ; 318 if(komma)
3531  02d6 0d08          	tnz	(OFST+7,sp)
3532  02d8 271c          	jreq	L5412
3533                     ; 320 	if(ind_out_[komma]==DIGISYM[10])ind_out_[komma]=DIGISYM[0];
3535  02da 7b08          	ld	a,(OFST+7,sp)
3536  02dc 5f            	clrw	x
3537  02dd 97            	ld	xl,a
3538  02de e675          	ld	a,(_ind_out_,x)
3539  02e0 a1ff          	cp	a,#255
3540  02e2 2608          	jrne	L7412
3543  02e4 7b08          	ld	a,(OFST+7,sp)
3544  02e6 5f            	clrw	x
3545  02e7 97            	ld	xl,a
3546  02e8 a6c0          	ld	a,#192
3547  02ea e775          	ld	(_ind_out_,x),a
3548  02ec               L7412:
3549                     ; 321 	ind_out_[komma]&=0b01111111;
3551  02ec 7b08          	ld	a,(OFST+7,sp)
3552  02ee 5f            	clrw	x
3553  02ef 97            	ld	xl,a
3554  02f0 e675          	ld	a,(_ind_out_,x)
3555  02f2 a47f          	and	a,#127
3556  02f4 e775          	ld	(_ind_out_,x),a
3557  02f6               L5412:
3558                     ; 323 if(fl&&bFL5)
3560  02f6 0d0a          	tnz	(OFST+9,sp)
3561  02f8 2718          	jreq	L1512
3563  02fa 3d6f          	tnz	_bFL5
3564  02fc 2714          	jreq	L1512
3565                     ; 325 	for(i=0;i<len;i++)
3567  02fe 0f01          	clr	(OFST+0,sp)
3569  0300 200a          	jra	L7512
3570  0302               L3512:
3571                     ; 327 		ind_out_[i]=DIGISYM[10];
3573  0302 7b01          	ld	a,(OFST+0,sp)
3574  0304 5f            	clrw	x
3575  0305 97            	ld	xl,a
3576  0306 a6ff          	ld	a,#255
3577  0308 e775          	ld	(_ind_out_,x),a
3578                     ; 325 	for(i=0;i<len;i++)
3580  030a 0c01          	inc	(OFST+0,sp)
3581  030c               L7512:
3584  030c 7b01          	ld	a,(OFST+0,sp)
3585  030e 1107          	cp	a,(OFST+6,sp)
3586  0310 25f0          	jrult	L3512
3587  0312               L1512:
3588                     ; 331 for(i=0;i<len;i++)
3590  0312 0f01          	clr	(OFST+0,sp)
3592  0314 2016          	jra	L7612
3593  0316               L3612:
3594                     ; 333 		dig3[start+i]=ind_out_[i];
3596  0316 7b06          	ld	a,(OFST+5,sp)
3597  0318 5f            	clrw	x
3598  0319 1b01          	add	a,(OFST+0,sp)
3599  031b 2401          	jrnc	L23
3600  031d 5c            	incw	x
3601  031e               L23:
3602  031e 02            	rlwa	x,a
3603  031f 7b01          	ld	a,(OFST+0,sp)
3604  0321 905f          	clrw	y
3605  0323 9097          	ld	yl,a
3606  0325 90e675        	ld	a,(_ind_out_,y)
3607  0328 e715          	ld	(_dig3,x),a
3608                     ; 331 for(i=0;i<len;i++)
3610  032a 0c01          	inc	(OFST+0,sp)
3611  032c               L7612:
3614  032c 7b01          	ld	a,(OFST+0,sp)
3615  032e 1107          	cp	a,(OFST+6,sp)
3616  0330 25e4          	jrult	L3612
3617                     ; 335 if(len==0)
3619  0332 0d07          	tnz	(OFST+6,sp)
3620  0334 2610          	jrne	L3712
3621                     ; 337 	dig3[0]=0xff;
3623  0336 35ff0015      	mov	_dig3,#255
3624                     ; 338 	dig3[1]=0xff;
3626  033a 35ff0016      	mov	_dig3+1,#255
3627                     ; 339 	dig3[2]=0xff;
3629  033e 35ff0017      	mov	_dig3+2,#255
3630                     ; 340 	dig3[3]=0xff;
3632  0342 35ff0018      	mov	_dig3+3,#255
3633  0346               L3712:
3634                     ; 342 dig3_[0]=dig3[0];
3636  0346 45152d        	mov	_dig3_,_dig3
3637                     ; 343 dig3_[1]=dig3[1];
3639  0349 45162e        	mov	_dig3_+1,_dig3+1
3640                     ; 344 dig3_[2]=dig3[2];
3642  034c 45172f        	mov	_dig3_+2,_dig3+2
3643                     ; 345 dig3_[3]=dig3[3];
3645  034f 451830        	mov	_dig3_+3,_dig3+3
3646                     ; 346 if(fad)
3648  0352 0d0b          	tnz	(OFST+10,sp)
3649  0354 2710          	jreq	L5712
3650                     ; 348 	dig3[0]=0xff;
3652  0356 35ff0015      	mov	_dig3,#255
3653                     ; 349 	dig3[1]=0xff;
3655  035a 35ff0016      	mov	_dig3+1,#255
3656                     ; 350 	dig3[2]=0xff;
3658  035e 35ff0017      	mov	_dig3+2,#255
3659                     ; 351 	dig3[3]=0xff;
3661  0362 35ff0018      	mov	_dig3+3,#255
3662  0366               L5712:
3663                     ; 354 }
3666  0366 5b03          	addw	sp,#3
3667  0368 81            	ret
3692                     ; 357 void tmblr_drv(void)
3692                     ; 358 {
3693                     	switch	.text
3694  0369               _tmblr_drv:
3698                     ; 359 if(GPIOB->IDR&0b10000000)
3700  0369 c65006        	ld	a,20486
3701  036c a580          	bcp	a,#128
3702  036e 2716          	jreq	L7022
3703                     ; 361 	tmblr_cnt++;
3705  0370 be08          	ldw	x,_tmblr_cnt
3706  0372 1c0001        	addw	x,#1
3707  0375 bf08          	ldw	_tmblr_cnt,x
3708                     ; 362 	if(tmblr_cnt>=10)tmblr_cnt=10;
3710  0377 9c            	rvf
3711  0378 be08          	ldw	x,_tmblr_cnt
3712  037a a3000a        	cpw	x,#10
3713  037d 2f16          	jrslt	L3122
3716  037f ae000a        	ldw	x,#10
3717  0382 bf08          	ldw	_tmblr_cnt,x
3718  0384 200f          	jra	L3122
3719  0386               L7022:
3720                     ; 366 	tmblr_cnt--;
3722  0386 be08          	ldw	x,_tmblr_cnt
3723  0388 1d0001        	subw	x,#1
3724  038b bf08          	ldw	_tmblr_cnt,x
3725                     ; 367 	if(tmblr_cnt<=0)tmblr_cnt=0;
3727  038d 9c            	rvf
3728  038e be08          	ldw	x,_tmblr_cnt
3729  0390 2c03          	jrsgt	L3122
3732  0392 5f            	clrw	x
3733  0393 bf08          	ldw	_tmblr_cnt,x
3734  0395               L3122:
3735                     ; 370 if(tmblr_cnt>=9)tmblr_state=tsU;
3737  0395 9c            	rvf
3738  0396 be08          	ldw	x,_tmblr_cnt
3739  0398 a30009        	cpw	x,#9
3740  039b 2f06          	jrslt	L7122
3743  039d 350100a0      	mov	_tmblr_state,#1
3745  03a1 2009          	jra	L1222
3746  03a3               L7122:
3747                     ; 371 else if(tmblr_cnt<=0)tmblr_state=tsI;
3749  03a3 9c            	rvf
3750  03a4 be08          	ldw	x,_tmblr_cnt
3751  03a6 2c04          	jrsgt	L1222
3754  03a8 350200a0      	mov	_tmblr_state,#2
3755  03ac               L1222:
3756                     ; 376 }
3759  03ac 81            	ret
3784                     ; 380 void but_drv(void)
3784                     ; 381 {
3785                     	switch	.text
3786  03ad               _but_drv:
3790                     ; 382 if(GPIOE->IDR&0b00000001)
3792  03ad c65015        	ld	a,20501
3793  03b0 a501          	bcp	a,#1
3794  03b2 2716          	jreq	L5322
3795                     ; 384 	but_cnt++;
3797  03b4 be06          	ldw	x,_but_cnt
3798  03b6 1c0001        	addw	x,#1
3799  03b9 bf06          	ldw	_but_cnt,x
3800                     ; 385 	if(but_cnt>=10)but_cnt=10;
3802  03bb 9c            	rvf
3803  03bc be06          	ldw	x,_but_cnt
3804  03be a3000a        	cpw	x,#10
3805  03c1 2f16          	jrslt	L1422
3808  03c3 ae000a        	ldw	x,#10
3809  03c6 bf06          	ldw	_but_cnt,x
3810  03c8 200f          	jra	L1422
3811  03ca               L5322:
3812                     ; 389 	but_cnt--;
3814  03ca be06          	ldw	x,_but_cnt
3815  03cc 1d0001        	subw	x,#1
3816  03cf bf06          	ldw	_but_cnt,x
3817                     ; 390 	if(but_cnt<=0)but_cnt=0;
3819  03d1 9c            	rvf
3820  03d2 be06          	ldw	x,_but_cnt
3821  03d4 2c03          	jrsgt	L1422
3824  03d6 5f            	clrw	x
3825  03d7 bf06          	ldw	_but_cnt,x
3826  03d9               L1422:
3827                     ; 393 if(but_cnt>=9)but_state=bsOFF;
3829  03d9 9c            	rvf
3830  03da be06          	ldw	x,_but_cnt
3831  03dc a30009        	cpw	x,#9
3832  03df 2f04          	jrslt	L5422
3835  03e1 3f9f          	clr	_but_state
3837  03e3 2009          	jra	L7422
3838  03e5               L5422:
3839                     ; 394 else if(but_cnt<=0)but_state=bsON;
3841  03e5 9c            	rvf
3842  03e6 be06          	ldw	x,_but_cnt
3843  03e8 2c04          	jrsgt	L7422
3846  03ea 3501009f      	mov	_but_state,#1
3847  03ee               L7422:
3848                     ; 399 }
3851  03ee 81            	ret
3876                     ; 403 void enc_but_drv(void)
3876                     ; 404 {
3877                     	switch	.text
3878  03ef               _enc_but_drv:
3882                     ; 405 if(!((GPIOB->IDR)&(1<<5)))
3884  03ef c65006        	ld	a,20486
3885  03f2 a520          	bcp	a,#32
3886  03f4 2609          	jrne	L3622
3887                     ; 407 	enc_but_drv_cnt++;
3889  03f6 be03          	ldw	x,_enc_but_drv_cnt
3890  03f8 1c0001        	addw	x,#1
3891  03fb bf03          	ldw	_enc_but_drv_cnt,x
3893  03fd 200f          	jra	L5622
3894  03ff               L3622:
3895                     ; 411 	if(enc_but_drv_cnt>=10)
3897  03ff 9c            	rvf
3898  0400 be03          	ldw	x,_enc_but_drv_cnt
3899  0402 a3000a        	cpw	x,#10
3900  0405 2f04          	jrslt	L7622
3901                     ; 413 		cmnd=1;
3903  0407 35010005      	mov	_cmnd,#1
3904  040b               L7622:
3905                     ; 415 	enc_but_drv_cnt=0;
3907  040b 5f            	clrw	x
3908  040c bf03          	ldw	_enc_but_drv_cnt,x
3909  040e               L5622:
3910                     ; 417 }
3913  040e 81            	ret
3949                     ; 420 void enc_an(void)
3949                     ; 421 {
3950                     	switch	.text
3951  040f               _enc_an:
3955                     ; 423 if(encCW)
3957                     	btst	_encCW
3958  0414 2420          	jruge	L1032
3959                     ; 425 	if(encCW_cnt1)
3961  0416 3d0d          	tnz	_encCW_cnt1
3962  0418 2708          	jreq	L3032
3963                     ; 427 		if(encCW_cnt2<10)
3965  041a b60c          	ld	a,_encCW_cnt2
3966  041c a10a          	cp	a,#10
3967  041e 2402          	jruge	L3032
3968                     ; 429 			encCW_cnt2++;
3970  0420 3c0c          	inc	_encCW_cnt2
3971  0422               L3032:
3972                     ; 432 	encCW_cnt1=80;
3974  0422 3550000d      	mov	_encCW_cnt1,#80
3975                     ; 434 	if(encCW_cnt2>8)
3977  0426 b60c          	ld	a,_encCW_cnt2
3978  0428 a109          	cp	a,#9
3979  042a 251a          	jrult	L1132
3980                     ; 436 		encCW_=1;
3982  042c 72100001      	bset	_encCW_
3983                     ; 437 		encCW=0;
3985  0430 72110003      	bres	_encCW
3986  0434 2010          	jra	L1132
3987  0436               L1032:
3988                     ; 442 	if(encCW_cnt1)
3990  0436 3d0d          	tnz	_encCW_cnt1
3991  0438 270c          	jreq	L1132
3992                     ; 444 		encCW_cnt1--;
3994  043a 3a0d          	dec	_encCW_cnt1
3995                     ; 445 		if(encCW_cnt1==0)
3997  043c 3d0d          	tnz	_encCW_cnt1
3998  043e 2606          	jrne	L1132
3999                     ; 447 			encCW_cnt2=0;
4001  0440 3f0c          	clr	_encCW_cnt2
4002                     ; 448 			encCW_=0;
4004  0442 72110001      	bres	_encCW_
4005  0446               L1132:
4006                     ; 454 if(encOW)
4008                     	btst	_encOW
4009  044b 2420          	jruge	L7132
4010                     ; 456 	if(encOW_cnt1)
4012  044d 3d0b          	tnz	_encOW_cnt1
4013  044f 2708          	jreq	L1232
4014                     ; 458 		if(encOW_cnt2<10)
4016  0451 b60a          	ld	a,_encOW_cnt2
4017  0453 a10a          	cp	a,#10
4018  0455 2402          	jruge	L1232
4019                     ; 460 			encOW_cnt2++;
4021  0457 3c0a          	inc	_encOW_cnt2
4022  0459               L1232:
4023                     ; 463 	encOW_cnt1=50;
4025  0459 3532000b      	mov	_encOW_cnt1,#50
4026                     ; 464 	if(encOW_cnt2>5)
4028  045d b60a          	ld	a,_encOW_cnt2
4029  045f a106          	cp	a,#6
4030  0461 251a          	jrult	L7232
4031                     ; 466 		encOW_=1;
4033  0463 72100000      	bset	_encOW_
4034                     ; 467 		encOW=0;
4036  0467 72110002      	bres	_encOW
4037  046b 2010          	jra	L7232
4038  046d               L7132:
4039                     ; 472 	if(encOW_cnt1)
4041  046d 3d0b          	tnz	_encOW_cnt1
4042  046f 270c          	jreq	L7232
4043                     ; 474 		encOW_cnt1--;
4045  0471 3a0b          	dec	_encOW_cnt1
4046                     ; 475 		if(encOW_cnt1==0)
4048  0473 3d0b          	tnz	_encOW_cnt1
4049  0475 2606          	jrne	L7232
4050                     ; 477 			encOW_cnt2=0;
4052  0477 3f0a          	clr	_encOW_cnt2
4053                     ; 478 			encOW_=0;
4055  0479 72110000      	bres	_encOW_
4056  047d               L7232:
4057                     ; 483 if(encCW||encOW||encCW_||encOW_)
4059                     	btst	_encCW
4060  0482 2518          	jrult	L7332
4062                     	btst	_encOW
4063  0489 2511          	jrult	L7332
4065                     	btst	_encCW_
4066  0490 250a          	jrult	L7332
4068                     	btst	_encOW_
4069  0497 2503          	jrult	L44
4070  0499 cc06e0        	jp	L5332
4071  049c               L44:
4072  049c               L7332:
4073                     ; 485 	if(!ind_fad_cnt)
4075  049c 3d80          	tnz	_ind_fad_cnt
4076  049e 2608          	jrne	L5432
4077                     ; 487 		ind_fad_cnt=10;
4079  04a0 350a0080      	mov	_ind_fad_cnt,#10
4081  04a4 accc06cc      	jpf	L7432
4082  04a8               L5432:
4083                     ; 491 		if(tmblr_state==tsI)
4085  04a8 b6a0          	ld	a,_tmblr_state
4086  04aa a102          	cp	a,#2
4087  04ac 2703          	jreq	L64
4088  04ae cc05c0        	jp	L1532
4089  04b1               L64:
4090                     ; 494 			if(but_state==bsON)
4092  04b1 b69f          	ld	a,_but_state
4093  04b3 a101          	cp	a,#1
4094  04b5 2703cc053d    	jrne	L3532
4095                     ; 496 				if(encCW)
4097                     	btst	_encCW
4098  04bf 2418          	jruge	L5532
4099                     ; 498 					can_transmit(0x18a,51,0,0,0,0,0,0,0);		//Время+
4101  04c1 4b00          	push	#0
4102  04c3 4b00          	push	#0
4103  04c5 4b00          	push	#0
4104  04c7 4b00          	push	#0
4105  04c9 4b00          	push	#0
4106  04cb 4b00          	push	#0
4107  04cd 4b00          	push	#0
4108  04cf 4b33          	push	#51
4109  04d1 ae018a        	ldw	x,#394
4110  04d4 cd07e6        	call	_can_transmit
4112  04d7 5b08          	addw	sp,#8
4113  04d9               L5532:
4114                     ; 500 				if(encCW_)
4116                     	btst	_encCW_
4117  04de 2418          	jruge	L7532
4118                     ; 502 					can_transmit(0x18a,53,0,0,0,0,0,0,0);		//Время++
4120  04e0 4b00          	push	#0
4121  04e2 4b00          	push	#0
4122  04e4 4b00          	push	#0
4123  04e6 4b00          	push	#0
4124  04e8 4b00          	push	#0
4125  04ea 4b00          	push	#0
4126  04ec 4b00          	push	#0
4127  04ee 4b35          	push	#53
4128  04f0 ae018a        	ldw	x,#394
4129  04f3 cd07e6        	call	_can_transmit
4131  04f6 5b08          	addw	sp,#8
4132  04f8               L7532:
4133                     ; 505 				if(encOW)
4135                     	btst	_encOW
4136  04fd 2418          	jruge	L1632
4137                     ; 507 					can_transmit(0x18a,52,0,0,0,0,0,0,0);		//Время-
4139  04ff 4b00          	push	#0
4140  0501 4b00          	push	#0
4141  0503 4b00          	push	#0
4142  0505 4b00          	push	#0
4143  0507 4b00          	push	#0
4144  0509 4b00          	push	#0
4145  050b 4b00          	push	#0
4146  050d 4b34          	push	#52
4147  050f ae018a        	ldw	x,#394
4148  0512 cd07e6        	call	_can_transmit
4150  0515 5b08          	addw	sp,#8
4151  0517               L1632:
4152                     ; 510 				if(encOW_)
4154                     	btst	_encOW_
4155  051c 2503          	jrult	L05
4156  051e cc06cc        	jp	L7432
4157  0521               L05:
4158                     ; 512 					can_transmit(0x18a,54,0,0,0,0,0,0,0);		//Время--
4160  0521 4b00          	push	#0
4161  0523 4b00          	push	#0
4162  0525 4b00          	push	#0
4163  0527 4b00          	push	#0
4164  0529 4b00          	push	#0
4165  052b 4b00          	push	#0
4166  052d 4b00          	push	#0
4167  052f 4b36          	push	#54
4168  0531 ae018a        	ldw	x,#394
4169  0534 cd07e6        	call	_can_transmit
4171  0537 5b08          	addw	sp,#8
4172  0539 accc06cc      	jpf	L7432
4173  053d               L3532:
4174                     ; 517 				if(encCW)
4176                     	btst	_encCW
4177  0542 2418          	jruge	L7632
4178                     ; 519 					can_transmit(0x18a,61,0,0,0,0,0,0,0);
4180  0544 4b00          	push	#0
4181  0546 4b00          	push	#0
4182  0548 4b00          	push	#0
4183  054a 4b00          	push	#0
4184  054c 4b00          	push	#0
4185  054e 4b00          	push	#0
4186  0550 4b00          	push	#0
4187  0552 4b3d          	push	#61
4188  0554 ae018a        	ldw	x,#394
4189  0557 cd07e6        	call	_can_transmit
4191  055a 5b08          	addw	sp,#8
4192  055c               L7632:
4193                     ; 521 				if(encCW_)
4195                     	btst	_encCW_
4196  0561 2418          	jruge	L1732
4197                     ; 523 					can_transmit(0x18a,63,0,0,0,0,0,0,0);
4199  0563 4b00          	push	#0
4200  0565 4b00          	push	#0
4201  0567 4b00          	push	#0
4202  0569 4b00          	push	#0
4203  056b 4b00          	push	#0
4204  056d 4b00          	push	#0
4205  056f 4b00          	push	#0
4206  0571 4b3f          	push	#63
4207  0573 ae018a        	ldw	x,#394
4208  0576 cd07e6        	call	_can_transmit
4210  0579 5b08          	addw	sp,#8
4211  057b               L1732:
4212                     ; 525 				if(encOW)
4214                     	btst	_encOW
4215  0580 2418          	jruge	L3732
4216                     ; 527 					can_transmit(0x18a,62,0,0,0,0,0,0,0);
4218  0582 4b00          	push	#0
4219  0584 4b00          	push	#0
4220  0586 4b00          	push	#0
4221  0588 4b00          	push	#0
4222  058a 4b00          	push	#0
4223  058c 4b00          	push	#0
4224  058e 4b00          	push	#0
4225  0590 4b3e          	push	#62
4226  0592 ae018a        	ldw	x,#394
4227  0595 cd07e6        	call	_can_transmit
4229  0598 5b08          	addw	sp,#8
4230  059a               L3732:
4231                     ; 529 				if(encOW_)
4233                     	btst	_encOW_
4234  059f 2503          	jrult	L25
4235  05a1 cc06cc        	jp	L7432
4236  05a4               L25:
4237                     ; 531 					can_transmit(0x18a,64,0,0,0,0,0,0,0);
4239  05a4 4b00          	push	#0
4240  05a6 4b00          	push	#0
4241  05a8 4b00          	push	#0
4242  05aa 4b00          	push	#0
4243  05ac 4b00          	push	#0
4244  05ae 4b00          	push	#0
4245  05b0 4b00          	push	#0
4246  05b2 4b40          	push	#64
4247  05b4 ae018a        	ldw	x,#394
4248  05b7 cd07e6        	call	_can_transmit
4250  05ba 5b08          	addw	sp,#8
4251  05bc accc06cc      	jpf	L7432
4252  05c0               L1532:
4253                     ; 535 		else	if(tmblr_state==tsU)
4255  05c0 b6a0          	ld	a,_tmblr_state
4256  05c2 a101          	cp	a,#1
4257  05c4 2703          	jreq	L45
4258  05c6 cc06cc        	jp	L7432
4259  05c9               L45:
4260                     ; 538 			if(but_state==bsON)
4262  05c9 b69f          	ld	a,_but_state
4263  05cb a101          	cp	a,#1
4264  05cd 2703cc0650    	jrne	L3042
4265                     ; 540 				if(encCW)
4267                     	btst	_encCW
4268  05d7 2418          	jruge	L5042
4269                     ; 542 					can_transmit(0x18a,51,0,0,0,0,0,0,0);		//Время+
4271  05d9 4b00          	push	#0
4272  05db 4b00          	push	#0
4273  05dd 4b00          	push	#0
4274  05df 4b00          	push	#0
4275  05e1 4b00          	push	#0
4276  05e3 4b00          	push	#0
4277  05e5 4b00          	push	#0
4278  05e7 4b33          	push	#51
4279  05e9 ae018a        	ldw	x,#394
4280  05ec cd07e6        	call	_can_transmit
4282  05ef 5b08          	addw	sp,#8
4283  05f1               L5042:
4284                     ; 544 				if(encCW_)
4286                     	btst	_encCW_
4287  05f6 2418          	jruge	L7042
4288                     ; 546 					can_transmit(0x18a,53,0,0,0,0,0,0,0);		//Время++
4290  05f8 4b00          	push	#0
4291  05fa 4b00          	push	#0
4292  05fc 4b00          	push	#0
4293  05fe 4b00          	push	#0
4294  0600 4b00          	push	#0
4295  0602 4b00          	push	#0
4296  0604 4b00          	push	#0
4297  0606 4b35          	push	#53
4298  0608 ae018a        	ldw	x,#394
4299  060b cd07e6        	call	_can_transmit
4301  060e 5b08          	addw	sp,#8
4302  0610               L7042:
4303                     ; 549 				if(encOW)
4305                     	btst	_encOW
4306  0615 2418          	jruge	L1142
4307                     ; 551 					can_transmit(0x18a,52,0,0,0,0,0,0,0);		//Время-
4309  0617 4b00          	push	#0
4310  0619 4b00          	push	#0
4311  061b 4b00          	push	#0
4312  061d 4b00          	push	#0
4313  061f 4b00          	push	#0
4314  0621 4b00          	push	#0
4315  0623 4b00          	push	#0
4316  0625 4b34          	push	#52
4317  0627 ae018a        	ldw	x,#394
4318  062a cd07e6        	call	_can_transmit
4320  062d 5b08          	addw	sp,#8
4321  062f               L1142:
4322                     ; 554 				if(encOW_)
4324                     	btst	_encOW_
4325  0634 2490          	jruge	L7432
4326                     ; 556 					can_transmit(0x18a,54,0,0,0,0,0,0,0);		//Время--
4328  0636 4b00          	push	#0
4329  0638 4b00          	push	#0
4330  063a 4b00          	push	#0
4331  063c 4b00          	push	#0
4332  063e 4b00          	push	#0
4333  0640 4b00          	push	#0
4334  0642 4b00          	push	#0
4335  0644 4b36          	push	#54
4336  0646 ae018a        	ldw	x,#394
4337  0649 cd07e6        	call	_can_transmit
4339  064c 5b08          	addw	sp,#8
4340  064e 207c          	jra	L7432
4341  0650               L3042:
4342                     ; 561 				if(encCW)
4344                     	btst	_encCW
4345  0655 2418          	jruge	L7142
4346                     ; 563 					can_transmit(0x18a,71,0,0,0,0,0,0,0);
4348  0657 4b00          	push	#0
4349  0659 4b00          	push	#0
4350  065b 4b00          	push	#0
4351  065d 4b00          	push	#0
4352  065f 4b00          	push	#0
4353  0661 4b00          	push	#0
4354  0663 4b00          	push	#0
4355  0665 4b47          	push	#71
4356  0667 ae018a        	ldw	x,#394
4357  066a cd07e6        	call	_can_transmit
4359  066d 5b08          	addw	sp,#8
4360  066f               L7142:
4361                     ; 565 				if(encCW_)
4363                     	btst	_encCW_
4364  0674 2418          	jruge	L1242
4365                     ; 567 					can_transmit(0x18a,73,0,0,0,0,0,0,0);
4367  0676 4b00          	push	#0
4368  0678 4b00          	push	#0
4369  067a 4b00          	push	#0
4370  067c 4b00          	push	#0
4371  067e 4b00          	push	#0
4372  0680 4b00          	push	#0
4373  0682 4b00          	push	#0
4374  0684 4b49          	push	#73
4375  0686 ae018a        	ldw	x,#394
4376  0689 cd07e6        	call	_can_transmit
4378  068c 5b08          	addw	sp,#8
4379  068e               L1242:
4380                     ; 569 				if(encOW)
4382                     	btst	_encOW
4383  0693 2418          	jruge	L3242
4384                     ; 571 					can_transmit(0x18a,72,0,0,0,0,0,0,0);
4386  0695 4b00          	push	#0
4387  0697 4b00          	push	#0
4388  0699 4b00          	push	#0
4389  069b 4b00          	push	#0
4390  069d 4b00          	push	#0
4391  069f 4b00          	push	#0
4392  06a1 4b00          	push	#0
4393  06a3 4b48          	push	#72
4394  06a5 ae018a        	ldw	x,#394
4395  06a8 cd07e6        	call	_can_transmit
4397  06ab 5b08          	addw	sp,#8
4398  06ad               L3242:
4399                     ; 573 				if(encOW_)
4401                     	btst	_encOW_
4402  06b2 2418          	jruge	L7432
4403                     ; 575 					can_transmit(0x18a,74,0,0,0,0,0,0,0);
4405  06b4 4b00          	push	#0
4406  06b6 4b00          	push	#0
4407  06b8 4b00          	push	#0
4408  06ba 4b00          	push	#0
4409  06bc 4b00          	push	#0
4410  06be 4b00          	push	#0
4411  06c0 4b00          	push	#0
4412  06c2 4b4a          	push	#74
4413  06c4 ae018a        	ldw	x,#394
4414  06c7 cd07e6        	call	_can_transmit
4416  06ca 5b08          	addw	sp,#8
4417  06cc               L7432:
4418                     ; 580 	ind_fad_cnt=10;
4420  06cc 350a0080      	mov	_ind_fad_cnt,#10
4421                     ; 581 	encCW=0;
4423  06d0 72110003      	bres	_encCW
4424                     ; 582 	encCW_=0;
4426  06d4 72110001      	bres	_encCW_
4427                     ; 583 	encOW=0;
4429  06d8 72110002      	bres	_encOW
4430                     ; 584 	encOW_=0;
4432  06dc 72110000      	bres	_encOW_
4433  06e0               L5332:
4434                     ; 587 if(cmnd)
4436  06e0 3d05          	tnz	_cmnd
4437  06e2 271a          	jreq	L7242
4438                     ; 589 	can_transmit(0x18a,90,0,0,0,0,0,0,0);
4440  06e4 4b00          	push	#0
4441  06e6 4b00          	push	#0
4442  06e8 4b00          	push	#0
4443  06ea 4b00          	push	#0
4444  06ec 4b00          	push	#0
4445  06ee 4b00          	push	#0
4446  06f0 4b00          	push	#0
4447  06f2 4b5a          	push	#90
4448  06f4 ae018a        	ldw	x,#394
4449  06f7 cd07e6        	call	_can_transmit
4451  06fa 5b08          	addw	sp,#8
4452                     ; 590 	cmnd=0;
4454  06fc 3f05          	clr	_cmnd
4455  06fe               L7242:
4456                     ; 593 }
4459  06fe 81            	ret
4493                     ; 596 void can_in_an(void)
4493                     ; 597 {
4494                     	switch	.text
4495  06ff               _can_in_an:
4499                     ; 604 if(mess[6]==33)
4501  06ff b61e          	ld	a,_mess+6
4502  0701 a121          	cp	a,#33
4503  0703 2636          	jrne	L5442
4504                     ; 609 	ind_U=(mess[7]+(mess[8]*256));
4506  0705 b620          	ld	a,_mess+8
4507  0707 5f            	clrw	x
4508  0708 97            	ld	xl,a
4509  0709 4f            	clr	a
4510  070a 02            	rlwa	x,a
4511  070b 01            	rrwa	x,a
4512  070c bb1f          	add	a,_mess+7
4513  070e 2401          	jrnc	L06
4514  0710 5c            	incw	x
4515  0711               L06:
4516  0711 b78b          	ld	_ind_U+1,a
4517  0713 9f            	ld	a,xl
4518  0714 b78a          	ld	_ind_U,a
4519                     ; 610 	ind_I=(mess[9]+(mess[10]*256));
4521  0716 b622          	ld	a,_mess+10
4522  0718 5f            	clrw	x
4523  0719 97            	ld	xl,a
4524  071a 4f            	clr	a
4525  071b 02            	rlwa	x,a
4526  071c 01            	rrwa	x,a
4527  071d bb21          	add	a,_mess+9
4528  071f 2401          	jrnc	L26
4529  0721 5c            	incw	x
4530  0722               L26:
4531  0722 b789          	ld	_ind_I+1,a
4532  0724 9f            	ld	a,xl
4533  0725 b788          	ld	_ind_I,a
4534                     ; 611 	work_stat=(enum_work_stat)mess[11];
4536  0727 452338        	mov	_work_stat,_mess+11
4537                     ; 612 	ind_U_set=(mess[12]+(mess[13]*256));
4539  072a b625          	ld	a,_mess+13
4540  072c 5f            	clrw	x
4541  072d 97            	ld	xl,a
4542  072e 4f            	clr	a
4543  072f 02            	rlwa	x,a
4544  0730 01            	rrwa	x,a
4545  0731 bb24          	add	a,_mess+12
4546  0733 2401          	jrnc	L46
4547  0735 5c            	incw	x
4548  0736               L46:
4549  0736 b787          	ld	_ind_U_set+1,a
4550  0738 9f            	ld	a,xl
4551  0739 b786          	ld	_ind_U_set,a
4552  073b               L5442:
4553                     ; 622 if(mess[6]==34)
4555  073b b61e          	ld	a,_mess+6
4556  073d a122          	cp	a,#34
4557  073f 2633          	jrne	L1342
4558                     ; 624 	time= (mess[7]+(mess[8]*256));
4560  0741 b620          	ld	a,_mess+8
4561  0743 5f            	clrw	x
4562  0744 97            	ld	xl,a
4563  0745 4f            	clr	a
4564  0746 02            	rlwa	x,a
4565  0747 01            	rrwa	x,a
4566  0748 bb1f          	add	a,_mess+7
4567  074a 2401          	jrnc	L66
4568  074c 5c            	incw	x
4569  074d               L66:
4570  074d b78f          	ld	_time+1,a
4571  074f 9f            	ld	a,xl
4572  0750 b78e          	ld	_time,a
4573                     ; 625 	time_set= (mess[9]+(mess[10]*256));
4575  0752 b622          	ld	a,_mess+10
4576  0754 5f            	clrw	x
4577  0755 97            	ld	xl,a
4578  0756 4f            	clr	a
4579  0757 02            	rlwa	x,a
4580  0758 01            	rrwa	x,a
4581  0759 bb21          	add	a,_mess+9
4582  075b 2401          	jrnc	L07
4583  075d 5c            	incw	x
4584  075e               L07:
4585  075e b78d          	ld	_time_set+1,a
4586  0760 9f            	ld	a,xl
4587  0761 b78c          	ld	_time_set,a
4588                     ; 626 	ind_I_set=(mess[12]+(mess[13]*256));
4590  0763 b625          	ld	a,_mess+13
4591  0765 5f            	clrw	x
4592  0766 97            	ld	xl,a
4593  0767 4f            	clr	a
4594  0768 02            	rlwa	x,a
4595  0769 01            	rrwa	x,a
4596  076a bb24          	add	a,_mess+12
4597  076c 2401          	jrnc	L27
4598  076e 5c            	incw	x
4599  076f               L27:
4600  076f b785          	ld	_ind_I_set+1,a
4601  0771 9f            	ld	a,xl
4602  0772 b784          	ld	_ind_I_set,a
4603  0774               L1342:
4604                     ; 638 can_in_an_end:
4604                     ; 639 bCAN_RX=0;
4606  0774 3f36          	clr	_bCAN_RX
4607                     ; 640 }   
4610  0776 81            	ret
4633                     ; 643 void init_CAN(void) {
4634                     	switch	.text
4635  0777               _init_CAN:
4639                     ; 644 	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
4641  0777 72135420      	bres	21536,#1
4642                     ; 645 	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
4644  077b 72105420      	bset	21536,#0
4646  077f               L3642:
4647                     ; 646 	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
4649  077f c65421        	ld	a,21537
4650  0782 a501          	bcp	a,#1
4651  0784 27f9          	jreq	L3642
4652                     ; 648 	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
4654  0786 72185420      	bset	21536,#4
4655                     ; 650 	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
4657  078a 35025427      	mov	21543,#2
4658                     ; 659 	CAN->Page.Filter01.F0R1= UKU_MESS_STID>>3;			// 16 bits mode
4660  078e 35155428      	mov	21544,#21
4661                     ; 660 	CAN->Page.Filter01.F0R2= UKU_MESS_STID<<5;
4663  0792 35c05429      	mov	21545,#192
4664                     ; 661 	CAN->Page.Filter01.F0R5= UKU_MESS_STID_MASK>>3;
4666  0796 357f542c      	mov	21548,#127
4667                     ; 662 	CAN->Page.Filter01.F0R6= UKU_MESS_STID_MASK<<5;
4669  079a 35e0542d      	mov	21549,#224
4670                     ; 664 	CAN->Page.Filter01.F1R1= BPS_MESS_STID>>3;			// 16 bits mode
4672  079e 35335430      	mov	21552,#51
4673                     ; 665 	CAN->Page.Filter01.F1R2= BPS_MESS_STID<<5;
4675  07a2 35c05431      	mov	21553,#192
4676                     ; 666 	CAN->Page.Filter01.F1R5= BPS_MESS_STID_MASK>>3;
4678  07a6 357f5434      	mov	21556,#127
4679                     ; 667 	CAN->Page.Filter01.F1R6= BPS_MESS_STID_MASK<<5;
4681  07aa 35e05435      	mov	21557,#224
4682                     ; 671 	CAN->PSR= 6;									// set page 6
4684  07ae 35065427      	mov	21543,#6
4685                     ; 676 	CAN->Page.Config.FMR1&=~3;								//mask mode
4687  07b2 c65430        	ld	a,21552
4688  07b5 a4fc          	and	a,#252
4689  07b7 c75430        	ld	21552,a
4690                     ; 682 	CAN->Page.Config.FCR1= ((3<<1) & (CAN_FCR1_FSC00 | CAN_FCR1_FSC01));		//16 bit scale
4692  07ba 35065432      	mov	21554,#6
4693                     ; 683 	CAN->Page.Config.FCR1= ((3<<5) & (CAN_FCR1_FSC10 | CAN_FCR1_FSC11));		//16 bit scale
4695  07be 35605432      	mov	21554,#96
4696                     ; 686 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
4698  07c2 72105432      	bset	21554,#0
4699                     ; 687 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT1;
4701  07c6 72185432      	bset	21554,#4
4702                     ; 690 	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
4704  07ca 35065427      	mov	21543,#6
4705                     ; 692 	CAN->Page.Config.BTR1= 4;					// CAN_BTR1_BRP=9, 	tq= fcpu/(9+1)
4707  07ce 3504542c      	mov	21548,#4
4708                     ; 693 	CAN->Page.Config.BTR2= (1<<7)|(6<<4) | 7; 		// BS2=8, BS1=7, 		
4710  07d2 35e7542d      	mov	21549,#231
4711                     ; 695 	CAN->IER|=(1<<1);
4713  07d6 72125425      	bset	21541,#1
4714                     ; 698 	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
4716  07da 72115420      	bres	21536,#0
4718  07de               L1742:
4719                     ; 699 	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
4721  07de c65421        	ld	a,21537
4722  07e1 a501          	bcp	a,#1
4723  07e3 26f9          	jrne	L1742
4724                     ; 700 }
4727  07e5 81            	ret
4835                     ; 704 void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
4835                     ; 705 {
4836                     	switch	.text
4837  07e6               _can_transmit:
4839  07e6 89            	pushw	x
4840       00000000      OFST:	set	0
4843                     ; 707 if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>3))can_buff_wr_ptr=0;
4845  07e7 b62b          	ld	a,_can_buff_wr_ptr
4846  07e9 a104          	cp	a,#4
4847  07eb 2502          	jrult	L3552
4850  07ed 3f2b          	clr	_can_buff_wr_ptr
4851  07ef               L3552:
4852                     ; 709 can_out_buff[can_buff_wr_ptr][0]=(char)(id_st>>6);
4854  07ef b62b          	ld	a,_can_buff_wr_ptr
4855  07f1 97            	ld	xl,a
4856  07f2 a610          	ld	a,#16
4857  07f4 42            	mul	x,a
4858  07f5 1601          	ldw	y,(OFST+1,sp)
4859  07f7 a606          	ld	a,#6
4860  07f9               L001:
4861  07f9 9054          	srlw	y
4862  07fb 4a            	dec	a
4863  07fc 26fb          	jrne	L001
4864  07fe 909f          	ld	a,yl
4865  0800 e72c          	ld	(_can_out_buff,x),a
4866                     ; 710 can_out_buff[can_buff_wr_ptr][1]=(char)(id_st<<2);
4868  0802 b62b          	ld	a,_can_buff_wr_ptr
4869  0804 97            	ld	xl,a
4870  0805 a610          	ld	a,#16
4871  0807 42            	mul	x,a
4872  0808 7b02          	ld	a,(OFST+2,sp)
4873  080a 48            	sll	a
4874  080b 48            	sll	a
4875  080c e72d          	ld	(_can_out_buff+1,x),a
4876                     ; 712 can_out_buff[can_buff_wr_ptr][2]=data0;
4878  080e b62b          	ld	a,_can_buff_wr_ptr
4879  0810 97            	ld	xl,a
4880  0811 a610          	ld	a,#16
4881  0813 42            	mul	x,a
4882  0814 7b05          	ld	a,(OFST+5,sp)
4883  0816 e72e          	ld	(_can_out_buff+2,x),a
4884                     ; 713 can_out_buff[can_buff_wr_ptr][3]=data1;
4886  0818 b62b          	ld	a,_can_buff_wr_ptr
4887  081a 97            	ld	xl,a
4888  081b a610          	ld	a,#16
4889  081d 42            	mul	x,a
4890  081e 7b06          	ld	a,(OFST+6,sp)
4891  0820 e72f          	ld	(_can_out_buff+3,x),a
4892                     ; 714 can_out_buff[can_buff_wr_ptr][4]=data2;
4894  0822 b62b          	ld	a,_can_buff_wr_ptr
4895  0824 97            	ld	xl,a
4896  0825 a610          	ld	a,#16
4897  0827 42            	mul	x,a
4898  0828 7b07          	ld	a,(OFST+7,sp)
4899  082a e730          	ld	(_can_out_buff+4,x),a
4900                     ; 715 can_out_buff[can_buff_wr_ptr][5]=data3;
4902  082c b62b          	ld	a,_can_buff_wr_ptr
4903  082e 97            	ld	xl,a
4904  082f a610          	ld	a,#16
4905  0831 42            	mul	x,a
4906  0832 7b08          	ld	a,(OFST+8,sp)
4907  0834 e731          	ld	(_can_out_buff+5,x),a
4908                     ; 716 can_out_buff[can_buff_wr_ptr][6]=data4;
4910  0836 b62b          	ld	a,_can_buff_wr_ptr
4911  0838 97            	ld	xl,a
4912  0839 a610          	ld	a,#16
4913  083b 42            	mul	x,a
4914  083c 7b09          	ld	a,(OFST+9,sp)
4915  083e e732          	ld	(_can_out_buff+6,x),a
4916                     ; 717 can_out_buff[can_buff_wr_ptr][7]=data5;
4918  0840 b62b          	ld	a,_can_buff_wr_ptr
4919  0842 97            	ld	xl,a
4920  0843 a610          	ld	a,#16
4921  0845 42            	mul	x,a
4922  0846 7b0a          	ld	a,(OFST+10,sp)
4923  0848 e733          	ld	(_can_out_buff+7,x),a
4924                     ; 718 can_out_buff[can_buff_wr_ptr][8]=data6;
4926  084a b62b          	ld	a,_can_buff_wr_ptr
4927  084c 97            	ld	xl,a
4928  084d a610          	ld	a,#16
4929  084f 42            	mul	x,a
4930  0850 7b0b          	ld	a,(OFST+11,sp)
4931  0852 e734          	ld	(_can_out_buff+8,x),a
4932                     ; 719 can_out_buff[can_buff_wr_ptr][9]=data7;
4934  0854 b62b          	ld	a,_can_buff_wr_ptr
4935  0856 97            	ld	xl,a
4936  0857 a610          	ld	a,#16
4937  0859 42            	mul	x,a
4938  085a 7b0c          	ld	a,(OFST+12,sp)
4939  085c e735          	ld	(_can_out_buff+9,x),a
4940                     ; 721 can_buff_wr_ptr++;
4942  085e 3c2b          	inc	_can_buff_wr_ptr
4943                     ; 722 if(can_buff_wr_ptr>3)can_buff_wr_ptr=0;
4945  0860 b62b          	ld	a,_can_buff_wr_ptr
4946  0862 a104          	cp	a,#4
4947  0864 2502          	jrult	L5552
4950  0866 3f2b          	clr	_can_buff_wr_ptr
4951  0868               L5552:
4952                     ; 723 } 
4955  0868 85            	popw	x
4956  0869 81            	ret
4998                     ; 726 void ind_hndl(void)
4998                     ; 727 {
4999                     	switch	.text
5000  086a               _ind_hndl:
5002  086a 89            	pushw	x
5003       00000002      OFST:	set	2
5006                     ; 729 if(ind_fad_cnt)
5008  086b 3d80          	tnz	_ind_fad_cnt
5009  086d 2702          	jreq	L7652
5010                     ; 731 	ind_fad_cnt--;
5012  086f 3a80          	dec	_ind_fad_cnt
5013  0871               L7652:
5014                     ; 833 int2ind_slkuf2(ind_U,0,3,1,0,0,0);
5016  0871 4b00          	push	#0
5017  0873 4b00          	push	#0
5018  0875 4b00          	push	#0
5019  0877 4b01          	push	#1
5020  0879 4b03          	push	#3
5021  087b 4b00          	push	#0
5022  087d be8a          	ldw	x,_ind_U
5023  087f cd0201        	call	_int2ind_slkuf2
5025  0882 5b06          	addw	sp,#6
5026                     ; 838 if(work_stat==wsGS)
5028  0884 b638          	ld	a,_work_stat
5029  0886 a101          	cp	a,#1
5030  0888 2703          	jreq	L401
5031  088a cc09a3        	jp	L1752
5032  088d               L401:
5033                     ; 840 	if((ind_fad_cnt)&&(but_state==bsOFF))
5035  088d 3d80          	tnz	_ind_fad_cnt
5036  088f 273b          	jreq	L3752
5038  0891 3d9f          	tnz	_but_state
5039  0893 2637          	jrne	L3752
5040                     ; 843 		if(ind_I_set<=999)int2ind_slkuf1(ind_I_set,0,3,1,1,0,1);
5042  0895 9c            	rvf
5043  0896 be84          	ldw	x,_ind_I_set
5044  0898 a303e8        	cpw	x,#1000
5045  089b 2e15          	jrsge	L5752
5048  089d 4b01          	push	#1
5049  089f 4b00          	push	#0
5050  08a1 4b01          	push	#1
5051  08a3 4b01          	push	#1
5052  08a5 4b03          	push	#3
5053  08a7 4b00          	push	#0
5054  08a9 be84          	ldw	x,_ind_I_set
5055  08ab cd015e        	call	_int2ind_slkuf1
5057  08ae 5b06          	addw	sp,#6
5059  08b0 204f          	jra	L1062
5060  08b2               L5752:
5061                     ; 844 		else int2ind_slkuf1(ind_I_set/10,0,3,0,1,0,1);
5063  08b2 4b01          	push	#1
5064  08b4 4b00          	push	#0
5065  08b6 4b01          	push	#1
5066  08b8 4b00          	push	#0
5067  08ba 4b03          	push	#3
5068  08bc 4b00          	push	#0
5069  08be be84          	ldw	x,_ind_I_set
5070  08c0 a60a          	ld	a,#10
5071  08c2 cd0000        	call	c_sdivx
5073  08c5 cd015e        	call	_int2ind_slkuf1
5075  08c8 5b06          	addw	sp,#6
5076  08ca 2035          	jra	L1062
5077  08cc               L3752:
5078                     ; 849 		if(ind_I<=999)int2ind_slkuf1(ind_I,0,3,1,1,0,0);
5080  08cc 9c            	rvf
5081  08cd be88          	ldw	x,_ind_I
5082  08cf a303e8        	cpw	x,#1000
5083  08d2 2e15          	jrsge	L3062
5086  08d4 4b00          	push	#0
5087  08d6 4b00          	push	#0
5088  08d8 4b01          	push	#1
5089  08da 4b01          	push	#1
5090  08dc 4b03          	push	#3
5091  08de 4b00          	push	#0
5092  08e0 be88          	ldw	x,_ind_I
5093  08e2 cd015e        	call	_int2ind_slkuf1
5095  08e5 5b06          	addw	sp,#6
5097  08e7 2018          	jra	L1062
5098  08e9               L3062:
5099                     ; 850 		else int2ind_slkuf1(ind_I/10,0,3,0,1,0,0);
5101  08e9 4b00          	push	#0
5102  08eb 4b00          	push	#0
5103  08ed 4b01          	push	#1
5104  08ef 4b00          	push	#0
5105  08f1 4b03          	push	#3
5106  08f3 4b00          	push	#0
5107  08f5 be88          	ldw	x,_ind_I
5108  08f7 a60a          	ld	a,#10
5109  08f9 cd0000        	call	c_sdivx
5111  08fc cd015e        	call	_int2ind_slkuf1
5113  08ff 5b06          	addw	sp,#6
5114  0901               L1062:
5115                     ; 854 	if(ind_U<1000){
5117  0901 9c            	rvf
5118  0902 be8a          	ldw	x,_ind_U
5119  0904 a303e8        	cpw	x,#1000
5120  0907 2e15          	jrsge	L7062
5121                     ; 855 		int2ind_slkuf2(ind_U,0,3,1,1,0,0);
5123  0909 4b00          	push	#0
5124  090b 4b00          	push	#0
5125  090d 4b01          	push	#1
5126  090f 4b01          	push	#1
5127  0911 4b03          	push	#3
5128  0913 4b00          	push	#0
5129  0915 be8a          	ldw	x,_ind_U
5130  0917 cd0201        	call	_int2ind_slkuf2
5132  091a 5b06          	addw	sp,#6
5134  091c 2018          	jra	L1162
5135  091e               L7062:
5136                     ; 857 		int2ind_slkuf2(ind_U/10,0,3,0,1,0,0);
5138  091e 4b00          	push	#0
5139  0920 4b00          	push	#0
5140  0922 4b01          	push	#1
5141  0924 4b00          	push	#0
5142  0926 4b03          	push	#3
5143  0928 4b00          	push	#0
5144  092a be8a          	ldw	x,_ind_U
5145  092c a60a          	ld	a,#10
5146  092e cd0000        	call	c_sdivx
5148  0931 cd0201        	call	_int2ind_slkuf2
5150  0934 5b06          	addw	sp,#6
5151  0936               L1162:
5152                     ; 861 	if(bFL2)	int2ind_slkuf3(((time/60)*100)+(time%60),0,4,2,0,0,0);
5154  0936 3d6e          	tnz	_bFL2
5155  0938 272e          	jreq	L3162
5158  093a 4b00          	push	#0
5159  093c 4b00          	push	#0
5160  093e 4b00          	push	#0
5161  0940 4b02          	push	#2
5162  0942 4b04          	push	#4
5163  0944 4b00          	push	#0
5164  0946 be8e          	ldw	x,_time
5165  0948 90ae003c      	ldw	y,#60
5166  094c 65            	divw	x,y
5167  094d 51            	exgw	x,y
5168  094e 1f07          	ldw	(OFST+5,sp),x
5169  0950 be8e          	ldw	x,_time
5170  0952 90ae003c      	ldw	y,#60
5171  0956 65            	divw	x,y
5172  0957 90ae0064      	ldw	y,#100
5173  095b cd0000        	call	c_imul
5175  095e 72fb07        	addw	x,(OFST+5,sp)
5176  0961 cd02c5        	call	_int2ind_slkuf3
5178  0964 5b06          	addw	sp,#6
5180  0966 202c          	jra	L5162
5181  0968               L3162:
5182                     ; 862 	else 	int2ind_slkuf3(((time/60)*100)+(time%60),0,4,0,0,0,0);
5184  0968 4b00          	push	#0
5185  096a 4b00          	push	#0
5186  096c 4b00          	push	#0
5187  096e 4b00          	push	#0
5188  0970 4b04          	push	#4
5189  0972 4b00          	push	#0
5190  0974 be8e          	ldw	x,_time
5191  0976 90ae003c      	ldw	y,#60
5192  097a 65            	divw	x,y
5193  097b 51            	exgw	x,y
5194  097c 1f07          	ldw	(OFST+5,sp),x
5195  097e be8e          	ldw	x,_time
5196  0980 90ae003c      	ldw	y,#60
5197  0984 65            	divw	x,y
5198  0985 90ae0064      	ldw	y,#100
5199  0989 cd0000        	call	c_imul
5201  098c 72fb07        	addw	x,(OFST+5,sp)
5202  098f cd02c5        	call	_int2ind_slkuf3
5204  0992 5b06          	addw	sp,#6
5205  0994               L5162:
5206                     ; 864 	if(bFL5)dig1_[3]&=0xdf;
5208  0994 3d6f          	tnz	_bFL5
5209  0996 2603          	jrne	L601
5210  0998 cc0da9        	jp	L1262
5211  099b               L601:
5214  099b 721b0020      	bres	_dig1_+3,#5
5215  099f aca90da9      	jpf	L1262
5216  09a3               L1752:
5217                     ; 866 else if(work_stat==wsPS)
5219  09a3 b638          	ld	a,_work_stat
5220  09a5 a102          	cp	a,#2
5221  09a7 2703          	jreq	L011
5222  09a9 cc0ac2        	jp	L3262
5223  09ac               L011:
5224                     ; 869 	if(ind_I<=999)int2ind_slkuf1(ind_I,0,3,1,1,0,0);
5226  09ac 9c            	rvf
5227  09ad be88          	ldw	x,_ind_I
5228  09af a303e8        	cpw	x,#1000
5229  09b2 2e15          	jrsge	L5262
5232  09b4 4b00          	push	#0
5233  09b6 4b00          	push	#0
5234  09b8 4b01          	push	#1
5235  09ba 4b01          	push	#1
5236  09bc 4b03          	push	#3
5237  09be 4b00          	push	#0
5238  09c0 be88          	ldw	x,_ind_I
5239  09c2 cd015e        	call	_int2ind_slkuf1
5241  09c5 5b06          	addw	sp,#6
5243  09c7 2018          	jra	L7262
5244  09c9               L5262:
5245                     ; 870 	else int2ind_slkuf1(ind_I/10,0,3,0,1,0,0);
5247  09c9 4b00          	push	#0
5248  09cb 4b00          	push	#0
5249  09cd 4b01          	push	#1
5250  09cf 4b00          	push	#0
5251  09d1 4b03          	push	#3
5252  09d3 4b00          	push	#0
5253  09d5 be88          	ldw	x,_ind_I
5254  09d7 a60a          	ld	a,#10
5255  09d9 cd0000        	call	c_sdivx
5257  09dc cd015e        	call	_int2ind_slkuf1
5259  09df 5b06          	addw	sp,#6
5260  09e1               L7262:
5261                     ; 873 	if((!ind_fad_cnt)||(but_state!=bsOFF)) {
5263  09e1 3d80          	tnz	_ind_fad_cnt
5264  09e3 2704          	jreq	L3362
5266  09e5 3d9f          	tnz	_but_state
5267  09e7 2767          	jreq	L1362
5268  09e9               L3362:
5269                     ; 875 		if(ind_U<1000){
5271  09e9 9c            	rvf
5272  09ea be8a          	ldw	x,_ind_U
5273  09ec a303e8        	cpw	x,#1000
5274  09ef 2e15          	jrsge	L5362
5275                     ; 876 			int2ind_slkuf2(ind_U,0,3,1,1,0,0);
5277  09f1 4b00          	push	#0
5278  09f3 4b00          	push	#0
5279  09f5 4b01          	push	#1
5280  09f7 4b01          	push	#1
5281  09f9 4b03          	push	#3
5282  09fb 4b00          	push	#0
5283  09fd be8a          	ldw	x,_ind_U
5284  09ff cd0201        	call	_int2ind_slkuf2
5286  0a02 5b06          	addw	sp,#6
5288  0a04 2018          	jra	L1462
5289  0a06               L5362:
5290                     ; 878 			int2ind_slkuf2(ind_U/10,0,3,0,1,0,0);
5292  0a06 4b00          	push	#0
5293  0a08 4b00          	push	#0
5294  0a0a 4b01          	push	#1
5295  0a0c 4b00          	push	#0
5296  0a0e 4b03          	push	#3
5297  0a10 4b00          	push	#0
5298  0a12 be8a          	ldw	x,_ind_U
5299  0a14 a60a          	ld	a,#10
5300  0a16 cd0000        	call	c_sdivx
5302  0a19 cd0201        	call	_int2ind_slkuf2
5304  0a1c 5b06          	addw	sp,#6
5305  0a1e               L1462:
5306                     ; 893 	if(bFL2)	int2ind_slkuf3(((time/60)*100)+(time%60),0,4,2,0,0,0);
5308  0a1e 3d6e          	tnz	_bFL2
5309  0a20 2765          	jreq	L7462
5312  0a22 4b00          	push	#0
5313  0a24 4b00          	push	#0
5314  0a26 4b00          	push	#0
5315  0a28 4b02          	push	#2
5316  0a2a 4b04          	push	#4
5317  0a2c 4b00          	push	#0
5318  0a2e be8e          	ldw	x,_time
5319  0a30 90ae003c      	ldw	y,#60
5320  0a34 65            	divw	x,y
5321  0a35 51            	exgw	x,y
5322  0a36 1f07          	ldw	(OFST+5,sp),x
5323  0a38 be8e          	ldw	x,_time
5324  0a3a 90ae003c      	ldw	y,#60
5325  0a3e 65            	divw	x,y
5326  0a3f 90ae0064      	ldw	y,#100
5327  0a43 cd0000        	call	c_imul
5329  0a46 72fb07        	addw	x,(OFST+5,sp)
5330  0a49 cd02c5        	call	_int2ind_slkuf3
5332  0a4c 5b06          	addw	sp,#6
5334  0a4e 2063          	jra	L1562
5335  0a50               L1362:
5336                     ; 883 		if(ind_U_set<1000) {
5338  0a50 9c            	rvf
5339  0a51 be86          	ldw	x,_ind_U_set
5340  0a53 a303e8        	cpw	x,#1000
5341  0a56 2e15          	jrsge	L3462
5342                     ; 884 			int2ind_slkuf2(ind_U_set,0,3,1,1,0,1);
5344  0a58 4b01          	push	#1
5345  0a5a 4b00          	push	#0
5346  0a5c 4b01          	push	#1
5347  0a5e 4b01          	push	#1
5348  0a60 4b03          	push	#3
5349  0a62 4b00          	push	#0
5350  0a64 be86          	ldw	x,_ind_U_set
5351  0a66 cd0201        	call	_int2ind_slkuf2
5353  0a69 5b06          	addw	sp,#6
5355  0a6b 20b1          	jra	L1462
5356  0a6d               L3462:
5357                     ; 886 			int2ind_slkuf2(ind_U_set/10,0,3,0,1,0,1);
5359  0a6d 4b01          	push	#1
5360  0a6f 4b00          	push	#0
5361  0a71 4b01          	push	#1
5362  0a73 4b00          	push	#0
5363  0a75 4b03          	push	#3
5364  0a77 4b00          	push	#0
5365  0a79 be86          	ldw	x,_ind_U_set
5366  0a7b a60a          	ld	a,#10
5367  0a7d cd0000        	call	c_sdivx
5369  0a80 cd0201        	call	_int2ind_slkuf2
5371  0a83 5b06          	addw	sp,#6
5372  0a85 2097          	jra	L1462
5373  0a87               L7462:
5374                     ; 894 	else 	int2ind_slkuf3(((time/60)*100)+(time%60),0,4,0,0,0,0);
5376  0a87 4b00          	push	#0
5377  0a89 4b00          	push	#0
5378  0a8b 4b00          	push	#0
5379  0a8d 4b00          	push	#0
5380  0a8f 4b04          	push	#4
5381  0a91 4b00          	push	#0
5382  0a93 be8e          	ldw	x,_time
5383  0a95 90ae003c      	ldw	y,#60
5384  0a99 65            	divw	x,y
5385  0a9a 51            	exgw	x,y
5386  0a9b 1f07          	ldw	(OFST+5,sp),x
5387  0a9d be8e          	ldw	x,_time
5388  0a9f 90ae003c      	ldw	y,#60
5389  0aa3 65            	divw	x,y
5390  0aa4 90ae0064      	ldw	y,#100
5391  0aa8 cd0000        	call	c_imul
5393  0aab 72fb07        	addw	x,(OFST+5,sp)
5394  0aae cd02c5        	call	_int2ind_slkuf3
5396  0ab1 5b06          	addw	sp,#6
5397  0ab3               L1562:
5398                     ; 896 	if(bFL5)dig2_[3]&=0xdf;
5400  0ab3 3d6f          	tnz	_bFL5
5401  0ab5 2603          	jrne	L211
5402  0ab7 cc0da9        	jp	L1262
5403  0aba               L211:
5406  0aba 721b0028      	bres	_dig2_+3,#5
5407  0abe aca90da9      	jpf	L1262
5408  0ac2               L3262:
5409                     ; 900 	if(tmblr_state==tsI)
5411  0ac2 b6a0          	ld	a,_tmblr_state
5412  0ac4 a102          	cp	a,#2
5413  0ac6 2703          	jreq	L411
5414  0ac8 cc0c38        	jp	L7562
5415  0acb               L411:
5416                     ; 903 		if((ind_fad_cnt)&&(but_state==bsOFF))
5418  0acb 3d80          	tnz	_ind_fad_cnt
5419  0acd 273b          	jreq	L1662
5421  0acf 3d9f          	tnz	_but_state
5422  0ad1 2637          	jrne	L1662
5423                     ; 905 			if(ind_I_set<=999)int2ind_slkuf1(ind_I_set,0,3,1,1,0,1);
5425  0ad3 9c            	rvf
5426  0ad4 be84          	ldw	x,_ind_I_set
5427  0ad6 a303e8        	cpw	x,#1000
5428  0ad9 2e15          	jrsge	L3662
5431  0adb 4b01          	push	#1
5432  0add 4b00          	push	#0
5433  0adf 4b01          	push	#1
5434  0ae1 4b01          	push	#1
5435  0ae3 4b03          	push	#3
5436  0ae5 4b00          	push	#0
5437  0ae7 be84          	ldw	x,_ind_I_set
5438  0ae9 cd015e        	call	_int2ind_slkuf1
5440  0aec 5b06          	addw	sp,#6
5442  0aee 204f          	jra	L7662
5443  0af0               L3662:
5444                     ; 906 			else int2ind_slkuf1(ind_I_set/10,0,3,0,1,0,1);
5446  0af0 4b01          	push	#1
5447  0af2 4b00          	push	#0
5448  0af4 4b01          	push	#1
5449  0af6 4b00          	push	#0
5450  0af8 4b03          	push	#3
5451  0afa 4b00          	push	#0
5452  0afc be84          	ldw	x,_ind_I_set
5453  0afe a60a          	ld	a,#10
5454  0b00 cd0000        	call	c_sdivx
5456  0b03 cd015e        	call	_int2ind_slkuf1
5458  0b06 5b06          	addw	sp,#6
5459  0b08 2035          	jra	L7662
5460  0b0a               L1662:
5461                     ; 910 			if(ind_I_set<=999)int2ind_slkuf1(ind_I_set,0,3,1,1,0,0);
5463  0b0a 9c            	rvf
5464  0b0b be84          	ldw	x,_ind_I_set
5465  0b0d a303e8        	cpw	x,#1000
5466  0b10 2e15          	jrsge	L1762
5469  0b12 4b00          	push	#0
5470  0b14 4b00          	push	#0
5471  0b16 4b01          	push	#1
5472  0b18 4b01          	push	#1
5473  0b1a 4b03          	push	#3
5474  0b1c 4b00          	push	#0
5475  0b1e be84          	ldw	x,_ind_I_set
5476  0b20 cd015e        	call	_int2ind_slkuf1
5478  0b23 5b06          	addw	sp,#6
5480  0b25 2018          	jra	L7662
5481  0b27               L1762:
5482                     ; 911 			else int2ind_slkuf1(ind_I_set/10,0,3,0,1,0,0);
5484  0b27 4b00          	push	#0
5485  0b29 4b00          	push	#0
5486  0b2b 4b01          	push	#1
5487  0b2d 4b00          	push	#0
5488  0b2f 4b03          	push	#3
5489  0b31 4b00          	push	#0
5490  0b33 be84          	ldw	x,_ind_I_set
5491  0b35 a60a          	ld	a,#10
5492  0b37 cd0000        	call	c_sdivx
5494  0b3a cd015e        	call	_int2ind_slkuf1
5496  0b3d 5b06          	addw	sp,#6
5497  0b3f               L7662:
5498                     ; 915 		if(ind_U_set<1000) {
5500  0b3f 9c            	rvf
5501  0b40 be86          	ldw	x,_ind_U_set
5502  0b42 a303e8        	cpw	x,#1000
5503  0b45 2e15          	jrsge	L5762
5504                     ; 916 			int2ind_slkuf2(ind_U_set,0,3,1,1,0,0);
5506  0b47 4b00          	push	#0
5507  0b49 4b00          	push	#0
5508  0b4b 4b01          	push	#1
5509  0b4d 4b01          	push	#1
5510  0b4f 4b03          	push	#3
5511  0b51 4b00          	push	#0
5512  0b53 be86          	ldw	x,_ind_U_set
5513  0b55 cd0201        	call	_int2ind_slkuf2
5515  0b58 5b06          	addw	sp,#6
5517  0b5a 2018          	jra	L7762
5518  0b5c               L5762:
5519                     ; 918 			int2ind_slkuf2(ind_U_set/10,0,3,0,1,0,0);
5521  0b5c 4b00          	push	#0
5522  0b5e 4b00          	push	#0
5523  0b60 4b01          	push	#1
5524  0b62 4b00          	push	#0
5525  0b64 4b03          	push	#3
5526  0b66 4b00          	push	#0
5527  0b68 be86          	ldw	x,_ind_U_set
5528  0b6a a60a          	ld	a,#10
5529  0b6c cd0000        	call	c_sdivx
5531  0b6f cd0201        	call	_int2ind_slkuf2
5533  0b72 5b06          	addw	sp,#6
5534  0b74               L7762:
5535                     ; 921 		dig1_[3]&=0xdf;
5537  0b74 721b0020      	bres	_dig1_+3,#5
5538                     ; 924 		if((ind_fad_cnt)&&(but_state==bsON))
5540  0b78 3d80          	tnz	_ind_fad_cnt
5541  0b7a 2761          	jreq	L1072
5543  0b7c b69f          	ld	a,_but_state
5544  0b7e a101          	cp	a,#1
5545  0b80 265b          	jrne	L1072
5546                     ; 926 			if(time_set==0xffff)
5548  0b82 be8c          	ldw	x,_time_set
5549  0b84 a3ffff        	cpw	x,#65535
5550  0b87 2624          	jrne	L3072
5551                     ; 928 				dig3[0]=0xbf;
5553  0b89 35bf0015      	mov	_dig3,#191
5554                     ; 929 				dig3[1]=0xbf;
5556  0b8d 35bf0016      	mov	_dig3+1,#191
5557                     ; 930 				dig3[2]=0xbf;
5559  0b91 35bf0017      	mov	_dig3+2,#191
5560                     ; 931 				dig3[3]=0xbf;
5562  0b95 35bf0018      	mov	_dig3+3,#191
5563                     ; 932 				dig3_[0]=0xff;
5565  0b99 35ff002d      	mov	_dig3_,#255
5566                     ; 933 				dig3_[1]=0xff;
5568  0b9d 35ff002e      	mov	_dig3_+1,#255
5569                     ; 934 				dig3_[2]=0xff;
5571  0ba1 35ff002f      	mov	_dig3_+2,#255
5572                     ; 935 				dig3_[3]=0xff;
5574  0ba5 35ff0030      	mov	_dig3_+3,#255
5576  0ba9 aca90da9      	jpf	L1262
5577  0bad               L3072:
5578                     ; 937 			else int2ind_slkuf3(((time_set/60)*100)+(time_set%60),0,4,2,0,0,1);
5580  0bad 4b01          	push	#1
5581  0baf 4b00          	push	#0
5582  0bb1 4b00          	push	#0
5583  0bb3 4b02          	push	#2
5584  0bb5 4b04          	push	#4
5585  0bb7 4b00          	push	#0
5586  0bb9 be8c          	ldw	x,_time_set
5587  0bbb 90ae003c      	ldw	y,#60
5588  0bbf 65            	divw	x,y
5589  0bc0 51            	exgw	x,y
5590  0bc1 1f07          	ldw	(OFST+5,sp),x
5591  0bc3 be8c          	ldw	x,_time_set
5592  0bc5 90ae003c      	ldw	y,#60
5593  0bc9 65            	divw	x,y
5594  0bca 90ae0064      	ldw	y,#100
5595  0bce cd0000        	call	c_imul
5597  0bd1 72fb07        	addw	x,(OFST+5,sp)
5598  0bd4 cd02c5        	call	_int2ind_slkuf3
5600  0bd7 5b06          	addw	sp,#6
5601  0bd9 aca90da9      	jpf	L1262
5602  0bdd               L1072:
5603                     ; 941 			if(time_set==0xffff)
5605  0bdd be8c          	ldw	x,_time_set
5606  0bdf a3ffff        	cpw	x,#65535
5607  0be2 2624          	jrne	L1172
5608                     ; 943 				dig3[0]=0xbf;
5610  0be4 35bf0015      	mov	_dig3,#191
5611                     ; 944 				dig3[1]=0xbf;
5613  0be8 35bf0016      	mov	_dig3+1,#191
5614                     ; 945 				dig3[2]=0xbf;
5616  0bec 35bf0017      	mov	_dig3+2,#191
5617                     ; 946 				dig3[3]=0xbf;
5619  0bf0 35bf0018      	mov	_dig3+3,#191
5620                     ; 947 				dig3_[0]=0xbf;
5622  0bf4 35bf002d      	mov	_dig3_,#191
5623                     ; 948 				dig3_[1]=0xbf;
5625  0bf8 35bf002e      	mov	_dig3_+1,#191
5626                     ; 949 				dig3_[2]=0xbf;
5628  0bfc 35bf002f      	mov	_dig3_+2,#191
5629                     ; 950 				dig3_[3]=0xbf;
5631  0c00 35bf0030      	mov	_dig3_+3,#191
5633  0c04 aca90da9      	jpf	L1262
5634  0c08               L1172:
5635                     ; 952 			else int2ind_slkuf3(((time_set/60)*100)+(time_set%60),0,4,2,0,0,0);
5637  0c08 4b00          	push	#0
5638  0c0a 4b00          	push	#0
5639  0c0c 4b00          	push	#0
5640  0c0e 4b02          	push	#2
5641  0c10 4b04          	push	#4
5642  0c12 4b00          	push	#0
5643  0c14 be8c          	ldw	x,_time_set
5644  0c16 90ae003c      	ldw	y,#60
5645  0c1a 65            	divw	x,y
5646  0c1b 51            	exgw	x,y
5647  0c1c 1f07          	ldw	(OFST+5,sp),x
5648  0c1e be8c          	ldw	x,_time_set
5649  0c20 90ae003c      	ldw	y,#60
5650  0c24 65            	divw	x,y
5651  0c25 90ae0064      	ldw	y,#100
5652  0c29 cd0000        	call	c_imul
5654  0c2c 72fb07        	addw	x,(OFST+5,sp)
5655  0c2f cd02c5        	call	_int2ind_slkuf3
5657  0c32 5b06          	addw	sp,#6
5658  0c34 aca90da9      	jpf	L1262
5659  0c38               L7562:
5660                     ; 955 	else if(tmblr_state==tsU)
5662  0c38 b6a0          	ld	a,_tmblr_state
5663  0c3a a101          	cp	a,#1
5664  0c3c 2703          	jreq	L611
5665  0c3e cc0da9        	jp	L1262
5666  0c41               L611:
5667                     ; 958 		if(ind_I_set<=999)int2ind_slkuf1(ind_I_set,0,3,1,1,0,0);
5669  0c41 9c            	rvf
5670  0c42 be84          	ldw	x,_ind_I_set
5671  0c44 a303e8        	cpw	x,#1000
5672  0c47 2e15          	jrsge	L1272
5675  0c49 4b00          	push	#0
5676  0c4b 4b00          	push	#0
5677  0c4d 4b01          	push	#1
5678  0c4f 4b01          	push	#1
5679  0c51 4b03          	push	#3
5680  0c53 4b00          	push	#0
5681  0c55 be84          	ldw	x,_ind_I_set
5682  0c57 cd015e        	call	_int2ind_slkuf1
5684  0c5a 5b06          	addw	sp,#6
5686  0c5c 2018          	jra	L3272
5687  0c5e               L1272:
5688                     ; 959 		else int2ind_slkuf1(ind_I_set/10,0,3,0,1,0,0);
5690  0c5e 4b00          	push	#0
5691  0c60 4b00          	push	#0
5692  0c62 4b01          	push	#1
5693  0c64 4b00          	push	#0
5694  0c66 4b03          	push	#3
5695  0c68 4b00          	push	#0
5696  0c6a be84          	ldw	x,_ind_I_set
5697  0c6c a60a          	ld	a,#10
5698  0c6e cd0000        	call	c_sdivx
5700  0c71 cd015e        	call	_int2ind_slkuf1
5702  0c74 5b06          	addw	sp,#6
5703  0c76               L3272:
5704                     ; 963 		if((!ind_fad_cnt)||(but_state!=bsOFF)) {
5706  0c76 3d80          	tnz	_ind_fad_cnt
5707  0c78 2704          	jreq	L7272
5709  0c7a 3d9f          	tnz	_but_state
5710  0c7c 2771          	jreq	L5272
5711  0c7e               L7272:
5712                     ; 964 			if(ind_U_set<1000) {
5714  0c7e 9c            	rvf
5715  0c7f be86          	ldw	x,_ind_U_set
5716  0c81 a303e8        	cpw	x,#1000
5717  0c84 2e15          	jrsge	L1372
5718                     ; 965 				int2ind_slkuf2(ind_U_set,0,3,1,1,0,0);
5720  0c86 4b00          	push	#0
5721  0c88 4b00          	push	#0
5722  0c8a 4b01          	push	#1
5723  0c8c 4b01          	push	#1
5724  0c8e 4b03          	push	#3
5725  0c90 4b00          	push	#0
5726  0c92 be86          	ldw	x,_ind_U_set
5727  0c94 cd0201        	call	_int2ind_slkuf2
5729  0c97 5b06          	addw	sp,#6
5731  0c99 2018          	jra	L5372
5732  0c9b               L1372:
5733                     ; 967 				int2ind_slkuf2(ind_U_set/10,0,3,0,1,0,0);
5735  0c9b 4b00          	push	#0
5736  0c9d 4b00          	push	#0
5737  0c9f 4b01          	push	#1
5738  0ca1 4b00          	push	#0
5739  0ca3 4b03          	push	#3
5740  0ca5 4b00          	push	#0
5741  0ca7 be86          	ldw	x,_ind_U_set
5742  0ca9 a60a          	ld	a,#10
5743  0cab cd0000        	call	c_sdivx
5745  0cae cd0201        	call	_int2ind_slkuf2
5747  0cb1 5b06          	addw	sp,#6
5748  0cb3               L5372:
5749                     ; 976 		dig2_[3]&=0xdf;
5751  0cb3 721b0028      	bres	_dig2_+3,#5
5752                     ; 979 		if((ind_fad_cnt)&&(but_state==bsON))
5754  0cb7 3d80          	tnz	_ind_fad_cnt
5755  0cb9 2603cc0d54    	jreq	L3472
5757  0cbe b69f          	ld	a,_but_state
5758  0cc0 a101          	cp	a,#1
5759  0cc2 26f7          	jrne	L3472
5760                     ; 981 			if(time_set==0xffff)
5762  0cc4 be8c          	ldw	x,_time_set
5763  0cc6 a3ffff        	cpw	x,#65535
5764  0cc9 265b          	jrne	L5472
5765                     ; 983 				dig3[0]=0xbf;
5767  0ccb 35bf0015      	mov	_dig3,#191
5768                     ; 984 				dig3[1]=0xbf;
5770  0ccf 35bf0016      	mov	_dig3+1,#191
5771                     ; 985 				dig3[2]=0xbf;
5773  0cd3 35bf0017      	mov	_dig3+2,#191
5774                     ; 986 				dig3[3]=0xbf;
5776  0cd7 35bf0018      	mov	_dig3+3,#191
5777                     ; 987 				dig3_[0]=0xff;
5779  0cdb 35ff002d      	mov	_dig3_,#255
5780                     ; 988 				dig3_[1]=0xff;
5782  0cdf 35ff002e      	mov	_dig3_+1,#255
5783                     ; 989 				dig3_[2]=0xff;
5785  0ce3 35ff002f      	mov	_dig3_+2,#255
5786                     ; 990 				dig3_[3]=0xff;
5788  0ce7 35ff0030      	mov	_dig3_+3,#255
5790  0ceb aca90da9      	jpf	L1262
5791  0cef               L5272:
5792                     ; 970 			if(ind_U_set<1000) {
5794  0cef 9c            	rvf
5795  0cf0 be86          	ldw	x,_ind_U_set
5796  0cf2 a303e8        	cpw	x,#1000
5797  0cf5 2e15          	jrsge	L7372
5798                     ; 971 				int2ind_slkuf2(ind_U_set,0,3,1,1,0,1);
5800  0cf7 4b01          	push	#1
5801  0cf9 4b00          	push	#0
5802  0cfb 4b01          	push	#1
5803  0cfd 4b01          	push	#1
5804  0cff 4b03          	push	#3
5805  0d01 4b00          	push	#0
5806  0d03 be86          	ldw	x,_ind_U_set
5807  0d05 cd0201        	call	_int2ind_slkuf2
5809  0d08 5b06          	addw	sp,#6
5811  0d0a 20a7          	jra	L5372
5812  0d0c               L7372:
5813                     ; 973 				int2ind_slkuf2(ind_U_set/10,0,3,0,1,0,1);
5815  0d0c 4b01          	push	#1
5816  0d0e 4b00          	push	#0
5817  0d10 4b01          	push	#1
5818  0d12 4b00          	push	#0
5819  0d14 4b03          	push	#3
5820  0d16 4b00          	push	#0
5821  0d18 be86          	ldw	x,_ind_U_set
5822  0d1a a60a          	ld	a,#10
5823  0d1c cd0000        	call	c_sdivx
5825  0d1f cd0201        	call	_int2ind_slkuf2
5827  0d22 5b06          	addw	sp,#6
5828  0d24 208d          	jra	L5372
5829  0d26               L5472:
5830                     ; 992 			else int2ind_slkuf3(((time_set/60)*100)+(time_set%60),0,4,2,0,0,1);
5832  0d26 4b01          	push	#1
5833  0d28 4b00          	push	#0
5834  0d2a 4b00          	push	#0
5835  0d2c 4b02          	push	#2
5836  0d2e 4b04          	push	#4
5837  0d30 4b00          	push	#0
5838  0d32 be8c          	ldw	x,_time_set
5839  0d34 90ae003c      	ldw	y,#60
5840  0d38 65            	divw	x,y
5841  0d39 51            	exgw	x,y
5842  0d3a 1f07          	ldw	(OFST+5,sp),x
5843  0d3c be8c          	ldw	x,_time_set
5844  0d3e 90ae003c      	ldw	y,#60
5845  0d42 65            	divw	x,y
5846  0d43 90ae0064      	ldw	y,#100
5847  0d47 cd0000        	call	c_imul
5849  0d4a 72fb07        	addw	x,(OFST+5,sp)
5850  0d4d cd02c5        	call	_int2ind_slkuf3
5852  0d50 5b06          	addw	sp,#6
5853  0d52 2055          	jra	L1262
5854  0d54               L3472:
5855                     ; 996 			if(time_set==0xffff)
5857  0d54 be8c          	ldw	x,_time_set
5858  0d56 a3ffff        	cpw	x,#65535
5859  0d59 2622          	jrne	L3572
5860                     ; 998 				dig3[0]=0xbf;
5862  0d5b 35bf0015      	mov	_dig3,#191
5863                     ; 999 				dig3[1]=0xbf;
5865  0d5f 35bf0016      	mov	_dig3+1,#191
5866                     ; 1000 				dig3[2]=0xbf;
5868  0d63 35bf0017      	mov	_dig3+2,#191
5869                     ; 1001 				dig3[3]=0xbf;
5871  0d67 35bf0018      	mov	_dig3+3,#191
5872                     ; 1002 				dig3_[0]=0xbf;
5874  0d6b 35bf002d      	mov	_dig3_,#191
5875                     ; 1003 				dig3_[1]=0xbf;
5877  0d6f 35bf002e      	mov	_dig3_+1,#191
5878                     ; 1004 				dig3_[2]=0xbf;
5880  0d73 35bf002f      	mov	_dig3_+2,#191
5881                     ; 1005 				dig3_[3]=0xbf;
5883  0d77 35bf0030      	mov	_dig3_+3,#191
5885  0d7b 202c          	jra	L1262
5886  0d7d               L3572:
5887                     ; 1007 			else int2ind_slkuf3(((time_set/60)*100)+(time_set%60),0,4,2,0,0,0);
5889  0d7d 4b00          	push	#0
5890  0d7f 4b00          	push	#0
5891  0d81 4b00          	push	#0
5892  0d83 4b02          	push	#2
5893  0d85 4b04          	push	#4
5894  0d87 4b00          	push	#0
5895  0d89 be8c          	ldw	x,_time_set
5896  0d8b 90ae003c      	ldw	y,#60
5897  0d8f 65            	divw	x,y
5898  0d90 51            	exgw	x,y
5899  0d91 1f07          	ldw	(OFST+5,sp),x
5900  0d93 be8c          	ldw	x,_time_set
5901  0d95 90ae003c      	ldw	y,#60
5902  0d99 65            	divw	x,y
5903  0d9a 90ae0064      	ldw	y,#100
5904  0d9e cd0000        	call	c_imul
5906  0da1 72fb07        	addw	x,(OFST+5,sp)
5907  0da4 cd02c5        	call	_int2ind_slkuf3
5909  0da7 5b06          	addw	sp,#6
5910  0da9               L1262:
5911                     ; 1013 }
5914  0da9 85            	popw	x
5915  0daa 81            	ret
5944                     ; 1016 void can_tx_hndl(void)
5944                     ; 1017 {
5945                     	switch	.text
5946  0dab               _can_tx_hndl:
5950                     ; 1019 if(bTX_FREE)
5952  0dab 3d35          	tnz	_bTX_FREE
5953  0dad 2757          	jreq	L7672
5954                     ; 1021 	if(can_buff_rd_ptr!=can_buff_wr_ptr)
5956  0daf b62a          	ld	a,_can_buff_rd_ptr
5957  0db1 b12b          	cp	a,_can_buff_wr_ptr
5958  0db3 275f          	jreq	L5772
5959                     ; 1023 		bTX_FREE=0;
5961  0db5 3f35          	clr	_bTX_FREE
5962                     ; 1025 		CAN->PSR= 0;
5964  0db7 725f5427      	clr	21543
5965                     ; 1026 		CAN->Page.TxMailbox.MDLCR=8;
5967  0dbb 35085429      	mov	21545,#8
5968                     ; 1027 		CAN->Page.TxMailbox.MIDR1=can_out_buff[can_buff_rd_ptr][0];
5970  0dbf b62a          	ld	a,_can_buff_rd_ptr
5971  0dc1 97            	ld	xl,a
5972  0dc2 a610          	ld	a,#16
5973  0dc4 42            	mul	x,a
5974  0dc5 e62c          	ld	a,(_can_out_buff,x)
5975  0dc7 c7542a        	ld	21546,a
5976                     ; 1028 		CAN->Page.TxMailbox.MIDR2=can_out_buff[can_buff_rd_ptr][1];
5978  0dca b62a          	ld	a,_can_buff_rd_ptr
5979  0dcc 97            	ld	xl,a
5980  0dcd a610          	ld	a,#16
5981  0dcf 42            	mul	x,a
5982  0dd0 e62d          	ld	a,(_can_out_buff+1,x)
5983  0dd2 c7542b        	ld	21547,a
5984                     ; 1030 		memcpy(&CAN->Page.TxMailbox.MDAR1, &can_out_buff[can_buff_rd_ptr][2],8);
5986  0dd5 b62a          	ld	a,_can_buff_rd_ptr
5987  0dd7 97            	ld	xl,a
5988  0dd8 a610          	ld	a,#16
5989  0dda 42            	mul	x,a
5990  0ddb 01            	rrwa	x,a
5991  0ddc ab2e          	add	a,#_can_out_buff+2
5992  0dde 2401          	jrnc	L221
5993  0de0 5c            	incw	x
5994  0de1               L221:
5995  0de1 5f            	clrw	x
5996  0de2 97            	ld	xl,a
5997  0de3 bf00          	ldw	c_x,x
5998  0de5 ae0008        	ldw	x,#8
5999  0de8               L421:
6000  0de8 5a            	decw	x
6001  0de9 92d600        	ld	a,([c_x],x)
6002  0dec d7542e        	ld	(21550,x),a
6003  0def 5d            	tnzw	x
6004  0df0 26f6          	jrne	L421
6005                     ; 1032 		can_buff_rd_ptr++;
6007  0df2 3c2a          	inc	_can_buff_rd_ptr
6008                     ; 1033 		if(can_buff_rd_ptr>3)can_buff_rd_ptr=0;
6010  0df4 b62a          	ld	a,_can_buff_rd_ptr
6011  0df6 a104          	cp	a,#4
6012  0df8 2502          	jrult	L3772
6015  0dfa 3f2a          	clr	_can_buff_rd_ptr
6016  0dfc               L3772:
6017                     ; 1035 		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;
6019  0dfc 72105428      	bset	21544,#0
6020                     ; 1036 		CAN->IER|=(1<<0);
6022  0e00 72105425      	bset	21541,#0
6023  0e04 200e          	jra	L5772
6024  0e06               L7672:
6025                     ; 1041 	tx_busy_cnt++;
6027  0e06 3c29          	inc	_tx_busy_cnt
6028                     ; 1042 	if(tx_busy_cnt>=100)
6030  0e08 b629          	ld	a,_tx_busy_cnt
6031  0e0a a164          	cp	a,#100
6032  0e0c 2506          	jrult	L5772
6033                     ; 1044 		tx_busy_cnt=0;
6035  0e0e 3f29          	clr	_tx_busy_cnt
6036                     ; 1045 		bTX_FREE=1;
6038  0e10 35010035      	mov	_bTX_FREE,#1
6039  0e14               L5772:
6040                     ; 1048 }
6043  0e14 81            	ret
6066                     ; 1052 void t4_init(void){
6067                     	switch	.text
6068  0e15               _t4_init:
6072                     ; 1053 	TIM4->PSCR = 7;
6074  0e15 35075345      	mov	21317,#7
6075                     ; 1054 	TIM4->ARR= 66;
6077  0e19 35425346      	mov	21318,#66
6078                     ; 1055 	TIM4->IER|= TIM4_IER_UIE;					// enable break interrupt
6080  0e1d 72105341      	bset	21313,#0
6081                     ; 1057 	TIM4->CR1=(TIM4_CR1_URS | TIM4_CR1_CEN | TIM4_CR1_ARPE);	
6083  0e21 35855340      	mov	21312,#133
6084                     ; 1059 }
6087  0e25 81            	ret
6110                     ; 1062 void t1_init(void)
6110                     ; 1063 {
6111                     	switch	.text
6112  0e26               _t1_init:
6116                     ; 1064 TIM1->ARRH= 0x03;
6118  0e26 35035262      	mov	21090,#3
6119                     ; 1065 TIM1->ARRL= 0xff;
6121  0e2a 35ff5263      	mov	21091,#255
6122                     ; 1066 TIM1->CCR1H= 0x00;	
6124  0e2e 725f5265      	clr	21093
6125                     ; 1067 TIM1->CCR1L= 0xff;
6127  0e32 35ff5266      	mov	21094,#255
6128                     ; 1068 TIM1->CCR2H= 0x00;	
6130  0e36 725f5267      	clr	21095
6131                     ; 1069 TIM1->CCR2L= 0x00;
6133  0e3a 725f5268      	clr	21096
6134                     ; 1071 TIM1->CCMR1= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
6136  0e3e 35685258      	mov	21080,#104
6137                     ; 1072 TIM1->CCMR2= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
6139  0e42 35685259      	mov	21081,#104
6140                     ; 1073 TIM1->CCER1= TIM1_CCER1_CC1E | TIM1_CCER1_CC2E ; //OC1, OC2 output pins enabled
6142  0e46 3511525c      	mov	21084,#17
6143                     ; 1075 TIM1->CR1=(TIM1_CR1_CEN | TIM1_CR1_ARPE);
6145  0e4a 35815250      	mov	21072,#129
6146                     ; 1076 TIM1->BKR|= TIM1_BKR_AOE;
6148  0e4e 721c526d      	bset	21101,#6
6149                     ; 1077 }
6152  0e52 81            	ret
6206                     ; 1085 @far @interrupt void TIM4_UPD_Interrupt (void) 
6206                     ; 1086 {
6208                     	switch	.text
6209  0e53               f_TIM4_UPD_Interrupt:
6211  0e53 3b0002        	push	c_x+2
6212  0e56 be00          	ldw	x,c_x
6213  0e58 89            	pushw	x
6214  0e59 3b0002        	push	c_y+2
6215  0e5c be00          	ldw	x,c_y
6216  0e5e 89            	pushw	x
6219                     ; 1087 TIM4->SR1&=~TIM4_SR1_UIF;
6221  0e5f 72115342      	bres	21314,#0
6222                     ; 1093 cnt_T4++;
6224  0e63 3c83          	inc	_cnt_T4
6225                     ; 1094 if(cnt_T4>=3)cnt_T4=0;
6227  0e65 b683          	ld	a,_cnt_T4
6228  0e67 a103          	cp	a,#3
6229  0e69 2502          	jrult	L1303
6232  0e6b 3f83          	clr	_cnt_T4
6233  0e6d               L1303:
6234                     ; 1098 if(!cnt_T4)
6236  0e6d 3d83          	tnz	_cnt_T4
6237  0e6f 2655          	jrne	L3303
6238                     ; 1100 	strob_cnt++;
6240  0e71 3c82          	inc	_strob_cnt
6241                     ; 1101 	if(strob_cnt>=4)strob_cnt=0;
6243  0e73 b682          	ld	a,_strob_cnt
6244  0e75 a104          	cp	a,#4
6245  0e77 2502          	jrult	L5303
6248  0e79 3f82          	clr	_strob_cnt
6249  0e7b               L5303:
6250                     ; 1102 	(GPIOB->ODR)=(GPIOB->ODR)|0x0f;
6252  0e7b c65005        	ld	a,20485
6253  0e7e aa0f          	or	a,#15
6254  0e80 c75005        	ld	20485,a
6255                     ; 1104 	GPIOD->ODR=dig1[strob_cnt];
6257  0e83 b682          	ld	a,_strob_cnt
6258  0e85 5f            	clrw	x
6259  0e86 97            	ld	xl,a
6260  0e87 e605          	ld	a,(_dig1,x)
6261  0e89 c7500f        	ld	20495,a
6262                     ; 1105 	spi(dig2[strob_cnt]);
6264  0e8c b682          	ld	a,_strob_cnt
6265  0e8e 5f            	clrw	x
6266  0e8f 97            	ld	xl,a
6267  0e90 e60d          	ld	a,(_dig2,x)
6268  0e92 cd009f        	call	_spi
6270                     ; 1106 	GPIOC->ODR&=~(1<<2);
6272  0e95 7215500a      	bres	20490,#2
6273                     ; 1107 	GPIOC->ODR|=(1<<2);
6275  0e99 7214500a      	bset	20490,#2
6276                     ; 1108 	spi(dig3[strob_cnt]);
6278  0e9d b682          	ld	a,_strob_cnt
6279  0e9f 5f            	clrw	x
6280  0ea0 97            	ld	xl,a
6281  0ea1 e615          	ld	a,(_dig3,x)
6282  0ea3 cd009f        	call	_spi
6284                     ; 1109 	GPIOC->ODR&=~(1<<3);
6286  0ea6 7217500a      	bres	20490,#3
6287                     ; 1110 	GPIOC->ODR|=(1<<3);
6289  0eaa 7216500a      	bset	20490,#3
6290                     ; 1112 	(GPIOB->ODR)&=~(1<<(3-strob_cnt));
6292  0eae a603          	ld	a,#3
6293  0eb0 b082          	sub	a,_strob_cnt
6294  0eb2 5f            	clrw	x
6295  0eb3 97            	ld	xl,a
6296  0eb4 a601          	ld	a,#1
6297  0eb6 5d            	tnzw	x
6298  0eb7 2704          	jreq	L431
6299  0eb9               L631:
6300  0eb9 48            	sll	a
6301  0eba 5a            	decw	x
6302  0ebb 26fc          	jrne	L631
6303  0ebd               L431:
6304  0ebd 43            	cpl	a
6305  0ebe c45005        	and	a,20485
6306  0ec1 c75005        	ld	20485,a
6308  0ec4 2031          	jra	L7303
6309  0ec6               L3303:
6310                     ; 1114 else if(cnt_T4==2)
6312  0ec6 b683          	ld	a,_cnt_T4
6313  0ec8 a102          	cp	a,#2
6314  0eca 262b          	jrne	L7303
6315                     ; 1116 	GPIOD->ODR=dig1_[strob_cnt];
6317  0ecc b682          	ld	a,_strob_cnt
6318  0ece 5f            	clrw	x
6319  0ecf 97            	ld	xl,a
6320  0ed0 e61d          	ld	a,(_dig1_,x)
6321  0ed2 c7500f        	ld	20495,a
6322                     ; 1117 	spi(dig2_[strob_cnt]);
6324  0ed5 b682          	ld	a,_strob_cnt
6325  0ed7 5f            	clrw	x
6326  0ed8 97            	ld	xl,a
6327  0ed9 e625          	ld	a,(_dig2_,x)
6328  0edb cd009f        	call	_spi
6330                     ; 1118 	GPIOC->ODR&=~(1<<2);
6332  0ede 7215500a      	bres	20490,#2
6333                     ; 1119 	GPIOC->ODR|=(1<<2);
6335  0ee2 7214500a      	bset	20490,#2
6336                     ; 1120 	spi(dig3_[strob_cnt]);
6338  0ee6 b682          	ld	a,_strob_cnt
6339  0ee8 5f            	clrw	x
6340  0ee9 97            	ld	xl,a
6341  0eea e62d          	ld	a,(_dig3_,x)
6342  0eec cd009f        	call	_spi
6344                     ; 1121 	GPIOC->ODR&=~(1<<3);
6346  0eef 7217500a      	bres	20490,#3
6347                     ; 1122 	GPIOC->ODR|=(1<<3);
6349  0ef3 7216500a      	bset	20490,#3
6350  0ef7               L7303:
6351                     ; 1126 if(++t0_cnt0>=12)
6353  0ef7 3c00          	inc	_t0_cnt0
6354  0ef9 b600          	ld	a,_t0_cnt0
6355  0efb a10c          	cp	a,#12
6356  0efd 2556          	jrult	L3403
6357                     ; 1128 	b100Hz=1;
6359  0eff 72100010      	bset	_b100Hz
6360                     ; 1129 	t0_cnt0=0;
6362  0f03 3f00          	clr	_t0_cnt0
6363                     ; 1130 	if(++t0_cnt1>=10)
6365  0f05 3c01          	inc	_t0_cnt1
6366  0f07 b601          	ld	a,_t0_cnt1
6367  0f09 a10a          	cp	a,#10
6368  0f0b 2506          	jrult	L5403
6369                     ; 1132 		t0_cnt1=0;
6371  0f0d 3f01          	clr	_t0_cnt1
6372                     ; 1133 		b10Hz=1;
6374  0f0f 7210000f      	bset	_b10Hz
6375  0f13               L5403:
6376                     ; 1135 	if(++t0_cnt2>=20)
6378  0f13 3c02          	inc	_t0_cnt2
6379  0f15 b602          	ld	a,_t0_cnt2
6380  0f17 a114          	cp	a,#20
6381  0f19 2512          	jrult	L7403
6382                     ; 1137 		t0_cnt2=0;
6384  0f1b 3f02          	clr	_t0_cnt2
6385                     ; 1138 		b5Hz=1;
6387  0f1d 7210000e      	bset	_b5Hz
6388                     ; 1139 		if(bFL5)bFL5=0;
6390  0f21 3d6f          	tnz	_bFL5
6391  0f23 2704          	jreq	L1503
6394  0f25 3f6f          	clr	_bFL5
6396  0f27 2004          	jra	L7403
6397  0f29               L1503:
6398                     ; 1140 		else bFL5=1;
6400  0f29 3501006f      	mov	_bFL5,#1
6401  0f2d               L7403:
6402                     ; 1142 	if(++t0_cnt4>=50)
6404  0f2d 3c04          	inc	_t0_cnt4
6405  0f2f b604          	ld	a,_t0_cnt4
6406  0f31 a132          	cp	a,#50
6407  0f33 2512          	jrult	L5503
6408                     ; 1144 		t0_cnt4=0;
6410  0f35 3f04          	clr	_t0_cnt4
6411                     ; 1145 		b2Hz=1;
6413  0f37 7210000d      	bset	_b2Hz
6414                     ; 1146 		if(bFL2)bFL2=0;
6416  0f3b 3d6e          	tnz	_bFL2
6417  0f3d 2704          	jreq	L7503
6420  0f3f 3f6e          	clr	_bFL2
6422  0f41 2004          	jra	L5503
6423  0f43               L7503:
6424                     ; 1147 		else bFL2=1;
6426  0f43 3501006e      	mov	_bFL2,#1
6427  0f47               L5503:
6428                     ; 1149 	if(++t0_cnt3>=100)
6430  0f47 3c03          	inc	_t0_cnt3
6431  0f49 b603          	ld	a,_t0_cnt3
6432  0f4b a164          	cp	a,#100
6433  0f4d 2506          	jrult	L3403
6434                     ; 1151 		t0_cnt3=0;
6436  0f4f 3f03          	clr	_t0_cnt3
6437                     ; 1152 		b1Hz=1;
6439  0f51 7210000c      	bset	_b1Hz
6440  0f55               L3403:
6441                     ; 1156 if(GPIOB->IDR&=(1<<6))encApin=1;
6443  0f55 c65006        	ld	a,20486
6444  0f58 a440          	and	a,#64
6445  0f5a c75006        	ld	20486,a
6446  0f5d 2706          	jreq	L5603
6449  0f5f 72100009      	bset	_encApin
6451  0f63 2004          	jra	L7603
6452  0f65               L5603:
6453                     ; 1157 else encApin=0;
6455  0f65 72110009      	bres	_encApin
6456  0f69               L7603:
6457                     ; 1159 if(GPIOB->IDR&=(1<<4))encBpin=1;
6459  0f69 c65006        	ld	a,20486
6460  0f6c a410          	and	a,#16
6461  0f6e c75006        	ld	20486,a
6462  0f71 2706          	jreq	L1703
6465  0f73 72100008      	bset	_encBpin
6467  0f77 2004          	jra	L3703
6468  0f79               L1703:
6469                     ; 1160 else encBpin=0;
6471  0f79 72110008      	bres	_encBpin
6472  0f7d               L3703:
6473                     ; 1162 if(encApin_old==encApin)
6475  0f7d 7201000707    	btjf	_encApin_old,L041
6476  0f82 720100093b    	btjf	_encApin,L5703
6477  0f87 2005          	jra	L241
6478  0f89               L041:
6479  0f89 7200000934    	btjt	_encApin,L5703
6480  0f8e               L241:
6481                     ; 1164 	if(encAcnt<3)
6483  0f8e b611          	ld	a,_encAcnt
6484  0f90 a103          	cp	a,#3
6485  0f92 2430          	jruge	L7013
6486                     ; 1166 		encAcnt++;
6488  0f94 3c11          	inc	_encAcnt
6489                     ; 1167 		if(encAcnt>=3)
6491  0f96 b611          	ld	a,_encAcnt
6492  0f98 a103          	cp	a,#3
6493  0f9a 2528          	jrult	L7013
6494                     ; 1169 			encA=encApin;
6496                     	btst		_encApin
6497  0fa1 90110005      	bccm	_encA
6498                     ; 1170 			if(encA==encB)encCW=1;
6500  0fa5 7201000507    	btjf	_encA,L441
6501  0faa 720100040d    	btjf	_encB,L3013
6502  0faf 2005          	jra	L641
6503  0fb1               L441:
6504  0fb1 7200000406    	btjt	_encB,L3013
6505  0fb6               L641:
6508  0fb6 72100003      	bset	_encCW
6510  0fba 2008          	jra	L7013
6511  0fbc               L3013:
6512                     ; 1171 			else encOW=1;
6514  0fbc 72100002      	bset	_encOW
6515  0fc0 2002          	jra	L7013
6516  0fc2               L5703:
6517                     ; 1175 else encAcnt=0;
6519  0fc2 3f11          	clr	_encAcnt
6520  0fc4               L7013:
6521                     ; 1177 if(encBpin_old==encBpin)
6523  0fc4 7201000607    	btjf	_encBpin_old,L051
6524  0fc9 7201000820    	btjf	_encBpin,L1113
6525  0fce 2005          	jra	L251
6526  0fd0               L051:
6527  0fd0 7200000819    	btjt	_encBpin,L1113
6528  0fd5               L251:
6529                     ; 1179 	if(encBcnt<3)
6531  0fd5 b610          	ld	a,_encBcnt
6532  0fd7 a103          	cp	a,#3
6533  0fd9 2415          	jruge	L7113
6534                     ; 1181 		encBcnt++;
6536  0fdb 3c10          	inc	_encBcnt
6537                     ; 1182 		if(encBcnt>=3)
6539  0fdd b610          	ld	a,_encBcnt
6540  0fdf a103          	cp	a,#3
6541  0fe1 250d          	jrult	L7113
6542                     ; 1184 			encB=encBpin;
6544                     	btst		_encBpin
6545  0fe8 90110004      	bccm	_encB
6546  0fec 2002          	jra	L7113
6547  0fee               L1113:
6548                     ; 1188 else encBcnt=0;
6550  0fee 3f10          	clr	_encBcnt
6551  0ff0               L7113:
6552                     ; 1193 encApin_old=encApin;
6554                     	btst		_encApin
6555  0ff5 90110007      	bccm	_encApin_old
6556                     ; 1194 encBpin_old=encBpin;
6558                     	btst		_encBpin
6559  0ffe 90110006      	bccm	_encBpin_old
6560                     ; 1196 }
6563  1002 85            	popw	x
6564  1003 bf00          	ldw	c_y,x
6565  1005 320002        	pop	c_y+2
6566  1008 85            	popw	x
6567  1009 bf00          	ldw	c_x,x
6568  100b 320002        	pop	c_x+2
6569  100e 80            	iret
6594                     ; 1199 @far @interrupt void CAN_RX_Interrupt (void) 
6594                     ; 1200 {
6595                     	switch	.text
6596  100f               f_CAN_RX_Interrupt:
6600                     ; 1202 CAN->PSR= 7;	
6602  100f 35075427      	mov	21543,#7
6603                     ; 1207 memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
6605  1013 ae000e        	ldw	x,#14
6606  1016               L651:
6607  1016 d65427        	ld	a,(21543,x)
6608  1019 e717          	ld	(_mess-1,x),a
6609  101b 5a            	decw	x
6610  101c 26f8          	jrne	L651
6611                     ; 1218 bCAN_RX=1;
6613  101e 35010036      	mov	_bCAN_RX,#1
6614                     ; 1219 CAN->RFR|=(1<<5);
6616  1022 721a5424      	bset	21540,#5
6617                     ; 1221 }
6620  1026 80            	iret
6643                     ; 1224 @far @interrupt void CAN_TX_Interrupt (void) 
6643                     ; 1225 {
6644                     	switch	.text
6645  1027               f_CAN_TX_Interrupt:
6649                     ; 1226 if((CAN->TSR)&(1<<0))
6651  1027 c65422        	ld	a,21538
6652  102a a501          	bcp	a,#1
6653  102c 2708          	jreq	L1413
6654                     ; 1228 	bTX_FREE=1;	
6656  102e 35010035      	mov	_bTX_FREE,#1
6657                     ; 1230 	CAN->TSR|=(1<<0);
6659  1032 72105422      	bset	21538,#0
6660  1036               L1413:
6661                     ; 1232 }
6664  1036 80            	iret
6697                     ; 1235 @far @interrupt void ADC2_EOC_Interrupt (void) {
6698                     	switch	.text
6699  1037               f_ADC2_EOC_Interrupt:
6701       00000004      OFST:	set	4
6702  1037 5204          	subw	sp,#4
6705                     ; 1239 GPIOE->ODR|=(1<<6);
6707  1039 721c5014      	bset	20500,#6
6708                     ; 1241 ADC2->CSR&=~(1<<7);
6710  103d 721f5400      	bres	21504,#7
6711                     ; 1243 temp_adc=(((short)(ADC2->DRH))<<8)+((short)(ADC2->DRL));
6713  1041 c65405        	ld	a,21509
6714  1044 5f            	clrw	x
6715  1045 97            	ld	xl,a
6716  1046 1f01          	ldw	(OFST-3,sp),x
6717  1048 c65404        	ld	a,21508
6718  104b 5f            	clrw	x
6719  104c 97            	ld	xl,a
6720  104d 4f            	clr	a
6721  104e 02            	rlwa	x,a
6722  104f 72fb01        	addw	x,(OFST-3,sp)
6723                     ; 1251 GPIOE->ODR&=~(1<<6);
6725  1052 721d5014      	bres	20500,#6
6726                     ; 1253 }
6729  1056 5b04          	addw	sp,#4
6730  1058 80            	iret
6775                     ; 1261 main()
6775                     ; 1262 {
6777                     	switch	.text
6778  1059               _main:
6780  1059 88            	push	a
6781       00000001      OFST:	set	1
6784                     ; 1264 CLK->ECKR|=1;
6786  105a 721050c1      	bset	20673,#0
6788  105e               L3713:
6789                     ; 1265 while((CLK->ECKR & 2) == 0);
6791  105e c650c1        	ld	a,20673
6792  1061 a502          	bcp	a,#2
6793  1063 27f9          	jreq	L3713
6794                     ; 1266 CLK->SWCR|=2;
6796  1065 721250c5      	bset	20677,#1
6797                     ; 1267 CLK->SWR=0xB4;
6799  1069 35b450c4      	mov	20676,#180
6800                     ; 1269 delay_ms(200);
6802  106d ae00c8        	ldw	x,#200
6803  1070 cd0000        	call	_delay_ms
6805                     ; 1270 FLASH_DUKR=0xae;
6807  1073 35ae5064      	mov	_FLASH_DUKR,#174
6808                     ; 1271 FLASH_DUKR=0x56;
6810  1077 35565064      	mov	_FLASH_DUKR,#86
6811                     ; 1272 enableInterrupts();
6814  107b 9a            rim
6816                     ; 1274 GPIOB->DDR|=0x0f;
6819  107c c65007        	ld	a,20487
6820  107f aa0f          	or	a,#15
6821  1081 c75007        	ld	20487,a
6822                     ; 1275 GPIOB->CR1&=~(0x0f);
6824  1084 c65008        	ld	a,20488
6825  1087 a4f0          	and	a,#240
6826  1089 c75008        	ld	20488,a
6827                     ; 1276 GPIOB->CR2&=~(0x0f);
6829  108c c65009        	ld	a,20489
6830  108f a4f0          	and	a,#240
6831  1091 c75009        	ld	20489,a
6832                     ; 1278 GPIOD->DDR|=0xff;
6834  1094 c65011        	ld	a,20497
6835  1097 aaff          	or	a,#255
6836  1099 c75011        	ld	20497,a
6837                     ; 1279 GPIOD->CR1&=~(0xff);
6839  109c c65012        	ld	a,20498
6840  109f a400          	and	a,#0
6841  10a1 c75012        	ld	20498,a
6842                     ; 1280 GPIOD->CR2&=~(0xff);
6844  10a4 c65013        	ld	a,20499
6845  10a7 a400          	and	a,#0
6846  10a9 c75013        	ld	20499,a
6847                     ; 1282 GPIOB->DDR&=~(1<<5);
6849  10ac 721b5007      	bres	20487,#5
6850                     ; 1283 GPIOB->CR1|=(1<<5);
6852  10b0 721a5008      	bset	20488,#5
6853                     ; 1285 GPIOB->DDR&=~(1<<4);
6855  10b4 72195007      	bres	20487,#4
6856                     ; 1286 GPIOB->CR1|=(1<<4);
6858  10b8 72185008      	bset	20488,#4
6859                     ; 1289 GPIOB->DDR&=~(1<<6);
6861  10bc 721d5007      	bres	20487,#6
6862                     ; 1290 GPIOB->CR1|=(1<<6);/*
6864  10c0 721c5008      	bset	20488,#6
6865                     ; 1293 GPIOB->DDR&=~(1<<7);
6867  10c4 721f5007      	bres	20487,#7
6868                     ; 1294 GPIOB->CR1|=(1<<7);
6870  10c8 721e5008      	bset	20488,#7
6871                     ; 1296 GPIOE->DDR&=~(1<<0);
6873  10cc 72115016      	bres	20502,#0
6874                     ; 1297 GPIOE->CR1|=(1<<0);
6876  10d0 72105017      	bset	20503,#0
6877                     ; 1299 GPIOE->DDR&=~(1<<1);
6879  10d4 72135016      	bres	20502,#1
6880                     ; 1300 GPIOE->CR1|=(1<<1);
6882  10d8 72125017      	bset	20503,#1
6883                     ; 1311 t4_init();
6885  10dc cd0e15        	call	_t4_init
6887                     ; 1312 spi_init();
6889  10df cd0042        	call	_spi_init
6891                     ; 1326 init_CAN();
6893  10e2 cd0777        	call	_init_CAN
6895  10e5               L7713:
6896                     ; 1356 	if(bCAN_RX)
6898  10e5 3d36          	tnz	_bCAN_RX
6899  10e7 2705          	jreq	L3023
6900                     ; 1359 		bCAN_RX=0;
6902  10e9 3f36          	clr	_bCAN_RX
6903                     ; 1360 		can_in_an();
6905  10eb cd06ff        	call	_can_in_an
6907  10ee               L3023:
6908                     ; 1365 	if(b100Hz)
6910                     	btst	_b100Hz
6911  10f3 2413          	jruge	L5023
6912                     ; 1367 		b100Hz=0;
6914  10f5 72110010      	bres	_b100Hz
6915                     ; 1373 		can_tx_hndl();
6917  10f9 cd0dab        	call	_can_tx_hndl
6919                     ; 1375 		enc_but_drv();
6921  10fc cd03ef        	call	_enc_but_drv
6923                     ; 1376 		enc_an();
6925  10ff cd040f        	call	_enc_an
6927                     ; 1378 		tmblr_drv();
6929  1102 cd0369        	call	_tmblr_drv
6931                     ; 1379 		but_drv();	
6933  1105 cd03ad        	call	_but_drv
6935  1108               L5023:
6936                     ; 1382 	if(b10Hz)
6938                     	btst	_b10Hz
6939  110d 2407          	jruge	L7023
6940                     ; 1384 		b10Hz=0;
6942  110f 7211000f      	bres	_b10Hz
6943                     ; 1386 		ind_hndl();
6945  1113 cd086a        	call	_ind_hndl
6947  1116               L7023:
6948                     ; 1393 	if(b5Hz)
6950                     	btst	_b5Hz
6951  111b 2418          	jruge	L1123
6952                     ; 1395 		b5Hz=0;
6954  111d 7211000e      	bres	_b5Hz
6955                     ; 1397 		GPIOE->DDR|=(1<<1);
6957  1121 72125016      	bset	20502,#1
6958                     ; 1398 		GPIOE->CR1|=(1<<1);
6960  1125 72125017      	bset	20503,#1
6961                     ; 1399 		GPIOE->CR2|=(1<<1);		
6963  1129 72125018      	bset	20504,#1
6964                     ; 1401 		GPIOE->ODR^=(1<<1);
6966  112d c65014        	ld	a,20500
6967  1130 a802          	xor	a,	#2
6968  1132 c75014        	ld	20500,a
6969  1135               L1123:
6970                     ; 1406 	if(b2Hz)
6972                     	btst	_b2Hz
6973  113a 242c          	jruge	L3123
6974                     ; 1408 		b2Hz=0;
6976  113c 7211000d      	bres	_b2Hz
6977                     ; 1413 		can_transmit(0x18a,45,(tmblr_state&0x0f)+((cmnd<<4)&0xf0),/**(((char*)&ust_U)+1)*/0,/**((char*)&ust_U)*/0,/**(((char*)&ust_I)+1)*/0,/**((char*)&ust_I)*/0,/**(((char*)&ust_time)+1)*/0,/**((char*)&ust_time)*/0);
6979  1140 4b00          	push	#0
6980  1142 4b00          	push	#0
6981  1144 4b00          	push	#0
6982  1146 4b00          	push	#0
6983  1148 4b00          	push	#0
6984  114a 4b00          	push	#0
6985  114c b605          	ld	a,_cmnd
6986  114e 97            	ld	xl,a
6987  114f a610          	ld	a,#16
6988  1151 42            	mul	x,a
6989  1152 9f            	ld	a,xl
6990  1153 a4f0          	and	a,#240
6991  1155 6b07          	ld	(OFST+6,sp),a
6992  1157 b6a0          	ld	a,_tmblr_state
6993  1159 a40f          	and	a,#15
6994  115b 1b07          	add	a,(OFST+6,sp)
6995  115d 88            	push	a
6996  115e 4b2d          	push	#45
6997  1160 ae018a        	ldw	x,#394
6998  1163 cd07e6        	call	_can_transmit
7000  1166 5b08          	addw	sp,#8
7001  1168               L3123:
7002                     ; 1417 	if(b1Hz)
7004                     	btst	_b1Hz
7005  116d 2503cc10e5    	jruge	L7713
7006                     ; 1419 		b1Hz=0;
7008  1172 7211000c      	bres	_b1Hz
7009                     ; 1421 		bB=!bB;
7011  1176 9010000a      	bcpl	_bB
7012  117a cc10e5        	jra	L7713
7903                     	xdef	_main
7904                     	xdef	f_ADC2_EOC_Interrupt
7905                     	xdef	f_CAN_TX_Interrupt
7906                     	xdef	f_CAN_RX_Interrupt
7907                     	xdef	f_TIM4_UPD_Interrupt
7908                     	xdef	_t1_init
7909                     	xdef	_t4_init
7910                     	xdef	_can_tx_hndl
7911                     	xdef	_ind_hndl
7912                     	xdef	_init_CAN
7913                     	xdef	_can_in_an
7914                     	xdef	_enc_an
7915                     	xdef	_enc_but_drv
7916                     	xdef	_but_drv
7917                     	xdef	_tmblr_drv
7918                     	xdef	_int2ind_slkuf3
7919                     	xdef	_int2ind_slkuf2
7920                     	xdef	_int2ind_slkuf1
7921                     	xdef	_spi
7922                     	xdef	_spi_init
7923                     	xdef	_delay_ms
7924                     	xdef	_bin2bcd_int
7925                     	xdef	_bcd2ind
7926                     	xdef	_bcd2ind_zero
7927                     	switch	.ubsct
7928  0000               _bAV:
7929  0000 00            	ds.b	1
7930                     	xdef	_bAV
7931  0001               _bREW:
7932  0001 00            	ds.b	1
7933                     	xdef	_bREW
7934  0002               _wrk_state:
7935  0002 00            	ds.b	1
7936                     	xdef	_wrk_state
7937  0003               _enc_but_drv_cnt:
7938  0003 0000          	ds.b	2
7939                     	xdef	_enc_but_drv_cnt
7940  0005               _cmnd:
7941  0005 00            	ds.b	1
7942                     	xdef	_cmnd
7943                     	xdef	_ch_en
7944  0006               _but_cnt:
7945  0006 0000          	ds.b	2
7946                     	xdef	_but_cnt
7947  0008               _tmblr_cnt:
7948  0008 0000          	ds.b	2
7949                     	xdef	_tmblr_cnt
7950                     .bit:	section	.data,bit
7951  0000               _encOW_:
7952  0000 00            	ds.b	1
7953                     	xdef	_encOW_
7954                     	switch	.ubsct
7955  000a               _encOW_cnt2:
7956  000a 00            	ds.b	1
7957                     	xdef	_encOW_cnt2
7958  000b               _encOW_cnt1:
7959  000b 00            	ds.b	1
7960                     	xdef	_encOW_cnt1
7961                     	switch	.bit
7962  0001               _encCW_:
7963  0001 00            	ds.b	1
7964                     	xdef	_encCW_
7965                     	switch	.ubsct
7966  000c               _encCW_cnt2:
7967  000c 00            	ds.b	1
7968                     	xdef	_encCW_cnt2
7969  000d               _encCW_cnt1:
7970  000d 00            	ds.b	1
7971                     	xdef	_encCW_cnt1
7972  000e               _enc_plazma:
7973  000e 0000          	ds.b	2
7974                     	xdef	_enc_plazma
7975                     	switch	.bit
7976  0002               _encOW:
7977  0002 00            	ds.b	1
7978                     	xdef	_encOW
7979  0003               _encCW:
7980  0003 00            	ds.b	1
7981                     	xdef	_encCW
7982  0004               _encB:
7983  0004 00            	ds.b	1
7984                     	xdef	_encB
7985  0005               _encA:
7986  0005 00            	ds.b	1
7987                     	xdef	_encA
7988                     	switch	.ubsct
7989  0010               _encBcnt:
7990  0010 00            	ds.b	1
7991                     	xdef	_encBcnt
7992  0011               _encAcnt:
7993  0011 00            	ds.b	1
7994                     	xdef	_encAcnt
7995                     	switch	.bit
7996  0006               _encBpin_old:
7997  0006 00            	ds.b	1
7998                     	xdef	_encBpin_old
7999  0007               _encApin_old:
8000  0007 00            	ds.b	1
8001                     	xdef	_encApin_old
8002  0008               _encBpin:
8003  0008 00            	ds.b	1
8004                     	xdef	_encBpin
8005  0009               _encApin:
8006  0009 00            	ds.b	1
8007                     	xdef	_encApin
8008                     	switch	.ubsct
8009  0012               _rdata:
8010  0012 000000000000  	ds.b	6
8011                     	xdef	_rdata
8012  0018               _mess:
8013  0018 000000000000  	ds.b	14
8014                     	xdef	_mess
8015  0026               _can_plazma:
8016  0026 0000          	ds.b	2
8017                     	xdef	_can_plazma
8018  0028               _can_error_cnt:
8019  0028 00            	ds.b	1
8020                     	xdef	_can_error_cnt
8021                     	xdef	_bCAN_RX
8022  0029               _tx_busy_cnt:
8023  0029 00            	ds.b	1
8024                     	xdef	_tx_busy_cnt
8025                     	xdef	_bTX_FREE
8026  002a               _can_buff_rd_ptr:
8027  002a 00            	ds.b	1
8028                     	xdef	_can_buff_rd_ptr
8029  002b               _can_buff_wr_ptr:
8030  002b 00            	ds.b	1
8031                     	xdef	_can_buff_wr_ptr
8032  002c               _can_out_buff:
8033  002c 000000000000  	ds.b	64
8034                     	xdef	_can_out_buff
8035  006c               _bFL_:
8036  006c 00            	ds.b	1
8037                     	xdef	_bFL_
8038  006d               _bFL:
8039  006d 00            	ds.b	1
8040                     	xdef	_bFL
8041  006e               _bFL2:
8042  006e 00            	ds.b	1
8043                     	xdef	_bFL2
8044  006f               _bFL5:
8045  006f 00            	ds.b	1
8046                     	xdef	_bFL5
8047  0070               _ind_out:
8048  0070 0000000000    	ds.b	5
8049                     	xdef	_ind_out
8050  0075               _ind_out_:
8051  0075 0000000000    	ds.b	5
8052                     	xdef	_ind_out_
8053  007a               _zero_on:
8054  007a 00            	ds.b	1
8055                     	xdef	_zero_on
8056  007b               _dig:
8057  007b 0000000000    	ds.b	5
8058                     	xdef	_dig
8059  0080               _ind_fad_cnt:
8060  0080 00            	ds.b	1
8061                     	xdef	_ind_fad_cnt
8062  0081               _ind_cnt:
8063  0081 00            	ds.b	1
8064                     	xdef	_ind_cnt
8065                     	xdef	_dig3_
8066                     	xdef	_dig2_
8067                     	xdef	_dig1_
8068                     	xdef	_dig3
8069                     	xdef	_dig2
8070                     	xdef	_dig1
8071                     	xdef	_DIGISYM
8072  0082               _strob_cnt:
8073  0082 00            	ds.b	1
8074                     	xdef	_strob_cnt
8075  0083               _cnt_T4:
8076  0083 00            	ds.b	1
8077                     	xdef	_cnt_T4
8078                     	switch	.bit
8079  000a               _bB:
8080  000a 00            	ds.b	1
8081                     	xdef	_bB
8082  000b               _bT4:
8083  000b 00            	ds.b	1
8084                     	xdef	_bT4
8085  000c               _b1Hz:
8086  000c 00            	ds.b	1
8087                     	xdef	_b1Hz
8088  000d               _b2Hz:
8089  000d 00            	ds.b	1
8090                     	xdef	_b2Hz
8091  000e               _b5Hz:
8092  000e 00            	ds.b	1
8093                     	xdef	_b5Hz
8094  000f               _b10Hz:
8095  000f 00            	ds.b	1
8096                     	xdef	_b10Hz
8097  0010               _b100Hz:
8098  0010 00            	ds.b	1
8099                     	xdef	_b100Hz
8100                     	xdef	_t0_cnt4
8101                     	xdef	_t0_cnt3
8102                     	xdef	_t0_cnt2
8103                     	xdef	_t0_cnt1
8104                     	xdef	_t0_cnt0
8105                     	xdef	_can_transmit
8106                     	xdef	_work_stat
8107                     	switch	.ubsct
8108  0084               _ind_I_set:
8109  0084 0000          	ds.b	2
8110                     	xdef	_ind_I_set
8111  0086               _ind_U_set:
8112  0086 0000          	ds.b	2
8113                     	xdef	_ind_U_set
8114  0088               _ind_I:
8115  0088 0000          	ds.b	2
8116                     	xdef	_ind_I
8117  008a               _ind_U:
8118  008a 0000          	ds.b	2
8119                     	xdef	_ind_U
8120  008c               _time_set:
8121  008c 0000          	ds.b	2
8122                     	xdef	_time_set
8123  008e               _time:
8124  008e 0000          	ds.b	2
8125                     	xdef	_time
8126  0090               _wrk_mode:
8127  0090 00            	ds.b	1
8128                     	xdef	_wrk_mode
8129  0091               _ust_I_loc:
8130  0091 0000          	ds.b	2
8131                     	xdef	_ust_I_loc
8132  0093               _ust_Iloc:
8133  0093 0000          	ds.b	2
8134                     	xdef	_ust_Iloc
8135  0095               _ust_I_:
8136  0095 0000          	ds.b	2
8137                     	xdef	_ust_I_
8138  0097               _ust_I:
8139  0097 0000          	ds.b	2
8140                     	xdef	_ust_I
8141  0099               _out_I_:
8142  0099 0000          	ds.b	2
8143                     	xdef	_out_I_
8144  009b               _out_I:
8145  009b 0000          	ds.b	2
8146                     	xdef	_out_I
8147  009d               _out_U:
8148  009d 0000          	ds.b	2
8149                     	xdef	_out_U
8150  009f               _but_state:
8151  009f 00            	ds.b	1
8152                     	xdef	_but_state
8153  00a0               _tmblr_state:
8154  00a0 00            	ds.b	1
8155                     	xdef	_tmblr_state
8156                     	xref.b	c_x
8157                     	xref.b	c_y
8177                     	xref	c_imul
8178                     	xref	c_sdivx
8179                     	xref	c_lcmp
8180                     	xref	c_ltor
8181                     	xref	c_lgadc
8182                     	xref	c_rtol
8183                     	xref	c_vmul
8184                     	end
