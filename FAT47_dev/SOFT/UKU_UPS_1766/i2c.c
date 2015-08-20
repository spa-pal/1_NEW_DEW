#include "i2c.h"
#include "LPC17xx.H"
#include "main.h"

//-----------------------------------------------
void i2c_init(void)
{
/*
SET_REG(LPC_PINCON->PINSEL4,0,8*2,2);
SET_REG(LPC_PINCON->PINSEL4,0,9*2,2);
SET_REG(LPC_PINCON->PINMODE4,0,8*2,2);
SET_REG(LPC_PINCON->PINMODE4,0,9*2,2);

LPC_GPIO2->FIODIR&=~(1<<9);
LPC_GPIO2->FIOPIN&=~(1<<9);

LPC_GPIO2->FIODIR&=~(1<<8);
LPC_GPIO2->FIOPIN&=~(1<<8);
*/
SET_REG(LPC_PINCON->PINSEL0,0,11*2,2);
SET_REG(LPC_PINCON->PINSEL0,0,10*2,2);
SET_REG(LPC_PINCON->PINMODE0,0,11*2,2);
SET_REG(LPC_PINCON->PINMODE0,0,10*2,2);

LPC_GPIO0->FIODIR&=~(1<<10);
LPC_GPIO0->FIOPIN&=~(1<<10);

LPC_GPIO0->FIODIR&=~(1<<11);
LPC_GPIO0->FIOPIN&=~(1<<11);
}


//-----------------------------------------------
void i2c_Start(void)
{
SDA_LOW()
SCL_HIGH()
delay_us(2);
SCL_LOW()
delay_us(2);
return;
}

//-----------------------------------------------
void i2c_Restart(void)
{
SCL_LOW()                      
SDA_HIGH()                     
delay_us(2);
SCL_HIGH()
delay_us(2);
SDA_LOW()                      
delay_us(2);
return;
}    

//-----------------------------------------------
signed char i2c_ReadAcknowledge(void)
{
unsigned char ack;
SDA_HIGH()
SCL_LOW()
delay_us(1);
SCL_HIGH()                              
delay_us(1);		
if(SDA_PIN) ack = 1;
else ack = 0;
SCL_LOW()		
delay_us(1);
return	ack;				
}

//-----------------------------------------------
char i2c_ReadByte(void)
{
unsigned char i;
unsigned char byte = 0;
SDA_HIGH();
for(i=0; i<8; i++)
	{
	SCL_LOW()
	SDA_HIGH();		
	delay_us(1);
	SCL_HIGH();
	delay_us(1);
	byte = byte << 1;		 
	if(SDA_PIN) byte|=1;
	else byte&=0xfe;
	delay_us(1);
	SCL_LOW()
	}
return byte;
}

//-----------------------------------------------
void i2c_SendAcknowledge(unsigned char status)
{
SCL_LOW()
delay_us(3);
if(status&0x01)
	{
     SDA_LOW()                          
     }
else
	{
     SDA_HIGH()
	}
delay_us(1);
SCL_HIGH()			
delay_us(1);
SCL_LOW()
delay_us(1);
return;
}

//-----------------------------------------------
unsigned char i2c_SendByte(unsigned char byte)
{
signed char i;
SCL_LOW()
delay_us(1);


for(i=8; i>=1; i--)
	{
     if(byte&0x80)
         	{
         	SDA_HIGH()
         	}
     else
         	{
         	SDA_LOW()
         	}
     delay_us(1);
     byte<<=1;
     SCL_HIGH()
	delay_us(1);
	SCL_LOW()
	delay_us(1);
 	}

SDA_HIGH()
return 0;
}

//-----------------------------------------------
void i2c_Stop(void)
{
SDA_LOW()
delay_us(5);                      
SCL_HIGH()
delay_us(5);
SDA_HIGH()                     
delay_us(5);	
SDA_HIGH()
return;
}    

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
