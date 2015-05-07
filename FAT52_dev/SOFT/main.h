#define LCD_SIZE 200

#define MASK(lengt) 		(0xffffffff>>(32-lengt))
#define MASK_OFFSET(shift,lengt)	(MASK(lengt)<<shift)

#define GET_REG( reg, shift, lengt) 		( (reg & MASK_OFFSET(shift,lengt)) >> shift)
#define SET_REG( reg, val, shift, lengt)  	reg = ( (reg & ~MASK_OFFSET(shift,lengt)) | ((val&MASK(lengt)) << shift) )
//#define CHK_REG( reg, mask ) ( (reg) & (mask) == (mask) )


#define OFFBP1 GET_REG(LPC_GPIO0->FIOPIN,8,1)
#define OFFBP2 GET_REG(LPC_GPIO0->FIOPIN,9,1)

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#define BIN__N(x) (x) | x>>3 | x>>6 | x>>9
#define BIN__B(x) (x) & 0xf | (x)>>12 & 0xf0
#define BIN8(v) (BIN__B(BIN__N(0x##v)))

#define SEC_IN_HOUR	3600L

#define KOEFPOT 100

#define BAUD_RATE0 9600UL
#define BAUD_RATE1 9600UL

#define HARDVARE_VERSION	 5



//#define PAROL_ALL_ZERO


#ifndef PAROL_ALL_ZERO
#define PAROL_KALIBR 873
#define PAROL_SET 184
#define PAROL_MODE 0 
#define PAROL_ALLER 815 
#define PAROL_BAT_IN 722 
#define PAROL_BAT_OUT 722
#define PAROL_KE 125
#define PAROL_VZ 126
#define PAROL_TST 999 
#define PAROL_DEFAULT 295
#define PAROL_AUSW 949
#endif                

#ifdef PAROL_ALL_ZERO
#define PAROL_KALIBR 0
#define PAROL_SET 0
#define PAROL_MODE 0 
#define PAROL_ALLER 0 
#define PAROL_BAT_IN 0 
#define PAROL_BAT_OUT 0
#define PAROL_KE 0
#define PAROL_VZ 0
#define PAROL_TST 0
#define PAROL_DEFAULT 0
#define PAROL_AUSW 0
#endif

#define BUT0	0
#define BUT1	1
#define BUT2	2
#define BUT3	3
#define BUT4	4   
#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)|(1UL<<BUT3)|(1UL<<BUT4)

//-----------------------------------------------
//Таймер
extern char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz,b33Hz;
extern short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7,t0_cnt8;
extern char bFL5,bFL2,bFL,bFL_;

//-----------------------------------------------
//АЦП
extern int adc_buff[6][64],adc_buff_[6];
extern char adc_cnt,adc_cnt1,adc_ch;

//-----------------------------------------------
//Состояние сети
extern short Hz_cnt,fnet,Hz_out;
extern char bFF,bFF_;
extern signed short Unet;
extern char unet_drv_cnt;
extern signed short unet_store;

extern signed char ptr_ind;
extern char mnemo_cnt;
extern signed char parol[3];
extern char fl_simv_num,fl_simv_len;
extern char default_temp;
extern signed short av_j_si_max,av_j_si_max_;
extern char simax;
extern char phase;
extern const char sm_[]; //
extern const char sm_exit[]; //
extern const char smon[]; 
extern const char smoff[];
extern const char sm_mont[13][4]; //
extern char content[63]; 

//-----------------------------------------------
//Коэффициенты, отображаемые из EEPROM
extern signed short Ktsrc[2];
extern signed short Kusrc[2];
extern signed short Kisrc[2];
extern signed short Ki0src[2];
extern signed short Kubat;
extern signed short Kibat0;
extern signed short Kibat1;
extern signed short Ktbat;
extern signed short Kunet;
extern signed short Ktout[3];

extern signed short MAIN_IST;
extern signed short UMAX;
extern signed short UB0;
extern signed short UB20;
extern signed short TMAX;
extern signed short AV_OFF_AVT;
extern signed short USIGN;
extern signed short UMN;
extern signed short ZV_ON;
extern signed short IKB;
extern signed short KVZ;
extern signed short IMAX;
extern signed short KIMAX;
extern signed short APV_ON;
extern signed short IZMAX;
extern signed short U0B;
extern signed short TZAS;
extern signed short VZ_HR;
extern signed short TBAT;

extern signed short NUMBAT;
extern signed short NUMIST;
extern signed short NUMDT;
extern signed short NUMSK;
extern signed short BAT_C_REAL;
extern signed short BAT_C_NOM;
extern signed short BAT_RESURS;

//signed short ZAR_CNT,ZAR_CNT_KE;
//signed short BAT_RESURS;

extern signed short AUSW_MAIN;
extern signed long 	AUSW_MAIN_NUMBER;
extern signed short AUSW_DAY;
extern signed short AUSW_MONTH;
extern signed short AUSW_YEAR;
extern signed short AUSW_UKU;
extern signed short AUSW_UKU_SUB;
extern signed long AUSW_UKU_NUMBER;
extern signed long	AUSW_BPS1_NUMBER;
extern signed long  AUSW_BPS2_NUMBER;
extern signed short AUSW_RS232;
extern signed short AUSW_PDH;
extern signed short AUSW_SDH;
extern signed short AUSW_ETH;

extern signed short TMAX_EXT_EN[3];
extern signed short TMAX_EXT[3];
extern signed short TMIN_EXT_EN[3];
extern signed short TMIN_EXT[3];
extern signed short T_EXT_REL_EN[3];
extern signed short T_EXT_ZVUK_EN[3];
extern signed short T_EXT_LCD_EN[3];
extern signed short T_EXT_RS_EN[3];

