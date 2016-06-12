#include "CanDevice.h"
#include "DataProc.h"
#include <ustring.h>
#include "SignalMatrix.h"
#include <windows.h>


void InitFileRecordHeader(WideString & s )
{
    static const wchar_t * RecordHeader[] =
    {
        L"时间戳\t",//提示信息列.
        L"辅助电压(V)\t",
        L"NTC电压(V)\t", // 5V电压.
        L"总电压(V)\t",
        L"总电流(A)\t",
        L"正极绝缘阻抗(KΩ)\t"
        L"负极绝缘阻抗(KΩ)\t"
        L"SOC(%)\t",
        L"SOH(%)\t",
        L"最高温度(℃)\t",
        L"最低温度(℃)\t",
        L"最高单体电压(mV)\t",
        L"最低单体电压(mV)\t",
        L"告警信息\t"   //提示信息列.
        L"告警1-充电电流大\t",
        L"告警2-放电电流大\t",
        L"告警3-单体电压过高\t",
        L"告警4-单体电压过低\t",
        L"告警5-温度过高\t",
        L"告警6-温差过大\t",
        L"告警7-单体压差过大\t",
        L"告警8-SOC过低\t",
        L"告警9-绝缘故障\t",
        L"告警10-总电压过高\t",
        L"告警11-温度过低\t",
        L"告警12-车载充电机通信故障\t",
        L"告警13-BMS内部通讯故障\t",
        L"告警14-加热元件故障\t",
        L"告警15-高压主接触器故障\t",
        L"告警16-系统硬件故障\t",
        L"告警17-预充电失败\t",
        L"单体电压\t",     //提示信息列.
        L"电芯电压-1(mV)\t",
        L"电芯电压-2(mV)\t",
        L"电芯电压-3(mV)\t",
        L"电芯电压-4(mV)\t",
        L"电芯电压-5(mV)\t",
        L"电芯电压-6(mV)\t",
        L"电芯电压-7(mV)\t",
        L"电芯电压-8(mV)\t",
        L"电芯电压-9(mV)\t",
        L"电芯电压-10(mV)\t",
        L"电芯电压-11(mV)\t",
        L"电芯电压-12(mV)\t",
        L"电芯电压-13(mV)\t",
        L"电芯电压-14(mV)\t",
        L"电芯电压-15(mV)\t",
        L"电芯电压-16(mV)\t",
        L"电芯电压-17(mV)\t",
        L"电芯电压-18(mV)\t",
        L"电芯电压-19(mV)\t",
        L"电芯电压-20(mV)\t",
        L"电芯电压-21(mV)\t",
        L"电芯电压-22(mV)\t",
        L"电芯电压-23(mV)\t",
        L"电芯电压-24(mV)\t",
        L"电芯电压-25(mV)\t",
        L"电芯电压-26(mV)\t",
        L"电芯电压-27(mV)\t",
        L"电芯电压-28(mV)\t",
        L"电芯电压-29(mV)\t",
        L"电芯电压-30(mV)\t",
        L"电芯电压-31(mV)\t",
        L"电芯电压-32(mV)\t",
        L"电芯电压-33(mV)\t",
        L"电芯电压-34(mV)\t",
        L"电芯电压-35(mV)\t",
        L"电芯电压-36(mV)\t",
        L"电芯电压-37(mV)\t",
        L"电芯电压-38(mV)\t",
        L"电芯电压-39(mV)\t",
        L"电芯电压-40(mV)\t",

        L"电池温度\t",        //提示信息列.
        L"电池温度-1(℃)\t",
        L"电池温度-2(℃)\t",
        L"电池温度-3(℃)\t",
        L"电池温度-4(℃)\t",
        L"电池温度-5(℃)\t",
        L"电池温度-6(℃)\t",
        L"电池温度-7(℃)\t",
        L"电池温度-8(℃)\t",
        L"电池温度-9(℃)\t",
        L"电池温度-10(℃)\t",

    };

    for(int i = 0 ;i < sizeof(RecordHeader)/sizeof(RecordHeader[0]);i++)
    {
        s += (WideString)RecordHeader[i];
    }

    s += (WideString)L"\n";
}

