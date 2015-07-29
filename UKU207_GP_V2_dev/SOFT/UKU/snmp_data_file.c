#include "snmp_data_file.h" 
#include "eeprom_map.h"
#include "main.h"
#include "net_config.h"
//#include "main.h"
#include "control.h"
#include "LPC17xx.H"
#include <string.h>
#include "25lc640.h"
#include "common_func.h"

char snmp_community[10];

//Информация об устройстве
//signed short snmp_device_code;
//signed 	   snmp_sernum;
//signed short snmp_sernum_lsb;
//signed short snmp_sernum_msb;
//char 	   snmp_location[100];
//signed short snmp_numofbat;
signed short snmp_num_of_psu;
signed short snmp_max_time_of_process;
signed short snmp_time_visualisation;
signed short snmp_pult_time_mode; 		
signed short snmp_load_current_measure_mode;	
signed short snmp_main_menu_mode;
signed short snmp_restart_enabled;
signed short snmp_modbus_adress;
signed long snmp_modbus_baudrate;	

//signed short snmp_numofinv;
//signed short snmp_numofavt;
//signed short snmp_numofdt;
//signed short snmp_numofsk;
//signed short snmp_numofevents;

//Рабочие параметры
signed short snmp_U_up;  	
signed short snmp_I_ug; 	
signed short snmp_U_maxg;  	
signed short snmp_I_maxp; 	
signed long snmp_time_p;  	
signed long snmp_time_g;	

// Параметры реверса
signed short snmp_reverse_state;
signed short snmp_avtoreverse_enable;
signed short snmp_avtoreverse_ff_time;
signed short snmp_avtoreverse_rew_time;
signed short snmp_avtoreverse_pause_time; 
signed short snmp_avtoreverse_ff_i;
signed short snmp_avtoreverse_rew_i;
signed short snmp_avtoreverse_ff_u;
signed short snmp_avtoreverse_rew_u;

//Состояние первичной сети
signed short snmp_mains_power_voltage;
signed short snmp_mains_power_frequency;
signed short snmp_mains_power_status;
signed short snmp_mains_power_alarm;

//Состояние выхода
signed short snmp_out_voltage;
signed short snmp_out_current;

//Состояние БПСов
signed short snmp_bps_number[8];
signed short snmp_bps_voltage[8];
signed short snmp_bps_current[8];
signed short snmp_bps_temperature[8];
signed short snmp_bps_stat[8];

//Состояние инверторов
signed short snmp_inv_number[3];
signed short snmp_inv_voltage[3];
signed short snmp_inv_current[3];
signed short snmp_inv_temperature[3];
signed short snmp_inv_stat[3];



//Спецфункции
signed short snmp_spc_stat;
char snmp_spc_trap_message[100];
signed short snmp_spc_trap_value_0,snmp_spc_trap_value_1,snmp_spc_trap_value_2;

//Состояние автоматов
signed char snmp_avt_number[12];
signed char snmp_avt_stat[12];

//Состояние силовых вводов
signed short snmp_energy_vvod_phase_a;
signed short snmp_energy_vvod_phase_b;
signed short snmp_energy_vvod_phase_c;
signed short snmp_energy_pes_phase_a;
signed short snmp_energy_pes_phase_b;
signed short snmp_energy_pes_phase_c;

//Показания счетчика
signed long snmp_energy_total_energy;
signed short snmp_energy_current_energy;


//Команды
signed short snmp_command;
signed short snmp_command_parametr;

