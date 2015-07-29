#include "lcd_AGM1232_uku207_3.h"
#include "rtl.h"
#include "type.h"
#include "main.h"
#include "simbol.h"
#include "25lc640.h"
#include "Timer.h"
#include "gran.h"
#include "uart0.h"
#include "uart1.h"
#include "cmd.h"
#include "ret.h"
#include "eeprom_map.h"
#include "common_func.h"
#include "control.h"
#include "mess.h"
#include "full_can.h"
#include "watchdog.h"
#include "ad7705.h"
#include "beep.h"
#include "avar_hndl.h"
#include "memo.h"
#include "simbols.h"
#include "graphic.h"
//#include "snmp_data_file.h" 
#include "net_config.h"
#include "uart0.h"
#include <rtl.h>
#include "modbus.h"

extern U8 own_hw_adr[];

BOOL tick;
extern LOCALM localm[];
#define MY_IP localm[NETIF_ETH].IpAdr
#define DHCP_TOUT   50

//***********************************************
//Таймер
char b10000Hz,b1000Hz,b2000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz,b1min,bFL34;
short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7,t0_cnt_min;
char bFL5,bFL2,bFL,bFL_,bTPS,bFL_REV;
signed short main_10Hz_cnt=0;
signed short main_1Hz_cnt=0;

 
//***********************************************
//Структура ИБЭПа
char cnt_of_slave=3;
//char cnt_of_wrks;   //колличество работающих источников , для индикации



//**********************************************
//Коэффициенты, отображаемые из EEPROM
signed short Ktsrc[2];
signed short Kusrc[2];
signed short Kisrc[2];
signed short Ki0src[2];
signed short Kubat[2];
signed short Kubatm[2];
unsigned short Kibat0[2];
signed short Kibat1[2];
signed short Ktbat[2];
signed short Kunet;
signed short Kunet_ext[3];
signed short Ktext[3];
signed short Kuload;
signed short KunetA;
signed short KunetB;
signed short KunetC;

signed short MAIN_IST;
signed short UMAX;
signed short UB0;
signed short UB20;

signed short TSIGN;
signed short AV_OFF_AVT;
signed short USIGN;
signed short UMN;
signed short ZV_ON;
signed short IKB;
//signed short KVZ;
signed short UVZ;
signed short IMAX;
signed short IMIN;
signed short APV_ON;
signed short IZMAX;
signed short U0B;
signed short TZAS;
signed short VZ_HR;
signed short TBAT;
signed short U_AVT;
signed short DU;
signed short PAR;
signed short TBATMAX;
signed short TBATSIGN;
signed short UBM_AV;
signed short TBOXMAX;
signed short TBOXREG;
signed short TBOXVENTMAX;
signed short TLOADDISABLE;
signed short TLOADENABLE;
signed short TBATDISABLE;
signed short TBATENABLE;

signed short NUMBAT;
signed short NUMIST;
signed short NUMINV;
signed short NUMDT;
signed short NUMSK;
signed short NUMEXT;
signed short NUMAVT;

enum_apv_on APV_ON1,APV_ON2;
signed short APV_ON2_TIME;

enum_bat_is_on BAT_IS_ON[2];
signed short BAT_DAY_OF_ON[2];
signed short BAT_MONTH_OF_ON[2];
signed short BAT_YEAR_OF_ON[2];
signed short BAT_C_NOM[2];
signed short BAT_RESURS[2];
signed short BAT_C_REAL[2];

unsigned short AUSW_MAIN;
unsigned long 	AUSW_MAIN_NUMBER=0x123456;
unsigned short AUSW_DAY;
unsigned short AUSW_MONTH;
unsigned short AUSW_YEAR;
unsigned short AUSW_UKU;
unsigned short AUSW_UKU_SUB;
unsigned long AUSW_UKU_NUMBER;
unsigned long	AUSW_BPS1_NUMBER;
unsigned long  AUSW_BPS2_NUMBER;
unsigned short AUSW_RS232;
unsigned short AUSW_PDH;
unsigned short AUSW_SDH;
unsigned short AUSW_ETH;

signed short TMAX_EXT_EN[3];
signed short TMAX_EXT[3];
signed short TMIN_EXT_EN[3];
signed short TMIN_EXT[3];
signed short T_EXT_REL_EN[3];
signed short T_EXT_ZVUK_EN[3];
signed short T_EXT_LCD_EN[3];
signed short T_EXT_RS_EN[3];

signed short SK_SIGN[4];
signed short SK_REL_EN[4];
signed short SK_ZVUK_EN[4];
signed short SK_LCD_EN[4];
signed short SK_RS_EN[4];

enum_avz AVZ;

unsigned short HOUR_AVZ;
unsigned short MIN_AVZ;
unsigned short SEC_AVZ;
unsigned short DATE_AVZ;
unsigned short MONTH_AVZ;
unsigned short YEAR_AVZ;
unsigned short AVZ_TIME;

enum_mnemo_on MNEMO_ON;
unsigned short MNEMO_TIME;

signed short POWER_CNT_ADRESS;

signed short ETH_IS_ON;
signed short ETH_DHCP_ON;
signed short ETH_IP_1;
signed short ETH_IP_2;
signed short ETH_IP_3;
signed short ETH_IP_4;
signed short ETH_MASK_1;
signed short ETH_MASK_2;
signed short ETH_MASK_3;
signed short ETH_MASK_4;
signed short ETH_TRAP1_IP_1;
signed short ETH_TRAP1_IP_2;
signed short ETH_TRAP1_IP_3;
signed short ETH_TRAP1_IP_4;
signed short ETH_TRAP2_IP_1;
signed short ETH_TRAP2_IP_2;
signed short ETH_TRAP2_IP_3;
signed short ETH_TRAP2_IP_4;
signed short ETH_TRAP3_IP_1;
signed short ETH_TRAP3_IP_2;
signed short ETH_TRAP3_IP_3;
signed short ETH_TRAP3_IP_4;
signed short ETH_TRAP4_IP_1;
signed short ETH_TRAP4_IP_2;
signed short ETH_TRAP4_IP_3;
signed short ETH_TRAP4_IP_4;
signed short ETH_TRAP5_IP_1;
signed short ETH_TRAP5_IP_2;
signed short ETH_TRAP5_IP_3;
signed short ETH_TRAP5_IP_4;

signed short ETH_SNMP_PORT_READ;
signed short ETH_SNMP_PORT_WRITE;

signed short ETH_GW_1;
signed short ETH_GW_2;
signed short ETH_GW_3;
signed short ETH_GW_4;

signed short MODBUS_ADRESS;
signed short MODBUS_BAUDRATE;



//***********************************************
//Состояние батарей
BAT_STAT bat[2];
signed short		bat_u_old_cnt;

//***********************************************
//Состояние источников
BPS_STAT bps[12];

//***********************************************
//Состояние инверторов
INV_STAT inv[3];
char first_inv_slot;

//***********************************************
//Состояние нагрузки
signed short load_U;
signed short load_I;
signed short load_U_;	//быстрые измерения, для регулирования, без усреднения
signed short load_I_;	//быстрые измерения, для регулирования, без усреднения

//***********************************************
//Индикация

char lcd_buffer[LCD_SIZE+100]={"Hello World"};
signed char parol[3];
char phase;
char lcd_bitmap[1024];
char dig[5];
char dumm_ind[20];
stuct_ind a_ind,b_ind[10],c_ind;
char dumm_ind_[20];
char zero_on;
char mnemo_cnt=50;
char simax;
short av_j_si_max;
const char ABCDEF[]={"0123456789ABCDEF"};
const char sm_mont[13][4]={"   ","янв","фев","мар","апр","май","июн","июл","авг","сен","окт","ноя","дек"}; //
signed short ptr_ind=0;

signed short ind_pointer=0;
char ind_fl_cnt;

//***********************************************
//Состояние первичной сети
signed short net_U,net_Ustore,net_Ua,net_Ub,net_Uc;
char bFF,bFF_;
signed short net_F,hz_out,hz_out_cnt;
char net_av;

//***********************************************
//Состояние внешних датчиков
//signed short tout[4];
char tout_max_cnt[4],tout_min_cnt[4];
enum_tout_stat tout_stat[4];
signed short t_ext[3];
BOOL ND_EXT[3];
signed char sk_cnt_dumm[4],sk_cnt[4],sk_av_cnt[4];
enum_sk_stat sk_stat[4]={ssOFF,ssOFF,ssOFF,ssOFF};
enum_sk_av_stat sk_av_stat[4]={sasOFF,sasOFF,sasOFF,sasOFF},sk_av_stat_old[4];
signed short t_box;

//***********************************************
//Звуки
extern char beep_cnt;
BOOL bSILENT;








signed short u_necc,u_necc_,u_necc_up,u_necc_dn;
signed short main_cnt_5Hz;
signed short num_necc;
signed short num_necc_Imax;
signed short num_necc_Imin;
signed short cnt_num_necc;
//char bSAME_IST_ON;
signed mat_temper;

//***********************************************
//АПВ
unsigned main_apv_cnt,hour_apv_cnt[2],reset_apv_cnt[2];
unsigned short apv_cnt_sec[2],apv_cnt[2];

//***********************************************
//Текстовые константы
const char sm_[]	={"                    "};
const char sm_exit[]={" Выход              "};
const char sm_time[]={" 0%:0^:0& 0</>  /0{ "};





//**********************************************
//Работа с кнопками 
char but;                            
unsigned long but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;

//***********************************************
//Межблоковая связь
char cnt_net_drv;

//***********************************************
//КАН 
extern char ptr_can1_tx_wr,ptr_can1_tx_rd;
extern char ptr_can2_tx_wr,ptr_can2_tx_rd;
extern unsigned short rotor_can[6];
extern char RXBUFF[40],TXBUFF[40];





//***********************************************
//Работа с кнопками
char speed,l_but,n_but;
char speed__;
char speed__old;
signed short speed_cnt;

//***********************************************
//Неразобранное
enum {wrkON=0x55,wrkOFF=0xAA}wrk;
char cnt_wrk;
signed short ibat_integr;
unsigned short av_beep,av_rele,av_stat;
char default_temp;
char ND_out[3];

//***********************************************
//Тест
enum_tst_state tst_state[15];

//***********************************************
//АЦП
//extern short adc_buff[16][16],adc_buff_[16];
extern char adc_cnt,adc_cnt1,adc_ch;

//***********************************************

char flag=0;


extern signed short bat_ver_cnt;
signed short Isumm;
signed short Isumm_;


signed short tst_pwm_u;
signed short tst_pwm_i;

#include <LPC17xx.H>                        /* LPC21xx definitions */



/*
extern void lcd_init(void);
extern void lcd_on(void);
extern void lcd_clear(void);
*/

extern short plazma_adc_cnt;
extern char net_buff_cnt;
extern unsigned short net_buff[32],net_buff_;
extern char rele_stat/*,rele_stat_*/;
extern char bRXIN0;


char cntrl_plazma;
extern char bOUT_FREE2;
extern char /*av_net,*//*av_bat[2],*/av_bps[12],av_inv[6],av_dt[4],av_sk[4];

char content[63];

//const short ptr_bat_zar_cnt[2]={EE_ZAR1_CNT,EE_ZAR2_CNT};


//unsigned short YEAR_AVZ,MONTH_AVZ,DATE_AVZ,HOUR_AVZ,MIN_AVZ,SEC_AVZ;


//**********************************************
//Самокалиброввка
extern signed short samokalibr_cnt;

//**********************************************
//Сообщения
extern char mess[MESS_DEEP],mess_old[MESS_DEEP],mess_cnt[MESS_DEEP];
extern short mess_par0[MESS_DEEP],mess_par1[MESS_DEEP],mess_data[2];


//**********************************************
//Контроль наличия батарей
extern signed short 	main_kb_cnt;
extern signed short 	kb_cnt_1lev;
extern signed short 	kb_cnt_2lev;
extern char 			kb_full_ver;
extern char 			kb_start[2];

//***********************************************
//Управление ШИМом
//extern signed short cntrl_stat;
extern signed short cntrl_stat_old;
extern signed short cntrl_stat_new;
extern signed short Ibmax;


//-----------------------------------------------
//Контроль заряда
char sign_U[2],sign_I[2];
char superviser_cnt;


char plazma_plazma_plazma;

char bRESET=0;
char bRESET_EXT=0;
char ext_can_cnt;
//-----------------------------------------------
//Состояние вводов
signed short vvod_pos;

//-----------------------------------------------
//Плата расширения
unsigned short adc_buff_ext_[3];
unsigned short Uvv[3];
unsigned short Uvv0;
short pos_vent;
short t_ext_can;
char t_ext_can_nd;


//-----------------------------------------------
//Плата расширения 2
char eb2_data[30];
short eb2_data_short[10];
short Uvv_eb2[3],Upes_eb2[3];
short Kvv_eb2[3],Kpes_eb2[3];
//-----------------------------------------------
//Работа со щетчиком
signed long power_summary;
signed short power_current;

//-----------------------------------------------
//Климатконтроль и вентиляторы
signed short main_vent_pos;
signed char t_box_cnt=0;
enum_mixer_vent_stat mixer_vent_stat=mvsOFF;
INT_BOX_TEMPER ibt;
enum_tbatdisable_stat tbatdisable_stat=tbdsON;
enum_tloaddisable_stat tloaddisable_stat=tldsON;
enum_av_tbox_stat av_tbox_stat=atsOFF;
signed short av_tbox_cnt;
//char tbatdisable_cmnd=20,tloaddisable_cmnd=22;
//short tbatdisable_cnt,tloaddisable_cnt;

//-----------------------------------------------
//Состояние контролируемых автоматов нагрузки 
enum_avt_stat avt_stat[12],avt_stat_old[12];

//short sys_plazma,sys_plazma1;

char snmp_plazma;


short plazma_but_an;

char bCAN_OFF;



//-----------------------------------------------
//Гальваника

//-----------------------------------------------
//Состояние БПС
short unet_drv_cnt;
//-----------------------------------------------
//Состояние нагрузки

//-----------------------------------------------
//Управление процессом
enum_work_stat work_stat=wsOFF;
//enum_stat work_stat=wsOFF;
enum_onoff bps_stat=stOFF;

signed short _x_,_xu_;
//**********************************************
//Коэффициенты, отображаемые из EEPROM
signed short Kiload0;
signed short Kiload1;
signed short U_MAX;
signed short U_MIN;
signed short I_MAX;
signed short I_MIN;
signed short T_MAX;
signed short T_SIGN;
signed short I_ug;
signed short I_ug2;
signed short I_ug3;
signed short I_ug_block_cnt;
signed short U_up;
signed short U_up2;
signed short U_up3;
signed short U_up_block_cnt;
signed short U_maxg;
signed short I_maxp;
signed long 	T_PROC_GS;		//установленное время для источника тока, секунды
signed short 	T_PROC_GS_block_cnt;
signed short 	T_PROC_GS_MODE;	//режим времени для источника тока, если 1 то непрерывно
signed long 	T_PROC_PS;		//установленное время для источника напряжения, секунды
signed short 	T_PROC_PS_block_cnt;
signed short 	T_PROC_PS_MODE;	//режим времени для источника напряжения, если 1 то непрерывно
signed long T_PROC_MAX;			//максималное время для установок времен процессов, секунды
signed short TIME_VISION;	//способ отображения времени процесса на экране - прямое(с начала) или обратное(до конца)
signed short TIME_VISION_PULT;//способ отображения времени на пульте - часы-минуты или минуты-секунды
signed short I_MAX_IPS;		//максимальный ток всего источника, =I_MAX*NUMIST
signed short I_MIN_IPS;		//минимальный ток всего источника, =I_MIN*NUMIST
signed short I_LOAD_MODE;	//способ измерения выходного тока - по шунту или как сумму токов источников
enum_main_menu_mode main_menu_mode;	//режим работы главного меню 
enum_restart_enable restart_enable;	//рестарт включен-выключен
enum_rele_log RELE_LOG;			   	//логика работы реле индикации токоограничения
signed short T_DEL_REL_START;		
signed short T_DEL_REL_WRK;			
signed short DELT_REL_U;				
signed short DELT_REL_I;
signed long time_proc;		//время процесса прямое
signed long time_proc_remain;	//время процесса обратное
signed long cap_time_proc;
char can2_plazma;
char plazma_restart;

//-----------------------------------------------
//Данные для передачи по КАН
short can_time;
short can_time_set;
short can_u;
short can_u_set;
short can_i;
short can_i_set;
enum_work_stat can_work_stat;

//-----------------------------------------------
//Управление от пульта
enum_tumbler_stat tumbler_stat=tsOFF,tumbler_stat_old=tsOFF;


signed short plazma_vol_u_0,plazma_vol_u_1;

signed short U_up_d;

signed short I_ug_temp;
signed short U_up_temp;
signed short fiks_stat_I;
signed short fiks_stat_U;

//-----------------------------------------------
enum_viz_stat viz_stat=vsOFF;
signed short viz_stat_cnt=0;

//**********************************************
//Реле токоограничения
signed long delta_U_abs,delta_U_rel,delta_I_abs,delta_I_rel;
char bCURRENT_STAB;
signed short cnt_del_rel;

short main_cnt;

//-----------------------------------------------
//Реверс
enum_rev_stat REV_STAT=rsFF;
short REV_IS_ON;
short AVT_REV_IS_ON;
short AVT_REV_TIME_FF;
short AVT_REV_TIME_REW;
short AVT_REV_TIME_PAUSE;
short AVT_REV_I_NOM_FF;
short AVT_REV_I_NOM_REW;
short AVT_REV_U_NOM_FF;
short AVT_REV_U_NOM_REW;
short time_proc_phase;
enum_proc_phase proc_phase=ppFF;

//-----------------------------------------------
//Проверка конденсатора
short CAP_ZAR_TIME;
short CAP_PAUSE1_TIME;
short CAP_RAZR_TIME;
short CAP_PAUSE2_TIME;
short CAP_MAX_VOLT;
short CAP_WRK_CURR;
short CAP_COUNTER;
short CAP_TIME_SEC;
short CAP_TIME_MIN;
short CAP_TIME_HOUR;


char  bOFF;
char bRAZR;

//-----------------------------------------------
void rtc_init (void) 
{
LPC_RTC->CCR=0x11;
}

//-----------------------------------------------
static void timer_poll () 
{
if (SysTick->CTRL & 0x10000) 
     {
     timer_tick ();
     tick = __TRUE;
     }
}



//-----------------------------------------------
signed short abs_pal(signed short in)
{
if(in<0)return -in;
else return in;
}

//-----------------------------------------------
void init_ETH(void)
{
localm[NETIF_ETH].IpAdr[0]=lc640_read_int(EE_ETH_IP_1);
localm[NETIF_ETH].IpAdr[1]=lc640_read_int(EE_ETH_IP_2);
localm[NETIF_ETH].IpAdr[2]=lc640_read_int(EE_ETH_IP_3);
localm[NETIF_ETH].IpAdr[3]=lc640_read_int(EE_ETH_IP_4);

localm[NETIF_ETH].NetMask[0]=lc640_read_int(EE_ETH_MASK_1);
localm[NETIF_ETH].NetMask[1]=lc640_read_int(EE_ETH_MASK_2);
localm[NETIF_ETH].NetMask[2]=lc640_read_int(EE_ETH_MASK_3);
localm[NETIF_ETH].NetMask[3]=lc640_read_int(EE_ETH_MASK_4);

localm[NETIF_ETH].DefGW[0]=lc640_read_int(EE_ETH_GW_1);
localm[NETIF_ETH].DefGW[1]=lc640_read_int(EE_ETH_GW_2);
localm[NETIF_ETH].DefGW[2]=lc640_read_int(EE_ETH_GW_3);
localm[NETIF_ETH].DefGW[3]=lc640_read_int(EE_ETH_GW_4);

}


//-----------------------------------------------
void ADC_IRQHandler(void) {
LPC_ADC->ADCR &=  ~(7<<24);



adc_self_ch_buff[adc_self_ch_cnt]=(LPC_ADC->ADGDR>>4) & 0xFFF;/* Read Conversion Result             */
adc_self_ch_cnt++;
if(adc_self_ch_cnt<3)
	{
	LPC_ADC->ADCR |=  (1<<24);
	}
else
	{

 
	//SET_REG(LPC_ADC->ADCR,1,24,3);
	}

/*			adc_buff_[0]=AD_last;
			if(AD_last<adc_buff_min[adc_ch])adc_buff_min[adc_ch]=AD_last;
			if(AD_last>adc_buff_max[adc_ch])adc_buff_max[adc_ch]=AD_last;*/
}
/*
//-----------------------------------------------
void def_set(int umax__,int ub0__,int ub20__,int usign__,int imax__,int uob__,int numi,int _uvz)
{
;
lc640_write_int(EE_NUMIST,numi);
lc640_write_int(EE_NUMINV,0);
//lc640_write_int(EE_NUMDT,0);
//lc640_write_int(EE_NUMSK,0);
//lc640_write_int(EE_MAIN_IST,0);
lc640_write_int(EE_PAR,1);
lc640_write_int(EE_TBAT,60);
//lc640_write_int(EE_UMAX,umax__);
lc640_write_int(EE_DU,ub20__/2);
lc640_write_int(EE_UB0,ub0__);
lc640_write_int(EE_UB20,ub20__);
lc640_write_int(EE_TSIGN,70);
lc640_write_int(EE_TMAX,80);
//lc640_write_int(EE_C_BAT,180);
lc640_write_int(EE_USIGN,usign__);
lc640_write_int(EE_UMN,187);
lc640_write_int(EE_ZV_ON,0);
lc640_write_int(EE_IKB,10);
//lc640_write_int(EE_KVZ,1030);
//lc640_write_int(EE_UVZ,_uvz);
lc640_write_int(EE_IMAX,imax__);
lc640_write_int(EE_IMIN,(imax__*8)/10);
//lc640_write_int(EE_APV_ON,apvON);
lc640_write_int(EE_APV_ON1,apvON);
lc640_write_int(EE_APV_ON2,apvON);
lc640_write_int(EE_APV_ON2_TIME,1);
lc640_write_int(EE_IZMAX,160);
lc640_write_int(EE_U0B,uob__);
lc640_write_int(EE_TZAS,3);
lc640_write_int(EE_TBATMAX,50);  
lc640_write_int(EE_TBATSIGN,40);
lc640_write_int(EE_MNEMO_ON,mnON);
lc640_write_int(EE_MNEMO_TIME,30);	
lc640_write_int(EE_AV_OFF_AVT,1);
//lc640_write_int(EE_APV_ON1,apvOFF);



lc640_write_int(EE_TBOXMAX,70);
lc640_write_int(EE_TBOXVENTMAX,60);
lc640_write_int(EE_TBOXREG,25);
lc640_write_int(EE_TLOADDISABLE,80);
//lc640_write_int(EE_TLOADENABLE,70);
//lc640_write_int(EE_TBATDISABLE,91);
//lc640_write_int(EE_TBATENABLE,80);

lc640_write_int(ADR_SK_SIGN[0],0);
lc640_write_int(ADR_SK_REL_EN[0],0);
lc640_write_int(ADR_SK_LCD_EN[0],0xffff);

lc640_write_int(ADR_SK_SIGN[1],0);
lc640_write_int(ADR_SK_REL_EN[1],0);
lc640_write_int(ADR_SK_LCD_EN[1],0xffff);

lc640_write_int(ADR_SK_SIGN[2],0);
lc640_write_int(ADR_SK_REL_EN[2],0);
lc640_write_int(ADR_SK_LCD_EN[2],0xffff);

lc640_write_int(ADR_SK_SIGN[3],0);
lc640_write_int(ADR_SK_REL_EN[3],0);
lc640_write_int(ADR_SK_LCD_EN[3],0xffff);

lc640_write_int(EE_UBM_AV,10);

lc640_write_int(EE_POS_VENT,11);
}  */

//-----------------------------------------------
void can_reset_hndl(void)
{
//if((lc640_read_int(EE_CAN_RESET_CNT)<0)||(lc640_read_int(EE_CAN_RESET_CNT)>2))	lc640_write_int(EE_CAN_RESET_CNT,0);

can_reset_cnt++;

if((can_reset_cnt>=10)&&(lc640_read_int(EE_CAN_RESET_CNT)==0)&&(!(avar_stat&0x0001))&&(!bRESET))
	{
	lc640_write_int(EE_CAN_RESET_CNT,1);
	bRESET=1;
	}

if((can_reset_cnt>=300)&&(lc640_read_int(EE_CAN_RESET_CNT)==1)&&(!(avar_stat&0x0001))&&(!bRESET))
	{
	lc640_write_int(EE_CAN_RESET_CNT,1);
	bRESET=1;
	}

if((main_1Hz_cnt>=360UL)&&(lc640_read_int(EE_CAN_RESET_CNT)!=0))
	{
	lc640_write_int(EE_CAN_RESET_CNT,0);
	}




}

//-----------------------------------------------
void net_drv(void)
{ 
//char temp_;    

	//T_MAX=100;
	//TSIGN=100;
	UMAX=(short)((((signed long)U_MAX)*11L)/10L);
	DU=UMAX;
	TZAS=3;

if(++cnt_net_drv>=24) cnt_net_drv=0; //всего 16 посылок

if(cnt_net_drv<=15) // с 1 по 12 посылки адресные
	{ 
	if(mess_find_unvol(MESS2NET_DRV))
		{
		if(mess_data[0]==PARAM_BPS_NET_OFF)
			{
			//mess_data[1]=1;
			if(sub_ind1==cnt_net_drv)
				{
				return;
				}
			}
		}
	
	//bps[0]._vol_u=800;
	//bps[0]._vol_i=400;

			   
	if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,GETTM,bps[cnt_net_drv]._flags_tu,*((char*)(&bps[cnt_net_drv]._vol_u)),*((char*)((&bps[cnt_net_drv]._vol_u))+1),*((char*)(&bps[cnt_net_drv]._vol_i)),*((char*)((&bps[cnt_net_drv]._vol_i))+1));
     
	if(cnt_net_drv<15)
	     {
	     if(bps[cnt_net_drv]._cnt<CNT_SRC_MAX)
   	 		{    
   	 		bps[cnt_net_drv]._cnt++;
   	 		if( (bps[cnt_net_drv]._cnt>=CNT_SRC_MAX) && (!net_av) && (!(bps[cnt_net_drv]._av&0x08)) && (cnt_net_drv<NUMIST) ) 
   	 			{
   	 			//avar_bps_hndl(cnt_net_drv,3,1);
   	 			}
   	 		}
		else bps[cnt_net_drv]._cnt=CNT_SRC_MAX;
						
		if((bps[cnt_net_drv]._cnt>=3)&&(bps[cnt_net_drv]._cnt_old<3))bps[cnt_net_drv]._cnt_more2++;
		bps[cnt_net_drv]._cnt_old=bps[cnt_net_drv]._cnt;
	     }
	}
/*
else if(cnt_net_drv==15)
	{
     if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,*((char*)(&Uvv[0])),*((char*)((&Uvv[0]))+1),*((char*)(&Uvv[1])),*((char*)((&Uvv[1]))+1),0,bRESET_EXT);
     }

else if(cnt_net_drv==16)
	{
     if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,(char)main_vent_pos,*((char*)(&POWER_CNT_ADRESS)),*((char*)((&POWER_CNT_ADRESS))+1),0,0,0);
     }

else if(cnt_net_drv==10)
	{
     if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     }
*/
else if(cnt_net_drv==17)
	{
     if(!bCAN_OFF)can1_out(0xff,0xff,MEM_KF,*((char*)(&UMAX)),*((char*)((&UMAX))+1),*((char*)(&DU)),*((char*)((&DU))+1),0);
     } 
    
else if(cnt_net_drv==18)
	{
     if(!bCAN_OFF)can1_out(0xff,0xff,MEM_KF4,*((char*)(&T_MAX)),*((char*)((&T_MAX))+1),*((char*)(&T_SIGN)),*((char*)((&T_SIGN))+1),((char)(I_MAX/10)));
     } 
	/*
else if(cnt_net_drv==14)
	{                 
//	can2_out(0xff,0xff,MEM_KF2,*((char*)(&U_INV_MAX)),*((char*)((&U_INV_MAX))+1),*((char*)(&U_INV_MIN)),*((char*)((&U_INV_MIN))+1),(char)T_INV_MAX);
     }
	
	
else if(cnt_net_drv==20)
	{
     if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,*((char*)(&POWER_CNT_ADRESS)),*((char*)((&POWER_CNT_ADRESS))+1),0,0,0,0);
     }
else if(cnt_net_drv==21)
	{
     if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 
else if(cnt_net_drv==22)
	{
     if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 
else if(cnt_net_drv==23)
	{                 
	if(!bCAN_OFF)can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } */	 
}



//-----------------------------------------------
void parol_init(void)
{
parol[0]=0;
parol[1]=0;
parol[2]=0;
sub_ind=0;
}

//-----------------------------------------------
void can_data_hndl(void)
{
if(main_menu_mode==mmmIT)
	{
	can_u_set=U_maxg;
	can_i_set=I_ug;
	can_u=load_U;
	can_i=load_I;
	if(T_PROC_GS_MODE)				//если установлен режим непрерывного времени
		{
		can_time_set=0xffff;
		}
	else
		{
		if(TIME_VISION_PULT)can_time_set=(short)(T_PROC_GS/60);
		else can_time_set=(short)(T_PROC_GS);
		}

	if((TIME_VISION)||(T_PROC_GS_MODE))	//если установлен режим непрерывного времени	или режим прямого отсчета времени
		{
		if(TIME_VISION_PULT)can_time=(short)(time_proc/60);
		else can_time=(short)(time_proc);
		}
	else
		{
		if(TIME_VISION_PULT)can_time=(short)(time_proc_remain/60);
		else can_time=(short)(time_proc_remain);
		}
	can_work_stat=work_stat;



/*	if(work_stat==wsGS)
		{
		if((TIME_VISION)||(T_PROC_GS_MODE))				//если установлен режим непрерывного времени
			{
			if(TIME_VISION_PULT)can_time=(short)(time_proc/60);
			else can_time=(short)(time_proc);
			}
		else
			{
			if(TIME_VISION_PULT)can_time=(short)(time_proc_remain/60);
			else can_time=(short)(time_proc_remain);
			}

		}
	else 
		{
		can_u=U_maxg;
		can_i=I_ug;
			
		if(T_PROC_GS_MODE)				//если установлен режим непрерывного времени
			{
			can_time=0xffff;
			}
		else
			{
			if(TIME_VISION_PULT)can_time=(short)(T_PROC_GS/60);
			else can_time=(short)(T_PROC_GS);
			}
		} */


	}

if(main_menu_mode==mmmIN)
	{
	can_u_set=U_up;
	can_i_set=I_maxp;
	can_u=load_U;
	can_i=load_I;
	if(T_PROC_PS_MODE)				//если установлен режим непрерывного времени
		{
		can_time_set=0xffff;
		}
	else
		{
		if(TIME_VISION_PULT)can_time_set=(short)(T_PROC_PS/60);
		else can_time_set=(short)(T_PROC_PS);
		}

	if((TIME_VISION)||(T_PROC_PS_MODE))	//если установлен режим непрерывного времени	или режим прямого отсчета времени
		{
		if(TIME_VISION_PULT)can_time=(short)(time_proc/60);
		else can_time=(short)(time_proc);
		}
	else
		{
		if(TIME_VISION_PULT)can_time=(short)(time_proc_remain/60);
		else can_time=(short)(time_proc_remain);
		}
	can_work_stat=work_stat;
	}

//can_time=1357;
}

//-----------------------------------------------
void bitmap_hndl(void)
{
short x,ii,i;
unsigned int ptr_bitmap;
//static char ptr_cnt,ptr_cnt1,ptr_cnt2,ptr_cnt3,ptr_cnt4;

for(ii=0;ii<488;ii++)
	{
	lcd_bitmap[ii]=0x00;
	}

	{
	for(i=0;i<4;i++)
		{
		ptr_bitmap=122*(unsigned)i;
		for(x=(20*i);x<((20*i)+20);x++)
	 		{

			if(lcd_buffer[x]==94)
				{
				lcd_bitmap[ptr_bitmap++]=0x7e;
				lcd_bitmap[ptr_bitmap++]=0x42;
				lcd_bitmap[ptr_bitmap++]=0x5a;
				lcd_bitmap[ptr_bitmap++]=0x5a;
				lcd_bitmap[ptr_bitmap++]=0x42;
				lcd_bitmap[ptr_bitmap++]=0x7e;
				}
			else
				{
				lcd_bitmap[ptr_bitmap++]=caracter[(unsigned)lcd_buffer[x]*6];
				lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+1];
				lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+2];
				lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+3];
				lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+4];
				lcd_bitmap[ptr_bitmap++]=caracter[((unsigned)lcd_buffer[x]*6)+5];
				}
			} 
		}
	}	
}

