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

#include <queue> //STL--����
#include <vector>//STL--����
#include <iterator>
using namespace std;

#define CAN_DATA_LEN 8


typedef enum CanDevType
{
     //��λ����֧�ֵ�CAN�豸����

     DevType_USBCAN2,           //DSP studio��USBCAN2�ӿ�
     DevType_ValueCAN3,       //�ݲ���Ӷ�ValueCAN3��֧��.

}CanDevType;

typedef struct CanMsgST
{
    int m_iCANID;
    unsigned char m_aucData[CAN_DATA_LEN];
    unsigned char m_ucLength;
    unsigned char m_ExtFlag;//�Ƿ���չ֡.
    unsigned char m_ucChannel;//��Ϣͨ����.
    TSystemTime m_stTime;   //ʱ���.
    
}CanMsgST;

//�׳��쳣��.
class UnimplentmentedExecption
{
public :
    static void ThrowException_Zh()
    {
        AnsiString s = "δʵ�ֵķ���";
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
class CANDevice;//ǰ������

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
    //ͨ������-Ŀǰ֧���⼸�ּ���.
    static const int BaudRateList[6];

protected :
    bool bIsOpen; //�ӿڴ�״̬
    int iTicks;   //״̬����Ҫʹ�õļ�����

    HANDLE m_handle_thread;

    //TMyThread *thrd ;//�����߳�.

    CanDevType DeviceType;
    int iBaudRate;//CANͨ������
    unsigned char ucChannel; //CANͨ��ͨ��ѡ��
    std::queue < CanMsgST > SndQueue;  //�ȴ����͵���Ϣ����
    std::queue < CanMsgST > RcvQueue;  //������Ϣ���ݴ����
    std::queue < AnsiString> EventQueue;//�쳣�¼���Ϣ�����������ڵ���.

    int iErrorCounts; // CAN�������.

    virtual bool HwSendMsg(std::vector<CanMsgST>& vMsgs) //������Ϣ
    {
         UnimplentmentedExecption::ThrowException();
         return false;
    }
    virtual bool HwSendMsg(const CanMsgST &stMsg)           //������Ϣ
    {
         UnimplentmentedExecption::ThrowException();
         return false;
    }

    virtual int  HwRcvMsg(std::vector<CanMsgST>& vMsgs) //������Ϣ
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

    CANDevice(CanDevType _devType, unsigned char _channel = 0, int _baudRate = 500000) //���캯��
        :DeviceType(_devType),ucChannel(_channel),iBaudRate(_baudRate),bIsOpen(false),iErrorCounts(0)
    {
        //thrd = new TMyThread(this);
        //thrd->Resume();
    }                           

    ~CANDevice() //��������
    {
        //thrd->TermMyThread = true;
        //thrd->WaitFor();
        //delete thrd;
    }

    virtual bool SetParams(unsigned char _channel,int _baudRate);//���ò���
    virtual bool OpenDevice(AnsiString &errStr, unsigned char _channel = 0, int _baudRate = 500000, int _baudRate1 = 500000);    //���豸
    virtual bool CloseDevice(AnsiString &errStr);  //�ر��豸
    virtual void SndMsg(std::vector<CanMsgST> & vMsg); //�û�ʹ�õķ��ͷ���
    virtual void SndMsg(const CanMsgST & msg); //�û�ʹ�õķ��ͷ���
    virtual void GetMsg(std::vector<CanMsgST> & v);    //�û�ʹ�õĽ��շ���
    void GetEventMsg(std::vector<AnsiString> &v);     //��ѯ������Ϣ��.

    void DriverThread(void);//����--������Ϣ
    virtual void ConnectionInfo(AnsiString &s) { s = "������"; }
};

void GetMsgTimeStr(const CanMsgST & stMsg, AnsiString &s);
void SetMsgTime(CanMsgST & stMsg);

#endif
