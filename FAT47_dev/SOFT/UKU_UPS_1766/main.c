#include "LPC17xx.H"
#include "main.h"                   /* LPC17xx definitions                */
//#include "ports_operations.h"
#include "button_drv.h"
#include "button_action.h"
#include "net_config.h"
#include "ind_drv.h"
#include "beeper_drv.h"
#include "control.h"
#include "gran.h"
#include "25lc640.h"
#include "memo.h"
#include "full_can.h"
#include "cmd.h"
#include "avar_hndl.h"
#include "led_break_drv.h"
#include "rtl.h"
#include "snmp_data_file.h"
#include "eeprom_map.h"
#include "ssd1306.h"
#include "i2c.h"
#include "ssd_1306.h"
//#include "simbol.h"
#include "simbol16x9.h"
#include "stdio.h"

extern LOCALM localm[];
extern U8 own_hw_adr[];
extern U8  snmp_Community[];
extern U16  snmp_PortNum;
extern U16  snmp_TrapPort;

unsigned char delete_oleg;
const char sm_mont[13][4]={"упс","янв","фев","мар","апр","май","июн","июл","авг","сен","окт","ноя","дек"}; //
char tcp_init_cnt;

/////

//------Таймер
short t100=10-10,t50=20-5,t10=100-25,t5=200-45,t2=500-65,t1=1000-85;   // подобрана фаза для несовпадения событий
char f1000Hz,f100Hz,f50Hz,f10Hz,f5Hz,f2Hz,f1Hz;								  // флаги срабатывания событий
BOOL tick;

//-----Индикация
char level_U,level_I,level_Q,init,ind_level_U,ind_level_I,ind_level_Q,flash_;
//typedef enum ind_mode{norm,reverse,alone,flash} ind_mode;	   // 3 вида режима отображения
ind_mode level_U_mode,level_I_mode,level_Q_mode; 
//-----------------------------------------------
//Индикация
stuct_ind a,b[10];
short ind_out[3];
char lcd_bitmap[1024];
char lcd_buffer[LCD_SIZE+100]={"QWERTYUIOP12345ZXCVBNMASDFGHJKL12345ФЫВА"};
//-----Состояние
//typedef enum work{power_net,acb} work;
work work_at=power_net;
//typedef enum stat{breakdown,active} stat;
stat work_stat;
signed short flash_net_def_cnt;	   
//-----
//**********************************************
//Коэффициенты, отображаемые из EEPROM
//signed short Ktsrc[2];
//signed short Kusrc[2];
//signed short Kisrc[2];
//signed short Ki0src[2];
signed short Kubat[2];
//signed short Kubatm[2];
signed short Kibat0[2];
signed short Kibat1[2];
//signed short Ktbat[2];
signed short Kunet;
//signed short Kunet_ext[3];
//signed short Ktext[3];
//signed short Kuload;
//
//signed short MAIN_IST;
//signed short UMAX;
//signed short UB0;
//signed short UB20;
//signed short TMAX;
//signed short TSIGN;
//signed short AV_OFF_AVT;
//signed short USIGN;
//signed short UMN;
//signed short ZV_ON;
//signed short IKB;
//signed short KVZ;
//signed short IMAX;
//signed short KIMAX;
//signed short APV_ON;
//signed short IZMAX;
//signed short U0B;
//signed short TZAS;
//signed short VZ_HR;
//signed short TBAT;
//signed short U_AVT;
//signed short DU;
//signed short PAR;
//signed short TBATMAX;
//signed short TBATSIGN;
//signed short UBM_AV;
//signed short TBOXMAX;
//signed short TBOXREG;
//signed short TBOXVENTMAX;
//signed short TLOADDISABLE;
//signed short TLOADENABLE;
//signed short TBATDISABLE;
//signed short TBATENABLE;
//
//signed short NUMBAT;
//signed short NUMIST;
//signed short NUMINV;
//signed short NUMDT;
//signed short NUMSK;
//signed short NUMEXT;
//signed short NUMAVT;
//
//enum_apv_on APV_ON1,APV_ON2;
//signed short APV_ON2_TIME;
//
//enum_bat_is_on BAT_IS_ON[2];
//signed short BAT_DAY_OF_ON[2];
//signed short BAT_MONTH_OF_ON[2];
//signed short BAT_YEAR_OF_ON[2];
//signed short BAT_C_NOM[2];
//signed short BAT_RESURS[2];
//signed short BAT_C_REAL[2];
//
//unsigned short AUSW_MAIN;
//unsigned long 	AUSW_MAIN_NUMBER;
//unsigned short AUSW_DAY;
//unsigned short AUSW_MONTH;
//unsigned short AUSW_YEAR;
//unsigned short AUSW_UKU;
//unsigned short AUSW_UKU_SUB;
//unsigned long AUSW_UKU_NUMBER;
//unsigned long	AUSW_BPS1_NUMBER;
//unsigned long  AUSW_BPS2_NUMBER;
//unsigned short AUSW_RS232;
//unsigned short AUSW_PDH;
//unsigned short AUSW_SDH;
//unsigned short AUSW_ETH;
//
//signed short TMAX_EXT_EN[3];
//signed short TMAX_EXT[3];
//signed short TMIN_EXT_EN[3];
//signed short TMIN_EXT[3];
//signed short T_EXT_REL_EN[3];
//signed short T_EXT_ZVUK_EN[3];
//signed short T_EXT_LCD_EN[3];
//signed short T_EXT_RS_EN[3];
//
//signed short SK_SIGN[4];
//signed short SK_REL_EN[4];
//signed short SK_ZVUK_EN[4];
//signed short SK_LCD_EN[4];
//signed short SK_RS_EN[4];
//
//enum_avz AVZ;
//
//unsigned short HOUR_AVZ;
//unsigned short MIN_AVZ;
//unsigned short SEC_AVZ;
//unsigned short DATE_AVZ;
//unsigned short MONTH_AVZ;
//unsigned short YEAR_AVZ;
//unsigned short AVZ_TIME;
//
//enum_mnemo_on MNEMO_ON;
//unsigned short MNEMO_TIME;
//
//signed short POWER_CNT_ADRESS;
//
//signed short ETH_IS_ON;
signed long SERIAL_NUMBER;

