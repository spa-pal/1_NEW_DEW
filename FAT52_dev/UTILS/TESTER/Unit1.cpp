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

static short plazma;
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

     ComPort1->BaudRate=br9600;
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




if(!(Edit1->Focused()))Edit1->Text= IntToStr(CAP_ZAR_TIME/1000)+ (IntToStr(CAP_ZAR_TIME/100)%10) + (IntToStr(CAP_ZAR_TIME/10)%10) + ',' + (IntToStr(CAP_ZAR_TIME%10));
if(!(Edit2->Focused()))Edit2->Text= IntToStr(CAP_PAUSE1_TIME/1000)+ (IntToStr(CAP_PAUSE1_TIME/100)%10) + (IntToStr(CAP_PAUSE1_TIME/10)%10) + ',' + (IntToStr(CAP_PAUSE1_TIME%10));
if(!(Edit3->Focused()))Edit3->Text= IntToStr(CAP_RAZR_TIME/1000)+ (IntToStr(CAP_RAZR_TIME/100)%10) + (IntToStr(CAP_RAZR_TIME/10)%10) + ',' + (IntToStr(CAP_RAZR_TIME%10));
if(!(Edit4->Focused()))Edit4->Text= IntToStr(CAP_PAUSE2_TIME/1000)+ (IntToStr(CAP_PAUSE2_TIME/100)%10) + (IntToStr(CAP_PAUSE2_TIME/10)%10) + ',' + (IntToStr(CAP_PAUSE2_TIME%10));
if(!(Edit5->Focused()))Edit5->Text= IntToStr(CAP_MAX_VOLT/100) + (IntToStr(CAP_MAX_VOLT/10)%10) + (IntToStr(CAP_MAX_VOLT%10));
if(!(Edit6->Focused()))Edit6->Text= IntToStr(CAP_WRK_CURR/100) + (IntToStr(CAP_WRK_CURR/10)%10) + (IntToStr(CAP_WRK_CURR%10));

Edit7->Text= IntToStr(CAP_COUNTER/1000)+ (IntToStr(CAP_COUNTER/100)%10) + (IntToStr(CAP_COUNTER/10)%10) + (IntToStr(CAP_COUNTER%10));
Edit8->Text= IntToStr(CAP_TIME_HOUR/10) + IntToStr(CAP_TIME_HOUR%10) + ":" + IntToStr(CAP_TIME_MIN/10) + IntToStr(CAP_TIME_MIN%10) + ":" + IntToStr(CAP_TIME_SEC/10) + IntToStr(CAP_TIME_SEC%10);

//plazma=;

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
unsigned i;
i=0;




if(requestStatus == rsGETSETTED)
        { 
        requestStatus = rsOFF;
        if((UIB[1]==0x03))
                { plazma++;
                
                CAP_ZAR_TIME= ((unsigned short)UIB[4]) + (((unsigned short)UIB[3])<<8);
                CAP_PAUSE1_TIME= (unsigned short)UIB[6] + (((unsigned short)UIB[5])*256);
                CAP_RAZR_TIME= (unsigned short)UIB[8] + (((unsigned short)UIB[7])*256);
                CAP_PAUSE2_TIME= (unsigned short)UIB[10] + (((unsigned short)UIB[9])*256);
                CAP_MAX_VOLT= (unsigned short)UIB[12] + (((unsigned short)UIB[11])*256);
                CAP_WRK_CURR= (unsigned short)UIB[14] + (((unsigned short)UIB[13])*256);
                CAP_COUNTER= (unsigned short)UIB[16] + (((unsigned short)UIB[15])*256);
                CAP_TIME_SEC= (unsigned short)UIB[18] + (((unsigned short)UIB[17])*256);
                CAP_TIME_MIN= (unsigned short)UIB[20] + (((unsigned short)UIB[19])*256);
                CAP_TIME_HOUR= (unsigned short)UIB[22] + (((unsigned short)UIB[21])*256);

                //CAP_ZAR_TIME=1234;
                }
        }

//plazma++;
if((UIB[0]==0x11))
	{
    	//Memo1->Lines->Add(char2str_h(UIB[0])+"  "+char2str_h(UIB[1])+"  "+char2str_h(UIB[2])+"  "+char2str_h(UIB[3])+"  "+char2str_h(UIB[4])+"  "+char2str_h(UIB[5])+"  "+char2str_h(UIB[6]));

     }

else if((UIB[0]==CMND)&&(UIB[1]==1))
	{
    	//Memo1->Lines->Add(char2str_h(UIB[2])+"  "+char2str_h(UIB[3])+"  "+char2str_h(UIB[4])+"  "+char2str_h(UIB[5])+"  "+char2str_h(UIB[6]));

     }