//-----------------------------------------------
void ind_hndl(void)
{
//const char* ptr;
const char* ptrs[40];
//const char* sub_ptrs[40];
static char sub_cnt,sub_cnt1;
char i,sub_cnt_max;
char ii_;
static char ii_cnt/*,cnt_ind_bat*/;


	   
sub_cnt_max=5;
i=0;

/*	      
if(spc_stat==spcVZ)
	{
	sub_ptrs[i++]=		" Выравн.заряд  X:0x ";
	sub_cnt_max++;
	}*/

cnt_of_slave=NUMIST+NUMINV;



sub_cnt1++;	
if(sub_cnt1>=20)
	{
	sub_cnt1=0;
	sub_cnt++;
	if(sub_cnt>=sub_cnt_max)
		{
		sub_cnt=0;
		}
	}


if(ind==iMn)
	{
	signed long temp_SL_U;
	if(work_stat==wsCAP)
		{
		ptrs[0]=		"   ИСПЫТАНИЕ ФАЗА ! ";
		ptrs[1]=		" Iу    +А Umax    @B";
		ptrs[2]=		" I     #А U       $B";
		ptrs[3]=		" Цикл N   ^   0T:0s ";

		bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);

		if(cap_time_proc<CAP_ZAR_TIME) sub_bgnd("A",'!',0);
		else if(cap_time_proc<(CAP_ZAR_TIME+CAP_PAUSE1_TIME)) sub_bgnd("B",'!',0);
		else if(cap_time_proc<(CAP_ZAR_TIME+CAP_PAUSE1_TIME+CAP_RAZR_TIME)) sub_bgnd("C",'!',0);
		else if(cap_time_proc<(CAP_ZAR_TIME+CAP_PAUSE1_TIME+CAP_RAZR_TIME+CAP_PAUSE2_TIME)) sub_bgnd("D",'!',0);
		
		int2lcd(CAP_WRK_CURR,'+',0);
		int2lcd(CAP_MAX_VOLT,'@',0);
		int2lcd(load_I/10,'#',0);
		int2lcd(load_U/10,'$',0);
		int2lcd(CAP_COUNTER+1,'^',0);
		int2lcd((cap_time_proc/10)%60,'s',0);
		int2lcd((cap_time_proc/10)/60,'T',0);
		}
	else if(main_menu_mode==mmmIT)
		{
		if(work_stat!=wsGS)	{	 	
	 		ptrs[0]=		" Источник тока  ^   ";
			
			if(REV_IS_ON) {
				if(AVT_REV_IS_ON) {
					ptrs[0]=		" Источник тока  ^   ";
				} else {
					if(REV_STAT==rsFF) ptrs[0]=		" Источник тока  ^>>>";
					if(REV_STAT==rsREW) ptrs[0]=		" Источник тока  ^<<<";
				}
			}
		}
		else if(work_stat==wsGS)	{		ptrs[0]=	" Источник тока      ";
			if((REV_IS_ON)&&(AVT_REV_IS_ON)&&((proc_phase==ppFF_P_REW)||(proc_phase==ppREW_P_FF))) {
				if(ind_fl_cnt&0x02)		ptrs[0]=	" Источник тока  ^ <>";
				else 				ptrs[0]=	" Источник тока      ";
			} else if(((REV_IS_ON)&&(REV_STAT==rsFF))/*||(!REV_IS_ON)*/) {
				if(ind_fl_cnt==0)	  	ptrs[0]=	" Источник тока  ^>  ";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник тока  ^>> ";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник тока  ^>>>";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник тока  ^ >>";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник тока  ^  >";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник тока  ^   ";
			} else if((REV_IS_ON)&&(REV_STAT==rsREW)) {
				if(ind_fl_cnt==0)		ptrs[0]=	" Источник тока  ^  <";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник тока  ^ <<";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник тока  ^<<<";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник тока  ^<< ";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник тока  ^<  ";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник тока  ^   ";
			}  
		}
		/*if((bFL_REV)&&(REV_IS_ON))
			{
			if(REV_STAT==rsFF)	ptrs[0]=		" Реверс         ВКЛ.";
			else 			ptrs[0]=		" Реверс        ВЫКЛ."; 
			}*/

		//if((work_stat==wsGS)&&(!bFL34))
		//ptrs[0]=		"    {    }    [    ]";
		//ptrs[0]=		"                    ";
	  	ptrs[1]=		" Iу    +А Umax    @B";
	   	ptrs[2]=		" Длит-сть.  0t:0T:0s";
		if(work_stat==wsGS)
		ptrs[2]=		"      0t:0T:0s      ";
	   	ptrs[3]=		" I     #А U       $B";
		ptrs[4]=		" Uмax.ист.тока    {В";
	   	ptrs[5]=		" Выход              ";
		ptrs[6]=		" Установки          ";
	   	ptrs[7]=		" Выпрямители        ";
	
	
		if(sub_ind-index_set>3)index_set=sub_ind-3;
		else if (sub_ind<index_set)index_set=sub_ind;
		
		if(unet_drv_cnt>15)	bgnd_par(	"  Авария питающей   ",
								"      сети!!!!      ",
								"  Отсутствует одна  ",
								" или несколько фаз. ");
		else 
			{
			bgnd_par(ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);
			pointer_set(0);
			}
	   	

		if((!REV_IS_ON)||(!AVT_REV_IS_ON))sub_bgnd(" ",'^',0);

		//if(fiks_temp_I==0)int2lcd(I_ug,'+',1);
		//else int2lcd(I_ug_fiks,'+',1);
		if(I_ug_temp<1000) {
			int2lcd(I_ug_temp,'+',1);
		} else {
			int2lcd(I_ug_temp/10,'+',0);
		}
		
	   	if(load_I<1000) {
			int2lcd(load_I,'#',1);
		} else {
			int2lcd(load_I/10,'#',0);
		}

		if(load_U<1000) {
			int2lcd(load_U,'$',1);
		} else {
			int2lcd(load_U/10,'$',0);
		}

		if(U_maxg<1000) {
			int2lcd(U_maxg,'{',1);
			int2lcd(U_maxg,'@',1);
		} else {
			int2lcd(U_maxg/10,'{',0);
			int2lcd(U_maxg/10,'@',0);
		}
		
	//	if(index_set<=2)
			{
			if(work_stat==wsGS)
				{
				if((TIME_VISION)||(T_PROC_GS_MODE))
					{
					int2lcd(time_proc%60,'s',0);
					int2lcd((time_proc/60)%60,'T',0);
					int2lcd(time_proc/3600,'t',0);
					}
				else
					{
					int2lcd(time_proc_remain%60,'s',0);
					int2lcd((time_proc_remain/60)%60,'T',0);
					int2lcd(time_proc_remain/3600,'t',0);
					}
				if(bFL2)
					{
					sub_bgnd(" ",':',0);
					sub_bgnd(" ",':',0);
					}
				}
			else 
				{
				if(T_PROC_GS_MODE)				//если установлен режим непрерывного времени
					{
					sub_bgnd("непрерывно",'t',-3);
					}
				else
					{
					int2lcd(T_PROC_GS%60,'s',0);
					int2lcd((T_PROC_GS/60)%60,'T',0);
					int2lcd(T_PROC_GS/3600,'t',0);
					}
				}
			}
	

		//int2lcdyx(fiks_stat_I,0,4,0);
		//int2lcdyx(bps[1]._vol_i,0,8,0);
		//int2lcdyx(_x_,0,19,0);
	/*	int2lcdyx(_xu_,0,14,0);*/
		//int2lcdyx(can2_plazma,0,19,0);
		//int2lcd(bps[0]._vol_i,'{',0);
		//int2lcd(bps[1]._vol_i,'}',0);
		//int2lcd(bps[0]._vol_u,'[',0);
		//int2lcd(bps[1]._vol_u,']',0);
		}
	else if(main_menu_mode==mmmIN)
		{
		if(work_stat!=wsPS)	{	 	
	 		ptrs[0]=		" Источник напр. ^   ";
			
			if(REV_IS_ON) {
				if(AVT_REV_IS_ON) {
					ptrs[0]=		" Источник напр. ^   ";
				} else {
					if(REV_STAT==rsFF) ptrs[0]=		" Источник напр. ^>>>";
					if(REV_STAT==rsREW) ptrs[0]=		" Источник напр. ^<<<";
				}
			}
		}
		else if(work_stat==wsPS)	{		ptrs[0]=	" Источник напр.     ";
			if((REV_IS_ON)&&(AVT_REV_IS_ON)&&((proc_phase==ppFF_P_REW)||(proc_phase==ppREW_P_FF))) {
				if(ind_fl_cnt&0x02)		ptrs[0]=	" Источник напр. ^ <>";
				else 				ptrs[0]=	" Источник напр.     ";
			} else if(((REV_IS_ON)&&(REV_STAT==rsFF))/*||(!REV_IS_ON)*/) {
				if(ind_fl_cnt==0)	  	ptrs[0]=	" Источник напр. ^>  ";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник напр. ^>> ";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник напр. ^>>>";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник напр. ^ >>";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник напр. ^  >";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник напр. ^   ";
			} else if((REV_IS_ON)&&(REV_STAT==rsREW)) {
				if(ind_fl_cnt==0)		ptrs[0]=	" Источник напр. ^  <";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник напр. ^ <<";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник напр. ^<<<";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник напр. ^<< ";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник напр. ^<  ";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник напр. ^   ";
			}  
		}

 /*	 	ptrs[0]=		" Источник напряж.   ";
		if((bFL_REV)&&(REV_IS_ON))
			{
			if(REV_STAT==rsFF)	ptrs[0]=		" Реверс         ВКЛ.";
			else 			ptrs[0]=		" Реверс        ВЫКЛ."; 
			}
		if((work_stat==wsPS)&&(!bFL34))
		ptrs[0]=		"                    "; */
	  	ptrs[1]=		" Uу    %B Imax    }A";
	   	ptrs[2]=		" Длит-сть.  0t:0T:0s";
		if(work_stat==wsPS)
		ptrs[2]=		"      0t:0T:0s      ";
	   	ptrs[3]=		" U     &B I       *A";
		ptrs[4]=		" Iмax.ист.напр.   }A";
	   	ptrs[5]=		" Выход              ";
		ptrs[6]=		" Установки          ";
	   	ptrs[7]=		" Выпрямители        ";
	
	
		if(sub_ind-index_set>3)index_set=sub_ind-3;
		else if (sub_ind<index_set)index_set=sub_ind;
		
		if(unet_drv_cnt>15)	bgnd_par(	"  Авария питающей   ",
								"      сети!!!!      ",
								"  Отсутствует одна  ",
								" или несколько фаз. ");
		else 
			{
			bgnd_par(ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);
			pointer_set(0);
			}

		if((!REV_IS_ON)||(!AVT_REV_IS_ON))sub_bgnd(" ",'^',0);
	
	/*	if(work_stat==wsOFF)
			{
			if(bFL2)int2lcd(I_ug,'!',1);
			else sub_bgnd("     ",'!',-2);
			}
		else int2lcd(I_ug,'!',1);
	
		if(work_stat==wsOFF)
			{
			if(bFL2)int2lcd(U_up,'%',1);
			else sub_bgnd("     ",'%',-2);
			}
		else int2lcd(U_up,'%',1); */
	   	
		//int2lcd(I_ug,'+',1);
		//int2lcd(U_maxg,'@',1);
	   	//int2lcd(load_I,'#',1);
		//int2lcd(load_U,'$',1);
		if(U_up_temp<1000) {
			int2lcd(U_up_temp,'%',1);
		} else {
			int2lcd(U_up_temp/10,'%',0);
		}
		//int2lcd(I_maxp,'^',1);
	   	if(load_U<1000) {
			int2lcd(load_U,'&',1); 
		} else {
			int2lcd(load_U/10,'&',0);
		}
		
		if(load_I<1000)int2lcd(load_I,'*',1);
		else int2lcd(load_I/10,'*',0);
		//int2lcd(U_maxg,'<',1);

	/*	if(U_maxg<1000) {
			int2lcd(U_maxg,'<',1);
			int2lcd(U_maxg,'@',1);
		} else {
			int2lcd(U_maxg/10,'<',0);
			int2lcd(U_maxg/10,'@',0);
		}*/


		//int2lcd(I_maxp,'>',1);
		if(I_maxp<1000) {
			int2lcd(I_maxp,'}',1);
			int2lcd(I_maxp,'}',1);
		} else {
			int2lcd(I_maxp/10,'}',0);
			int2lcd(I_maxp/10,'}',0);
		}	
			{
			if(work_stat==wsPS)
				{
				if((TIME_VISION)||(T_PROC_PS_MODE))
					{
					int2lcd(time_proc%60,'s',0);
					int2lcd((time_proc/60)%60,'T',0);
					int2lcd(time_proc/3600,'t',0);
					}
				else
					{
					int2lcd(time_proc_remain%60,'s',0);
					int2lcd((time_proc_remain/60)%60,'T',0);
					int2lcd(time_proc_remain/3600,'t',0);
					}
				if(bFL2)
					{
					sub_bgnd(" ",':',0);
					sub_bgnd(" ",':',0);
					}
				}
			else 
				{
				if(T_PROC_PS_MODE)				//если установлен режим непрерывного времени
					{
					sub_bgnd("непрерывно",'t',-3);
					}
				else
					{
					int2lcd(T_PROC_PS%60,'s',0);
					int2lcd((T_PROC_PS/60)%60,'T',0);
					int2lcd(T_PROC_PS/3600,'t',0);
					}
				}
			}
	
	/*	int2lcdyx(bps[0]._vol_u,0,4,0);
		int2lcdyx(bps[0]._vol_i,0,8,0);
		int2lcdyx(bps[0]._flags_tu,0,0,0);
		int2lcdyx(_xu_,0,14,0);*/
		//int2lcdyx(can2_plazma,0,19,0);
		//int2lcd(bps[0]._vol_i,'{',0);
		//int2lcd(bps[1]._vol_i,'}',0);
		//int2lcd(bps[0]._vol_u,'[',0);
		//int2lcd(bps[1]._vol_u,']',0);
		}
	else if(main_menu_mode==mmmITIN)
		{
			 	
/*	 	ptrs[0]=		" Источник тока      ";
		if((bFL_REV)&&(REV_IS_ON))
			{
			if(REV_STAT==rsFF)	ptrs[0]=		" Реверс         ВКЛ.";
			else 			ptrs[0]=		" Реверс        ВЫКЛ."; 
			}
		if((work_stat==wsGS)&&(!bFL34))
		//ptrs[0]=		"    {    }    [    ]";
		ptrs[0]=		"                    ";*/

		if(work_stat!=wsGS)	{	 	
	 		ptrs[0]=		" Источник тока  ^   ";
			
			if(REV_IS_ON) {
				if(AVT_REV_IS_ON) {
					ptrs[0]=		" Источник тока  ^>>>";
				} else {
					if(REV_STAT==rsFF) ptrs[0]=		" Источник тока  ^>>>";
					if(REV_STAT!=rsFF) ptrs[0]=		" Источник тока  ^<<<";
				}
			}
		}
		else if(work_stat==wsGS)	{		ptrs[0]=	" Источник тока      ";
			if(((REV_IS_ON)&&(REV_STAT==rsFF))/*||(!REV_IS_ON)*/) {
				if(ind_fl_cnt==0)	  	ptrs[0]=	" Источник тока  ^>  ";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник тока  ^>> ";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник тока  ^>>>";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник тока  ^ >>";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник тока  ^  >";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник тока  ^   ";
			} else if((REV_IS_ON)&&(REV_STAT==rsREW)) {
				if(ind_fl_cnt==0)		ptrs[0]=	" Источник тока  ^  <";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник тока  ^ <<";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник тока  ^<<<";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник тока  ^<< ";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник тока  ^<  ";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник тока  ^   ";
			}
		}

	  	ptrs[1]=		" Iу    +А Umax    @B";
	   	ptrs[2]=		" Длит-сть.  0t:0T:0s";
		if(work_stat==wsGS)
		ptrs[2]=		"      0t:0T:0s      ";
	   	ptrs[3]=		" I     #А U       $B";
/*	 	ptrs[4]=		" Источник напряж.   ";
		if((bFL_REV)&&(REV_IS_ON))
			{
			if(REV_STAT==rsFF)	ptrs[4]=		" Реверс         ВКЛ.";
			else 			ptrs[4]=		" Реверс        ВЫКЛ."; 
			}*/
		if(work_stat!=wsPS)	{	 	
	 		ptrs[4]=		" Источник напр. ^   ";
			
			if(REV_IS_ON) {
				if(AVT_REV_IS_ON) {
					ptrs[4]=		" Источник напр. ^>>>";
				} else {
					if(REV_STAT==rsFF) ptrs[4]=		" Источник напр. ^>>>";
					if(REV_STAT!=rsFF) ptrs[4]=		" Источник напр. ^<<<";
				}
			}
		}
		else if(work_stat==wsPS)	{		ptrs[4]=	" Источник напр.     ";
			if(((REV_IS_ON)&&(REV_STAT==rsFF))/*||(!REV_IS_ON)*/) {
				if(ind_fl_cnt==0)	  	ptrs[4]=	" Источник напр. ^>  ";
				else if(ind_fl_cnt==1)	ptrs[4]=	" Источник напр. ^>> ";
				else if(ind_fl_cnt==2)	ptrs[4]=	" Источник напр. ^>>>";
				else if(ind_fl_cnt==3)	ptrs[4]=	" Источник напр. ^ >>";
				else if(ind_fl_cnt==4)	ptrs[4]=	" Источник напр. ^  >";
				else if(ind_fl_cnt==5)	ptrs[4]=	" Источник напр. ^   ";
			} else if((REV_IS_ON)&&(REV_STAT==rsREW)) {
				if(ind_fl_cnt==0)		ptrs[4]=	" Источник напр. ^  <";
				else if(ind_fl_cnt==1)	ptrs[4]=	" Источник напр. ^ <<";
				else if(ind_fl_cnt==2)	ptrs[4]=	" Источник напр. ^<<<";
				else if(ind_fl_cnt==3)	ptrs[4]=	" Источник напр. ^<< ";
				else if(ind_fl_cnt==4)	ptrs[4]=	" Источник напр. ^<  ";
				else if(ind_fl_cnt==5)	ptrs[4]=	" Источник напр. ^   ";
			}
		}

		if((work_stat==wsPS)&&(!bFL34))
		ptrs[4]=		"                    ";
	  	ptrs[5]=		" Uу    %B Imax    }A";
	   	ptrs[6]=		" Длит-сть.  0t:0T:0s";
		if(work_stat==wsPS)
		ptrs[6]=		"      0t:0T:0s      ";
	   	ptrs[7]=		" U     &B I       *A";
		ptrs[8]=		" Uмax.ист.тока    {В";
		ptrs[9]=		" Iмax.ист.напр.   }A";
	   	ptrs[10]=		" Выход              ";
		ptrs[11]=		" Установки          ";
	   	ptrs[12]=		" Выпрямители        ";
	
	
		if(sub_ind-index_set>3)index_set=sub_ind-3;
		else if (sub_ind<index_set)index_set=sub_ind;
		
		if(unet_drv_cnt>15)	bgnd_par(	"  Авария питающей   ",
								"      сети!!!!      ",
								"  Отсутствует одна  ",
								" или несколько фаз. ");
		else 
			{
			bgnd_par(ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);
			pointer_set(0);
			}
		if((!REV_IS_ON)||(!AVT_REV_IS_ON))sub_bgnd(" ",'^',0);
	/*	if(work_stat==wsOFF)
			{
			if(bFL2)int2lcd(I_ug,'!',1);
			else sub_bgnd("     ",'!',-2);
			}
		else int2lcd(I_ug,'!',1);
	
		if(work_stat==wsOFF)
			{
			if(bFL2)int2lcd(U_up,'%',1);
			else sub_bgnd("     ",'%',-2);
			}
		else int2lcd(U_up,'%',1); */
	   	
		if(I_ug_temp<1000)int2lcd(I_ug_temp,'+',1);
		else int2lcd(I_ug_temp/10,'+',0);
		//int2lcd(U_maxg,'@',1);
	   	if(load_I<1000) {
			int2lcd(load_I,'#',1);
			int2lcd(load_I,'*',1);
		} else {
			int2lcd(load_I/10,'#',0);
			int2lcd(load_I/10,'*',0);
		}
		//int2lcd(load_U,'$',1);
	   	//int2lcd(U_up,'%',1);
		
	   	//int2lcd(load_U,'&',1);

		if(U_up_temp<1000) {
			int2lcd(U_up_temp,'%',1);
		} else {
			int2lcd(U_up_temp/10,'%',0);
		}
		//int2lcd(I_maxp,'^',1);
	   	if(load_U<1000) {
			int2lcd(load_U,'&',1);
			int2lcd(load_U,'$',1); 
		} else {
			int2lcd(load_U/10,'&',0);
			int2lcd(load_U/10,'$',0);
		}
		//int2lcd(load_I,'*',1);
		//int2lcd(U_maxg,'<',1);
		if(I_maxp<1000) {
			int2lcd(I_maxp,'}',1);
			int2lcd(I_maxp,'}',1);
		} else {
			int2lcd(I_maxp/10,'}',0);
			int2lcd(I_maxp/10,'}',0);
		}

		if(U_maxg<1000) {
			int2lcd(U_maxg,'{',1);
			int2lcd(U_maxg,'@',1);
		} else {
			int2lcd(U_maxg/10,'{',0);
			int2lcd(U_maxg/10,'@',0);
		}

	
		if(index_set<=2)
			{
			if(work_stat==wsGS)
				{
				if((TIME_VISION)||(T_PROC_GS_MODE))
					{
					int2lcd(time_proc%60,'s',0);
					int2lcd((time_proc/60)%60,'T',0);
					int2lcd(time_proc/3600,'t',0);
					}
				else
					{
					int2lcd(time_proc_remain%60,'s',0);
					int2lcd((time_proc_remain/60)%60,'T',0);
					int2lcd(time_proc_remain/3600,'t',0);
					}
				if(bFL2)
					{
					sub_bgnd(" ",':',0);
					sub_bgnd(" ",':',0);
					}
				}
			else 
				{
				if(T_PROC_GS_MODE)				//если установлен режим непрерывного времени
					{
					sub_bgnd("непрерывно",'t',-3);
					}
				else
					{
					int2lcd(T_PROC_GS%60,'s',0);
					int2lcd((T_PROC_GS/60)%60,'T',0);
					int2lcd(T_PROC_GS/3600,'t',0);
					}
				}
			}
		else 
			{
			if(work_stat==wsPS)
				{
				if((TIME_VISION)||(T_PROC_PS_MODE))
					{
					int2lcd(time_proc%60,'s',0);
					int2lcd((time_proc/60)%60,'T',0);
					int2lcd(time_proc/3600,'t',0);
					}
				else
					{
					int2lcd(time_proc_remain%60,'s',0);
					int2lcd((time_proc_remain/60)%60,'T',0);
					int2lcd(time_proc_remain/3600,'t',0);
					}
				if(bFL2)
					{
					sub_bgnd(" ",':',0);
					sub_bgnd(" ",':',0);
					}
				}
			else 
				{
				if(T_PROC_PS_MODE)				//если установлен режим непрерывного времени
					{
					sub_bgnd("непрерывно",'t',-3);
					}
				else
					{
					int2lcd(T_PROC_PS%60,'s',0);
					int2lcd((T_PROC_PS/60)%60,'T',0);
					int2lcd(T_PROC_PS/3600,'t',0);
					}				
				}
			}
	
	/*	int2lcdyx(bps[0]._vol_u,0,4,0);
		int2lcdyx(bps[0]._vol_i,0,8,0);
		int2lcdyx(bps[0]._flags_tu,0,0,0);
		int2lcdyx(_xu_,0,14,0);*/
		//int2lcdyx(can2_plazma,0,19,0);
		//int2lcd(bps[0]._vol_i,'{',0);
		//int2lcd(bps[1]._vol_i,'}',0);
		//int2lcd(bps[0]._vol_u,'[',0);
		//int2lcd(bps[1]._vol_u,']',0);
		}
	else 
		{
/*	 	ptrs[0]=		" Источник напряж.   ";
		if((bFL_REV)&&(REV_IS_ON))
			{
			if(REV_STAT==rsFF)	ptrs[0]=		" Реверс         ВКЛ.";
			else 			ptrs[0]=		" Реверс        ВЫКЛ."; 
			}
		if((work_stat==wsPS)&&(!bFL34))
		ptrs[0]=		"                    ";*/

		if(work_stat!=wsPS)	{	 	
	 		ptrs[0]=		" Источник напр. ^   ";
			
			if(REV_IS_ON) {
				if(AVT_REV_IS_ON) {
					ptrs[0]=		" Источник напр. ^>>>";
				} else {
					if(REV_STAT==rsFF) ptrs[0]=		" Источник напр. ^>>>";
					if(REV_STAT!=rsFF) ptrs[0]=		" Источник напр. ^<<<";
				}
			}
		}
		else if(work_stat==wsPS)	{		ptrs[0]=	" Источник напр.     ";
			if(((REV_IS_ON)&&(REV_STAT==rsFF))/*||(!REV_IS_ON)*/) {
				if(ind_fl_cnt==0)	  	ptrs[0]=	" Источник напр. ^>  ";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник напр. ^>> ";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник напр. ^>>>";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник напр. ^ >>";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник напр. ^  >";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник напр. ^   ";
			} else if((REV_IS_ON)&&(REV_STAT==rsREW)) {
				if(ind_fl_cnt==0)		ptrs[0]=	" Источник напр. ^  <";
				else if(ind_fl_cnt==1)	ptrs[0]=	" Источник напр. ^ <<";
				else if(ind_fl_cnt==2)	ptrs[0]=	" Источник напр. ^<<<";
				else if(ind_fl_cnt==3)	ptrs[0]=	" Источник напр. ^<< ";
				else if(ind_fl_cnt==4)	ptrs[0]=	" Источник напр. ^<  ";
				else if(ind_fl_cnt==5)	ptrs[0]=	" Источник напр. ^   ";
			}
		}



	  	ptrs[1]=		" Uу    %B Imax    }A";
	   	ptrs[2]=		" Длит-сть.  0t:0T:0s";
		if(work_stat==wsPS)
		ptrs[2]=		"      0t:0T:0s      ";
	   	ptrs[3]=		" U     &B I       *A";			 	
/*	 	ptrs[4]=		" Источник тока      ";
		if((bFL_REV)&&(REV_IS_ON))
			{
			if(REV_STAT==rsFF)	ptrs[4]=		" Реверс         ВКЛ.";
			else 			ptrs[4]=		" Реверс        ВЫКЛ."; 
			}		
		if((work_stat==wsGS)&&(!bFL34))
		//ptrs[0]=		"    {    }    [    ]";
		ptrs[4]=		"                    ";*/
		if(work_stat!=wsGS)	{	 	
	 		ptrs[4]=		" Источник тока  ^   ";
			
			if(REV_IS_ON) {
				if(AVT_REV_IS_ON) {
					ptrs[4]=		" Источник тока  ^>>>";
				} else {
					if(REV_STAT==rsFF) ptrs[4]=		" Источник тока  ^>>>";
					if(REV_STAT!=rsFF) ptrs[4]=		" Источник тока  ^<<<";
				}
			}
		}
		else if(work_stat==wsGS)	{		ptrs[4]=	" Источник тока      ";
			if(((REV_IS_ON)&&(REV_STAT==rsFF))/*||(!REV_IS_ON)*/) {
				if(ind_fl_cnt==0)	  	ptrs[4]=	" Источник тока  ^>  ";
				else if(ind_fl_cnt==1)	ptrs[4]=	" Источник тока  ^>> ";
				else if(ind_fl_cnt==2)	ptrs[4]=	" Источник тока  ^>>>";
				else if(ind_fl_cnt==3)	ptrs[4]=	" Источник тока  ^ >>";
				else if(ind_fl_cnt==4)	ptrs[4]=	" Источник тока  ^  >";
				else if(ind_fl_cnt==5)	ptrs[4]=	" Источник тока  ^   ";
			} else if((REV_IS_ON)&&(REV_STAT==rsREW)) {
				if(ind_fl_cnt==0)		ptrs[4]=	" Источник тока  ^  <";
				else if(ind_fl_cnt==1)	ptrs[4]=	" Источник тока  ^ <<";
				else if(ind_fl_cnt==2)	ptrs[4]=	" Источник тока  ^<<<";
				else if(ind_fl_cnt==3)	ptrs[4]=	" Источник тока  ^<< ";
				else if(ind_fl_cnt==4)	ptrs[4]=	" Источник тока  ^<  ";
				else if(ind_fl_cnt==5)	ptrs[4]=	" Источник тока  ^   ";
			}
		}
	  	ptrs[5]=		" Iу    +А Umax    @B";
	   	ptrs[6]=		" Длит-сть.  0t:0T:0s";
		if(work_stat==wsGS)
		ptrs[6]=		"      0t:0T:0s      ";
	   	ptrs[7]=		" I     #А U       $B";
		ptrs[8]=		" Uмax.ист.тока    {В";
		ptrs[9]=		" Iмax.ист.напр.   }A";
	   	ptrs[10]=		" Выход              ";
		ptrs[11]=		" Установки          ";
	   	ptrs[12]=		" Выпрямители        ";
	
	
		if(sub_ind-index_set>3)index_set=sub_ind-3;
		else if (sub_ind<index_set)index_set=sub_ind;
		
		if(unet_drv_cnt>15)	bgnd_par(	"  Авария питающей   ",
								"      сети!!!!      ",
								"  Отсутствует одна  ",
								" или несколько фаз. ");
		else 
			{
			bgnd_par(ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2],ptrs[index_set+3]);
			pointer_set(0);
			}
	
	/*	if(work_stat==wsOFF)
			{
			if(bFL2)int2lcd(I_ug,'!',1);
			else sub_bgnd("     ",'!',-2);
			}
		else int2lcd(I_ug,'!',1);
	
		if(work_stat==wsOFF)
			{
			if(bFL2)int2lcd(U_up,'%',1);
			else sub_bgnd("     ",'%',-2);
			}
		else int2lcd(U_up,'%',1); */

		if((!REV_IS_ON)||(!AVT_REV_IS_ON))sub_bgnd(" ",'^',0);
	   	
		if(I_ug_temp<1000)int2lcd(I_ug_temp,'+',1);
		else int2lcd(I_ug_temp/10,'+',0);
		//int2lcd(U_maxg,'@',1);
	   	if(load_I<1000) {
			int2lcd(load_I,'#',1);
			int2lcd(load_I,'*',1);
		} else {
			int2lcd(load_I/10,'#',0);
			int2lcd(load_I/10,'*',0);
		}
		//int2lcd(load_U,'$',1);
	   	//int2lcd(U_up,'%',1);
		if(U_up_temp<1000) {
			int2lcd(U_up_temp,'%',1);
		} else {
			int2lcd(U_up_temp/10,'%',0);
		}
		//int2lcd(I_maxp,'^',1);
	   	//int2lcd(load_U,'&',1);
		if(load_I<1000) {
			int2lcd(load_I,'#',1);
			int2lcd(load_I,'*',1);
		} else {
			int2lcd(load_I/10,'#',0);
			int2lcd(load_I/10,'*',0);
		}
		//int2lcd(U_maxg,'<',1);
		//int2lcd(I_maxp,'>',1);

		if(load_U<1000) {
			int2lcd(load_U,'&',1);
			int2lcd(load_U,'$',1); 
		} else {
			int2lcd(load_U/10,'&',0);
			int2lcd(load_U/10,'$',0);
		}

		if(U_maxg<1000) {
			int2lcd(U_maxg,'{',1);
			int2lcd(U_maxg,'@',1);
		} else {
			int2lcd(U_maxg/10,'{',0);
			int2lcd(U_maxg/10,'@',0);
		}

		if(I_maxp<1000) {
			int2lcd(I_maxp,'}',1);
			int2lcd(I_maxp,'}',1);
		} else {
			int2lcd(I_maxp/10,'}',0);
			int2lcd(I_maxp/10,'}',0);
		}

	
		if(index_set<=2)
			{
			if(work_stat==wsPS)
				{
				if((TIME_VISION)||(T_PROC_PS_MODE))
					{
					int2lcd(time_proc%60,'s',0);
					int2lcd((time_proc/60)%60,'T',0);
					int2lcd(time_proc/3600,'t',0);
					}
				else
					{
					int2lcd(time_proc_remain%60,'s',0);
					int2lcd((time_proc_remain/60)%60,'T',0);
					int2lcd(time_proc_remain/3600,'t',0);
					}
				if(bFL2)
					{
					sub_bgnd(" ",':',0);
					sub_bgnd(" ",':',0);
					}
				}
			else 
				{
				if(T_PROC_PS_MODE)				//если установлен режим непрерывного времени
					{
					sub_bgnd("непрерывно",'t',-3);
					}
				else
					{
					int2lcd(T_PROC_PS%60,'s',0);
					int2lcd((T_PROC_PS/60)%60,'T',0);
					int2lcd(T_PROC_PS/3600,'t',0);
					}				
				}
			}
		else 
			{
			if(work_stat==wsGS)
				{
				if((TIME_VISION)||(T_PROC_GS_MODE))
					{
					int2lcd(time_proc%60,'s',0);
					int2lcd((time_proc/60)%60,'T',0);
					int2lcd(time_proc/3600,'t',0);
					}
				else
					{
					int2lcd(time_proc_remain%60,'s',0);
					int2lcd((time_proc_remain/60)%60,'T',0);
					int2lcd(time_proc_remain/3600,'t',0);
					}
				if(bFL2)
					{
					sub_bgnd(" ",':',0);
					sub_bgnd(" ",':',0);
					}
				}
			else 
				{
				if(T_PROC_GS_MODE)				//если установлен режим непрерывного времени
					{
					sub_bgnd("непрерывно",'t',-3);
					}
				else
					{
					int2lcd(T_PROC_GS%60,'s',0);
					int2lcd((T_PROC_GS/60)%60,'T',0);
					int2lcd(T_PROC_GS/3600,'t',0);
					}
				}
			}
	

	

	/*	//int2lcdyx(can2_plazma,0,19,0);*/
		//int2lcd(bps[0]._vol_i,'{',0);
		//int2lcd(bps[1]._vol_i,'}',0);
		//int2lcd(bps[0]._vol_u,'[',0);
		//int2lcd(bps[1]._vol_u,']',0);
		}
		/*int2lcdyx(bps[0]._vol_u,0,4,0);
		int2lcdyx(bps[0]._vol_i,0,8,0);
		int2lcdyx(I_ug_temp,0,12,0);
		int2lcdyx(U_maxg,0,19,0);*/	
	
/*nt2lcdyx((((LPC_CAN1->GSR)&(0xff000000))>>24),0,19,0);
	int2lcdyx((((LPC_CAN1->GSR)&(0x00ff0000))>>16),0,15,0);

	int2lcdyx((((LPC_CAN1->GSR)&(0x000000ff))),0,2,0);
	int2lcdyx(can_reset_cnt,0,5,0);
	int2lcdyx(lc640_read_int(EE_CAN_RESET_CNT),0,8,0);  */
	//int2lcdyx(bRESET,0,10,0);

/*	int2lcdyx(REV_STAT,0,0,0);
	int2lcdyx(proc_phase,0,3,0);
	int2lcdyx(time_proc_phase,0,7,0);
	int2lcdyx(I_ug_temp,0,13,0); */

/*	int2lcdyx(bCURRENT_STAB,0,0,0);
	int2lcdyx(cnt_del_rel,0,5,0);
	int2lcdyx(time_proc,0,10,0);
	int2lcdyx(T_DEL_REL_START,0,13,0);
	int2lcdyx(T_DEL_REL_WRK,0,18,0);*/
/*	int2lcdyx((short)delta_I_rel,0,17,0);
	int2lcdyx(bCURRENT_STAB,0,19,0); */
		
				

/*	int2lcdyx(localm[NETIF_ETH].IpAdr[2],0,11,0);
	int2lcdyx(localm[NETIF_ETH].IpAdr[3],0,7,0);	 */
	//int2lcdyx(work_stat,0,15,0);
	//int2lcdyx(bOFF,0,19,0);
	//int2lcdyx(bRAZR,0,17,0);
	
	//int2lcdyx(find_U_curve(U_up),0,5,0);
/*	temp_SL_U=find_U_curve(U_up);
	temp_SL_U=lc640_read_int(SEKTOR_KURVE_U+(temp_SL_U*2));

	int2lcdyx(temp_SL_U,0,12,0); */
	//int2lcdyx(bps[0]._rotor,0,19,0);	
/*	int2lcdyx(lc640_read_long(EE_TIME_PROC_PS_RESTART),0,10,0);	*/


/*
if((lc640_read_int(EE_CAN_RESET_CNT)<0)||(lc640_read_int(EE_CAN_RESET_CNT)>2))	lc640_write_int(EE_CAN_RESET_CNT,0);

can_reset_cnt++;

if((can_reset_cnt>=10)&&(!(avar_stat&0x0001))&&(!bRESET))
	{
	if(lc640_read_int(EE_CAN_RESET_CNT)<2)
		{
		lc640_write_int(EE_CAN_RESET_CNT,lc640_read_int(EE_CAN_RESET_CNT)+1);
		bRESET=1;
		}
	}

if((main_1Hz_cnt>=3600UL)&&(lc640_read_int(EE_CAN_RESET_CNT)!=0))
	{
	lc640_write_int(EE_CAN_RESET_CNT,0);
	}*/
	if(work_stat!=wsGS) fiks_stat_I=0;
	if(work_stat!=wsPS) fiks_stat_U=0;


	//int2lcdyx(fiks_stat_I,0,4,0);
	//int2lcdyx(fiks_stat_U,0,6,0);
	}




 else if(ind==iBps)
	{
	const char* ptr[8];

	if((sub_ind==(NUMIST-2))) {
	bgnd_par(			"N   U,В  I,A  t°C   ",
					"     .    .         ",
					"     .    .         ",
					" Выход              ");
	}

	else { 
	bgnd_par(			"N   U,В  I,A  t°C   ",
					"     .    .         ",
					"     .    .         ",
					"     .    .         ");
	}


	int2lcdyx(sub_ind+1,1,0,0);
	int2lcdyx(sub_ind+2,2,0,0);
	
		
		
	int2lcdyx(bps[sub_ind  ]._Uii,1,6,1);
	int2lcdyx(bps[sub_ind+1]._Uii,2,6,1);
	
	
	int2lcdyx(bps[sub_ind  ]._Ii,1,11,1);
	int2lcdyx(bps[sub_ind+1]._Ii,2,11,1);
	
	
	int2lcdyx(bps[sub_ind  ]._Ti,1,15,0);
	int2lcdyx(bps[sub_ind+1]._Ti,2,15,0);
	
	
	char2lcdhyx(bps[sub_ind1  ]._flags_tm,1,19);
	char2lcdhyx(bps[sub_ind1+1]._flags_tm,2,19);
	
	
	if((sub_ind<(NUMIST-2))) {
	int2lcdyx(sub_ind+3,3,0,0);
	int2lcdyx(bps[sub_ind+2]._Uii,3,6,1);
	int2lcdyx(bps[sub_ind+2]._Ii,3,11,1);
	int2lcdyx(bps[sub_ind+2]._Ti,3,15,0);
	char2lcdhyx(bps[sub_ind1+2]._flags_tm,3,19);
	} else {
	lcd_buffer[60]=1;
	}
					

/*	int2lcdyx(bps[sub_ind1  ]._cnt,1,19,0);
	int2lcdyx(bps[sub_ind1+1]._cnt,2,19,0);
	int2lcdyx(bps[sub_ind1+2]._cnt,3,19,0);*/
		
	/*	int2lcdyx(bps[sub_ind1  ]._ist_blok_cnt,1,5,0);
		int2lcdyx(bps[sub_ind1+1]._ist_blok_cnt,2,5,0);
		int2lcdyx(bps[sub_ind1+2]._ist_blok_cnt,3,5,0);*/			
		

	 /*
		int2lcdyx(bps[sub_ind1  ]._vol_u,1,12,0);
		int2lcdyx(bps[sub_ind1+1]._vol_u,2,12,0);
		int2lcdyx(bps[sub_ind1+2]._vol_u,3,12,0);		


		char2lcdhyx(bps[sub_ind1]._flags_tm,1,15);
		char2lcdhyx(bps[sub_ind1+1]._flags_tm,2,15);
		char2lcdhyx(bps[sub_ind1+2]._flags_tm,3,15);	
		*/

	//int2lcdyx(sub_ind,0,19,0);
     }  

