/*----------------------------------------------------------------------------
 *      RL-ARM - TCPnet
 *----------------------------------------------------------------------------
 *      Name:    SNMP_MIB.C
 *      Purpose: SNMP Agent Management Information Base Module
 *      Rev.:    V4.12
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2010 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include "LPC17xx.H"
#include "main.H"
#include "control.H"
#include "snmp_data_file.h" 

/* snmp_demo.c */
extern U8   get_button (void);
extern void LED_out (U32 val);
extern BOOL LCDupdate;
extern U8   lcd_text[2][16+1];

/* System */
extern U32  snmp_SysUpTime;

/* Local variables */
//static U8   LedOut;
//static U8   KeyIn;

/* MIB Read Only integer constants */
static const U8 sysServices = 79;
static const U16 sysMainsVoltage = 220;
static const U8 displayPsuQauntity = 2;
static const U8 TestForTableValues = 57;

 char* const aaa = "Novosibirsk, Russia";

int a_;
char aa_;
char* aaa_="abc";

/* MIB Entry event Callback functions. */
//static void write_leds (int mode);
//static void read_key (int mode);
//static void upd_display (int mode);

/*----------------------------------------------------------------------------
 *      MIB Data Table
 *---------------------------------------------------------------------------*/

 MIB_ENTRY snmp_mib[] = {

  /* ---------- System MIB ----------- */

  /* SysDescr Entry */
  { MIB_OCTET_STR | MIB_ATR_RO,	     8, {OID0(1,3), 6, 1, 2, 1, 1, 1, 0},      MIB_STR("First ARM SNMP agent for SibPromAutomatika"),     NULL },
  /* SysObjectID Entry */
  { MIB_OBJECT_ID | MIB_ATR_RO,	     8, {OID0(1,3), 6, 1, 2, 1, 1, 2, 0},	    MIB_STR("\x2b\x06\x01\x04\x01\x82\x83\x1F"),    NULL },
  /* SysUpTime Entry */
  { MIB_TIME_TICKS | MIB_ATR_RO,     8, {OID0(1,3), 6, 1, 2, 1, 1, 3, 0},    4, &snmp_SysUpTime,    NULL },
  /* SysContact Entry */
  { MIB_OCTET_STR | MIB_ATR_RO,	     8, {OID0(1,3), 6, 1, 2, 1, 1, 4, 0},    MIB_STR("Skype:danilov_aa"),    NULL },
  /* SysName Entry */
  { MIB_OCTET_STR | MIB_ATR_RO,		    8, {OID0(1,3), 6, 1, 2, 1, 1, 5, 0},    MIB_STR("UKU203LAN"),    NULL },
  /* SysLocation Entry */
  { MIB_OCTET_STR | MIB_ATR_RO,		     8, {OID0(1,3), 6, 1, 2, 1, 1, 6, 0},    MIB_STR("Novosibirsk, Russia"),    NULL },
  /* SysServices Entry */
  { MIB_INTEGER | MIB_ATR_RO,			    8, {OID0(1,3), 6, 1, 2, 1, 1, 7, 0},    MIB_INT(sysServices),    NULL },

  /* ---------- Experimental MIB ----------- */

	//{ MIB_OCTET_STR | MIB_ATR_RO, 13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 1, 3, 1, 1, 0},  4,(void*)&aaa_,  NULL},	//Название ИБЭПа
	//{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 1, 3, 1, 2, 0},MIB_INT(AUSW_MAIN_NUMBER),  NULL},		//Серийный номер


 // 	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_CODE, 0},  	MIB_INT(snmp_device_code),  		NULL},   	//код устройства
//	{ MIB_INTEGER ,		  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_SERIAL, 0},	MIB_INT(snmp_sernum),	  		snmp_sernum_write },	//серийный номер	
//  	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_SERIAL_LSB, 0}, MIB_INT(snmp_sernum_lsb),  		NULL},	//серийный номер младший байт
//	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_SERIAL_MSB, 0},	MIB_INT(snmp_sernum_msb),  		NULL},	//серийный номер старший байт
// 	{ MIB_OCTET_STR, 			12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_LOCATION, 0},  	MIB_STR(snmp_location),  		snmp_location_write},	//местоположение устройства
//  	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_NUMOFBAT, 0}, 	MIB_INT(snmp_numofbat),  		NULL},	//количество введенных батарей
//	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_NUMOFBPS, 0},	MIB_INT(snmp_numofbps),  		NULL},	//количество введенных источников
//	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_DEVICE_INFO, DISPLAY_DEVICE_INFO_NUMOFEVENTS, 0},MIB_INT(snmp_numofevents),  		NULL},	//количество введенных источников



	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_MAIN, DISPLAY_MAIN_VOLTAGE, 0},  						MIB_INT(snmp_main_voltage),  		NULL},	//напряжение первичной сети
  	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_MAIN, DISPLAY_MAIN_POWER_ON_OFF, 0}, 					MIB_INT(snmp_main_power_on_off),	NULL},	//наличие первичной сети
	
	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_INVERTER, DISPLAY_INVERTER_VOLTAGE, 0},  				MIB_INT(snmp_inverter_voltage),  		NULL},	//напряжение инвертора
  	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_INVERTER, DISPLAY_INVERTER_CURRENT, 0},  				MIB_INT(snmp_inverter_current),  		NULL},	//ток инвертора
	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_INVERTER, DISPLAY_INVERTER_TEMPERATURE, 0},  			MIB_INT(snmp_inverter_temperature),  	NULL},	//температура инвертора

	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_BATTERY, DISPLAY_BATTERY_VOLTAGE, 0},  				MIB_INT(snmp_battery_voltage),  		NULL},	//напряжение батареи
  	{ MIB_INTEGER | MIB_ATR_RO,  	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_BATTERY, DISPLAY_BATTERY_CURRENT, 0},  				MIB_INT(snmp_battery_current),  		NULL},	//ток батареи

	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_ETH_SETTINGS, DISPLAY_ETH_SETTINGS_IP, 0},MIB_INT(snmp_eth_settings_ip),  				snmp_eth_settings_ip_write},		//ETH, IP
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_ETH_SETTINGS, DISPLAY_ETH_SETTINGS_NET_MASK, 0},MIB_INT(snmp_eth_settings_net_mask),  	snmp_eth_settings_net_mask_write},	//ETH, маска
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_ETH_SETTINGS, DISPLAY_ETH_SETTINGS_DEF_GATW, 0},MIB_INT(snmp_eth_settings_def_gatw),  	snmp_eth_settings_def_gatw_write},	//ETH, шлюз
	 
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_READ_PORT, 0},  	MIB_INT(snmp_snmp_settings_read_port),  		snmp_snmp_settings_read_port_write},	//SNMP, порт чтения
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_WRITE_PORT, 0},  	MIB_INT(snmp_snmp_settings_write_port),  		snmp_snmp_settings_write_port_write},	//SNMP, порт записи
 	{ MIB_OCTET_STR, 				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_READ_COMMUNITY, 0},  		MIB_STR(snmp_snmp_settings_read_community),  		snmp_snmp_settings_read_community_write},	//SNMP, пароль на чтение
 	{ MIB_OCTET_STR, 				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_WRITE_COMMUNITY, 0},  	MIB_STR(snmp_snmp_settings_write_community),  		snmp_snmp_settings_write_community_write},	//SNMP,	пароль на запись
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_TRAP_SERVER_1, 0},MIB_INT(snmp_snmp_settings_trap_server_1),  	snmp_snmp_settings_trap_server_1_write},	//SNMP, приемник трапов №1
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_TRAP_SERVER_2, 0},MIB_INT(snmp_snmp_settings_trap_server_2),  	snmp_snmp_settings_trap_server_2_write},	//SNMP, приемник трапов №1
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_TRAP_SERVER_3, 0},MIB_INT(snmp_snmp_settings_trap_server_3),  	snmp_snmp_settings_trap_server_3_write},	//SNMP, приемник трапов №1
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_TRAP_SERVER_4, 0},MIB_INT(snmp_snmp_settings_trap_server_4),  	snmp_snmp_settings_trap_server_4_write},	//SNMP, приемник трапов №1
	{ MIB_IP_ADDR,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SNMP_SETTINGS, DISPLAY_SNMP_SETTINGS_TRAP_SERVER_5, 0},MIB_INT(snmp_snmp_settings_trap_server_5),  	snmp_snmp_settings_trap_server_5_write},	//SNMP, приемник трапов №1


	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_MAIN_POWER_TRAP_SEND_OF_AV, 0},  				MIB_INT(snmp_trap_settings_main_power_trap_send_of_av),  				snmp_trap_settings_main_power_trap_send_of_av_write},	//Включение-выключение посылки трапов об аварии сети
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_MAIN_POWER_TRAP_SEND_OF_NO_AV, 0},  			MIB_INT(snmp_trap_settings_main_power_trap_send_of_no_av),  			snmp_trap_settings_main_power_trap_send_of_no_av_write},	//Включение-выключение посылки трапов о снятии аварии сети
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_INVERTER_TEMPERATURE_TRAP_SEND_OF_AV, 0},  	MIB_INT(snmp_trap_settings_inverter_temperature_trap_send_of_av),  		snmp_trap_settings_inverter_temperature_trap_send_of_av_write},	//Включение-выключение посылки трапов об аварии инвертора по температуре
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV, 0},	MIB_INT(snmp_trap_settings_inverter_temperature_trap_send_of_no_av),  	snmp_trap_settings_inverter_temperature_trap_send_of_no_av_write},	//Включение-выключение посылки трапов о снятии инвертора по температуре
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_INVERTER_VOLT_TRAP_SEND_OF_AV, 0},  			MIB_INT(snmp_trap_settings_inverter_voltage_trap_send_of_av),  			snmp_trap_settings_inverter_voltage_trap_send_of_av_write},	//Включение-выключение посылки трапов об аварии сети
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_INVERTER_VOLT_TRAP_SEND_OF_NO_AV, 0},  		MIB_INT(snmp_trap_settings_inverter_voltage_trap_send_of_no_av),  		snmp_trap_settings_inverter_voltage_trap_send_of_no_av_write},	//Включение-выключение посылки трапов о снятии аварии сети
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_INVERTER_CURR_TRAP_SEND_OF_AV, 0},  			MIB_INT(snmp_trap_settings_inverter_current_trap_send_of_av),  			snmp_trap_settings_inverter_current_trap_send_of_av_write},	//Включение-выключение посылки трапов об аварии инвертора по температуре
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_INVERTER_CURR_TRAP_SEND_OF_NO_AV, 0},  		MIB_INT(snmp_trap_settings_inverter_current_trap_send_of_no_av),  		snmp_trap_settings_inverter_current_trap_send_of_no_av_write},	//Включение-выключение посылки трапов о снятии инвертора по температуре
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_BATTERY_VOLTAGE_TRAP_SEND_OF_AV, 0},  		MIB_INT(snmp_trap_settings_battery_voltage_trap_send_of_av),  			snmp_trap_settings_battery_voltage_trap_send_of_av_write},	//Включение-выключение посылки трапов об аварии сети
	{ MIB_INTEGER,  				12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_TRAP_SETTINGS, DISPLAY_TRAP_SETTINGS_BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV, 0},  		MIB_INT(snmp_trap_settings_battery_voltage_trap_send_of_no_av),  		snmp_trap_settings_battery_voltage_trap_send_of_no_av_write},	//Включение-выключение посылки трапов о снятии аварии сети



