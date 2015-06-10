#include "snmp_data_file.h" 
#include "eeprom_map.h"
#include "main.h"
#include "net_config.h"
//#include "main.h"
#include "control.h"
#include "LPC17xx.H"
#include <string.h>
#include "25lc640.h"
//#include "common_func.h"



//Информация об устройстве
signed short snmp_device_code;
signed 	   snmp_sernum;
signed short snmp_sernum_lsb;
signed short snmp_sernum_msb;
char 	   snmp_location[100];
signed short snmp_numofbat;
signed short snmp_numofbps;
signed short snmp_numofevents;


//Состояние первичной сети
signed short snmp_main_voltage;
signed short snmp_main_power_on_off;


//Состояние нагрузки
signed short snmp_load_voltage;
signed short snmp_load_current;

//Состояние БПСов
signed short snmp_bps_number[2];
signed short snmp_bps_voltage[2];
signed short snmp_bps_current[2];
signed short snmp_bps_temperature[2];
signed short snmp_bps_stat[2];

//Состояние Батареи
signed short snmp_battery_voltage;
signed short snmp_battery_current;


//Спецфункции
signed short snmp_spc_stat;
char snmp_spc_trap_message[100];
signed short snmp_spc_trap_value;


//Состояние инвертора
signed short snmp_inverter_voltage;
signed short snmp_inverter_current;
signed short snmp_inverter_temperature;


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
//SNMP-установки
signed short snmp_snmp_settings_read_port;
signed short snmp_snmp_settings_write_port;
char 		 snmp_snmp_settings_read_community[16];
char 		 snmp_snmp_settings_write_community[16];
long 		 snmp_snmp_settings_trap_server_1;
long 		 snmp_snmp_settings_trap_server_2;
long 		 snmp_snmp_settings_trap_server_3;
long 		 snmp_snmp_settings_trap_server_4;
long 		 snmp_snmp_settings_trap_server_5;
//ETH-установки
long 		 snmp_eth_settings_ip;
long 		 snmp_eth_settings_net_mask;
long 		 snmp_eth_settings_def_gatw;
//Трап-установки
signed short snmp_trap_settings_main_power_trap_send_of_av;
signed short snmp_trap_settings_main_power_trap_send_of_no_av;
signed short snmp_trap_settings_inverter_temperature_trap_send_of_av;
signed short snmp_trap_settings_inverter_temperature_trap_send_of_no_av;
signed short snmp_trap_settings_inverter_voltage_trap_send_of_av;
signed short snmp_trap_settings_inverter_voltage_trap_send_of_no_av;
signed short snmp_trap_settings_inverter_current_trap_send_of_av;
signed short snmp_trap_settings_inverter_current_trap_send_of_no_av;
signed short snmp_trap_settings_battery_voltage_trap_send_of_av;
signed short snmp_trap_settings_battery_voltage_trap_send_of_no_av;


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

signed short snmp_alarm_status;

char snmp_spc_trap_message[100];
signed short snmp_spc_trap_value_0,snmp_spc_trap_value_1,snmp_spc_trap_value_2;

