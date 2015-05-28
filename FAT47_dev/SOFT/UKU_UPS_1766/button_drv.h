#ifndef _BUTTON_DRV_	 //читать, если файл ранее не считан

#define _BUTTON_DRV_	  //установить, что файл прочитан

					  // назначение кнопок пинам
//-------port0
#define BUT0	24	 //R
#define BUT1	25	 //C
#define BUT2	26	 //L


#define BUT_MASK (1UL<<BUT0)|(1UL<<BUT1)|(1UL<<BUT2)

#define BUT_ON 4
#define BUT_ONL 20 
#define LongPush 50

				  // при чтении с порта получаем след значения для кнопок
//#define	butOFF 7
//#define butR   6
//#define butR_  butR+LongPush
//#define butL   3
//#define butL_  butL+LongPush
//#define butC   5
//#define butC_  butC+LongPush
//#define butRL  2
//#define butRL_ butRL+LongPush
//#define butRLC  	0
//#define butRLC_ 	butRLC+LongPush

extern char butt_on;

void button_on(void);

#endif


