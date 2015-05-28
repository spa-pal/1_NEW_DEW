#include "25lc640.h"
#include "control.h"
//#include "mess.h"
//#include "gran.h"
//#include "common_func.h"
#include "eeprom_map.h"
#include "avar_hndl.h"
#include "main.h"
#include "beeper_drv.h"
#include <LPC17xx.h>
#include "led_break_drv.h"
#include "snmp_data_file.h"
char chch;

//#define KOEFPOT  105L
//
//
//
//
//
//
//
//extern signed short u_necc,u_necc_,u_necc_up,u_necc_dn;
//extern signed short main_cnt_5Hz;
//extern signed short num_necc;
//extern signed short num_necc_Imax;
//extern signed short num_necc_Imin;
////extern char bSAME_IST_ON;
////extern signed short Unet,unet_store;
////extern char bat_cnt_to_block[2];
////extern enum  {bisON=0x0055,bisOFF=0x00aa}BAT_IS_ON[2];
//extern signed mat_temper;
//
//
//
//
////***********************************************
////Аварии
//typedef struct  
//	{
//     unsigned int bAN:1; 
//     unsigned int bAB1:1; 
//     unsigned int bAB2:1;
//     unsigned int bAS1:1;
//     unsigned int bAS2:1;
//     unsigned int bAS3:1;
//     unsigned int bAS4:1;
//     unsigned int bAS5:1;
//     unsigned int bAS6:1;
//     unsigned int bAS7:1;
//     unsigned int bAS8:1;
//     unsigned int bAS9:1;
//     unsigned int bAS10:1;
//     unsigned int bAS11:1;
//     unsigned int bAS12:1;
//     }avar_struct;
//     
//extern union 
//{
//avar_struct av;
//int avar_stat;
//}a__,a_;
//
//***********************************************
//АЦП
long adc_buff[16][16];
//signed short adc_buff_max[12],adc_buff_min[12]={5000,5000,5000,5000,5000,5000,5000,5000,5000,5000},unet_buff_max,unet_buff_min=5000;
char adc_self_ch_cnt/*,adc_ch_net*/;
short adc_buff_[16];
char adc_cnt,adc_cnt1,adc_ch,adc_ch_cnt;
//short zero_cnt;
//enum_adc_stat adc_stat=asCH;
unsigned short net_buff[32],net_buff_;
char net_buff_cnt;
//short ADWR,period_cnt,non_zero_cnt;
//char rele_stat;
//char bRELE_OUT;
signed short adc_self_ch_buff[3],adc_self_ch_disp[3];
//long main_power_buffer[8],main_power_buffer_;
short adc_result;
//short main_power_buffer_cnt;
//short adc_gorb_cnt,adc_zero_cnt;
//char adc_window_flag;
//short adc_window_cnt;
short adc_net_buff_cnt;
//
//
//extern int mess_par0[MESS_DEEP],mess_par1[MESS_DEEP],mess_data[2];
//
//extern signed short TBAT;
//extern signed short Kunet;
//extern signed short Kubat[2];
//extern unsigned short ad7705_buff[2][16],ad7705_buff_[2];
//extern unsigned short Kibat0[2];
//extern signed short Kibat1[2];
//extern signed short Ktbat[2];
////extern signed short bat_Ib[2];
//short adc_buff_out_[3];
//extern char kb_full_ver;
//extern signed short Kuload;
//
//signed short bat_ver_cnt=150;
//extern signed short Isumm;
//extern signed short Isumm_;
//extern char ND_out[3];
////extern signed short tout[4];
//
//
//short plazma_adc_cnt;
//
//extern char cntrl_plazma;
//
////extern const short ptr_bat_zar_cnt[2];
//
////***********************************************
////Управление вентилятором
//signed char vent_stat=0;
//
////***********************************************
////Управление ШИМом
//signed short cntrl_stat=600;
//signed short cntrl_stat_old=600;
//signed short cntrl_stat_new;
//signed short Ibmax;
//
////***********************************************
////Самокалиброввка
//signed short samokalibr_cnt;
//
//
//
////***********************************************
////Выравнивание токов
//short avg_main_cnt=20;
//short i_avg_max,i_avg_min,i_avg_summ,i_avg; 
//short avg;
//char bAVG;
//char avg_cnt;  
//char avg_num; 
//
////**********************************************
////Контроль наличия батарей
//signed short 	main_kb_cnt;
//signed short 	kb_cnt_1lev;
//signed short 	kb_cnt_2lev;
//char 		kb_full_ver;
//char kb_start[2];
//
////**********************************************
////Работа с БПСами
//char num_of_wrks_bps;
//char bps_all_off_cnt,bps_mask_off_cnt,bps_mask_on_off_cnt;
//char bps_hndl_2sec_cnt;
//unsigned short bps_on_mask,bps_off_mask;
//
////***********************************************
////Спецфункции
//enum_spc_stat spc_stat;
//char spc_bat;
//char spc_phase;
//unsigned short vz_cnt_s,vz_cnt_h,vz_cnt_h_;
//char bAVZ;
//enum_ke_start_stat ke_start_stat;
//short cnt_end_ke;
//unsigned long ke_date[2];
//
////***********************************************
////Аварии
//extern unsigned avar_stat;	 	//"Отображение" всех аварийных в данный момент устройств в одном месте
//extern unsigned avar_ind_stat; 	//"Отображение" всех не просмотренных аварийных устройств в одном месте
//extern unsigned avar_stat_old;
//extern unsigned avar_stat_new,avar_stat_offed;
////Структура переменных
////1бит  - питающая сеть
////2бита - батареи
////12бит - БПСы
////5бит  - инверторы
////4бита - внешние датчики температуры
////4бита - внешние сухие контакты
//
//
//short cntrl_stat_blok_cnt,cntrl_stat_blok_cnt_,cntrl_stat_blok_cnt_plus[2],cntrl_stat_blok_cnt_minus[2];
//
////-----------------------------------------------
//void ke_start(char in)
//{          
//ke_start_stat=(enum_ke_start_stat)0;
//
//if(spc_stat==spcVZ)ke_start_stat=kssNOT_VZ;
//else
//	{
//	ke_start_stat=kssYES;
//
//	spc_stat=spcKE;
//	spc_bat=in;
//	bat[in]._zar_cnt_ke=0;
//	lc640_write_int(ADR_EE_BAT_ZAR_CNT_KE[in],0);
//	spc_phase=0;
//
//		{					
//		signed temp_temp;
//		signed char temp;
//		temp_temp=bat[in]._u_old[((bat_u_old_cnt+1)&0x07)]; 
//		    
//		temp=LPC_RTC->YEAR;
//		gran_char(&temp,1,99);
//		*((char*)(&(ke_date[0])))=temp;
//			
//		temp=LPC_RTC->MONTH;
//		gran_char(&temp,1,12);
//		*(((char*)(&(ke_date[0])))+1)=temp;
//		
//		temp=LPC_RTC->DOM;
//		gran_char(&temp,1,31);
//		*(((char*)(&(ke_date[0])))+2)=temp;			
//				
//		*(((char*)(&(ke_date[0])))+3)=*((char*)&temp_temp);
//		temp=LPC_RTC->HOUR;
//		gran_char(&temp,0,23);
//		*((char*)(&(ke_date[1])))=temp;
//               
//		temp=LPC_RTC->MIN;
//		gran_char(&temp,0,59);
//		*(((char*)(&(ke_date[1])))+1)=temp;
//	          
//		temp=LPC_RTC->SEC;
//		gran_char(&temp,0,59);
//		*(((char*)(&(ke_date[1])))+2)=temp;
//			
//		*(((char*)(&(ke_date[1])))+3)=*(((char*)&temp_temp)+1);
//		}
//
//	}
//}
//
////-----------------------------------------------
//void ke_drv(void)
//{
//
//if(spc_stat==spcKE)
//	{
//	if(spc_phase==0)
//		{
//		mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-spc_bat)),20);
//		mess_send(MESS2BPS_HNDL,PARAM_BPS_ALL_OFF_AFTER_2SEC,0xffff,20);
//
//		bat[spc_bat]._zar_cnt_ke+=abs(bat[spc_bat]._Ib);
//	    	
//		if(bat[spc_bat]._zar_cnt_ke>=AH_CONSTANT)
//			{
//			bat[spc_bat]._zar_cnt_ke-=AH_CONSTANT;
//			lc640_write_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat],lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat])+1);
//			}
//		}
//
//	else if(spc_phase==1)
//		{
//		mess_send(MESS2BAT_HNDL,PARAM_BAT_MASK_OFF_AFTER_2SEC,(1<<(1-spc_bat)),20);
//		}
//
//	if(bat[spc_bat]._Ub<(USIGN*10))
//		{
//		cnt_end_ke++;
//		if(cnt_end_ke>=30)
//			{
//			
//			if((spc_stat==spcKE)&&(spc_phase==0))
//				{
//				lc640_write_int(ADR_EE_BAT_C_REAL[spc_bat],lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat]));
//				ke_mem_hndl(spc_bat,lc640_read_int(ADR_EE_BAT_ZAR_CNT_KE[spc_bat]));
//				lc640_write_int(ADR_EE_BAT_ZAR_CNT[spc_bat],0);
//				cntrl_stat=50;
//				cntrl_stat_old=50;
//				}
//
//			if((BAT_IS_ON[1-spc_bat]) == bisON)
//				{
//				spc_phase=1;
//				}			
//			else spc_stat=spcOFF;
//
//			}
//		}
//	else cnt_end_ke=0;
//
//	if((bat[spc_bat]._Ub>=bat[1-spc_bat]._Ub)&&(spc_phase==1))
//		{
//		spc_stat=spcOFF;
//		}
//	}
///*
//if(spc_stat==spc_KE1p1)
//	{                               
//	ah_cnt0+=abs(Ibat[0]);
//	if(ah_cnt0>=360000)
//		{
//		ah_cnt0=0;
//		ah_cnt1+=1;
//		}
//	
//	if(Ubat[0]<K[UBMIN])
//		{
//		if(cnt_UBMIN)
//			{
//			if(--cnt_UBMIN==0)
//				{
//				if(lc640_read(BAT2_STAT)==ON)spc_stat=spc_KE1p2;
//				else spc_stat=spc_OFF;
//				ke_mem_hndl(0,ah_cnt1);
//				CBAT_EE[0]=(ah_cnt1*10)+(int)(ah_cnt0/36000UL);
//				lc640_write_int(B1_ZAR,0);
//				zar_cnt[0]=0;
//				ce_is_on[0]=cio_ON;
//				}
//			}
//		}
//	else cnt_UBMIN=10;	
//	}
//	
//else if(spc_stat==spc_KE1p2)
//	{
//	if(Ubat[0]>=Ubat[1])
//		{
//		if(cnt_UBMIN)
//			{
//			if(--cnt_UBMIN==0) spc_stat=spc_OFF;
//			}
//		}
//	else cnt_UBMIN=10;	
//	}	
//	
//else if(spc_stat==spc_KE2p1)
//	{
//	ah_cnt0+=abs(Ibat[1]);
//	if(ah_cnt0>=360000)
//		{
//		ah_cnt0=0;
//		ah_cnt1+=1;
//		}	
//	      	
//	if(Ubat[1]<K[UBMIN])
//		{
//		if(cnt_UBMIN)
//			{
//			if(--cnt_UBMIN==0)
//				{
//				if(lc640_read(BAT1_STAT)==ON)spc_stat=spc_KE2p2;
//				else spc_stat=spc_OFF;
//				ke_mem_hndl(1,ah_cnt1);
//				CBAT_EE[1]=(ah_cnt1*10)+(int)(ah_cnt0/36000UL);
//				lc640_write_int(B2_ZAR,0);
//				zar_cnt[1]=0;
//				ce_is_on[1]=cio_ON;
//				}
//			}
//		}
//	else cnt_UBMIN=10;	
//	}
//	
//else if(spc_stat==spc_KE2p2)
//	{
//	if(Ubat[1]>=Ubat[0])
//		{
//		if(cnt_UBMIN)
//			{
//			if(--cnt_UBMIN==0) spc_stat=spc_OFF;
//			}
//		}
//	else cnt_UBMIN=10;	
//	} 
//	
//if((abs(Ibat[0]))<=(2*K[Ibk]))
//	{
//	if(cnt_BAT1_izar<600)cnt_BAT1_izar++;
//	else if(cnt_BAT1_izar>600)cnt_BAT1_izar=0; 
//	
//	cnt_BAT1_izar_=0;	
//	}
//else
//	{
//	if(cnt_BAT1_izar_<60)
//		{
//		cnt_BAT1_izar_++;
//		if(cnt_BAT1_izar_>=60)
//			{
//			cnt_BAT1_izar=0;
//			cnt_BAT1_izar_=0;
//			}
//		}
//	}	
//
//if((abs(Ibat[1]))<=(2*K[Ibk]))
//	{
//	if(cnt_BAT2_izar<600)cnt_BAT2_izar++;
//	else if(cnt_BAT2_izar>600)cnt_BAT2_izar=0; 
//	
//	cnt_BAT2_izar_=0;	
//	}
//else
//	{
//	if(cnt_BAT2_izar_<60)
//		{
//		cnt_BAT2_izar_++;
//		if(cnt_BAT2_izar_>=60)
//			{
//			cnt_BAT2_izar=0;
//			cnt_BAT2_izar_=0;
//			}
//		}
//	}	
//	
//*/			
//}
//
////-----------------------------------------------
//char vz_start(char hour)
//{          
//char out;
//out=0;
//if(spc_stat==spcOFF)
//	{
//	spc_stat=spcVZ;  
//	vz_cnt_h=hour;
//	vz_cnt_h_=0;
//	vz_cnt_s=0;
//	out=1;
//	//vz_mem_hndl(1);
//	}
////else if((spc_stat==spc_KE1p1)||(spc_stat==spc_KE1p2)) out=22; 
////else if((spc_stat==spc_KE2p1)||(spc_stat==spc_KE2p2)) out=33;
////plazma=out;	
//return out;
//}
//
////-----------------------------------------------
//void vz_stop(void)
//{
//if(spc_stat==spcVZ)
//     {
//vz_mem_hndl(vz_cnt_h);          
//vz_cnt_s=0;
//vz_cnt_h=0;
//vz_cnt_h_=0;
//spc_stat=spcOFF;
//     }
//
//}
//
////-----------------------------------------------
//void avz_next_date_hndl(void)
//{
//if((LPC_RTC->MONTH+AVZ)>12)lc640_write_int(EE_YEAR_AVZ,LPC_RTC->YEAR+1);
//else lc640_write_int(EE_YEAR_AVZ,LPC_RTC->YEAR);
//
////lc640_write_int(EE_YEAR_AVZ,6);
//
//if((LPC_RTC->MONTH+AVZ)>12)lc640_write_int(EE_MONTH_AVZ,(LPC_RTC->MONTH+AVZ)-12);
//else lc640_write_int(EE_MONTH_AVZ,LPC_RTC->MONTH+AVZ);                                                 
//
////lc640_write_int(EE_MONTH_AVZ,5);
//
//if(LPC_RTC->DOM>28) lc640_write_int(EE_DATE_AVZ,28);
//else lc640_write_int(EE_DATE_AVZ,LPC_RTC->DOM);
//
////lc640_write_int(EE_DATE_AVZ,4);
//
//lc640_write_int(EE_HOUR_AVZ,LPC_RTC->HOUR);
//lc640_write_int(EE_MIN_AVZ,LPC_RTC->MIN);
//lc640_write_int(EE_SEC_AVZ,LPC_RTC->SEC);
//
//}
//
////-----------------------------------------------
//void avz_drv(void)                               
//{                
//if(AVZ!=AVZ_OFF)
//	{
//	if((LPC_RTC->YEAR==YEAR_AVZ)&&(LPC_RTC->MONTH==MONTH_AVZ)&&(LPC_RTC->DOM==DATE_AVZ)&&(LPC_RTC->HOUR==HOUR_AVZ)&&(LPC_RTC->MIN==MIN_AVZ)&&(LPC_RTC->SEC==SEC_AVZ))
//		{
//		bAVZ=1;
//		}
//	}
//if(bAVZ)
//	{
//	if(vz_start(AVZ_TIME))
//		{
//		bAVZ=0;
//		avz_next_date_hndl();
//		}
//	}	
//
//}
//
////-----------------------------------------------
//void vz_drv(void)
//{ 
//if(spc_stat==spcVZ)
//	{
//	if(vz_cnt_s<3600)
//		{
//		vz_cnt_s++;
//		if(vz_cnt_s>=3600)
//			{
//			vz_cnt_s=0;
//			if(vz_cnt_h)
//				{
//				vz_cnt_h--;
//				vz_cnt_h_++;
//				if(vz_cnt_h==0)
//					{
//					spc_stat=spcOFF;
//			    		//vz_mem_hndl(0);
//					}
//				}
//			}
//		}
//	}
//} 
//
//
//
//
////-----------------------------------------------
//void kb_init(void)
//{
//main_kb_cnt=(TBAT*60)-60/*120*/;
//}
//
////-----------------------------------------------
//void kb_hndl(void)
//{
//
//static signed short ibat[2],ibat_[2];
//
//if(++main_kb_cnt>=TBAT*60)
//	{
//	main_kb_cnt=0;
//	
//	kb_start[0]=0;
//	kb_start[1]=0;
//
//	if( (BAT_IS_ON[0]==bisON) && (bat[0]._Ub>80) && ( (abs(bat[0]._Ib<IKB)) || (bat[0]._av&1) ) ) kb_start[0]=1;
//	if( (BAT_IS_ON[1]==bisON) && (bat[1]._Ub>80) && ( (abs(bat[1]._Ib<IKB)) || (bat[1]._av&1) ) ) kb_start[1]=1;
//	
//	if( (net_av) || (num_of_wrks_bps==0) || ( (spc_stat!=spcOFF) && (spc_stat!=spcVZ) ) ) 
//		{
//		kb_start[0]=0;
//		kb_start[1]=0;
//		}
//
//	if((kb_start[0]==1)||(kb_start[1]==1))
//		{
//		kb_cnt_1lev=10;
//		}
//	else kb_cnt_1lev=0;
//	}
//
//if(kb_cnt_1lev)
//	{
//	kb_cnt_1lev--;
//
//	if(kb_cnt_1lev>5)mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_PLUS,30,15);
//	else if(kb_cnt_1lev>0) mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_MINUS,30,15);
//
//
//	if(kb_cnt_1lev==5)
//		{
//		ibat[0]=abs(bat[0]._Ib);
//		ibat[1]=abs(bat[1]._Ib);
//		}
//	
//	if(kb_cnt_1lev==0)
//		{
//		ibat_[0]=abs(bat[0]._Ib);
//		ibat_[1]=abs(bat[1]._Ib);
//
//		kb_cnt_2lev=0;
//		if( (ibat[0]+ibat_[0]) < IKB ) 
//			{
//			kb_cnt_2lev=10;  
//			}
//		else if(bat[0]._Ub>200)
//			{
//			kb_start[0]=0;
//			avar_bat_hndl(0,0);
//			}
//		
//		if( (ibat[1]+ibat_[1]) < IKB )
//			{
//			kb_cnt_2lev=10;     
//			}
//		else  if(bat[1]._Ub>200)
//			{
//			kb_start[1]=0;
//			avar_bat_hndl(1,0);
//			}
//		}	
//
//
//	}
//else if(kb_cnt_2lev)
//	{
//	kb_cnt_2lev--;
//
//	if(kb_cnt_2lev>5)mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_PLUS,200,15);
//	else if(kb_cnt_2lev>0) mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_MINUS,200,15);
//
//
//	if(kb_cnt_2lev==5)
//		{
//		ibat[0]=abs(bat[0]._Ib);
//		ibat[1]=abs(bat[1]._Ib);
//		}
//	
//	if(kb_cnt_2lev==0)
//		{
//		ibat_[0]=abs(bat[0]._Ib);
//		ibat_[1]=abs(bat[1]._Ib);
//
//		kb_full_ver=0;
//
//		if( (ibat[0]+ibat_[0]) < IKB ) 
//			{
//			kb_full_ver=1;  
//			}
//		else if(bat[0]._Ub>200)			
//			{
//			kb_start[0]=0;
//			avar_bat_hndl(0,0);
//			}
//
//		if( (ibat[1]+ibat_[1]) < IKB )
//			{
//			kb_full_ver=1;     
//			}
//		else	if(bat[1]._Ub>200)		
//			{
//			kb_start[1]=0;
//			avar_bat_hndl(1,0);
//			}
//
//
//		}	
//	}
//
//else if(kb_full_ver)
//	{
//	
//	mess_send(MESS2CNTRL_HNDL,PARAM_CNTRL_STAT_STEP_DOWN,0,15);
//
//	if( abs(bat[0]._Ib) > IKB ) 
//		{
//		if(kb_start[0]==1)
//			{
//			kb_start[0]=0;
//			avar_bat_hndl(0,0);
//			}
//		}
//
//	if( abs(bat[1]._Ib) > IKB ) 
//		{
//		if(kb_start[1]==1)
//			{
//			kb_start[1]=0;
//			avar_bat_hndl(1,0);
//			}
//		}
//
//	if ((kb_start[0]==0) && (kb_start[1]==0)) 
//		{
//		kb_full_ver=0;
//		}
//
//	if(( (mess_find(MESS2KB_HNDL))	&& (mess_data[0]==PARAM_CNTRL_IS_DOWN) ) || (load_U<(USIGN*10)) )
//		{
//		kb_full_ver=0;
//		if((kb_start[0]==1)&&((load_I>(2*IKB)/10))) avar_bat_hndl(0,1);
//		if((kb_start[1]==1)&&((load_I>(2*IKB)/10))) avar_bat_hndl(1,1);
//		}
//	}
//
//}
//
//
//
//
//-----------------------------------------------
void samokalibr_init(void)
{
//samokalibr_cnt=1785;
}
//-----------------------------------------------
void samokalibr_hndl(void)
{
//if(++samokalibr_cnt>=1800)samokalibr_cnt=0;
//
//if(samokalibr_cnt>=1785U)
//	{
//	mess_send(MESS2RELE_HNDL,PARAM_RELE_SAMOKALIBR,1,15);
//	mess_send(MESS2IND_HNDL,PARAM_SAMOKALIBR,0,15);
//	mess_send(MESS2MATEMAT,PARAM_SAMOKALIBR,0,15);
//	} 
//
//if(samokalibr_cnt==1799U)
//	{
//	if(Kibat0[0]!=ad7705_buff_[0]) lc640_write_int(ADR_KI0BAT[0],ad7705_buff_[0]);
//	if(Kibat0[1]!=ad7705_buff_[1]) lc640_write_int(ADR_KI0BAT[1],ad7705_buff_[1]);
//	
//	}	 	
}



