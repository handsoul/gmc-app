//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Shape1"
#pragma link "LedGroupMain"
#pragma resource "*.dfm"


#include "USBCAN2.h"
#include "ValueCan3.h"

//ListView��ʾ�������.
#define MAX_LISTVIEW_ITEM_COUNT 20000

//LED��ɫ����
#define COLOR_ON (TColor)RGB(90, 220, 90)
#define COLOR_OFF clBtnShadow
#define COLOR_ALARM clYellow
#define COLOR_PROTECTION clRed

//��Ϣ��ʾ�˲�ģʽѡ��.
#define FILTER_MODE_NORMAL 0
#define FILTER_MODE_IGNORE 1
#define FILTER_MODE_ACK    2

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    //StatusBar��ɫ�����õı���.
    StPanelColor = clBtnFace;
    //CAN�ӿڱ�����ʼ��.
    pCanDev = NULL;
}


// ������.
static vector< AnsiString> vJcodeStrings;
extern "C" void AddToStringList(const char * buf)
{
    AnsiString s(buf);
    vJcodeStrings.push_back(s);
}

static void StringGridAutoSize(TStringGrid & sg)
{
    sg.DefaultColWidth = (sg.Width - 3)/sg.ColCount;
    sg.Width =  3  + (sg.DefaultColWidth +1)* sg.ColCount;
    sg.DefaultRowHeight = (sg.Height -3) / sg.RowCount;
    sg.Height = 3 + (sg.DefaultRowHeight+1)* sg.RowCount;
}

bool isValidHexChar(char Key)
{
    return (Key >= '0' && Key <= '9')
           || (Key >= 'a' && Key <= 'f')
           || (Key >= 'A' && Key <= 'F');
}

