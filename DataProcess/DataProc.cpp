#include "CanDevice.h"
#include "DataProc.h"
#include <ustring.h>
#include "SignalMatrix.h"
#include <windows.h>


void InitFileRecordHeader(WideString & s )
{
    static const wchar_t * RecordHeader[] =
    {
        L"ʱ���\t",//��ʾ��Ϣ��.
        L"������ѹ(V)\t",
        L"NTC��ѹ(V)\t", // 5V��ѹ.
        L"�ܵ�ѹ(V)\t",
        L"�ܵ���(A)\t",
        L"������Ե�迹(K��)\t"
        L"������Ե�迹(K��)\t"
        L"SOC(%)\t",
        L"SOH(%)\t",
        L"����¶�(��)\t",
        L"����¶�(��)\t",
        L"��ߵ����ѹ(mV)\t",
        L"��͵����ѹ(mV)\t",
        L"�澯��Ϣ\t"   //��ʾ��Ϣ��.
        L"�澯1-��������\t",
        L"�澯2-�ŵ������\t",
        L"�澯3-�����ѹ����\t",
        L"�澯4-�����ѹ����\t",
        L"�澯5-�¶ȹ���\t",
        L"�澯6-�²����\t",
        L"�澯7-����ѹ�����\t",
        L"�澯8-SOC����\t",
        L"�澯9-��Ե����\t",
        L"�澯10-�ܵ�ѹ����\t",
        L"�澯11-�¶ȹ���\t",
        L"�澯12-���س���ͨ�Ź���\t",
        L"�澯13-BMS�ڲ�ͨѶ����\t",
        L"�澯14-����Ԫ������\t",
        L"�澯15-��ѹ���Ӵ�������\t",
        L"�澯16-ϵͳӲ������\t",
        L"�澯17-Ԥ���ʧ��\t",
        L"�����ѹ\t",     //��ʾ��Ϣ��.
        L"��о��ѹ-1(mV)\t",
        L"��о��ѹ-2(mV)\t",
        L"��о��ѹ-3(mV)\t",
        L"��о��ѹ-4(mV)\t",
        L"��о��ѹ-5(mV)\t",
        L"��о��ѹ-6(mV)\t",
        L"��о��ѹ-7(mV)\t",
        L"��о��ѹ-8(mV)\t",
        L"��о��ѹ-9(mV)\t",
        L"��о��ѹ-10(mV)\t",
        L"��о��ѹ-11(mV)\t",
        L"��о��ѹ-12(mV)\t",
        L"��о��ѹ-13(mV)\t",
        L"��о��ѹ-14(mV)\t",
        L"��о��ѹ-15(mV)\t",
        L"��о��ѹ-16(mV)\t",
        L"��о��ѹ-17(mV)\t",
        L"��о��ѹ-18(mV)\t",
        L"��о��ѹ-19(mV)\t",
        L"��о��ѹ-20(mV)\t",
        L"��о��ѹ-21(mV)\t",
        L"��о��ѹ-22(mV)\t",
        L"��о��ѹ-23(mV)\t",
        L"��о��ѹ-24(mV)\t",
        L"��о��ѹ-25(mV)\t",
        L"��о��ѹ-26(mV)\t",
        L"��о��ѹ-27(mV)\t",
        L"��о��ѹ-28(mV)\t",
        L"��о��ѹ-29(mV)\t",
        L"��о��ѹ-30(mV)\t",
        L"��о��ѹ-31(mV)\t",
        L"��о��ѹ-32(mV)\t",
        L"��о��ѹ-33(mV)\t",
        L"��о��ѹ-34(mV)\t",
        L"��о��ѹ-35(mV)\t",
        L"��о��ѹ-36(mV)\t",
        L"��о��ѹ-37(mV)\t",
        L"��о��ѹ-38(mV)\t",
        L"��о��ѹ-39(mV)\t",
        L"��о��ѹ-40(mV)\t",

        L"����¶�\t",        //��ʾ��Ϣ��.
        L"����¶�-1(��)\t",
        L"����¶�-2(��)\t",
        L"����¶�-3(��)\t",
        L"����¶�-4(��)\t",
        L"����¶�-5(��)\t",
        L"����¶�-6(��)\t",
        L"����¶�-7(��)\t",
        L"����¶�-8(��)\t",
        L"����¶�-9(��)\t",
        L"����¶�-10(��)\t",

    };

    for(int i = 0 ;i < sizeof(RecordHeader)/sizeof(RecordHeader[0]);i++)
    {
        s += (WideString)RecordHeader[i];
    }

    s += (WideString)L"\n";
}

