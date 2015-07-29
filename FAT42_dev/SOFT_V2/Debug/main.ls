   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32.1 - 30 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2172                     	bsct
2173  0000               _t0_cnt0:
2174  0000 0000          	dc.w	0
2175  0002               _t0_cnt1:
2176  0002 00            	dc.b	0
2177  0003               _t0_cnt2:
2178  0003 00            	dc.b	0
2179  0004               _t0_cnt3:
2180  0004 00            	dc.b	0
2181  0005               _t0_cnt4:
2182  0005 00            	dc.b	0
2183  0006               _led_ind:
2184  0006 05            	dc.b	5
2185  0007               _adr_drv_stat:
2186  0007 00            	dc.b	0
2187  0008               _bTX_FREE:
2188  0008 01            	dc.b	1
2189  0009               _bCAN_RX:
2190  0009 00            	dc.b	0
2191  000a               _flags:
2192  000a 00            	dc.b	0
2193  000b               _pwm_u:
2194  000b 00c8          	dc.w	200
2195  000d               _pwm_i:
2196  000d 0032          	dc.w	50
2197                     .bit:	section	.data,bit
2198  0000               _bBL_IPS:
2199  0000 00            	dc.b	0
2200                     	bsct
2201  000f               _bRES:
2202  000f 00            	dc.b	0
2203  0010               _bRES_:
2204  0010 00            	dc.b	0
2205  0011               _led_red:
2206  0011 00000000      	dc.l	0
2207  0015               _led_green:
2208  0015 03030303      	dc.l	50529027
2209  0019               _led_drv_cnt:
2210  0019 1e            	dc.b	30
2211  001a               _rotor_int:
2212  001a 007b          	dc.w	123
2213  001c               _volum_u_main_:
2214  001c 02bc          	dc.w	700
2273                     ; 161 void gran(signed short *adr, signed short min, signed short max)
2273                     ; 162 {
2275                     	switch	.text
2276  0000               _gran:
2278  0000 89            	pushw	x
2279       00000000      OFST:	set	0
2282                     ; 163 if (*adr<min) *adr=min;
2284  0001 9c            	rvf
2285  0002 9093          	ldw	y,x
2286  0004 51            	exgw	x,y
2287  0005 fe            	ldw	x,(x)
2288  0006 1305          	cpw	x,(OFST+5,sp)
2289  0008 51            	exgw	x,y
2290  0009 2e03          	jrsge	L7541
2293  000b 1605          	ldw	y,(OFST+5,sp)
2294  000d ff            	ldw	(x),y
2295  000e               L7541:
2296                     ; 164 if (*adr>max) *adr=max; 
2298  000e 9c            	rvf
2299  000f 1e01          	ldw	x,(OFST+1,sp)
2300  0011 9093          	ldw	y,x
2301  0013 51            	exgw	x,y
2302  0014 fe            	ldw	x,(x)
2303  0015 1307          	cpw	x,(OFST+7,sp)
2304  0017 51            	exgw	x,y
2305  0018 2d05          	jrsle	L1641
2308  001a 1e01          	ldw	x,(OFST+1,sp)
2309  001c 1607          	ldw	y,(OFST+7,sp)
2310  001e ff            	ldw	(x),y
2311  001f               L1641:
2312                     ; 165 } 
2315  001f 85            	popw	x
2316  0020 81            	ret
2369                     ; 168 void granee(@eeprom signed short *adr, signed short min, signed short max)
2369                     ; 169 {
2370                     	switch	.text
2371  0021               _granee:
2373  0021 89            	pushw	x
2374       00000000      OFST:	set	0
2377                     ; 170 if (*adr<min) *adr=min;
2379  0022 9c            	rvf
2380  0023 9093          	ldw	y,x
2381  0025 51            	exgw	x,y
2382  0026 fe            	ldw	x,(x)
2383  0027 1305          	cpw	x,(OFST+5,sp)
2384  0029 51            	exgw	x,y
2385  002a 2e09          	jrsge	L1151
2388  002c 1e05          	ldw	x,(OFST+5,sp)
2389  002e 89            	pushw	x
2390  002f 1e03          	ldw	x,(OFST+3,sp)
2391  0031 cd0000        	call	c_eewrw
2393  0034 85            	popw	x
2394  0035               L1151:
2395                     ; 171 if (*adr>max) *adr=max; 
2397  0035 9c            	rvf
2398  0036 1e01          	ldw	x,(OFST+1,sp)
2399  0038 9093          	ldw	y,x
2400  003a 51            	exgw	x,y
2401  003b fe            	ldw	x,(x)
2402  003c 1307          	cpw	x,(OFST+7,sp)
2403  003e 51            	exgw	x,y
2404  003f 2d09          	jrsle	L3151
2407  0041 1e07          	ldw	x,(OFST+7,sp)
2408  0043 89            	pushw	x
2409  0044 1e03          	ldw	x,(OFST+3,sp)
2410  0046 cd0000        	call	c_eewrw
2412  0049 85            	popw	x
2413  004a               L3151:
2414                     ; 172 }
2417  004a 85            	popw	x
2418  004b 81            	ret
2479                     ; 175 long delay_ms(short in)
2479                     ; 176 {
2480                     	switch	.text
2481  004c               _delay_ms:
2483  004c 520c          	subw	sp,#12
2484       0000000c      OFST:	set	12
2487                     ; 179 i=((long)in)*100UL;
2489  004e 90ae0064      	ldw	y,#100
2490  0052 cd0000        	call	c_vmul
2492  0055 96            	ldw	x,sp
2493  0056 1c0005        	addw	x,#OFST-7
2494  0059 cd0000        	call	c_rtol
2496                     ; 181 for(ii=0;ii<i;ii++)
2498  005c ae0000        	ldw	x,#0
2499  005f 1f0b          	ldw	(OFST-1,sp),x
2500  0061 ae0000        	ldw	x,#0
2501  0064 1f09          	ldw	(OFST-3,sp),x
2503  0066 2012          	jra	L3551
2504  0068               L7451:
2505                     ; 183 		iii++;
2507  0068 96            	ldw	x,sp
2508  0069 1c0001        	addw	x,#OFST-11
2509  006c a601          	ld	a,#1
2510  006e cd0000        	call	c_lgadc
2512                     ; 181 for(ii=0;ii<i;ii++)
2514  0071 96            	ldw	x,sp
2515  0072 1c0009        	addw	x,#OFST-3
2516  0075 a601          	ld	a,#1
2517  0077 cd0000        	call	c_lgadc
2519  007a               L3551:
2522  007a 9c            	rvf
2523  007b 96            	ldw	x,sp
2524  007c 1c0009        	addw	x,#OFST-3
2525  007f cd0000        	call	c_ltor
2527  0082 96            	ldw	x,sp
2528  0083 1c0005        	addw	x,#OFST-7
2529  0086 cd0000        	call	c_lcmp
2531  0089 2fdd          	jrslt	L7451
2532                     ; 186 }
2535  008b 5b0c          	addw	sp,#12
2536  008d 81            	ret
2572                     ; 189 void led_hndl(void)
2572                     ; 190 {
2573                     	switch	.text
2574  008e               _led_hndl:
2578                     ; 191 if(adress_error)
2580  008e 725d0000      	tnz	_adress_error
2581  0092 2718          	jreq	L7651
2582                     ; 193 	led_red=0x55555555L;
2584  0094 ae5555        	ldw	x,#21845
2585  0097 bf13          	ldw	_led_red+2,x
2586  0099 ae5555        	ldw	x,#21845
2587  009c bf11          	ldw	_led_red,x
2588                     ; 194 	led_green=0x55555555L;
2590  009e ae5555        	ldw	x,#21845
2591  00a1 bf17          	ldw	_led_green+2,x
2592  00a3 ae5555        	ldw	x,#21845
2593  00a6 bf15          	ldw	_led_green,x
2595  00a8 ac100710      	jpf	L1751
2596  00ac               L7651:
2597                     ; 210 else if(bps_class==bpsIBEP)	//если блок ИБЭПный
2599  00ac 3d01          	tnz	_bps_class
2600  00ae 2703          	jreq	L41
2601  00b0 cc0363        	jp	L3751
2602  00b3               L41:
2603                     ; 212 	if(jp_mode!=jp3)
2605  00b3 b647          	ld	a,_jp_mode
2606  00b5 a103          	cp	a,#3
2607  00b7 2603          	jrne	L61
2608  00b9 cc025f        	jp	L5751
2609  00bc               L61:
2610                     ; 214 		if(main_cnt1<(5*ee_TZAS))
2612  00bc 9c            	rvf
2613  00bd ce0014        	ldw	x,_ee_TZAS
2614  00c0 90ae0005      	ldw	y,#5
2615  00c4 cd0000        	call	c_imul
2617  00c7 b34c          	cpw	x,_main_cnt1
2618  00c9 2d18          	jrsle	L7751
2619                     ; 216 			led_red=0x00000000L;
2621  00cb ae0000        	ldw	x,#0
2622  00ce bf13          	ldw	_led_red+2,x
2623  00d0 ae0000        	ldw	x,#0
2624  00d3 bf11          	ldw	_led_red,x
2625                     ; 217 			led_green=0x03030303L;
2627  00d5 ae0303        	ldw	x,#771
2628  00d8 bf17          	ldw	_led_green+2,x
2629  00da ae0303        	ldw	x,#771
2630  00dd bf15          	ldw	_led_green,x
2632  00df ac200220      	jpf	L1061
2633  00e3               L7751:
2634                     ; 220 		else if((link==ON)&&(flags_tu&0b10000000))
2636  00e3 b65f          	ld	a,_link
2637  00e5 a155          	cp	a,#85
2638  00e7 261e          	jrne	L3061
2640  00e9 b65d          	ld	a,_flags_tu
2641  00eb a580          	bcp	a,#128
2642  00ed 2718          	jreq	L3061
2643                     ; 222 			led_red=0x00055555L;
2645  00ef ae5555        	ldw	x,#21845
2646  00f2 bf13          	ldw	_led_red+2,x
2647  00f4 ae0005        	ldw	x,#5
2648  00f7 bf11          	ldw	_led_red,x
2649                     ; 223 			led_green=0xffffffffL;
2651  00f9 aeffff        	ldw	x,#65535
2652  00fc bf17          	ldw	_led_green+2,x
2653  00fe aeffff        	ldw	x,#-1
2654  0101 bf15          	ldw	_led_green,x
2656  0103 ac200220      	jpf	L1061
2657  0107               L3061:
2658                     ; 226 		else if(((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(100+(5*ee_TZAS)))) && (ee_AVT_MODE!=0x55)&& (!ee_DEVICE))
2660  0107 9c            	rvf
2661  0108 ce0014        	ldw	x,_ee_TZAS
2662  010b 90ae0005      	ldw	y,#5
2663  010f cd0000        	call	c_imul
2665  0112 b34c          	cpw	x,_main_cnt1
2666  0114 2e37          	jrsge	L7061
2668  0116 9c            	rvf
2669  0117 ce0014        	ldw	x,_ee_TZAS
2670  011a 90ae0005      	ldw	y,#5
2671  011e cd0000        	call	c_imul
2673  0121 1c0064        	addw	x,#100
2674  0124 b34c          	cpw	x,_main_cnt1
2675  0126 2d25          	jrsle	L7061
2677  0128 ce0004        	ldw	x,_ee_AVT_MODE
2678  012b a30055        	cpw	x,#85
2679  012e 271d          	jreq	L7061
2681  0130 ce0002        	ldw	x,_ee_DEVICE
2682  0133 2618          	jrne	L7061
2683                     ; 228 			led_red=0x00000000L;
2685  0135 ae0000        	ldw	x,#0
2686  0138 bf13          	ldw	_led_red+2,x
2687  013a ae0000        	ldw	x,#0
2688  013d bf11          	ldw	_led_red,x
2689                     ; 229 			led_green=0xffffffffL;	
2691  013f aeffff        	ldw	x,#65535
2692  0142 bf17          	ldw	_led_green+2,x
2693  0144 aeffff        	ldw	x,#-1
2694  0147 bf15          	ldw	_led_green,x
2696  0149 ac200220      	jpf	L1061
2697  014d               L7061:
2698                     ; 232 		else  if(link==OFF)
2700  014d b65f          	ld	a,_link
2701  014f a1aa          	cp	a,#170
2702  0151 2618          	jrne	L3161
2703                     ; 234 			led_red=0x55555555L;
2705  0153 ae5555        	ldw	x,#21845
2706  0156 bf13          	ldw	_led_red+2,x
2707  0158 ae5555        	ldw	x,#21845
2708  015b bf11          	ldw	_led_red,x
2709                     ; 235 			led_green=0xffffffffL;
2711  015d aeffff        	ldw	x,#65535
2712  0160 bf17          	ldw	_led_green+2,x
2713  0162 aeffff        	ldw	x,#-1
2714  0165 bf15          	ldw	_led_green,x
2716  0167 ac200220      	jpf	L1061
2717  016b               L3161:
2718                     ; 238 		else if((link==ON)&&((flags&0b00111110)==0))
2720  016b b65f          	ld	a,_link
2721  016d a155          	cp	a,#85
2722  016f 261d          	jrne	L7161
2724  0171 b60a          	ld	a,_flags
2725  0173 a53e          	bcp	a,#62
2726  0175 2617          	jrne	L7161
2727                     ; 240 			led_red=0x00000000L;
2729  0177 ae0000        	ldw	x,#0
2730  017a bf13          	ldw	_led_red+2,x
2731  017c ae0000        	ldw	x,#0
2732  017f bf11          	ldw	_led_red,x
2733                     ; 241 			led_green=0xffffffffL;
2735  0181 aeffff        	ldw	x,#65535
2736  0184 bf17          	ldw	_led_green+2,x
2737  0186 aeffff        	ldw	x,#-1
2738  0189 bf15          	ldw	_led_green,x
2740  018b cc0220        	jra	L1061
2741  018e               L7161:
2742                     ; 244 		else if((flags&0b00111110)==0b00000100)
2744  018e b60a          	ld	a,_flags
2745  0190 a43e          	and	a,#62
2746  0192 a104          	cp	a,#4
2747  0194 2616          	jrne	L3261
2748                     ; 246 			led_red=0x00010001L;
2750  0196 ae0001        	ldw	x,#1
2751  0199 bf13          	ldw	_led_red+2,x
2752  019b ae0001        	ldw	x,#1
2753  019e bf11          	ldw	_led_red,x
2754                     ; 247 			led_green=0xffffffffL;	
2756  01a0 aeffff        	ldw	x,#65535
2757  01a3 bf17          	ldw	_led_green+2,x
2758  01a5 aeffff        	ldw	x,#-1
2759  01a8 bf15          	ldw	_led_green,x
2761  01aa 2074          	jra	L1061
2762  01ac               L3261:
2763                     ; 249 		else if(flags&0b00000010)
2765  01ac b60a          	ld	a,_flags
2766  01ae a502          	bcp	a,#2
2767  01b0 2716          	jreq	L7261
2768                     ; 251 			led_red=0x00010001L;
2770  01b2 ae0001        	ldw	x,#1
2771  01b5 bf13          	ldw	_led_red+2,x
2772  01b7 ae0001        	ldw	x,#1
2773  01ba bf11          	ldw	_led_red,x
2774                     ; 252 			led_green=0x00000000L;	
2776  01bc ae0000        	ldw	x,#0
2777  01bf bf17          	ldw	_led_green+2,x
2778  01c1 ae0000        	ldw	x,#0
2779  01c4 bf15          	ldw	_led_green,x
2781  01c6 2058          	jra	L1061
2782  01c8               L7261:
2783                     ; 254 		else if(flags&0b00001000)
2785  01c8 b60a          	ld	a,_flags
2786  01ca a508          	bcp	a,#8
2787  01cc 2716          	jreq	L3361
2788                     ; 256 			led_red=0x00090009L;
2790  01ce ae0009        	ldw	x,#9
2791  01d1 bf13          	ldw	_led_red+2,x
2792  01d3 ae0009        	ldw	x,#9
2793  01d6 bf11          	ldw	_led_red,x
2794                     ; 257 			led_green=0x00000000L;	
2796  01d8 ae0000        	ldw	x,#0
2797  01db bf17          	ldw	_led_green+2,x
2798  01dd ae0000        	ldw	x,#0
2799  01e0 bf15          	ldw	_led_green,x
2801  01e2 203c          	jra	L1061
2802  01e4               L3361:
2803                     ; 259 		else if(flags&0b00010000)
2805  01e4 b60a          	ld	a,_flags
2806  01e6 a510          	bcp	a,#16
2807  01e8 2716          	jreq	L7361
2808                     ; 261 			led_red=0x00490049L;
2810  01ea ae0049        	ldw	x,#73
2811  01ed bf13          	ldw	_led_red+2,x
2812  01ef ae0049        	ldw	x,#73
2813  01f2 bf11          	ldw	_led_red,x
2814                     ; 262 			led_green=0x00000000L;	
2816  01f4 ae0000        	ldw	x,#0
2817  01f7 bf17          	ldw	_led_green+2,x
2818  01f9 ae0000        	ldw	x,#0
2819  01fc bf15          	ldw	_led_green,x
2821  01fe 2020          	jra	L1061
2822  0200               L7361:
2823                     ; 265 		else if((link==ON)&&(flags&0b00100000))
2825  0200 b65f          	ld	a,_link
2826  0202 a155          	cp	a,#85
2827  0204 261a          	jrne	L1061
2829  0206 b60a          	ld	a,_flags
2830  0208 a520          	bcp	a,#32
2831  020a 2714          	jreq	L1061
2832                     ; 267 			led_red=0x00000000L;
2834  020c ae0000        	ldw	x,#0
2835  020f bf13          	ldw	_led_red+2,x
2836  0211 ae0000        	ldw	x,#0
2837  0214 bf11          	ldw	_led_red,x
2838                     ; 268 			led_green=0x00030003L;
2840  0216 ae0003        	ldw	x,#3
2841  0219 bf17          	ldw	_led_green+2,x
2842  021b ae0003        	ldw	x,#3
2843  021e bf15          	ldw	_led_green,x
2844  0220               L1061:
2845                     ; 271 		if((jp_mode==jp1))
2847  0220 b647          	ld	a,_jp_mode
2848  0222 a101          	cp	a,#1
2849  0224 2618          	jrne	L5461
2850                     ; 273 			led_red=0x00000000L;
2852  0226 ae0000        	ldw	x,#0
2853  0229 bf13          	ldw	_led_red+2,x
2854  022b ae0000        	ldw	x,#0
2855  022e bf11          	ldw	_led_red,x
2856                     ; 274 			led_green=0x33333333L;
2858  0230 ae3333        	ldw	x,#13107
2859  0233 bf17          	ldw	_led_green+2,x
2860  0235 ae3333        	ldw	x,#13107
2861  0238 bf15          	ldw	_led_green,x
2863  023a ac100710      	jpf	L1751
2864  023e               L5461:
2865                     ; 276 		else if((jp_mode==jp2))
2867  023e b647          	ld	a,_jp_mode
2868  0240 a102          	cp	a,#2
2869  0242 2703          	jreq	L02
2870  0244 cc0710        	jp	L1751
2871  0247               L02:
2872                     ; 278 			led_red=0xccccccccL;
2874  0247 aecccc        	ldw	x,#52428
2875  024a bf13          	ldw	_led_red+2,x
2876  024c aecccc        	ldw	x,#-13108
2877  024f bf11          	ldw	_led_red,x
2878                     ; 279 			led_green=0x00000000L;
2880  0251 ae0000        	ldw	x,#0
2881  0254 bf17          	ldw	_led_green+2,x
2882  0256 ae0000        	ldw	x,#0
2883  0259 bf15          	ldw	_led_green,x
2884  025b ac100710      	jpf	L1751
2885  025f               L5751:
2886                     ; 282 	else if(jp_mode==jp3)
2888  025f b647          	ld	a,_jp_mode
2889  0261 a103          	cp	a,#3
2890  0263 2703          	jreq	L22
2891  0265 cc0710        	jp	L1751
2892  0268               L22:
2893                     ; 284 		if(main_cnt1<(5*ee_TZAS))
2895  0268 9c            	rvf
2896  0269 ce0014        	ldw	x,_ee_TZAS
2897  026c 90ae0005      	ldw	y,#5
2898  0270 cd0000        	call	c_imul
2900  0273 b34c          	cpw	x,_main_cnt1
2901  0275 2d18          	jrsle	L7561
2902                     ; 286 			led_red=0x00000000L;
2904  0277 ae0000        	ldw	x,#0
2905  027a bf13          	ldw	_led_red+2,x
2906  027c ae0000        	ldw	x,#0
2907  027f bf11          	ldw	_led_red,x
2908                     ; 287 			led_green=0x03030303L;
2910  0281 ae0303        	ldw	x,#771
2911  0284 bf17          	ldw	_led_green+2,x
2912  0286 ae0303        	ldw	x,#771
2913  0289 bf15          	ldw	_led_green,x
2915  028b ac100710      	jpf	L1751
2916  028f               L7561:
2917                     ; 289 		else if((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(70+(5*ee_TZAS))))
2919  028f 9c            	rvf
2920  0290 ce0014        	ldw	x,_ee_TZAS
2921  0293 90ae0005      	ldw	y,#5
2922  0297 cd0000        	call	c_imul
2924  029a b34c          	cpw	x,_main_cnt1
2925  029c 2e2a          	jrsge	L3661
2927  029e 9c            	rvf
2928  029f ce0014        	ldw	x,_ee_TZAS
2929  02a2 90ae0005      	ldw	y,#5
2930  02a6 cd0000        	call	c_imul
2932  02a9 1c0046        	addw	x,#70
2933  02ac b34c          	cpw	x,_main_cnt1
2934  02ae 2d18          	jrsle	L3661
2935                     ; 291 			led_red=0x00000000L;
2937  02b0 ae0000        	ldw	x,#0
2938  02b3 bf13          	ldw	_led_red+2,x
2939  02b5 ae0000        	ldw	x,#0
2940  02b8 bf11          	ldw	_led_red,x
2941                     ; 292 			led_green=0xffffffffL;	
2943  02ba aeffff        	ldw	x,#65535
2944  02bd bf17          	ldw	_led_green+2,x
2945  02bf aeffff        	ldw	x,#-1
2946  02c2 bf15          	ldw	_led_green,x
2948  02c4 ac100710      	jpf	L1751
2949  02c8               L3661:
2950                     ; 295 		else if((flags&0b00011110)==0)
2952  02c8 b60a          	ld	a,_flags
2953  02ca a51e          	bcp	a,#30
2954  02cc 2618          	jrne	L7661
2955                     ; 297 			led_red=0x00000000L;
2957  02ce ae0000        	ldw	x,#0
2958  02d1 bf13          	ldw	_led_red+2,x
2959  02d3 ae0000        	ldw	x,#0
2960  02d6 bf11          	ldw	_led_red,x
2961                     ; 298 			led_green=0xffffffffL;
2963  02d8 aeffff        	ldw	x,#65535
2964  02db bf17          	ldw	_led_green+2,x
2965  02dd aeffff        	ldw	x,#-1
2966  02e0 bf15          	ldw	_led_green,x
2968  02e2 ac100710      	jpf	L1751
2969  02e6               L7661:
2970                     ; 302 		else if((flags&0b00111110)==0b00000100)
2972  02e6 b60a          	ld	a,_flags
2973  02e8 a43e          	and	a,#62
2974  02ea a104          	cp	a,#4
2975  02ec 2618          	jrne	L3761
2976                     ; 304 			led_red=0x00010001L;
2978  02ee ae0001        	ldw	x,#1
2979  02f1 bf13          	ldw	_led_red+2,x
2980  02f3 ae0001        	ldw	x,#1
2981  02f6 bf11          	ldw	_led_red,x
2982                     ; 305 			led_green=0xffffffffL;	
2984  02f8 aeffff        	ldw	x,#65535
2985  02fb bf17          	ldw	_led_green+2,x
2986  02fd aeffff        	ldw	x,#-1
2987  0300 bf15          	ldw	_led_green,x
2989  0302 ac100710      	jpf	L1751
2990  0306               L3761:
2991                     ; 307 		else if(flags&0b00000010)
2993  0306 b60a          	ld	a,_flags
2994  0308 a502          	bcp	a,#2
2995  030a 2718          	jreq	L7761
2996                     ; 309 			led_red=0x00010001L;
2998  030c ae0001        	ldw	x,#1
2999  030f bf13          	ldw	_led_red+2,x
3000  0311 ae0001        	ldw	x,#1
3001  0314 bf11          	ldw	_led_red,x
3002                     ; 310 			led_green=0x00000000L;	
3004  0316 ae0000        	ldw	x,#0
3005  0319 bf17          	ldw	_led_green+2,x
3006  031b ae0000        	ldw	x,#0
3007  031e bf15          	ldw	_led_green,x
3009  0320 ac100710      	jpf	L1751
3010  0324               L7761:
3011                     ; 312 		else if(flags&0b00001000)
3013  0324 b60a          	ld	a,_flags
3014  0326 a508          	bcp	a,#8
3015  0328 2718          	jreq	L3071
3016                     ; 314 			led_red=0x00090009L;
3018  032a ae0009        	ldw	x,#9
3019  032d bf13          	ldw	_led_red+2,x
3020  032f ae0009        	ldw	x,#9
3021  0332 bf11          	ldw	_led_red,x
3022                     ; 315 			led_green=0x00000000L;	
3024  0334 ae0000        	ldw	x,#0
3025  0337 bf17          	ldw	_led_green+2,x
3026  0339 ae0000        	ldw	x,#0
3027  033c bf15          	ldw	_led_green,x
3029  033e ac100710      	jpf	L1751
3030  0342               L3071:
3031                     ; 317 		else if(flags&0b00010000)
3033  0342 b60a          	ld	a,_flags
3034  0344 a510          	bcp	a,#16
3035  0346 2603          	jrne	L42
3036  0348 cc0710        	jp	L1751
3037  034b               L42:
3038                     ; 319 			led_red=0x00490049L;
3040  034b ae0049        	ldw	x,#73
3041  034e bf13          	ldw	_led_red+2,x
3042  0350 ae0049        	ldw	x,#73
3043  0353 bf11          	ldw	_led_red,x
3044                     ; 320 			led_green=0xffffffffL;	
3046  0355 aeffff        	ldw	x,#65535
3047  0358 bf17          	ldw	_led_green+2,x
3048  035a aeffff        	ldw	x,#-1
3049  035d bf15          	ldw	_led_green,x
3050  035f ac100710      	jpf	L1751
3051  0363               L3751:
3052                     ; 324 else if(bps_class==bpsIPS)	//если блок ИПСный
3054  0363 b601          	ld	a,_bps_class
3055  0365 a101          	cp	a,#1
3056  0367 2703          	jreq	L62
3057  0369 cc0710        	jp	L1751
3058  036c               L62:
3059                     ; 326 	if(jp_mode!=jp3)
3061  036c b647          	ld	a,_jp_mode
3062  036e a103          	cp	a,#3
3063  0370 2603          	jrne	L03
3064  0372 cc061c        	jp	L5171
3065  0375               L03:
3066                     ; 328 		if(main_cnt1<(5*ee_TZAS))
3068  0375 9c            	rvf
3069  0376 ce0014        	ldw	x,_ee_TZAS
3070  0379 90ae0005      	ldw	y,#5
3071  037d cd0000        	call	c_imul
3073  0380 b34c          	cpw	x,_main_cnt1
3074  0382 2d18          	jrsle	L7171
3075                     ; 330 			led_red=0x00000000L;
3077  0384 ae0000        	ldw	x,#0
3078  0387 bf13          	ldw	_led_red+2,x
3079  0389 ae0000        	ldw	x,#0
3080  038c bf11          	ldw	_led_red,x
3081                     ; 331 			led_green=0x03030303L;
3083  038e ae0303        	ldw	x,#771
3084  0391 bf17          	ldw	_led_green+2,x
3085  0393 ae0303        	ldw	x,#771
3086  0396 bf15          	ldw	_led_green,x
3088  0398 acdd05dd      	jpf	L1271
3089  039c               L7171:
3090                     ; 334 		else if((link==ON)&&(flags_tu&0b10000000))
3092  039c b65f          	ld	a,_link
3093  039e a155          	cp	a,#85
3094  03a0 261e          	jrne	L3271
3096  03a2 b65d          	ld	a,_flags_tu
3097  03a4 a580          	bcp	a,#128
3098  03a6 2718          	jreq	L3271
3099                     ; 336 			led_red=0x00055555L;
3101  03a8 ae5555        	ldw	x,#21845
3102  03ab bf13          	ldw	_led_red+2,x
3103  03ad ae0005        	ldw	x,#5
3104  03b0 bf11          	ldw	_led_red,x
3105                     ; 337 			led_green=0xffffffffL;
3107  03b2 aeffff        	ldw	x,#65535
3108  03b5 bf17          	ldw	_led_green+2,x
3109  03b7 aeffff        	ldw	x,#-1
3110  03ba bf15          	ldw	_led_green,x
3112  03bc acdd05dd      	jpf	L1271
3113  03c0               L3271:
3114                     ; 340 		else if(((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(100+(5*ee_TZAS)))) && (ee_AVT_MODE!=0x55)&& (!ee_DEVICE))
3116  03c0 9c            	rvf
3117  03c1 ce0014        	ldw	x,_ee_TZAS
3118  03c4 90ae0005      	ldw	y,#5
3119  03c8 cd0000        	call	c_imul
3121  03cb b34c          	cpw	x,_main_cnt1
3122  03cd 2e37          	jrsge	L7271
3124  03cf 9c            	rvf
3125  03d0 ce0014        	ldw	x,_ee_TZAS
3126  03d3 90ae0005      	ldw	y,#5
3127  03d7 cd0000        	call	c_imul
3129  03da 1c0064        	addw	x,#100
3130  03dd b34c          	cpw	x,_main_cnt1
3131  03df 2d25          	jrsle	L7271
3133  03e1 ce0004        	ldw	x,_ee_AVT_MODE
3134  03e4 a30055        	cpw	x,#85
3135  03e7 271d          	jreq	L7271
3137  03e9 ce0002        	ldw	x,_ee_DEVICE
3138  03ec 2618          	jrne	L7271
3139                     ; 342 			led_red=0x00000000L;
3141  03ee ae0000        	ldw	x,#0
3142  03f1 bf13          	ldw	_led_red+2,x
3143  03f3 ae0000        	ldw	x,#0
3144  03f6 bf11          	ldw	_led_red,x
3145                     ; 343 			led_green=0xffffffffL;	
3147  03f8 aeffff        	ldw	x,#65535
3148  03fb bf17          	ldw	_led_green+2,x
3149  03fd aeffff        	ldw	x,#-1
3150  0400 bf15          	ldw	_led_green,x
3152  0402 acdd05dd      	jpf	L1271
3153  0406               L7271:
3154                     ; 346 		else  if(link==OFF)
3156  0406 b65f          	ld	a,_link
3157  0408 a1aa          	cp	a,#170
3158  040a 2703          	jreq	L23
3159  040c cc0528        	jp	L3371
3160  040f               L23:
3161                     ; 348 			if((flags&0b00011110)==0)
3163  040f b60a          	ld	a,_flags
3164  0411 a51e          	bcp	a,#30
3165  0413 262d          	jrne	L5371
3166                     ; 350 				led_red=0x00000000L;
3168  0415 ae0000        	ldw	x,#0
3169  0418 bf13          	ldw	_led_red+2,x
3170  041a ae0000        	ldw	x,#0
3171  041d bf11          	ldw	_led_red,x
3172                     ; 351 				if(bMAIN)led_green=0xfffffff5L;
3174                     	btst	_bMAIN
3175  0424 240e          	jruge	L7371
3178  0426 aefff5        	ldw	x,#65525
3179  0429 bf17          	ldw	_led_green+2,x
3180  042b aeffff        	ldw	x,#-1
3181  042e bf15          	ldw	_led_green,x
3183  0430 acdd05dd      	jpf	L1271
3184  0434               L7371:
3185                     ; 352 				else led_green=0xffffffffL;
3187  0434 aeffff        	ldw	x,#65535
3188  0437 bf17          	ldw	_led_green+2,x
3189  0439 aeffff        	ldw	x,#-1
3190  043c bf15          	ldw	_led_green,x
3191  043e acdd05dd      	jpf	L1271
3192  0442               L5371:
3193                     ; 355 			else if((flags&0b00111110)==0b00000100)
3195  0442 b60a          	ld	a,_flags
3196  0444 a43e          	and	a,#62
3197  0446 a104          	cp	a,#4
3198  0448 262d          	jrne	L5471
3199                     ; 357 				led_red=0x00010001L;
3201  044a ae0001        	ldw	x,#1
3202  044d bf13          	ldw	_led_red+2,x
3203  044f ae0001        	ldw	x,#1
3204  0452 bf11          	ldw	_led_red,x
3205                     ; 358 				if(bMAIN)led_green=0xfffffff5L;
3207                     	btst	_bMAIN
3208  0459 240e          	jruge	L7471
3211  045b aefff5        	ldw	x,#65525
3212  045e bf17          	ldw	_led_green+2,x
3213  0460 aeffff        	ldw	x,#-1
3214  0463 bf15          	ldw	_led_green,x
3216  0465 acdd05dd      	jpf	L1271
3217  0469               L7471:
3218                     ; 359 				else led_green=0xffffffffL;	
3220  0469 aeffff        	ldw	x,#65535
3221  046c bf17          	ldw	_led_green+2,x
3222  046e aeffff        	ldw	x,#-1
3223  0471 bf15          	ldw	_led_green,x
3224  0473 acdd05dd      	jpf	L1271
3225  0477               L5471:
3226                     ; 361 			else if(flags&0b00000010)
3228  0477 b60a          	ld	a,_flags
3229  0479 a502          	bcp	a,#2
3230  047b 272d          	jreq	L5571
3231                     ; 363 				led_red=0x00010001L;
3233  047d ae0001        	ldw	x,#1
3234  0480 bf13          	ldw	_led_red+2,x
3235  0482 ae0001        	ldw	x,#1
3236  0485 bf11          	ldw	_led_red,x
3237                     ; 364 				if(bMAIN)led_green=0x00000005L;
3239                     	btst	_bMAIN
3240  048c 240e          	jruge	L7571
3243  048e ae0005        	ldw	x,#5
3244  0491 bf17          	ldw	_led_green+2,x
3245  0493 ae0000        	ldw	x,#0
3246  0496 bf15          	ldw	_led_green,x
3248  0498 acdd05dd      	jpf	L1271
3249  049c               L7571:
3250                     ; 365 				else led_green=0x00000000L;
3252  049c ae0000        	ldw	x,#0
3253  049f bf17          	ldw	_led_green+2,x
3254  04a1 ae0000        	ldw	x,#0
3255  04a4 bf15          	ldw	_led_green,x
3256  04a6 acdd05dd      	jpf	L1271
3257  04aa               L5571:
3258                     ; 367 			else if(flags&0b00001000)
3260  04aa b60a          	ld	a,_flags
3261  04ac a508          	bcp	a,#8
3262  04ae 272d          	jreq	L5671
3263                     ; 369 				led_red=0x00090009L;
3265  04b0 ae0009        	ldw	x,#9
3266  04b3 bf13          	ldw	_led_red+2,x
3267  04b5 ae0009        	ldw	x,#9
3268  04b8 bf11          	ldw	_led_red,x
3269                     ; 370 				if(bMAIN)led_green=0x00000005L;
3271                     	btst	_bMAIN
3272  04bf 240e          	jruge	L7671
3275  04c1 ae0005        	ldw	x,#5
3276  04c4 bf17          	ldw	_led_green+2,x
3277  04c6 ae0000        	ldw	x,#0
3278  04c9 bf15          	ldw	_led_green,x
3280  04cb acdd05dd      	jpf	L1271
3281  04cf               L7671:
3282                     ; 371 				else led_green=0x00000000L;	
3284  04cf ae0000        	ldw	x,#0
3285  04d2 bf17          	ldw	_led_green+2,x
3286  04d4 ae0000        	ldw	x,#0
3287  04d7 bf15          	ldw	_led_green,x
3288  04d9 acdd05dd      	jpf	L1271
3289  04dd               L5671:
3290                     ; 373 			else if(flags&0b00010000)
3292  04dd b60a          	ld	a,_flags
3293  04df a510          	bcp	a,#16
3294  04e1 272d          	jreq	L5771
3295                     ; 375 				led_red=0x00490049L;
3297  04e3 ae0049        	ldw	x,#73
3298  04e6 bf13          	ldw	_led_red+2,x
3299  04e8 ae0049        	ldw	x,#73
3300  04eb bf11          	ldw	_led_red,x
3301                     ; 376 				if(bMAIN)led_green=0x00000005L;
3303                     	btst	_bMAIN
3304  04f2 240e          	jruge	L7771
3307  04f4 ae0005        	ldw	x,#5
3308  04f7 bf17          	ldw	_led_green+2,x
3309  04f9 ae0000        	ldw	x,#0
3310  04fc bf15          	ldw	_led_green,x
3312  04fe acdd05dd      	jpf	L1271
3313  0502               L7771:
3314                     ; 377 				else led_green=0x00000000L;	
3316  0502 ae0000        	ldw	x,#0
3317  0505 bf17          	ldw	_led_green+2,x
3318  0507 ae0000        	ldw	x,#0
3319  050a bf15          	ldw	_led_green,x
3320  050c acdd05dd      	jpf	L1271
3321  0510               L5771:
3322                     ; 381 				led_red=0x55555555L;
3324  0510 ae5555        	ldw	x,#21845
3325  0513 bf13          	ldw	_led_red+2,x
3326  0515 ae5555        	ldw	x,#21845
3327  0518 bf11          	ldw	_led_red,x
3328                     ; 382 				led_green=0xffffffffL;
3330  051a aeffff        	ldw	x,#65535
3331  051d bf17          	ldw	_led_green+2,x
3332  051f aeffff        	ldw	x,#-1
3333  0522 bf15          	ldw	_led_green,x
3334  0524 acdd05dd      	jpf	L1271
3335  0528               L3371:
3336                     ; 398 		else if((link==ON)&&((flags&0b00111110)==0))
3338  0528 b65f          	ld	a,_link
3339  052a a155          	cp	a,#85
3340  052c 261d          	jrne	L7002
3342  052e b60a          	ld	a,_flags
3343  0530 a53e          	bcp	a,#62
3344  0532 2617          	jrne	L7002
3345                     ; 400 			led_red=0x00000000L;
3347  0534 ae0000        	ldw	x,#0
3348  0537 bf13          	ldw	_led_red+2,x
3349  0539 ae0000        	ldw	x,#0
3350  053c bf11          	ldw	_led_red,x
3351                     ; 401 			led_green=0xffffffffL;
3353  053e aeffff        	ldw	x,#65535
3354  0541 bf17          	ldw	_led_green+2,x
3355  0543 aeffff        	ldw	x,#-1
3356  0546 bf15          	ldw	_led_green,x
3358  0548 cc05dd        	jra	L1271
3359  054b               L7002:
3360                     ; 404 		else if((flags&0b00111110)==0b00000100)
3362  054b b60a          	ld	a,_flags
3363  054d a43e          	and	a,#62
3364  054f a104          	cp	a,#4
3365  0551 2616          	jrne	L3102
3366                     ; 406 			led_red=0x00010001L;
3368  0553 ae0001        	ldw	x,#1
3369  0556 bf13          	ldw	_led_red+2,x
3370  0558 ae0001        	ldw	x,#1
3371  055b bf11          	ldw	_led_red,x
3372                     ; 407 			led_green=0xffffffffL;	
3374  055d aeffff        	ldw	x,#65535
3375  0560 bf17          	ldw	_led_green+2,x
3376  0562 aeffff        	ldw	x,#-1
3377  0565 bf15          	ldw	_led_green,x
3379  0567 2074          	jra	L1271
3380  0569               L3102:
3381                     ; 409 		else if(flags&0b00000010)
3383  0569 b60a          	ld	a,_flags
3384  056b a502          	bcp	a,#2
3385  056d 2716          	jreq	L7102
3386                     ; 411 			led_red=0x00010001L;
3388  056f ae0001        	ldw	x,#1
3389  0572 bf13          	ldw	_led_red+2,x
3390  0574 ae0001        	ldw	x,#1
3391  0577 bf11          	ldw	_led_red,x
3392                     ; 412 			led_green=0x00000000L;	
3394  0579 ae0000        	ldw	x,#0
3395  057c bf17          	ldw	_led_green+2,x
3396  057e ae0000        	ldw	x,#0
3397  0581 bf15          	ldw	_led_green,x
3399  0583 2058          	jra	L1271
3400  0585               L7102:
3401                     ; 414 		else if(flags&0b00001000)
3403  0585 b60a          	ld	a,_flags
3404  0587 a508          	bcp	a,#8
3405  0589 2716          	jreq	L3202
3406                     ; 416 			led_red=0x00090009L;
3408  058b ae0009        	ldw	x,#9
3409  058e bf13          	ldw	_led_red+2,x
3410  0590 ae0009        	ldw	x,#9
3411  0593 bf11          	ldw	_led_red,x
3412                     ; 417 			led_green=0x00000000L;	
3414  0595 ae0000        	ldw	x,#0
3415  0598 bf17          	ldw	_led_green+2,x
3416  059a ae0000        	ldw	x,#0
3417  059d bf15          	ldw	_led_green,x
3419  059f 203c          	jra	L1271
3420  05a1               L3202:
3421                     ; 419 		else if(flags&0b00010000)
3423  05a1 b60a          	ld	a,_flags
3424  05a3 a510          	bcp	a,#16
3425  05a5 2716          	jreq	L7202
3426                     ; 421 			led_red=0x00490049L;
3428  05a7 ae0049        	ldw	x,#73
3429  05aa bf13          	ldw	_led_red+2,x
3430  05ac ae0049        	ldw	x,#73
3431  05af bf11          	ldw	_led_red,x
3432                     ; 422 			led_green=0x00000000L;	
3434  05b1 ae0000        	ldw	x,#0
3435  05b4 bf17          	ldw	_led_green+2,x
3436  05b6 ae0000        	ldw	x,#0
3437  05b9 bf15          	ldw	_led_green,x
3439  05bb 2020          	jra	L1271
3440  05bd               L7202:
3441                     ; 425 		else if((link==ON)&&(flags&0b00100000))
3443  05bd b65f          	ld	a,_link
3444  05bf a155          	cp	a,#85
3445  05c1 261a          	jrne	L1271
3447  05c3 b60a          	ld	a,_flags
3448  05c5 a520          	bcp	a,#32
3449  05c7 2714          	jreq	L1271
3450                     ; 427 			led_red=0x00000000L;
3452  05c9 ae0000        	ldw	x,#0
3453  05cc bf13          	ldw	_led_red+2,x
3454  05ce ae0000        	ldw	x,#0
3455  05d1 bf11          	ldw	_led_red,x
3456                     ; 428 			led_green=0x00030003L;
3458  05d3 ae0003        	ldw	x,#3
3459  05d6 bf17          	ldw	_led_green+2,x
3460  05d8 ae0003        	ldw	x,#3
3461  05db bf15          	ldw	_led_green,x
3462  05dd               L1271:
3463                     ; 431 		if((jp_mode==jp1))
3465  05dd b647          	ld	a,_jp_mode
3466  05df a101          	cp	a,#1
3467  05e1 2618          	jrne	L5302
3468                     ; 433 			led_red=0x00000000L;
3470  05e3 ae0000        	ldw	x,#0
3471  05e6 bf13          	ldw	_led_red+2,x
3472  05e8 ae0000        	ldw	x,#0
3473  05eb bf11          	ldw	_led_red,x
3474                     ; 434 			led_green=0x33333333L;
3476  05ed ae3333        	ldw	x,#13107
3477  05f0 bf17          	ldw	_led_green+2,x
3478  05f2 ae3333        	ldw	x,#13107
3479  05f5 bf15          	ldw	_led_green,x
3481  05f7 ac100710      	jpf	L1751
3482  05fb               L5302:
3483                     ; 436 		else if((jp_mode==jp2))
3485  05fb b647          	ld	a,_jp_mode
3486  05fd a102          	cp	a,#2
3487  05ff 2703          	jreq	L43
3488  0601 cc0710        	jp	L1751
3489  0604               L43:
3490                     ; 440 			led_red=0xccccccccL;
3492  0604 aecccc        	ldw	x,#52428
3493  0607 bf13          	ldw	_led_red+2,x
3494  0609 aecccc        	ldw	x,#-13108
3495  060c bf11          	ldw	_led_red,x
3496                     ; 441 			led_green=0x00000000L;
3498  060e ae0000        	ldw	x,#0
3499  0611 bf17          	ldw	_led_green+2,x
3500  0613 ae0000        	ldw	x,#0
3501  0616 bf15          	ldw	_led_green,x
3502  0618 ac100710      	jpf	L1751
3503  061c               L5171:
3504                     ; 444 	else if(jp_mode==jp3)
3506  061c b647          	ld	a,_jp_mode
3507  061e a103          	cp	a,#3
3508  0620 2703          	jreq	L63
3509  0622 cc0710        	jp	L1751
3510  0625               L63:
3511                     ; 446 		if(main_cnt1<(5*ee_TZAS))
3513  0625 9c            	rvf
3514  0626 ce0014        	ldw	x,_ee_TZAS
3515  0629 90ae0005      	ldw	y,#5
3516  062d cd0000        	call	c_imul
3518  0630 b34c          	cpw	x,_main_cnt1
3519  0632 2d18          	jrsle	L7402
3520                     ; 448 			led_red=0x00000000L;
3522  0634 ae0000        	ldw	x,#0
3523  0637 bf13          	ldw	_led_red+2,x
3524  0639 ae0000        	ldw	x,#0
3525  063c bf11          	ldw	_led_red,x
3526                     ; 449 			led_green=0x03030303L;
3528  063e ae0303        	ldw	x,#771
3529  0641 bf17          	ldw	_led_green+2,x
3530  0643 ae0303        	ldw	x,#771
3531  0646 bf15          	ldw	_led_green,x
3533  0648 ac100710      	jpf	L1751
3534  064c               L7402:
3535                     ; 451 		else if((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(70+(5*ee_TZAS))))
3537  064c 9c            	rvf
3538  064d ce0014        	ldw	x,_ee_TZAS
3539  0650 90ae0005      	ldw	y,#5
3540  0654 cd0000        	call	c_imul
3542  0657 b34c          	cpw	x,_main_cnt1
3543  0659 2e29          	jrsge	L3502
3545  065b 9c            	rvf
3546  065c ce0014        	ldw	x,_ee_TZAS
3547  065f 90ae0005      	ldw	y,#5
3548  0663 cd0000        	call	c_imul
3550  0666 1c0046        	addw	x,#70
3551  0669 b34c          	cpw	x,_main_cnt1
3552  066b 2d17          	jrsle	L3502
3553                     ; 453 			led_red=0x00000000L;
3555  066d ae0000        	ldw	x,#0
3556  0670 bf13          	ldw	_led_red+2,x
3557  0672 ae0000        	ldw	x,#0
3558  0675 bf11          	ldw	_led_red,x
3559                     ; 454 			led_green=0xffffffffL;	
3561  0677 aeffff        	ldw	x,#65535
3562  067a bf17          	ldw	_led_green+2,x
3563  067c aeffff        	ldw	x,#-1
3564  067f bf15          	ldw	_led_green,x
3566  0681 cc0710        	jra	L1751
3567  0684               L3502:
3568                     ; 457 		else if((flags&0b00011110)==0)
3570  0684 b60a          	ld	a,_flags
3571  0686 a51e          	bcp	a,#30
3572  0688 2616          	jrne	L7502
3573                     ; 459 			led_red=0x00000000L;
3575  068a ae0000        	ldw	x,#0
3576  068d bf13          	ldw	_led_red+2,x
3577  068f ae0000        	ldw	x,#0
3578  0692 bf11          	ldw	_led_red,x
3579                     ; 460 			led_green=0xffffffffL;
3581  0694 aeffff        	ldw	x,#65535
3582  0697 bf17          	ldw	_led_green+2,x
3583  0699 aeffff        	ldw	x,#-1
3584  069c bf15          	ldw	_led_green,x
3586  069e 2070          	jra	L1751
3587  06a0               L7502:
3588                     ; 464 		else if((flags&0b00111110)==0b00000100)
3590  06a0 b60a          	ld	a,_flags
3591  06a2 a43e          	and	a,#62
3592  06a4 a104          	cp	a,#4
3593  06a6 2616          	jrne	L3602
3594                     ; 466 			led_red=0x00010001L;
3596  06a8 ae0001        	ldw	x,#1
3597  06ab bf13          	ldw	_led_red+2,x
3598  06ad ae0001        	ldw	x,#1
3599  06b0 bf11          	ldw	_led_red,x
3600                     ; 467 			led_green=0xffffffffL;	
3602  06b2 aeffff        	ldw	x,#65535
3603  06b5 bf17          	ldw	_led_green+2,x
3604  06b7 aeffff        	ldw	x,#-1
3605  06ba bf15          	ldw	_led_green,x
3607  06bc 2052          	jra	L1751
3608  06be               L3602:
3609                     ; 469 		else if(flags&0b00000010)
3611  06be b60a          	ld	a,_flags
3612  06c0 a502          	bcp	a,#2
3613  06c2 2716          	jreq	L7602
3614                     ; 471 			led_red=0x00010001L;
3616  06c4 ae0001        	ldw	x,#1
3617  06c7 bf13          	ldw	_led_red+2,x
3618  06c9 ae0001        	ldw	x,#1
3619  06cc bf11          	ldw	_led_red,x
3620                     ; 472 			led_green=0x00000000L;	
3622  06ce ae0000        	ldw	x,#0
3623  06d1 bf17          	ldw	_led_green+2,x
3624  06d3 ae0000        	ldw	x,#0
3625  06d6 bf15          	ldw	_led_green,x
3627  06d8 2036          	jra	L1751
3628  06da               L7602:
3629                     ; 474 		else if(flags&0b00001000)
3631  06da b60a          	ld	a,_flags
3632  06dc a508          	bcp	a,#8
3633  06de 2716          	jreq	L3702
3634                     ; 476 			led_red=0x00090009L;
3636  06e0 ae0009        	ldw	x,#9
3637  06e3 bf13          	ldw	_led_red+2,x
3638  06e5 ae0009        	ldw	x,#9
3639  06e8 bf11          	ldw	_led_red,x
3640                     ; 477 			led_green=0x00000000L;	
3642  06ea ae0000        	ldw	x,#0
3643  06ed bf17          	ldw	_led_green+2,x
3644  06ef ae0000        	ldw	x,#0
3645  06f2 bf15          	ldw	_led_green,x
3647  06f4 201a          	jra	L1751
3648  06f6               L3702:
3649                     ; 479 		else if(flags&0b00010000)
3651  06f6 b60a          	ld	a,_flags
3652  06f8 a510          	bcp	a,#16
3653  06fa 2714          	jreq	L1751
3654                     ; 481 			led_red=0x00490049L;
3656  06fc ae0049        	ldw	x,#73
3657  06ff bf13          	ldw	_led_red+2,x
3658  0701 ae0049        	ldw	x,#73
3659  0704 bf11          	ldw	_led_red,x
3660                     ; 482 			led_green=0xffffffffL;	
3662  0706 aeffff        	ldw	x,#65535
3663  0709 bf17          	ldw	_led_green+2,x
3664  070b aeffff        	ldw	x,#-1
3665  070e bf15          	ldw	_led_green,x
3666  0710               L1751:
3667                     ; 486 }
3670  0710 81            	ret
3698                     ; 489 void led_drv(void)
3698                     ; 490 {
3699                     	switch	.text
3700  0711               _led_drv:
3704                     ; 492 GPIOA->DDR|=(1<<4);
3706  0711 72185002      	bset	20482,#4
3707                     ; 493 GPIOA->CR1|=(1<<4);
3709  0715 72185003      	bset	20483,#4
3710                     ; 494 GPIOA->CR2&=~(1<<4);
3712  0719 72195004      	bres	20484,#4
3713                     ; 495 if(led_red_buff&0b1L) GPIOA->ODR|=(1<<4); 	//Горит если в led_red_buff 1 и на ножке 1
3715  071d b63d          	ld	a,_led_red_buff+3
3716  071f a501          	bcp	a,#1
3717  0721 2706          	jreq	L1112
3720  0723 72185000      	bset	20480,#4
3722  0727 2004          	jra	L3112
3723  0729               L1112:
3724                     ; 496 else GPIOA->ODR&=~(1<<4); 
3726  0729 72195000      	bres	20480,#4
3727  072d               L3112:
3728                     ; 499 GPIOA->DDR|=(1<<5);
3730  072d 721a5002      	bset	20482,#5
3731                     ; 500 GPIOA->CR1|=(1<<5);
3733  0731 721a5003      	bset	20483,#5
3734                     ; 501 GPIOA->CR2&=~(1<<5);	
3736  0735 721b5004      	bres	20484,#5
3737                     ; 502 if(led_green_buff&0b1L) GPIOA->ODR|=(1<<5);	//Горит если в led_green_buff 1 и на ножке 1
3739  0739 b639          	ld	a,_led_green_buff+3
3740  073b a501          	bcp	a,#1
3741  073d 2706          	jreq	L5112
3744  073f 721a5000      	bset	20480,#5
3746  0743 2004          	jra	L7112
3747  0745               L5112:
3748                     ; 503 else GPIOA->ODR&=~(1<<5);
3750  0745 721b5000      	bres	20480,#5
3751  0749               L7112:
3752                     ; 506 led_red_buff>>=1;
3754  0749 373a          	sra	_led_red_buff
3755  074b 363b          	rrc	_led_red_buff+1
3756  074d 363c          	rrc	_led_red_buff+2
3757  074f 363d          	rrc	_led_red_buff+3
3758                     ; 507 led_green_buff>>=1;
3760  0751 3736          	sra	_led_green_buff
3761  0753 3637          	rrc	_led_green_buff+1
3762  0755 3638          	rrc	_led_green_buff+2
3763  0757 3639          	rrc	_led_green_buff+3
3764                     ; 508 if(++led_drv_cnt>32)
3766  0759 3c19          	inc	_led_drv_cnt
3767  075b b619          	ld	a,_led_drv_cnt
3768  075d a121          	cp	a,#33
3769  075f 2512          	jrult	L1212
3770                     ; 510 	led_drv_cnt=0;
3772  0761 3f19          	clr	_led_drv_cnt
3773                     ; 511 	led_red_buff=led_red;
3775  0763 be13          	ldw	x,_led_red+2
3776  0765 bf3c          	ldw	_led_red_buff+2,x
3777  0767 be11          	ldw	x,_led_red
3778  0769 bf3a          	ldw	_led_red_buff,x
3779                     ; 512 	led_green_buff=led_green;
3781  076b be17          	ldw	x,_led_green+2
3782  076d bf38          	ldw	_led_green_buff+2,x
3783  076f be15          	ldw	x,_led_green
3784  0771 bf36          	ldw	_led_green_buff,x
3785  0773               L1212:
3786                     ; 518 } 
3789  0773 81            	ret
3815                     ; 521 void JP_drv(void)
3815                     ; 522 {
3816                     	switch	.text
3817  0774               _JP_drv:
3821                     ; 524 GPIOD->DDR&=~(1<<6);
3823  0774 721d5011      	bres	20497,#6
3824                     ; 525 GPIOD->CR1|=(1<<6);
3826  0778 721c5012      	bset	20498,#6
3827                     ; 526 GPIOD->CR2&=~(1<<6);
3829  077c 721d5013      	bres	20499,#6
3830                     ; 528 GPIOD->DDR&=~(1<<7);
3832  0780 721f5011      	bres	20497,#7
3833                     ; 529 GPIOD->CR1|=(1<<7);
3835  0784 721e5012      	bset	20498,#7
3836                     ; 530 GPIOD->CR2&=~(1<<7);
3838  0788 721f5013      	bres	20499,#7
3839                     ; 532 if(GPIOD->IDR&(1<<6))
3841  078c c65010        	ld	a,20496
3842  078f a540          	bcp	a,#64
3843  0791 270a          	jreq	L3312
3844                     ; 534 	if(cnt_JP0<10)
3846  0793 b646          	ld	a,_cnt_JP0
3847  0795 a10a          	cp	a,#10
3848  0797 2411          	jruge	L7312
3849                     ; 536 		cnt_JP0++;
3851  0799 3c46          	inc	_cnt_JP0
3852  079b 200d          	jra	L7312
3853  079d               L3312:
3854                     ; 539 else if(!(GPIOD->IDR&(1<<6)))
3856  079d c65010        	ld	a,20496
3857  07a0 a540          	bcp	a,#64
3858  07a2 2606          	jrne	L7312
3859                     ; 541 	if(cnt_JP0)
3861  07a4 3d46          	tnz	_cnt_JP0
3862  07a6 2702          	jreq	L7312
3863                     ; 543 		cnt_JP0--;
3865  07a8 3a46          	dec	_cnt_JP0
3866  07aa               L7312:
3867                     ; 547 if(GPIOD->IDR&(1<<7))
3869  07aa c65010        	ld	a,20496
3870  07ad a580          	bcp	a,#128
3871  07af 270a          	jreq	L5412
3872                     ; 549 	if(cnt_JP1<10)
3874  07b1 b645          	ld	a,_cnt_JP1
3875  07b3 a10a          	cp	a,#10
3876  07b5 2411          	jruge	L1512
3877                     ; 551 		cnt_JP1++;
3879  07b7 3c45          	inc	_cnt_JP1
3880  07b9 200d          	jra	L1512
3881  07bb               L5412:
3882                     ; 554 else if(!(GPIOD->IDR&(1<<7)))
3884  07bb c65010        	ld	a,20496
3885  07be a580          	bcp	a,#128
3886  07c0 2606          	jrne	L1512
3887                     ; 556 	if(cnt_JP1)
3889  07c2 3d45          	tnz	_cnt_JP1
3890  07c4 2702          	jreq	L1512
3891                     ; 558 		cnt_JP1--;
3893  07c6 3a45          	dec	_cnt_JP1
3894  07c8               L1512:
3895                     ; 563 if((cnt_JP0==10)&&(cnt_JP1==10))
3897  07c8 b646          	ld	a,_cnt_JP0
3898  07ca a10a          	cp	a,#10
3899  07cc 2608          	jrne	L7512
3901  07ce b645          	ld	a,_cnt_JP1
3902  07d0 a10a          	cp	a,#10
3903  07d2 2602          	jrne	L7512
3904                     ; 565 	jp_mode=jp0;
3906  07d4 3f47          	clr	_jp_mode
3907  07d6               L7512:
3908                     ; 567 if((cnt_JP0==0)&&(cnt_JP1==10))
3910  07d6 3d46          	tnz	_cnt_JP0
3911  07d8 260a          	jrne	L1612
3913  07da b645          	ld	a,_cnt_JP1
3914  07dc a10a          	cp	a,#10
3915  07de 2604          	jrne	L1612
3916                     ; 569 	jp_mode=jp1;
3918  07e0 35010047      	mov	_jp_mode,#1
3919  07e4               L1612:
3920                     ; 571 if((cnt_JP0==10)&&(cnt_JP1==0))
3922  07e4 b646          	ld	a,_cnt_JP0
3923  07e6 a10a          	cp	a,#10
3924  07e8 2608          	jrne	L3612
3926  07ea 3d45          	tnz	_cnt_JP1
3927  07ec 2604          	jrne	L3612
3928                     ; 573 	jp_mode=jp2;
3930  07ee 35020047      	mov	_jp_mode,#2
3931  07f2               L3612:
3932                     ; 575 if((cnt_JP0==0)&&(cnt_JP1==0))
3934  07f2 3d46          	tnz	_cnt_JP0
3935  07f4 2608          	jrne	L5612
3937  07f6 3d45          	tnz	_cnt_JP1
3938  07f8 2604          	jrne	L5612
3939                     ; 577 	jp_mode=jp3;
3941  07fa 35030047      	mov	_jp_mode,#3
3942  07fe               L5612:
3943                     ; 580 }
3946  07fe 81            	ret
3978                     ; 583 void link_drv(void)		//10Hz
3978                     ; 584 {
3979                     	switch	.text
3980  07ff               _link_drv:
3984                     ; 585 if(jp_mode!=jp3)
3986  07ff b647          	ld	a,_jp_mode
3987  0801 a103          	cp	a,#3
3988  0803 2744          	jreq	L7712
3989                     ; 587 	if(link_cnt<52)link_cnt++;
3991  0805 b65e          	ld	a,_link_cnt
3992  0807 a134          	cp	a,#52
3993  0809 2402          	jruge	L1022
3996  080b 3c5e          	inc	_link_cnt
3997  080d               L1022:
3998                     ; 588 	if(link_cnt==49)flags&=0xc1;		//если оборвалась связь первым делом сбрасываем все аварии и внешнюю блокировку
4000  080d b65e          	ld	a,_link_cnt
4001  080f a131          	cp	a,#49
4002  0811 2606          	jrne	L3022
4005  0813 b60a          	ld	a,_flags
4006  0815 a4c1          	and	a,#193
4007  0817 b70a          	ld	_flags,a
4008  0819               L3022:
4009                     ; 589 	if(link_cnt==50)
4011  0819 b65e          	ld	a,_link_cnt
4012  081b a132          	cp	a,#50
4013  081d 262e          	jrne	L5122
4014                     ; 591 		link=OFF;
4016  081f 35aa005f      	mov	_link,#170
4017                     ; 596 		if(bps_class==bpsIPS)bMAIN=1;	//если БПС определен как ИПСный - пытаться стать главным;
4019  0823 b601          	ld	a,_bps_class
4020  0825 a101          	cp	a,#1
4021  0827 2606          	jrne	L7022
4024  0829 72100001      	bset	_bMAIN
4026  082d 2004          	jra	L1122
4027  082f               L7022:
4028                     ; 597 		else bMAIN=0;
4030  082f 72110001      	bres	_bMAIN
4031  0833               L1122:
4032                     ; 599 		cnt_net_drv=0;
4034  0833 3f2f          	clr	_cnt_net_drv
4035                     ; 600     		if(!res_fl_)
4037  0835 725d0008      	tnz	_res_fl_
4038  0839 2612          	jrne	L5122
4039                     ; 602 	    		bRES_=1;
4041  083b 35010010      	mov	_bRES_,#1
4042                     ; 603 	    		res_fl_=1;
4044  083f a601          	ld	a,#1
4045  0841 ae0008        	ldw	x,#_res_fl_
4046  0844 cd0000        	call	c_eewrc
4048  0847 2004          	jra	L5122
4049  0849               L7712:
4050                     ; 607 else link=OFF;	
4052  0849 35aa005f      	mov	_link,#170
4053  084d               L5122:
4054                     ; 608 } 
4057  084d 81            	ret
4126                     .const:	section	.text
4127  0000               L05:
4128  0000 0000000b      	dc.l	11
4129  0004               L25:
4130  0004 00000001      	dc.l	1
4131                     ; 612 void vent_drv(void)
4131                     ; 613 {
4132                     	switch	.text
4133  084e               _vent_drv:
4135  084e 520e          	subw	sp,#14
4136       0000000e      OFST:	set	14
4139                     ; 616 	short vent_pwm_i_necc=400;
4141  0850 ae0190        	ldw	x,#400
4142  0853 1f07          	ldw	(OFST-7,sp),x
4143                     ; 617 	short vent_pwm_t_necc=400;
4145  0855 ae0190        	ldw	x,#400
4146  0858 1f09          	ldw	(OFST-5,sp),x
4147                     ; 618 	short vent_pwm_max_necc=400;
4149                     ; 623 	tempSL=36000L/(signed long)ee_Umax;
4151  085a ce0012        	ldw	x,_ee_Umax
4152  085d cd0000        	call	c_itolx
4154  0860 96            	ldw	x,sp
4155  0861 1c0001        	addw	x,#OFST-13
4156  0864 cd0000        	call	c_rtol
4158  0867 ae8ca0        	ldw	x,#36000
4159  086a bf02          	ldw	c_lreg+2,x
4160  086c ae0000        	ldw	x,#0
4161  086f bf00          	ldw	c_lreg,x
4162  0871 96            	ldw	x,sp
4163  0872 1c0001        	addw	x,#OFST-13
4164  0875 cd0000        	call	c_ldiv
4166  0878 96            	ldw	x,sp
4167  0879 1c000b        	addw	x,#OFST-3
4168  087c cd0000        	call	c_rtol
4170                     ; 624 	tempSL=(signed long)I/tempSL;
4172  087f be6b          	ldw	x,_I
4173  0881 cd0000        	call	c_itolx
4175  0884 96            	ldw	x,sp
4176  0885 1c000b        	addw	x,#OFST-3
4177  0888 cd0000        	call	c_ldiv
4179  088b 96            	ldw	x,sp
4180  088c 1c000b        	addw	x,#OFST-3
4181  088f cd0000        	call	c_rtol
4183                     ; 626 	if(ee_DEVICE==1) tempSL=(signed long)(I/ee_IMAXVENT);
4185  0892 ce0002        	ldw	x,_ee_DEVICE
4186  0895 a30001        	cpw	x,#1
4187  0898 2613          	jrne	L1522
4190  089a be6b          	ldw	x,_I
4191  089c 90ce0000      	ldw	y,_ee_IMAXVENT
4192  08a0 cd0000        	call	c_idiv
4194  08a3 cd0000        	call	c_itolx
4196  08a6 96            	ldw	x,sp
4197  08a7 1c000b        	addw	x,#OFST-3
4198  08aa cd0000        	call	c_rtol
4200  08ad               L1522:
4201                     ; 628 	if(tempSL>10)vent_pwm_i_necc=1000;
4203  08ad 9c            	rvf
4204  08ae 96            	ldw	x,sp
4205  08af 1c000b        	addw	x,#OFST-3
4206  08b2 cd0000        	call	c_ltor
4208  08b5 ae0000        	ldw	x,#L05
4209  08b8 cd0000        	call	c_lcmp
4211  08bb 2f07          	jrslt	L3522
4214  08bd ae03e8        	ldw	x,#1000
4215  08c0 1f07          	ldw	(OFST-7,sp),x
4217  08c2 2025          	jra	L5522
4218  08c4               L3522:
4219                     ; 629 	else if(tempSL<1)vent_pwm_i_necc=400;
4221  08c4 9c            	rvf
4222  08c5 96            	ldw	x,sp
4223  08c6 1c000b        	addw	x,#OFST-3
4224  08c9 cd0000        	call	c_ltor
4226  08cc ae0004        	ldw	x,#L25
4227  08cf cd0000        	call	c_lcmp
4229  08d2 2e07          	jrsge	L7522
4232  08d4 ae0190        	ldw	x,#400
4233  08d7 1f07          	ldw	(OFST-7,sp),x
4235  08d9 200e          	jra	L5522
4236  08db               L7522:
4237                     ; 630 	else vent_pwm_i_necc=(short)(400L + (tempSL*60L));
4239  08db 1e0d          	ldw	x,(OFST-1,sp)
4240  08dd 90ae003c      	ldw	y,#60
4241  08e1 cd0000        	call	c_imul
4243  08e4 1c0190        	addw	x,#400
4244  08e7 1f07          	ldw	(OFST-7,sp),x
4245  08e9               L5522:
4246                     ; 631 	gran(&vent_pwm_i_necc,400,1000);
4248  08e9 ae03e8        	ldw	x,#1000
4249  08ec 89            	pushw	x
4250  08ed ae0190        	ldw	x,#400
4251  08f0 89            	pushw	x
4252  08f1 96            	ldw	x,sp
4253  08f2 1c000b        	addw	x,#OFST-3
4254  08f5 cd0000        	call	_gran
4256  08f8 5b04          	addw	sp,#4
4257                     ; 633 	tempSL=(signed long)T;
4259  08fa b664          	ld	a,_T
4260  08fc b703          	ld	c_lreg+3,a
4261  08fe 48            	sll	a
4262  08ff 4f            	clr	a
4263  0900 a200          	sbc	a,#0
4264  0902 b702          	ld	c_lreg+2,a
4265  0904 b701          	ld	c_lreg+1,a
4266  0906 b700          	ld	c_lreg,a
4267  0908 96            	ldw	x,sp
4268  0909 1c000b        	addw	x,#OFST-3
4269  090c cd0000        	call	c_rtol
4271                     ; 634 	if(tempSL<=(ee_tsign-30L))vent_pwm_t_necc=400;
4273  090f 9c            	rvf
4274  0910 ce000c        	ldw	x,_ee_tsign
4275  0913 cd0000        	call	c_itolx
4277  0916 a61e          	ld	a,#30
4278  0918 cd0000        	call	c_lsbc
4280  091b 96            	ldw	x,sp
4281  091c 1c000b        	addw	x,#OFST-3
4282  091f cd0000        	call	c_lcmp
4284  0922 2f07          	jrslt	L3622
4287  0924 ae0190        	ldw	x,#400
4288  0927 1f09          	ldw	(OFST-5,sp),x
4290  0929 2030          	jra	L5622
4291  092b               L3622:
4292                     ; 635 	else if(tempSL>=ee_tsign)vent_pwm_t_necc=1000;
4294  092b 9c            	rvf
4295  092c ce000c        	ldw	x,_ee_tsign
4296  092f cd0000        	call	c_itolx
4298  0932 96            	ldw	x,sp
4299  0933 1c000b        	addw	x,#OFST-3
4300  0936 cd0000        	call	c_lcmp
4302  0939 2c07          	jrsgt	L7622
4305  093b ae03e8        	ldw	x,#1000
4306  093e 1f09          	ldw	(OFST-5,sp),x
4308  0940 2019          	jra	L5622
4309  0942               L7622:
4310                     ; 636 	else vent_pwm_t_necc=(short)(400L+(20L*(tempSL-(((signed long)ee_tsign)-30L))));
4312  0942 ce000c        	ldw	x,_ee_tsign
4313  0945 1d001e        	subw	x,#30
4314  0948 1f03          	ldw	(OFST-11,sp),x
4315  094a 1e0d          	ldw	x,(OFST-1,sp)
4316  094c 72f003        	subw	x,(OFST-11,sp)
4317  094f 90ae0014      	ldw	y,#20
4318  0953 cd0000        	call	c_imul
4320  0956 1c0190        	addw	x,#400
4321  0959 1f09          	ldw	(OFST-5,sp),x
4322  095b               L5622:
4323                     ; 637 	gran(&vent_pwm_t_necc,400,1000);
4325  095b ae03e8        	ldw	x,#1000
4326  095e 89            	pushw	x
4327  095f ae0190        	ldw	x,#400
4328  0962 89            	pushw	x
4329  0963 96            	ldw	x,sp
4330  0964 1c000d        	addw	x,#OFST-1
4331  0967 cd0000        	call	_gran
4333  096a 5b04          	addw	sp,#4
4334                     ; 639 	vent_pwm_max_necc=vent_pwm_i_necc;
4336  096c 1e07          	ldw	x,(OFST-7,sp)
4337  096e 1f05          	ldw	(OFST-9,sp),x
4338                     ; 640 	if(vent_pwm_t_necc>vent_pwm_i_necc)vent_pwm_max_necc=vent_pwm_t_necc;
4340  0970 9c            	rvf
4341  0971 1e09          	ldw	x,(OFST-5,sp)
4342  0973 1307          	cpw	x,(OFST-7,sp)
4343  0975 2d04          	jrsle	L3722
4346  0977 1e09          	ldw	x,(OFST-5,sp)
4347  0979 1f05          	ldw	(OFST-9,sp),x
4348  097b               L3722:
4349                     ; 642 	if(vent_pwm<vent_pwm_max_necc)vent_pwm+=10;
4351  097b 9c            	rvf
4352  097c be02          	ldw	x,_vent_pwm
4353  097e 1305          	cpw	x,(OFST-9,sp)
4354  0980 2e07          	jrsge	L5722
4357  0982 be02          	ldw	x,_vent_pwm
4358  0984 1c000a        	addw	x,#10
4359  0987 bf02          	ldw	_vent_pwm,x
4360  0989               L5722:
4361                     ; 643 	if(vent_pwm>vent_pwm_max_necc)vent_pwm-=10;
4363  0989 9c            	rvf
4364  098a be02          	ldw	x,_vent_pwm
4365  098c 1305          	cpw	x,(OFST-9,sp)
4366  098e 2d07          	jrsle	L7722
4369  0990 be02          	ldw	x,_vent_pwm
4370  0992 1d000a        	subw	x,#10
4371  0995 bf02          	ldw	_vent_pwm,x
4372  0997               L7722:
4373                     ; 644 	gran(&vent_pwm,400,1000);
4375  0997 ae03e8        	ldw	x,#1000
4376  099a 89            	pushw	x
4377  099b ae0190        	ldw	x,#400
4378  099e 89            	pushw	x
4379  099f ae0002        	ldw	x,#_vent_pwm
4380  09a2 cd0000        	call	_gran
4382  09a5 5b04          	addw	sp,#4
4383                     ; 646 }
4386  09a7 5b0e          	addw	sp,#14
4387  09a9 81            	ret
4421                     ; 651 void pwr_drv(void)
4421                     ; 652 {
4422                     	switch	.text
4423  09aa               _pwr_drv:
4427                     ; 656 BLOCK_INIT
4429  09aa 72145007      	bset	20487,#2
4432  09ae 72145008      	bset	20488,#2
4435  09b2 72155009      	bres	20489,#2
4436                     ; 658 if(main_cnt1<1500)main_cnt1++;
4438  09b6 9c            	rvf
4439  09b7 be4c          	ldw	x,_main_cnt1
4440  09b9 a305dc        	cpw	x,#1500
4441  09bc 2e07          	jrsge	L1132
4444  09be be4c          	ldw	x,_main_cnt1
4445  09c0 1c0001        	addw	x,#1
4446  09c3 bf4c          	ldw	_main_cnt1,x
4447  09c5               L1132:
4448                     ; 660 if((main_cnt1<(5*ee_TZAS))&&(bps_class!=bpsIPS))
4450  09c5 9c            	rvf
4451  09c6 ce0014        	ldw	x,_ee_TZAS
4452  09c9 90ae0005      	ldw	y,#5
4453  09cd cd0000        	call	c_imul
4455  09d0 b34c          	cpw	x,_main_cnt1
4456  09d2 2d0d          	jrsle	L3132
4458  09d4 b601          	ld	a,_bps_class
4459  09d6 a101          	cp	a,#1
4460  09d8 2707          	jreq	L3132
4461                     ; 662 	BLOCK_ON
4463  09da 72145005      	bset	20485,#2
4465  09de cc0a67        	jra	L5132
4466  09e1               L3132:
4467                     ; 665 else if(bps_class==bpsIPS)
4469  09e1 b601          	ld	a,_bps_class
4470  09e3 a101          	cp	a,#1
4471  09e5 261a          	jrne	L7132
4472                     ; 668 		if(bBL_IPS)
4474                     	btst	_bBL_IPS
4475  09ec 2406          	jruge	L1232
4476                     ; 670 			 BLOCK_ON
4478  09ee 72145005      	bset	20485,#2
4480  09f2 2073          	jra	L5132
4481  09f4               L1232:
4482                     ; 673 		else if(!bBL_IPS)
4484                     	btst	_bBL_IPS
4485  09f9 256c          	jrult	L5132
4486                     ; 675 			  BLOCK_OFF
4488  09fb 72155005      	bres	20485,#2
4489  09ff 2066          	jra	L5132
4490  0a01               L7132:
4491                     ; 679 else if(((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(70+(5*ee_TZAS)))))
4493  0a01 9c            	rvf
4494  0a02 ce0014        	ldw	x,_ee_TZAS
4495  0a05 90ae0005      	ldw	y,#5
4496  0a09 cd0000        	call	c_imul
4498  0a0c b34c          	cpw	x,_main_cnt1
4499  0a0e 2e3f          	jrsge	L1332
4501  0a10 9c            	rvf
4502  0a11 ce0014        	ldw	x,_ee_TZAS
4503  0a14 90ae0005      	ldw	y,#5
4504  0a18 cd0000        	call	c_imul
4506  0a1b 1c0046        	addw	x,#70
4507  0a1e b34c          	cpw	x,_main_cnt1
4508  0a20 2d2d          	jrsle	L1332
4509                     ; 681 	if(bps_class==bpsIPS)
4511  0a22 b601          	ld	a,_bps_class
4512  0a24 a101          	cp	a,#1
4513  0a26 2606          	jrne	L3332
4514                     ; 683 		  BLOCK_OFF
4516  0a28 72155005      	bres	20485,#2
4518  0a2c 2039          	jra	L5132
4519  0a2e               L3332:
4520                     ; 686 	else if(bps_class==bpsIBEP)
4522  0a2e 3d01          	tnz	_bps_class
4523  0a30 2635          	jrne	L5132
4524                     ; 688 		if(ee_DEVICE)
4526  0a32 ce0002        	ldw	x,_ee_DEVICE
4527  0a35 2712          	jreq	L1432
4528                     ; 690 			if(flags&0b00100000)BLOCK_ON //GPIOB->ODR|=(1<<2);
4530  0a37 b60a          	ld	a,_flags
4531  0a39 a520          	bcp	a,#32
4532  0a3b 2706          	jreq	L3432
4535  0a3d 72145005      	bset	20485,#2
4537  0a41 2024          	jra	L5132
4538  0a43               L3432:
4539                     ; 691 			else	BLOCK_OFF //GPIOB->ODR&=~(1<<2);
4541  0a43 72155005      	bres	20485,#2
4542  0a47 201e          	jra	L5132
4543  0a49               L1432:
4544                     ; 695 			BLOCK_OFF
4546  0a49 72155005      	bres	20485,#2
4547  0a4d 2018          	jra	L5132
4548  0a4f               L1332:
4549                     ; 700 else if(bBL)
4551                     	btst	_bBL
4552  0a54 2406          	jruge	L3532
4553                     ; 702 	BLOCK_ON
4555  0a56 72145005      	bset	20485,#2
4557  0a5a 200b          	jra	L5132
4558  0a5c               L3532:
4559                     ; 705 else if(!bBL)
4561                     	btst	_bBL
4562  0a61 2504          	jrult	L5132
4563                     ; 707 	BLOCK_OFF
4565  0a63 72155005      	bres	20485,#2
4566  0a67               L5132:
4567                     ; 711 gran(&pwm_u,2,1020);
4569  0a67 ae03fc        	ldw	x,#1020
4570  0a6a 89            	pushw	x
4571  0a6b ae0002        	ldw	x,#2
4572  0a6e 89            	pushw	x
4573  0a6f ae000b        	ldw	x,#_pwm_u
4574  0a72 cd0000        	call	_gran
4576  0a75 5b04          	addw	sp,#4
4577                     ; 721 TIM1->CCR2H= (char)(pwm_u/256);	
4579  0a77 be0b          	ldw	x,_pwm_u
4580  0a79 90ae0100      	ldw	y,#256
4581  0a7d cd0000        	call	c_idiv
4583  0a80 9f            	ld	a,xl
4584  0a81 c75267        	ld	21095,a
4585                     ; 722 TIM1->CCR2L= (char)pwm_u;
4587  0a84 55000c5268    	mov	21096,_pwm_u+1
4588                     ; 724 TIM1->CCR1H= (char)(pwm_i/256);	
4590  0a89 be0d          	ldw	x,_pwm_i
4591  0a8b 90ae0100      	ldw	y,#256
4592  0a8f cd0000        	call	c_idiv
4594  0a92 9f            	ld	a,xl
4595  0a93 c75265        	ld	21093,a
4596                     ; 725 TIM1->CCR1L= (char)pwm_i;
4598  0a96 55000e5266    	mov	21094,_pwm_i+1
4599                     ; 727 TIM1->CCR3H= (char)(vent_pwm/256);	
4601  0a9b be02          	ldw	x,_vent_pwm
4602  0a9d 90ae0100      	ldw	y,#256
4603  0aa1 cd0000        	call	c_idiv
4605  0aa4 9f            	ld	a,xl
4606  0aa5 c75269        	ld	21097,a
4607                     ; 728 TIM1->CCR3L= (char)vent_pwm;
4609  0aa8 550003526a    	mov	21098,_vent_pwm+1
4610                     ; 729 }
4613  0aad 81            	ret
4651                     ; 734 void pwr_hndl(void)				
4651                     ; 735 {
4652                     	switch	.text
4653  0aae               _pwr_hndl:
4657                     ; 736 if(jp_mode==jp3)
4659  0aae b647          	ld	a,_jp_mode
4660  0ab0 a103          	cp	a,#3
4661  0ab2 2627          	jrne	L1732
4662                     ; 738 	if((flags&0b00001010)==0)
4664  0ab4 b60a          	ld	a,_flags
4665  0ab6 a50a          	bcp	a,#10
4666  0ab8 260d          	jrne	L3732
4667                     ; 740 		pwm_u=500;
4669  0aba ae01f4        	ldw	x,#500
4670  0abd bf0b          	ldw	_pwm_u,x
4671                     ; 742 		bBL=0;
4673  0abf 72110003      	bres	_bBL
4675  0ac3 acc90bc9      	jpf	L1042
4676  0ac7               L3732:
4677                     ; 744 	else if(flags&0b00001010)
4679  0ac7 b60a          	ld	a,_flags
4680  0ac9 a50a          	bcp	a,#10
4681  0acb 2603          	jrne	L06
4682  0acd cc0bc9        	jp	L1042
4683  0ad0               L06:
4684                     ; 746 		pwm_u=0;
4686  0ad0 5f            	clrw	x
4687  0ad1 bf0b          	ldw	_pwm_u,x
4688                     ; 748 		bBL=1;
4690  0ad3 72100003      	bset	_bBL
4691  0ad7 acc90bc9      	jpf	L1042
4692  0adb               L1732:
4693                     ; 752 else if(jp_mode==jp2)
4695  0adb b647          	ld	a,_jp_mode
4696  0add a102          	cp	a,#2
4697  0adf 2610          	jrne	L3042
4698                     ; 754 	pwm_u=0;
4700  0ae1 5f            	clrw	x
4701  0ae2 bf0b          	ldw	_pwm_u,x
4702                     ; 755 	pwm_i=0x3ff;
4704  0ae4 ae03ff        	ldw	x,#1023
4705  0ae7 bf0d          	ldw	_pwm_i,x
4706                     ; 756 	bBL=0;
4708  0ae9 72110003      	bres	_bBL
4710  0aed acc90bc9      	jpf	L1042
4711  0af1               L3042:
4712                     ; 758 else if(jp_mode==jp1)
4714  0af1 b647          	ld	a,_jp_mode
4715  0af3 a101          	cp	a,#1
4716  0af5 2612          	jrne	L7042
4717                     ; 760 	pwm_u=0x3ff;
4719  0af7 ae03ff        	ldw	x,#1023
4720  0afa bf0b          	ldw	_pwm_u,x
4721                     ; 761 	pwm_i=0x3ff;
4723  0afc ae03ff        	ldw	x,#1023
4724  0aff bf0d          	ldw	_pwm_i,x
4725                     ; 762 	bBL=0;
4727  0b01 72110003      	bres	_bBL
4729  0b05 acc90bc9      	jpf	L1042
4730  0b09               L7042:
4731                     ; 765 else if((bMAIN)&&(link==ON)/*&&(ee_AVT_MODE!=0x55)*/)
4733                     	btst	_bMAIN
4734  0b0e 2417          	jruge	L3142
4736  0b10 b65f          	ld	a,_link
4737  0b12 a155          	cp	a,#85
4738  0b14 2611          	jrne	L3142
4739                     ; 767 	pwm_u=volum_u_main_;
4741  0b16 be1c          	ldw	x,_volum_u_main_
4742  0b18 bf0b          	ldw	_pwm_u,x
4743                     ; 768 	pwm_i=0x3ff;
4745  0b1a ae03ff        	ldw	x,#1023
4746  0b1d bf0d          	ldw	_pwm_i,x
4747                     ; 769 	bBL_IPS=0;
4749  0b1f 72110000      	bres	_bBL_IPS
4751  0b23 acc90bc9      	jpf	L1042
4752  0b27               L3142:
4753                     ; 772 else if(link==OFF)
4755  0b27 b65f          	ld	a,_link
4756  0b29 a1aa          	cp	a,#170
4757  0b2b 2650          	jrne	L7142
4758                     ; 781  	if(ee_DEVICE)
4760  0b2d ce0002        	ldw	x,_ee_DEVICE
4761  0b30 270d          	jreq	L1242
4762                     ; 783 		pwm_u=0x00;
4764  0b32 5f            	clrw	x
4765  0b33 bf0b          	ldw	_pwm_u,x
4766                     ; 784 		pwm_i=0x00;
4768  0b35 5f            	clrw	x
4769  0b36 bf0d          	ldw	_pwm_i,x
4770                     ; 785 		bBL=1;
4772  0b38 72100003      	bset	_bBL
4774  0b3c cc0bc9        	jra	L1042
4775  0b3f               L1242:
4776                     ; 789 		if((flags&0b00011010)==0)
4778  0b3f b60a          	ld	a,_flags
4779  0b41 a51a          	bcp	a,#26
4780  0b43 2622          	jrne	L5242
4781                     ; 791 			pwm_u=ee_U_AVT;
4783  0b45 ce000a        	ldw	x,_ee_U_AVT
4784  0b48 bf0b          	ldw	_pwm_u,x
4785                     ; 792 			gran(&pwm_u,0,1020);
4787  0b4a ae03fc        	ldw	x,#1020
4788  0b4d 89            	pushw	x
4789  0b4e 5f            	clrw	x
4790  0b4f 89            	pushw	x
4791  0b50 ae000b        	ldw	x,#_pwm_u
4792  0b53 cd0000        	call	_gran
4794  0b56 5b04          	addw	sp,#4
4795                     ; 793 		    	pwm_i=0x3ff;
4797  0b58 ae03ff        	ldw	x,#1023
4798  0b5b bf0d          	ldw	_pwm_i,x
4799                     ; 794 			bBL=0;
4801  0b5d 72110003      	bres	_bBL
4802                     ; 795 			bBL_IPS=0;
4804  0b61 72110000      	bres	_bBL_IPS
4806  0b65 2062          	jra	L1042
4807  0b67               L5242:
4808                     ; 797 		else if(flags&0b00011010)
4810  0b67 b60a          	ld	a,_flags
4811  0b69 a51a          	bcp	a,#26
4812  0b6b 275c          	jreq	L1042
4813                     ; 799 			pwm_u=0;
4815  0b6d 5f            	clrw	x
4816  0b6e bf0b          	ldw	_pwm_u,x
4817                     ; 800 			pwm_i=0;
4819  0b70 5f            	clrw	x
4820  0b71 bf0d          	ldw	_pwm_i,x
4821                     ; 801 			bBL=1;
4823  0b73 72100003      	bset	_bBL
4824                     ; 802 			bBL_IPS=1;
4826  0b77 72100000      	bset	_bBL_IPS
4827  0b7b 204c          	jra	L1042
4828  0b7d               L7142:
4829                     ; 811 else	if(link==ON)				//если есть связь
4831  0b7d b65f          	ld	a,_link
4832  0b7f a155          	cp	a,#85
4833  0b81 2646          	jrne	L1042
4834                     ; 813 	if((flags&0b00100000)==0)	//если нет блокировки извне
4836  0b83 b60a          	ld	a,_flags
4837  0b85 a520          	bcp	a,#32
4838  0b87 2630          	jrne	L7342
4839                     ; 815 		if(((flags&0b00011010)==0)||(flags&0b01000000)) 	//если нет аварий или если они заблокированы
4841  0b89 b60a          	ld	a,_flags
4842  0b8b a51a          	bcp	a,#26
4843  0b8d 2706          	jreq	L3442
4845  0b8f b60a          	ld	a,_flags
4846  0b91 a540          	bcp	a,#64
4847  0b93 2712          	jreq	L1442
4848  0b95               L3442:
4849                     ; 817 			pwm_u=vol_u_temp+_x_;					//управление от укушки + выравнивание токов
4851  0b95 be5b          	ldw	x,__x_
4852  0b97 72bb0055      	addw	x,_vol_u_temp
4853  0b9b bf0b          	ldw	_pwm_u,x
4854                     ; 818 		    	pwm_i=vol_i_temp;
4856  0b9d be53          	ldw	x,_vol_i_temp
4857  0b9f bf0d          	ldw	_pwm_i,x
4858                     ; 819 			bBL=0;
4860  0ba1 72110003      	bres	_bBL
4862  0ba5 2022          	jra	L1042
4863  0ba7               L1442:
4864                     ; 821 		else if(flags&0b00011010)					//если есть аварии
4866  0ba7 b60a          	ld	a,_flags
4867  0ba9 a51a          	bcp	a,#26
4868  0bab 271c          	jreq	L1042
4869                     ; 823 			pwm_u=0;								//то полный стоп
4871  0bad 5f            	clrw	x
4872  0bae bf0b          	ldw	_pwm_u,x
4873                     ; 824 			pwm_i=0;
4875  0bb0 5f            	clrw	x
4876  0bb1 bf0d          	ldw	_pwm_i,x
4877                     ; 825 			bBL=1;
4879  0bb3 72100003      	bset	_bBL
4880  0bb7 2010          	jra	L1042
4881  0bb9               L7342:
4882                     ; 828 	else if(flags&0b00100000)	//если заблокирован извне то полное выключение
4884  0bb9 b60a          	ld	a,_flags
4885  0bbb a520          	bcp	a,#32
4886  0bbd 270a          	jreq	L1042
4887                     ; 830 		pwm_u=0;
4889  0bbf 5f            	clrw	x
4890  0bc0 bf0b          	ldw	_pwm_u,x
4891                     ; 831 	    	pwm_i=0;
4893  0bc2 5f            	clrw	x
4894  0bc3 bf0d          	ldw	_pwm_i,x
4895                     ; 832 		bBL=1;
4897  0bc5 72100003      	bset	_bBL
4898  0bc9               L1042:
4899                     ; 838 }
4902  0bc9 81            	ret
4944                     	switch	.const
4945  0008               L46:
4946  0008 00000258      	dc.l	600
4947  000c               L66:
4948  000c 00000708      	dc.l	1800
4949  0010               L07:
4950  0010 000003e8      	dc.l	1000
4951                     ; 841 void matemat(void)
4951                     ; 842 {
4952                     	switch	.text
4953  0bca               _matemat:
4955  0bca 5204          	subw	sp,#4
4956       00000004      OFST:	set	4
4959                     ; 863 temp_SL=adc_buff_[4];
4961  0bcc ce000d        	ldw	x,_adc_buff_+8
4962  0bcf cd0000        	call	c_itolx
4964  0bd2 96            	ldw	x,sp
4965  0bd3 1c0001        	addw	x,#OFST-3
4966  0bd6 cd0000        	call	c_rtol
4968                     ; 864 temp_SL-=ee_K[0][0];
4970  0bd9 ce0018        	ldw	x,_ee_K
4971  0bdc cd0000        	call	c_itolx
4973  0bdf 96            	ldw	x,sp
4974  0be0 1c0001        	addw	x,#OFST-3
4975  0be3 cd0000        	call	c_lgsub
4977                     ; 865 if(temp_SL<0) temp_SL=0;
4979  0be6 9c            	rvf
4980  0be7 0d01          	tnz	(OFST-3,sp)
4981  0be9 2e0a          	jrsge	L3742
4984  0beb ae0000        	ldw	x,#0
4985  0bee 1f03          	ldw	(OFST-1,sp),x
4986  0bf0 ae0000        	ldw	x,#0
4987  0bf3 1f01          	ldw	(OFST-3,sp),x
4988  0bf5               L3742:
4989                     ; 866 temp_SL*=ee_K[0][1];
4991  0bf5 ce001a        	ldw	x,_ee_K+2
4992  0bf8 cd0000        	call	c_itolx
4994  0bfb 96            	ldw	x,sp
4995  0bfc 1c0001        	addw	x,#OFST-3
4996  0bff cd0000        	call	c_lgmul
4998                     ; 867 temp_SL/=600;
5000  0c02 96            	ldw	x,sp
5001  0c03 1c0001        	addw	x,#OFST-3
5002  0c06 cd0000        	call	c_ltor
5004  0c09 ae0008        	ldw	x,#L46
5005  0c0c cd0000        	call	c_ldiv
5007  0c0f 96            	ldw	x,sp
5008  0c10 1c0001        	addw	x,#OFST-3
5009  0c13 cd0000        	call	c_rtol
5011                     ; 868 I=(signed short)temp_SL;
5013  0c16 1e03          	ldw	x,(OFST-1,sp)
5014  0c18 bf6b          	ldw	_I,x
5015                     ; 873 temp_SL=(signed long)adc_buff_[1];
5017  0c1a ce0007        	ldw	x,_adc_buff_+2
5018  0c1d cd0000        	call	c_itolx
5020  0c20 96            	ldw	x,sp
5021  0c21 1c0001        	addw	x,#OFST-3
5022  0c24 cd0000        	call	c_rtol
5024                     ; 875 if(temp_SL<0) temp_SL=0;
5026  0c27 9c            	rvf
5027  0c28 0d01          	tnz	(OFST-3,sp)
5028  0c2a 2e0a          	jrsge	L5742
5031  0c2c ae0000        	ldw	x,#0
5032  0c2f 1f03          	ldw	(OFST-1,sp),x
5033  0c31 ae0000        	ldw	x,#0
5034  0c34 1f01          	ldw	(OFST-3,sp),x
5035  0c36               L5742:
5036                     ; 876 temp_SL*=(signed long)ee_K[2][1];
5038  0c36 ce0022        	ldw	x,_ee_K+10
5039  0c39 cd0000        	call	c_itolx
5041  0c3c 96            	ldw	x,sp
5042  0c3d 1c0001        	addw	x,#OFST-3
5043  0c40 cd0000        	call	c_lgmul
5045                     ; 877 temp_SL/=1800L;
5047  0c43 96            	ldw	x,sp
5048  0c44 1c0001        	addw	x,#OFST-3
5049  0c47 cd0000        	call	c_ltor
5051  0c4a ae000c        	ldw	x,#L66
5052  0c4d cd0000        	call	c_ldiv
5054  0c50 96            	ldw	x,sp
5055  0c51 1c0001        	addw	x,#OFST-3
5056  0c54 cd0000        	call	c_rtol
5058                     ; 878 Ui=(unsigned short)temp_SL;
5060  0c57 1e03          	ldw	x,(OFST-1,sp)
5061  0c59 bf67          	ldw	_Ui,x
5062                     ; 885 temp_SL=adc_buff_[3];
5064  0c5b ce000b        	ldw	x,_adc_buff_+6
5065  0c5e cd0000        	call	c_itolx
5067  0c61 96            	ldw	x,sp
5068  0c62 1c0001        	addw	x,#OFST-3
5069  0c65 cd0000        	call	c_rtol
5071                     ; 887 if(temp_SL<0) temp_SL=0;
5073  0c68 9c            	rvf
5074  0c69 0d01          	tnz	(OFST-3,sp)
5075  0c6b 2e0a          	jrsge	L7742
5078  0c6d ae0000        	ldw	x,#0
5079  0c70 1f03          	ldw	(OFST-1,sp),x
5080  0c72 ae0000        	ldw	x,#0
5081  0c75 1f01          	ldw	(OFST-3,sp),x
5082  0c77               L7742:
5083                     ; 888 temp_SL*=ee_K[1][1];
5085  0c77 ce001e        	ldw	x,_ee_K+6
5086  0c7a cd0000        	call	c_itolx
5088  0c7d 96            	ldw	x,sp
5089  0c7e 1c0001        	addw	x,#OFST-3
5090  0c81 cd0000        	call	c_lgmul
5092                     ; 889 temp_SL/=1800;
5094  0c84 96            	ldw	x,sp
5095  0c85 1c0001        	addw	x,#OFST-3
5096  0c88 cd0000        	call	c_ltor
5098  0c8b ae000c        	ldw	x,#L66
5099  0c8e cd0000        	call	c_ldiv
5101  0c91 96            	ldw	x,sp
5102  0c92 1c0001        	addw	x,#OFST-3
5103  0c95 cd0000        	call	c_rtol
5105                     ; 890 Un=(unsigned short)temp_SL;
5107  0c98 1e03          	ldw	x,(OFST-1,sp)
5108  0c9a bf69          	ldw	_Un,x
5109                     ; 893 temp_SL=adc_buff_[2];
5111  0c9c ce0009        	ldw	x,_adc_buff_+4
5112  0c9f cd0000        	call	c_itolx
5114  0ca2 96            	ldw	x,sp
5115  0ca3 1c0001        	addw	x,#OFST-3
5116  0ca6 cd0000        	call	c_rtol
5118                     ; 894 temp_SL*=ee_K[3][1];
5120  0ca9 ce0026        	ldw	x,_ee_K+14
5121  0cac cd0000        	call	c_itolx
5123  0caf 96            	ldw	x,sp
5124  0cb0 1c0001        	addw	x,#OFST-3
5125  0cb3 cd0000        	call	c_lgmul
5127                     ; 895 temp_SL/=1000;
5129  0cb6 96            	ldw	x,sp
5130  0cb7 1c0001        	addw	x,#OFST-3
5131  0cba cd0000        	call	c_ltor
5133  0cbd ae0010        	ldw	x,#L07
5134  0cc0 cd0000        	call	c_ldiv
5136  0cc3 96            	ldw	x,sp
5137  0cc4 1c0001        	addw	x,#OFST-3
5138  0cc7 cd0000        	call	c_rtol
5140                     ; 896 T=(signed short)(temp_SL-273L);
5142  0cca 7b04          	ld	a,(OFST+0,sp)
5143  0ccc 5f            	clrw	x
5144  0ccd 4d            	tnz	a
5145  0cce 2a01          	jrpl	L27
5146  0cd0 53            	cplw	x
5147  0cd1               L27:
5148  0cd1 97            	ld	xl,a
5149  0cd2 1d0111        	subw	x,#273
5150  0cd5 01            	rrwa	x,a
5151  0cd6 b764          	ld	_T,a
5152  0cd8 02            	rlwa	x,a
5153                     ; 897 if(T<-30)T=-30;
5155  0cd9 9c            	rvf
5156  0cda b664          	ld	a,_T
5157  0cdc a1e2          	cp	a,#226
5158  0cde 2e04          	jrsge	L1052
5161  0ce0 35e20064      	mov	_T,#226
5162  0ce4               L1052:
5163                     ; 898 if(T>120)T=120;
5165  0ce4 9c            	rvf
5166  0ce5 b664          	ld	a,_T
5167  0ce7 a179          	cp	a,#121
5168  0ce9 2f04          	jrslt	L3052
5171  0ceb 35780064      	mov	_T,#120
5172  0cef               L3052:
5173                     ; 900 Udb=flags;
5175  0cef b60a          	ld	a,_flags
5176  0cf1 5f            	clrw	x
5177  0cf2 97            	ld	xl,a
5178  0cf3 bf65          	ldw	_Udb,x
5179                     ; 906 }
5182  0cf5 5b04          	addw	sp,#4
5183  0cf7 81            	ret
5214                     ; 909 void temper_drv(void)		//1 Hz
5214                     ; 910 {
5215                     	switch	.text
5216  0cf8               _temper_drv:
5220                     ; 912 if(T>ee_tsign) tsign_cnt++;
5222  0cf8 9c            	rvf
5223  0cf9 5f            	clrw	x
5224  0cfa b664          	ld	a,_T
5225  0cfc 2a01          	jrpl	L67
5226  0cfe 53            	cplw	x
5227  0cff               L67:
5228  0cff 97            	ld	xl,a
5229  0d00 c3000c        	cpw	x,_ee_tsign
5230  0d03 2d09          	jrsle	L5152
5233  0d05 be4a          	ldw	x,_tsign_cnt
5234  0d07 1c0001        	addw	x,#1
5235  0d0a bf4a          	ldw	_tsign_cnt,x
5237  0d0c 201d          	jra	L7152
5238  0d0e               L5152:
5239                     ; 913 else if (T<(ee_tsign-1)) tsign_cnt--;
5241  0d0e 9c            	rvf
5242  0d0f ce000c        	ldw	x,_ee_tsign
5243  0d12 5a            	decw	x
5244  0d13 905f          	clrw	y
5245  0d15 b664          	ld	a,_T
5246  0d17 2a02          	jrpl	L001
5247  0d19 9053          	cplw	y
5248  0d1b               L001:
5249  0d1b 9097          	ld	yl,a
5250  0d1d 90bf00        	ldw	c_y,y
5251  0d20 b300          	cpw	x,c_y
5252  0d22 2d07          	jrsle	L7152
5255  0d24 be4a          	ldw	x,_tsign_cnt
5256  0d26 1d0001        	subw	x,#1
5257  0d29 bf4a          	ldw	_tsign_cnt,x
5258  0d2b               L7152:
5259                     ; 915 gran(&tsign_cnt,0,60);
5261  0d2b ae003c        	ldw	x,#60
5262  0d2e 89            	pushw	x
5263  0d2f 5f            	clrw	x
5264  0d30 89            	pushw	x
5265  0d31 ae004a        	ldw	x,#_tsign_cnt
5266  0d34 cd0000        	call	_gran
5268  0d37 5b04          	addw	sp,#4
5269                     ; 917 if(tsign_cnt>=55)
5271  0d39 9c            	rvf
5272  0d3a be4a          	ldw	x,_tsign_cnt
5273  0d3c a30037        	cpw	x,#55
5274  0d3f 2f16          	jrslt	L3252
5275                     ; 919 	if(((jp_mode==jp0)&&!(flags&0b01000000))||(jp_mode==jp3))	flags|=0b00000100; //поднять бит подогрева 
5277  0d41 3d47          	tnz	_jp_mode
5278  0d43 2606          	jrne	L1352
5280  0d45 b60a          	ld	a,_flags
5281  0d47 a540          	bcp	a,#64
5282  0d49 2706          	jreq	L7252
5283  0d4b               L1352:
5285  0d4b b647          	ld	a,_jp_mode
5286  0d4d a103          	cp	a,#3
5287  0d4f 2612          	jrne	L3352
5288  0d51               L7252:
5291  0d51 7214000a      	bset	_flags,#2
5292  0d55 200c          	jra	L3352
5293  0d57               L3252:
5294                     ; 921 else if (tsign_cnt<=5) flags&=0b11111011;	//Сбросить бит подогрева
5296  0d57 9c            	rvf
5297  0d58 be4a          	ldw	x,_tsign_cnt
5298  0d5a a30006        	cpw	x,#6
5299  0d5d 2e04          	jrsge	L3352
5302  0d5f 7215000a      	bres	_flags,#2
5303  0d63               L3352:
5304                     ; 926 if(T>ee_tmax) tmax_cnt++;
5306  0d63 9c            	rvf
5307  0d64 5f            	clrw	x
5308  0d65 b664          	ld	a,_T
5309  0d67 2a01          	jrpl	L201
5310  0d69 53            	cplw	x
5311  0d6a               L201:
5312  0d6a 97            	ld	xl,a
5313  0d6b c3000e        	cpw	x,_ee_tmax
5314  0d6e 2d09          	jrsle	L7352
5317  0d70 be48          	ldw	x,_tmax_cnt
5318  0d72 1c0001        	addw	x,#1
5319  0d75 bf48          	ldw	_tmax_cnt,x
5321  0d77 201d          	jra	L1452
5322  0d79               L7352:
5323                     ; 927 else if (T<(ee_tmax-1)) tmax_cnt--;
5325  0d79 9c            	rvf
5326  0d7a ce000e        	ldw	x,_ee_tmax
5327  0d7d 5a            	decw	x
5328  0d7e 905f          	clrw	y
5329  0d80 b664          	ld	a,_T
5330  0d82 2a02          	jrpl	L401
5331  0d84 9053          	cplw	y
5332  0d86               L401:
5333  0d86 9097          	ld	yl,a
5334  0d88 90bf00        	ldw	c_y,y
5335  0d8b b300          	cpw	x,c_y
5336  0d8d 2d07          	jrsle	L1452
5339  0d8f be48          	ldw	x,_tmax_cnt
5340  0d91 1d0001        	subw	x,#1
5341  0d94 bf48          	ldw	_tmax_cnt,x
5342  0d96               L1452:
5343                     ; 929 gran(&tmax_cnt,0,60);
5345  0d96 ae003c        	ldw	x,#60
5346  0d99 89            	pushw	x
5347  0d9a 5f            	clrw	x
5348  0d9b 89            	pushw	x
5349  0d9c ae0048        	ldw	x,#_tmax_cnt
5350  0d9f cd0000        	call	_gran
5352  0da2 5b04          	addw	sp,#4
5353                     ; 931 if(tmax_cnt>=55)
5355  0da4 9c            	rvf
5356  0da5 be48          	ldw	x,_tmax_cnt
5357  0da7 a30037        	cpw	x,#55
5358  0daa 2f16          	jrslt	L5452
5359                     ; 933 	if(((jp_mode==jp0)&&!(flags&0b01000000))||(jp_mode==jp3))	flags|=0b00000010;
5361  0dac 3d47          	tnz	_jp_mode
5362  0dae 2606          	jrne	L3552
5364  0db0 b60a          	ld	a,_flags
5365  0db2 a540          	bcp	a,#64
5366  0db4 2706          	jreq	L1552
5367  0db6               L3552:
5369  0db6 b647          	ld	a,_jp_mode
5370  0db8 a103          	cp	a,#3
5371  0dba 2612          	jrne	L5552
5372  0dbc               L1552:
5375  0dbc 7212000a      	bset	_flags,#1
5376  0dc0 200c          	jra	L5552
5377  0dc2               L5452:
5378                     ; 935 else if (tmax_cnt<=5) flags&=0b11111101;
5380  0dc2 9c            	rvf
5381  0dc3 be48          	ldw	x,_tmax_cnt
5382  0dc5 a30006        	cpw	x,#6
5383  0dc8 2e04          	jrsge	L5552
5386  0dca 7213000a      	bres	_flags,#1
5387  0dce               L5552:
5388                     ; 938 } 
5391  0dce 81            	ret
5423                     ; 941 void u_drv(void)		//1Hz
5423                     ; 942 { 
5424                     	switch	.text
5425  0dcf               _u_drv:
5429                     ; 943 if(jp_mode!=jp3)
5431  0dcf b647          	ld	a,_jp_mode
5432  0dd1 a103          	cp	a,#3
5433  0dd3 2770          	jreq	L1752
5434                     ; 945 	if(Ui>ee_Umax)umax_cnt++;
5436  0dd5 9c            	rvf
5437  0dd6 be67          	ldw	x,_Ui
5438  0dd8 c30012        	cpw	x,_ee_Umax
5439  0ddb 2d09          	jrsle	L3752
5442  0ddd be62          	ldw	x,_umax_cnt
5443  0ddf 1c0001        	addw	x,#1
5444  0de2 bf62          	ldw	_umax_cnt,x
5446  0de4 2003          	jra	L5752
5447  0de6               L3752:
5448                     ; 946 	else umax_cnt=0;
5450  0de6 5f            	clrw	x
5451  0de7 bf62          	ldw	_umax_cnt,x
5452  0de9               L5752:
5453                     ; 947 	gran(&umax_cnt,0,10);
5455  0de9 ae000a        	ldw	x,#10
5456  0dec 89            	pushw	x
5457  0ded 5f            	clrw	x
5458  0dee 89            	pushw	x
5459  0def ae0062        	ldw	x,#_umax_cnt
5460  0df2 cd0000        	call	_gran
5462  0df5 5b04          	addw	sp,#4
5463                     ; 948 	if(umax_cnt>=10)flags|=0b00001000; 	//Поднять аварию по превышению напряжения
5465  0df7 9c            	rvf
5466  0df8 be62          	ldw	x,_umax_cnt
5467  0dfa a3000a        	cpw	x,#10
5468  0dfd 2f04          	jrslt	L7752
5471  0dff 7216000a      	bset	_flags,#3
5472  0e03               L7752:
5473                     ; 951 	if((Ui<Un)&&((Un-Ui)>ee_dU)&&(!BLOCK_IS_ON/*(GPIOB->ODR&(1<<2))*/))umin_cnt++;	
5475  0e03 9c            	rvf
5476  0e04 be67          	ldw	x,_Ui
5477  0e06 b369          	cpw	x,_Un
5478  0e08 2e1c          	jrsge	L1062
5480  0e0a 9c            	rvf
5481  0e0b be69          	ldw	x,_Un
5482  0e0d 72b00067      	subw	x,_Ui
5483  0e11 c30010        	cpw	x,_ee_dU
5484  0e14 2d10          	jrsle	L1062
5486  0e16 c65005        	ld	a,20485
5487  0e19 a504          	bcp	a,#4
5488  0e1b 2609          	jrne	L1062
5491  0e1d be60          	ldw	x,_umin_cnt
5492  0e1f 1c0001        	addw	x,#1
5493  0e22 bf60          	ldw	_umin_cnt,x
5495  0e24 2003          	jra	L3062
5496  0e26               L1062:
5497                     ; 952 	else umin_cnt=0;
5499  0e26 5f            	clrw	x
5500  0e27 bf60          	ldw	_umin_cnt,x
5501  0e29               L3062:
5502                     ; 953 	gran(&umin_cnt,0,10);	
5504  0e29 ae000a        	ldw	x,#10
5505  0e2c 89            	pushw	x
5506  0e2d 5f            	clrw	x
5507  0e2e 89            	pushw	x
5508  0e2f ae0060        	ldw	x,#_umin_cnt
5509  0e32 cd0000        	call	_gran
5511  0e35 5b04          	addw	sp,#4
5512                     ; 954 	if(umin_cnt>=10)flags|=0b00010000;	  
5514  0e37 9c            	rvf
5515  0e38 be60          	ldw	x,_umin_cnt
5516  0e3a a3000a        	cpw	x,#10
5517  0e3d 2f6f          	jrslt	L7062
5520  0e3f 7218000a      	bset	_flags,#4
5521  0e43 2069          	jra	L7062
5522  0e45               L1752:
5523                     ; 956 else if(jp_mode==jp3)
5525  0e45 b647          	ld	a,_jp_mode
5526  0e47 a103          	cp	a,#3
5527  0e49 2663          	jrne	L7062
5528                     ; 958 	if(Ui>700)umax_cnt++;
5530  0e4b 9c            	rvf
5531  0e4c be67          	ldw	x,_Ui
5532  0e4e a302bd        	cpw	x,#701
5533  0e51 2f09          	jrslt	L3162
5536  0e53 be62          	ldw	x,_umax_cnt
5537  0e55 1c0001        	addw	x,#1
5538  0e58 bf62          	ldw	_umax_cnt,x
5540  0e5a 2003          	jra	L5162
5541  0e5c               L3162:
5542                     ; 959 	else umax_cnt=0;
5544  0e5c 5f            	clrw	x
5545  0e5d bf62          	ldw	_umax_cnt,x
5546  0e5f               L5162:
5547                     ; 960 	gran(&umax_cnt,0,10);
5549  0e5f ae000a        	ldw	x,#10
5550  0e62 89            	pushw	x
5551  0e63 5f            	clrw	x
5552  0e64 89            	pushw	x
5553  0e65 ae0062        	ldw	x,#_umax_cnt
5554  0e68 cd0000        	call	_gran
5556  0e6b 5b04          	addw	sp,#4
5557                     ; 961 	if(umax_cnt>=10)flags|=0b00001000;
5559  0e6d 9c            	rvf
5560  0e6e be62          	ldw	x,_umax_cnt
5561  0e70 a3000a        	cpw	x,#10
5562  0e73 2f04          	jrslt	L7162
5565  0e75 7216000a      	bset	_flags,#3
5566  0e79               L7162:
5567                     ; 964 	if((Ui<200)&&(!BLOCK_IS_ON/*(GPIOB->ODR&(1<<2))*/))umin_cnt++;	
5569  0e79 9c            	rvf
5570  0e7a be67          	ldw	x,_Ui
5571  0e7c a300c8        	cpw	x,#200
5572  0e7f 2e10          	jrsge	L1262
5574  0e81 c65005        	ld	a,20485
5575  0e84 a504          	bcp	a,#4
5576  0e86 2609          	jrne	L1262
5579  0e88 be60          	ldw	x,_umin_cnt
5580  0e8a 1c0001        	addw	x,#1
5581  0e8d bf60          	ldw	_umin_cnt,x
5583  0e8f 2003          	jra	L3262
5584  0e91               L1262:
5585                     ; 965 	else umin_cnt=0;
5587  0e91 5f            	clrw	x
5588  0e92 bf60          	ldw	_umin_cnt,x
5589  0e94               L3262:
5590                     ; 966 	gran(&umin_cnt,0,10);	
5592  0e94 ae000a        	ldw	x,#10
5593  0e97 89            	pushw	x
5594  0e98 5f            	clrw	x
5595  0e99 89            	pushw	x
5596  0e9a ae0060        	ldw	x,#_umin_cnt
5597  0e9d cd0000        	call	_gran
5599  0ea0 5b04          	addw	sp,#4
5600                     ; 967 	if(umin_cnt>=10)flags|=0b00010000;	  
5602  0ea2 9c            	rvf
5603  0ea3 be60          	ldw	x,_umin_cnt
5604  0ea5 a3000a        	cpw	x,#10
5605  0ea8 2f04          	jrslt	L7062
5608  0eaa 7218000a      	bset	_flags,#4
5609  0eae               L7062:
5610                     ; 969 }
5613  0eae 81            	ret
5640                     ; 972 void x_drv(void)
5640                     ; 973 {
5641                     	switch	.text
5642  0eaf               _x_drv:
5646                     ; 974 if(_x__==_x_)
5648  0eaf be59          	ldw	x,__x__
5649  0eb1 b35b          	cpw	x,__x_
5650  0eb3 262a          	jrne	L7362
5651                     ; 976 	if(_x_cnt<60)
5653  0eb5 9c            	rvf
5654  0eb6 be57          	ldw	x,__x_cnt
5655  0eb8 a3003c        	cpw	x,#60
5656  0ebb 2e25          	jrsge	L7462
5657                     ; 978 		_x_cnt++;
5659  0ebd be57          	ldw	x,__x_cnt
5660  0ebf 1c0001        	addw	x,#1
5661  0ec2 bf57          	ldw	__x_cnt,x
5662                     ; 979 		if(_x_cnt>=60)
5664  0ec4 9c            	rvf
5665  0ec5 be57          	ldw	x,__x_cnt
5666  0ec7 a3003c        	cpw	x,#60
5667  0eca 2f16          	jrslt	L7462
5668                     ; 981 			if(_x_ee_!=_x_)_x_ee_=_x_;
5670  0ecc ce0016        	ldw	x,__x_ee_
5671  0ecf b35b          	cpw	x,__x_
5672  0ed1 270f          	jreq	L7462
5675  0ed3 be5b          	ldw	x,__x_
5676  0ed5 89            	pushw	x
5677  0ed6 ae0016        	ldw	x,#__x_ee_
5678  0ed9 cd0000        	call	c_eewrw
5680  0edc 85            	popw	x
5681  0edd 2003          	jra	L7462
5682  0edf               L7362:
5683                     ; 986 else _x_cnt=0;
5685  0edf 5f            	clrw	x
5686  0ee0 bf57          	ldw	__x_cnt,x
5687  0ee2               L7462:
5688                     ; 988 if(_x_cnt>60) _x_cnt=0;	
5690  0ee2 9c            	rvf
5691  0ee3 be57          	ldw	x,__x_cnt
5692  0ee5 a3003d        	cpw	x,#61
5693  0ee8 2f03          	jrslt	L1562
5696  0eea 5f            	clrw	x
5697  0eeb bf57          	ldw	__x_cnt,x
5698  0eed               L1562:
5699                     ; 990 _x__=_x_;
5701  0eed be5b          	ldw	x,__x_
5702  0eef bf59          	ldw	__x__,x
5703                     ; 991 }
5706  0ef1 81            	ret
5732                     ; 994 void apv_start(void)
5732                     ; 995 {
5733                     	switch	.text
5734  0ef2               _apv_start:
5738                     ; 996 if((apv_cnt[0]==0)&&(apv_cnt[1]==0)&&(apv_cnt[2]==0)&&!bAPV)
5740  0ef2 3d42          	tnz	_apv_cnt
5741  0ef4 2624          	jrne	L3662
5743  0ef6 3d43          	tnz	_apv_cnt+1
5744  0ef8 2620          	jrne	L3662
5746  0efa 3d44          	tnz	_apv_cnt+2
5747  0efc 261c          	jrne	L3662
5749                     	btst	_bAPV
5750  0f03 2515          	jrult	L3662
5751                     ; 998 	apv_cnt[0]=60;
5753  0f05 353c0042      	mov	_apv_cnt,#60
5754                     ; 999 	apv_cnt[1]=60;
5756  0f09 353c0043      	mov	_apv_cnt+1,#60
5757                     ; 1000 	apv_cnt[2]=60;
5759  0f0d 353c0044      	mov	_apv_cnt+2,#60
5760                     ; 1001 	apv_cnt_=3600;
5762  0f11 ae0e10        	ldw	x,#3600
5763  0f14 bf40          	ldw	_apv_cnt_,x
5764                     ; 1002 	bAPV=1;	
5766  0f16 72100002      	bset	_bAPV
5767  0f1a               L3662:
5768                     ; 1004 }
5771  0f1a 81            	ret
5797                     ; 1007 void apv_stop(void)
5797                     ; 1008 {
5798                     	switch	.text
5799  0f1b               _apv_stop:
5803                     ; 1009 apv_cnt[0]=0;
5805  0f1b 3f42          	clr	_apv_cnt
5806                     ; 1010 apv_cnt[1]=0;
5808  0f1d 3f43          	clr	_apv_cnt+1
5809                     ; 1011 apv_cnt[2]=0;
5811  0f1f 3f44          	clr	_apv_cnt+2
5812                     ; 1012 apv_cnt_=0;	
5814  0f21 5f            	clrw	x
5815  0f22 bf40          	ldw	_apv_cnt_,x
5816                     ; 1013 bAPV=0;
5818  0f24 72110002      	bres	_bAPV
5819                     ; 1014 }
5822  0f28 81            	ret
5857                     ; 1018 void apv_hndl(void)
5857                     ; 1019 {
5858                     	switch	.text
5859  0f29               _apv_hndl:
5863                     ; 1020 if(apv_cnt[0])
5865  0f29 3d42          	tnz	_apv_cnt
5866  0f2b 271e          	jreq	L5072
5867                     ; 1022 	apv_cnt[0]--;
5869  0f2d 3a42          	dec	_apv_cnt
5870                     ; 1023 	if(apv_cnt[0]==0)
5872  0f2f 3d42          	tnz	_apv_cnt
5873  0f31 265a          	jrne	L1172
5874                     ; 1025 		flags&=0b11100001;
5876  0f33 b60a          	ld	a,_flags
5877  0f35 a4e1          	and	a,#225
5878  0f37 b70a          	ld	_flags,a
5879                     ; 1026 		tsign_cnt=0;
5881  0f39 5f            	clrw	x
5882  0f3a bf4a          	ldw	_tsign_cnt,x
5883                     ; 1027 		tmax_cnt=0;
5885  0f3c 5f            	clrw	x
5886  0f3d bf48          	ldw	_tmax_cnt,x
5887                     ; 1028 		umax_cnt=0;
5889  0f3f 5f            	clrw	x
5890  0f40 bf62          	ldw	_umax_cnt,x
5891                     ; 1029 		umin_cnt=0;
5893  0f42 5f            	clrw	x
5894  0f43 bf60          	ldw	_umin_cnt,x
5895                     ; 1031 		led_drv_cnt=30;
5897  0f45 351e0019      	mov	_led_drv_cnt,#30
5898  0f49 2042          	jra	L1172
5899  0f4b               L5072:
5900                     ; 1034 else if(apv_cnt[1])
5902  0f4b 3d43          	tnz	_apv_cnt+1
5903  0f4d 271e          	jreq	L3172
5904                     ; 1036 	apv_cnt[1]--;
5906  0f4f 3a43          	dec	_apv_cnt+1
5907                     ; 1037 	if(apv_cnt[1]==0)
5909  0f51 3d43          	tnz	_apv_cnt+1
5910  0f53 2638          	jrne	L1172
5911                     ; 1039 		flags&=0b11100001;
5913  0f55 b60a          	ld	a,_flags
5914  0f57 a4e1          	and	a,#225
5915  0f59 b70a          	ld	_flags,a
5916                     ; 1040 		tsign_cnt=0;
5918  0f5b 5f            	clrw	x
5919  0f5c bf4a          	ldw	_tsign_cnt,x
5920                     ; 1041 		tmax_cnt=0;
5922  0f5e 5f            	clrw	x
5923  0f5f bf48          	ldw	_tmax_cnt,x
5924                     ; 1042 		umax_cnt=0;
5926  0f61 5f            	clrw	x
5927  0f62 bf62          	ldw	_umax_cnt,x
5928                     ; 1043 		umin_cnt=0;
5930  0f64 5f            	clrw	x
5931  0f65 bf60          	ldw	_umin_cnt,x
5932                     ; 1045 		led_drv_cnt=30;
5934  0f67 351e0019      	mov	_led_drv_cnt,#30
5935  0f6b 2020          	jra	L1172
5936  0f6d               L3172:
5937                     ; 1048 else if(apv_cnt[2])
5939  0f6d 3d44          	tnz	_apv_cnt+2
5940  0f6f 271c          	jreq	L1172
5941                     ; 1050 	apv_cnt[2]--;
5943  0f71 3a44          	dec	_apv_cnt+2
5944                     ; 1051 	if(apv_cnt[2]==0)
5946  0f73 3d44          	tnz	_apv_cnt+2
5947  0f75 2616          	jrne	L1172
5948                     ; 1053 		flags&=0b11100001;
5950  0f77 b60a          	ld	a,_flags
5951  0f79 a4e1          	and	a,#225
5952  0f7b b70a          	ld	_flags,a
5953                     ; 1054 		tsign_cnt=0;
5955  0f7d 5f            	clrw	x
5956  0f7e bf4a          	ldw	_tsign_cnt,x
5957                     ; 1055 		tmax_cnt=0;
5959  0f80 5f            	clrw	x
5960  0f81 bf48          	ldw	_tmax_cnt,x
5961                     ; 1056 		umax_cnt=0;
5963  0f83 5f            	clrw	x
5964  0f84 bf62          	ldw	_umax_cnt,x
5965                     ; 1057 		umin_cnt=0;          
5967  0f86 5f            	clrw	x
5968  0f87 bf60          	ldw	_umin_cnt,x
5969                     ; 1059 		led_drv_cnt=30;
5971  0f89 351e0019      	mov	_led_drv_cnt,#30
5972  0f8d               L1172:
5973                     ; 1063 if(apv_cnt_)
5975  0f8d be40          	ldw	x,_apv_cnt_
5976  0f8f 2712          	jreq	L5272
5977                     ; 1065 	apv_cnt_--;
5979  0f91 be40          	ldw	x,_apv_cnt_
5980  0f93 1d0001        	subw	x,#1
5981  0f96 bf40          	ldw	_apv_cnt_,x
5982                     ; 1066 	if(apv_cnt_==0) 
5984  0f98 be40          	ldw	x,_apv_cnt_
5985  0f9a 2607          	jrne	L5272
5986                     ; 1068 		bAPV=0;
5988  0f9c 72110002      	bres	_bAPV
5989                     ; 1069 		apv_start();
5991  0fa0 cd0ef2        	call	_apv_start
5993  0fa3               L5272:
5994                     ; 1073 if((umin_cnt==0)&&(umax_cnt==0)/*&&(cnt_adc_ch_2_delta==0)*/&&(!BLOCK_IS_ON/*(GPIOB->ODR&(1<<2))*/))
5996  0fa3 be60          	ldw	x,_umin_cnt
5997  0fa5 261e          	jrne	L1372
5999  0fa7 be62          	ldw	x,_umax_cnt
6000  0fa9 261a          	jrne	L1372
6002  0fab c65005        	ld	a,20485
6003  0fae a504          	bcp	a,#4
6004  0fb0 2613          	jrne	L1372
6005                     ; 1075 	if(cnt_apv_off<20)
6007  0fb2 b63f          	ld	a,_cnt_apv_off
6008  0fb4 a114          	cp	a,#20
6009  0fb6 240f          	jruge	L7372
6010                     ; 1077 		cnt_apv_off++;
6012  0fb8 3c3f          	inc	_cnt_apv_off
6013                     ; 1078 		if(cnt_apv_off>=20)
6015  0fba b63f          	ld	a,_cnt_apv_off
6016  0fbc a114          	cp	a,#20
6017  0fbe 2507          	jrult	L7372
6018                     ; 1080 			apv_stop();
6020  0fc0 cd0f1b        	call	_apv_stop
6022  0fc3 2002          	jra	L7372
6023  0fc5               L1372:
6024                     ; 1084 else cnt_apv_off=0;	
6026  0fc5 3f3f          	clr	_cnt_apv_off
6027  0fc7               L7372:
6028                     ; 1086 }
6031  0fc7 81            	ret
6034                     	switch	.ubsct
6035  0000               L1472_flags_old:
6036  0000 00            	ds.b	1
6072                     ; 1089 void flags_drv(void)
6072                     ; 1090 {
6073                     	switch	.text
6074  0fc8               _flags_drv:
6078                     ; 1092 if(jp_mode!=jp3) 
6080  0fc8 b647          	ld	a,_jp_mode
6081  0fca a103          	cp	a,#3
6082  0fcc 2723          	jreq	L1672
6083                     ; 1094 	if(((flags&(1<<3)/*0b00001000*/)&&(!(flags_old&(1<<3)/*0b00001000*/)))||((flags&(1<<4)/*0b00010000*/)&&(!(flags_old&(1<<4)/*0b00010000*/)))) 
6085  0fce b60a          	ld	a,_flags
6086  0fd0 a508          	bcp	a,#8
6087  0fd2 2706          	jreq	L7672
6089  0fd4 b600          	ld	a,L1472_flags_old
6090  0fd6 a508          	bcp	a,#8
6091  0fd8 270c          	jreq	L5672
6092  0fda               L7672:
6094  0fda b60a          	ld	a,_flags
6095  0fdc a510          	bcp	a,#16
6096  0fde 2726          	jreq	L3772
6098  0fe0 b600          	ld	a,L1472_flags_old
6099  0fe2 a510          	bcp	a,#16
6100  0fe4 2620          	jrne	L3772
6101  0fe6               L5672:
6102                     ; 1096     		if(link==OFF)apv_start();
6104  0fe6 b65f          	ld	a,_link
6105  0fe8 a1aa          	cp	a,#170
6106  0fea 261a          	jrne	L3772
6109  0fec cd0ef2        	call	_apv_start
6111  0fef 2015          	jra	L3772
6112  0ff1               L1672:
6113                     ; 1099 else if(jp_mode==jp3) 
6115  0ff1 b647          	ld	a,_jp_mode
6116  0ff3 a103          	cp	a,#3
6117  0ff5 260f          	jrne	L3772
6118                     ; 1101 	if((flags&(1<<3)/*0b00001000*/)&&(!(flags_old&(1<<3)/*0b00001000*/))) 
6120  0ff7 b60a          	ld	a,_flags
6121  0ff9 a508          	bcp	a,#8
6122  0ffb 2709          	jreq	L3772
6124  0ffd b600          	ld	a,L1472_flags_old
6125  0fff a508          	bcp	a,#8
6126  1001 2603          	jrne	L3772
6127                     ; 1103     		apv_start();
6129  1003 cd0ef2        	call	_apv_start
6131  1006               L3772:
6132                     ; 1106 flags_old=flags;
6134  1006 450a00        	mov	L1472_flags_old,_flags
6135                     ; 1108 } 
6138  1009 81            	ret
6173                     ; 1245 void adr_drv_v4(char in)
6173                     ; 1246 {
6174                     	switch	.text
6175  100a               _adr_drv_v4:
6179                     ; 1247 if(adress!=in)adress=in;
6181  100a c10001        	cp	a,_adress
6182  100d 2703          	jreq	L7103
6185  100f c70001        	ld	_adress,a
6186  1012               L7103:
6187                     ; 1248 }
6190  1012 81            	ret
6219                     ; 1251 void adr_drv_v3(void)
6219                     ; 1252 {
6220                     	switch	.text
6221  1013               _adr_drv_v3:
6223  1013 88            	push	a
6224       00000001      OFST:	set	1
6227                     ; 1258 GPIOB->DDR&=~(1<<0);
6229  1014 72115007      	bres	20487,#0
6230                     ; 1259 GPIOB->CR1&=~(1<<0);
6232  1018 72115008      	bres	20488,#0
6233                     ; 1260 GPIOB->CR2&=~(1<<0);
6235  101c 72115009      	bres	20489,#0
6236                     ; 1261 ADC2->CR2=0x08;
6238  1020 35085402      	mov	21506,#8
6239                     ; 1262 ADC2->CR1=0x40;
6241  1024 35405401      	mov	21505,#64
6242                     ; 1263 ADC2->CSR=0x20+0;
6244  1028 35205400      	mov	21504,#32
6245                     ; 1264 ADC2->CR1|=1;
6247  102c 72105401      	bset	21505,#0
6248                     ; 1265 ADC2->CR1|=1;
6250  1030 72105401      	bset	21505,#0
6251                     ; 1266 adr_drv_stat=1;
6253  1034 35010007      	mov	_adr_drv_stat,#1
6254  1038               L1303:
6255                     ; 1267 while(adr_drv_stat==1);
6258  1038 b607          	ld	a,_adr_drv_stat
6259  103a a101          	cp	a,#1
6260  103c 27fa          	jreq	L1303
6261                     ; 1269 GPIOB->DDR&=~(1<<1);
6263  103e 72135007      	bres	20487,#1
6264                     ; 1270 GPIOB->CR1&=~(1<<1);
6266  1042 72135008      	bres	20488,#1
6267                     ; 1271 GPIOB->CR2&=~(1<<1);
6269  1046 72135009      	bres	20489,#1
6270                     ; 1272 ADC2->CR2=0x08;
6272  104a 35085402      	mov	21506,#8
6273                     ; 1273 ADC2->CR1=0x40;
6275  104e 35405401      	mov	21505,#64
6276                     ; 1274 ADC2->CSR=0x20+1;
6278  1052 35215400      	mov	21504,#33
6279                     ; 1275 ADC2->CR1|=1;
6281  1056 72105401      	bset	21505,#0
6282                     ; 1276 ADC2->CR1|=1;
6284  105a 72105401      	bset	21505,#0
6285                     ; 1277 adr_drv_stat=3;
6287  105e 35030007      	mov	_adr_drv_stat,#3
6288  1062               L7303:
6289                     ; 1278 while(adr_drv_stat==3);
6292  1062 b607          	ld	a,_adr_drv_stat
6293  1064 a103          	cp	a,#3
6294  1066 27fa          	jreq	L7303
6295                     ; 1280 GPIOE->DDR&=~(1<<6);
6297  1068 721d5016      	bres	20502,#6
6298                     ; 1281 GPIOE->CR1&=~(1<<6);
6300  106c 721d5017      	bres	20503,#6
6301                     ; 1282 GPIOE->CR2&=~(1<<6);
6303  1070 721d5018      	bres	20504,#6
6304                     ; 1283 ADC2->CR2=0x08;
6306  1074 35085402      	mov	21506,#8
6307                     ; 1284 ADC2->CR1=0x40;
6309  1078 35405401      	mov	21505,#64
6310                     ; 1285 ADC2->CSR=0x20+9;
6312  107c 35295400      	mov	21504,#41
6313                     ; 1286 ADC2->CR1|=1;
6315  1080 72105401      	bset	21505,#0
6316                     ; 1287 ADC2->CR1|=1;
6318  1084 72105401      	bset	21505,#0
6319                     ; 1288 adr_drv_stat=5;
6321  1088 35050007      	mov	_adr_drv_stat,#5
6322  108c               L5403:
6323                     ; 1289 while(adr_drv_stat==5);
6326  108c b607          	ld	a,_adr_drv_stat
6327  108e a105          	cp	a,#5
6328  1090 27fa          	jreq	L5403
6329                     ; 1293 if((adc_buff_[0]>=(ADR_CONST_0-20))&&(adc_buff_[0]<=(ADR_CONST_0+20))) adr[0]=0;
6331  1092 9c            	rvf
6332  1093 ce0005        	ldw	x,_adc_buff_
6333  1096 a3022a        	cpw	x,#554
6334  1099 2f0f          	jrslt	L3503
6336  109b 9c            	rvf
6337  109c ce0005        	ldw	x,_adc_buff_
6338  109f a30253        	cpw	x,#595
6339  10a2 2e06          	jrsge	L3503
6342  10a4 725f0002      	clr	_adr
6344  10a8 204c          	jra	L5503
6345  10aa               L3503:
6346                     ; 1294 else if((adc_buff_[0]>=(ADR_CONST_1-20))&&(adc_buff_[0]<=(ADR_CONST_1+20))) adr[0]=1;
6348  10aa 9c            	rvf
6349  10ab ce0005        	ldw	x,_adc_buff_
6350  10ae a3036d        	cpw	x,#877
6351  10b1 2f0f          	jrslt	L7503
6353  10b3 9c            	rvf
6354  10b4 ce0005        	ldw	x,_adc_buff_
6355  10b7 a30396        	cpw	x,#918
6356  10ba 2e06          	jrsge	L7503
6359  10bc 35010002      	mov	_adr,#1
6361  10c0 2034          	jra	L5503
6362  10c2               L7503:
6363                     ; 1295 else if((adc_buff_[0]>=(ADR_CONST_2-20))&&(adc_buff_[0]<=(ADR_CONST_2+20))) adr[0]=2;
6365  10c2 9c            	rvf
6366  10c3 ce0005        	ldw	x,_adc_buff_
6367  10c6 a302a3        	cpw	x,#675
6368  10c9 2f0f          	jrslt	L3603
6370  10cb 9c            	rvf
6371  10cc ce0005        	ldw	x,_adc_buff_
6372  10cf a302cc        	cpw	x,#716
6373  10d2 2e06          	jrsge	L3603
6376  10d4 35020002      	mov	_adr,#2
6378  10d8 201c          	jra	L5503
6379  10da               L3603:
6380                     ; 1296 else if((adc_buff_[0]>=(ADR_CONST_3-20))&&(adc_buff_[0]<=(ADR_CONST_3+20))) adr[0]=3;
6382  10da 9c            	rvf
6383  10db ce0005        	ldw	x,_adc_buff_
6384  10de a303e3        	cpw	x,#995
6385  10e1 2f0f          	jrslt	L7603
6387  10e3 9c            	rvf
6388  10e4 ce0005        	ldw	x,_adc_buff_
6389  10e7 a3040c        	cpw	x,#1036
6390  10ea 2e06          	jrsge	L7603
6393  10ec 35030002      	mov	_adr,#3
6395  10f0 2004          	jra	L5503
6396  10f2               L7603:
6397                     ; 1297 else adr[0]=5;
6399  10f2 35050002      	mov	_adr,#5
6400  10f6               L5503:
6401                     ; 1299 if((adc_buff_[1]>=(ADR_CONST_0-20))&&(adc_buff_[1]<=(ADR_CONST_0+20))) adr[1]=0;
6403  10f6 9c            	rvf
6404  10f7 ce0007        	ldw	x,_adc_buff_+2
6405  10fa a3022a        	cpw	x,#554
6406  10fd 2f0f          	jrslt	L3703
6408  10ff 9c            	rvf
6409  1100 ce0007        	ldw	x,_adc_buff_+2
6410  1103 a30253        	cpw	x,#595
6411  1106 2e06          	jrsge	L3703
6414  1108 725f0003      	clr	_adr+1
6416  110c 204c          	jra	L5703
6417  110e               L3703:
6418                     ; 1300 else if((adc_buff_[1]>=(ADR_CONST_1-20))&&(adc_buff_[1]<=(ADR_CONST_1+20))) adr[1]=1;
6420  110e 9c            	rvf
6421  110f ce0007        	ldw	x,_adc_buff_+2
6422  1112 a3036d        	cpw	x,#877
6423  1115 2f0f          	jrslt	L7703
6425  1117 9c            	rvf
6426  1118 ce0007        	ldw	x,_adc_buff_+2
6427  111b a30396        	cpw	x,#918
6428  111e 2e06          	jrsge	L7703
6431  1120 35010003      	mov	_adr+1,#1
6433  1124 2034          	jra	L5703
6434  1126               L7703:
6435                     ; 1301 else if((adc_buff_[1]>=(ADR_CONST_2-20))&&(adc_buff_[1]<=(ADR_CONST_2+20))) adr[1]=2;
6437  1126 9c            	rvf
6438  1127 ce0007        	ldw	x,_adc_buff_+2
6439  112a a302a3        	cpw	x,#675
6440  112d 2f0f          	jrslt	L3013
6442  112f 9c            	rvf
6443  1130 ce0007        	ldw	x,_adc_buff_+2
6444  1133 a302cc        	cpw	x,#716
6445  1136 2e06          	jrsge	L3013
6448  1138 35020003      	mov	_adr+1,#2
6450  113c 201c          	jra	L5703
6451  113e               L3013:
6452                     ; 1302 else if((adc_buff_[1]>=(ADR_CONST_3-20))&&(adc_buff_[1]<=(ADR_CONST_3+20))) adr[1]=3;
6454  113e 9c            	rvf
6455  113f ce0007        	ldw	x,_adc_buff_+2
6456  1142 a303e3        	cpw	x,#995
6457  1145 2f0f          	jrslt	L7013
6459  1147 9c            	rvf
6460  1148 ce0007        	ldw	x,_adc_buff_+2
6461  114b a3040c        	cpw	x,#1036
6462  114e 2e06          	jrsge	L7013
6465  1150 35030003      	mov	_adr+1,#3
6467  1154 2004          	jra	L5703
6468  1156               L7013:
6469                     ; 1303 else adr[1]=5;
6471  1156 35050003      	mov	_adr+1,#5
6472  115a               L5703:
6473                     ; 1305 if((adc_buff_[9]>=(ADR_CONST_0-20))&&(adc_buff_[9]<=(ADR_CONST_0+20))) adr[2]=0;
6475  115a 9c            	rvf
6476  115b ce0017        	ldw	x,_adc_buff_+18
6477  115e a3022a        	cpw	x,#554
6478  1161 2f0f          	jrslt	L3113
6480  1163 9c            	rvf
6481  1164 ce0017        	ldw	x,_adc_buff_+18
6482  1167 a30253        	cpw	x,#595
6483  116a 2e06          	jrsge	L3113
6486  116c 725f0004      	clr	_adr+2
6488  1170 204c          	jra	L5113
6489  1172               L3113:
6490                     ; 1306 else if((adc_buff_[9]>=(ADR_CONST_1-20))&&(adc_buff_[9]<=(ADR_CONST_1+20))) adr[2]=1;
6492  1172 9c            	rvf
6493  1173 ce0017        	ldw	x,_adc_buff_+18
6494  1176 a3036d        	cpw	x,#877
6495  1179 2f0f          	jrslt	L7113
6497  117b 9c            	rvf
6498  117c ce0017        	ldw	x,_adc_buff_+18
6499  117f a30396        	cpw	x,#918
6500  1182 2e06          	jrsge	L7113
6503  1184 35010004      	mov	_adr+2,#1
6505  1188 2034          	jra	L5113
6506  118a               L7113:
6507                     ; 1307 else if((adc_buff_[9]>=(ADR_CONST_2-20))&&(adc_buff_[9]<=(ADR_CONST_2+20))) adr[2]=2;
6509  118a 9c            	rvf
6510  118b ce0017        	ldw	x,_adc_buff_+18
6511  118e a302a3        	cpw	x,#675
6512  1191 2f0f          	jrslt	L3213
6514  1193 9c            	rvf
6515  1194 ce0017        	ldw	x,_adc_buff_+18
6516  1197 a302cc        	cpw	x,#716
6517  119a 2e06          	jrsge	L3213
6520  119c 35020004      	mov	_adr+2,#2
6522  11a0 201c          	jra	L5113
6523  11a2               L3213:
6524                     ; 1308 else if((adc_buff_[9]>=(ADR_CONST_3-20))&&(adc_buff_[9]<=(ADR_CONST_3+20))) adr[2]=3;
6526  11a2 9c            	rvf
6527  11a3 ce0017        	ldw	x,_adc_buff_+18
6528  11a6 a303e3        	cpw	x,#995
6529  11a9 2f0f          	jrslt	L7213
6531  11ab 9c            	rvf
6532  11ac ce0017        	ldw	x,_adc_buff_+18
6533  11af a3040c        	cpw	x,#1036
6534  11b2 2e06          	jrsge	L7213
6537  11b4 35030004      	mov	_adr+2,#3
6539  11b8 2004          	jra	L5113
6540  11ba               L7213:
6541                     ; 1309 else adr[2]=5;
6543  11ba 35050004      	mov	_adr+2,#5
6544  11be               L5113:
6545                     ; 1313 if((adr[0]==5)||(adr[1]==5)||(adr[2]==5))
6547  11be c60002        	ld	a,_adr
6548  11c1 a105          	cp	a,#5
6549  11c3 270e          	jreq	L5313
6551  11c5 c60003        	ld	a,_adr+1
6552  11c8 a105          	cp	a,#5
6553  11ca 2707          	jreq	L5313
6555  11cc c60004        	ld	a,_adr+2
6556  11cf a105          	cp	a,#5
6557  11d1 2606          	jrne	L3313
6558  11d3               L5313:
6559                     ; 1316 	adress_error=1;
6561  11d3 35010000      	mov	_adress_error,#1
6563  11d7               L1413:
6564                     ; 1327 }
6567  11d7 84            	pop	a
6568  11d8 81            	ret
6569  11d9               L3313:
6570                     ; 1320 	if(adr[2]&0x02) bps_class=bpsIPS;
6572  11d9 c60004        	ld	a,_adr+2
6573  11dc a502          	bcp	a,#2
6574  11de 2706          	jreq	L3413
6577  11e0 35010001      	mov	_bps_class,#1
6579  11e4 2002          	jra	L5413
6580  11e6               L3413:
6581                     ; 1321 	else bps_class=bpsIBEP;
6583  11e6 3f01          	clr	_bps_class
6584  11e8               L5413:
6585                     ; 1323 	adress = adr[0] + (adr[1]*4) + ((adr[2]&0x01)*16);
6587  11e8 c60004        	ld	a,_adr+2
6588  11eb a401          	and	a,#1
6589  11ed 97            	ld	xl,a
6590  11ee a610          	ld	a,#16
6591  11f0 42            	mul	x,a
6592  11f1 9f            	ld	a,xl
6593  11f2 6b01          	ld	(OFST+0,sp),a
6594  11f4 c60003        	ld	a,_adr+1
6595  11f7 48            	sll	a
6596  11f8 48            	sll	a
6597  11f9 cb0002        	add	a,_adr
6598  11fc 1b01          	add	a,(OFST+0,sp)
6599  11fe c70001        	ld	_adress,a
6600  1201 20d4          	jra	L1413
6644                     ; 1330 void volum_u_main_drv(void)
6644                     ; 1331 {
6645                     	switch	.text
6646  1203               _volum_u_main_drv:
6648  1203 88            	push	a
6649       00000001      OFST:	set	1
6652                     ; 1334 if(bMAIN)
6654                     	btst	_bMAIN
6655  1209 2503          	jrult	L031
6656  120b cc1354        	jp	L5613
6657  120e               L031:
6658                     ; 1336 	if(Un<(UU_AVT-10))volum_u_main_+=5;
6660  120e 9c            	rvf
6661  120f ce0006        	ldw	x,_UU_AVT
6662  1212 1d000a        	subw	x,#10
6663  1215 b369          	cpw	x,_Un
6664  1217 2d09          	jrsle	L7613
6667  1219 be1c          	ldw	x,_volum_u_main_
6668  121b 1c0005        	addw	x,#5
6669  121e bf1c          	ldw	_volum_u_main_,x
6671  1220 2036          	jra	L1713
6672  1222               L7613:
6673                     ; 1337 	else if(Un<(UU_AVT-1))volum_u_main_++;
6675  1222 9c            	rvf
6676  1223 ce0006        	ldw	x,_UU_AVT
6677  1226 5a            	decw	x
6678  1227 b369          	cpw	x,_Un
6679  1229 2d09          	jrsle	L3713
6682  122b be1c          	ldw	x,_volum_u_main_
6683  122d 1c0001        	addw	x,#1
6684  1230 bf1c          	ldw	_volum_u_main_,x
6686  1232 2024          	jra	L1713
6687  1234               L3713:
6688                     ; 1338 	else if(Un>(UU_AVT+10))volum_u_main_-=10;
6690  1234 9c            	rvf
6691  1235 ce0006        	ldw	x,_UU_AVT
6692  1238 1c000a        	addw	x,#10
6693  123b b369          	cpw	x,_Un
6694  123d 2e09          	jrsge	L7713
6697  123f be1c          	ldw	x,_volum_u_main_
6698  1241 1d000a        	subw	x,#10
6699  1244 bf1c          	ldw	_volum_u_main_,x
6701  1246 2010          	jra	L1713
6702  1248               L7713:
6703                     ; 1339 	else if(Un>(UU_AVT+1))volum_u_main_--;
6705  1248 9c            	rvf
6706  1249 ce0006        	ldw	x,_UU_AVT
6707  124c 5c            	incw	x
6708  124d b369          	cpw	x,_Un
6709  124f 2e07          	jrsge	L1713
6712  1251 be1c          	ldw	x,_volum_u_main_
6713  1253 1d0001        	subw	x,#1
6714  1256 bf1c          	ldw	_volum_u_main_,x
6715  1258               L1713:
6716                     ; 1340 	if(volum_u_main_>1020)volum_u_main_=1020;
6718  1258 9c            	rvf
6719  1259 be1c          	ldw	x,_volum_u_main_
6720  125b a303fd        	cpw	x,#1021
6721  125e 2f05          	jrslt	L5023
6724  1260 ae03fc        	ldw	x,#1020
6725  1263 bf1c          	ldw	_volum_u_main_,x
6726  1265               L5023:
6727                     ; 1341 	if(volum_u_main_<0)volum_u_main_=0;
6729  1265 9c            	rvf
6730  1266 be1c          	ldw	x,_volum_u_main_
6731  1268 2e03          	jrsge	L7023
6734  126a 5f            	clrw	x
6735  126b bf1c          	ldw	_volum_u_main_,x
6736  126d               L7023:
6737                     ; 1344 	i_main_sigma=0;
6739  126d 5f            	clrw	x
6740  126e bf0c          	ldw	_i_main_sigma,x
6741                     ; 1345 	i_main_num_of_bps=0;
6743  1270 3f0e          	clr	_i_main_num_of_bps
6744                     ; 1346 	for(i=0;i<6;i++)
6746  1272 0f01          	clr	(OFST+0,sp)
6747  1274               L1123:
6748                     ; 1348 		if(i_main_flag[i])
6750  1274 7b01          	ld	a,(OFST+0,sp)
6751  1276 5f            	clrw	x
6752  1277 97            	ld	xl,a
6753  1278 6d11          	tnz	(_i_main_flag,x)
6754  127a 2719          	jreq	L7123
6755                     ; 1350 			i_main_sigma+=i_main[i];
6757  127c 7b01          	ld	a,(OFST+0,sp)
6758  127e 5f            	clrw	x
6759  127f 97            	ld	xl,a
6760  1280 58            	sllw	x
6761  1281 ee17          	ldw	x,(_i_main,x)
6762  1283 72bb000c      	addw	x,_i_main_sigma
6763  1287 bf0c          	ldw	_i_main_sigma,x
6764                     ; 1351 			i_main_flag[i]=1;
6766  1289 7b01          	ld	a,(OFST+0,sp)
6767  128b 5f            	clrw	x
6768  128c 97            	ld	xl,a
6769  128d a601          	ld	a,#1
6770  128f e711          	ld	(_i_main_flag,x),a
6771                     ; 1352 			i_main_num_of_bps++;
6773  1291 3c0e          	inc	_i_main_num_of_bps
6775  1293 2006          	jra	L1223
6776  1295               L7123:
6777                     ; 1356 			i_main_flag[i]=0;	
6779  1295 7b01          	ld	a,(OFST+0,sp)
6780  1297 5f            	clrw	x
6781  1298 97            	ld	xl,a
6782  1299 6f11          	clr	(_i_main_flag,x)
6783  129b               L1223:
6784                     ; 1346 	for(i=0;i<6;i++)
6786  129b 0c01          	inc	(OFST+0,sp)
6789  129d 7b01          	ld	a,(OFST+0,sp)
6790  129f a106          	cp	a,#6
6791  12a1 25d1          	jrult	L1123
6792                     ; 1359 	i_main_avg=i_main_sigma/i_main_num_of_bps;
6794  12a3 be0c          	ldw	x,_i_main_sigma
6795  12a5 b60e          	ld	a,_i_main_num_of_bps
6796  12a7 905f          	clrw	y
6797  12a9 9097          	ld	yl,a
6798  12ab cd0000        	call	c_idiv
6800  12ae bf0f          	ldw	_i_main_avg,x
6801                     ; 1360 	for(i=0;i<6;i++)
6803  12b0 0f01          	clr	(OFST+0,sp)
6804  12b2               L3223:
6805                     ; 1362 		if(i_main_flag[i])
6807  12b2 7b01          	ld	a,(OFST+0,sp)
6808  12b4 5f            	clrw	x
6809  12b5 97            	ld	xl,a
6810  12b6 6d11          	tnz	(_i_main_flag,x)
6811  12b8 2603cc1349    	jreq	L1323
6812                     ; 1364 			if(i_main[i]<(i_main_avg-10))x[i]++;
6814  12bd 9c            	rvf
6815  12be 7b01          	ld	a,(OFST+0,sp)
6816  12c0 5f            	clrw	x
6817  12c1 97            	ld	xl,a
6818  12c2 58            	sllw	x
6819  12c3 90be0f        	ldw	y,_i_main_avg
6820  12c6 72a2000a      	subw	y,#10
6821  12ca 90bf00        	ldw	c_y,y
6822  12cd 9093          	ldw	y,x
6823  12cf 90ee17        	ldw	y,(_i_main,y)
6824  12d2 90b300        	cpw	y,c_y
6825  12d5 2e11          	jrsge	L3323
6828  12d7 7b01          	ld	a,(OFST+0,sp)
6829  12d9 5f            	clrw	x
6830  12da 97            	ld	xl,a
6831  12db 58            	sllw	x
6832  12dc 9093          	ldw	y,x
6833  12de ee23          	ldw	x,(_x,x)
6834  12e0 1c0001        	addw	x,#1
6835  12e3 90ef23        	ldw	(_x,y),x
6837  12e6 2029          	jra	L5323
6838  12e8               L3323:
6839                     ; 1365 			else if(i_main[i]>(i_main_avg+10))x[i]--;
6841  12e8 9c            	rvf
6842  12e9 7b01          	ld	a,(OFST+0,sp)
6843  12eb 5f            	clrw	x
6844  12ec 97            	ld	xl,a
6845  12ed 58            	sllw	x
6846  12ee 90be0f        	ldw	y,_i_main_avg
6847  12f1 72a9000a      	addw	y,#10
6848  12f5 90bf00        	ldw	c_y,y
6849  12f8 9093          	ldw	y,x
6850  12fa 90ee17        	ldw	y,(_i_main,y)
6851  12fd 90b300        	cpw	y,c_y
6852  1300 2d0f          	jrsle	L5323
6855  1302 7b01          	ld	a,(OFST+0,sp)
6856  1304 5f            	clrw	x
6857  1305 97            	ld	xl,a
6858  1306 58            	sllw	x
6859  1307 9093          	ldw	y,x
6860  1309 ee23          	ldw	x,(_x,x)
6861  130b 1d0001        	subw	x,#1
6862  130e 90ef23        	ldw	(_x,y),x
6863  1311               L5323:
6864                     ; 1366 			if(x[i]>100)x[i]=100;
6866  1311 9c            	rvf
6867  1312 7b01          	ld	a,(OFST+0,sp)
6868  1314 5f            	clrw	x
6869  1315 97            	ld	xl,a
6870  1316 58            	sllw	x
6871  1317 9093          	ldw	y,x
6872  1319 90ee23        	ldw	y,(_x,y)
6873  131c 90a30065      	cpw	y,#101
6874  1320 2f0b          	jrslt	L1423
6877  1322 7b01          	ld	a,(OFST+0,sp)
6878  1324 5f            	clrw	x
6879  1325 97            	ld	xl,a
6880  1326 58            	sllw	x
6881  1327 90ae0064      	ldw	y,#100
6882  132b ef23          	ldw	(_x,x),y
6883  132d               L1423:
6884                     ; 1367 			if(x[i]<-100)x[i]=-100;
6886  132d 9c            	rvf
6887  132e 7b01          	ld	a,(OFST+0,sp)
6888  1330 5f            	clrw	x
6889  1331 97            	ld	xl,a
6890  1332 58            	sllw	x
6891  1333 9093          	ldw	y,x
6892  1335 90ee23        	ldw	y,(_x,y)
6893  1338 90a3ff9c      	cpw	y,#65436
6894  133c 2e0b          	jrsge	L1323
6897  133e 7b01          	ld	a,(OFST+0,sp)
6898  1340 5f            	clrw	x
6899  1341 97            	ld	xl,a
6900  1342 58            	sllw	x
6901  1343 90aeff9c      	ldw	y,#65436
6902  1347 ef23          	ldw	(_x,x),y
6903  1349               L1323:
6904                     ; 1360 	for(i=0;i<6;i++)
6906  1349 0c01          	inc	(OFST+0,sp)
6909  134b 7b01          	ld	a,(OFST+0,sp)
6910  134d a106          	cp	a,#6
6911  134f 2403cc12b2    	jrult	L3223
6912  1354               L5613:
6913                     ; 1374 }
6916  1354 84            	pop	a
6917  1355 81            	ret
6940                     ; 1377 void init_CAN(void) {
6941                     	switch	.text
6942  1356               _init_CAN:
6946                     ; 1378 	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
6948  1356 72135420      	bres	21536,#1
6949                     ; 1379 	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
6951  135a 72105420      	bset	21536,#0
6953  135e               L7523:
6954                     ; 1380 	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
6956  135e c65421        	ld	a,21537
6957  1361 a501          	bcp	a,#1
6958  1363 27f9          	jreq	L7523
6959                     ; 1382 	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
6961  1365 72185420      	bset	21536,#4
6962                     ; 1384 	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
6964  1369 35025427      	mov	21543,#2
6965                     ; 1393 	CAN->Page.Filter01.F0R1= UKU_MESS_STID>>3;			// 16 bits mode
6967  136d 35135428      	mov	21544,#19
6968                     ; 1394 	CAN->Page.Filter01.F0R2= UKU_MESS_STID<<5;
6970  1371 35c05429      	mov	21545,#192
6971                     ; 1395 	CAN->Page.Filter01.F0R5= UKU_MESS_STID_MASK>>3;
6973  1375 357f542c      	mov	21548,#127
6974                     ; 1396 	CAN->Page.Filter01.F0R6= UKU_MESS_STID_MASK<<5;
6976  1379 35e0542d      	mov	21549,#224
6977                     ; 1398 	CAN->Page.Filter01.F1R1= BPS_MESS_STID>>3;			// 16 bits mode
6979  137d 35315430      	mov	21552,#49
6980                     ; 1399 	CAN->Page.Filter01.F1R2= BPS_MESS_STID<<5;
6982  1381 35c05431      	mov	21553,#192
6983                     ; 1400 	CAN->Page.Filter01.F1R5= BPS_MESS_STID_MASK>>3;
6985  1385 357f5434      	mov	21556,#127
6986                     ; 1401 	CAN->Page.Filter01.F1R6= BPS_MESS_STID_MASK<<5;
6988  1389 35e05435      	mov	21557,#224
6989                     ; 1405 	CAN->PSR= 6;									// set page 6
6991  138d 35065427      	mov	21543,#6
6992                     ; 1410 	CAN->Page.Config.FMR1&=~3;								//mask mode
6994  1391 c65430        	ld	a,21552
6995  1394 a4fc          	and	a,#252
6996  1396 c75430        	ld	21552,a
6997                     ; 1416 	CAN->Page.Config.FCR1= ((3<<1) & (CAN_FCR1_FSC00 | CAN_FCR1_FSC01));		//16 bit scale
6999  1399 35065432      	mov	21554,#6
7000                     ; 1417 	CAN->Page.Config.FCR1= ((3<<5) & (CAN_FCR1_FSC10 | CAN_FCR1_FSC11));		//16 bit scale
7002  139d 35605432      	mov	21554,#96
7003                     ; 1420 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
7005  13a1 72105432      	bset	21554,#0
7006                     ; 1421 	CAN->Page.Config.FCR1|= CAN_FCR1_FACT1;
7008  13a5 72185432      	bset	21554,#4
7009                     ; 1424 	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
7011  13a9 35065427      	mov	21543,#6
7012                     ; 1426 	CAN->Page.Config.BTR1= 9;					// CAN_BTR1_BRP=9, 	tq= fcpu/(9+1)
7014  13ad 3509542c      	mov	21548,#9
7015                     ; 1427 	CAN->Page.Config.BTR2= (1<<7)|(6<<4) | 7; 		// BS2=8, BS1=7, 		
7017  13b1 35e7542d      	mov	21549,#231
7018                     ; 1429 	CAN->IER|=(1<<1);
7020  13b5 72125425      	bset	21541,#1
7021                     ; 1432 	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
7023  13b9 72115420      	bres	21536,#0
7025  13bd               L5623:
7026                     ; 1433 	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
7028  13bd c65421        	ld	a,21537
7029  13c0 a501          	bcp	a,#1
7030  13c2 26f9          	jrne	L5623
7031                     ; 1434 }
7034  13c4 81            	ret
7142                     ; 1437 void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
7142                     ; 1438 {
7143                     	switch	.text
7144  13c5               _can_transmit:
7146  13c5 89            	pushw	x
7147       00000000      OFST:	set	0
7150                     ; 1440 if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>3))can_buff_wr_ptr=0;
7152  13c6 b670          	ld	a,_can_buff_wr_ptr
7153  13c8 a104          	cp	a,#4
7154  13ca 2502          	jrult	L7433
7157  13cc 3f70          	clr	_can_buff_wr_ptr
7158  13ce               L7433:
7159                     ; 1442 can_out_buff[can_buff_wr_ptr][0]=(char)(id_st>>6);
7161  13ce b670          	ld	a,_can_buff_wr_ptr
7162  13d0 97            	ld	xl,a
7163  13d1 a610          	ld	a,#16
7164  13d3 42            	mul	x,a
7165  13d4 1601          	ldw	y,(OFST+1,sp)
7166  13d6 a606          	ld	a,#6
7167  13d8               L631:
7168  13d8 9054          	srlw	y
7169  13da 4a            	dec	a
7170  13db 26fb          	jrne	L631
7171  13dd 909f          	ld	a,yl
7172  13df e771          	ld	(_can_out_buff,x),a
7173                     ; 1443 can_out_buff[can_buff_wr_ptr][1]=(char)(id_st<<2);
7175  13e1 b670          	ld	a,_can_buff_wr_ptr
7176  13e3 97            	ld	xl,a
7177  13e4 a610          	ld	a,#16
7178  13e6 42            	mul	x,a
7179  13e7 7b02          	ld	a,(OFST+2,sp)
7180  13e9 48            	sll	a
7181  13ea 48            	sll	a
7182  13eb e772          	ld	(_can_out_buff+1,x),a
7183                     ; 1445 can_out_buff[can_buff_wr_ptr][2]=data0;
7185  13ed b670          	ld	a,_can_buff_wr_ptr
7186  13ef 97            	ld	xl,a
7187  13f0 a610          	ld	a,#16
7188  13f2 42            	mul	x,a
7189  13f3 7b05          	ld	a,(OFST+5,sp)
7190  13f5 e773          	ld	(_can_out_buff+2,x),a
7191                     ; 1446 can_out_buff[can_buff_wr_ptr][3]=data1;
7193  13f7 b670          	ld	a,_can_buff_wr_ptr
7194  13f9 97            	ld	xl,a
7195  13fa a610          	ld	a,#16
7196  13fc 42            	mul	x,a
7197  13fd 7b06          	ld	a,(OFST+6,sp)
7198  13ff e774          	ld	(_can_out_buff+3,x),a
7199                     ; 1447 can_out_buff[can_buff_wr_ptr][4]=data2;
7201  1401 b670          	ld	a,_can_buff_wr_ptr
7202  1403 97            	ld	xl,a
7203  1404 a610          	ld	a,#16
7204  1406 42            	mul	x,a
7205  1407 7b07          	ld	a,(OFST+7,sp)
7206  1409 e775          	ld	(_can_out_buff+4,x),a
7207                     ; 1448 can_out_buff[can_buff_wr_ptr][5]=data3;
7209  140b b670          	ld	a,_can_buff_wr_ptr
7210  140d 97            	ld	xl,a
7211  140e a610          	ld	a,#16
7212  1410 42            	mul	x,a
7213  1411 7b08          	ld	a,(OFST+8,sp)
7214  1413 e776          	ld	(_can_out_buff+5,x),a
7215                     ; 1449 can_out_buff[can_buff_wr_ptr][6]=data4;
7217  1415 b670          	ld	a,_can_buff_wr_ptr
7218  1417 97            	ld	xl,a
7219  1418 a610          	ld	a,#16
7220  141a 42            	mul	x,a
7221  141b 7b09          	ld	a,(OFST+9,sp)
7222  141d e777          	ld	(_can_out_buff+6,x),a
7223                     ; 1450 can_out_buff[can_buff_wr_ptr][7]=data5;
7225  141f b670          	ld	a,_can_buff_wr_ptr
7226  1421 97            	ld	xl,a
7227  1422 a610          	ld	a,#16
7228  1424 42            	mul	x,a
7229  1425 7b0a          	ld	a,(OFST+10,sp)
7230  1427 e778          	ld	(_can_out_buff+7,x),a
7231                     ; 1451 can_out_buff[can_buff_wr_ptr][8]=data6;
7233  1429 b670          	ld	a,_can_buff_wr_ptr
7234  142b 97            	ld	xl,a
7235  142c a610          	ld	a,#16
7236  142e 42            	mul	x,a
7237  142f 7b0b          	ld	a,(OFST+11,sp)
7238  1431 e779          	ld	(_can_out_buff+8,x),a
7239                     ; 1452 can_out_buff[can_buff_wr_ptr][9]=data7;
7241  1433 b670          	ld	a,_can_buff_wr_ptr
7242  1435 97            	ld	xl,a
7243  1436 a610          	ld	a,#16
7244  1438 42            	mul	x,a
7245  1439 7b0c          	ld	a,(OFST+12,sp)
7246  143b e77a          	ld	(_can_out_buff+9,x),a
7247                     ; 1454 can_buff_wr_ptr++;
7249  143d 3c70          	inc	_can_buff_wr_ptr
7250                     ; 1455 if(can_buff_wr_ptr>3)can_buff_wr_ptr=0;
7252  143f b670          	ld	a,_can_buff_wr_ptr
7253  1441 a104          	cp	a,#4
7254  1443 2502          	jrult	L1533
7257  1445 3f70          	clr	_can_buff_wr_ptr
7258  1447               L1533:
7259                     ; 1456 } 
7262  1447 85            	popw	x
7263  1448 81            	ret
7292                     ; 1459 void can_tx_hndl(void)
7292                     ; 1460 {
7293                     	switch	.text
7294  1449               _can_tx_hndl:
7298                     ; 1461 if(bTX_FREE)
7300  1449 3d08          	tnz	_bTX_FREE
7301  144b 2757          	jreq	L3633
7302                     ; 1463 	if(can_buff_rd_ptr!=can_buff_wr_ptr)
7304  144d b66f          	ld	a,_can_buff_rd_ptr
7305  144f b170          	cp	a,_can_buff_wr_ptr
7306  1451 275f          	jreq	L1733
7307                     ; 1465 		bTX_FREE=0;
7309  1453 3f08          	clr	_bTX_FREE
7310                     ; 1467 		CAN->PSR= 0;
7312  1455 725f5427      	clr	21543
7313                     ; 1468 		CAN->Page.TxMailbox.MDLCR=8;
7315  1459 35085429      	mov	21545,#8
7316                     ; 1469 		CAN->Page.TxMailbox.MIDR1=can_out_buff[can_buff_rd_ptr][0];
7318  145d b66f          	ld	a,_can_buff_rd_ptr
7319  145f 97            	ld	xl,a
7320  1460 a610          	ld	a,#16
7321  1462 42            	mul	x,a
7322  1463 e671          	ld	a,(_can_out_buff,x)
7323  1465 c7542a        	ld	21546,a
7324                     ; 1470 		CAN->Page.TxMailbox.MIDR2=can_out_buff[can_buff_rd_ptr][1];
7326  1468 b66f          	ld	a,_can_buff_rd_ptr
7327  146a 97            	ld	xl,a
7328  146b a610          	ld	a,#16
7329  146d 42            	mul	x,a
7330  146e e672          	ld	a,(_can_out_buff+1,x)
7331  1470 c7542b        	ld	21547,a
7332                     ; 1472 		memcpy(&CAN->Page.TxMailbox.MDAR1, &can_out_buff[can_buff_rd_ptr][2],8);
7334  1473 b66f          	ld	a,_can_buff_rd_ptr
7335  1475 97            	ld	xl,a
7336  1476 a610          	ld	a,#16
7337  1478 42            	mul	x,a
7338  1479 01            	rrwa	x,a
7339  147a ab73          	add	a,#_can_out_buff+2
7340  147c 2401          	jrnc	L241
7341  147e 5c            	incw	x
7342  147f               L241:
7343  147f 5f            	clrw	x
7344  1480 97            	ld	xl,a
7345  1481 bf00          	ldw	c_x,x
7346  1483 ae0008        	ldw	x,#8
7347  1486               L441:
7348  1486 5a            	decw	x
7349  1487 92d600        	ld	a,([c_x],x)
7350  148a d7542e        	ld	(21550,x),a
7351  148d 5d            	tnzw	x
7352  148e 26f6          	jrne	L441
7353                     ; 1474 		can_buff_rd_ptr++;
7355  1490 3c6f          	inc	_can_buff_rd_ptr
7356                     ; 1475 		if(can_buff_rd_ptr>3)can_buff_rd_ptr=0;
7358  1492 b66f          	ld	a,_can_buff_rd_ptr
7359  1494 a104          	cp	a,#4
7360  1496 2502          	jrult	L7633
7363  1498 3f6f          	clr	_can_buff_rd_ptr
7364  149a               L7633:
7365                     ; 1477 		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;
7367  149a 72105428      	bset	21544,#0
7368                     ; 1478 		CAN->IER|=(1<<0);
7370  149e 72105425      	bset	21541,#0
7371  14a2 200e          	jra	L1733
7372  14a4               L3633:
7373                     ; 1483 	tx_busy_cnt++;
7375  14a4 3c6e          	inc	_tx_busy_cnt
7376                     ; 1484 	if(tx_busy_cnt>=100)
7378  14a6 b66e          	ld	a,_tx_busy_cnt
7379  14a8 a164          	cp	a,#100
7380  14aa 2506          	jrult	L1733
7381                     ; 1486 		tx_busy_cnt=0;
7383  14ac 3f6e          	clr	_tx_busy_cnt
7384                     ; 1487 		bTX_FREE=1;
7386  14ae 35010008      	mov	_bTX_FREE,#1
7387  14b2               L1733:
7388                     ; 1490 }
7391  14b2 81            	ret
7430                     ; 1493 void net_drv(void)
7430                     ; 1494 { 
7431                     	switch	.text
7432  14b3               _net_drv:
7436                     ; 1496 if(bMAIN)
7438                     	btst	_bMAIN
7439  14b8 2503          	jrult	L051
7440  14ba cc1560        	jp	L5043
7441  14bd               L051:
7442                     ; 1498 	if(++cnt_net_drv>=7) cnt_net_drv=0; 
7444  14bd 3c2f          	inc	_cnt_net_drv
7445  14bf b62f          	ld	a,_cnt_net_drv
7446  14c1 a107          	cp	a,#7
7447  14c3 2502          	jrult	L7043
7450  14c5 3f2f          	clr	_cnt_net_drv
7451  14c7               L7043:
7452                     ; 1500 	if(cnt_net_drv<=5) 
7454  14c7 b62f          	ld	a,_cnt_net_drv
7455  14c9 a106          	cp	a,#6
7456  14cb 244c          	jruge	L1143
7457                     ; 1502 		can_transmit(0x09e,cnt_net_drv,cnt_net_drv,GETTM,0,(char)(volum_u_main_+x[cnt_net_drv]),(char)((volum_u_main_+x[cnt_net_drv])/256),1000,1000);
7459  14cd 4be8          	push	#232
7460  14cf 4be8          	push	#232
7461  14d1 b62f          	ld	a,_cnt_net_drv
7462  14d3 5f            	clrw	x
7463  14d4 97            	ld	xl,a
7464  14d5 58            	sllw	x
7465  14d6 ee23          	ldw	x,(_x,x)
7466  14d8 72bb001c      	addw	x,_volum_u_main_
7467  14dc 90ae0100      	ldw	y,#256
7468  14e0 cd0000        	call	c_idiv
7470  14e3 9f            	ld	a,xl
7471  14e4 88            	push	a
7472  14e5 b62f          	ld	a,_cnt_net_drv
7473  14e7 5f            	clrw	x
7474  14e8 97            	ld	xl,a
7475  14e9 58            	sllw	x
7476  14ea e624          	ld	a,(_x+1,x)
7477  14ec bb1d          	add	a,_volum_u_main_+1
7478  14ee 88            	push	a
7479  14ef 4b00          	push	#0
7480  14f1 4bed          	push	#237
7481  14f3 3b002f        	push	_cnt_net_drv
7482  14f6 3b002f        	push	_cnt_net_drv
7483  14f9 ae009e        	ldw	x,#158
7484  14fc cd13c5        	call	_can_transmit
7486  14ff 5b08          	addw	sp,#8
7487                     ; 1503 		i_main_bps_cnt[cnt_net_drv]++;
7489  1501 b62f          	ld	a,_cnt_net_drv
7490  1503 5f            	clrw	x
7491  1504 97            	ld	xl,a
7492  1505 6c06          	inc	(_i_main_bps_cnt,x)
7493                     ; 1504 		if(i_main_bps_cnt[cnt_net_drv]>10)i_main_flag[cnt_net_drv]=0;
7495  1507 b62f          	ld	a,_cnt_net_drv
7496  1509 5f            	clrw	x
7497  150a 97            	ld	xl,a
7498  150b e606          	ld	a,(_i_main_bps_cnt,x)
7499  150d a10b          	cp	a,#11
7500  150f 254f          	jrult	L5043
7503  1511 b62f          	ld	a,_cnt_net_drv
7504  1513 5f            	clrw	x
7505  1514 97            	ld	xl,a
7506  1515 6f11          	clr	(_i_main_flag,x)
7507  1517 2047          	jra	L5043
7508  1519               L1143:
7509                     ; 1506 	else if(cnt_net_drv==6)
7511  1519 b62f          	ld	a,_cnt_net_drv
7512  151b a106          	cp	a,#6
7513  151d 2641          	jrne	L5043
7514                     ; 1508 		plazma_int[2]=pwm_u;
7516  151f be0b          	ldw	x,_pwm_u
7517  1521 bf34          	ldw	_plazma_int+4,x
7518                     ; 1509 		can_transmit(0x18e,adress,PUTTM1,*(((char*)&I)+1),*((char*)&I),*(((char*)&Un)+1),*((char*)&Un),*(((char*)&Ui)+1),*((char*)&Ui));
7520  1523 3b0067        	push	_Ui
7521  1526 3b0068        	push	_Ui+1
7522  1529 3b0069        	push	_Un
7523  152c 3b006a        	push	_Un+1
7524  152f 3b006b        	push	_I
7525  1532 3b006c        	push	_I+1
7526  1535 4bda          	push	#218
7527  1537 3b0001        	push	_adress
7528  153a ae018e        	ldw	x,#398
7529  153d cd13c5        	call	_can_transmit
7531  1540 5b08          	addw	sp,#8
7532                     ; 1510 		can_transmit(0x18e,adress,PUTTM2,T,0,flags,_x_,*(((char*)&plazma_int[2])+1),*((char*)&plazma_int[2]));
7534  1542 3b0034        	push	_plazma_int+4
7535  1545 3b0035        	push	_plazma_int+5
7536  1548 3b005c        	push	__x_+1
7537  154b 3b000a        	push	_flags
7538  154e 4b00          	push	#0
7539  1550 3b0064        	push	_T
7540  1553 4bdb          	push	#219
7541  1555 3b0001        	push	_adress
7542  1558 ae018e        	ldw	x,#398
7543  155b cd13c5        	call	_can_transmit
7545  155e 5b08          	addw	sp,#8
7546  1560               L5043:
7547                     ; 1513 }
7550  1560 81            	ret
7660                     ; 1516 void can_in_an(void)
7660                     ; 1517 {
7661                     	switch	.text
7662  1561               _can_in_an:
7664  1561 5205          	subw	sp,#5
7665       00000005      OFST:	set	5
7668                     ; 1527 if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==GETTM))	
7670  1563 b6c6          	ld	a,_mess+6
7671  1565 c10001        	cp	a,_adress
7672  1568 2703          	jreq	L471
7673  156a cc1677        	jp	L5543
7674  156d               L471:
7676  156d b6c7          	ld	a,_mess+7
7677  156f c10001        	cp	a,_adress
7678  1572 2703          	jreq	L671
7679  1574 cc1677        	jp	L5543
7680  1577               L671:
7682  1577 b6c8          	ld	a,_mess+8
7683  1579 a1ed          	cp	a,#237
7684  157b 2703          	jreq	L002
7685  157d cc1677        	jp	L5543
7686  1580               L002:
7687                     ; 1530 	can_error_cnt=0;
7689  1580 3f6d          	clr	_can_error_cnt
7690                     ; 1532 	bMAIN=0;
7692  1582 72110001      	bres	_bMAIN
7693                     ; 1533  	flags_tu=mess[9];
7695  1586 45c95d        	mov	_flags_tu,_mess+9
7696                     ; 1534  	if(flags_tu&0b00000001)
7698  1589 b65d          	ld	a,_flags_tu
7699  158b a501          	bcp	a,#1
7700  158d 2706          	jreq	L7543
7701                     ; 1539  			/*if(flags_tu_cnt_off>=4)*/flags|=0b00100000;
7703  158f 721a000a      	bset	_flags,#5
7705  1593 200e          	jra	L1643
7706  1595               L7543:
7707                     ; 1550  				flags&=0b11011111; 
7709  1595 721b000a      	bres	_flags,#5
7710                     ; 1551  				off_bp_cnt=5*ee_TZAS;
7712  1599 c60015        	ld	a,_ee_TZAS+1
7713  159c 97            	ld	xl,a
7714  159d a605          	ld	a,#5
7715  159f 42            	mul	x,a
7716  15a0 9f            	ld	a,xl
7717  15a1 b750          	ld	_off_bp_cnt,a
7718  15a3               L1643:
7719                     ; 1557  	if(flags_tu&0b00000010) flags|=0b01000000;
7721  15a3 b65d          	ld	a,_flags_tu
7722  15a5 a502          	bcp	a,#2
7723  15a7 2706          	jreq	L3643
7726  15a9 721c000a      	bset	_flags,#6
7728  15ad 2004          	jra	L5643
7729  15af               L3643:
7730                     ; 1558  	else flags&=0b10111111; 
7732  15af 721d000a      	bres	_flags,#6
7733  15b3               L5643:
7734                     ; 1560  	vol_u_temp=mess[10]+mess[11]*256;
7736  15b3 b6cb          	ld	a,_mess+11
7737  15b5 5f            	clrw	x
7738  15b6 97            	ld	xl,a
7739  15b7 4f            	clr	a
7740  15b8 02            	rlwa	x,a
7741  15b9 01            	rrwa	x,a
7742  15ba bbca          	add	a,_mess+10
7743  15bc 2401          	jrnc	L451
7744  15be 5c            	incw	x
7745  15bf               L451:
7746  15bf b756          	ld	_vol_u_temp+1,a
7747  15c1 9f            	ld	a,xl
7748  15c2 b755          	ld	_vol_u_temp,a
7749                     ; 1561  	vol_i_temp=mess[12]+mess[13]*256;  
7751  15c4 b6cd          	ld	a,_mess+13
7752  15c6 5f            	clrw	x
7753  15c7 97            	ld	xl,a
7754  15c8 4f            	clr	a
7755  15c9 02            	rlwa	x,a
7756  15ca 01            	rrwa	x,a
7757  15cb bbcc          	add	a,_mess+12
7758  15cd 2401          	jrnc	L651
7759  15cf 5c            	incw	x
7760  15d0               L651:
7761  15d0 b754          	ld	_vol_i_temp+1,a
7762  15d2 9f            	ld	a,xl
7763  15d3 b753          	ld	_vol_i_temp,a
7764                     ; 1570 	plazma_int[2]=T;
7766  15d5 5f            	clrw	x
7767  15d6 b664          	ld	a,_T
7768  15d8 2a01          	jrpl	L061
7769  15da 53            	cplw	x
7770  15db               L061:
7771  15db 97            	ld	xl,a
7772  15dc bf34          	ldw	_plazma_int+4,x
7773                     ; 1571  	rotor_int=flags_tu+(((short)flags)<<8);
7775  15de b60a          	ld	a,_flags
7776  15e0 5f            	clrw	x
7777  15e1 97            	ld	xl,a
7778  15e2 4f            	clr	a
7779  15e3 02            	rlwa	x,a
7780  15e4 01            	rrwa	x,a
7781  15e5 bb5d          	add	a,_flags_tu
7782  15e7 2401          	jrnc	L261
7783  15e9 5c            	incw	x
7784  15ea               L261:
7785  15ea b71b          	ld	_rotor_int+1,a
7786  15ec 9f            	ld	a,xl
7787  15ed b71a          	ld	_rotor_int,a
7788                     ; 1572 	can_transmit(0x18e,adress,PUTTM1,*(((char*)&I)+1),*((char*)&I),*(((char*)&Un)+1),*((char*)&Un),*(((char*)&Ui)+1),*((char*)&Ui));
7790  15ef 3b0067        	push	_Ui
7791  15f2 3b0068        	push	_Ui+1
7792  15f5 3b0069        	push	_Un
7793  15f8 3b006a        	push	_Un+1
7794  15fb 3b006b        	push	_I
7795  15fe 3b006c        	push	_I+1
7796  1601 4bda          	push	#218
7797  1603 3b0001        	push	_adress
7798  1606 ae018e        	ldw	x,#398
7799  1609 cd13c5        	call	_can_transmit
7801  160c 5b08          	addw	sp,#8
7802                     ; 1573 	can_transmit(0x18e,adress,PUTTM2,T,0,flags,_x_,*(((char*)&plazma_int[2])+1),*((char*)&plazma_int[2]));
7804  160e 3b0034        	push	_plazma_int+4
7805  1611 3b0035        	push	_plazma_int+5
7806  1614 3b005c        	push	__x_+1
7807  1617 3b000a        	push	_flags
7808  161a 4b00          	push	#0
7809  161c 3b0064        	push	_T
7810  161f 4bdb          	push	#219
7811  1621 3b0001        	push	_adress
7812  1624 ae018e        	ldw	x,#398
7813  1627 cd13c5        	call	_can_transmit
7815  162a 5b08          	addw	sp,#8
7816                     ; 1574      link_cnt=0;
7818  162c 3f5e          	clr	_link_cnt
7819                     ; 1575      link=ON;
7821  162e 3555005f      	mov	_link,#85
7822                     ; 1577      if(flags_tu&0b10000000)
7824  1632 b65d          	ld	a,_flags_tu
7825  1634 a580          	bcp	a,#128
7826  1636 2716          	jreq	L7643
7827                     ; 1579      	if(!res_fl)
7829  1638 725d0009      	tnz	_res_fl
7830  163c 2625          	jrne	L3743
7831                     ; 1581      		res_fl=1;
7833  163e a601          	ld	a,#1
7834  1640 ae0009        	ldw	x,#_res_fl
7835  1643 cd0000        	call	c_eewrc
7837                     ; 1582      		bRES=1;
7839  1646 3501000f      	mov	_bRES,#1
7840                     ; 1583      		res_fl_cnt=0;
7842  164a 3f3e          	clr	_res_fl_cnt
7843  164c 2015          	jra	L3743
7844  164e               L7643:
7845                     ; 1588      	if(main_cnt>20)
7847  164e 9c            	rvf
7848  164f be4e          	ldw	x,_main_cnt
7849  1651 a30015        	cpw	x,#21
7850  1654 2f0d          	jrslt	L3743
7851                     ; 1590     			if(res_fl)
7853  1656 725d0009      	tnz	_res_fl
7854  165a 2707          	jreq	L3743
7855                     ; 1592      			res_fl=0;
7857  165c 4f            	clr	a
7858  165d ae0009        	ldw	x,#_res_fl
7859  1660 cd0000        	call	c_eewrc
7861  1663               L3743:
7862                     ; 1597       if(res_fl_)
7864  1663 725d0008      	tnz	_res_fl_
7865  1667 2603          	jrne	L202
7866  1669 cc1b87        	jp	L1243
7867  166c               L202:
7868                     ; 1599       	res_fl_=0;
7870  166c 4f            	clr	a
7871  166d ae0008        	ldw	x,#_res_fl_
7872  1670 cd0000        	call	c_eewrc
7874  1673 ac871b87      	jpf	L1243
7875  1677               L5543:
7876                     ; 1602 else if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==KLBR)&&(mess[9]==mess[10]))
7878  1677 b6c6          	ld	a,_mess+6
7879  1679 c10001        	cp	a,_adress
7880  167c 2703          	jreq	L402
7881  167e cc188d        	jp	L5053
7882  1681               L402:
7884  1681 b6c7          	ld	a,_mess+7
7885  1683 c10001        	cp	a,_adress
7886  1686 2703          	jreq	L602
7887  1688 cc188d        	jp	L5053
7888  168b               L602:
7890  168b b6c8          	ld	a,_mess+8
7891  168d a1ee          	cp	a,#238
7892  168f 2703          	jreq	L012
7893  1691 cc188d        	jp	L5053
7894  1694               L012:
7896  1694 b6c9          	ld	a,_mess+9
7897  1696 b1ca          	cp	a,_mess+10
7898  1698 2703          	jreq	L212
7899  169a cc188d        	jp	L5053
7900  169d               L212:
7901                     ; 1604 	rotor_int++;
7903  169d be1a          	ldw	x,_rotor_int
7904  169f 1c0001        	addw	x,#1
7905  16a2 bf1a          	ldw	_rotor_int,x
7906                     ; 1605 	if((mess[9]&0xf0)==0x20)
7908  16a4 b6c9          	ld	a,_mess+9
7909  16a6 a4f0          	and	a,#240
7910  16a8 a120          	cp	a,#32
7911  16aa 2673          	jrne	L7053
7912                     ; 1607 		if((mess[9]&0x0f)==0x01)
7914  16ac b6c9          	ld	a,_mess+9
7915  16ae a40f          	and	a,#15
7916  16b0 a101          	cp	a,#1
7917  16b2 260d          	jrne	L1153
7918                     ; 1609 			ee_K[0][0]=adc_buff_[4];
7920  16b4 ce000d        	ldw	x,_adc_buff_+8
7921  16b7 89            	pushw	x
7922  16b8 ae0018        	ldw	x,#_ee_K
7923  16bb cd0000        	call	c_eewrw
7925  16be 85            	popw	x
7927  16bf 204a          	jra	L3153
7928  16c1               L1153:
7929                     ; 1611 		else if((mess[9]&0x0f)==0x02)
7931  16c1 b6c9          	ld	a,_mess+9
7932  16c3 a40f          	and	a,#15
7933  16c5 a102          	cp	a,#2
7934  16c7 260b          	jrne	L5153
7935                     ; 1613 			ee_K[0][1]++;
7937  16c9 ce001a        	ldw	x,_ee_K+2
7938  16cc 1c0001        	addw	x,#1
7939  16cf cf001a        	ldw	_ee_K+2,x
7941  16d2 2037          	jra	L3153
7942  16d4               L5153:
7943                     ; 1615 		else if((mess[9]&0x0f)==0x03)
7945  16d4 b6c9          	ld	a,_mess+9
7946  16d6 a40f          	and	a,#15
7947  16d8 a103          	cp	a,#3
7948  16da 260b          	jrne	L1253
7949                     ; 1617 			ee_K[0][1]+=10;
7951  16dc ce001a        	ldw	x,_ee_K+2
7952  16df 1c000a        	addw	x,#10
7953  16e2 cf001a        	ldw	_ee_K+2,x
7955  16e5 2024          	jra	L3153
7956  16e7               L1253:
7957                     ; 1619 		else if((mess[9]&0x0f)==0x04)
7959  16e7 b6c9          	ld	a,_mess+9
7960  16e9 a40f          	and	a,#15
7961  16eb a104          	cp	a,#4
7962  16ed 260b          	jrne	L5253
7963                     ; 1621 			ee_K[0][1]--;
7965  16ef ce001a        	ldw	x,_ee_K+2
7966  16f2 1d0001        	subw	x,#1
7967  16f5 cf001a        	ldw	_ee_K+2,x
7969  16f8 2011          	jra	L3153
7970  16fa               L5253:
7971                     ; 1623 		else if((mess[9]&0x0f)==0x05)
7973  16fa b6c9          	ld	a,_mess+9
7974  16fc a40f          	and	a,#15
7975  16fe a105          	cp	a,#5
7976  1700 2609          	jrne	L3153
7977                     ; 1625 			ee_K[0][1]-=10;
7979  1702 ce001a        	ldw	x,_ee_K+2
7980  1705 1d000a        	subw	x,#10
7981  1708 cf001a        	ldw	_ee_K+2,x
7982  170b               L3153:
7983                     ; 1627 		granee(&ee_K[0][1],50,3000);									
7985  170b ae0bb8        	ldw	x,#3000
7986  170e 89            	pushw	x
7987  170f ae0032        	ldw	x,#50
7988  1712 89            	pushw	x
7989  1713 ae001a        	ldw	x,#_ee_K+2
7990  1716 cd0021        	call	_granee
7992  1719 5b04          	addw	sp,#4
7994  171b ac731873      	jpf	L3353
7995  171f               L7053:
7996                     ; 1629 	else if((mess[9]&0xf0)==0x10)
7998  171f b6c9          	ld	a,_mess+9
7999  1721 a4f0          	and	a,#240
8000  1723 a110          	cp	a,#16
8001  1725 2673          	jrne	L5353
8002                     ; 1631 		if((mess[9]&0x0f)==0x01)
8004  1727 b6c9          	ld	a,_mess+9
8005  1729 a40f          	and	a,#15
8006  172b a101          	cp	a,#1
8007  172d 260d          	jrne	L7353
8008                     ; 1633 			ee_K[1][0]=adc_buff_[1];
8010  172f ce0007        	ldw	x,_adc_buff_+2
8011  1732 89            	pushw	x
8012  1733 ae001c        	ldw	x,#_ee_K+4
8013  1736 cd0000        	call	c_eewrw
8015  1739 85            	popw	x
8017  173a 204a          	jra	L1453
8018  173c               L7353:
8019                     ; 1635 		else if((mess[9]&0x0f)==0x02)
8021  173c b6c9          	ld	a,_mess+9
8022  173e a40f          	and	a,#15
8023  1740 a102          	cp	a,#2
8024  1742 260b          	jrne	L3453
8025                     ; 1637 			ee_K[1][1]++;
8027  1744 ce001e        	ldw	x,_ee_K+6
8028  1747 1c0001        	addw	x,#1
8029  174a cf001e        	ldw	_ee_K+6,x
8031  174d 2037          	jra	L1453
8032  174f               L3453:
8033                     ; 1639 		else if((mess[9]&0x0f)==0x03)
8035  174f b6c9          	ld	a,_mess+9
8036  1751 a40f          	and	a,#15
8037  1753 a103          	cp	a,#3
8038  1755 260b          	jrne	L7453
8039                     ; 1641 			ee_K[1][1]+=10;
8041  1757 ce001e        	ldw	x,_ee_K+6
8042  175a 1c000a        	addw	x,#10
8043  175d cf001e        	ldw	_ee_K+6,x
8045  1760 2024          	jra	L1453
8046  1762               L7453:
8047                     ; 1643 		else if((mess[9]&0x0f)==0x04)
8049  1762 b6c9          	ld	a,_mess+9
8050  1764 a40f          	and	a,#15
8051  1766 a104          	cp	a,#4
8052  1768 260b          	jrne	L3553
8053                     ; 1645 			ee_K[1][1]--;
8055  176a ce001e        	ldw	x,_ee_K+6
8056  176d 1d0001        	subw	x,#1
8057  1770 cf001e        	ldw	_ee_K+6,x
8059  1773 2011          	jra	L1453
8060  1775               L3553:
8061                     ; 1647 		else if((mess[9]&0x0f)==0x05)
8063  1775 b6c9          	ld	a,_mess+9
8064  1777 a40f          	and	a,#15
8065  1779 a105          	cp	a,#5
8066  177b 2609          	jrne	L1453
8067                     ; 1649 			ee_K[1][1]-=10;
8069  177d ce001e        	ldw	x,_ee_K+6
8070  1780 1d000a        	subw	x,#10
8071  1783 cf001e        	ldw	_ee_K+6,x
8072  1786               L1453:
8073                     ; 1654 		granee(&ee_K[1][1],10,30000);
8075  1786 ae7530        	ldw	x,#30000
8076  1789 89            	pushw	x
8077  178a ae000a        	ldw	x,#10
8078  178d 89            	pushw	x
8079  178e ae001e        	ldw	x,#_ee_K+6
8080  1791 cd0021        	call	_granee
8082  1794 5b04          	addw	sp,#4
8084  1796 ac731873      	jpf	L3353
8085  179a               L5353:
8086                     ; 1658 	else if((mess[9]&0xf0)==0x00)
8088  179a b6c9          	ld	a,_mess+9
8089  179c a5f0          	bcp	a,#240
8090  179e 2671          	jrne	L3653
8091                     ; 1660 		if((mess[9]&0x0f)==0x01)
8093  17a0 b6c9          	ld	a,_mess+9
8094  17a2 a40f          	and	a,#15
8095  17a4 a101          	cp	a,#1
8096  17a6 260d          	jrne	L5653
8097                     ; 1662 			ee_K[2][0]=adc_buff_[2];
8099  17a8 ce0009        	ldw	x,_adc_buff_+4
8100  17ab 89            	pushw	x
8101  17ac ae0020        	ldw	x,#_ee_K+8
8102  17af cd0000        	call	c_eewrw
8104  17b2 85            	popw	x
8106  17b3 204a          	jra	L7653
8107  17b5               L5653:
8108                     ; 1664 		else if((mess[9]&0x0f)==0x02)
8110  17b5 b6c9          	ld	a,_mess+9
8111  17b7 a40f          	and	a,#15
8112  17b9 a102          	cp	a,#2
8113  17bb 260b          	jrne	L1753
8114                     ; 1666 			ee_K[2][1]++;
8116  17bd ce0022        	ldw	x,_ee_K+10
8117  17c0 1c0001        	addw	x,#1
8118  17c3 cf0022        	ldw	_ee_K+10,x
8120  17c6 2037          	jra	L7653
8121  17c8               L1753:
8122                     ; 1668 		else if((mess[9]&0x0f)==0x03)
8124  17c8 b6c9          	ld	a,_mess+9
8125  17ca a40f          	and	a,#15
8126  17cc a103          	cp	a,#3
8127  17ce 260b          	jrne	L5753
8128                     ; 1670 			ee_K[2][1]+=10;
8130  17d0 ce0022        	ldw	x,_ee_K+10
8131  17d3 1c000a        	addw	x,#10
8132  17d6 cf0022        	ldw	_ee_K+10,x
8134  17d9 2024          	jra	L7653
8135  17db               L5753:
8136                     ; 1672 		else if((mess[9]&0x0f)==0x04)
8138  17db b6c9          	ld	a,_mess+9
8139  17dd a40f          	and	a,#15
8140  17df a104          	cp	a,#4
8141  17e1 260b          	jrne	L1063
8142                     ; 1674 			ee_K[2][1]--;
8144  17e3 ce0022        	ldw	x,_ee_K+10
8145  17e6 1d0001        	subw	x,#1
8146  17e9 cf0022        	ldw	_ee_K+10,x
8148  17ec 2011          	jra	L7653
8149  17ee               L1063:
8150                     ; 1676 		else if((mess[9]&0x0f)==0x05)
8152  17ee b6c9          	ld	a,_mess+9
8153  17f0 a40f          	and	a,#15
8154  17f2 a105          	cp	a,#5
8155  17f4 2609          	jrne	L7653
8156                     ; 1678 			ee_K[2][1]-=10;
8158  17f6 ce0022        	ldw	x,_ee_K+10
8159  17f9 1d000a        	subw	x,#10
8160  17fc cf0022        	ldw	_ee_K+10,x
8161  17ff               L7653:
8162                     ; 1683 		granee(&ee_K[2][1],10,30000);
8164  17ff ae7530        	ldw	x,#30000
8165  1802 89            	pushw	x
8166  1803 ae000a        	ldw	x,#10
8167  1806 89            	pushw	x
8168  1807 ae0022        	ldw	x,#_ee_K+10
8169  180a cd0021        	call	_granee
8171  180d 5b04          	addw	sp,#4
8173  180f 2062          	jra	L3353
8174  1811               L3653:
8175                     ; 1687 	else if((mess[9]&0xf0)==0x30)
8177  1811 b6c9          	ld	a,_mess+9
8178  1813 a4f0          	and	a,#240
8179  1815 a130          	cp	a,#48
8180  1817 265a          	jrne	L3353
8181                     ; 1689 		if((mess[9]&0x0f)==0x02)
8183  1819 b6c9          	ld	a,_mess+9
8184  181b a40f          	and	a,#15
8185  181d a102          	cp	a,#2
8186  181f 260b          	jrne	L3163
8187                     ; 1691 			ee_K[3][1]++;
8189  1821 ce0026        	ldw	x,_ee_K+14
8190  1824 1c0001        	addw	x,#1
8191  1827 cf0026        	ldw	_ee_K+14,x
8193  182a 2037          	jra	L5163
8194  182c               L3163:
8195                     ; 1693 		else if((mess[9]&0x0f)==0x03)
8197  182c b6c9          	ld	a,_mess+9
8198  182e a40f          	and	a,#15
8199  1830 a103          	cp	a,#3
8200  1832 260b          	jrne	L7163
8201                     ; 1695 			ee_K[3][1]+=10;
8203  1834 ce0026        	ldw	x,_ee_K+14
8204  1837 1c000a        	addw	x,#10
8205  183a cf0026        	ldw	_ee_K+14,x
8207  183d 2024          	jra	L5163
8208  183f               L7163:
8209                     ; 1697 		else if((mess[9]&0x0f)==0x04)
8211  183f b6c9          	ld	a,_mess+9
8212  1841 a40f          	and	a,#15
8213  1843 a104          	cp	a,#4
8214  1845 260b          	jrne	L3263
8215                     ; 1699 			ee_K[3][1]--;
8217  1847 ce0026        	ldw	x,_ee_K+14
8218  184a 1d0001        	subw	x,#1
8219  184d cf0026        	ldw	_ee_K+14,x
8221  1850 2011          	jra	L5163
8222  1852               L3263:
8223                     ; 1701 		else if((mess[9]&0x0f)==0x05)
8225  1852 b6c9          	ld	a,_mess+9
8226  1854 a40f          	and	a,#15
8227  1856 a105          	cp	a,#5
8228  1858 2609          	jrne	L5163
8229                     ; 1703 			ee_K[3][1]-=10;
8231  185a ce0026        	ldw	x,_ee_K+14
8232  185d 1d000a        	subw	x,#10
8233  1860 cf0026        	ldw	_ee_K+14,x
8234  1863               L5163:
8235                     ; 1705 		granee(&ee_K[3][1],300,517);									
8237  1863 ae0205        	ldw	x,#517
8238  1866 89            	pushw	x
8239  1867 ae012c        	ldw	x,#300
8240  186a 89            	pushw	x
8241  186b ae0026        	ldw	x,#_ee_K+14
8242  186e cd0021        	call	_granee
8244  1871 5b04          	addw	sp,#4
8245  1873               L3353:
8246                     ; 1708 	link_cnt=0;
8248  1873 3f5e          	clr	_link_cnt
8249                     ; 1709      link=ON;
8251  1875 3555005f      	mov	_link,#85
8252                     ; 1710      if(res_fl_)
8254  1879 725d0008      	tnz	_res_fl_
8255  187d 2603          	jrne	L412
8256  187f cc1b87        	jp	L1243
8257  1882               L412:
8258                     ; 1712       	res_fl_=0;
8260  1882 4f            	clr	a
8261  1883 ae0008        	ldw	x,#_res_fl_
8262  1886 cd0000        	call	c_eewrc
8264  1889 ac871b87      	jpf	L1243
8265  188d               L5053:
8266                     ; 1718 else if((mess[6]==0xff)&&(mess[7]==0xff)&&(mess[8]==MEM_KF))
8268  188d b6c6          	ld	a,_mess+6
8269  188f a1ff          	cp	a,#255
8270  1891 2703          	jreq	L612
8271  1893 cc1921        	jp	L5363
8272  1896               L612:
8274  1896 b6c7          	ld	a,_mess+7
8275  1898 a1ff          	cp	a,#255
8276  189a 2703          	jreq	L022
8277  189c cc1921        	jp	L5363
8278  189f               L022:
8280  189f b6c8          	ld	a,_mess+8
8281  18a1 a162          	cp	a,#98
8282  18a3 267c          	jrne	L5363
8283                     ; 1721 	tempSS=mess[9]+(mess[10]*256);
8285  18a5 b6ca          	ld	a,_mess+10
8286  18a7 5f            	clrw	x
8287  18a8 97            	ld	xl,a
8288  18a9 4f            	clr	a
8289  18aa 02            	rlwa	x,a
8290  18ab 01            	rrwa	x,a
8291  18ac bbc9          	add	a,_mess+9
8292  18ae 2401          	jrnc	L461
8293  18b0 5c            	incw	x
8294  18b1               L461:
8295  18b1 02            	rlwa	x,a
8296  18b2 1f04          	ldw	(OFST-1,sp),x
8297  18b4 01            	rrwa	x,a
8298                     ; 1722 	if(ee_Umax!=tempSS) ee_Umax=tempSS;
8300  18b5 ce0012        	ldw	x,_ee_Umax
8301  18b8 1304          	cpw	x,(OFST-1,sp)
8302  18ba 270a          	jreq	L7363
8305  18bc 1e04          	ldw	x,(OFST-1,sp)
8306  18be 89            	pushw	x
8307  18bf ae0012        	ldw	x,#_ee_Umax
8308  18c2 cd0000        	call	c_eewrw
8310  18c5 85            	popw	x
8311  18c6               L7363:
8312                     ; 1723 	tempSS=mess[11]+(mess[12]*256);
8314  18c6 b6cc          	ld	a,_mess+12
8315  18c8 5f            	clrw	x
8316  18c9 97            	ld	xl,a
8317  18ca 4f            	clr	a
8318  18cb 02            	rlwa	x,a
8319  18cc 01            	rrwa	x,a
8320  18cd bbcb          	add	a,_mess+11
8321  18cf 2401          	jrnc	L661
8322  18d1 5c            	incw	x
8323  18d2               L661:
8324  18d2 02            	rlwa	x,a
8325  18d3 1f04          	ldw	(OFST-1,sp),x
8326  18d5 01            	rrwa	x,a
8327                     ; 1724 	if(ee_dU!=tempSS) ee_dU=tempSS;
8329  18d6 ce0010        	ldw	x,_ee_dU
8330  18d9 1304          	cpw	x,(OFST-1,sp)
8331  18db 270a          	jreq	L1463
8334  18dd 1e04          	ldw	x,(OFST-1,sp)
8335  18df 89            	pushw	x
8336  18e0 ae0010        	ldw	x,#_ee_dU
8337  18e3 cd0000        	call	c_eewrw
8339  18e6 85            	popw	x
8340  18e7               L1463:
8341                     ; 1725 	if((mess[13]&0x0f)==0x5)
8343  18e7 b6cd          	ld	a,_mess+13
8344  18e9 a40f          	and	a,#15
8345  18eb a105          	cp	a,#5
8346  18ed 261a          	jrne	L3463
8347                     ; 1727 		if(ee_AVT_MODE!=0x55)ee_AVT_MODE=0x55;
8349  18ef ce0004        	ldw	x,_ee_AVT_MODE
8350  18f2 a30055        	cpw	x,#85
8351  18f5 2603          	jrne	L222
8352  18f7 cc1b87        	jp	L1243
8353  18fa               L222:
8356  18fa ae0055        	ldw	x,#85
8357  18fd 89            	pushw	x
8358  18fe ae0004        	ldw	x,#_ee_AVT_MODE
8359  1901 cd0000        	call	c_eewrw
8361  1904 85            	popw	x
8362  1905 ac871b87      	jpf	L1243
8363  1909               L3463:
8364                     ; 1729 	else if(ee_AVT_MODE==0x55)ee_AVT_MODE=0;	
8366  1909 ce0004        	ldw	x,_ee_AVT_MODE
8367  190c a30055        	cpw	x,#85
8368  190f 2703          	jreq	L422
8369  1911 cc1b87        	jp	L1243
8370  1914               L422:
8373  1914 5f            	clrw	x
8374  1915 89            	pushw	x
8375  1916 ae0004        	ldw	x,#_ee_AVT_MODE
8376  1919 cd0000        	call	c_eewrw
8378  191c 85            	popw	x
8379  191d ac871b87      	jpf	L1243
8380  1921               L5363:
8381                     ; 1732 else if((mess[6]==0xff)&&(mess[7]==0xff)&&((mess[8]==MEM_KF1)||(mess[8]==MEM_KF4)))
8383  1921 b6c6          	ld	a,_mess+6
8384  1923 a1ff          	cp	a,#255
8385  1925 2703          	jreq	L622
8386  1927 cc19e5        	jp	L5563
8387  192a               L622:
8389  192a b6c7          	ld	a,_mess+7
8390  192c a1ff          	cp	a,#255
8391  192e 2703          	jreq	L032
8392  1930 cc19e5        	jp	L5563
8393  1933               L032:
8395  1933 b6c8          	ld	a,_mess+8
8396  1935 a126          	cp	a,#38
8397  1937 2709          	jreq	L7563
8399  1939 b6c8          	ld	a,_mess+8
8400  193b a129          	cp	a,#41
8401  193d 2703          	jreq	L232
8402  193f cc19e5        	jp	L5563
8403  1942               L232:
8404  1942               L7563:
8405                     ; 1735 	tempSS=mess[9]+(mess[10]*256);
8407  1942 b6ca          	ld	a,_mess+10
8408  1944 5f            	clrw	x
8409  1945 97            	ld	xl,a
8410  1946 4f            	clr	a
8411  1947 02            	rlwa	x,a
8412  1948 01            	rrwa	x,a
8413  1949 bbc9          	add	a,_mess+9
8414  194b 2401          	jrnc	L071
8415  194d 5c            	incw	x
8416  194e               L071:
8417  194e 02            	rlwa	x,a
8418  194f 1f04          	ldw	(OFST-1,sp),x
8419  1951 01            	rrwa	x,a
8420                     ; 1736 	if(ee_tmax!=tempSS) ee_tmax=tempSS;
8422  1952 ce000e        	ldw	x,_ee_tmax
8423  1955 1304          	cpw	x,(OFST-1,sp)
8424  1957 270a          	jreq	L1663
8427  1959 1e04          	ldw	x,(OFST-1,sp)
8428  195b 89            	pushw	x
8429  195c ae000e        	ldw	x,#_ee_tmax
8430  195f cd0000        	call	c_eewrw
8432  1962 85            	popw	x
8433  1963               L1663:
8434                     ; 1737 	tempSS=mess[11]+(mess[12]*256);
8436  1963 b6cc          	ld	a,_mess+12
8437  1965 5f            	clrw	x
8438  1966 97            	ld	xl,a
8439  1967 4f            	clr	a
8440  1968 02            	rlwa	x,a
8441  1969 01            	rrwa	x,a
8442  196a bbcb          	add	a,_mess+11
8443  196c 2401          	jrnc	L271
8444  196e 5c            	incw	x
8445  196f               L271:
8446  196f 02            	rlwa	x,a
8447  1970 1f04          	ldw	(OFST-1,sp),x
8448  1972 01            	rrwa	x,a
8449                     ; 1738 	if(ee_tsign!=tempSS) ee_tsign=tempSS;
8451  1973 ce000c        	ldw	x,_ee_tsign
8452  1976 1304          	cpw	x,(OFST-1,sp)
8453  1978 270a          	jreq	L3663
8456  197a 1e04          	ldw	x,(OFST-1,sp)
8457  197c 89            	pushw	x
8458  197d ae000c        	ldw	x,#_ee_tsign
8459  1980 cd0000        	call	c_eewrw
8461  1983 85            	popw	x
8462  1984               L3663:
8463                     ; 1741 	if(mess[8]==MEM_KF1)
8465  1984 b6c8          	ld	a,_mess+8
8466  1986 a126          	cp	a,#38
8467  1988 2623          	jrne	L5663
8468                     ; 1743 		if(ee_DEVICE!=0)ee_DEVICE=0;
8470  198a ce0002        	ldw	x,_ee_DEVICE
8471  198d 2709          	jreq	L7663
8474  198f 5f            	clrw	x
8475  1990 89            	pushw	x
8476  1991 ae0002        	ldw	x,#_ee_DEVICE
8477  1994 cd0000        	call	c_eewrw
8479  1997 85            	popw	x
8480  1998               L7663:
8481                     ; 1744 		if(ee_TZAS!=(signed short)mess[13]) ee_TZAS=(signed short)mess[13];
8483  1998 b6cd          	ld	a,_mess+13
8484  199a 5f            	clrw	x
8485  199b 97            	ld	xl,a
8486  199c c30014        	cpw	x,_ee_TZAS
8487  199f 270c          	jreq	L5663
8490  19a1 b6cd          	ld	a,_mess+13
8491  19a3 5f            	clrw	x
8492  19a4 97            	ld	xl,a
8493  19a5 89            	pushw	x
8494  19a6 ae0014        	ldw	x,#_ee_TZAS
8495  19a9 cd0000        	call	c_eewrw
8497  19ac 85            	popw	x
8498  19ad               L5663:
8499                     ; 1746 	if(mess[8]==MEM_KF4)	//MEM_KF4 передают УКУшки там, где нужно полное управление БПСами с УКУ, включить-выключить, короче не для ИБЭП
8501  19ad b6c8          	ld	a,_mess+8
8502  19af a129          	cp	a,#41
8503  19b1 2703          	jreq	L432
8504  19b3 cc1b87        	jp	L1243
8505  19b6               L432:
8506                     ; 1748 		if(ee_DEVICE!=1)ee_DEVICE=1;
8508  19b6 ce0002        	ldw	x,_ee_DEVICE
8509  19b9 a30001        	cpw	x,#1
8510  19bc 270b          	jreq	L5763
8513  19be ae0001        	ldw	x,#1
8514  19c1 89            	pushw	x
8515  19c2 ae0002        	ldw	x,#_ee_DEVICE
8516  19c5 cd0000        	call	c_eewrw
8518  19c8 85            	popw	x
8519  19c9               L5763:
8520                     ; 1749 		if(ee_IMAXVENT!=(signed short)mess[13]) ee_IMAXVENT=(signed short)mess[13];
8522  19c9 b6cd          	ld	a,_mess+13
8523  19cb 5f            	clrw	x
8524  19cc 97            	ld	xl,a
8525  19cd c30000        	cpw	x,_ee_IMAXVENT
8526  19d0 2603          	jrne	L632
8527  19d2 cc1b87        	jp	L1243
8528  19d5               L632:
8531  19d5 b6cd          	ld	a,_mess+13
8532  19d7 5f            	clrw	x
8533  19d8 97            	ld	xl,a
8534  19d9 89            	pushw	x
8535  19da ae0000        	ldw	x,#_ee_IMAXVENT
8536  19dd cd0000        	call	c_eewrw
8538  19e0 85            	popw	x
8539  19e1 ac871b87      	jpf	L1243
8540  19e5               L5563:
8541                     ; 1753 else if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==CMND)&&(mess[9]==ALRM_RES))
8543  19e5 b6c6          	ld	a,_mess+6
8544  19e7 c10001        	cp	a,_adress
8545  19ea 262d          	jrne	L3073
8547  19ec b6c7          	ld	a,_mess+7
8548  19ee c10001        	cp	a,_adress
8549  19f1 2626          	jrne	L3073
8551  19f3 b6c8          	ld	a,_mess+8
8552  19f5 a116          	cp	a,#22
8553  19f7 2620          	jrne	L3073
8555  19f9 b6c9          	ld	a,_mess+9
8556  19fb a163          	cp	a,#99
8557  19fd 261a          	jrne	L3073
8558                     ; 1755 	flags&=0b11100001;
8560  19ff b60a          	ld	a,_flags
8561  1a01 a4e1          	and	a,#225
8562  1a03 b70a          	ld	_flags,a
8563                     ; 1756 	tsign_cnt=0;
8565  1a05 5f            	clrw	x
8566  1a06 bf4a          	ldw	_tsign_cnt,x
8567                     ; 1757 	tmax_cnt=0;
8569  1a08 5f            	clrw	x
8570  1a09 bf48          	ldw	_tmax_cnt,x
8571                     ; 1758 	umax_cnt=0;
8573  1a0b 5f            	clrw	x
8574  1a0c bf62          	ldw	_umax_cnt,x
8575                     ; 1759 	umin_cnt=0;
8577  1a0e 5f            	clrw	x
8578  1a0f bf60          	ldw	_umin_cnt,x
8579                     ; 1760 	led_drv_cnt=30;
8581  1a11 351e0019      	mov	_led_drv_cnt,#30
8583  1a15 ac871b87      	jpf	L1243
8584  1a19               L3073:
8585                     ; 1762 else if((mess[6]==0xff)&&(mess[7]==0xff)&&(mess[8]==CMND)&&(mess[9]==CMND))
8587  1a19 b6c6          	ld	a,_mess+6
8588  1a1b a1ff          	cp	a,#255
8589  1a1d 265f          	jrne	L7073
8591  1a1f b6c7          	ld	a,_mess+7
8592  1a21 a1ff          	cp	a,#255
8593  1a23 2659          	jrne	L7073
8595  1a25 b6c8          	ld	a,_mess+8
8596  1a27 a116          	cp	a,#22
8597  1a29 2653          	jrne	L7073
8599  1a2b b6c9          	ld	a,_mess+9
8600  1a2d a116          	cp	a,#22
8601  1a2f 264d          	jrne	L7073
8602                     ; 1764 	if((mess[10]==0x55)&&(mess[11]==0x55)) _x_++;
8604  1a31 b6ca          	ld	a,_mess+10
8605  1a33 a155          	cp	a,#85
8606  1a35 260f          	jrne	L1173
8608  1a37 b6cb          	ld	a,_mess+11
8609  1a39 a155          	cp	a,#85
8610  1a3b 2609          	jrne	L1173
8613  1a3d be5b          	ldw	x,__x_
8614  1a3f 1c0001        	addw	x,#1
8615  1a42 bf5b          	ldw	__x_,x
8617  1a44 2024          	jra	L3173
8618  1a46               L1173:
8619                     ; 1765 	else if((mess[10]==0x66)&&(mess[11]==0x66)) _x_--; 
8621  1a46 b6ca          	ld	a,_mess+10
8622  1a48 a166          	cp	a,#102
8623  1a4a 260f          	jrne	L5173
8625  1a4c b6cb          	ld	a,_mess+11
8626  1a4e a166          	cp	a,#102
8627  1a50 2609          	jrne	L5173
8630  1a52 be5b          	ldw	x,__x_
8631  1a54 1d0001        	subw	x,#1
8632  1a57 bf5b          	ldw	__x_,x
8634  1a59 200f          	jra	L3173
8635  1a5b               L5173:
8636                     ; 1766 	else if((mess[10]==0x77)&&(mess[11]==0x77)) _x_=0;
8638  1a5b b6ca          	ld	a,_mess+10
8639  1a5d a177          	cp	a,#119
8640  1a5f 2609          	jrne	L3173
8642  1a61 b6cb          	ld	a,_mess+11
8643  1a63 a177          	cp	a,#119
8644  1a65 2603          	jrne	L3173
8647  1a67 5f            	clrw	x
8648  1a68 bf5b          	ldw	__x_,x
8649  1a6a               L3173:
8650                     ; 1767      gran(&_x_,-XMAX,XMAX);
8652  1a6a ae0019        	ldw	x,#25
8653  1a6d 89            	pushw	x
8654  1a6e aeffe7        	ldw	x,#65511
8655  1a71 89            	pushw	x
8656  1a72 ae005b        	ldw	x,#__x_
8657  1a75 cd0000        	call	_gran
8659  1a78 5b04          	addw	sp,#4
8661  1a7a ac871b87      	jpf	L1243
8662  1a7e               L7073:
8663                     ; 1769 else if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==CMND)&&(mess[9]==mess[10])&&(mess[9]==0xee))
8665  1a7e b6c6          	ld	a,_mess+6
8666  1a80 c10001        	cp	a,_adress
8667  1a83 2665          	jrne	L5273
8669  1a85 b6c7          	ld	a,_mess+7
8670  1a87 c10001        	cp	a,_adress
8671  1a8a 265e          	jrne	L5273
8673  1a8c b6c8          	ld	a,_mess+8
8674  1a8e a116          	cp	a,#22
8675  1a90 2658          	jrne	L5273
8677  1a92 b6c9          	ld	a,_mess+9
8678  1a94 b1ca          	cp	a,_mess+10
8679  1a96 2652          	jrne	L5273
8681  1a98 b6c9          	ld	a,_mess+9
8682  1a9a a1ee          	cp	a,#238
8683  1a9c 264c          	jrne	L5273
8684                     ; 1771 	rotor_int++;
8686  1a9e be1a          	ldw	x,_rotor_int
8687  1aa0 1c0001        	addw	x,#1
8688  1aa3 bf1a          	ldw	_rotor_int,x
8689                     ; 1772      tempI=pwm_u;
8691  1aa5 be0b          	ldw	x,_pwm_u
8692  1aa7 1f04          	ldw	(OFST-1,sp),x
8693                     ; 1773 	ee_U_AVT=tempI;
8695  1aa9 1e04          	ldw	x,(OFST-1,sp)
8696  1aab 89            	pushw	x
8697  1aac ae000a        	ldw	x,#_ee_U_AVT
8698  1aaf cd0000        	call	c_eewrw
8700  1ab2 85            	popw	x
8701                     ; 1774 	UU_AVT=Un;
8703  1ab3 be69          	ldw	x,_Un
8704  1ab5 89            	pushw	x
8705  1ab6 ae0006        	ldw	x,#_UU_AVT
8706  1ab9 cd0000        	call	c_eewrw
8708  1abc 85            	popw	x
8709                     ; 1775 	delay_ms(100);
8711  1abd ae0064        	ldw	x,#100
8712  1ac0 cd004c        	call	_delay_ms
8714                     ; 1776 	if(ee_U_AVT==tempI)can_transmit(0x18e,adress,PUTID,0xdd,0xdd,0,0,0,0);
8716  1ac3 ce000a        	ldw	x,_ee_U_AVT
8717  1ac6 1304          	cpw	x,(OFST-1,sp)
8718  1ac8 2703          	jreq	L042
8719  1aca cc1b87        	jp	L1243
8720  1acd               L042:
8723  1acd 4b00          	push	#0
8724  1acf 4b00          	push	#0
8725  1ad1 4b00          	push	#0
8726  1ad3 4b00          	push	#0
8727  1ad5 4bdd          	push	#221
8728  1ad7 4bdd          	push	#221
8729  1ad9 4b91          	push	#145
8730  1adb 3b0001        	push	_adress
8731  1ade ae018e        	ldw	x,#398
8732  1ae1 cd13c5        	call	_can_transmit
8734  1ae4 5b08          	addw	sp,#8
8735  1ae6 ac871b87      	jpf	L1243
8736  1aea               L5273:
8737                     ; 1781 else if((mess[7]==PUTTM1)&&(mess[6]!=adress)&&(mess[6]>=0)&&(mess[6]<=5))
8739  1aea b6c7          	ld	a,_mess+7
8740  1aec a1da          	cp	a,#218
8741  1aee 2652          	jrne	L3373
8743  1af0 b6c6          	ld	a,_mess+6
8744  1af2 c10001        	cp	a,_adress
8745  1af5 274b          	jreq	L3373
8747  1af7 b6c6          	ld	a,_mess+6
8748  1af9 a106          	cp	a,#6
8749  1afb 2445          	jruge	L3373
8750                     ; 1783 	i_main_bps_cnt[mess[6]]=0;
8752  1afd b6c6          	ld	a,_mess+6
8753  1aff 5f            	clrw	x
8754  1b00 97            	ld	xl,a
8755  1b01 6f06          	clr	(_i_main_bps_cnt,x)
8756                     ; 1784 	i_main_flag[mess[6]]=1;
8758  1b03 b6c6          	ld	a,_mess+6
8759  1b05 5f            	clrw	x
8760  1b06 97            	ld	xl,a
8761  1b07 a601          	ld	a,#1
8762  1b09 e711          	ld	(_i_main_flag,x),a
8763                     ; 1785 	if(bMAIN)
8765                     	btst	_bMAIN
8766  1b10 2475          	jruge	L1243
8767                     ; 1787 		i_main[mess[6]]=(signed short)mess[8]+(((signed short)mess[9])*256);
8769  1b12 b6c9          	ld	a,_mess+9
8770  1b14 5f            	clrw	x
8771  1b15 97            	ld	xl,a
8772  1b16 4f            	clr	a
8773  1b17 02            	rlwa	x,a
8774  1b18 1f01          	ldw	(OFST-4,sp),x
8775  1b1a b6c8          	ld	a,_mess+8
8776  1b1c 5f            	clrw	x
8777  1b1d 97            	ld	xl,a
8778  1b1e 72fb01        	addw	x,(OFST-4,sp)
8779  1b21 b6c6          	ld	a,_mess+6
8780  1b23 905f          	clrw	y
8781  1b25 9097          	ld	yl,a
8782  1b27 9058          	sllw	y
8783  1b29 90ef17        	ldw	(_i_main,y),x
8784                     ; 1788 		i_main[adress]=I;
8786  1b2c c60001        	ld	a,_adress
8787  1b2f 5f            	clrw	x
8788  1b30 97            	ld	xl,a
8789  1b31 58            	sllw	x
8790  1b32 90be6b        	ldw	y,_I
8791  1b35 ef17          	ldw	(_i_main,x),y
8792                     ; 1789      	i_main_flag[adress]=1;
8794  1b37 c60001        	ld	a,_adress
8795  1b3a 5f            	clrw	x
8796  1b3b 97            	ld	xl,a
8797  1b3c a601          	ld	a,#1
8798  1b3e e711          	ld	(_i_main_flag,x),a
8799  1b40 2045          	jra	L1243
8800  1b42               L3373:
8801                     ; 1793 else if((mess[7]==PUTTM2)&&(mess[6]!=adress)&&(mess[6]>=0)&&(mess[6]<=5))
8803  1b42 b6c7          	ld	a,_mess+7
8804  1b44 a1db          	cp	a,#219
8805  1b46 263f          	jrne	L1243
8807  1b48 b6c6          	ld	a,_mess+6
8808  1b4a c10001        	cp	a,_adress
8809  1b4d 2738          	jreq	L1243
8811  1b4f b6c6          	ld	a,_mess+6
8812  1b51 a106          	cp	a,#6
8813  1b53 2432          	jruge	L1243
8814                     ; 1795 	i_main_bps_cnt[mess[6]]=0;
8816  1b55 b6c6          	ld	a,_mess+6
8817  1b57 5f            	clrw	x
8818  1b58 97            	ld	xl,a
8819  1b59 6f06          	clr	(_i_main_bps_cnt,x)
8820                     ; 1796 	i_main_flag[mess[6]]=1;		
8822  1b5b b6c6          	ld	a,_mess+6
8823  1b5d 5f            	clrw	x
8824  1b5e 97            	ld	xl,a
8825  1b5f a601          	ld	a,#1
8826  1b61 e711          	ld	(_i_main_flag,x),a
8827                     ; 1797 	if(bMAIN)
8829                     	btst	_bMAIN
8830  1b68 241d          	jruge	L1243
8831                     ; 1799 		if(mess[9]==0)i_main_flag[i]=1;
8833  1b6a 3dc9          	tnz	_mess+9
8834  1b6c 260a          	jrne	L5473
8837  1b6e 7b03          	ld	a,(OFST-2,sp)
8838  1b70 5f            	clrw	x
8839  1b71 97            	ld	xl,a
8840  1b72 a601          	ld	a,#1
8841  1b74 e711          	ld	(_i_main_flag,x),a
8843  1b76 2006          	jra	L7473
8844  1b78               L5473:
8845                     ; 1800 		else i_main_flag[i]=0;
8847  1b78 7b03          	ld	a,(OFST-2,sp)
8848  1b7a 5f            	clrw	x
8849  1b7b 97            	ld	xl,a
8850  1b7c 6f11          	clr	(_i_main_flag,x)
8851  1b7e               L7473:
8852                     ; 1801 		i_main_flag[adress]=1;
8854  1b7e c60001        	ld	a,_adress
8855  1b81 5f            	clrw	x
8856  1b82 97            	ld	xl,a
8857  1b83 a601          	ld	a,#1
8858  1b85 e711          	ld	(_i_main_flag,x),a
8859  1b87               L1243:
8860                     ; 1807 can_in_an_end:
8860                     ; 1808 bCAN_RX=0;
8862  1b87 3f09          	clr	_bCAN_RX
8863                     ; 1809 }   
8866  1b89 5b05          	addw	sp,#5
8867  1b8b 81            	ret
8890                     ; 1812 void t4_init(void){
8891                     	switch	.text
8892  1b8c               _t4_init:
8896                     ; 1813 	TIM4->PSCR = 4;
8898  1b8c 35045345      	mov	21317,#4
8899                     ; 1814 	TIM4->ARR= 77;
8901  1b90 354d5346      	mov	21318,#77
8902                     ; 1815 	TIM4->IER|= TIM4_IER_UIE;					// enable break interrupt
8904  1b94 72105341      	bset	21313,#0
8905                     ; 1817 	TIM4->CR1=(TIM4_CR1_URS | TIM4_CR1_CEN | TIM4_CR1_ARPE);	
8907  1b98 35855340      	mov	21312,#133
8908                     ; 1819 }
8911  1b9c 81            	ret
8934                     ; 1822 void t1_init(void)
8934                     ; 1823 {
8935                     	switch	.text
8936  1b9d               _t1_init:
8940                     ; 1824 TIM1->ARRH= 0x03;
8942  1b9d 35035262      	mov	21090,#3
8943                     ; 1825 TIM1->ARRL= 0xff;
8945  1ba1 35ff5263      	mov	21091,#255
8946                     ; 1826 TIM1->CCR1H= 0x00;	
8948  1ba5 725f5265      	clr	21093
8949                     ; 1827 TIM1->CCR1L= 0xff;
8951  1ba9 35ff5266      	mov	21094,#255
8952                     ; 1828 TIM1->CCR2H= 0x00;	
8954  1bad 725f5267      	clr	21095
8955                     ; 1829 TIM1->CCR2L= 0x00;
8957  1bb1 725f5268      	clr	21096
8958                     ; 1830 TIM1->CCR3H= 0x00;	
8960  1bb5 725f5269      	clr	21097
8961                     ; 1831 TIM1->CCR3L= 0x64;
8963  1bb9 3564526a      	mov	21098,#100
8964                     ; 1833 TIM1->CCMR1= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
8966  1bbd 35685258      	mov	21080,#104
8967                     ; 1834 TIM1->CCMR2= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
8969  1bc1 35685259      	mov	21081,#104
8970                     ; 1835 TIM1->CCMR3= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
8972  1bc5 3568525a      	mov	21082,#104
8973                     ; 1836 TIM1->CCER1= TIM1_CCER1_CC1E | TIM1_CCER1_CC2E ; //OC1, OC2 output pins enabled
8975  1bc9 3511525c      	mov	21084,#17
8976                     ; 1837 TIM1->CCER2= TIM1_CCER2_CC3E; //OC1, OC2 output pins enabled
8978  1bcd 3501525d      	mov	21085,#1
8979                     ; 1838 TIM1->CR1=(TIM1_CR1_CEN | TIM1_CR1_ARPE);
8981  1bd1 35815250      	mov	21072,#129
8982                     ; 1839 TIM1->BKR|= TIM1_BKR_AOE;
8984  1bd5 721c526d      	bset	21101,#6
8985                     ; 1840 }
8988  1bd9 81            	ret
9013                     ; 1844 void adc2_init(void)
9013                     ; 1845 {
9014                     	switch	.text
9015  1bda               _adc2_init:
9019                     ; 1846 adc_plazma[0]++;
9021  1bda beb2          	ldw	x,_adc_plazma
9022  1bdc 1c0001        	addw	x,#1
9023  1bdf bfb2          	ldw	_adc_plazma,x
9024                     ; 1870 GPIOB->DDR&=~(1<<4);
9026  1be1 72195007      	bres	20487,#4
9027                     ; 1871 GPIOB->CR1&=~(1<<4);
9029  1be5 72195008      	bres	20488,#4
9030                     ; 1872 GPIOB->CR2&=~(1<<4);
9032  1be9 72195009      	bres	20489,#4
9033                     ; 1874 GPIOB->DDR&=~(1<<5);
9035  1bed 721b5007      	bres	20487,#5
9036                     ; 1875 GPIOB->CR1&=~(1<<5);
9038  1bf1 721b5008      	bres	20488,#5
9039                     ; 1876 GPIOB->CR2&=~(1<<5);
9041  1bf5 721b5009      	bres	20489,#5
9042                     ; 1878 GPIOB->DDR&=~(1<<6);
9044  1bf9 721d5007      	bres	20487,#6
9045                     ; 1879 GPIOB->CR1&=~(1<<6);
9047  1bfd 721d5008      	bres	20488,#6
9048                     ; 1880 GPIOB->CR2&=~(1<<6);
9050  1c01 721d5009      	bres	20489,#6
9051                     ; 1882 GPIOB->DDR&=~(1<<7);
9053  1c05 721f5007      	bres	20487,#7
9054                     ; 1883 GPIOB->CR1&=~(1<<7);
9056  1c09 721f5008      	bres	20488,#7
9057                     ; 1884 GPIOB->CR2&=~(1<<7);
9059  1c0d 721f5009      	bres	20489,#7
9060                     ; 1894 ADC2->TDRL=0xff;
9062  1c11 35ff5407      	mov	21511,#255
9063                     ; 1896 ADC2->CR2=0x08;
9065  1c15 35085402      	mov	21506,#8
9066                     ; 1897 ADC2->CR1=0x40;
9068  1c19 35405401      	mov	21505,#64
9069                     ; 1900 	ADC2->CSR=0x20+adc_ch+3;
9071  1c1d b6bf          	ld	a,_adc_ch
9072  1c1f ab23          	add	a,#35
9073  1c21 c75400        	ld	21504,a
9074                     ; 1902 	ADC2->CR1|=1;
9076  1c24 72105401      	bset	21505,#0
9077                     ; 1903 	ADC2->CR1|=1;
9079  1c28 72105401      	bset	21505,#0
9080                     ; 1906 adc_plazma[1]=adc_ch;
9082  1c2c b6bf          	ld	a,_adc_ch
9083  1c2e 5f            	clrw	x
9084  1c2f 97            	ld	xl,a
9085  1c30 bfb4          	ldw	_adc_plazma+2,x
9086                     ; 1907 }
9089  1c32 81            	ret
9123                     ; 1916 @far @interrupt void TIM4_UPD_Interrupt (void) 
9123                     ; 1917 {
9125                     	switch	.text
9126  1c33               f_TIM4_UPD_Interrupt:
9130                     ; 1918 TIM4->SR1&=~TIM4_SR1_UIF;
9132  1c33 72115342      	bres	21314,#0
9133                     ; 1920 if(++pwm_vent_cnt>=10)pwm_vent_cnt=0;
9135  1c37 3c05          	inc	_pwm_vent_cnt
9136  1c39 b605          	ld	a,_pwm_vent_cnt
9137  1c3b a10a          	cp	a,#10
9138  1c3d 2502          	jrult	L1104
9141  1c3f 3f05          	clr	_pwm_vent_cnt
9142  1c41               L1104:
9143                     ; 1921 GPIOB->ODR|=(1<<3);
9145  1c41 72165005      	bset	20485,#3
9146                     ; 1922 if(pwm_vent_cnt>=5)GPIOB->ODR&=~(1<<3);
9148  1c45 b605          	ld	a,_pwm_vent_cnt
9149  1c47 a105          	cp	a,#5
9150  1c49 2504          	jrult	L3104
9153  1c4b 72175005      	bres	20485,#3
9154  1c4f               L3104:
9155                     ; 1927 if(++t0_cnt0>=100)
9157  1c4f 9c            	rvf
9158  1c50 be00          	ldw	x,_t0_cnt0
9159  1c52 1c0001        	addw	x,#1
9160  1c55 bf00          	ldw	_t0_cnt0,x
9161  1c57 a30064        	cpw	x,#100
9162  1c5a 2f3f          	jrslt	L5104
9163                     ; 1929 	t0_cnt0=0;
9165  1c5c 5f            	clrw	x
9166  1c5d bf00          	ldw	_t0_cnt0,x
9167                     ; 1930 	b100Hz=1;
9169  1c5f 72100008      	bset	_b100Hz
9170                     ; 1932 	if(++t0_cnt1>=10)
9172  1c63 3c02          	inc	_t0_cnt1
9173  1c65 b602          	ld	a,_t0_cnt1
9174  1c67 a10a          	cp	a,#10
9175  1c69 2506          	jrult	L7104
9176                     ; 1934 		t0_cnt1=0;
9178  1c6b 3f02          	clr	_t0_cnt1
9179                     ; 1935 		b10Hz=1;
9181  1c6d 72100007      	bset	_b10Hz
9182  1c71               L7104:
9183                     ; 1938 	if(++t0_cnt2>=20)
9185  1c71 3c03          	inc	_t0_cnt2
9186  1c73 b603          	ld	a,_t0_cnt2
9187  1c75 a114          	cp	a,#20
9188  1c77 2506          	jrult	L1204
9189                     ; 1940 		t0_cnt2=0;
9191  1c79 3f03          	clr	_t0_cnt2
9192                     ; 1941 		b5Hz=1;
9194  1c7b 72100006      	bset	_b5Hz
9195  1c7f               L1204:
9196                     ; 1945 	if(++t0_cnt4>=50)
9198  1c7f 3c05          	inc	_t0_cnt4
9199  1c81 b605          	ld	a,_t0_cnt4
9200  1c83 a132          	cp	a,#50
9201  1c85 2506          	jrult	L3204
9202                     ; 1947 		t0_cnt4=0;
9204  1c87 3f05          	clr	_t0_cnt4
9205                     ; 1948 		b2Hz=1;
9207  1c89 72100005      	bset	_b2Hz
9208  1c8d               L3204:
9209                     ; 1951 	if(++t0_cnt3>=100)
9211  1c8d 3c04          	inc	_t0_cnt3
9212  1c8f b604          	ld	a,_t0_cnt3
9213  1c91 a164          	cp	a,#100
9214  1c93 2506          	jrult	L5104
9215                     ; 1953 		t0_cnt3=0;
9217  1c95 3f04          	clr	_t0_cnt3
9218                     ; 1954 		b1Hz=1;
9220  1c97 72100004      	bset	_b1Hz
9221  1c9b               L5104:
9222                     ; 1960 }
9225  1c9b 80            	iret
9250                     ; 1963 @far @interrupt void CAN_RX_Interrupt (void) 
9250                     ; 1964 {
9251                     	switch	.text
9252  1c9c               f_CAN_RX_Interrupt:
9256                     ; 1966 CAN->PSR= 7;									// page 7 - read messsage
9258  1c9c 35075427      	mov	21543,#7
9259                     ; 1968 memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
9261  1ca0 ae000e        	ldw	x,#14
9262  1ca3               L452:
9263  1ca3 d65427        	ld	a,(21543,x)
9264  1ca6 e7bf          	ld	(_mess-1,x),a
9265  1ca8 5a            	decw	x
9266  1ca9 26f8          	jrne	L452
9267                     ; 1979 bCAN_RX=1;
9269  1cab 35010009      	mov	_bCAN_RX,#1
9270                     ; 1980 CAN->RFR|=(1<<5);
9272  1caf 721a5424      	bset	21540,#5
9273                     ; 1982 }
9276  1cb3 80            	iret
9299                     ; 1985 @far @interrupt void CAN_TX_Interrupt (void) 
9299                     ; 1986 {
9300                     	switch	.text
9301  1cb4               f_CAN_TX_Interrupt:
9305                     ; 1987 if((CAN->TSR)&(1<<0))
9307  1cb4 c65422        	ld	a,21538
9308  1cb7 a501          	bcp	a,#1
9309  1cb9 2708          	jreq	L7404
9310                     ; 1989 	bTX_FREE=1;	
9312  1cbb 35010008      	mov	_bTX_FREE,#1
9313                     ; 1991 	CAN->TSR|=(1<<0);
9315  1cbf 72105422      	bset	21538,#0
9316  1cc3               L7404:
9317                     ; 1993 }
9320  1cc3 80            	iret
9378                     ; 1996 @far @interrupt void ADC2_EOC_Interrupt (void) {
9379                     	switch	.text
9380  1cc4               f_ADC2_EOC_Interrupt:
9382       00000009      OFST:	set	9
9383  1cc4 be00          	ldw	x,c_x
9384  1cc6 89            	pushw	x
9385  1cc7 be00          	ldw	x,c_y
9386  1cc9 89            	pushw	x
9387  1cca be02          	ldw	x,c_lreg+2
9388  1ccc 89            	pushw	x
9389  1ccd be00          	ldw	x,c_lreg
9390  1ccf 89            	pushw	x
9391  1cd0 5209          	subw	sp,#9
9394                     ; 2001 adc_plazma[2]++;
9396  1cd2 beb6          	ldw	x,_adc_plazma+4
9397  1cd4 1c0001        	addw	x,#1
9398  1cd7 bfb6          	ldw	_adc_plazma+4,x
9399                     ; 2008 ADC2->CSR&=~(1<<7);
9401  1cd9 721f5400      	bres	21504,#7
9402                     ; 2010 temp_adc=(((signed long)(ADC2->DRH))*256)+((signed long)(ADC2->DRL));
9404  1cdd c65405        	ld	a,21509
9405  1ce0 b703          	ld	c_lreg+3,a
9406  1ce2 3f02          	clr	c_lreg+2
9407  1ce4 3f01          	clr	c_lreg+1
9408  1ce6 3f00          	clr	c_lreg
9409  1ce8 96            	ldw	x,sp
9410  1ce9 1c0001        	addw	x,#OFST-8
9411  1cec cd0000        	call	c_rtol
9413  1cef c65404        	ld	a,21508
9414  1cf2 5f            	clrw	x
9415  1cf3 97            	ld	xl,a
9416  1cf4 90ae0100      	ldw	y,#256
9417  1cf8 cd0000        	call	c_umul
9419  1cfb 96            	ldw	x,sp
9420  1cfc 1c0001        	addw	x,#OFST-8
9421  1cff cd0000        	call	c_ladd
9423  1d02 96            	ldw	x,sp
9424  1d03 1c0006        	addw	x,#OFST-3
9425  1d06 cd0000        	call	c_rtol
9427                     ; 2015 if(adr_drv_stat==1)
9429  1d09 b607          	ld	a,_adr_drv_stat
9430  1d0b a101          	cp	a,#1
9431  1d0d 260b          	jrne	L7704
9432                     ; 2017 	adr_drv_stat=2;
9434  1d0f 35020007      	mov	_adr_drv_stat,#2
9435                     ; 2018 	adc_buff_[0]=temp_adc;
9437  1d13 1e08          	ldw	x,(OFST-1,sp)
9438  1d15 cf0005        	ldw	_adc_buff_,x
9440  1d18 2020          	jra	L1014
9441  1d1a               L7704:
9442                     ; 2021 else if(adr_drv_stat==3)
9444  1d1a b607          	ld	a,_adr_drv_stat
9445  1d1c a103          	cp	a,#3
9446  1d1e 260b          	jrne	L3014
9447                     ; 2023 	adr_drv_stat=4;
9449  1d20 35040007      	mov	_adr_drv_stat,#4
9450                     ; 2024 	adc_buff_[1]=temp_adc;
9452  1d24 1e08          	ldw	x,(OFST-1,sp)
9453  1d26 cf0007        	ldw	_adc_buff_+2,x
9455  1d29 200f          	jra	L1014
9456  1d2b               L3014:
9457                     ; 2027 else if(adr_drv_stat==5)
9459  1d2b b607          	ld	a,_adr_drv_stat
9460  1d2d a105          	cp	a,#5
9461  1d2f 2609          	jrne	L1014
9462                     ; 2029 	adr_drv_stat=6;
9464  1d31 35060007      	mov	_adr_drv_stat,#6
9465                     ; 2030 	adc_buff_[9]=temp_adc;
9467  1d35 1e08          	ldw	x,(OFST-1,sp)
9468  1d37 cf0017        	ldw	_adc_buff_+18,x
9469  1d3a               L1014:
9470                     ; 2033 adc_buff[adc_ch][adc_cnt]=temp_adc;
9472  1d3a b6be          	ld	a,_adc_cnt
9473  1d3c 5f            	clrw	x
9474  1d3d 97            	ld	xl,a
9475  1d3e 58            	sllw	x
9476  1d3f 1f03          	ldw	(OFST-6,sp),x
9477  1d41 b6bf          	ld	a,_adc_ch
9478  1d43 97            	ld	xl,a
9479  1d44 a620          	ld	a,#32
9480  1d46 42            	mul	x,a
9481  1d47 72fb03        	addw	x,(OFST-6,sp)
9482  1d4a 1608          	ldw	y,(OFST-1,sp)
9483  1d4c df0019        	ldw	(_adc_buff,x),y
9484                     ; 2039 adc_ch++;
9486  1d4f 3cbf          	inc	_adc_ch
9487                     ; 2040 if(adc_ch>=5)
9489  1d51 b6bf          	ld	a,_adc_ch
9490  1d53 a105          	cp	a,#5
9491  1d55 250c          	jrult	L1114
9492                     ; 2043 	adc_ch=0;
9494  1d57 3fbf          	clr	_adc_ch
9495                     ; 2044 	adc_cnt++;
9497  1d59 3cbe          	inc	_adc_cnt
9498                     ; 2045 	if(adc_cnt>=16)
9500  1d5b b6be          	ld	a,_adc_cnt
9501  1d5d a110          	cp	a,#16
9502  1d5f 2502          	jrult	L1114
9503                     ; 2047 		adc_cnt=0;
9505  1d61 3fbe          	clr	_adc_cnt
9506  1d63               L1114:
9507                     ; 2051 if((adc_cnt&0x03)==0)
9509  1d63 b6be          	ld	a,_adc_cnt
9510  1d65 a503          	bcp	a,#3
9511  1d67 264b          	jrne	L5114
9512                     ; 2055 	tempSS=0;
9514  1d69 ae0000        	ldw	x,#0
9515  1d6c 1f08          	ldw	(OFST-1,sp),x
9516  1d6e ae0000        	ldw	x,#0
9517  1d71 1f06          	ldw	(OFST-3,sp),x
9518                     ; 2056 	for(i=0;i<16;i++)
9520  1d73 0f05          	clr	(OFST-4,sp)
9521  1d75               L7114:
9522                     ; 2058 		tempSS+=(signed long)adc_buff[adc_ch][i];
9524  1d75 7b05          	ld	a,(OFST-4,sp)
9525  1d77 5f            	clrw	x
9526  1d78 97            	ld	xl,a
9527  1d79 58            	sllw	x
9528  1d7a 1f03          	ldw	(OFST-6,sp),x
9529  1d7c b6bf          	ld	a,_adc_ch
9530  1d7e 97            	ld	xl,a
9531  1d7f a620          	ld	a,#32
9532  1d81 42            	mul	x,a
9533  1d82 72fb03        	addw	x,(OFST-6,sp)
9534  1d85 de0019        	ldw	x,(_adc_buff,x)
9535  1d88 cd0000        	call	c_itolx
9537  1d8b 96            	ldw	x,sp
9538  1d8c 1c0006        	addw	x,#OFST-3
9539  1d8f cd0000        	call	c_lgadd
9541                     ; 2056 	for(i=0;i<16;i++)
9543  1d92 0c05          	inc	(OFST-4,sp)
9546  1d94 7b05          	ld	a,(OFST-4,sp)
9547  1d96 a110          	cp	a,#16
9548  1d98 25db          	jrult	L7114
9549                     ; 2060 	adc_buff_[adc_ch]=(signed short)(tempSS>>4);
9551  1d9a 96            	ldw	x,sp
9552  1d9b 1c0006        	addw	x,#OFST-3
9553  1d9e cd0000        	call	c_ltor
9555  1da1 a604          	ld	a,#4
9556  1da3 cd0000        	call	c_lrsh
9558  1da6 be02          	ldw	x,c_lreg+2
9559  1da8 b6bf          	ld	a,_adc_ch
9560  1daa 905f          	clrw	y
9561  1dac 9097          	ld	yl,a
9562  1dae 9058          	sllw	y
9563  1db0 90df0005      	ldw	(_adc_buff_,y),x
9564  1db4               L5114:
9565                     ; 2071 adc_plazma_short++;
9567  1db4 bebc          	ldw	x,_adc_plazma_short
9568  1db6 1c0001        	addw	x,#1
9569  1db9 bfbc          	ldw	_adc_plazma_short,x
9570                     ; 2086 }
9573  1dbb 5b09          	addw	sp,#9
9574  1dbd 85            	popw	x
9575  1dbe bf00          	ldw	c_lreg,x
9576  1dc0 85            	popw	x
9577  1dc1 bf02          	ldw	c_lreg+2,x
9578  1dc3 85            	popw	x
9579  1dc4 bf00          	ldw	c_y,x
9580  1dc6 85            	popw	x
9581  1dc7 bf00          	ldw	c_x,x
9582  1dc9 80            	iret
9645                     ; 2094 main()
9645                     ; 2095 {
9647                     	switch	.text
9648  1dca               _main:
9652                     ; 2097 CLK->ECKR|=1;
9654  1dca 721050c1      	bset	20673,#0
9656  1dce               L7314:
9657                     ; 2098 while((CLK->ECKR & 2) == 0);
9659  1dce c650c1        	ld	a,20673
9660  1dd1 a502          	bcp	a,#2
9661  1dd3 27f9          	jreq	L7314
9662                     ; 2099 CLK->SWCR|=2;
9664  1dd5 721250c5      	bset	20677,#1
9665                     ; 2100 CLK->SWR=0xB4;
9667  1dd9 35b450c4      	mov	20676,#180
9668                     ; 2102 delay_ms(200);
9670  1ddd ae00c8        	ldw	x,#200
9671  1de0 cd004c        	call	_delay_ms
9673                     ; 2103 FLASH_DUKR=0xae;
9675  1de3 35ae5064      	mov	_FLASH_DUKR,#174
9676                     ; 2104 FLASH_DUKR=0x56;
9678  1de7 35565064      	mov	_FLASH_DUKR,#86
9679                     ; 2105 enableInterrupts();
9682  1deb 9a            rim
9684                     ; 2108 adr_drv_v3();
9687  1dec cd1013        	call	_adr_drv_v3
9689                     ; 2112 t4_init();
9691  1def cd1b8c        	call	_t4_init
9693                     ; 2114 		GPIOG->DDR|=(1<<0);
9695  1df2 72105020      	bset	20512,#0
9696                     ; 2115 		GPIOG->CR1|=(1<<0);
9698  1df6 72105021      	bset	20513,#0
9699                     ; 2116 		GPIOG->CR2&=~(1<<0);	
9701  1dfa 72115022      	bres	20514,#0
9702                     ; 2119 		GPIOG->DDR&=~(1<<1);
9704  1dfe 72135020      	bres	20512,#1
9705                     ; 2120 		GPIOG->CR1|=(1<<1);
9707  1e02 72125021      	bset	20513,#1
9708                     ; 2121 		GPIOG->CR2&=~(1<<1);
9710  1e06 72135022      	bres	20514,#1
9711                     ; 2123 init_CAN();
9713  1e0a cd1356        	call	_init_CAN
9715                     ; 2128 GPIOC->DDR|=(1<<1);
9717  1e0d 7212500c      	bset	20492,#1
9718                     ; 2129 GPIOC->CR1|=(1<<1);
9720  1e11 7212500d      	bset	20493,#1
9721                     ; 2130 GPIOC->CR2|=(1<<1);
9723  1e15 7212500e      	bset	20494,#1
9724                     ; 2132 GPIOC->DDR|=(1<<2);
9726  1e19 7214500c      	bset	20492,#2
9727                     ; 2133 GPIOC->CR1|=(1<<2);
9729  1e1d 7214500d      	bset	20493,#2
9730                     ; 2134 GPIOC->CR2|=(1<<2);
9732  1e21 7214500e      	bset	20494,#2
9733                     ; 2141 t1_init();
9735  1e25 cd1b9d        	call	_t1_init
9737                     ; 2143 GPIOA->DDR|=(1<<5);
9739  1e28 721a5002      	bset	20482,#5
9740                     ; 2144 GPIOA->CR1|=(1<<5);
9742  1e2c 721a5003      	bset	20483,#5
9743                     ; 2145 GPIOA->CR2&=~(1<<5);
9745  1e30 721b5004      	bres	20484,#5
9746                     ; 2151 GPIOB->DDR|=(1<<3);
9748  1e34 72165007      	bset	20487,#3
9749                     ; 2152 GPIOB->CR1|=(1<<3);
9751  1e38 72165008      	bset	20488,#3
9752                     ; 2153 GPIOB->CR2|=(1<<3);
9754  1e3c 72165009      	bset	20489,#3
9755                     ; 2155 GPIOC->DDR|=(1<<3);
9757  1e40 7216500c      	bset	20492,#3
9758                     ; 2156 GPIOC->CR1|=(1<<3);
9760  1e44 7216500d      	bset	20493,#3
9761                     ; 2157 GPIOC->CR2|=(1<<3);
9763  1e48 7216500e      	bset	20494,#3
9764                     ; 2160 if(bps_class==bpsIPS) 
9766  1e4c b601          	ld	a,_bps_class
9767  1e4e a101          	cp	a,#1
9768  1e50 260a          	jrne	L5414
9769                     ; 2162 	pwm_u=ee_U_AVT;
9771  1e52 ce000a        	ldw	x,_ee_U_AVT
9772  1e55 bf0b          	ldw	_pwm_u,x
9773                     ; 2163 	volum_u_main_=ee_U_AVT;
9775  1e57 ce000a        	ldw	x,_ee_U_AVT
9776  1e5a bf1c          	ldw	_volum_u_main_,x
9777  1e5c               L5414:
9778                     ; 2170 	if(bCAN_RX)
9780  1e5c 3d09          	tnz	_bCAN_RX
9781  1e5e 2705          	jreq	L1514
9782                     ; 2172 		bCAN_RX=0;
9784  1e60 3f09          	clr	_bCAN_RX
9785                     ; 2173 		can_in_an();	
9787  1e62 cd1561        	call	_can_in_an
9789  1e65               L1514:
9790                     ; 2175 	if(b100Hz)
9792                     	btst	_b100Hz
9793  1e6a 240a          	jruge	L3514
9794                     ; 2177 		b100Hz=0;
9796  1e6c 72110008      	bres	_b100Hz
9797                     ; 2186 		adc2_init();
9799  1e70 cd1bda        	call	_adc2_init
9801                     ; 2187 		can_tx_hndl();
9803  1e73 cd1449        	call	_can_tx_hndl
9805  1e76               L3514:
9806                     ; 2190 	if(b10Hz)
9808                     	btst	_b10Hz
9809  1e7b 2419          	jruge	L5514
9810                     ; 2192 		b10Hz=0;
9812  1e7d 72110007      	bres	_b10Hz
9813                     ; 2194           matemat();
9815  1e81 cd0bca        	call	_matemat
9817                     ; 2195 	    	led_drv(); 
9819  1e84 cd0711        	call	_led_drv
9821                     ; 2196 	     link_drv();
9823  1e87 cd07ff        	call	_link_drv
9825                     ; 2197 	     pwr_hndl();		//вычисление воздействий на силу
9827  1e8a cd0aae        	call	_pwr_hndl
9829                     ; 2198 	     JP_drv();
9831  1e8d cd0774        	call	_JP_drv
9833                     ; 2199 	     flags_drv();
9835  1e90 cd0fc8        	call	_flags_drv
9837                     ; 2200 		net_drv();
9839  1e93 cd14b3        	call	_net_drv
9841  1e96               L5514:
9842                     ; 2203 	if(b5Hz)
9844                     	btst	_b5Hz
9845  1e9b 240d          	jruge	L7514
9846                     ; 2205 		b5Hz=0;
9848  1e9d 72110006      	bres	_b5Hz
9849                     ; 2207 		pwr_drv();		//воздействие на силу
9851  1ea1 cd09aa        	call	_pwr_drv
9853                     ; 2208 		led_hndl();
9855  1ea4 cd008e        	call	_led_hndl
9857                     ; 2210 		vent_drv();
9859  1ea7 cd084e        	call	_vent_drv
9861  1eaa               L7514:
9862                     ; 2213 	if(b2Hz)
9864                     	btst	_b2Hz
9865  1eaf 2404          	jruge	L1614
9866                     ; 2215 		b2Hz=0;
9868  1eb1 72110005      	bres	_b2Hz
9869  1eb5               L1614:
9870                     ; 2224 	if(b1Hz)
9872                     	btst	_b1Hz
9873  1eba 24a0          	jruge	L5414
9874                     ; 2226 		b1Hz=0;
9876  1ebc 72110004      	bres	_b1Hz
9877                     ; 2228 		temper_drv();			//вычисление аварий температуры
9879  1ec0 cd0cf8        	call	_temper_drv
9881                     ; 2229 		u_drv();
9883  1ec3 cd0dcf        	call	_u_drv
9885                     ; 2230           x_drv();
9887  1ec6 cd0eaf        	call	_x_drv
9889                     ; 2231           if(main_cnt<1000)main_cnt++;
9891  1ec9 9c            	rvf
9892  1eca be4e          	ldw	x,_main_cnt
9893  1ecc a303e8        	cpw	x,#1000
9894  1ecf 2e07          	jrsge	L5614
9897  1ed1 be4e          	ldw	x,_main_cnt
9898  1ed3 1c0001        	addw	x,#1
9899  1ed6 bf4e          	ldw	_main_cnt,x
9900  1ed8               L5614:
9901                     ; 2232   		if((link==OFF)||(jp_mode==jp3))apv_hndl();
9903  1ed8 b65f          	ld	a,_link
9904  1eda a1aa          	cp	a,#170
9905  1edc 2706          	jreq	L1714
9907  1ede b647          	ld	a,_jp_mode
9908  1ee0 a103          	cp	a,#3
9909  1ee2 2603          	jrne	L7614
9910  1ee4               L1714:
9913  1ee4 cd0f29        	call	_apv_hndl
9915  1ee7               L7614:
9916                     ; 2235   		can_error_cnt++;
9918  1ee7 3c6d          	inc	_can_error_cnt
9919                     ; 2236   		if(can_error_cnt>=10)
9921  1ee9 b66d          	ld	a,_can_error_cnt
9922  1eeb a10a          	cp	a,#10
9923  1eed 2505          	jrult	L3714
9924                     ; 2238   			can_error_cnt=0;
9926  1eef 3f6d          	clr	_can_error_cnt
9927                     ; 2239 			init_CAN();
9929  1ef1 cd1356        	call	_init_CAN
9931  1ef4               L3714:
9932                     ; 2243 		volum_u_main_drv();
9934  1ef4 cd1203        	call	_volum_u_main_drv
9936                     ; 2245 		pwm_stat++;
9938  1ef7 3c04          	inc	_pwm_stat
9939                     ; 2246 		if(pwm_stat>=10)pwm_stat=0;
9941  1ef9 b604          	ld	a,_pwm_stat
9942  1efb a10a          	cp	a,#10
9943  1efd 2502          	jrult	L5714
9946  1eff 3f04          	clr	_pwm_stat
9947  1f01               L5714:
9948                     ; 2247 adc_plazma_short++;
9950  1f01 bebc          	ldw	x,_adc_plazma_short
9951  1f03 1c0001        	addw	x,#1
9952  1f06 bfbc          	ldw	_adc_plazma_short,x
9953  1f08 ac5c1e5c      	jpf	L5414
10967                     	xdef	_main
10968                     	xdef	f_ADC2_EOC_Interrupt
10969                     	xdef	f_CAN_TX_Interrupt
10970                     	xdef	f_CAN_RX_Interrupt
10971                     	xdef	f_TIM4_UPD_Interrupt
10972                     	xdef	_adc2_init
10973                     	xdef	_t1_init
10974                     	xdef	_t4_init
10975                     	xdef	_can_in_an
10976                     	xdef	_net_drv
10977                     	xdef	_can_tx_hndl
10978                     	xdef	_can_transmit
10979                     	xdef	_init_CAN
10980                     	xdef	_volum_u_main_drv
10981                     	xdef	_adr_drv_v3
10982                     	xdef	_adr_drv_v4
10983                     	xdef	_flags_drv
10984                     	xdef	_apv_hndl
10985                     	xdef	_apv_stop
10986                     	xdef	_apv_start
10987                     	xdef	_x_drv
10988                     	xdef	_u_drv
10989                     	xdef	_temper_drv
10990                     	xdef	_matemat
10991                     	xdef	_pwr_hndl
10992                     	xdef	_pwr_drv
10993                     	xdef	_vent_drv
10994                     	xdef	_link_drv
10995                     	xdef	_JP_drv
10996                     	xdef	_led_drv
10997                     	xdef	_led_hndl
10998                     	xdef	_delay_ms
10999                     	xdef	_granee
11000                     	xdef	_gran
11001                     .eeprom:	section	.data
11002  0000               _ee_IMAXVENT:
11003  0000 0000          	ds.b	2
11004                     	xdef	_ee_IMAXVENT
11005                     	switch	.ubsct
11006  0001               _bps_class:
11007  0001 00            	ds.b	1
11008                     	xdef	_bps_class
11009  0002               _vent_pwm:
11010  0002 0000          	ds.b	2
11011                     	xdef	_vent_pwm
11012  0004               _pwm_stat:
11013  0004 00            	ds.b	1
11014                     	xdef	_pwm_stat
11015  0005               _pwm_vent_cnt:
11016  0005 00            	ds.b	1
11017                     	xdef	_pwm_vent_cnt
11018                     	switch	.eeprom
11019  0002               _ee_DEVICE:
11020  0002 0000          	ds.b	2
11021                     	xdef	_ee_DEVICE
11022  0004               _ee_AVT_MODE:
11023  0004 0000          	ds.b	2
11024                     	xdef	_ee_AVT_MODE
11025                     	switch	.ubsct
11026  0006               _i_main_bps_cnt:
11027  0006 000000000000  	ds.b	6
11028                     	xdef	_i_main_bps_cnt
11029  000c               _i_main_sigma:
11030  000c 0000          	ds.b	2
11031                     	xdef	_i_main_sigma
11032  000e               _i_main_num_of_bps:
11033  000e 00            	ds.b	1
11034                     	xdef	_i_main_num_of_bps
11035  000f               _i_main_avg:
11036  000f 0000          	ds.b	2
11037                     	xdef	_i_main_avg
11038  0011               _i_main_flag:
11039  0011 000000000000  	ds.b	6
11040                     	xdef	_i_main_flag
11041  0017               _i_main:
11042  0017 000000000000  	ds.b	12
11043                     	xdef	_i_main
11044  0023               _x:
11045  0023 000000000000  	ds.b	12
11046                     	xdef	_x
11047                     	xdef	_volum_u_main_
11048                     	switch	.eeprom
11049  0006               _UU_AVT:
11050  0006 0000          	ds.b	2
11051                     	xdef	_UU_AVT
11052                     	switch	.ubsct
11053  002f               _cnt_net_drv:
11054  002f 00            	ds.b	1
11055                     	xdef	_cnt_net_drv
11056                     	switch	.bit
11057  0001               _bMAIN:
11058  0001 00            	ds.b	1
11059                     	xdef	_bMAIN
11060                     	switch	.ubsct
11061  0030               _plazma_int:
11062  0030 000000000000  	ds.b	6
11063                     	xdef	_plazma_int
11064                     	xdef	_rotor_int
11065  0036               _led_green_buff:
11066  0036 00000000      	ds.b	4
11067                     	xdef	_led_green_buff
11068  003a               _led_red_buff:
11069  003a 00000000      	ds.b	4
11070                     	xdef	_led_red_buff
11071                     	xdef	_led_drv_cnt
11072                     	xdef	_led_green
11073                     	xdef	_led_red
11074  003e               _res_fl_cnt:
11075  003e 00            	ds.b	1
11076                     	xdef	_res_fl_cnt
11077                     	xdef	_bRES_
11078                     	xdef	_bRES
11079                     	switch	.eeprom
11080  0008               _res_fl_:
11081  0008 00            	ds.b	1
11082                     	xdef	_res_fl_
11083  0009               _res_fl:
11084  0009 00            	ds.b	1
11085                     	xdef	_res_fl
11086                     	switch	.ubsct
11087  003f               _cnt_apv_off:
11088  003f 00            	ds.b	1
11089                     	xdef	_cnt_apv_off
11090                     	switch	.bit
11091  0002               _bAPV:
11092  0002 00            	ds.b	1
11093                     	xdef	_bAPV
11094                     	switch	.ubsct
11095  0040               _apv_cnt_:
11096  0040 0000          	ds.b	2
11097                     	xdef	_apv_cnt_
11098  0042               _apv_cnt:
11099  0042 000000        	ds.b	3
11100                     	xdef	_apv_cnt
11101                     	xdef	_bBL_IPS
11102                     	switch	.bit
11103  0003               _bBL:
11104  0003 00            	ds.b	1
11105                     	xdef	_bBL
11106                     	switch	.ubsct
11107  0045               _cnt_JP1:
11108  0045 00            	ds.b	1
11109                     	xdef	_cnt_JP1
11110  0046               _cnt_JP0:
11111  0046 00            	ds.b	1
11112                     	xdef	_cnt_JP0
11113  0047               _jp_mode:
11114  0047 00            	ds.b	1
11115                     	xdef	_jp_mode
11116                     	xdef	_pwm_i
11117                     	xdef	_pwm_u
11118  0048               _tmax_cnt:
11119  0048 0000          	ds.b	2
11120                     	xdef	_tmax_cnt
11121  004a               _tsign_cnt:
11122  004a 0000          	ds.b	2
11123                     	xdef	_tsign_cnt
11124                     	switch	.eeprom
11125  000a               _ee_U_AVT:
11126  000a 0000          	ds.b	2
11127                     	xdef	_ee_U_AVT
11128  000c               _ee_tsign:
11129  000c 0000          	ds.b	2
11130                     	xdef	_ee_tsign
11131  000e               _ee_tmax:
11132  000e 0000          	ds.b	2
11133                     	xdef	_ee_tmax
11134  0010               _ee_dU:
11135  0010 0000          	ds.b	2
11136                     	xdef	_ee_dU
11137  0012               _ee_Umax:
11138  0012 0000          	ds.b	2
11139                     	xdef	_ee_Umax
11140  0014               _ee_TZAS:
11141  0014 0000          	ds.b	2
11142                     	xdef	_ee_TZAS
11143                     	switch	.ubsct
11144  004c               _main_cnt1:
11145  004c 0000          	ds.b	2
11146                     	xdef	_main_cnt1
11147  004e               _main_cnt:
11148  004e 0000          	ds.b	2
11149                     	xdef	_main_cnt
11150  0050               _off_bp_cnt:
11151  0050 00            	ds.b	1
11152                     	xdef	_off_bp_cnt
11153  0051               _flags_tu_cnt_off:
11154  0051 00            	ds.b	1
11155                     	xdef	_flags_tu_cnt_off
11156  0052               _flags_tu_cnt_on:
11157  0052 00            	ds.b	1
11158                     	xdef	_flags_tu_cnt_on
11159  0053               _vol_i_temp:
11160  0053 0000          	ds.b	2
11161                     	xdef	_vol_i_temp
11162  0055               _vol_u_temp:
11163  0055 0000          	ds.b	2
11164                     	xdef	_vol_u_temp
11165                     	switch	.eeprom
11166  0016               __x_ee_:
11167  0016 0000          	ds.b	2
11168                     	xdef	__x_ee_
11169                     	switch	.ubsct
11170  0057               __x_cnt:
11171  0057 0000          	ds.b	2
11172                     	xdef	__x_cnt
11173  0059               __x__:
11174  0059 0000          	ds.b	2
11175                     	xdef	__x__
11176  005b               __x_:
11177  005b 0000          	ds.b	2
11178                     	xdef	__x_
11179  005d               _flags_tu:
11180  005d 00            	ds.b	1
11181                     	xdef	_flags_tu
11182                     	xdef	_flags
11183  005e               _link_cnt:
11184  005e 00            	ds.b	1
11185                     	xdef	_link_cnt
11186  005f               _link:
11187  005f 00            	ds.b	1
11188                     	xdef	_link
11189  0060               _umin_cnt:
11190  0060 0000          	ds.b	2
11191                     	xdef	_umin_cnt
11192  0062               _umax_cnt:
11193  0062 0000          	ds.b	2
11194                     	xdef	_umax_cnt
11195                     	switch	.eeprom
11196  0018               _ee_K:
11197  0018 000000000000  	ds.b	16
11198                     	xdef	_ee_K
11199                     	switch	.ubsct
11200  0064               _T:
11201  0064 00            	ds.b	1
11202                     	xdef	_T
11203  0065               _Udb:
11204  0065 0000          	ds.b	2
11205                     	xdef	_Udb
11206  0067               _Ui:
11207  0067 0000          	ds.b	2
11208                     	xdef	_Ui
11209  0069               _Un:
11210  0069 0000          	ds.b	2
11211                     	xdef	_Un
11212  006b               _I:
11213  006b 0000          	ds.b	2
11214                     	xdef	_I
11215  006d               _can_error_cnt:
11216  006d 00            	ds.b	1
11217                     	xdef	_can_error_cnt
11218                     	xdef	_bCAN_RX
11219  006e               _tx_busy_cnt:
11220  006e 00            	ds.b	1
11221                     	xdef	_tx_busy_cnt
11222                     	xdef	_bTX_FREE
11223  006f               _can_buff_rd_ptr:
11224  006f 00            	ds.b	1
11225                     	xdef	_can_buff_rd_ptr
11226  0070               _can_buff_wr_ptr:
11227  0070 00            	ds.b	1
11228                     	xdef	_can_buff_wr_ptr
11229  0071               _can_out_buff:
11230  0071 000000000000  	ds.b	64
11231                     	xdef	_can_out_buff
11232                     	switch	.bss
11233  0000               _adress_error:
11234  0000 00            	ds.b	1
11235                     	xdef	_adress_error
11236  0001               _adress:
11237  0001 00            	ds.b	1
11238                     	xdef	_adress
11239  0002               _adr:
11240  0002 000000        	ds.b	3
11241                     	xdef	_adr
11242                     	xdef	_adr_drv_stat
11243                     	xdef	_led_ind
11244                     	switch	.ubsct
11245  00b1               _led_ind_cnt:
11246  00b1 00            	ds.b	1
11247                     	xdef	_led_ind_cnt
11248  00b2               _adc_plazma:
11249  00b2 000000000000  	ds.b	10
11250                     	xdef	_adc_plazma
11251  00bc               _adc_plazma_short:
11252  00bc 0000          	ds.b	2
11253                     	xdef	_adc_plazma_short
11254  00be               _adc_cnt:
11255  00be 00            	ds.b	1
11256                     	xdef	_adc_cnt
11257  00bf               _adc_ch:
11258  00bf 00            	ds.b	1
11259                     	xdef	_adc_ch
11260                     	switch	.bss
11261  0005               _adc_buff_:
11262  0005 000000000000  	ds.b	20
11263                     	xdef	_adc_buff_
11264  0019               _adc_buff:
11265  0019 000000000000  	ds.b	320
11266                     	xdef	_adc_buff
11267                     	switch	.ubsct
11268  00c0               _mess:
11269  00c0 000000000000  	ds.b	14
11270                     	xdef	_mess
11271                     	switch	.bit
11272  0004               _b1Hz:
11273  0004 00            	ds.b	1
11274                     	xdef	_b1Hz
11275  0005               _b2Hz:
11276  0005 00            	ds.b	1
11277                     	xdef	_b2Hz
11278  0006               _b5Hz:
11279  0006 00            	ds.b	1
11280                     	xdef	_b5Hz
11281  0007               _b10Hz:
11282  0007 00            	ds.b	1
11283                     	xdef	_b10Hz
11284  0008               _b100Hz:
11285  0008 00            	ds.b	1
11286                     	xdef	_b100Hz
11287                     	xdef	_t0_cnt4
11288                     	xdef	_t0_cnt3
11289                     	xdef	_t0_cnt2
11290                     	xdef	_t0_cnt1
11291                     	xdef	_t0_cnt0
11292                     	xref.b	c_lreg
11293                     	xref.b	c_x
11294                     	xref.b	c_y
11314                     	xref	c_lrsh
11315                     	xref	c_lgadd
11316                     	xref	c_ladd
11317                     	xref	c_umul
11318                     	xref	c_lgmul
11319                     	xref	c_lgsub
11320                     	xref	c_lsbc
11321                     	xref	c_idiv
11322                     	xref	c_ldiv
11323                     	xref	c_itolx
11324                     	xref	c_eewrc
11325                     	xref	c_imul
11326                     	xref	c_lcmp
11327                     	xref	c_ltor
11328                     	xref	c_lgadc
11329                     	xref	c_rtol
11330                     	xref	c_vmul
11331                     	xref	c_eewrw
11332                     	end