//Журнал аварий
char snmp_log[64][128]=
				{
				"01@abcd@efgh@ijkl@01@        ",
				"02@abcd@efgh@ijkl@02@        ",
				"03@abcd@efgh@ijkl@03@        ",
				"04@abcd@efgh@ijkl@04@        ",
				"05@abcd@efgh@ijkl@05@        ",
				"06@abcd@efgh@ijkl@06@        ",
				"07@abcd@efgh@ijkl@07@        ",
				"08@abcd@efgh@ijkl@08@        ",
				"09@abcd@efgh@ijkl@09@        ",
				"10@abcd@efgh@ijkl@10@        ",
				"11@abcd@efgh@ijkl@11@        ",
				"12@abcd@efgh@ijkl@12@        ",
				"13@abcd@efgh@ijkl@13@        ",
				"14@abcd@efgh@ijkl@14@        ",
				"15@abcd@efgh@ijkl@15@        ",
				"16@abcd@efgh@ijkl@16@        ",
				"17@abcd@efgh@ijkl@17@        ",
				"18@abcd@efgh@ijkl@18@        ",
				"19@abcd@efgh@ijkl@19@        ",
				"20@abcd@efgh@ijkl@20@        ",
				"21@abcd@efgh@ijkl@21@        ",
				"22@abcd@efgh@ijkl@22@        ",
				"23@abcd@efgh@ijkl@23@        ",
				"24@abcd@efgh@ijkl@24@        ",
				"25@abcd@efgh@ijkl@25@        ",
				"26@abcd@efgh@ijkl@26@        ",
				"27@abcd@efgh@ijkl@27@        ",
				"28@abcd@efgh@ijkl@28@        ",
				"29@abcd@efgh@ijkl@29@        ",
				"30@abcd@efgh@ijkl@30@        "
				};

//Установочные параметры
signed short snmp_main_bps;
signed short snmp_zv_en;
signed short snmp_alarm_auto_disable;
signed short snmp_bat_test_time;
signed short snmp_u_max;
signed short snmp_u_0_grad;
signed short snmp_u_20_grad;
signed short snmp_u_sign;
signed short snmp_u_min_power;
signed short snmp_u_withouth_bat;
signed short snmp_control_current;
signed short snmp_max_charge_current;
signed short snmp_max_current;
signed short snmp_max_current_koef;
signed short snmp_max_current_koef;
signed short snmp_up_charge_koef;
signed short snmp_powerup_psu_timeout;
signed short snmp_max_temperature;


U16 obj[10];
U8 temp_ip[4];
char snmp_trap_send_i,snmp_trap_send_ii;