////-----------------------------------------------
//void ubat_old_drv(void)
//{        
//bat_u_old_cnt++;
//gran_ring(&bat_u_old_cnt,0,8);
//
//bat[0]._u_old[bat_u_old_cnt]=bat[0]._Ub;
//bat[1]._u_old[bat_u_old_cnt]=bat[1]._Ub;
//}
//
////-----------------------------------------------
void unet_drv(void)
{
if ((snmp_main_voltage<180)&&(main_cnt>3))//(LPC_GPIO1->FIOPIN&(1<<28))
	{
	net_stat_cnt--;
	}
else 
	{
	net_stat_cnt++;
	}
if(net_stat_cnt<-10) net_stat_cnt=-10;
if(net_stat_cnt>10)	net_stat_cnt=10;

if((net_stat_cnt<-5)&&(!net_av))
	{
	avar_unet_hndl(1);
	snmp_main_power_on_off=0;
	}
										 
else if((net_stat_cnt>5)&&(net_av))
	{
	avar_unet_hndl(0);
	snmp_main_power_on_off=1;
	}
}

//-----------------------------------------------
void matemat(void)
{

signed long temp_SL/*,temp_SL_*/;
char /*temp,*/i;


i=NUMB;
	if(bps[i]._cnt<5)
     	{
     	bps[i]._Ii=bps[i]._buff[0]+(bps[i]._buff[1]*256);
     	bps[i]._Uin=bps[i]._buff[2]+(bps[i]._buff[3]*256);
     	bps[i]._Uii=bps[i]._buff[4]+(bps[i]._buff[5]*256);
     	bps[i]._Ti=(signed)(bps[i]._buff[6]);
     	bps[i]._adr_ee=bps[i]._buff[7];
     	bps[i]._flags_tm=bps[i]._buff[8];
	    bps[i]._rotor=bps[i]._buff[10]+(bps[i]._buff[11]*256); 
     	} 
	else 
     	{
     	bps[i]._Uii=0; 
     	bps[i]._Ii=0;
     	bps[i]._Uin=0;
     	bps[i]._Ti=0;
     	bps[i]._flags_tm=0; 
	    bps[i]._rotor=0;
     	}
if (bps[i]._Uii>1900&&bps[i]._Uii<=2400) level_U=(bps[i]._Uii-1900)/50;
else if (bps[i]._Uii>2400) level_U=10;
else level_U=0;
if (level_U>10)	level_U=10;

snmp_inverter_voltage=	bps[i]._Uii/10;

if (bps[i]._Ii>0&&bps[i]._Ii<=155)level_I=bps[i]._Ii*10/150;  // 15A при 150
else if (bps[i]._Ii>155) level_I=0;
else level_I=0;
if (level_I>10)	level_I=10;
//level_I=bps[i]._cnt/6;
snmp_inverter_current=	bps[i]._Ii;

snmp_inverter_temperature=	bps[i]._Ti;
//snmp_inverter_temperature=	but;

//if (bps[i]._Ti>0&&bps[i]._Ti<=80) level_Q=bps[i]._Ti/8;
//else if (bps[i]._Ti>80) level_Q=10;
//else level_Q=0;
temp_SL=(signed long)adc_buff_[0]; //2618 (73V)
temp_SL*=Kubat[0]; // min=1500
temp_SL/=6400L;

snmp_battery_voltage=(signed short)temp_SL;

#ifndef BAT48
if (temp_SL>500&&temp_SL<=720)level_Q=(temp_SL-500)/22;
else if (temp_SL>720) level_Q=10;
else level_Q=0;
if (level_Q>10)	level_Q=10;
#endif

#ifdef BAT48
if (temp_SL>400&&temp_SL<=570)level_Q=(temp_SL-400)/17;
else if (temp_SL>570) level_Q=10;
else level_Q=0;
if (level_Q>10)	level_Q=10;

#endif

temp_SL=(signed long)adc_buff_[1];
temp_SL-=(signed long)Kibat0[0];
temp_SL*=(signed long)Kibat1[0];
temp_SL/=1000L;
snmp_battery_current=(signed short)temp_SL*(-1L);

//snmp_battery_current=(signed short)adc_buff_[1];

//snmp_battery_voltage=(signed short)adc_buff_[1];
//snmp_battery_current=(signed short)Kibat0[0];

//snmp_battery_current=(signed short)adc_buff_[1];

temp_SL=(signed long)adc_buff_[2]; //2618 (73V)
temp_SL*=Kunet; // min=1500
temp_SL/=15000L;
snmp_main_voltage=(signed short)temp_SL;
//snmp_main_voltage=but;
//
//
//
//load_I=-(bat[0]._Ib/10)-(bat[1]._Ib/10);
//
//Isumm=0;
//
//for(i=0;i<NUMIST;i++)
//     {
//     if(bps[i]._cnt<5)Isumm+=bps[i]._Ii;
//     }  
//     
//load_I=load_I+Isumm;
//if(load_I<0)load_I=0;
//
// 
//if (NUMINV)
//	{
//	for(i=4;i<(4+NUMINV);i++)// адресация инверторов начинается с 4			   /**/
//	{
//	if(bps[i]._cnt<25)
//     	{
//     	bps[i]._Ii=bps[i]._buff[0]+(bps[i]._buff[1]*256);
//     	bps[i]._Uin=bps[i]._buff[2]+(bps[i]._buff[3]*256);
//     	bps[i]._Uii=bps[i]._buff[4]+(bps[i]._buff[5]*256);
//     	bps[i]._Ti=(signed)(bps[i]._buff[6]);
//     	bps[i]._adr_ee=bps[i]._buff[7];
//     	bps[i]._flags_tm=bps[i]._buff[8];
//	    bps[i]._rotor=bps[i]._buff[10]+(bps[i]._buff[11]*256);    
//     	} 
//	else 
//     	{
//     	bps[i]._Uii=0; 
//     	bps[i]._Ii=0;
//     	bps[i]._Uin=0;
//     	bps[i]._Ti=0;
//     	bps[i]._flags_tm=0; 
//	    bps[i]._rotor=0;    
//     	}
//     }
//   }						  
}

