//#define _24_

#define BLOCK_INIT  GPIOB->DDR|=(1<<2);GPIOB->CR1|=(1<<2);GPIOB->CR2&=~(1<<2);
#define BLOCK_ON 	GPIOB->ODR|=(1<<2);
#define BLOCK_OFF 	GPIOB->ODR&=~(1<<2);
#define BLOCK_IS_ON (GPIOB->ODR&(1<<2))

#include "string.h"
//#include <iostm8s208.h>
#include <iostm8s103.h>
#include "stm8s.h"
//#include "main.h"
short t0_cnt0=0;
char t0_cnt1=0,t0_cnt2=0,t0_cnt3=0,t0_cnt4=0;
_Bool b100Hz, b10Hz, b5Hz, b2Hz, b1Hz;

u8 mess[14];

@near signed short adc_buff[10][16],adc_buff_[10];
char adc_ch,adc_cnt;
signed short adc_plazma_short,adc_plazma[5];
char led_ind_cnt;
char led_ind=5;
char adr_drv_stat=0;
@near char adr[3],adress;
@near char adress_error;



#define BPS_MESS_STID	0x018e
#define BPS_MESS_STID_MASK	0x03ff
#define UKU_MESS_STID	0x009e
#define UKU_MESS_STID_MASK	0x03ff

#define XMAX 		25

#define CMND		0x16
#define MEM_KF 	0x62 
#define MEM_KF1 	0x26
#define MEM_KF4 	0x29
#define MEM_KF2 	0x27
#define ALRM_RES 	0x63
#define GETID 		0x90
#define PUTID 		0x91
#define PUTTM1 	0xDA
#define PUTTM2 	0xDB
#define PUTTM 		0xDE
#define GETTM 		0xED 
#define KLBR 		0xEE

#define ON 0x55
#define OFF 0xaa

//КАН
char can_out_buff[4][16];
char can_buff_wr_ptr;
char can_buff_rd_ptr;
char bTX_FREE=1;
char tx_busy_cnt;
char bCAN_RX=0;
char can_error_cnt;

signed short I,Un,Ui,Udb;
signed char T;
@eeprom signed short ee_K[4][2];


signed short umax_cnt,umin_cnt;
char link,link_cnt;

char flags=0; // байт аварийных и др. флагов
// 0 -  anee iaao a?aiia? oi 0, anee iao oi 1
// 1 -  авария по Tmax (1-авария);
// 2 -  авария по Tsign (1-авария);
// 3 -  авария по Umax (1-авария);
// 4 -  авария по Umin (1-авария);
// 5 -  внешняя блокровка (1-заблокировано); 
// 6 -  внешняя блокировка срабатывания аварий (1-заблокировано);

//Телеуправление
char flags_tu; // oi?aaey?uaa neiai io oinoa
// 0 -  aeiee?iaea, anee 1 oi caaeiee?iaaou 
// 1 -  aeiee?iaea ecaia caueo(1-aeoeai.); 
signed short _x_,_x__; 
int _x_cnt;
@eeprom signed _x_ee_;
unsigned short vol_u_temp;
unsigned short vol_i_temp;
char flags_tu_cnt_on,flags_tu_cnt_off;

//Работа источника

char off_bp_cnt;
signed short main_cnt, main_cnt1;

@eeprom signed short ee_TZAS;
@eeprom signed short ee_Umax;
@eeprom signed short ee_dU;
@eeprom signed short ee_tmax;
@eeprom signed short ee_tsign;
@eeprom signed short ee_U_AVT;

signed short tsign_cnt,tmax_cnt; 

signed short pwm_u=200,pwm_i=50;
enum {jp0,jp1,jp2,jp3} jp_mode;
char cnt_JP0,cnt_JP1;
_Bool bBL;
_Bool bBL_IPS=0;
char apv_cnt[3];
int apv_cnt_;
_Bool bAPV;
char cnt_apv_off;

//Управление пересбросом
@eeprom char res_fl,res_fl_;
char bRES=0;
char bRES_=0; 
char res_fl_cnt;

//Управление светодиодами
long led_red=0x00000000L;
long led_green=0x03030303L;
char led_drv_cnt=30;
long led_red_buff;
long led_green_buff;

//Отладка
signed short rotor_int=123;
signed short plazma_int[3];


_Bool bMAIN;
char cnt_net_drv;

@eeprom int UU_AVT;
signed short volum_u_main_=700;
signed short x[6];
signed short i_main[6];
char i_main_flag[6];
signed short i_main_avg;
char i_main_num_of_bps;
signed short i_main_sigma;
char i_main_bps_cnt[6];

@eeprom int ee_AVT_MODE;			//какой-то переключатель, переключается последним байтом в посылке с MEM_KF
@eeprom signed short ee_DEVICE;	//переключатель, переключается MEM_KF4 или MEM_KF1, MEM_KF4 устанавливает его в 1
							// и означает что это БПС неибэпный, включается и выключается только по команде,
							//никакие TZAS, U_AVT не работают 


char pwm_vent_cnt;
char pwm_stat;

//short vent_pos;
short vent_pwm;
enum {bpsIBEP,bpsIPS} bps_class;
@eeprom short ee_IMAXVENT;

//-----------------------------------------------
void gran(signed short *adr, signed short min, signed short max)
{
if (*adr<min) *adr=min;
if (*adr>max) *adr=max; 
} 

//-----------------------------------------------
void granee(@eeprom signed short *adr, signed short min, signed short max)
{
if (*adr<min) *adr=min;
if (*adr>max) *adr=max; 
}

//-----------------------------------------------
long delay_ms(short in)
{
long i,ii,iii;

i=((long)in)*100UL;

for(ii=0;ii<i;ii++)
	{
		iii++;
	}

}

//-----------------------------------------------
void led_hndl(void)
{
if(adress_error)
	{
	led_red=0x55555555L;
	led_green=0x55555555L;
	}

/*else if(bps_class==bpsIBEP)		//проверка работы адресатора
	{
	if(adress==0)led_red=0x00000001L;
	if(adress==1)led_red=0x00000005L;
	if(adress==2)led_red=0x00000015L;
	if(adress==3)led_red=0x00000055L;
	if(adress==4)led_red=0x00000155L;
	if(adress==5)led_red=0x00111111L;
	if(adress==6)led_red=0x01111111L;
	if(adress==7)led_red=0x11111111L;
	led_green=0x00000000L;	
	}*/

else if(bps_class==bpsIBEP)	//если блок ИБЭПный
	{
	if(jp_mode!=jp3)
		{
		if(main_cnt1<(5*ee_TZAS))
			{
			led_red=0x00000000L;
			led_green=0x03030303L;
			}

		else if((link==ON)&&(flags_tu&0b10000000))
			{
			led_red=0x00055555L;
			led_green=0xffffffffL;
			} 

		else if(((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(100+(5*ee_TZAS)))) && (ee_AVT_MODE!=0x55)&& (!ee_DEVICE))
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;	
			}  
		
		else  if(link==OFF)
			{
			led_red=0x55555555L;
			led_green=0xffffffffL;
			}
				    
		else if((link==ON)&&((flags&0b00111110)==0))
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;
			}
			
		else if((flags&0b00111110)==0b00000100)
			{
			led_red=0x00010001L;
			led_green=0xffffffffL;	
			}
		else if(flags&0b00000010)
			{
			led_red=0x00010001L;
			led_green=0x00000000L;	
			} 
		else if(flags&0b00001000)
			{
			led_red=0x00090009L;
			led_green=0x00000000L;	
			}
		else if(flags&0b00010000)
			{
			led_red=0x00490049L;
			led_green=0x00000000L;	
			}			
	
		else if((link==ON)&&(flags&0b00100000))
			{
			led_red=0x00000000L;
			led_green=0x00030003L;
			} 
	
		if((jp_mode==jp1))
			{
			led_red=0x00000000L;
			led_green=0x33333333L;
			}
		else if((jp_mode==jp2))
			{
			led_red=0xccccccccL;
			led_green=0x00000000L;
			}
		}		
	else if(jp_mode==jp3)
		{
		if(main_cnt1<(5*ee_TZAS))
			{
			led_red=0x00000000L;
			led_green=0x03030303L;
			}
		else if((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(70+(5*ee_TZAS))))
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;	
			} 
			
		else if((flags&0b00011110)==0)
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;
			}
	    
	
		else if((flags&0b00111110)==0b00000100)
			{
			led_red=0x00010001L;
			led_green=0xffffffffL;	
			}
		else if(flags&0b00000010)
			{
			led_red=0x00010001L;
			led_green=0x00000000L;	
			} 
		else if(flags&0b00001000)
			{
			led_red=0x00090009L;
			led_green=0x00000000L;	
			}
		else if(flags&0b00010000)
			{
			led_red=0x00490049L;
			led_green=0xffffffffL;	
			}  
		}
	}
