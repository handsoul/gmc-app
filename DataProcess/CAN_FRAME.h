#ifndef __CAN_FRAME_H__
#define __CAN_FRAME_H__

#include "DataProc.h"
#include "CanDevice.h"

typedef struct tagCANIDUN
{
		//bits[24:31]                                                        �ڴ��ַ
		u32 m_btProtoNO : 5;    // [24:28]: Э���(Э������)            --->  0x0000
		u32 m_btRsv3V0  : 3;    // [29:31]: ����λ(���0)                        |
		//bits[16:23]                                                            |
		u32 m_btDstAddr : 8;    // [16:23]: Ŀ��ڵ��ַ                --->  0x0001
		//bits[8:15]                                                             |
		u32 m_btCmdID   : 8;    // [8:15]:  ����ID                      --->  0x0002
		//bits[0:7]                                                              |
		u32 m_btCntFlag : 1;    // [0]:     CNTλ(0: ���1֡, 1: ������1֡)      |
		u32 m_btRsv6V1  : 6;    // [1:6]:   ����λ(���1)               --->  0x0003
		u32 m_btMsgDir  : 1;    // [7]:     ��Ϣ����(0: S->M, 1: M->S)

}CAN_ID_UN;




#endif
// end of file