else if((UIB[0]==CMND)&&(UIB[1]==2))
	{
    	//Memo1->Lines->Add(char2str_h(UIB[2]));

     }
else if((UIB[0]==CMND)&&(UIB[1]==3))
	{
    	//Memo1->Lines->Add(char2str_h(UIB[2]));

     }
/*
else if((UIB[0]==CMND)&&(UIB[1]==10))
	{
	unsigned int adress;
     adress=*((unsigned int*)&UIB[2]);
     if((adress&0x000001ff)==0) Memo1->Lines->Add("Сектор №"+IntToStr(adress>>9));
     Memo1->Lines->Add(long2str_h(adress)+"    "+char2str_h(UIB[6])+"  "+char2str_h(UIB[7])+"  "+char2str_h(UIB[8])+"  "+char2str_h(UIB[9])+"  "
     								   +char2str_h(UIB[10])+"  "+char2str_h(UIB[11])+"  "+char2str_h(UIB[12])+"  "+char2str_h(UIB[13])+"  "
                                                +char2str_h(UIB[14])+"  "+char2str_h(UIB[15])+"  "+char2str_h(UIB[16])+"  "+char2str_h(UIB[17])+"  "
                                                +char2str_h(UIB[18])+"  "+char2str_h(UIB[19])+"  "+char2str_h(UIB[20])+"  "+char2str_h(UIB[21])+"  "
                                                +UIB[6]+UIB[7]+UIB[8]+UIB[9]+UIB[10]+UIB[11]+UIB[12]+UIB[13]+UIB[14]+UIB[15]+UIB[16]+UIB[17]+UIB[18]+UIB[19]+UIB[20]+UIB[21]);

     Memo1->Lines->Add(long2str_h(adress+16)+"    "+char2str_h(UIB[22])+"  "+char2str_h(UIB[23])+"  "+char2str_h(UIB[24])+"  "+char2str_h(UIB[25])+"  "
     								   +char2str_h(UIB[26])+"  "+char2str_h(UIB[27])+"  "+char2str_h(UIB[28])+"  "+char2str_h(UIB[29])+"  "
                                                +char2str_h(UIB[30])+"  "+char2str_h(UIB[31])+"  "+char2str_h(UIB[32])+"  "+char2str_h(UIB[33])+"  "
                                                +char2str_h(UIB[34])+"  "+char2str_h(UIB[35])+"  "+char2str_h(UIB[36])+"  "+char2str_h(UIB[37])+"  "
                                                +UIB[22]+UIB[23]+UIB[24]+UIB[25]+UIB[26]+UIB[27]+UIB[28]+UIB[29]+UIB[30]+UIB[31]+UIB[32]+UIB[33]+UIB[34]+UIB[35]+UIB[36]+UIB[37]);

     Memo1->Lines->Add(long2str_h(adress+32)+"    "+char2str_h(UIB[38])+"  "+char2str_h(UIB[39])+"  "+char2str_h(UIB[40])+"  "+char2str_h(UIB[41])+"  "
     								   +char2str_h(UIB[42])+"  "+char2str_h(UIB[43])+"  "+char2str_h(UIB[44])+"  "+char2str_h(UIB[45])+"  "
                                                +char2str_h(UIB[46])+"  "+char2str_h(UIB[47])+"  "+char2str_h(UIB[48])+"  "+char2str_h(UIB[49])+"  "
                                                +char2str_h(UIB[50])+"  "+char2str_h(UIB[51])+"  "+char2str_h(UIB[52])+"  "+char2str_h(UIB[53])+"  "
                                                +UIB[38]+UIB[39]+UIB[40]+UIB[41]+UIB[42]+UIB[43]+UIB[44]+UIB[45]+UIB[46]+UIB[47]+UIB[48]+UIB[49]+UIB[50]+UIB[51]+UIB[52]+UIB[37]);

     Memo1->Lines->Add(long2str_h(adress+48)+"    "+char2str_h(UIB[54])+"  "+char2str_h(UIB[55])+"  "+char2str_h(UIB[56])+"  "+char2str_h(UIB[57])+"  "
     								   +char2str_h(UIB[58])+"  "+char2str_h(UIB[59])+"  "+char2str_h(UIB[60])+"  "+char2str_h(UIB[61])+"  "
                                                +char2str_h(UIB[62])+"  "+char2str_h(UIB[63])+"  "+char2str_h(UIB[64])+"  "+char2str_h(UIB[65])+"  "
                                                +char2str_h(UIB[66])+"  "+char2str_h(UIB[67])+"  "+char2str_h(UIB[68])+"  "+char2str_h(UIB[69])+"  "
                                                +UIB[54]+UIB[55]+UIB[56]+UIB[57]+UIB[58]+UIB[59]+UIB[60]+UIB[61]+UIB[62]+UIB[63]+UIB[64]+UIB[65]+UIB[66]+UIB[67]+UIB[68]+UIB[69]);

     } */