else if(bps_class==bpsIPS)	//если блок ИПСный
	{
	if(jp_mode!=jp3)
		{
		if(main_cnt1<(5*ee_TZAS))
			{
			led_red=0x00000000L;
			led_green=0x03030303L;
			}

		else if((link==ON)&&(flags_tu&0b10000000))
			{
			led_red=0x00055555L;
			led_green=0xffffffffL;
			} 

		else if(((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(100+(5*ee_TZAS)))) && (ee_AVT_MODE!=0x55)&& (!ee_DEVICE))
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;	
			}  
		
		else  if(link==OFF)
			{
			if((flags&0b00011110)==0)
				{
				led_red=0x00000000L;
				if(bMAIN)led_green=0xfffffff5L;
				else led_green=0xffffffffL;
				}
	    	
			else if((flags&0b00111110)==0b00000100)
				{
				led_red=0x00010001L;
				if(bMAIN)led_green=0xfffffff5L;
				else led_green=0xffffffffL;	
				}
			else if(flags&0b00000010)
				{
				led_red=0x00010001L;
				if(bMAIN)led_green=0x00000005L;
				else led_green=0x00000000L;
				} 
			else if(flags&0b00001000)
				{
				led_red=0x00090009L;
				if(bMAIN)led_green=0x00000005L;
				else led_green=0x00000000L;	
				}
			else if(flags&0b00010000)
				{
				led_red=0x00490049L;
				if(bMAIN)led_green=0x00000005L;
				else led_green=0x00000000L;	
				}  
			else
				{
				led_red=0x55555555L;
				led_green=0xffffffffL;
				}


/*			if(bMAIN)
				{
				led_red=0x0L;
				led_green=0xfffffff5L;
				}
			else
				{
				led_red=0x55555555L;
				led_green=0xffffffffL;
				}*/
			}
				    
		else if((link==ON)&&((flags&0b00111110)==0))
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;
			}
			
		else if((flags&0b00111110)==0b00000100)
			{
			led_red=0x00010001L;
			led_green=0xffffffffL;	
			}
		else if(flags&0b00000010)
			{
			led_red=0x00010001L;
			led_green=0x00000000L;	
			} 
		else if(flags&0b00001000)
			{
			led_red=0x00090009L;
			led_green=0x00000000L;	
			}
		else if(flags&0b00010000)
			{
			led_red=0x00490049L;
			led_green=0x00000000L;	
			}			
	
		else if((link==ON)&&(flags&0b00100000))
			{
			led_red=0x00000000L;
			led_green=0x00030003L;
			} 
	
		if((jp_mode==jp1))
			{
			led_red=0x00000000L;
			led_green=0x33333333L;
			}
		else if((jp_mode==jp2))
			{
			//if(ee_DEVICE)led_red=0xccccccacL;
			//else led_red=0xcc0cccacL;			
			led_red=0xccccccccL;
			led_green=0x00000000L;
			}
		}		
	else if(jp_mode==jp3)
		{
		if(main_cnt1<(5*ee_TZAS))
			{
			led_red=0x00000000L;
			led_green=0x03030303L;
			}
		else if((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(70+(5*ee_TZAS))))
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;	
			} 
			
		else if((flags&0b00011110)==0)
			{
			led_red=0x00000000L;
			led_green=0xffffffffL;
			}
	    
	
		else if((flags&0b00111110)==0b00000100)
			{
			led_red=0x00010001L;
			led_green=0xffffffffL;	
			}
		else if(flags&0b00000010)
			{
			led_red=0x00010001L;
			led_green=0x00000000L;	
			} 
		else if(flags&0b00001000)
			{
			led_red=0x00090009L;
			led_green=0x00000000L;	
			}
		else if(flags&0b00010000)
			{
			led_red=0x00490049L;
			led_green=0xffffffffL;	
			}  
		}
	}
}

//-----------------------------------------------
void led_drv(void)
{
//Красный светодиод
GPIOA->DDR|=(1<<4);
GPIOA->CR1|=(1<<4);
GPIOA->CR2&=~(1<<4);
if(led_red_buff&0b1L) GPIOA->ODR|=(1<<4); 	//Горит если в led_red_buff 1 и на ножке 1
else GPIOA->ODR&=~(1<<4); 

//Зеленый светодиод
GPIOA->DDR|=(1<<5);
GPIOA->CR1|=(1<<5);
GPIOA->CR2&=~(1<<5);	
if(led_green_buff&0b1L) GPIOA->ODR|=(1<<5);	//Горит если в led_green_buff 1 и на ножке 1
else GPIOA->ODR&=~(1<<5);


led_red_buff>>=1;
led_green_buff>>=1;
if(++led_drv_cnt>32)
	{
	led_drv_cnt=0;
	led_red_buff=led_red;
	led_green_buff=led_green;
	}

//?
//GPIOB->ODR|=(1<<4);
//GPIOB->ODR|=(1<<5);
} 

//-----------------------------------------------
void JP_drv(void)
{

GPIOD->DDR&=~(1<<6);
GPIOD->CR1|=(1<<6);
GPIOD->CR2&=~(1<<6);

GPIOD->DDR&=~(1<<7);
GPIOD->CR1|=(1<<7);
GPIOD->CR2&=~(1<<7);

if(GPIOD->IDR&(1<<6))
	{
	if(cnt_JP0<10)
		{
		cnt_JP0++;
		}			     
	}
else if(!(GPIOD->IDR&(1<<6)))
	{
	if(cnt_JP0)
		{
		cnt_JP0--;
		}	
	}
	 
if(GPIOD->IDR&(1<<7))
	{
	if(cnt_JP1<10)
		{
		cnt_JP1++;
		}			     
	}
else if(!(GPIOD->IDR&(1<<7)))
	{
	if(cnt_JP1)
		{
		cnt_JP1--;
		}	
	}	


if((cnt_JP0==10)&&(cnt_JP1==10))
	{
	jp_mode=jp0;
	}
if((cnt_JP0==0)&&(cnt_JP1==10))
	{
	jp_mode=jp1;
	}
if((cnt_JP0==10)&&(cnt_JP1==0))
	{
	jp_mode=jp2;
	}		 
if((cnt_JP0==0)&&(cnt_JP1==0))
	{
	jp_mode=jp3;
	}	
		
}

//-----------------------------------------------
void link_drv(void)		//10Hz
{
if(jp_mode!=jp3)
	{
	if(link_cnt<52)link_cnt++;
	if(link_cnt==49)flags&=0xc1;		//если оборвалась связь первым делом сбрасываем все аварии и внешнюю блокировку
	if(link_cnt==50)
		{
		link=OFF;
		
		//попробую вместо
		//if((AVT_MODE!=0x55)&&(!eeDEVICE))bMAIN=1;
		//написать
		if(bps_class==bpsIPS)bMAIN=1;	//если БПС определен как ИПСный - пытаться стать главным;
		else bMAIN=0;

		cnt_net_drv=0;
    		if(!res_fl_)
			{
	    		bRES_=1;
	    		res_fl_=1;
	    		}
    		}            
	}
else link=OFF;	
} 

//-----------------------------------------------
//Вентилятор
void vent_drv(void)
{

	
	short vent_pwm_i_necc=400;
	short vent_pwm_t_necc=400;
	short vent_pwm_max_necc=400;
	signed long tempSL;

	//I=1200;

	tempSL=36000L/(signed long)ee_Umax;
	tempSL=(signed long)I/tempSL;
	
	if(ee_DEVICE==1) tempSL=(signed long)(I/ee_IMAXVENT);
	
	if(tempSL>10)vent_pwm_i_necc=1000;
	else if(tempSL<1)vent_pwm_i_necc=400;
	else vent_pwm_i_necc=(short)(400L + (tempSL*60L));
	gran(&vent_pwm_i_necc,400,1000);
	//vent_pwm_i_necc=400;
	tempSL=(signed long)T;
	if(tempSL<=(ee_tsign-30L))vent_pwm_t_necc=400;
	else if(tempSL>=ee_tsign)vent_pwm_t_necc=1000;
	else vent_pwm_t_necc=(short)(400L+(20L*(tempSL-(((signed long)ee_tsign)-30L))));
	gran(&vent_pwm_t_necc,400,1000);
	
	vent_pwm_max_necc=vent_pwm_i_necc;
	if(vent_pwm_t_necc>vent_pwm_i_necc)vent_pwm_max_necc=vent_pwm_t_necc;
	
	if(vent_pwm<vent_pwm_max_necc)vent_pwm+=10;
	if(vent_pwm>vent_pwm_max_necc)vent_pwm-=10;
	gran(&vent_pwm,400,1000);
	//vent_pwm=100;
}