//��¼T01����,�����澯����Ϣ.�澯��Ϣ��JV���źž����л��.
void T01SignalMatrixToStr(BMS_RUN_INFO_ST & stInfo , WideString &s)
{
    TSystemTime currentTime;
    GetLocalTime(&currentTime);

    AnsiString _s = "";
    _s.sprintf(" %04d-%02d-%02d %02d:%02d:%02d",
        (int)currentTime.wYear,
        (int)currentTime.wMonth,
        (int)currentTime.wDay,
        (int)currentTime.wHour,
        (int)currentTime.wMinute,
        (int)currentTime.wSecond
    );

    // ʱ��.
    s += _s + "\t";
    // ������ѹ.
    float fTemp = stInfo.m_usAuxPowerVolt / 1000.0;
    s += FloatToStrF(fTemp, ffFixed, 5, 1) + L"\t";

    // 5V��ѹֵ.
    s += IntToStr((int)stInfo.m_usNtcPowerVolt) + L"\t";

    //  �ܵ�ѹ
    fTemp = stInfo.m_ulBattVolt / 1000.0;
    s += FloatToStrF(fTemp, ffFixed, 5, 1) + L"\t";
    //  �ܵ���
    fTemp = stInfo.m_slBattCurr / 1000.0;
    s += FloatToStrF(fTemp, ffFixed, 5, 1) + L"\t";
    //   �����迹.
    s += IntToStr((int)stInfo.m_ulPosInsRes) + L"\t";
    //   �����迹.
    s += IntToStr((int)stInfo.m_ulNegInsRes) + L"\t";
    //  SOC
    s += IntToStr(stInfo.m_ucBattSocPercent) + L"\t";
    //  SOH
    s += IntToStr(stInfo.m_ucBattSOH) + L"\t";
    //  ����¶�
    s += IntToStr(stInfo.m_ssCellMaxTemp) + L"\t";
    //  ����¶�
    s += IntToStr(stInfo.m_ssCellMinTemp) + L"\t";
    //  ��ߵ����ѹ.
    s += IntToStr(stInfo.m_usCellMaxVolt) + L"\t";
    //  ��͵����ѹ.
    s += IntToStr(stInfo.m_usCellMinVolt) + L"\t";
    //  ����.
    s +=L"  \t";
    //  �澯.
    for(int i =0 ;i < sizeof(stInfo.m_aucAlarmSt)/sizeof(stInfo.m_aucAlarmSt[0]);i++)
    {
        u8 ucLevel = (stInfo.m_aucAlarmSt[i] & 0x04 ) ? 1:
                     (stInfo.m_aucAlarmSt[i] & 0x02 ) ? 2:
                     (stInfo.m_aucAlarmSt[i] & 0x01 ) ? 3:0;
        if( ucLevel > 0)
        {
            s += IntToStr(ucLevel) + "��"+ L"\t";
        }
        else
        {
            s += L"  \t";
        }
    }
    //  ����.
    s +=L"  \t";
    //  �����ѹ.
    for(int i = 0 ;i < sizeof(stInfo.m_ausCellVolt)/sizeof(stInfo.m_ausCellVolt[0]);i++)
    {
        s += IntToStr(stInfo.m_ausCellVolt[i]) + L"\t";
    }
    //  ����.
    s +=L"  \t";
    for(int i = 0 ;i  < sizeof(stInfo.m_assCellTemp)/sizeof(stInfo.m_assCellTemp[0]);i++)
    {
        s += IntToStr(stInfo.m_assCellTemp[i]) + L"\t";
    }

    s += L"\n";
}

//�ļ���д.
#define HISTORY_DIR "history"
#define COMM_DATA_DIR "Comm Data"
#define MAX_RECORD_SINGLE_FILE 60000 //���ļ������ʷ��¼����
#define MAX_MSGS_SINGLE_FILE 60000   //����ͨ�ż�¼�ļ���¼�������ʷ��¼����.


bool dirExists(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}


bool CreateHistoryDir(const AnsiString & OutputFolder)
{
    UnicodeString s = OutputFolder;

    if (CreateDirectory(s.c_str(), NULL) ||
        ERROR_ALREADY_EXISTS == GetLastError())
    {
        return true;
    }
    else
    {
         return false;
    }
}

static bool bHistoryDirExist = false;

