#include "led_break_drv.h"
#include "main.h"
#include "LPC17xx.H"

/*
периодицность отсчета, т.е. периодичность опросов 1= 10мс 100Гц
1с=100отс
формат	blink(2,20,50,100)
		blink(кол-во в пачке,длительность одного,пауза в пачке,задержка после пачки)
*/
char b_quantity,b_restart=0,b_count_q;
signed short b_duration,b_pause,b_delay;
signed short b_count_b;

void blink(char q,signed short d,signed short p,signed short dl)
{
if (q!=b_quantity||d!=b_duration||p!=b_pause||dl!=b_delay)//если новая команда, обновить данные и рестарт
	{
	b_quantity=q;
	b_duration=d;
	b_pause=p;
	b_delay=dl;
	b_restart=1;
	}
}

void blinker (void)
{
	INIT_LED;						   //инициализация порта
	if (b_restart)					   //при новой команде сброс всех счетчиков
		{
		LED_OFF;
		b_count_q=1;
		b_count_b=0;
		b_restart=0;
		}
	else if (b_quantity)				  // команда не пустая
		{
		if (b_count_b<b_duration)
			{
			LED_ON;					//вкл звук на время длит
			++b_count_b;
			}		    
		else if(b_count_q<b_quantity)		  //если пачка из более чем 1
			{
			if(b_count_b<(b_duration+b_pause))
				{
				LED_OFF; //выкл звук на время паузы
				++b_count_b;
				}
			else
				{
				b_count_b=0;			 	//на повтор
				++b_count_q;
				}					
			}
		else if(b_count_b<(b_duration+b_delay))
			{
			LED_OFF;						//выкл звук	на время задержки м/у пачками
			++b_count_b;
			}
		else
			{
			b_count_b=0;			 	//на повтор всей пачки
			b_count_q=1;
			}					
		}
}