else if(ind==iLoad)
	{
	bgnd_par(		"      НАГРУЗКА      ",
				" Uнагр =     [В     ",
				" Iнагр =     ]А     ",
				sm_exit);
	lcd_buffer[60]=1;
	     	
     int2lcd(load_U,'[',1);
     int2lcd(load_I,']',1);

     
                   	      	   	    		
     }





else if(ind==iVent)
	{

	ptrs[0]=  		" Fвент.текущ.     !%";
     ptrs[1]=  		" Fвент.max. (  @%) #";
	ptrs[2]=  	     " Выход              ";

	bgnd_par(			"     ВЕНТИЛЯТОР     ",
					ptrs[index_set],
					ptrs[index_set+1],
					ptrs[index_set+2]);

	pointer_set(1);

     int2lcd(main_vent_pos*5,'!',0);
	int2lcd(pos_vent,'#',0);
	int2lcd(pos_vent*5+45,'@',0);     
	}

else if(ind==iAvtRev)
	{

	if(AVT_REV_IS_ON)
		{
		ptrs[0]=  	" Включен            ";
		}
	else 
		{
		ptrs[0]=  	" Выключен           ";
		}

	ptrs[1]=  		" Tпрям.     0{:0}:0[";
	ptrs[2]=  	     " Тобр.      0(:0):0]";
	ptrs[3]=  	     " Тперекл.      0<:0>";
	ptrs[4]=  	     " Iст.пр.          !А";
	ptrs[5]=  	     " Iст.обр.         @А";
	ptrs[6]=  	     " Uст.пр.          #B";
	ptrs[7]=  	     " Uст.обр.         $B";
	ptrs[8]=  	     " Выход              ";	
	
	if(sub_ind-index_set>2)index_set=sub_ind-2;
	else if (sub_ind<index_set)index_set=sub_ind;
	
	bgnd_par(			"     АВТОРЕВЕРС     ",
					ptrs[index_set],
					ptrs[index_set+1],
					ptrs[index_set+2]);	
		
	pointer_set(1);

	int2lcd(AVT_REV_TIME_FF%60,'[',0);
	int2lcd((AVT_REV_TIME_FF/60)%60,'}',0);
	int2lcd(AVT_REV_TIME_FF/3600,'{',0);
	int2lcd(AVT_REV_TIME_REW%60,']',0);
	int2lcd((AVT_REV_TIME_REW/60)%60,')',0);
	int2lcd(AVT_REV_TIME_REW/3600,'(',0);
	int2lcd(AVT_REV_TIME_PAUSE%60,'>',0);
	int2lcd((AVT_REV_TIME_PAUSE/60)%60,'<',0);
	int2lcd(AVT_REV_I_NOM_FF,'!',1);
	int2lcd(AVT_REV_I_NOM_REW,'@',1);
	int2lcd(AVT_REV_U_NOM_FF,'#',1);
	int2lcd(AVT_REV_U_NOM_REW,'$',1);
	   
	}

else if(ind==iAvt)
	{
     ptrs[0]=  		"  АВТОМАТЫ НАГРУЗОК ";
	ptrs[1]=  		" Автомат №1       ! ";
	ptrs[2]=  		" Автомат №2       @ ";
	ptrs[3]=  		" Автомат №3       # ";
	ptrs[4]=  		" Автомат №4       $ ";
	ptrs[5]=  		" Автомат №5       % ";
	ptrs[6]=  		" Автомат №6       ^ ";
	ptrs[7]=  		" Автомат №7       & ";
	ptrs[8]=  		" Автомат №8       * ";
	ptrs[9]=  		" Автомат №9       ( ";
	ptrs[10]=  		" Автомат №10      ) ";
	ptrs[11]=  		" Автомат №11      + ";
	ptrs[12]=  		" Автомат №12      = ";

	ptrs[1+NUMAVT]=  	" Выход              ";
	ptrs[2+NUMAVT]=  	"                    ";
	ptrs[3+NUMAVT]=  	"                    ";

	bgnd_par(		ptrs[0],
				ptrs[index_set+1],
				ptrs[index_set+2],
				ptrs[index_set+3]);

	if(sub_ind-index_set>2)index_set=sub_ind-2;
	else if (sub_ind<index_set)index_set=sub_ind;
	pointer_set(1);

	//int2lcdyx(eb2_data_short[6],0,6,0);

	if(avt_stat[0]==avtON)	sub_bgnd("ВКЛ.",'!',-3);
	else 				sub_bgnd("ВЫКЛ.",'!',-4);
	if(avt_stat[1]==avtON)	sub_bgnd("ВКЛ.",'@',-3);
	else 				sub_bgnd("ВЫКЛ.",'@',-4);
	if(avt_stat[2]==avtON)	sub_bgnd("ВКЛ.",'#',-3);
	else 				sub_bgnd("ВЫКЛ.",'#',-4);
	if(avt_stat[3]==avtON)	sub_bgnd("ВКЛ.",'$',-3);
	else 				sub_bgnd("ВЫКЛ.",'$',-4);
	if(avt_stat[4]==avtON)	sub_bgnd("ВКЛ.",'%',-3);
	else 				sub_bgnd("ВЫКЛ.",'%',-4);
	if(avt_stat[5]==avtON)	sub_bgnd("ВКЛ.",'^',-3);
	else 				sub_bgnd("ВЫКЛ.",'^',-4);
	if(avt_stat[6]==avtON)	sub_bgnd("ВКЛ.",'&',-3);
	else 				sub_bgnd("ВЫКЛ.",'&',-4);
	if(avt_stat[7]==avtON)	sub_bgnd("ВКЛ.",'*',-3);
	else 				sub_bgnd("ВЫКЛ.",'*',-4);
	if(avt_stat[8]==avtON)	sub_bgnd("ВКЛ.",'(',-3);
	else 				sub_bgnd("ВЫКЛ.",'(',-4);
	if(avt_stat[9]==avtON)	sub_bgnd("ВКЛ.",')',-3);
	else 				sub_bgnd("ВЫКЛ.",')',-4);
	if(avt_stat[10]==avtON)	sub_bgnd("ВКЛ.",'+',-3);
	else 				sub_bgnd("ВЫКЛ.",'+',-4); 
	if(avt_stat[11]==avtON)	sub_bgnd("ВКЛ.",'=',-3);
	else 				sub_bgnd("ВЫКЛ.",'=',-4);
     //int2lcd(Uvv[1],'$',0);
     //int2lcd(Uvv[2],'$',0);

     //long2lcd_mmm(power_summary,'%',2);
     //int2lcd(power_current,'^',0);

     //int2lcdyx(adc_buff_ext_[0],0,4,0);
     //int2lcdyx(adc_buff_ext_[1],0,10,0);
     //int2lcdyx(adc_buff_ext_[2],0,16,0);
     }

else if(ind==iEnerg)
	{
     ptrs[0]=  		"  ЭЛЕКТРОСНАБЖЕНИЕ  ";

     ptrs[1]=  		" Ввод       #В      ";
     ptrs[2]=  	     " ПЭС        $В      ";            
     ptrs[3]=  	     " Pсумм.       %кВт*ч";
	ptrs[4]=  	     " Pтекущ.      ^Вт   ";
	ptrs[5]=  	     " Выход              ";
	ptrs[6]=  	     "                    ";
	ptrs[7]=  	     "                    ";

	bgnd_par(		ptrs[0],
				ptrs[index_set+1],
				ptrs[index_set+2],
				ptrs[index_set+3]);

	if(sub_ind-index_set>2)index_set=sub_ind-2;
	else if (sub_ind<index_set)index_set=sub_ind;
	pointer_set(1);

	int2lcd(Uvv0,'#',0);
     int2lcd(Uvv[1],'$',0);
     //int2lcd(Uvv[2],'$',0);

     long2lcd_mmm(power_summary,'%',2);
     int2lcd(power_current,'^',0);

     //int2lcdyx(adc_buff_ext_[0],0,4,0);
     //int2lcdyx(adc_buff_ext_[1],0,10,0);
     //int2lcdyx(adc_buff_ext_[2],0,16,0);
     }

else if(ind==iEnerg3)
	{
     ptrs[0]=  		"  ЭЛЕКТРОСНАБЖЕНИЕ  ";

     ptrs[1]=  		" Ввод ф.A    !В     ";
	ptrs[2]=  		" Ввод ф.B    @В     ";
	ptrs[3]=  		" Ввод ф.C    #В     ";
     ptrs[4]=  	     " ПЭС  ф.A    &В     ";
     ptrs[5]=  	     " ПЭС  ф.B    )В     ";
     ptrs[6]=  	     " ПЭС  ф.C    (В     ";		            
     ptrs[7]=  	     " Pсумм.       %кВт*ч";
	ptrs[8]=  	     " Pтекущ.      ^Вт   ";
	ptrs[9]=  	     " Выход              ";
	ptrs[10]=  	     "                    ";
	ptrs[11]=  	     "                    ";

	bgnd_par(		ptrs[0],
				ptrs[index_set+1],
				ptrs[index_set+2],
				ptrs[index_set+3]);

	if(sub_ind-index_set>2)index_set=sub_ind-2;
	else if (sub_ind<index_set)index_set=sub_ind;
	pointer_set(1);

	int2lcd(Uvv_eb2[0],'!',0);
	int2lcd(Uvv_eb2[1],'@',0);
	int2lcd(Uvv_eb2[2],'#',0);
	int2lcd(Upes_eb2[0],'&',0);
	int2lcd(Upes_eb2[1],')',0);
	int2lcd(Upes_eb2[2],'(',0);
     long2lcd_mmm(power_summary,'%',3);
     int2lcd(power_current,'^',0);

     }




		 
else if(ind==iBatLog)
	{
	if(BAT_IS_ON[sub_ind1]==bisON)ptrs[0]=" Введена  0!/@  /0# ";
	else ptrs[0]=" Выведена 0!/@  /0# ";
     ptrs[1]=" Номин.емк.     $A*ч";
     ptrs[2]=" Наработка      %ч. ";
     ptrs[3]=" Контроль емкости   ";
     ptrs[4]=" Выравнивающий заряд";
     ptrs[5]=" Разряды            ";
     ptrs[6]=sm_exit;	
	if((sub_ind-index_set)>1)index_set=sub_ind-1;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(	" БАТАРЕЙНЫЙ ЖУРНАЛ  ",
			"     БАТАРЕЯ N^     ",
			ptrs[index_set],
			ptrs[index_set+1]);
	pointer_set(2);	

	int2lcd(sub_ind1+1,'^',0); 
	int2lcd(BAT_DAY_OF_ON[sub_ind1],'!',0);
	sub_bgnd(sm_mont[BAT_MONTH_OF_ON[sub_ind1]],'@',0);
	int2lcd(BAT_YEAR_OF_ON[sub_ind1],'#',0); 
	int2lcd(BAT_C_NOM[sub_ind1],'$',0);
	int2lcd(BAT_RESURS[sub_ind1],'%',0);
	}




	
else if((ind==iSet_prl)||(ind==iK_prl))
	{
	bgnd_par("  Введите  пароль   ",sm_,sm_,sm_);
	int2lcdyx(parol[0],1,8,0);
     int2lcdyx(parol[1],1,9,0);
     int2lcdyx(parol[2],1,10,0);
     lcd_buffer[48+sub_ind]='¤';
	}	
		

	
else if(ind==iSet)
	{
	#define SI_SET_MAX	23
    	ptrs[0]=				" Источников        !";
	ptrs[1]=				" Максимальная длит- ";
    	ptrs[2]=				" сть процесса  0[:0]";
	ptrs[3]=				" Отображение времени";
	ptrs[4]=				" процесса          @";
	ptrs[5]=				" Отображение времени";
	ptrs[6]=				" на пульте         #";
	ptrs[7]=				" Измерение тока     ";
	ptrs[8]=				" нагрузки          $";
	ptrs[9]=				" Режим главного меню";
	ptrs[10]=				"                   %";
	ptrs[11]=				" Фиксированные     ";
	ptrs[12]=				"          настройки";
	ptrs[13]=				" Реле индикации     ";
	ptrs[14]=				" токоограничения    ";
	ptrs[15]=				" Рестарт           ^";
	ptrs[16]=				" Ethernet           ";
	ptrs[17]=				" MODBUS ADRESS     <";
	ptrs[18]=				" MODBUS BAUDRATE    ";
	ptrs[19]=				"                  >0";
	ptrs[20]=				" Автореверс         ";
	ptrs[SI_SET_MAX-2]=		" Выход              ";
	ptrs[SI_SET_MAX-1]=		" Калибровка         ";
	ptrs[SI_SET_MAX]=		" Тест ШИМ           ";
	ptrs[SI_SET_MAX+1]=		"                    ";
	ptrs[SI_SET_MAX+2]=		"                    ";	        
	
	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(	"     УСТАНОВКИ      ",
				ptrs[index_set],
				ptrs[index_set+1],
				ptrs[index_set+2]);

	pointer_set(1);	
	
/*    if(MNEMO_ON==mnON)
     	{
     	sub_bgnd("через yс.",'y',-8);
     	int2lcd(MNEMO_TIME,'y',0);
     	}
	else sub_bgnd("выкл.",'y',-4); */

	int2lcd(NUMIST,'!',0);
	int2lcd((T_PROC_MAX/60)%60,']',0);
	int2lcd(T_PROC_MAX/3600,'[',0);
	if(TIME_VISION)
     	{
     	sub_bgnd("прямое",'@',-5);
     	}
	else sub_bgnd("обратное",'@',-7); 

	if(TIME_VISION_PULT)
     	{
     	sub_bgnd("чч:мм",'#',-4);
     	}
	else sub_bgnd("мм:сс",'#',-4);
	
	if(I_LOAD_MODE)
     	{
     	sub_bgnd("шунт",'$',-3);
     	}
	else sub_bgnd("суммIбпс",'$',-7);

	if(main_menu_mode==mmmIT) 	  	sub_bgnd("источник тока",'%',-12);
	else if(main_menu_mode==mmmIN) 	sub_bgnd("источник напряжения",'%',-18);
	else if(main_menu_mode==mmmITIN) 	sub_bgnd("ист.тока-ист.напр.",'%',-17);
	else 						sub_bgnd("ист.напр.-ист.тока",'%',-17);

	if(restart_enable==reON) 	  	sub_bgnd("ВКЛ.",'^',-3);
	else 						sub_bgnd("ВЫКЛ.",'^',-4);
	

	int2lcd(MODBUS_ADRESS,'<',0);
	int2lcd(MODBUS_BAUDRATE,'>',0);
	}





else if(ind==iSet_T)
	{
	static char phase_cnt;
	if(++phase_cnt>=15)
	     {
	     phase_cnt=0;
	     if(++phase>=3)phase=0;
	     }
	ptrs[0]=sm_time;
	ptrs[1]=sm_;
	if(phase==0)ptrs[2]="     <> - выбор     ";
     if(phase==1)ptrs[2]="   ^v - установка   ";
     if(phase==2)ptrs[2]="     ¤  - выход     ";
	
	bgnd_par(" УСТАНОВКА  ВРЕМЕНИ ",ptrs[0],ptrs[1],ptrs[2]);
     if(sub_ind==0)lcd_buffer[42]='^';
     else if(sub_ind==1)lcd_buffer[45]='^';
     else if(sub_ind==2)lcd_buffer[48]='^';
     else if(sub_ind==3)lcd_buffer[51]='^';
     else if(sub_ind==4)lcd_buffer[54]='^';
     else if(sub_ind==5)lcd_buffer[58]='^';
  
 	int2lcd(LPC_RTC->SEC,'&',0);
 	int2lcd(LPC_RTC->MIN,'^',0);
 	int2lcd(LPC_RTC->HOUR,'%',0);
 	
 	int2lcd(LPC_RTC->DOM,'<',0);
 	sub_bgnd(sm_mont[LPC_RTC->MONTH],'>',0);
 	int2lcd(LPC_RTC->YEAR,'{',0);
 	if(bFL2)
 	     {
 	     lcd_buffer[find(':')]=' ';
 	     lcd_buffer[find(':')]=' ';
 	     }  
	}  

else if (ind==iLan_set)
	{
	char sss[10]="abcdef";
	char i;
	 
	ptrs[0]=	" Ethernet         ! ";
	ptrs[1]=	" DHCPклиент       @ ";
	ptrs[2]=	" IPадрес            ";
	ptrs[3]=	"  000.000.000.00#   ";
	ptrs[4]=	" Маска подсети      ";
	ptrs[5]=	"  000.000.000.00$   ";
	ptrs[6]=	" Шлюз               ";
	ptrs[7]=	"  000.000.000.00)   ";
	ptrs[8]=	" Порт.чтения       [";
	ptrs[9]=	" Порт.записи       ]";
	ptrs[10]=	" Community <        ";
	ptrs[11]=	" Адресат для TRAP N1";
	ptrs[12]=	"  000.000.000.00%   ";
	ptrs[13]=	" Адресат для TRAP N2";
	ptrs[14]=	"  000.000.000.00^   ";
	ptrs[15]=	" Адресат для TRAP N3";
	ptrs[16]=	"  000.000.000.00&   ";
	ptrs[17]=	" Адресат для TRAP N4";
	ptrs[18]=	"  000.000.000.00*   ";
	ptrs[19]=	" Адресат для TRAP N5";
	ptrs[20]=	"  000.000.000.00(   ";
	ptrs[21]=	" Выход              ";

	
	if(!ETH_IS_ON || (lc640_read_int(EE_ETH_IS_NOT)))
		{
		ptrs[1]=" Выход              ";
		ptrs[2]="                    ";
		ptrs[3]="                    ";
		}

	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;

     bgnd_par(	" УСТАНОВКИ Ethernet ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);
	
	pointer_set(1);
     if(ETH_IS_ON && (lc640_read_int(EE_ETH_IS_NOT)!=1))
     	{
     	sub_bgnd("ВКЛ.",'!',-3);   
     	}
     else 
     	{
     	sub_bgnd("ВЫКЛ.",'!',-4);   
     	}

     if(ETH_DHCP_ON)
     	{
     	sub_bgnd("ВКЛ.",'@',-3);   
     	}
     else 
     	{
     	sub_bgnd("ВЫКЛ.",'@',-4);   
     	}
		  
	if(sub_ind==2)	ip2lcd(ETH_IP_1,ETH_IP_2,ETH_IP_3,ETH_IP_4,'#',(sub_ind1+1));
	else ip2lcd(ETH_IP_1,ETH_IP_2,ETH_IP_3,ETH_IP_4,'#',0);
	if(sub_ind==4)	ip2lcd(ETH_MASK_1,ETH_MASK_2,ETH_MASK_3,ETH_MASK_4,'$',(sub_ind1+1));
	else ip2lcd(ETH_MASK_1,ETH_MASK_2,ETH_MASK_3,ETH_MASK_4,'$',0);
	if(sub_ind==6)	ip2lcd(ETH_GW_1,ETH_GW_2,ETH_GW_3,ETH_GW_4,')',(sub_ind1+1));
	else ip2lcd(ETH_GW_1,ETH_GW_2,ETH_GW_3,ETH_GW_4,')',0);

	int2lcd(ETH_SNMP_PORT_READ,'[',0);
	int2lcd(ETH_SNMP_PORT_WRITE,']',0);

	if( (ETH_TRAP1_IP_1==255) && (ETH_TRAP1_IP_2==255) && (ETH_TRAP1_IP_3==255) && (ETH_TRAP1_IP_4==255) ) sub_bgnd("    неактивен    ",'%',-14);
	else
		{
		if(sub_ind==11)	ip2lcd(ETH_TRAP1_IP_1,ETH_TRAP1_IP_2,ETH_TRAP1_IP_3,ETH_TRAP1_IP_4,'%',(sub_ind1+1));
		else ip2lcd(ETH_TRAP1_IP_1,ETH_TRAP1_IP_2,ETH_TRAP1_IP_3,ETH_TRAP1_IP_4,'%',0);
		}

	if( (ETH_TRAP2_IP_1==255) && (ETH_TRAP2_IP_2==255) && (ETH_TRAP2_IP_3==255) && (ETH_TRAP2_IP_4==255) ) sub_bgnd("    неактивен    ",'^',-14);
	else
		{
		if(sub_ind==13)	ip2lcd(ETH_TRAP2_IP_1,ETH_TRAP2_IP_2,ETH_TRAP2_IP_3,ETH_TRAP2_IP_4,'^',(sub_ind1+1));
		else ip2lcd(ETH_TRAP2_IP_1,ETH_TRAP2_IP_2,ETH_TRAP2_IP_3,ETH_TRAP2_IP_4,'^',0);
		}

	if( (ETH_TRAP3_IP_1==255) && (ETH_TRAP3_IP_2==255) && (ETH_TRAP3_IP_3==255) && (ETH_TRAP3_IP_4==255) ) sub_bgnd("    неактивен    ",'&',-14);
	else
		{
		if(sub_ind==15)	ip2lcd(ETH_TRAP3_IP_1,ETH_TRAP3_IP_2,ETH_TRAP3_IP_3,ETH_TRAP3_IP_4,'&',(sub_ind1+1));
		else ip2lcd(ETH_TRAP3_IP_1,ETH_TRAP3_IP_2,ETH_TRAP3_IP_3,ETH_TRAP3_IP_4,'&',0);
		}

	if( (ETH_TRAP4_IP_1==255) && (ETH_TRAP4_IP_2==255) && (ETH_TRAP4_IP_3==255) && (ETH_TRAP4_IP_4==255) ) sub_bgnd("    неактивен    ",'*',-14);
	else
		{
		if(sub_ind==17)	ip2lcd(ETH_TRAP4_IP_1,ETH_TRAP4_IP_2,ETH_TRAP4_IP_3,ETH_TRAP4_IP_4,'*',(sub_ind1+1));
		else ip2lcd(ETH_TRAP4_IP_1,ETH_TRAP4_IP_2,ETH_TRAP4_IP_3,ETH_TRAP4_IP_4,'*',0);
		}

	if( (ETH_TRAP5_IP_1==255) && (ETH_TRAP5_IP_2==255) && (ETH_TRAP5_IP_3==255) && (ETH_TRAP5_IP_4==255) ) sub_bgnd("    неактивен    ",'(',-14);
	else
		{
		if(sub_ind==19)	ip2lcd(ETH_TRAP5_IP_1,ETH_TRAP5_IP_2,ETH_TRAP5_IP_3,ETH_TRAP5_IP_4,'(',(sub_ind1+1));
		else ip2lcd(ETH_TRAP5_IP_1,ETH_TRAP5_IP_2,ETH_TRAP5_IP_3,ETH_TRAP5_IP_4,'(',0);
		}




	//int2lcdyx(sub_ind,0,1,0);	
	//int2lcdyx(index_set,0,3,0);
	//int2lcdyx(sub_ind1,0,5,0);
	//for(i=0;(i<9)&&(snmp_community[i]))

	for(i=0;i<9;i++)
		{
		sss[i]=snmp_Community[i];
		}
	sss[9]=0;		

	if(sub_ind==10)community2lcd(sss,'<',sub_ind1,1);
	else community2lcd(sss,'<',sub_ind1,0);
	
	//int2lcdyx(snmp_community[0],0,4,0);
	//int2lcdyx(snmp_community[11],0,9,0);
	//int2lcdyx(snmp_community[2],0,14,0);
	//int2lcdyx(snmp_community[sub_ind1],0,19,0);	
	}

else if(ind==iTst_pwm)
	{
	ptrs[0]=		" U=    [В  I=    ]А ";
	ptrs[1]=		" ШИМ напряж.=     ( ";
	ptrs[2]=		" ШИМ тока=        ) ";
	ptrs[3]=	    	" Выход              ";
	ptrs[4]=	    	"                    ";
	ptrs[5]=	    	"                    ";

	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
				
	bgnd_par(		"      ТЕСТ ШИМ      ",
				ptrs[index_set],
				ptrs[index_set+1],
				ptrs[index_set+2]);

	pointer_set(1);
	     	
     int2lcd(load_U,'[',1);
     int2lcd(load_I,']',1);
	int2lcd(tst_pwm_u,'(',0);
     int2lcd(tst_pwm_i,')',0);

     
                   	      	   	    		
     }
else if (ind==iRele_set)
	{ 
	ptrs[0]=		" Сигнал           ! ";
	ptrs[1]=		" Tзад.вкл.      @сек";
	ptrs[2]=		" Tзад.сраб.     #сек";
	ptrs[3]=		" dU             <%  ";
	ptrs[4]=		" dI             >%  ";
	ptrs[5]=  	" Выход              ";
	ptrs[6]=  	"                    ";
	ptrs[7]=  	"                    ";
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>1) index_set=sub_ind-1;
     bgnd_par(	"     УСТАНОВКИ      ",
			"РЕЛЕ ТОКООГРАНИЧЕНИЯ",
			ptrs[index_set],
			ptrs[index_set+1]);
	
	pointer_set(2);

	if(RELE_LOG==rlOFF)sub_bgnd("ВЫКЛ.",'!',-3);
	else if(RELE_LOG==rlON_NZ)sub_bgnd("ВКЛ.(НЗ)",'!',-6);
	else if(RELE_LOG==rlON_NR)sub_bgnd("ВКЛ.(НР)",'!',-6);

	int2lcd(T_DEL_REL_START,'@',0);
	int2lcd(T_DEL_REL_WRK,'#',0);
	int2lcd(DELT_REL_U,'<',0);
	int2lcd(DELT_REL_I,'>',0);
	}

else if (ind==iFiks_set)
	{ 
	ptrs[0]=		" U2          !В     ";
	ptrs[1]=		" U3          @В     ";
	ptrs[2]=		" I2	         #A     ";
	ptrs[3]=		" I3	         $A     ";
	ptrs[4]=  	" Выход              ";
	ptrs[6]=  	"                    ";
	ptrs[7]=  	"                    ";
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>1) index_set=sub_ind-1;
     bgnd_par(	"   ФИКСИРОВАННЫЕ    ",
			"     НАСТРОЙКИ      ",
			ptrs[index_set],
			ptrs[index_set+1]);
	
	pointer_set(2);

	int2lcd(U_up2,'!',1);
	int2lcd(U_up3,'@',1);
	int2lcd(I_ug2,'#',1);
	int2lcd(I_ug3,'$',1);
	}

else if (ind==iExt_set_3U)
	{ 
	ptrs[0]=		" Сухой контакт №1   ";
	ptrs[1]=		" Сухой контакт №2   ";
	ptrs[2]=		" Сухой контакт №3   ";
	ptrs[3]=		" Сухой контакт №4   ";
	ptrs[NUMSK]=  	" Выход              ";
	ptrs[NUMSK+1]= "                    ";
	ptrs[NUMSK+2]=	"                    ";
	ptrs[NUMSK+3]=	"                    ";
		
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("     УСТАНОВКИ      ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	}



else if (ind==iExt_sk_3U)
	{ 
	ptrs[0]=" состояние - @      ";
	ptrs[1]=" аварийное          ";
	ptrs[2]=" состояние - #      ";
	ptrs[3]=" Звук            ]  ";
	ptrs[4]=" Дисплей         (  ";
	ptrs[5]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("  СУХОЙ КОНТАКТ N!  ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	int2lcd(sub_ind1+1,'!',0);
	if(sk_stat[sub_ind1]==ssON)sub_bgnd("замкнут",'@',0);
	else sub_bgnd("разомк.",'@',0);
	if(!SK_SIGN[sub_ind1])sub_bgnd("замкнут",'#',0);
	else sub_bgnd("незамк.",'#',0);
	if(!SK_ZVUK_EN[sub_ind1])sub_bgnd("вкл.",']',-2);
	else sub_bgnd("выкл.",']',-2);
	if(!SK_LCD_EN[sub_ind1])sub_bgnd("вкл.",'(',-2);
	else sub_bgnd("выкл.",'(',-2);
	}		

else if (ind==iExt_sk_GLONASS)
	{ 
	ptrs[0]=" состояние - @      ";
	ptrs[1]=" аварийное          ";
	ptrs[2]=" состояние - #      ";
	ptrs[3]=" Звук            ]  ";
	ptrs[4]=" Дисплей         (  ";
	ptrs[5]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("  СУХОЙ КОНТАКТ N!  ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	int2lcd(sub_ind1+1,'!',0);
	if(sk_stat[sub_ind1]==ssON)sub_bgnd("замкнут",'@',0);
	else sub_bgnd("разомк.",'@',0);
	if(!SK_SIGN[sub_ind1])sub_bgnd("замкнут",'#',0);
	else sub_bgnd("незамк.",'#',0);
	if(!SK_ZVUK_EN[sub_ind1])sub_bgnd("вкл.",']',-2);
	else sub_bgnd("выкл.",']',-2);
	if(!SK_LCD_EN[sub_ind1])sub_bgnd("вкл.",'(',-2);
	else sub_bgnd("выкл.",'(',-2);
	}		



else if (ind==iExt_ddi)
	{ 
	ptrs[0]=" состояние - @      ";
	ptrs[1]=" аварийное          ";
	ptrs[2]=" состояние - #      ";
	ptrs[3]=" Реле            [  ";
	ptrs[4]=" Дисплей         (  ";
	ptrs[5]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("   ДАТЧИК ДЫМА      ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	
	if(sk_stat[1]==ssON)sub_bgnd("замкнут",'@',0);
	else sub_bgnd("разомк.",'@',0);
	if(!SK_SIGN[1])sub_bgnd("замкнут",'#',0);
	else sub_bgnd("незамк.",'#',0);
	if(SK_REL_EN[1])sub_bgnd("вкл.",'[',-2);
	else sub_bgnd("выкл.",'[',-2);
	if(SK_LCD_EN[1])sub_bgnd("вкл.",'(',-2);
	else sub_bgnd("выкл.",'(',-2);
	}	

else if (ind==iExt_dud)
	{ 
	ptrs[0]=" состояние - @      ";
	ptrs[1]=" аварийное          ";
	ptrs[2]=" состояние - #      ";
	ptrs[3]=" Реле            [  ";
	ptrs[4]=" Дисплей         (  ";
	ptrs[5]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("   ДАТЧИК УДАРА     ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);
	
	if(sk_stat[2]==ssON)sub_bgnd("замкнут",'@',0);
	else sub_bgnd("разомк.",'@',0);
	if(!SK_SIGN[2])sub_bgnd("замкнут",'#',0);
	else sub_bgnd("незамк.",'#',0);
	if(SK_REL_EN[2])sub_bgnd("вкл.",'[',-2);
	else sub_bgnd("выкл.",'[',-2);
	if(SK_LCD_EN[2])sub_bgnd("вкл.",'(',-2);
	else sub_bgnd("выкл.",'(',-2);
	}


else if (ind==iExt_dp)
	{ 
	ptrs[0]=" состояние - @      ";
	ptrs[1]=" аварийное          ";
	ptrs[2]=" состояние - #      ";
	ptrs[3]=" Реле            [  ";
     ptrs[4]=" Дисплей         (  ";
	ptrs[5]=sm_exit;
	
	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>2) index_set=sub_ind-2;
     bgnd_par("ДАТЧИК ПЕРЕВОРАЧИВ. ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	
	pointer_set(1);

	if(sk_stat[3]==ssON)sub_bgnd("замкнут",'@',0);
	else sub_bgnd("разомк.",'@',0);
	if(!SK_SIGN[3])sub_bgnd("замкнут",'#',0);
	else sub_bgnd("незамк.",'#',0);
	if(!SK_REL_EN[3])sub_bgnd("вкл.",'[',-2);
	else sub_bgnd("выкл.",'[',-2);
	if(!SK_LCD_EN[3])sub_bgnd("вкл.",'(',-2);
	else sub_bgnd("выкл.",'(',-2);


    /* int2lcdyx(sk_stat[0],0,2,0);
     int2lcdyx(sk_stat[1],0,5,0);
     int2lcdyx(sk_stat[2],0,8,0);
     int2lcdyx(sk_stat[3],0,11,0);*/
	}

else if(ind==iK)
	{
	char i;
	i=0;
	
	ptrs[i++]=	" Нагрузка           ";
	ptrs[i++]=	" БПС                ";
    	ptrs[i++]=	" Предельные пар.-ры ";
	ptrs[i++]=	" Выходная характ.-ка";
	ptrs[i++]=	" Реверс            !";
    	ptrs[i++]=	" Выход              ";
    	
    	ptrs[i++]=	"                    ";

	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("     КАЛИБРОВКА     ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

	pointer_set(1);	
	
	if(REV_IS_ON)sub_bgnd("ЕСТЬ",'!',-3);
	else sub_bgnd("НЕТ",'!',-2); 
	}    	


else if(ind==iK_viz_sel)
	{
	char i;
	i=0;
	
	ptrs[i++]=	" по напряжению      ";
	ptrs[i++]=	" по току            ";
    	ptrs[i++]=	" Выход              ";
    	ptrs[i++]=	"                    ";

	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("ВЫХОДНАЯ ХАРАКТ.-КА ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

	pointer_set(1);	 
	}   


else if(ind==iK_viz_u)
	{
	char i;
	i=0;
	
	if(viz_stat!=vsON)
		{
		ptrs[0]=		" U=    [В  I=    ]А ";
		ptrs[1]=		" Пуск               ";
	    	ptrs[2]=		" Выход              ";
	    	ptrs[3]=		"                    ";
		}
	else 
		{
		ptrs[0]=		" U=    [В  I=    ]А ";
		ptrs[1]=		" Шаг    <  ШИМ    > ";
	    	ptrs[2]=		" Стоп               ";
	    	ptrs[3]=		"                    ";
		}

	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("ВЫХ. ХАР. ПО НАПРЯЖ.",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

	if(viz_stat!=vsON)pointer_set(2);	 
	else pointer_set(3);

	int2lcd(load_U,'[',1);
     int2lcd(load_I,']',1);
	int2lcd(tst_pwm_u,'>',0);
     int2lcd(viz_stat_cnt/50+1,'<',0);
	}   

else if(ind==iK_viz_i)
	{
	char i;
	i=0;
	
	if(viz_stat!=vsON)
		{
		ptrs[0]=		" U=    [В  I=    ]А ";
		ptrs[1]=		" Пуск               ";
	    	ptrs[2]=		" Выход              ";
	    	ptrs[3]=		"                    ";
		}
	else 
		{
		ptrs[0]=		" U=    [В  I=    ]А ";
		ptrs[1]=		" Шаг    <  ШИМ    > ";
	    	ptrs[2]=		" Стоп               ";
	    	ptrs[3]=		"                    ";
		}

	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("ВЫХ. ХАР. ПО ТОКУ   ",
			ptrs[index_set],
			ptrs[index_set+1],
			ptrs[index_set+2]);

	if(viz_stat!=vsON)pointer_set(2);	 
	else pointer_set(3);

	int2lcd(load_U,'[',1);
     int2lcd(load_I,']',1);
	int2lcd(tst_pwm_i,'>',0);
     int2lcd(viz_stat_cnt/50+1,'<',0);
	}   


else if(ind==iK_load)
	{

	bgnd_par(		" КАЛИБРОВКА НАГРУЗКИ",
					" Uвых=     @В       ",
					" Iвых=     !A       ",
					" Выход              ");

	pointer_set(1);	
	int2lcd(load_U,'@',1);
	int2lcd(load_I,'!',1);

/*	int2lcdyx(bps[0]._vol_u,0,4,0);
	int2lcdyx(bps[0]._vol_u,0,8,0);
	int2lcdyx(bps[0]._flags_tu,0,12,0);

	int2lcdyx(Kiload0,3,19,0);
	int2lcdyx(Kiload1,3,15,0);
	int2lcdyx(ad7705_buff_[0],3,8,0); */
    }


else if(ind==iK_max_param)
	{
	ptrs[0]=  	" Uист.max.      !В  ";				   
    ptrs[1]=  	" Uист.min.      @B  ";
    ptrs[2]=  	" Iист.max.      #A  ";
    ptrs[3]=  	" Iист.min.      $A  ";
   	ptrs[4]=	" tсигн=         <°C ";
	ptrs[5]=	" tmax=          %°C ";
    ptrs[6]=	" Выход              ";
	ptrs[7]=    "                    ";
	
	if((sub_ind-index_set)>1)index_set=sub_ind-1;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par(		"    МАКСМАЛЬНЫЕ     ",
					"  ПАРАМЕТРЫ РАБОТЫ  ",
					ptrs[index_set],
					ptrs[index_set+1]);

	pointer_set(2);	
	int2lcd(U_MAX/10,'!',0);
	int2lcd(U_MIN/10,'@',0);
	int2lcd(I_MAX,'#',1);
	int2lcd(I_MIN,'$',1);
	int2lcd(T_MAX,'%',0);
	int2lcd(T_SIGN,'<',0);
	
	}

else if(ind==iK_bat_simple)
	{
	ptrs[0]=		" Uбат =     @В      ";
	ptrs[1]=		" откалибруйте Uбат  ";
	ptrs[2]=		"  нажатием љ или њ  ";
     ptrs[3]=		" Iбат =     #А      ";
     if(phase==0)
          {
          ptrs[4]=	"   нажмите ¤ для    ";
          ptrs[5]=	"калибровки нуля Iбат";
          }
     else          
          {
          ptrs[4]=	" откалибруйте Iбат  ";
          ptrs[5]=	"  нажатием љ или њ  ";
          }
     if(bat[sub_ind1]._nd)
     	{
     	ptrs[6]=		" Датчик температуры ";
     	ptrs[7]=		"     неисправен     ";
     	ptrs[8]=		"  или неподключен.  ";
     	}
     else
     	{	     
     	ptrs[6]=		" tбат =    $°C      ";
     	ptrs[7]=		" откалибруйте tбат  ";
     	ptrs[8]=		"  нажатием љ или њ  ";
     	}

     ptrs[9]=		" Выход              ";
     ptrs[10]=		"                    ";
     ptrs[11]=		"                    ";

	bgnd_par(		" КАЛИБРОВКА БАТ. N! ",
				ptrs[index_set],
				ptrs[index_set+1],
				ptrs[index_set+2]);
     
     if(sub_ind==0)
     	{
     	mess_send(MESS2BPS_HNDL,PARAM_BPS_ALL_OFF_AFTER_2SEC,0xffff,10);
     	mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-sub_ind1)),10);
     	//mess_send(MESS2BAT_HNDL1,PARAM_BAT_ON,(1<<sub_ind1),10);
     	}
     
     if(sub_ind==3)
     	{
     	if(phase==0)
     		{
			mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,0xffff,10);
     		mess_send(MESS2RELE_HNDL,PARAM_RELE_SAMOKALIBR,1,10);
			mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<sub_ind1),10);
     		//mess_send(MESS2BAT_HNDL1,PARAM_BAT_ON,(1<<(1-sub_ind1)),10);
     		}
     	else if(phase==1)
     		{
			mess_send(MESS2BPS_HNDL,PARAM_BPS_ALL_OFF_AFTER_2SEC,0xffff,10);
			mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-sub_ind1)),10);
     		//mess_send(MESS2BAT_HNDL1,PARAM_BAT_ON,(1<<sub_ind1),10);
   			}
     		
     	}

     if(sub_ind==6)
     	{
   		//mess_send(_MESS_BAT_MASK_ON,_MESS_BAT_MASK_ON,(0xffff),10);
    		//mess_send(MESS_SRC_ON_OFF,_MESS_SRC_MASK_UNBLOK,0xffff,10);
     		
     	}

     if(sub_ind==9)
     	{
     	mess_send(MESS2BPS_HNDL,PARAM_BPS_ALL_OFF_AFTER_2SEC,0xffff,10);
     	mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-sub_ind1)),10);
     	//mess_send(MESS2BAT_HNDL1,PARAM_BAT_ON,(1<<sub_ind1),10);
     	}
	
	if((sub_ind==0)||(sub_ind==1)||(sub_ind==2))index_set=0;
	else if((sub_ind==3)||(sub_ind==4)||(sub_ind==5))index_set=3;
	else if((sub_ind==6)||(sub_ind==7)||(sub_ind==8))index_set=6;
	else index_set=9;
	


	pointer_set(1);	
	int2lcd(sub_ind1+1,'!',0);
	int2lcd(bat[sub_ind1]._Ub,'@',1);
	int2lcd_mmm(bat[sub_ind1]._Ib,'#',2);
	int2lcd_mmm(bat[sub_ind1]._Tb,'$',0);

	//int2lcdyx(ad7705_buff_[0],0,6,0);
	//int2lcdyx(adc_buff_[12],0,15,0);
	
	}  	



