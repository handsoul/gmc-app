#ifndef __VALUE_CAN3_H__
#define __VALUE_CAN3_H__

#include "CanDevice.h"
#include "icsnVC40.h"
#include "icsneo40DLLAPI.h" // API头文件

// ValueCAN3的设备类实现.
class ValueCAN3:public CANDevice
{

private:
    int m_hObject;		 //handle for device
    bool m_bPortOpen;
    int m_iDevCh;
    int m_iMSORHS;
protected :
    bool HwSendMsg(std::vector<CanMsgST>& vMsgs);
    bool HwSendMsg(const CanMsgST &stMsg);
    int  HwRcvMsg(std::vector<CanMsgST>& vMsgs);
public:
    bool SetParams(unsigned char _channel,int _baudRate);   //设置参数
    bool OpenDevice(AnsiString &errStr,
                            unsigned char _channel = 0,
                            int _baudRate0 = 500000,
                            int _baudRate1 = 500000);       //打开设备
    bool CloseDevice(AnsiString &errStr);                   //关闭设备
    void ConnectionInfo(AnsiString &s){s = "";}

    ValueCAN3(): CANDevice(DevType_ValueCAN3,0), m_hObject(0),m_bPortOpen(false),m_iDevCh(0),m_iMSORHS(NETID_HSCAN)
    {}
};

bool InitValueCanDLL(void);

#endif