if((UIB[0]==CMND)&&(UIB[1]==21))
	{
     short i;

  /*   for(i=0;i<128;i++)
     	{
          damp_[i]=i<<3;
          }

	Memo1->Lines->Add("Запрос страницы " + IntToStr(*((short*)&UIB[2])));
     out_adr_blok_to_page((char*)&damp_[ 0 ] );
     Sleep(100);
     out_adr_blok_to_page( (char*)&damp_[ 32 ]);
     Sleep(100);
     out_adr_blok_to_page( (char*)&damp_[ 64 ]);
     Sleep(100);
     out_adr_blok_to_page( (char*)&damp_[ 96 ]);   */



     //Memo1->Lines->Add("Запрос страницы " + IntToStr(*((short*)&UIB[2])));
     out_adr_blok_to_page( &damp[ (*((short*)&UIB[2]))*256 ] );
     Sleep(20);
     out_adr_blok_to_page( &damp[ ((*((short*)&UIB[2]))*256)+64 ]);
     Sleep(20);
     out_adr_blok_to_page( &damp[ ((*((short*)&UIB[2]))*256)+128 ]);
     Sleep(20);
     out_adr_blok_to_page( &damp[ ((*((short*)&UIB[2]))*256)+192 ]); 
     }

if((UIB[0]==CMND)&&(UIB[1]==11))
	{
     if(UIB[2]==1)
          {
     	//if(UIB[6]==0x0a)Memo1->Lines->Add("Поиск файла \"" + AnsiString(UIB[3]) + ".wav\"");
          //else if(UIB[7]==0x0a)Memo1->Lines->Add("Поиск файла \"" + AnsiString(UIB[3]) + AnsiString(UIB[4]) + ".wav\"");
          }
	}
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
   	rx_buffer[rx_wr_index]=data;
   	bRXIN=1;
   	if (++rx_wr_index == RX_BUFFER_SIZE) rx_wr_index=0;
   	if (++rx_counter == RX_BUFFER_SIZE)
      	{
      	rx_counter=0;
      	rx_buffer_overflow=1;
      	}
     }

modbusCnt=2;



if(rx_buffer_overflow)
	{
	rx_wr_index=0;
	rx_rd_index=0;
	rx_counter=0;
	rx_buffer_overflow=0;
	}

//if(rx_counter&&(rx_buffer[index_offset(rx_wr_index,-1)])==END)
//	{
/*
     temp=rx_buffer[index_offset(rx_wr_index,-3)];
    	if(temp<150)
    		{

    		if(control_check(index_offset(rx_wr_index,-1)))
    			{

    			rx_rd_index=index_offset(rx_wr_index,-3-temp);
    			for(i=0;i<(temp+3);i++)
				{
				UIB[i]=rx_buffer[index_offset(rx_rd_index,i)];
				}
			rx_rd_index=rx_wr_index;
			rx_counter=0;
			uart_in_an();

    			}

    		} */
    //	}

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
                uart_modbus_request();
                }
        }
if(b1Hz)
        {
        b1Hz=0;

        }

if(modbusCnt)
        {
        modbusCnt--;
        if(modbusCnt==0)
                {

                bmodbusIn=1;

                for(int i=0;i<rx_wr_index;i++)
                        {
			UIB[i]=rx_buffer[i];
			}
                rx_wr_index=0;
		rx_counter=0;
		uart_in_an();
                }
        }
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

        tempD= Edit1->Text.ToDouble();
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

        tempD= Edit2->Text.ToDouble();
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

        tempD= Edit3->Text.ToDouble();
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

        tempD= Edit4->Text.ToDouble();
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

        temp= Edit5->Text.ToInt();
        //temp= (int)tempD;//Edit1->Text.ToInt();

        //tempF=FloatToStr(tempD);

        //temp= (int)(((tempD)*10)+0.1);
        if(temp>9999)temp=9999;
        if(temp<0)temp=0;
        Label16->Caption= IntToStr(temp);
        Button9->SetFocus();
        temp1=0x23;


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

        temp= Edit6->Text.ToInt();
        //temp= (int)tempD;//Edit1->Text.ToInt();

        //tempF=FloatToStr(tempD);

        //temp= (int)(((tempD)*10)+0.1);
        if(temp>9999)temp=9999;
        if(temp<0)temp=0;
        Label16->Caption= IntToStr(temp);
        Button9->SetFocus();
        temp1=0x23;


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


