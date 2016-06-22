#ifndef __CAN_FRAME_H__
#define __CAN_FRAME_H__

#include "DataProc.h"
#include "CanDevice.h"

typedef struct tagCANIDUN
{
		//bits[24:31]                                                        内存地址
		u32 m_btProtoNO : 5;    // [24:28]: 协议号(协议类型)            --->  0x0000
		u32 m_btRsv3V0  : 3;    // [29:31]: 保留位(填充0)                        |
		//bits[16:23]                                                            |
		u32 m_btDstAddr : 8;    // [16:23]: 目标节点地址                --->  0x0001
		//bits[8:15]                                                             |
		u32 m_btCmdID   : 8;    // [8:15]:  命令ID                      --->  0x0002
		//bits[0:7]                                                              |
		u32 m_btCntFlag : 1;    // [0]:     CNT位(0: 最后1帧, 1: 还有下1帧)      |
		u32 m_btRsv6V1  : 6;    // [1:6]:   保留位(填充1)               --->  0x0003
		u32 m_btMsgDir  : 1;    // [7]:     消息方向(0: S->M, 1: M->S)

}CAN_ID_UN;




#endif
// end of file
