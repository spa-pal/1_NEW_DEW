#include "control.h"
#include "LPC17XX.H" 
#include "main.h"
#include "avar.h"
#include "gran.h"
#include "25lc640.h"
#include "eeprom_map.h"
//#include "pcf8563.h"
#include "common_func.h"




//-----------------------------------------------
void clr_scrn(void)
{
char i;
for (i=0;i<LCD_SIZE;i++)
	{
	lcd_buffer[i]=' ';
	}
}

//-----------------------------------------------
char find(char xy)
{
char i=0;
do i++;
while ((lcd_buffer[i]!=xy)&&(i<LCD_SIZE));
//if(i==(LCD_SIZE)) i++;
return i;
}


//-----------------------------------------------
void bin2bcd_int(unsigned int in)
{

char i=5;
for(i=0;i<5;i++)
	{
	dig[i]=in%10;
	in/=10;
	}   
}
//-----------------------------------------------
void bcd2lcd_zero(char sig)
{
char i;
zero_on=1;
for (i=5;i>0;i--)
	{
	if(zero_on&&(!dig[i-1])&&(i>sig))
		{
		dig[i-1]=0x20;
		}
	else
		{
		dig[i-1]=dig[i-1]+0x30;
		zero_on=0;
		}	
	}
}             

//-----------------------------------------------
void int2lcd_m(signed short in,char xy,char des)
{
char i;
char n;
char bMinus;
bMinus=0;
if(in<0)
	{
	bMinus=1;
	in=(~in+1);
	}
bin2bcd_int(in);
bcd2lcd_zero(des+1);
i=find(xy);
if(i!=255)
	{
	for (n=0;n<5;n++)
		{ 
		if(n<des)
			{
			lcd_buffer[i]=dig[n];
			} 
		else if (n==des)
   			{
   			lcd_buffer[i]='.';
   			lcd_buffer[i-1]=dig[n];
   			} 	  
		else if((n>=des)&&(dig[n]!=0x20))
			{
			if(!des)lcd_buffer[i]=dig[n];	
			else lcd_buffer[i-1]=dig[n];
   			}
   		else if((n>=des)&&(dig[n]!=0x20)&&(bMinus))
	   		{
			if(!des)lcd_buffer[i]='-';	
			else lcd_buffer[i-1]='-';
			n=5;
   			}	   
		i--;	
		}
	}
}

//-----------------------------------------------
void int2lcd_mm(signed short in,char xy,char des)
{
char i;
char n;
char minus='+';
if(in<0)
	{
	in=-in;
	minus='-';
	}
minus='-';	
bin2bcd_int(in);
bcd2lcd_zero(des+1);
i=find(xy);
for (n=0;n<5;n++)
	{
   	if(!des&&(dig[n]!=' '))
   		{
   		if((dig[n+1]==' ')&&(minus=='-'))lcd_buffer[i-1]='-';
   		lcd_buffer[i]=dig[n];	 
   		}
   	else 
   		{
   		if(n<des)lcd_buffer[i]=dig[n];
   		else if (n==des)
   			{
   			lcd_buffer[i]='.';
   			lcd_buffer[i-1]=dig[n];
   			} 
   		else if ((n>des)&&(dig[n]!=' ')) lcd_buffer[i-1]=dig[n]; 
   		else if ((minus=='-')&&(n>des)&&(dig[n]!=' ')&&(dig[n+1]==' ')) lcd_buffer[i]='-';  		
   		}  
		
	i--;	
	}
}

//-----------------------------------------------
void int2lcd_mmm(signed short in,char xy,char des)
{
signed char i;
char n;
char s[10];
char minus='+';
char zero_on;
char simb_num;

if(in<0)
	{
	in=-in;
	minus='-';
	}

for(i=0;i<10;i++)
	{
	s[i]=in%10;
	in/=10;
	}   

zero_on=1;
simb_num=0;

for (i=9;i>=0;i--)
	{
	if(zero_on&&(!s[i])&&(i>(des)))
	     {
	     s[i]=0x20;
	     }
	else 
	     {
	     s[i]=s[i]+0x30;
	     zero_on=0;
	     simb_num++;
	     }
	 }
	          
if(minus=='-')	
     {
     s[simb_num++]=minus; 
     }    
if(des)
     {
     for(i=simb_num;i>des;i--)
          {
          s[i]=s[i-1];
          }
     s[des]='.';
     simb_num++;     
     }
	
n=find(xy);
for (i=0;i<simb_num;i++)
	{
     lcd_buffer[n-i]=s[i];
	}
}

