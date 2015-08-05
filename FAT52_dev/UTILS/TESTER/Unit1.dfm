object Form1: TForm1
  Left = 438
  Top = 121
  Width = 498
  Height = 534
  Caption = ' ИПС-15000-380/100В-160А'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label16: TLabel
    Left = 176
    Top = 464
    Width = 81
    Height = 13
    Caption = 'Label16'
  end
  object B1: TButton
    Left = 18
    Top = 64
    Width = 93
    Height = 25
    Caption = 'Открыть'
    TabOrder = 0
    OnClick = B1Click
  end
  object ComboBox1: TComboBox
    Left = 18
    Top = 26
    Width = 93
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
    Items.Strings = (
      'COM1'
      'COM2'
      'COM3'
      'COM4'
      'COM5'
      'COM6'
      'COM7'
      'COM8'
      'COM9'
      'COM10')
  end
  object Panel2: TPanel
    Left = 128
    Top = 72
    Width = 353
    Height = 57
    BorderStyle = bsSingle
    TabOrder = 2
    object Label2: TLabel
      Left = 8
      Top = 14
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Время паузы, сек. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit2: TEdit
      Left = 240
      Top = 12
      Width = 57
      Height = 32
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '000,0'
      OnKeyPress = Edit2KeyPress
    end
    object Button3: TButton
      Left = 296
      Top = 12
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 1
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 296
      Top = 28
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 2
      OnClick = Button4Click
    end
  end
  object Panel3: TPanel
    Left = 128
    Top = 128
    Width = 353
    Height = 57
    BorderStyle = bsSingle
    TabOrder = 3
    object Label3: TLabel
      Left = 8
      Top = 14
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Время разряда, сек. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit3: TEdit
      Left = 240
      Top = 12
      Width = 57
      Height = 32
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '000,0'
      OnKeyPress = Edit3KeyPress
    end
    object Button5: TButton
      Left = 296
      Top = 12
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 1
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 296
      Top = 28
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 2
      OnClick = Button6Click
    end
  end
  object Panel4: TPanel
    Left = 128
    Top = 184
    Width = 353
    Height = 57
    BorderStyle = bsSingle
    TabOrder = 4
    object Label4: TLabel
      Left = 8
      Top = 14
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Время паузы, сек. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit4: TEdit
      Left = 240
      Top = 12
      Width = 57
      Height = 32
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '000,0'
      OnKeyPress = Edit4KeyPress
    end
    object Button7: TButton
      Left = 296
      Top = 12
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 1
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 296
      Top = 28
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 2
      OnClick = Button8Click
    end
  end
  object Panel1: TPanel
    Left = 128
    Top = 16
    Width = 352
    Height = 57
    BorderStyle = bsSingle
    TabOrder = 5
    object Label1: TLabel
      Left = 8
      Top = 14
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Время заряда, сек. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 240
      Top = 12
      Width = 57
      Height = 32
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '000,0'
      OnKeyPress = Edit1KeyPress
    end
    object Button1: TButton
      Left = 296
      Top = 12
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 296
      Top = 28
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 2
      OnClick = Button2Click
    end
  end
  object Button9: TButton
    Left = 8
    Top = 440
    Width = 115
    Height = 49
    Caption = 'СТАРТ'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 128
    Top = 440
    Width = 115
    Height = 49
    Caption = 'ПАУЗА'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 248
    Top = 440
    Width = 115
    Height = 49
    Caption = 'СТОП'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 368
    Top = 440
    Width = 115
    Height = 49
    Caption = 'СБРОС'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
    OnClick = Button12Click
  end
  object Panel5: TPanel
    Left = -1
    Top = 240
    Width = 266
    Height = 89
    BorderStyle = bsSingle
    TabOrder = 10
    object Label5: TLabel
      Left = 8
      Top = 6
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Максимальное '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 8
      Top = 30
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'выходное'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 8
      Top = 54
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'напряжение, В. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit5: TEdit
      Left = 168
      Top = 28
      Width = 41
      Height = 32
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '000'
      OnKeyPress = Edit5KeyPress
    end
    object Button13: TButton
      Left = 208
      Top = 28
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 1
      OnClick = Button13Click
    end
    object Button14: TButton
      Left = 208
      Top = 44
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 2
      OnClick = Button14Click
    end
  end
  object Panel6: TPanel
    Left = 264
    Top = 240
    Width = 217
    Height = 89
    BorderStyle = bsSingle
    TabOrder = 11
    object Label8: TLabel
      Left = 8
      Top = 14
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Ток'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 8
      Top = 38
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'заряда, А. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit6: TEdit
      Left = 120
      Top = 28
      Width = 41
      Height = 32
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '000'
      OnKeyPress = Edit6KeyPress
    end
    object Button15: TButton
      Left = 160
      Top = 28
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 1
      OnClick = Button15Click
    end
    object Button16: TButton
      Left = 160
      Top = 44
      Width = 49
      Height = 16
      Caption = ' '
      TabOrder = 2
      OnClick = Button16Click
    end
  end
  object Panel7: TPanel
    Left = -1
    Top = 336
    Width = 242
    Height = 89
    BorderStyle = bsSingle
    TabOrder = 12
    object Label9: TLabel
      Left = 8
      Top = 6
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'Число'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label11: TLabel
      Left = 8
      Top = 30
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'пройденных'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label12: TLabel
      Left = 8
      Top = 54
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'циклов'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit7: TEdit
      Left = 168
      Top = 36
      Width = 62
      Height = 37
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '0000'
    end
  end
  object Panel8: TPanel
    Left = 239
    Top = 336
    Width = 242
    Height = 89
    BorderStyle = bsSingle
    TabOrder = 13
    object Label13: TLabel
      Left = 8
      Top = 6
      Width = 217
      Height = 32
      AutoSize = False
      Caption = 'Продолжительность'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label14: TLabel
      Left = 8
      Top = 30
      Width = 193
      Height = 32
      AutoSize = False
      Caption = 'испытания'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit8: TEdit
      Left = 128
      Top = 36
      Width = 105
      Height = 37
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '00:00:00'
    end
  end
  object ComPort1: TComPort
    BaudRate = br9600
    Port = 'COM1'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    OnRxChar = ComPort1RxChar
    Left = 16
    Top = 456
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
    Left = 48
    Top = 456
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '640'
    Options = [ofHideReadOnly, ofCreatePrompt, ofEnableSizing]
    Left = 84
    Top = 452
  end
  object SaveDialog1: TSaveDialog
    Options = [ofHideReadOnly, ofCreatePrompt, ofEnableSizing]
    Left = 128
    Top = 456
  end
end
