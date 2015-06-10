#include <rtl.h>

#define SOFT_NUM	1055
#define SOFT_DATE	210611UL
//--------------портовые операции
#define MASK(lengt) 		(0xffffffff>>(32-lengt))
#define MASK_OFFSET(shift,lengt)	(MASK(lengt)<<shift)

#define GET_REG( reg, shift, lengt) 		( (reg & MASK_OFFSET(shift,lengt)) >> shift)
#define SET_REG( reg, val, shift, lengt)  	reg = ( (reg & ~MASK_OFFSET(shift,lengt)) | (val << shift) )
//--------------реле
#define COIL_ON		LPC_GPIO1->FIODIR|=(1<<23);LPC_GPIO1->FIOSET|=(1<<23)
#define COIL_OFF	LPC_GPIO1->FIODIR|=(1<<23);LPC_GPIO1->FIOCLR|=(1<<23)
#define COIL_CAL_ON		LPC_GPIO1->FIODIR|=(1<<22);LPC_GPIO1->FIOSET|=(1<<22)
#define COIL_CAL_OFF	LPC_GPIO1->FIODIR|=(1<<22);LPC_GPIO1->FIOCLR|=(1<<22)

//-----------------------------------
#define CNT_SRC_MAX	10
#define NUMB 8-1

extern char tcp_init_cnt;

extern char f1000Hz,f100Hz,f50Hz,f10Hz,f5Hz,f2Hz,f1Hz;		 // флаги срабатывания событий
//-----Индикация
extern char level_U,level_I,level_Q,ind_level_U,ind_level_I,ind_level_Q,flash_;
typedef enum ind_mode{norm,reverse,alone,flash} ind_mode;	   // 3 вида режима отображения
extern ind_mode level_U_mode,level_I_mode,level_Q_mode;
extern signed short flash_net_def_cnt;