else if(ind==iK_inv)
	{
	
	ptrs[0]=" Uинв =    @В       ";
	ptrs[1]=" откалибруйте Uинв  ";
	ptrs[2]="  нажатием љ или њ  "; 
	ptrs[3]=" Iинв =     %А      ";
	if(phase==0)
          {
          ptrs[4]=	"   нажмите ¤ для    ";
          ptrs[5]=	"калибровки нуля Iинв";
          }
     else
     	{
          ptrs[4]=" откалибруйте Iинв  ";
          ptrs[5]="  нажатием љ или њ  ";     	
     	} 
     	
	ptrs[6]=" tинв =   ^°C       ";    
	ptrs[7]=" откалибруйте tинв  ";
	ptrs[8]="  нажатием љ или њ  ";
	ptrs[9]=sm_exit;
	ptrs[10]=sm_;
	ptrs[11]=sm_;     	     	    
	

     if((sub_ind==0)||(sub_ind==1)||(sub_ind==2))index_set=0;
	else if((sub_ind==3)||(sub_ind==4)||(sub_ind==5))index_set=3;
	else if((sub_ind==6)||(sub_ind==7)||(sub_ind==8))index_set=6;
	else index_set=9;
	
	bgnd_par("КАЛИБРОВКА ИНВЕРТ N!",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	int2lcd(sub_ind1+1,'!',0);
	int2lcd(inv[sub_ind1]._Uii,'@',1);
	int2lcd(inv[sub_ind1]._Ii,'%',1);
	int2lcd(inv[sub_ind1]._Ti,'^',0); 


     if((sub_ind==0))
		{
//		mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,(1<<sub_ind1),10);
//		mess_send(MESS2BAT_HNDL,PARAM_BAT_ALL_OFF_AFTER_2SEC,0,10);
	    mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_SET,1000,10);
          }
     if(sub_ind==3)
		{
		if(phase==0)
			{
//          	mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,~(1<<sub_ind1),10);
          	}
      	else if(phase==1)
			{
//          	mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,(1<<sub_ind1),10);
//			mess_send(MESS2BAT_HNDL,PARAM_BAT_ALL_OFF_AFTER_2SEC,0,10);
          	}
          mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_SET,1000,10);
          }
	

	
  
	     
	//MSG_IND2PWM_SRC1=900;
	//MSG_IND2PWM_SRC2=900;         
/*int2lcdyx(sub_ind1,0,0,0);
int2lcdyx(sub_ind,0,1,0);
int2lcdyx(phase,0,2,0);
int2lcdyx(MSG_IND2OUT_DIS_SRC1,0,3,0);
int2lcdyx(MSG_IND2OUT_DIS_SRC2,0,4,0);  
int2lcdyx(MSG_IND2OUT_EN_SRC1,0,5,0);
int2lcdyx(MSG_IND2OUT_EN_SRC2,0,6,0); */

//int2lcdyx(cntrl_stat1,0,19,0); 
//int2lcdyx(load_U,0,5,0); 
//int2lcdyx(cntrl_stat,0,10,0); 
//int2lcdyx(bps[sub_ind1]._rotor,0,19,0); 
//int2lcdyx(u_necc,0,19,0);  
	 }

else if(ind==iK_bps_sel)
	{
	ptrs[0]=						" БПС N1             ";
     ptrs[1]=						" БПС N2             ";
     ptrs[2]=						" БПС N3             ";
	ptrs[3]=						" БПС N4             ";
     ptrs[4]=						" БПС N5             ";
     ptrs[5]=						" БПС N6             ";
	ptrs[6]=						" БПС N7             ";
     ptrs[7]=						" БПС N8             ";
     ptrs[8]=						" БПС N9             ";
	ptrs[9]=						" БПС N10            ";
     ptrs[10]=						" БПС N11            ";
     ptrs[11]=						" БПС N12            ";               
	ptrs[NUMIST]=					" Выход              ";
	ptrs[1+NUMIST]=				"                    ";
	ptrs[2+NUMIST]=				"                    ";

	if((sub_ind-index_set)>2)index_set=sub_ind-2;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par("  КАЛИБРОВКА БПСов  ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);
	pointer_set(1);
	
     }     

else if(ind==iK_bps)
	{
	
	ptrs[0]=" Uист =    @В       ";
     ptrs[1]=" откалибруйте Uист  ";
     ptrs[2]="  нажатием љ или њ  "; 
	ptrs[3]=" Iист =     %А      ";
	if(phase==0)
          {
          ptrs[4]=	"   нажмите ¤ для    ";
          ptrs[5]=	"калибровки нуля Iист";
          }
     else
     	{
          ptrs[4]=" откалибруйте Iист  ";
          ptrs[5]="  нажатием љ или њ  ";     	
     	} 
     	
     ptrs[6]=" tист =   ^°C       ";    
	ptrs[7]=" откалибруйте tист  ";
     ptrs[8]="  нажатием љ или њ  ";
     ptrs[9]=sm_exit;
     ptrs[10]=sm_;
     ptrs[11]=sm_;     	     	    
	

     if((sub_ind==0)||(sub_ind==1)||(sub_ind==2))index_set=0;
	else if((sub_ind==3)||(sub_ind==4)||(sub_ind==5))index_set=3;
	else if((sub_ind==6)||(sub_ind==7)||(sub_ind==8))index_set=6;
	else if((sub_ind==9)||(sub_ind==10)||(sub_ind==11))index_set=9;
	else if((sub_ind==12)||(sub_ind==13)||(sub_ind==14))index_set=12;	
	else index_set=15;
	
	bgnd_par(" КАЛИБРОВКА БПС N! ",ptrs[index_set],ptrs[index_set+1],ptrs[index_set+2]);

	pointer_set(1);	
	int2lcd(sub_ind1+1,'!',0);
	int2lcd(bps[sub_ind1]._Uii,'@',1);
	int2lcd(bps[sub_ind1]._Uin,'#',1);
	int2lcd(U_AVT,'$',1);
	int2lcd(bps[sub_ind1]._Ii,'%',1);
	int2lcd(bps[sub_ind1]._Ti,'^',0); 
	 
	
     if((sub_ind==0)||(sub_ind==3))
		{
		mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,(1<<sub_ind1),10);
		mess_send(MESS2BAT_HNDL,PARAM_BAT_ALL_OFF_AFTER_2SEC,0,10);
	    	mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_SET,1000,10);
          }
     if(sub_ind==6)
		{
          mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,(1<<sub_ind1),10);
          mess_send(MESS2BAT_HNDL,PARAM_BAT_ALL_OFF_AFTER_2SEC,0,40);
          mess_send(MESS2UNECC_HNDL,PARAM_UNECC_SET,U_AVT,10);
	    	mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_FAST_REG,0,10);

          }

     if(sub_ind==9)
		{
		if(phase==0)
			{
          	mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,~(1<<sub_ind1),10);
          	}
      	else if(phase==1)
			{
          	mess_send(MESS2BPS_HNDL,PARAM_BPS_MASK_ON_OFF_AFTER_2SEC,(1<<sub_ind1),10);
			mess_send(MESS2BAT_HNDL,PARAM_BAT_ALL_OFF_AFTER_2SEC,0,10);
          	}
          mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_SET,1000,10);
          }
	
    	if(sub_ind==12)
		{
          }	
          
          
	if(mess_find( (MESS2IND_HNDL)) && (mess_data[0]==PARAM_U_AVT_GOOD) )
		{
		show_mess("     Установка      ",
	          	"    напряжения      ",
	          	" автономной работы  ",
	          	"    произведена     ",3000);
		}	     
	     
	//MSG_IND2PWM_SRC1=900;
	//MSG_IND2PWM_SRC2=900;         
/*int2lcdyx(sub_ind1,0,0,0);
int2lcdyx(sub_ind,0,1,0);
int2lcdyx(phase,0,2,0);
int2lcdyx(MSG_IND2OUT_DIS_SRC1,0,3,0);
int2lcdyx(MSG_IND2OUT_DIS_SRC2,0,4,0);  
int2lcdyx(MSG_IND2OUT_EN_SRC1,0,5,0);
int2lcdyx(MSG_IND2OUT_EN_SRC2,0,6,0); */

//int2lcdyx(cntrl_stat1,0,19,0); 
//int2lcdyx(load_U,0,5,0); 
//int2lcdyx(cntrl_stat,0,10,0); 
//int2lcdyx(bps[sub_ind1]._rotor,0,19,0); 
//int2lcdyx(u_necc,0,19,0);  
	 }

else if(ind==iK_power_net)
	{
	ptrs[0]=" Uввод=    @В       ";
	ptrs[1]=" Uпэс =    #В       ";
     ptrs[2]=" Выход              ";
	ptrs[3]="                    ";
	
	if((sub_ind-index_set)>1)index_set=sub_ind-1;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par( "      КАЛИБРОВКА    ",
               "   СИЛОВЫХ ВВОДОВ   ",
               ptrs[index_set],
               ptrs[index_set+1]);

	pointer_set(2);	
	int2lcd(Uvv[0],'@',0);
     int2lcd(Uvv[1],'#',0);
	//int2lcdyx(net_buff_,3,10,0);
	
	//int2lcdyx(Kunet,3,16,0);
     }


else if(ind==iK_power_net3)
	{
     ptrs[0]=  		" Ввод ф.A    !В     ";
	ptrs[1]=  		" Ввод ф.B    @В     ";
	ptrs[2]=  		" Ввод ф.C    #В     ";
     ptrs[3]=  	     " ПЭС  ф.A    &В     ";
     ptrs[4]=  	     " ПЭС  ф.B    *В     ";
     ptrs[5]=  	     " ПЭС  ф.C    (В     ";		            
     ptrs[6]=" Выход              ";
	ptrs[7]="                    ";
	
	if((sub_ind-index_set)>1)index_set=sub_ind-1;
	else if(sub_ind<index_set)index_set=sub_ind;
	bgnd_par( "      КАЛИБРОВКА    ",
               "   СИЛОВЫХ ВВОДОВ   ",
               ptrs[index_set],
               ptrs[index_set+1]);

	pointer_set(2);	
	int2lcd(Uvv_eb2[0],'!',0);
	int2lcd(Uvv_eb2[1],'@',0);
	int2lcd(Uvv_eb2[2],'#',0);
	int2lcd(Upes_eb2[0],'&',0);
	int2lcd(Upes_eb2[1],'*',0);
	int2lcd(Upes_eb2[2],'(',0);
	//int2lcdyx(net_buff_,3,10,0);
	
	//int2lcdyx(Kunet,3,16,0);
     }


	 
			
