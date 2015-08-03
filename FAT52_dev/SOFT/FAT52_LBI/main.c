#include "stm8s.h"
#include "string.h"
#include "main.h"
#include <ctype.h>
#include <math.h>

char t0_cnt0=0,t0_cnt1=0,t0_cnt2=0,t0_cnt3=0,t0_cnt4=0;
_Bool b100Hz, b10Hz, b5Hz, b2Hz, b1Hz,bBAT_REQ;

u8 mess[14];

#define MY_MESS_STID	0x009e
#define MY_MESS_STID_MASK	0x03ff


char rs485_out_buff[20];

#define TX_BUFFER_SIZE1 300
#define RX_BUFFER_SIZE1 50

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
char can_out_buff[6][16];
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
#define PUT_LB_TM1 	0xD1
#define PUT_LB_TM2 	0xD2
#define PUT_LB_TM3 	0xD3
#define PUT_LB_TM4 	0xD4


#define ON 0x55
#define OFF 0xaa
signed short plazma_int[3];

short rs485_rx_cnt;
char bRX485;

//@near short max_cell_volt[7];
//@near short min_cell_volt[7];
//@near short max_cell_temp[7];
//@near short min_cell_temp[7];
//@near short tot_bat_volt[7];
//@near short ch_curr[7];
//@near short dsch_curr[7];
//@near short s_o_c[7];
//@near short rat_cap[7];
//@near short	r_b_t[7];
//@near short	c_c_l_v[7];
//short	s_o_h[7];
//short	b_p_ser_num[7];
//unsigned char flags_byte0[7],flags_byte1[7];
unsigned char rs485_cnt=0;
_Bool bRS485ERR;
//char plazma_cnt;
char transmit_cnt_number; 	//Счетчик батарей на передачу, считает от 0 до 6 (7 батарей)

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

UART1->CR2|= UART1_CR2_TIEN | UART1_CR2_TCIEN;
}


//-----------------------------------------------
void uart1_out_adr(char *ptr, char len)
{
@near char UOB1[30];
@near char i,t=0;
@near short ii;

//for(ii=0;ii<10;ii++)
GPIOB->ODR|=(1<<7);


for(i=0;i<len;i++)
	{
	UOB1[i]=ptr[i];
	}
	



tx_stat=tsON;

for (i=0;i<len;i++)
	{
	putchar1(UOB1[i]);
	} 

rs485_cnt++;
}

//-----------------------------------------------
int str2int(char *ptr, char len)
{


@near char i;
@near char temp[10]={0,0,0,0,0,0,0,0,0};
@near int temp_out=0;
@near char tt;
//i=3;
//disableInterrupts();
for (i=0;i<len;i++)
{
	tt=*(ptr+i);
	
	if(isalnum(tt/**(ptr+i)*/))
	{
		if(isdigit(tt/**(ptr+i)*/))
		{
		temp[i]=tt/**(ptr+i)*/-'0';
		}
		if(islower(tt/**(ptr+i)*/))
		{
		temp[i]=tt/**(ptr+i)*/-'a'+10;
		}
		if(isupper(tt/**(ptr+i)*/))
		{
		temp[i]=tt;
		temp[i]-=/**(ptr+i)*/'A';
		temp[i]+=10;
		}
		//temp_out=temp[i];
	}
}

for(i=len;i;i--)
{
	temp_out+= ((int)pow(16,len-i))*temp[i-1]; 
}

//temp_out+= temp[3]+(temp[2]*16)+(temp[1]*256);
//enableInterrupts();
return temp_out;
}