//-----------------------------------------------
//Воздействие на силу
//5Hz
void pwr_drv(void)
{
/*GPIOB->DDR|=(1<<2);
GPIOB->CR1|=(1<<2);
GPIOB->CR2&=~(1<<2);*/
BLOCK_INIT

if(main_cnt1<1500)main_cnt1++;

if((main_cnt1<(5*ee_TZAS))&&(bps_class!=bpsIPS))
	{
	BLOCK_ON
	//GPIOB->ODR|=(1<<2);
	}
else if(bps_class==bpsIPS)
		{
//GPIOB->ODR|=(1<<2);
		if(bBL_IPS)
			{
			 BLOCK_ON
			//GPIOB->ODR|=(1<<2);
			}
		else if(!bBL_IPS)
			{
			  BLOCK_OFF
			//GPIOB->ODR&=~(1<<2);
			}
		}
else if(((main_cnt1>(5*ee_TZAS))&&(main_cnt1<(70+(5*ee_TZAS)))))
	{
	if(bps_class==bpsIPS)
		{
		  BLOCK_OFF
		//GPIOB->ODR&=~(1<<2);
		}
	else if(bps_class==bpsIBEP)
		{
		if(ee_DEVICE)
			{
			if(flags&0b00100000)BLOCK_ON //GPIOB->ODR|=(1<<2);
			else	BLOCK_OFF //GPIOB->ODR&=~(1<<2);
			}
		else
			{
			BLOCK_OFF
			//GPIOB->ODR&=~(1<<2);
			}
		}
	}    	
else if(bBL)
	{
	BLOCK_ON
	//GPIOB->ODR|=(1<<2);
	}
else if(!bBL)
	{
	BLOCK_OFF
	//GPIOB->ODR&=~(1<<2);
	}

gran(&pwm_u,2,1020);

//pwm_u=1000;
//pwm_i=1000;

//GPIOB->ODR|=(1<<3);

//pwm_u=300;
//vent_pwm=600;

TIM1->CCR2H= (char)(pwm_u/256);	
TIM1->CCR2L= (char)pwm_u;

TIM1->CCR1H= (char)(pwm_i/256);	
TIM1->CCR1L= (char)pwm_i;

TIM1->CCR3H= (char)(vent_pwm/256);	
TIM1->CCR3L= (char)vent_pwm;
}

//-----------------------------------------------
//Вычисление воздействий на силу
//10Hz
void pwr_hndl(void)				
{
if(jp_mode==jp3)
	{
	if((flags&0b00001010)==0)
		{
		pwm_u=500;
		//pwm_i=0x3ff;
		bBL=0;
		}
	else if(flags&0b00001010)
		{
		pwm_u=0;
		//pwm_i=0;
		bBL=1;
		}	
	
	}  
else if(jp_mode==jp2)
	{
	pwm_u=0;
	pwm_i=0x3ff;
	bBL=0;
	}     
else if(jp_mode==jp1)
	{
	pwm_u=0x3ff;
	pwm_i=0x3ff;
	bBL=0;
	} 

else if((bMAIN)&&(link==ON)/*&&(ee_AVT_MODE!=0x55)*/)
	{
	pwm_u=volum_u_main_;
	pwm_i=0x3ff;
	bBL_IPS=0;
	}

else if(link==OFF)
	{
/*	if(ee_Device==0x55)
		{
		pwm_u=0x3ff;
		pwm_i=0x3ff;
		bBL=0;
		}
	else*/
 	if(ee_DEVICE)
		{
		pwm_u=0x00;
		pwm_i=0x00;
		bBL=1;
		}
	else 
		{
		if((flags&0b00011010)==0)
			{
			pwm_u=ee_U_AVT;
			gran(&pwm_u,0,1020);
		    	pwm_i=0x3ff;
			bBL=0;
			bBL_IPS=0;
			}
		else if(flags&0b00011010)
			{
			pwm_u=0;
			pwm_i=0;
			bBL=1;
			bBL_IPS=1;
			}
		}
//pwm_u=950;
//		pwm_i=950;
	}
	
		

else	if(link==ON)				//если есть связь
	{
	if((flags&0b00100000)==0)	//если нет блокировки извне
		{
		if(((flags&0b00011010)==0)||(flags&0b01000000)) 	//если нет аварий или если они заблокированы
			{
			pwm_u=vol_u_temp+_x_;					//управление от укушки + выравнивание токов
		    	pwm_i=vol_i_temp;
			bBL=0;
			}
		else if(flags&0b00011010)					//если есть аварии
			{
			pwm_u=0;								//то полный стоп
			pwm_i=0;
			bBL=1;
			}
		}
	else if(flags&0b00100000)	//если заблокирован извне то полное выключение
		{
		pwm_u=0;
	    	pwm_i=0;
		bBL=1;
		}
/*pwm_u=950;
		pwm_i=950;*/ 		
	}	   
//pwm_u=vol_u_temp;		
}

//-----------------------------------------------
void matemat(void)
{
signed long temp_SL;

#ifdef _220_
temp_SL=adc_buff_[0];
temp_SL-=ee_K[0][0];
if(temp_SL<0) temp_SL=0;
temp_SL*=ee_K[0][1];
temp_SL/=2400;
I=(signed short)temp_SL;
#else

#ifdef _24_
temp_SL=adc_buff_[4];
temp_SL-=ee_K[0][0];
if(temp_SL<0) temp_SL=0;
temp_SL*=ee_K[0][1];
temp_SL/=600;
I=(signed short)temp_SL;
//I=ee_K[0][0];
#else
temp_SL=adc_buff_[4];
temp_SL-=ee_K[0][0];
if(temp_SL<0) temp_SL=0;
temp_SL*=ee_K[0][1];
temp_SL/=600;
I=(signed short)temp_SL;
#endif 
#endif
//I=adc_buff_[4];

temp_SL=(signed long)adc_buff_[1];
//temp_SL-=ee_K[1,0];
if(temp_SL<0) temp_SL=0;
temp_SL*=(signed long)ee_K[2][1];
temp_SL/=1800L;
Ui=(unsigned short)temp_SL;
//Ui=adc_buff_[1];
//Ui=1000;
//Ui=adc_plazma_short;
//Ui=ee_K[2][1];;


temp_SL=adc_buff_[3];
//temp_SL-=ee_K[2][0];
if(temp_SL<0) temp_SL=0;
temp_SL*=ee_K[1][1];
temp_SL/=1800;
Un=(unsigned short)temp_SL;
//Un=adc_buff_[4];

temp_SL=adc_buff_[2];
temp_SL*=ee_K[3][1];
temp_SL/=1000;
T=(signed short)(temp_SL-273L);
if(T<-30)T=-30;
if(T>120)T=120;
//T=-3;
Udb=flags;

//Ui=adc_plazma[0];
//I=adc_plazma[1];
//T=adc_plazma[2];

}

//-----------------------------------------------
void temper_drv(void)		//1 Hz
{

if(T>ee_tsign) tsign_cnt++;
else if (T<(ee_tsign-1)) tsign_cnt--;

gran(&tsign_cnt,0,60);

if(tsign_cnt>=55)
	{
	if(((jp_mode==jp0)&&!(flags&0b01000000))||(jp_mode==jp3))	flags|=0b00000100; //поднять бит подогрева 
	}
else if (tsign_cnt<=5) flags&=0b11111011;	//Сбросить бит подогрева



	
if(T>ee_tmax) tmax_cnt++;
else if (T<(ee_tmax-1)) tmax_cnt--;

gran(&tmax_cnt,0,60);

if(tmax_cnt>=55)
	{
	if(((jp_mode==jp0)&&!(flags&0b01000000))||(jp_mode==jp3))	flags|=0b00000010;
	}
else if (tmax_cnt<=5) flags&=0b11111101;


} 

