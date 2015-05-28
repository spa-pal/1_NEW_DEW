#include "button_drv.h"
#include "main.h"
#include "LPC17xx.H"

unsigned long but=0;
char but_acc=butOFF,but_i=0,but_ii=0,LP,butt_on;

void button_on(void)
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

//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();
//__nop();

but=LPC_GPIO1->FIOPIN&(7<<BUT0);	  // читаем 3 бита с порта
//but=LPC_GPIO1->FIOPIN|(~(1UL<<BUT0))&(~(1UL<<BUT1))&(~(1UL<<BUT2))&(~(1UL<<BUT3))&(~(1UL<<BUT4));

but>>=BUT0;		// преобразуем в удобный вид

if(but!=butOFF|but_i!=0)			// если какую-либо из кнопок нажали либо уже была недавно нажата
	{						
	//if (but_i==0) but_acc=but; 	//при первом вызове запоминаем нажатую кнопку
	but_i++;
	if (but_i>=10)				   // ждем 100 мс на дребезг затем ждем когда кнопка отожмется 
		{
		if (but_i==10) but_acc=but;		   // после выдержки на дребезг запоминаем нажатую кнопку
		if (but==butOFF|but_ii!=0)		   // зафиксировали отжатие кнопки либо была уже отжта недавно
			{
			if (but_ii==0)				  // при первом вызове 
				{
				if(!LP) butt_on=but_acc;  // фиксируем что было короткое нажатие? если не было длинного нажатия
				but_ii=but_i;			  // начинаем отсчет 100 мс на дребезг
				}
			if (but_i>=but_ii+10)		  // выждали 100 мс на дребезг
				{
				but_i=0;				  //выход 
				but_ii=0;
				LP=0;
				}
			}
		else if (but_i>=50)				// время одижания превысило 500мс
			{
				butt_on=but_acc+LongPush;	 // фиксируем длинное нажатие
				but_i=11;
				LP=1;				   		 // установка флага на длинное нажание
			}
		}
	}






}




