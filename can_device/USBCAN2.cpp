#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <queue> //STL容器--队列
#include <vector>
#include "ControlCAN.h"
#include "USBCAN2.h"

//接口函数指针
LPVCI_OpenDevice VCI_OpenDevice;
LPVCI_CloseDevice VCI_CloseDevice;
LPVCI_InitCan VCI_InitCAN;
LPVCI_ReadBoardInfo VCI_ReadBoardInfo;
LPVCI_ReadErrInfo VCI_ReadErrInfo;
LPVCI_ReadCanStatus VCI_ReadCanStatus;
LPVCI_GetReference VCI_GetReference;
LPVCI_SetReference VCI_SetReference;
LPVCI_GetReceiveNum VCI_GetReceiveNum;
LPVCI_ClearBuffer VCI_ClearBuffer;
LPVCI_StartCAN VCI_StartCAN;
LPVCI_ResetCAN VCI_ResetCAN;
LPVCI_Transmit VCI_Transmit;
LPVCI_Receive VCI_Receive;
LPVCI_GetReference2 VCI_GetReference2;
LPVCI_SetReference2 VCI_SetReference2;
LPVCI_ResumeConfig VCI_ResumeConfig;
LPVCI_ConnectDevice VCI_ConnectDevice;
LPVCI_UsbDeviceReset VCI_UsbDeviceReset;
LPVCI_FindUsbDevice VCI_FindUsbDevice;

const BitRatesCfg_ST CANDEV_USBCAN2::BitRateCfg[] ={

    {10000  , 0x9F,0xFF},//10K
    {20000  , 0x18,0x1C},//20K
    {40000  , 0x87,0xFF},//40K
    {50000  , 0x09,0x1C},//50K
    {80000  , 0x83,0xFF},//80K
    {100000 , 0x04,0x1C},//100K
    {125000 , 0x03,0x1C},//125K
    {200000 , 0x81,0xFA},//250K
    {250000 , 0x01,0x1C},//500K
    {400000 , 0x80,0xFA},//400K
    {500000 , 0x00,0x1C},//500K
    {666000 , 0x80,0xB6},//666K
    {800000 , 0x00,0x16},//800K
    {1000000, 0x00,0x14},//1000K
};

const char * CANDEV_USBCAN2::chNames[] =
{
    "CAN1",
    "CAN2"
};

//初始化上述函数指针

static HMODULE m_hDLL = NULL;//用来保存打开的动态库句柄