//-----------------------------------------------
void u_drv(void)		//1Hz
{ 
if(jp_mode!=jp3)
	{        
	if(Ui>ee_Umax)umax_cnt++;
	else umax_cnt=0;
	gran(&umax_cnt,0,10);
	if(umax_cnt>=10)flags|=0b00001000; 	//Поднять аварию по превышению напряжения

	
	if((Ui<Un)&&((Un-Ui)>ee_dU)&&(!BLOCK_IS_ON/*(GPIOB->ODR&(1<<2))*/))umin_cnt++;	
	else umin_cnt=0;
	gran(&umin_cnt,0,10);	
	if(umin_cnt>=10)flags|=0b00010000;	  
	}
else if(jp_mode==jp3)
	{        
	if(Ui>700)umax_cnt++;
	else umax_cnt=0;
	gran(&umax_cnt,0,10);
	if(umax_cnt>=10)flags|=0b00001000;

	
	if((Ui<200)&&(!BLOCK_IS_ON/*(GPIOB->ODR&(1<<2))*/))umin_cnt++;	
	else umin_cnt=0;
	gran(&umin_cnt,0,10);	
	if(umin_cnt>=10)flags|=0b00010000;	  
	}
}

//-----------------------------------------------
void x_drv(void)
{
if(_x__==_x_)
	{
	if(_x_cnt<60)
		{
		_x_cnt++;
		if(_x_cnt>=60)
			{
			if(_x_ee_!=_x_)_x_ee_=_x_;
			}
		}
		
	}
else _x_cnt=0;

if(_x_cnt>60) _x_cnt=0;	

_x__=_x_;
}

//-----------------------------------------------
void apv_start(void)
{
if((apv_cnt[0]==0)&&(apv_cnt[1]==0)&&(apv_cnt[2]==0)&&!bAPV)
	{
	apv_cnt[0]=60;
	apv_cnt[1]=60;
	apv_cnt[2]=60;
	apv_cnt_=3600;
	bAPV=1;	
	}
}

//-----------------------------------------------
void apv_stop(void)
{
apv_cnt[0]=0;
apv_cnt[1]=0;
apv_cnt[2]=0;
apv_cnt_=0;	
bAPV=0;
}


//-----------------------------------------------
void apv_hndl(void)
{
if(apv_cnt[0])
	{
	apv_cnt[0]--;
	if(apv_cnt[0]==0)
		{
		flags&=0b11100001;
		tsign_cnt=0;
		tmax_cnt=0;
		umax_cnt=0;
		umin_cnt=0;
		//cnt_adc_ch_2_delta=0;
		led_drv_cnt=30;
		}
	}
else if(apv_cnt[1])
	{
	apv_cnt[1]--;
	if(apv_cnt[1]==0)
		{
		flags&=0b11100001;
		tsign_cnt=0;
		tmax_cnt=0;
		umax_cnt=0;
		umin_cnt=0;
//		cnt_adc_ch_2_delta=0;		
		led_drv_cnt=30;
		}
	}	       
else if(apv_cnt[2])
	{
	apv_cnt[2]--;
	if(apv_cnt[2]==0)
		{
		flags&=0b11100001;
		tsign_cnt=0;
		tmax_cnt=0;
		umax_cnt=0;
		umin_cnt=0;          
//		cnt_adc_ch_2_delta=0;		
		led_drv_cnt=30;
		}
	}	         
	
if(apv_cnt_)
	{
	apv_cnt_--;
	if(apv_cnt_==0) 
		{
		bAPV=0;
		apv_start();
		}
	}	   
	
if((umin_cnt==0)&&(umax_cnt==0)/*&&(cnt_adc_ch_2_delta==0)*/&&(!BLOCK_IS_ON/*(GPIOB->ODR&(1<<2))*/))
	{
	if(cnt_apv_off<20)
		{
		cnt_apv_off++;
		if(cnt_apv_off>=20)
			{
			apv_stop();
			}
		}
	}
else cnt_apv_off=0;	
	
}

//-----------------------------------------------
void flags_drv(void)
{
static char flags_old;
if(jp_mode!=jp3) 
	{
	if(((flags&(1<<3)/*0b00001000*/)&&(!(flags_old&(1<<3)/*0b00001000*/)))||((flags&(1<<4)/*0b00010000*/)&&(!(flags_old&(1<<4)/*0b00010000*/)))) 
    		{	
    		if(link==OFF)apv_start();
    		}
     }
else if(jp_mode==jp3) 
	{
	if((flags&(1<<3)/*0b00001000*/)&&(!(flags_old&(1<<3)/*0b00001000*/))) 
    		{	
    		apv_start();
    		}
     }
flags_old=flags;

} 

/* -------------------------------------------------------------------------- */
/*void adr_drv(void)
{
//#define ADR_CONST_0	445
//#define ADR_CONST_1	696
//#define ADR_CONST_2	537
//#define ADR_CONST_3	1015

GPIOB->DDR&=~(1<<0);
GPIOB->CR1&=~(1<<0);
GPIOB->CR2&=~(1<<0);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+0;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=1;
while(adr_drv_stat==1);

GPIOB->DDR&=~(1<<1);
GPIOB->CR1&=~(1<<1);
GPIOB->CR2&=~(1<<1);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+1;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=3;
while(adr_drv_stat==3);

GPIOE->DDR&=~(1<<6);
GPIOE->CR1&=~(1<<6);
GPIOE->CR2&=~(1<<6);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+9;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=5;
while(adr_drv_stat==5);



if((adc_buff_[0]>=(ADR_CONST_0-20))&&(adc_buff_[0]<=(ADR_CONST_0+20))) adr[0]=0;
else if((adc_buff_[0]>=(ADR_CONST_1-20))&&(adc_buff_[0]<=(ADR_CONST_1+20))) adr[0]=1;
else if((adc_buff_[0]>=(ADR_CONST_2-20))&&(adc_buff_[0]<=(ADR_CONST_2+20))) adr[0]=2;
else if((adc_buff_[0]>=(ADR_CONST_3-20))&&(adc_buff_[0]<=(ADR_CONST_3+20))) adr[0]=3;
else adr[0]=5;

if((adc_buff_[1]>=(ADR_CONST_0-20))&&(adc_buff_[1]<=(ADR_CONST_0+20))) adr[1]=0;
else if((adc_buff_[1]>=(ADR_CONST_1-20))&&(adc_buff_[1]<=(ADR_CONST_1+20))) adr[1]=1;
else if((adc_buff_[1]>=(ADR_CONST_2-20))&&(adc_buff_[1]<=(ADR_CONST_2+20))) adr[1]=2;
else if((adc_buff_[1]>=(ADR_CONST_3-20))&&(adc_buff_[1]<=(ADR_CONST_3+20))) adr[1]=3;
else adr[1]=5;

if((adc_buff_[9]>=(ADR_CONST_0-20))&&(adc_buff_[9]<=(ADR_CONST_0+20))) adr[2]=0;
else if((adc_buff_[9]>=(ADR_CONST_1-20))&&(adc_buff_[9]<=(ADR_CONST_1+20))) adr[2]=1;
else if((adc_buff_[9]>=(ADR_CONST_2-20))&&(adc_buff_[9]<=(ADR_CONST_2+20))) adr[2]=2;
else if((adc_buff_[9]>=(ADR_CONST_3-20))&&(adc_buff_[9]<=(ADR_CONST_3+20))) adr[2]=3;
else adr[2]=5;

if((adr[0]==5)||(adr[0]==5)||(adr[0]==5))adress=100;
else adress = adr[0] + (adr[1]*4) + (adr[2]*16);

//adress=1;
}*/

