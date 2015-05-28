#ifndef _MENU_NAVI_	 //читать, если файл ранее не считан

#define _MENU_NAVI_	  //установить, что файл прочитан


#define MAX_MAIN_MENU 19			  //кол-во строк в каждом меню
//---меню П5---
#define MAX_P5_MENU MAX_MAIN_MENU+7
//---меню П6---
#define MAX_P6_MENU MAX_P5_MENU+7
//---меню П7---
#define MAX_P7_MENU MAX_P6_MENU+7
//---меню П8---
#define MAX_P8_MENU MAX_P7_MENU+4
//---меню П9---
#define MAX_P9_MENU MAX_P8_MENU+4
//---меню П10---
#define MAX_P10_MENU MAX_P9_MENU+10
//---меню П11---
#define MAX_P11_MENU MAX_P10_MENU+4
//---меню П12---
#define MAX_P12_MENU MAX_P11_MENU+6
//---меню П13---
#define MAX_P13_MENU MAX_P12_MENU+6
//---меню П14---
#define MAX_P14_MENU MAX_P13_MENU+37
//---меню П15---
#define MAX_P15_MENU MAX_P14_MENU+6
//---меню П16---
#define MAX_P16_MENU MAX_P15_MENU+0
//---меню П17---
#define MAX_P17_MENU MAX_P16_MENU+8
//---меню П18---
#define MAX_P18_MENU MAX_P17_MENU+8
//---меню П19---
#define MAX_P19_MENU MAX_P18_MENU+22
//-----------------------------------
//---меню П13-П2---	126
#define MAX_P13_P2_MENU MAX_P19_MENU+4
//---меню П13-П3---
#define MAX_P13_P3_MENU MAX_P13_P2_MENU+7
//---меню П13-П4---	 125
#define MAX_P13_P4_MENU MAX_P13_P3_MENU+4
//---меню П13-П5---  125
#define MAX_P13_P5_MENU MAX_P13_P4_MENU+4
//-----------------------------------
//---меню П14-П2---
#define MAX_P14_P2_MENU MAX_P13_P5_MENU+4
//---меню П14-П3---
#define MAX_P14_P3_MENU MAX_P14_P2_MENU+4
//---меню П14-П4---
#define MAX_P14_P4_MENU MAX_P14_P3_MENU+4
//---меню П14-П5---
#define MAX_P14_P5_MENU MAX_P14_P4_MENU+9
//---меню П14-П11---
#define MAX_P14_P11_MENU MAX_P14_P5_MENU+5
//---меню П14-П32--- 
#define MAX_P14_P32_MENU MAX_P14_P11_MENU+5
//---меню П14-П38---  873
#define MAX_P14_P38_MENU MAX_P14_P32_MENU+5
//-----------------------------------
//---меню П19-П17---
#define MAX_P19_P17_MENU MAX_P14_P38_MENU+5
//---меню П19-П18---  
#define MAX_P19_P18_MENU MAX_P19_P17_MENU+5
//---меню П19-П19---  
#define MAX_P19_P19_MENU MAX_P19_P18_MENU+5


//--------------------------------

extern char lcdPointer, capt;

extern char* mainMenu[];
//--------мнимые названия меню предопределяющие в программе навигацию по меню 
typedef enum {mainMnu,P4menu,P5menu,P6menu,P7menu,P8menu,P9menu,P10menu,P11menu,P12menu,P13menu,P14menu,P15menu,P14P3menu,} menu_enum;
extern menu_enum menu;

extern char startString,endString;
extern int 	menuPointer;
extern void menuNavi(void);

void writeLCD_buffer (void);

#endif