//***********************************************
//ETH-настройки
signed short ETH_IP_1;
signed short ETH_IP_2;
signed short ETH_IP_3;
signed short ETH_IP_4;
signed short ETH_NET_MASK_1;
signed short ETH_NET_MASK_2;
signed short ETH_NET_MASK_3;
signed short ETH_NET_MASK_4;
signed short ETH_DEF_GATW_1;
signed short ETH_DEF_GATW_2;
signed short ETH_DEF_GATW_3;
signed short ETH_DEF_GATW_4;

//
//signed short ETH_SNMP_PORT_READ;
//signed short ETH_SNMP_PORT_WRITE;
//


//***********************************************
//SNMP-настройки
signed short SNMP_READ_PORT;
signed short SNMP_WRITE_PORT;
signed short SNMP_TRAP1_IP_1;
signed short SNMP_TRAP1_IP_2;
signed short SNMP_TRAP1_IP_3;
signed short SNMP_TRAP1_IP_4;
signed short SNMP_TRAP2_IP_1;
signed short SNMP_TRAP2_IP_2;
signed short SNMP_TRAP2_IP_3;
signed short SNMP_TRAP2_IP_4;
signed short SNMP_TRAP3_IP_1;
signed short SNMP_TRAP3_IP_2;
signed short SNMP_TRAP3_IP_3;
signed short SNMP_TRAP3_IP_4;
signed short SNMP_TRAP4_IP_1;
signed short SNMP_TRAP4_IP_2;
signed short SNMP_TRAP4_IP_3;
signed short SNMP_TRAP4_IP_4;
signed short SNMP_TRAP5_IP_1;
signed short SNMP_TRAP5_IP_2;
signed short SNMP_TRAP5_IP_3;
signed short SNMP_TRAP5_IP_4;

//***********************************************
//Трап-настройки
signed short MAIN_POWER_TRAP_SEND_OF_AV;
signed short MAIN_POWER_TRAP_SEND_OF_NO_AV;
signed short INVERTER_TEMPERATURE_TRAP_SEND_OF_AV;
signed short INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV;
signed short INVERTER_VOLTAGE_TRAP_SEND_OF_AV;
signed short INVERTER_VOLTAGE_TRAP_SEND_OF_NO_AV;
signed short INVERTER_CURRENT_TRAP_SEND_OF_AV;
signed short INVERTER_CURRENT_TRAP_SEND_OF_NO_AV;
signed short BATTERY_VOLTAGE_TRAP_SEND_OF_AV;
signed short BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV;


//***********************************************
//Структура ИБЭПа
char cnt_of_slave=8;
//***********************************************
//Состояние источников
BPS_STAT bps[12];
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
//Состояние первичной сети
char net_av;
signed short net_stat_cnt=0;



//-----------------------------------------------
//Кнопки
char speed,l_but,n_but;
char but;                            
unsigned long but_n,but_s;
char but0_cnt;
char but1_cnt;
char but_onL_temp;


signed short main_cnt;
char plazma_pal;
signed short rele_cnt;
char bRELE;
//-----------------------------------------------
void ind_hndl(void)
{
if(ind==iMn)
	{
	}
if(ind==iDef_net_set)
	{
	}
}

