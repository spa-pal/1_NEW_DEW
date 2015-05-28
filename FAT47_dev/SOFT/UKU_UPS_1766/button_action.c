#include "button_action.h"
#include "button_drv.h"
#include "main.h"
#include "beeper_drv.h"
#include "control.h"
#include "25lc640.h"
#include "memo.h"
#include "eeprom_map.h"
#include "gran.h"
#include "led_break_drv.h"
//#include "avar_hndl.h"
#include "full_can.h"
#include "cmd.h"
#include "snmp_data_file.h"


#define UAKB_L 1500
#define UAKB_H 2100
signed short temp_SS;

void button_act(void)			 // описание воздействий кнопок L C R
{

//---------------------------------------------------------------
// Здесь описываем какие действия предпринимать при нажатии кнопок L L_ C C_ R R_ LR
//---------------------------------------------------------------
char i;
switch (butt_on) 
	{
	case butRL:	//////////////////////////////////////////////////////////////////////////////////			
		{
		if(level_U_mode!=flash&&level_I_mode!=flash&&level_Q_mode!=flash) // вход в калибровку
			{
			level_U_mode=flash;
			level_I_mode=norm;		
			level_Q_mode=norm;
			}
		else										// выход из калибровки
			{
			level_U_mode=norm;
			level_I_mode=norm;		
			level_Q_mode=norm;
			}
		};
		break;

	case butL:	//////////////////////////////////////////////////////////////////////////////////	
		{
			if(level_U_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(0*16)+4,(0*16)+4,0,0,0);
				}
			else if(level_I_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(2*16)+4,(2*16)+4,0,0,0);
				}
			else
				{
//				can1_out(NUMB,NUMB,KLBR,(3*16)+4,(3*16)+4,0,0,0);
				temp_SS-=5;
				gran(&temp_SS,UAKB_L,UAKB_H);
				lc640_write_int(EE_KUBAT1,temp_SS);
				}
		//flash_net_def_cnt=1000;
		};
		break;

	case butL_:	//////////////////////////////////////////////////////////////////////////////////	
		{
			if(level_U_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(0*16)+5,(0*16)+5,0,0,0);
				}
			else if(level_I_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(2*16)+5,(2*16)+5,0,0,0);
				}
			else
				{
//				can1_out(NUMB,NUMB,KLBR,(3*16)+5,(3*16)+5,0,0,0);
				temp_SS-=20;
				gran(&temp_SS,UAKB_L,UAKB_H);
				lc640_write_int(EE_KUBAT1,temp_SS);
				}
		};
		break;

	case butC:	/////////////////////////////////////////////////////////////////////////////////			
		{
		if(level_U_mode!=flash&&level_I_mode!=flash&&level_Q_mode!=flash)
			{							   // преключения м/у видами отображения
			if(level_U_mode==norm)
//				{
//				level_U_mode=reverse;
//				level_I_mode=reverse;		
//				level_Q_mode=reverse;
//				}
//			else if(level_U_mode==reverse)
				{
				level_U_mode=alone;
				level_I_mode=alone;		
				level_Q_mode=alone;
				}
			else
				{
				level_U_mode=norm;
				level_I_mode=norm;		
				level_Q_mode=norm;
				}			
			}
		else								// преключения м/у калибровками
			{
			if(level_U_mode==flash)
				{
				level_U_mode=norm;
				level_I_mode=flash;		
				level_Q_mode=norm;
				}
			else if(level_I_mode==flash)
				{
				level_U_mode=norm;
				level_I_mode=norm;		
				level_Q_mode=flash;
				temp_SS=lc640_read_int(EE_KUBAT1);
				}
			else
				{
				level_U_mode=flash;
				level_I_mode=norm;		
				level_Q_mode=norm;
				}
			}

		};
		break;

	case butC_:	/////////////////////////////////////////////////////////////////////////////////			
		{
		if(level_I_mode==flash)
			{
			can1_out(NUMB,NUMB,KLBR,(2*16)+1,(2*16)+1,0,0,0);
			beep(1,10,0,100,1);
			}
		else if(level_Q_mode==flash)
			{
			temp_SS=UAKB_L+UAKB_H/2-UAKB_L/2;
			lc640_write_int(EE_KUBAT1,temp_SS);
			beep(1,10,0,100,1);
			}
		};
		break;

	case butR:	//////////////////////////////////////////////////////////////////////////////////			
		{
			if(level_U_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(0*16)+2,(0*16)+2,0,0,0);
				}
			else if(level_I_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(2*16)+2,(2*16)+2,0,0,0);
				}
			else
				{
//				can1_out(NUMB,NUMB,KLBR,(3*16)+2,(3*16)+2,0,0,0);
				temp_SS+=5;
				gran(&temp_SS,UAKB_L,UAKB_H);
				lc640_write_int(EE_KUBAT1,temp_SS);
				}
		};
		break;

		case butR_:	//////////////////////////////////////////////////////////////////////////////			
			{
			if(level_U_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(0*16)+3,(0*16)+3,0,0,0);
				}
			else if(level_I_mode==flash)
				{
				can1_out(NUMB,NUMB,KLBR,(2*16)+3,(2*16)+3,0,0,0);
				}
			else
				{
//				can1_out(NUMB,NUMB,KLBR,(3*16)+3,(3*16)+3,0,0,0);
				temp_SS+=20;
				gran(&temp_SS,UAKB_L,UAKB_H);
				lc640_write_int(EE_KUBAT1,temp_SS);
				}
			};
		break;

		case butRLC_:	//////////////////////////////////////////////////////////////////////////////			
			{
/*			ETH_IP_1=192;
			ETH_IP_2=168;
			ETH_IP_3=1;
			ETH_IP_4=1;
			lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
			lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
			lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
			lc640_write_int(EE_ETH_IP_4,ETH_IP_4); 

			ETH_NET_MASK_1=255;
			ETH_NET_MASK_2=255;
			ETH_NET_MASK_3=255;
			ETH_NET_MASK_4=0;
			lc640_write_int(EE_ETH_NET_MASK_1,ETH_NET_MASK_1);
			lc640_write_int(EE_ETH_NET_MASK_2,ETH_NET_MASK_2);
			lc640_write_int(EE_ETH_NET_MASK_3,ETH_NET_MASK_3);
			lc640_write_int(EE_ETH_NET_MASK_4,ETH_NET_MASK_4);

			ETH_DEF_GATW_1=192;
			ETH_DEF_GATW_2=168;
			ETH_DEF_GATW_3=1;
			ETH_DEF_GATW_4=254;
			lc640_write_int(EE_ETH_DEF_GATW_1,ETH_DEF_GATW_1);
			lc640_write_int(EE_ETH_DEF_GATW_2,ETH_DEF_GATW_2);
			lc640_write_int(EE_ETH_DEF_GATW_3,ETH_DEF_GATW_3);
			lc640_write_int(EE_ETH_DEF_GATW_4,ETH_DEF_GATW_4);

			snmp_snmp_settings_read_community[0]='p';
			snmp_snmp_settings_read_community[1]='u';
			snmp_snmp_settings_read_community[2]='b';
			snmp_snmp_settings_read_community[3]='l';
			snmp_snmp_settings_read_community[4]='i';
			snmp_snmp_settings_read_community[5]='c';
			snmp_snmp_settings_read_community[6]=0;
			snmp_snmp_settings_read_community[7]=0;
			snmp_snmp_settings_read_community[8]=0;
			snmp_snmp_settings_read_community[9]=0;
			snmp_snmp_settings_read_community[10]=0;
			snmp_snmp_settings_read_community[11]=0;
			snmp_snmp_settings_read_community[12]=0;
			snmp_snmp_settings_read_community[13]=0;
			snmp_snmp_settings_read_community[14]=0;
			snmp_snmp_settings_read_community[15]=0;

			for(i=0;i<16;i++)
				{
				lc640_write(EE_SNMP_READ_COMMUNITY+i,snmp_snmp_settings_read_community[i]);
				}

			SNMP_READ_PORT=161;
			lc640_write_int(EE_SNMP_READ_PORT,SNMP_READ_PORT);
			SNMP_WRITE_PORT=162;
			lc640_write_int(EE_SNMP_WRITE_PORT,SNMP_WRITE_PORT); /**/

			//tcp_init_cnt=10;

			flash_net_def_cnt=1000;
			};
		break;

	}
butt_on=0;			// сброс кнопки после обработки

}