if(ind==iDeb)
     {
     if(sub_ind==0)
     	{


         	bgnd_par("*0000*000000*       ",
     	         "                    ",
     	         "                    ",
     	         "      ********      ");

	int2lcdyx(SOFT_NUM,0,4,0);
	long2lcdyx_mmm(SOFT_DATE,0,11,0);

/*	int2lcdyx(a_ind.i,0,2,0);
	int2lcdyx(a_ind.s_i,0,6,0);
	int2lcdyx(a_ind.s_i1,0,10,0);
	int2lcdyx(a_ind.s_i2,0,14,0);
	int2lcdyx(a_ind.i_s,0,16,0);




	int2lcdyx(c_ind.i,1,2,0);
	int2lcdyx(c_ind.s_i,1,6,0);
	int2lcdyx(c_ind.s_i1,1,10,0);
	int2lcdyx(c_ind.s_i2,1,14,0);
	int2lcdyx(c_ind.i_s,1,16,0);*/


	int2lcdyx(t_box,2,4,0);
	int2lcdyx(t_ext_can,3,5,0);
	//int2lcdyx(t_ext_can_nd,3,6,0);
	int2lcdyx(t_ext[1],2,10,0);
	int2lcdyx(t_ext[2],3,10,0);

	//int2lcdyx(cntrl_stat,0,19,0);

	//int2lcdyx(adc_buff_[14],3,14,0);

	/*int2lcdyx(adc_buff_[12],2,14,0);
	int2lcdyx(adc_buff_[14],3,14,0);
	int2lcdyx(adc_buff_[5],2,19,0);
	int2lcdyx(adc_buff_[6],3,19,0);*/

	//int2lcdyx(tloaddisable_cmnd,2,14,0);
	//int2lcdyx(tloaddisable_stat,3,14,0);

/*		int2lcdyx(load_U,0,15,0);
		int2lcdyx(u_necc,0,19,0);
		
		

		int2lcdyx(sub_ind1+1,1,0,0);
		int2lcdyx(sub_ind1+2,2,0,0);
		int2lcdyx(sub_ind1+3,3,0,0);
		
		
		int2lcdyx(bps[sub_ind1  ]._cnt,1,2,0);
		int2lcdyx(bps[sub_ind1+1]._cnt,2,2,0);
		int2lcdyx(bps[sub_ind1+2]._cnt,3,2,0);*/		
		
	/*	int2lcdyx(bps[sub_ind1  ]._ist_blok_cnt,1,5,0);
		int2lcdyx(bps[sub_ind1+1]._ist_blok_cnt,2,5,0);
		int2lcdyx(bps[sub_ind1+2]._ist_blok_cnt,3,5,0);*/			
		
	/*	char2lcdhyx(bps[sub_ind1  ]._flags_tu,1,8);
		char2lcdhyx(bps[sub_ind1+1]._flags_tu,2,8);
		char2lcdhyx(bps[sub_ind1+2]._flags_tu,3,8);

		int2lcdyx(bps[sub_ind1  ]._vol_u,1,12,0);
		int2lcdyx(bps[sub_ind1+1]._vol_u,2,12,0);
		int2lcdyx(bps[sub_ind1+2]._vol_u,3,12,0);		


		char2lcdhyx(bps[sub_ind1]._flags_tm,1,15);
		char2lcdhyx(bps[sub_ind1+1]._flags_tm,2,15);
		char2lcdhyx(bps[sub_ind1+2]._flags_tm,3,15);	

		char2lcdhyx(bps[sub_ind1]._Ii,1,19);
		char2lcdhyx(bps[sub_ind1+1]._Ii,2,19);
		char2lcdhyx(bps[sub_ind1+2]._Ii,3,19);*/
	/*
		char2lcdhyx(bps[sub_ind1]._rotor>>8,1,15);
		char2lcdhyx(bps[sub_ind1+1]._rotor>>8,2,15);
		char2lcdhyx(bps[sub_ind1+2]._rotor>>8,3,15);		
		
		char2lcdhyx((char)bps[sub_ind1]._rotor,1,17);
		char2lcdhyx((char)bps[sub_ind1+1]._rotor,2,17);
		char2lcdhyx((char)bps[sub_ind1+2]._rotor,3,17);*/



     	
 /*    	bgnd_par("                    ",
     	         "                    ",
     	         "                    ",
     	         "%                   ");


		int2lcdyx(main_kb_cnt,0,3,0);
		int2lcdyx(cntrl_stat,1,3,0);
   		
		
		int2lcdyx(u_necc_up,0,7,0);
		int2lcdyx(u_necc,1,7,0);
		int2lcdyx(u_necc_dn,2,7,0);
		int2lcdyx(bat[0]._Ub,3,7,0);

		int2lcdyx(sign_U,0,10,0);
		int2lcdyx(sign_I,1,10,0);
		int2lcdyx(superviser_cnt,2,10,0);	


		int2lcdyx(bat[0]._zar,0,19,0);
		int2lcdyx(BAT_C_REAL[0],1,19,0);
		int2lcdyx(BAT_C_NOM[0],2,19,0);
		int2lcdyx(lc640_read_int(EE_BAT1_ZAR_CNT),3,19,0);  */

		  //bat_ver_cnt



	/*	int2lcdyx(tlv_buff[1][1],0,9,0);
		int2lcdyx(tlv_buff[1][2],0,14,0);
		int2lcdyx(tlv_buff[1][3],0,19,0);

   		int2lcdyx(tlv_buff[1][4],1,4,0);
		int2lcdyx(tlv_buff[1][5],1,9,0);
		int2lcdyx(tlv_buff[1][6],1,14,0);
		int2lcdyx(tlv_buff[1][7],1,19,0);

   		int2lcdyx(tlv_buff[1][8],2,4,0);
		int2lcdyx(tlv_buff[1][9],2,9,0);
		int2lcdyx(tlv_buff[1][10],2,14,0);
		int2lcdyx(tlv_buff[1][11],2,19,0);

   		int2lcdyx(tlv_buff[1][12],3,4,0);
		int2lcdyx(tlv_buff[1][13],3,9,0);
		int2lcdyx(tlv_buff[1][14],3,14,0);
		int2lcdyx(tlv_buff[1][15],3,19,0);	*/
      

     	}     

    	else if(sub_ind==1) 
     	{
     	bgnd_par("Б                   ",
     	         "                    ",
     	         "                    ",
     	         "                    ");

		int2lcdyx(bAVG,0,0,0);
		int2lcdyx(i_avg_max,0,5,0);
		int2lcdyx(i_avg_min,0,13,0);
		int2lcdyx(avg,0,19,0);
 /*         int2lcdyx(bat[0]._Ubm,1,7,0); 	int2lcdyx(bat[0]._av,1,10,0);
		int2lcdyx(bat[0]._dUbm,2,7,0);
		int2lcdyx(bat[0]._cnt_as,3,7,0);
		
 
		int2lcdyx(bat[1]._Ub,0,14,0);
          int2lcdyx(bat[1]._Ubm,1,14,0);	int2lcdyx(bat[1]._av,1,17,0);
		int2lcdyx(bat[1]._dUbm,2,14,0);
		int2lcdyx(bat[1]._cnt_as,3,14,0);*/

		int2lcdyx(sub_ind1+1,1,0,0);
		int2lcdyx(sub_ind1+2,2,0,0);
		int2lcdyx(sub_ind1+3,3,0,0);
		
		
		int2lcdyx(bps[sub_ind1  ]._cnt,1,2,0);
		int2lcdyx(bps[sub_ind1+1]._cnt,2,2,0);
		int2lcdyx(bps[sub_ind1+2]._cnt,3,2,0);		
		
	/*	int2lcdyx(bps[sub_ind1  ]._ist_blok_cnt,1,5,0);
		int2lcdyx(bps[sub_ind1+1]._ist_blok_cnt,2,5,0);
		int2lcdyx(bps[sub_ind1+2]._ist_blok_cnt,3,5,0);*/			
		
	/*	char2lcdhyx(bps[sub_ind1  ]._flags_tu,1,8);
		char2lcdhyx(bps[sub_ind1+1]._flags_tu,2,8);
		char2lcdhyx(bps[sub_ind1+2]._flags_tu,3,8);

		int2lcdyx(bps[sub_ind1  ]._vol_u,1,12,0);
		int2lcdyx(bps[sub_ind1+1]._vol_u,2,12,0);
		int2lcdyx(bps[sub_ind1+2]._vol_u,3,12,0);		


		char2lcdhyx(bps[sub_ind1]._flags_tm,1,15);
		char2lcdhyx(bps[sub_ind1+1]._flags_tm,2,15);
		char2lcdhyx(bps[sub_ind1+2]._flags_tm,3,15);	
		*/
		int2lcdyx(bps[sub_ind1]._Ii,1,15,0);
		int2lcdyx(bps[sub_ind1+1]._Ii,2,15,0);
		int2lcdyx(bps[sub_ind1+2]._Ii,3,15,0);
	/*
		char2lcdhyx(bps[sub_ind1]._rotor>>8,1,15);
		char2lcdhyx(bps[sub_ind1+1]._rotor>>8,2,15);
		char2lcdhyx(bps[sub_ind1+2]._rotor>>8,3,15);		
		*/
		
		int2lcdyx(bps[sub_ind1]._rotor,1,19,0);
		int2lcdyx(bps[sub_ind1+1]._rotor,2,19,0);
		int2lcdyx(bps[sub_ind1+2]._rotor,3,19,0);


 		}

 

    else if(sub_ind==2)
     	{
     	bgnd_par(	"AB                  ",
     		    	"                    ",
     		    	"                    ",
     		    	"                    ");



		//int2lcdhyx(avar_ind_stat,0,7);
		char2lcdbyx(rele_stat,1,7);
		
		int2lcdyx(sk_av_stat[0],0,19,0);
		int2lcdyx(sk_av_stat[1],1,19,0);
		int2lcdyx(sk_av_stat[2],2,19,0);

		int2lcdyx(SK_REL_EN[0]&0x000f,0,16,0);
		int2lcdyx(SK_REL_EN[1]&0x000f,1,16,0);
		int2lcdyx(SK_REL_EN[2]&0x000f,2,16,0);

		int2lcdyx(SK_SIGN[0]&0x000f,0,10,0);
		int2lcdyx(SK_SIGN[1]&0x000f,1,10,0);
		int2lcdyx(SK_SIGN[2]&0x000f,2,10,0);

		int2lcdyx(SK_LCD_EN[0]&0x000f,0,13,0);
		int2lcdyx(SK_LCD_EN[1]&0x000f,1,13,0);
		int2lcdyx(SK_LCD_EN[2]&0x000f,2,13,0);
		//int2lcdyx(adc_buff_ext_[1],1,19,0);
		//int2lcdyx(plazma_suz[2],2,4,0);
		//int2lcdyx(plazma_suz[3],3,4,0);
		}  

	else if(sub_ind==3)
     	{
     	bgnd_par("КЕ                  ",
     	         "                    ",
     	         "                   ^",
     	         "                   &");


	
		

/*	    		int2lcdyx(adc_net_buff_cnt,0,4,0);

		    	int2lcdyx((short)(main_power_buffer[0]>>12),0,19,0);
			int2lcdyx((short)(main_power_buffer[1]>>12),1,19,0);
			int2lcdyx((short)(main_power_buffer[2]>>12),2,19,0);
			int2lcdyx((short)(main_power_buffer[3]>>12),3,19,0);

		    	int2lcdyx((net_buff_),2,5,0); */


		   
		    


/*		int2lcdyx(load_U,0,4,0);
		int2lcdyx(load_I,1,4,0);
		lcd_buffer[44]='a';
		int2lcd_mmm((bat[0]._Ib)/10,'a',1);
		lcd_buffer[64]='a';
		int2lcd_mmm((bat[1]._Ib)/10,'a',1);

 		int2lcdyx(u_necc,0,8,0);

		
		
		lcd_buffer[14]='.';
		lcd_buffer[34]='.';
		int2lcdyx(Isumm,0,15,1);		
		int2lcdyx(Isumm_,1,15,1);


		int2lcdyx(cntrl_stat,0,19,0);
		int2lcdyx(num_necc,1,19,0);
		
		
		  
//		int2lcdyx(cntrl_stat,0,15,0);
		 
		//int2lcdyx(cntrl_plazma,1,3,0);
		//lcd_buffer[30]='a';
		int2lcd_mmm(Ibmax,'a',0);
		int2lcdyx(IZMAX,1,14,0);

		lcd_buffer[65]='a';
		int2lcd_mmm(bat[0]._Ib,'a',0);

		lcd_buffer[70]='a';
		int2lcd_mmm(bat[1]._Ib,'a',0); 

		lcd_buffer[75]='a';
		int2lcd_mmm(Ibmax,'a',0); 

	//	int2lcdyx(IMAX,2,3,0);
		
		

	//	int2lcdyx(IZMAX,3,19,0);

		//int2lcdyx(num_necc_Imax,3,6,0);
		//int2lcdyx(num_necc_Imin,3,12,0);


 //    	lcd_buffer[4]='a';            
 //    	int2lcd_mmm(Ibat,'a',1);   int2lcdyx(cntrl_stat,0,9,0);          int2lcdyx(hour_apv_cnt,0,13,0);                             char2lcdhyx(St_[0],0,19);  
 //    	int2lcdyx(Ubat,1,4,0);     int2lcdyx(main_apv_cnt,1,9,0);        int2lcdyx(lc640_read_int(bps1_AVAR_PTR),1,13,0);            char2lcdhyx(St_[1],1,19);
 //    	int2lcdyx(Us[0],2,4,0);  int2lcdyx(apv_cnt_1,2,9,0);           int2lcdyx(lc640_read_int(SRC1_AVAR_CNT),2,13,0);                                     int2lcdhyx(av_stat,2,19);
 //    	int2lcdyx(Us[1],3,4,0);  int2lcdyx(reset_apv_cnt,3,9,0);                                            int2lcdyx(plazma,3,19,0);
     	//int2lcd(plazma,'(',0);

     	//int2lcd(Us[0],'#',1);
     	//int2lcd(Us[1],'$',1);
     	//int2lcd(Is[0],'%',1);
     	//int2lcd(Is[1],'^',1);
    // 	int2lcd(bat[0]._Ub,'<',1);
    // 	int2lcd_mmm(bat[0]._Ib,'>',2);
 //    	char2lcdhyx(St_[0],3,13);
 //    	char2lcdhyx(St_[1],3,19);
 //    	char2lcdhyx(St,3,5);  */
		}

	else if(sub_ind==4)
     	{
     	bgnd_par(" АВАРИИ             ",
     	         "                    ",
     	         "                    ",
     	         "                    ");

		int2lcdyx(main_10Hz_cnt,0,7,0);
		int2lcdyx(bat[0]._av,0,10,0);
		int2lcdyx(bat[1]._av,0,12,0);
		char2lcdhyx(rele_stat,0,19);

 		long2lcdhyx(avar_stat,1,7);
		long2lcdhyx(avar_stat_old,2,7);
		//long2lcdhyx(avar_ind_stat,3,7);

		long2lcdhyx(avar_stat_new,2,19);
		long2lcdhyx(avar_stat_offed,3,19);



	//	int2lcdyx(bat[0]._Ub,1,15,0);
	//	int2lcdyx(bat[1]._rel_stat,2,15,0);


/*		int2lcdyx(mat_temper,0,7,0);
		int2lcdyx(load_U,0,11,0);  
		int2lcdyx(cntrl_stat,0,15,0);
		int2lcdyx(cntrl_stat_old,0,19,0); 
		int2lcdyx(cntrl_plazma,1,3,0);
		lcd_buffer[30]='a';
		int2lcd_mmm(Ibmax,'a',0);
		int2lcdyx(IZMAX,1,14,0);*/

		}
   else if(sub_ind==5)
     	{
     	bgnd_par("**                  ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    


     	
     	int2lcdyx(vz_cnt_s_,0,6,0);
		int2lcdyx(vz_cnt_s,1,6,0);
		int2lcdyx(vz_cnt_h,2,6,0);
		int2lcdyx(vz_cnt_h_,3,6,0);

     	int2lcdyx(__ee_vz_cnt,3,12,0);
//		int2lcdyx(lc640_read_int(EE_VZ_CNT),1,10,0);
	/*		int2lcdyx(eb2_data[10],2,10,0);
		int2lcdyx(eb2_data[11],3,10,0);

     	int2lcdyx(eb2_data[12],0,14,0);
		int2lcdyx(eb2_data[13],1,14,0);
		int2lcdyx(eb2_data[14],2,14,0);
		int2lcdyx(eb2_data[15],3,14,0);
     	
     	int2lcdyx(eb2_data[16],0,18,0);
		int2lcdyx(eb2_data[17],1,18,0);
		int2lcdyx(eb2_data[18],2,18,0);
		int2lcdyx(eb2_data[19],3,18,0);*/

	/*	int2lcdyx(eb2_data_short[0],0,13,0);
		int2lcdyx(eb2_data_short[1],1,13,0);
		int2lcdyx(eb2_data_short[2],2,13,0);

		int2lcdyx(eb2_data_short[3],0,19,0);
		int2lcdyx(eb2_data_short[4],1,19,0);
		int2lcdyx(eb2_data_short[5],2,19,0);  */

     	/*int2lcdyx(eb2_data[20],0,10,0);
		int2lcdyx(eb2_data[21],1,10,0);
		int2lcdyx(eb2_data[22],2,10,0);
		int2lcdyx(eb2_data[23],3,10,0);*/

    		}
    else if(sub_ind==6)
     	{
     	bgnd_par("                    ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    
     	/*int2lcdyx(ad7705_buff[0][0],0,4,0);
     	int2lcdyx(ad7705_buff[0][1],0,9,0);
     	int2lcdyx(ad7705_buff[0][2],0,14,0);
     	int2lcdyx(ad7705_buff[0][3],0,19,0);
     	int2lcdyx(ad7705_buff[0][4],1,4,0);
     	int2lcdyx(ad7705_buff[0][5],1,9,0);
     	int2lcdyx(ad7705_buff[0][6],1,14,0);
     	int2lcdyx(ad7705_buff[0][7],1,19,0);
     	int2lcdyx(ad7705_buff[0][8],2,4,0);
     	int2lcdyx(ad7705_buff[0][9],2,9,0);
     	int2lcdyx(ad7705_buff[0][10],2,14,0);
     	int2lcdyx(ad7705_buff[0][11],2,19,0);
     	int2lcdyx(ad7705_buff[0][12],3,4,0);
     	int2lcdyx(ad7705_buff[0][13],3,9,0);
     	int2lcdyx(ad7705_buff[0][14],3,14,0);
     	int2lcdyx(ad7705_buff[0][15],3,19,0);*/

		int2lcdyx(adc_buff_[0],0,4,0);
    		int2lcdyx(adc_buff_[1],0,9,0);
     	int2lcdyx(adc_buff_[2],0,14,0);
     	int2lcdyx(adc_buff_[3],0,19,0); 
     	int2lcdyx(adc_buff_[4],1,4,0);	
     	int2lcdyx(adc_buff_[5],1,9,0);
     	int2lcdyx(adc_buff_[6],1,14,0);
     	int2lcdyx(adc_buff_[7],1,19,0); 
     	int2lcdyx(adc_buff_[8],2,4,0);
     	int2lcdyx(adc_buff_[9],2,9,0);
     	int2lcdyx(adc_buff_[10],2,14,0);
     	int2lcdyx(adc_buff_[11],2,19,0);
     	int2lcdyx(adc_buff_[12],3,4,0);
     	int2lcdyx(adc_buff_[13],3,9,0);
     	int2lcdyx(adc_buff_[14],3,14,0);
     	int2lcdyx(adc_buff_[15],3,19,0);
    	}  		  		

   else if(sub_ind==7)
     	{
     	bgnd_par("7                   ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     		    
		int2lcdyx(main_vent_pos,0,19,0);
		int2lcdyx(TBOXMAX,1,2,0);
		int2lcdyx(TBOXREG,2,2,0);
		int2lcdyx(t_box,3,2,0);

		int2lcdyx(adc_buff_ext_[0],1,10,0);
		int2lcdyx(adc_buff_ext_[1],2,10,0);
		int2lcdyx(adc_buff_ext_[2],3,10,0);
    		}
    else if(sub_ind==8)
     	{
     	bgnd_par("                    ",
     		    "                    ",
     		    "                    ",
     		    "                    ");
     	int2lcdyx(ibt._T[0],0,2,0);
		int2lcdyx(ibt._T[1],1,2,0);
     	int2lcdyx(ibt._T[2],2,2,0);
		int2lcdyx(ibt._T[3],3,2,0);
		
     	int2lcdyx(ibt._nd[0],0,4,0);
		int2lcdyx(ibt._nd[1],1,4,0);
     	int2lcdyx(ibt._nd[2],2,4,0);
		int2lcdyx(ibt._nd[3],3,4,0);	    

     	int2lcdyx(ibt._T_dispers[0],0,7,0);
		int2lcdyx(ibt._T_dispers[1],1,7,0);
     	int2lcdyx(ibt._T_dispers[2],2,7,0);
		int2lcdyx(ibt._T_dispers[3],3,7,0);
			    
		int2lcdyx(ibt._avg1,0,19,0);
		int2lcdyx(ibt._max_dispers_num,1,19,0);
		int2lcdyx(t_box,3,19,0);
     	}		     	
     			
     }

else if((ind==iAv_view)||(ind==iAv_view_avt))
	{
//	unsigned short tempUI,tempUI_;
//    	unsigned long tempUL;
	
	bgnd_par(sm_,sm_,sm_,sm_);
	if(sub_ind==0)
		{	
		if(avar_stat&0x00000001)
			{
			bgnd_par(	"    Авария  сети    ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			int2lcd(net_U,']',0);
			}
    		else 
			{
	    		bgnd_par(	"    Авария  сети    ",
	    				"     устранена      ",
					sm_,sm_); 
			}
		}
	else if((sub_ind==1)||(sub_ind==2))
		{
		if(avar_stat&(1<<sub_ind))
			{
			bgnd_par(	"   Авария бат. N!   ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			}
    		else 
			{
	    		bgnd_par(	"   Авария бат. N!   ",
	    				"     устранена      ",
					sm_,sm_); 
		
		     }
		int2lcd(sub_ind,'!',0);
		} 
     
	else if((sub_ind>=3)&&(sub_ind<=14))
		{
		if((sub_ind-2)<=9)					ptrs[0]=	"   Авария БПС N+    ";
		else 							ptrs[0]=	"   Авария БПС N +   ";
		if(bps[sub_ind-3]._last_avar==0)		ptrs[1]=	"     перегрев!!!    ";
		else if(bps[sub_ind-3]._last_avar==1)	ptrs[1]=	"  завышено Uвых!!!  ";	
		else if(bps[sub_ind-3]._last_avar==2)	ptrs[1]=	"  занижено Uвых!!!  ";	
		else if(bps[sub_ind-3]._last_avar==3)	ptrs[1]=	"    отключился!!!   ";
		if(avar_stat&(1<<sub_ind)) 			ptrs[2]=	"    не устранена    ";
		else								ptrs[2]=	"     устранена      ";	
										ptrs[3]=	"                    ";

		bgnd_par(ptrs[0],ptrs[1],ptrs[2],ptrs[3]);
		int2lcd((sub_ind-2),'+',0);
          
		//int2lcdxy(sub_ind,0x20,0);

		} 
		
	else if(sub_ind==25)
		{ 

		if(sk_av_stat[0]==sasON)
			{
			bgnd_par(	"   Авария СК. N1    ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			}
    		else 
			{
	    		bgnd_par(	"   Авария СК. N1    ",
	    				"     устранена      ",
					sm_,sm_); 
		
		     }

		}

	else if(sub_ind==26)
		{ 

		if(sk_av_stat[1]==sasON)
			{
			bgnd_par(	"   Авария СК. N2    ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			}
    		else 
			{
	    		bgnd_par(	"   Авария СК. N2    ",
	    				"     устранена      ",
					sm_,sm_); 
		
		     }

		}

	else if(sub_ind==27)
		{ 

		if(sk_av_stat[2]==sasON)
			{
			bgnd_par(	"   Авария СК. N3    ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			}
    		else 
			{
	    		bgnd_par(	"   Авария СК. N3    ",
	    				"     устранена      ",
					sm_,sm_); 
		
		     }

		}

	else if(sub_ind==28)
		{ 

		if(sk_av_stat[3]==sasON)
			{
			bgnd_par(	"   Авария СК. N4    ",
				    	"    не устранена    ",
				    	sm_,sm_); 
			}
    		else 
			{
	    		bgnd_par(	"   Авария СК. N4    ",
	    				"     устранена      ",
					sm_,sm_); 
		
		     }

		}


	else if(sub_ind==5)
		{

		}

	else if(sub_ind==6)
		{

		}

	else if(sub_ind==7)
		{

		} 
		
	else if(sub_ind==8)
		{

		}

	else if(sub_ind==9)
		{

		}

	else if(sub_ind==10)
		{

		}
	    		     
	else if(sub_ind==11)
		{

		} 
		
	else if(sub_ind==12)
		{

		}

	else if(sub_ind==13)
		{

		}

	else if(sub_ind==14)
		{

		}

	else if(sub_ind==15)
		{

		} 
					
	} 
#ifndef _DEBUG_	
else if(ind==iAvz)
	{
	
 	if(AVZ==AVZ_1) 		ptrs[0]=	" раз в месяц        ";
	else if(AVZ==AVZ_2) 	ptrs[0]=	" раз в 2 месяца     ";
	else if(AVZ==AVZ_3) 	ptrs[0]=	" раз в 3 месяца     "; 
	else if(AVZ==AVZ_6) 	ptrs[0]=	" раз в полгода      ";
	else if(AVZ==AVZ_12) 	ptrs[0]=	" раз в год          ";
	else 				ptrs[0]=	" выключен           "; 
	
	ptrs[1]=						" Длительность    (ч.";
	if(AVZ!=AVZ_OFF)
		{
		ptrs[2]=					" очередное включение";
		ptrs[3]=					"  0%  &0^  0@:0#:0$ ";
		ptrs[4]=					sm_exit;
		}
	else ptrs[2]=						sm_exit;

	if(sub_ind<index_set) index_set=sub_ind;
	else if((sub_ind-index_set)>1) index_set=sub_ind-1;
	if((sub_ind==2)&&(AVZ!=AVZ_OFF)) index_set=2;
	
	bgnd_par(	"   АВТОМАТИЧЕСКИЙ   ",
			"ВЫРАВНИВАЮЩИЙ ЗАРЯД ",
			ptrs[index_set],
			ptrs[index_set+1]);

	pointer_set(2);
		
	int2lcd(HOUR_AVZ,'@',0);
	int2lcd(MIN_AVZ,'#',0);
	int2lcd(SEC_AVZ,'$',0);
	int2lcd(DATE_AVZ,'%',0);
	int2lcd(YEAR_AVZ,'^',0);

	sub_bgnd(sm_mont[MONTH_AVZ],'&',-2);

	int2lcd(AVZ_TIME,'(',0);
	
	}




#endif
/*
const char sm7[]	={" Источник N2        "}; //
const char sm8[]	={" Нагрузка           "}; //
const char sm9[]	={" Сеть               "}; //
const char sm10[]	={" Спецфункции        "}; // 
const char sm11[]	={" Журнал аварий      "}; //
const char sm12[]	=" Батарейный журнал  "}; //
const cha		=" Паспорт            "}; //
*/


//char2lcdhyx(bat_rel_stat[0],0,10);
//char2lcdhyx(bat_rel_stat[1],0,15);
//int2lcdyx(u_necc,0,19,0);
//int2lcdyx(cntrl_stat,0,5,0); 	   mess_cnt[i]

//char2lcdhyx(bat_rel_stat[0],0,5);
//char2lcdhyx(bat_rel_stat[1],0,10);
//int2lcdyx(mess_cnt[1],0,2,0);
//int2lcdyx(GET_REG(IOPIN1,21,1),0,5,0); 
//int2lcdyx(samokalibr_cnt,0,10,0);
//char2lcdhyx(rele_stat,0,19);
//char2lcdhyx(mess_cnt[1],0,16); 

//int2lcdyx(ad7705_res1,0,8,0);
//int2lcdyx(ad7705_res2,0,16,0); 
//	int2lcdyx(bat[0]._cnt_to_block,0,1,0);
//	int2lcdyx(bat[1]._cnt_to_block,0,3,0);
//	int2lcdyx(bat[0]._rel_stat,0,5,0);
/*	int2lcdyx(ind,0,3,0); 
	int2lcdyx(sub_ind,0,6,0);
	int2lcdyx(index_set,0,9,0);
	int2lcdyx(ptr_ind,0,14,0);
	;*/
/*int2lcdyx(ind,0,19,0);
int2lcdyx(retindsec,0,15,0);
int2lcdyx(retcnt,0,11,0);
int2lcdyx(retcntsec,0,7,0);	*/
//int2lcdyx(bps[0]._flags_tu,0,15,0);
//int2lcdyx(cntrl_stat,0,19,0); 

//int2lcdyx(lc640_read_int(EE_ETH_IS_ON),0,19,0);
//int2lcdyx(lc640_read_int(EE_ETH_IS_NOT),0,15,0);
//int2lcdyx(speed_cnt,0,15,0);

}							    


#define BUT0	16
#define BUT1	17
#define BUT2	18
#define BUT3	19
#define BUT4	20   
#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)|(1UL<<BUT3)|(1UL<<BUT4)

#define BUT_ON 4
#define BUT_ONL 20 

#define butLUR_  101
#define butU   253
#define butU_  125
#define butD   251
#define butD_  123
#define butL   247
#define butL_  119
#define butR   239
#define butR_  111
#define butE   254
#define butE_  126
#define butEL_  118
#define butUD  249
#define butUD_  121
#define butLR   231
#define butLR_   103
#define butED_  122
#define butER_  110


#define BUT_ON 4
#define BUT_ONL 20 
//-----------------------------------------------
void but_drv(void)
{
char i;
LPC_GPIO1->FIODIR|=(1<<21);
LPC_GPIO1->FIOPIN&=~(1<<21);
LPC_GPIO1->FIODIR&=~((1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<26));
LPC_PINCON->PINMODE3&=~((1<<12)|(1<<13)|(1<<14)|(1<<15)|(1<<16)|(1<<17)|(1<<18)|(1<<19)|(1<<20)|(1<<21));

LPC_GPIO2->FIODIR|=(1<<8);
LPC_GPIO2->FIOPIN&=~(1<<8);
for(i=0;i<200;i++)
{
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
__nop();
}

			LPC_GPIO2->FIODIR|=(1<<8);
			LPC_GPIO2->FIOPIN|=(1<<8);

but_n=((LPC_GPIO1->FIOPIN|(~((1<<22)|(1<<23)|(1<<24)|(1<<25)|(1<<26))))>>22)/*&0x0000001f*/;



if((but_n==1023UL)||(but_n!=but_s))
 	{
	speed=0;
 
   	if (((but0_cnt>=BUT_ON)||(but1_cnt!=0))&&(!l_but))
  		{
   	     n_but=1;
          but=but_s;

          }
   	if (but1_cnt>=but_onL_temp)
  		{
   	     n_but=1;
 
          but=but_s&0x7f;
          }
    	l_but=0;
   	but_onL_temp=BUT_ONL;
    	but0_cnt=0;
  	but1_cnt=0;          
     goto but_drv_out;
  	}
else if(but_n==but_s)
 	{
  	but0_cnt++;
  	if(but0_cnt>=BUT_ON)
  		{
   		but0_cnt=0;
   		but1_cnt++;
   		if(but1_cnt>=but_onL_temp)
   			{              
    			but=but_s&0x7f;
    			but1_cnt=0;
    			n_but=1;
    			     
    			l_but=1;
			if(speed)
				{
    				but_onL_temp=but_onL_temp>>1;
        			if(but_onL_temp<=2) but_onL_temp=2;
				}    
   			}
  		}
 	}
but_drv_out: 
but_s=but_n; 
   
}

//-----------------------------------------------
void but_an(void)
{
signed short temp_SS;
signed short deep,i,cap,ptr;
char av_head[4];


if(!n_but)goto but_an_end;
/*else 
	{
	plazma_but_an++;
	goto but_an_end;
	}*/
av_beep=0x0000;
av_rele=0x0000;
mnemo_cnt=MNEMO_TIME;
if((main_1Hz_cnt<10)&&((but==butU)||(but==butU_)||(but==butD)||(but==butD_)||(but==butL)||(but==butL_)||(but==butR)||(but==butR_)||(but==butE)||(but==butE_)))
	{
	__ee_spc_stat=spcOFF;
	spc_stat=spcOFF;
	}
if(but==butUD)
     {
     if(ind!=iDeb)
          {
		c_ind=a_ind;
		tree_up(iDeb,0,0,0);
		
          }
     else 
          {
		tree_down(0,0);
          }
		
		     
     }
/*else if(but==butLR)
	{
	bSILENT=1;
	beep_init(0x00000000,'S');
	}*/
else if(but==butUD_)
     {
	}

else if(but==butED_)
     {
	if(!bCAN_OFF)bCAN_OFF=1;
	else bCAN_OFF=0;
	speed=0;
	}

else if(work_stat==wsCAP)work_stat=wsOFF;

else if(ind==iDeb)
	{
	if(but==butR)
		{
		sub_ind++;
		index_set=0;
		gran_ring_char(&sub_ind,0,9);
		}
	else if(but==butL)
		{
		sub_ind--;
		index_set=0;
		gran_ring_char(&sub_ind,0,9);
		}
		
	else if(sub_ind==1)
		{
		if(but==butU)
	     	{
	     	sub_ind1--;
	     	gran_char(&sub_ind1,0,7);
	     	}
		if(but==butD)
	     	{
	     	sub_ind1++;
	     	gran_char(&sub_ind1,0,7);
	     	}
	     
		if(but==butE)
	     	{
	     	/*SET_REG(C2GSR,3,24,8);
			C2MOD=0;
			 bOUT_FREE2=1;*/

			 // CAN interface 1, use IRQVec7, at 125kbit
//can2_init(7,8,CANBitrate250k_60MHz);

// Receive message with ID 102h on CAN 1
//FullCAN_SetFilter(2,0x18e);
			 }
		if(but==butE)
	     	{
			//lc640_write_int(EE_BAT1_ZAR_CNT,10);
			ind_pointer=0;
			ind=(i_enum)0;
			sub_ind=0;
			sub_ind1=0;
			sub_ind2=0;
			index_set=0;
			}
	     
			
		}
		
	 else if(sub_ind==5)
	 	{
		if(but==butE_)
		{
		//can1_init(BITRATE62_5K6_25MHZ);
		//FullCAN_SetFilter(0,0x18e);
		LPC_CAN1->MOD&=~(1<<0);
		}
		}
		
		
		
			
     else if(but==butU)
	     {
	     index_set--;
	     gran_char(&index_set,0,4);
	     //lc640_write_int(ptr_ki_src[0],lc640_read_int(ptr_ki_src[0])+10);
	     }	
     else if(but==butD)
	     {
	     index_set++;
	     gran_char(&index_set,0,4); 
	     //lc640_write_int(ptr_ki_src[0],lc640_read_int(ptr_ki_src[0])-10);
	     }	
     else if(but==butE)
         	{
          //a=b[--ptr_ind];
          can1_out(1,2,3,4,5,6,7,8);
          }   
          
     else if(but==butE_)
         	{
          //a=b[--ptr_ind];
          can1_out_adr(TXBUFF,3);
          }                      				
	}

else if(ind==iMn)
	{
	if(but==butD_)can1_init(BITRATE62_5K25MHZ);//                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
     unet_drv_cnt=0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
 
	
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    //tree_up(iLan_set ,0,0,0);
	if(main_menu_mode==mmmIT)
		{
		if(but==butD)
			{
			sub_ind++;
			if(sub_ind==3)
				{
				sub_ind++;
				}
	
/*			if(sub_ind==7)
				{
				sub_ind++;
				} */
			
			gran_char(&sub_ind,0,7);
			}
			
		else if(but==butU)
			{
			sub_ind--;
			if(sub_ind==3)
				{
				sub_ind--;
				}
	
/*			if(sub_ind==7)
				{
				sub_ind--;
				}*/
						
			gran_char(&sub_ind,0,7);
			}	
		
	
/*		else if(but==butE_)
			{
			bRESET=1;//tree_up(iK_bps_sel,0,0,0);
			}*/
		else if(sub_ind==0)
			{
			if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
				/*---work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=0;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;*/
					}			
				else 
					{
					stop_proc();
				/*---work_stat=wsOFF;
					restart_off();*/
					}
				}
			if((but==butR)&&(REV_IS_ON))
				{
				if(work_stat!=wsGS)
					{
					if(REV_STAT!=rsFF)
						{
						REV_STAT=rsFF;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
			if((but==butL)&&(REV_IS_ON))
				{
				if(work_stat!=wsGS)
					{
					if(REV_STAT!=rsREW)
						{
						REV_STAT=rsREW;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
		  	}
	
		else if(sub_ind==1) {
			if((REV_IS_ON)&&(AVT_REV_IS_ON)) {
				if(work_stat==wsGS) { /*
					if(REV_STAT==rsFF) {
						if(but==butR) {
							AVT_REV_I_NOM_FF++;
						    	gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
							lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
							speed__=0;
						} else if(but==butR_) {
							speed__++;
							if(speed__<50) {
								AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/5)+1)*5;
						    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
								lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
								speed=1;
							} else {
								AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/50)+1)*50;
						    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
								lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
								speed=1;
							}
							speed=1;
						} else if(but==butL) {
							AVT_REV_I_NOM_FF--;
						    	gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
							lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
							speed__=0;
						} else if(but==butL_) {
							speed__++;
							if(speed__<50) {
								AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/5)-1)*5;
						    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
								lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
								speed=1;
							} else {
								AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/50)-1)*50;
						    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
								lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
								speed=1;
							}
							speed=1;
						}
					}*/
				}
			} else if(fiks_stat_I==0){
				if(but==butR) {
			    		if(I_ug<1000)I_ug++;
					else I_ug=((I_ug/10)+1)*10;
			    		gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed__=0;
				} else if(but==butR_) {
					speed__++;
					if(speed__<50)	{
						if(I_ug<1000)I_ug=((I_ug/5)+1)*5;
						else I_ug=((I_ug/10)+1)*10;
			    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
						lc640_write_int(EE_I_UG,I_ug);
						speed=1;
					} else {
						I_ug=((I_ug/50)+1)*50;
			    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
						lc640_write_int(EE_I_UG,I_ug);
						speed=1;
					}
					speed=1;
				} else if(but==butL) {
					if(I_ug<1000)I_ug--;
					else I_ug=((I_ug/10)-1)*10;
			    		gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed__=0;
				} else if(but==butL_) {
					speed__++;
					if(speed__<50)	{
						if(I_ug<1000)I_ug=((I_ug/5)-1)*5;
						else I_ug=((I_ug/10)-1)*10;
			    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
						lc640_write_int(EE_I_UG,I_ug);
						speed=1;
					} else {
						I_ug=((I_ug/50)-1)*50;
			    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
						lc640_write_int(EE_I_UG,I_ug);
						speed=1;
					}
					speed=1;
				}
			}
			if(but==butE) {
				if(work_stat!=wsGS)	{
					start_GS();
				/*---	work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=0;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					//avt_rev_start();*/
				} else {
					stop_proc();
				/*---	work_stat=wsOFF;
					restart_off();*/
				}
			}
			if(but==butLR)	{
				if(work_stat==wsGS)	{
					fiks_stat_I++;
					gran_ring(&fiks_stat_I,0,2);
				}
			}
			speed=1;
		}
	
		else if(sub_ind==2)
			{
			if(but==butR)
				{
				T_PROC_GS++;
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_GS=(((T_PROC_GS/10L)+1L)*10L);
					}
				else 
					{
					T_PROC_GS=(((T_PROC_GS/60L)+1L)*60L);
					}
				speed=1;
				}
			else if(but==butL)
				{
				T_PROC_GS--;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_GS=(((T_PROC_GS/10L)-1L)*10L);
					
					}
				else 
					{
					T_PROC_GS=(((T_PROC_GS/60L)-1L)*60L);
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=0;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
				}

			
			if(T_PROC_GS>T_PROC_MAX)								 	//Если устанавливаем врямя процесса
				{												//для источника тока больше чем 
				T_PROC_GS=T_PROC_MAX+1;								//максимальное время процессов
				if(T_PROC_GS_MODE!=1)								//(из главных установок) то 
					{											//устанавливается режим непрерывной 
					T_PROC_GS_MODE=1;								//работы(T_PROC_GS_MODE=1), при попытке
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);	//вернуть время в разрешенный интеравал - 
					}											//режим непрерывной работы снимается 
				}												//(T_PROC_GS_MODE=0)
	
			else if(T_PROC_GS<30)
				{
				T_PROC_GS=29;
				if(T_PROC_GS_MODE!=1)
					{
					T_PROC_GS_MODE=1;
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);
					}
				}
			else 
				{
				if(T_PROC_GS_MODE!=0)
					{
					T_PROC_GS_MODE=0;
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);
					}
				}
												
			//gran_long(&T_PROC_GS,30,T_PROC_MAX);
			lc640_write_long(EE_T_PROC_GS,T_PROC_GS);
			
			}

		else if((sub_ind==4)&&(work_stat==wsOFF)) {
			temp_SS=lc640_read_int(EE_U_MAX_G);
		     if(but==butR) {
				if(temp_SS<1000) {
					temp_SS++;
				} else {
					temp_SS=((temp_SS/10)+1)*10;
				}	
		     }
		     else if(but==butR_) {
		     	temp_SS=((temp_SS/10)+1)*10;
		     }	
		     else if(but==butL) {
				if(temp_SS<1000) {
					temp_SS--;
				} else {
					temp_SS=((temp_SS/10)-1)*10;
				}	
			}
		     else if(but==butL_) {
		     	temp_SS=((temp_SS/10)-1)*10;
		     }
		    	gran(&temp_SS,U_MIN,U_MAX);
			lc640_write_int(EE_U_MAX_G,temp_SS);					
			speed=1;	
		}
		else if(sub_ind==5)
		    	{
			if(but==butE)sub_ind=0;
		    	}
		else if(sub_ind==6)
		    	{
			if(but==butE)
				{
				tree_up(iSet_prl,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==7)
		    	{
			if(but==butE)
				{
				tree_up(iBps,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==7)
		    	{
			if(but==butE)
				{
				tree_up(iK_prl,0,0,0);
				parol_init();
				}
		    	}
		}

	else if(main_menu_mode==mmmIN)
		{
		if(but==butD)
			{
			sub_ind++;
			if(sub_ind==3)
				{
				sub_ind++;
				}
	
			gran_char(&sub_ind,0,7);
			}
			
		else if(but==butU)
			{
			sub_ind--;
			if(sub_ind==3)
				{
				sub_ind--;
				}
		
			gran_char(&sub_ind,0,7);
			}	
	
	
	/*	else if(but==butE_)
			{
			bRESET=1;//tree_up(iK_bps_sel,0,0,0);
			}*/
	
		else if(sub_ind==0)
			{
			if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					/*work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=0;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0; */
					start_PS();
					}			
				else
					{
					stop_proc();
					/*work_stat=wsOFF;
					restart_off();*/
					}
				}

			if((but==butR)&&(REV_IS_ON))
				{
				if(work_stat!=wsPS)
					{
					if(REV_STAT!=rsFF)
						{
						REV_STAT=rsFF;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
			if((but==butL)&&(REV_IS_ON))
				{
				if(work_stat!=wsPS)
					{
					if(REV_STAT!=rsREW)
						{
						REV_STAT=rsREW;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
		  	}
		else if(sub_ind==1)
			{
			if(but==butR)
				{
		    		U_up++;
		    		gran(&U_up,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP,U_up);
				speed__=0;
				find_U_curve(U_up);
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<50)
					{
					U_up=((U_up/5)+1)*5;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
					}
				else 
					{
					U_up=((U_up/50)+1)*50;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
					}
				speed=1;
				}

			else if(but==butL)
				{
		    		U_up--;
		    		gran(&U_up,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP,U_up);
				speed__=0;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<50)
					{
					U_up=((U_up/5)-1)*5;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
					}
				else 
					{
					U_up=((U_up/50)-1)*50;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=0;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
				}
			else if(but==butLR)
				{
				if(work_stat==wsPS)
					{
					fiks_stat_U++;
					gran_ring(&fiks_stat_U,0,2);
					}
				}
			speed=1;
			}
	
		else if(sub_ind==2)
			{
			if(but==butR)
				{
				T_PROC_PS++;
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_PS=(((T_PROC_PS/10L)+1L)*10L);
					}
				else 
					{
					T_PROC_PS=(((T_PROC_PS/60L)+1L)*60L);
					}
				speed=1;
				}
			else if(but==butL)
				{
				T_PROC_PS--;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_PS=(((T_PROC_PS/10L)-1L)*10L);
					
					}
				else 
					{
					T_PROC_PS=(((T_PROC_PS/60L)-1L)*60L);
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=0;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
				}

			
			if(T_PROC_PS>T_PROC_MAX)								 	//Если устанавливаем врямя процесса
				{												//для источника тока больше чем 
				T_PROC_PS=T_PROC_MAX+1;								//максимальное время процессов
				if(T_PROC_PS_MODE!=1)								//(из главных установок) то 
					{											//устанавливается режим непрерывной 
					T_PROC_PS_MODE=1;								//работы(T_PROC_PS_MODE=1), при попытке
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);	//вернуть время в разрешенный интеравал - 
					}											//режим непрерывной работы снимается 
				}												//(T_PROC_PS_MODE=0)
	
			else if(T_PROC_PS<30)
				{
				T_PROC_PS=29;
				if(T_PROC_PS_MODE!=1)
					{
					T_PROC_PS_MODE=1;
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);
					}
				}
			else 
				{
				if(T_PROC_PS_MODE!=0)
					{
					T_PROC_PS_MODE=0;
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);
					}
				}
												
			//gran_long(&T_PROC_PS,30,T_PROC_MAX);
			lc640_write_long(EE_T_PROC_PS,T_PROC_PS);
			
			}

		else if((sub_ind==4)&&(work_stat==wsOFF)) {
			if(but==butR) {
		    		if(I_maxp<1000)I_maxp++;
				else I_maxp=((I_maxp/10)+1)*10;
				gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_MAX_P,I_maxp);
				speed__=0;
			} else if(but==butR_) {
				speed__++;
				if(speed__<50)	{
					if(I_maxp<1000)I_maxp=((I_maxp/5)+1)*5;
					else I_maxp=((I_maxp/10)+1)*10;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				} else {
					I_maxp=((I_maxp/50)+1)*50;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				}
				speed=1;
			} else if(but==butL) {
		    		if(I_maxp<1000)I_maxp--;
				else I_maxp=((I_maxp/10)-1)*10;
		    		gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_MAX_P,I_maxp);
				speed__=0;
			} else if(but==butL_) {
				speed__++;
				if(speed__<50)	{
					if(I_maxp<1000)I_maxp=((I_maxp/5)-1)*5;
					else I_maxp=((I_maxp/10)-1)*10;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				} else {
					I_maxp=((I_maxp/50)-1)*50;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				}
				speed=1;
			}
		}
		else if(sub_ind==5)
		    	{
			if(but==butE)sub_ind=0;
		    	}
		else if(sub_ind==6)
		    	{
			if(but==butE)
				{
				tree_up(iSet_prl,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==7)
		    	{
			if(but==butE)
				{
				tree_up(iBps,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==7)
		    	{
			if(but==butE)
				{
				tree_up(iK_prl,0,0,0);
				parol_init();
				}
		    	}
		}
	else if(main_menu_mode==mmmITIN)
		{
		if(but==butD)
			{
			sub_ind++;
			if(sub_ind==3)
				{
				sub_ind++;
				}
	
			if(sub_ind==7)
				{
				sub_ind++;
				}
			
			gran_char(&sub_ind,0,12);
			}
			
		else if(but==butU)
			{
			sub_ind--;
			if(sub_ind==3)
				{
				sub_ind--;
				}
	
			if(sub_ind==7)
				{
				sub_ind--;
				}
						
			gran_char(&sub_ind,0,12);
			}	
	
	
	/*	else if(but==butE_)
			{
			bRESET=1;//tree_up(iK_bps_sel,0,0,0);
			}*/
		else if(sub_ind==0)
			{
			if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=0;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=0;
					index_set=0;*/
					}			
				else 
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();
					*/
					}
				}

			if((but==butR)&&(REV_IS_ON))
				{
				if(work_stat!=wsGS)
					{
					if(REV_STAT!=rsFF)
						{
						REV_STAT=rsFF;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
			if((but==butL)&&(REV_IS_ON))
				{
				if(work_stat!=wsGS)
					{
					if(REV_STAT!=rsREW)
						{
						REV_STAT=rsREW;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
		  	}
	
		else if(sub_ind==1)
			{
			if(but==butR)
				{
		    		I_ug++;
		    		gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG,I_ug);
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<50)
					{
					I_ug=((I_ug/5)+1)*5;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				else 
					{
					I_ug=((I_ug/50)+1)*50;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				speed=1;
				}

			else if(but==butL)
				{
		    		I_ug--;
		    		gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG,I_ug);
				speed__=0;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<50)
					{
					I_ug=((I_ug/5)-1)*5;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				else 
					{
					I_ug=((I_ug/50)-1)*50;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=0;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=0;
					index_set=0;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();
					*/
					}
				}
			if(but==butLR)	{
				if(work_stat==wsGS)	{
					fiks_stat_I++;
					gran_ring(&fiks_stat_I,0,2);
				}
			}
			speed=1;
			}
	
		else if(sub_ind==2)
			{
			if(but==butR)
				{
				T_PROC_GS++;
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_GS=(((T_PROC_GS/10L)+1L)*10L);
					}
				else 
					{
					T_PROC_GS=(((T_PROC_GS/60L)+1L)*60L);
					}
				speed=1;
				}
			else if(but==butL)
				{
				T_PROC_GS--;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_GS=(((T_PROC_GS/10L)-1L)*10L);
					
					}
				else 
					{
					T_PROC_GS=(((T_PROC_GS/60L)-1L)*60L);
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=0;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=0;
					index_set=0;
					*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();
					*/
					}
				}

			
			if(T_PROC_GS>T_PROC_MAX)								 	//Если устанавливаем врямя процесса
				{												//для источника тока больше чем 
				T_PROC_GS=T_PROC_MAX+1;								//максимальное время процессов
				if(T_PROC_GS_MODE!=1)								//(из главных установок) то 
					{											//устанавливается режим непрерывной 
					T_PROC_GS_MODE=1;								//работы(T_PROC_GS_MODE=1), при попытке
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);	//вернуть время в разрешенный интеравал - 
					}											//режим непрерывной работы снимается 
				}												//(T_PROC_GS_MODE=0)
	
			else if(T_PROC_GS<30)
				{
				T_PROC_GS=29;
				if(T_PROC_GS_MODE!=1)
					{
					T_PROC_GS_MODE=1;
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);
					}
				}
			else 
				{
				if(T_PROC_GS_MODE!=0)
					{
					T_PROC_GS_MODE=0;
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);
					}
				}
												
			//gran_long(&T_PROC_GS,30,T_PROC_MAX);
			lc640_write_long(EE_T_PROC_GS,T_PROC_GS);
			
			}
	
		else if(sub_ind==4)
			{
			if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=4;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=4;
					index_set=4; */
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
				}

			if((but==butR)&&(REV_IS_ON))
				{
				if(work_stat!=wsPS)
					{
					if(REV_STAT!=rsFF)
						{
						REV_STAT=rsFF;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
			if((but==butL)&&(REV_IS_ON))
				{
				if(work_stat!=wsPS)
					{
					if(REV_STAT!=rsREW)
						{
						REV_STAT=rsREW;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}


		  	}
		else if(sub_ind==5) {
			if(but==butR) {
		    		if(U_up<1000)U_up++;
				else U_up=((U_up/10)+1)*10;
		    		gran(&U_up,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP,U_up);
				speed__=0;
			} else if(but==butR_) {
				speed__++;
				if(speed__<50)	{
					if(U_up<1000)U_up=((U_up/5)+1)*5;
					else U_up=((U_up/10)+1)*10;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				} else {
					U_up=((U_up/50)+1)*50;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				}
				speed=1;
			} else if(but==butL) {
		    		if(U_up<1000)U_up--;
				else U_up=((U_up/10)-1)*10;
		    		gran(&U_up,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP,U_up);
				speed__=0;
			} else if(but==butL_) {
				speed__++;
				if(speed__<50)	{
					if(U_up<1000)U_up=((U_up/5)-1)*5;
					else U_up=((U_up/10)-1)*10;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				} else {
					U_up=((U_up/50)-1)*50;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				}
				speed=1;
			} else if(but==butE) {
				if(work_stat!=wsPS)	{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=4;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=4;
					index_set=4; */
				} else {
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
				}
			}
			else if(but==butLR)
				{
				if(work_stat==wsPS)
					{
					fiks_stat_U++;
					gran_ring(&fiks_stat_U,0,2);
					}
				}
			speed=1;
		}
	
		else if(sub_ind==6)
			{
			if(but==butR)
				{
				T_PROC_PS++;
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_PS=(((T_PROC_PS/10L)+1L)*10L);
					}
				else 
					{
					T_PROC_PS=(((T_PROC_PS/60L)+1L)*60L);
					}
				speed=1;
				}
			else if(but==butL)
				{
				T_PROC_PS--;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_PS=(((T_PROC_PS/10L)-1L)*10L);
					
					}
				else 
					{
					T_PROC_PS=(((T_PROC_PS/60L)-1L)*60L);
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=4;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=4;
					index_set=4;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();	*/
					}
				}

			
			if(T_PROC_PS>T_PROC_MAX)								 	//Если устанавливаем врямя процесса
				{												//для источника тока больше чем 
				T_PROC_PS=T_PROC_MAX+1;								//максимальное время процессов
				if(T_PROC_PS_MODE!=1)								//(из главных установок) то 
					{											//устанавливается режим непрерывной 
					T_PROC_PS_MODE=1;								//работы(T_PROC_PS_MODE=1), при попытке
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);	//вернуть время в разрешенный интеравал - 
					}											//режим непрерывной работы снимается 
				}												//(T_PROC_PS_MODE=0)
	
			else if(T_PROC_PS<30)
				{
				T_PROC_PS=29;
				if(T_PROC_PS_MODE!=1)
					{
					T_PROC_PS_MODE=1;
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);
					}
				}
			else 
				{
				if(T_PROC_PS_MODE!=0)
					{
					T_PROC_PS_MODE=0;
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);
					}
				}
												
			//gran_long(&T_PROC_PS,30,T_PROC_MAX);
			lc640_write_long(EE_T_PROC_PS,T_PROC_PS);
			
			}

		else if((sub_ind==8)&&(work_stat==wsOFF)) {
			temp_SS=lc640_read_int(EE_U_MAX_G);
		     if(but==butR) {
				if(temp_SS<1000) {
					temp_SS++;
				} else {
					temp_SS=((temp_SS/10)+1)*10;
				}	
		     }
		     else if(but==butR_) {
		     	temp_SS=((temp_SS/10)+1)*10;
		     }	
		     else if(but==butL) {
				if(temp_SS<1000) {
					temp_SS--;
				} else {
					temp_SS=((temp_SS/10)-1)*10;
				}	
			}
		     else if(but==butL_) {
		     	temp_SS=((temp_SS/10)-1)*10;
		     }
		    	gran(&temp_SS,U_MIN,U_MAX);
			lc640_write_int(EE_U_MAX_G,temp_SS);					
			speed=1;	
		}
		else if((sub_ind==9)&&(work_stat==wsOFF)){
			if(but==butR) {
		    		if(I_maxp<1000)I_maxp++;
				else I_maxp=((I_maxp/10)+1)*10;
				gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_MAX_P,I_maxp);
				speed__=0;
			} else if(but==butR_) {
				speed__++;
				if(speed__<50)	{
					if(I_maxp<1000)I_maxp=((I_maxp/5)+1)*5;
					else I_maxp=((I_maxp/10)+1)*10;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				} else {
					I_maxp=((I_maxp/50)+1)*50;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				}
				speed=1;
			} else if(but==butL) {
		    		if(I_maxp<1000)I_maxp--;
				else I_maxp=((I_maxp/10)-1)*10;
		    		gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_MAX_P,I_maxp);
				speed__=0;
			} else if(but==butL_) {
				speed__++;
				if(speed__<50)	{
					if(I_maxp<1000)I_maxp=((I_maxp/5)-1)*5;
					else I_maxp=((I_maxp/10)-1)*10;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				} else {
					I_maxp=((I_maxp/50)-1)*50;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				}
				speed=1;
			}
		}
		else if(sub_ind==10)
		    {
			if(but==butE)sub_ind=0;
		    }
		else if(sub_ind==11)
		    {
			if(but==butE)
				{
				tree_up(iSet_prl,0,0,0);
				parol_init();
				}
		    }
		else if(sub_ind==12)
		    	{
			if(but==butE)
				{
				tree_up(iBps,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==12)
		    {
			if(but==butE)
				{
				tree_up(iK_prl,0,0,0);
				parol_init();
				}
		    	}
		}
	else /*if(main_menu_mode==mmmINIT)*/
		{
		if(but==butD)
			{
			sub_ind++;
			if(sub_ind==3)
				{
				sub_ind++;
				}
	
			if(sub_ind==7)
				{
				sub_ind++;
				}
			
			gran_char(&sub_ind,0,12);
			}
			
		else if(but==butU)
			{
			sub_ind--;
			if(sub_ind==3)
				{
				sub_ind--;
				}
	
			if(sub_ind==7)
				{
				sub_ind--;
				}
						
			gran_char(&sub_ind,0,12);
			}	
	
	
/*		else if(but==butE_)
			{
			bRESET=1;//tree_up(iK_bps_sel,0,0,0);
			} */
		else if(sub_ind==0)
			{
			if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=0;
					/*restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=0;
					index_set=0;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();
					*/
					}
				}

			if((but==butR)&&(REV_IS_ON))
				{
				if(work_stat!=wsPS)
					{
					if(REV_STAT!=rsFF)
						{
						REV_STAT=rsFF;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
			if((but==butL)&&(REV_IS_ON))
				{
				if(work_stat!=wsPS)
					{
					if(REV_STAT!=rsREW)
						{
						REV_STAT=rsREW;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
		  	}
		else if(sub_ind==1) {
			if(but==butR) {
		    		if(U_up<1000)U_up++;
				else U_up=((U_up/10)+1)*10;
		    		gran(&U_up,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP,U_up);
				speed__=0;
			} else if(but==butR_) {
				speed__++;
				if(speed__<50)	{
					if(U_up<1000)U_up=((U_up/5)+1)*5;
					else U_up=((U_up/10)+1)*10;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				} else {
					U_up=((U_up/50)+1)*50;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				}
				speed=1;
			} else if(but==butL) {
		    		if(U_up<1000)U_up--;
				else U_up=((U_up/10)-1)*10;
		    		gran(&U_up,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP,U_up);
				speed__=0;
			} else if(but==butL_) {
				speed__++;
				if(speed__<50)	{
					if(U_up<1000)U_up=((U_up/5)-1)*5;
					else U_up=((U_up/10)-1)*10;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				} else {
					U_up=((U_up/50)-1)*50;
		    			gran(&U_up,U_MIN,U_MAX);
					lc640_write_int(EE_U_UP,U_up);
					speed=1;
				}
				speed=1;
			} else if(but==butE) {
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=0;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=0;
					index_set=0;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
			}
			else if(but==butLR)
				{
				if(work_stat==wsPS)
					{
					fiks_stat_U++;
					gran_ring(&fiks_stat_U,0,2);
					}
				}

			speed=1;
		}
	
		else if(sub_ind==2)
			{
			if(but==butR)
				{
				T_PROC_PS++;
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_PS=(((T_PROC_PS/10L)+1L)*10L);
					}
				else 
					{
					T_PROC_PS=(((T_PROC_PS/60L)+1L)*60L);
					}
				speed=1;
				}
			else if(but==butL)
				{
				T_PROC_PS--;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_PS=(((T_PROC_PS/10L)-1L)*10L);
					
					}
				else 
					{
					T_PROC_PS=(((T_PROC_PS/60L)-1L)*60L);
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsPS)
					{
					start_PS();
					/*
					work_stat=wsPS;
					time_proc=0;
					time_proc_remain=T_PROC_PS;
					*/
					index_set=0;
					/*
					restart_on_PS();
					bFAST_REG=1;
					bU_VALID=0;
 					sub_ind=0;
					index_set=0; */
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
				}

			
			if(T_PROC_PS>T_PROC_MAX)								 	//Если устанавливаем врямя процесса
				{												//для источника тока больше чем 
				T_PROC_PS=T_PROC_MAX+1;								//максимальное время процессов
				if(T_PROC_PS_MODE!=1)								//(из главных установок) то 
					{											//устанавливается режим непрерывной 
					T_PROC_PS_MODE=1;								//работы(T_PROC_PS_MODE=1), при попытке
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);	//вернуть время в разрешенный интеравал - 
					}											//режим непрерывной работы снимается 
				}												//(T_PROC_PS_MODE=0)
	
			else if(T_PROC_PS<30)
				{
				T_PROC_PS=29;
				if(T_PROC_PS_MODE!=1)
					{
					T_PROC_PS_MODE=1;
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);
					}
				}
			else 
				{
				if(T_PROC_PS_MODE!=0)
					{
					T_PROC_PS_MODE=0;
					lc640_write_int(EE_T_PROC_PS_MODE,T_PROC_PS_MODE);
					}
				}
												
			//gran_long(&T_PROC_PS,30,T_PROC_MAX);
			lc640_write_long(EE_T_PROC_PS,T_PROC_PS);
			
			}
	
		else if(sub_ind==4)
			{
			if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=4;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=4;
					index_set=4;*/
					}			
				else 
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();	*/
					}
				}
			if((but==butR)&&(REV_IS_ON))
				{
				if(work_stat!=wsGS)
					{
					if(REV_STAT!=rsFF)
						{
						REV_STAT=rsFF;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}
			if((but==butL)&&(REV_IS_ON))
				{
				if(work_stat!=wsGS)
					{
					if(REV_STAT!=rsREW)
						{
						REV_STAT=rsREW;
						lc640_write_int(EE_REV_STAT,REV_STAT);
						}
					}
				}

		  	}
		else if(sub_ind==5)
			{
			if(but==butR)
				{
		    		I_ug++;
		    		gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG,I_ug);
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<50)
					{
					I_ug=((I_ug/5)+1)*5;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				else 
					{
					I_ug=((I_ug/50)+1)*50;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				speed=1;
				}

			else if(but==butL)
				{
		    		I_ug--;
		    		gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG,I_ug);
				speed__=0;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<50)
					{
					I_ug=((I_ug/5)-1)*5;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				else 
					{
					I_ug=((I_ug/50)-1)*50;
		    			gran(&I_ug,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_UG,I_ug);
					speed=1;
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=4;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=4;
					index_set=4;*/
					}			
				else
					{
					stop_proc();
					/*work_stat=wsOFF;
					restart_off();*/
					}
				}
			if(but==butLR)	{
				if(work_stat==wsGS)	{
					fiks_stat_I++;
					gran_ring(&fiks_stat_I,0,2);
				}
			}
			speed=1;
			}
	
		else if(sub_ind==6)
			{
			if(but==butR)
				{
				T_PROC_GS++;
				speed__=0;
				}
			else if(but==butR_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_GS=(((T_PROC_GS/10L)+1L)*10L);
					}
				else 
					{
					T_PROC_GS=(((T_PROC_GS/60L)+1L)*60L);
					}
				speed=1;
				}
			else if(but==butL)
				{
				T_PROC_GS--;
				}
			else if(but==butL_)
				{
				speed__++;
				if(speed__<20)
					{
					T_PROC_GS=(((T_PROC_GS/10L)-1L)*10L);
					
					}
				else 
					{
					T_PROC_GS=(((T_PROC_GS/60L)-1L)*60L);
					}
				speed=1;
				}

			else if(but==butE)
				{
				if(work_stat!=wsGS)
					{
					start_GS();
					/*
					work_stat=wsGS;
					time_proc=0;
					time_proc_remain=T_PROC_GS;
					*/
					index_set=4;
					/*
					restart_on_GS();
					bFAST_REG=1;
					bU_VALID=0;
					sub_ind=4;
					index_set=4;*/
					}			
				else
					{
					stop_proc();
					/*
					work_stat=wsOFF;
					restart_off();*/
					}
				}

			
			if(T_PROC_GS>T_PROC_MAX)								 	//Если устанавливаем врямя процесса
				{												//для источника тока больше чем 
				T_PROC_GS=T_PROC_MAX+1;								//максимальное время процессов
				if(T_PROC_GS_MODE!=1)								//(из главных установок) то 
					{											//устанавливается режим непрерывной 
					T_PROC_GS_MODE=1;								//работы(T_PROC_GS_MODE=1), при попытке
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);	//вернуть время в разрешенный интеравал - 
					}											//режим непрерывной работы снимается 
				}												//(T_PROC_GS_MODE=0)
	
			else if(T_PROC_GS<30)
				{
				T_PROC_GS=29;
				if(T_PROC_GS_MODE!=1)
					{
					T_PROC_GS_MODE=1;
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);
					}
				}
			else 
				{
				if(T_PROC_GS_MODE!=0)
					{
					T_PROC_GS_MODE=0;
					lc640_write_int(EE_T_PROC_GS_MODE,T_PROC_GS_MODE);
					}
				}
												
			//gran_long(&T_PROC_GS,30,T_PROC_MAX);
			lc640_write_long(EE_T_PROC_GS,T_PROC_GS);
			
			}

		else if((sub_ind==8)&&(work_stat==wsOFF)) {
			temp_SS=lc640_read_int(EE_U_MAX_G);
		     if(but==butR) {
				if(temp_SS<1000) {
					temp_SS++;
				} else {
					temp_SS=((temp_SS/10)+1)*10;
				}	
		     }
		     else if(but==butR_) {
		     	temp_SS=((temp_SS/10)+1)*10;
		     }	
		     else if(but==butL) {
				if(temp_SS<1000) {
					temp_SS--;
				} else {
					temp_SS=((temp_SS/10)-1)*10;
				}	
			}
		     else if(but==butL_) {
		     	temp_SS=((temp_SS/10)-1)*10;
		     }
		    	gran(&temp_SS,U_MIN,U_MAX);
			lc640_write_int(EE_U_MAX_G,temp_SS);					
			speed=1;	
		}
		else if((sub_ind==9)&&(work_stat==wsOFF)) {
			if(but==butR) {
		    		if(I_maxp<1000)I_maxp++;
				else I_maxp=((I_maxp/10)+1)*10;
				gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_MAX_P,I_maxp);
				speed__=0;
			} else if(but==butR_) {
				speed__++;
				if(speed__<50)	{
					if(I_maxp<1000)I_maxp=((I_maxp/5)+1)*5;
					else I_maxp=((I_maxp/10)+1)*10;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				} else {
					I_maxp=((I_maxp/50)+1)*50;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				}
				speed=1;
			} else if(but==butL) {
		    		if(I_maxp<1000)I_maxp--;
				else I_maxp=((I_maxp/10)-1)*10;
		    		gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_MAX_P,I_maxp);
				speed__=0;
			} else if(but==butL_) {
				speed__++;
				if(speed__<50)	{
					if(I_maxp<1000)I_maxp=((I_maxp/5)-1)*5;
					else I_maxp=((I_maxp/10)-1)*10;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				} else {
					I_maxp=((I_maxp/50)-1)*50;
		    			gran(&I_maxp,I_MIN_IPS,I_MAX_IPS);
					lc640_write_int(EE_I_MAX_P,I_maxp);
					speed=1;
				}
				speed=1;
			}
		}
		else if(sub_ind==10)
		    	{
			if(but==butE)sub_ind=0;
		    	}
		else if(sub_ind==11)
		    	{
			if(but==butE)
				{
				tree_up(iSet_prl,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==12)
		    	{
			if(but==butE)
				{
				tree_up(iBps,0,0,0);
				parol_init();
				}
		    	}
		else if(sub_ind==12)
		    {
			if(but==butE)
				{
				tree_up(iK_prl,0,0,0);
				parol_init();
				}
		    	}
		}
	}




else if(ind==iBps)
	{
	ret(1000);
	if (but==butU)
		{      
		sub_ind--;
		/*if(NUMIST>=3)*/gran_char(&sub_ind,0,NUMIST-2);
		//else gran_char(&sub_ind,0,0);
		}
		
	else if (but==butD)
		{
		sub_ind++;
		/*if(NUMIST>=3)*/gran_char(&sub_ind,0,NUMIST-2);
		//else gran_char(&sub_ind,0,0);
		
		}

	else if((but==butE)&&(sub_ind==(NUMIST-2)))
		{
	     tree_down(0,0);
	     ret(0);
		}
	}
else if(ind==iEnerg)
	{
	ret(1000);
	if (but==butU)
		{      
		sub_ind--;
		gran_char(&sub_ind,0,4);
		}
		
	else if (but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,4);		
		}

	else if((but==butE)&&(sub_ind==4))
		{
	     tree_down(0,0);
	     ret(0);
		}
     }

else if(ind==iEnerg3)
	{
	ret(1000);
	if (but==butU)
		{      
		sub_ind--;
		gran_char(&sub_ind,0,8);
		}
		
	else if (but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,8);		
		}

	else if((but==butE)&&(sub_ind==8))
		{
	     tree_down(0,0);
	     ret(0);
		}
     }

else if((ind==iSet_prl)||(ind==iK_prl))
	{
	ret(50);
	if(but==butR)
		{
		sub_ind++;
		gran_ring_char(&sub_ind,0,2);
		}
	else if(but==butL)
		{
		sub_ind--;
		gran_ring_char(&sub_ind,0,2);
		}	
	else if(but==butU)
		{
		parol[sub_ind]++;
		gran_ring_char(&parol[sub_ind],0,9);
		}	
	else if(but==butD)
		{
		parol[sub_ind]--;
		gran_ring_char(&parol[sub_ind],0,9);
		}	
	else if(but==butE)
		{
		unsigned short tempU;
		tempU=parol[2]+(parol[1]*10U)+(parol[0]*100U);
		
		if(ind==iSet_prl)
			{
	     	if(tempU==PAROL_SET) 
				{
				tree_down(0,0);
				tree_up(iSet,0,0,0);
				ret(1000);
				}
			else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"     неверный!!!    ",
	          			"                    ",1000);
				}
			}
		else	if(ind==iK_prl)
			{
	     	if(tempU==PAROL_KALIBR) 
				{
				tree_down(0,0);
				tree_up(iK,0,0,0);
				ret(1000);
				
				}
			else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"     неверный!!!    ",
	          			"                    ",1000);
				}
			} 
	
		else	if(ind==iAusw_prl)
			{
	     	if(tempU==PAROL_AUSW) 
				{
				tree_down(0,0);
				tree_up(iAusw_set,1,0,0);
				default_temp=10;
				ret(0);
				}
			else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"     неверный!!!    ",
	          			"                    ",1000);
				}
			} 	
			
		else	if(ind==iSet_st_prl)
			{
	     	if(tempU==PAROL_DEFAULT) 
				{
	//			ind=iDefault;
				sub_ind=1;
				index_set=0;
				default_temp=10;
				}
			else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"     неверный!!!    ",
	          			"                    ",1000);
				}
			} 
						

		else if(ind==iSpc_prl_ke)
			{
			if(tempU==PAROL_KE) 
				{
				char temp;
				temp=sub_ind1;
				tree_down(0,0);
				tree_up(iKe,0,0,temp);
				ret(1000);
				}
	  		else 
				{	
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"     неверный!!!    ",
	          			"                    ",1000);
				}
			}
		else if(ind==iSpc_prl_vz)
			{
			if(tempU==PAROL_VZ) 
				{
				tree_down(0,0);
				tree_up(iVz,0,0,0);
				ret(1000);
				}
	  		else 
				{
		          tree_down(0,0);
	    	          show_mess("                    ",
	          			"       Пароль       ",
	          			"     неверный!!!    ",
	          			"                    ",1000);
				}     	          
			}
		}
	}