//-----------------------------------------------
void delay_us(long del)
{
long temp;
temp=5*del;

while (--temp);
return;
}

//-----------------------------------------------
void Delay (unsigned long tick) 
{       
unsigned long syst;

syst = tick;
while (--syst);
}


#define butLRC_		120
#define butC_		125
#define butC		253
#define butR_		126
#define butR		254
#define butL_		123
#define butL		251
#define butLR		250
#define butE		247
#define butE_		247-128

 /*
//-----------------------------------------------
void bitmap_hndl(void)
{
short x,ii,i;
unsigned int ptr_bitmap;
static char ptr_cnt,ptr_cnt1,ptr_cnt2,ptr_cnt3,ptr_cnt4;

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

//-----------------------------------------------
void bitmap_hndl2(void)
{
short x,ii,i;
unsigned int ptr_bitmap;
static char ptr_cnt,ptr_cnt1,ptr_cnt2,ptr_cnt3,ptr_cnt4;

for(ii=0;ii<1023;ii++)
	{
	lcd_bitmap[ii]=0x00;
	}
//lcd_bitmap[0]=caracter2[0];
//lcd_bitmap[128]=caracter2[0];
for(i=0;i<4;i++)
	{
	ptr_bitmap=4+(256*(unsigned)i);
	
//lcd_bitmap[ptr_bitmap++]=caracter2[0];

	for(x=(12*i);x<((12*i)+12);x++)
	 	{
		lcd_bitmap[ptr_bitmap++]=caracter2[((unsigned)lcd_buffer[x])*20];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+1];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+2];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+3];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+4];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+5];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+6];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+7];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+8];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+9];
		}  
	
	ptr_bitmap=(256*(unsigned)i)+132;
	for(x=(12*i);x<((12*i)+12);x++)
		{
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+10];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+11];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+12];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+13];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+14];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+15];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+16];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+17];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+18];
		lcd_bitmap[ptr_bitmap++]=caracter2[(((unsigned)lcd_buffer[x])*20)+19];
		} 
	}
}
*/
//-----------------------------------------------
void bitmap_hndl16x9(void)
{
short x,i,a;
unsigned int ptr_bitmap, z;


for(i=0;i<1023;i++)
	{
	lcd_bitmap[i]=0;
	}


for(i=0;i<4;i++) {
	for(x=0;x<10;x++)
	 	{
		//если 192 то надо 93
		if(lcd_buffer[x+10*i]>191) z=((lcd_buffer[x+10*i]-99)*24);
		if(lcd_buffer[x+10*i]>31) z=(lcd_buffer[x+10*i]-32)*24;
		else z=0;

		ptr_bitmap=(256*(unsigned)i)+(12*x);
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+2];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+4];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+6];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+8];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+10];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+12];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+14];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+16];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+18];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+20];
		ptr_bitmap=(256*(unsigned)i)+(12*x)+128;
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+1];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+3];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+5];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+7];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+9];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+11];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+13];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+15];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+17];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+19];
		lcd_bitmap[ptr_bitmap++]=caracter16x9[z+21];
		} 
	

	 
	}

}
//-----------------------------------------------
void but_an(void)
{
if(!n_but)goto but_an_end;

snmp_trap_send("Main power alarm. Power source is ACB",1,1);


if(ind==iMn)
	{
	if((but==butLRC_)||(but==butE_))
		{
		ind=iDef_net_set;
		}
	if(but==butC_)
		{
		ind=iK;
		sub_ind=0;
		}
	if(but==butE)
		{
		snmp_trap_send("Main power alarm. Power source is ACB",1,1);
		}

	}

else if(ind==iDef_net_set)
	{
	if((but==butLRC_)||(but==butE_))
		{
		char i;

		ind=iMn;

			ETH_IP_1=192;
			ETH_IP_2=168;
			ETH_IP_3=1;
			ETH_IP_4=1;
			lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
			lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
			lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
			lc640_write_int(EE_ETH_IP_4,ETH_IP_4); 

			ETH_NET_MASK_1=255;
			ETH_NET_MASK_2=255;
			ETH_NET_MASK_3=255;
			ETH_NET_MASK_4=0;
			lc640_write_int(EE_ETH_NET_MASK_1,ETH_NET_MASK_1);
			lc640_write_int(EE_ETH_NET_MASK_2,ETH_NET_MASK_2);
			lc640_write_int(EE_ETH_NET_MASK_3,ETH_NET_MASK_3);
			lc640_write_int(EE_ETH_NET_MASK_4,ETH_NET_MASK_4);

			ETH_DEF_GATW_1=192;
			ETH_DEF_GATW_2=168;
			ETH_DEF_GATW_3=1;
			ETH_DEF_GATW_4=254;
			lc640_write_int(EE_ETH_DEF_GATW_1,ETH_DEF_GATW_1);
			lc640_write_int(EE_ETH_DEF_GATW_2,ETH_DEF_GATW_2);
			lc640_write_int(EE_ETH_DEF_GATW_3,ETH_DEF_GATW_3);
			lc640_write_int(EE_ETH_DEF_GATW_4,ETH_DEF_GATW_4);

			snmp_snmp_settings_read_community[0]='p';
			snmp_snmp_settings_read_community[1]='u';
			snmp_snmp_settings_read_community[2]='b';
			snmp_snmp_settings_read_community[3]='l';
			snmp_snmp_settings_read_community[4]='i';
			snmp_snmp_settings_read_community[5]='c';
			snmp_snmp_settings_read_community[6]=0;
			snmp_snmp_settings_read_community[7]=0;
			snmp_snmp_settings_read_community[8]=0;
			snmp_snmp_settings_read_community[9]=0;
			snmp_snmp_settings_read_community[10]=0;
			snmp_snmp_settings_read_community[11]=0;
			snmp_snmp_settings_read_community[12]=0;
			snmp_snmp_settings_read_community[13]=0;
			snmp_snmp_settings_read_community[14]=0;
			snmp_snmp_settings_read_community[15]=0;

			for(i=0;i<16;i++)
				{
				lc640_write(EE_SNMP_READ_COMMUNITY+i,snmp_snmp_settings_read_community[i]);
				}

			SNMP_READ_PORT=161;
			lc640_write_int(EE_SNMP_READ_PORT,SNMP_READ_PORT);
			SNMP_WRITE_PORT=162;
			lc640_write_int(EE_SNMP_WRITE_PORT,SNMP_WRITE_PORT); /**/

		}
	}

else if(ind==iK)
	{
	if(but==butC_)
		{
		ind=iMn;
		}
	if(but==butC)
		{
		sub_ind++;
		if(sub_ind>=6)sub_ind=0;
		}
	else if(sub_ind==0)
		{
		if(but==butR)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+2,(0*16)+2,0,0,0);
			}
		else if(but==butR_)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+3,(0*16)+3,0,0,0);
			}
		else if(but==butL)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+4,(0*16)+4,0,0,0);
			}
		else if(but==butL_)
			{
			can1_out(NUMB,NUMB,KLBR,(0*16)+5,(0*16)+5,0,0,0);
			}

		}
	else if(sub_ind==1)
		{
		if(but==butR)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+2,(2*16)+2,0,0,0);
			}
		else if(but==butR_)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+3,(2*16)+3,0,0,0);
			}
		else if(but==butL)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+4,(2*16)+4,0,0,0);
			}
		else if(but==butL_)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+5,(2*16)+5,0,0,0);
			}
		else if(but==butLR)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+1,(2*16)+1,0,0,0);
			}
		}

	else if(sub_ind==2)
		{
		if(but==butR)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+2,(3*16)+2,0,0,0);
			}
		else if(but==butR_)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+3,(3*16)+3,0,0,0);
			}
		else if(but==butL)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+4,(3*16)+4,0,0,0);
			}
		else if(but==butL_)
			{
			can1_out(NUMB,NUMB,KLBR,(3*16)+5,(3*16)+5,0,0,0);
			}

		}