//��ʼ���ļ���¼
bool InitHistoryRecord(AnsiString & s)
{
    if(CreateHistoryDir(HISTORY_DIR) == false)
    {
        s = "������ʷ��¼�ļ�Ŀ¼ʧ��";
        return false;
    }

    s = "��ʷ��¼��ʼ��׼�����";
    bHistoryDirExist = true;
    return true;
}


AnsiString GetTimeStr(void)
{
    TSystemTime currentTime;
    GetLocalTime(&currentTime);

    AnsiString s = "";
    s.sprintf("%04d-%02d-%02d_%02d_%02d_%02d",
        (int)currentTime.wYear,
        (int)currentTime.wMonth,
        (int)currentTime.wDay,
        (int)currentTime.wHour,
        (int)currentTime.wMinute,
        (int)currentTime.wSecond
    );

    return s;
}

static const char BOM_Unicode[] = {0xFF,0xFE};
static FILE * pCurFileHandle = NULL;//��ǰ�ļ�ָ��.
static FILE * pCommFileHandle = NULL;//����ͨ��������.

void CloseCurrentFile(void)
{
     if(pCurFileHandle != NULL)
     {
        fclose(pCurFileHandle);
        pCurFileHandle = NULL;
     }
}

void CanMsgToStr(CanMsgST & stMsg , bool isRcvMsg , WideString & s)
{
    AnsiString sTime = "";

    TSystemTime currentTime;
    GetLocalTime(&currentTime);

    sTime.sprintf("%04d-%02d-%02d %02d:%02d:%02d:%03d",
        (int)currentTime.wYear,
        (int)currentTime.wMonth,
        (int)currentTime.wDay,
        (int)currentTime.wHour,
        (int)currentTime.wMinute,
        (int)currentTime.wSecond,
        (int)currentTime.wMilliseconds
    );

    s = "";

    //ʱ��
    s += sTime + L"\t";

    //CAN��Ϣת��Ϊ����.
    if(isRcvMsg)
    {
        s += L"����\t";
    }
    else
    {
        s += L"����\t";
    }

    //��ϢID
    s += "0x" + IntToHex(stMsg.m_iCANID,8) + "\t";
    //��Ϣ������.

    //֡����
    s += (stMsg.m_ExtFlag > 0)?L"EXT\t":L"STD\t";

    AnsiString sd = "";
    for(int i = 0;i < (int)stMsg.m_ucLength ; i ++ )
    {
        sd += IntToHex((int)stMsg.m_aucData[i],2) + L" ";
    }
    s += sd ;

}


static bool bCommDirExist = false;
//��ʼ���ļ���¼
bool InitCommRecord(AnsiString & s)
{
    if(CreateHistoryDir(COMM_DATA_DIR) == false)
    {
        s = "�������ļ�¼�ļ�Ŀ¼ʧ��";
        return false;
    }

    s = "���ļ�¼��ʼ��׼�����";
    bCommDirExist = true;
    return true;
}

bool SaveCanMsg(CanMsgST & stMsg, bool isRcvMsg)
{
    //��ͷ.

    static int iFileLineCounter = 0;
    static WideString sHeaderComm =
        L"ʱ��\t����\t��ϢID\t֡����\t������\t\n";
    
    static WideString sMsg = "";

    if(bCommDirExist == false)
    {
        AnsiString _errStr = "";
        InitCommRecord(_errStr);
        return bCommDirExist;
    }

    if(pCommFileHandle == NULL)
    {
        AnsiString sFileName = "";  //�ļ���.
        sFileName = COMM_DATA_DIR;
        sFileName += "//";
        sFileName += "Communication-Data-";//
        sFileName += GetTimeStr();
        sFileName += ".csv";

        pCommFileHandle = fopen(sFileName.c_str(), "wb+");

        if(pCommFileHandle == NULL)
        {
            return false;
        }
        
        //д��BOM,�Ա����ļ�������Unicode.
        fwrite(BOM_Unicode,sizeof(BOM_Unicode),1,pCommFileHandle);
        fwrite(sHeaderComm.c_bstr(),sHeaderComm.Length()*sizeof(wchar_t),1,pCommFileHandle);
    }

    if ( pCommFileHandle == NULL)
    {
        return false;
    }

    CanMsgToStr(stMsg,isRcvMsg,sMsg);
    sMsg += L"\n";//����.
    //д��CAN��Ϣ��¼
    fwrite(sMsg.c_bstr(),sMsg.Length()*sizeof(wchar_t),1,pCommFileHandle);

    if(++iFileLineCounter >= MAX_MSGS_SINGLE_FILE)
    {
        //�ر��ļ�.
        fclose(pCommFileHandle);
        pCommFileHandle = NULL;
        iFileLineCounter = 0;
    }

    return true;
}