//-----------------------------------------------
void long2lcd_mmm(signed long in,char xy,char des)
{
signed char i;
char n;
char s[10];
char minus='+';
char zero_on;
char simb_num;

if(in<0)
	{
	in=-in;
	minus='-';
	}

for(i=0;i<10;i++)
	{
	s[i]=in%10;
	in/=10;
	}   

zero_on=1;
simb_num=0;

for (i=9;i>=0;i--)
	{
	if(zero_on&&(!s[i])&&(i>(des)))
	     {
	     s[i]=0x20;
	     }
	else 
	     {
	     s[i]=s[i]+0x30;
	     zero_on=0;
	     simb_num++;
	     }
	 }
	          
if(minus=='-')	
     {
     s[simb_num++]=minus; 
     }    
if(des)
     {
     for(i=simb_num;i>des;i--)
          {
          s[i]=s[i-1];
          }
     s[des]='.';
     simb_num++;     
     }
	
n=find(xy);
for (i=0;i<simb_num;i++)
	{
     lcd_buffer[n-i]=s[i];
	}
}

//-----------------------------------------------
void long2lcdyx_mmm(unsigned long in,char y,char x,char des)
{
signed char i;
char n;
char s[10];
char minus='+';
char zero_on;
char simb_num;

if(in<0)
	{
	in=-in;
	minus='-';
	}

for(i=0;i<10;i++)
	{
	s[i]=in%10;
	in/=10;
	}   

zero_on=1;
simb_num=0;

for (i=9;i>=0;i--)
	{
	if(zero_on&&(!s[i])&&(i>(des)))
	     {
	     s[i]=0x20;
	     }
	else 
	     {
	     s[i]=s[i]+0x30;
	     zero_on=0;
	     simb_num++;
	     }
	 }
	          
if(minus=='-')	
     {
     s[simb_num++]=minus; 
     }    
if(des)
     {
     for(i=simb_num;i>des;i--)
          {
          s[i]=s[i-1];
          }
     s[des]='.';
     simb_num++;     
     }
	
n=(20*y)+x;
for (i=0;i<simb_num;i++)
	{
     lcd_buffer[n-i]=s[i];
	}



}

//-----------------------------------------------
void int2lcdyx(unsigned short in,char y,char x,char des)
{
char i;
char n;
bin2bcd_int(in);
bcd2lcd_zero(des+1);
i=(y*20)+x;
for (n=0;n<5;n++)
	{ 
	if(n<des)
		{
		lcd_buffer[i]=dig[n];
		}   
	if((n>=des)&&(dig[n]!=0x20))
		{
		if(!des)lcd_buffer[i]=dig[n];	
		else lcd_buffer[i-1]=dig[n];
   		}   
	i--;	
	}
}


//-----------------------------------------------
void int2lcd(unsigned short in,char xy,char des)
{
char i;
char n;

bin2bcd_int(in);
bcd2lcd_zero(des+1);
i=find(xy);
for (n=0;n<5;n++)
	{
   	if(!des&&(dig[n]!=' '))
   		{
   		lcd_buffer[i]=dig[n];	 
   		}
   	else 
   		{
   		if(n<des)lcd_buffer[i]=dig[n];
   		else if (n==des)
   			{
   			lcd_buffer[i]='.';
   			lcd_buffer[i-1]=dig[n];
   			} 
   		else if ((n>des)&&(dig[n]!=' ')) lcd_buffer[i-1]=dig[n];   		
   		}  
		
	i--;	
	}
}

//-----------------------------------------------
void long2lcdhyx(unsigned long in,char y,char x)
{
char i;
char n;

i=(20*y)+x;

n=*((char*)&in);
lcd_buffer[i]=ABCDEF[n%16];
i--;
lcd_buffer[i]=ABCDEF[n/16];
i--;

n=*(((char*)&in)+1);
lcd_buffer[i]=ABCDEF[n%16];
i--;
lcd_buffer[i]=ABCDEF[n/16];
i--;

n=*(((char*)&in)+2);
lcd_buffer[i]=ABCDEF[n%16];
i--;
lcd_buffer[i]=ABCDEF[n/16];
i--;

n=*(((char*)&in)+3);
lcd_buffer[i]=ABCDEF[n%16];
i--;
lcd_buffer[i]=ABCDEF[n/16];
i--;
}

