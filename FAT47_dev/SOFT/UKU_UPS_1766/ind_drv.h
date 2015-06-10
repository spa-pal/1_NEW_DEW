#ifndef _IND_DRV_	 //читать, если файл ранее не считан

#define _IND_DRV_	  //установить, что файл прочитан

#define DMASK ((1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7)|(1<<D8)|(1<<D9)|(1<<CH_U))

//-------port2
#define D0     		0
#define D1     		D0+1
#define D2     		D1+1
#define D3     		D2+1
#define D4     		D3+1
#define D5			D4+1
#define D6  		D5+1
#define D7   		D6+1
#define D8  		D7+1
#define D9	     	D8+1

#define CH_U     	12
//---------port4
#define CH_I     	28
#define CH_Q     	29
//--------port0
#define POWER_NET	30
#define ACB      	29
#define ACTIVE     	25
#define BREAKDOWN	26





void ind_drv(void);

#endif