#define UAKB_L 1500
#define UAKB_H 2100
	else if(sub_ind==3)
		{
		if(but==butR)
			{
			Kubat[0]+=2;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}
		else if(but==butR_)
			{
			Kubat[0]+=5;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}
		else if(but==butL)
			{
			Kubat[0]-=2;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}
		else if(but==butL_)
			{
			Kubat[0]-=5;
			gran(&Kubat[0],UAKB_L,UAKB_H);
			lc640_write_int(EE_KUBAT1,Kubat[0]);
			}

		}

#define IAKB_L 500
#define IAKB_H 1500
	else if(sub_ind==4)
		{
		if(but==butR)
			{
			Kibat1[0]+=5;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butR_)
			{
			Kibat1[0]+=20;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butL)
			{
			Kibat1[0]-=5;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butL_)
			{
			Kibat1[0]-=20;
			gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI1BAT1,Kibat1[0]);
			}
		else if(but==butLR)
			{
			Kibat0[0]=adc_buff_[1];
			//gran(&Kibat1[0],IAKB_L,IAKB_H);
			lc640_write_int(EE_KI0BAT1,Kibat0[0]);			}


		}

	else if(sub_ind==5)
		{
		if(but==butR)
			{
			Kunet++;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		else if(but==butR_)
			{
			Kunet+=5;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		else if(but==butL)
			{
			Kunet--;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		else if(but==butL_)
			{
			Kunet-=5;
			gran(&Kunet,900,1300);
			lc640_write_int(EE_KUNET,Kunet);
			}
		}

	}

	   
but_an_end:
n_but=0;

}	


#define BUT_ON 4
#define BUT_ONL 20 

#define BUT0	24	 //R
#define BUT1	25	 //C
#define BUT2	26	 //L
#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)
//-----------------------------------------------
void but_drv(void)
{
LPC_GPIO1->FIODIR&=~BUT_MASK;
LPC_PINCON->PINMODE3&=~(0x3f<<12);
#if(BUT0<16)
	{
	LPC_PINCON->PINMODE3&=~(1<<(BUT0*2))&~(1<<((BUT0*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINMODE3&=~(1<<((BUT0-16)*2))&~(1<<(((BUT0-16)*2)+1));
	}
#endif
#if(BUT1<16)
	{
	LPC_PINCON->PINMODE3&=~(1<<(BUT1*2))&~(1<<((BUT1*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINMODE3&=~(1<<((BUT1-16)*2))&~(1<<(((BUT1-16)*2)+1));
	}
#endif
#if(BUT2<16)
	{
	LPC_PINCON->PINMODE3&=~(1<<(BUT2*2))&~(1<<((BUT2*2)+1));
	}
#else 	
	{
	LPC_PINCON->PINMODE3&=~(1<<((BUT2-16)*2))&~(1<<(((BUT2-16)*2)+1));
	}
#endif

LPC_GPIO1->FIODIR&=~(1<<30);
LPC_PINCON->PINMODE3&=~(1<<((30-16)*2))&~(1<<(((30-16)*2)+1));


//but=LPC_GPIO1->FIOPIN&(7<<BUT0);	  // читаем 3 бита с порта
//but=LPC_GPIO1->FIOPIN|(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2))&(~(1UL<<BUT3))&(~(1UL<<BUT4));

//but>>=BUT0;		// преобразуем в удобный вид






but_n=LPC_GPIO1->FIOPIN|(0xFFFFFFFFUL&(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2)));
but_n>>=BUT0;
if(LPC_GPIO1->FIOPIN&(1<<30))but_n|=(1<<3);
else but_n&=~(1<<3);
if((but_n==0xffUL)||(but_n!=but_s))
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
LPC_GPIO1->FIODIR&=~(1UL<<BUT0)&~(1UL<<BUT1)&~(1UL<<BUT2);
	   
}





//Таймер

void rtc_init (void) 
{
LPC_RTC->CCR=0x11;
}

//-----------------------------------------------
void net_drv(void)
{ 
//char temp_;    

if(++cnt_net_drv>=24) cnt_net_drv=0; //всего 16 посылок

if(cnt_net_drv<=7) // с 1 по 12 посылки адресные		  /**/
	{    
	can1_out(cnt_net_drv,cnt_net_drv,GETTM,bps[cnt_net_drv]._flags_tu,*((char*)(&bps[cnt_net_drv]._vol_u)),*((char*)((&bps[cnt_net_drv]._vol_u))+1),*((char*)(&bps[cnt_net_drv]._vol_i)),*((char*)((&bps[cnt_net_drv]._vol_i))+1));
     
	if(cnt_net_drv<cnt_of_slave)
	     {
	     if(bps[cnt_net_drv]._cnt<CNT_SRC_MAX)
   	 		{    
   	 		bps[cnt_net_drv]._cnt++;
   	 		if( (bps[cnt_net_drv]._cnt>=CNT_SRC_MAX) /*&& (!net_av)*/ && (!(bps[cnt_net_drv]._av&0x08)) ) 
   	 			{
 	 			avar_bps_hndl(cnt_net_drv,3,1);
   	 			}
   	 		}
		else bps[cnt_net_drv]._cnt=CNT_SRC_MAX;
						
		if((bps[cnt_net_drv]._cnt>=3)&&(bps[cnt_net_drv]._cnt_old<3))bps[cnt_net_drv]._cnt_more2++;
		bps[cnt_net_drv]._cnt_old=bps[cnt_net_drv]._cnt;
	     }
	}

else if(cnt_net_drv==8)
	{
//     can1_out(cnt_net_drv,cnt_net_drv,*((char*)(&Uvv[0])),*((char*)((&Uvv[0]))+1),*((char*)(&Uvv[1])),*((char*)((&Uvv[1]))+1),0,bRESET_EXT);
     }

else if(cnt_net_drv==9)
	{
//     can1_out(cnt_net_drv,cnt_net_drv,(char)main_vent_pos,*((char*)(&POWER_CNT_ADRESS)),*((char*)((&POWER_CNT_ADRESS))+1),0,0,0);
     }

else if(cnt_net_drv==10)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     }

else if(cnt_net_drv==12)
	{
//     can1_out(0xff,0xff,MEM_KF,*((char*)(&UMAX)),*((char*)((&UMAX))+1),*((char*)(&DU)),*((char*)((&DU))+1),0);
     } 
     
else if(cnt_net_drv==13)
	{
//     can1_out(0xff,0xff,MEM_KF1,*((char*)(&TMAX)),*((char*)((&TMAX))+1),*((char*)(&TSIGN)),*((char*)((&TSIGN))+1),(char)TZAS);
     } 
else if(cnt_net_drv==14)
	{                 
//	can2_out(0xff,0xff,MEM_KF2,*((char*)(&U_INV_MAX)),*((char*)((&U_INV_MAX))+1),*((char*)(&U_INV_MIN)),*((char*)((&U_INV_MIN))+1),(char)T_INV_MAX);
     }
	
	
else if(cnt_net_drv==20)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     }
else if(cnt_net_drv==21)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 
else if(cnt_net_drv==22)
	{
     can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 
else if(cnt_net_drv==23)
	{                 
	can1_out(cnt_net_drv,cnt_net_drv,0,0,0,0,0,0);
     } 	 
}


//-----------------------------------------------
void init_ETH(void)
{

localm[NETIF_ETH].IpAdr[0]=lc640_read_int(EE_ETH_IP_1);
localm[NETIF_ETH].IpAdr[1]=lc640_read_int(EE_ETH_IP_2);
localm[NETIF_ETH].IpAdr[2]=lc640_read_int(EE_ETH_IP_3);
localm[NETIF_ETH].IpAdr[3]=lc640_read_int(EE_ETH_IP_4);

localm[NETIF_ETH].NetMask[0]=lc640_read_int(EE_ETH_NET_MASK_1);
localm[NETIF_ETH].NetMask[1]=lc640_read_int(EE_ETH_NET_MASK_2);
localm[NETIF_ETH].NetMask[2]=lc640_read_int(EE_ETH_NET_MASK_3);
localm[NETIF_ETH].NetMask[3]=lc640_read_int(EE_ETH_NET_MASK_4);

localm[NETIF_ETH].DefGW[0]=lc640_read_int(EE_ETH_DEF_GATW_1);
localm[NETIF_ETH].DefGW[1]=lc640_read_int(EE_ETH_DEF_GATW_2);
localm[NETIF_ETH].DefGW[2]=lc640_read_int(EE_ETH_DEF_GATW_3);
localm[NETIF_ETH].DefGW[3]=lc640_read_int(EE_ETH_DEF_GATW_4); 

}


//-----------------------------------------------
static void timer_poll () 
{
//if (SysTick->CTRL & 0x10000) 
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
void ADC_IRQHandler(void) {
LPC_ADC->ADCR &=  ~(7<<24);



adc_self_ch_buff[adc_self_ch_cnt]=(LPC_ADC->ADGDR>>4) & 0xFFF;/* Read Conversion Result             */
adc_self_ch_cnt++;
if(adc_self_ch_cnt<3)
	{
	LPC_ADC->ADCR |=  (1<<24);
	}
}



void SysTick_Handler (void) 	 /* SysTick Interrupt Handler (1ms)    */
{
f1000Hz=1;

if (++t100==10)
	{
	f100Hz=1;
	t100=0;
	}

if (++t50==20)
	{
	f50Hz=1;
	t50=0;
	}

if (++t10==100)
	{
	f10Hz=1;
	t10=0;
	}

if (++t5==200)
	{
	f5Hz=1;
	t5=0;
	}

if (++t2==500)
	{
	f2Hz=1;
	t2=0;
	}

if (++t1==1000)
	{
	f1Hz=1;
	t1=0;
	}

}
//===============================================
//===============================================
//===============================================
//===============================================
int main (void)
{
short iiii_;
char mac_adr[6] = { 0x00,0x73,0x05,50,60,70 };

SystemInit();

SysTick_Config(SystemFrequency/1000 - 1); /* Generate interrupt each 1 ms   */

LPC_GPIO1->FIODIR|=(1<<20);	  // для ресета
LPC_GPIO1->FIODIR&=~(1<<28);	 // выход контроля наличия сети

///beep(0,0,0,0,0); //инициализация
///blink(0,0,0,0);
///rtc_init();
///LPC_GPIO0->FIODIR|=(1<<POWER_NET);
///LPC_GPIO0->FIOCLR|=(1<<POWER_NET);
///LPC_GPIO1->FIOPIN^=(1<<20);
Delay(10000000);
///LPC_GPIO1->FIOPIN^=(1<<20);
///LPC_GPIO0->FIOSET|=(1<<POWER_NET);

adc_init();

///can1_init(BITRATE62_5K6_25MHZ);
///FullCAN_SetFilter(0,0x18e);

///memo_read();
///LPC_GPIO1->FIOPIN^=(1<<20);
///avar_bps_hndl(NUMB,3,1);
//  init=1;	  // для тестов

SERIAL_NUMBER=lc640_read_long(EE_SERIAL_NUMBER);

mac_adr[5]=*((char*)&SERIAL_NUMBER);
mac_adr[4]=*(((char*)&SERIAL_NUMBER)+1);
mac_adr[3]=*(((char*)&SERIAL_NUMBER)+2);

mem_copy (own_hw_adr, mac_adr, 6);

LPC_GPIO1->FIOPIN^=(1<<20);


snmp_Community[0]=(char)lc640_read(EE_SNMP_READ_COMMUNITY);
if((snmp_Community[0]==0)||(snmp_Community[0]==' '))snmp_Community[0]=0;
snmp_Community[1]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+1);
if((snmp_Community[1]==0)||(snmp_Community[1]==' '))snmp_Community[1]=0;
snmp_Community[2]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+2);
if((snmp_Community[2]==0)||(snmp_Community[2]==' '))snmp_Community[2]=0;
snmp_Community[3]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+3);
if((snmp_Community[3]==0)||(snmp_Community[3]==' '))snmp_Community[3]=0;
snmp_Community[4]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+4);
if((snmp_Community[4]==0)||(snmp_Community[4]==' '))snmp_Community[4]=0;
snmp_Community[5]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+5);
if((snmp_Community[5]==0)||(snmp_Community[5]==' '))snmp_Community[5]=0;
snmp_Community[6]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+6);
if((snmp_Community[6]==0)||(snmp_Community[6]==' '))snmp_Community[6]=0;
snmp_Community[7]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+7);
if((snmp_Community[7]==0)||(snmp_Community[7]==' '))snmp_Community[7]=0;
snmp_Community[8]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+8);
if((snmp_Community[8]==0)||(snmp_Community[8]==' '))snmp_Community[8]=0;
snmp_Community[9]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+9); 
if((snmp_Community[9]==0)||(snmp_Community[9]==' '))snmp_Community[9]=0;
snmp_Community[10]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+10); 
if((snmp_Community[10]==0)||(snmp_Community[10]==' '))snmp_Community[10]=0;
snmp_Community[11]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+11); 
if((snmp_Community[11]==0)||(snmp_Community[11]==' '))snmp_Community[11]=0;
snmp_Community[12]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+12); 
if((snmp_Community[12]==0)||(snmp_Community[12]==' '))snmp_Community[12]=0;
snmp_Community[13]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+13); 
if((snmp_Community[13]==0)||(snmp_Community[13]==' '))snmp_Community[13]=0;
snmp_Community[14]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+14); 
if((snmp_Community[14]==0)||(snmp_Community[14]==' '))snmp_Community[14]=0;
snmp_Community[15]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+15); 
if((snmp_Community[15]==0)||(snmp_Community[15]==' '))snmp_Community[15]=0;
///snmp_Community[16]=0; 
///LPC_GPIO1->FIOPIN^=(1<<20);
///snmp_PortNum  = lc640_read_int(EE_SNMP_READ_PORT);
///snmp_TrapPort = lc640_read_int(EE_SNMP_WRITE_PORT); 
///LPC_GPIO1->FIOPIN^=(1<<20);
///	init_TcpNet ();
/// LPC_GPIO1->FIOPIN^=(1<<20);
///	init_ETH();
///LPC_GPIO1->FIOPIN^=(1<<20); 