//记录T01数据,包括告警等信息.告警信息从JV的信号矩阵中获得.
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

    // 时间.
    s += _s + "\t";
    // 辅助电压.
    float fTemp = stInfo.m_usAuxPowerVolt / 1000.0;
    s += FloatToStrF(fTemp, ffFixed, 5, 1) + L"\t";

    // 5V电压值.
    s += IntToStr((int)stInfo.m_usNtcPowerVolt) + L"\t";

    //  总电压
    fTemp = stInfo.m_ulBattVolt / 1000.0;
    s += FloatToStrF(fTemp, ffFixed, 5, 1) + L"\t";
    //  总电流
    fTemp = stInfo.m_slBattCurr / 1000.0;
    s += FloatToStrF(fTemp, ffFixed, 5, 1) + L"\t";
    //   正极阻抗.
    s += IntToStr((int)stInfo.m_ulPosInsRes) + L"\t";
    //   负极阻抗.
    s += IntToStr((int)stInfo.m_ulNegInsRes) + L"\t";
    //  SOC
    s += IntToStr(stInfo.m_ucBattSocPercent) + L"\t";
    //  SOH
    s += IntToStr(stInfo.m_ucBattSOH) + L"\t";
    //  最高温度
    s += IntToStr(stInfo.m_ssCellMaxTemp) + L"\t";
    //  最低温度
    s += IntToStr(stInfo.m_ssCellMinTemp) + L"\t";
    //  最高单体电压.
    s += IntToStr(stInfo.m_usCellMaxVolt) + L"\t";
    //  最低单体电压.
    s += IntToStr(stInfo.m_usCellMinVolt) + L"\t";
    //  空列.
    s +=L"  \t";
    //  告警.
    for(int i =0 ;i < sizeof(stInfo.m_aucAlarmSt)/sizeof(stInfo.m_aucAlarmSt[0]);i++)
    {
        u8 ucLevel = (stInfo.m_aucAlarmSt[i] & 0x04 ) ? 1:
                     (stInfo.m_aucAlarmSt[i] & 0x02 ) ? 2:
                     (stInfo.m_aucAlarmSt[i] & 0x01 ) ? 3:0;
        if( ucLevel > 0)
        {
            s += IntToStr(ucLevel) + "级"+ L"\t";
        }
        else
        {
            s += L"  \t";
        }
    }
    //  空列.
    s +=L"  \t";
    //  单体电压.
    for(int i = 0 ;i < sizeof(stInfo.m_ausCellVolt)/sizeof(stInfo.m_ausCellVolt[0]);i++)
    {
        s += IntToStr(stInfo.m_ausCellVolt[i]) + L"\t";
    }
    //  空列.
    s +=L"  \t";
    for(int i = 0 ;i  < sizeof(stInfo.m_assCellTemp)/sizeof(stInfo.m_assCellTemp[0]);i++)
    {
        s += IntToStr(stInfo.m_assCellTemp[i]) + L"\t";
    }

    s += L"\n";
}

//文件读写.
#define HISTORY_DIR "history"
#define COMM_DATA_DIR "Comm Data"
#define MAX_RECORD_SINGLE_FILE 60000 //单文件最大历史记录条数
#define MAX_MSGS_SINGLE_FILE 60000   //单个通信记录文件记录的最大历史记录数据.


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

//初始化文件记录
bool InitHistoryRecord(AnsiString & s)
{
    if(CreateHistoryDir(HISTORY_DIR) == false)
    {
        s = "创建历史记录文件目录失败";
        return false;
    }

    s = "历史记录初始化准备完成";
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
static FILE * pCurFileHandle = NULL;//当前文件指针.
static FILE * pCommFileHandle = NULL;//保存通信数据用.

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

    //时间
    s += sTime + L"\t";

    //CAN消息转换为数据.
    if(isRcvMsg)
    {
        s += L"接收\t";
    }
    else
    {
        s += L"发送\t";
    }

    //消息ID
    s += "0x" + IntToHex(stMsg.m_iCANID,8) + "\t";
    //消息数据域.

    //帧类型
    s += (stMsg.m_ExtFlag > 0)?L"EXT\t":L"STD\t";

    AnsiString sd = "";
    for(int i = 0;i < (int)stMsg.m_ucLength ; i ++ )
    {
        sd += IntToHex((int)stMsg.m_aucData[i],2) + L" ";
    }
    s += sd ;

}


