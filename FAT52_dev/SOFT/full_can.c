#include "full_can.h"
#include "LPC17XX.H" 
#include "main.h"
#include "uart0.h"
#include "cmd.c"
#include "gran.h"

short volatile gCANFilter = 0;
char ptr_can1_tx_wr,ptr_can1_tx_rd;
long can1_info[8];
long can1_id[8];
long can1_data[8];
long can1_datb[8];
//unsigned short rotor_can[6];

// FullCAN Message List
FULLCAN_MSG volatile gFullCANList[MAX_FILTERS];

char bR;
char RXBUFF[40],TXBUFF[40];
char bIN;
char bd_dumm[25];
char bd[25];
char TX_len;
char bOUT;
char can_tx_cnt;
char bOUT_FREE=1;
char rotor_rotor_rotor[2];

char plazma_can[10];


volatile uint32_t CANStatus;

//-----------------------------------------------
char CRC1_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 

//-----------------------------------------------
char CRC2_in(void)
{
char r,j,lb;
lb=(RXBUFF[1]&0x1f)+0x04;
r=RXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(RXBUFF[j]^Table95[r]);
	}
if(r==0)r=0xFF;
return r;	
}  

//-----------------------------------------------
char CRC1_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table87[r]);
	}
if(r==0)r=0xFF;
return r;	
} 

//-----------------------------------------------
char CRC2_out(void)
{
char r,j,lb;
lb=(TXBUFF[1]&0x1f)+0x04;
r=TXBUFF[0];
for(j=1;j<(lb+1);j++)
	{
	r=(TXBUFF[j]^Table95[r]);
	}
if(r==0)r=0xFF;
return r;	
}

//-----------------------------------------------
void can1_out_adr(char* ptr,char num)
{
//plazma_can4++;
if(num<=8)
	{
	can1_info[ptr_can1_tx_wr]=(((long)num)<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	}
	
else if(num<=16)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-8))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	

else if(num<=24)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;

	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-16))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[17];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[19];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[20];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[21];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[22];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[23];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	

else if(num<=32)
	{
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[0];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[1];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[2];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[3];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[4];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[5];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[6];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[7];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;

	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[8];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[9];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[10];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[11];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[12];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[13];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[14];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[15];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(8UL<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[16];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[17];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[18];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[19];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[20];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[21];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[22];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[23];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;
	
	can1_info[ptr_can1_tx_wr]=(((long)(num-24))<<16)&0x000f0000UL;
	can1_id[ptr_can1_tx_wr]=0x0000009eUL;
	*((char*)&can1_data[ptr_can1_tx_wr])=ptr[24];
	*(((char*)&can1_data[ptr_can1_tx_wr])+1)=ptr[25];
	*(((char*)&can1_data[ptr_can1_tx_wr])+2)=ptr[26];
	*(((char*)&can1_data[ptr_can1_tx_wr])+3)=ptr[27];
	*((char*)&can1_datb[ptr_can1_tx_wr])=ptr[28];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=ptr[29];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=ptr[30];
	*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=ptr[31];	
	ptr_can1_tx_wr++;
	if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;	
	}	


if(bOUT_FREE)
	{
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}
}	


//-----------------------------------------------
void can1_out(char dat0,char dat1,char dat2,char dat3,char dat4,char dat5,char dat6,char dat7)
{
can1_info[ptr_can1_tx_wr]=((8UL)<<16)&0x000f0000UL;
can1_id[ptr_can1_tx_wr]=0x0000018eUL;
*((char*)&can1_data[ptr_can1_tx_wr])=dat0;
*(((char*)&can1_data[ptr_can1_tx_wr])+1)=dat1;
*(((char*)&can1_data[ptr_can1_tx_wr])+2)=dat2;
*(((char*)&can1_data[ptr_can1_tx_wr])+3)=dat3;
*((char*)&can1_datb[ptr_can1_tx_wr])=dat4;
*(((char*)&can1_datb[ptr_can1_tx_wr])+1)=dat5;
*(((char*)&can1_datb[ptr_can1_tx_wr])+2)=dat6;
*(((char*)&can1_datb[ptr_can1_tx_wr])+3)=dat7;	
ptr_can1_tx_wr++;
if(ptr_can1_tx_wr>=8)ptr_can1_tx_wr=0;


if(bOUT_FREE)
	{
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
     bOUT_FREE=0;	
	}
}	