/* -------------------------------------------------------------------------- */
/*void adr_drv_v2(void)
{
#define ADR_CONST_0	635
#define ADR_CONST_1	995
#define ADR_CONST_2	767
#define ADR_CONST_3	1015

GPIOB->DDR&=~(1<<0);
GPIOB->CR1&=~(1<<0);
GPIOB->CR2&=~(1<<0);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+0;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=1;
while(adr_drv_stat==1);

GPIOB->DDR&=~(1<<1);
GPIOB->CR1&=~(1<<1);
GPIOB->CR2&=~(1<<1);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+1;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=3;
while(adr_drv_stat==3);

GPIOE->DDR&=~(1<<6);
GPIOE->CR1&=~(1<<6);
GPIOE->CR2&=~(1<<6);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+9;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=5;
while(adr_drv_stat==5);



if((adc_buff_[0]>=(ADR_CONST_0-20))&&(adc_buff_[0]<=(ADR_CONST_0+20))) adr[0]=0;
else if((adc_buff_[0]>=(ADR_CONST_1-20))&&(adc_buff_[0]<=(ADR_CONST_1+20))) adr[0]=1;
else if((adc_buff_[0]>=(ADR_CONST_2-20))&&(adc_buff_[0]<=(ADR_CONST_2+20))) adr[0]=2;
else if((adc_buff_[0]>=(ADR_CONST_3-20))&&(adc_buff_[0]<=(ADR_CONST_3+20))) adr[0]=3;
else adr[0]=5;

if((adc_buff_[1]>=(ADR_CONST_0-20))&&(adc_buff_[1]<=(ADR_CONST_0+20))) adr[1]=0;
else if((adc_buff_[1]>=(ADR_CONST_1-20))&&(adc_buff_[1]<=(ADR_CONST_1+20))) adr[1]=1;
else if((adc_buff_[1]>=(ADR_CONST_2-20))&&(adc_buff_[1]<=(ADR_CONST_2+20))) adr[1]=2;
else if((adc_buff_[1]>=(ADR_CONST_3-20))&&(adc_buff_[1]<=(ADR_CONST_3+20))) adr[1]=3;
else adr[1]=5;

if((adc_buff_[9]>=(ADR_CONST_0-20))&&(adc_buff_[9]<=(ADR_CONST_0+20))) adr[2]=0;
else if((adc_buff_[9]>=(ADR_CONST_1-20))&&(adc_buff_[9]<=(ADR_CONST_1+20))) adr[2]=1;
else if((adc_buff_[9]>=(ADR_CONST_2-20))&&(adc_buff_[9]<=(ADR_CONST_2+20))) adr[2]=2;
else if((adc_buff_[9]>=(ADR_CONST_3-20))&&(adc_buff_[9]<=(ADR_CONST_3+20))) adr[2]=3;
else adr[2]=5;

if((adr[0]==5)||(adr[0]==5)||(adr[0]==5))adress=100;
else adress = adr[0] + (adr[1]*4) + (adr[2]*16);

//adress=1;
}*/

/* -------------------------------------------------------------------------- */
void adr_drv_v4(char in)
{
if(adress!=in)adress=in;
}

/* -------------------------------------------------------------------------- */
void adr_drv_v3(void)
{
#define ADR_CONST_0	574
#define ADR_CONST_1	897
#define ADR_CONST_2	695
#define ADR_CONST_3	1015

GPIOB->DDR&=~(1<<0);
GPIOB->CR1&=~(1<<0);
GPIOB->CR2&=~(1<<0);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+0;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=1;
while(adr_drv_stat==1);

GPIOB->DDR&=~(1<<1);
GPIOB->CR1&=~(1<<1);
GPIOB->CR2&=~(1<<1);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+1;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=3;
while(adr_drv_stat==3);

GPIOE->DDR&=~(1<<6);
GPIOE->CR1&=~(1<<6);
GPIOE->CR2&=~(1<<6);
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+9;
ADC2->CR1|=1;
ADC2->CR1|=1;
adr_drv_stat=5;
while(adr_drv_stat==5);



if((adc_buff_[0]>=(ADR_CONST_0-20))&&(adc_buff_[0]<=(ADR_CONST_0+20))) adr[0]=0;
else if((adc_buff_[0]>=(ADR_CONST_1-20))&&(adc_buff_[0]<=(ADR_CONST_1+20))) adr[0]=1;
else if((adc_buff_[0]>=(ADR_CONST_2-20))&&(adc_buff_[0]<=(ADR_CONST_2+20))) adr[0]=2;
else if((adc_buff_[0]>=(ADR_CONST_3-20))&&(adc_buff_[0]<=(ADR_CONST_3+20))) adr[0]=3;
else adr[0]=5;

if((adc_buff_[1]>=(ADR_CONST_0-20))&&(adc_buff_[1]<=(ADR_CONST_0+20))) adr[1]=0;
else if((adc_buff_[1]>=(ADR_CONST_1-20))&&(adc_buff_[1]<=(ADR_CONST_1+20))) adr[1]=1;
else if((adc_buff_[1]>=(ADR_CONST_2-20))&&(adc_buff_[1]<=(ADR_CONST_2+20))) adr[1]=2;
else if((adc_buff_[1]>=(ADR_CONST_3-20))&&(adc_buff_[1]<=(ADR_CONST_3+20))) adr[1]=3;
else adr[1]=5;

if((adc_buff_[9]>=(ADR_CONST_0-20))&&(adc_buff_[9]<=(ADR_CONST_0+20))) adr[2]=0;
else if((adc_buff_[9]>=(ADR_CONST_1-20))&&(adc_buff_[9]<=(ADR_CONST_1+20))) adr[2]=1;
else if((adc_buff_[9]>=(ADR_CONST_2-20))&&(adc_buff_[9]<=(ADR_CONST_2+20))) adr[2]=2;
else if((adc_buff_[9]>=(ADR_CONST_3-20))&&(adc_buff_[9]<=(ADR_CONST_3+20))) adr[2]=3;
else adr[2]=5;

//adr[0]=5;

if((adr[0]==5)||(adr[1]==5)||(adr[2]==5))
	{
	//adress=100;
	adress_error=1;
	}
else 
	{
	if(adr[2]&0x02) bps_class=bpsIPS;
	else bps_class=bpsIBEP;

	adress = adr[0] + (adr[1]*4) + ((adr[2]&0x01)*16);
	}

//adress=1;
}

/* -------------------------------------------------------------------------- */
void volum_u_main_drv(void)
{
char i;

if(bMAIN)
	{
	if(Un<(UU_AVT-10))volum_u_main_+=5;
	else if(Un<(UU_AVT-1))volum_u_main_++;
	else if(Un>(UU_AVT+10))volum_u_main_-=10;
	else if(Un>(UU_AVT+1))volum_u_main_--;
	if(volum_u_main_>1020)volum_u_main_=1020;
	if(volum_u_main_<0)volum_u_main_=0;
	//volum_u_main_=700;
	
	i_main_sigma=0;
	i_main_num_of_bps=0;
	for(i=0;i<6;i++)
		{
		if(i_main_flag[i])
			{
			i_main_sigma+=i_main[i];
			i_main_flag[i]=1;
			i_main_num_of_bps++;
			}
		else
			{
			i_main_flag[i]=0;	
			}
		}
	i_main_avg=i_main_sigma/i_main_num_of_bps;
	for(i=0;i<6;i++)
		{
		if(i_main_flag[i])
			{
			if(i_main[i]<(i_main_avg-10))x[i]++;
			else if(i_main[i]>(i_main_avg+10))x[i]--;
			if(x[i]>100)x[i]=100;
			if(x[i]<-100)x[i]=-100;
			//if()
			}
			
		}
	//plazma_int[2]=x[1];
	}
}

/* -------------------------------------------------------------------------- */
void init_CAN(void) {
	CAN->MCR&=~CAN_MCR_SLEEP;					// CAN wake up request
	CAN->MCR|= CAN_MCR_INRQ;					// CAN initialization request
	while((CAN->MSR & CAN_MSR_INAK) == 0);	// waiting for CAN enter the init mode
	
	CAN->MCR|= CAN_MCR_NART;					// no automatic retransmition
	
	CAN->PSR= 2;							// *** FILTER 0 SETTINGS ***
	


//#ifdef ID_SCALE_8					// accepted range of IDs on filter 0
//	CAN->Page.Filter01.F0R1= MY_MESS_STID>>3;			// 8 bits mode
//	CAN->Page.Filter01.F0R2= MY_MESS_STID_MASK>>3;
//#endif
//#ifdef ID_SCALE_16
	CAN->Page.Filter01.F0R1= UKU_MESS_STID>>3;			// 16 bits mode
	CAN->Page.Filter01.F0R2= UKU_MESS_STID<<5;
	CAN->Page.Filter01.F0R5= UKU_MESS_STID_MASK>>3;
	CAN->Page.Filter01.F0R6= UKU_MESS_STID_MASK<<5;
	
	CAN->Page.Filter01.F1R1= BPS_MESS_STID>>3;			// 16 bits mode
	CAN->Page.Filter01.F1R2= BPS_MESS_STID<<5;
	CAN->Page.Filter01.F1R5= BPS_MESS_STID_MASK>>3;
	CAN->Page.Filter01.F1R6= BPS_MESS_STID_MASK<<5;
	
//#endif

	CAN->PSR= 6;									// set page 6
//#ifdef ID_LIST_MODE
//	CAN->Page.Config.FMR1|= 3;								//list mode
//#endif
//#ifdef ID_MASK_MODE
	CAN->Page.Config.FMR1&=~3;								//mask mode
//#endif
//#ifdef ID_SCALE_8
//	CAN->Page.Config.FCR1&= ~(CAN_FCR1_FSC00 | CAN_FCR1_FSC01);			//8 bit scale 
//#endif
//#ifdef ID_SCALE_16
	CAN->Page.Config.FCR1= ((3<<1) & (CAN_FCR1_FSC00 | CAN_FCR1_FSC01));		//16 bit scale
	CAN->Page.Config.FCR1= ((3<<5) & (CAN_FCR1_FSC10 | CAN_FCR1_FSC11));		//16 bit scale
//#endif

	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
	CAN->Page.Config.FCR1|= CAN_FCR1_FACT1;
	
	
	CAN->PSR= 6;								// *** BIT TIMING SETTINGS ***
	
	CAN->Page.Config.BTR1= 9;					// CAN_BTR1_BRP=9, 	tq= fcpu/(9+1)
	CAN->Page.Config.BTR2= (1<<7)|(6<<4) | 7; 		// BS2=8, BS1=7, 		
	
	CAN->IER|=(1<<1);
	
	
	CAN->MCR&=~CAN_MCR_INRQ;					// leave initialization request
	while((CAN->MSR & CAN_MSR_INAK) != 0);	// waiting for CAN leave the init mode
}