//**********************************************
//Коэффициенты, отображаемые из EEPROM
//extern signed short Ktsrc[2];
//extern signed short Kusrc[2];
//extern signed short Kisrc[2];
//extern signed short Ki0src[2];
extern signed short Kubat[2];
//extern signed short Kubatm[2];
extern signed short Kibat0[2];
extern signed short Kibat1[2];
//extern signed short Ktbat[2];
extern signed short Kunet;
//extern signed short Ktext[3];
//extern signed short Kuload;
//extern signed short Kunet_ext[3];
//
//extern signed short MAIN_IST;
//extern signed short UMAX;
//extern signed short UB0;
//extern signed short UB20;
//extern signed short TMAX;
//extern signed short TSIGN;
//extern signed short AV_OFF_AVT;
//extern signed short USIGN;
//extern signed short UMN;
//extern signed short ZV_ON;
//extern signed short IKB;
//extern signed short KVZ;
//extern signed short IMAX;
//extern signed short KIMAX;
//extern signed short APV_ON;
//extern signed short IZMAX;
//extern signed short U0B;
//extern signed short TZAS;
//extern signed short VZ_HR;
//extern signed short TBAT;
//extern signed short U_AVT;
//extern signed short DU;
//extern signed short PAR;
//extern signed short TBATMAX;
//extern signed short TBATSIGN;
//extern signed short UBM_AV;
//extern signed short TBOXMAX;
//extern signed short TBOXREG;
//extern signed short TBOXVENTMAX;
//extern signed short TLOADDISABLE;
//extern signed short TLOADENABLE;
//extern signed short TBATDISABLE;
//extern signed short TBATENABLE;
//extern signed short TBOXMAX;
//extern signed short TBOXREG;
//extern signed short TBOXVENTMAX;
//extern signed short TLOADDISABLE;
//extern signed short TLOADENABLE;
//extern signed short TBATDISABLE;
//extern signed short TBATENABLE;
//
//extern signed short NUMBAT;
//extern signed short NUMIST;
//extern signed short NUMINV;
//extern signed short NUMDT;
//extern signed short NUMSK;
//extern signed short NUMEXT;
//extern signed short NUMAVT;
//
//typedef enum {apvON=0x01,apvOFF=0x00}enum_apv_on;
//extern enum_apv_on APV_ON1,APV_ON2;
//
//extern signed short APV_ON2_TIME;
//
//typedef enum {bisON=0x0055,bisOFF=0x00aa}enum_bat_is_on;
//extern enum_bat_is_on BAT_IS_ON[2];
//
//extern signed short BAT_DAY_OF_ON[2];
//extern signed short BAT_MONTH_OF_ON[2];
//extern signed short BAT_YEAR_OF_ON[2];
//extern signed short BAT_C_NOM[2];
//extern signed short BAT_RESURS[2];
//extern signed short BAT_C_REAL[2];
//
//extern unsigned short AUSW_MAIN;
//extern unsigned long 	AUSW_MAIN_NUMBER;
//extern unsigned short AUSW_DAY;
//extern unsigned short AUSW_MONTH;
//extern unsigned short AUSW_YEAR;
//extern unsigned short AUSW_UKU;
//extern unsigned short AUSW_UKU_SUB;
//extern unsigned long AUSW_UKU_NUMBER;
//extern unsigned long	AUSW_BPS1_NUMBER;
//extern unsigned long  AUSW_BPS2_NUMBER;
//extern unsigned short AUSW_RS232;
//extern unsigned short AUSW_PDH;
//extern unsigned short AUSW_SDH;
//extern unsigned short AUSW_ETH;
//
//extern signed short TMAX_EXT_EN[3];
//extern signed short TMAX_EXT[3];
//extern signed short TMIN_EXT_EN[3];
//extern signed short TMIN_EXT[3];
//extern signed short T_EXT_REL_EN[3];
//extern signed short T_EXT_ZVUK_EN[3];
//extern signed short T_EXT_LCD_EN[3];
//extern signed short T_EXT_RS_EN[3];
//
//extern signed short SK_SIGN[4];
//extern signed short SK_REL_EN[4];
//extern signed short SK_ZVUK_EN[4];
//extern signed short SK_LCD_EN[4];
//extern signed short SK_RS_EN[4];
//
//typedef enum {AVZ_1=1,AVZ_2=2,AVZ_3=3,AVZ_6=6,AVZ_12=12,AVZ_OFF=0}enum_avz;
//extern enum_avz AVZ;
//
//extern unsigned short HOUR_AVZ;
//extern unsigned short MIN_AVZ;
//extern unsigned short SEC_AVZ;
//extern unsigned short DATE_AVZ;
//extern unsigned short MONTH_AVZ;
//extern unsigned short YEAR_AVZ;
//extern unsigned short AVZ_TIME;
//typedef enum {mnON=0x55,mnOFF=0xAA}enum_mnemo_on;
//extern enum_mnemo_on MNEMO_ON;
//extern unsigned short MNEMO_TIME;
extern signed long SERIAL_NUMBER;
//
//***********************************************
//ETH-настройки
extern signed short ETH_IP_1;
extern signed short ETH_IP_2;
extern signed short ETH_IP_3;
extern signed short ETH_IP_4;
extern signed short ETH_NET_MASK_1;
extern signed short ETH_NET_MASK_2;
extern signed short ETH_NET_MASK_3;
extern signed short ETH_NET_MASK_4;
extern signed short ETH_DEF_GATW_1;
extern signed short ETH_DEF_GATW_2;
extern signed short ETH_DEF_GATW_3;
extern signed short ETH_DEF_GATW_4;

//extern signed short ETH_IS_ON;
//extern signed short ETH_DHCP_ON;
//extern signed short ETH_IP_1;
//extern signed short ETH_IP_2;
//extern signed short ETH_IP_3;
//extern signed short ETH_IP_4;
//extern signed short ETH_MASK_1;
//extern signed short ETH_MASK_2;
//extern signed short ETH_MASK_3;
//extern signed short ETH_MASK_4;
//extern signed short ETH_SNMP_PORT_READ;
//extern signed short ETH_SNMP_PORT_WRITE;
//extern signed short ETH_GW_1;
//extern signed short ETH_GW_2;
//extern signed short ETH_GW_3;
//extern signed short ETH_GW_4;

