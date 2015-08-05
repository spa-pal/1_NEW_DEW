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
        TPanel *Panel2;
        TLabel *Label2;
        TEdit *Edit2;
        TButton *Button3;
        TButton *Button4;
        TPanel *Panel3;
        TLabel *Label3;
        TEdit *Edit3;
        TButton *Button5;
        TButton *Button6;
        TPanel *Panel4;
        TLabel *Label4;
        TEdit *Edit4;
        TButton *Button7;
        TButton *Button8;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button9;
        TButton *Button10;
        TButton *Button11;
        TButton *Button12;
        TPanel *Panel5;
        TLabel *Label5;
        TEdit *Edit5;
        TButton *Button13;
        TButton *Button14;
        TLabel *Label6;
        TLabel *Label7;
        TPanel *Panel6;
        TLabel *Label8;
        TLabel *Label10;
        TEdit *Edit6;
        TButton *Button15;
        TButton *Button16;
        TPanel *Panel7;
        TLabel *Label9;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *Edit7;
        TPanel *Panel8;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *Edit8;
        TLabel *Label16;
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
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