//-----------------------------------------------
void can_transmit(unsigned short id_st,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7)
{

if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>3))can_buff_wr_ptr=0;

can_out_buff[can_buff_wr_ptr][0]=(char)(id_st>>6);
can_out_buff[can_buff_wr_ptr][1]=(char)(id_st<<2);

can_out_buff[can_buff_wr_ptr][2]=data0;
can_out_buff[can_buff_wr_ptr][3]=data1;
can_out_buff[can_buff_wr_ptr][4]=data2;
can_out_buff[can_buff_wr_ptr][5]=data3;
can_out_buff[can_buff_wr_ptr][6]=data4;
can_out_buff[can_buff_wr_ptr][7]=data5;
can_out_buff[can_buff_wr_ptr][8]=data6;
can_out_buff[can_buff_wr_ptr][9]=data7;

can_buff_wr_ptr++;
if(can_buff_wr_ptr>3)can_buff_wr_ptr=0;
} 

//-----------------------------------------------
void can_tx_hndl(void)
{
if(bTX_FREE)
	{
	if(can_buff_rd_ptr!=can_buff_wr_ptr)
		{
		bTX_FREE=0;

		CAN->PSR= 0;
		CAN->Page.TxMailbox.MDLCR=8;
		CAN->Page.TxMailbox.MIDR1=can_out_buff[can_buff_rd_ptr][0];
		CAN->Page.TxMailbox.MIDR2=can_out_buff[can_buff_rd_ptr][1];

		memcpy(&CAN->Page.TxMailbox.MDAR1, &can_out_buff[can_buff_rd_ptr][2],8);

		can_buff_rd_ptr++;
		if(can_buff_rd_ptr>3)can_buff_rd_ptr=0;

		CAN->Page.TxMailbox.MCSR|= CAN_MCSR_TXRQ;
		CAN->IER|=(1<<0);
		}
	}
else 
	{
	tx_busy_cnt++;
	if(tx_busy_cnt>=100)
		{
		tx_busy_cnt=0;
		bTX_FREE=1;
		}
	}
}

//-----------------------------------------------
void net_drv(void)
{ 
//char temp_;    
if(bMAIN)
	{
	if(++cnt_net_drv>=7) cnt_net_drv=0; 
	
	if(cnt_net_drv<=5) 
		{ 
		can_transmit(0x09e,cnt_net_drv,cnt_net_drv,GETTM,0,(char)(volum_u_main_+x[cnt_net_drv]),(char)((volum_u_main_+x[cnt_net_drv])/256),1000,1000);
		i_main_bps_cnt[cnt_net_drv]++;
		if(i_main_bps_cnt[cnt_net_drv]>10)i_main_flag[cnt_net_drv]=0;
		}
	else if(cnt_net_drv==6)
		{
		plazma_int[2]=pwm_u;
		can_transmit(0x18e,adress,PUTTM1,*(((char*)&I)+1),*((char*)&I),*(((char*)&Un)+1),*((char*)&Un),*(((char*)&Ui)+1),*((char*)&Ui));
		can_transmit(0x18e,adress,PUTTM2,T,0,flags,_x_,*(((char*)&plazma_int[2])+1),*((char*)&plazma_int[2]));
		}
	}
}

//-----------------------------------------------
void can_in_an(void)
{
char temp,i;
signed temp_S;
int tempI;



//if((mess[0]==1)&&(mess[1]==2)&&(mess[2]==3)&&(mess[3]==4)&&(mess[4]==5)&&(mess[5]==6)&&(mess[6]==7)&&(mess[7]==8))can_transmit1(1,2,3,4,5,6,7//,8);


if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==GETTM))	
	{ 
	
	can_error_cnt=0;
	
	bMAIN=0;
 	flags_tu=mess[9];
 	if(flags_tu&0b00000001)
 		{
 		//if(flags_tu_cnt_off<4)
 			//{
 			//flags_tu_cnt_off++;
 			/*if(flags_tu_cnt_off>=4)*/flags|=0b00100000;
 			//}
 		//else flags_tu_cnt_off=4;
 		}
 	else  		
 		{
 		//if(flags_tu_cnt_off)
 			//{
 			//flags_tu_cnt_off--;
 			//if(flags_tu_cnt_off<=0)
 				{
 				flags&=0b11011111; 
 				off_bp_cnt=5*ee_TZAS;
 				}
 			//}
 		//else flags_tu_cnt_off=0;
 		}
 		 
 	if(flags_tu&0b00000010) flags|=0b01000000;
 	else flags&=0b10111111; 
 		
 	vol_u_temp=mess[10]+mess[11]*256;
 	vol_i_temp=mess[12]+mess[13]*256;  
 	
 	//I=1234;
    //	Un=6543;
 	//Ui=6789;
 	//T=246;
 	//flags=0x55;
 	//_x_=33;
 	//rotor_int=1000;
	plazma_int[2]=T;
 	rotor_int=flags_tu+(((short)flags)<<8);
	can_transmit(0x18e,adress,PUTTM1,*(((char*)&I)+1),*((char*)&I),*(((char*)&Un)+1),*((char*)&Un),*(((char*)&Ui)+1),*((char*)&Ui));
	can_transmit(0x18e,adress,PUTTM2,T,0,flags,_x_,*(((char*)&plazma_int[2])+1),*((char*)&plazma_int[2]));
     link_cnt=0;
     link=ON;
     
     if(flags_tu&0b10000000)
     	{
     	if(!res_fl)
     		{             
     		res_fl=1;
     		bRES=1;
     		res_fl_cnt=0;
     		}
     	}
     else 
     	{
     	if(main_cnt>20)
     		{
    			if(res_fl)
     			{
     			res_fl=0;
     			}
     		}
     	}	
     	
      if(res_fl_)
      	{
      	res_fl_=0;
      	}     	
	}