////-----------------------------------------------
//void mnemo_hndl(void)
//{
//if((ind==iMn)&&(sub_ind==0)&&(MNEMO_ON==mnON))
//	{
//	if(mnemo_cnt)mnemo_cnt--;
//	}
//else mnemo_cnt=MNEMO_TIME;
//}
//
////-----------------------------------------------
void adc_init(void)
{

//SET_REG(LPC_PINCON->PINSEL1,1,(25-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(24-16)*2,2);
SET_REG(LPC_PINCON->PINSEL1,1,(23-16)*2,2);
SET_REG(LPC_PINCON->PINSEL3,3,(31-16)*2,2);

//SET_REG(LPC_PINCON->PINMODE1,2,(25-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(24-16)*2,2);
SET_REG(LPC_PINCON->PINMODE1,2,(23-16)*2,2);
SET_REG(LPC_PINCON->PINMODE3,2,(31-16)*2,2);

SET_REG(LPC_ADC->ADCR,0,24,3);	   // adc stopped

SET_REG(LPC_ADC->ADCR,1,21,1);   // adc active
SET_REG(LPC_ADC->ADCR,0,16,1);   // burst 0
SET_REG(LPC_ADC->ADCR,1,8,8);		// clock


LPC_ADC->ADINTEN     =  (1<< 8);      /* global enable interrupt            */

NVIC_EnableIRQ(ADC_IRQn);             /* enable ADC Interrupt               */


}

//-----------------------------------------------
void adc_drv7(void) //(Uсети - постоянка)
{
//int temp_S;
//char i;
//signed short temp_SS;

adc_self_ch_disp[0]=abs_pal(adc_self_ch_buff[1]-adc_self_ch_buff[0]);//adc_self_ch_buff[0]&0x0f80;
adc_self_ch_disp[1]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[1]);//adc_self_ch_buff[1]&0x0f80;
adc_self_ch_disp[2]=abs_pal(adc_self_ch_buff[2]-adc_self_ch_buff[0]);//adc_self_ch_buff[2]&0x0f80;

//adc_self_ch_disp[0]=adc_self_ch_buff[0]&0x0ff0;
//adc_self_ch_disp[1]=adc_self_ch_buff[1]&0x0ff0;
//adc_self_ch_disp[2]=adc_self_ch_buff[2]&0x0ff0;


if(adc_self_ch_disp[2]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[2];
	} 
else if(adc_self_ch_disp[1]<300)//==adc_self_ch_disp[2])
	{
	adc_result=adc_self_ch_buff[1];
	}
else if(adc_self_ch_disp[0]<300)//==adc_self_ch_disp[1])
	{
	adc_result=adc_self_ch_buff[0];
	}
    //adc_result=92;

//if(adc_ch_net)
//	{

	//main_power_buffer[0]+=(long)(adc_result);
	//main_power_buffer[1]+=(long)(adc_result);
	//main_power_buffer[2]+=(long)(adc_result);
	//main_power_buffer[3]+=(long)(adc_result);

/*	adc_net_buff_cnt++;
	if(adc_net_buff_cnt>=0x1000)
		{
		adc_net_buff_cnt=0;
		}
	if((adc_net_buff_cnt&0x03ff)==0)
		{
		net_buff_=(short)((main_power_buffer[adc_net_buff_cnt>>10])>>8);
		main_power_buffer[adc_net_buff_cnt>>10]=0;
		} */


//	} 
//else if(!adc_ch_net)
	{
	adc_buff[adc_ch][adc_ch_cnt]=(long)adc_result;
	
	if((adc_ch_cnt&0x03)==0)
		{
		long temp_L;
		char i;
		temp_L=0;
		for(i=0;i<16;i++)
			{
			temp_L+=adc_buff[adc_ch][i];
			}
		adc_buff_[adc_ch]= (short)(temp_L>>4);

		//adc_buff_[3]=346;
		}
	if(++adc_ch>=3) 
		{
		adc_ch=0;
		adc_ch_cnt++;
		if(adc_ch_cnt>=16)adc_ch_cnt=0;
		}
	}

//adc_buff[adc_ch][adc_cnt1]=(adc_self_ch_buff[2]+adc_self_ch_buff[1])/2;

//if(adc_buff[adc_ch][adc_cnt1]<adc_buff_min[adc_ch])adc_buff_min[adc_ch]=adc_buff[adc_ch][adc_cnt1];
//if(adc_buff[adc_ch][adc_cnt1]>adc_buff_max[adc_ch])adc_buff_max[adc_ch]=adc_buff[adc_ch][adc_cnt1];
/*
	{
	if((adc_cnt1&0x03)==0)
		{
		temp_S=0;
		for(i=0;i<16;i++)
			{
			temp_S+=adc_buff[adc_ch][i];
			} 
         	adc_buff_[adc_ch]=temp_S>>4;
          }
	}*/


		  

adc_self_ch_cnt=0;

//adc_ch_net++;
//adc_ch_net&=1;

//SET_REG(LPC_GPIO0->FIODIR,7,5,3);
//SET_REG(LPC_GPIO0->FIOPIN,adc_ch,5,3);
/*
if(adc_ch_net)
	{
	LPC_GPIO2->FIODIR|=(1<<7);				 // ??
	LPC_GPIO2->FIOPIN|=(1<<7);
//	SET_REG(LPC_ADC->ADCR,1<<2,0,8);		// AD0.2 P0.25
	}
else
	{
	LPC_GPIO2->FIODIR|=(1<<7);
	LPC_GPIO2->FIOPIN&=~(1<<7);
	if(adc_ch==0)	SET_REG(LPC_ADC->ADCR,1<<0,0,8);   // AD0.0 P0.23
	else 			SET_REG(LPC_ADC->ADCR,1<<1,0,8);	   // AD0.1 P0.24


//	SET_REG(LPC_GPIO0->FIODIR,1,28,1);
//	SET_REG(LPC_GPIO1->FIODIR,1,30,1);
//	SET_REG(LPC_GPIO3->FIODIR,1,26,1);
//
//	if(!(adc_ch&(1<<0)))SET_REG(LPC_GPIO0->FIOPIN,0,28,1);
//	else 			SET_REG(LPC_GPIO0->FIOPIN,1,28,1);
//
//	if(!(adc_ch&(1<<1)))SET_REG(LPC_GPIO1->FIOPIN,0,30,1);
//	else 			SET_REG(LPC_GPIO1->FIOPIN,1,30,1);
//
//	if(!(adc_ch&(1<<2)))SET_REG(LPC_GPIO3->FIOPIN,0,26,1);
//	else 			SET_REG(LPC_GPIO3->FIOPIN,1,26,1);
	}
*/	