//-----------------------------------------------
void char2lcdh(char in,char yx)
{
char i;

i=find(yx);

lcd_buffer[i]=ABCDEF[in%16];
i--;
lcd_buffer[i]=ABCDEF[in/16];
i--;
}

//-----------------------------------------------
void char2lcdhyx(char in,char y,char x)
{
char i;

i=(20*y)+x;

lcd_buffer[i]=ABCDEF[in%16];
i--;
lcd_buffer[i]=ABCDEF[in/16];
i--;
}

//-----------------------------------------------
void int2lcdhyx(int in,char y,char x)
{
char i;

i=(20*y)+x;

lcd_buffer[i]=ABCDEF[in%16];
i--;
in/=16;
lcd_buffer[i]=ABCDEF[in%16];
i--;
in/=16;
lcd_buffer[i]=ABCDEF[in%16];
i--;
in/=16;
lcd_buffer[i]=ABCDEF[in];

}

//-----------------------------------------------
void char2lcdbyx(char in,char y,char x)
{
char i;

i=(20*y)+x;

lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
lcd_buffer[i--]=ABCDEF[in%2];
in/=2;
}

//-----------------------------------------------
signed short ptr_carry(signed short in,signed short modul,signed short carry)
{
signed short tempSS;
tempSS=in;                                                             
tempSS+=carry;
if(tempSS<0)tempSS+=modul;
else if(tempSS>=modul)tempSS-=modul;

return (signed short)tempSS;
}

//-----------------------------------------------
void parol_init(void)
{
parol[0]=0;
parol[1]=0;
parol[2]=0;
sub_ind=0;
}


//-----------------------------------------------
void bgnd_par(char const *ptr0,char const *ptr1,char const *ptr2,char const *ptr3)
{
char i,*ptr_ram;
clr_scrn();

ptr_ram=lcd_buffer;
for(i=0;i<20;i++)
	{
	*ptr_ram++=*ptr0++;
	}
for(i=0;i<20;i++)
	{
	*ptr_ram++=*ptr1++;
	}
for(i=0;i<20;i++)
	{
	*ptr_ram++=*ptr2++;
	}
for(i=0;i<20;i++)
	{
	*ptr_ram++=*ptr3++;
	}


}

//-----------------------------------------------
void sub_bgnd(char const *adr,char xy,signed char offset)
{
char temp;
temp=find(xy);

//ptr_ram=&lcd_buffer[find(xy)];
if(temp!=255)
while (*adr)
	{
	lcd_buffer[temp+offset]=*adr++;
	temp++;
    	}
}


//-----------------------------------------------
void fl_simv(char y, char x, char len)
{
fl_simv_num=x+(y*20);
fl_simv_len=len;
}


//-----------------------------------------------
void event_data2ind(char num, char simbol)
{
char iii;
char dt[4],dt_[4],dt__[4];
unsigned short tempii;    
		
tempii=(signed short)num;
tempii*=32;
tempii+=EVENT_LOG;
     
lc640_read_long_ptr(tempii,dt);
lc640_read_long_ptr(tempii+8,dt_);
lc640_read_long_ptr(tempii+12,dt__);

iii=find(simbol);

lcd_buffer[iii++]=' ';
lcd_buffer[iii++]='0';
lcd_buffer[iii++]='!';
lcd_buffer[iii++]='/';
lcd_buffer[iii++]='@'; 
lcd_buffer[iii++]=' ';
lcd_buffer[iii++]=' ';
lcd_buffer[iii++]='/';
lcd_buffer[iii++]='0';
lcd_buffer[iii++]='#';
int2lcd(dt_[2],'!',0);
int2lcd(dt_[0],'#',0);   
if(!((dt_[1]>=1)&&(dt_[1]<=12)))dt_[1]=1;
sub_bgnd(sm_mont[dt_[1]],'@',0); 
lcd_buffer[iii++]=' ';		
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

//-----------------------------------------------
void event2ind(char num, char simbol)
{
char iii;
char dt[4],dt_[4],dt__[4];
unsigned int tempii;    
		
tempii=lc640_read_int(PTR_EVENT_LOG);
tempii=ptr_carry(tempii,64,-1*((signed)num));
tempii*=32;
tempii+=EVENT_LOG;
     
lc640_read_long_ptr(tempii,dt);
lc640_read_long_ptr(tempii+8,dt_);
lc640_read_long_ptr(tempii+12,dt__);

iii=find(simbol);
     
if(dt[0]=='U')
    	{ 
    	if(dt[2]=='R')
    		{
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
    		}
    	
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
  		}	   
     }   
     
else if(dt[0]=='P')
	{
     lcd_buffer[iii++]='�';
     lcd_buffer[iii++]='�';
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
  		}     	
     }   