//-----------------------------------------------
void snmp_data (void) 
{
char i;

snmp_mains_power_voltage=net_U;
snmp_mains_power_frequency=net_F;/*
snmp_mains_power_status=0; 
#if(UKU_VERSION==900)
snmp_mains_power_status=2;
#endif
if(St&0x01)snmp_mains_power_status|=0x01;
if(St&0x01)snmp_mains_power_alarm=1;





for(i=0;i<snmp_numofevents;i++)event2snmp(i);
//snmp_bpsnumber[0]=1;
//snmp_bpsnumber[1]=2;

snmp_sernum=AUSW_MAIN_NUMBER;
snmp_sernum_lsb=0x1122;
snmp_sernum_msb=0x3344;
snmp_device_code=AUSW_MAIN;

//memcpy(snmp_location,"lkhg;la",);


snmp_numofbat=1;

*/

/**/
snmp_out_voltage=load_U;
snmp_out_current=load_I;
/**/

//snmp_numofbat=NUMBAT;
snmp_num_of_psu=NUMIST;
snmp_max_time_of_process=T_PROC_MAX/60;
snmp_time_visualisation=TIME_VISION;
snmp_pult_time_mode=TIME_VISION_PULT;
snmp_load_current_measure_mode=I_LOAD_MODE;	
snmp_main_menu_mode=main_menu_mode;
if(restart_enable==reON) snmp_restart_enabled=1;
else snmp_restart_enabled=0; 
snmp_modbus_adress=MODBUS_ADRESS;
snmp_modbus_baudrate=MODBUS_BAUDRATE*10U;

//snmp_numofavt=NUMAVT;
//snmp_numofdt=NUMDT;
//snmp_numofsk=NUMSK;
//snmp_numofevents=lc640_read_int(CNT_EVENT_LOG);

snmp_energy_vvod_phase_a=Uvv_eb2[0];
snmp_energy_vvod_phase_b=Uvv_eb2[1];
snmp_energy_vvod_phase_c=Uvv_eb2[2];
snmp_energy_pes_phase_a=Upes_eb2[0];
snmp_energy_pes_phase_b=Upes_eb2[1];
snmp_energy_pes_phase_c=Upes_eb2[2];

snmp_energy_total_energy=power_summary;
snmp_energy_current_energy=power_current;




snmp_bps_number[0]=1;
snmp_bps_voltage[0]=bps[0]._Uii;
snmp_bps_current[0]=bps[0]._Ii;
snmp_bps_temperature[0]=bps[0]._Ti;
snmp_bps_stat[0]=bps[0]._av;												//Байт состояния БПСа.

/*if(St_[0]&(1<<2))snmp_bps_stat[0]=(1<<3); 							//авария по Umin
else if(St_[0]&(1<<3))snmp_bps_stat[0]=(1<<2); 						//авария по Umax
else if(bps[0]._av&(1<<0))snmp_bps_stat[0]=(1<<1); 						//авария по Tmax
else if(St_[0]&(1<<5))snmp_bps_stat[0]=(1<<5); 						//заблокирован
else if((!(St_[0]&0x3c))&&(!St&0x01)&&(!OFFBP1))snmp_bps_stat[0]=1; 		//Работает
*/

snmp_bps_number[1]=2;
snmp_bps_voltage[1]=bps[1]._Uii;
snmp_bps_current[1]=bps[1]._Ii;
snmp_bps_temperature[1]=bps[1]._Ti;
snmp_bps_stat[1]=bps[1]._av;
												//Байт состояния БПСа.
/*if(St_[1]&(1<<2))snmp_bps_stat[1]=(1<<3); 							//авария по Umin
else if(St_[1]&(1<<3))snmp_bps_stat[1]=(1<<2); 						//авария по Umax
else if(St_[1]&(1<<4))snmp_bps_stat[1]=(1<<1); 						//авария по Tmax
else if(St_[1]&(1<<5))snmp_bps_stat[1]=(1<<5); 						//заблокирован
else if((!(St_[1]&0x3c))&&(!St&0x01)&&(!OFFBP2))snmp_bps_stat[1]=1; 		//Работает
*/

snmp_bps_number[2]=3;
snmp_bps_voltage[2]=bps[2]._Uii;
snmp_bps_current[2]=bps[2]._Ii;
snmp_bps_temperature[2]=bps[2]._Ti;
snmp_bps_stat[2]=bps[2]._av;

snmp_bps_number[3]=4;
snmp_bps_voltage[3]=bps[3]._Uii;
snmp_bps_current[3]=bps[3]._Ii;
snmp_bps_temperature[3]=bps[3]._Ti;
snmp_bps_stat[3]=bps[3]._av;

snmp_bps_number[4]=5;
snmp_bps_voltage[4]=bps[4]._Uii;
snmp_bps_current[4]=bps[4]._Ii;
snmp_bps_temperature[4]=bps[4]._Ti;
snmp_bps_stat[4]=bps[4]._av;

snmp_bps_number[5]=6;
snmp_bps_voltage[5]=bps[5]._Uii;
snmp_bps_current[5]=bps[5]._Ii;
snmp_bps_temperature[5]=bps[5]._Ti;
snmp_bps_stat[5]=bps[5]._av;

snmp_bps_number[6]=7;
snmp_bps_voltage[6]=bps[6]._Uii;
snmp_bps_current[6]=bps[6]._Ii;
snmp_bps_temperature[6]=bps[6]._Ti;
snmp_bps_stat[6]=bps[6]._av;

snmp_bps_number[7]=8;
snmp_bps_voltage[7]=bps[7]._Uii;
snmp_bps_current[7]=bps[7]._Ii;
snmp_bps_temperature[7]=bps[7]._Ti;
snmp_bps_stat[7]=bps[7]._av;



snmp_U_up=U_up;  	
snmp_I_ug=I_ug; 	
snmp_U_maxg=U_maxg;  	
snmp_I_maxp=I_maxp; 	
if(T_PROC_PS_MODE==1)snmp_time_p=0L;
else snmp_time_p=T_PROC_PS;  	
if(T_PROC_GS_MODE==1)snmp_time_g=0L;
else snmp_time_g=T_PROC_GS;


if(REV_STAT) snmp_reverse_state=0;
else snmp_reverse_state=1;
if(AVT_REV_IS_ON)snmp_avtoreverse_enable=1;
else snmp_avtoreverse_enable=0;
snmp_avtoreverse_ff_time=AVT_REV_TIME_FF;
snmp_avtoreverse_rew_time=AVT_REV_TIME_REW;
snmp_avtoreverse_pause_time=AVT_REV_TIME_PAUSE;
snmp_avtoreverse_ff_i=AVT_REV_I_NOM_FF;  	
snmp_avtoreverse_rew_i=AVT_REV_I_NOM_REW; 	
snmp_avtoreverse_ff_u=AVT_REV_U_NOM_FF; 	
snmp_avtoreverse_rew_u=AVT_REV_U_NOM_REW;  	



/*
snmp_bat_voltage=Ubat;
snmp_bat_current=Ibat;
snmp_bat_temperature=t_b;
if(BAT_C_REAL==0x5555)
	{
	snmp_bat_capacity=BAT_C_NOM*10;												    11
	}
else
	{
	snmp_bat_capacity=BAT_C_REAL;
	}
snmp_bat_charge=zar_percent;
snmp_bat_status=0;
if(St&0x02)snmp_bat_status|=0x01;
if(Ibat>0)snmp_bat_status|=0x02;


if(spc_stat==spc_OFF) snmp_spc_stat=0;
else if(spc_stat==spc_KE) snmp_spc_stat=1;
else if(spc_stat==spc_VZ) snmp_spc_stat=10;


snmp_main_bps=MAIN_IST+1;
snmp_zv_en=ZV_ON;
snmp_alarm_auto_disable=AV_OFF_AVT;
snmp_bat_test_time=TBAT;
snmp_u_max=UMAX;
snmp_u_0_grad=UB0;
snmp_u_20_grad=UB20;
snmp_u_sign=USIGN;
snmp_u_min_power=UMN;
snmp_u_withouth_bat=U0B;
snmp_control_current=IKB;
snmp_max_charge_current=IZMAX;
snmp_max_current=IMAX;
snmp_max_current_koef=KIMAX;
snmp_up_charge_koef=KVZ;
snmp_powerup_psu_timeout=TZAS;
snmp_max_temperature=TMAX;*/

for(i=0;i<12;i++)
	{
	snmp_avt_number[i]=i+1;
	if(avt_stat[i]==avtOFF)snmp_avt_stat[i]=0;
	else snmp_avt_stat[i]=1;
	}
}

