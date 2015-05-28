#include "LPC17xx.H"
//----------Port0
void dir_out_p0(int a,int p) // установить биты по маске а начиная с места 	p
{
LPC_GPIO0->FIODIR|=(a<<p);
}
void dir_in_p0(int a,int p)
{
LPC_GPIO0->FIODIR&=~(a<<p);
}
void set_p0(int a,int p)
{
LPC_GPIO0->FIOSET|=(a<<p);
}
void clr_p0(int a,int p)
{					  
LPC_GPIO0->FIOCLR|=(a<<p);
}
int in_p0(int a,int p)				   // не работает почему-то
{
return LPC_GPIO0->FIOPIN&(a<<p);
}
//-------- Port1
void dir_out_p1(int a,int p)
{
LPC_GPIO1->FIODIR|=(a<<p);
}
void dir_in_p1(int a,int p)
{
LPC_GPIO1->FIODIR&=~(a<<p);
}
void set_p1(int a,int p)
{
LPC_GPIO1->FIOSET|=(a<<p);
}
void clr_p1(int a,int p)
{
LPC_GPIO1->FIOCLR|=(a<<p);
}

long in_p1(int a,int p)				 // не работает почему-то
{
return (LPC_GPIO1->FIOPIN&(a<<p));
}
//-------- Port2
void dir_out_p2(int a,int p)
{
LPC_GPIO2->FIODIR|=(a<<p);
}
void dir_in_p2(int a,int p)
{
LPC_GPIO2->FIODIR&=~(a<<p);
}
void set_p2(int a,int p)
{
LPC_GPIO2->FIOSET|=(a<<p);
}
void clr_p2(int a,int p)
{
LPC_GPIO2->FIOCLR|=(a<<p);
}

//-------- Port3
void dir_out_p3(int a,int p)
{
LPC_GPIO3->FIODIR|=(a<<p);
}
void dir_in_p3(int a,int p)
{
LPC_GPIO3->FIODIR&=~(a<<p);
}
void set_p3(int a,int p)
{
LPC_GPIO3->FIOSET|=(a<<p);
}
void clr_p3(int a,int p)
{
LPC_GPIO3->FIOCLR|=(a<<p);
}

//-------- Port4
void dir_out_p4(int a,int p)
{
LPC_GPIO4->FIODIR|=(a<<p);
}
void dir_in_p4(int a,int p)
{
LPC_GPIO4->FIODIR&=~(a<<p);
}
void set_p4(int a,int p)
{
LPC_GPIO4->FIOSET|=(a<<p);
}
void clr_p4(int a,int p)
{
LPC_GPIO4->FIOCLR|=(a<<p);
}