//-----------------------------------------------
void snmp_data (void) 
{
//char i;

snmp_snmp_settings_read_port=SNMP_READ_PORT;
//snmp_snmp_settings_read_port=bps[NUMB]._flags_tm ;
snmp_snmp_settings_write_port=SNMP_WRITE_PORT;
snmp_snmp_settings_trap_server_1=(((long)SNMP_TRAP1_IP_4)<<24)+(((long)SNMP_TRAP1_IP_3)<<16)+(((long)SNMP_TRAP1_IP_2)<<8)+(((long)SNMP_TRAP1_IP_1));
snmp_snmp_settings_trap_server_2=(((long)SNMP_TRAP2_IP_4)<<24)+(((long)SNMP_TRAP2_IP_3)<<16)+(((long)SNMP_TRAP2_IP_2)<<8)+(((long)SNMP_TRAP2_IP_1));
snmp_snmp_settings_trap_server_3=(((long)SNMP_TRAP3_IP_4)<<24)+(((long)SNMP_TRAP3_IP_3)<<16)+(((long)SNMP_TRAP3_IP_2)<<8)+(((long)SNMP_TRAP3_IP_1));
snmp_snmp_settings_trap_server_4=(((long)SNMP_TRAP4_IP_4)<<24)+(((long)SNMP_TRAP4_IP_3)<<16)+(((long)SNMP_TRAP4_IP_2)<<8)+(((long)SNMP_TRAP4_IP_1));
snmp_snmp_settings_trap_server_5=(((long)SNMP_TRAP5_IP_4)<<24)+(((long)SNMP_TRAP5_IP_3)<<16)+(((long)SNMP_TRAP5_IP_2)<<8)+(((long)SNMP_TRAP5_IP_1));

snmp_eth_settings_ip=(((long)ETH_IP_4)<<24)+(((long)ETH_IP_3)<<16)+(((long)ETH_IP_2)<<8)+(((long)ETH_IP_1));
snmp_eth_settings_net_mask=(((long)ETH_NET_MASK_4)<<24)+(((long)ETH_NET_MASK_3)<<16)+(((long)ETH_NET_MASK_2)<<8)+(((long)ETH_NET_MASK_1));
snmp_eth_settings_def_gatw=(((long)ETH_DEF_GATW_4)<<24)+(((long)ETH_DEF_GATW_3)<<16)+(((long)ETH_DEF_GATW_2)<<8)+(((long)ETH_DEF_GATW_1));



snmp_trap_settings_main_power_trap_send_of_no_av=MAIN_POWER_TRAP_SEND_OF_AV;
snmp_trap_settings_main_power_trap_send_of_no_av=MAIN_POWER_TRAP_SEND_OF_NO_AV;
snmp_trap_settings_inverter_temperature_trap_send_of_av=INVERTER_TEMPERATURE_TRAP_SEND_OF_AV;
snmp_trap_settings_inverter_temperature_trap_send_of_no_av=INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV;
snmp_trap_settings_inverter_voltage_trap_send_of_av=INVERTER_VOLTAGE_TRAP_SEND_OF_AV;
snmp_trap_settings_inverter_voltage_trap_send_of_no_av=INVERTER_VOLTAGE_TRAP_SEND_OF_NO_AV;
snmp_trap_settings_inverter_current_trap_send_of_av=INVERTER_CURRENT_TRAP_SEND_OF_AV;
snmp_trap_settings_inverter_current_trap_send_of_no_av=INVERTER_CURRENT_TRAP_SEND_OF_NO_AV;
snmp_trap_settings_battery_voltage_trap_send_of_av=BATTERY_VOLTAGE_TRAP_SEND_OF_AV;
snmp_trap_settings_battery_voltage_trap_send_of_no_av=BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV;

snmp_alarm_status=bps[NUMB]._flags_tm;

//snmp_main_voltage=220;

/*
snmp_mains_power_voltage=Unet;
snmp_mains_power_frequency=fnet;
snmp_mains_power_status=0;
#if(UKU_VERSION==900)
snmp_mains_power_status=2;
#endif
if(St&0x01)snmp_mains_power_status|=0x01;
if(St&0x01)snmp_mains_power_alarm=1;

snmp_load_voltage=Uload;
snmp_load_current=iload;
snmp_numofbps=2;

snmp_numofevents=lc640_read_int(CNT_EVENT_LOG);

for(i=0;i<snmp_numofevents;i++)event2snmp(i);
//snmp_bpsnumber[0]=1;
//snmp_bpsnumber[1]=2;

snmp_sernum=AUSW_MAIN_NUMBER;
snmp_sernum_lsb=0x1122;
snmp_sernum_msb=0x3344;
snmp_device_code=AUSW_MAIN;

//memcpy(snmp_location,"lkhg;la",);


snmp_numofbat=1;



snmp_bps_number[0]=1;
snmp_bps_voltage[0]=Us[0];
snmp_bps_current[0]=Is[0];
snmp_bps_temperature[0]=t_i[0];
snmp_bps_stat[0]=0;												//Байт состояния БПСа.
if(St_[0]&(1<<2))snmp_bps_stat[0]=(1<<3); 							//авария по Umin
else if(St_[0]&(1<<3))snmp_bps_stat[0]=(1<<2); 						//авария по Umax
else if(St_[0]&(1<<4))snmp_bps_stat[0]=(1<<1); 						//авария по Tmax
else if(St_[0]&(1<<5))snmp_bps_stat[0]=(1<<5); 						//заблокирован
else if((!(St_[0]&0x3c))&&(!St&0x01)&&(!OFFBP1))snmp_bps_stat[0]=1; 		//Работает



snmp_bps_number[1]=2;
snmp_bps_voltage[1]=Us[1];
snmp_bps_current[1]=Is[1];
snmp_bps_temperature[1]=t_i[1];
snmp_bps_stat[1]=0;												//Байт состояния БПСа.
if(St_[1]&(1<<2))snmp_bps_stat[1]=(1<<3); 							//авария по Umin
else if(St_[1]&(1<<3))snmp_bps_stat[1]=(1<<2); 						//авария по Umax
else if(St_[1]&(1<<4))snmp_bps_stat[1]=(1<<1); 						//авария по Tmax
else if(St_[1]&(1<<5))snmp_bps_stat[1]=(1<<5); 						//заблокирован
else if((!(St_[1]&0x3c))&&(!St&0x01)&&(!OFFBP2))snmp_bps_stat[1]=1; 		//Работает

snmp_bat_voltage=Ubat;
snmp_bat_current=Ibat;
snmp_bat_temperature=t_b;
if(BAT_C_REAL==0x5555)
	{
	snmp_bat_capacity=BAT_C_NOM*10;
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
}
/*
//-----------------------------------------------
void snmp_sernum_write (int mode) 
{
if(mode==MIB_WRITE)
	{
	lc640_write_long(EE_AUSW_MAIN_NUMBER,snmp_sernum);
	lc640_write_long(EE_AUSW_UKU_NUMBER,snmp_sernum);
	}
}*/

//-----------------------------------------------
void snmp_location_write (int mode) 
{
char i;
if(mode==MIB_WRITE)
	{
	for(i=0;i<64;i++)
		{
		lc640_write(EE_LOCATION+i,snmp_location[i]);
		}
	}
}

//-----------------------------------------------
void snmp_snmp_settings_read_community_write (int mode) 
{
char i;
if(mode==MIB_WRITE)
	{
	for(i=0;i<16;i++)
		{
		lc640_write(EE_SNMP_READ_COMMUNITY+i,snmp_snmp_settings_read_community[i]);
		}
	}
}

//-----------------------------------------------
void snmp_snmp_settings_write_community_write (int mode) 
{
char i;
if(mode==MIB_WRITE)
	{
	for(i=0;i<16;i++)
		{
		lc640_write(EE_SNMP_WRITE_COMMUNITY+i,snmp_snmp_settings_write_community[i]);
		}
	}
}

//-----------------------------------------------
void snmp_main_bps_write (int mode)
{
if(mode==MIB_WRITE)
	{
//	lc640_write_int(EE_MAIN_BPS,snmp_main_bps-1);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_read_port_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_SNMP_READ_PORT,snmp_snmp_settings_read_port);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_write_port_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_SNMP_WRITE_PORT,snmp_snmp_settings_write_port);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_trap_server_1_write (int mode)
{
if(mode==MIB_WRITE)
	{
	SNMP_TRAP1_IP_1=(signed short)(snmp_snmp_settings_trap_server_1&0x000000ff);
	SNMP_TRAP1_IP_2=(signed short)((snmp_snmp_settings_trap_server_1>>8)&0x000000ff);
	SNMP_TRAP1_IP_3=(signed short)((snmp_snmp_settings_trap_server_1>>16)&0x000000ff);
	SNMP_TRAP1_IP_4=(signed short)((snmp_snmp_settings_trap_server_1>>24)&0x000000ff);
	lc640_write_int(EE_SNMP_TRAP1_IP_1,SNMP_TRAP1_IP_1);
	lc640_write_int(EE_SNMP_TRAP1_IP_2,SNMP_TRAP1_IP_2);
	lc640_write_int(EE_SNMP_TRAP1_IP_3,SNMP_TRAP1_IP_3);
	lc640_write_int(EE_SNMP_TRAP1_IP_4,SNMP_TRAP1_IP_4);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_trap_server_2_write (int mode)
{
if(mode==MIB_WRITE)
	{
	SNMP_TRAP2_IP_1=(signed short)(snmp_snmp_settings_trap_server_2&0x000000ff);
	SNMP_TRAP2_IP_2=(signed short)((snmp_snmp_settings_trap_server_2>>8)&0x000000ff);
	SNMP_TRAP2_IP_3=(signed short)((snmp_snmp_settings_trap_server_2>>16)&0x000000ff);
	SNMP_TRAP2_IP_4=(signed short)((snmp_snmp_settings_trap_server_2>>24)&0x000000ff);
	lc640_write_int(EE_SNMP_TRAP2_IP_1,SNMP_TRAP2_IP_1);
	lc640_write_int(EE_SNMP_TRAP2_IP_2,SNMP_TRAP2_IP_2);
	lc640_write_int(EE_SNMP_TRAP2_IP_3,SNMP_TRAP2_IP_3);
	lc640_write_int(EE_SNMP_TRAP2_IP_4,SNMP_TRAP2_IP_4);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_trap_server_3_write (int mode)
{
if(mode==MIB_WRITE)
	{
	SNMP_TRAP3_IP_1=(signed short)(snmp_snmp_settings_trap_server_3&0x000000ff);
	SNMP_TRAP3_IP_2=(signed short)((snmp_snmp_settings_trap_server_3>>8)&0x000000ff);
	SNMP_TRAP3_IP_3=(signed short)((snmp_snmp_settings_trap_server_3>>16)&0x000000ff);
	SNMP_TRAP3_IP_4=(signed short)((snmp_snmp_settings_trap_server_3>>24)&0x000000ff);
	lc640_write_int(EE_SNMP_TRAP3_IP_1,SNMP_TRAP3_IP_1);
	lc640_write_int(EE_SNMP_TRAP3_IP_2,SNMP_TRAP3_IP_2);
	lc640_write_int(EE_SNMP_TRAP3_IP_3,SNMP_TRAP3_IP_3);
	lc640_write_int(EE_SNMP_TRAP3_IP_4,SNMP_TRAP3_IP_4);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_trap_server_4_write (int mode)
{
if(mode==MIB_WRITE)
	{
	SNMP_TRAP4_IP_1=(signed short)(snmp_snmp_settings_trap_server_4&0x000000ff);
	SNMP_TRAP4_IP_2=(signed short)((snmp_snmp_settings_trap_server_4>>8)&0x000000ff);
	SNMP_TRAP4_IP_3=(signed short)((snmp_snmp_settings_trap_server_4>>16)&0x000000ff);
	SNMP_TRAP4_IP_4=(signed short)((snmp_snmp_settings_trap_server_4>>24)&0x000000ff);
	lc640_write_int(EE_SNMP_TRAP4_IP_1,SNMP_TRAP4_IP_1);
	lc640_write_int(EE_SNMP_TRAP4_IP_2,SNMP_TRAP4_IP_2);
	lc640_write_int(EE_SNMP_TRAP4_IP_3,SNMP_TRAP4_IP_3);
	lc640_write_int(EE_SNMP_TRAP4_IP_4,SNMP_TRAP4_IP_4);
	}
}

//-----------------------------------------------
void snmp_snmp_settings_trap_server_5_write (int mode)
{
if(mode==MIB_WRITE)
	{
	SNMP_TRAP5_IP_1=(signed short)(snmp_snmp_settings_trap_server_5&0x000000ff);
	SNMP_TRAP5_IP_2=(signed short)((snmp_snmp_settings_trap_server_5>>8)&0x000000ff);
	SNMP_TRAP5_IP_3=(signed short)((snmp_snmp_settings_trap_server_5>>16)&0x000000ff);
	SNMP_TRAP5_IP_4=(signed short)((snmp_snmp_settings_trap_server_5>>24)&0x000000ff);
	lc640_write_int(EE_SNMP_TRAP5_IP_1,SNMP_TRAP5_IP_1);
	lc640_write_int(EE_SNMP_TRAP5_IP_2,SNMP_TRAP5_IP_2);
	lc640_write_int(EE_SNMP_TRAP5_IP_3,SNMP_TRAP5_IP_3);
	lc640_write_int(EE_SNMP_TRAP5_IP_4,SNMP_TRAP5_IP_4);
	}
}

//-----------------------------------------------
void snmp_eth_settings_ip_write (int mode)
{
if(mode==MIB_WRITE)
	{
	ETH_IP_1=(signed short)(snmp_eth_settings_ip&0x000000ff);
	ETH_IP_2=(signed short)((snmp_eth_settings_ip>>8)&0x000000ff);
	ETH_IP_3=(signed short)((snmp_eth_settings_ip>>16)&0x000000ff);
	ETH_IP_4=(signed short)((snmp_eth_settings_ip>>24)&0x000000ff);
	lc640_write_int(EE_ETH_IP_1,ETH_IP_1);
	lc640_write_int(EE_ETH_IP_2,ETH_IP_2);
	lc640_write_int(EE_ETH_IP_3,ETH_IP_3);
	lc640_write_int(EE_ETH_IP_4,ETH_IP_4);
	}
}

//-----------------------------------------------
void snmp_eth_settings_net_mask_write (int mode)
{
if(mode==MIB_WRITE)
	{
	ETH_NET_MASK_1=(signed short)(snmp_eth_settings_net_mask&0x000000ff);
	ETH_NET_MASK_2=(signed short)((snmp_eth_settings_net_mask>>8)&0x000000ff);
	ETH_NET_MASK_3=(signed short)((snmp_eth_settings_net_mask>>16)&0x000000ff);
	ETH_NET_MASK_4=(signed short)((snmp_eth_settings_net_mask>>24)&0x000000ff);
	lc640_write_int(EE_ETH_NET_MASK_1,ETH_NET_MASK_1);
	lc640_write_int(EE_ETH_NET_MASK_2,ETH_NET_MASK_2);
	lc640_write_int(EE_ETH_NET_MASK_3,ETH_NET_MASK_3);
	lc640_write_int(EE_ETH_NET_MASK_4,ETH_NET_MASK_4);
	}
}

//-----------------------------------------------
void snmp_eth_settings_def_gatw_write (int mode)
{
if(mode==MIB_WRITE)
	{
	ETH_DEF_GATW_1=(signed short)(snmp_eth_settings_def_gatw&0x000000ff);
	ETH_DEF_GATW_2=(signed short)((snmp_eth_settings_def_gatw>>8)&0x000000ff);
	ETH_DEF_GATW_3=(signed short)((snmp_eth_settings_def_gatw>>16)&0x000000ff);
	ETH_DEF_GATW_4=(signed short)((snmp_eth_settings_def_gatw>>24)&0x000000ff);
	lc640_write_int(EE_ETH_DEF_GATW_1,ETH_DEF_GATW_1);
	lc640_write_int(EE_ETH_DEF_GATW_2,ETH_DEF_GATW_2);
	lc640_write_int(EE_ETH_DEF_GATW_3,ETH_DEF_GATW_3);
	lc640_write_int(EE_ETH_DEF_GATW_4,ETH_DEF_GATW_4);
	}
}

//-----------------------------------------------
void snmp_trap_settings_main_power_trap_send_of_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_MAIN_POWER_TRAP_SEND_OF_AV,snmp_trap_settings_main_power_trap_send_of_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_main_power_trap_send_of_no_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_MAIN_POWER_TRAP_SEND_OF_NO_AV,snmp_trap_settings_main_power_trap_send_of_no_av);
	}
}


//-----------------------------------------------
void snmp_trap_settings_inverter_temperature_trap_send_of_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_TEMPERATURE_TRAP_SEND_OF_AV,snmp_trap_settings_inverter_temperature_trap_send_of_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_inverter_temperature_trap_send_of_no_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV,snmp_trap_settings_inverter_temperature_trap_send_of_no_av);
	}
}
////

//-----------------------------------------------
void snmp_trap_settings_inverter_voltage_trap_send_of_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_VOLTAGE_TRAP_SEND_OF_AV,snmp_trap_settings_inverter_voltage_trap_send_of_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_inverter_voltage_trap_send_of_no_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_VOLTAGE_TRAP_SEND_OF_NO_AV,snmp_trap_settings_inverter_voltage_trap_send_of_no_av);
	}
}