i2c_init();
ssd1306_init(SSD1306_SWITCHCAPVCC); 
//LPC_GPIO2->FIODIR|=(1<<9);
//LPC_GPIO2->FIOPIN|=(1<<9);


 sprintf(lcd_buffer,"asd");
 bitmap_hndl16x9();
 for(iiii_=0;iiii_<1024;iiii_++)	ssd1306_data(lcd_bitmap[iiii_]);
while(1){
  bitmap_hndl16x9();
 for(iiii_=0;iiii_<1024;iiii_++)	ssd1306_data(lcd_bitmap[iiii_]);
 Delay(100000);
 delete_oleg++;;
}

while(1)
	{
	if(f1000Hz)
		{
		f1000Hz=0;
		adc_drv7();
		//ind_drv();
		}
	if(f100Hz)
		{
		f100Hz=0;
		LPC_GPIO1->FIODIR^=(1<<20);	 // сброс супервизора
		//button_on();
		blinker();
		beeper();
		but_drv();
		but_an();
		}
	if(f50Hz)
		{
		f50Hz=0;
		if (init) net_drv(); // задержка опросов иначе зависает кан

		}
	if(f10Hz)
		{
		f10Hz=0;
		LPC_GPIO1->FIOPIN^=(1<<20);
		//button_act();		// обрабатываем реакцию на нажатие кнопок L C R
		unet_drv();			// следилка за сетью 220
		if(main_cnt>2)inv_drv(NUMB);
		 
		timer_poll ();
     	main_TcpNet ();

		ind_hndl();
		
		if(tcp_init_cnt)
			{
			tcp_init_cnt--;
			if(!tcp_init_cnt)
				{
				

snmp_Community[0]=(char)lc640_read(EE_SNMP_READ_COMMUNITY);
//if((snmp_Community[0]==0)||(snmp_Community[0]==' '))snmp_Community[0]=0;
snmp_Community[1]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+1);
if((snmp_Community[1]==0)||(snmp_Community[1]==' '))snmp_Community[1]=0;
snmp_Community[2]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+2);
if((snmp_Community[2]==0)||(snmp_Community[2]==' '))snmp_Community[2]=0;
snmp_Community[3]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+3);
if((snmp_Community[3]==0)||(snmp_Community[3]==' '))snmp_Community[3]=0;
snmp_Community[4]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+4);
if((snmp_Community[4]==0)||(snmp_Community[4]==' '))snmp_Community[4]=0;
snmp_Community[5]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+5);
if((snmp_Community[5]==0)||(snmp_Community[5]==' '))snmp_Community[5]=0;
snmp_Community[6]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+6);
if((snmp_Community[6]==0)||(snmp_Community[6]==' '))snmp_Community[6]=0;
snmp_Community[7]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+7);
if((snmp_Community[7]==0)||(snmp_Community[7]==' '))snmp_Community[7]=0;
snmp_Community[8]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+8);
if((snmp_Community[8]==0)||(snmp_Community[8]==' '))snmp_Community[8]=0;
snmp_Community[9]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+9); 
if((snmp_Community[9]==0)||(snmp_Community[9]==' '))snmp_Community[9]=0;
snmp_Community[10]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+10); 
if((snmp_Community[10]==0)||(snmp_Community[10]==' '))snmp_Community[10]=0;
snmp_Community[11]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+11); 
if((snmp_Community[11]==0)||(snmp_Community[11]==' '))snmp_Community[11]=0;
snmp_Community[12]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+12); 
if((snmp_Community[12]==0)||(snmp_Community[12]==' '))snmp_Community[12]=0;
snmp_Community[13]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+13); 
if((snmp_Community[13]==0)||(snmp_Community[13]==' '))snmp_Community[13]=0;
snmp_Community[14]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+14); 
if((snmp_Community[14]==0)||(snmp_Community[14]==' '))snmp_Community[14]=0;
snmp_Community[15]=(char)lc640_read(EE_SNMP_READ_COMMUNITY+15); 
if((snmp_Community[15]==0)||(snmp_Community[15]==' '))snmp_Community[15]=0;
snmp_Community[16]=0;

