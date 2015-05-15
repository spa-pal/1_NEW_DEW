#include "stm8s.h"
#include "string.h"
#include "main.h"

char t0_cnt0=0,t0_cnt1=0,t0_cnt2=0,t0_cnt3=0,t0_cnt4=0;
_Bool b100Hz, b10Hz, b5Hz, b2Hz, b1Hz;

u8 mess[14];

#define MY_MESS_STID	0x009e
#define MY_MESS_STID_MASK	0x03ff


char rs485_out_buff[20];

#define TX_BUFFER_SIZE1 50
#define RX_BUFFER_SIZE1 300

@near char tx_buffer1[TX_BUFFER_SIZE1]={0};
signed char tx_counter1;
signed char tx_wr_index1,tx_rd_index1;
@near char rx_buffer[RX_BUFFER_SIZE1]={0};
signed short rx_counter1;
signed short rx_wr_index1,rx_rd_index1;
tx_stat_enum tx_stat=tsOFF;
@near char tx_stat_cnt;
char tx_wd_cnt=100;
char bOUT_FREE;

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
//@eeprom signed short ee_K[4][2];

@near signed short adc_buff[10][16],adc_buff_[10];
char adc_ch,adc_cnt;
signed short adc_plazma_short,adc_plazma[5];
char led_ind_cnt;
char led_ind=5;
char adr_drv_stat=0;
@near char adr[3],adress;
@near char adress_error;

char link,link_cnt;

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
signed short plazma_int[3];

short rs485_rx_cnt;

//-----------------------------------------------
void gran_char(signed char *adr, signed char min, signed char max)
{
if (*adr<min) *adr=min;
if (*adr>max)  *adr=max; 
}

//-----------------------------------------------
void gran(signed short *adr, signed short min, signed short max)
{
if (*adr<min) *adr=min;
if (*adr>max)  *adr=max; 
}




//-----------------------------------------------
void uart1_init (void)
{
//Порт A4 - RX
GPIOA->DDR&=~(1<<4);
GPIOA->CR1|=(1<<4);
GPIOA->CR2&=~(1<<4);

//Порт A5 - TX
GPIOA->DDR|=(1<<5);
GPIOA->CR1|=(1<<5);
GPIOA->CR2&=~(1<<5);	

//Порт B6 - PV
GPIOB->DDR|=(1<<6);
GPIOB->CR1|=(1<<6);
GPIOB->CR2&=~(1<<6);
GPIOB->ODR|=(1<<6);		//Сразу в 1
	
//Порт B7 - DE
GPIOB->DDR|=(1<<7);
GPIOB->CR1|=(1<<7);
GPIOB->CR2&=~(1<<7);
	
UART1->CR1&=~UART1_CR1_M;					
UART1->CR3|= (0<<4) & UART1_CR3_STOP;  	
UART1->BRR2= 0x09;
UART1->BRR1= 0x20;
UART1->CR2|= UART1_CR2_TEN | UART1_CR2_REN | UART1_CR2_RIEN/*| UART2_CR2_TIEN*/ ;	
}

//-----------------------------------------------
void putchar1(char c)
{
while (tx_counter1 == TX_BUFFER_SIZE1);
///#asm("cli")
if (tx_counter1 || ((UART1->SR & UART1_SR_TXE)==0))
   {
   tx_buffer1[tx_wr_index1]=c;
   if (++tx_wr_index1 == TX_BUFFER_SIZE1) tx_wr_index1=0;
   ++tx_counter1;
   }
else UART1->DR=c;

UART1->CR2|= UART1_CR2_TIEN;
}


