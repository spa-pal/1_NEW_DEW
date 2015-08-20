/*
#define SCL_HIGH() 	LPC_GPIO2->FIODIR&=~(1<<8);LPC_GPIO2->FIOPIN&=~(1<<8);
#define SCL_LOW()  	LPC_GPIO2->FIODIR|=(1<<8);LPC_GPIO2->FIOPIN&=~(1<<8);
#define SCL_PIN 	(LPC_GPIO2->FIOPIN)&(1<<8)

#define SDA_HIGH() 	LPC_GPIO2->FIODIR&=~(1<<9);LPC_GPIO2->FIOPIN|=(1<<9);
#define SDA_LOW()  	LPC_GPIO2->FIODIR|=(1<<9);LPC_GPIO2->FIOPIN&=~(1<<9);
#define SDA_PIN 	(LPC_GPIO2->FIOPIN)&(1<<9) 
*/

#define SCL_HIGH() 	LPC_GPIO0->FIODIR&=~(1<<11);LPC_GPIO0->FIOPIN&=~(1<<11);
#define SCL_LOW()  	LPC_GPIO0->FIODIR|=(1<<11);LPC_GPIO0->FIOPIN&=~(1<<11);
#define SCL_PIN 	(LPC_GPIO0->FIOPIN)&(1<<11)

#define SDA_HIGH() 	LPC_GPIO0->FIODIR&=~(1<<10);LPC_GPIO0->FIOPIN|=(1<<10);
#define SDA_LOW()  	LPC_GPIO0->FIODIR|=(1<<10);LPC_GPIO0->FIOPIN&=~(1<<10);
#define SDA_PIN 	(LPC_GPIO0->FIOPIN)&(1<<10)
//-----------------------------------------------
void i2c_init(void);
//-----------------------------------------------
void i2c_Start(void);
//-----------------------------------------------
void i2c_Restart(void);
//-----------------------------------------------
signed char i2c_ReadAcknowledge(void);
//-----------------------------------------------
char i2c_ReadByte(void);
//-----------------------------------------------
void i2c_SendAcknowledge(unsigned char status);
//-----------------------------------------------
unsigned char i2c_SendByte(unsigned char byte);
//-----------------------------------------------
void i2c_Stop(void);



/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/