void InitUSBCAN2DLL(AnsiString &sDllName)
{
    if(m_hDLL != NULL)
    {
        DestoryUSBCAN2DLL();
    }

    UnicodeString s = sDllName;

    m_hDLL = LoadLibrary(s.c_str());//打开动态库
    
    if(m_hDLL == NULL)
    {
        AnsiString s = "无法打开动态库文件" + sDllName;
        throw s;
    }
    //取得函数地址
    VCI_OpenDevice=(LPVCI_OpenDevice)::GetProcAddress(m_hDLL,"VCI_OpenDevice");
    VCI_CloseDevice=(LPVCI_CloseDevice)::GetProcAddress(m_hDLL,"VCI_CloseDevice");
    VCI_InitCAN=(LPVCI_InitCan)::GetProcAddress(m_hDLL,"VCI_InitCAN");
    VCI_ReadBoardInfo=(LPVCI_ReadBoardInfo)::GetProcAddress(m_hDLL,"VCI_ReadBoardInfo");
    VCI_ReadErrInfo=(LPVCI_ReadErrInfo)::GetProcAddress(m_hDLL,"VCI_ReadErrInfo");
    VCI_ReadCanStatus=(LPVCI_ReadCanStatus)::GetProcAddress(m_hDLL,"VCI_ReadCANStatus");
    VCI_GetReference=(LPVCI_GetReference)::GetProcAddress(m_hDLL,"VCI_GetReference");
    VCI_SetReference=(LPVCI_SetReference)::GetProcAddress(m_hDLL,"VCI_SetReference");
    VCI_GetReceiveNum=(LPVCI_GetReceiveNum)::GetProcAddress(m_hDLL,"VCI_GetReceiveNum");
    VCI_ClearBuffer=(LPVCI_ClearBuffer)::GetProcAddress(m_hDLL,"VCI_ClearBuffer");
    VCI_StartCAN=(LPVCI_StartCAN)::GetProcAddress(m_hDLL,"VCI_StartCAN");
    VCI_ResetCAN=(LPVCI_ResetCAN)::GetProcAddress(m_hDLL,"VCI_ResetCAN");
    VCI_Transmit=(LPVCI_Transmit)::GetProcAddress(m_hDLL,"VCI_Transmit");
    VCI_Receive=(LPVCI_Receive)::GetProcAddress(m_hDLL,"VCI_Receive");

    VCI_GetReference2=(LPVCI_GetReference2)GetProcAddress(m_hDLL,"VCI_GetReference2");
    VCI_SetReference2=(LPVCI_SetReference2)GetProcAddress(m_hDLL,"VCI_SetReference2");
    VCI_ResumeConfig=(LPVCI_ResumeConfig)GetProcAddress(m_hDLL,"VCI_ResumeConfig");
    VCI_ConnectDevice=(LPVCI_ConnectDevice)GetProcAddress(m_hDLL,"VCI_ConnectDevice");
    VCI_UsbDeviceReset=(LPVCI_UsbDeviceReset)GetProcAddress(m_hDLL,"VCI_UsbDeviceReset");

}

void DestoryUSBCAN2DLL(void)
{
    if(m_hDLL != NULL)
    {
        FreeLibrary(m_hDLL);
        m_hDLL = NULL;
    }
}

bool CANDEV_USBCAN2::SetParams(unsigned char _channel,int _baudRate )//设置参数
{
    VCI_INIT_CONFIG stDevCfg;
    int i;
    for(i = 0 ;i < sizeof(BitRateCfg)/sizeof(BitRateCfg[0]);i++)
    {
        if(_baudRate == BitRateCfg[i].baudRate)
        {
            break;
        }
    }

    if(i >= sizeof(BitRateCfg)/sizeof(BitRateCfg[0]))
    {
        return false;//未找到支持的速率
    }

    if(_channel >= 2)
    {
        return false;//只有两个通道
    }

    m_devCh =  _channel;
    m_baudRate = _baudRate;

    stDevCfg.AccCode = 0x00000000;
    stDevCfg.AccMask = 0xFFFFFFFF;
    stDevCfg.Filter = 0;//接收全部数据
    stDevCfg.Mode = 0;

    stDevCfg.Timing0 = BitRateCfg[i].timer0;
    stDevCfg.Timing1 = BitRateCfg[i].timer1;

    //打开通道.
    if( VCI_InitCAN(m_devtype,m_devind,m_devCh,&stDevCfg)!= 1)
    {
        return false;//初始化失败.
    }

    ::Sleep(100);//暂停100ms让设备初始化完成.

    return true;
}