//***********************************************
//SNMP-настройки
extern signed short SNMP_READ_PORT;
extern signed short SNMP_WRITE_PORT;
extern signed short SNMP_TRAP1_IP_1;
extern signed short SNMP_TRAP1_IP_2;
extern signed short SNMP_TRAP1_IP_3;
extern signed short SNMP_TRAP1_IP_4;
extern signed short SNMP_TRAP2_IP_1;
extern signed short SNMP_TRAP2_IP_2;
extern signed short SNMP_TRAP2_IP_3;
extern signed short SNMP_TRAP2_IP_4;
extern signed short SNMP_TRAP3_IP_1;
extern signed short SNMP_TRAP3_IP_2;
extern signed short SNMP_TRAP3_IP_3;
extern signed short SNMP_TRAP3_IP_4;
extern signed short SNMP_TRAP4_IP_1;
extern signed short SNMP_TRAP4_IP_2;
extern signed short SNMP_TRAP4_IP_3;
extern signed short SNMP_TRAP4_IP_4;
extern signed short SNMP_TRAP5_IP_1;
extern signed short SNMP_TRAP5_IP_2;
extern signed short SNMP_TRAP5_IP_3;
extern signed short SNMP_TRAP5_IP_4;

//***********************************************
//Трап-настройки
extern signed short MAIN_POWER_TRAP_SEND_OF_AV;
extern signed short MAIN_POWER_TRAP_SEND_OF_NO_AV;
extern signed short INVERTER_TEMPERATURE_TRAP_SEND_OF_AV;
extern signed short INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV;
extern signed short INVERTER_VOLTAGE_TRAP_SEND_OF_AV;
extern signed short INVERTER_VOLTAGE_TRAP_SEND_OF_NO_AV;
extern signed short INVERTER_CURRENT_TRAP_SEND_OF_AV;
extern signed short INVERTER_CURRENT_TRAP_SEND_OF_NO_AV;
extern signed short BATTERY_VOLTAGE_TRAP_SEND_OF_AV;
extern signed short BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV;

//
//***********************************************
//Состояние первичной сети
extern char net_av;
extern signed short net_stat_cnt;
//***********************************************

//Состояние источников


typedef struct
     {
     enum {dSRC=3,dINV=5}_device;
	char _av;
	//0бит - авария по перегреву
	//1бит - авария по завышенному Uвых
	//2бит - авария по заниженному Uвых
	//3бит - авария по обрыву связи
	//4бит - авария по завышенному Iвых	    
    //5бит - авария по завышенному на 5% Iвых
	 enum {bsAPV,bsWRK,bsRDY,bsBL,bsAV,bsOFF_AV_NET}_state;
     char _cnt;
     char _cnt_old;
     char _cnt_more2;
     char _buff[16]; 
     //char _av_net;
     //char _av_u_max;
     //char _av_u_min;
     //char _av_temper; 
     signed _Uii; 
     signed _Uin;
     signed _Ii;
     signed _Ti; 
     char _flags_tu;
     //char _flags_tu_old;
     //char _is_ready;
     //char _is_wrk;
     //char _is_link;
     //char _is_av;
     signed _vol_u;
     signed _vol_i;
     char _is_on_cnt;
     //int _ist_blok_host_cnt_; //блокирование источников извне(CAN или RS), если не 0 то источник заблокирован.
     int _ist_blok_host_cnt;
     short _blok_cnt; //блокирование источников 
     char _flags_tm;
	 signed short _light_overload_av_cnt;     
     signed short _overload_av_cnt;	   
     signed short _temp_av_cnt;
     signed short _umax_av_cnt;
     signed short _umin_av_cnt;
     signed _rotor;
     signed  short _x_; 
     char _adr_ee;
	char _last_avar;
     } BPS_STAT; 
