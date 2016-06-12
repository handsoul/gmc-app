#ifndef __USBCAN2_H__
#define __USBCAN2_H__

#include "DataProc.h"//���Ͷ���
#include "CanDevice.h"
#include "ControlCAN.h"

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vcl.h>
#include <queue> //STL����--����
#include <vector>

typedef struct tagBitRates
{
    int baudRate;
    unsigned char timer0;
    unsigned char timer1;
    
}BitRatesCfg_ST;

class CANDEV_USBCAN2 : public CANDevice
{

public :
    static const int DEV_USBCAN2    = 4;
    static const int PortsNum       = 2;//2���˿�.��0��ʼ
    static const BitRatesCfg_ST BitRateCfg[];//������������Ϣ
    static const char * chNames[];
protected:
   
    u32 m_devtype;//USBCAN2���ͺ�
    u32 m_devind;
    u32 m_devCh;
    int m_baudRate;
    VCI_CAN_OBJ m_pvciRcvBuf[100]; //���ջ���������СΪ100.
    int m_iNameIdx;

    bool HwSendMsg(std::vector<CanMsgST>& vMsgs);   //������Ϣ
    bool HwSendMsg(const CanMsgST &stMsg);          //������Ϣ
    int  HwRcvMsg(std::vector<CanMsgST>& vMsgs);    //������Ϣ
public :

    virtual bool SetParams(unsigned char _channel,int _baudRate);//���ò���
    virtual bool OpenDevice(AnsiString &errStr, unsigned char _channel = 0,int _baudRate0 = 500000 , int _baudRate1 = 500000);    //���豸
    virtual bool CloseDevice(AnsiString &errStr);  //�ر��豸
    virtual void ConnectionInfo(AnsiString & s);

    CANDEV_USBCAN2():CANDevice(DevType_USBCAN2,0)
    {
       m_devtype = DEV_USBCAN2;
       m_devind = 0;
       m_devCh  = 0;
       m_iNameIdx = 0;

       //m_pvciRcvBuf = new
    }
    
    ~CANDEV_USBCAN2()
    {
        //delete m_pvciRcvBuf;//ɾ��.
    }
};


void InitUSBCAN2DLL(AnsiString &sDllName);
void DestoryUSBCAN2DLL(void);

#endif//__USBCAN2_H__