char CharToHex(char Key)
{
    char c = (Key >= '0' && Key <= '9')? (Key-'0'):
        (Key >= 'a' && Key <= 'f')? (Key-'a' + 0x0A):
        (Key >= 'A' && Key <= 'F')? (Key-'A' + 0x0A):0xFF;
    return c;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::ShowInfo(AnsiString s, LogPri eLogPri)
{
#define WARN_COLOR clYellow
#define MSG_COLRO   clBtnFace

    if(eLogPri == Msg_WarningMsg)
    {
        StPanelColor =  clBtnShadow;
        s = "        ����:  " + s;
    }
    else if(eLogPri == Msg_ErrorMsg)
    {
        StPanelColor =  clYellow;
        s = "        ����:  " + s;
    }
    else if (eLogPri == Msg_Special) {
        StPanelColor =  COLOR_ON;
        s = "        ��ʾ:  " + s;
    }
    else
    {
        StPanelColor =  MSG_COLRO;
        s = "        " + s;
    }

    StBar_Main->Panels->Items[1]->Text = s;
}

bool TForm1::IsIDPrintable(int id)
{
    if(FilterMode == FILTER_MODE_IGNORE )
    {
        return (CanIDFilterSet.count(id)== 0);
    }
    else if(FilterMode == FILTER_MODE_ACK)
    {
        return (CanIDFilterSet.count(id)> 0);
    }
    else  //δ����ģʽ,ȫ����ʾ.
    {
        return true;
    }
}

void __fastcall TForm1::ShowCanMsg(const CanMsgST & msg,int dir)
{
    AnsiString s ;

    if(!chkboxScrollEnalble->Checked)
    {
        return;
    }

	TListItem *pItem ;

    pItem = ListView1->Items->Add();//ͨ��1.
    pItem->Caption = "   " + IntToStr((int)++ListCnt1);

    pItem->SubItems->Add((dir == 0)?"����":"����");

    GetMsgTimeStr(msg, s);
    pItem->SubItems->Add(s);//ʱ����

    pItem->SubItems->Add("0x" + IntToHex(msg.m_iCANID,8));
    pItem->SubItems->Add((msg.m_ExtFlag == 0)?"��׼֡":"��չ֡");
    s = "   ";
    for(int i = 0 ;i < msg.m_ucLength;i++)
    {
        s += "  " + IntToHex(msg.m_aucData[i],2);
    }
    //ListView1-> Items-> BeginUpdate();
    pItem->SubItems->Add(s);
    //ListView1-> Items-> EndUpdate();
}


void __fastcall TForm1::ShowCanMsg(std::vector<CanMsgST> &v ,int dir)
{
    AnsiString s ;
    std::vector<CanMsgST>::iterator it;


    if(!chkboxScrollEnalble->Checked)
    {
        return;
    }

    if(v.size() <= 0)
    {
        return;
    }

    //ListView1-> Items-> BeginUpdate();

    for(it = v.begin();it != v.end(); ++ it)
    {
        if(this->IsIDPrintable(it->m_iCANID) == false)
            continue;

        TListItem *pItem ;

        if(IsIDPrintable(it->m_iCANID) == false)
            continue;

        pItem = ListView1->Items->Add();//ͨ��1.
        pItem->Caption = "   " + IntToStr((int)++ListCnt1);

        pItem->SubItems->Add((dir == 0)?"����":"����");

        GetMsgTimeStr(*it,s);
        pItem->SubItems->Add(s);//ʱ����

        pItem->SubItems->Add("0x" + IntToHex((*it).m_iCANID,8));
        pItem->SubItems->Add(((*it).m_ExtFlag == 0)?"��׼֡":"��չ֡");
        s = "   ";
        for(int i = 0 ;i < (*it).m_ucLength;i++)
        {
            s += "  " + IntToHex((*it).m_aucData[i],2);
        }

        pItem->SubItems->Add(s);
        //������Ϣ���͸��¶�Ӧ�ؼ�����.
    }

    //ֻ��¼�����10000����¼--��ֹ�ڴ�������µĲ��ȶ����
    while(ListView1->Items->Count > MAX_LISTVIEW_ITEM_COUNT)
    {
        ListView1->Items->Delete(0);//��ͣɾ�������ԴﵽЧ��
    }

    //ListView1-> Items-> EndUpdate();
}



void __fastcall TForm1::DoSendMsg(CanMsgST & msg , bool TriggleResponse)
{
    this->pCanDev->SndMsg(msg);
    //CurMsg = msg;

    if(TriggleResponse == true)
    {
        //TimeoutTicks = 0;
        //HeartbeatCnt = 0;
    }

    msg.m_ucChannel = ComboxChannel->ItemIndex;

    SaveCanMsg(msg, false);

    SetMsgTime(msg);
    ShowCanMsg(msg,0);
}


void __fastcall TForm1::btnConnectCANClick(TObject *Sender)
{
  //
    AnsiString s = "";
    unsigned char ucChannel;
    int iBitRate;

    if( pCanDev != NULL && pCanDev->IsDeviceOpen() == true)
    {
        //�ر��豸
        CommTimer->Enabled = false;
        try{

            pCanDev->CloseDevice(s);
            btnConnectCAN->Caption = "����";
            pCanDev->ConnectionInfo(s);
            StBar_Main->Panels->Items[0]->Text = s;
        }
        catch(...)
        {
            ShowInfo("�쳣");
        }
        ShowInfo("���ӶϿ�");
        this->ComboxBitRate->Enabled = true;
        this->ComboxChannel->Enabled = true;
        this->ComboxCanDevType->Enabled = true;
        //Sh_ConnSt->Brush->Color =  COLOR_OFF;
        this->chkPeriodicGetInfo->Checked = false;

        delete pCanDev;

        pCanDev = NULL;

        CloseCurrentFile();
        return;
    }

    try{
        //DLL�ļ���.
        if (ComboxCanDevType->ItemIndex < 2)
        {
            AnsiString astrDllNames[2]=
            {
                    "ControlCan-DSP.dll",
                    "ControlCan-ZLG.dll",
            };
            InitUSBCAN2DLL(astrDllNames[ComboxCanDevType->ItemIndex]);

            if(pCanDev == NULL)
            {
                pCanDev = (CANDevice*)new CANDEV_USBCAN2;
            }
        }
        else if( ComboxCanDevType->ItemIndex == 2) // valueCAN3
        {
             if(InitValueCanDLL() == false)
             {
                 ShowInfo("��ʧ��,����ļ�icsneo40.dll�Ƿ���" , Msg_WarningMsg);
                 return;
             }

             pCanDev = (CANDevice*)new ValueCAN3;
        }

        ucChannel = this->ComboxChannel->ItemIndex;

        if(this->ComboxBitRate->ItemIndex >=  sizeof(CANDevice::BaudRateList)/sizeof(CANDevice::BaudRateList[0]))
        {
            this->ComboxBitRate->ItemIndex = 1;//500
        }

        iBitRate = CANDevice::BaudRateList[this->ComboxBitRate->ItemIndex ];

        if(pCanDev->OpenDevice(s,ucChannel,iBitRate,iBitRate)== false)
        {
            ShowInfo("��ʧ��:" + s, Msg_WarningMsg);
            delete pCanDev;
            pCanDev = NULL;
            return;
        }
    }
    catch(AnsiString& ss)
    {
        ShowInfo("��ʧ��:" + ss,Msg_WarningMsg);
        return;
    }
    catch(...)
    {
        ShowInfo("δ֪ϵͳ�쳣" + Msg_ErrorMsg);
        return;
    }

    //CommTimer->Enabled = true;
    ShowInfo("�򿪳ɹ�");

    this->btnConnectCAN->Caption = "�Ͽ�";
    pCanDev->ConnectionInfo(s);
    StBar_Main->Panels->Items[0]->Text = s;

    this->ComboxBitRate->Enabled = false;
    this->ComboxChannel->Enabled = false;
    this->ComboxCanDevType->Enabled = false;
    this->CommTimer->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    //CAN�豸�б�
    this->ComboxCanDevType->Items->Add("USBCAN2-DSP");
    this->ComboxCanDevType->Items->Add("USBCAN2-ZLG");
    this->ComboxCanDevType->Items->Add("ValueCAN3");
    this->ComboxCanDevType->Style = csDropDownList;
    this->ComboxCanDevType->ItemIndex = 0;

    //CANͨ������ѡ��
    this->ComboxBitRate->Items->Clear();
    this->ComboxBitRate->Items->Add("100kbps");
    this->ComboxBitRate->Items->Add("250kbps");
    this->ComboxBitRate->Items->Add("200kbps");
    this->ComboxBitRate->Items->Add("400kbps");
    this->ComboxBitRate->Items->Add("500kbps");
    this->ComboxBitRate->Items->Add("1000kbps");
    this->ComboxBitRate->Style = csDropDownList;
    //Ĭ��ֵΪ500K-->ͨ��������CAN�������.
    this->ComboxBitRate->ItemIndex = 4;

    //CANͨ��ѡ��.
    this->ComboxChannel->Items->Clear();
    this->ComboxChannel->Items->Add("CAN1");
    this->ComboxChannel->Items->Add("CAN2");
    this->ComboxChannel->Style = csDropDownList;
    this->ComboxChannel->ItemIndex = 0;
    //this->Shape1->Brush->Color =  clBtnShadow;


    this->cboxFrameType->Items->Clear();

    this->cboxFrameType->Items->Add("��׼֡");
    this->cboxFrameType->Items->Add("��չ֡");
    this->cboxFrameType->ItemIndex = 1;//Ĭ��������չ֡.
    this->cboxFrameType->Style = csDropDownList;

    //״̬����������
    StBar_Main->Font->Size = 11;

    //��������
    PC_Main->ActivePage = TS_CellInfo; // ����Ĭ��ҳ��.

    //��ʱ����ʼ��.
    CommTimer->Interval = 30;//30ms����һ��
    CommTimer->Enabled = true;

    // �����ʾ.
    StringGridAutoSize(*this->SG_RunInfo);
    // StringGridAutoSize(*this->SG_AIAO);


    SG_RunInfo->Cells[0][0] = "��������";
    SG_RunInfo->Cells[0][1] = "��Դ��ѹ";
    SG_RunInfo->Cells[0][2] = "���ƿ��¶�";
    SG_RunInfo->Cells[0][3] = "λ��";
	SG_RunInfo->Cells[0][4] = "�ٶ�";
	SG_RunInfo->Cells[0][5] = "ģ������0";
	SG_RunInfo->Cells[0][6] = "ģ������1";
	SG_RunInfo->Cells[0][7] = "ģ������2";
	SG_RunInfo->Cells[0][8] = "ģ������3";



    SG_RunInfo->Cells[1][0] = "����ֵ";
    SG_RunInfo->Cells[2][0] = "��λ";


    // �����޸�.
    CB_MotorDir->Items->Add("˳ʱ��");
    CB_MotorDir->Items->Add("��ʱ��");
    CB_MotorDir->Style = csDropDownList;

    CB_MotorSpeed->Items->Add("0-ֹͣ");
    CB_MotorSpeed->Items->Add("1");
    CB_MotorSpeed->Items->Add("2");
    CB_MotorSpeed->Items->Add("3");
    CB_MotorSpeed->Items->Add("4");
    CB_MotorSpeed->Items->Add("5");
	CB_MotorSpeed->Style = csDropDownList;


	// ������ʾ������.

	for(int i = 0;i < lg_Input->LedNum;i++)
	{
		lg_Input->LedLabelInfo[i] = L"Input" + IntToStr(i+1) + "1"; // ��ԭ��ͼ��Ӧ.
	}

    // ͨ�����.
	for(int i = 0;i < lg_AbsEncoder->LedNum;i++)
	{
		lg_AbsEncoder->LedLabelInfo[i] = L"N" + IntToStr(i);     // ��ԭ��ͼ����Ӧ.
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StBar_MainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
          const TRect &Rect)
{
    TCanvas& c = *StatusBar->Canvas;
    if(Panel->Index == 1)
    {
        c.Brush->Color = StPanelColor;//������ɫ
        c.FillRect(Rect);
        DrawText(c.Handle,Panel->Text.c_str(),
            -1, (RECT*)&Rect,
            DT_SINGLELINE | DT_VCENTER);
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnSendMsgClick(TObject *Sender)
{
    if(this->pCanDev == NULL || this->pCanDev->IsDeviceOpen() == false)
    {
        ShowInfo("CAN�ӿ���δ����",Msg_WarningMsg);
        return;
    }
    CanMsgST stMsg;
    //��������.
    AnsiString _sID =  this->Edit3->Text;
    AnsiString _sData = this->Edit2->Text;

    AnsiString sID = StringReplace(_sID," ","",TReplaceFlags()<<rfReplaceAll);
    AnsiString sData = StringReplace(_sData," ","",TReplaceFlags()<<rfReplaceAll);

    if(sID.Length() == 0)
    {
        ShowInfo("δָ����ϢID",Msg_WarningMsg);
        return;
    }

    try{
        stMsg.m_iCANID = StrToInt("0x" + sID);
    }
    catch(...)
    {
        ShowInfo("ID������16�����ַ����߳��ȳ�����Χ",Msg_WarningMsg);
        return;
    }

    stMsg.m_ExtFlag = (this->cboxFrameType->ItemIndex == 0)? 0: 1;//��׼֡OR��չ֡.
    stMsg.m_ucLength = 0;

	if(stMsg.m_ExtFlag == 0 && stMsg.m_iCANID > 0x7FF)
	{
		ShowInfo("��׼֡ID����11bit���ֱ�����",Msg_WarningMsg);
		stMsg.m_iCANID &= 0x7FF;
	}
	else if(stMsg.m_iCANID >= 0x1FFFFFFF)
	{
		ShowInfo("��չ֡ID����29bit���ֱ�����",Msg_WarningMsg);
		stMsg.m_iCANID &= 0x1FFFFFFF;
	}

	if((sData.Length() & 0x01) > 0)
	{
		sData += "0";//���Ȳ���ż������0�ճ�ż��
	}

	if((sData.Length() == 0) || (sData.Length() > 8*2))
	{
		ShowInfo("��Ϣ�����򳤶�Ϊ0���߳���8",Msg_WarningMsg);
		return;
	}


	// ���������0.

    ::memset(stMsg.m_aucData,0,sizeof(stMsg.m_aucData));

	//!!!!AnsiString ������1��ʼ...����..
	for(int i =1  ;i < sData.Length() && stMsg.m_ucLength <= 8;i+=2)
	{
		char h = CharToHex(sData[i]);
		char l = CharToHex(sData[i+1]);
		if(h < 0x10 && l <= 0x10)
		{
			stMsg.m_aucData[stMsg.m_ucLength] = h<<4|l;
			stMsg.m_ucLength ++;
		}
		else
		{
			ShowInfo("��Ϣ���ݰ�����16�����ַ�",Msg_WarningMsg);
			return;
		}
	}

	if (chkFillData->Checked)
	{
        stMsg.m_ucLength = 8;//���ݳ�����䵽8λ.
	}

    //���ݽ�ͨ����д���ȥ.
    stMsg.m_ucChannel = 0;

    DoSendMsg(stMsg,false);
    ShowInfo("��Ϣ�ѷ���");
}
//---------------------------------------------------------------------------

bool TForm1::ParseIDList(std::set<int> &idList)
{
    idList.clear();
    for(int i = 0 ;i < this->memoIDList->Lines->Count;i++)
    {
        // int id = StrToIntDef(memoIDList->Lines[i],-1);
        int id = StrToIntDef("0x"+memoIDList->Lines->Strings[i],-1);
        if(id == -1)
        {
            ShowInfo("��"+IntToStr(i+1)+"�������޷�����",Msg_WarningMsg);
            idList.clear();
            return false;
        }
        else if(id > 0x1FFFFFFF || id < 0)
        {
            ShowInfo("��"+IntToStr(i+1)+"�����벻����ЧCANID",Msg_WarningMsg);
            idList.clear();
            return false;
        }
        else
        {
            idList.insert(id);
        }
    }

    return true;
}



void __fastcall TForm1::memoIDListKeyPress(TObject *Sender, System::WideChar &Key)
{
    if (!(
           (Key >= '0' && Key <= '9')
           || (Key >= 'a' && Key <= 'f')
           || (Key >= 'A' && Key <= 'Z')
           //|| (Key == '-')
           || (Key == VK_BACK)
           || (Key == VK_RETURN)
           || (Key == VK_DELETE)
         )
        )
    {
    	Key = '\0';
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::memoIDListKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(ParseIDList(this->CanIDFilterSet) == false)
    {
        //FilterMode = 0;
        //RadioGroup1->ItemIndex = FilterMode;
    }

	FilterMode =  RadioGroup1->ItemIndex;
}

static AnsiString ShowTime(void)
{
    TSystemTime currentTime;
    GetLocalTime(&currentTime);

    AnsiString s = "";
    s.sprintf("%04d-%02d-%02d %02d:%02d:%02d",
        (int)currentTime.wYear,
        (int)currentTime.wMonth,
        (int)currentTime.wDay,
        (int)currentTime.wHour,
        (int)currentTime.wMinute,
        (int)currentTime.wSecond
    );

    return s;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::CommTimerTimer(TObject *Sender)
{
    static int iPeriodCounter = 0;
    static int iCAN0PeriodCounter = 0;
    static int iTimeOutCommunication = 0;

    static int comFailedCnt = 0;
    static bool bCommFailed = true;  // Ĭ�ϲ���.

    static int iTimer300ms = 0;
    static int Timer1s = 1000 / CommTimer->Interval;

    std::vector<CanMsgST> v;
    std::vector<CanMsgST>::iterator it;

    //��ʾʱ��.
    if( ++Timer1s >= (int)((1000 / CommTimer->Interval)-2))
    {
        Timer1s = 0;
        this->StBar_Main->Panels->Items[2]->Text = ShowTime();
    }

    if(this->pCanDev == NULL || this->pCanDev->IsDeviceOpen()== false)
        return;

    // edt_CANError->Text = IntToStr(pCanDev->GetErrCnt());

    if( chkPeriodicGetInfo->Checked)
    {
        if( ++ iPeriodCounter >= (int)((1000 / CommTimer->Interval)))
        {
            //
            btnSendMsg->Click();
        }
    }

    pCanDev->DriverThread();
    pCanDev->GetMsg(v);

    if(v.size() <= 0)
    {
        return;
    }


    for(it = v.begin() ;it < v.end();++it)
    {
        //this->MsgHandler(*it);
    }

    if (chkBoxSaveCommData->Checked)
    {
        for(it = v.begin() ;it < v.end();++it)
        {
            SaveCanMsg(*it, true); // Ĭ�ϲ���¼����.
        }
    }

    ShowCanMsg(v,1);//��Ϣˢ����ʾ.
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
    if(ListView1->Items->Count == 0)
    {
        return;
    }

    //���
    ListView1->Items->BeginUpdate();
    ListView1->Items->Clear();
    ListCnt1 = 0;//����������.
    ListView1->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
    if(ParseIDList(this->CanIDFilterSet) == false)
    {
        FilterMode = 0;
        RadioGroup1->ItemIndex = FilterMode;
    }

    FilterMode =  RadioGroup1->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SG_CellInfoDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
    TStringGrid * pSG = dynamic_cast<TStringGrid*>(Sender);

    if(pSG == NULL)
    {
        return;
    }

    if(ACol == 0 || ARow == 0)
    {
        pSG->Canvas->Brush->Color = clBtnFace;
    }
    else
    {
        pSG->Canvas->Brush->Color = clWindow;
	}

    pSG->Canvas->FillRect(Rect);

    if(State.Contains(gdFocused) && (ACol != 0 && ARow != 0))
    {
        pSG->Canvas->Pen->Color = clBlue;
        pSG->Canvas->Rectangle(Rect);
    }

    TTextFormat format;
    format << tfCenter << tfSingleLine << tfVerticalCenter;
    UnicodeString st = pSG->Cells[ACol][ARow];

    pSG->Canvas->TextRect(Rect,st,format);
}

void __fastcall TForm1::SG_RunInfoDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{
    TStringGrid * pSG = dynamic_cast<TStringGrid*>(Sender);

    if(pSG == NULL)
    {
        return;
    }

    if(ACol == 0 || ARow == 0)
    {
        pSG->Canvas->Brush->Color = clBtnFace;
    }
    else
    {
        pSG->Canvas->Brush->Color = clWhite;
	}

    pSG->Canvas->FillRect(Rect);

    if(State.Contains(gdFocused) && (ACol != 0 && ARow != 0))
    {
        pSG->Canvas->Pen->Color = clBlue;
        pSG->Canvas->Rectangle(Rect);
    }

    TTextFormat format;
    format << tfCenter << tfSingleLine << tfVerticalCenter;
    UnicodeString st = pSG->Cells[ACol][ARow];

    pSG->Canvas->TextRect(Rect,st,format);
}
//---------------------------------------------------------------------------


extern "C"
{
    #include "Parser.h"
}
extern "C" void SplitCmd(char *);
void __fastcall TForm1::btnParseInputClick(TObject *Sender)
{
    // ��ʼ����.
    static char cmdBuffer[2048];
    vector<AnsiString>::const_iterator it;
    // ��ʼ�����������

    vJcodeStrings.clear();

    if (mm_JcodeInput->Lines->Count > 0)
    {
        AnsiString s(mm_JcodeInput->Lines[0][0]);
        memset(cmdBuffer,0,sizeof(cmdBuffer));
        strncpy(cmdBuffer,s.c_str(),sizeof(cmdBuffer)-1);
        SplitCmd(cmdBuffer);

        for (it = vJcodeStrings.begin();it < vJcodeStrings.end();++it)
        {
            mm_JcodeParser->Lines->Add(*it);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnExecuteCmdClick(TObject *Sender)
{
    // ��ת�ٺͷ����·������ư�.
    if(this->pCanDev == NULL || this->pCanDev->IsDeviceOpen() == false)
    {
        ShowInfo("CAN�ӿ���δ����",Msg_WarningMsg);
        return;
    }


    CanMsgST stMsg;
    stMsg.m_iCANID  = 0x100;
    stMsg.m_ExtFlag = 0;
    stMsg.m_ucLength= 8;

    if (CB_MotorDir->ItemIndex == -1)
    {
         ShowInfo("��ѡ����",Msg_WarningMsg);
         return;
    }


    if (CB_MotorSpeed->ItemIndex == -1)
    {
         ShowInfo("��ѡ���ٶȼ���",Msg_WarningMsg);
         return;
    }

    ::memset(stMsg.m_aucData,0,8);

    stMsg.m_aucData[0] = CB_MotorDir->ItemIndex;
    stMsg.m_aucData[1] = CB_MotorSpeed->ItemIndex;

    DoSendMsg(stMsg,false);
    ShowInfo("����������ѷ���");
}
//---------------------------------------------------------------------------