//д����ʷ��¼�ļ�
bool SavT01Record(BMS_RUN_INFO_ST & stInfo)
{
    static WideString sHeader = "";
    static AnsiString sFileName = "";
    static int iFileLineCounter = 0;

    if(bHistoryDirExist == false)
    {
        AnsiString _errStr = "";
        InitHistoryRecord(_errStr);
        return bHistoryDirExist;
    }

    if(pCurFileHandle == NULL)
    {
        sFileName = HISTORY_DIR;
        sFileName += "//T01_CAN2_";
        sFileName += GetTimeStr();
        sFileName += ".csv";

        pCurFileHandle = fopen(sFileName.c_str(), "wb+");

        if(pCurFileHandle == NULL)
        {
            return false;
        }

        //д���ͷ
        if(sHeader.IsEmpty())
        {
            InitFileRecordHeader(sHeader);
        }
        //д��BOM,�Ա����ļ�������Unicode.
        fwrite(BOM_Unicode,sizeof(BOM_Unicode),1,pCurFileHandle);
        fwrite(sHeader.c_bstr(),sHeader.Length()*sizeof(wchar_t),1,pCurFileHandle);
    }

    //д���¼
    WideString sRecord = "";
    T01SignalMatrixToStr(stInfo , sRecord);

    fwrite(sRecord.c_bstr(),sRecord.Length()*sizeof(wchar_t),1,pCurFileHandle);

    if(++iFileLineCounter >= MAX_RECORD_SINGLE_FILE)
    {
        //�ر��ļ�.
        fclose(pCurFileHandle);
        pCurFileHandle = NULL;
        iFileLineCounter = 0;
    }

    return true;
}

/*
 *  ��¼�������ĵ�����.
 */

WideString GetCAN0HeaderLine(void)
{
    const wchar_t * RecordHeader[] =
    {
        L"ʱ���\t",//��ʾ��Ϣ��.
        L"SOC(%)\t",
        L"�ܵ�ѹ(V)\t",
        L"�ܵ���(A)\t",
        // BMS����״̬.
        L"BMS�澯����\t",
        L"BMS������\t",
        // BMS�������.
        L"BMS�������\t",
        L"BMS���״̬\t",
        // �����ѹ/�¶ȼ�ֵ
        L"BMS��ߵ����ѹ(mV)\t",
        L"BMS��͵����ѹ(mV)\t",
        L"�������¶�(��)\t",
        L"�������¶�(��)\t",
        // ���س�������.
        L"���س���-�¶�״̬\t",
        L"���س���-��������״̬\t",
        L"���س���-ֱ�����״̬\t",
        L"���س���-Ӳ��״̬\t",
        L"���س���-����״̬\t",
        L"���س���-�������\t",
        L"���س���-�����ѹ\t",
        // // BMS�г�ģʽ���.
        L"MCU-ĸ�ߵ�ѹ(V)\t",
        L"VCU-���̵�������\t",
        L"BMS-�����̵�������\t",
        L"BMS-�����̵�������\t",
        L"BMS-Ԥ��̵�������\t",
        L"BMS-����ģʽ����\t",
        L"BMS-Ԥ��״̬\t",
        L"BMS-Ԥ�����ָʾ\t",
    };

    AnsiString s = "";
    
    for(int i = 0 ;i < sizeof(RecordHeader)/sizeof(RecordHeader[0]);i++)
    {
        s += (WideString)RecordHeader[i];
    }

    s += (WideString)L"\n";

    return s;
}