else if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==KLBR)&&(mess[9]==mess[10]))
	{
	rotor_int++;
	if((mess[9]&0xf0)==0x20)
		{
		if((mess[9]&0x0f)==0x01)
			{
			ee_K[0][0]=adc_buff_[4];
			}
		else if((mess[9]&0x0f)==0x02)
			{
			ee_K[0][1]++;
			} 
		else if((mess[9]&0x0f)==0x03)
			{
			ee_K[0][1]+=10;
			}	 
		else if((mess[9]&0x0f)==0x04)
			{
			ee_K[0][1]--;
			} 
		else if((mess[9]&0x0f)==0x05)
			{
			ee_K[0][1]-=10;
			}
		granee(&ee_K[0][1],50,3000);									
		}
	else if((mess[9]&0xf0)==0x10)
		{
		if((mess[9]&0x0f)==0x01)
			{
			ee_K[1][0]=adc_buff_[1];
			}
		else if((mess[9]&0x0f)==0x02)
			{
			ee_K[1][1]++;
			} 
		else if((mess[9]&0x0f)==0x03)
			{
			ee_K[1][1]+=10;
			}	 
		else if((mess[9]&0x0f)==0x04)
			{
			ee_K[1][1]--;
			} 
		else if((mess[9]&0x0f)==0x05)
			{
			ee_K[1][1]-=10;
			}
	//	#ifdef _220_
	//	granee(&ee_K[1][1],4500,5500);
	//	#else
		granee(&ee_K[1][1],10,30000);
	//	#endif									
		}		
		 
	else if((mess[9]&0xf0)==0x00)
		{
		if((mess[9]&0x0f)==0x01)
			{
			ee_K[2][0]=adc_buff_[2];
			}
		else if((mess[9]&0x0f)==0x02)
			{
			ee_K[2][1]++;
			} 
		else if((mess[9]&0x0f)==0x03)
			{
			ee_K[2][1]+=10;
			}	 
		else if((mess[9]&0x0f)==0x04)
			{
			ee_K[2][1]--;
			} 
		else if((mess[9]&0x0f)==0x05)
			{
			ee_K[2][1]-=10;
			}
		//#ifdef _220_
		//granee(&ee_K[2][1],400,5500);
		//#else
		granee(&ee_K[2][1],10,30000);
		//#endif									
		}		 
		
	else if((mess[9]&0xf0)==0x30)
		{
		if((mess[9]&0x0f)==0x02)
			{
			ee_K[3][1]++;
			} 
		else if((mess[9]&0x0f)==0x03)
			{
			ee_K[3][1]+=10;
			}	 
		else if((mess[9]&0x0f)==0x04)
			{
			ee_K[3][1]--;
			} 
		else if((mess[9]&0x0f)==0x05)
			{
			ee_K[3][1]-=10;
			}
		granee(&ee_K[3][1],300,517);									
		}     
		
	link_cnt=0;
     link=ON;
     if(res_fl_)
      	{
      	res_fl_=0;
      	}       	
	
	
	} 

else if((mess[6]==0xff)&&(mess[7]==0xff)&&(mess[8]==MEM_KF))
	{
	signed short tempSS;
	tempSS=mess[9]+(mess[10]*256);
	if(ee_Umax!=tempSS) ee_Umax=tempSS;
	tempSS=mess[11]+(mess[12]*256);
	if(ee_dU!=tempSS) ee_dU=tempSS;
	if((mess[13]&0x0f)==0x5)
		{
		if(ee_AVT_MODE!=0x55)ee_AVT_MODE=0x55;
		}
	else if(ee_AVT_MODE==0x55)ee_AVT_MODE=0;	
	}

else if((mess[6]==0xff)&&(mess[7]==0xff)&&((mess[8]==MEM_KF1)||(mess[8]==MEM_KF4)))
	{
	signed short tempSS;
	tempSS=mess[9]+(mess[10]*256);
	if(ee_tmax!=tempSS) ee_tmax=tempSS;
	tempSS=mess[11]+(mess[12]*256);
	if(ee_tsign!=tempSS) ee_tsign=tempSS;
	
	
	if(mess[8]==MEM_KF1)
		{
		if(ee_DEVICE!=0)ee_DEVICE=0;
		if(ee_TZAS!=(signed short)mess[13]) ee_TZAS=(signed short)mess[13];
		}
	if(mess[8]==MEM_KF4)	//MEM_KF4 передают УКУшки там, где нужно полное управление БПСами с УКУ, включить-выключить, короче не для ИБЭП
		{
		if(ee_DEVICE!=1)ee_DEVICE=1;
		if(ee_IMAXVENT!=(signed short)mess[13]) ee_IMAXVENT=(signed short)mess[13];
		}
	}

else if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==CMND)&&(mess[9]==ALRM_RES))
	{
	flags&=0b11100001;
	tsign_cnt=0;
	tmax_cnt=0;
	umax_cnt=0;
	umin_cnt=0;
	led_drv_cnt=30;
	}		
else if((mess[6]==0xff)&&(mess[7]==0xff)&&(mess[8]==CMND)&&(mess[9]==CMND))
	{
	if((mess[10]==0x55)&&(mess[11]==0x55)) _x_++;
	else if((mess[10]==0x66)&&(mess[11]==0x66)) _x_--; 
	else if((mess[10]==0x77)&&(mess[11]==0x77)) _x_=0;
     gran(&_x_,-XMAX,XMAX);
	}
else if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==CMND)&&(mess[9]==mess[10])&&(mess[9]==0xee))
	{
	rotor_int++;
     tempI=pwm_u;
	ee_U_AVT=tempI;
	UU_AVT=Un;
	delay_ms(100);
	if(ee_U_AVT==tempI)can_transmit(0x18e,adress,PUTID,0xdd,0xdd,0,0,0,0);
      
	}	


else if((mess[7]==PUTTM1)&&(mess[6]!=adress)&&(mess[6]>=0)&&(mess[6]<=5))
	{
	i_main_bps_cnt[mess[6]]=0;
	i_main_flag[mess[6]]=1;
	if(bMAIN)
		{
		i_main[mess[6]]=(signed short)mess[8]+(((signed short)mess[9])*256);
		i_main[adress]=I;
     	i_main_flag[adress]=1;
		}
	}

else if((mess[7]==PUTTM2)&&(mess[6]!=adress)&&(mess[6]>=0)&&(mess[6]<=5))
	{
	i_main_bps_cnt[mess[6]]=0;
	i_main_flag[mess[6]]=1;		
	if(bMAIN)
		{
		if(mess[9]==0)i_main_flag[i]=1;
		else i_main_flag[i]=0;
		i_main_flag[adress]=1;
		}
	}



can_in_an_end:
bCAN_RX=0;
}   

//-----------------------------------------------
void t4_init(void){
	TIM4->PSCR = 4;
	TIM4->ARR= 77;
	TIM4->IER|= TIM4_IER_UIE;					// enable break interrupt
	
	TIM4->CR1=(TIM4_CR1_URS | TIM4_CR1_CEN | TIM4_CR1_ARPE);	
	
}

//-----------------------------------------------
void t1_init(void)
{
TIM1->ARRH= 0x03;
TIM1->ARRL= 0xff;
TIM1->CCR1H= 0x00;	
TIM1->CCR1L= 0xff;
TIM1->CCR2H= 0x00;	
TIM1->CCR2L= 0x00;
TIM1->CCR3H= 0x00;	
TIM1->CCR3L= 0x64;

TIM1->CCMR1= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
TIM1->CCMR2= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
TIM1->CCMR3= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
TIM1->CCER1= TIM1_CCER1_CC1E | TIM1_CCER1_CC2E ; //OC1, OC2 output pins enabled
TIM1->CCER2= TIM1_CCER2_CC3E; //OC1, OC2 output pins enabled
TIM1->CR1=(TIM1_CR1_CEN | TIM1_CR1_ARPE);
TIM1->BKR|= TIM1_BKR_AOE;
}


//-----------------------------------------------
void adc2_init(void)
{
adc_plazma[0]++;

/*
GPIOB->DDR&=~(1<<0);
GPIOB->CR1&=~(1<<0);
GPIOB->CR2&=~(1<<0);

GPIOB->DDR&=~(1<<1);
GPIOB->CR1&=~(1<<1);
GPIOB->CR2&=~(1<<1);*/

/*GPIOB->DDR=0;
GPIOB->CR1=0;
GPIOB->CR2=0;

GPIOE->DDR&=~(1<<6);
GPIOE->CR1&=~(1<<6);
GPIOE->CR2&=~(1<<6);*/

//GPIOB->DDR&=~(1<<3);
//GPIOB->CR1&=~(1<<3);
//GPIOB->CR2&=~(1<<3);


GPIOB->DDR&=~(1<<4);
GPIOB->CR1&=~(1<<4);
GPIOB->CR2&=~(1<<4);

GPIOB->DDR&=~(1<<5);
GPIOB->CR1&=~(1<<5);
GPIOB->CR2&=~(1<<5);

GPIOB->DDR&=~(1<<6);
GPIOB->CR1&=~(1<<6);
GPIOB->CR2&=~(1<<6);

GPIOB->DDR&=~(1<<7);
GPIOB->CR1&=~(1<<7);
GPIOB->CR2&=~(1<<7);

/*
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+0;
ADC2->CR1|=1;
ADC2->CR1|=1;
*/

ADC2->TDRL=0xff;
	
ADC2->CR2=0x08;
ADC2->CR1=0x40;
//if(adc_ch)
	{
	ADC2->CSR=0x20+adc_ch+3;
	
	ADC2->CR1|=1;
	ADC2->CR1|=1;
	}

adc_plazma[1]=adc_ch;
}