else if(ind==iSpc)
	{
	//ret_ind(0,0,0);
	//ret_ind_sec(iMn,60);
	ret(1000);
	if (but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,4);
		}
	else if (but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,4);
		}
	else if(but==butE)
		{
		if(sub_ind==0)
			{   
               tree_up(iSpc_prl_vz,0,0,0);
			parol_init();
			}
		else if(sub_ind==1)
			{
               tree_up(iAvz,0,0,0);
               parol_init();
			}			
		else if((sub_ind==2)||(sub_ind==3))
			{
               tree_up(iSpc_prl_ke,0,0,sub_ind-2);
              	parol_init();
			} 
	/*	else if(sub_ind==4)
			{
			tree_up(iAKE,0,0,0);
			}	
		else if(sub_ind==5)
			{
			tree_up(iAKE,0,0,1);
			}*/						
		else if(sub_ind==4)
			{
			tree_down(0,0);
			ret(0);
			}	
		}
	else if(but==butL)
		{
		tree_down(0,0);
		ret(0);
		}			
	}

else if(ind==iVz)
	{
	ret_ind(0,0,0);
	//ret_ind_sec(0,0);
	if (but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,2);
		}
	else if (but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,2);
		}
	else if(sub_ind==0)
		{
		if(spc_stat!=spcVZ)
			{
			if(but==butR)
				{
				VZ_HR++;
				}
			else if(but==butL)
				{
				VZ_HR--;
				}
			gran(&VZ_HR,1,24);
			lc640_write_int(EE_VZ_HR,VZ_HR);
			}			
          }
	else if(sub_ind==1)
		{
          if(spc_stat!=spcVZ)
          	{
          	char temp;
          	//temp=vz_start(VZ_HR);
          	if(temp==22) 
          		{
          		sub_ind=22;
          		ret_ind(iVz,1,5);
          		} 
			else if(temp==33) 
          		{
          		sub_ind=33;
          		ret_ind(iVz,1,5);
          		}          		
          	}    
         	else if(spc_stat==spcVZ)
          	{
          	//vz_stop();
          	}             	 
		}			
	else if(sub_ind==2)
		{                 
		if(but==butE)
			{
			tree_down(0,0);
			}
          } 
	}





else if(ind==iSet)
	{

	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if(sub_ind==2)
			{
			sub_ind=3;
			index_set=2;
			}
		if(sub_ind==4)
			{
			sub_ind=5;
			index_set=4;
			}
		if(sub_ind==6)
			{
			sub_ind=7;
			index_set=6;
			}
		if(sub_ind==8)
			{
			sub_ind=9;
			index_set=8;
			}
          if(sub_ind==10)
               {
			sub_ind=11;
			index_set=10;
               }
          if(sub_ind==12)
               {
			sub_ind=13;
			index_set=12;
               }
          if(sub_ind==14)
               {
			sub_ind=15;
			//index_set=12;
               }
          if(sub_ind==14)
               {
               //index_set=13;
               }
          /*if(sub_ind==15)
               {
               sub_ind=16;
               //index_set=15;
               }*/
          if(sub_ind==18)
               {
               index_set=17;
               }
          if(sub_ind==19)
               {
               sub_ind=20;
               //index_set=15;
               }		
		gran_char(&sub_ind,0,SI_SET_MAX);
		}
	else if(but==butU)
		{
		sub_ind--;
		if(sub_ind==2)
			{
			sub_ind=1;
			}
		if(sub_ind==4)
			{
			sub_ind=3;
			//index_set=3;
			}
		if(sub_ind==6)
			{
			sub_ind=5;
			//index_set=3;
			}
		if(sub_ind==8)
			{
			sub_ind=7;
			//index_set=3;
			}
		if(sub_ind==10)
			{
			sub_ind=9;
			//index_set=3;
			}
		if(sub_ind==12)
			{
			sub_ind=11;
			//index_set=3;
			}
		if(sub_ind==14)
			{
			sub_ind=13;
			//index_set=3;
			}
		if(sub_ind==19)
			{
			sub_ind=18;
			index_set=17;
			}
		gran_char(&sub_ind,0,SI_SET_MAX);
		}
	else if(but==butD_)
		{
		sub_ind=SI_SET_MAX-2;
		}

     else if(sub_ind==0)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMIST++;
	     	gran(&NUMIST,1,12);
	     	lc640_write_int(EE_NUMIST,NUMIST);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMIST--;
	     	gran(&NUMIST,1,12);
	     	lc640_write_int(EE_NUMIST,NUMIST);
	     	}
          }

     else if(sub_ind==1)
	     {
		if(but==butR)
			{
			T_PROC_MAX=(((T_PROC_MAX/60L)+1L)*60L);
			speed=1;
			}
		else if(but==butR_)
			{
			T_PROC_MAX=(((T_PROC_MAX/300L)+1L)*300L);
			speed=1;
			}
		else if(but==butL)
			{
			T_PROC_MAX=(((T_PROC_MAX/60L)-1L)*60L);
			speed=1;
			}

		else if(but==butL_)
			{
			T_PROC_MAX=(((T_PROC_MAX/60L)-5L)*60L);
			speed=1;
			}						
		gran_long(&T_PROC_MAX,300L,86400L);
		lc640_write_long(EE_T_PROC_MAX,T_PROC_MAX);
		
		}					
     else if(sub_ind==3)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	TIME_VISION=1;
	     	lc640_write_int(EE_TIME_VISION,TIME_VISION);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	TIME_VISION=0;
	     	lc640_write_int(EE_TIME_VISION,TIME_VISION);
	     	}
          }
     else if(sub_ind==5)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	TIME_VISION_PULT=1;
	     	lc640_write_int(EE_TIME_VISION_PULT,TIME_VISION_PULT);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	TIME_VISION_PULT=0;
	     	lc640_write_int(EE_TIME_VISION_PULT,TIME_VISION_PULT);
	     	}
          }
     else if(sub_ind==7)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	I_LOAD_MODE=1;
	     	lc640_write_int(EE_I_LOAD_MODE,I_LOAD_MODE);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	I_LOAD_MODE=0;
	     	lc640_write_int(EE_I_LOAD_MODE,I_LOAD_MODE);
	     	}
          }

     else if(sub_ind==9)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	if(main_menu_mode==mmmIT)main_menu_mode=mmmIN;
			else if(main_menu_mode==mmmIN)main_menu_mode=mmmITIN;
			else if(main_menu_mode==mmmITIN)main_menu_mode=mmmINIT;
			else main_menu_mode=mmmIT;
			lc640_write_int(EE_MAIN_MENU_MODE,main_menu_mode);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	if(main_menu_mode==mmmIT)main_menu_mode=mmmINIT;
			else if(main_menu_mode==mmmINIT)main_menu_mode=mmmITIN;
			else if(main_menu_mode==mmmITIN)main_menu_mode=mmmIN;
			else main_menu_mode=mmmIT;
			lc640_write_int(EE_MAIN_MENU_MODE,main_menu_mode);
	     	}
          }

	else if(sub_ind==11)
	    	{
		if(but==butE)
			{
			tree_up(iFiks_set,0,0,0);
			}
	    	}

	else if(sub_ind==13)
	    	{
		if(but==butE)
			{
			tree_up(iRele_set,0,0,0);
			}
	    	}

     else if(sub_ind==15)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	if(restart_enable==reON)restart_enable=reOFF;
			else restart_enable=reON;
	     	lc640_write_int(EE_RESTART_ENABLE,restart_enable);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	if(restart_enable==reOFF)restart_enable=reON;
			else restart_enable=reOFF;
	     	lc640_write_int(EE_RESTART_ENABLE,restart_enable);
	     	}
          }

	else if(sub_ind==16)
	    	{
		if(but==butE)
			{
			tree_up(iLan_set,0,0,0);
			}
	    	}

     else if(sub_ind==17)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	MODBUS_ADRESS++;
	     	gran(&MODBUS_ADRESS,1,100);
	     	lc640_write_int(EE_MODBUS_ADRESS,MODBUS_ADRESS);
			speed=1;
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	MODBUS_ADRESS--;
	     	gran(&MODBUS_ADRESS,1,100);
	     	lc640_write_int(EE_MODBUS_ADRESS,MODBUS_ADRESS);
			speed=1;
	     	}
          }
     else if(sub_ind==18)
	     {
	     if((but==butR)||(but==butR_))
	     	{
			if(MODBUS_BAUDRATE==120)MODBUS_BAUDRATE=240;
			else if(MODBUS_BAUDRATE==240)MODBUS_BAUDRATE=480;
	     	else if(MODBUS_BAUDRATE==480)MODBUS_BAUDRATE=960;
			else if(MODBUS_BAUDRATE==960)MODBUS_BAUDRATE=1920;
			else if(MODBUS_BAUDRATE==1920)MODBUS_BAUDRATE=3840;
			//else if(MODBUS_BAUDRATE==3840)MODBUS_BAUDRATE=5760;
			else if(MODBUS_BAUDRATE==3840)MODBUS_BAUDRATE=5760;
			else if(MODBUS_BAUDRATE==5760)MODBUS_BAUDRATE=11520;
			else MODBUS_BAUDRATE=120;
	     	gran(&MODBUS_BAUDRATE,120,11520);
	     	lc640_write_int(EE_MODBUS_BAUDRATE,MODBUS_BAUDRATE);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
			if(MODBUS_BAUDRATE==120)MODBUS_BAUDRATE=11520;
			else if(MODBUS_BAUDRATE==240)MODBUS_BAUDRATE=120;
	     	else if(MODBUS_BAUDRATE==480)MODBUS_BAUDRATE=240;
			else if(MODBUS_BAUDRATE==960)MODBUS_BAUDRATE=480;
			else if(MODBUS_BAUDRATE==1920)MODBUS_BAUDRATE=960;
			else if(MODBUS_BAUDRATE==3840)MODBUS_BAUDRATE=1920;
			//else if(MODBUS_BAUDRATE==3840)MODBUS_BAUDRATE=3840;
			else if(MODBUS_BAUDRATE==5760)MODBUS_BAUDRATE=3840;
			else MODBUS_BAUDRATE=11520;
	     	gran(&MODBUS_BAUDRATE,120,11520);
	     	lc640_write_int(EE_MODBUS_BAUDRATE,MODBUS_BAUDRATE);
	     	}
          }
	else if(sub_ind==20)
	    	{
		if(but==butE)
			{
			tree_up(iAvtRev,0,0,0);
			}
	    	}
	else if(sub_ind==SI_SET_MAX-2)
	    	{
		if(but==butE)
			{
			tree_down(0,0);
			}
	    	}
	else if(sub_ind==SI_SET_MAX-1)
	    	{
		if(but==butE)
			{
			tree_up(iK_prl,0,0,0);
			parol_init();
			}
	    	}	
	else if(sub_ind==SI_SET_MAX)
	    {
		if(but==butE)
			{
			tree_up(iTst_pwm,1,0,0);
			tst_pwm_u=100;
			tst_pwm_i=200;
			}
	    }	
     }



else if(ind==iSet_T)
	{
	signed char temp;
	if(but==butR)
		{
		sub_ind++;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butL)
		{
		sub_ind--;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butE)
		{
		tree_down(0,0);
		}	
	else if(sub_ind==0)
	     {
	     temp=LPC_RTC->HOUR;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,0,23);
	          LPC_RTC->HOUR=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,0,23);
	          LPC_RTC->HOUR=temp;
	          }	
	     speed=1;               
	     }
     else if(sub_ind==1)
	     {
	     temp=LPC_RTC->MIN;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,0,59);
	          LPC_RTC->MIN=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,0,59);
	          LPC_RTC->MIN=temp;
	          }	
	     speed=1;               
	     }
     else if(sub_ind==2)
	     {
	     temp=LPC_RTC->SEC;
	     if((but==butU)||(but==butU_))
	          {
	          temp=0;
	          gran_ring_char(&temp,0,59);
	          LPC_RTC->SEC=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp=0;
	          gran_ring_char(&temp,0,59);
	          LPC_RTC->SEC=temp;
	          }	
	     speed=1;               
	     }

     else if(sub_ind==3)
	     {
	     temp=LPC_RTC->DOM;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,1,31);
	          LPC_RTC->DOM=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,1,31);
	          LPC_RTC->DOM=temp;
	          }	
	     speed=1;               
	     }
     else if(sub_ind==4)
	     {
	     temp=LPC_RTC->MONTH;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,1,12);
	          LPC_RTC->MONTH=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,1,12);
	          LPC_RTC->MONTH=temp;
	          }	
	     speed=1;               
	     }	  
     else if(sub_ind==5)
	     {
	     temp=LPC_RTC->YEAR;
	     if((but==butU)||(but==butU_))
	          {
	          temp++;
	          gran_ring_char(&temp,0,99);
	          LPC_RTC->YEAR=temp;
	          }
          else if((but==butD)||(but==butD_))
	          {
	          temp--;
	          gran_ring_char(&temp,0,99);
	          LPC_RTC->YEAR=temp;
	          }	
	     speed=1;               
	     }		        
	}  
/*	   	
else if(ind==iStr)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if(sub_ind==2)index_set=1;
		if(sub_ind==3)sub_ind++;
		gran_char(&sub_ind,0,4);

		}
	else if(but==butU)
		{
		sub_ind--;
		if(sub_ind==3)sub_ind--;
		gran_char(&sub_ind,0,4);
		}
	else if(but==butD_)
		{
		sub_ind=4;
		}				
     else if(sub_ind==1)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMIST++;
	     	gran(&NUMIST,0,12);
	     	lc640_write_int(EE_NUMIST,NUMIST);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMIST--;
	     	gran(&NUMIST,0,12);
	     	lc640_write_int(EE_NUMIST,NUMIST);
	     	}
          }	

     else if(sub_ind==2)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMAVT++;
	     	gran(&NUMAVT,0,12);
	     	lc640_write_int(EE_NUMAVT,NUMAVT);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMAVT--;
	     	gran(&NUMAVT,0,12);
	     	lc640_write_int(EE_NUMAVT,NUMAVT);
	     	}
          }	
          
    else if(sub_ind==4)
	     {
	     if(but==butE)
	          {
			tree_down(0,0);
	          }
          }	          
	}     
*/
else if(ind==iStr)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if(sub_ind==2)index_set=1;
		if(sub_ind==3)sub_ind++;
		gran_char(&sub_ind,1,5);	

		}
	else if(but==butU)
		{
		sub_ind--;
		if(sub_ind==3)sub_ind--;
		gran_char(&sub_ind,1,5);	 
		}
	else if(but==butD_)
		{
/**/		sub_ind=5;		 /**/
		}				
     else if(sub_ind==1)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMIST++;
	     	gran(&NUMIST,0,12);
	     	lc640_write_int(EE_NUMIST,NUMIST);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMIST--;
	     	gran(&NUMIST,0,12);
	     	lc640_write_int(EE_NUMIST,NUMIST);
	     	}
          }	
/**/
	  else if(sub_ind==2)
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMINV++;
	     	gran(&NUMINV,0,12-NUMIST);
	     	lc640_write_int(EE_NUMINV,NUMINV);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMINV--;
	     	gran(&NUMINV,0,12-NUMIST);
	     	lc640_write_int(EE_NUMINV,NUMINV);
	     	}
          }	
/**/
/**/     else if(sub_ind==3)  /**/
	     {
	     if((but==butR)||(but==butR_))
	     	{
	     	NUMAVT++;
	     	gran(&NUMAVT,0,12);
	     	lc640_write_int(EE_NUMAVT,NUMAVT);
	     	}
	     
	     else if((but==butL)||(but==butL_))
	     	{
	     	NUMAVT--;
	     	gran(&NUMAVT,0,12);
	     	lc640_write_int(EE_NUMAVT,NUMAVT);
	     	}
          }	
          
/**/    else if(sub_ind==5)	  /**/
	     {
	     if(but==butE)
	          {
			tree_down(0,0);
	          }
          }	          
	}

   