snmp_PortNum  = lc640_read_int(EE_SNMP_READ_PORT);
snmp_TrapPort = lc640_read_int(EE_SNMP_WRITE_PORT);

	init_TcpNet ();

	init_ETH();
				}
			}
		}
	if(f5Hz)
		{
		f5Hz=0;
		if(!init)			// просто эффект инициализации
			{
			if (level_U<10) {++level_U;++level_I;++level_Q;}
			else if(!init) {init=1;level_U=level_I=level_Q=0;}
			}
		avar_hndl();
		memo_read();
		if (init) matemat();
		rele_hndl();
		snmp_data();
		}
	if(f2Hz)
		{
		short iiii;
		char data;
		f2Hz=0;
		if(level_U_mode==flash||level_I_mode==flash||level_Q_mode==flash) flash_=0;


		//bitmap_hndl2();
		//bitmap_hndl();

		//data++;
		//for(iiii=0;iiii<1024;iiii++)	ssd1306_data(lcd_bitmap[iiii]);
		//ssd1306_command(SSD1306_DISPLAYOFF);
	/*	ssd1306_command(SSD1306_DISPLAYALLON );
		ssd1306_command(SSD1306_DISPLAYON);
		ssd1306_command(SSD1306_INVERTDISPLAY);*/
		//i2c_Start();
		//delay_us(10);
		//i2c_SendByte(0x78);
		//i2c_ReadAcknowledge();
		//i2c_Stop();

		
		}
	if(f1Hz)
		{
		f1Hz=0;
		if(level_U_mode==flash||level_I_mode==flash||level_Q_mode==flash) flash_=10;
		
		if(main_cnt<1000)main_cnt++;
//snmp_trap_send("Main power alarm. Power source is ACB",1,1);	 
		}
	}// end while
	
}
