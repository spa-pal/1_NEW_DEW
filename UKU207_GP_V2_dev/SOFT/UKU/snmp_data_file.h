extern char snmp_community[10];

//Информация об устройстве
/*extern signed short snmp_device_code;
extern signed 	   snmp_sernum;
extern signed short snmp_sernum_lsb;
extern signed short snmp_sernum_msb;
extern char 	   snmp_location[100];
extern signed short snmp_numofbat;	*/
extern signed short snmp_num_of_psu;
extern signed short snmp_max_time_of_process;
extern signed short snmp_time_visualisation;
extern signed short snmp_pult_time_mode; 		
extern signed short snmp_load_current_measure_mode;	
extern signed short snmp_main_menu_mode;
extern signed short snmp_restart_enabled;
extern signed short snmp_modbus_adress;
extern signed long snmp_modbus_baudrate;	


//Состояние первичной сети
extern signed short snmp_mains_power_voltage;
extern signed short snmp_mains_power_frequency;
extern signed short snmp_mains_power_status;
extern signed short snmp_mains_power_alarm;

//Состояние выхода
extern signed short snmp_out_voltage;
extern signed short snmp_out_current;


//Состояние БПСов
extern signed short snmp_bps_number[8];
extern signed short snmp_bps_voltage[8];
extern signed short snmp_bps_current[8];
extern signed short snmp_bps_temperature[8];
extern signed short snmp_bps_stat[8];

//Состояние инверторов
extern signed short snmp_inv_number[3];
extern signed short snmp_inv_voltage[3];
extern signed short snmp_inv_current[3];
extern signed short snmp_inv_temperature[3];
extern signed short snmp_inv_stat[3];

//Спецфункции
//Спецфункции
extern signed short snmp_spc_stat;
extern char snmp_spc_trap_message[100];
extern signed short snmp_spc_trap_value_0,snmp_spc_trap_value_1,snmp_spc_trap_value_2;

//Состояние силовых вводов
extern signed short snmp_energy_vvod_phase_a;
extern signed short snmp_energy_vvod_phase_b;
extern signed short snmp_energy_vvod_phase_c;
extern signed short snmp_energy_pes_phase_a;
extern signed short snmp_energy_pes_phase_b;
extern signed short snmp_energy_pes_phase_c;

//Показания счетчика
extern signed long snmp_energy_total_energy;
extern signed short snmp_energy_current_energy;

//Состояние автоматов
extern signed char snmp_avt_number[12];
extern signed char snmp_avt_stat[12];

//Команды
extern signed short snmp_command;
extern signed short snmp_command_parametr;

//Журнал аварий
extern char snmp_log[64][128];

//Установочные параметры
extern signed short snmp_main_bps;
extern signed short snmp_zv_en;
extern signed short snmp_alarm_auto_disable;
extern signed short snmp_bat_test_time;
extern signed short snmp_u_max;
extern signed short snmp_u_0_grad;
extern signed short snmp_u_20_grad;
extern signed short snmp_u_sign;
extern signed short snmp_u_min_power;
extern signed short snmp_u_withouth_bat;
extern signed short snmp_control_current;
extern signed short snmp_max_charge_current;
extern signed short snmp_max_current;
extern signed short snmp_max_current_koef;
extern signed short snmp_max_current_koef;
extern signed short snmp_up_charge_koef;
extern signed short snmp_powerup_psu_timeout;
extern signed short snmp_max_temperature;

//Рабочие параметры
extern signed short snmp_U_up;  	
extern signed short snmp_I_ug; 	
extern signed short snmp_U_maxg;  	
extern signed short snmp_I_maxp; 	
extern signed long snmp_time_p;  	
extern signed long snmp_time_g;

// Параметры реверса
extern signed short snmp_reverse_state;
extern signed short snmp_avtoreverse_enable;
extern signed short snmp_avtoreverse_ff_time;
extern signed short snmp_avtoreverse_rew_time;
extern signed short snmp_avtoreverse_pause_time; 
extern signed short snmp_avtoreverse_ff_i;
extern signed short snmp_avtoreverse_rew_i;
extern signed short snmp_avtoreverse_ff_u;
extern signed short snmp_avtoreverse_rew_u;

//-----------------------------------------------
void snmp_data (void);
void snmp_sernum_write (int mode); 
void snmp_location_write (int mode);
void snmp_command_execute (int mode);
void event2snmp(char num);
void snmp_main_bps_write (int mode);
void snmp_zv_on_write (int mode);
void snmp_alarm_auto_disable_write (int mode);
void snmp_bat_test_time_write (int mode);
void snmp_u_max_write (int mode);
void snmp_u_0_grad_write (int mode);
void snmp_u_20_grad_write (int mode);
void snmp_u_sign_write (int mode);
void snmp_u_min_power_write (int mode);
void snmp_u_withouth_bat_write (int mode);
void snmp_control_current_write (int mode);
void snmp_max_charge_current_write (int mode);
void snmp_max_current_write (int mode);
void snmp_max_current_koef_write (int mode);
void snmp_up_charge_koef_write (int mode);
void snmp_powerup_psu_timeout_write (int mode);
void snmp_max_temperature_write (int mode);
void event2snmp(char num);
void snmp_trap_send(char* str, signed short in0, signed short in1, signed short in2);
void snmp_alarm_aktiv_write1(void);
void snmp_alarm_aktiv_write2(void);
void snmp_alarm_aktiv_write3(void);
void snmp_alarm_aktiv_write4(void);
void snmp_num_of_psu_write (int mode);
void snmp_max_time_of_process_write(int mode); 
void snmp_time_visualisation_write(int mode);
void snmp_pult_time_mode_write(int mode);  	
void snmp_load_current_measure_mode_write(int mode); 
void snmp_main_menu_mode_write(int mode); 
void snmp_restart_enabled_write(int mode);
void snmp_modbus_adress_write(int mode);
void snmp_modbus_baudrate_write(int mode);
void snmp_U_up_write(int mode);
void snmp_I_ug_write(int mode);
void snmp_U_maxg_write(int mode);
void snmp_I_maxp_write(int mode);
void snmp_time_p_write(int mode);
void snmp_time_g_write(int mode); 
void snmp_reverse_state_write (int mode);
void snmp_avtoreverse_enable_write(int mode);
void snmp_avtoreverse_ff_time_write(int mode);
void snmp_avtoreverse_rew_time_write(int mode);
void snmp_avtoreverse_pause_time_write(int mode);
void snmp_avtoreverse_ff_i_write(int mode);
void snmp_avtoreverse_rew_i_write(int mode);
void snmp_avtoreverse_ff_u_write(int mode);
void snmp_avtoreverse_rew_u_write(int mode);	



 