//-----------------------------------------------
void snmp_sernum_write (int mode) 
{
if(mode==MIB_WRITE)
	{
//	lc640_write_long(EE_AUSW_MAIN_NUMBER,snmp_sernum);
	//lc640_write_long(EE_AUSW_UKU_NUMBER,snmp_sernum);
	}
}

//-----------------------------------------------
void snmp_location_write (int mode) 
{
/*char i;
if(mode==MIB_WRITE)
	{
	for(i=0;i<64;i++)
		{
		lc640_write(EE_LOCATION+i,snmp_location[i]);
		}
	}*/
}

//-----------------------------------------------
void snmp_num_of_psu_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_NUMIST,snmp_num_of_psu);
	}
}

//-----------------------------------------------
void snmp_max_time_of_process_write(int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_T_PROC_MAX,snmp_max_time_of_process*60);
	}
}

//-----------------------------------------------
void snmp_time_visualisation_write(int mode) 
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_TIME_VISION,snmp_time_visualisation);
	}
}

//-----------------------------------------------
void snmp_pult_time_mode_write(int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_TIME_VISION_PULT,snmp_pult_time_mode);
	}
}  	
//-----------------------------------------------
void snmp_load_current_measure_mode_write(int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_I_LOAD_MODE,snmp_load_current_measure_mode);
	}
}
//-----------------------------------------------
void snmp_main_menu_mode_write(int mode)
{
if(mode==MIB_WRITE)
	{
	if((snmp_main_menu_mode>=0)&&(snmp_main_menu_mode<=3))lc640_write_int(EE_MAIN_MENU_MODE,snmp_main_menu_mode);
	}
}

