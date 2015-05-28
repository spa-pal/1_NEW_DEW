#include "beeper_drv.h"
#include "main.h"
#include "LPC17xx.H"

/*
периодицность отсчета, т.е. периодичность опросов 1= 10мс 100Гц
1с=100отс
формат:
beep(2,20,50,100,30)
beep(кол-во в пачке,длительность одного,пауза в пачке,задержка после пачки, длит в сек всей команды)
*/
char quantity,restart=0,count_q,single;
signed short duration,pause,delay,timer_b;
signed short count_b,count_t;

void beep(char q,signed short d,signed short p,signed short dl,char t)
{
if (q!=quantity||d!=duration||p!=pause||dl!=delay)//если новая команда, обновить данные и рестарт
	{
	quantity=q;
	duration=d;
	pause=p;
	delay=dl;
	timer_b=t*100;
	restart=1;
	}
}

void beeper (void)
{
	INIT_BP;						   //инициализация порта
	if (restart)					   //при новой команде сброс всех счетчиков
		{
		BEEPER_OFF;
		count_q=1;
		count_b=0;
		count_t=0;
		restart=0;
		}
	else if (quantity)				  // команда не пустая
		{
		if (count_b<duration)
			{
			BEEPER_ON;					//вкл звук на время длит
			++count_b;
			}		    
		else if(count_q<quantity)		  //если пачка из более чем 1
			{
			if(count_b<(duration+pause))
				{
				BEEPER_OFF; //выкл звук на время паузы
				++count_b;
				}
			else
				{
				count_b=0;			 	//на повтор
				++count_q;
				}					
			}
		else if(count_b<(duration+delay))
			{
			BEEPER_OFF;						//выкл звук	на время задержки м/у пачками
			++count_b;
			}
		else
			{
			count_b=0;			 	//на повтор всей пачки
			count_q=1;
			}					
		
		if(timer_b)
			{
			if(count_t++==timer_b) beep (0,0,0,0,0);
			}
		}
}
