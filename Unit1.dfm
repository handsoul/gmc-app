object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'General Motor Controller'
  ClientHeight = 687
  ClientWidth = 966
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  DesignSize = (
    966
    687)
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = -4
    Top = -1
    Width = 973
    Height = 58
    Anchors = [akLeft, akRight]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuHighlight
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentBackground = False
    ParentFont = False
    TabOrder = 1
    object Label1: TLabel
      Left = 39
      Top = 10
      Width = 49
      Height = 14
      Caption = 'CAN'#35774#22791
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 159
      Top = 10
      Width = 28
      Height = 14
      Caption = #36890#36947
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 258
      Top = 10
      Width = 28
      Height = 14
      Caption = #36895#29575
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
    end
    object ComboxChannel: TComboBox
      Left = 132
      Top = 28
      Width = 89
      Height = 20
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #23435#20307
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentFont = False
      TabOrder = 0
    end
    object ComboxCanDevType: TComboBox
      Left = 24
      Top = 28
      Width = 89
      Height = 20
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #23435#20307
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentFont = False
      TabOrder = 1
    end
    object ComboxBitRate: TComboBox
      Left = 231
      Top = 30
      Width = 87
      Height = 20
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #23435#20307
      Font.Style = []
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ParentFont = False
      TabOrder = 2
    end
    object btnConnectCAN: TButton
      Left = 339
      Top = 7
      Width = 78
      Height = 47
      Caption = #36830#25509
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = btnConnectCANClick
    end
    object chkPeriodicGetInfo: TCheckBox
      Left = 632
      Top = 23
      Width = 76
      Height = 16
      Caption = #33258#21160#26597#35810
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 4
    end
  end
  object StBar_Main: TStatusBar
    Left = 0
    Top = 661
    Width = 966
    Height = 26
    Panels = <
      item
        Alignment = taCenter
        Width = 150
      end
      item
        Style = psOwnerDraw
        Width = 500
      end
      item
        Alignment = taCenter
        Width = 200
      end
      item
        Alignment = taCenter
        Text = '-*************-'
        Width = 150
      end>
    OnDrawPanel = StBar_MainDrawPanel
  end
  object PC_Main: TPageControl
    Left = 0
    Top = 55
    Width = 969
    Height = 607
    ActivePage = TBSH_NODES_DATA
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object TS_CellInfo: TTabSheet
      Caption = '  '#36816#34892#29366#24577'  '
      ImageIndex = 2
      ExplicitLeft = 5
      ExplicitTop = 21
      object grpDI: TGroupBox
        Left = 16
        Top = 24
        Width = 163
        Height = 551
        Caption = ' '#36890#29992#25968#23383#36755#20837
        Color = clBtnHighlight
        ParentBackground = False
        ParentColor = False
        TabOrder = 0
        object lg_Input: TLedGroup
          Left = 9
          Top = 16
          Width = 151
          Height = 532
          BevelOuter = bvNone
          Color = clHighlightText
          TabOrder = 0
          MarginTop = 3
          MarginDown = 3
          MarginLeft = 3
          MarginRight = 3
          LedDefaultShape = stRoundRect
          LedDefaultColor = clGray
          LedDefaultHeight = 25
          LedDefaultWidth = 25
          LedLayoutRatio = 50.000000000000000000
          LedNum = 8
          LedDirection = ldVertical
        end
      end
      object SG_RunInfo: TStringGrid
        Left = 400
        Top = 24
        Width = 545
        Height = 233
        ColCount = 3
        DefaultDrawing = False
        RowCount = 9
        ScrollBars = ssNone
        TabOrder = 1
        OnDrawCell = SG_RunInfoDrawCell
        ColWidths = (
          64
          64
          64)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
      object GroupBox2: TGroupBox
        Left = 196
        Top = 25
        Width = 173
        Height = 551
        Caption = #32477#23545#20540#32534#30721#22120
        Color = clBtnHighlight
        ParentBackground = False
        ParentColor = False
        TabOrder = 2
        object lg_AbsEncoder: TLedGroup
          Left = 16
          Top = 16
          Width = 137
          Height = 532
          BevelOuter = bvNone
          Color = clHighlightText
          TabOrder = 0
          MarginTop = 3
          MarginDown = 3
          MarginLeft = 3
          MarginRight = 3
          LedDefaultShape = stRoundRect
          LedDefaultColor = clGray
          LedDefaultHeight = 25
          LedDefaultWidth = 25
          LedLayoutRatio = 50.000000000000000000
          LedNum = 14
          LedDirection = ldVertical
        end
      end
      object GroupBox1: TGroupBox
        Left = 400
        Top = 364
        Width = 265
        Height = 212
        Caption = #30005#26426#25511#21046#22120#39044#30041#36755#20986
        TabOrder = 3
        object CheckBox1: TCheckBox
          Left = 20
          Top = 26
          Width = 49
          Height = 17
          Caption = 'SW11'
          TabOrder = 0
        end
        object CheckBox2: TCheckBox
          Left = 20
          Top = 78
          Width = 49
          Height = 17
          Caption = 'SW21'
          TabOrder = 1
        end
        object CheckBox3: TCheckBox
          Left = 20
          Top = 131
          Width = 49
          Height = 17
          Caption = 'SW31'
          TabOrder = 2
        end
        object CheckBox4: TCheckBox
          Left = 20
          Top = 184
          Width = 49
          Height = 17
          Caption = 'SW41'
          TabOrder = 3
        end
        object CheckBox5: TCheckBox
          Left = 84
          Top = 26
          Width = 49
          Height = 17
          Caption = 'SW51'
          TabOrder = 4
        end
        object CheckBox6: TCheckBox
          Left = 84
          Top = 78
          Width = 49
          Height = 17
          Caption = 'SW61'
          TabOrder = 5
        end
        object CheckBox7: TCheckBox
          Left = 84
          Top = 131
          Width = 49
          Height = 17
          Caption = 'SW71'
          TabOrder = 6
        end
        object CheckBox8: TCheckBox
          Left = 84
          Top = 184
          Width = 49
          Height = 17
          Caption = 'SW81'
          TabOrder = 7
        end
        object Button3: TButton
          Left = 175
          Top = 88
          Width = 58
          Height = 56
          Caption = #36755#20986
          TabOrder = 8
        end
      end
      object GroupBox3: TGroupBox
        Left = 400
        Top = 263
        Width = 545
        Height = 94
        Caption = #36890#29992#27169#25311#36755#20986
        TabOrder = 4
        object Label9: TLabel
          Left = 10
          Top = 29
          Width = 30
          Height = 13
          Caption = #36890#36947'0'
        end
        object Label10: TLabel
          Left = 10
          Top = 61
          Width = 30
          Height = 13
          Caption = #36890#36947'1'
        end
        object Label11: TLabel
          Left = 274
          Top = 29
          Width = 30
          Height = 13
          Caption = #36890#36947'2'
        end
        object Label12: TLabel
          Left = 274
          Top = 60
          Width = 30
          Height = 13
          Caption = #36890#36947'4'
        end
        object ED_AO0: TEdit
          Left = 70
          Top = 24
          Width = 97
          Height = 21
          TabOrder = 0
        end
        object ED_AO1: TEdit
          Left = 70
          Top = 59
          Width = 97
          Height = 21
          TabOrder = 1
        end
        object ED_AO2: TEdit
          Left = 326
          Top = 24
          Width = 97
          Height = 21
          TabOrder = 2
        end
        object Button2: TButton
          Left = 464
          Top = 24
          Width = 58
          Height = 56
          Caption = #36755#20986
          TabOrder = 3
        end
        object ED_AO3: TEdit
          Left = 326
          Top = 59
          Width = 97
          Height = 21
          TabOrder = 4
        end
      end
      object GroupBox4: TGroupBox
        Left = 671
        Top = 364
        Width = 274
        Height = 212
        Caption = #36890#29992#25968#23383#36755#20986
        TabOrder = 5
        object CheckBox9: TCheckBox
          Left = 20
          Top = 26
          Width = 69
          Height = 17
          Caption = 'OUTPUT0'
          TabOrder = 0
        end
        object CheckBox10: TCheckBox
          Left = 20
          Top = 76
          Width = 69
          Height = 18
          Caption = 'OUTPUT1'
          TabOrder = 1
        end
        object CheckBox11: TCheckBox
          Left = 20
          Top = 126
          Width = 61
          Height = 18
          Caption = 'OUTPUT2'
          TabOrder = 2
        end
        object CheckBox12: TCheckBox
          Left = 20
          Top = 177
          Width = 61
          Height = 18
          Caption = 'OUTPUT3'
          TabOrder = 3
        end
        object CheckBox13: TCheckBox
          Left = 116
          Top = 26
          Width = 61
          Height = 18
          Caption = 'OUTPUT4'
          TabOrder = 4
        end
        object CheckBox14: TCheckBox
          Left = 116
          Top = 76
          Width = 61
          Height = 18
          Caption = 'OUTPUT5'
          TabOrder = 5
        end
        object CheckBox15: TCheckBox
          Left = 116
          Top = 126
          Width = 61
          Height = 18
          Caption = 'OUTPUT6'
          TabOrder = 6
        end
        object CheckBox16: TCheckBox
          Left = 116
          Top = 176
          Width = 61
          Height = 18
          Caption = 'OUTPUT7'
          TabOrder = 7
        end
        object Button4: TButton
          Left = 193
          Top = 88
          Width = 58
          Height = 56
          Caption = #36755#20986
          TabOrder = 8
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = '   '#25509#21475#37197#32622'  '
      ImageIndex = 2
      object Label22: TLabel
        Left = 77
        Top = 102
        Width = 96
        Height = 13
        Caption = #25903#25345#30340#32534#30721#22120#31867#22411
      end
      object Label14: TLabel
        Left = 526
        Top = 102
        Width = 96
        Height = 13
        Caption = #25903#25345#30340#39537#21160#22120#31867#22411
      end
      object Label23: TLabel
        Left = 77
        Top = 49
        Width = 72
        Height = 13
        Caption = #21152#36895#26354#32447#25991#20214
      end
      object Label26: TLabel
        Left = 77
        Top = 133
        Width = 60
        Height = 13
        Caption = #39537#21160#22120#21442#25968
      end
      object Label27: TLabel
        Left = 525
        Top = 133
        Width = 60
        Height = 13
        Caption = #32534#30721#22120#21442#25968
      end
      object ComboBox1: TComboBox
        Left = 179
        Top = 100
        Width = 89
        Height = 20
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentFont = False
        TabOrder = 0
      end
      object ComboBox2: TComboBox
        Left = 628
        Top = 100
        Width = 89
        Height = 20
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentFont = False
        TabOrder = 1
      end
      object Button1: TButton
        Left = 318
        Top = 44
        Width = 75
        Height = 25
        Caption = #21152#36733
        TabOrder = 2
      end
      object Edit1: TEdit
        Left = 179
        Top = 46
        Width = 123
        Height = 21
        TabOrder = 3
      end
      object StringGrid1: TStringGrid
        Left = 77
        Top = 152
        Width = 316
        Height = 345
        ColCount = 3
        DefaultDrawing = False
        RowCount = 8
        ScrollBars = ssNone
        TabOrder = 4
        OnDrawCell = SG_RunInfoDrawCell
        ColWidths = (
          64
          64
          64)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24)
      end
      object StringGrid2: TStringGrid
        Left = 525
        Top = 152
        Width = 316
        Height = 345
        ColCount = 3
        DefaultDrawing = False
        RowCount = 8
        ScrollBars = ssNone
        TabOrder = 5
        OnDrawCell = SG_RunInfoDrawCell
        ColWidths = (
          64
          64
          64)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object TabSheet4: TTabSheet
      Caption = '  '#36164#28304#21629#21517#31354#38388
      ImageIndex = 6
    end
    object TS_CANMsg: TTabSheet
      Caption = '  '#36890#20449#35760#24405' '
      ImageIndex = 1
      object Label25: TLabel
        Left = 5
        Top = 14
        Width = 66
        Height = 12
        Caption = #25253#25991'ID(HEX)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label24: TLabel
        Left = 5
        Top = 52
        Width = 36
        Height = 12
        Caption = #24103#31867#22411
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label31: TLabel
        Left = 7
        Top = 85
        Width = 36
        Height = 12
        Caption = #25968#25454#22495
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label7: TLabel
        Left = 3
        Top = 197
        Width = 86
        Height = 13
        Caption = #36807#28388'ID'#21015#34920'(Hex)'
      end
      object Label4: TLabel
        Left = 743
        Top = 6
        Width = 84
        Height = 13
        Caption = 'CAN '#25509#25910#35745#25968#22120
      end
      object Label5: TLabel
        Left = 602
        Top = 6
        Width = 84
        Height = 13
        Caption = 'CAN '#21457#36865#35745#25968#22120
      end
      object chkboxScrollEnalble: TCheckBox
        Left = 422
        Top = 2
        Width = 71
        Height = 17
        Caption = #25968#25454#21047#26032
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object chkBoxSaveCommData: TCheckBox
        Left = 499
        Top = 2
        Width = 97
        Height = 17
        Caption = #20445#23384#25968#25454
        TabOrder = 1
      end
      object Edit3: TEdit
        Left = 85
        Top = 13
        Width = 120
        Height = 20
        BevelEdges = []
        BevelInner = bvNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentFont = False
        TabOrder = 2
        Text = '123'
      end
      object cboxFrameType: TComboBox
        Left = 85
        Top = 48
        Width = 120
        Height = 20
        Style = csDropDownList
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentCtl3D = False
        ParentFont = False
        TabOrder = 3
      end
      object Edit2: TEdit
        Left = 85
        Top = 80
        Width = 149
        Height = 20
        BevelEdges = []
        BevelInner = bvNone
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentFont = False
        TabOrder = 4
        Text = '11 22 33 44 55 66 77 88'
      end
      object btnSendMsg: TButton
        Left = 240
        Top = 37
        Width = 36
        Height = 63
        Caption = #21457#36865
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        OnClick = btnSendMsgClick
      end
      object ListView1: TListView
        Left = 282
        Top = 39
        Width = 667
        Height = 508
        Columns = <
          item
            Caption = '   '#24207#21495
            MaxWidth = 70
            MinWidth = 70
            Width = 70
          end
          item
            Alignment = taCenter
            Caption = #26041#21521
            MaxWidth = 50
            MinWidth = 50
          end
          item
            Alignment = taCenter
            Caption = #26102#38388
            MaxWidth = 100
            MinWidth = 100
            Width = 100
          end
          item
            Alignment = taCenter
            Caption = #28040#24687'ID'
            MaxWidth = 80
            MinWidth = 80
            Width = 80
          end
          item
            Alignment = taCenter
            Caption = #24103#31867#22411
            MaxWidth = 60
            MinWidth = 60
            Width = 60
          end
          item
            Caption = '                     '#25968#25454#22495
            MaxWidth = 280
            MinWidth = 280
            Width = 280
          end>
        DoubleBuffered = True
        Font.Charset = GB2312_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #26032#23435#20307
        Font.Style = []
        ReadOnly = True
        ParentDoubleBuffered = False
        ParentFont = False
        PopupMenu = POM_ClearMsg
        TabOrder = 6
        ViewStyle = vsReport
      end
      object RadioGroup1: TRadioGroup
        Left = 3
        Top = 142
        Width = 273
        Height = 49
        Caption = #36807#28388#35268#21017
        Columns = 3
        ItemIndex = 0
        Items.Strings = (
          #20840#37096#25509#25910
          #24573#30053'ID'
          #21305#37197'ID')
        TabOrder = 7
        OnClick = RadioGroup1Click
      end
      object memoIDList: TMemo
        Left = 9
        Top = 216
        Width = 267
        Height = 328
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 8
        OnKeyPress = memoIDListKeyPress
        OnKeyUp = memoIDListKeyUp
      end
      object chkFillData: TCheckBox
        Left = 211
        Top = 14
        Width = 81
        Height = 17
        Caption = #25968#25454#22495#34917#20840
        TabOrder = 9
      end
    end
    object TabSheet2: TTabSheet
      Caption = '   J'#20195#30721#36816#34892'   '
      ImageIndex = 3
      object label6: TLabel
        Left = 22
        Top = 161
        Width = 51
        Height = 13
        Caption = ' '#35299#26512#32467#26524
      end
      object Label8: TLabel
        Left = 22
        Top = 8
        Width = 63
        Height = 13
        Caption = ' '#21629#20196#36755#20837#26694
      end
      object mm_JcodeInput: TMemo
        Left = 22
        Top = 27
        Width = 850
        Height = 92
        TabOrder = 0
      end
      object mm_JcodeParser: TMemo
        Left = 22
        Top = 180
        Width = 850
        Height = 374
        TabOrder = 1
      end
      object btnParseInput: TButton
        Left = 797
        Top = 131
        Width = 75
        Height = 25
        Caption = #35299#26512
        TabOrder = 2
        OnClick = btnParseInputClick
      end
    end
    object TS_MotorCtrl: TTabSheet
      Caption = '  '#30005#26426#25511#21046#35843#35797'  '
      ImageIndex = 4
      object Label28: TLabel
        Left = 108
        Top = 61
        Width = 28
        Height = 14
        Caption = #26041#21521
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object Label29: TLabel
        Left = 108
        Top = 101
        Width = 56
        Height = 14
        Caption = #36895#24230#32423#21035
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object CB_MotorDir: TComboBox
        Left = 183
        Top = 60
        Width = 89
        Height = 20
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentFont = False
        TabOrder = 0
      end
      object CB_MotorSpeed: TComboBox
        Left = 183
        Top = 100
        Width = 89
        Height = 20
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = #23435#20307
        Font.Style = []
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ParentFont = False
        TabOrder = 1
      end
      object btnExecuteCmd: TButton
        Left = 183
        Top = 168
        Width = 89
        Height = 25
        Caption = #25191#34892
        TabOrder = 2
        OnClick = btnExecuteCmdClick
      end
    end
    object TabSheet3: TTabSheet
      Caption = #26354#32447#24037#20855
      ImageIndex = 5
    end
    object TBSH_NODES_DATA: TTabSheet
      Caption = '  gmc'#32593#32476'  '
      ImageIndex = 7
      object Label13: TLabel
        Left = 351
        Top = 16
        Width = 174
        Height = 19
        Caption = 'CAN'#32593#32476'Gmc'#33410#28857#20449#24687
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
      end
      object SG_GmcCanNetInfo: TStringGrid
        Left = 124
        Top = 41
        Width = 713
        Height = 504
        ColCount = 6
        RowCount = 20
        TabOrder = 0
      end
    end
  end
  object CommTimer: TTimer
    Interval = 20
    OnTimer = CommTimerTimer
    Left = 1088
    Top = 24
  end
  object POM_ClearMsg: TPopupMenu
    Left = 808
    Top = 8
    object N1: TMenuItem
      Caption = #28165#31354
      OnClick = N1Click
    end
  end
end
