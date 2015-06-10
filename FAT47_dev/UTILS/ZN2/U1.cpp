//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U1.h"

unsigned char simbol[20]={0xff,0x55,0x00,0xAA,0x33,0x00,0x00,0x00};
unsigned char simbol_vert[6]={0,0,0,0,0,0};
unsigned char simbol_all[5120];
unsigned char bukva;
char indikator;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
qwads_drow();
ComboBox1->ItemIndex=0;






}

//---------------------------------------------------------------------------
void __fastcall TForm1::vert_create(void)
{
char i,j;
for(i=0;i<8;i++)
	{
     for(j=0;j<6;j++)
     	{
          if(simbol[i]&(1<<j))
          	{
               simbol_vert[5-j]|=(1<<i);
               }
          else simbol_vert[5-j]&=(~(1<<i));
          }

     }
/*i=0;
j=0;
        if(simbol[i]&(1<<j))
          	{
               simbol_vert[5-j]|=(1<<i);
               }
          else simbol_vert[5-j]&=(~(1<<i)); */

}

//---------------------------------------------------------------------------
void __fastcall TForm1::horiz_create(void)
{
char i,j;
for(i=0;i<6;i++)
	{
     for(j=0;j<8;j++)
     	{
          if(simbol_vert[i]&(1<<j))
          	{
               simbol[j]|=(1<<(5-i));
               }
          else simbol[j]&=(~(1<<(5-i)));
          }

     }
/*i=0;
j=0;
        if(simbol[i]&(1<<j))
          	{
               simbol_vert[5-j]|=(1<<i);
               }
          else simbol_vert[5-j]&=(~(1<<i)); */

}
//---------------------------------------------------------------------------
void __fastcall TForm1::string_create(void)
{
int i;
int number;
AnsiString line,sub_line;
line=Memo1->Lines->Text;
if(!line.IsEmpty())
	{
     do line.Delete(1,1);
     while ((*(line.c_str())!='x')&&(!line.IsEmpty()));
     Memo1->Lines->Clear();
     Memo1->Lines->Add(line);
     }
     i=0;
lbl_0001:
     if(!line.IsEmpty()) sub_line=line.SubString(1,3);
	simbol_all[i]=sub_line.ToInt();
     line.Delete(1,5);
     if((*(line.c_str())!='}')&&(i<2048)) goto lbl_0001;

}

//---------------------------------------------------------------------------
void __fastcall TForm1::array_create(void)
{
int i;
int number;
unsigned char temp;

AnsiString line,sub_line;
line=Memo1->Lines->Text;
if(!line.IsEmpty())
	{
     do line.Delete(1,1);
     while ((*(line.c_str())!='x')&&(!line.IsEmpty()));
     Memo1->Lines->Clear();
     Memo1->Lines->Add(line);
     }
     i=0;
lbl_0001:
     if(!line.IsEmpty()) sub_line=line.SubString(1,3);
 //    if(sub_line!=)
     try
     {
     temp=sub_line.ToInt();
     }
     catch ( EConvertError& )
     {
     goto label_0001_out;
     }
	temp=sub_line.ToInt();
     if(temp)
          {
          temp=temp;
          }
     simbol_all[i]=temp;
     i++;
     line.Delete(1,5);
     if((*(line.c_str())!='}')&&(i<2048)) goto lbl_0001;
label_0001_out:
}