extern signed short SK_SIGN[4];
extern signed short SK_REL_EN[4];
extern signed short SK_ZVUK_EN[4];
extern signed short SK_LCD_EN[4];
extern signed short SK_RS_EN[4];

typedef enum {AVZ_1=1,AVZ_2=2,AVZ_3=3,AVZ_6=6,AVZ_12=12,AVZ_OFF=0}enum_AVZ;
extern enum_AVZ AVZ;

extern unsigned short HOUR_AVZ;
extern unsigned short MIN_AVZ;
extern unsigned short SEC_AVZ;
extern unsigned short DATE_AVZ;
extern unsigned short MONTH_AVZ;
extern unsigned short YEAR_AVZ;
extern unsigned short AVZ_TIME;

extern signed short dumm[8];

typedef enum  {bisON=0x0055,bisOFF=0x00aa}enum_BAT_IS_ON;
extern enum_BAT_IS_ON BAT_IS_ON;
typedef enum  {apvON=0x0055,apvOFF=0x00aa}enum_apv_on;
extern enum_apv_on apv_on1,apv_on2;

extern signed short BAT_DAY_OF_ON,BAT_MONTH_OF_ON,BAT_YEAR_OF_ON;
extern signed short apv_on2_time;

typedef enum {mnON=0x55,mnOFF=0xAA}enum_MNEMO_ON;
extern enum_MNEMO_ON MNEMO_ON;
extern unsigned short MNEMO_TIME;


//-----------------------------------------------
//Состояние системы
extern char St;
extern short main_cnt;
extern char bRESET;
extern char reset_cnt;

//-----------------------------------------------
//Связь
typedef enum {lsON,lsOFF} enum_link_stat;
extern enum_link_stat link_stat;
extern signed short link_cnt;



//-----------------------------------------------
//Состояние источников
extern char St_[2];
extern signed short t_i[2],Us[2],Is[2];
extern char ND[2];

//-----------------------------------------------
//Состояние нагрузки
extern signed short iload,Uload;

//-----------------------------------------------
//Состояние внешних датчиков
extern signed short tout[3];
extern char tout_max_cnt[3],tout_min_cnt[3];
typedef enum {tNORM,tMAX,tMIN}enum_tout_stat;
extern enum_tout_stat tout_stat[3];
extern char in_stat_out_old[4];
typedef enum {skON=0x55,skOFF=0xaa}enum_sk_stat;
extern enum_sk_stat sk_stat[4];
extern char ND_out[3];
extern char in_stat_out[4];

//-----------------------------------------------
//Кнопки
extern char speed,l_but,n_but;
extern char but;                            
extern unsigned long but_n,but_s;
extern char but0_cnt;
extern char but1_cnt;
extern char but_onL_temp;

 //-----------------------------------------------
//Сообщения
extern char MSG_IND2OUT_DIS_SRC1,MSG_IND2OUT_DIS_SRC1_OLD;
extern char MSG_IND2OUT_DIS_SRC2,MSG_IND2OUT_DIS_SRC2_OLD;
extern char MSG_IND2OUT_EN_SRC1,MSG_IND2OUT_EN_SRC1_OLD;
extern char MSG_IND2OUT_EN_SRC2,MSG_IND2OUT_EN_SRC2_OLD;
extern char MSG_IND2OUT_EN_RELSAM,MSG_IND2OUT_EN_RELSAM_OLD;
extern short MSG_IND2PWM_SRC1,MSG_IND2PWM_SRC2;


//-----------------------------------------------
//Управление реле
typedef enum {rsON,rsOFF} enum_rele_stat;

//-----------------------------------------------
//Управление вентилятором
extern signed char pos_vent_,pos_vent;

//-----------------------------------------------
//Время
extern unsigned short hour_cnt_5hz,hour_cnt_1hz;
extern char cnt_ind;

//-----------------------------------------------
//Напряжения вводов
extern signed short Uvv[3],U[3];

//-----------------------------------------------
//Датчик температуры
extern signed short T;

//-----------------------------------------------
//Управление вводами
extern signed short vvod;
extern signed short vvod_cnt_to1,vvod_cnt_to2;

//-----------------------------------------------
//Работа со щетчиком
extern signed long power_summary;
extern signed short power_current;
extern char power_cnt_adrl,power_cnt_adrh;

//-----------------------------------------------
//Работа со щетчиком 102m
extern char tot_pow_buff[10];
extern char tot_pow_buff_ptr,tot_pow_buff_cnt;
extern char tot_pow_buff_ready;
extern char curr_pow_buff[10];
extern char curr_pow_buff_ptr,curr_pow_buff_cnt;
extern char curr_pow_buff_ready;

//-----------------------------------------------
//Отладка
extern unsigned short rotor_can[6];
extern unsigned short cnt_sec;
extern char plazma_suzun;
extern char uart_plazma[5];
extern char tx_stat_off_cnt;



extern char sum_pow_dig[20];
extern char sum_pow_dig_cnt;
extern char bSP;
extern long sum_pow_102m;
extern char cur_pow_dig[20];
extern char cur_pow_dig_cnt;
extern char bCP;
extern long cur_pow_102m;
extern char plazma_ppp;

extern short uart1_rx_plazma;

//-----------------------------------------------
void Delay (unsigned long tick); 
void SysTick_Handler (void);


/******************************************************************************
**                            End Of File
******************************************************************************/
