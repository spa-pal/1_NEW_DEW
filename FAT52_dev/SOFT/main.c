                  
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "gran.h" 
#include "main.h" 
#include "uart0.h"
#include "full_can.h"
#include "power_cnt.h"

//-----------------------------------------------
//Таймер
char b1000Hz,b100Hz,b50Hz,b10Hz,b5Hz,b2Hz,b1Hz,b33Hz;
short t0cnt,t0cnt0,t0cnt1,t0cnt2,t0cnt3,t0cnt4,t0cnt5,t0cnt6,t0_cnt7,t0_cnt8;
char bFL5,bFL2,bFL,bFL_;



//-----------------------------------------------
//АЦП
int adc_buff[6][64],adc_buff_[6];
char adc_cnt,adc_cnt1,adc_ch;

//-----------------------------------------------
//Состояние сети
short Hz_cnt,fnet,Hz_out;
char bFF,bFF_;
signed short Unet;
char unet_drv_cnt;
signed short unet_store;


//-----------------------------------------------
//Состояние системы
short main_cnt;
char bRESET;
char reset_cnt;
//-----------------------------------------------
//Связь
enum_link_stat link_stat=lsOFF;
signed short link_cnt=0;

//-----------------------------------------------
//Датчик температуры
signed short T=47;

//-----------------------------------------------
//Состояние нагрузки
signed short iload,Uload;

//-----------------------------------------------
//Управление реле
enum_rele_stat rele_stat[2]={rsOFF,rsOFF};

//-----------------------------------------------
//Управление вентилятором
signed char pos_vent_,pos_vent=17;
signed char pos_vent_cnt;

//-----------------------------------------------
//Время
unsigned short hour_cnt_5hz,hour_cnt_1hz;
char cnt_ind;

//-----------------------------------------------
//Напряжения вводов
signed short Uvv[3],U[3];

//-----------------------------------------------
//Управление вводами
signed short vvod;
signed short vvod_cnt_to1=0,vvod_cnt_to2=0;

//-----------------------------------------------
//Работа со щетчиком
signed long power_summary=0;
signed short power_current=0;
char power_cnt_adrl=0x0e,power_cnt_adrh=0x09;

//-----------------------------------------------
//Работа со щетчиком 102m
char tot_pow_buff[10];
char tot_pow_buff_ptr,tot_pow_buff_cnt;
char tot_pow_buff_ready;
char curr_pow_buff[10];
char curr_pow_buff_ptr,curr_pow_buff_cnt;
char curr_pow_buff_ready;
		static char ppp;

//-----------------------------------------------
//Отладка
unsigned short rotor_can[6];
unsigned short cnt_sec;
char plazma_suzun;
char rele_temp;
char uart_plazma[5];
char tr_buff[10];


volatile unsigned long SysTickCnt;

char tttttt;
char tx_stat_off_cnt;
char plazma_ppp;

//-----------------------------------------------
void Delay (unsigned long tick) 
{       
unsigned long systickcnt;

systickcnt = SysTickCnt;
while ((SysTickCnt - systickcnt) < tick);
}