if(adc_ch==0)		SET_REG(LPC_ADC->ADCR,1<<0,0,8);   // AD0.0 P0.23
else if(adc_ch==1) 	SET_REG(LPC_ADC->ADCR,1<<1,0,8);	   // AD0.1 P0.24
else if(adc_ch==2) 	SET_REG(LPC_ADC->ADCR,1<<5,0,8);	   // AD0.5 P1.31


LPC_ADC->ADCR |=  (1<<24);	   // start conversion

}


//*************-----------------------------------------------
void rele_hndl(void)
{
LPC_GPIO1->FIODIR|=(1<<23);
if (bps[NUMB]._av&(0x1F)) 
	{
	rele_cnt++;
	if(rele_cnt>50)rele_cnt=50;
	}
else
	{
	rele_cnt--;
	if(rele_cnt<0)rele_cnt=0;
	}
if(rele_cnt>48)bRELE=1;
else if(rele_cnt<2)bRELE=0;

if(bRELE)LPC_GPIO1->FIOCLR|=(1<<23);
else LPC_GPIO1->FIOSET|=(1<<23);
////static char cnt_rel_sam;
////char temp;
//
////temp=0;
//
//
//SET_REG(LPC_PINCON->PINSEL0,0,4*2,6*2);
//SET_REG(LPC_GPIO0->FIODIR,63,4,6);
//SET_REG(LPC_PINCON->PINSEL7,0,(25-16)*2,2);
//SET_REG(LPC_GPIO3->FIODIR,1,25,1);
//SET_REG(LPC_PINCON->PINSEL1,0,(29-16)*2,2);
//SET_REG(LPC_GPIO0->FIODIR,1,29,1);
//
//
//
//
//
//
//if(((bat[0]._rel_stat)  || (tbatdisable_stat!=tbdsON))&&(tbatdisable_cmnd))
//	{
//	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_BAT1,1);
//	}
//else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_BAT1,1);	  	
//
//if(((bat[1]._rel_stat) || (tbatdisable_stat!=tbdsON))&&(tbatdisable_cmnd))
//	{
//	SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_BAT2,1);
//	}
//else SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_BAT2,1);
//
//
//if(mess_find_unvol((MESS2RELE_HNDL))&&(PARAM_RELE_SAMOKALIBR)) 
//	{
//	if(mess_data[1]==1)SET_REG(LPC_GPIO0->FIOSET,1,29,1);
//	else if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,29,1);
//	}
//else SET_REG(LPC_GPIO0->FIOCLR,1,29,1);
//
//
////Реле аварии сети
//if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_NET))
//	{
//	if(mess_data[1]==0) SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
//	else SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
//	}
//else	if(!(avar_ind_stat&0x00000001)) SET_REG(LPC_GPIO3->FIOSET,1,SHIFT_REL_AV_NET,1);
//else SET_REG(LPC_GPIO3->FIOCLR,1,SHIFT_REL_AV_NET,1);
//
//
//#ifdef U
////Реле общей аварии
//if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_COMM))
//	{
//	if(mess_data[1]==0) temp&=~(1<<SHIFT_REL_AV_COMM);
//	else if(mess_data[1]==1) temp|=(1<<SHIFT_REL_AV_COMM);
//	}
//else 
//	{
//     if(  (!(avar_ind_stat&0x00007fff)) &&
//          ((!SK_REL_EN[0]) || (sk_av_stat[0]!=sasON))  &&
//          ((!SK_REL_EN[1]) || (sk_av_stat[1]!=sasON))  &&
//          ((!SK_REL_EN[2]) || (sk_av_stat[2]!=sasON))  /*&&
//          ((!SK_REL_EN[3]) || (sk_av_stat[3]!=sasON))*/  )temp&=~(1<<SHIFT_REL_AV_COMM);
//     else temp|=(1<<SHIFT_REL_AV_COMM);
//	}
//
//
////Реле осевого вентилятора
//if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_VENT))
//	{
//	if(mess_data[1]==0) temp&=~(1<<SHIFT_REL_VENT);
//	else if(mess_data[1]==1) temp|=(1<<SHIFT_REL_VENT);
//	}
//else 
//	{
//	if(mixer_vent_stat==mvsOFF) temp&=~(1<<SHIFT_REL_VENT);
//     else temp|=(1<<SHIFT_REL_VENT);
//	}
///*
////Реле аварии батарей
//if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_AV_BAT))
//	{
//	if(mess_data[1]==0) temp&=~(1<<SHIFT_REL_AV_BAT);
//	else if(mess_data[1]==1) temp|=(1<<SHIFT_REL_AV_BAT);
//     }
//else 
//	{
//	if(!(avar_ind_stat&0x00000006)) temp&=~(1<<SHIFT_REL_AV_BAT);
//     else temp|=(1<<SHIFT_REL_AV_BAT);
//	} 
//*/
////Реле выключения нагрузки
//if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LOAD_OFF))
//	{
//	if(mess_data[1]==0) temp&=~(1<<SHIFT_REL_LOAD_OFF);
//	else if(mess_data[1]==1) temp|=(1<<SHIFT_REL_LOAD_OFF);
//     }
//else if(tloaddisable_cmnd==0)
//	{
//	temp|=(1<<SHIFT_REL_LOAD_OFF);
//	}
//else if((tloaddisable_cmnd)&&(tloaddisable_cmnd<=11))
//	{
//	temp&=~(1<<SHIFT_REL_LOAD_OFF);
//	}
//
//else 
//	{
//	if(!(tloaddisable_stat==tldsON)) temp&=~(1<<SHIFT_REL_LOAD_OFF);
//     else temp|=(1<<SHIFT_REL_LOAD_OFF);
//	} 
//
//
//
////Реле освещения
//if((mess_find_unvol(MESS2RELE_HNDL))&&	(mess_data[0]==PARAM_RELE_LIGHT))
//	{
//	if(mess_data[1]==0) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
//	else if(mess_data[1]==1) SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
//     }
//else 
//	{
//	if(sk_av_stat[0]!=sasON) SET_REG(LPC_GPIO0->FIOCLR,1,SHIFT_REL_LIGHT,1);
//     else SET_REG(LPC_GPIO0->FIOSET,1,SHIFT_REL_LIGHT,1);
//	}
//
//rele_stat=temp;
//#endif
}

////-----------------------------------------------
//void bps_hndl(void)
//{
//static unsigned char sh_cnt0/*,sh_cnt1,sh_cnt2,*/,b1Hz_sh/*,b2Hz_sh*/;
//char ptr__,i;
//
//if(sh_cnt0<10)
//	{
//	sh_cnt0++;
//	if(sh_cnt0>=10)
//		{
//		sh_cnt0=0;
//		b1Hz_sh=1;
//		}
//	}
//
///*if(sh_cnt1<5)
//	{
//	sh_cnt1++;
//	if(sh_cnt1==5)
//		{
//		sh_cnt1=0;
//		b2Hz_sh=1;
//		}
//	} */
//
//
///*
//if(mess_find(MESS_SRC_ON_OFF))
//	{
//	if(mess_data[0]==_MESS_SRC_MASK_BLOK_2SEC)
//		{
//		char i;
//		for(i=0;i<NUMIST;i++)
//			{
//			if(mess_data[1]&(1<<i))src[i]._ist_blok_cnt=20;
//			}
//		
//		}
//	else if(mess_data[0]==_MESS_SRC_MASK_UNBLOK)
//		{
//		char i;
//		for(i=0;i<NUMIST;i++)
//			{
//			if(mess_data[1]&(1<<i))src[i]._ist_blok_cnt=0;
//			}
//		
//		}
//	}
//	
//else if(mess_find(_MESS_SRC_MASK_ON))
//	{				
//	if(mess_data[0]==_MESS_SRC_MASK_ON)
//		{
//		char i;
//		for(i=0;i<NUMIST;i++)
//			{
//			if(mess_data[1]&(1<<i))
//				{
//				src[i]._ist_blok_cnt=0;
//				src[i]._flags_tu=2;
//				}
//			}
//		
//		}				
//	}*/
//
//
//
///*else*/ 
//bps_on_mask=0;
//bps_off_mask=0;
//
//if(mess_find_unvol(MESS2BPS_HNDL))
//	{
//	if(mess_data[0]==PARAM_BPS_ALL_OFF_AFTER_2SEC)
//		{
//		bps_off_mask=0xffff;
//		}
//
//	if(mess_data[0]==PARAM_BPS_MASK_OFF_AFTER_2SEC)
//		{
//		bps_off_mask=mess_data[1];
//		}
//
//	if(mess_data[0]==PARAM_BPS_MASK_ON)
//		{
//		bps_on_mask=mess_data[1];
//		}
//
//	if(mess_data[0]==PARAM_BPS_ALL_ON)
//		{
//		bps_on_mask=0xffff;
//		}
//
//	if(mess_data[0]==PARAM_BPS_MASK_ON_OFF_AFTER_2SEC)
//		{
//		bps_on_mask=mess_data[1];
//		bps_off_mask=~(mess_data[1]);
//		}
//
//
//	for(i=0;i<=NUMIST;i++)
//		{
//		if(bps_off_mask&(1<<i)) bps[i]._blok_cnt++;
//		else bps[i]._blok_cnt=0;
//		gran(&bps[i]._blok_cnt,0,50);
//		if(bps[i]._blok_cnt>20) bps[i]._flags_tu=1;
//		if(bps_on_mask&(1<<i)) bps[i]._flags_tu=0;
//	     }
//
//	
///*
//
//	if(bps_all_off_cnt>20)
//		{
//		for(i=0;i<=NUMIST;i++)
//			{
//	     	bps[i]._flags_tu=1;
//	     	}
//		}
//	else if(bps_mask_off_cnt>20)
//		{
//		for(i=0;i<=NUMIST;i++)
//			{
//			if(mess_data[1]&(1<<i)) bps[i]._flags_tu=1;
//	     	}
//		}	
//		
//	else if(bps_mask_on_off_cnt>20)
//		{
//		for(i=0;i<=NUMIST;i++)
//			{
//			if(mess_data[1]&(1<<i)) bps[i]._flags_tu=1;
//			else bps[i]._flags_tu=0;
//	     	}
//		}
//		
//	if(mess_data[0]==PARAM_BPS_MASK_ON)
//		{
//		for(i=0;i<=NUMIST;i++)
//			{
//			if(mess_data[1]&(1<<i)) bps[i]._flags_tu=0;
//	     	}
//		}
//*/										
//	}
//
//
//else if(b1Hz_sh)
//	{
//	ptr__=0;
//     for(i=0;i<=NUMIST;i++)
//		{
//	     bps[i]._flags_tu=1;
//	     }	
//  	     
//  	for(i=0;(i<NUMIST)&&(ptr__<num_necc);i++)
//  		{
//  	     if((bps[i]._state==bsRDY)||(bps[i]._state==bsWRK))
//  	         	{
//  	         	bps[i]._flags_tu=0;
//  	         	ptr__++;
//  	         	}
//  	     }
//	if(main_1Hz_cnt<60)
//		{
//     	for(i=0;i<=NUMIST;i++)
//			{
//	     	bps[i]._flags_tu=0;
//	     	}	
//		}	 
//  	}
//
//
//for(i=0;i<NUMIST;i++)
//     {
//     if(bps[i]._ist_blok_host_cnt!=0)
//          {
//          bps[i]._flags_tu=99;
//	     bps[i]._ist_blok_host_cnt--;
//          }
//     }
//
//
//
//
//b1Hz_sh=0;
//
//
//num_of_wrks_bps=0;
//for(i=0;i<NUMIST;i++)
//	{
//	if(bps[i]._state==bsWRK)num_of_wrks_bps++;
//	}
//}
//
//биты аварий в приходящих сообщениях от источников
#define AV_OVERLOAD	0 
#define AV_T	1