//-----------------------------------------------
void snmp_trap_settings_inverter_current_trap_send_of_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_CURRENT_TRAP_SEND_OF_AV,snmp_trap_settings_inverter_current_trap_send_of_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_inverter_current_trap_send_of_no_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_CURRENT_TRAP_SEND_OF_NO_AV,snmp_trap_settings_inverter_current_trap_send_of_no_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_battery_voltage_trap_send_of_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_BATTERY_VOLTAGE_TRAP_SEND_OF_AV,snmp_trap_settings_battery_voltage_trap_send_of_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_battery_voltage_trap_send_of_no_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV,snmp_trap_settings_battery_voltage_trap_send_of_no_av);
	}
}
/*
//-----------------------------------------------
void snmp_trap_settings_inverter_temperature_trap_send_of_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_TEMPERATURE_TRAP_SEND_OF_AV,snmp_trap_settings_inverter_temperature_trap_send_of_av);
	}
}

//-----------------------------------------------
void snmp_trap_settings_inverter_temperature_trap_send_of_no_av_write (int mode)
{
if(mode==MIB_WRITE)
	{
	lc640_write_int(EE_INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV,snmp_trap_settings_inverter_temperature_trap_send_of_no_av);
	}
}
*/

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
/*
//-----------------------------------------------
void snmp_powerup_psu_timeout_write (int mode)
{
if(mode==MIB_WRITE)
	{
     lc640_write_int(EE_TZAS,snmp_powerup_psu_timeout);
	}
}*/