else if (ind==iLan_set)
	{
	char si_max;
	ret(1000);

	si_max=1;
	if(ETH_IS_ON!=0)si_max=21;

	if(but==butD)
		{
		sub_ind++;

		if((sub_ind==2)&&(index_set==0))
			{
			index_set=1;
			sub_ind1=0;
			}
		if(sub_ind==3) 
			{
			sub_ind=4;
			index_set=3;
			sub_ind1=0;
			}
		if(sub_ind==5) 
			{
			sub_ind=6;
			index_set=5;
			sub_ind1=0;
			}
		if(sub_ind==7) 
			{
			sub_ind=8;
			//index_set=3;
			sub_ind1=0;
			}
		if(sub_ind==10) 
			{
			//sub_ind=6;
			//index_set=9;
			sub_ind1=0;
			}
		if(sub_ind==11) 
			{
			//sub_ind=6;
			index_set=10;
			sub_ind1=0;
			}
		if(sub_ind==12) 
			{
			sub_ind++;
			}
		if(sub_ind==13) 
			{
			//sub_ind=6;
			index_set=12;
			sub_ind1=0;
			}
		if(sub_ind==14) 
			{
			sub_ind++;
			}
		if(sub_ind==15) 
			{
			//sub_ind=6;
			index_set=14;
			sub_ind1=0;
			}
		if(sub_ind==16) 
			{
			sub_ind++;
			}
		if(sub_ind==17) 
			{
			//sub_ind=6;
			index_set=16;
			sub_ind1=0;
			}
		if(sub_ind==18) 
			{
			sub_ind++;
			}
		if(sub_ind==19) 
			{
			//sub_ind=6;
			index_set=18;
			sub_ind1=0;
			}
		if(sub_ind==20) 
			{
			sub_ind++;
			}
		gran_char(&sub_ind,0,si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,si_max);
		if(sub_ind==20) 
			{
			sub_ind--;
			}		
		if(sub_ind==18) 
			{
			sub_ind--;
			}		
		if(sub_ind==16) 
			{
			sub_ind--;
			}
		if(sub_ind==14) 
			{
			sub_ind--;
			}
		if(sub_ind==12) 
			{
			sub_ind--;
			}
		if(sub_ind==7) 
			{
			sub_ind--;
			}
		if(sub_ind==5) 
			{
			sub_ind--;
			}
		if(sub_ind==3) 
			{
			sub_ind--;
			}
		}
	else if(but==butD_)
		{
		sub_ind=si_max;
		}
	else if(but==butLR_)
		{
		lc640_write_int(EE_ETH_IS_ON,1);
		lc640_write_int(EE_ETH_IS_NOT,0);
		lc640_write_int(EE_ETH_DHCP_ON,0);
		lc640_write_int(EE_ETH_IP_1,192);
		lc640_write_int(EE_ETH_IP_2,168);
		lc640_write_int(EE_ETH_IP_3,1);
		lc640_write_int(EE_ETH_IP_4,237);
		lc640_write_int(EE_ETH_MASK_1,255);
		lc640_write_int(EE_ETH_MASK_2,255);
		lc640_write_int(EE_ETH_MASK_3,255);
		lc640_write_int(EE_ETH_MASK_4,0);
		lc640_write_int(EE_ETH_GW_1,192);
		lc640_write_int(EE_ETH_GW_2,168);
		lc640_write_int(EE_ETH_GW_3,1);
		lc640_write_int(EE_ETH_GW_4,254);
		lc640_write_int(EE_ETH_SNMP_PORT_READ,161);
		lc640_write_int(EE_ETH_SNMP_PORT_WRITE,162);
		lc640_write_int(EE_COMMUNITY,'1');
		lc640_write_int(EE_COMMUNITY+2,'2');
		lc640_write_int(EE_COMMUNITY+4,'3');
		lc640_write_int(EE_COMMUNITY+6,0);
		lc640_write_int(EE_COMMUNITY+8,0);
		lc640_write_int(EE_ETH_TRAP1_IP_1,255);
		lc640_write_int(EE_ETH_TRAP1_IP_2,255);
		lc640_write_int(EE_ETH_TRAP1_IP_3,255);
		lc640_write_int(EE_ETH_TRAP1_IP_4,255);
		lc640_write_int(EE_ETH_TRAP2_IP_1,255);
		lc640_write_int(EE_ETH_TRAP2_IP_2,255);
		lc640_write_int(EE_ETH_TRAP2_IP_3,255);
		lc640_write_int(EE_ETH_TRAP2_IP_4,255);
		lc640_write_int(EE_ETH_TRAP3_IP_1,255);
		lc640_write_int(EE_ETH_TRAP3_IP_2,255);
		lc640_write_int(EE_ETH_TRAP3_IP_3,255);
		lc640_write_int(EE_ETH_TRAP3_IP_4,255);
		lc640_write_int(EE_ETH_TRAP4_IP_1,255);
		lc640_write_int(EE_ETH_TRAP4_IP_2,255);
		lc640_write_int(EE_ETH_TRAP4_IP_3,255);
		lc640_write_int(EE_ETH_TRAP4_IP_4,255);
		lc640_write_int(EE_ETH_TRAP5_IP_1,255);
		lc640_write_int(EE_ETH_TRAP5_IP_2,255);
		lc640_write_int(EE_ETH_TRAP5_IP_3,255);
		lc640_write_int(EE_ETH_TRAP5_IP_4,255);
		}					
	else if(sub_ind==0)
	     {
	     if((but==butE)||(but==butL)||(but==butR))
	     	{
	     	if(ETH_IS_ON)lc640_write_int(EE_ETH_IS_ON,0);
			else 
				{
				lc640_write_int(EE_ETH_IS_ON,1);
				lc640_write_int(EE_ETH_IS_NOT,0);
				}
	     	}
	     }	
     else if((sub_ind==1)&&(ETH_IS_ON))
	     {
		if((but==butE)||(but==butL)||(but==butR))
	     	{
	     	if(ETH_DHCP_ON)lc640_write_int(EE_ETH_DHCP_ON,0);
			else lc640_write_int(EE_ETH_DHCP_ON,1);
	     	}
		}	
     else if(sub_ind==2)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_1++;
				gran_ring(&ETH_IP_1,0,255);
				lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_1--;
				gran_ring(&ETH_IP_1,0,255);
				lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_2++;
				gran_ring(&ETH_IP_2,0,255);
				lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_2--;
				gran_ring(&ETH_IP_2,0,255);
				lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_3++;
				gran_ring(&ETH_IP_3,0,255);
				lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_3--;
				gran_ring(&ETH_IP_3,0,255);
				lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_IP_4++;
				gran_ring(&ETH_IP_4,0,255);
				lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_IP_4--;
				gran_ring(&ETH_IP_4,0,255);
				lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
				}
			speed=1;
			}

          }
     else if(sub_ind==4)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_1++;
				gran_ring(&ETH_MASK_1,0,255);
				lc640_write_int(EE_ETH_MASK_1,ETH_MASK_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_1--;
				gran_ring(&ETH_MASK_1,0,255);
				lc640_write_int(EE_ETH_MASK_1,ETH_MASK_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_2++;
				gran_ring(&ETH_MASK_2,0,255);
				lc640_write_int(EE_ETH_MASK_2,ETH_MASK_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_2--;
				gran_ring(&ETH_MASK_2,0,255);
				lc640_write_int(EE_ETH_MASK_2,ETH_MASK_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_3++;
				gran_ring(&ETH_MASK_3,0,255);
				lc640_write_int(EE_ETH_MASK_3,ETH_MASK_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_3--;
				gran_ring(&ETH_MASK_3,0,255);
				lc640_write_int(EE_ETH_MASK_3,ETH_MASK_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_MASK_4++;
				gran_ring(&ETH_MASK_4,0,255);
				lc640_write_int(EE_ETH_MASK_4,ETH_MASK_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_MASK_4--;
				gran_ring(&ETH_MASK_4,0,255);
				lc640_write_int(EE_ETH_MASK_4,ETH_MASK_4);
				}
			speed=1;
			}
		}
     else if(sub_ind==6)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_1++;
				gran_ring(&ETH_GW_1,0,255);
				lc640_write_int(EE_ETH_GW_1,ETH_GW_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_1--;
				gran_ring(&ETH_GW_1,0,255);
				lc640_write_int(EE_ETH_GW_1,ETH_GW_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_2++;
				gran_ring(&ETH_GW_2,0,255);
				lc640_write_int(EE_ETH_GW_2,ETH_GW_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_2--;
				gran_ring(&ETH_GW_2,0,255);
				lc640_write_int(EE_ETH_GW_2,ETH_GW_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_3++;
				gran_ring(&ETH_GW_3,0,255);
				lc640_write_int(EE_ETH_GW_3,ETH_GW_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_3--;
				gran_ring(&ETH_GW_3,0,255);
				lc640_write_int(EE_ETH_GW_3,ETH_GW_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_GW_4++;
				gran_ring(&ETH_GW_4,0,255);
				lc640_write_int(EE_ETH_GW_4,ETH_GW_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_GW_4--;
				gran_ring(&ETH_GW_4,0,255);
				lc640_write_int(EE_ETH_GW_4,ETH_GW_4);
				}
			speed=1;
			}
		}
      else if(sub_ind==8)
	     {
		if(but==butR)ETH_SNMP_PORT_READ++;
		else if(but==butR_)ETH_SNMP_PORT_READ+=2;
		else if(but==butL)ETH_SNMP_PORT_READ--;
		else if(but==butL_)ETH_SNMP_PORT_READ-=2;
		speed=1;
		lc640_write_int(EE_ETH_SNMP_PORT_READ,ETH_SNMP_PORT_READ);
		}

     else if(sub_ind==9)
	     {
		if(but==butR)ETH_SNMP_PORT_WRITE++;
		else if(but==butR_)ETH_SNMP_PORT_WRITE+=2;
		else if(but==butL)ETH_SNMP_PORT_WRITE--;
		else if(but==butL_)ETH_SNMP_PORT_WRITE-=2;
		speed=1;
		lc640_write_int(EE_ETH_SNMP_PORT_WRITE,ETH_SNMP_PORT_WRITE);
		}					
     else if(sub_ind==10)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,8);
	     	}
		if((but==butR)||(but==butR_))
			{
			snmp_Community[sub_ind1]++;
			if(snmp_Community[sub_ind1]<32) snmp_Community[sub_ind1]=32;
			else if ((snmp_Community[sub_ind1]>32)&&(snmp_Community[sub_ind1]<48)) snmp_Community[sub_ind1]=48;
			else if ((snmp_Community[sub_ind1]>57)&&(snmp_Community[sub_ind1]<65)) snmp_Community[sub_ind1]=65;
			else if ((snmp_Community[sub_ind1]>90)&&(snmp_Community[sub_ind1]<97)) snmp_Community[sub_ind1]=97;
			else if (snmp_Community[sub_ind1]>122) snmp_Community[sub_ind1]=32;
				//gran_ring(&ETH_GW_1,0,255);
			lc640_write_int(EE_COMMUNITY+(sub_ind1*2),snmp_Community[sub_ind1]);
			speed=1;
			}
		if((but==butL)||(but==butL_))
			{
			snmp_Community[sub_ind1]--;
			if(snmp_Community[sub_ind1]<32) snmp_Community[sub_ind1]=122;
			else if ((snmp_Community[sub_ind1]>32)&&(snmp_Community[sub_ind1]<48)) snmp_Community[sub_ind1]=32;
			else if ((snmp_Community[sub_ind1]>57)&&(snmp_Community[sub_ind1]<65)) snmp_Community[sub_ind1]=57;
			else if ((snmp_Community[sub_ind1]>90)&&(snmp_Community[sub_ind1]<97)) snmp_Community[sub_ind1]=90;
			else if (snmp_Community[sub_ind1]>122) snmp_Community[sub_ind1]=122;
			//gran_ring(&ETH_GW_1,0,255);
			lc640_write_int(EE_COMMUNITY+(sub_ind1*2),snmp_Community[sub_ind1]);
			speed=1;
			}
		}
 
     else if(sub_ind==11)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_1++;
				gran_ring(&ETH_TRAP1_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_1,ETH_TRAP1_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_1--;
				gran_ring(&ETH_TRAP1_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_1,ETH_TRAP1_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_2++;
				gran_ring(&ETH_TRAP1_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_2,ETH_TRAP1_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_2--;
				gran_ring(&ETH_TRAP1_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_2,ETH_TRAP1_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_3++;
				gran_ring(&ETH_TRAP1_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_3,ETH_TRAP1_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_3--;
				gran_ring(&ETH_TRAP1_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_3,ETH_TRAP1_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP1_IP_4++;
				gran_ring(&ETH_TRAP1_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_4,ETH_TRAP1_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP1_IP_4--;
				gran_ring(&ETH_TRAP1_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP1_IP_4,ETH_TRAP1_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==13)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_1++;
				gran_ring(&ETH_TRAP2_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_1,ETH_TRAP2_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_1--;
				gran_ring(&ETH_TRAP2_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_1,ETH_TRAP2_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_2++;
				gran_ring(&ETH_TRAP2_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_2,ETH_TRAP2_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_2--;
				gran_ring(&ETH_TRAP2_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_2,ETH_TRAP2_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_3++;
				gran_ring(&ETH_TRAP2_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_3,ETH_TRAP2_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_3--;
				gran_ring(&ETH_TRAP2_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_3,ETH_TRAP2_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP2_IP_4++;
				gran_ring(&ETH_TRAP2_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_4,ETH_TRAP2_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP2_IP_4--;
				gran_ring(&ETH_TRAP2_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP2_IP_4,ETH_TRAP2_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==15)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_1++;
				gran_ring(&ETH_TRAP3_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_1,ETH_TRAP3_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_1--;
				gran_ring(&ETH_TRAP3_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_1,ETH_TRAP3_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_2++;
				gran_ring(&ETH_TRAP3_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_2,ETH_TRAP3_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_2--;
				gran_ring(&ETH_TRAP3_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_2,ETH_TRAP3_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_3++;
				gran_ring(&ETH_TRAP3_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_3,ETH_TRAP3_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_3--;
				gran_ring(&ETH_TRAP3_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_3,ETH_TRAP3_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP3_IP_4++;
				gran_ring(&ETH_TRAP3_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_4,ETH_TRAP3_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP3_IP_4--;
				gran_ring(&ETH_TRAP3_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP3_IP_4,ETH_TRAP3_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==17)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_1++;
				gran_ring(&ETH_TRAP4_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_1,ETH_TRAP4_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_1--;
				gran_ring(&ETH_TRAP4_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_1,ETH_TRAP4_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_2++;
				gran_ring(&ETH_TRAP4_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_2,ETH_TRAP4_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_2--;
				gran_ring(&ETH_TRAP4_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_2,ETH_TRAP4_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_3++;
				gran_ring(&ETH_TRAP4_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_3,ETH_TRAP4_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_3--;
				gran_ring(&ETH_TRAP4_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_3,ETH_TRAP4_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP4_IP_4++;
				gran_ring(&ETH_TRAP4_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_4,ETH_TRAP4_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP4_IP_4--;
				gran_ring(&ETH_TRAP4_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP4_IP_4,ETH_TRAP4_IP_4);
				}
			speed=1;
			}
		}	
     else if(sub_ind==19)
	     {
		if(but==butE_)
	     	{
	     	sub_ind1++;
			gran_ring_char(&sub_ind1,0,3);
	     	}
		else if(sub_ind1==0)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_1++;
				gran_ring(&ETH_TRAP5_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_1,ETH_TRAP5_IP_1);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_1--;
				gran_ring(&ETH_TRAP5_IP_1,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_1,ETH_TRAP5_IP_1);
				}
			speed=1;
			}
		else if(sub_ind1==1)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_2++;
				gran_ring(&ETH_TRAP5_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_2,ETH_TRAP5_IP_2);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_2--;
				gran_ring(&ETH_TRAP5_IP_2,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_2,ETH_TRAP5_IP_2);
				}
			speed=1;
			}
		else if(sub_ind1==2)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_3++;
				gran_ring(&ETH_TRAP5_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_3,ETH_TRAP5_IP_3);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_3--;
				gran_ring(&ETH_TRAP5_IP_3,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_3,ETH_TRAP5_IP_3);
				}
			speed=1;
			}
		else if(sub_ind1==3)
			{
			if((but==butR)||(but==butR_))
				{
				ETH_TRAP5_IP_4++;
				gran_ring(&ETH_TRAP5_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_4,ETH_TRAP5_IP_4);
				}
			else if((but==butL)||(but==butL_))
				{
				ETH_TRAP5_IP_4--;
				gran_ring(&ETH_TRAP5_IP_4,0,255);
				lc640_write_int(EE_ETH_TRAP5_IP_4,ETH_TRAP5_IP_4);
				}
			speed=1;
			}
		}													          
    else if(sub_ind==si_max)
	     {
	     if(but==butE)
	          {
	          tree_down(0,0);
	          }
          }	          	
	}

else if(ind==iTst_pwm)
	{
	ret(3000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,1,3);
		}
	else if(but==butU)
		{
		sub_ind--;
		if(sub_ind==1)index_set=0;
		gran_char(&sub_ind,1,3);
		}
	else if(but==butD_)
		{
		sub_ind=3;
		}

    	else if(sub_ind==1)
	     {
		if(but==butE_)
			{
			if(tst_pwm_u)tst_pwm_u=0;
			else tst_pwm_u=1022;
			}
		else if(but==butR)
			{
			tst_pwm_u++;
			gran(&tst_pwm_u,0,1022);
			}
		else if(but==butR_)
			{
			tst_pwm_u+=5;
			gran(&tst_pwm_u,0,1022);
			}
		else if(but==butL)
			{
			tst_pwm_u--;
			gran(&tst_pwm_u,0,1022);
			}
		else if(but==butL_)
			{
			tst_pwm_u-=5;
			gran(&tst_pwm_u,0,1022);
			}
		speed=1;
          }

    	else if(sub_ind==2)
		{
		if(but==butE_)
			{
			if(tst_pwm_i)tst_pwm_i=0;
			else tst_pwm_i=1022;
			}
		else if(but==butR)
			{
			tst_pwm_i++;
			gran(&tst_pwm_i,0,1022);
			}
		else if(but==butR_)
			{
			tst_pwm_i+=5;
			gran(&tst_pwm_i,0,1022);
			}
		else if(but==butL)
			{
			tst_pwm_i--;
			gran(&tst_pwm_i,0,1022);
			}
		else if(but==butL_)
			{
			tst_pwm_i-=5;
			gran(&tst_pwm_i,0,1022);
			}
		speed=1;
          }

    	else if(sub_ind==3)
	     {
	     if(but==butE)
	          {
	          tree_down(0,0);
	          }
          }

	}
	     
else if(ind==iK)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butD_)
		{
		sub_ind=5;
		}
	else if(sub_ind==4)
		{
		if(but==butR)
			{
			REV_IS_ON=1;
			lc640_write_int(EE_REV_IS_ON,REV_IS_ON);
			}
		else if(but==butL)
			{
			REV_IS_ON=0;
			lc640_write_int(EE_REV_IS_ON,REV_IS_ON);
			}					
		}			
	else if(but==butE)
		{
		if(sub_ind==0)
			{
			tree_up(iK_load,0,0,0);
			phase=1;	
			ret(1000);		
			}
		else if(sub_ind==1)
			{
			tree_up(iK_bps_sel,0,0,0);	
			ret(1000);
			}
		else if(sub_ind==2)
			{
			tree_up(iK_max_param,0,0,0);	
			ret(1000);
			}
		else if(sub_ind==3)
			{
			tree_up(iK_viz_sel,0,0,0);	
			ret(1000);
			}
	   	else if(sub_ind==5)	   
			{
	        tree_down(0,0);
	        ret(0);
            }	               			
		}					
	}


else if(ind==iK_bps_sel)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,NUMIST);
		phase=0;
		can1_out(sub_ind,sub_ind,CMND,ALRM_RES,0,0,0,0);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,NUMIST);
		phase=0;
		can1_out(sub_ind,sub_ind,CMND,ALRM_RES,0,0,0,0);
		}
	else if(but==butD_)
		{
		sub_ind=1+NUMIST;
		}	
	else if((but==butE)&&(NUMIST)&&(sub_ind<NUMIST))
		{
		tree_up(iK_bps,0,0,sub_ind);	
		
		ret(1000);
		}	
	else if(sub_ind==(NUMIST))
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
		}				
	}


else if(ind==iK_bps)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		if((sub_ind==1)||(sub_ind==2))sub_ind=3;
		else if((sub_ind==4)||(sub_ind==5))sub_ind=6;
		else if((sub_ind==7)||(sub_ind==8))sub_ind=9;
		else if((sub_ind==10)||(sub_ind==11))sub_ind=12;
		else if((sub_ind==13)||(sub_ind==14))sub_ind=15;
		gran_char(&sub_ind,0,9);
		phase=0;
		}
	else if(but==butU)
		{
		sub_ind--;
		if((sub_ind==1)||(sub_ind==2))sub_ind=0;
		else if((sub_ind==4)||(sub_ind==5))sub_ind=3;
		else if((sub_ind==7)||(sub_ind==8))sub_ind=6;
		else if((sub_ind==10)||(sub_ind==11))sub_ind=9;
		else if((sub_ind==13)||(sub_ind==14))sub_ind=12;		
		gran_char(&sub_ind,0,9);
		phase=0;
		}
	else if(but==butD_)
		{
		sub_ind=9;
		}
	else if (sub_ind == 0)
		{
		if(but==butLR) can1_out(sub_ind1,sub_ind1,KLBR,(0*16)+1,(0*16)+1,0,0,0);
	     else if(but==butR) can1_out(sub_ind1,sub_ind1,KLBR,(0*16)+2,(0*16)+2,0,0,0);
		else if(but==butR_)	can1_out(sub_ind1,sub_ind1,KLBR,(0*16)+3,(0*16)+3,0,0,0);
    		else if(but==butL) can1_out(sub_ind1,sub_ind1,KLBR,(0*16)+4,(0*16)+4,0,0,0); 
		else if(but==butL_) can1_out(sub_ind1,sub_ind1,KLBR,(0*16)+5,(0*16)+5,0,0,0);
		speed=1;
		}	
		
/*	else if (sub_ind == 3)
		{
		if(but==butLR) can1_out(sub_ind1,sub_ind1,KLBR,(1*16)+1,(1*16)+1,0,0,0);
	     else if(but==butR) can1_out(sub_ind1,sub_ind1,KLBR,(1*16)+2,(1*16)+2,0,0,0);
		else if(but==butR_)	can1_out(sub_ind1,sub_ind1,KLBR,(1*16)+3,(1*16)+3,0,0,0);
    		else if(but==butL) can1_out(sub_ind1,sub_ind1,KLBR,(1*16)+4,(1*16)+4,0,0,0); 
		else if(but==butL_) can1_out(sub_ind1,sub_ind1,KLBR,(1*16)+5,(1*16)+5,0,0,0);
		speed=1;
		}		
		
	else if (sub_ind == 6)
		{
		temp_SS=lc640_read_int(EE_U_AVT);
		if(but==butR)temp_SS++;
		else if(but==butR_)temp_SS+=2;
		else if(but==butL)temp_SS--;
		else if(but==butL_)temp_SS-=2;
		else if(but==butE_)can1_out(sub_ind1,sub_ind1,CMND,0xee,0xee,0,0,0);   
		
		#ifdef UKU206_220				
		gran(&temp_SS,2000,3000);
		#endif

		#ifdef UKU206_24
		gran(&temp_SS,200,300);
		#endif

		#ifdef UKU320
		gran(&temp_SS,400,800);
		#endif

		#ifdef UKU320_24
		gran(&temp_SS,200,300);
		#endif

		#ifdef UKU320_F
		gran(&temp_SS,400,800);
		#endif		
		lc640_write_int(EE_U_AVT,temp_SS);
		
		speed=1;
		}*/	
		
	else if (sub_ind == 3)
		{
		if(but==butE)
			{
			can1_out(sub_ind1,sub_ind1,KLBR,(2*16)+1,(2*16)+1,0,0,0);
			phase=1;
			}
	     else if(but==butR) can1_out(sub_ind1,sub_ind1,KLBR,(2*16)+2,(2*16)+2,0,0,0);
		else if(but==butR_)	can1_out(sub_ind1,sub_ind1,KLBR,(2*16)+3,(2*16)+3,0,0,0);
    		else if(but==butL) can1_out(sub_ind1,sub_ind1,KLBR,(2*16)+4,(2*16)+4,0,0,0); 
		else if(but==butL_) can1_out(sub_ind1,sub_ind1,KLBR,(2*16)+5,(2*16)+5,0,0,0);
		speed=1;
		}		
		
	else if (sub_ind == 6)
		{
		if(but==butR) can1_out(sub_ind1,sub_ind1,KLBR,(3*16)+2,(3*16)+2,0,0,0);
		else if(but==butR_)	can1_out(sub_ind1,sub_ind1,KLBR,(3*16)+3,(3*16)+3,0,0,0);
    		else if(but==butL) can1_out(sub_ind1,sub_ind1,KLBR,(3*16)+4,(3*16)+4,0,0,0); 
		else if(but==butL_) can1_out(sub_ind1,sub_ind1,KLBR,(3*16)+5,(3*16)+5,0,0,0);
		speed=1;
		}								
			

	else if(sub_ind==9)
		{
		if(but==butE)
			{
			//a=b[--ptr_ind];
			//sub_ind++;
			tree_down(0,1);
			ret(0);
			}
		}			
	}		


else if(ind==iK_load)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,2);
		if(sub_ind==0)phase=1;
		if(sub_ind==1)phase=0;
		if(sub_ind==2)phase=0;
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,2);
		if(sub_ind==0)phase=1;
		if(sub_ind==1)phase=0;
		if(sub_ind==2)phase=0;
		}
	else if(sub_ind==0)
		{
		temp_SS=lc640_read_int(EE_KULOAD);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=2;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=2;
	     	}
	    gran(&temp_SS,100,6000);
		lc640_write_int(EE_KULOAD,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==1)
		{
		temp_SS=lc640_read_int(EE_KILOAD1);
	     if(but==butE)
	     	{
			lc640_write_int(EE_KILOAD0,ad7705_buff_[0]);
			phase=1;
	     	}
	     else if(but==butR)
	     	{
			phase=1;
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
			phase=1;
	     	temp_SS+=5;
	     	}	
	     else if(but==butL)
	     	{
			phase=1;
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
			phase=1;
	     	temp_SS-=5;
	     	}
	    gran(&temp_SS,100,30000);
		lc640_write_int(EE_KILOAD1,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==2)
		{
		if(but==butE)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}


else if(ind==iK_max_param)
	{

	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,6);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,6);
		}
	else if(sub_ind==0)
		{
		temp_SS=lc640_read_int(EE_U_MAX);
	     if(but==butR)
	     	{
		    temp_SS=((temp_SS/10)+1)*10;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS=((temp_SS/10)+10)*10;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS=((temp_SS/10)-1)*10;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS=((temp_SS/10)-10)*10;
	     	}
	    gran(&temp_SS,50,15000);
		lc640_write_int(EE_U_MAX,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==1)
		{
		temp_SS=lc640_read_int(EE_U_MIN);
	     if(but==butR)
	     	{
		    temp_SS=((temp_SS/10)+1)*10;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS=((temp_SS/10)+10)*10;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS=((temp_SS/10)-1)*10;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS=((temp_SS/10)-10)*10;
	     	}
	    gran(&temp_SS,10,1000);
		lc640_write_int(EE_U_MIN,temp_SS);					
		speed=1;	
		}

	else if(sub_ind==2)
		{
		temp_SS=lc640_read_int(EE_I_MAX);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=5;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=5;
	     	}
	    gran(&temp_SS,10,2000);
		lc640_write_int(EE_I_MAX,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==3)
		{
		temp_SS=lc640_read_int(EE_I_MIN);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=5;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=5;
	     	}
	    gran(&temp_SS,1,2000);
		lc640_write_int(EE_I_MIN,temp_SS);					
		speed=1;	
		}

	else if(sub_ind==4)
		{
		temp_SS=lc640_read_int(EE_T_SIGN);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=1;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=1;
	     	}
	    gran(&temp_SS,5,100);
		lc640_write_int(EE_T_SIGN,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==5)
		{
		temp_SS=lc640_read_int(EE_T_MAX);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=1;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=1;
	     	}
	    gran(&temp_SS,5,100);
		lc640_write_int(EE_T_MAX,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==6)
		{
		if(but==butE)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}

else if(ind==iK_viz_sel)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,2);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,2);
		}
	else if(sub_ind==0)
		{
		if(but==butE)
			{
			tree_up(iK_viz_u,0,0,0);
			show_mess	(	"     Установите     ",
	          			" ток нагрузки 5-20% ",
	          			"  от максимального  ",
	          			"   и нажмите пуск   ",3000);	
			viz_stat=vsOFF;
			viz_stat_cnt=0;
			//ret(1000);
			}	
		}
	else if(sub_ind==1)
		{
		if(but==butE)
			{
			tree_up(iK_viz_i,0,0,0);
			show_mess	(	"     Установите     ",
	          			" ток нагрузки 100% ",
	          			"  от максимального  ",
	          			"   и нажмите пуск   ",3000);	
			viz_stat=vsOFF;
			viz_stat_cnt=0;
			//ret(1000);
			}	
		}
 	else if(sub_ind==2)
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
		}				 
	} 

else if(ind==iK_viz_u)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,1);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,1);
		}
	else if(sub_ind==0)
		{
		if(but==butE)
			{
			if(viz_stat!=vsON)
				{
				viz_stat=vsON;
				viz_stat_cnt=0;
				ret(0);
				}
			else viz_stat=vsOFF;
			}	
		}
/*	else if(sub_ind==1)
		{
		if(but==butE)
			{
			tree_up(iK_viz_i,0,0,0);	
			ret(1000);
			}	
		}*/
 	else if(sub_ind==1)
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
		}				 
	} 

else if(ind==iK_viz_i)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,1);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,1);
		}
	else if(sub_ind==0)
		{
		if(but==butE)
			{
			if(viz_stat!=vsON)
				{
				viz_stat=vsON;
				viz_stat_cnt=0;
				ret(0);
				}
			else viz_stat=vsOFF;
			}	
		}
/*	else if(sub_ind==1)
		{
		if(but==butE)
			{
			tree_up(iK_viz_i,0,0,0);	
			ret(1000);
			}	
		}*/
 	else if(sub_ind==1)
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
		}				 
	} 

else if(ind==iK_t_ext_6U)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,NUMDT);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,NUMDT);
		}
	else if(sub_ind==0)
		{
		temp_SS=lc640_read_int(KT_EXT0);
	     if(but==butR)
	     	{
		     temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=2;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=2;
	     	}
	     gran(&temp_SS,1900,3000);
		lc640_write_int(KT_EXT0,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==1)
		{
		temp_SS=lc640_read_int(KT_EXT1);
	     if(but==butR)
	     	{
		     temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=2;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=2;
	     	}
	     gran(&temp_SS,1900,3000);
		lc640_write_int(KT_EXT1,temp_SS);					
		speed=1;	
					
		}
	else if(sub_ind==2)
		{
		temp_SS=lc640_read_int(KT_EXT2);
	     if(but==butR)
	     	{
		     temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS+=2;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS-=2;
	     	}
	     gran(&temp_SS,1900,3000);
		lc640_write_int(KT_EXT2,temp_SS);					
		speed=1;	
					
		}
 	if(sub_ind==NUMDT)
		{
		if(but==butE)
			{
			tree_down(0,1);
			ret(0);
			}
		}			
	}
			


else if(ind==iBatLogVz)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butE)
		{
		if(sub_ind==av_j_si_max)
			{
			tree_down(0,0);
			}
		} 
	else if(but==butL)
		{
		tree_down(0,0);
		}		
    //	else if(but==butR) vz_mem_hndl(sub_ind1,_sec);
	
		
	}

else if(ind==iBatLogKe)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butE)
		{
		if(sub_ind==av_j_si_max)
			{
			tree_down(0,0);
			}
		} 
	else if(but==butL)
		{
		tree_down(0,0);
		}		
    //	else if(but==butR) ke_mem_hndl(sub_ind1,_sec);		
	}

else if(ind==iBatLogWrk)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,av_j_si_max);
		}
	else if(but==butE)
		{
		if(sub_ind==av_j_si_max)
			{
			tree_down(0,0);
			}
		else if(sub_ind<=av_j_si_max)
			{
			//ind=iWrk;
			//sub_ind2=content[sub_ind];
			index_set=0;
			//sub_ind=0;
			}	
		} 
	else if(but==butL)
		{
		tree_down(0,0);
		}		
	else if(but==butR)
		{
	    //	wrk_mem_hndl(sub_ind1);

		} 
	}


else if(ind==iRele_set)
	{
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,5);
		}
	else if(but==butE)
		{
		if(sub_ind==5)
			{
			tree_down(0,0);
			}
		} 

	else if(sub_ind==0)
		{
		if((but==butE)||(but==butR))
			{
			if(RELE_LOG==rlOFF)RELE_LOG=rlON_NZ;
			else if(RELE_LOG==rlON_NZ)RELE_LOG=rlON_NR;
			else RELE_LOG=rlOFF;
			lc640_write_int(EE_RELE_LOG,RELE_LOG);
			}
		else if(but==butL)
			{
			if(RELE_LOG==rlOFF)RELE_LOG=rlON_NR;
			else if(RELE_LOG==rlON_NR)RELE_LOG=rlON_NZ;
			else RELE_LOG=rlOFF;
			lc640_write_int(EE_RELE_LOG,RELE_LOG);
			}
		} 
	else if(sub_ind==1)
		{
		temp_SS=lc640_read_int(EE_T_DEL_REL_START);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS++;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS--;
	     	}
	    	gran(&temp_SS,0,1000);
		lc640_write_int(EE_T_DEL_REL_START,temp_SS);					
		speed=1;	
		}
	else if(sub_ind==2)
		{
		temp_SS=lc640_read_int(EE_T_DEL_REL_WRK);
	     if(but==butR)
	     	{
		    temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS++;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS--;
	     	}
	    	gran(&temp_SS,0,1000);
		lc640_write_int(EE_T_DEL_REL_WRK,temp_SS);					
		speed=1;	
		}

	else if(sub_ind==3)
		{
		temp_SS=lc640_read_int(EE_DELT_REL_U);
	     if(but==butR)
	     	{
		    	temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS++;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS--;
	     	}
	    	gran(&temp_SS,1,50);
		lc640_write_int(EE_DELT_REL_U,temp_SS);					
		speed=1;	
					
		}

	else if(sub_ind==4)
		{
		temp_SS=lc640_read_int(EE_DELT_REL_I);
	     if(but==butR)
	     	{
		    	temp_SS++;
	     	}
	     else if(but==butR_)
	     	{
	     	temp_SS++;
	     	}	
	     else if(but==butL)
	     	{
	     	temp_SS--;
	     	}
	     else if(but==butL_)
	     	{
	     	temp_SS--;
	     	}
	    	gran(&temp_SS,1,50);
		lc640_write_int(EE_DELT_REL_I,temp_SS);					
		speed=1;	
		}

/*	else if(but==butL)
		{
		tree_down(0,0);
		}*/		
    //	else if(but==butR) ke_mem_hndl(sub_ind1,_sec);		
	}



/*
else if(ind==iTst_6U)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,14+NUMIST);
		phase=0;
		tst_state[0]=tstOFF;
		tst_state[1]=tstOFF;
		tst_state[2]=tstOFF;
		tst_state[3]=tstOFF;
		tst_state[4]=tstOFF;
		tst_state[5]=tstOFF;
		tst_state[6]=tstOFF;
		tst_state[7]=tstOFF;
		tst_state[8]=tstOFF;
		tst_state[9]=tstOFF;

		if(sub_ind==1)
			{
			sub_ind=2;
			index_set=1;
			}
		if(sub_ind==3)
			{
			sub_ind=4;
			index_set=3;
			}
		if(sub_ind==5)
			{
			sub_ind=6;
			index_set=5;
			}
		if(sub_ind==7)
			{
			sub_ind=8;
			//index_set=7;
			}
		if(sub_ind==9)
			{
			index_set=8;
			}
		if(sub_ind==10)
			{
			sub_ind=11;
			index_set=10;
			}
		}

	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,14+NUMIST);
		phase=0;
		tst_state[0]=tstOFF;
		tst_state[1]=tstOFF;
		tst_state[2]=tstOFF;
		tst_state[3]=tstOFF;
		tst_state[4]=tstOFF;
		tst_state[5]=tstOFF;
		tst_state[6]=tstOFF;
		tst_state[7]=tstOFF;
		tst_state[8]=tstOFF;
		tst_state[9]=tstOFF;
		
		if(sub_ind==10)
			{
			sub_ind=9;
			//index_set=5;
			}
		if(sub_ind==7)
			{
			sub_ind=6;
			//index_set=5;
			}
		if(sub_ind==5)
			{
			sub_ind=4;
			//index_set=5;
			}
		if(sub_ind==3)
			{
			sub_ind=2;
			//index_set=5;
			}
		if(sub_ind==1)
			{
			sub_ind=0;
			//index_set=5;
			}
		}

	else if(sub_ind==0)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[0]==tstOFF) tst_state[0]=tst1;
			else if(tst_state[0]==tst1) tst_state[0]=tst2;
			else tst_state[0]=tstOFF; 
			}
		else if(but==butL)
			{
			if(tst_state[0]==tst2) tst_state[0]=tst1;
			else if(tst_state[0]==tstOFF) tst_state[0]=tst2;
			else tst_state[0]=tstOFF; 
			}
		}
	else if(sub_ind==2)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[1]==tstOFF) tst_state[1]=tst1;
			else if(tst_state[1]==tst1) tst_state[1]=tst2;
			else tst_state[1]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[1]==tst2) tst_state[1]=tst1;
			else if(tst_state[1]==tstOFF) tst_state[1]=tst2;
			else tst_state[1]=tstOFF;
			}
		}		

	else if(sub_ind==4)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[9]==tstOFF) tst_state[9]=tst1;
			else if(tst_state[9]==tst1) tst_state[9]=tst2;
			else tst_state[9]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[9]==tst2) tst_state[9]=tst1;
			else if(tst_state[9]==tstOFF) tst_state[9]=tst2;
			else tst_state[9]=tstOFF;
			}
		}
		
	else if(sub_ind==6)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[2]==tstOFF) tst_state[2]=tst1;
			else if(tst_state[2]==tst1) tst_state[2]=tst2;
			else tst_state[2]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[2]==tst2) tst_state[2]=tst1;
			else if(tst_state[2]==tstOFF) tst_state[2]=tst2;
			else tst_state[2]=tstOFF;
			}
		}

	else if(sub_ind==8)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[3]==tstOFF) tst_state[3]=tst1;
			else if(tst_state[3]==tst1) tst_state[3]=tst2;
			else tst_state[3]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[3]==tst2) tst_state[3]=tst1;
			else if(tst_state[3]==tstOFF) tst_state[3]=tst2;
			else tst_state[3]=tstOFF;
			}
		}
	else if(sub_ind==9)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[4]==tstOFF) tst_state[4]=tst1;
			else if(tst_state[4]==tst1) tst_state[4]=tst2;
			else tst_state[4]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[4]==tst2) tst_state[4]=tst1;
			else if(tst_state[4]==tstOFF) tst_state[4]=tst2;
			else tst_state[4]=tstOFF;
			}
		}
	else if(sub_ind==11)
		{
		if((but==butE)||(but==butR)||(but==butL))
			{
			if(tst_state[7]==tstOFF) tst_state[7]=tst1;
			else tst_state[7]=tstOFF;
			}
		}
	else if(sub_ind==12)
		{
		if((but==butE)||(but==butR)||(but==butL))
			{
			if(tst_state[8]==tstOFF) tst_state[8]=tst1;
			else tst_state[8]=tstOFF;
			}
		}
	else if((sub_ind>=13)&&(sub_ind<(13+NUMIST))&&(NUMIST)&&((but==butE)))	
		{
		tree_up(iTst_bps,0,0,sub_ind-13);
		can1_out(sub_ind1,sub_ind1,CMND,ALRM_RES,0,0,0,0);
		tst_state[5]=tst1;
		tst_state[6]=tstOFF;
		}											
	else if(sub_ind==(13+NUMIST))
		{
		if(but==butE)
			{
			bRESET=1;
			}
		}

	else if(sub_ind==(14+NUMIST))
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
	
		}	
	}*/
