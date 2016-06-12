#include "ValueCan3.h"
#include <vcl.h>


//加载DLL.

static HINSTANCE hDLL = 0;

bool InitValueCanDLL(void)
{
    if(hDLL == 0)
    {
        if(LoadDLLAPI(hDLL) == true)
        {
            return true;
        }
        else
        {
            hDLL = 0;
            return false;
        }
    }

    return true;
}

bool ValueCAN3::OpenDevice(AnsiString &errStr,unsigned char _channel,int _baudRate0,int _baudRate1)
{
    // 一共两个通道.
    int iResult;
    int iNumOfDevices;
    NeoDevice ndNeoToOpen;

    if (bIsOpen == true)
    {
        errStr = "打开成功";
        return true;
    }

    m_iDevCh = _channel;

    if (m_iDevCh > 2)
    {
        return false;
    }


    if(_channel == 0)
    {
        m_iMSORHS = NETID_HSCAN;
    }
    else if(_channel == 1)
    {
        m_iMSORHS = NETID_MSCAN;
    }


    iNumOfDevices = 1;

    iResult = icsneoFindNeoDevices(65535,&ndNeoToOpen, &iNumOfDevices);

    if(iResult == 0 || iNumOfDevices == 0)
    {
        errStr = "未搜索到ValueCan3设备";
        return false;
    }


    iResult = icsneoOpenNeoDevice(&ndNeoToOpen, &m_hObject, NULL, 1, 0);

    if(iResult == 0)
    {
        errStr = "设备无法打开,请检查其他应用程序是否正在使用ValueCAN3";
        return false;
    }


    // 可以读取序列号.
    bIsOpen = true;

    // 设置波特率.
    SetParams(m_iDevCh,_baudRate0);

    iErrorCounts = 0;//错误计数器清零.

    return true;
}

bool ValueCAN3::SetParams(unsigned char _channel,int _baudRate)
{
    int networkID ;

    if (_baudRate != 250000 &&
        _baudRate != 400000 &&
                _baudRate != 500000 &&
                _baudRate != 1000000)
    {
        return false;
    }

    if(_channel == 0)
    {
        networkID = NETID_HSCAN;
    }
    else if(_channel == 1)
    {
        networkID = NETID_MSCAN;
    }
    else
    {
        return false;
    }

    return (icsneoSetBitRate(m_hObject,_baudRate,networkID) == 1);
}


bool ValueCAN3::CloseDevice(AnsiString &errStr)
{
    int iNumOfErrs;

    if( bIsOpen == true)
    {
        icsneoClosePort(m_hObject,&iNumOfErrs);
        bIsOpen = false;

        errStr = "设备关闭成功";
    }
    else
    {
        errStr = "设备未打开";
    }

    return true;
}


bool ValueCAN3::HwSendMsg(std::vector<CanMsgST>& vMsgs)
{
    return false;
}

bool ValueCAN3::HwSendMsg(const CanMsgST &stMsg)
{
    if(bIsOpen == false)
    {
        return false;
    }

    icsSpyMessage vMsg;

    if( stMsg.m_ucChannel >= 2)
    {
        return false;
    }

    vMsg.NetworkID = (m_iDevCh == 0)?NETID_HSCAN:NETID_MSCAN;
    vMsg.ArbIDOrHeader = stMsg.m_iCANID;
    vMsg.NumberBytesData = (stMsg.m_ucLength >= 8) ? 8: stMsg.m_ucLength;
    memcpy(vMsg.Data,stMsg.m_aucData,vMsg.NumberBytesData);
    vMsg.StatusBitField = (stMsg.m_ExtFlag > 0)?SPY_STATUS_XTD_FRAME:0;

    int result =  icsneoTxMessages(m_hObject,&vMsg,vMsg.NetworkID,1);

    return result;
}

int  ValueCAN3::HwRcvMsg(std::vector<CanMsgST>& vMsgs)
{
    static  icsSpyMessage astMsgs[20000];
    CanMsgST stMsg;
    int count;
    int errors;
    int result;
    int networkID;

    if(bIsOpen == false)
    {
        return 0;
    }
    // 读取消息并过滤消息.

    result = icsneoGetMessages(m_hObject, astMsgs, &count, &errors);

    if(result != 1)   // 返回错误.
    {
        return 0;
    }

    vMsgs.clear();

    for(int i = 0 ;i < count;i++)
    {
        if(astMsgs[i].Protocol != SPY_PROTOCOL_CAN)   // 非CAN协议消息过滤.
        {
            continue;
        }
        else if(astMsgs[i].StatusBitField & SPY_STATUS_TX_MSG) // 发送消息过滤.
        {
            continue;
        }
        else if(astMsgs[i].StatusBitField & SPY_STATUS_GLOBAL_ERR) //CAN错误过滤.
        {
            ++iErrorCounts;//CAN错误帧计数器.
            continue;
        }
        else if (m_iMSORHS != astMsgs[i].NetworkID) // ID非当前选中CAN通道
        {
            continue;
        }

        stMsg.m_iCANID = astMsgs[i].ArbIDOrHeader;
        stMsg.m_ucLength = (astMsgs[i].NumberBytesData > 8)? 8: astMsgs[i].NumberBytesData;
        memcpy(stMsg.m_aucData,astMsgs[i].Data,stMsg.m_ucLength);
        stMsg.m_ucChannel = (astMsgs[i].NetworkID == NETID_HSCAN) ? 0:1;
        networkID =  astMsgs[i].NetworkID;

        stMsg.m_ExtFlag = ((astMsgs[i].StatusBitField & SPY_STATUS_XTD_FRAME) > 0);
        vMsgs.push_back(stMsg);
    }


    return 0;
}