//-----------------------------------------------
void snmp_max_temperature_write (int mode)
{
if(mode==MIB_WRITE)
	{
 //    lc640_write_int(EE_TMAX,snmp_max_temperature);
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
return &temp_str[0];
}

//-----------------------------------------------
void event2snmp(char num)
{
char /*iii,*/index;
char dt[4],dt_[4],dt__[4],dt___[4],dt____[4],dt4[4];
unsigned int tempii;    

memcpy(&snmp_log[num][0],"                                                                                ",78);
//memcpy(&snmp_log[num][0],"BKL",10);


		
//tempii=lc640_read_int(PTR_EVENT_LOG);
//tempii=ptr_carry(tempii,64,-1*((signed)num));
tempii*=32;
//tempii+=EVENT_LOG;
     
lc640_read_long_ptr(tempii,dt);
lc640_read_long_ptr(tempii+4,dt4);
lc640_read_long_ptr(tempii+8,dt_);
lc640_read_long_ptr(tempii+12,dt__);
lc640_read_long_ptr(tempii+16,dt___);
lc640_read_long_ptr(tempii+20,dt____);
//iii=find(simbol);
     
if(dt[0]=='U')	 		//Включение ИБЭПа
    	{ 
    	if(dt[2]=='R')
    		{
		memcpy(&snmp_log[num][0],"Включение ИБЭПа@                                      ",50);
		memcpy(&snmp_log[num][17],datatime2str(dt_[2],dt_[1],dt_[0],dt__[0],dt__[1],dt__[2]),20);
		memcpy(&snmp_log[num][40],"@                   ",20);
    		}
     }   

     
else if(dt[0]=='P')		//Авария питающей сети
	{
	index=0;
     memcpy(&snmp_log[num][index],"Авария питающей сети @  ",23);	
	index+=23;
	memcpy(&snmp_log[num][index],datatime2str(dt_[2],dt_[1],dt_[0],dt__[0],dt__[1],dt__[2]),19);
	index+=19;
	snmp_log[num][index]='@';
	index++;

	if((dt___[0]=='A')&&(dt___[1]=='A'))
		{
		memcpy(&snmp_log[num][index]," не устранена  ",13);
		index+=13;
		}
	else 
		{
		memcpy(&snmp_log[num][index]," устранена   ",11);
		index+=11;
			
		memcpy(&snmp_log[num][index],datatime2str(dt___[2],dt___[1],dt___[0],dt____[0],dt____[1],dt____[2]),19);
		}

     }  

else if(dt[0]=='B')		//События батареи
    	{
	index=0;
    	if(dt[2]=='C')
    		{
		memcpy(&snmp_log[num][index],"Батарея.  Авария!!! @  ",21);
		index+=21;
		memcpy(&snmp_log[num][index],datatime2str(dt_[2],dt_[1],dt_[0],dt__[0],dt__[1],dt__[2]),19);
		index+=19;
		
		snmp_log[num][index]='@';
		index++;

		memcpy(&snmp_log[num][index],"Батарея не обнаружена, ",22);
		index+=22;

		if((dt___[0]=='A')&&(dt___[1]=='A'))
			{
			memcpy(&snmp_log[num][index]," не устранена  ",13);
			index+=13;
			}
		else 
			{
			memcpy(&snmp_log[num][index]," устранена   ",11);
			index+=11;
			memcpy(&snmp_log[num][index],datatime2str(dt___[2],dt___[1],dt___[0],dt____[0],dt____[1],dt____[2]),19);
			}

    		}
    	if(dt[2]=='Z')
    		{

		memcpy(&snmp_log[num][index],"Батарея.  Выравнивающий заряд @  ",32);
		index+=32;
		memcpy(&snmp_log[num][index],datatime2str(dt_[2],dt_[1],dt_[0],dt__[0],dt__[1],dt__[2]),19);
		index+=19;
		
		snmp_log[num][index]='@';
		index++;

		if((dt___[0]=='A')&&(dt___[1]=='A'))
			{
			memcpy(&snmp_log[num][index]," не завершен  ",13);
			index+=13;
			}
		else 
			{
			memcpy(&snmp_log[num][index]," завершен   ",11);
			index+=11;
			memcpy(&snmp_log[num][index],datatime2str(dt___[2],dt___[1],dt___[0],dt____[0],dt____[1],dt____[2]),19);
			}


/*
    		lcd_buffer[iii++]='В';
    		lcd_buffer[iii++]='З';
    		lcd_buffer[iii++]=' ';    		
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]=' ';  
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]=' ';
    		
    		if((dt_[0]==LPC_RTC->YEAR)&&(dt_[1]==LPC_RTC->MONTH)&&(dt_[2]==LPC_RTC->DOM))
    			{
    	    		lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='!';
    	    		lcd_buffer[iii++]=':'; 
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='@';
    			lcd_buffer[iii++]=':';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='#';
    	    		int2lcd(dt__[0],'!',0);
    			int2lcd(dt__[1],'@',0);
    			int2lcd(dt__[2],'#',0);    		     		
    			}	                   
 		else      	
    			{
    	 		lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='!';
    			lcd_buffer[iii++]='@'; 
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='#';
    			int2lcd(dt_[2],'!',0);
    			
    			int2lcd(dt_[0],'#',0);   
    			if(!((dt_[1]>=1)&&(dt_[1]<=12)))dt_[1]=1;
			sub_bgnd(sm_mont[dt_[1]],'@',0);  
    			} */ 		
    		}    		
/*
    	if(dt[2]=='W')
    		{
    		lcd_buffer[iii++]='Б';
    		lcd_buffer[iii++]='а';
    		lcd_buffer[iii++]='т';
		if(dt[1]<9)
    			{
    			lcd_buffer[iii++]=0x31+dt[1];
    			lcd_buffer[iii++]='р';
    			lcd_buffer[iii++]=' ';
    			}
    		else if((dt[1]>=9)&&(dt[1]<99))
    			{
    			lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    			lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    			lcd_buffer[iii++]='р';
    			}
    		else 
    			{
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]=' '; 
    			lcd_buffer[iii++]=' ';    		
    			} 
    		lcd_buffer[iii++]=' ';    		
    		
    		
		
    		if((dt_[0]==LPC_RTC->YEAR)&&(dt_[1]==LPC_RTC->MONTH)&&(dt_[2]==LPC_RTC->DOM))
    			{
    	    		lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='!';
    	    		lcd_buffer[iii++]=':'; 
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='@';
    			lcd_buffer[iii++]=':';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='#';
    	    		int2lcd(dt__[0],'!',0);
    			int2lcd(dt__[1],'@',0);
    			int2lcd(dt__[2],'#',0);    		     		
    			}	                   
 		else      	
    			{
    	 		lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='!';
    			lcd_buffer[iii++]='@'; 
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='#';
    			int2lcd(dt_[2],'!',0);
    			
    			int2lcd(dt_[0],'#',0);   
    			if(!((dt_[1]>=1)&&(dt_[1]<=12)))dt_[1]=1;
			sub_bgnd(sm_mont[dt_[1]],'@',0);  
    			}  		
    		} */   		
 
 	if(dt[2]=='K')
    		{

		memcpy(&snmp_log[num][index],"Батарея.  Контроль емкости @  ",29);
		index+=29;
		memcpy(&snmp_log[num][index],datatime2str(dt_[2],dt_[1],dt_[0],dt__[0],dt__[1],dt__[2]),19);
		index+=19;
		
		snmp_log[num][index]='@';
		index++;

		if((dt___[0]=='A')&&(dt___[1]=='A'))
			{
			memcpy(&snmp_log[num][index]," не завершен  ",13);
			index+=13;
			}
		else 
			{
			short temp_US;
			memcpy(&snmp_log[num][index]," завершен   ",11);
			index+=11;
			memcpy(&snmp_log[num][index],datatime2str(dt___[2],dt___[1],dt___[0],dt____[0],dt____[1],dt____[2]),19);
			memcpy(&snmp_log[num][index],", Uнач   , В, Uкон   , В, Cбат    , А*ч ", 39);
			
			temp_US=dt_[3]+(dt__[3]*256);

			snmp_log[num][index+10]=(temp_US%10)+0x30;
			temp_US/=10;
			snmp_log[num][index+8]=(temp_US%10)+0x30;
			temp_US/=10;
			if(temp_US)snmp_log[num][index+7]=(temp_US%10)+0x30;
			else snmp_log[num][index+7]=0x20;


			temp_US=dt4[2]+(dt4[3]*256);

			snmp_log[num][index+22]=(temp_US%10)+0x30;
			temp_US/=10;
			snmp_log[num][index+20]=(temp_US%10)+0x30;
			temp_US/=10;
			if(temp_US)snmp_log[num][index+19]=(temp_US%10)+0x30;
			else snmp_log[num][index+19]=0x20;


			temp_US=dt4[0]+(dt4[1]*256);

			snmp_log[num][index+35]=(temp_US%10)+0x30;
			temp_US/=10;
			snmp_log[num][index+33]=(temp_US%10)+0x30;
			temp_US/=10;
			if(temp_US)snmp_log[num][index+32]=(temp_US%10)+0x30;
			else snmp_log[num][index+32]=0x20;
			}



		/*
    		lcd_buffer[iii++]='Б';
    		lcd_buffer[iii++]='а';
    		lcd_buffer[iii++]='т';
		if(dt[1]<9)
    			{
    			lcd_buffer[iii++]=0x31+dt[1];
    			lcd_buffer[iii++]='к';
    			lcd_buffer[iii++]='е';
    			}
    		else if((dt[1]>=9)&&(dt[1]<99))
    			{
    			lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    			lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    			lcd_buffer[iii++]='к';
    			}
    		else 
    			{
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]=' '; 
    			lcd_buffer[iii++]=' ';    		
    			} 
    		lcd_buffer[iii++]=' ';    		
    		
    		if((dt_[0]==LPC_RTC->YEAR)&&(dt_[1]==LPC_RTC->MONTH)&&(dt_[2]==LPC_RTC->DOM))
    			{
    	    		lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='!';
    	    		lcd_buffer[iii++]=':'; 
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='@';
    			lcd_buffer[iii++]=':';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='#';
    	    		int2lcd(dt__[0],'!',0);
    			int2lcd(dt__[1],'@',0);
    			int2lcd(dt__[2],'#',0);    		     		
    			}	                   
 		else      	
    			{
    	 		lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='!';
    			lcd_buffer[iii++]='@'; 
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]='0';
    			lcd_buffer[iii++]='#';
    			int2lcd(dt_[2],'!',0);
    			
    			int2lcd(dt_[0],'#',0);   
    			if(!((dt_[1]>=1)&&(dt_[1]<=12)))dt_[1]=1;
			sub_bgnd(sm_mont[dt_[1]],'@',0);  
    			} */ 		
    		}    		

    		     	     	
    	}     	    
     	
else if(dt[0]=='S')
    	{
	index=0;
	memcpy(&snmp_log[num][0],"БПС №      ",6);
	index=6;
	snmp_log[num][5]=0x31+dt[1];
	index=7;
	memcpy(&snmp_log[num][index],"   Авария!!!@  ",14);
	index+=14;
		//memcpy(&snmp_log[num][0/*+num*/],"00/янв/11 00:00:00 @",20);
	memcpy(&snmp_log[num][index],datatime2str(dt_[2],dt_[1],dt_[0],dt__[0],dt__[1],dt__[2]),19);
	index+=20;

	if(dt[2]=='L')
		{
		memcpy(&snmp_log[num][40],"@отключился             ",20);
		index=65;
		}
	else if(dt[2]=='T')
		{
		memcpy(&snmp_log[num][index],"@ перегрев   ",10);
		index+=10;
		}		
	else if(dt[2]=='U')
		{
		memcpy(&snmp_log[num][index],"@ завышено Uвых.  ",16);
		index+=16;
		}		
	else if(dt[2]=='u')
		{
		memcpy(&snmp_log[num][index],"@ занижено Uвых.  ",16);
		index+=16;
		}
	else 		
		{
		memcpy(&snmp_log[num][index],"@ фигня  ",7);
		index+=7;
		}


	if((dt___[0]=='A')&&(dt___[1]=='A'))
		{
		memcpy(&snmp_log[num][index],", не устранена  ",15);
		index+=15;
		}
	else 
		{
		memcpy(&snmp_log[num][index],",  устранена   ",13);
		index+=13;
			
		memcpy(&snmp_log[num][index],datatime2str(dt___[2],dt___[1],dt___[0],dt____[0],dt____[1],dt____[2]),19);


		    /*
			ptrs[4]="  0[]  0< 0>:0=:0)  ";
			bgnd_par(ptrs[index_set],ptrs[1+index_set],ptrs[2+index_set],ptrs[3+index_set]);
			int2lcd(av_data_off[4],'>',0);
			int2lcd(av_data_off[5],'=',0);
			int2lcd(av_data_off[6],')',0);
			int2lcd(av_data_off[2],'[',0);
			int2lcd(av_data_off[0],'<',0); 
			if(!((av_data_off[1]>=1)&&(av_data_off[1]<=12)))av_data_off[1]=1;
			sub_bgnd(sm_mont[av_data_off[1]],']',0);   */





 /*
		ptrs[0]="   Авария БПС N+    ";
		
		if(av_head[2]=='L')
			{
			ptrs[1]="     отключился     ";
			}
		else if(av_head[2]=='T')
			{
			ptrs[1]="      перегрев      ";
			}		
		else if(av_head[2]=='U')
			{
			ptrs[1]="   завышено Uвых.   ";
			}		
		else if(av_head[2]=='u')
			{
			ptrs[1]="   занижено Uвых.   ";
			}								
		
		
		ptrs[2]="  0%(  0^ 0@:0#:0$  ";
			
						
			}	
		int2lcd(av_head[1]+1,'+',0);
		int2lcd(av_data_on[4],'@',0);
		int2lcd(av_data_on[5],'#',0);
		int2lcd(av_data_on[6],'$',0);
		int2lcd(av_data_on[2],'%',0);
		int2lcd(av_data_on[0],'^',0); 
		if(!((av_data_on[1]>=1)&&(av_data_on[1]<=12)))av_data_on[1]=1;
		sub_bgnd(sm_mont[av_data_on[1]],'(',0);
		*/
	    }



/*    	lcd_buffer[iii++]='Б';
    	lcd_buffer[iii++]='П';
    	lcd_buffer[iii++]='С';
 	if(dt[1]<9)
    		{
    		lcd_buffer[iii++]=0x31+dt[1];
    		lcd_buffer[iii++]=' ';
    		}
    	else if((dt[1]>=9)&&(dt[1]<99))
    		{
    		lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    		lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    		}
    	else 
    		{
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]=' ';     		
    		} 
    	lcd_buffer[iii++]=' '; 
    	lcd_buffer[iii++]=' ';
    	
    	if((dt_[0]==LPC_RTC->YEAR)&&(dt_[1]==LPC_RTC->MONTH)&&(dt_[2]==LPC_RTC->DOM))
    		{
    	    	lcd_buffer[iii++]='0';
    		lcd_buffer[iii++]='!';
    	    	lcd_buffer[iii++]=':'; 
    		lcd_buffer[iii++]='0';
    		lcd_buffer[iii++]='@';
    		lcd_buffer[iii++]=':';
    		lcd_buffer[iii++]='0';
    		lcd_buffer[iii++]='#';
    	    	int2lcd(dt__[0],'!',0);
    		int2lcd(dt__[1],'@',0);
    		int2lcd(dt__[2],'#',0);    		     		
    		}	                   
 	else      	
    		{
    	 	lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]='0';
    		lcd_buffer[iii++]='!';
    		lcd_buffer[iii++]='@'; 
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]='0';
    		lcd_buffer[iii++]='#';
    		int2lcd(dt_[2],'!',0);
    		int2lcd(dt_[0],'#',0);   
    		if(!((dt_[1]>=1)&&(dt_[1]<=12)))dt_[1]=1;
		sub_bgnd(sm_mont[dt_[1]],'@',0);  
		} */   	
    	}
  /*   	
else if(dt[0]=='B')
    	{
    	lcd_buffer[iii++]='Б';
    	lcd_buffer[iii++]='а';
    	lcd_buffer[iii++]='т';
 	if(dt[1]<9)
    		{
    		lcd_buffer[iii++]=0x31+dt[1];
    		lcd_buffer[iii++]=' ';
    		}
    	else if((dt[1]>=9)&&(dt[1]<99))
    		{
    		lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    		lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    		}
    	else 
    		{
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]=' ';     		
    		} 
    	lcd_buffer[iii++]=' ';
    	}     	    
else if(dt[0]=='I')
    	{
    	lcd_buffer[iii++]='И';
    	lcd_buffer[iii++]='н';
    	lcd_buffer[iii++]='в';
	if(dt[1]<9)
    		{
    		lcd_buffer[iii++]=0x31+dt[1];
    		lcd_buffer[iii++]=' ';
    		}
    	else if((dt[1]>=9)&&(dt[1]<99))
    		{
    		lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    		lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    		}
    	else 
    		{
    		lcd_buffer[iii++]=' ';
    		lcd_buffer[iii++]=' ';     		
    		} 
    	lcd_buffer[iii++]=' ';
    	} */   
}

//-----------------------------------------------
void snmp_trap_send(char* str, unsigned short in, unsigned short in1)
{
U16 obj[3];
U8 temp_ip[4];
char i,ii;

for(i=0;(i<100);i++)
	{
	snmp_spc_trap_message[i]=0;
	}


obj[0] = 0;
ii=1;
if(str!=0)
	{
	obj[0]++;
	for(i=0;(i<100)&&(str[i]);i++)
		{
		snmp_spc_trap_message[i]=str[i];
		}
	obj[ii] = 38;
	ii++;
	}
if(in!=0xffff)
	{
	obj[0]++;
	snmp_spc_trap_value_0=in;
	obj[ii] = 39;
	ii++;
	}

if(in1!=0xffff)
	{
	obj[0]++;
	snmp_spc_trap_value_1=in1;
	obj[ii] = 40;
	}


if((SNMP_TRAP1_IP_1!=255)&&(SNMP_TRAP1_IP_2!=255)&&(SNMP_TRAP1_IP_3!=255)&&(SNMP_TRAP1_IP_4!=255))
	{
	temp_ip[0]= SNMP_TRAP1_IP_1;
	temp_ip[1]= SNMP_TRAP1_IP_2;
	temp_ip[2]= SNMP_TRAP1_IP_3;
	temp_ip[3]= SNMP_TRAP1_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	} 
if((SNMP_TRAP2_IP_1!=255)&&(SNMP_TRAP2_IP_2!=255)&&(SNMP_TRAP1_IP_3!=255)&&(SNMP_TRAP2_IP_4!=255))
	{
	temp_ip[0]= SNMP_TRAP2_IP_1;
	temp_ip[1]= SNMP_TRAP2_IP_2;
	temp_ip[2]= SNMP_TRAP2_IP_3;
	temp_ip[3]= SNMP_TRAP2_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	} 
if((SNMP_TRAP3_IP_1!=255)&&(SNMP_TRAP3_IP_2!=255)&&(SNMP_TRAP3_IP_3!=255)&&(SNMP_TRAP3_IP_4!=255))
	{
	temp_ip[0]= SNMP_TRAP3_IP_1;
	temp_ip[1]= SNMP_TRAP3_IP_2;
	temp_ip[2]= SNMP_TRAP3_IP_3;
	temp_ip[3]= SNMP_TRAP3_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	} 
if((SNMP_TRAP4_IP_1!=255)&&(SNMP_TRAP4_IP_2!=255)&&(SNMP_TRAP4_IP_3!=255)&&(SNMP_TRAP4_IP_4!=255))
	{
	temp_ip[0]= SNMP_TRAP4_IP_1;
	temp_ip[1]= SNMP_TRAP4_IP_2;
	temp_ip[2]= SNMP_TRAP4_IP_3;
	temp_ip[3]= SNMP_TRAP4_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}
if((SNMP_TRAP5_IP_1!=255)&&(SNMP_TRAP5_IP_2!=255)&&(SNMP_TRAP5_IP_3!=255)&&(SNMP_TRAP5_IP_4!=255))
	{
	temp_ip[0]= SNMP_TRAP5_IP_1;
	temp_ip[1]= SNMP_TRAP5_IP_2;
	temp_ip[2]= SNMP_TRAP5_IP_3;
	temp_ip[3]= SNMP_TRAP5_IP_4;
	snmp_trap (temp_ip, 6, 3, obj);
	}/**/ 
}


 
