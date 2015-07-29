#define ADRESS	11


#include "string.h"
//#include <iostm8s208.h>
#include <iostm8s103.h>
#include "stm8s.h"

char t0_cnt0=0,t0_cnt1=0,t0_cnt2=0,t0_cnt3=0,t0_cnt4=0;
_Bool b100Hz, b10Hz, b5Hz, b2Hz, b1Hz;

u8 mess[14];

@near signed short adc_buff[10][16],adc_buff_[10];
@near signed short unet_buff[3]={1100,2000,3000};
char adc_ch,adc_cnt;
signed short adc_plazma_short,adc_plazma;
char led_ind_cnt;
char led_ind=5;
char adr_drv_stat=0;
@near char adr[3];

#define BPS_MESS_STID	0x018e
#define BPS_MESS_STID_MASK	0x03ff
#define UKU_MESS_STID	0x009e
#define UKU_MESS_STID_MASK	0x03ff

#define XMAX 		25

#define CMND		0x16
#define MEM_KF 	0x62 
#define MEM_KF1 	0x26
#define MEM_KF2 	0x27
#define ALRM_RES 	0x63
#define GETID 		0x90
#define PUTID 		0x91
#define PUTTM1 	0xDA
#define PUTTM2 	0xDB
#define PUTTM 		0xDE
#define GETTM 		0xED 
#define KLBR 		0xEE
#define PUTTM_NET 	0xEA

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




char link,link_cnt;


//Работа источника
@eeprom char TZAS;
char off_bp_cnt;
signed short main_cnt, main_cnt1;
@eeprom signed short Umax,dU,tmax,tsign;
signed short tsign_cnt,tmax_cnt; 
@eeprom int U_AVT;
signed short pwm_u=50,pwm_i=50;
enum {jp0,jp1,jp2,jp3} jp_mode;
char cnt_JP0,cnt_JP1;
_Bool bBL;
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
long led_red=0x55555550L,led_green=0xaaaaaaaaL;
char led_drv_cnt=30;

   
   
   


char cnt_net_drv;

@eeprom int UU_AVT;
signed short volum_u_main[6],volum_u_main_=700;
signed short x[6];
signed short i_main[6];
char i_main_flag[6];
signed short i_main_avg;
char i_main_num_of_bps;
signed short i_main_sigma;
char i_main_bps_cnt[6];

@eeprom int AVT_MODE;

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
void link_drv(void)
{
if(jp_mode!=jp3)
	{
	if(link_cnt<52)link_cnt++;
	//if(link_cnt==49)flags&=0xc1;//0b11000001;
	if(link_cnt==50)
		{
		//link_cnt=50;
    		link=OFF;
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
void can_in_an(void)
{
char temp,i;
signed temp_S;
int tempI;



//if((mess[0]==1)&&(mess[1]==2)&&(mess[2]==3)&&(mess[3]==4)&&(mess[4]==5)&&(mess[5]==6)&&(mess[6]==7)&&(mess[7]==8))can_transmit1(1,2,3,4,5,6,7//,8);


if((mess[6]==ADRESS)&&(mess[7]==ADRESS)&&(mess[8]==GETTM))	
	{ 
	
	can_error_cnt=0;
	
	can_transmit(0x18e,ADRESS,PUTTM_NET,*(((char*)&unet_buff[0])+1),*((char*)&unet_buff[0]),*(((char*)&unet_buff[1])+1),*((char*)&unet_buff[1]),*(((char*)unet_buff[2])+1),*((char*)unet_buff[2]));
     link_cnt=0;
     link=ON;
     
 /*    if(flags_tu&0b10000000)
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
      	} */    	
	}




can_in_an_end:
bCAN_RX=0;
}   

//-----------------------------------------------
void t4_init(void){
	TIM4->PSCR = 7;
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

TIM1->CCMR1= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
TIM1->CCMR2= ((6<<4) & TIM1_CCMR_OCM) | TIM1_CCMR_OCxPE; //OC2 toggle mode, prelouded
TIM1->CCER1= TIM1_CCER1_CC1E | TIM1_CCER1_CC2E ; //OC1, OC2 output pins enabled

TIM1->CR1=(TIM1_CR1_CEN | TIM1_CR1_ARPE);
TIM1->BKR|= TIM1_BKR_AOE;
}


//-----------------------------------------------
void adc2_init(void)
{
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

GPIOB->DDR&=~(1<<3);
GPIOB->CR1&=~(1<<3);
GPIOB->CR2&=~(1<<3);

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

ADC2->TDRL=0xff;
	
ADC2->CR2=0x08;
ADC2->CR1=0x40;
ADC2->CSR=0x20+adc_ch+3;
	
ADC2->CR1|=1;
ADC2->CR1|=1;
}




//***********************************************
//***********************************************
//***********************************************
//***********************************************
@far @interrupt void TIM4_UPD_Interrupt (void) 
{
TIM4->SR1&=~TIM4_SR1_UIF;


if(++t0_cnt0>=10)
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
	adc_plazma++;
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

adc_plazma_short=adc_buff_[1];

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

t1_init();

GPIOA->DDR|=(1<<5);
GPIOA->CR1|=(1<<5);
GPIOA->CR2&=~(1<<5);

TZAS=10;

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
		
	     link_drv();
		}

	if(b5Hz)
		{
		b5Hz=0;
		

		
		
		
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

          if(main_cnt<1000)main_cnt++;
  		
  		can_error_cnt++;
  		if(can_error_cnt>=10)
  			{
  			can_error_cnt=0;
			init_CAN();
  			}
		}

	}
}