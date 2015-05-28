#include "LPC17xx.H"
#include "main.h"
#include "ind_drv.h"
#include "snmp_data_file.h"

char channel=0;

void ind_drv (void)
	{
	char t;
	signed short D,DD=0;

	if(flash_net_def_cnt)flash_net_def_cnt--;

	LPC_GPIO2->FIODIR|=DMASK;
	LPC_GPIO4->FIODIR|=((1<<CH_I)|(1<<CH_Q));
	LPC_GPIO0->FIODIR|=((1<<POWER_NET)|(1<<ACB)|(1<<ACTIVE)|(1<<BREAKDOWN));

	LPC_GPIO2->FIOCLR|=(1<<CH_U);
	LPC_GPIO4->FIOCLR|=((1<<CH_I)|(1<<CH_Q));
	LPC_GPIO2->FIOCLR|=DMASK;


	if(ind==iK)
		{
		if(sub_ind==0) ind_level_U=level_U;
		else if(sub_ind==1) ind_level_U=level_I;
		else if(sub_ind==2) ind_level_U=5+((bps[NUMB]._Ti-20)/5);
		else if(sub_ind==3) ind_level_U=level_Q;
		else if(sub_ind==5) ind_level_U=5+((snmp_main_voltage-220)/10);
		ind_level_I=sub_ind+1;
		}
/*

	if (level_U_mode==flash)	 // для режима калибровки
		{
			ind_level_U=level_U;
			ind_level_I=flash_;
			ind_level_Q=flash_;
		}
	else if (level_I_mode==flash)
		{
			ind_level_U=flash_;
			ind_level_I=level_I;
			ind_level_Q=flash_;
		}
	else if (level_Q_mode==flash)
		{
			ind_level_U=flash_;
			ind_level_I=flash_;
			ind_level_Q=level_Q;
		} */
	else
		{
		ind_level_U=level_U;
		ind_level_I=level_I;
		ind_level_Q=level_Q;
		}

	switch (++channel) 
		{
		case 1:		
			{
			D=1;
			for (t=0;t<ind_level_U;t++)	D=D*2;	// конвертим уровень сигнала в кол-во битов
			if (level_U_mode==reverse)		   // реверсивный режим
				{
				D=D-1;
				DD=0;
				while (D != 0)
					{
					DD=(DD>>1)+0x200;
					D>>=1;
					}			
				}
			else if(level_U_mode==alone) DD=D/2;	 // режим одиночного сегмента
			else DD=D-1;			
			LPC_GPIO2->FIOSET|=(DD<<D0);		// выводим уровень сигнала в битах
			LPC_GPIO2->FIOSET|=(1<<CH_U);	// включаем дисплейчик
			};
			break;
		case 2:				
			{
			D=1;
			for (t=0;t<ind_level_I;t++)	D=D*2;	// конвертим уровень сигнала в кол-во битов
			if (level_I_mode==reverse)
				{
				D=D-1;
				DD=0;
				while (D != 0)
					{
					DD=(DD>>1)+0x200;
					D>>=1;
					}			
				}
			else if(level_I_mode==alone) DD=D/2;
			else DD=D-1;					
			LPC_GPIO2->FIOSET|=(DD<<D0);		// выводим уровень сигнала в битах
			LPC_GPIO4->FIOSET|=(1<<CH_I);
			};
			break;
		case 3:				
			{
			D=1;
			for (t=0;t<ind_level_Q;t++)	D=D*2;	// конвертим уровень сигнала в кол-во битов
			if (level_Q_mode==reverse)
				{
				D=D-1;
				DD=0;
				while (D != 0)
					{
					DD=(DD>>1)+0x200;
					D>>=1;
					}			
				}
			else if(level_Q_mode==alone) DD=D/2;
			else DD=D-1;			
			LPC_GPIO2->FIOSET|=(DD<<D0);		// выводим уровень сигнала в битах
			LPC_GPIO4->FIOSET|=(1<<CH_Q);
			channel=0;
			};
			break;
		default: channel=0;
		}

	if(ind==iDef_net_set)
		{
		static char flash_dns;

		flash_dns++;

		if(flash_dns&0x40)
			{
			LPC_GPIO0->FIOCLR|=(1<<POWER_NET);
			LPC_GPIO0->FIOCLR|=(1<<ACB);
			}
		else 
			{
			LPC_GPIO0->FIOSET|=(1<<POWER_NET);
			LPC_GPIO0->FIOSET|=(1<<ACB);
			}
		}

	else if(ind==iK)
		{
		static char flash_k;

		flash_k++;

		if(flash_k&0x40)
			{
			LPC_GPIO0->FIOCLR|=(1<<POWER_NET);
			//
			}
		else 
			{
			LPC_GPIO0->FIOSET|=(1<<POWER_NET);
			//LPC_GPIO0->FIOSET|=(1<<ACB);
			}
		LPC_GPIO0->FIOSET|=(1<<ACB);
		}

	else if(flash_net_def_cnt)
		{
		if(flash_net_def_cnt&0x0010)
			{
			LPC_GPIO0->FIOCLR|=(1<<POWER_NET);
			LPC_GPIO0->FIOCLR|=(1<<ACB);
			LPC_GPIO0->FIOCLR|=(1<<ACTIVE);
			}
		else 
			{
			LPC_GPIO0->FIOSET|=(1<<POWER_NET);
			LPC_GPIO0->FIOSET|=(1<<ACB);
			LPC_GPIO0->FIOSET|=(1<<ACTIVE);
			}
		}
	else
		{

	if (work_at==power_net)
		{
		LPC_GPIO0->FIOCLR|=(1<<POWER_NET);
		LPC_GPIO0->FIOSET|=(1<<ACB);
		}
	else
		{
		LPC_GPIO0->FIOCLR|=(1<<ACB);
		LPC_GPIO0->FIOSET|=(1<<POWER_NET);
		}
	if (work_stat==active)
		{
		LPC_GPIO0->FIOSET|=(1<<ACTIVE);
//		LPC_GPIO0->FIOCLR|=(1<<BREAKDOWN);
		}
	else
		{
//		LPC_GPIO0->FIOSET|=(1<<BREAKDOWN);
		LPC_GPIO0->FIOCLR|=(1<<ACTIVE);
		}

		}
	 
	}