//-----------------------------------------------
void matemath(void)
{
unsigned long tempUL; 
if(link_stat==lsON)
     {
     U[0]=Uvv[0];
     U[1]=Uvv[1];
     U[2]=Uvv[2];

     }
else
     {
     signed long temp_SL;
     temp_SL=(signed long)adc_buff_[2];
     temp_SL*=126L;
     temp_SL/=1000;
     U[0]=(short)temp_SL;
     temp_SL=(signed long)adc_buff_[1];
     temp_SL*=122L;
     temp_SL/=1000;
     U[1]=(short)temp_SL;
     temp_SL=(signed long)adc_buff_[0];
     temp_SL*=122L;
     temp_SL/=1000;
     U[2]=(short)temp_SL;
     }

//power_current=uart_plazma[0];

tempUL=(unsigned long)adc_buff_[4];
tempUL*=1022UL;
tempUL/=10000UL;
tempUL-=273UL;
T=(short)tempUL;
//T=adc_buff_[4];

if(tot_pow_buff_ready)
	{
	char i;
	signed long temp_SL_;

	temp_SL_=0;
	i=tot_pow_buff_cnt/*-1*/;

	i--;
	temp_SL_+=(1L*(signed long)(tot_pow_buff[i]-0x30));
	
	i--;
	temp_SL_+=(10L*(signed long)(tot_pow_buff[i]-0x30));
	
	i--;
	
	i--;
	temp_SL_+=(100L*(signed long)(tot_pow_buff[i]-0x30));
	
	if(i)
		{
		i--;
		temp_SL_+=(1000L*(signed long)(tot_pow_buff[i]-0x30));
		if(i)
			{
			i--;
			temp_SL_+=(10000L*(signed long)(tot_pow_buff[i]-0x30));
			if(i)
				{
				i--;
				temp_SL_+=(100000L*(signed long)(tot_pow_buff[i]-0x30));
				if(i)
					{
					i--;
					temp_SL_+=(1000000L*(signed long)(tot_pow_buff[i]-0x30));
					if(i)
						{
						i--;
						temp_SL_+=(10000000L*(signed long)(tot_pow_buff[i]-0x30));
						}						
					}
				}			
			}			
		}	

	power_summary=temp_SL_;
	tot_pow_buff_ready=0;
	}

if(curr_pow_buff_ready)
	{
	char i;
	signed long temp_SL_;

	temp_SL_=0;
	i=curr_pow_buff_cnt-3;

	i--;
	temp_SL_+=(1L*(signed long)(curr_pow_buff[i]-0x30));
	
	i--;
	temp_SL_+=(10L*(signed long)(curr_pow_buff[i]-0x30));
	
	i--;
	temp_SL_+=(100L*(signed long)(curr_pow_buff[i]-0x30));
	
	i--;
	
	i--;	 
	temp_SL_+=(1000L*(signed long)(curr_pow_buff[i]-0x30));
	
	if(i)
		{
		i--;
		temp_SL_+=(1000L*(signed long)(curr_pow_buff[i]-0x30));
		}
	power_current=(signed short)temp_SL_;
	curr_pow_buff_ready=0; 
	}
}