else if(dt[0]=='B')
    	{
    	if(dt[2]=='C')
    		{
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
		if(dt[1]<9)
    			{
    			lcd_buffer[iii++]=0x31+dt[1];
    			lcd_buffer[iii++]='�';
    			lcd_buffer[iii++]=' ';
    			}
    		else if((dt[1]>=9)&&(dt[1]<99))
    			{
    			lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    			lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    			lcd_buffer[iii++]='�';
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
    		}
    	if(dt[2]=='Z')
    		{
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
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
    			}  		
    		}    		

    	if(dt[2]=='W')
    		{
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
		if(dt[1]<9)
    			{
    			lcd_buffer[iii++]=0x31+dt[1];
    			lcd_buffer[iii++]='�';
    			lcd_buffer[iii++]=' ';
    			}
    		else if((dt[1]>=9)&&(dt[1]<99))
    			{
    			lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    			lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    			lcd_buffer[iii++]='�';
    			}
    		else 
    			{
    			lcd_buffer[iii++]=' ';
    			lcd_buffer[iii++]=' '; 
    			lcd_buffer[iii++]=' ';    		
    			} 
    		lcd_buffer[iii++]=' ';    		
    		
    		
 /*   		lcd_buffer[iii++]='�';
		if(dt[1]<9)
    			{
    			lcd_buffer[iii++]=0x31+dt[1];
    			lcd_buffer[iii++]='�';
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
    		lcd_buffer[iii++]=' ';   */ 		
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
    		}    		
 
 	if(dt[2]=='K')
    		{
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
    		lcd_buffer[iii++]='�';
		if(dt[1]<9)
    			{
    			lcd_buffer[iii++]=0x31+dt[1];
    			lcd_buffer[iii++]='�';
    			lcd_buffer[iii++]='�';
    			}
    		else if((dt[1]>=9)&&(dt[1]<99))
    			{
    			lcd_buffer[iii++]=0x30+((dt[1]+1)/10);
    			lcd_buffer[iii++]=0x30+((dt[1]+1)%10);
    			lcd_buffer[iii++]='�';
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
    		}    		

    		     	     	
    	}     	    
     	
else if(dt[0]=='S')
    	{
    	lcd_buffer[iii++]='�';
    	lcd_buffer[iii++]='�';
    	lcd_buffer[iii++]='�';
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
		}    	
    	}
     	
else if(dt[0]=='B')
    	{
    	lcd_buffer[iii++]='�';
    	lcd_buffer[iii++]='�';
    	lcd_buffer[iii++]='�';
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
    	lcd_buffer[iii++]='�';
    	lcd_buffer[iii++]='�';
    	lcd_buffer[iii++]='�';
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
}

//-----------------------------------------------
void tree_up(char tind, char tsub_ind, char tindex_set, char tsub_ind1)
{
b[ptr_ind++]=a;
ind=tind;
sub_ind=tsub_ind;
index_set=tindex_set;
sub_ind1=tsub_ind1;
}

//-----------------------------------------------
void tree_down(signed char offset_ind,signed char offset_sub_ind)
{
ptr_ind--;
ptr_ind+=offset_ind;

if(ptr_ind<0)ptr_ind=0;
a=b[ptr_ind];

sub_ind+=offset_sub_ind;
/*if(offset_ind)
     {
     sub_ind=0;
     }*/
}

//-----------------------------------------------
void pointer_set(char num_of_first_row)
{
if(sub_ind==index_set)lcd_buffer[num_of_first_row*20]=1;
else if(sub_ind==(index_set+1))lcd_buffer[(num_of_first_row+1)*20]=1;
else if(sub_ind==(index_set+2))lcd_buffer[(num_of_first_row+2)*20]=1;
else if(sub_ind==(index_set+3))lcd_buffer[(num_of_first_row+3)*20]=1;
else if(sub_ind==(index_set+4))lcd_buffer[(num_of_first_row+4)*20]=1;
else if(sub_ind==(index_set+5))lcd_buffer[(num_of_first_row+5)*20]=1;
else if(sub_ind==(index_set+6))lcd_buffer[(num_of_first_row+6)*20]=1;
else if(sub_ind==(index_set+7))lcd_buffer[(num_of_first_row+7)*20]=1;
}	
