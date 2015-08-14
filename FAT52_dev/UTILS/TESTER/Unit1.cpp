//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "cmd.c"
#include "Unit1.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CPort"
#pragma resource "*.dfm"
char UOB[1000];
TForm1 *Form1;
#define RX_BUFFER_SIZE 1000U
char rx_buffer[RX_BUFFER_SIZE];
signed int rx_wr_index,rx_rd_index,rx_counter;
BOOL bRXIN;
BOOL rx_buffer_overflow;
unsigned char UIB[150]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char damp[1000000];
unsigned short damp_[128];
unsigned short t1cnt,t2cnt,t3cnt,t4cnt;
BOOL b100Hz;
BOOL b10Hz;
BOOL b5Hz;
BOOL b2Hz;
BOOL b1Hz;

unsigned short CAP_ZAR_TIME;
unsigned short CAP_PAUSE1_TIME;
unsigned short CAP_RAZR_TIME;
unsigned short CAP_PAUSE2_TIME;
unsigned short CAP_MAX_VOLT;
unsigned short CAP_WRK_CURR;
unsigned short CAP_COUNTER;
unsigned short CAP_TIME_SEC;
unsigned short CAP_TIME_MIN;
unsigned short CAP_TIME_HOUR;

FILE *F;
AnsiString SName = "Неизвестен";
unsigned file_lengt;

enum_requestStatus requestStatus = rsOFF;

char modbusCnt=0;
BOOL bmodbusIn=0;

unsigned short rs485_rx_cnt;

int tx_plazma;
int rx_plazma;

static short plazma;
char bRX485;

char rs485_out_buff[1000];



#define MAXCELLVOLTAGE 
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::B1Click(TObject *Sender)
{

if(!(ComPort1->Connected))
{
try
    	{
     ComPort1->Port=ComboBox1->Text;

     ComPort1->BaudRate=br19200;
     ComPort1->DataBits=dbEight;
     ComPort1->Open();
	}
catch (...)
	{
     ShowMessage("Невозможно открыть порт");
     }
if(ComPort1->Connected)
    	{
     B1->Caption="Закрыть";
     }
}
else if(ComPort1->Connected)
{
try
    	{
     ComPort1->Close();
	}
catch (...)
	{
     ShowMessage("Невозможно закрыть порт");
     }
if(!(ComPort1->Connected))
    	{
     B1->Caption="Открыть";
     }
}	}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x21;
UOB[6]=0xe9;
UOB[7]=0xff;

if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
ComboBox1->ItemIndex=0;
//Memo1->Clear();
//ComboBox4->ItemIndex=0;
//ComboBox2->ItemIndex=0;
//ComboBox3->ItemIndex=0;
//mboBox6->ItemIndex=1;	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x22;
UOB[6]=0xA9;
UOB[7]=0xfE;

if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------
//-----------------------------------------------
int index_offset (signed int index,signed int offset)
{
index=index+offset;
if(index>=RX_BUFFER_SIZE) index-=RX_BUFFER_SIZE;
if(index<0) index+=RX_BUFFER_SIZE;
return index;
}

//-----------------------------------------------
char control_check(int index)
{
int i=0,ii=0,iii;

if(rx_buffer[index]!=END) goto error_cc;

ii=rx_buffer[index_offset(index,-2)];
iii=0;
for(i=0;i<=ii;i++)
	{
	iii^=rx_buffer[index_offset(index,-2-ii+i)];
	}
if (iii!=rx_buffer[index_offset(index,-1)]) goto error_cc;


success_cc:
return 1;
goto end_cc;
error_cc:
return 0;
goto end_cc;

end_cc:
}

//---------------------------------------------------------------------------