//-----------------------------------------------
void can_adr_hndl(void)
{
	TXBUFF[2]=RXBUFF[3];
	TXBUFF[3]=RXBUFF[2];
	TXBUFF[4]=((RXBUFF[4]&0xF0)>>4)|((RXBUFF[4]&0x0f)<<4);
	TXBUFF[5]=((RXBUFF[5]&0xF0)>>4)|((RXBUFF[5]&0x0f)<<4);	
}	

//-----------------------------------------------
void can_in_an(void)
{
if(!bIN) goto CAN_IN_AN_end; 

if((RXBUFF[0]==8)&&(RXBUFF[1]==8))
     {
     can1_out(8,PUTTM,*((char*)&adc_buff_[0]),*(((char*)&adc_buff_[0])+1),*((char*)&adc_buff_[2]),*(((char*)&adc_buff_[2])+1),*((char*)&T),*(((char*)&T)+1));
     link_cnt=0;
     link_stat=lsON;
     Uvv[0]=*((signed short*)&RXBUFF[2]);
     Uvv[1]=*((signed short*)&RXBUFF[4]);
     Uvv[2]=*((signed short*)&RXBUFF[6]);
	 bRESET=RXBUFF[7];
     }
else if((RXBUFF[0]==9)&&(RXBUFF[1]==9))
     {
     can1_out(9,PUTTM,vvod,reset_cnt,0,0,0,0);

     pos_vent=RXBUFF[2];
     //gran_char(&pos_vent,0,12);
     power_cnt_adrl=RXBUFF[3];
     power_cnt_adrh=RXBUFF[4];

     link_cnt=0;
     link_stat=lsON;
     }     

else if((RXBUFF[0]==10)&&(RXBUFF[1]==10))
     {
     can1_out(10,PUTTM,*((char*)&power_current),*(((char*)&power_current)+1),*((char*)&power_summary),*(((char*)&power_summary)+1),*(((char*)&power_summary)+2),*(((char*)&power_summary)+3));

     }

CAN_IN_AN_end:
bIN=0;
}   
/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
void CAN_ISR_Rx1( void )
{
unsigned int buf;
unsigned int *pDest;
char temp;
char *ptr,j;
//can_cnt++;

rotor_can[0]++;

  if (!(LPC_CAN1->RFS & 0xC0000400L))
  { // 11-bit ID, no RTR, matched a filter

rotor_can[1]++;
    // initialize destination pointer
    // filter number is in lower 10 bits of C1RFS
    pDest = (unsigned int *) &(gFullCANList[(LPC_CAN1->RFS & 0x000003FFL)].Dat1);
    
    // calculate contents for first entry into FullCAN list
    buf = LPC_CAN1->RFS & 0xC00F0000L; // mask FF, RTR and DLC
    buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
    buf |= LPC_CAN1->RID & 0x000007FFL; // get CAN message ID

    // now copy entire message to FullCAN list
    *pDest = buf; 
    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
    *pDest = LPC_CAN1->RDA; 
    pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
    *pDest = LPC_CAN1->RDB; 

    // now set the sempahore to complete
    buf |= 0x03000000L; // set semaphore to 11b
    pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
    *pDest = buf; 
    
	temp=(char)gFullCANList[0].DatA;
	if(temp==0x30) bR=0;
	else bR++;
	
	temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     ptr=(char*)(&gFullCANList[0].DatA);
	
	if(!bR)
		{
		for(j=0;j<temp;j++)
			{
			RXBUFF[j]=*ptr;
			ptr++;
			}
		}
	else if(bR==1)
		{
		for(j=8;j<(temp+8);j++)
			{
			RXBUFF[j]=*ptr;
			ptr++;
			}                      
			
		} 		
	
	
	
		
	temp=((RXBUFF[1]&0x1f)+4);
rotor_can[2]++;
	if((CRC1_in()==RXBUFF[temp+1])&&(CRC2_in()==RXBUFF[temp+2])&&bR)
		{
  
		bIN=1;
  		rotor_can[3]++;
  		can_in_an();
		}    
    
  }

  LPC_CAN1->CMR = 0x04; // release receive buffer
}