//-----------------------------------------------
void adc_drv(void)
{
int temp_S;
char i;

if(GET_REG(LPC_ADC->ADGDR,31,1))//ADDR_bit.DONE)
	{
     adc_buff[adc_ch][adc_cnt]=GET_REG(LPC_ADC->ADGDR,4,12);//ADDR_bit.VVDDA;
	//-adc_buff_[adc_ch]=adc_buff[adc_ch][adc_cnt];
     //if(adc_ch==2)adc_buff[adc_ch][adc_cnt]=23;
     if((adc_cnt&0x03)==0)
          {
          temp_S=0;
		for(i=0;i<64;i++)
			{
			temp_S+=(int)adc_buff[adc_ch][i];
			} 
          adc_buff_[adc_ch]=temp_S>>6;
		//adc_buff_[adc_ch]=adc_buff[adc_ch][0];
		//adc_buff_[adc_ch]=124;
          } 

     if(++adc_ch>=6) 
		{
		adc_ch=0;
		adc_cnt++;
		if(adc_cnt>=64)adc_cnt=0;
		} 
	}    

SET_REG(LPC_PINCON->PINSEL1,1,(23-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(24-16)*2,2);
SET_REG(LPC_PINCON->PINSEL0,2,(2)*2,2);

SET_REG(LPC_PINCON->PINMODE1,2,(23-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(24-16)*2,2);
SET_REG(LPC_PINCON->PINMODE0,2,(2)*2,2);

SET_REG(LPC_ADC->ADCR,1,21,1);
SET_REG(LPC_ADC->ADCR,0,16,1);
SET_REG(LPC_ADC->ADCR,24,2,8);

if(adc_ch==0)SET_REG(LPC_ADC->ADCR,1<<0,0,8);
else if(adc_ch==1)SET_REG(LPC_ADC->ADCR,1<<1,0,8);
else if(adc_ch==2)SET_REG(LPC_ADC->ADCR,1<<1,0,8);
else if(adc_ch==3)SET_REG(LPC_ADC->ADCR,1<<7,0,8);
else if(adc_ch==4)SET_REG(LPC_ADC->ADCR,1<<7,0,8);
else if(adc_ch==5)SET_REG(LPC_ADC->ADCR,1<<0,0,8);
//else SET_REG(LPC_ADC->ADCR,1<<2,0,8);

SET_REG(LPC_ADC->ADCR,1,24,3);

}



//таблица соответствия шим и увых для резистора 300R
///1600		0.5
///750		1.0		
///478		1.5
///340		2.0
///256		2.5
///200		3.0
///159		3.5
///129		4.0
///106		4.5
///87		5.0
///72		5.5
///60		6.0
///51		6.5
///44		7.0
///39		7.5
///34		8.0
///29		8.5
///25		9.0
///21		9.5
///16		10.0
///10		full

//таблица соответствия шим и увых для резистора 1к
//1000		2.19
//800		2.60		
//700		2.87
//600		3.20
//500		3.60
//400		4.15
//300		4.88
//200		5.91
//150		6.60
//100		7.49
//90			7.70
//80			7.92
//70			8.15
//60			8.43
//50			8.74
//40			9.15
//30			9.63
//10			full



//таблица соответствия шим и увых для платы с преобразователем при Uпит=48В
///160		10.0		//стоит
///204		12.0
///244		14.0
///322		16.0
///386		18.0
///458		20.0
///539		22.0
///632		24.0
////700		25.0
///734		26.0
////830		27.5
///840		28.0
///970		30.0
///1120		32.0
///1265		34.0
/////1400		35
///1470		36.0		
/////1670		37.5
///1720		38.0
///1780		40.0
///2000		42.0
////2223		42.5
///2290		44.0
////2355		45.0
///2390		46.0
///2470		47.3


//таблица соответствия шим и увых для платы с преобразователем при Uпит=48В и нагрузкой 280Ом
//21			3.0		//стоит
//59			6.5
//65			7.3
//87			9.5
//110		11.7
//120		12.5
//135		14.0
//154		15.5
//162		16.2
//190		18.5
//220		20.7
//230		21.5
//252		23.0
//275		24.5
//287		25.2
//327		27.5
//367		29.8
//385		30.5
//412		32.0
//450		33.5
//463		34.2
//524		36.5		
//600		38.7
//626		39.5
//686		41.0
//753		42.5
//790		43.2
//940		45.5
//1200		48.5
//1850		51.5
//2470		54.4



//-----------------------------------------------
void vent_drv(void)
{
signed short temp_SS;
#ifdef VENT_3WIRE

const signed short vent_pwm_const[20]={  
								1600,	//0.5
								750,		//1.0		
								478,		//1.5
								340,		//2.0
								256,		//2.5
								200,		//3.0
								159,		//3.5
								129,		//4.0
								104,		//4.5
								86,		//5.0
								70,		//5.5
								58,		//6.0
								49,		//6.5
								38,		//7.0
								30,		//7.5
								22,		//8.0
								17,		//8.5
								13,		//9.0
								10,		//9.5
								6,		//10.0
                                        };

/*const signed short vent_pwm_const[20]={  	1060,	//2
                                        	830, 	//2.5
                                        	660, 	//3
                                        	525, 	//3.5
                                        	425, 	//4
                                        	350,  	//4.5
                                        	290,		//5
                                        	240,  	//5.5
                                        	210,  	//6
                                        	162,		//6.5
									120,		//7
									100,		//7.5
									83,		//8
									58,		//8.5
									42,  	//9
									33,		//9.5
									25  		//10
                                        };*/
/*const signed short vent_pwm_const[12]={  0,   //0
                                        200, //125, //1
                                        160, //137, //2
                                        130, //149, //3
                                        100,  //161, //4
                                        75,  //173, //5
                                        53,  //185, //6
                                        35,  //197, //7
                                        15,  //209, //8
                                        10,  //221, //9
                                        7,  //233, //10
                                        5  //245  //11
                                        };*/



#endif
#ifdef VENT_2WIRE
/*const signed short vent_pwm_const[20]={  
								160,			//10.0		//стоит
								204,			//12.0
								244,			//14.0
								322,			//16.0
								386,			//18.0
								458,			//20.0
								539,			//22.0
								632,			//24.0
								734,			//26.0
								840,			//28.0
								970,			//30.0
								1120,		//32.0
								1265,		//34.0
								1470,		//36.0		
								1720,		//38.0
								1780,		//40.0
								2000,		//42.0
								2290,		//44.0
								2390,		//46.0
								2470,		//47.3
                                        }; */
const signed short vent_pwm_const[20]={  
								21,			//3.0		//стоит
								59,			//6.5
								87,			//9.5
								//110		11.7
								120,			//12.5
								//135		14.0
								154,			//15.5
								//162		16.2
								190,			//18.5
								//220		20.7
								230,			//21.5
								//252		23.0
								275,			//24.5
								//287		25.2
								327,			//27.5
								367,			//29.8
								385,			//30.5
								//412		32.0
								450, 		//33.5
								463, 		//34.2
								524, 		//36.5		
								//600		38.7
								626, 		//39.5
								//686		41.0
								753, 		//42.5
								//790		43.2
								940, 		//45.5
								1200, 		//48.5
								1850, 		//51.5
								2470 		//54.4
                                        }; 
#endif

gran_char(&pos_vent,1,20);

if(link_stat==lsON)
     {
     if(pos_vent_<pos_vent)pos_vent_++;
     if(pos_vent_>pos_vent)pos_vent_--;
     }
else
     {
	if(T>30)
		{
		pos_vent_cnt++;
		if(pos_vent_cnt>=30)
			{
			pos_vent_cnt=0;
			pos_vent_++;
			if(pos_vent_>=20)pos_vent_=20;
			}
		}
	else if(T<28)
		{
		pos_vent_cnt++;
		if(pos_vent_cnt>=30)
			{
			pos_vent_cnt=0;
			pos_vent_--;
			if(pos_vent_<=1)pos_vent_=1;
			}
		}
	else pos_vent_cnt=0;
     //pos_vent_=20;
     }

temp_SS=vent_pwm_const[pos_vent_-1];

#ifdef VENT_3WIRE
gran(&temp_SS,5,1600);
#endif
#ifdef VENT_2WIRE
gran(&temp_SS,10,2500);
#endif
LPC_PWM1->MR6=temp_SS;
LPC_PWM1->LER=(1<<6);

}

//-----------------------------------------------
void net_drv(void)
{
link_cnt++;
gran(&link_cnt,0,10);
if(link_cnt>=10) link_stat=lsOFF;
}



//-----------------------------------------------
void power_hndl(void)
{
if(link_stat==lsON)
     {
     if(vvod==1) vvod_cnt_to1=0;
     else vvod_cnt_to2=0;    
          
          
          {
          if((U[0]<190)&&(U[1]>190))
               {
               vvod_cnt_to2++;
               gran(&vvod_cnt_to2,0,20);
               if(vvod_cnt_to2>=20)
                    {
                    vvod=2;
                    }
               }
          else vvod_cnt_to2=0;
          }
     
          {
          
          if(U[0]>200)
               {
               vvod_cnt_to1++;
               gran(&vvod_cnt_to1,0,300);
               if(vvod_cnt_to1>=300)
                    {
                    vvod=1;
                    }
               }
          else vvod_cnt_to1=0;
          }
//     vvod=1;
     }
/*else
     {
     if(vvod==1)
          {
          vvod_cnt_to1=0;
          if((U[0]<160)&&(U[1]>160))
               {
               vvod_cnt_to2++;
               gran(&vvod_cnt_to2,0,20);
               if(vvod_cnt_to2>=20)
                    {
                    vvod=2;
                    }
               }
          }
     else
          {
          vvod_cnt_to2=0;
          if(U[0]>180)
               {
               vvod_cnt_to1++;
               gran(&vvod_cnt_to1,0,300);
               if(vvod_cnt_to1>=300)
                    {
                    vvod=1;
                    }
               }

          }
     vvod=2;
     }*/



}


//-----------------------------------------------
void rele_drv(void)
{
//SET_REG(LPC_GPIO1->FIODIR,1,28,1);
SET_REG(LPC_GPIO1->FIODIR,1,29,1);

/*if(rele_stat[0]==rsOFF)*///LPC_GPIO1->FIOPIN|=(1<<28);
//else LPC_GPIO1->FIOPIN&=~(1<<28);

if(rele_stat[1]==rsOFF) LPC_GPIO1->FIOPIN^=(1<<29);
else LPC_GPIO1->FIOPIN&=~(1<<29);
}

//-----------------------------------------------
void rele_hndl(void)
{
//if(rele_stat[0]!=rsON)rele_stat[0]=rsON;
//else rele_stat[0]=rsOFF;
//if(rele_stat[1]!=rsON)rele_stat[1]=rsON;
//else rele_stat[1]=rsOFF;

//if(plazma_can[0]&0x01)rele_stat[1]=rsON;
//else rele_stat[1]=rsOFF;
//rele_stat[0]=rsON;

//SET_REG(LPC_GPIO1->FIODIR,1,28,1);
//SET_REG(LPC_GPIO1->FIODIR,1,29,1);

//if(rele_stat[0]==rsOFF)LPC_GPIO1->FIOPIN^=(1<<28);
//else LPC_GPIO1->FIOPIN&=~(1<<28);

//if(rele_stat[1]==rsOFF)LPC_GPIO1->FIOPIN^=(1<<29);
//else LPC_GPIO1->FIOPIN&=~(1<<29);


if(vvod==1)rele_stat[1]=rsON;
else rele_stat[1]=rsOFF; 
}

//-----------------------------------------------
void watchdog_enable (void) 
{
LPC_WDT->WDTC=5000000;
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

//-----------------------------------------------
void rtc_init (void) 
{
LPC_RTC->CCR=0x11;
}
//-----------------------------------------------
void pwm_init(void)
{
SET_REG(LPC_PINCON->PINSEL3,2,(26-16)*2,2);
//SET_REG(LPC_PINCON->PINSEL7,3,(26-16)*2,2);
LPC_PWM1->PR=0;
LPC_PWM1->PCR=1<<14;
LPC_PWM1->MCR=2;
LPC_PWM1->MR0=2500;
//LPC_PWM1->MR2=800;
LPC_PWM1->MR6=125;
LPC_PWM1->LER=(1<<0)|(1<<6);
LPC_PWM1->TCR=2;
LPC_PWM1->TCR=9;
}


//***********************************************
//***********************************************
//***********************************************
//***********************************************
//***********************************************
void SysTick_Handler (void) 	 /* SysTick Interrupt Handler (1ms)    */
{
SysTickCnt++;

rele_drv();

if(++t0cnt4>=10)
{
t0cnt4=0;
b1000Hz=1;

if(tx_stat_off_cnt)
	{
	tx_stat_off_cnt--;
	if(!tx_stat_off_cnt)tx_stat=tsOFF;
	}

if(tx_wd_cnt)
	{
	tx_wd_cnt--;

	}


if(++t0cnt5>=20)
     {
     t0cnt5=0;
     b50Hz=1;
     }

if(++t0_cnt7>=25)
     {
     t0_cnt7=0;
     b33Hz=1;
     }

if(++t0cnt>=10)
     {
     t0cnt=0;
     b100Hz=1;

     Hz_cnt++;
     if(Hz_cnt>=500)
	     {	
	     Hz_cnt=0;
	     fnet=Hz_out;
	     Hz_out=0;
	     }

     if(++t0cnt0>=10)
	     {
	     t0cnt0=0;
	     b10Hz=1;
	     }

     if(t0cnt0==5)
	     {
	     }

     if(++t0cnt1>=20)
	     {
	     t0cnt1=0;
	     b5Hz=1;
		if(bFL5)bFL5=0;
		else bFL5=1;     
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


	     }
     }
}
}


//===============================================
//===============================================
//===============================================
//===============================================
int main (void) 	                        
{

SystemInit();
SysTick_Config(SystemFrequency/10000 - 1); /* Generate interrupt each 1 ms   */


SET_REG(LPC_PINCON->PINSEL1,0,(17-16)*2,2); //Вход PV у 485
LPC_GPIO0->FIODIR|=(1<<17);
LPC_GPIO0->FIOCLR|=(1<<17);



LPC_GPIO1->FIODIR  |= 1<<27;                
	;
//FIO1MASK = 0x00000000;	 
//LPC_GPIO0->FIODIR  |= 1<<10;
//LPC_GPIO0->FIOSET  |= 1<<10;

SET_REG(LPC_GPIO0->FIODIR,0,10,1); //вход частоты (временный, проводком)


LPC_GPIO4->FIODIR |= (1<<29);           /* LEDs on PORT2 defined as Output    */

rtc_init();
pwm_init();
//UARTInit(0, 9600);	/* baud rate setting */
UARTInit(1, 9600);	/* baud rate setting */
UARTInit(0, 9600);	/* baud rate setting */
can1_init(BITRATE62_5K6_25MHZ);
FullCAN_SetFilter(0,0x09e);
vent_drv();
vvod=1;

rele_hndl();
//uart_plazma[0]=123;
SET_REG(LPC_PINCON->PINSEL1,0,(17-16)*2,2);	//Вход PV у 485
LPC_GPIO0->FIODIR|=(1<<17);
LPC_GPIO0->FIOSET|=(1<<17);

SET_REG(LPC_PINCON->PINSEL1,0,(18-16)*2,2); //Вход PV у 485
LPC_GPIO0->FIODIR|=(1<<18);
LPC_GPIO0->FIOCLR|=(1<<18);
Delay (2000);
watchdog_enable();
while (1) 
	{
	/*LPC_GPIO0->FIODIR|=(1<<3);
	LPC_GPIO0->FIOPIN^=(1<<3);*/
	watchdog_reset();

     if(sleep_in) 
		{
          sleep_in=0;
          sleep_an();
          }
   	if(!tx_wd_cnt) 
		{
          SET_REG(LPC_PINCON->PINSEL1,0,(18-16)*2,2); //Вход PV у 485
          LPC_GPIO0->FIODIR|=(1<<18);
          LPC_GPIO0->FIOCLR|=(1<<18);
          
          //tx_stat=tsOFF;		
          }
	if(bRXIN0)
     	{
		bRXIN0=0;
		uart_in0();
		}
 	if(b100Hz)
		{
		b100Hz=0;
          
          //tttttt++;
          //SET_REG(LPC_GPIO1->FIODIR,1,29,1);

          /*if(tttttt&0x01)*///LPC_GPIO1->FIOPIN^=(1<<29);
          //else LPC_GPIO1->FIOPIN^=~(1<<29);

         	}
		
	if(b33Hz)
		{
		b33Hz=0;
          adc_drv();
		}
			 
	if(b10Hz)
		{
		b10Hz=0;
          power_hndl();
		if(!bRESET)
		  	{
			LPC_GPIO2->FIODIR|=(1<<0);
			LPC_GPIO2->FIOPIN^=(1<<0);
			}
 		}
			
	if(b5Hz)
		{
          
		b5Hz=0;
          rele_hndl();
          net_drv();
          matemath();
          //read_current_power();
		reset_cnt++;
		if(reset_cnt==255) reset_cnt=250;
		uart_out0 (1,1,2,3,4,5,6);
		

		}

	if(b2Hz)
		{

		b2Hz=0;
          //plazma_can[0]++
			{
			//LPC_GPIO0->FIODIR|=(1<<19);
			//LPC_GPIO0->FIOPIN|=(1<<19);
			Delay (100);
          	if(ppp==0)
               	{
               	read_summary_power();
               	ppp=1;
               	}
          	else if(ppp==1)
               	{
               	read_current_power();
               	ppp=2;
               	}
         		else if(ppp==3)
               	{
               	//read_summary_power_();
               	ppp=0;
               	}
      /*     	else if(ppp==3)
               	{
               	//read_current_power_();
               	ppp=0;
               	}

			Delay (1000);
			//LPC_GPIO0->FIOPIN&=~(1<<19);  */
			
			}
		
		}
										
	if(b1Hz)
		{
		static _1hz_cnt;
		b1Hz=0;
          vent_drv();
          tr_buff[0]=0x33;
          //uart_out_adr1(tr_buff,6);
          //read_summary_power();
		if(ppp==2/*++_1hz_cnt>3*/)
			{
			_1hz_cnt=0;
			rx_read_power_cnt_phase=0;  
			ppp=3;
			}
          }

	if (rx_read_power_cnt_phase==0)
		{
		char command_with_crc[20];

		command_with_crc[0]=0xaf;  // /
		command_with_crc[1]=0x3f;  // ?
		command_with_crc[2]=0x21;  // !
		command_with_crc[3]=0x8d;  // CR
		command_with_crc[4]=0x0a;  // LF

		uart_out_adr1(command_with_crc,5);

		rx_wr_index1=0;
		rx_read_power_cnt_phase=1;
		}
	if (rx_read_power_cnt_phase==2)
		{
		char command_with_crc[20];
	
		command_with_crc[0]=0x06;  //  
		command_with_crc[1]=0x30;  // 0
		command_with_crc[2]=0x35;  // 5
		command_with_crc[3]=0xb1;  // 1
		command_with_crc[4]=0x8d;  // CR
		command_with_crc[5]=0x0a;  // LF
	
		uart_out_adr1(command_with_crc,6);
	
		rx_wr_index1=0;
		rx_read_power_cnt_phase=3;
		}  

/*	if (rx_read_power_cnt_phase==2)
		{
				char command_with_crc[20];

				command_with_crc[0]=0x06;  //  
				command_with_crc[1]=0x30;  // 0
				command_with_crc[2]=0x35;  // 5
				command_with_crc[3]=0xb1;  // 1
				command_with_crc[4]=0x8d;  // CR
				command_with_crc[5]=0x0a;  // LF

				uart_out_adr1(command_with_crc,6);

				rx_wr_index1=0;
				rx_read_power_cnt_phase=3;
		} */
	if (rx_read_power_cnt_phase==5)
		{
				char command_with_crc[20];

				command_with_crc[0]=0x81;  //  
				command_with_crc[1]=0xD2;  // R
				command_with_crc[2]=0xb1;  // 1
				command_with_crc[3]=0x82;  // 
				command_with_crc[4]=0xC5;  // E 
				command_with_crc[5]=0xD4;  // T
				command_with_crc[6]=0x30;  // 0
				command_with_crc[7]=0x50;  // P
				command_with_crc[8]=0xC5;  // E 
				command_with_crc[9]=0x28;  // (
				command_with_crc[10]=0xA9;  // )
				command_with_crc[11]=0x03;  // 
				command_with_crc[12]=0xb7;  // bcc


				uart_out_adr1(command_with_crc,13);

				rx_wr_index1=0;
				rx_read_power_cnt_phase=6;
		}

	if (rx_read_power_cnt_phase==10)
		{
				char command_with_crc[20];

		command_with_crc[0]=0x81;  //  
		command_with_crc[1]=0xD2;  // R
		command_with_crc[2]=0xb1;  // 1
		command_with_crc[3]=0x82;  // 
		command_with_crc[4]=0x50;  // P 
		command_with_crc[5]=0xCF;  // O
		command_with_crc[6]=0xd7;  // W
		command_with_crc[7]=0xc5;  // E
		command_with_crc[8]=0x50;  // P 
		command_with_crc[9]=0x28;  // (
		command_with_crc[10]=0xA9;  // )
		command_with_crc[11]=0x03;  // 
		command_with_crc[12]=0xe4;  // bcc
	
		uart_out_adr1(command_with_crc,13);

				rx_wr_index1=0;
				rx_read_power_cnt_phase=11;
		}

	if (rx_read_power_cnt_phase==14)
		{
		char command_with_crc[20];

		command_with_crc[0]=0x81;  //  
		command_with_crc[1]=0x42;  // B
		command_with_crc[2]=0x30;  // 0
		command_with_crc[3]=0x03;  // 
		command_with_crc[4]=0xf5;  // u 
	
		uart_out_adr1(command_with_crc,5);

				rx_wr_index1=0;
				rx_read_power_cnt_phase=20;

		ppp=3;
		}
	}
}