/*
else if(ind==iTst_220)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,12+NUMIST);
		phase=0;
		tst_state[0]=tstOFF;
		tst_state[1]=tstOFF;
		tst_state[2]=tstOFF;
		tst_state[3]=tstOFF;
		tst_state[4]=tstOFF;
		tst_state[5]=tstOFF;
		tst_state[6]=tstOFF;
		tst_state[7]=tstOFF;
		tst_state[8]=tstOFF;

		if(sub_ind==1)
			{
			sub_ind=2;
			index_set=1;
			}
		if(sub_ind==3)
			{
			sub_ind=4;
			index_set=3;
			}
		if(sub_ind==5)
			{
			sub_ind=6;
			//index_set=5;
			}
		if(sub_ind==7)
			{
			index_set=6;
			}
		if(sub_ind==8)
			{
			sub_ind=9;
			index_set=5;
			}
		}

	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,12+NUMIST);
		phase=0;
		tst_state[0]=tstOFF;
		tst_state[1]=tstOFF;
		tst_state[2]=tstOFF;
		tst_state[3]=tstOFF;
		tst_state[4]=tstOFF;
		tst_state[5]=tstOFF;
		tst_state[6]=tstOFF;
		tst_state[7]=tstOFF;
		tst_state[8]=tstOFF;
		
		if(sub_ind==8)
			{
			sub_ind=7;
			//index_set=5;
			}
		if(sub_ind==5)
			{
			sub_ind=4;
			//index_set=5;
			}
		if(sub_ind==3)
			{
			sub_ind=2;
			//index_set=5;
			}
		if(sub_ind==1)
			{
			sub_ind=0;
			//index_set=5;
			}
		}

	else if(sub_ind==0)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[0]==tstOFF) tst_state[0]=tst1;
			else if(tst_state[0]==tst1) tst_state[0]=tst2;
			else tst_state[0]=tstOFF; 
			}
		else if(but==butL)
			{
			if(tst_state[0]==tst2) tst_state[0]=tst1;
			else if(tst_state[0]==tstOFF) tst_state[0]=tst2;
			else tst_state[0]=tstOFF; 
			}
		}
	else if(sub_ind==2)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[1]==tstOFF) tst_state[1]=tst1;
			else if(tst_state[1]==tst1) tst_state[1]=tst2;
			else tst_state[1]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[1]==tst2) tst_state[1]=tst1;
			else if(tst_state[1]==tstOFF) tst_state[1]=tst2;
			else tst_state[1]=tstOFF;
			}
		}		
		
	else if(sub_ind==4)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[2]==tstOFF) tst_state[2]=tst1;
			else if(tst_state[2]==tst1) tst_state[2]=tst2;
			else tst_state[2]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[2]==tst2) tst_state[2]=tst1;
			else if(tst_state[2]==tstOFF) tst_state[2]=tst2;
			else tst_state[2]=tstOFF;
			}
		}

	else if(sub_ind==6)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[3]==tstOFF) tst_state[3]=tst1;
			else if(tst_state[3]==tst1) tst_state[3]=tst2;
			else tst_state[3]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[3]==tst2) tst_state[3]=tst1;
			else if(tst_state[3]==tstOFF) tst_state[3]=tst2;
			else tst_state[3]=tstOFF;
			}
		}
	else if(sub_ind==7)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[4]==tstOFF) tst_state[4]=tst1;
			else if(tst_state[4]==tst1) tst_state[4]=tst2;
			else tst_state[4]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[4]==tst2) tst_state[4]=tst1;
			else if(tst_state[4]==tstOFF) tst_state[4]=tst2;
			else tst_state[4]=tstOFF;
			}
		}
	else if(sub_ind==9)
		{
		if((but==butE)||(but==butR)||(but==butL))
			{
			if(tst_state[7]==tstOFF) tst_state[7]=tst1;
			else tst_state[7]=tstOFF;
			}
		}
	else if(sub_ind==10)
		{
		if((but==butE)||(but==butR)||(but==butL))
			{
			if(tst_state[8]==tstOFF) tst_state[8]=tst1;
			else tst_state[8]=tstOFF;
			}
		}
	else if((sub_ind>=11)&&(sub_ind<(11+NUMIST))&&(NUMIST)&&((but==butE)))	
		{
		tree_up(iTst_bps,0,0,sub_ind-11);
		can1_out(sub_ind1,sub_ind1,CMND,ALRM_RES,0,0,0,0);
		tst_state[5]=tst1;
		tst_state[6]=tstOFF;
		}											

	else if(sub_ind==(11+NUMIST))
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
		}
	else if(sub_ind==(12+NUMIST))
		{
		if(but==butE)
			{
			bRESET=1;
			}
		}			
	}*/
/*
else if(ind==iTst_bps)
	{
	ret(1000);
	if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,3);
		tst_state[5]=tst1;
		tst_state[6]=tstOFF;
		
		if(sub_ind==2)
			{
			sub_ind=3;
			//index_set=2;
			}

		}

	else if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,3);
		tst_state[5]=tst1;
		tst_state[6]=tstOFF;
		
		if(sub_ind==2)
			{
			sub_ind=1;
			//index_set=2;
			}
		}

	else if(sub_ind==0)
		{
		if(but==butR)
			{
			if(tst_state[5]==tstOFF)tst_state[5]=tst1;
			else if(tst_state[5]==tst1)tst_state[5]=tst2;
			else tst_state[5]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[5]==tstOFF)tst_state[5]=tst2;
			else if(tst_state[5]==tst1)tst_state[5]=tstOFF;
			else tst_state[5]=tst1;
			}
		}
	else if(sub_ind==1)
		{
		if((but==butE)||(but==butR))
			{
			if(tst_state[6]==tstOFF) tst_state[6]=tst1;
			else if(tst_state[6]==tst1) tst_state[6]=tst2;
			else tst_state[6]=tstOFF;
			}
		else if(but==butL)
			{
			if(tst_state[6]==tst2) tst_state[6]=tst1;
			else if(tst_state[6]==tstOFF) tst_state[6]=tst2;
			else tst_state[6]=tstOFF;
			}
		}		
		
	else if(sub_ind==3)
		{
		if(but==butE)
			{
			tree_down(0,0);
			ret(0);
			}
		}	
	}
*/
else if(ind==iFiks_set)
	{
	if(but==butU)
		{
		sub_ind--;
		gran_char(&sub_ind,0,4);
		}
	else if(but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,4);
		}
	else if(sub_ind==0)
		{
		if(but==butR)
			{
		    	U_up2++;
		    	gran(&U_up2,U_MIN,U_MAX);
			lc640_write_int(EE_U_UP2,U_up2);
			speed__=0;
			//find_U_curve(U_up2);
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				U_up2=((U_up2/5)+1)*5;
		    		gran(&U_up2,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP2,U_up2);
				speed=1;
				}
			else 
				{
				U_up2=((U_up2/50)+1)*50;
		    		gran(&U_up2,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP2,U_up2);
				speed=1;
				}
			speed=1;
			}

		else if(but==butL)
			{
			U_up2--;
		    	gran(&U_up2,U_MIN,U_MAX);
			lc640_write_int(EE_U_UP2,U_up2);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				U_up2=((U_up2/5)-1)*5;
		    		gran(&U_up2,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP2,U_up2);
				speed=1;
				}
			else 
				{
				U_up2=((U_up2/50)-1)*50;
		    		gran(&U_up2,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP2,U_up2);
				speed=1;
				}
			speed=1;
			}
	  	}

	else if(sub_ind==1)
		{
		if(but==butR)
			{
		    	U_up3++;
		    	gran(&U_up3,U_MIN,U_MAX);
			lc640_write_int(EE_U_UP3,U_up3);
			speed__=0;
			//find_U_curve(U_up3);
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				U_up3=((U_up3/5)+1)*5;
		    		gran(&U_up3,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP3,U_up3);
				speed=1;
				}
			else 
				{
				U_up3=((U_up3/50)+1)*50;
		    		gran(&U_up3,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP3,U_up3);
				speed=1;
				}
			speed=1;
			}

		else if(but==butL)
			{
			U_up3--;
		    	gran(&U_up3,U_MIN,U_MAX);
			lc640_write_int(EE_U_UP3,U_up3);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				U_up3=((U_up3/5)-1)*5;
		    		gran(&U_up3,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP3,U_up3);
				speed=1;
				}
			else 
				{
				U_up3=((U_up3/50)-1)*50;
		    		gran(&U_up3,U_MIN,U_MAX);
				lc640_write_int(EE_U_UP3,U_up3);
				speed=1;
				}
			speed=1;
			}
	  	}
	else if(sub_ind==2)
		{
		if(but==butR)
			{
			I_ug2++;
		    	gran(&I_ug2,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_I_UG2,I_ug2);
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				I_ug2=((I_ug2/5)+1)*5;
		    		gran(&I_ug2,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG2,I_ug2);
				speed=1;
				}
			else 
				{
				I_ug2=((I_ug2/50)+1)*50;
		    		gran(&I_ug2,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG2,I_ug2);
				speed=1;
				}
			speed=1;
			}
		else if(but==butL)
			{
		    	I_ug2--;
		    	gran(&I_ug2,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_I_UG2,I_ug2);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				I_ug2=((I_ug2/5)-1)*5;
		    		gran(&I_ug2,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG2,I_ug2);
				speed=1;
				}
			else 
				{
				I_ug2=((I_ug2/50)-1)*50;
		    		gran(&I_ug2,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG2,I_ug2);
				speed=1;
				}
			speed=1;
			}
	  	}

	else if(sub_ind==3)
		{
		if(but==butR)
			{
			I_ug3++;
		    	gran(&I_ug3,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_I_UG3,I_ug3);
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				I_ug3=((I_ug3/5)+1)*5;
		    		gran(&I_ug3,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG3,I_ug3);
				speed=1;
				}
			else 
				{
				I_ug3=((I_ug3/50)+1)*50;
		    		gran(&I_ug3,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG3,I_ug3);
				speed=1;
				}
			speed=1;
			}
		else if(but==butL)
			{
		    	I_ug3--;
		    	gran(&I_ug3,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_I_UG3,I_ug3);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				I_ug3=((I_ug3/5)-1)*5;
		    		gran(&I_ug3,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG3,I_ug3);
				speed=1;
				}
			else 
				{
				I_ug3=((I_ug3/50)-1)*50;
		    		gran(&I_ug3,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_I_UG3,I_ug3);
				speed=1;
				}
			speed=1;
			}
	  	}
	else if(sub_ind==4)
		{
		tree_down(0,0);
		}
	}

else if(ind==iAvtRev)
	{
	ret(1000);
	if (but==butU)
		{      
		sub_ind--;
		gran_char(&sub_ind,0,8);
		}
		
	else if (but==butD)
		{
		sub_ind++;
		gran_char(&sub_ind,0,8);		
		}
	else if(sub_ind==0)
		{
		if((but==butR)||(but==butR_))
			{
			AVT_REV_IS_ON=1;
			}
		else if((but==butL)||(but==butL_))
			{
			AVT_REV_IS_ON=0;
			}
		if(AVT_REV_IS_ON!=lc640_read_int(EE_AVT_REV_IS_ON))lc640_write_int(EE_AVT_REV_IS_ON,AVT_REV_IS_ON);	
		}
	else if(sub_ind==1)
		{
		if(but==butR)
			{
			AVT_REV_TIME_FF++;
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<20)
				{
				AVT_REV_TIME_FF=(((AVT_REV_TIME_FF/10L)+1L)*10L);
				}
			else 
				{
				AVT_REV_TIME_FF=(((AVT_REV_TIME_FF/60L)+1L)*60L);
				}
			speed=1;
			}
		else if(but==butL)
			{
			AVT_REV_TIME_FF--;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<20)
				{
				AVT_REV_TIME_FF=(((AVT_REV_TIME_FF/10L)-1L)*10L);
				}
			else 
				{
				AVT_REV_TIME_FF=(((AVT_REV_TIME_FF/60L)-1L)*60L);
				}
			speed=1;
			}

		gran(&AVT_REV_TIME_FF,30,T_PROC_MAX);
		if(AVT_REV_TIME_FF!=lc640_read_int(EE_AVT_REV_TIME_FF))lc640_write_int(EE_AVT_REV_TIME_FF,AVT_REV_TIME_FF);	
		}

	else if(sub_ind==2)
		{
		if(but==butR)
			{
			AVT_REV_TIME_REW++;
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<20)
				{
				AVT_REV_TIME_REW=(((AVT_REV_TIME_REW/10L)+1L)*10L);
				}
			else 
				{
				AVT_REV_TIME_REW=(((AVT_REV_TIME_REW/60L)+1L)*60L);
				}
			speed=1;
			}
		else if(but==butL)
			{
			AVT_REV_TIME_REW--;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<20)
				{
				AVT_REV_TIME_REW=(((AVT_REV_TIME_REW/10L)-1L)*10L);
				}
			else 
				{
				AVT_REV_TIME_REW=(((AVT_REV_TIME_REW/60L)-1L)*60L);
				}
			speed=1;
			}

		gran(&AVT_REV_TIME_REW,30,T_PROC_MAX);
		if(AVT_REV_TIME_REW!=lc640_read_int(EE_AVT_REV_TIME_REW))lc640_write_int(EE_AVT_REV_TIME_REW,AVT_REV_TIME_REW);	
		}
	else if(sub_ind==3)
		{
		if(but==butR)
			{
			AVT_REV_TIME_PAUSE++;
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<20)
				{
				AVT_REV_TIME_PAUSE=(((AVT_REV_TIME_PAUSE/10L)+1L)*10L);
				}
			else 
				{
				AVT_REV_TIME_PAUSE=(((AVT_REV_TIME_PAUSE/60L)+1L)*60L);
				}
			speed=1;
			}
		else if(but==butL)
			{
			AVT_REV_TIME_PAUSE--;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<20)
				{
				AVT_REV_TIME_PAUSE=(((AVT_REV_TIME_PAUSE/10L)-1L)*10L);
				}
			else 
				{
				AVT_REV_TIME_PAUSE=(((AVT_REV_TIME_PAUSE/60L)-1L)*60L);
				}
			speed=1;
			}

		gran(&AVT_REV_TIME_PAUSE,2,600);
		if(AVT_REV_TIME_PAUSE!=lc640_read_int(EE_AVT_REV_TIME_PAUSE))lc640_write_int(EE_AVT_REV_TIME_PAUSE,AVT_REV_TIME_PAUSE);	
		}

	else if(sub_ind==4)
		{
		if(but==butR)
			{
			AVT_REV_I_NOM_FF++;
		    	gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/5)+1)*5;
		    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
				speed=1;
				}
			else 
				{
				AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/50)+1)*50;
		    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
				speed=1;
				}
			speed=1;
			}
		else if(but==butL)
			{
		    	AVT_REV_I_NOM_FF--;
		    	gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/5)-1)*5;
		    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
				speed=1;
				}
			else 
				{
				AVT_REV_I_NOM_FF=((AVT_REV_I_NOM_FF/50)-1)*50;
		    		gran(&AVT_REV_I_NOM_FF,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_FF,AVT_REV_I_NOM_FF);
				speed=1;
				}
			speed=1;
			}
	  	}
	else if(sub_ind==5)
		{
		if(but==butR)
			{
			AVT_REV_I_NOM_REW++;
		    	gran(&AVT_REV_I_NOM_REW,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_AVT_REV_I_NOM_REW,AVT_REV_I_NOM_REW);
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_I_NOM_REW=((AVT_REV_I_NOM_REW/5)+1)*5;
		    		gran(&AVT_REV_I_NOM_REW,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_REW,AVT_REV_I_NOM_REW);
				speed=1;
				}
			else 
				{
				AVT_REV_I_NOM_REW=((AVT_REV_I_NOM_REW/50)+1)*50;
		    		gran(&AVT_REV_I_NOM_REW,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_REW,AVT_REV_I_NOM_REW);
				speed=1;
				}
			speed=1;
			}
		else if(but==butL)
			{
		    	AVT_REV_I_NOM_REW--;
		    	gran(&AVT_REV_I_NOM_REW,I_MIN_IPS,I_MAX_IPS);
			lc640_write_int(EE_AVT_REV_I_NOM_REW,AVT_REV_I_NOM_REW);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_I_NOM_REW=((AVT_REV_I_NOM_REW/5)-1)*5;
		    		gran(&AVT_REV_I_NOM_REW,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_REW,AVT_REV_I_NOM_REW);
				speed=1;
				}
			else 
				{
				AVT_REV_I_NOM_REW=((AVT_REV_I_NOM_REW/50)-1)*50;
		    		gran(&AVT_REV_I_NOM_REW,I_MIN_IPS,I_MAX_IPS);
				lc640_write_int(EE_AVT_REV_I_NOM_REW,AVT_REV_I_NOM_REW);
				speed=1;
				}
			speed=1;
			}
	  	}
	else if(sub_ind==6)
		{
		if(but==butR)
			{
			AVT_REV_U_NOM_FF++;
		    	gran(&AVT_REV_U_NOM_FF,U_MIN,U_MAX);
			lc640_write_int(EE_AVT_REV_U_NOM_FF,AVT_REV_U_NOM_FF);
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_U_NOM_FF=((AVT_REV_U_NOM_FF/5)+1)*5;
		    		gran(&AVT_REV_U_NOM_FF,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_FF,AVT_REV_U_NOM_FF);
				speed=1;
				}
			else 
				{
				AVT_REV_U_NOM_FF=((AVT_REV_U_NOM_FF/50)+1)*50;
		    		gran(&AVT_REV_U_NOM_FF,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_FF,AVT_REV_U_NOM_FF);
				speed=1;
				}
			speed=1;
			}
		else if(but==butL)
			{
		    	AVT_REV_U_NOM_FF--;
		    	gran(&AVT_REV_U_NOM_FF,U_MIN,U_MAX);
			lc640_write_int(EE_AVT_REV_U_NOM_FF,AVT_REV_U_NOM_FF);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_U_NOM_FF=((AVT_REV_U_NOM_FF/5)-1)*5;
		    		gran(&AVT_REV_U_NOM_FF,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_FF,AVT_REV_U_NOM_FF);
				speed=1;
				}
			else 
				{
				AVT_REV_U_NOM_FF=((AVT_REV_U_NOM_FF/50)-1)*50;
		    		gran(&AVT_REV_U_NOM_FF,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_FF,AVT_REV_U_NOM_FF);
				speed=1;
				}
			speed=1;
			}
	  	}
	else if(sub_ind==7)
		{
		if(but==butR)
			{
			AVT_REV_U_NOM_REW++;
		    	gran(&AVT_REV_U_NOM_REW,U_MIN,U_MAX);
			lc640_write_int(EE_AVT_REV_U_NOM_REW,AVT_REV_U_NOM_REW);
			speed__=0;
			}
		else if(but==butR_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_U_NOM_REW=((AVT_REV_U_NOM_REW/5)+1)*5;
		    		gran(&AVT_REV_U_NOM_REW,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_REW,AVT_REV_U_NOM_REW);
				speed=1;
				}
			else 
				{
				AVT_REV_U_NOM_REW=((AVT_REV_U_NOM_REW/50)+1)*50;
		    		gran(&AVT_REV_U_NOM_REW,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_REW,AVT_REV_U_NOM_REW);
				speed=1;
				}
			speed=1;
			}
		else if(but==butL)
			{
		    	AVT_REV_U_NOM_REW--;
		    	gran(&AVT_REV_U_NOM_REW,U_MIN,U_MAX);
			lc640_write_int(EE_AVT_REV_U_NOM_REW,AVT_REV_U_NOM_REW);
			speed__=0;
			}
		else if(but==butL_)
			{
			speed__++;
			if(speed__<50)
				{
				AVT_REV_U_NOM_REW=((AVT_REV_U_NOM_REW/5)-1)*5;
		    		gran(&AVT_REV_U_NOM_REW,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_REW,AVT_REV_U_NOM_REW);
				speed=1;
				}
			else 
				{
				AVT_REV_U_NOM_REW=((AVT_REV_U_NOM_REW/50)-1)*50;
		    		gran(&AVT_REV_U_NOM_REW,U_MIN,U_MAX);
				lc640_write_int(EE_AVT_REV_U_NOM_REW,AVT_REV_U_NOM_REW);
				speed=1;
				}
			speed=1;
			}
	  	}
	else if((but==butE)&&(sub_ind==8))
		{
	     tree_down(0,0);
	     ret(0);
		}
     }
but_an_end:
n_but=0;


}

//-----------------------------------------------
void watchdog_enable (void) 
{
LPC_WDT->WDTC=2000000;
LPC_WDT->WDCLKSEL=0;
LPC_WDT->WDMOD=3;
LPC_WDT->WDFEED=0xaa;
LPC_WDT->WDFEED=0x55;
}

//-----------------------------------------------
void watchdog_reset (void) 
{
LPC_WDT->WDFEED=0xaa;
LPC_WDT->WDFEED=0x55;
}


//***********************************************
//***********************************************
//***********************************************
//***********************************************
//***********************************************
void SysTick_Handler (void) 	 /* SysTick Interrupt Handler (1ms)    */
{
//sys_plazma++;
b2000Hz=1;

if(bTPS)
	{
	LPC_GPIO1->FIODIR|=(1UL<<26);
	LPC_GPIO1->FIOPIN^=(1UL<<26);
	}

if(++t0cnt4>=2)
	{
t0cnt4=0;
b1000Hz=1;

	bFF=(char)(GET_REG(LPC_GPIO0->FIOPIN, 27, 1));
	if(bFF!=bFF_) hz_out++;
	bFF_=bFF;


if(++t0cnt5>=20)
     {
     t0cnt5=0;
     b50Hz=1;
     }
     
if(++t0cnt>=10)
     {
     t0cnt=0;
     b100Hz=1;

     hz_out_cnt++;
     if(hz_out_cnt>=500)
	     {	
	     hz_out_cnt=0;
	     net_F=hz_out;
	     hz_out=0;
	     }

     if(++t0cnt0>=10)
	     {
	     t0cnt0=0;
	     b10Hz=1;
		beep_drv();
		if(main_10Hz_cnt<10000) main_10Hz_cnt++;
	     }

     if(t0cnt0==5)
	     {
		//beep_drv();
		ind_fl_cnt++;
		if(ind_fl_cnt>=6)ind_fl_cnt=0;
	     }

     if(++t0cnt1>=20)
	     {
	     t0cnt1=0;
	     b5Hz=1;
		if(bFL5)bFL5=0;
		else bFL5=1;  
		bFL34++;
		if(bFL34>=6)bFL34=0;   
	     }

     if(++t0cnt2>=50)
	     {
	     t0cnt2=0;
	     b2Hz=1;
		if(bFL2)bFL2=0;
		else bFL2=1;
	     }         

     if(++t0cnt3>=100)
	     {
	     t0cnt3=0;
	     b1Hz=1;
		 if(main_1Hz_cnt<10000) main_1Hz_cnt++;

		if(bFL_REV)bFL_REV=0;
		else bFL_REV=1;
	     }
     }

	}
//LPC_GPIO0->FIOCLR|=0x00000001;

if(modbus_timeout_cnt<6)
	{
	modbus_timeout_cnt++;
	if(modbus_timeout_cnt>=6)
		{
		bMODBUS_TIMEOUT=1;
		}
	}
else if (modbus_timeout_cnt>6)
	{
	modbus_timeout_cnt=0;
	bMODBUS_TIMEOUT=0;
	}
  return;          



//LPC_GPIO0->FIOCLR|=0x00000001;
}


//***********************************************
__irq void timer0_interrupt(void) 
{	
/*if(BPS1_spa_leave)T0EMR_bit.EM1=0; 
else T0EMR_bit.EM1=1;
if(BPS2_spa_leave)T0EMR_bit.EM3=0; 
else T0EMR_bit.EM3=1;
T0IR = 0xff;*/
}

//===============================================
//===============================================
//===============================================
//===============================================
int main (void) 
{
char ind_reset_cnt=0;
//long i;
char mac_adr[6] = { 0x00,0x73,0x04,50,60,70 };

//i=200000;
//while(--i){};

SystemInit();

bTPS=1;

SysTick->LOAD = (SystemFrequency / 2000) - 1;
SysTick->CTRL = 0x07;

//init_timer( 0,SystemFrequency/2000/4 - 1 ); // 1ms	
//enable_timer( 0 );

SET_REG(LPC_GPIO0->FIODIR, 0, 27, 1);
SET_REG(LPC_GPIO2->FIODIR, 1, 7, 1);
SET_REG(LPC_GPIO2->FIODIR, 1, 8, 1);
//LPC_GPIO1->FIODIR  |= 1<<27;                
	;
//FIO1MASK = 0x00000000;	 
//LPC_GPIO0->FIODIR  |= 1<<27;
//LPC_GPIO0->FIOSET  |= 1<<27;

///SET_REG(LPC_GPIO0->FIODIR,0,10,1); //вход частоты 



ad7705_reset();
delay_ms(20);

ad7705_write(0x21);
ad7705_write(BIN8(1101)); 
ad7705_write(0x11);
ad7705_write(0x44);


ad7705_buff[0][1]=0x7fff;
ad7705_buff[0][2]=0x7fff;
ad7705_buff[0][3]=0x7fff;
ad7705_buff[0][4]=0x7fff;
ad7705_buff[0][5]=0x7fff;
ad7705_buff[0][6]=0x7fff;
ad7705_buff[0][7]=0x7fff;
ad7705_buff[0][8]=0x7fff;
ad7705_buff[0][9]=0x7fff;
ad7705_buff[0][10]=0x7fff;
ad7705_buff[0][11]=0x7fff;
ad7705_buff[0][12]=0x7fff;
ad7705_buff[0][13]=0x7fff;
ad7705_buff[0][14]=0x7fff;
ad7705_buff[0][15]=0x7fff;
ad7705_buff[1][1]=0x7fff;
ad7705_buff[1][2]=0x7fff;
ad7705_buff[1][3]=0x7fff;
ad7705_buff[1][4]=0x7fff;
ad7705_buff[1][5]=0x7fff;
ad7705_buff[1][6]=0x7fff;
ad7705_buff[1][7]=0x7fff;
ad7705_buff[1][8]=0x7fff;
ad7705_buff[1][9]=0x7fff;
ad7705_buff[1][10]=0x7fff;
ad7705_buff[1][11]=0x7fff;
ad7705_buff[1][12]=0x7fff;
ad7705_buff[1][13]=0x7fff;
ad7705_buff[1][14]=0x7fff;
ad7705_buff[1][15]=0x7fff;

ad7705_buff_[0]=0x7fff;
ad7705_buff_[1]=0x7fff;

/*
ad7705_reset();
delay_ms(20);

ad7705_write(0x20);
ad7705_write(BIN8(1101)); 
ad7705_write(0x10);
ad7705_write(0x44);

ad7705_reset();
delay_ms(20);  

ad7705_write(0x20);
ad7705_write(BIN8(1101)); 
ad7705_write(0x10);
ad7705_write(0x44); 

delay_ms(20); */




lcd_init();  
lcd_on();
lcd_clear();
		
///LPC_GPIO4->FIODIR |= (1<<29);           /* LEDs on PORT2 defined as Output    */
rtc_init();
///pwm_init();
ind=iMn;
//snmp_plazma=15;

memo_read();

can1_init(BITRATE62_5K25MHZ); 
can2_init(BITRATE125K25MHZ);
FullCAN_SetFilter(1,0x18a);
FullCAN_SetFilter(0,0x18e);

mac_adr[5]=*((char*)&AUSW_MAIN_NUMBER);
mac_adr[4]=*(((char*)&AUSW_MAIN_NUMBER)+1);
mac_adr[3]=*(((char*)&AUSW_MAIN_NUMBER)+2);
mem_copy (own_hw_adr, mac_adr, 6);

snmp_Community[0]=(char)lc640_read_int(EE_COMMUNITY); 
//if((snmp_Community[0]==0)||(snmp_Community[0]==' '))snmp_Community[0]=0;
snmp_Community[1]=(char)lc640_read_int(EE_COMMUNITY+2);
if((snmp_Community[1]==0)||(snmp_Community[1]==' '))snmp_Community[1]=0;
snmp_Community[2]=(char)lc640_read_int(EE_COMMUNITY+4);
if((snmp_Community[2]==0)||(snmp_Community[2]==' '))snmp_Community[2]=0;
snmp_Community[3]=(char)lc640_read_int(EE_COMMUNITY+6);
if((snmp_Community[3]==0)||(snmp_Community[3]==' '))snmp_Community[3]=0;
snmp_Community[4]=(char)lc640_read_int(EE_COMMUNITY+8);
if((snmp_Community[4]==0)||(snmp_Community[4]==' '))snmp_Community[4]=0;
snmp_Community[5]=(char)lc640_read_int(EE_COMMUNITY+10);
if((snmp_Community[5]==0)||(snmp_Community[5]==' '))snmp_Community[5]=0;
snmp_Community[6]=(char)lc640_read_int(EE_COMMUNITY+12);
if((snmp_Community[6]==0)||(snmp_Community[6]==' '))snmp_Community[6]=0;
snmp_Community[7]=(char)lc640_read_int(EE_COMMUNITY+14);
if((snmp_Community[7]==0)||(snmp_Community[7]==' '))snmp_Community[7]=0;
snmp_Community[8]=(char)lc640_read_int(EE_COMMUNITY+16);
if((snmp_Community[8]==0)||(snmp_Community[8]==' '))snmp_Community[8]=0;
snmp_Community[9]=0; /**/

if((lc640_read_int(EE_ETH_IS_ON)==1)&&(lc640_read_int(EE_ETH_IS_NOT)!=1))
	{
	bgnd_par(		"                    ",
     		"    Инициализация   ",
     		"      Ethernet      ",
     		"                    ");
	lc640_write_int(EE_ETH_IS_NOT,1);
	
	bitmap_hndl();
	lcd_out(lcd_bitmap);
	watchdog_enable();
	init_TcpNet ();
	lcd_out(lcd_bitmap);
	init_ETH();
	//mem_copy (&localm[NETIF_ETH], &ip_config, sizeof(ip_config));
//	lcd_out(lcd_bitmap);
	delay();
	delay();
	delay();
	delay();
	delay();
	lc640_write_int(EE_ETH_IS_NOT,0);
	} 
//event2snmp(2);

//reload_hndl();
//LPC_GPIO0->FIODIR |= (0x60000000);

adc_init();

LPC_GPIO0->FIODIR|=(1<<11);
LPC_GPIO0->FIOSET|=(1<<11);


//lc640_write_int(100,134);



UARTInit(0, 9600);	/* baud rate setting */


//sys_plazma1=sys_plazma;
ind_reset_cnt=58;

plazma_restart=1;

if(lc640_read_int(EE_RESTART_ENABLE)==reON)
	{
	plazma_restart=2;
	if(lc640_read_long(EE_TIME_PROC_GS_RESTART))
		{
		plazma_restart=3;
		time_proc=lc640_read_long(EE_TIME_PROC_GS_RESTART);
		time_proc_remain=lc640_read_long(EE_T_PROC_GS)-time_proc;
		ind=iMn;
		if(lc640_read_int(EE_MAIN_MENU_MODE)==mmmIT)
			{
			index_set=1;
			}
		else if(lc640_read_int(EE_MAIN_MENU_MODE)==mmmITIN)
			{
			index_set=1;
			}
		else if(lc640_read_int(EE_MAIN_MENU_MODE)==mmmINIT)
			{
			index_set=3;
			}
		work_stat=wsGS;
		plazma_restart=4;
		}
	if(lc640_read_long(EE_TIME_PROC_PS_RESTART))
		{
		time_proc=lc640_read_long(EE_TIME_PROC_PS_RESTART);
		time_proc_remain=lc640_read_long(EE_T_PROC_PS)-time_proc;
		ind=iMn;
		if(lc640_read_int(EE_MAIN_MENU_MODE)==mmmIN)
			{
			index_set=1;
			}
		else if(lc640_read_int(EE_MAIN_MENU_MODE)==mmmITIN)
			{
			index_set=3;
			}
		else if(lc640_read_int(EE_MAIN_MENU_MODE)==mmmINIT)
			{
			index_set=1;
			}
		work_stat=wsPS;
		}
	}

//lc640_write_int(EE_CAP_ZAR_TIME,1234);					
//lc640_write_int(EE_CAP_PAUSE1_TIME,2345);					
//lc640_write_int(EE_CAP_RAZR_TIME,3456);					
//lc640_write_int(EE_CAP_PAUSE2_TIME,4567);					

//lc640_write_int(EE_AVT_REV_TIME_FF,200);
main_cnt=0;

watchdog_enable();
	
while (1)  
	{
	bTPS=0; 
     //timer_poll ();
     main_TcpNet ();

	//watchdog_reset();
	if(bMODBUS_TIMEOUT)
		{
		bMODBUS_TIMEOUT=0;
		//modbus_plazma++;;
		modbus_in();
		}
	if(bRXIN0) 
		{
		bRXIN0=0;
	
		uart_in0();
		} 
	/*
	if(bRXIN1) 
		{
		bRXIN1=0;
	
		uart_in1();
		}*/ 
     if(b10000Hz)
		{
		b10000Hz=0; 
		

		}

     if(b2000Hz)
		{

		if(adc_window_cnt<200)adc_window_cnt++;

		b2000Hz=0; 
		
		
		}

	if(b1000Hz)
		{
		b1000Hz=0;
		adc_drv7();

		}
	
	if(b100Hz)
		{
		b100Hz=0;

		//LPC_GPIO2->FIODIR|=(1<<7);
		//LPC_GPIO2->FIOPIN^=(1<<7);		

		if(!bRESET)but_drv();
		but_an();
		}
		 
	if(b50Hz)
		{
		b50Hz=0;

		net_drv();
		}

	if(b10Hz)
		{
		char i;

     timer_tick ();
     tick = __TRUE;

		b10Hz=0;
				
				
		bps_drv(0);
		bps_hndl();

						
		unet_drv();

		
		
		ind_hndl(); 
		#ifndef SIMULATOR
		bitmap_hndl();
		if(!bRESET)
			{
			lcd_out(lcd_bitmap);
			}
		#endif
		//ad7705_drv();
		//ad7705_write(0x20);

		adc_window_cnt=0;  

		ret_hndl();  
		mess_hndl();
		ret_hndl();
		//cntrl_hndl();
		if(speed__==speed__old)
			{
			speed_cnt++;
			if(speed_cnt>5)
				{
				speed_cnt=0;
				speed__=0;
				speed__old=0;
				}
			}
		
		speed__old=speed__;

		viz_hndl();
		rele_current_stab_hndl();
		cap_time_hndl();
		}

	if(b5Hz)
		{
		b5Hz=0;

		if(!bRESET)
			{
			ad7705_drv();
			}
		if(!bRESET)
			{
			memo_read();
			}
		LPC_GPIO1->FIODIR|=(1UL<<26);
		matemat();
		
		//if(!bRESET)avar_hndl();
		snmp_data();
		//LPC_GPIO1->FIODIR|=(1UL<<31);
		//LPC_GPIO1->FIOPIN^=(1UL<<31);
		can_data_hndl();
		can2_out(33,*((char*)(&can_u)),*(((char*)(&can_u))+1),*((char*)(&can_i)),*(((char*)(&can_i))+1),(char)can_work_stat,*((char*)(&can_u_set)),*(((char*)(&can_u_set))+1));
		can2_out(34,*((char*)(&can_time)),*(((char*)(&can_time))+1),*((char*)(&can_time_set)),*(((char*)(&can_time_set))+1),0,*((char*)(&can_i_set)),*(((char*)(&can_i_set))+1));
		

  		}

	if(b2Hz)
		{
		b2Hz=0;

				//uart_out_adr1(dig,150);
		modbus_buf[0]=0x01;
		modbus_buf[1]=0x03;
		modbus_buf[2]=0x00;
		modbus_buf[3]=0x05;
		modbus_buf[4]=0x00;
		modbus_buf[5]=0x01;
		//modbus_buf[0]=33;
		//modbus_buf[0]=33;
		modbus_crc16=CRC16_2(modbus_buf,6);
		
  		}

	if(b1Hz)
		{
		b1Hz=0;
		if(!bRESET)
			{
			watchdog_reset();
			}
		//can1_out_adr((char*)&net_U,21);

		//samokalibr_hndl();
		
		//zar_drv();
		ubat_old_drv();
		//kb_hndl();
		beep_hndl();
				
		plazma_plazma_plazma++;

		if(++ind_reset_cnt>=60)
			{
			ind_reset_cnt=0;
			lcd_init();
			lcd_on();
			lcd_clear();
			}
               
          
		
		
		if(t_ext_can_nd<10) t_ext_can_nd++;
		
		//if(main_1Hz_cnt<200)main_1Hz_cnt++;


		can_reset_hndl();

		time_hndl();

		rele_current_stab_hndl();
		revers_hndl();
		if(main_cnt<1000)main_cnt++;




		}
	if(b1min)
		{
		b1min=0;

/*		if((tloaddisable_cmnd)&&(tloaddisable_cmnd<=10))
			{
			tloaddisable_cmnd--;
			if(!tloaddisable_cmnd)tloaddisable_cmnd=20;
			}
		if((tbatdisable_cmnd)&&(tbatdisable_cmnd<=10))
			{
			if(!tbatdisable_cmnd)tbatdisable_cmnd=20;
			}*/

		
		}
	
	/*if((((LPC_CAN1->GSR)&(0x00ff0000))>>16)>60) 
		{
		can1_init(BITRATE62_5K25MHZ);
		FullCAN_SetFilter(1,0x18a);
		FullCAN_SetFilter(0,0x18e);
		}*/
		
	if(bCAN1_INIT)
		{
		
		bCAN1_INIT=0;
		can1_init(BITRATE62_5K25MHZ); 
		FullCAN_SetFilter(1,0x18a);
		FullCAN_SetFilter(0,0x18e);
		}  
	}
}