static bool bCommDirExist = false;
//初始化文件记录
bool InitCommRecord(AnsiString & s)
{
    if(CreateHistoryDir(COMM_DATA_DIR) == false)
    {
        s = "创建报文记录文件目录失败";
        return false;
    }

    s = "报文记录初始化准备完成";
    bCommDirExist = true;
    return true;
}

bool SaveCanMsg(CanMsgST & stMsg, bool isRcvMsg)
{
    //表头.

    static int iFileLineCounter = 0;
    static WideString sHeaderComm =
        L"时间\t方向\t消息ID\t帧类型\t数据域\t\n";
    
    static WideString sMsg = "";

    if(bCommDirExist == false)
    {
        AnsiString _errStr = "";
        InitCommRecord(_errStr);
        return bCommDirExist;
    }

    if(pCommFileHandle == NULL)
    {
        AnsiString sFileName = "";  //文件名.
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
        
        //写入BOM,以表明文件编码是Unicode.
        fwrite(BOM_Unicode,sizeof(BOM_Unicode),1,pCommFileHandle);
        fwrite(sHeaderComm.c_bstr(),sHeaderComm.Length()*sizeof(wchar_t),1,pCommFileHandle);
    }

    if ( pCommFileHandle == NULL)
    {
        return false;
    }

    CanMsgToStr(stMsg,isRcvMsg,sMsg);
    sMsg += L"\n";//换行.
    //写入CAN消息记录
    fwrite(sMsg.c_bstr(),sMsg.Length()*sizeof(wchar_t),1,pCommFileHandle);

    if(++iFileLineCounter >= MAX_MSGS_SINGLE_FILE)
    {
        //关闭文件.
        fclose(pCommFileHandle);
        pCommFileHandle = NULL;
        iFileLineCounter = 0;
    }

    return true;
}


//写入历史记录文件
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

        //写入表头
        if(sHeader.IsEmpty())
        {
            InitFileRecordHeader(sHeader);
        }
        //写入BOM,以表明文件编码是Unicode.
        fwrite(BOM_Unicode,sizeof(BOM_Unicode),1,pCurFileHandle);
        fwrite(sHeader.c_bstr(),sHeader.Length()*sizeof(wchar_t),1,pCurFileHandle);
    }

    //写入记录
    WideString sRecord = "";
    T01SignalMatrixToStr(stInfo , sRecord);

    fwrite(sRecord.c_bstr(),sRecord.Length()*sizeof(wchar_t),1,pCurFileHandle);

    if(++iFileLineCounter >= MAX_RECORD_SINGLE_FILE)
    {
        //关闭文件.
        fclose(pCurFileHandle);
        pCurFileHandle = NULL;
        iFileLineCounter = 0;
    }

    return true;
}

/*
 *  记录整车报文的数据.
 */