//-----------------------------------------------
void snmp_restart_enabled_write(int mode)
{
if(mode==MIB_WRITE)
	{
	if(snmp_restart_enabled=1)lc640_write_int(EE_RESTART_ENABLED,reON);
	else lc640_write_int(EE_RESTART_ENABLED,reOFF);
	}
}

//-----------------------------------------------
void snmp_modbus_adress_write(int mode)
{
if(mode==MIB_WRITE)
	{
	if((snmp_modbus_adress>=1)&&(snmp_modbus_adress<=254))lc640_write_int(EE_MODBUS_ADRESS,snmp_modbus_adress);
	}
}

//-----------------------------------------------
void snmp_modbus_baudrate_write(int mode)
{
if(mode==MIB_WRITE)
	{
	if((snmp_modbus_adress>=1200)&&(snmp_modbus_adress<=57600))lc640_write_int(EE_MODBUS_BAUDRATE,(signed short)snmp_modbus_baudrate/10);
	}
}

//-----------------------------------------------
void snmp_U_up_write(int mode)
{
if(mode==MIB_WRITE)
	{
	gran(&snmp_U_up,U_MIN,U_MAX);
	lc640_write_int(EE_U_UP,snmp_U_up);
	}
}
//-----------------------------------------------
void snmp_I_ug_write(int mode)
{
if(mode==MIB_WRITE)
	{
	gran(&snmp_I_ug,I_MIN_IPS,I_MAX_IPS);
	lc640_write_int(EE_I_UG,snmp_I_ug);	
	}
}


//-----------------------------------------------
void snmp_U_maxg_write(int mode)
{
if(mode==MIB_WRITE)
	{
	gran(&snmp_U_maxg,U_MIN,U_MAX);
	lc640_write_int(EE_U_MAX_G,snmp_U_maxg);
	}
}
//-----------------------------------------------
void snmp_I_maxp_write(int mode)
{
if(mode==MIB_WRITE)
	{
	gran(&snmp_I_maxp,I_MIN_IPS,I_MAX_IPS);
	lc640_write_int(EE_I_MAX_P,snmp_I_maxp);
	}
}
//-----------------------------------------------
void snmp_time_p_write(int mode)
{
if(mode==MIB_WRITE)
	{
	if(snmp_time_p<=0)
		{
		lc640_write_int(EE_T_PROC_PS_MODE,1);
		lc640_write_int(EE_T_PROC_PS,0);
		}
	else 
		{
		if(snmp_time_p>T_PROC_MAX)snmp_time_p=T_PROC_MAX;
		lc640_write_int(EE_T_PROC_PS,snmp_time_p);
		}
	}
}
//-----------------------------------------------
void snmp_time_g_write(int mode)  	
{
if(mode==MIB_WRITE)
	{
	if(snmp_time_g<=0)
		{
		lc640_write_int(EE_T_PROC_GS_MODE,1);
		lc640_write_int(EE_T_PROC_GS,0);
		}
	else 
		{
		if(snmp_time_g>T_PROC_MAX)snmp_time_g=T_PROC_MAX;
		lc640_write_int(EE_T_PROC_GS,snmp_time_g);
		}
	}
}