bool CANDEV_USBCAN2::OpenDevice(AnsiString &errStr, unsigned char _channel , int _baudRate0 , int _baudRate1)    //打开设备
{
    int i;

    if(bIsOpen != false)
    {
        //关闭设备
        errStr = "设备已经打开";
        return true;
    }

    for(i = 0 ; i < 4 ; i++)
    {
        int res = VCI_OpenDevice(m_devtype, i ,0x1388);
        if( res == 1) //搜到到设备了.
        {
            break;
        }
    }
    
    if( i >= 4)
    {
        errStr = "未搜索到设备";
        return false;
    }

    m_devind = i;//设备索引号
    m_devCh = _channel;

    //VCI_ResetCAN(m_devtype,m_devind,m_devCh);

    //::Sleep(100);//让设备完成复位.

    //打开通道0
    if(SetParams(_channel,_baudRate0) == false)
    {
        errStr = "设置通道1参数失败";
        return false;
    }

    //打开通道1.
    /*if(SetParams(1,_baudRate1) == false)
    {
        errStr = "设置通道2参数失败";
        return false;
    }*/

    if( VCI_StartCAN(m_devtype,m_devind,m_devCh) != 1)
    {
        return false;//启动失败.
    }

    /*
    if( VCI_StartCAN(m_devtype,m_devind,1) != 1)
    {
        return false;//启动失败.
    }
    */

    bIsOpen = true;
    errStr = "打开成功";

    m_iNameIdx =  _channel;

    return true;
}

bool CANDEV_USBCAN2::CloseDevice(AnsiString &errStr)  //关闭设备
{
    if(bIsOpen == false)
        return true;
    bIsOpen = false;
    VCI_CloseDevice(m_devtype,m_devind);
    return true;
}

bool CANDEV_USBCAN2::HwSendMsg(std::vector<CanMsgST>& vMsgs)
{
    return false;
}

bool CANDEV_USBCAN2::HwSendMsg(const CanMsgST &stMsg)                 //发送消息
{
    VCI_CAN_OBJ stToSnd;
    u8 ucChannel;
    if(bIsOpen == false)
    {
        return false;
    }

    stToSnd.ID = stMsg.m_iCANID;
    stToSnd.DataLen = (stMsg.m_ucLength >= 8)? 8:stMsg.m_ucLength;
    ::memcpy(stToSnd.Data,stMsg.m_aucData,stToSnd.DataLen);
    stToSnd.RemoteFlag = 0;//正常数据帧
    stToSnd.ExternFlag = stMsg.m_ExtFlag & 0x01;//0标准帧，1扩展帧.
    stToSnd.SendType = 0; // 默认填0.兼容ZLG USB CAN

    // ucChannel = stMsg.m_ucChannel;
    
    if( ucChannel >= 2) //确定通道.
    {
        ucChannel = 1;
    }

    if( VCI_Transmit(m_devtype,m_devind,m_devCh,&stToSnd,1) != 1)
    {
        return false;
    }
    
    return true;
}

int CANDEV_USBCAN2::HwRcvMsg(std::vector<CanMsgST> &v)    //接收消息
{
    VCI_ERR_INFO errinfo;
    CanMsgST stMsg;

    if(bIsOpen == false)
    {
        return -1;
    }
    
    int ilen = (int)VCI_Receive(m_devtype,m_devind,m_devCh,m_pvciRcvBuf,100,5);//超时时间,10ms.

    if(ilen <= 0)
    {
        VCI_ReadErrInfo(m_devtype,m_devind,0 ,&errinfo);
    }
    else
    {
        for(int i = 0;i < ilen ;i ++)
        {
            stMsg.m_iCANID = (int)m_pvciRcvBuf[i].ID;
            stMsg.m_ucLength = (m_pvciRcvBuf[i].DataLen > 8 ) ? 8: m_pvciRcvBuf[i].DataLen ;
            stMsg.m_ExtFlag =  m_pvciRcvBuf[i].ExternFlag;
            stMsg.m_ucChannel = m_devCh;
            memcpy(stMsg.m_aucData,m_pvciRcvBuf[i].Data,stMsg.m_ucLength);
            v.push_back(stMsg); //增加到接收区域.
        }
    }

    return ilen;
}

void CANDEV_USBCAN2::ConnectionInfo(AnsiString & s)
{
    if(this->IsDeviceOpen() == false)
        s = "无连接";
    else
    {
        s = "" ;
        s += AnsiString(chNames[m_iNameIdx]);
        s += "," ;
        s += IntToStr(this->m_baudRate/1000);
        s += "kbps";
    }
}
