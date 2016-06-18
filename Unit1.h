//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Tabs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "CanDevice.h"
#include "DataProc.h"
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.FileCtrl.hpp>
#include "LedGroupMain.h"
#include <set>
#include <vector>

typedef enum tagE_Msglevel{

       Msg_NormalMsg,
       Msg_WarningMsg,
       Msg_ErrorMsg,
       Msg_Special,

}LogPri;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PC_Main;
    TPanel *Panel1;
    TComboBox *ComboxChannel;
    TComboBox *ComboxCanDevType;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *ComboxBitRate;
    TButton *btnConnectCAN;
    TTimer *CommTimer;
    TStatusBar *StBar_Main;
    TCheckBox *chkPeriodicGetInfo;
    TTabSheet *TS_CANMsg;
    TCheckBox *chkboxScrollEnalble;
    TCheckBox *chkBoxSaveCommData;
    TEdit *Edit3;
    TLabel *Label25;
    TLabel *Label24;
    TComboBox *cboxFrameType;
    TLabel *Label31;
    TEdit *Edit2;
    TButton *btnSendMsg;
    TListView *ListView1;
    TRadioGroup *RadioGroup1;
    TMemo *memoIDList;
    TLabel *Label7;
    TPopupMenu *POM_ClearMsg;
    TMenuItem *N1;
    TTabSheet *TabSheet1;
	TLabel *Label4;
	TLabel *Label5;
	TCheckBox *chkFillData;
	TTabSheet *TS_CellInfo;
	TTabSheet *TabSheet2;
    TMemo *mm_JcodeInput;
    TMemo *mm_JcodeParser;
	TLabel *label6;
	TLabel *Label8;
    TGroupBox *grpDI;
    TStringGrid *SG_RunInfo;
    TButton *btnParseInput;
    TComboBox *ComboBox1;
    TLabel *Label22;
    TComboBox *ComboBox2;
    TLabel *Label14;
    TLabel *Label23;
    TButton *Button1;
    TEdit *Edit1;
    TStringGrid *StringGrid1;
    TStringGrid *StringGrid2;
    TLabel *Label26;
    TLabel *Label27;
    TTabSheet *TS_MotorCtrl;
    TComboBox *CB_MotorDir;
    TLabel *Label28;
    TComboBox *CB_MotorSpeed;
    TLabel *Label29;
    TButton *btnExecuteCmd;
	TLedGroup *lg_Input;
	TGroupBox *GroupBox2;
	TLedGroup *lg_AbsEncoder;
	TTabSheet *TabSheet3;
    void __fastcall btnConnectCANClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall StBar_MainDrawPanel(TStatusBar *StatusBar, TStatusPanel *Panel,
          const TRect &Rect);
    void __fastcall btnSendMsgClick(TObject *Sender);
    void __fastcall memoIDListKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall memoIDListKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall CommTimerTimer(TObject *Sender);
    void __fastcall N1Click(TObject *Sender);
    void __fastcall RadioGroup1Click(TObject *Sender);
    void __fastcall SG_CellInfoDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
    void __fastcall SG_RunInfoDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
    void __fastcall btnParseInputClick(TObject *Sender);
    void __fastcall btnExecuteCmdClick(TObject *Sender);










private:	// User declarations
    CANDevice * pCanDev;
    TColor StPanelColor;

     //ListView显示用的计数器.
    u32 ListCnt1;
    // 过滤报文.
    std::set<int> CanIDFilterSet;
    int FilterMode;




public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    void __fastcall ShowInfo(AnsiString s, LogPri eLogPri = Msg_NormalMsg);
    void __fastcall ShowCanMsg(std::vector<CanMsgST> &v ,int dir);
    void __fastcall TForm1::ShowCanMsg(const CanMsgST & msg,int dir);
    bool ParseIDList(std::set<int> &idList);
    bool IsIDPrintable(int id);
    void __fastcall TForm1::DoSendMsg(CanMsgST & msg , bool TriggleResponse);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