AnsiString long2str_h(unsigned long in)
{
const char DIGISYM[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
AnsiString outA;
char out[9];
char i;
//out="        ";

for(i=0;i<8;i++)
	{
     out[7-i]=DIGISYM[in%16];
     in/=16;
     }
out[8]=0;
outA=AnsiString(out);
//out[0]='a';
return outA;


}

//---------------------------------------------------------------------------

AnsiString char2str_h(unsigned char in)
{
const char DIGISYM[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
AnsiString outA;
char out[2];
char i;
//out="        ";

for(i=0;i<2;i++)
	{
     out[1-i]=DIGISYM[in%16];
     in/=16;
     }
out[2]=0;
outA=AnsiString(out);
//out[0]='a';
return outA;


}

//---------------------------------------------------------------------------
void __fastcall TForm1::out_adr_blok_to_page(char* ptr)
{
char i,t=0;
UOB[0]=CMND;
UOB[1]=21;
t= UOB[0]^UOB[1];
for (i=0;i<64;i++)
	{
     UOB[i+2]=ptr[i];
	t^=UOB[i+2];
	}
UOB[66]=66;
t^=UOB[66];
UOB[67]=t;
UOB[68]=0x0a;

ComPort1->Write(UOB,69);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::uart1_out_adr(char* ptr, int len)
{
ComPort1->Write(ptr,len);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::uart_out_out(unsigned short len, char data0, char data1, char data2, char data3, char data4, char data5, char data6, char data7)
{
char i,t=0;

UOB[0]=data0;
UOB[1]=data1;
UOB[2]=data2;
UOB[3]=data3;
UOB[4]=data4;
UOB[5]=data5;
UOB[6]=data6;
UOB[7]=data7;

for (i=0;i<len;i++)
	{
	t^=UOB[i];
	}

UOB[len]=len;
t^=UOB[len];
UOB[len+1]=t;
UOB[len+2]=END;

if(ComPort1->Connected)ComPort1->Write(UOB,len+3);



}

//---------------------------------------------------------------------------
void __fastcall TForm1::ind_hndl(void)
{
//Edit1->Text= IntToStr(CAP_ZAR_TIME);




Label16->Caption= IntToStr(CAP_MAX_VOLT);

}

//---------------------------------------------------------------------------
void __fastcall TForm1::uart_modbus_request(void)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x03;
UOB[2]=0x00;
UOB[3]=0x28;
UOB[4]=0x00;
UOB[5]=0x0a;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;
if(ComPort1->Connected)ComPort1->Write(UOB,8);

requestStatus = rsGETSETTED;
}
//-----------------------------------------------
void __fastcall TForm1::uart_in_an(void)
{
short i;

	if(bRX485==1)
	{


	rs485_out_buff[0]=0x7e;
	rs485_out_buff[1]=0x31;
	rs485_out_buff[2]=0x31;
	rs485_out_buff[3]=0x30;
	rs485_out_buff[4]=0x31;
	rs485_out_buff[5]=0x44;
	rs485_out_buff[6]=0x30;
	rs485_out_buff[7]=0x30;
	rs485_out_buff[8]=0x30;
	rs485_out_buff[9]=0x36;
	rs485_out_buff[10]=0x31;
	rs485_out_buff[11]=0x31;
	rs485_out_buff[12]=0x38;

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б1
     for (i=(13);i<(52);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
     rs485_out_buff[51]=0x30;
     rs485_out_buff[52]=0x31;

	rs485_out_buff[13]=0x30;
	rs485_out_buff[14]=0x44;
	rs485_out_buff[15]=0x37;
	rs485_out_buff[16]=0x41;
     rs485_out_buff[17]=0x30;
	rs485_out_buff[18]=0x44;
	rs485_out_buff[19]=0x33;
	rs485_out_buff[20]=0x43;
     rs485_out_buff[21]=0x31;
	rs485_out_buff[22]=0x38;
	rs485_out_buff[23]=0x31;
	rs485_out_buff[24]=0x39;
	rs485_out_buff[25]=0x31;
	rs485_out_buff[26]=0x34;
	rs485_out_buff[27]=0x31;
	rs485_out_buff[28]=0x32;
	rs485_out_buff[29]=0x30;
	rs485_out_buff[30]=0x30;
	rs485_out_buff[31]=0x30;
	rs485_out_buff[32]=0x30;
	rs485_out_buff[33]=0x30;
	rs485_out_buff[34]=0x30;
	rs485_out_buff[35]=0x35;
	rs485_out_buff[36]=0x35;
	rs485_out_buff[37]=0x36;
	rs485_out_buff[38]=0x33;
	rs485_out_buff[43]=0x46;
	rs485_out_buff[44]=0x46;
	rs485_out_buff[45]=0x30;
	rs485_out_buff[46]=0x45;
	rs485_out_buff[47]=0x41;
	rs485_out_buff[48]=0x36;
	rs485_out_buff[49]=0x36;
	rs485_out_buff[50]=0x34;

	if(CheckBox1->Checked) {
	rs485_out_buff[39]=0x31;
	rs485_out_buff[40]=0x44;
	rs485_out_buff[41]=0x34;
	rs485_out_buff[42]=0x43;
     }

/*
	 */

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б2
     for (i=(13+40);i<(52+40);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
	rs485_out_buff[51+40]=0x30;
	rs485_out_buff[52+40]=0x32;

	rs485_out_buff[13+40]=0x30;
	rs485_out_buff[14+40]=0x44;
	rs485_out_buff[15+40]=0x37;
	rs485_out_buff[16+40]=0x41;
	rs485_out_buff[17+40]=0x30;
	rs485_out_buff[18+40]=0x44;
	rs485_out_buff[19+40]=0x33;
	rs485_out_buff[20+40]=0x43;
	rs485_out_buff[21+40]=0x31;
	rs485_out_buff[22+40]=0x38;
	rs485_out_buff[23+40]=0x31;
	rs485_out_buff[24+40]=0x38;
	rs485_out_buff[25+40]=0x31;
	rs485_out_buff[26+40]=0x34;
	rs485_out_buff[27+40]=0x31;
	rs485_out_buff[28+40]=0x32;
	rs485_out_buff[29+40]=0x30;
	rs485_out_buff[30+40]=0x30;
	rs485_out_buff[31+40]=0x30;
	rs485_out_buff[32+40]=0x30;
	rs485_out_buff[33+40]=0x30;
	rs485_out_buff[34+40]=0x30;
	rs485_out_buff[35+40]=0x35;
	rs485_out_buff[36+40]=0x35;
	rs485_out_buff[37+40]=0x36;
	rs485_out_buff[38+40]=0x33;
	rs485_out_buff[43+40]=0x46;
	rs485_out_buff[44+40]=0x46;
	rs485_out_buff[45+40]=0x30;
	rs485_out_buff[46+40]=0x45;
	rs485_out_buff[47+40]=0x41;
	rs485_out_buff[48+40]=0x36;
	rs485_out_buff[49+40]=0x36;
	rs485_out_buff[50+40]=0x34;


     if(CheckBox2->Checked) {
	rs485_out_buff[39+40]=0x31;
	rs485_out_buff[40+40]=0x44;
	rs485_out_buff[41+40]=0x34;
	rs485_out_buff[42+40]=0x43;
     }
     /*

*/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б3
     for (i=(13+80);i<(52+80);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
	rs485_out_buff[51+80]=0x30;
	rs485_out_buff[52+80]=0x33;

	rs485_out_buff[13+80]=0x30;
	rs485_out_buff[14+80]=0x44;
	rs485_out_buff[15+80]=0x37;
	rs485_out_buff[16+80]=0x41;
	rs485_out_buff[17+80]=0x30;
	rs485_out_buff[18+80]=0x44;
	rs485_out_buff[19+80]=0x33;
	rs485_out_buff[20+80]=0x43;
	rs485_out_buff[21+80]=0x31;
	rs485_out_buff[22+80]=0x38;
	rs485_out_buff[23+80]=0x31;
	rs485_out_buff[24+80]=0x38;
	rs485_out_buff[25+80]=0x31;
	rs485_out_buff[26+80]=0x34;
	rs485_out_buff[27+80]=0x31;
	rs485_out_buff[28+80]=0x32;
	rs485_out_buff[29+80]=0x30;
	rs485_out_buff[30+80]=0x30;
	rs485_out_buff[31+80]=0x30;
	rs485_out_buff[32+80]=0x30;
	rs485_out_buff[33+80]=0x30;
	rs485_out_buff[34+80]=0x30;
	rs485_out_buff[35+80]=0x35;
	rs485_out_buff[36+80]=0x35;
	rs485_out_buff[37+80]=0x36;
	rs485_out_buff[38+80]=0x33;
	rs485_out_buff[43+80]=0x46;
	rs485_out_buff[44+80]=0x46;
	rs485_out_buff[45+80]=0x30;
	rs485_out_buff[46+80]=0x45;
	rs485_out_buff[47+80]=0x41;
	rs485_out_buff[48+80]=0x36;
	rs485_out_buff[49+80]=0x36;
	rs485_out_buff[50+80]=0x34;

	if(CheckBox3->Checked) {
	rs485_out_buff[39+80]=0x31;
	rs485_out_buff[40+80]=0x44;
	rs485_out_buff[41+80]=0x34;
	rs485_out_buff[42+80]=0x43;
	}

/*


*/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б4
     for (i=(13+120);i<(52+120);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
	rs485_out_buff[51+120]=0x30;
	rs485_out_buff[52+120]=0x34;

	rs485_out_buff[13+120]=0x30;
	rs485_out_buff[14+120]=0x44;
	rs485_out_buff[15+120]=0x37;
	rs485_out_buff[16+120]=0x41;
	rs485_out_buff[17+120]=0x30;
	rs485_out_buff[18+120]=0x44;
	rs485_out_buff[19+120]=0x33;
	rs485_out_buff[20+120]=0x43;
	rs485_out_buff[21+120]=0x31;
	rs485_out_buff[22+120]=0x38;
	rs485_out_buff[23+120]=0x31;
	rs485_out_buff[24+120]=0x38;
	rs485_out_buff[25+120]=0x31;
	rs485_out_buff[26+120]=0x34;
	rs485_out_buff[27+120]=0x31;
	rs485_out_buff[28+120]=0x32;
	rs485_out_buff[29+120]=0x30;
	rs485_out_buff[30+120]=0x30;
	rs485_out_buff[31+120]=0x30;
	rs485_out_buff[32+120]=0x30;
	rs485_out_buff[33+120]=0x30;
	rs485_out_buff[34+120]=0x30;
	rs485_out_buff[35+120]=0x35;
	rs485_out_buff[36+120]=0x35;
	rs485_out_buff[37+120]=0x36;
	rs485_out_buff[38+120]=0x33;
	rs485_out_buff[43+120]=0x46;
	rs485_out_buff[44+120]=0x46;
	rs485_out_buff[45+120]=0x30;
	rs485_out_buff[46+120]=0x45;
	rs485_out_buff[47+120]=0x41;
	rs485_out_buff[48+120]=0x36;
	rs485_out_buff[49+120]=0x36;
	rs485_out_buff[50+120]=0x34;

	if(CheckBox4->Checked) {
	rs485_out_buff[39+120]=0x31;
	rs485_out_buff[40+120]=0x44;
	rs485_out_buff[41+120]=0x34;
	rs485_out_buff[42+120]=0x43;
	}
/*


*/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б5
     for (i=(13+160);i<(52+160);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
	rs485_out_buff[51+160]=0x30;
	rs485_out_buff[52+160]=0x35;

	rs485_out_buff[13+160]=0x30;
	rs485_out_buff[14+160]=0x44;
	rs485_out_buff[15+160]=0x37;
	rs485_out_buff[16+160]=0x41;
	rs485_out_buff[17+160]=0x30;
	rs485_out_buff[18+160]=0x44;
	rs485_out_buff[19+160]=0x33;
	rs485_out_buff[20+160]=0x43;
	rs485_out_buff[21+160]=0x31;
	rs485_out_buff[22+160]=0x38;
	rs485_out_buff[23+160]=0x31;
	rs485_out_buff[24+160]=0x38;
	rs485_out_buff[25+160]=0x31;
	rs485_out_buff[26+160]=0x34;
	rs485_out_buff[27+160]=0x31;
	rs485_out_buff[28+160]=0x32;
	rs485_out_buff[29+160]=0x30;
	rs485_out_buff[30+160]=0x30;
	rs485_out_buff[31+160]=0x30;
	rs485_out_buff[32+160]=0x30;
	rs485_out_buff[33+160]=0x30;
	rs485_out_buff[34+160]=0x30;
	rs485_out_buff[35+160]=0x35;
	rs485_out_buff[36+160]=0x35;
	rs485_out_buff[37+160]=0x36;
	rs485_out_buff[38+160]=0x33;
	rs485_out_buff[43+160]=0x46;
	rs485_out_buff[44+160]=0x46;
	rs485_out_buff[45+160]=0x30;
	rs485_out_buff[46+160]=0x45;
	rs485_out_buff[47+160]=0x41;
	rs485_out_buff[48+160]=0x36;
	rs485_out_buff[49+160]=0x36;
	rs485_out_buff[50+160]=0x34;

	if(CheckBox5->Checked) {
	rs485_out_buff[39+160]=0x31;
	rs485_out_buff[40+160]=0x44;
	rs485_out_buff[41+160]=0x34;
	rs485_out_buff[42+160]=0x43;
	}
/*


*/

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б6
     for (i=(13+200);i<(52+200);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
	rs485_out_buff[51+200]=0x30;
	rs485_out_buff[52+200]=0x36;

 	rs485_out_buff[13+200]=0x30;
	rs485_out_buff[14+200]=0x44;
	rs485_out_buff[15+200]=0x37;
	rs485_out_buff[16+200]=0x41;
	rs485_out_buff[17+200]=0x30;
	rs485_out_buff[18+200]=0x44;
	rs485_out_buff[19+200]=0x33;
	rs485_out_buff[20+200]=0x43;
     rs485_out_buff[21+200]=0x31;
	rs485_out_buff[22+200]=0x38;
	rs485_out_buff[23+200]=0x31;
	rs485_out_buff[24+200]=0x38;
	rs485_out_buff[25+200]=0x31;
	rs485_out_buff[26+200]=0x34;
	rs485_out_buff[27+200]=0x31;
	rs485_out_buff[28+200]=0x32;
	rs485_out_buff[29+200]=0x30;
	rs485_out_buff[30+200]=0x30;
	rs485_out_buff[31+200]=0x30;
	rs485_out_buff[32+200]=0x30;
	rs485_out_buff[33+200]=0x30;
	rs485_out_buff[34+200]=0x30;
	rs485_out_buff[35+200]=0x35;
	rs485_out_buff[36+200]=0x35;
	rs485_out_buff[37+200]=0x36;
	rs485_out_buff[38+200]=0x33;
	rs485_out_buff[43+200]=0x46;
	rs485_out_buff[44+200]=0x46;
	rs485_out_buff[45+200]=0x30;
	rs485_out_buff[46+200]=0x45;
	rs485_out_buff[47+200]=0x41;
	rs485_out_buff[48+200]=0x36;
	rs485_out_buff[49+200]=0x36;
	rs485_out_buff[50+200]=0x34;

	if(CheckBox6->Checked) {
	rs485_out_buff[39+200]=0x31;
	rs485_out_buff[40+200]=0x44;
	rs485_out_buff[41+200]=0x34;
	rs485_out_buff[42+200]=0x43;
     }
/*


 */

 //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//Б7
     for (i=(13+240);i<(52+240);i++)
     	{
          rs485_out_buff[i]=0x30;
          }
	rs485_out_buff[51+240]=0x30;
	rs485_out_buff[52+240]=0x37;

 	rs485_out_buff[13+240]=0x30;
	rs485_out_buff[14+240]=0x44;
	rs485_out_buff[15+240]=0x37;
	rs485_out_buff[16+240]=0x41;
	rs485_out_buff[17+240]=0x30;
	rs485_out_buff[18+240]=0x44;
	rs485_out_buff[19+240]=0x33;
	rs485_out_buff[20+240]=0x43;
	rs485_out_buff[21+240]=0x31;
	rs485_out_buff[22+240]=0x38;
	rs485_out_buff[23+240]=0x31;
	rs485_out_buff[24+240]=0x38;
	rs485_out_buff[25+240]=0x31;
	rs485_out_buff[26+240]=0x34;
	rs485_out_buff[27+240]=0x31;
	rs485_out_buff[28+240]=0x32;
	rs485_out_buff[29+240]=0x30;
	rs485_out_buff[30+240]=0x30;
	rs485_out_buff[31+240]=0x30;
	rs485_out_buff[32+240]=0x30;
	rs485_out_buff[33+240]=0x30;
	rs485_out_buff[34+240]=0x30;
	rs485_out_buff[35+240]=0x35;
	rs485_out_buff[36+240]=0x35;
	rs485_out_buff[37+240]=0x36;
	rs485_out_buff[38+240]=0x33;
	rs485_out_buff[43+240]=0x46;
	rs485_out_buff[44+240]=0x46;
	rs485_out_buff[45+240]=0x30;
	rs485_out_buff[46+240]=0x45;
	rs485_out_buff[47+240]=0x41;
	rs485_out_buff[48+240]=0x36;
	rs485_out_buff[49+240]=0x36;
	rs485_out_buff[50+240]=0x34;

	if(CheckBox7->Checked) {
	rs485_out_buff[39+240]=0x31;
	rs485_out_buff[40+240]=0x44;
	rs485_out_buff[41+240]=0x34;
	rs485_out_buff[42+240]=0x43;
	}
/*


*/
	rs485_out_buff[293]=0x43;
	rs485_out_buff[294]=0x37;
	rs485_out_buff[295]=0x45;
	rs485_out_buff[296]=0x43;
	rs485_out_buff[297]=0x0d;

	uart1_out_adr(rs485_out_buff,298);
     //uart_modbus_request();
	
		//rs485_cnt=0;
		//bRS485ERR=0;

	}
	else if(bRX485==2)
	{
	rs485_out_buff[0]=0x7e;
	rs485_out_buff[1]=0x31;
	rs485_out_buff[2]=0x31;
	rs485_out_buff[3]=0x30;
	rs485_out_buff[4]=0x31;
	rs485_out_buff[5]=0x44;
	rs485_out_buff[6]=0x30;
	rs485_out_buff[7]=0x30;
	rs485_out_buff[8]=0x30;
	rs485_out_buff[9]=0x36;
	rs485_out_buff[10]=0x31;
	rs485_out_buff[11]=0x31;
	rs485_out_buff[12]=0x38;
	
	rs485_out_buff[13]=0x34;
	rs485_out_buff[14]=0x35;
	rs485_out_buff[15]=0x30;
	rs485_out_buff[16]=0x36;
	rs485_out_buff[17]=0x41;
	rs485_out_buff[18]=0x31;
	rs485_out_buff[19]=0x35;
	rs485_out_buff[20]=0x34;
	
	rs485_out_buff[21]=0x31;
	rs485_out_buff[22]=0x32;
	rs485_out_buff[23]=0x30;
	rs485_out_buff[24]=0x30;
	rs485_out_buff[25]=0x30;
	rs485_out_buff[26]=0x30;
	rs485_out_buff[27]=0x30;
	rs485_out_buff[28]=0x30;
	rs485_out_buff[29]=0x30;
	rs485_out_buff[30]=0x30;
	rs485_out_buff[31]=0x30;
	rs485_out_buff[32]=0x30;
	rs485_out_buff[33]=0x30;
	rs485_out_buff[34]=0x30;
	rs485_out_buff[35]=0x30;
	rs485_out_buff[36]=0x30;
	rs485_out_buff[37]=0x30;
	rs485_out_buff[38]=0x30;
	rs485_out_buff[39]=0x30;
	rs485_out_buff[40]=0x30;
	rs485_out_buff[41]=0x30;
	rs485_out_buff[42]=0x30;
	rs485_out_buff[43]=0x30;
	rs485_out_buff[44]=0x30;
	rs485_out_buff[45]=0x30;
	rs485_out_buff[46]=0x30;
	rs485_out_buff[47]=0x33;
	rs485_out_buff[48]=0x32;
	rs485_out_buff[49]=0x34;
	rs485_out_buff[50]=0x35;
	rs485_out_buff[51]=0x30;
	rs485_out_buff[52]=0x30;
	rs485_out_buff[53]=0x30;
	rs485_out_buff[54]=0x31;	
	
	rs485_out_buff[21+34]=0x30;
	rs485_out_buff[22+34]=0x30;
	rs485_out_buff[23+34]=0x33;
	rs485_out_buff[24+34]=0x34;
	rs485_out_buff[25+34]=0x30;
	rs485_out_buff[26+34]=0x30;
	rs485_out_buff[27+34]=0x30;
	rs485_out_buff[28+34]=0x30;
	rs485_out_buff[29+34]=0x30;
	rs485_out_buff[30+34]=0x30;
	rs485_out_buff[31+34]=0x30;
	rs485_out_buff[32+34]=0x30;
	rs485_out_buff[33+34]=0x30;
	rs485_out_buff[34+34]=0x30;
	rs485_out_buff[35+34]=0x30;
	rs485_out_buff[36+34]=0x30;
	rs485_out_buff[37+34]=0x30;
	rs485_out_buff[38+34]=0x30;
	rs485_out_buff[39+34]=0x30;
	rs485_out_buff[40+34]=0x30;
	rs485_out_buff[41+34]=0x30;
	rs485_out_buff[42+34]=0x30;
	rs485_out_buff[43+34]=0x30;
	rs485_out_buff[44+34]=0x30;
	rs485_out_buff[45+34]=0x34;
	rs485_out_buff[46+34]=0x33;
	rs485_out_buff[47+34]=0x30;
	rs485_out_buff[48+34]=0x30;
	rs485_out_buff[49+34]=0x30;
	rs485_out_buff[50+34]=0x30;
	rs485_out_buff[51+34]=0x36;
	rs485_out_buff[52+34]=0x37;
	rs485_out_buff[53+34]=0x30;
	rs485_out_buff[54+34]=0x32;

	rs485_out_buff[21+68]=0x30;
	rs485_out_buff[22+68]=0x30;
	rs485_out_buff[23+68]=0x30;
	rs485_out_buff[24+68]=0x30;
	rs485_out_buff[25+68]=0x35;
	rs485_out_buff[26+68]=0x36;
	rs485_out_buff[27+68]=0x30;
	rs485_out_buff[28+68]=0x30;
	rs485_out_buff[29+68]=0x30;
	rs485_out_buff[30+68]=0x30;
	rs485_out_buff[31+68]=0x30;
	rs485_out_buff[32+68]=0x30;
	rs485_out_buff[33+68]=0x30;
	rs485_out_buff[34+68]=0x30;
	rs485_out_buff[35+68]=0x30;
	rs485_out_buff[36+68]=0x30;
	rs485_out_buff[37+68]=0x30;
	rs485_out_buff[38+68]=0x30;
	rs485_out_buff[39+68]=0x30;
	rs485_out_buff[40+68]=0x30;
	rs485_out_buff[41+68]=0x30;
	rs485_out_buff[42+68]=0x30;
	rs485_out_buff[43+68]=0x36;
	rs485_out_buff[44+68]=0x35;
	rs485_out_buff[45+68]=0x30;
	rs485_out_buff[46+68]=0x30;
	rs485_out_buff[47+68]=0x30;
	rs485_out_buff[48+68]=0x30;
	rs485_out_buff[49+68]=0x30;
	rs485_out_buff[50+68]=0x30;
	rs485_out_buff[51+68]=0x30;
	rs485_out_buff[52+68]=0x30;
	rs485_out_buff[53+68]=0x38;
	rs485_out_buff[54+68]=0x33;	
	
	rs485_out_buff[21+102]=0x30;
	rs485_out_buff[22+102]=0x30;
	rs485_out_buff[23+102]=0x30;
	rs485_out_buff[24+102]=0x30;
	rs485_out_buff[25+102]=0x30;
	rs485_out_buff[26+102]=0x30;
	rs485_out_buff[27+102]=0x37;
	rs485_out_buff[28+102]=0x38;
	rs485_out_buff[29+102]=0x30;
	rs485_out_buff[30+102]=0x30;
	rs485_out_buff[31+102]=0x30;
	rs485_out_buff[32+102]=0x30;
	rs485_out_buff[33+102]=0x30;
	rs485_out_buff[34+102]=0x30;
	rs485_out_buff[35+102]=0x30;
	rs485_out_buff[36+102]=0x30;
	rs485_out_buff[37+102]=0x30;
	rs485_out_buff[38+102]=0x30;
	rs485_out_buff[39+102]=0x30;
	rs485_out_buff[40+102]=0x30;
	rs485_out_buff[41+102]=0x38;
	rs485_out_buff[42+102]=0x37;
	rs485_out_buff[43+102]=0x30;
	rs485_out_buff[44+102]=0x30;
	rs485_out_buff[45+102]=0x30;
	rs485_out_buff[46+102]=0x30;
	rs485_out_buff[47+102]=0x30;
	rs485_out_buff[48+102]=0x30;
	rs485_out_buff[49+102]=0x30;
	rs485_out_buff[50+102]=0x30;
	rs485_out_buff[51+102]=0x30;
	rs485_out_buff[52+102]=0x30;
	rs485_out_buff[53+102]=0x30;
	rs485_out_buff[54+102]=0x34;

	rs485_out_buff[21+136]=0x30;
	rs485_out_buff[22+136]=0x30;
	rs485_out_buff[23+136]=0x30;
	rs485_out_buff[24+136]=0x30;
	rs485_out_buff[25+136]=0x30;
	rs485_out_buff[26+136]=0x30;
	rs485_out_buff[27+136]=0x30;
	rs485_out_buff[28+136]=0x30;
	rs485_out_buff[29+136]=0x39;
	rs485_out_buff[30+136]=0x41;
	rs485_out_buff[31+136]=0x30;
	rs485_out_buff[32+136]=0x30;
	rs485_out_buff[33+136]=0x30;
	rs485_out_buff[34+136]=0x30;
	rs485_out_buff[35+136]=0x30;
	rs485_out_buff[36+136]=0x30;
	rs485_out_buff[37+136]=0x30;
	rs485_out_buff[38+136]=0x30;
	rs485_out_buff[39+136]=0x41;
	rs485_out_buff[40+136]=0x39;
	rs485_out_buff[41+136]=0x30;
	rs485_out_buff[42+136]=0x30;
	rs485_out_buff[43+136]=0x30;
	rs485_out_buff[44+136]=0x30;
	rs485_out_buff[45+136]=0x30;
	rs485_out_buff[46+136]=0x30;
	rs485_out_buff[47+136]=0x30;
	rs485_out_buff[48+136]=0x30;
	rs485_out_buff[49+136]=0x30;
	rs485_out_buff[50+136]=0x30;
	rs485_out_buff[51+136]=0x30;
	rs485_out_buff[52+136]=0x30;
	rs485_out_buff[53+136]=0x30;
	rs485_out_buff[54+136]=0x35;	
	
	rs485_out_buff[21+170]=0x30;
	rs485_out_buff[22+170]=0x30;
	rs485_out_buff[23+170]=0x30;
	rs485_out_buff[24+170]=0x30;
	rs485_out_buff[25+170]=0x30;
	rs485_out_buff[26+170]=0x30;
	rs485_out_buff[27+170]=0x30;
	rs485_out_buff[28+170]=0x30;
	rs485_out_buff[29+170]=0x30;
	rs485_out_buff[30+170]=0x30;
	rs485_out_buff[31+170]=0x42;
	rs485_out_buff[32+170]=0x43;
	rs485_out_buff[33+170]=0x30;
	rs485_out_buff[34+170]=0x30;
	rs485_out_buff[35+170]=0x30;
	rs485_out_buff[36+170]=0x30;
	rs485_out_buff[37+170]=0x43;
	rs485_out_buff[38+170]=0x42;
	rs485_out_buff[39+170]=0x30;
	rs485_out_buff[40+170]=0x30;
	rs485_out_buff[41+170]=0x30;
	rs485_out_buff[42+170]=0x30;
	rs485_out_buff[43+170]=0x30;
	rs485_out_buff[44+170]=0x30;
	rs485_out_buff[45+170]=0x30;
	rs485_out_buff[46+170]=0x30;
	rs485_out_buff[47+170]=0x30;
	rs485_out_buff[48+170]=0x30;
	rs485_out_buff[49+170]=0x30;
	rs485_out_buff[50+170]=0x30;
	rs485_out_buff[51+170]=0x30;
	rs485_out_buff[52+170]=0x30;
	rs485_out_buff[53+170]=0x30;
	rs485_out_buff[54+170]=0x36;

	rs485_out_buff[21+204]=0x30;
	rs485_out_buff[22+204]=0x30;
	rs485_out_buff[23+204]=0x30;
	rs485_out_buff[24+204]=0x30;
	rs485_out_buff[25+204]=0x30;
	rs485_out_buff[26+204]=0x30;
	rs485_out_buff[27+204]=0x30;
	rs485_out_buff[28+204]=0x30;
	rs485_out_buff[29+204]=0x30;
	rs485_out_buff[30+204]=0x30;
	rs485_out_buff[31+204]=0x30;
	rs485_out_buff[32+204]=0x30;
	rs485_out_buff[33+204]=0x44;
	rs485_out_buff[34+204]=0x45;
	rs485_out_buff[35+204]=0x45;
	rs485_out_buff[36+204]=0x44;
	rs485_out_buff[37+204]=0x30;
	rs485_out_buff[38+204]=0x30;
	rs485_out_buff[39+204]=0x30;
	rs485_out_buff[40+204]=0x30;
	rs485_out_buff[41+204]=0x30;
	rs485_out_buff[42+204]=0x30;
	rs485_out_buff[43+204]=0x30;
	rs485_out_buff[44+204]=0x30;
	rs485_out_buff[45+204]=0x30;
	rs485_out_buff[46+204]=0x30;
	rs485_out_buff[47+204]=0x30;
	rs485_out_buff[48+204]=0x30;
	rs485_out_buff[49+204]=0x30;
	rs485_out_buff[50+204]=0x30;
	rs485_out_buff[51+204]=0x30;
	rs485_out_buff[52+204]=0x30;
	rs485_out_buff[53+204]=0x30;
	rs485_out_buff[54+204]=0x37;
	
	rs485_out_buff[259]=0x43;
	rs485_out_buff[260]=0x46;
	rs485_out_buff[261]=0x31;
	rs485_out_buff[262]=0x39;
	rs485_out_buff[263]=0x0d;

	uart1_out_adr(rs485_out_buff,264);

	}
bRX485=0;	


}


void __fastcall TForm1::ComPort1RxChar(TObject *Sender, int Count)
{

int data,i;
unsigned char temp;
char cnt;


//plazma=Count;

for(i=0;i<Count;i++)
 	{
     ComPort1->Read(&data,1);
     temp=data;
	rx_buffer[rs485_rx_cnt]=data;
	rs485_rx_cnt++;


	if((data==0x0d)&&(rs485_rx_cnt==20))
		{
		if(rx_buffer[8]==0x32){
          rx_plazma++;
     	Label1->Caption=IntToStr(rx_plazma);
		bRX485=1;
		}

		if(rx_buffer[8]==0x33){
          tx_plazma++;
     	Label2->Caption=IntToStr(tx_plazma);
		bRX485=2;
		}
	}
	if(data==0x0d)rs485_rx_cnt=0;
     }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x31;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x32;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x62;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x41;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x51;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
#define STR	2

uart_out_out(4,CMND,40,STR%256,STR/256,0,0,0,0);
//Memo1->Lines->Add("Страница №"+IntToStr(STR));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x13;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;
if(ComPort1->Connected)ComPort1->Write(UOB,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x14;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;
if(ComPort1->Connected)ComPort1->Write(UOB,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x61;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x12;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;
if(ComPort1->Connected)ComPort1->Write(UOB,8);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x11;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x72;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
uart_out_out(3,CMND,24,1,0,0,0,0,0);
//Memo1->Lines->Add("Стирание микросхемы");
}
//---------------------------------------------------------------------------





void __fastcall TForm1::Timer1Timer(TObject *Sender)
{

b100Hz=1;
//t1cnt++;

if(++t1cnt>=10)
        {
        t1cnt=0;
        b10Hz=1;
        //CAP_ZAR_TIME=;

        ind_hndl();
        }

if(++t2cnt>=20)
        {
        t2cnt=0;
        b5Hz=1;
        }

if(++t3cnt>=5)
        {
        t3cnt=0;
        b2Hz=1;
        }

if(++t4cnt>=100)
        {
        t4cnt=0;
        b1Hz=1;
        }

if(b5Hz)
        {
        b5Hz=0;
        if(ComPort1->Connected)
                {
               // uart_modbus_request();
                }
        }
if(b1Hz)
        {
        b1Hz=0;

        }
uart_in_an();

}
//---------------------------------------------------------------------------



void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
unsigned char UOB_[100];
int temp,temp1;
float tempF;
double tempD;
unsigned short crc_temp;

if (Key==13)
        {
        try  {


        //temp= (int)tempD;//Edit1->Text.ToInt();

        //tempF=FloatToStr(tempD);

        temp= (int)(((tempD)*10)+0.1);
        if(temp>9999)temp=9999;
        if(temp<0)temp=0;
        Label16->Caption= IntToStr(temp);
        Button9->SetFocus();
        temp1=0x23;


        UOB_[0]=0x03;
        UOB_[1]=0x06;
        UOB_[2]=0x00;
        UOB_[3]=40;
        UOB_[4]=(char)(temp/256);
        UOB_[5]=(char)(temp%256);
 //       UOB[6]=(char)(temp1/256);
 //       UOB[7]=(char)(temp1%256);
        crc_temp=CRC16_2(UOB_,6);
        UOB_[6]=crc_temp%256;
        UOB_[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB_,8);


        }
        catch (...)
	        {
                ShowMessage("Неверное значение");
                }
        }
}
//---------------------------------------------------------------------------


//-----------------------------------------------
unsigned short __fastcall TForm1::CRC16_2(unsigned char* buf, short len)
{
unsigned short crc = 0xFFFF;
unsigned short pos;
short i;

for (pos = 0; pos < len; pos++)
  	{
    	crc ^= (unsigned short)buf[pos];          // XOR byte into least sig. byte of crc

    	for ( i = 8; i != 0; i--)
		{    // Loop over each bit
      	if ((crc & 0x0001) != 0) 
			{      // If the LSB is set
        		crc >>= 1;                    // Shift right and XOR 0xA001
        		crc ^= 0xA001;
      		}
      	else  crc >>= 1;                    // Just shift right
    		}
  	}
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
return crc;
}
void __fastcall TForm1::Button17Click(TObject *Sender)
{
        if(ComPort1->Connected)
                {
                uart_modbus_request();
                }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2KeyPress(TObject *Sender, char &Key)
{
unsigned char UOB_[100];
int temp,temp1;
float tempF;
double tempD;
unsigned short crc_temp;

if (Key==13)
        {
        try  {


        //temp= (int)tempD;//Edit1->Text.ToInt();

        //tempF=FloatToStr(tempD);

        temp= (int)(((tempD)*10)+0.1);
        if(temp>9999)temp=9999;
        if(temp<0)temp=0;
        Label16->Caption= IntToStr(temp);
        Button9->SetFocus();
        temp1=0x23;


        UOB_[0]=0x03;
        UOB_[1]=0x06;
        UOB_[2]=0x00;
        UOB_[3]=41;
        UOB_[4]=(char)(temp/256);
        UOB_[5]=(char)(temp%256);
 //       UOB[6]=(char)(temp1/256);
 //       UOB[7]=(char)(temp1%256);
        crc_temp=CRC16_2(UOB_,6);
        UOB_[6]=crc_temp%256;
        UOB_[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB_,8);


        }
        catch (...)
	        {
                ShowMessage("Неверное значение");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3KeyPress(TObject *Sender, char &Key)
{
unsigned char UOB_[100];
int temp,temp1;
float tempF;
double tempD;
unsigned short crc_temp;

if (Key==13)
        {
        try  {


        //temp= (int)tempD;//Edit1->Text.ToInt();

        //tempF=FloatToStr(tempD);

        temp= (int)(((tempD)*10)+0.1);
        if(temp>9999)temp=9999;
        if(temp<0)temp=0;
        Label16->Caption= IntToStr(temp);
        Button9->SetFocus();
        temp1=0x23;


        UOB_[0]=0x03;
        UOB_[1]=0x06;
        UOB_[2]=0x00;
        UOB_[3]=42;
        UOB_[4]=(char)(temp/256);
        UOB_[5]=(char)(temp%256);
 //       UOB[6]=(char)(temp1/256);
 //       UOB[7]=(char)(temp1%256);
        crc_temp=CRC16_2(UOB_,6);
        UOB_[6]=crc_temp%256;
        UOB_[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB_,8);


        }
        catch (...)
	        {
                ShowMessage("Неверное значение");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4KeyPress(TObject *Sender, char &Key)
{
unsigned char UOB_[100];
int temp,temp1;
float tempF;
double tempD;
unsigned short crc_temp;

if (Key==13)
        {
        try  {




        UOB_[0]=0x03;
        UOB_[1]=0x06;
        UOB_[2]=0x00;
        UOB_[3]=43;
        UOB_[4]=(char)(temp/256);
        UOB_[5]=(char)(temp%256);
 //       UOB[6]=(char)(temp1/256);
 //       UOB[7]=(char)(temp1%256);
        crc_temp=CRC16_2(UOB_,6);
        UOB_[6]=crc_temp%256;
        UOB_[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB_,8);


        }
        catch (...)
	        {
                ShowMessage("Неверное значение");
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x42;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x52;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);

//requestStatus = rsGETSETTED;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
unsigned short crc_temp;
UOB[0]=0x03;
UOB[1]=0x06;
UOB[2]=0x00;
UOB[3]=0x32;
UOB[4]=0x00;
UOB[5]=0x71;
crc_temp=CRC16_2(UOB,6);
UOB[6]=crc_temp%256;
UOB[7]=crc_temp/256;


if(ComPort1->Connected)ComPort1->Write(UOB,8);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5KeyPress(TObject *Sender, char &Key)
{
unsigned char UOB_[100];
int temp,temp1;
float tempF;
double tempD;
unsigned short crc_temp;

if (Key==13)
        {
        try  {




        UOB_[0]=0x03;
        UOB_[1]=0x06;
        UOB_[2]=0x00;
        UOB_[3]=44;
        UOB_[4]=(char)(temp/256);
        UOB_[5]=(char)(temp%256);
 //       UOB[6]=(char)(temp1/256);
 //       UOB[7]=(char)(temp1%256);
        crc_temp=CRC16_2(UOB_,6);
        UOB_[6]=crc_temp%256;
        UOB_[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB_,8);


        }
        catch (...)
	        {
                ShowMessage("Неверное значение");
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit6KeyPress(TObject *Sender, char &Key)
{
unsigned char UOB_[100];
int temp,temp1;
float tempF;
double tempD;
unsigned short crc_temp;

if (Key==13)
        {
        try  {



        UOB_[0]=0x03;
        UOB_[1]=0x06;
        UOB_[2]=0x00;
        UOB_[3]=45;
        UOB_[4]=(char)(temp/256);
        UOB_[5]=(char)(temp%256);
 //       UOB[6]=(char)(temp1/256);
 //       UOB[7]=(char)(temp1%256);
        crc_temp=CRC16_2(UOB_,6);
        UOB_[6]=crc_temp%256;
        UOB_[7]=crc_temp/256;

if(ComPort1->Connected)ComPort1->Write(UOB_,8);


        }
        catch (...)
	        {
                ShowMessage("Неверное значение");
                }
        }
}
//---------------------------------------------------------------------------