#define AVUMAX	3
#define AVUMIN	4

////-----------------------------------------------
//void bps_drv(char in)
//{
//char temp;
//if (bps[in]._device==dINV) return;	       /**/
//
//temp=bps[in]._flags_tm;
//
//if(temp&(1<<AV_T))
//	{
//	if(bps[in]._temp_av_cnt<1200) 
//		{
//		bps[in]._temp_av_cnt++;
//		if(bps[in]._temp_av_cnt>=1200)
//			{
//			bps[in]._temp_av_cnt=1200;
//		   	if(!(bps[in]._av&(1<<0)))avar_bps_hndl(in,0,1);
//			}
//		}
//	}
//
//else if(!(temp&(1<<AV_T)))
//	{
//	if(bps[in]._temp_av_cnt) 
//		{
//		bps[in]._temp_av_cnt--;
//		if(!bps[in]._temp_av_cnt)
//			{
//			if(bps[in]._av&(1<<0))avar_bps_hndl(in,0,0);
//			}
//		} 	
//
//	}
//
//if((temp&(1<<AVUMAX)))
//	{
//	if(bps[in]._umax_av_cnt<10) 
//		{
//		bps[in]._umax_av_cnt++;
//		if(bps[in]._umax_av_cnt>=10)
//			{ 
//			bps[in]._umax_av_cnt=10;
//			if(!(bps[in]._av&(1<<1)))avar_bps_hndl(in,1,1);
//		  	/*if((K[APV]!=ON)||((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afOFF)))avar_s_hndl(in,1,1);
//			if((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afON))
//				{
//				apv_cnt[in,0]=APV_INIT;
//				apv_cnt[in,1]=APV_INIT;
//				apv_cnt[in,2]=APV_INIT;
//				apv_flags[in]=afOFF;
//				}				*/
//						
//			}
//		} 
//	}		
//else if(!(temp&(1<<AVUMAX)))
//	{
//	if(bps[in]._umax_av_cnt>0) 
//		{
//		bps[in]._umax_av_cnt--;
//		if(bps[in]._umax_av_cnt==0)
//			{
//			bps[in]._umax_av_cnt=0;
//			avar_bps_hndl(in,1,0);
//	 //		apv_cnt[in,0]=0;
//	//		apv_cnt[in,1]=0;
//	 //		apv_cnt[in,2]=0;			
//			}
//		}
//	else if(bps[in]._umax_av_cnt<0) bps[in]._umax_av_cnt=0;		 
//	}
//
//if(temp&(1<<AVUMIN))
//	{
//	if(bps[in]._umin_av_cnt<10) 
//		{
//		bps[in]._umin_av_cnt++;
//		if(bps[in]._umin_av_cnt>=10)
//			{ 
//			bps[in]._umin_av_cnt=10;
//			if(!(bps[in]._av&(1<<2)))avar_bps_hndl(in,2,1);
//		  	/*	if((K[APV]!=ON)||((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afOFF)))avar_s_hndl(in,2,1);
//			if((apv_cnt[in,0]==0)&&(apv_cnt[in,1]==0)&&(apv_cnt[in,2]==0)&&(apv_flags[in]==afON))
//				{
//				apv_cnt[in,0]=APV_INIT;
//				apv_cnt[in,1]=APV_INIT;
//				apv_cnt[in,2]=APV_INIT;
//				apv_flags[in]=afOFF;
//				}*/				
//			}
//		} 
//	}	
//	
//else if(!(temp&(1<<AVUMIN)))
//	{
//	if(bps[in]._umin_av_cnt) 
//		{
//		bps[in]._umin_av_cnt--;
//		if(bps[in]._umin_av_cnt==0)
//			{
//			bps[in]._umin_av_cnt=0;
//			avar_bps_hndl(in,2,0);
//		//	apv_cnt[in,0]=0;
//		//	apv_cnt[in,1]=0;
//		//	apv_cnt[in,2]=0;
//			}
//		}
//	else if(bps[in]._umin_av_cnt>10)bps[in]._umin_av_cnt--;	 
//	}
//
//
//
//if (bps[in]._av&0x0f)					bps[in]._state=bsAV;
//else if ( (net_av) && 
//		(bps[in]._Uii<200))				bps[in]._state=bsOFF_AV_NET;
//else if (bps[in]._flags_tm&BIN8(100000))	bps[in]._state=bsRDY;
//else if (bps[in]._cnt<20)				bps[in]._state=bsWRK;
//
//
//
////else if(bps[in]._flags_tm&BIN8(100000)) bps[in]._state=ssBL;
////else if((!(bps[in]._flags_tm&BIN8(100000)))&&(net_U>100))bps[in]._state=ssWRK;
////else bps[0]._state=ssNOT;
//
////bps[in]._is_ready=0;
////bps[in]._is_wrk=0;
////if(bps[in]._av_net) bps[in]._flags_bp='N';// не подключен
////else if(bps[in]._av_u_max) bps[in]._flags_bp='P';// завышено напряжение(u_.av_.bAS1T)) bps_state[0]=ssAV;
////else if(bps[in]._av_u_min) bps[in]._flags_bp='M';// занижено напряжение
////else if(bps[in]._av_temper) bps[in]._flags_bp='T';// температура
////else if(bps[in]._flags_tm&BIN8(100000)) 
////	{
////	bps[in]._flags_bp='B';// заблокирован
////	bps[in]._is_ready=1;
////	}
////else if((!(bps[in]._flags_tm&BIN8(100000)))&&(net_U>100))
////     {
////     bps[in]._flags_bp='W';// работает
////     bps[in]._is_ready=1;
////     bps[in]._is_wrk=1;
//     
////     }
////else bps[in]._is_ready=1;     
//
//
//
//
//
///*
//bps[in]._flags_tu&=BIN8(11111110);
//if(bps[in]._ist_blok_cnt)
//	{
//	bps[in]._ist_blok_cnt--;
//	bps[in]._flags_tu|=BIN8(1);
//	}
//
//	   */ 
//
////Пересброс БПСа при потере связи
//if(bps[in]._cnt>=10) bps[in]._flags_tu|=BIN8(10000000);
//else bps[in]._flags_tu&=BIN8(1111111);
//	
//bps[in]._vol_u=cntrl_stat+bps[in]._x_;	
// 
//}
//
// 
//-----------------------------------------------
void inv_drv(char in)
{
char temp;
//if (bps[in]._device==dSRC) return;	   /**/

temp=bps[in]._flags_tm;

if(bps[in]._Ii>=110&&bps[in]._Ii<=200)
	{
	if(bps[in]._light_overload_av_cnt<10) 
		{
		bps[in]._light_overload_av_cnt++;
		if(bps[in]._light_overload_av_cnt>=10)
			{ 
			bps[in]._light_overload_av_cnt=10;
			if(!(bps[in]._av&(1<<5)))avar_bps_hndl(in,5,1);				
			}
		} 
	}		
else if((bps[in]._Ii<110)&&(bps[in]._Ii>-1))
	{
	if(bps[in]._light_overload_av_cnt>0) 
		{
		bps[in]._light_overload_av_cnt--;
		if(bps[in]._light_overload_av_cnt<=0)
			{
			bps[in]._light_overload_av_cnt=0;
			if(bps[in]._av&(1<<5))avar_bps_hndl(in,5,0);  ///////////
			}
		}
	else if(bps[in]._light_overload_av_cnt<0) bps[in]._light_overload_av_cnt=0;		 
	}


if((temp&(1<<AV_OVERLOAD)))
	{
	if(bps[in]._overload_av_cnt<10) 
		{
		bps[in]._overload_av_cnt++;
		if(bps[in]._overload_av_cnt>=10)
			{ 
			bps[in]._overload_av_cnt=10;
			if(!(bps[in]._av&(1<<4)))avar_bps_hndl(in,4,1);				
			}
		} 
	}		
else if(!(temp&(1<<AV_OVERLOAD)))
	{
	if(bps[in]._overload_av_cnt>0) 
		{
		bps[in]._overload_av_cnt--;
		if(bps[in]._overload_av_cnt<=0)
			{
			bps[in]._overload_av_cnt=0;
			if(bps[in]._av&(1<<4))avar_bps_hndl(in,4,0);  ///////////
			}
		}
	else if(bps[in]._overload_av_cnt<0) bps[in]._overload_av_cnt=0;		 
	}

if(temp&(1<<AV_T))
	{
	if(bps[in]._temp_av_cnt<1200) 
		{
		bps[in]._temp_av_cnt++;
		if(bps[in]._temp_av_cnt>=1200)
			{
			bps[in]._temp_av_cnt=1200;
		   	if(!(bps[in]._av&(1<<0)))avar_bps_hndl(in,0,1);
			}
		}
	}
else if(!(temp&(1<<AV_T)))
	{
	if(bps[in]._temp_av_cnt) 
		{
		bps[in]._temp_av_cnt--;
		if(!bps[in]._temp_av_cnt)
			{
			if(bps[in]._av&(1<<0))avar_bps_hndl(in,0,0);
			}
		} 	
	}

//temp&=(~((1<<AVUMAX)|((1<<AVUMIN))));

if((temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt<40) 
		{
		bps[in]._umax_av_cnt++;
		if(bps[in]._umax_av_cnt>=40)
			{ 
			bps[in]._umax_av_cnt=40;
			if(!(bps[in]._av&(1<<1)))avar_bps_hndl(in,1,1);				
			}
		} 
	}		
else if(!(temp&(1<<AVUMAX)))
	{
	if(bps[in]._umax_av_cnt>0) 
		{
		bps[in]._umax_av_cnt--;
		if(bps[in]._umax_av_cnt==0)
			{
			bps[in]._umax_av_cnt=0;
			avar_bps_hndl(in,1,0);
			}
		}
	else if(bps[in]._umax_av_cnt<0) bps[in]._umax_av_cnt=0;		 
	}

if(temp&(1<<AVUMIN))
	{
	if(bps[in]._umin_av_cnt<40) 
		{
		bps[in]._umin_av_cnt++;
		if(bps[in]._umin_av_cnt>=40)
			{ 
			bps[in]._umin_av_cnt=40;
			if(!(bps[in]._av&(1<<2)))avar_bps_hndl(in,2,1);
			}
		} 
	}	
else if(!(temp&(1<<AVUMIN)))
	{
	if(bps[in]._umin_av_cnt) 
		{
		bps[in]._umin_av_cnt--;
		if(bps[in]._umin_av_cnt==0)
			{
			bps[in]._umin_av_cnt=0;
			avar_bps_hndl(in,2,0);
			}
		}
	else if(bps[in]._umin_av_cnt>10)bps[in]._umin_av_cnt--;	 
	}
//
//
//
//if (bps[in]._av&0x1f)						bps[in]._state=bsAV;
//else if (bps[in]._Uii<200)					bps[in]._state=bsOFF_AV_NET;	  /**/
//else if (bps[in]._flags_tm&BIN8(100000))	bps[in]._state=bsRDY;
//else if (bps[in]._cnt<20)					bps[in]._state=bsWRK;
//
}											 

