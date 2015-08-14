object Form1: TForm1
  Left = 438
  Top = 121
  Width = 512
  Height = 534
  Caption = ' ÈÏÑ-15000-380/100Â-160À'
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
    Width = 38
    Height = 13
    Caption = 'Label16'
  end
  object Label1: TLabel
    Left = 176
    Top = 32
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 176
    Top = 56
    Width = 32
    Height = 13
    Caption = 'Label2'
  end
  object B1: TButton
    Left = 18
    Top = 64
    Width = 93
    Height = 25
    Caption = 'Îòêðûòü'
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
  object Button9: TButton
    Left = 8
    Top = 440
    Width = 115
    Height = 49
    Caption = 'ÑÒÀÐÒ'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    Visible = False
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 128
    Top = 440
    Width = 115
    Height = 49
    Caption = 'ÏÀÓÇÀ'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Visible = False
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 248
    Top = 440
    Width = 115
    Height = 49
    Caption = 'ÑÒÎÏ'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Visible = False
    OnClick = Button11Click
  end
  object Button12: TButton
    Left = 368
    Top = 440
    Width = 115
    Height = 49
    Caption = 'ÑÁÐÎÑ'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    Visible = False
    OnClick = Button12Click
  end
  object CheckBox1: TCheckBox
    Left = 20
    Top = 104
    Width = 97
    Height = 17
    Caption = 'Á1on'
    TabOrder = 6
  end
  object CheckBox2: TCheckBox
    Left = 20
    Top = 128
    Width = 97
    Height = 17
    Caption = 'Á2on'
    TabOrder = 7
  end
  object CheckBox3: TCheckBox
    Left = 20
    Top = 152
    Width = 97
    Height = 17
    Caption = 'Á3on'
    TabOrder = 8
  end
  object CheckBox4: TCheckBox
    Left = 20
    Top = 176
    Width = 97
    Height = 17
    Caption = 'Á4on'
    TabOrder = 9
  end
  object CheckBox5: TCheckBox
    Left = 20
    Top = 200
    Width = 97
    Height = 17
    Caption = 'Á5on'
    TabOrder = 10
  end
  object CheckBox6: TCheckBox
    Left = 20
    Top = 224
    Width = 97
    Height = 17
    Caption = 'Á6on'
    TabOrder = 11
  end
  object CheckBox7: TCheckBox
    Left = 20
    Top = 248
    Width = 97
    Height = 17
    Caption = 'Á7on'
    TabOrder = 12
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