WideString GetCAN0HeaderLine(void)
{
    const wchar_t * RecordHeader[] =
    {
        L"时间戳\t",//提示信息列.
        L"SOC(%)\t",
        L"总电压(V)\t",
        L"总电流(A)\t",
        // BMS故障状态.
        L"BMS告警级别\t",
        L"BMS故障码\t",
        // BMS充电命令.
        L"BMS充电命令\t",
        L"BMS充电状态\t",
        // 单体电压/温度极值
        L"BMS最高单体电压(mV)\t",
        L"BMS最低单体电压(mV)\t",
        L"电池最高温度(℃)\t",
        L"电池最低温度(℃)\t",
        // 车载充电机数据.
        L"车载充电机-温度状态\t",
        L"车载充电机-交流输入状态\t",
        L"车载充电机-直流输出状态\t",
        L"车载充电机-硬件状态\t",
        L"车载充电机-工作状态\t",
        L"车载充电机-输出电流\t",
        L"车载充电机-输出电压\t",
        // // BMS行车模式相关.
        L"MCU-母线电压(V)\t",
        L"VCU-主继电器命令\t",
        L"BMS-负极继电器反馈\t",
        L"BMS-正极继电器反馈\t",
        L"BMS-预充继电器反馈\t",
        L"BMS-工作模式请求\t",
        L"BMS-预充状态\t",
        L"BMS-预充错误指示\t",
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
    // 总电压.
    fTempValue = sigBuf.m_unBMS2.m_stBits.m_ullPackVolt;
    fTempValue *= 0.1;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";
    // 总电流.
    fTempValue = sigBuf.m_unBMS2.m_stBits.m_ullPackCurrent;
    fTempValue *= 0.1;
    fTempValue -= 500;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";

    // BMS告警级别.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS4.m_stBits.m_ullFaultCode) + L"\t";
    // BMS故障码.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS1.m_stBits.m_ullBMSAlarmLevel) + L"\t";
    // BMS充电命令.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS1.m_stBits.m_ullSlowChargeCmd) + L"\t";
    // BMS充电状态.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS1.m_stBits.m_ullBMSChargeSt) + L"\t";
    // BMS 最高单体电压.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS2.m_stBits.m_ullMaxCellVolt) + L"\t";
    // BMS 最低单体电压.
    sRecord += (WideString)IntToStr((u16)sigBuf.m_unBMS3.m_stBits.m_ullMinCellVolt) + L"\t";
    // 电池最高温度.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS3.m_stBits.m_ullMaxCellTemp-40) + L"\t";
    // 电池最低温度.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS3.m_stBits.m_ullMinCellTemp-40) + L"\t";
    // 车载充电机-温度状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCTempSt) + L"\t";
    // 车载充电机-交流输入状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCVoltInputSt) + L"\t";
    // 车载充电机-直流输出状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCVoltOutputSt) + L"\t";    
    // 车载充电机-硬件状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCHardwareSt) + L"\t";    
    // 车载充电机-工作状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unONC.m_stBits.m_ullACDCWorkingMode) + L"\t";
    // 车载充电机-输出电流.
    fTempValue = sigBuf.m_unONC.m_stBits.m_ullACDCOutputCurr;
    fTempValue *= 0.1;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";
    // 车载充电机-输出电压.
    fTempValue = sigBuf.m_unONC.m_stBits.m_ullACDCOutputVolt;
    fTempValue *= 0.1;
    sRecord += (WideString)FloatToStrF(fTempValue, ffFixed, 5, 1) + L"\t";

    // MCU母线电压.
    sRecord += (WideString)FloatToStrF((int)sigBuf.m_unMCU3.m_stBits.m_ullDrvMotorVolt * 0.01,ffFixed,6,2) + L"\t";
    // VCU主继电器操作命令.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unVCU1.m_stBits.m_ullVCU_MainRelayCmd) + L"\t";    
    // BMS-负极继电器状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullNegRelayFB) + L"\t";    
    // BMS-正极继电器状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPosRelayFB) + L"\t";    
    // BMS-预充继电器状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPreChRelayFB) + L"\t";    
    // BMS-工作模式请求
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullWorkModeReq) + L"\t";
    // BMS-预充结束状态.
    sRecord += (WideString)IntToStr((int)sigBuf.m_unBMS1.m_stBits.m_ullPreChComplete) + L"\t";
    // BMS-预充错误状态.
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

        //写入表头
        if(sHeader.IsEmpty())
        {
            sHeader = GetCAN0HeaderLine();
        }

        //写入BOM,以表明文件编码是Unicode.
        fwrite(BOM_Unicode,sizeof(BOM_Unicode),1,pCurFileHandle);
        fwrite(sHeader.c_bstr(),sHeader.Length()*sizeof(wchar_t),1,pCurFileHandle);
    }

    //写入记录
    WideString sRecord = "";
    T01CAN0SignalMatrixToStr(sigBuf , sRecord);

    fwrite(sRecord.c_bstr(),sRecord.Length()*sizeof(wchar_t),1,pCurFileHandle);

    if(++iFileLineCounter >= MAX_RECORD_SINGLE_FILE)
    {
        //关闭文件.
        fclose(pCurFileHandle);
        pCurFileHandle = NULL;
        iFileLineCounter = 0;
    }

    return true;        
}
