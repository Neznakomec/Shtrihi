object SettingWindow: TSettingWindow
  Left = 503
  Top = 174
  Width = 249
  Height = 249
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 112
    Width = 51
    Height = 16
    Caption = #1090#1077#1082#1089#1090#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object DeskewBox: TCheckBox
    Left = 16
    Top = 24
    Width = 185
    Height = 41
    Caption = #1048#1089#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1085#1072#1082#1083#1086#1085#1072
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    State = cbChecked
    TabOrder = 0
  end
  object OrientBox: TCheckBox
    Left = 16
    Top = 72
    Width = 209
    Height = 41
    BiDiMode = bdLeftToRight
    Caption = #1054#1087#1088#1077#1076#1077#1083#1103#1090#1100' '#1086#1088#1080#1077#1085#1090#1072#1094#1080#1102
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 1
  end
  object okButton: TButton
    Left = 80
    Top = 168
    Width = 75
    Height = 25
    Caption = #1054#1050
    TabOrder = 2
    OnClick = okButtonClick
  end
end
