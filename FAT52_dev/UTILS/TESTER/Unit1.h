//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CPort.hpp"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>


//#define BAT1ISON
//#define BAT2ISON
#define BAT3ISON
//#define BAT4ISON
#define BAT5ISON
#define BAT6ISON
#define BAT7ISON


typedef enum {rsOFF,rsGETSETTED}enum_requestStatus;
extern enum_requestStatus requestStatus;
extern char modbusCnt;
extern BOOL bmodbusIn;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *B1;
        TComboBox *ComboBox1;
        TComPort *ComPort1;
        TTimer *Timer1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TButton *Button12;
        TLabel *Label16;
	TLabel *Label1;
	TLabel *Label2;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox7;
	void __fastcall B1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall ComPort1RxChar(TObject *Sender, int Count);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
        void __fastcall Button19Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall Button17Click(TObject *Sender);
        void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit3KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit4KeyPress(TObject *Sender, char &Key);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Button15Click(TObject *Sender);
        void __fastcall Edit5KeyPress(TObject *Sender, char &Key);
        void __fastcall Edit6KeyPress(TObject *Sender, char &Key);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
	void __fastcall TForm1::uart_out_out(unsigned short len, char data0, char data1, char data2, char data3, char data4, char data5, char data6, char data7);
	void __fastcall TForm1::uart_in_an(void);
     void __fastcall TForm1::out_adr_blok_to_page(char* ptr);
     void __fastcall TForm1::uart_modbus_request(void);
     void __fastcall TForm1::ind_hndl(void);
     unsigned short __fastcall TForm1::CRC16_2(unsigned char* buf, short len);
     void __fastcall TForm1::uart1_out_adr(char* ptr, int len);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
