#ifndef __PARSER_H__
#define __PARSER_H__

// reference type definition.
#include "DataType.h"

// command seperator char
#define CMD_SEPARATOR           '/'
#define END_CHAR                '\0'

#define SIG_PREFIX          'M'
#define POS_PREFIX          'M'

#define CMD_INTERNAL_SEPERATOR  '-'

#define CMD_BUFSIZE             20
#define CMD_CHAIN_MAX_LEN       20
#define SYS_RESOURCE_MAX_LEN    20

// extra options.
#define DEBUG_CMD

#ifdef DEBUG_CMD
#define ERRINFO(format...) \
    fprintf(stderr,format)
#else
    #define ERRINFO(format...)
#endif

//#define VERBOSE_PRINT

#ifdef VERBOSE_PRINT
#define TRACE_PRINT ERRINFO
#else
#define TRACE_PRINT(format...)
#endif

// ��Դ����: ��������.
typedef struct tagResourceItemDI
{
    u8  m_ucIndex;
    s32 m_slvalue;
}R_DI;

// ��Դ����: �������.
typedef struct tagResourceItemDO
{
    u8  m_ucIndex;
    s32 m_slvalue;
}R_DO;

// ��Դ����: ģ������.
typedef  struct tagResourceAI
{
    u8  m_ucIndex;
    s32 m_slvalue;
}R_AI;

// ��Դ����: ģ�����.
typedef  struct tagResourceAO
{
    u8  m_ucIndex;
    s32 m_slvalue;
}R_AO;

// ��Դ���Ͷ���.
typedef struct tagRItem
{
    u8 m_ucRType;
    union
    {
        R_DI m_unR_DI;
        R_DO m_unR_DO;
        R_AI m_unR_AI;
        R_AO m_unR_AO;
    };
}RESOURCE_ITEM;


// �������� - ����1 - ������������.
typedef struct tagCmd_R1
{
    s32 m_slPos;
}CMD_R1_ST;

// �������� - ����2 - �����������.
typedef struct tagCmd_R2
{
    s32 m_slPos;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_R2_ST;

// ��������  - ����3 - ���е��Ĵ���λ��.
typedef struct tagCMD_R3
{
    u8 m_ucRegNo;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_R3_ST;

// �������� - ����4 - ���е�ԭ��.
typedef struct tagCMD_R4
{
    u8 m_ucReserved;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_R4_ST;

// �ٶ�����ָ�� - ����һ���������ٶ�
typedef struct tagCMD_P
{
    u8 m_ucSpeedIndex;
    s32 m_slSpeed;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_P_ST;

// �ź��������� - �����ź�Ϊ��
typedef struct tagCMD_SL
{
    u8 m_ucSigIndex;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_SL_ST;

// �ź��������� - �����ź�Ϊ��
typedef struct tagCMD_SH
{
    u8 m_ucSigIndex;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_SH_ST;

// �źŲ�ѯ����(��������). ��ѯ�ź�Ϊ����ִ��
typedef struct tagCMD_IL
{
    u8 m_ucSigIndex;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_IL_ST;

// �źŲ�ѯ����(��������). ��ѯ�ź�Ϊ����ִ��
typedef struct tagCMCD_IH
{
    u8 m_ucSigIndex;
#ifdef DEBUG_CMD
    s8  m_ascStr[CMD_BUFSIZE];
#endif
}CMD_IH_ST;

// ˼·: command.

// ִ����.
// ִ�нڵ�: ���� + ����

typedef struct tagConditonSig
{
    u8 m_iRid;
    s32 m_iTriggleValue;
}CONDITION_SIG_ST;

typedef struct tagConditonPos
{
    s32 m_slPos;
    s32 m_slOffset;
    u8  m_ucRelation;
}CONDITION_POS_ST;

typedef enum tagEnumCondType
{
    COND_TYPE_ONCE,
    COND_TYPE_SIG,
    COND_TYPE_POS,
}E_COND_TYPE;

typedef struct tagCondition
{
    u8 m_ucCondtionType;
    union
    {
        CONDITION_POS_ST m_stCondPos;
        CONDITION_SIG_ST m_stCondSig;
    };

}CONDITION_ST;

// �����ź�
typedef struct tagActionSig
{
    u8  m_ucRid;
    s32 m_slSetVal;
    // the member below is ugly.
    s32 m_slPos;
}ACTION_SIG_ST;

// �����˶����� - Ŀ���ٶ�.
typedef struct tagActionSpeed
{
    s32 m_slSpeed;  // �ٶ��ź�
}ACTION_SPEED_ST;

// �����˶����� - �յ�λ��
typedef struct tagActionPos
{
    s32 m_slPos;
    u8  m_ucType;// ����/������ʽ
}ACTION_POS_ST;

typedef enum tagEnumActionType
{
    ACTION_TYPE_NONE,
    ACTION_TYPE_SIG,
    ACTION_TYPE_POS,
    ACTION_TYPE_SPD,
    
}E_ACTION_TYPE;

typedef struct tagAction
{
    int m_iActionType;
    union
    {
        ACTION_SIG_ST m_stActionSig;
        ACTION_POS_ST m_stActionPos;
        ACTION_SPEED_ST m_stActionSpeed;
    };
}ACTION_ST;


typedef struct tagENode
{
    CONDITION_ST m_stCond;
    ACTION_ST	 m_stAction;
#ifdef ENABLE_EXTENDED_FILED
    u8  m_ucPri;		// ���ȼ�.
    u8  m_ucEnable;     // ʹ��.
    void (*m_pFnPrintExtraInfo)(struct tagENode *);
#endif
}ENODE_ST;

// �����������̬.
typedef struct tagCMD
{
	// ִ����.
	ENODE_ST m_astNodeChain[CMD_CHAIN_MAX_LEN];
    u8 m_ucLen;
    u8 m_ucJobDone;
}CMD_ST;

// ����״̬
typedef struct tagRunState
{
    // ��Դ
    RESOURCE_ITEM m_astResource[SYS_RESOURCE_MAX_LEN];
    // Ŀ���ٶ�
    s32 m_slDstSpeed;
    // Ŀ��λ��
    s32 m_slDstPos;
    // ��ǰ�ٶ�
    s32 m_slCurSpeed;
    // ��ǰλ��
    s32 m_slCurPos;
}RUN_STATE_ST;

typedef struct tagExecuteUnit
{
    CMD_ST m_stCmd;
    RUN_STATE_ST m_stRunState; // ��ǰϵͳ״̬
}ST_EU;

void SplitCmd(char * pCmd);

#endif // __PARSER_H__
