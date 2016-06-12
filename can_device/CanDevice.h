#ifndef _CANDEVICE_H__
#define _CANDEVICE_H__

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <vcl.h>

#if 0
#pragma warn -8057
#pragma warn -8012
#pragma warn -8123
#endif

#include <queue> //STL--队列
#include <vector>//STL--向量
#include <iterator>
using namespace std;

#define CAN_DATA_LEN 8


typedef enum CanDevType
{
     //上位机能支持的CAN设备类型

     DevType_USBCAN2,           //DSP studio的USBCAN2接口
     DevType_ValueCAN3,       //暂不添加对ValueCAN3的支持.

}CanDevType;

typedef struct CanMsgST
{
    int m_iCANID;
    unsigned char m_aucData[CAN_DATA_LEN];
    unsigned char m_ucLength;
    unsigned char m_ExtFlag;//是否扩展帧.
    unsigned char m_ucChannel;//消息通道号.
    TSystemTime m_stTime;   //时间戳.
    
}CanMsgST;

//抛出异常用.
class UnimplentmentedExecption
{
public :
    static void ThrowException_Zh()
    {
        AnsiString s = "未实现的方法";
        throw s;
    };

    static void ThrowException_En()
    {
        AnsiString s = "Unimplentmented Methods";
        throw s;
    };

    static void ThrowException(int languas = 0)
    {
        if(languas != 0)
            ThrowException_En();
        else
            ThrowException_Zh();
    }
} ;
/*
class CANDevice;//前置声明

class TMyThread : public TThread
{
protected:
    CANDevice *pToExecute;
    virtual void __fastcall Execute();
public:
    bool TermMyThread ;

    __fastcall TMyThread( CANDevice *pdev): TThread(true)
    {
        pToExecute = pdev ;
        TermMyThread = false;
    }
};
*/

class CANDevice
{
public:
    //通信速率-目前支持这几种即可.
    static const int BaudRateList[6];

protected :
    bool bIsOpen; //接口打开状态
    int iTicks;   //状态机需要使用的计数器

    HANDLE m_handle_thread;

    //TMyThread *thrd ;//接收线程.

    CanDevType DeviceType;
    int iBaudRate;//CAN通信速率
    unsigned char ucChannel; //CAN通信通道选择
    std::queue < CanMsgST > SndQueue;  //等待发送的消息队列
    std::queue < CanMsgST > RcvQueue;  //接收消息的暂存队列
    std::queue < AnsiString> EventQueue;//异常事件消息存放在这里，用于调试.

    int iErrorCounts; // CAN错误次数.

    virtual bool HwSendMsg(std::vector<CanMsgST>& vMsgs) //发送消息
    {
         UnimplentmentedExecption::ThrowException();
         return false;
    }
    virtual bool HwSendMsg(const CanMsgST &stMsg)           //发送消息
    {
         UnimplentmentedExecption::ThrowException();
         return false;
    }

    virtual int  HwRcvMsg(std::vector<CanMsgST>& vMsgs) //接收消息
    {
         UnimplentmentedExecption::ThrowException();
         return false;
    }
    
    void DbgMsg(AnsiString &_dbgMsg)
    {
        EventQueue.push(_dbgMsg);
    }
public:

    unsigned char GetChannel(){return ucChannel;}
    int GetBaudRate(){return iBaudRate;}
    int IsDeviceOpen(){return bIsOpen;}
    int GetErrCnt(void){return iErrorCounts;}

    CANDevice(CanDevType _devType, unsigned char _channel = 0, int _baudRate = 500000) //构造函数
        :DeviceType(_devType),ucChannel(_channel),iBaudRate(_baudRate),bIsOpen(false),iErrorCounts(0)
    {
        //thrd = new TMyThread(this);
        //thrd->Resume();
    }                           

    ~CANDevice() //析构函数
    {
        //thrd->TermMyThread = true;
        //thrd->WaitFor();
        //delete thrd;
    }

    virtual bool SetParams(unsigned char _channel,int _baudRate);//设置参数
    virtual bool OpenDevice(AnsiString &errStr, unsigned char _channel = 0, int _baudRate = 500000, int _baudRate1 = 500000);    //打开设备
    virtual bool CloseDevice(AnsiString &errStr);  //关闭设备
    virtual void SndMsg(std::vector<CanMsgST> & vMsg); //用户使用的发送方法
    virtual void SndMsg(const CanMsgST & msg); //用户使用的发送方法
    virtual void GetMsg(std::vector<CanMsgST> & v);    //用户使用的接收方法
    void GetEventMsg(std::vector<AnsiString> &v);     //查询调试消息用.

    void DriverThread(void);//发送--接收消息
    virtual void ConnectionInfo(AnsiString &s) { s = "无连接"; }
};

void GetMsgTimeStr(const CanMsgST & stMsg, AnsiString &s);
void SetMsgTime(CanMsgST & stMsg);

#endif