//---------------------------------------------------------------------------
void __fastcall TForm1::line_text_create(void)
{
int i,ii;
AnsiString line_;
Memo1->Lines->Clear();
line_=" ";//"flash char caracter[";//1536]={";
if(indikator==0)
     {
     //line_+=/*"flash char caracter[*/"flash char caracter[5120]={";

     for(i=0;i<256;i++)
     	{
        line_+=bukva;
        line_+='\n';
        for(ii=1;ii<=10;ii++)
 	     {
             line_+="0x";
  	     line_+=IntToHex(simbol_all[(i*20)+ii],2);
             line_+=", ";
             }
        line_+='\n';
        for(ii=11;ii<=20;ii++)
 	     {
             line_+="0x";
  	     line_+=IntToHex(simbol_all[(i*20)+ii],2);
             line_+=", ";
             }
        line_+='\n';
        line_+='\n';
        }
     line_+="};";     
     }
Memo1->Lines->Add(line_);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::qwads_drow(void)
{
short iii;
TImage *ptr_ptr[160]={ 	Image1,Image2,Image3,Image4,Image5,Image6,Image7,Image8,Image9,Image10,
			Image11,Image12,Image13,Image14,Image15,Image16,Image17,Image18,Image19,Image20,
                        Image21,Image22,Image23,Image24,Image25,Image26,Image27,Image28,Image29,Image30,
                        Image31,Image32,Image33,Image34,Image35,Image36,Image37,Image38,Image39,Image40,
                        Image41,Image42,Image43,Image44,Image45,Image46,Image47,Image48,Image49,Image50,
                        Image51,Image52,Image53,Image54,Image55,Image56,Image57,Image58,Image59,Image60,
                        Image61,Image62,Image63,Image64,Image65,Image66,Image67,Image68,Image69,Image70,
                        Image71,Image72,Image73,Image74,Image75,Image76,Image77,Image78,Image79,Image80,
                        Image81,Image82,Image83,Image84,Image85,Image86,Image87,Image88,Image89,Image90,
                        Image91,Image92,Image93,Image94,Image95,Image96,Image97,Image98,Image99,Image100,
                        Image101,Image102,Image103,Image104,Image105,Image106,Image107,Image108,Image109,Image110,
                        Image111,Image112,Image113,Image114,Image115,Image116,Image117,Image118,Image119,Image120,
                        Image121,Image122,Image123,Image124,Image125,Image126,Image127,Image128,Image129,Image130,
                        Image131,Image132,Image133,Image134,Image135,Image136,Image137,Image138,Image139,Image140,
                        Image141,Image142,Image143,Image144,Image145,Image146,Image147,Image148,Image149,Image150,
                        Image151,Image152,Image153,Image154,Image155,Image156,Image157,Image158,Image159,Image160};
//ptr_ptr=Image1;

for(iii=0;iii<160;iii++) {
if(simbol[iii/8]&(0x01<<(iii%8)))ptr_ptr[iii]->Picture->LoadFromFile("Black.bmp");
else ptr_ptr[iii]->Picture->LoadFromFile("White.bmp");
}
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
AnsiString temp_a;
unsigned char temp;
temp_a=(Edit1->Text);
//temp=*((char*)temp_a);
temp=*(temp_a.c_str());

//temp_a.c_str();

/*
char a='A';
unsigned char temp;
ComboBox1->Items->Add(IntToStr(a));
//temp_a=(Edit1->Text);
//temp=*((char*)temp_a);
//Label1->Caption=(temp); */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
short num_im;
TImage *ptr_ptr[160]={ 	Image1,Image2,Image3,Image4,Image5,Image6,Image7,Image8,Image9,Image10,
			Image11,Image12,Image13,Image14,Image15,Image16,Image17,Image18,Image19,Image20,
                        Image21,Image22,Image23,Image24,Image25,Image26,Image27,Image28,Image29,Image30,
                        Image31,Image32,Image33,Image34,Image35,Image36,Image37,Image38,Image39,Image40,
                        Image41,Image42,Image43,Image44,Image45,Image46,Image47,Image48,Image49,Image50,
                        Image51,Image52,Image53,Image54,Image55,Image56,Image57,Image58,Image59,Image60,
                        Image61,Image62,Image63,Image64,Image65,Image66,Image67,Image68,Image69,Image70,
                        Image71,Image72,Image73,Image74,Image75,Image76,Image77,Image78,Image79,Image80,
                        Image81,Image82,Image83,Image84,Image85,Image86,Image87,Image88,Image89,Image90,
                        Image91,Image92,Image93,Image94,Image95,Image96,Image97,Image98,Image99,Image100,
                        Image101,Image102,Image103,Image104,Image105,Image106,Image107,Image108,Image109,Image110,
                        Image111,Image112,Image113,Image114,Image115,Image116,Image117,Image118,Image119,Image120,
                        Image121,Image122,Image123,Image124,Image125,Image126,Image127,Image128,Image129,Image130,
                        Image131,Image132,Image133,Image134,Image135,Image136,Image137,Image138,Image139,Image140,
                        Image141,Image142,Image143,Image144,Image145,Image146,Image147,Image148,Image149,Image150,
                        Image151,Image152,Image153,Image154,Image155,Image156,Image157,Image158,Image159,Image160};


 for(int i =0; i<160; i++)
 	{
        if(Sender==ptr_ptr[i])
        	{
                num_im=i;
                break;
                }
        }

simbol[num_im/8]^=0x01<<(num_im%8);


vert_create();
Label2->Caption=IntToHex(simbol[0],2)+" "+
			IntToHex(simbol[1],2)+" "+
               IntToHex(simbol[2],2)+" "+
               IntToHex(simbol[3],2)+" "+
               IntToHex(simbol[4],2)+" "+
               IntToHex(simbol[5],2)+" "+
               IntToHex(simbol[6],2)+" "+
               IntToHex(simbol[7],2);

Label1->Caption=IntToHex(simbol_vert[0],2)+" "+
			IntToHex(simbol_vert[1],2)+" "+
               IntToHex(simbol_vert[2],2)+" "+
               IntToHex(simbol_vert[3],2)+" "+
               IntToHex(simbol_vert[4],2)+" "+
               IntToHex(simbol_vert[5],2)+" "+
               IntToHex(simbol_vert[6],2)+" "+
               IntToHex(simbol_vert[7],2);
TForm1::qwads_drow();
//TForm1::line_text_create();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
TForm1::array_create();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Edit1Change(TObject *Sender)
{

AnsiString temp_a;
unsigned char temp;
if(Edit1->Modified)
{
temp_a=(Edit1->Text);
//temp=*((char*)temp_a);
bukva=*(temp_a.c_str());
Edit2->Text=bukva;
Edit3->Text=IntToHex(bukva,2);
Edit1->SelectAll();

if(indikator==0)
     {
     int ptr;
     ptr=((int)bukva)*6;
     simbol_vert[0]=simbol_all[ptr];
     ptr++;
     simbol_vert[1]=simbol_all[ptr];
     ptr++;
     simbol_vert[2]=simbol_all[ptr];
     ptr++;
     simbol_vert[3]=simbol_all[ptr];
     ptr++;
     simbol_vert[4]=simbol_all[ptr];
     ptr++;
     simbol_vert[5]=simbol_all[ptr];
     ptr++;
     simbol_vert[6]=simbol_all[ptr];
     ptr++;
     simbol_vert[7]=simbol_all[ptr];
     ptr++;

     horiz_create();
     qwads_drow();
     }
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
indikator=(char)(ComboBox1->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
if(indikator==0)
     {
     memcpy(&simbol_all[bukva*20],simbol,20);
 /*    unsigned ptr;
     ptr=((unsigned)bukva)*6;
     simbol_all[ptr]=simbol_vert[0];
     ptr++;
     simbol_all[ptr]=simbol_vert[1];
     ptr++;
     simbol_all[ptr]=simbol_vert[2];
     ptr++;
     simbol_all[ptr]=simbol_vert[3];
     ptr++;
     simbol_all[ptr]=simbol_vert[4];
     ptr++;
     simbol_all[ptr]=simbol_vert[5];
     ptr++; */
     }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
line_text_create();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
Label3->Caption=IntToStr(indikator);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
AnsiString temp_a;
 char temp;
if(Edit2->Modified)
{
temp_a=(Edit2->Text);

try
     {
     temp=temp_a.ToInt();
     }
catch ( EConvertError& )
     {
     }

bukva=temp;
Edit1->Text=bukva;
Edit3->Text=IntToHex(bukva,2);


if(indikator==0)
     {
     int ptr;
     ptr=((int)bukva)*6;
     simbol_vert[0]=simbol_all[ptr];
     ptr++;
     simbol_vert[1]=simbol_all[ptr];
     ptr++;
     simbol_vert[2]=simbol_all[ptr];
     ptr++;
     simbol_vert[3]=simbol_all[ptr];
     ptr++;
     simbol_vert[4]=simbol_all[ptr];
     ptr++;
     simbol_vert[5]=simbol_all[ptr];
     ptr++;
     simbol_vert[6]=simbol_all[ptr];
     ptr++;
     simbol_vert[7]=simbol_all[ptr];
     ptr++;

     horiz_create();
     qwads_drow();
     }
 }
}
//---------------------------------------------------------------------------