////-----------------------------------------------
//void avt_hndl(void)
//{
//char i;
//for(i=0;i<12;i++)
//	{
//	if(eb2_data_short[6]&(1<<i))
//		{
//		avt_stat[i]=avtON;
//		}
//	else avt_stat[i]=avtOFF;
//	}
//
//}
//
////-----------------------------------------------
//void bat_hndl(void)
//{
///*if(mess_find(_MESS_BAT_MASK_ON))
//	{
//	if(mess_data[0]==_MESS_BAT_MASK_ON)
//		{
//		char i;
//		for(i=0;i<2;i++)
//			{
//			if(mess_data[1]&(1<<i))
//				{
//				bat[i]._cnt_to_block=0;
//     			bat[i]._rel_stat=0;
//     			}
//			}
//		}
//	}
//if(mess_find(_MESS_BAT_MASK_OFF))
//	{		
//	if(mess_data[0]==_MESS_BAT_MASK_OFF)
//		{
//		char i;
//		for(i=0;i<2;i++)
//			{
//			if((mess_data[1]&(1<<i)) && (bat[i]._cnt_to_block==0) && (bat[i]._rel_stat==0))
//				{
//				bat[i]._cnt_to_block=20;
//				bat[i]._rel_stat=1;
//     			}
//			}
//		
//		}		
//	}*/
//
//if(mess_find_unvol(MESS2BAT_HNDL))
//	{ 
//	char i;
//	
//	if(mess_data[0]==PARAM_BAT_ALL_OFF_AFTER_2SEC)
//		{
//		for(i=0;i<MAX_NUM_OF_BAT;i++)
//			{
//			if(bat[i]._cnt_to_block<50)bat[i]._cnt_to_block++;
//			}
//		}
//
//	else if(mess_data[0]==PARAM_BAT_MASK_OFF_AFTER_2SEC)
//		{
//		for(i=0;i<MAX_NUM_OF_BAT;i++)
//			{
//			if(mess_data[1]&(1<<i))
//				{
//				if(bat[i]._cnt_to_block<50) bat[i]._cnt_to_block++;
//				}
//			else bat[i]._cnt_to_block=0;
//			}
//		}
//	else 
//	 	{
//		for(i=0;i<MAX_NUM_OF_BAT;i++)
//			{
//			bat[i]._cnt_to_block=0;
//			}
//
//		}
//	for(i=0;i<MAX_NUM_OF_BAT;i++)
//		{
//		if(bat[i]._cnt_to_block>20)bat[i]._rel_stat=1;
//		else bat[i]._rel_stat=0;
//		}
//
//	}
//
//else 
//	{
//	char i;
//	for(i=0;i<MAX_NUM_OF_BAT;i++)
//		{
//		bat[i]._cnt_to_block=0;
//		bat[i]._rel_stat=0;
//		}
//
//	}
//
///*if(mess_find_unvol(MESS2BAT_HNDL1))
//	{
//	if(PARAM_BAT_ON)
//		{
//		char i;
//		for(i=0;i<MAX_NUM_OF_BAT;i++)
//			{
//			if(mess_data[1]&(1<<i))
//				{
//				bat[i]._cnt_to_block=0;
//				bat[i]._rel_stat=0;
//				}
//			}
//		}
//	} */
//}
//
//
////-----------------------------------------------
//void klimat_hndl(void)
//{
//
//
//if(t_box>TBOXMAX)
//	{
//	av_tbox_cnt++;
//	} 
//else if(t_box<TBOXMAX)
//	{
//	av_tbox_cnt--;
//	}
//gran(&av_tbox_cnt,0,6);
//
//if(av_tbox_cnt>5)
//	{
//	av_tbox_stat=atsON;
//	}
//if(av_tbox_cnt<1)
//	{
//	av_tbox_stat=atsOFF;
//	}
//
//if(t_box<(TBOXREG-2))
//	{
//	if(t_box_cnt<30)
//		{
//		t_box_cnt++;
//		if(t_box_cnt>=30)
//			{
//			main_vent_pos--;
//			t_box_cnt=0;
//			}
//		}
//	}
//else if(t_box>(TBOXREG))
//	{
//	if(t_box_cnt<30)
//		{
//		t_box_cnt++;
//		if(t_box_cnt>=30)
//			{
//			main_vent_pos++;
//			t_box_cnt=0;
//			}
//		}
//	}
//else
//	{
//	t_box_cnt=0;
//	}
//
//
//if(t_box>TBOXVENTMAX)gran(&main_vent_pos,0,20); 
//else gran(&main_vent_pos,0,pos_vent+9);
//
//if((mess_find_unvol(MESS2VENT_HNDL))&&(mess_data[0]==PARAM_VENT_CB))
//	{
//	main_vent_pos=mess_data[1];
//	}
//
//
//if(main_vent_pos<=1)mixer_vent_stat=mvsON;
//else mixer_vent_stat=mvsOFF;
//
//
//if((TBATDISABLE>=50) && (TBATDISABLE<=90))
//	{
//
//
//	if(t_box>TBATDISABLE)
//		{
//		tbatdisable_cnt++;
//		}
//	if(t_box<TBATENABLE)
//		{
//		tbatdisable_cnt--;
//		}
//	gran(&tbatdisable_cnt,0,6);
//
//	if(tbatdisable_cnt>5)
//		{
//		tbatdisable_stat=tbdsOFF;
//		}
//	if(tbatdisable_cnt<1)
//		{
//		tbatdisable_stat=tbdsON;
//		}
//	}
//else 
//	{
//	tbatdisable_stat=tbdsON;
//	}
//
//if((TLOADDISABLE>=50) && (TLOADDISABLE<=80))
//	{
//	if(t_box>TLOADDISABLE)
//		{
//		tloaddisable_cnt++;
//		}
//	if(t_box<TLOADENABLE)
//		{
//		tloaddisable_cnt--;
//		}
//	gran(&tloaddisable_cnt,0,6);
//
//	if(tloaddisable_cnt>5)
//		{
//		tloaddisable_stat=tldsOFF;
//		}
//	if(tloaddisable_cnt<1)
//		{
//		tloaddisable_stat=tldsON;
//		}
//	}
//else 
//	{
//	tloaddisable_stat=tldsON;
//	}
//
//}
//
////-----------------------------------------------
//void bat_drv(char in)
//{
//unsigned short /*tempUS,*/tempUS_;
//unsigned long tempUL,tempUL_;
//unsigned short b_zar;
////static unsigned short time_cnt[2];
//
//if(cntrl_stat_blok_cnt_plus[in])cntrl_stat_blok_cnt_plus[in]--;
//if(cntrl_stat_blok_cnt_minus[in])cntrl_stat_blok_cnt_minus[in]--;
//
//
//if(bat[in]._Ib>IZMAX) cntrl_stat_blok_cnt_plus[in]=100;
//if(bat[in]._Ib<0)     cntrl_stat_blok_cnt_minus[in]=100;
//
//if(cntrl_stat_blok_cnt_plus[in] && cntrl_stat_blok_cnt_minus[in])
//     {
//     if(!cntrl_stat_blok_cnt_)
//          {
//          cntrl_stat_blok_cnt_=600; 
//          cntrl_stat_blok_cnt_plus[in]=0;
//          cntrl_stat_blok_cnt_minus[in]=0;
//          }
//     else cntrl_stat_blok_cnt=3000;
//     }
//cntrl_stat_blok_cnt=0;
//
//if(++(bat[in]._time_cnt)>=10)
//	{
//	bat[in]._time_cnt=0;
//	//bat[in]._zar_cnt++;
//	}
//
//if(main_10Hz_cnt==50)
//	{
//	if(!bat[in]._rel_stat)
//		{
//		if(bat[in]._Ub<80) 
//			{
//			if(!(bat[in]._av&1))avar_bat_hndl(in,1);
//			}
//		}
//	}
//
//if(abs(bat[in]._Ib)>IKB) 
//	{
//	if((bat[in]._av&1))avar_bat_hndl(in,0);
//	}
//
//
//
//if(bat[in]._Ib>(-IKB))
//	{
//	if(bat[in]._cnt_wrk<10)
//		{
//		bat[in]._cnt_wrk++;
//		if((bat[in]._cnt_wrk>=10)&&(bat[in]._wrk)) 
//			{
//			bat[in]._wrk=0;
//			//beep_init(0x7L,'O');
//			//wrk_mem_hndl(0);
//			wrk_mem_hndl(in);
//			//plazma++;
//			}
//		}
//	else bat[in]._cnt_wrk=10;	
//	}	
//
//else if(bat[in]._Ib<(-IKB))
//	{
//	if(bat[in]._cnt_wrk)
//		{
//		bat[in]._cnt_wrk--;
//		if((bat[in]._cnt_wrk==0)&&(bat[in]._wrk==0)) 
//			{
//			bat[in]._wrk=1;
//
//				{
//				char temp;
//				signed short temp_temp;
//				temp_temp=bat[in]._u_old[((bat_u_old_cnt+1)&0x07)];
//			 
//				temp=LPC_RTC->YEAR;
//				gran_char((signed char*)&temp,1,99);
//				*((char*)(&(bat[in]._wrk_date[0])))=temp;
//			
//				temp=LPC_RTC->MONTH;
//				gran_char((signed char*)&temp,1,12);
//				*(((char*)(&(bat[in]._wrk_date[0])))+1)=temp;
//			
//				temp=LPC_RTC->DOM;
//				gran_char((signed char*)&temp,1,31);
//				*(((char*)(&(bat[in]._wrk_date[0])))+2)=temp;			
//				
//				*(((char*)(&(bat[in]._wrk_date[0])))+3)=*((char*)&temp_temp);
//
//				temp=LPC_RTC->HOUR;
//				gran_char((signed char*)&temp,0,23);
//				*((char*)(&(bat[in]._wrk_date[1])))=temp;
//               	
//				temp=LPC_RTC->MIN;
//				gran_char((signed char*)&temp,0,59);
//				*(((char*)(&(bat[in]._wrk_date[1])))+1)=temp;
//	          
//				temp=LPC_RTC->SEC;
//				gran_char((signed char*)&temp,0,59);
//				*(((char*)(&(bat[in]._wrk_date[1])))+2)=temp;
//			
//				*(((char*)(&(bat[in]._wrk_date[1])))+3)=*(((char*)&temp_temp)+1);
//				bat[in]._Iintegr=0;		//Счетчик десятков милиамперсекунд
//				bat[in]._Iintegr_=0;	//Счетчик сотен милиамперчасов
//				}
//	
//			}
//
//		}
//	else bat[in]._cnt_wrk=0;	 
//	
//	}					
//
///*
//if(Ibat>=(-IKB))
//	{
//	if(cnt_wrk<10)
//		{
//		cnt_wrk++;
//		if((cnt_wrk>=10)&&(wrk!=wrkOFF)) 
//			{
//			wrk=wrkOFF;
//			//beep_init(0x7L,'O');
//			wrk_mem_hndl(ibat_integr);
//			}
//		}
//	else cnt_wrk=10;	
//	}	
//
//else if((Ibat<(-IKB))&&(spc_stat!=spc_KE))
//	{
//	if(cnt_wrk)
//		{
//		cnt_wrk--;
//		if((cnt_wrk==0)&&(wrk!=wrkON)) 
//			{
//			char temp;
//			signed short temp_temp;
//			temp_temp=ubat_old[((ubat_old_cnt+1)&0x07)];
//			 
//			wrk=wrkON;
//			
//			temp=_year;
//			gran_char(&temp,1,99);
//			*((char*)(&(wrk_date[0])))=temp;
//			
//			temp=_month;
//			gran_char(&temp,1,12);
//			*(((char*)(&(wrk_date[0])))+1)=temp;
//			
//			temp=_date;
//			gran_char(&temp,1,31);
//			*(((char*)(&(wrk_date[0])))+2)=temp;			
//				
//			*(((char*)(&(wrk_date[0])))+3)=*((char*)&temp_temp);
//
//			temp=_hour;
//			gran_char(&temp,0,23);
//			*((char*)(&(wrk_date[1])))=temp;
//               
//			temp=_min;
//			gran_char(&temp,0,59);
//			*(((char*)(&(wrk_date[1])))+1)=temp;
//	          
//			temp=_sec;
//			gran_char(&temp,0,59);
//			*(((char*)(&(wrk_date[1])))+2)=temp;
//			
//			*(((char*)(&(wrk_date[1])))+3)=*(((char*)&temp_temp)+1);
//
//			
//			//beep_init(0xFL,'O'); 
//			ibat_integr=0;
//			ibat_integr_=0;
//			}
//		}
//	else cnt_wrk=0;	 
//	
//	}
//if(wrk==wrkON)
//	{
//	ibat_integr_+=-Ibat;
//	if(ibat_integr_>=SEC_IN_HOUR*10L)
//		{
//		ibat_integr_-=SEC_IN_HOUR*10L;
//		ibat_integr++;
//		}
//	}
//
//*/
//
//
///*if(bat[in]._cnt_to_block)
//	{
//	bat[in]._cnt_to_block--;
//	if(!(bat[in]._cnt_to_block))
//		{
//		//bat[in]._rel_stat=1;
//		}
//	}
//*/
//
//
//
//
////unsigned int tempUI,tempUI_;
////unsigned int b_zar; 
////char i;
////Ibat[0]=5000;                     
//
//
//                            
//if(bat[in]._time_cnt==0)
//	{
//	bat[in]._zar_cnt+=(signed long)bat[in]._Ib;
//	
//	if(bat[in]._zar_cnt>=AH_CONSTANT)
//		{
//		if(BAT_C_REAL[in]==0x5555) tempUS_=BAT_C_NOM[in];
//		else tempUS_=BAT_C_REAL[in];
//		
//		b_zar=lc640_read_int(ADR_EE_BAT_ZAR_CNT[in]);
//
//		if(b_zar<(tempUS_/**10*/))
//			{
//			bat[in]._zar_cnt-=AH_CONSTANT;
//
//			lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],b_zar+1);
//			}
//		else if(b_zar>(tempUS_/**10*/))  
//			{
//			lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],tempUS_);
//			bat[in]._zar_cnt=AH_CONSTANT;
//
//			}
//
//		}
//
//	else if(bat[in]._zar_cnt<=-AH_CONSTANT)
//		{
//		if(BAT_C_REAL[in]==0x5555) tempUS_=BAT_C_NOM[in];
//		else tempUS_=BAT_C_REAL[in];
//		
//		b_zar=lc640_read_int(ADR_EE_BAT_ZAR_CNT[in]);
//
//		if(b_zar>tempUS_)
//			{
//			lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],tempUS_);
//			b_zar=tempUS_;
//			}
//		if(b_zar)
//			{
//			bat[in]._zar_cnt+=AH_CONSTANT;
//
//			lc640_write_int(ADR_EE_BAT_ZAR_CNT[in],b_zar-1);
//			}
//		else 
//			{
//			bat[in]._zar_cnt=-AH_CONSTANT;
//			}
//
//		}
//
//			
//	tempUL=(unsigned long)lc640_read_int(ADR_EE_BAT_ZAR_CNT[in]);
//	
//	if(BAT_C_REAL[in]==0x5555) tempUL_=(unsigned long)BAT_C_NOM[in];
//	else tempUL_=(unsigned long)BAT_C_REAL[in];
//		           	
//	tempUL*=1000L;
//
//
//	if(tempUL_==0) tempUL=0;
//	else tempUL/=tempUL_;
//
//	tempUL/=10L;
//
//	bat[in]._zar=(unsigned short)tempUL;
//	
//	gran((signed short*)&bat[in]._zar,0,100);
//     }
//
//
////Подсчет тока разряда батареи      
//if(bat[in]._wrk==1)
//	{
//	if(bat[in]._Iintegr<36000)
//		{          
//		bat[in]._Iintegr+=abs(bat[in]._Ib);
//		if(bat[in]._Iintegr>=36000)
//			{
//			bat[in]._Iintegr=0;		//Счетчик десятков милиамперсекунд
//			bat[in]._Iintegr_++;	//Счетчик сотен милиамперчасов
//			}
//		}
//	else 
//		{
//		bat[in]._Iintegr=0;
//		}	
//	} 
//	    
////
//if((bat[in]._Tb>TBATSIGN)&&(!bat[in]._nd))	
//	{
//	bat[in]._sign_temper_cnt++;
//	}
//else 
//	{
//	bat[in]._sign_temper_cnt--;
//	}
//
//gran(&bat[in]._sign_temper_cnt,0,600);
//if(bat[in]._sign_temper_cnt>=590)	bat[in]._temper_stat|=(1<<0);
//if(bat[in]._sign_temper_cnt<=10)	bat[in]._temper_stat&=~(1<<0);
//
//
//if((bat[in]._Tb>TBATMAX)&&(!bat[in]._nd))	
//	{
//	bat[in]._max_temper_cnt++;
//	}
//else 
//	{
//	bat[in]._max_temper_cnt--;
//	}
//
//gran(&bat[in]._max_temper_cnt,0,600);
//if(bat[in]._max_temper_cnt>=590)	bat[in]._temper_stat|=(1<<1);
//if(bat[in]._max_temper_cnt<=10)	bat[in]._temper_stat&=~(1<<1);
//
//
//
////Подсчет наработки батареи
//if(bat[in]._resurs_cnt<36000)
//	{               
//	bat[in]._resurs_cnt++;
//	if(bat[in]._resurs_cnt>=36000)
//		{
//		bat[in]._resurs_cnt=0;
//		lc640_write_int(ADR_EE_BAT_RESURS[in],lc640_read_int(ADR_EE_BAT_RESURS[in])+1);
//		}
//	}
//else bat[in]._resurs_cnt=0;
//
//
//
//
//if(UBM_AV)
//     {
//     signed short temp_SS;
//
//     if(U0B<600)
//          {
//          temp_SS=bat[in]._Ub/4;
//          }
//     else temp_SS=bat[in]._Ub/5;
//	
//	temp_SS+=temp_SS;     
//
//     temp_SS-=(bat[in]._Ubm);
//
//     temp_SS=abs(temp_SS);
//
//     temp_SS*=10;
//
//     temp_SS/=12;
//
//     bat[in]._dUbm=temp_SS;
//
//
//     if(	(bat[in]._dUbm>UBM_AV) &&
//		(abs(bat[in]._Ib)<(5*IKB)) &&
//		(bat[in]._Ub>((short)(((long)USIGN*115)/100))) &&
//		(!(bat[in]._av & 2))  )
//		{
//		bat[in]._cnt_as++;
//		if(bat[in]._cnt_as==3000)
//			{
//			avar_bat_as_hndl(in,1);
//			}
//		if(bat[in]._cnt_as>=3005) bat[in]._cnt_as=3005;
//		}
//	else 
//		{
//		bat[in]._cnt_as=0;
//		}
//     
//     }
//
//
//
//}
//
//
//
//
//
//
//
////-----------------------------------------------
//void u_necc_hndl(void)
//{
//signed long temp_L;
//signed long temp_SL;
////signed short temp_SS;
//static unsigned char unh_cnt0,unh_cnt1/*,unh_cnt2*/,b1Hz_unh/*,b2Hz_unh*/;
//signed short t[2];
//char i;
//
////temp_SS=0;
//
//
//if(unh_cnt0<10)
//	{
//	unh_cnt0++;
//	if(unh_cnt0>=10)
//		{
//		unh_cnt0=0;
//		b1Hz_unh=1;
//		}
//	}
//
//if(unh_cnt1<5)
//	{
//	unh_cnt1++;
//	if(unh_cnt1==5)
//		{
//		unh_cnt1=0;
////		b2Hz_unh=1;
//		}
//	} 
//
//
//
//if(mess_find_unvol(MESS2UNECC_HNDL))
//	{		
//	if(mess_data[0]==PARAM_UNECC_SET)
//		{
//		u_necc=mess_data[1];
//		}		
//	}
//
//
//else if(b1Hz_unh)
//	{
//	
//	if((BAT_IS_ON[0]!=bisON) && (BAT_IS_ON[1]!=bisON))
//		{
//		u_necc=U0B;
//		}
//	else 
//		{
//		for(i=0;i<2;i++)
//			{
//			if(BAT_IS_ON[i]==bisON)
//				{
//				if(bat[1]._nd)t[i]=20;
//				else t[i]=bat[i]._Tb;
//				}
//			else
//				{
//				t[i]=-20;
//				}
//			}
//		if(t[0]>t[1])mat_temper=t[0];
//		else mat_temper=t[1];
//		
//	
//		if(mat_temper<0)temp_SL=UB0; 
//		else 
//			{
//			if(mat_temper>40)mat_temper=40; 
//			temp_SL=(UB20-UB0)*10;
//			temp_SL*=mat_temper;
//			temp_SL/=200;
//			temp_SL+=UB0;
//			}
//		if(spc_stat==spcVZ)
//			{
//			temp_SL*=KVZ;
//			temp_SL/=1000U;
//			}
//		u_necc=(unsigned int)temp_SL;
//		}  
//	}
//
//
//gran(&u_necc,400,UMAX);
//
//temp_L=(signed long) u_necc;
//temp_L*=98L;
//temp_L/=100L;
//u_necc_dn=(signed short)temp_L;
//
//temp_L=(signed long) u_necc;
//temp_L*=102L;
//temp_L/=100L;
//u_necc_up=(signed short)temp_L;
//
//
//}
//
//
////-----------------------------------------------
//void num_necc_hndl(void)
//{
//char num_necc_up,num_necc_down;
//static short num_necc_block_cnt;
//if(num_necc_block_cnt) num_necc_block_cnt--;
//
//Isumm_=Isumm;
//
//if(bat[0]._Ib<0) Isumm_+=(abs(bat[0]._Ib))/10;
//if(bat[1]._Ib<0) Isumm_+=(abs(bat[1]._Ib))/10;
//
//num_necc_up=(Isumm_/((signed short)IMAX))+1;
//
//Isumm_+=(signed short)((IMAX*(10-KIMAX))/10);
//
//num_necc_down=(Isumm_/((signed short)IMAX))+1;
//
//if(num_necc_up>num_necc)
//	{
//	num_necc=num_necc_up;
//	num_necc_block_cnt=60;
//	}
//else if(num_necc_down<num_necc)
//	{
//	if(!num_necc_block_cnt)
//		{
//		num_necc=num_necc_down;
//		num_necc_block_cnt=60;
//		}
//	}
//
//if(PAR) num_necc=NUMIST;
//
//gran(&num_necc,1,NUMIST);
//
//}
//
////-----------------------------------------------
//void cntrl_hndl(void)
//{
//static char	ch_cnt0,b1Hz_ch,i,iiii;
//static unsigned short IZMAX_;
//
//IZMAX_=IZMAX;
//
//if(cntrl_stat_blok_cnt)cntrl_stat_blok_cnt--;
//if(cntrl_stat_blok_cnt_)cntrl_stat_blok_cnt_--;
//
//if((bat[0]._temper_stat&0x03)||(bat[1]._temper_stat&0x03))IZMAX_=IZMAX/10;
//
//
//if(ch_cnt0<10)
//	{
//	ch_cnt0++;
//	if(ch_cnt0>=10)
//		{
//		ch_cnt0=0;
//		b1Hz_ch=1;
//		}
//	}
////signed long temp_L;
//
////plazma=0;
//
///*if(St&0x01)
//	{
//	cntrl_stat=0;
//     old_cntrl_stat=0;
//     }
//else*//* if((kb_cnt[0]>15)&&(kb_cnt[0]<=30))
//	{
//	cntrl_stat=old_cntrl_stat-30;
//	gran(&cntrl_stat,30,970);
//	}
//else*/ /*if((kb_cnt[0]<=15)&&(kb_cnt[0]>0))
//	{
//	cntrl_stat=old_cntrl_stat+30;
//	gran(&cntrl_stat,30,970);
//	} 
//else*//* if((kb_cnt[1]>15)&&(kb_cnt[1]<=30))
//	{
//	cntrl_stat=old_cntrl_stat-100;
//	gran(&cntrl_stat,30,970);
//	}
//else if((kb_cnt[1]<=15)&&(kb_cnt[1]>0))
//	{
//	cntrl_stat=old_cntrl_stat+100;
//	gran(&cntrl_stat,30,970);
//	}
//else if(kb_full_ver)
//	{
//	cntrl_stat-=50;
//	if(cntrl_stat<30)
//		{
//		if((av_stat&0x0002)==0)avar_bat_hndl(1);
//		kb_full_ver=0;
//		gran(&TBAT,5,60);
//     	bat_ver_cnt=TBAT*300;
//		}
//	gran(&cntrl_stat,30,970);
//	} 	 	
//
//
//else*/ 
///*if(mess_find(_MESS_FAST_REG))
//	{
// 	if(load_U>u_necc)
//		{
//		if(((load_U-u_necc)>10)&&(cntrl_stat>0))cntrl_stat-=50;
//		else if(cntrl_stat)cntrl_stat--;
//		}
//	else if(load_U<u_necc)
//		{
//		if(((u_necc-load_U)>10)&&(cntrl_stat<1015))cntrl_stat+=50;
//		else	if(cntrl_stat<1020)cntrl_stat++;
//		}		
//	}
//
//
//if(mess_find(_MESS_SRC_PWM))
//	{				
//	if(mess_data[0]==_MESS_SRC_PWM)
//		{
//		cntrl_stat=mess_data[1];
//		}				
//	}  */
//
//
////cntrl_stat++;
//
//
//
//if(mess_find_unvol(MESS2CNTRL_HNDL))
//	{
//	if(mess_data[0]==PARAM_CNTRL_STAT_PLUS)
//		{
//		cntrl_stat=cntrl_stat_old+mess_data[1];
//		}
//	else if(mess_data[0]==PARAM_CNTRL_STAT_MINUS)
//		{
//		cntrl_stat=cntrl_stat_old-mess_data[1];
//		}
//	else if(mess_data[0]==PARAM_CNTRL_STAT_STEP_DOWN)
//		{
//		cntrl_stat--;
//
//		if((cntrl_stat<=30)||(load_U<USIGN)) mess_send(MESS2KB_HNDL,PARAM_CNTRL_IS_DOWN,0,10);
//
//		}
//	else if(mess_data[0]==PARAM_CNTRL_STAT_SET)
//		{
//		cntrl_stat=mess_data[1];
//		}
//
//	else if(mess_data[0]==PARAM_CNTRL_STAT_FAST_REG)
//		{
//		if(load_U>u_necc)
//			{
//			if(((load_U-u_necc)>10)&&(cntrl_stat>0))cntrl_stat-=5;
//			else if((cntrl_stat)&&b1Hz_ch)cntrl_stat--;
//			}
//		else if(load_U<u_necc)
//			{	
//			if(((u_necc-load_U)>10)&&(cntrl_stat<1015))cntrl_stat+=5;
//			else	if((cntrl_stat<1020)&&b1Hz_ch)cntrl_stat++;
//			}	
//		 }
//
//	}
//
//else if(b1Hz_ch)
//	{
//	cntrl_stat_new=cntrl_stat_old;
//	
//	if((Ibmax/10)>(2*IZMAX_))
//		{
//          if(cntrl_stat_blok_cnt)cntrl_stat_new--;
//		else	cntrl_stat_new-=10;
//		}		
//	else if(((Ibmax/10)<(IZMAX_*2))&&(Ibmax>(IZMAX_*15)))
//		{
//          if(cntrl_stat_blok_cnt)cntrl_stat_new--;
//          else	cntrl_stat_new-=3;
//		}   
//	else if((Ibmax<(IZMAX_*15))&&((Ibmax/10)>IZMAX_))
//		{
//		cntrl_stat_new--;
//		}
//		
//	else if(load_U<u_necc)
//		{
//		if(load_U<(u_necc-(UB0-UB20)))
//			{
//			if(Ibmax<0)
//				{
//                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
//				else cntrl_stat_new+=10;
//				}
//			else if(Ibmax<(IZMAX_*5))
//				{
//                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
//				else	cntrl_stat_new+=2;
//				}
//			else if(Ibmax<((IZMAX_*95)/10))
//				{
//				cntrl_stat_new++;
//				}					
//			}
//		else if(load_U<(u_necc-((UB0-UB20)/4)))
//			{
//			if(Ibmax<(IZMAX_*5))
//				{
//                    if(cntrl_stat_blok_cnt)cntrl_stat_new++;
//				else	cntrl_stat_new+=2;
//				}
//			else if(Ibmax<((IZMAX_*95)/10))
//				{
//				cntrl_stat_new++;
//				}					
//			}	
//		else if(load_U<(u_necc-1))
//			{
//			if(Ibmax<((IZMAX_*95)/10))
//				{
//				cntrl_stat_new++;
//				}					
//			}					
//		}	
//	else if((load_U>u_necc)/*&&(!cntrl_blok)*/)
//		{
//		if(load_U>(u_necc+(UB0-UB20)))
//			{
//               if(cntrl_stat_blok_cnt)cntrl_stat_new--;
//			else	cntrl_stat_new-=10;
//			}
//		else if(load_U>(u_necc+((UB0-UB20)/4)))
//			{
//               if(cntrl_stat_blok_cnt)cntrl_stat_new--;
//			else cntrl_stat_new-=2;
//			}	
//		else if(load_U>(u_necc+1))
//			{
//			cntrl_stat_new--;
//			}					
//		}
//	gran(&cntrl_stat_new,10,1010);			
//	cntrl_stat_old=cntrl_stat_new;
//	cntrl_stat=cntrl_stat_new;	
//	}
//
//
//iiii=0;
//for(i=0;i<NUMIST;i++)
//     {
//     if(bps[i]._cnt<30)iiii=1;
//     }
//
//if(iiii==0)
//     {
//     cntrl_stat=600;	
//     cntrl_stat_old=600;
//     cntrl_stat_new=600;
//     }
//gran(&cntrl_stat,10,1010); 
//b1Hz_ch=0;
//}
//
////-----------------------------------------------
//void ext_drv(void)
//{
//char i;
//const char sk_buff[4]={13,11,15,7};
//
//for(i=0;i<4;i++)
//	{
//	if(adc_buff_[sk_buff[i]]<2000)
//		{
//		if(sk_cnt[i]<10)
//			{
//			sk_cnt[i]++;
//			if(sk_cnt[i]>=10)
//				{
//				sk_stat[i]=ssON;
//				}
//			}
//		else 
//			{
//			sk_cnt[i]=10;
//			}
//               
//		}
//	else
//		{
//		if(sk_cnt[i]>=0)
//			{
//			sk_cnt[i]--;
//			if(sk_cnt[i]<=0)
//				{
//				sk_stat[i]=ssOFF;
//				}
//			}
//		else 
//			{
//			sk_cnt[i]=0;
//			}
//		}
//	}
//
//for(i=0;i<4;i++)
//	{
//	if(i<4)
//		{
//		if(((SK_SIGN[i]==0)&&(sk_stat[i]==ssON))||((SK_SIGN[i])&&(sk_stat[i]==ssOFF)) )
//			{
//			if(sk_av_cnt[i]<10)
//				{
//				sk_av_cnt[i]++;
//				if(sk_av_cnt[i]>=10)
//					{
//					sk_av_stat[i]=sasON;
//					//uart_out0 (6,'S','K',0x30+i,'A','V',' ',' ');
//					}
//				}
//			else 
//				{
//				sk_av_cnt[i]=10;
//				}
//			}
//		else
//			{
//			if(sk_av_cnt[i]>=0)
//				{
//				sk_av_cnt[i]--;
//				if(sk_av_cnt[i]<=0)
//					{
//					sk_av_stat[i]=sasOFF;
//					//uart_out0 (6,'S','K',0x30+i,'N','O','R','M');
//					}
//				}
//			else 
//				{
//				sk_av_cnt[i]=0;
//				}
//			}
//		}
//	else
//		{
//		sk_av_stat[i]=sasOFF;
//		}
//	}
//}
//
//
////-----------------------------------------------
//void zar_superviser_drv(void)
//{
//
//if(((bat[0]._Ub>u_necc_up) || (bat[0]._Ub<u_necc_dn))&&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_U[0]=0;
//
//if(((bat[0]._Ib>(2*IKB)) || (bat[0]._Ib<(-IKB*2))) &&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_I[0]=0;
//																 
//if((main_kb_cnt==((TBAT*60)-10)) &&(spc_stat==spcOFF))
//	{
//	if((sign_U[0]==1) && (sign_I[0]==1) && (lc640_read_int(EE_BAT1_ZAR_CNT)!=BAT_C_REAL[0]) && (NUMBAT) && (!(bat[0]._av&1)))
//		{
//		lc640_write_int(EE_BAT1_ZAR_CNT,BAT_C_REAL[0]);
//		superviser_cnt++;
//		}
//	
//	}
//
//if(((bat[0]._Ub>u_necc_up) || (bat[1]._Ub<u_necc_dn))&&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_U[1]=0;
//
//if(((bat[1]._Ib>(2*IKB)) || (bat[1]._Ib<(-IKB*2))) &&(main_kb_cnt<((TBAT*60)-30))&&(main_kb_cnt>((TBAT*60)-150))) sign_I[1]=0;
//																 
//if((main_kb_cnt==((TBAT*60)-10)) &&(spc_stat==spcOFF))
//	{
//	if((sign_U[1]==1) && (sign_I[1]==1) && (lc640_read_int(EE_BAT2_ZAR_CNT)!=BAT_C_REAL[1]) && (NUMBAT==2) && (!(bat[1]._av&1)))
//		{
//		lc640_write_int(EE_BAT2_ZAR_CNT,BAT_C_REAL[1]);
//		superviser_cnt++;
//		}
//	
//	}
//
//if(main_kb_cnt==((TBAT*60)-2)) zar_superviser_start();
//}
//
////-----------------------------------------------
//void zar_superviser_start(void)
//{
//sign_U[0]=1;
//sign_I[0]=1;
//sign_U[1]=1;
//sign_I[1]=1;
//
//}
//
//
////-----------------------------------------------
//void vent_hndl(void)
//{
//
//}
//
//