//	{ MIB_INTEGER | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_STAT , 0},					MIB_INT(snmp_spc_stat),     NULL},
//	{ MIB_OCTET_STR | MIB_ATR_RO, 12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_TRAP_MESSAGE , 0},			MIB_STR(snmp_spc_trap_message),     NULL},
//	{ MIB_INTEGER | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_TRAP_VALUE , 0},			MIB_INT(snmp_spc_trap_value),     NULL},


//	{ MIB_INTEGER,  			12, {OID_ENTERPRISE, OID_DEVICE, SNMP_COMMAND, COMMAND_ANSWER, 0},					MIB_INT(snmp_command),  	snmp_command_execute},		//номер первого бпса 
//	{ MIB_INTEGER,  			12, {OID_ENTERPRISE, OID_DEVICE, SNMP_COMMAND, COMMAND_PARAMETR, 0},					MIB_INT(snmp_command_parametr),  	NULL},		//номер первого бпса
//	{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID_ENTERPRISE, OID_DEVICE, 4, 1, 3, 1},MIB_INT(snmp_bpsnumber[0]),  	NULL},		//номер первого бпса
//	{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID_ENTERPRISE, OID_DEVICE, 4, 1, 4, 1},MIB_INT(snmp_bpsnumber[0]),  	NULL},		//номер первого бпса
 // 	{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID_ENTERPRISE, OID_DEVICE, 4, 1, 5, 1},MIB_INT(snmp_bpsnumber[0]),  	NULL},		//номер первого бпса