extern BPS_STAT bps[12];
 

//-----Состояние
typedef enum work{power_net,acb} work;
extern work work_at;
typedef enum stat{breakdown,active} stat;
extern stat work_stat;
//-----

//-----------------------------------------------
//Кнопки
extern char speed,l_but,n_but;
extern char but;                            
extern unsigned long but_n,but_s;
extern char but0_cnt;
extern char but1_cnt;
extern char but_onL_temp;




//-----------------------------------------------
//Индикация
typedef enum {iMn,iDef_net_set,iNet,iSet,iBat,iSrc,iS2,iSet_prl,iK_prl,iDnd,iK,
	iSpcprl,iSpc,k,Crash_0,Crash_1,iKednd,
	iLoad,iSpc_prl_vz,iSpc_prl_ke,iKe,iVz,iAVAR,iStr,iVrs,iPrltst,iApv,
	iK_src,iK_bat,iK_load,iK_net,iTst,iTst_klbr,iTst_BPS1,iTst_BPS2,
	iTst_BPS12,iDebug,iDef,iSet_st_prl,iK_pdp,iSet_T,iDeb,iJ_bat,
	iPrl_bat_in_out,iPdp1,iJAv_sel,iJAv_net_sel,iJAv_net,iJAv_src1,
	iJAv_src2,iJAv_bat,iJAv_bat_sel,iAusw,iAusw_prl,iAusw_set,iK_t_out,
	iJ_bat_ke_sel,iJ_bat_ke,iJ_bat_vz_sel,iJ_bat_vz,iJ_bat_wrk_sel,iJ_bat_wrk,
	iExt_set,iExt_dt,iExt_sk,iAvz,iJAv_src1_sel,iJAv_src2_sel,iLog,iLog_,iLan_set,iLan,iSM}ind_enum;


typedef struct  
{
ind_enum i;

signed char s_i;
signed char s_i1;
signed char s_i2;
signed char i_s;
} stuct_ind;

extern stuct_ind a,b[10];

#define ind     a.i
#define sub_ind     a.s_i
#define sub_ind1     a.s_i1
#define sub_ind2     a.s_i2
#define index_set     a.i_s




signed short abs_pal(signed short in);
void ADC_IRQHandler(void);
void delay_us(long del);


#define OID_ENTERPRISE 	OID0(1,3), 6, 1, 4, 1, 130, 131, 31
#define OID_DEVICE 		25
#define DISPLAY_DEVICE_INFO			1
#define DISPLAY_DEVICE_INFO_CODE			1
#define DISPLAY_DEVICE_INFO_SERIAL			2
#define DISPLAY_DEVICE_INFO_SERIAL_LSB		3
#define DISPLAY_DEVICE_INFO_SERIAL_MSB		4
#define DISPLAY_DEVICE_INFO_LOCATION 		5
#define DISPLAY_DEVICE_INFO_NUMOFBAT 		6
#define DISPLAY_DEVICE_INFO_NUMOFBPS 		7
#define DISPLAY_DEVICE_INFO_NUMOFEVENTS		8

#define DISPLAY_MAIN						2
#define DISPLAY_MAIN_VOLTAGE					1
#define DISPLAY_MAIN_POWER_ON_OFF				2


#define DISPLAY_INVERTER					3
#define DISPLAY_INVERTER_VOLTAGE				1
#define DISPLAY_INVERTER_CURRENT				2
#define DISPLAY_INVERTER_TEMPERATURE			3

#define DISPLAY_BATTERY						4
#define DISPLAY_BATTERY_VOLTAGE					1
#define DISPLAY_BATTERY_CURRENT					2

#define DISPLAY_SPECIALS					5
#define DISPLAY_ALARM_STATUS				 	1

#define DISPLAY_ETH_SETTINGS				7
#define DISPLAY_ETH_SETTINGS_IP					1
#define DISPLAY_ETH_SETTINGS_NET_MASK			2
#define DISPLAY_ETH_SETTINGS_DEF_GATW			3