//***********************************************
//***********************************************
//***********************************************
//***********************************************
@far @interrupt void TIM4_UPD_Interrupt (void) 
{
TIM4->SR1&=~TIM4_SR1_UIF;

if(++pwm_vent_cnt>=10)pwm_vent_cnt=0;
GPIOB->ODR|=(1<<3);
if(pwm_vent_cnt>=5)GPIOB->ODR&=~(1<<3);

//GPIOB->ODR|=(1<<3);


if(++t0_cnt0>=100)
	{
	t0_cnt0=0;
	b100Hz=1;

	if(++t0_cnt1>=10)
		{
		t0_cnt1=0;
		b10Hz=1;
		}
		
	if(++t0_cnt2>=20)
		{
		t0_cnt2=0;
		b5Hz=1;

		}
		
	if(++t0_cnt4>=50)
		{
		t0_cnt4=0;
		b2Hz=1;
		}
		
	if(++t0_cnt3>=100)
		{
		t0_cnt3=0;
		b1Hz=1;
		}
	}

			// disable break interrupt
//GPIOA->ODR&=~(1<<4);	
}

//***********************************************
@far @interrupt void CAN_RX_Interrupt (void) 
{
	
CAN->PSR= 7;									// page 7 - read messsage
//while (CAN->RFR & CAN_RFR_FMP01) {				// make up all received messages
memcpy(&mess[0], &CAN->Page.RxFIFO.MFMI, 14); // compare the message content
//				for(i=5; i<MY_MESS_DLC+5; ++i)
//					if(mess[i+1]!=MY_MESS[i]) { tout= 0; break;	};
//				if(tout)
//					set_Rx_LEDs();
//				CAN->RFR|= CAN_RFR_RFOM;				// release received message
//				while(CAN->RFR & CAN_RFR_RFOM);		// wait until the current message is released

//adress=30;
//if((mess[8]==0xeD)&&(mess[6]==adress)) GPIOA->ODR^=(1<<5);	

bCAN_RX=1;
CAN->RFR|=(1<<5);

}

//***********************************************
@far @interrupt void CAN_TX_Interrupt (void) 
{
if((CAN->TSR)&(1<<0))
	{
	bTX_FREE=1;	
	//GPIOA->ODR^=(1<<5);
	CAN->TSR|=(1<<0);
	}
}

//***********************************************
@far @interrupt void ADC2_EOC_Interrupt (void) {

signed long temp_adc;


adc_plazma[2]++;

/*		GPIOA->DDR|=(1<<1);
		GPIOA->CR1|=(1<<1);
		GPIOA->CR2&=~(1<<1);	
		GPIOA->ODR|=(1<<1);*/

ADC2->CSR&=~(1<<7);

temp_adc=(((signed long)(ADC2->DRH))*256)+((signed long)(ADC2->DRL));

//temp_adc=4000;
//temp_adc=720;

if(adr_drv_stat==1)
	{
	adr_drv_stat=2;
	adc_buff_[0]=temp_adc;
	}

else if(adr_drv_stat==3)
	{
	adr_drv_stat=4;
	adc_buff_[1]=temp_adc;
	}

else if(adr_drv_stat==5)
	{
	adr_drv_stat=6;
	adc_buff_[9]=temp_adc;
	}

adc_buff[adc_ch][adc_cnt]=temp_adc;

//adc_plazma=ADC1->DR;
//if(adc_ch==0)adc_plazma_short=temp_adc;


adc_ch++;
if(adc_ch>=5)
	{
//	adc_plazma++;
	adc_ch=0;
	adc_cnt++;
	if(adc_cnt>=16)
		{
		adc_cnt=0;
		}
	}

if((adc_cnt&0x03)==0)
	{
	signed long tempSS;
	char i;
	tempSS=0;
	for(i=0;i<16;i++)
		{
		tempSS+=(signed long)adc_buff[adc_ch][i];
		}
	adc_buff_[adc_ch]=(signed short)(tempSS>>4);
	//else adc_buff_[adc_ch]=(signed short)(tempSS>>4);
	}

//adc_buff_[adc_ch]=adc_ch*10;

//GPIOD->ODR&=~(1<<0);

//ADC1->CR1&=~(1<<0);

//adc_plazma_short=adc_buff_[1];
adc_plazma_short++;

/*
adcw[0]=(ADC1->DB0RL)+((ADC1->DB0RH)*256);
adcw[1]=(ADC1->DB1RL)+((ADC1->DB1RH)*256);
adcw[2]=(ADC1->DB2RL)+((ADC1->DB2RH)*256);*/




//GPIOD->ODR|=(1<<0);


	
		//GPIOA->ODR&=~(1<<1);
}


//===============================================
//===============================================
//===============================================
//===============================================

main()
{

CLK->ECKR|=1;
while((CLK->ECKR & 2) == 0);
CLK->SWCR|=2;
CLK->SWR=0xB4;

delay_ms(200);
FLASH_DUKR=0xae;
FLASH_DUKR=0x56;
enableInterrupts();


adr_drv_v3();
//adr_drv_v4(1);


t4_init();

		GPIOG->DDR|=(1<<0);
		GPIOG->CR1|=(1<<0);
		GPIOG->CR2&=~(1<<0);	
		//GPIOG->ODR^=(1<<0);

		GPIOG->DDR&=~(1<<1);
		GPIOG->CR1|=(1<<1);
		GPIOG->CR2&=~(1<<1);

init_CAN();
//adc2_init();

//CAN->DGR&=0xfc;

GPIOC->DDR|=(1<<1);
GPIOC->CR1|=(1<<1);
GPIOC->CR2|=(1<<1);

GPIOC->DDR|=(1<<2);
GPIOC->CR1|=(1<<2);
GPIOC->CR2|=(1<<2);

/*
GPIOB->DDR|=(1<<2);
GPIOB->CR1|=(1<<2);
GPIOB->CR2|=(1<<2);
*/
t1_init();

GPIOA->DDR|=(1<<5);
GPIOA->CR1|=(1<<5);
GPIOA->CR2&=~(1<<5);
/*
GPIOB->DDR|=(1<<2);
GPIOB->CR1|=(1<<2);
GPIOB->CR2&=~(1<<2);
*/
GPIOB->DDR|=(1<<3);
GPIOB->CR1|=(1<<3);
GPIOB->CR2|=(1<<3);

GPIOC->DDR|=(1<<3);
GPIOC->CR1|=(1<<3);
GPIOC->CR2|=(1<<3);

//if(bps_class==bpsIPS) volum_u_main_=ee_U_AVT;
if(bps_class==bpsIPS) 
	{
	pwm_u=ee_U_AVT;
	volum_u_main_=ee_U_AVT;
	}
while (1)
	{

	
	
	if(bCAN_RX)
		{
		bCAN_RX=0;
		can_in_an();	
		}
	if(b100Hz)
		{
		b100Hz=0;

		/*GPIOB->DDR|=(1<<5);
		GPIOB->CR1|=(1<<5);
		GPIOB->CR2&=~(1<<5);	
		GPIOB->ODR^=(1<<5);*/

		//GPIOC->ODR^=(1<<1);
		
		adc2_init();
		can_tx_hndl();
      	}  
      	
	if(b10Hz)
		{
		b10Hz=0;
		
          matemat();
	    	led_drv(); 
	     link_drv();
	     pwr_hndl();		//вычисление воздействий на силу
	     JP_drv();
	     flags_drv();
		net_drv();
      	}

	if(b5Hz)
		{
		b5Hz=0;
		
		pwr_drv();		//воздействие на силу
		led_hndl();
		
		vent_drv();
      	}
      	
	if(b2Hz)
		{
		b2Hz=0;
//led_ind=adc_buff_[0]/100;

//		GPIOA->ODR^=(1<<5);


		
		}
      	
	if(b1Hz)
		{
		b1Hz=0;

		temper_drv();			//вычисление аварий температуры
		u_drv();
          x_drv();
          if(main_cnt<1000)main_cnt++;
  		if((link==OFF)||(jp_mode==jp3))apv_hndl();
  		
		//Пересброс КАНа в случае зависания
  		can_error_cnt++;
  		if(can_error_cnt>=10)
  			{
  			can_error_cnt=0;
			init_CAN();
  			}
		//

		volum_u_main_drv();
		
		pwm_stat++;
		if(pwm_stat>=10)pwm_stat=0;
adc_plazma_short++;

		
		}

	}
}