#include "25lc640.h"
#include "memo.h"
#include "eeprom_map.h"
#include "main.h"
//#include "snmp_data_file.h"
#include "control.h"

//-----------------------------------------------
void memo_read (void)
{
char i;
//Ktsrc[0]=lc640_read_int(KTSRC1);

U_MAX=lc640_read_int(EE_U_MAX);
U_MIN=lc640_read_int(EE_U_MIN);
I_MAX=lc640_read_int(EE_I_MAX);
I_MIN=lc640_read_int(EE_I_MIN);
T_MAX=lc640_read_int(EE_T_MAX);
T_SIGN=lc640_read_int(EE_T_SIGN);
if(!I_ug_block_cnt)I_ug=lc640_read_int(EE_I_UG);
I_ug2=lc640_read_int(EE_I_UG2);
I_ug3=lc640_read_int(EE_I_UG3);
if(!U_up_block_cnt)U_up=lc640_read_int(EE_U_UP);
U_up2=lc640_read_int(EE_U_UP2);
U_up3=lc640_read_int(EE_U_UP3);
U_maxg=lc640_read_int(EE_U_MAX_G);
I_maxp=lc640_read_int(EE_I_MAX_P);
if(!T_PROC_GS_block_cnt)T_PROC_GS=lc640_read_long(EE_T_PROC_GS);
if(!T_PROC_PS_block_cnt)T_PROC_PS=lc640_read_long(EE_T_PROC_PS);
T_PROC_MAX=lc640_read_long(EE_T_PROC_MAX);
TIME_VISION=lc640_read_int(EE_TIME_VISION);
TIME_VISION_PULT=lc640_read_int(EE_TIME_VISION_PULT);
I_LOAD_MODE=lc640_read_int(EE_I_LOAD_MODE);
main_menu_mode=(enum_main_menu_mode)lc640_read_int(EE_MAIN_MENU_MODE);
restart_enable=(enum_restart_enable)lc640_read_int(EE_RESTART_ENABLE);
T_PROC_GS_MODE=lc640_read_long(EE_T_PROC_GS_MODE);
T_PROC_PS_MODE=lc640_read_long(EE_T_PROC_PS_MODE);
MODBUS_ADRESS=lc640_read_int(EE_MODBUS_ADRESS);
MODBUS_BAUDRATE=lc640_read_int(EE_MODBUS_BAUDRATE);
RELE_LOG=lc640_read_int(EE_RELE_LOG);
T_DEL_REL_START=lc640_read_int(EE_T_DEL_REL_START);		
T_DEL_REL_WRK=lc640_read_int(EE_T_DEL_REL_WRK);			
DELT_REL_U=lc640_read_int(EE_DELT_REL_U);				
DELT_REL_I=lc640_read_int(EE_DELT_REL_I);
//REV_STAT=lc640_read_int(EE_REV_STAT);
REV_IS_ON=lc640_read_int(EE_REV_IS_ON);
AVT_REV_IS_ON=lc640_read_int(EE_AVT_REV_IS_ON);
AVT_REV_TIME_FF=lc640_read_int(EE_AVT_REV_TIME_FF);
AVT_REV_TIME_REW=lc640_read_int(EE_AVT_REV_TIME_REW);
AVT_REV_TIME_PAUSE=lc640_read_int(EE_AVT_REV_TIME_PAUSE);
AVT_REV_I_NOM_FF=lc640_read_int(EE_AVT_REV_I_NOM_FF);
AVT_REV_I_NOM_REW=lc640_read_int(EE_AVT_REV_I_NOM_REW);
AVT_REV_U_NOM_FF=lc640_read_int(EE_AVT_REV_U_NOM_FF);
AVT_REV_U_NOM_REW=lc640_read_int(EE_AVT_REV_U_NOM_REW);
			
/*
Kubat[0]=lc640_read_int(EE_KUBAT1);
Kubat[1]=lc640_read_int(EE_KUBAT2);
Kubatm[0]=lc640_read_int(EE_KUBATM1);
Kubatm[1]=lc640_read_int(EE_KUBATM2); */
Kiload0=lc640_read_int(EE_KILOAD0);
Kiload1=lc640_read_int(EE_KILOAD1);
Kuload=lc640_read_int(EE_KULOAD);
/*
Kunet_ext[0]=lc640_read_int(EE_KUNET_EXT0);
Kunet_ext[1]=lc640_read_int(EE_KUNET_EXT1);
Kunet_ext[2]=lc640_read_int(EE_KUNET_EXT2);
Kvv_eb2[0]=lc640_read_int(EE_KVV0_EB2);
Kvv_eb2[1]=lc640_read_int(EE_KVV1_EB2);
Kvv_eb2[2]=lc640_read_int(EE_KVV2_EB2);
Kpes_eb2[0]=lc640_read_int(EE_KPES0_EB2);
Kpes_eb2[1]=lc640_read_int(EE_KPES1_EB2);
Kpes_eb2[2]=lc640_read_int(EE_KPES2_EB2);
KunetA=lc640_read_int(EE_KUNETA);
KunetB=lc640_read_int(EE_KUNETB);
KunetC=lc640_read_int(EE_KUNETC);
*/

Ktext[0]=lc640_read_int(KT_EXT0);
Ktext[1]=lc640_read_int(KT_EXT1);
Ktext[2]=lc640_read_int(KT_EXT2);
	
//MAIN_IST=lc640_read_int(EE_MAIN_IST);
//UMAX=lc640_read_int(EE_UMAX);
UB0=lc640_read_int(EE_UB0);
UB20=lc640_read_int(EE_UB20);
//TMAX=lc640_read_int(EE_TMAX);
TSIGN=lc640_read_int(EE_TSIGN);
DU=lc640_read_int(EE_DU);
USIGN=lc640_read_int(EE_USIGN);
UMN=lc640_read_int(EE_UMN);
ZV_ON=0;
IKB=lc640_read_int(EE_IKB);
//UVZ=lc640_read_int(EE_UVZ);
IMAX=lc640_read_int(EE_IMAX);
IMIN=lc640_read_int(EE_IMIN);
APV_ON=lc640_read_int(EE_APV_ON);
IZMAX=lc640_read_int(EE_IZMAX);
U0B=lc640_read_int(EE_U0B);
TZAS=lc640_read_int(EE_TZAS);
NUMIST=lc640_read_int(EE_NUMIST);
//gran(&NUMIST,0,8);
NUMINV=lc640_read_int(EE_NUMINV);
gran(&NUMINV,0,8);
NUMSK=lc640_read_int(EE_NUMSK);
NUMDT=lc640_read_int(EE_NUMDT);
NUMAVT=lc640_read_int(EE_NUMAVT);
NUMEXT=NUMSK+NUMDT;
AV_OFF_AVT=lc640_read_int(EE_AV_OFF_AVT);
MNEMO_ON=(enum_mnemo_on)lc640_read_int(EE_MNEMO_ON);
MNEMO_TIME=lc640_read_int(EE_MNEMO_TIME);
U_AVT=lc640_read_int(EE_U_AVT);
PAR=lc640_read_int(EE_PAR);
TBATMAX=lc640_read_int(EE_TBATMAX);
TBATSIGN=lc640_read_int(EE_TBATSIGN);
UBM_AV=lc640_read_int(EE_UBM_AV);
//TBOXMAX=lc640_read_int(EE_TBOXMAX);
//TBOXREG=lc640_read_int(EE_TBOXREG);
//TBOXVENTMAX=lc640_read_int(EE_TBOXVENTMAX);
//TLOADDISABLE=lc640_read_int(EE_TLOADDISABLE);
//TLOADENABLE=lc640_read_int(EE_TLOADENABLE);
//TBATDISABLE=lc640_read_int(EE_TBATDISABLE);
//TBATENABLE=lc640_read_int(EE_TBATENABLE);


BAT_IS_ON[0]=(enum_bat_is_on)lc640_read_int(EE_BAT1_IS_ON);
BAT_IS_ON[1]=(enum_bat_is_on)lc640_read_int(EE_BAT2_IS_ON);
NUMBAT=0;
if(BAT_IS_ON[0]==bisON)NUMBAT+=1;
if(BAT_IS_ON[1]==bisON)NUMBAT+=1;

BAT_DAY_OF_ON[0]=lc640_read_int(EE_BAT1_DAY_OF_ON);
BAT_MONTH_OF_ON[0]=lc640_read_int(EE_BAT1_MONTH_OF_ON);
BAT_YEAR_OF_ON[0]=lc640_read_int(EE_BAT1_YEAR_OF_ON);
BAT_C_REAL[0]=lc640_read_int(EE_BAT1_C_REAL);
BAT_C_NOM[0]=lc640_read_int(EE_BAT1_C_NOM);
BAT_RESURS[0]=lc640_read_int(EE_BAT1_RESURS);

BAT_DAY_OF_ON[1]=lc640_read_int(EE_BAT2_DAY_OF_ON);
BAT_MONTH_OF_ON[1]=lc640_read_int(EE_BAT2_MONTH_OF_ON);
BAT_YEAR_OF_ON[1]=lc640_read_int(EE_BAT2_YEAR_OF_ON);
BAT_C_REAL[1]=lc640_read_int(EE_BAT2_C_REAL);
BAT_C_NOM[1]=lc640_read_int(EE_BAT2_C_NOM);
BAT_RESURS[1]=lc640_read_int(EE_BAT2_RESURS);

CAP_ZAR_TIME=lc640_read_int(EE_CAP_ZAR_TIME);
CAP_PAUSE1_TIME=lc640_read_int(EE_CAP_PAUSE1_TIME);
CAP_RAZR_TIME=lc640_read_int(EE_CAP_RAZR_TIME);
CAP_PAUSE2_TIME=lc640_read_int(EE_CAP_PAUSE2_TIME);
CAP_MAX_VOLT=lc640_read_int(EE_CAP_MAX_VOLT);
CAP_WRK_CURR=lc640_read_int(EE_CAP_WRK_CURR);


APV_ON1=(enum_apv_on)lc640_read_int(EE_APV_ON1);
APV_ON2=(enum_apv_on)lc640_read_int(EE_APV_ON2);
APV_ON2_TIME=lc640_read_int(EE_APV_ON2_TIME);
VZ_HR=lc640_read_int(EE_VZ_HR);
TBAT=lc640_read_int(EE_TBAT);

AUSW_MAIN=lc640_read_int(EE_AUSW_MAIN);
	AUSW_MAIN_NUMBER=lc640_read_long(EE_AUSW_MAIN_NUMBER);
	AUSW_DAY=lc640_read_int(EE_AUSW_DAY);
	AUSW_MONTH=lc640_read_int(EE_AUSW_MONTH);
	AUSW_YEAR=lc640_read_int(EE_AUSW_YEAR);
	AUSW_BPS1_NUMBER=lc640_read_long(EE_AUSW_BPS1_NUMBER);
	AUSW_BPS2_NUMBER=lc640_read_long(EE_AUSW_BPS2_NUMBER);
	AUSW_RS232=lc640_read_int(EE_AUSW_RS232);
	AUSW_PDH=lc640_read_int(EE_AUSW_PDH);
	AUSW_SDH=lc640_read_int(EE_AUSW_SDH);
	AUSW_ETH=lc640_read_int(EE_AUSW_ETH);
	AUSW_UKU=lc640_read_int(EE_AUSW_UKU);
	AUSW_UKU_SUB=lc640_read_int(EE_AUSW_UKU_SUB);
	AUSW_UKU_NUMBER=lc640_read_long(EE_AUSW_UKU_NUMBER);			


TMAX_EXT_EN[0]=lc640_read_int(EE_TMAX_EXT_EN0);
TMAX_EXT[0]=lc640_read_int(EE_TMAX_EXT0);
TMIN_EXT_EN[0]=lc640_read_int(EE_TMIN_EXT_EN0);
TMIN_EXT[0]=lc640_read_int(EE_TMIN_EXT0);	
T_EXT_REL_EN[0]=lc640_read_int(EE_T_EXT_REL_EN0);
T_EXT_ZVUK_EN[0]=lc640_read_int(EE_T_EXT_ZVUK_EN0);
T_EXT_LCD_EN[0]=lc640_read_int(EE_T_EXT_LCD_EN0);
T_EXT_RS_EN[0]=lc640_read_int(EE_T_EXT_RS_EN0);
SK_SIGN[0]=lc640_read_int(EE_SK_SIGN0);
SK_REL_EN[0]=lc640_read_int(EE_SK_REL_EN0);
SK_ZVUK_EN[0]=lc640_read_int(EE_SK_ZVUK_EN0);
SK_LCD_EN[0]=lc640_read_int(EE_SK_LCD_EN0);	
SK_RS_EN[0]=lc640_read_int(EE_SK_RS_EN0);
SK_SIGN[1]=lc640_read_int(EE_SK_SIGN1);
SK_REL_EN[1]=lc640_read_int(EE_SK_REL_EN1);
SK_ZVUK_EN[1]=lc640_read_int(EE_SK_ZVUK_EN1);
SK_LCD_EN[1]=lc640_read_int(EE_SK_LCD_EN1);	
SK_RS_EN[1]=lc640_read_int(EE_SK_RS_EN1);
SK_SIGN[2]=lc640_read_int(EE_SK_SIGN2);
SK_REL_EN[2]=lc640_read_int(EE_SK_REL_EN2);
SK_ZVUK_EN[2]=lc640_read_int(EE_SK_ZVUK_EN2);
SK_LCD_EN[2]=lc640_read_int(EE_SK_LCD_EN2);	
SK_RS_EN[2]=lc640_read_int(EE_SK_RS_EN2);
SK_SIGN[3]=lc640_read_int(EE_SK_SIGN3);
SK_REL_EN[3]=lc640_read_int(EE_SK_REL_EN3);
SK_ZVUK_EN[3]=lc640_read_int(EE_SK_ZVUK_EN3);
SK_LCD_EN[3]=lc640_read_int(EE_SK_LCD_EN3);	


AVZ=(enum_avz)(lc640_read_int(EE_AVZ));
//AVZ_TIME=lc640_read_int(EE_AVZ_TIME);
//HOUR_AVZ=lc640_read_int(EE_HOUR_AVZ);
MIN_AVZ=lc640_read_int(EE_MIN_AVZ);
SEC_AVZ=lc640_read_int(EE_SEC_AVZ);
DATE_AVZ=lc640_read_int(EE_DATE_AVZ);
MONTH_AVZ=lc640_read_int(EE_MONTH_AVZ);
if(!((MONTH_AVZ>0)&&(MONTH_AVZ<13)))MONTH_AVZ=0;
YEAR_AVZ=lc640_read_int(EE_YEAR_AVZ);

pos_vent=lc640_read_int(EE_POS_VENT);
POWER_CNT_ADRESS=lc640_read_int(EE_POWER_CNT_ADRESS);

ETH_IS_ON=lc640_read_int(EE_ETH_IS_ON);
ETH_DHCP_ON=lc640_read_int(EE_ETH_DHCP_ON);
ETH_IP_1=lc640_read_int(EE_ETH_IP_1);
ETH_IP_2=lc640_read_int(EE_ETH_IP_2);
ETH_IP_3=lc640_read_int(EE_ETH_IP_3);
ETH_IP_4=lc640_read_int(EE_ETH_IP_4);
ETH_MASK_1=lc640_read_int(EE_ETH_MASK_1);
ETH_MASK_2=lc640_read_int(EE_ETH_MASK_2);
ETH_MASK_3=lc640_read_int(EE_ETH_MASK_3);
ETH_MASK_4=lc640_read_int(EE_ETH_MASK_4);
ETH_GW_1=lc640_read_int(EE_ETH_GW_1);
ETH_GW_2=lc640_read_int(EE_ETH_GW_2);
ETH_GW_3=lc640_read_int(EE_ETH_GW_3);
ETH_GW_4=lc640_read_int(EE_ETH_GW_4);
ETH_TRAP1_IP_1=lc640_read_int(EE_ETH_TRAP1_IP_1);
ETH_TRAP1_IP_2=lc640_read_int(EE_ETH_TRAP1_IP_2);
ETH_TRAP1_IP_3=lc640_read_int(EE_ETH_TRAP1_IP_3);
ETH_TRAP1_IP_4=lc640_read_int(EE_ETH_TRAP1_IP_4);
ETH_TRAP2_IP_1=lc640_read_int(EE_ETH_TRAP2_IP_1);
ETH_TRAP2_IP_2=lc640_read_int(EE_ETH_TRAP2_IP_2);
ETH_TRAP2_IP_3=lc640_read_int(EE_ETH_TRAP2_IP_3);
ETH_TRAP2_IP_4=lc640_read_int(EE_ETH_TRAP2_IP_4);
ETH_TRAP3_IP_1=lc640_read_int(EE_ETH_TRAP3_IP_1);
ETH_TRAP3_IP_2=lc640_read_int(EE_ETH_TRAP3_IP_2);
ETH_TRAP3_IP_3=lc640_read_int(EE_ETH_TRAP3_IP_3);
ETH_TRAP3_IP_4=lc640_read_int(EE_ETH_TRAP3_IP_4);
ETH_TRAP4_IP_1=lc640_read_int(EE_ETH_TRAP4_IP_1);
ETH_TRAP4_IP_2=lc640_read_int(EE_ETH_TRAP4_IP_2);
ETH_TRAP4_IP_3=lc640_read_int(EE_ETH_TRAP4_IP_3);
ETH_TRAP4_IP_4=lc640_read_int(EE_ETH_TRAP4_IP_4);
ETH_TRAP5_IP_1=lc640_read_int(EE_ETH_TRAP5_IP_1);
ETH_TRAP5_IP_2=lc640_read_int(EE_ETH_TRAP5_IP_2);
ETH_TRAP5_IP_3=lc640_read_int(EE_ETH_TRAP5_IP_3);
ETH_TRAP5_IP_4=lc640_read_int(EE_ETH_TRAP5_IP_4);
ETH_SNMP_PORT_READ=lc640_read_int(EE_ETH_SNMP_PORT_READ);
ETH_SNMP_PORT_WRITE=lc640_read_int(EE_ETH_SNMP_PORT_WRITE);
/* ---
for(i=0;i<64;i++)
	{
	snmp_location[i]=lc640_read(EE_LOCATION+i);
	}*/
for(i=0;i<10;i++)
	{
	snmp_Community[i]=lc640_read(EE_COMMUNITY+(i*2));
	}


if(I_ug_block_cnt)
	{
	I_ug_block_cnt--;
	if(!I_ug_block_cnt)
		{
		lc640_write_int(EE_I_UG,I_ug);
		}
	}

if(U_up_block_cnt)
	{
	U_up_block_cnt--;
	if(!U_up_block_cnt)
		{
		lc640_write_int(EE_U_UP,U_up);
		}
	}

if(T_PROC_GS_block_cnt)
	{
	T_PROC_GS_block_cnt--;
	if(!T_PROC_GS_block_cnt)
		{
		lc640_write_long(EE_T_PROC_GS,T_PROC_GS);
		}
	}

if(T_PROC_PS_block_cnt)
	{
	T_PROC_PS_block_cnt--;
	if(!T_PROC_PS_block_cnt)
		{
		lc640_write_long(EE_T_PROC_PS,T_PROC_PS);
		}
	}
}