//	{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID_ENTERPRISE, OID_DEVICE, 4, 1, 6, 1},MIB_INT(snmp_bpsnumber[0]),  	NULL},		//номер первого бпса
//	{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID_ENTERPRISE, OID_DEVICE, 4, 1, 9, 1},MIB_INT(snmp_bpsnumber[0]),  	NULL},		//номер первого бпса


//	{ MIB_INTEGER, 			12, {OID_ENTERPRISE, OID_DEVICE, 8, 3, 0},   MIB_INT(snmp_bpsnumber[0]),    NULL},
//	{ MIB_INTEGER, 			12, {OID_ENTERPRISE, OID_DEVICE, 8, 1, 0},   MIB_INT(snmp_bpsnumber[0]),    NULL},



//	{ MIB_INTEGER | MIB_ATR_RO,  	13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 1, 2, 4, 1, 0},  MIB_INT(NUMBAT),  NULL},	//количество введенных батарей

	{ MIB_OCTET_STR | MIB_ATR_RO, 13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 1, 2, 7, 4, 0},	     MIB_STR("Novosibirsk, Russia"),     NULL},
	{ MIB_INTEGER, 			13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 1, 2, 7, 5, 0},	     MIB_INT(displayPsuQauntity),     NULL},
 /* { MIB_INTEGER | MIB_ATR_RO,  	13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 2, 2, 3, 1, 0},  MIB_INT(plazma_mib),  NULL},
  { MIB_INTEGER | MIB_ATR_RO,  	13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 2, 2, 3, 2, 0},  MIB_INT(plazma_mib1),  NULL},
  { MIB_INTEGER,  	13, {OID0(1,3), 6, 1, 4, 1, 130, 131, 31, 1, 2, 1, 2, 0},    MIB_INT(LPC_RTC->SEC),    NULL}, */
  
	



	{ MIB_OCTET_STR | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_TRAP_MESSAGE , 0},			MIB_STR(snmp_spc_trap_message),     NULL},
	{ MIB_INTEGER | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_TRAP_VALUE_0 , 0},			MIB_INT(snmp_spc_trap_value_0),     NULL},
	{ MIB_INTEGER | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_TRAP_VALUE_1 , 0},			MIB_INT(snmp_spc_trap_value_1),     NULL},
	{ MIB_INTEGER | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPEC,DISPLAY_SPEC_TRAP_VALUE_2 , 0},			MIB_INT(snmp_spc_trap_value_2),     NULL},

	{ MIB_INTEGER | MIB_ATR_RO, 	12, {OID_ENTERPRISE, OID_DEVICE, DISPLAY_SPECIALS,DISPLAY_ALARM_STATUS , 0},			MIB_INT(snmp_alarm_status),     NULL},


	};
const int snmp_mib_size = (sizeof(snmp_mib) / sizeof(MIB_ENTRY));

///*----------------------------------------------------------------------------
// *      MIB Callback Functions
// *---------------------------------------------------------------------------*/
//
//static void write_leds (int mode) {
//  /* No action on read access. */
//  if (mode == MIB_WRITE) {
//    LED_out (LedOut);
//  }
//}
//
//static void read_key (int mode) {
//  /* Read ARM Digital Input */
//  if (mode == MIB_READ) {
//    KeyIn = get_button();
//  }
//}
//
//static void upd_display (int mode) {
//  /* Update LCD Module display text. */
//  if (mode == MIB_WRITE) {
//    /* Write access. */
//    LCDupdate = __TRUE;
//  }
//}

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