void T01CAN0SignalMatrixToStr(T01SignalMatrixST & sigBuf , WideString & sRecord)
{
    float fTempValue ;

    TSystemTime currentTime;
    GetLocalTime(&currentTime);

    AnsiString _s = "";
    _s.sprintf(" %04d-%02d-%02d %02d:%02d:%02d:%3d",
        (int)currentTime.wYear,
        (int)currentTime.wMonth,
        (int)currentTime.wDay,
        (int)currentTime.wHour,
        (int)currentTime.wMinute,
        (int)currentTime.wSecond,
        (int)currentTime.wMilliseconds
    );

    sRecord = "";
    sRecord += (WideString)_s + L"\t";
    // SOC.
    fTempValue = sigBuf.m_unBMS1.m_stBits.m_ullSOC;
    fTempValue *= 0.5;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";
    // �ܵ�ѹ.
    fTempValue = sigBuf.m_unBMS2.m_stBits.m_ullPackVolt;
    fTempValue *= 0.1;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";
    // �ܵ���.
    fTempValue = sigBuf.m_unBMS2.m_stBits.m_ullPackCurrent;
    fTempValue *= 0.1;
    fTempValue -= 500;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";

    // BMS�澯����.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS4.m_stBits.m_ullFaultCode) + L"\t";
    // BMS������.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS1.m_stBits.m_ullBMSAlarmLevel) + L"\t";
    // BMS�������.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS1.m_stBits.m_ullSlowChargeCmd) + L"\t";
    // BMS���״̬.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS1.m_stBits.m_ullBMSChargeSt) + L"\t";
    // BMS ��ߵ����ѹ.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS2.m_stBits.m_ullMaxCellVolt) + L"\t";
    // BMS ��͵����ѹ.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS3.m_stBits.m_ullMinCellVolt) + L"\t";
    // �������¶�.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS3.m_stBits.m_ullMaxCellTemp-40) + L"\t";
    // �������¶�.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS3.m_stBits.m_ullMinCellTemp-40) + L"\t";
    // ���س���-�¶�״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCTempSt) + L"\t";
    // ���س���-��������״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCVoltInputSt) + L"\t";
    // ���س���-ֱ�����״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCVoltOutputSt) + L"\t";    
    // ���س���-Ӳ��״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCHardwareSt) + L"\t";    
    // ���س���-����״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCWorkingMode) + L"\t";
    // ���س���-�������.
    fTempValue = sigBuf.m_unONC.m_stBits.m_ullACDCOutputCurr;
    fTempValue *= 0.1;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";
    // ���س���-�����ѹ.
    fTempValue = sigBuf.m_unONC.m_stBits.m_ullACDCOutputVolt;
    fTempValue *= 0.1;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";

    // MCUĸ�ߵ�ѹ.
    sRecord += (WideString)FloatToStrF((int)sigBuf.m_unMCU3.m_stBits.m_ullDrvMotorVolt * 0.01,ffFixed,6,2) + L"\t";
    // VCU���̵�����������.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unVCU1.m_stBits.m_ullVCU_MainRelayCmd) + L"\t";    
    // BMS-�����̵���״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullNegRelayFB) + L"\t";    
    // BMS-�����̵���״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPosRelayFB) + L"\t";    
    // BMS-Ԥ��̵���״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPreChRelayFB) + L"\t";    
    // BMS-����ģʽ����
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullWorkModeReq) + L"\t";
    // BMS-Ԥ�����״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPreChComplete) + L"\t";
    // BMS-Ԥ�����״̬.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPreChFault) + L"\t";
    sRecord += L"\n";        
}

bool SavT01CAN0Data(T01SignalMatrixST & sigBuf)
{
    static WideString sHeader = "";
    static AnsiString sFileName = "";
    static int iFileLineCounter = 0;

    if(bHistoryDirExist == false)
    {
        AnsiString _errStr = "";
        InitHistoryRecord(_errStr);
        return bHistoryDirExist;
    }

    if(pCurFileHandle == NULL)
    {
        sFileName = HISTORY_DIR;
        sFileName += "//T01_CAN0_";
        sFileName += GetTimeStr();
        sFileName += ".csv";

        pCurFileHandle = fopen(sFileName.c_str(), "wb+");

        if(pCurFileHandle == NULL)
        {
            return false;
        }

        //д���ͷ
        if(sHeader.IsEmpty())
        {
            sHeader = GetCAN0HeaderLine();
        }

        //д��BOM,�Ա����ļ�������Unicode.
        fwrite(BOM_Unicode,sizeof(BOM_Unicode),1,pCurFileHandle);
        fwrite(sHeader.c_bstr(),sHeader.Length()*sizeof(wchar_t),1,pCurFileHandle);
    }

    //д���¼
    WideString sRecord = "";
    T01CAN0SignalMatrixToStr(sigBuf , sRecord);

    fwrite(sRecord.c_bstr(),sRecord.Length()*sizeof(wchar_t),1,pCurFileHandle);

    if(++iFileLineCounter >= MAX_RECORD_SINGLE_FILE)
    {
        //�ر��ļ�.
        fclose(pCurFileHandle);
        pCurFileHandle = NULL;
        iFileLineCounter = 0;
    }

    return true;        
}