//-----------------------------------------------
void rx485_in_an(void)
{
//@near char rs485_tx_buff[300];

	if(bRX485==1)
	{
	GPIOD->DDR|=(1<<7);
	GPIOD->CR1|=(1<<7);
	GPIOD->CR2&=~(1<<7);	
	GPIOD->ODR^=(1<<7);

	tx_buffer1[0]=0x7e;
	tx_buffer1[1]=0x31;
	tx_buffer1[2]=0x31;
	tx_buffer1[3]=0x30;
	tx_buffer1[4]=0x31;
	tx_buffer1[5]=0x44;
	tx_buffer1[6]=0x30;
	tx_buffer1[7]=0x30;
	tx_buffer1[8]=0x30;
	tx_buffer1[9]=0x36;
	tx_buffer1[10]=0x31;
	tx_buffer1[11]=0x31;
	tx_buffer1[12]=0x38;
	
	tx_buffer1[13]=0x30;
	tx_buffer1[14]=0x44;
	tx_buffer1[15]=0x37;
	tx_buffer1[16]=0x41;
	tx_buffer1[17]=0x30;
	tx_buffer1[18]=0x44;
	tx_buffer1[19]=0x33;
	tx_buffer1[20]=0x43;
	tx_buffer1[21]=0x31;
	tx_buffer1[22]=0x38;
	tx_buffer1[23]=0x31;
	tx_buffer1[24]=0x38;
	tx_buffer1[25]=0x31;
	tx_buffer1[26]=0x34;
	tx_buffer1[27]=0x31;
	tx_buffer1[28]=0x32;
	tx_buffer1[29]=0x30;
	tx_buffer1[30]=0x30;
	tx_buffer1[31]=0x30;
	tx_buffer1[32]=0x30;
	tx_buffer1[33]=0x30;
	tx_buffer1[34]=0x30;
	tx_buffer1[35]=0x35;
	tx_buffer1[36]=0x35;
	tx_buffer1[37]=0x36;
	tx_buffer1[38]=0x33;
	tx_buffer1[39]=0x31;
	tx_buffer1[40]=0x44;
	tx_buffer1[41]=0x34;
	tx_buffer1[42]=0x43;
	tx_buffer1[43]=0x46;
	tx_buffer1[44]=0x46;
	tx_buffer1[45]=0x30;
	tx_buffer1[46]=0x45;
	tx_buffer1[47]=0x41;
	tx_buffer1[48]=0x36;
	tx_buffer1[49]=0x36;
	tx_buffer1[50]=0x34;
	tx_buffer1[51]=0x30;
	tx_buffer1[52]=0x31;	
	
	tx_buffer1[13+40]=0x30;
	tx_buffer1[14+40]=0x44;
	tx_buffer1[15+40]=0x37;
	tx_buffer1[16+40]=0x41;
	tx_buffer1[17+40]=0x30;
	tx_buffer1[18+40]=0x44;
	tx_buffer1[19+40]=0x33;
	tx_buffer1[20+40]=0x43;
	tx_buffer1[21+40]=0x31;
	tx_buffer1[22+40]=0x38;
	tx_buffer1[23+40]=0x31;
	tx_buffer1[24+40]=0x38;
	tx_buffer1[25+40]=0x31;
	tx_buffer1[26+40]=0x34;
	tx_buffer1[27+40]=0x31;
	tx_buffer1[28+40]=0x32;
	tx_buffer1[29+40]=0x30;
	tx_buffer1[30+40]=0x30;
	tx_buffer1[31+40]=0x30;
	tx_buffer1[32+40]=0x30;
	tx_buffer1[33+40]=0x30;
	tx_buffer1[34+40]=0x30;
	tx_buffer1[35+40]=0x35;
	tx_buffer1[36+40]=0x35;
	tx_buffer1[37+40]=0x36;
	tx_buffer1[38+40]=0x33;
	tx_buffer1[39+40]=0x31;
	tx_buffer1[40+40]=0x44;
	tx_buffer1[41+40]=0x34;
	tx_buffer1[42+40]=0x43;
	tx_buffer1[43+40]=0x46;
	tx_buffer1[44+40]=0x46;
	tx_buffer1[45+40]=0x30;
	tx_buffer1[46+40]=0x45;
	tx_buffer1[47+40]=0x41;
	tx_buffer1[48+40]=0x36;
	tx_buffer1[49+40]=0x36;
	tx_buffer1[50+40]=0x34;
	tx_buffer1[51+40]=0x30;
	tx_buffer1[52+40]=0x32;	

	tx_buffer1[13+80]=0x30;
	tx_buffer1[14+80]=0x44;
	tx_buffer1[15+80]=0x37;
	tx_buffer1[16+80]=0x41;
	tx_buffer1[17+80]=0x30;
	tx_buffer1[18+80]=0x44;
	tx_buffer1[19+80]=0x33;
	tx_buffer1[20+80]=0x43;
	tx_buffer1[21+80]=0x31;
	tx_buffer1[22+80]=0x38;
	tx_buffer1[23+80]=0x31;
	tx_buffer1[24+80]=0x38;
	tx_buffer1[25+80]=0x31;
	tx_buffer1[26+80]=0x34;
	tx_buffer1[27+80]=0x31;
	tx_buffer1[28+80]=0x32;
	tx_buffer1[29+80]=0x30;
	tx_buffer1[30+80]=0x30;
	tx_buffer1[31+80]=0x30;
	tx_buffer1[32+80]=0x30;
	tx_buffer1[33+80]=0x30;
	tx_buffer1[34+80]=0x30;
	tx_buffer1[35+80]=0x35;
	tx_buffer1[36+80]=0x35;
	tx_buffer1[37+80]=0x36;
	tx_buffer1[38+80]=0x33;
	tx_buffer1[39+80]=0x31;
	tx_buffer1[40+80]=0x44;
	tx_buffer1[41+80]=0x34;
	tx_buffer1[42+80]=0x43;
	tx_buffer1[43+80]=0x46;
	tx_buffer1[44+80]=0x46;
	tx_buffer1[45+80]=0x30;
	tx_buffer1[46+80]=0x45;
	tx_buffer1[47+80]=0x41;
	tx_buffer1[48+80]=0x36;
	tx_buffer1[49+80]=0x36;
	tx_buffer1[50+80]=0x34;
	tx_buffer1[51+80]=0x30;
	tx_buffer1[52+80]=0x33;
	
	tx_buffer1[13+120]=0x30;
	tx_buffer1[14+120]=0x44;
	tx_buffer1[15+120]=0x37;
	tx_buffer1[16+120]=0x41;
	tx_buffer1[17+120]=0x30;
	tx_buffer1[18+120]=0x44;
	tx_buffer1[19+120]=0x33;
	tx_buffer1[20+120]=0x43;
	tx_buffer1[21+120]=0x31;
	tx_buffer1[22+120]=0x38;
	tx_buffer1[23+120]=0x31;
	tx_buffer1[24+120]=0x38;
	tx_buffer1[25+120]=0x31;
	tx_buffer1[26+120]=0x34;
	tx_buffer1[27+120]=0x31;
	tx_buffer1[28+120]=0x32;
	tx_buffer1[29+120]=0x30;
	tx_buffer1[30+120]=0x30;
	tx_buffer1[31+120]=0x30;
	tx_buffer1[32+120]=0x30;
	tx_buffer1[33+120]=0x30;
	tx_buffer1[34+120]=0x30;
	tx_buffer1[35+120]=0x35;
	tx_buffer1[36+120]=0x35;
	tx_buffer1[37+120]=0x36;
	tx_buffer1[38+120]=0x33;
	tx_buffer1[39+120]=0x31;
	tx_buffer1[40+120]=0x44;
	tx_buffer1[41+120]=0x34;
	tx_buffer1[42+120]=0x43;
	tx_buffer1[43+120]=0x46;
	tx_buffer1[44+120]=0x46;
	tx_buffer1[45+120]=0x30;
	tx_buffer1[46+120]=0x45;
	tx_buffer1[47+120]=0x41;
	tx_buffer1[48+120]=0x36;
	tx_buffer1[49+120]=0x36;
	tx_buffer1[50+120]=0x34;
	tx_buffer1[51+120]=0x30;
	tx_buffer1[52+120]=0x31;	

/*		max_cell_volt[0]=str2int(&rx_buffer[13],4);
		min_cell_volt[0]=str2int(&rx_buffer[17],4);
		max_cell_temp[0]=str2int(&rx_buffer[21],2);
		min_cell_temp[0]=str2int(&rx_buffer[23],2);
		tot_bat_volt[0]=str2int(&rx_buffer[25],4);
		ch_curr[0]=str2int(&rx_buffer[29],4);
		dsch_curr[0]=str2int(&rx_buffer[33],4);
		s_o_c[0]=str2int(&rx_buffer[37],2);
		rat_cap[0]=str2int(&rx_buffer[39],4);
		r_b_t[0]=str2int(&rx_buffer[43],2);
		c_c_l_v[0]=str2int(&rx_buffer[45],4);
		s_o_h[0]=str2int(&rx_buffer[49],2);
		b_p_ser_num[0]=str2int(&rx_buffer[51],2);

		max_cell_volt[1]=str2int(&rx_buffer[13+40],4);
		min_cell_volt[1]=str2int(&rx_buffer[17+40],4);
		max_cell_temp[1]=str2int(&rx_buffer[21+40],2);
		min_cell_temp[1]=str2int(&rx_buffer[23+40],2);
		tot_bat_volt[1]=str2int(&rx_buffer[25+40],4);
		ch_curr[1]=str2int(&rx_buffer[29+40],4);
		dsch_curr[1]=str2int(&rx_buffer[33+40],4);
		s_o_c[1]=str2int(&rx_buffer[37+40],2);
		rat_cap[1]=str2int(&rx_buffer[39+40],4);
		r_b_t[1]=str2int(&rx_buffer[43+40],2);
		c_c_l_v[1]=str2int(&rx_buffer[45+40],4);
		s_o_h[1]=str2int(&rx_buffer[49+40],2);
		b_p_ser_num[1]=str2int(&rx_buffer[51+40],2);
		
		max_cell_volt[2]=str2int(&rx_buffer[13+80],4);
		min_cell_volt[2]=str2int(&rx_buffer[17+80],4);
		max_cell_temp[2]=str2int(&rx_buffer[21+80],2);
		min_cell_temp[2]=str2int(&rx_buffer[23+80],2);
		tot_bat_volt[2]=str2int(&rx_buffer[25+80],4);
		ch_curr[2]=str2int(&rx_buffer[29+80],4);
		dsch_curr[2]=str2int(&rx_buffer[33+80],4);
		s_o_c[2]=str2int(&rx_buffer[37+80],2);
		rat_cap[2]=str2int(&rx_buffer[39+80],4);
		r_b_t[2]=str2int(&rx_buffer[43+80],2);
		c_c_l_v[2]=str2int(&rx_buffer[45+80],4);
		s_o_h[2]=str2int(&rx_buffer[49+80],2);
		b_p_ser_num[2]=str2int(&rx_buffer[51+80],2);		

		max_cell_volt[3]=str2int(&rx_buffer[13+120],4);
		min_cell_volt[3]=str2int(&rx_buffer[17+120],4);
		max_cell_temp[3]=str2int(&rx_buffer[21+120],2);
		min_cell_temp[3]=str2int(&rx_buffer[23+120],2);
		tot_bat_volt[3]=str2int(&rx_buffer[25+120],4);
		ch_curr[3]=str2int(&rx_buffer[29+120],4);
		dsch_curr[3]=str2int(&rx_buffer[33+120],4);
		s_o_c[3]=str2int(&rx_buffer[37+120],2);
		rat_cap[3]=str2int(&rx_buffer[39+120],4);
		r_b_t[3]=str2int(&rx_buffer[43+120],2);
		c_c_l_v[3]=str2int(&rx_buffer[45+120],4);
		s_o_h[3]=str2int(&rx_buffer[49+120],2);
		b_p_ser_num[3]=str2int(&rx_buffer[51+120],2);

		max_cell_volt[4]=str2int(&rx_buffer[13+160],4);
		min_cell_volt[4]=str2int(&rx_buffer[17+160],4);
		max_cell_temp[4]=str2int(&rx_buffer[21+160],2);
		min_cell_temp[4]=str2int(&rx_buffer[23+160],2);
		tot_bat_volt[4]=str2int(&rx_buffer[25+160],4);
		ch_curr[4]=str2int(&rx_buffer[29+160],4);
		dsch_curr[4]=str2int(&rx_buffer[33+160],4);
		s_o_c[4]=str2int(&rx_buffer[37+160],2);
		rat_cap[4]=str2int(&rx_buffer[39+160],4);
		r_b_t[4]=str2int(&rx_buffer[43+160],2);
		c_c_l_v[4]=str2int(&rx_buffer[45+160],4);
		s_o_h[4]=str2int(&rx_buffer[49+160],2);
		b_p_ser_num[4]=str2int(&rx_buffer[51+160],2);

		max_cell_volt[5]=str2int(&rx_buffer[13+200],4);
		min_cell_volt[5]=str2int(&rx_buffer[17+200],4);
		max_cell_temp[5]=str2int(&rx_buffer[21+200],2);
		min_cell_temp[5]=str2int(&rx_buffer[23+200],2);
		tot_bat_volt[5]=str2int(&rx_buffer[25+200],4);
		ch_curr[5]=str2int(&rx_buffer[29+200],4);
		dsch_curr[5]=str2int(&rx_buffer[33+200],4);
		s_o_c[5]=str2int(&rx_buffer[37+200],2);
		rat_cap[5]=str2int(&rx_buffer[39+200],4);
		r_b_t[5]=str2int(&rx_buffer[43+200],2);
		c_c_l_v[5]=str2int(&rx_buffer[45+200],4);
		s_o_h[5]=str2int(&rx_buffer[49+200],2);
		b_p_ser_num[5]=str2int(&rx_buffer[51+200],2);

		max_cell_volt[6]=str2int(&rx_buffer[13+240],4);
		min_cell_volt[6]=str2int(&rx_buffer[17+240],4);
		max_cell_temp[6]=str2int(&rx_buffer[21+240],2);
		min_cell_temp[6]=str2int(&rx_buffer[23+240],2);
		tot_bat_volt[6]=str2int(&rx_buffer[25+240],4);
		ch_curr[6]=str2int(&rx_buffer[29+240],4);
		dsch_curr[6]=str2int(&rx_buffer[33+240],4);
		s_o_c[6]=str2int(&rx_buffer[37+240],2);
		rat_cap[6]=str2int(&rx_buffer[39+240],4);
		r_b_t[6]=str2int(&rx_buffer[43+240],2);
		c_c_l_v[6]=str2int(&rx_buffer[45+240],4);
		s_o_h[6]=str2int(&rx_buffer[49+240],2);
		b_p_ser_num[6]=str2int(&rx_buffer[51+240],2);*/
		
		rs485_cnt=0;
		bRS485ERR=0;

	}
	else if(bRX485==2)
	{
			GPIOD->DDR|=(1<<7);
	GPIOD->CR1|=(1<<7);
	GPIOD->CR2&=~(1<<7);	
	GPIOD->ODR^=(1<<7);
	
/*		flags_byte0[0]=str2int(&rx_buffer[49],2);
		flags_byte1[0]++;//=str2int(&rx_buffer[51],2);

		flags_byte0[1]=str2int(&rx_buffer[49+34],2);
		flags_byte1[1]++;//=str2int(&rx_buffer[51],2);
		
		flags_byte0[2]=str2int(&rx_buffer[49+68],2);
		flags_byte1[2]++;//=str2int(&rx_buffer[51],2);

		flags_byte0[3]=str2int(&rx_buffer[49+102],2);
		flags_byte1[3]++;//=str2int(&rx_buffer[51],2);
		
		flags_byte0[4]=str2int(&rx_buffer[49+136],2);
		flags_byte1[4]++;//=str2int(&rx_buffer[51],2);

		flags_byte0[5]=str2int(&rx_buffer[49+170],2);
		flags_byte1[5]++;//=str2int(&rx_buffer[51],2);
		
		flags_byte0[6]=str2int(&rx_buffer[49+204],2);
		flags_byte1[6]++;//=str2int(&rx_buffer[51],2);*/		
		rs485_cnt=0;
		bRS485ERR=0;

	}
bRX485=0;	
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

if((can_buff_wr_ptr<0)||(can_buff_wr_ptr>4))can_buff_wr_ptr=0;

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
if(can_buff_wr_ptr>4)can_buff_wr_ptr=0;
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

//adress=1;

if((mess[6]==19)&&(mess[7]==19)&&(mess[8]==GETTM))	
	{ 
	GPIOD->DDR|=(1<<7);
	GPIOD->CR1|=(1<<7);
	GPIOD->CR2&=~(1<<7);	
	GPIOD->ODR^=(1<<7);
	can_error_cnt=0;
	
	//T=tot_bat_volt;
	
	//max_cell_volt=s_o_c;
	
	//max_cell_volt=35000;
/*	
	can_transmit(0x18e,PUT_LB_TM1,transmit_cnt_number,*(((char*)&max_cell_volt[transmit_cnt_number])+1),*((char*)&max_cell_volt[transmit_cnt_number]),*(((char*)&min_cell_volt[transmit_cnt_number])+1),*((char*)&min_cell_volt[transmit_cnt_number]),*(((char*)&tot_bat_volt[transmit_cnt_number])+1),*((char*)&tot_bat_volt[transmit_cnt_number]));
	can_transmit(0x18e,PUT_LB_TM2,transmit_cnt_number,*(((char*)&ch_curr[transmit_cnt_number])+1),*((char*)&ch_curr[transmit_cnt_number]),*(((char*)&dsch_curr[transmit_cnt_number])+1),*((char*)&dsch_curr[transmit_cnt_number]),*(((char*)&rat_cap[transmit_cnt_number])+1),*((char*)&rat_cap[transmit_cnt_number]));
	can_transmit(0x18e,PUT_LB_TM3,transmit_cnt_number,(unsigned char)s_o_h[transmit_cnt_number],(unsigned char)s_o_c[transmit_cnt_number],*(((char*)&c_c_l_v[transmit_cnt_number])+1),*((char*)&c_c_l_v[transmit_cnt_number]),(unsigned char)r_b_t[transmit_cnt_number],(unsigned char)flags_byte0[transmit_cnt_number]);
	can_transmit(0x18e,PUT_LB_TM4,transmit_cnt_number,(unsigned char)bRS485ERR,(unsigned char)rs485_cnt,(unsigned char)max_cell_temp[transmit_cnt_number],(unsigned char)min_cell_temp[transmit_cnt_number],(unsigned char)flags_byte1[transmit_cnt_number],0);
     link_cnt=0;
     link=ON;*/
     
     	
    	
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
/*
if(tx_wd_cnt)
	{
	tx_wd_cnt--;

	}
else 
	{
	GPIOB->ODR&=~(1<<7);
	}
*/

}

//***********************************************
@far @interrupt void CAN_RX_Interrupt (void) 
{

			

		/*GPIOB->DDR|=(1<<1);
		GPIOB->CR1|=(1<<1);
		GPIOB->CR2&=~(1<<1);	
		GPIOB->ODR^=(1<<1);	*/
		
	
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
@near char tx_status;

tx_status=UART1->SR;

if (tx_status & (UART1_SR_TXE))
{
	if (tx_counter1)
		{
		--tx_counter1;
		UART1->DR=tx_buffer1[tx_rd_index1];
		if (++tx_rd_index1 == TX_BUFFER_SIZE1) tx_rd_index1=0;
		}
	else 
		{
		tx_stat_cnt=3;
			bOUT_FREE=1;
			UART1->CR2&= ~UART1_CR2_TIEN;
			
		}
}
if (tx_status & (UART1_SR_TC))
	{		
	GPIOB->ODR&=~(1<<7);
	UART1->SR&=~UART1_SR_TC;
	}
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
rx_buffer[rs485_rx_cnt]=rx_data;
rs485_rx_cnt++;




/*if(tx_stat==tsOFF)
	{
	gran(&rx_wr_index,0,RX_BUFFER_SIZE); 
	rx_buffer[rx_wr_index]=temp;
	
		

	rx_wr_index++;

	}*/
	
	//;
	if((rx_data==0x0d)&&(rs485_rx_cnt==20))
		{
		if(rx_buffer[8]==0x32){
		bRX485=1;
		}
	
		if(rx_buffer[8]==0x33){
		bRX485=2;
		}
	}
	if(rx_data==0x0d)rs485_rx_cnt=0;	
	
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

adress=19;

enableInterrupts();
	while (1)
	{
	
	if(bRX485)
	{
		rx485_in_an();
	}

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
		
		/*GPIOD->DDR|=(1<<7);
		GPIOD->CR1|=(1<<7);
		GPIOD->CR2&=~(1<<7);	
		GPIOD->ODR^=(1<<7);*/
	
		if(rs485_cnt>=10)
			{
			rs485_cnt=10;
			bRS485ERR=1;
			}
		/*rs485_out_buff[0]=0x7e;
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
		
		uart1_out_adr(rs485_out_buff,20);*/
		

		//plazma_cnt++;
		}

	}
}