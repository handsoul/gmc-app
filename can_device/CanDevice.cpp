#include "CanDevice.h"
#include "DataProc.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <queue> //STL����--����
#include <vector>


const int CANDevice::BaudRateList[6]=
{
    100000,
    250000,
    200000,
    400000,
    500000,
    1000000,
};

bool CANDevice::SetParams(unsigned char _channel,int _baudRate)//���ò���
{
      UnimplentmentedExecption::ThrowException();
      return false;
}
    
bool CANDevice::OpenDevice(AnsiString &errStr, unsigned char _channel, int baudRate , int baudRate1)//���豸
{
      UnimplentmentedExecption::ThrowException();
      return false;
}
    
bool CANDevice::CloseDevice(AnsiString &errStr)  //�ر��豸
{
      UnimplentmentedExecption::ThrowException();
      return false;
}

void CANDevice::SndMsg(std::vector<CanMsgST> & vMsg) //�û�ʹ�õķ��ͷ���
{
    std::vector<CanMsgST>::iterator it;
    for(it = vMsg.begin();it != vMsg.end(); ++ it)
    {
        SndQueue.push(*it);
    }
}

void CANDevice::SndMsg(const CanMsgST & msg)
{
    SndQueue.push(msg);
}

void CANDevice::GetMsg(std::vector<CanMsgST> & v)    //�û�ʹ�õĽ��շ���
{
    if(this->IsDeviceOpen() == false)
        return;

    while(! RcvQueue.empty())
    {
        v.push_back(RcvQueue.front());
        RcvQueue.pop();
    }
}

void CANDevice::GetEventMsg(std::vector<AnsiString> &v)     //��ѯ������Ϣ��.
{
    if(this->IsDeviceOpen() == false)
        return;
    while(!EventQueue.empty())
    {
        v.push_back(EventQueue.front());
        EventQueue.pop();
    }
}


void CANDevice::DriverThread(void)
{
    std::vector<CanMsgST> v;
    std::vector<CanMsgST>::iterator it;

    if(this->IsDeviceOpen() == false)
    {
        //Sleep(5);//�豸�رյĻ���ÿ������5ms.
        return;
    }
    //ÿ��ֻ����һ��
    while( this->SndQueue.size() > 0 )
    {
        HwSendMsg(SndQueue.front());
        SndQueue.pop();
    }

    this->HwRcvMsg(v);

    if(v.size() > 0)
    {
        for(it = v.begin();it != v.end(); ++ it)
        {
            SetMsgTime(*it);
            this->RcvQueue.push(*it);
        }
    }
}

/*
void __fastcall TMyThread::Execute()
{
    while((TermMyThread == false) && (pToExecute != NULL))
    {
        try
        {
            pToExecute->DriverThread();

        }
        __finally
        {
            //do nothing.
        }
    }
}
*/

void SetMsgTime(CanMsgST & stMsg)
{
    GetLocalTime(&stMsg.m_stTime);
}

void GetMsgTimeStr(const CanMsgST & stMsg, AnsiString &s)
{
    s = "";
    s.sprintf("%02d:%02d:%02d:%03d",
        stMsg.m_stTime.wHour,
        stMsg.m_stTime.wMinute,
        stMsg.m_stTime.wSecond,
        stMsg.m_stTime.wMilliseconds
        );
}