//-----------------------------------------------
void snmp_zv_on_write (int mode)
{
if(mode==MIB_WRITE)
	{
//	lc640_write_int(EE_ZV_ON,snmp_zv_en);
	}
}

//-----------------------------------------------
void snmp_alarm_auto_disable_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_AV_OFF_AVT,snmp_alarm_auto_disable);
	}
}

//-----------------------------------------------
void snmp_bat_test_time_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_TBAT,snmp_bat_test_time);
	}
}

//-----------------------------------------------
void snmp_u_max_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_UMAX,snmp_u_max);
	}
}

//-----------------------------------------------
void snmp_u_0_grad_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_UB0,snmp_u_0_grad);
	}
}
//-----------------------------------------------
void snmp_u_20_grad_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_UB20,snmp_u_20_grad);
	}
}

//-----------------------------------------------
void snmp_u_sign_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_USIGN,snmp_u_sign);
	}
}
//-----------------------------------------------
void snmp_u_min_power_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_UMN,snmp_u_min_power);
	}
}
//-----------------------------------------------
void snmp_u_withouth_bat_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_U0B,snmp_u_withouth_bat);
	}
}

//-----------------------------------------------
void snmp_control_current_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_IKB,snmp_control_current);
	}
}

//-----------------------------------------------
void snmp_max_charge_current_write (int mode)
{
if(mode==MIB_WRITE)
	{
//     lc640_write_int(EE_IZMAX,snmp_max_charge_current);
	}
}

//-----------------------------------------------
void snmp_max_current_write (int mode)
{
if(mode==MIB_WRITE)
	{
     lc640_write_int(EE_IMAX,snmp_max_current);
	}
}

//-----------------------------------------------
void snmp_max_current_koef_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_KIMAX,snmp_max_current_koef);
	}
}

//-----------------------------------------------
void snmp_up_charge_koef_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_KVZ,snmp_up_charge_koef);
	}
}

//-----------------------------------------------
void snmp_powerup_psu_timeout_write (int mode)
{
if(mode==MIB_WRITE)
	{
     lc640_write_int(EE_TZAS,snmp_powerup_psu_timeout);
	}
}

//-----------------------------------------------
void snmp_max_temperature_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_TMAX,snmp_max_temperature);
	}
}

//-----------------------------------------------
void snmp_reverse_state_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_KVZ,snmp_up_charge_koef);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_enable_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_IS_ON,snmp_avtoreverse_enable);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_ff_time_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_TIME_FF,snmp_avtoreverse_ff_time);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_rew_time_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_TIME_REW,snmp_avtoreverse_rew_time);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_pause_time_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_TIME_PAUSE,snmp_avtoreverse_pause_time);	
	}
}

//-----------------------------------------------
void snmp_avtoreverse_ff_i_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_I_NOM_FF,snmp_avtoreverse_ff_i);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_rew_i_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_I_NOM_REW,snmp_avtoreverse_rew_i);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_ff_u_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_U_NOM_FF,snmp_avtoreverse_ff_u);
	}
}

//-----------------------------------------------
void snmp_avtoreverse_rew_u_write(int mode)
{
if(mode==MIB_WRITE)
	{
 	lc640_write_int(EE_AVT_REV_U_NOM_REW,snmp_avtoreverse_rew_u);
	}
}