/**************************************************************************
DOES:    Interrupt Service Routine for CAN receive on CAN interface 1
GLOBALS: Copies the received message into the gFullCANList[] array
         Handles semaphore bits as described in LPC user manual
RETURNS: nothing
***************************************************************************/ 
void can_isr_tx1 (void) 
{
//unsigned int buf;
//unsigned int *pDest;
char temp;
//char *ptr,j;

//plazma_can2++;

can_tx_cnt++;

rotor_can[5]++;

if(ptr_can1_tx_wr!=ptr_can1_tx_rd)
	{
	LPC_CAN1->TFI1=can1_info[ptr_can1_tx_rd];
     LPC_CAN1->TID1=can1_id[ptr_can1_tx_rd];
     LPC_CAN1->TDA1=can1_data[ptr_can1_tx_rd];
     LPC_CAN1->TDB1=can1_datb[ptr_can1_tx_rd];
     LPC_CAN1->CMR=0x00000021;
     ptr_can1_tx_rd++;
     if(ptr_can1_tx_rd>=8)ptr_can1_tx_rd=0;
	}
else bOUT_FREE=1;
temp=LPC_CAN1->ICR;

}


/**************************************************************************
Initialization of a CAN interface
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short can1_init (unsigned int can_btr)
{
//unsigned int *pSFR; // pointer into SFR space
//unsigned int *pSFR2; // pointer into SFR space
//unsigned int offset; // offset added to pSFR
                                               
LPC_SC->PCONP |= (1<<13);  /* Enable CAN1 and CAN2 clock */

LPC_PINCON->PINSEL0 &= ~0x0000000F;  /* CAN1 is p0.0 and p0.1	*/
LPC_PINCON->PINSEL0 |= 0x00000005;

gCANFilter = 0; // Reset and disable all message filters

LPC_CANAF->AFMR = 0x00000001L; // Acceptance Filter Mode Register = off !

LPC_CAN1->MOD = 1; // Go into Reset mode

LPC_CAN1->IER = 0;// Disable All Interrupts

LPC_CAN1->GSR = 0; // Clear Status register

LPC_CAN1->BTR = can_btr; // Set bit timing

//LPC_CAN1->IER |=(1<<0)|(1<<1)|(1<<9)|(1<<10); // Enable Receive & Transmit Interrupt

LPC_CAN1->MOD = 0; // Enter Normal Operating Mode



NVIC_EnableIRQ(CAN_IRQn);
LPC_CAN1->IER =0x03;
return 1;
}