//-----------------------------------------------
void uart1_out_adr(char *ptr, char len)
{
@near char UOB1[30];
@near char i,t=0;
@near short ii;

for(ii=0;ii<1000;ii++)GPIOB->ODR|=(1<<7);


for(i=0;i<len;i++)
	{
	UOB1[i]=ptr[i];
	}
	



tx_stat=tsON;

for (i=0;i<len;i++)
	{
	putchar1(UOB1[i]);
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
	CAN->Page.Filter01.F0R1= MY_MESS_STID>>3;			// 16 bits mode
	CAN->Page.Filter01.F0R2= MY_MESS_STID<<5;
	CAN->Page.Filter01.F0R5= MY_MESS_STID_MASK>>3;
	CAN->Page.Filter01.F0R6= MY_MESS_STID_MASK<<5;
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
//#endif

	CAN->Page.Config.FCR1|= CAN_FCR1_FACT0;	// filter 0 active
	
	
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


if((mess[6]==adress)&&(mess[7]==adress)&&(mess[8]==GETTM))	
	{ 
	
	can_error_cnt=0;
	
//	bMAIN=0;
// 	flags_tu=mess[9];

 		 
// 	if(flags_tu&0b00000010) flags|=0b01000000;
 	//else flags&=0b10111111; 
 		
// 	vol_u_temp=mess[10]+mess[11]*256;
 //	vol_i_temp=mess[12]+mess[13]*256;  
 	
 	//I=1234;
    //	Un=6543;
 	//Ui=6789;
 	//T=246;
 	//flags=0x55;
 	//_x_=33;
 	//rotor_int=1000;
	//plazma_int[2]=T;
 	//rotor_int=flags_tu+(((short)flags)<<8);
	
	//Un=1000;
	//Ui=500;
	
	can_transmit(0x18e,adress,PUTTM1,*(((char*)&I)+1),*((char*)&I),*(((char*)&Un)+1),*((char*)&Un),*(((char*)&Ui)+1),*((char*)&Ui));
	can_transmit(0x18e,adress,PUTTM2,T,0,0,0,*(((char*)&plazma_int[2])+1),*((char*)&plazma_int[2]));
     link_cnt=0;
     link=ON;
     
     	
    	
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

if(tx_stat_cnt)
	{
	tx_stat_cnt--;
	if(tx_stat_cnt==0)tx_stat=tsOFF;
	
	}

if(tx_wd_cnt)
	{
	tx_wd_cnt--;

	}
else 
	{
	GPIOB->ODR&=~(1<<7);
	}


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
@far @interrupt void UART1TxInterrupt (void) 
{
if (tx_counter1)
	{
   	--tx_counter1;
	UART1->DR=tx_buffer1[tx_rd_index1];
	if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
      
    	
	}
else 
	{
	//GPIOD->ODR&=~(1<<4);	
	tx_stat_cnt=3;
	//tx_stat=tsOFF;

		bOUT_FREE=1;
		UART1->CR2&= ~UART1_CR2_TIEN;
	}
tx_wd_cnt=3;
}

//***********************************************
@far @interrupt void UART1RxInterrupt (void) 
{
@near char temp,rx_status,rx_data;

rx_status=UART1->SR;
rx_data=UART1->DR;

if (rx_status & (UART1_SR_RXNE))
{

temp=rx_data;
/*if(tx_stat==tsOFF)
	{
	gran(&rx_wr_index,0,RX_BUFFER_SIZE); 
	rx_buffer[rx_wr_index]=temp;
	
		

	rx_wr_index++;

	}*/
	
	rs485_rx_cnt++;
	if(temp==0x0d)
	{
			Ui=rs485_rx_cnt;
			rs485_rx_cnt=0;
	}
}


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


t4_init();

		GPIOG->DDR|=(1<<0);
		GPIOG->CR1|=(1<<0);
		GPIOG->CR2&=~(1<<0);	
		//GPIOG->ODR^=(1<<0);

		GPIOG->DDR&=~(1<<1);
		GPIOG->CR1|=(1<<1);
		GPIOG->CR2&=~(1<<1);

init_CAN();

//CAN->DGR&=0xfc;

/*GPIOA->DDR|=(1<<5);
GPIOA->CR1|=(1<<5);
GPIOA->CR2&=~(1<<5);*/

uart1_init();

adress=1;

enableInterrupts();
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
      	}  
      	
	if(b10Hz)
		{
		b10Hz=0;
	
			can_tx_hndl();
      	}
      	
	if(b2Hz)
		{
		b2Hz=0;
		
		}
      	
	if(b1Hz)
		{
		b1Hz=0;
		
		rs485_out_buff[0]=0x7e;
		rs485_out_buff[1]=0x31;
		rs485_out_buff[2]=0x31;
		rs485_out_buff[3]=0x30;
		rs485_out_buff[4]=0x31;
		rs485_out_buff[5]=0x44;
		rs485_out_buff[6]=0x30;
		rs485_out_buff[7]=0x38;
		rs485_out_buff[8]=0x32;
		rs485_out_buff[9]=0x45;
		rs485_out_buff[10]=0x30;
		rs485_out_buff[11]=0x30;
		rs485_out_buff[12]=0x32;
		rs485_out_buff[13]=0x30;
		rs485_out_buff[14]=0x31;
		rs485_out_buff[15]=0x46;
		rs485_out_buff[16]=0x44;
		rs485_out_buff[17]=0x32;
		rs485_out_buff[18]=0x37;
		rs485_out_buff[19]=0x0d;
		
		uart1_out_adr(rs485_out_buff,20);
		
		GPIOB->DDR|=(1<<0);
		GPIOB->CR1|=(1<<0);
		GPIOB->CR2&=~(1<<0);	
		GPIOB->ODR^=(1<<0);			

		GPIOB->DDR|=(1<<1);
		GPIOB->CR1|=(1<<1);
		GPIOB->CR2&=~(1<<1);	
		GPIOB->ODR^=(1<<1);	
		
		}

	}
}