//-----------------------------------------------
void snmp_command_execute (int mode)
{
if(mode==MIB_WRITE)
	{
	
	//snmp_command=0x5555;

	switch (snmp_command)
		{
		case SNMP_BPS_DISABLE:
			{
			snmp_command=COMMAND_OK;

		/*	switch (snmp_command_parametr)
				{
			
				case 1: 
				{
				St_[0]|=0x20;
				St_[1]&=0xdf;
				St&=0xfb;
				cnt_src[1]=10;
				snmp_plazma++;
				snmp_plazma++;
				break;
				}
			
				case 2:
				{
				St_[1]|=0x20;
				St_[0]&=0xdf;
				St&=0xfb;
				cnt_src[0]=10;	
				snmp_plazma++;
				break;
				}*/	
			
				//break;
			//	}
			if(snmp_command_parametr==1) 
				{
			//	St_[0]|=0x20;
			//	St_[1]&=0xdf;
			//	St&=0xfb;
		//		cnt_src[1]=10;
		//		snmp_plazma++;
		//		snmp_plazma++;
				}
			
			else if(snmp_command_parametr==2)
				{
			//	St_[1]|=0x20;
			//	St_[0]&=0xdf;
			//	St&=0xfb;
		//		cnt_src[0]=10;	
		//		snmp_plazma++;
				}	
			
			break;
			}

		case SNMP_BPS_UNDISABLE:
			{
			snmp_command=COMMAND_OK;
		//	St_[0]&=0xdf;
		//	St_[1]&=0xdf;
			break;
			}

		case SNMP_SPEC_VZ:
			{
			if((snmp_command_parametr>=1)&&(snmp_command_parametr<=24))
				{
			//	if(!(St&0x03)&&(NUMBAT))
					{
					snmp_command=COMMAND_OK;
		//			spc_stat=spc_VZ;
		//			cnt_vz_sec_=3600UL*snmp_command_parametr;
					}
			//	else
 					{
					snmp_command=COMAND_FAIL;	
 					}
				}
			else 
				{
				snmp_command=WRONG_PARAMETER;
				}
			break;
			}

		case SNMP_SPEC_KE:
			{
	  	//	if(!(St&0x02)&&(NUMBAT))
				{
				//spc_stat=spc_KE;
			//zar_cnt_ee_ke=0;
			//	zar_cnt=0L;
				snmp_command=COMMAND_OK;
				}
		//	else
				{
				snmp_command=COMAND_FAIL;	
				}
			break;
			}

		case SNMP_SPEC_DISABLE:
			{
		//	spc_stat=spc_OFF;
			snmp_command=COMMAND_OK;
			break;
			}


		default:
			{
			snmp_command=COMMAND_INVALID;
			break;
			}
		}
/*		else if((UIB2[1]==0x52)&&(UIB2[4]==5)&&(UIB2[5]==5)&&(UIB2[6])&&(UIB2[6]<=NUMIST)&&(UIB2[6]==UIB2[7])) 	//Выключение источника 
		{
	
		if((UIB2[6]==1)&&(UIB2[7]==1)) 
			{
			St_[0]|=0x20;
			St_[1]&=0xdf;
			St&=0xfb;
			cnt_src[1]=10;
			}
			
		else if((UIB2[6]==2)&&(UIB2[7]==2))
			{
			St_[1]|=0x20;
			St_[0]&=0xdf;
			St&=0xfb;
			cnt_src[0]=10;
			}	
		
     	memo_out2[0]=0x33;
     	memo_out2[1]=0x62;
     	memo_out2[2]=4;
     	memo_out2[3]=0x03;
     	
     	memo_out2[4]=5;
     	memo_out2[5]=5;
     	memo_out2[6]=UIB2[6];
     	memo_out2[7]=UIB2[6];
         	memo_out2[8]=crc_87(memo_out2,8);
		memo_out2[9]=crc_95(memo_out2,8);
     	uart_out_adr2(memo_out2,10); 		
		} */



	}
}

//-----------------------------------------------
char* datatime2str(char day,char month,char year, char hour, char min, char sec)
{
char temp_str[20];
memcpy(temp_str,"00/янв/00  00:00:00       ",20);

temp_str[1]=(day%10)+0x30;
temp_str[0]=(day/10)+0x30;

memcpy(&temp_str[3],sm_mont[month],3);

temp_str[8]=(year%10)+0x30;
temp_str[7]=(year/10)+0x30;

temp_str[12]=(hour%10)+0x30;
temp_str[11]=(hour/10)+0x30;

temp_str[15]=(min%10)+0x30;
temp_str[14]=(min/10)+0x30;

temp_str[18]=(sec%10)+0x30;
temp_str[17]=(sec/10)+0x30;
return temp_str;
}