/**************************************************************************
Setting a CAN receive filter
as described in LPC_FullCAN_SW.h
***************************************************************************/ 
short FullCAN_SetFilter  (
                         unsigned short can_port, // CAN interface number
                         unsigned int CANID // 11-bit CAN ID
                         )
{
unsigned int p, n;
unsigned int buf0, buf1;
unsigned int ID_lower, ID_upper;
unsigned int candata;
unsigned int *pAddr;


// Acceptance Filter Mode Register = off !
LPC_CANAF->AFMR = 0x00000001L;

if (gCANFilter == 0)
     {    
     // First call, init entry zero
     gFullCANList[0].Dat1 = 0x000037FFL; // CAN 1, disabled and unused
     }
if (gCANFilter >= MAX_FILTERS)
     {
     return 0;
     }

CANID &= 0x000007FFL; // Mask out 11-bit ID
CANID |= (can_port << 13); // Put can_port info in bits 13-15

// Filters must be sorted by interface, then by priority
// new filter is sorted into array
p = 0;
while (p < gCANFilter) // loop through all existing filters 
     {
     if ((gFullCANList[p].Dat1 & 0x0000FFFFL) > CANID)
          {
          break;
          }
     p++;
     }

// insert new filter here
buf0 = gFullCANList[p].Dat1; // save current entry
gFullCANList[p].Dat1 = CANID; // insert the new entry

// move all remaining entries one row up
gCANFilter++;
while (p < gCANFilter)
     {
     p++;
     buf1 = gFullCANList[p].Dat1;
     gFullCANList[p].Dat1 = buf0;
     buf0 = buf1;
     }

// Now work on Acceptance Filter Configuration     
// Set CAN filter for 11-bit standard identifiers
p = 0;

// Set pointer for Standard Frame Individual
// Standard Frame Explicit
LPC_CANAF->SFF_sa = p;

pAddr = (unsigned int *) LPC_CANAF_RAM_BASE;
for (n = 0; n < ((gCANFilter+1)/2); n++)
     {
     ID_lower = gFullCANList[n * 2].Dat1 & 0x0000FFFFL;
     ID_upper = gFullCANList[n * 2 + 1].Dat1 & 0x0000FFFFL;
     candata = (ID_lower << 16) + ID_upper;
     *pAddr = candata;
     p += 4;
     pAddr++;
     }

// p is still pointing to ENDofTable;
  
// Set pointer for Standard Frame Groups
// Standard Frame Group Start Address Register
LPC_CANAF->SFF_GRP_sa = p;

// Set pointer for Extended Frame Individual
// Extended Frame Start Address Register
LPC_CANAF->EFF_sa = p;

// Set pointer for Extended Frame Groups
// Extended Frame Group Start Address Register
LPC_CANAF->EFF_GRP_sa = p;

// Set ENDofTable 
// End of AF Tables Register
LPC_CANAF->ENDofTable = p;

// Acceptance Filter Mode Register, start using filter
LPC_CANAF->AFMR = 0;
  
return 1;
}


//-----------------------------------------------
void CAN_IRQHandler(void)  
{
CANStatus = LPC_CAN1->ICR;
//plazma_can++;		
if ( CANStatus & (1 << 0) )
     {
	can_isr_rx1();
     }

if ( CANStatus & (1 << 1) )
     {
	can_isr_tx1();
     }

return;
}

//-----------------------------------------------
void can_isr_rx1 (void) 
{
unsigned int buf;
unsigned int *pDest;
//char temp;
char *ptr,j;

if (!(LPC_CAN1->RFS & 0xC0000400L))
     {
      
     pDest = (unsigned int *) &(gFullCANList[(LPC_CAN1->RFS & 0x000003FFL)].Dat1);
    
     // calculate contents for first entry into FullCAN list
     buf = LPC_CAN1->RFS & 0xC00F0000L; // mask FF, RTR and DLC
     buf |= 0x01002000L; // set semaphore to 01b and CAN port to 1
     buf |= LPC_CAN1->RID & 0x000007FFL; // get CAN message ID

     // now copy entire message to FullCAN list
     *pDest = buf; 
     pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatA
     *pDest = LPC_CAN1->RDA; 
     pDest++; // set to gFullCANList[(C1RFS & 0x000003FFL)].DatB
     *pDest = LPC_CAN1->RDB; 

     // now set the sempahore to complete
     buf |= 0x03000000L; // set semaphore to 11b
     pDest -= 2; // set to gFullCANList[(C1RFS & 0x000003FFL)].Dat1
     *pDest = buf; 
    
	//temp=(char)gFullCANList[0].DatA;
	//if(temp==0x30) bR=0;
	//else bR++;
	
	//temp=(char)(((gFullCANList[0].Dat1)>>16)&0x0f); 
     
     ptr=(char*)(&gFullCANList[0].DatA);
	
	//if(!bR)
		//{
		for(j=0;j<8;j++)
			{
			RXBUFF[j]=*ptr;
			ptr++;
			}
	//	}
	//else if(bR==1)
	//	{
	//	for(j=8;j<(temp+8);j++)
	//		{
	//		RXBUFF[j]=*ptr;
	//		ptr++;
	//		}                      
			
	//	} 		
	
	
	
		
	//temp=((RXBUFF[1]&0x1f)+4);

	///if((CRC1_in()==RXBUFF[temp+1])&&(CRC2_in()==RXBUFF[temp+2])&&bR)
	//	{
  
		bIN=1;
  		can_in_an();
          
		//}    
     }

LPC_CAN1->CMR = 0x04; // release receive buffer

}