#define DISPLAY_SNMP_SETTINGS				8
#define DISPLAY_SNMP_SETTINGS_READ_PORT			1
#define DISPLAY_SNMP_SETTINGS_WRITE_PORT		2
#define DISPLAY_SNMP_SETTINGS_READ_COMMUNITY	3
#define DISPLAY_SNMP_SETTINGS_WRITE_COMMUNITY	4
#define DISPLAY_SNMP_SETTINGS_TRAP_SERVER_1		5
#define DISPLAY_SNMP_SETTINGS_TRAP_SERVER_2		6
#define DISPLAY_SNMP_SETTINGS_TRAP_SERVER_3		7
#define DISPLAY_SNMP_SETTINGS_TRAP_SERVER_4		8
#define DISPLAY_SNMP_SETTINGS_TRAP_SERVER_5		9

#define DISPLAY_TRAP_SETTINGS				9
#define	DISPLAY_TRAP_SETTINGS_MAIN_POWER_TRAP_SEND_OF_AV				1
#define	DISPLAY_TRAP_SETTINGS_MAIN_POWER_TRAP_SEND_OF_NO_AV				2
#define	DISPLAY_TRAP_SETTINGS_INVERTER_TEMPERATURE_TRAP_SEND_OF_AV		3
#define	DISPLAY_TRAP_SETTINGS_INVERTER_TEMPERATURE_TRAP_SEND_OF_NO_AV	4
#define	DISPLAY_TRAP_SETTINGS_INVERTER_VOLT_TRAP_SEND_OF_AV				5
#define	DISPLAY_TRAP_SETTINGS_INVERTER_VOLT_TRAP_SEND_OF_NO_AV			6
#define	DISPLAY_TRAP_SETTINGS_INVERTER_CURR_TRAP_SEND_OF_AV				7
#define	DISPLAY_TRAP_SETTINGS_INVERTER_CURR_TRAP_SEND_OF_NO_AV			8
#define	DISPLAY_TRAP_SETTINGS_BATTERY_VOLTAGE_TRAP_SEND_OF_AV			9
#define	DISPLAY_TRAP_SETTINGS_BATTERY_VOLTAGE_TRAP_SEND_OF_NO_AV		10

#define DISPLAY_SPEC					12
#define DISPLAY_SPEC_TRAP_MESSAGE			1
#define DISPLAY_SPEC_TRAP_VALUE_0			2
#define DISPLAY_SPEC_TRAP_VALUE_1			3
#define DISPLAY_SPEC_TRAP_VALUE_2			4


#define LCD_SIZE 200

#define SNMP_COMMAND				8
#define COMMAND_ANSWER					1
#define COMMAND_PARAMETR					2

#define SYSPARAMS					10
#define SYSPARAMSMAINPSU					20
#define SYSPARAMSSOUNDALARMEN				40
#define SYSPARAMSALARMAUTODISABLE			41
#define SYSPARAMS_BAT_TEST_TIME			42
#define SYSPARAMS_U_MAX					49
#define SYSPARAMS_U_0_GRAD				50
#define SYSPARAMS_U_20_GRAD				51 
#define SYSPARAMS_U_SIGN					52
#define SYSPARAMS_U_MIN_POWER				53
#define SYSPARAMS_U_WITHOUT_BAT			54
#define SYSPARAMS_IBK					55
#define SYSPARAMS_IZMAX					56
#define SYSPARAMS_IMAX					57
#define SYSPARAMS_KIMAX					58
#define SYSPARAMS_KVZ					59
#define SYSPARAMS_TZAS					60
#define SYSPARAMS_TMAX					61	


 #define COMMAND_OK		0x5555
#define COMAND_FAIL		0xaaaa
#define COMMAND_INVALID	0xeeee
#define WRONG_PARAMETER	0xeeef

extern const char sm_mont[13][4]; //
extern signed short main_cnt;
extern char plazma_pal;
extern signed short rele_cnt;
extern char bRELE;