//-----------------------------------------------
void event2snmp(char num)
{

}

//-----------------------------------------------
void snmp_trap_send(char* str, signed short in0, signed short in1, signed short in2)
{
for(snmp_trap_send_i=0;snmp_trap_send_i<100;snmp_trap_send_i++)
	{
	snmp_spc_trap_message[snmp_trap_send_i]=0;
	}


obj[0] = 0;
snmp_trap_send_ii=1;
if(str!=0)
	{
	obj[0]++;
	for(snmp_trap_send_i=0;snmp_trap_send_i<100&&(str[snmp_trap_send_i]);snmp_trap_send_i++)
		{
		snmp_spc_trap_message[snmp_trap_send_i]=str[snmp_trap_send_i];
		}
	obj[snmp_trap_send_ii] = 7;
	snmp_trap_send_ii++;
	}
if(in0!=0xffff)
	{
	obj[0]++;
	snmp_spc_trap_value_0=in0;
	obj[snmp_trap_send_ii] = 8;
	snmp_trap_send_ii++;
	}
if(in1!=0xffff)
	{
	obj[0]++;
	snmp_spc_trap_value_1=in1;
	obj[snmp_trap_send_ii] = 9;
	snmp_trap_send_ii++;
	}
if(in2!=0xffff)
	{
	obj[0]++;
	snmp_spc_trap_value_2=in2;
	obj[snmp_trap_send_ii] = 10;
	snmp_trap_send_ii++;
	}


if((ETH_TRAP1_IP_1!=255)&&(ETH_TRAP1_IP_2!=255)&&(ETH_TRAP1_IP_3!=255)&&(ETH_TRAP1_IP_4!=255))
	{
	temp_ip[0]= ETH_TRAP1_IP_1;
	temp_ip[1]= ETH_TRAP1_IP_2;
	temp_ip[2]= ETH_TRAP1_IP_3;
	temp_ip[3]= ETH_TRAP1_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}
if((ETH_TRAP2_IP_1!=255)&&(ETH_TRAP2_IP_2!=255)&&(ETH_TRAP2_IP_3!=255)&&(ETH_TRAP2_IP_4!=255))
	{
	temp_ip[0]= ETH_TRAP2_IP_1;
	temp_ip[1]= ETH_TRAP2_IP_2;
	temp_ip[2]= ETH_TRAP2_IP_3;
	temp_ip[3]= ETH_TRAP2_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}

if((ETH_TRAP3_IP_1!=255)&&(ETH_TRAP3_IP_2!=255)&&(ETH_TRAP3_IP_3!=255)&&(ETH_TRAP3_IP_4!=255))
	{
	temp_ip[0]= ETH_TRAP3_IP_1;
	temp_ip[1]= ETH_TRAP3_IP_2;
	temp_ip[2]= ETH_TRAP3_IP_3;
	temp_ip[3]= ETH_TRAP3_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}

if((ETH_TRAP4_IP_1!=255)&&(ETH_TRAP4_IP_2!=255)&&(ETH_TRAP4_IP_3!=255)&&(ETH_TRAP4_IP_4!=255))
	{
	temp_ip[0]= ETH_TRAP4_IP_1;
	temp_ip[1]= ETH_TRAP4_IP_2;
	temp_ip[2]= ETH_TRAP4_IP_3;
	temp_ip[3]= ETH_TRAP4_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}

if((ETH_TRAP5_IP_1!=255)&&(ETH_TRAP5_IP_2!=255)&&(ETH_TRAP5_IP_3!=255)&&(ETH_TRAP5_IP_4!=255))
	{
	temp_ip[0]= ETH_TRAP5_IP_1;
	temp_ip[1]= ETH_TRAP5_IP_2;
	temp_ip[2]= ETH_TRAP5_IP_3;
	temp_ip[3]= ETH_TRAP5_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}			
}


 
