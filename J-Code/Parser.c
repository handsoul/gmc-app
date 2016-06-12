﻿#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Parser.h"
#include "SysCfg.h"

#define SIMULATION_MODE

#ifdef SIMULATION_MODE

extern void AddToStringList(const char * buf);

static char ascStringBuf[1024];

#define fprintf(_fd,args...) \
    {\
     int l = snprintf(ascStringBuf,sizeof(ascStringBuf),##args);\
     if (l > 0 && l < sizeof(ascStringBuf))\
     {\
        ascStringBuf[l] = '\0';\
        AddToStringList(ascStringBuf);\
     }\
    }
#endif

// TODO: 1. 完成解析过程中对解析过程的填充. DONE.
//       2. step 1完成后可以继续完成执行器部分. -> 列入计划.
//       3. 执行器完成后.实现了一些驱动无关的顶层设计. -> 列入一周计.
//       4. 完成实际的驱动设计即可. (硬件设计完成后)
//       5. 最终实现: 动作执行和回采的回环过程. 并调整回环测量过程以达到最终效果.

CMD_ST g_stCmd;

RUN_STATE_ST g_stRunState;

#define SKIP_WHITE_SPACE(pCmdStr) \ while(*pCmdStr == ' ') \
    {++pCmdStr;}


#define IS_DIGITAL_CHAR(c) \
    ((c >= '0') && (c <= '9'))

// 解析正确的数字
bool GetDigit(char *pCmdStr, int *pslValue)
{
    s32 slValule = 0;
    int slSign = 0;

    if (pCmdStr == NULL || *pCmdStr == END_CHAR)
    {
        return false;
    }

    if (*pCmdStr == '+' )
    {
        slSign = 0;
        pCmdStr++;
    }
    else if (*pCmdStr == '-')
    {
        slSign = -1;
        pCmdStr++;
    }

    while (*pCmdStr != END_CHAR)
    {
        if (IS_DIGITAL_CHAR(*pCmdStr) == false)
        {
            return false; // 出现无法解析的字符.
        }
        
        slValule += *pCmdStr - '0';

        if (*(++pCmdStr) != END_CHAR)
        {
            slValule *= 10;
        }
    }

    if (slSign < 0)
    {
        slValule =0-slValule;
    }

    *pslValue = slValule;

    return true;
}

// 解析正确的位置代码, 
// 位置代码的格式为: M0~MN.
bool GetPosExpression(char * pCmdStr, int * pslValue)
{
    if (*pCmdStr != 'M' && *pCmdStr != 'm')
    {
        return false;
    }

    return GetPosValueByName(pCmdStr,pslValue);
}

bool GetPosValueByExpression(char * pCmdStr, int *pslValue)
{
    if (GetPosExpression(pCmdStr, pslValue) == true)
    {
        return true;
    }
    else if (GetDigit(pCmdStr,pslValue) == true)
    {
        return true;
    }

    return false;
}

// GetDigit替换为求值的表达式即可.
int ParsePosExpression(char * pCmdStr, int * pslValue)
{
    char *pStart = pCmdStr;
    char *pEnd = pCmdStr;
    char scBackup = 0;
    char scBackupLast = 0;
    int i = 0;
    int slValue;
    int slResult = 0;

    if (pCmdStr == NULL)
    {
        return -1;
    }
    
    if (*pEnd == '+'
        || *pEnd == '-')
    {
        pEnd++; // 跳过第一个.
    }

    while(*pEnd != END_CHAR)
    {
        if (*pEnd == '+'
            || *pEnd == '-')
        {
            scBackup = *pEnd;
            *pEnd = END_CHAR;
            ++i;
            TRACE_PRINT("lexeme %d = %s\n",i,pStart);
            if (GetPosValueByExpression(pStart,&slValue)==true)
            {
                if (i == 1)
                {
                    slResult = slValue;
                }
                else if (scBackupLast == '+')
                {
                    slResult += slValue;
                }
                else
                {
                    slResult -= slValue;
                }
                TRACE_PRINT("Result = %d\n", slResult);
            }
            else
            {
                TRACE_PRINT("\t%s not recognized\n",pStart);
                return 0;
            }
            *pEnd = scBackup;
            pEnd++;
            pStart = pEnd;
            scBackupLast = scBackup;
        }
        else
        {
            ++pEnd;
        }

        // Last Lexeme.
        if (*pEnd == END_CHAR)
        {
            if (pEnd >= pStart+1)
            {
                ++i;
                TRACE_PRINT("lexeme %d = %s\n",i,pStart);
                if (GetPosValueByExpression(pStart,&slValue)==false)
                {
                    TRACE_PRINT("\t%s not recognized\n",pStart);
                    return false; // 出现了无法解析的表达式.
                }
                else
                {
                    if (i == 1)
                    {
                        slResult = slValue;
                    }
                    else if (scBackupLast == '+')
                    {
                        slResult += slValue;
                    }
                    else
                    {
                        slResult -= slValue;
                    }
                }

                TRACE_PRINT("Result = %d\n", slResult);
            }
            else
            {
                TRACE_PRINT("Empty Lexeme\n");
            }
        }
    }

    *pslValue = slResult;

    return 1;
}
// 位置解析.
// 返回值: 解析成功/错误.
// 完成绝对位置/相对位置的解析. 固定位置-配置.
bool HfnGetPos( char * pCmdStr, CONDITION_POS_ST * pCondPos)
{
    // 可能的方式: 
    // A: 绝对 -120+-20
    // B: 相对 MX-+20, MA-MB
    s32 slPos = 0;

    if (pCmdStr == NULL || *pCmdStr == '\0')
    {
        return false;
    }

    if (ParsePosExpression(pCmdStr,&slPos) == true)
    {
        pCondPos->m_ucRelation = 0;
        pCondPos->m_slOffset = 0;
        pCondPos->m_slPos = slPos;
        return true;
    }

    return false;
}

// 信号名称解析.
// 返回值: 解析成功/错误.
// 完成信号名 - 信号资源的映射.
bool HfnGetSig(char * pCmdStr, CONDITION_SIG_ST * pCondSig)
{
    s32 slSigID = 0;
    if ((slSigID = GetSigIndexByName(pCmdStr)) < 0)
    {
        return false;
    }

    pCondSig->m_iRid = slSigID;

    return true;
}

bool HfnParseActionR(char * pCmdStr, ACTION_ST * pstAction)
{
    CONDITION_POS_ST stPos;

    if(pCmdStr == NULL 
       || (*pCmdStr != 'R' && *pCmdStr != 'r'))
    {
        return false;
    }

    pCmdStr++;
    
    if (HfnGetPos(pCmdStr, &stPos) == false)
    {
        return false;
    }

    pstAction->m_iActionType = ACTION_TYPE_POS;
    pstAction->m_stActionPos.m_slPos = stPos.m_slPos;
    pstAction->m_stActionPos.m_ucType = 0;

    return true;
}

bool HfnParseActionP(char * pCmdStr, ACTION_ST * pstAction)
{
    s32 slSpdSeq = 0;
    if (pCmdStr == NULL
       || (*pCmdStr != 'P' && *pCmdStr != 'p'))
    {
        return false;
    }

    pCmdStr++;// 跳过字符[pP]

    if (GetDigit(pCmdStr,&slSpdSeq) == false)
    {
        ERRINFO("速度指针解析错误");
        return false;
    }

    pstAction->m_iActionType = ACTION_TYPE_SPD;
    pstAction->m_stActionPos.m_slPos = slSpdSeq;
 
    return true;
}

bool HfnParseActionS(char * pCmdStr, ACTION_ST * pstAction)
{

    u8 ucSigLevel = 0xFF;
    char * pEnd;
    char * pStart;
    char scBackup;
    CONDITION_POS_ST stPos;
    CONDITION_SIG_ST stSig;

    if(pCmdStr == NULL
       || (*pCmdStr != 'S' && *pCmdStr != 's'))
    {
        return false;
    }

    pCmdStr++;
    if (*pCmdStr == 'h' || *pCmdStr == 'H')
    {
        ucSigLevel = 1;
    }
    else if (*pCmdStr == 'l' || *pCmdStr == 'L')
    {
        ucSigLevel = 0;
    }  
    else
    {
        return false;
    }

    pCmdStr++;

    // 确认是否是位置,定位信号名.
    if (*pCmdStr == POS_PREFIX) // 使用的是指定位置的方式
    {
        pStart = pCmdStr + 1;
    }
    else
    {
        pStart = pCmdStr;
    }

    // 查找有效信号名称.
    if ((pEnd = strchr(pStart,'H')) == NULL
            &&(pEnd = strchr(pStart,'M')) == NULL) 
    {
        ERRINFO("未指定有效的信号名");
        return 0;
    }

    // 确认信号.
    if (HfnGetSig(pEnd,&stSig) == false)
    {
        ERRINFO("未指定有效的信号名");
        return false;
    }

    // 确定位置条件.
    scBackup = *pEnd;
    *pEnd = '\0';
    if (HfnGetPos(pCmdStr,&stPos) == false)
    {
        ERRINFO("\t位置表达式非法:%s\n\t当前命令解析退出\n",pCmdStr);
    }
    *pEnd = scBackup;

    pstAction->m_iActionType = ACTION_TYPE_SIG;
    pstAction->m_stActionSig.m_slPos = stPos.m_slPos;
    pstAction->m_stActionSig.m_slSetVal = ucSigLevel;
    pstAction->m_stActionSig.m_ucRid = stSig.m_iRid;

    return true;
}


// 动作解析
bool HfnGetAction(char *pCmdStr, ACTION_ST * pstAction)
{
    if (pCmdStr == NULL)
    {
        return false;
    }

    if (*pCmdStr == 'p' || *pCmdStr != 'P')
    {
        return HfnParseActionP(pCmdStr,pstAction);
    }
    else if (*pCmdStr == 'S' || *pCmdStr == 's')
    {
        return HfnParseActionS(pCmdStr,pstAction);
    }
    else if (*pCmdStr == 'r' || *pCmdStr == 'R')
    {
        return HfnParseActionR(pCmdStr,pstAction);
    }

    return false;
}


/*设置运转 - 返回解析是否成功*/
u8 ParseCmd_R(char * pCmdStr, CMD_ST * pstCmd)
{

    ACTION_ST stAction;

    if(pCmdStr == NULL)
    {
        return 0;
    }

    fprintf(stderr,"\t%s:\t开始解析\n",pCmdStr);

   
    if (HfnParseActionR(pCmdStr, &stAction) == false)
    {
        fprintf(stderr,"解析错误");
        return 0;
    }

    fprintf(stderr,"\t设置目标位置:%d\n",stAction.m_stActionPos.m_slPos);

    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stCond.m_ucCondtionType = COND_TYPE_ONCE; // 无条件执行一次即可.用于设定参数.此时的场景是设置运动的终点位置.(中途可能会停止)
    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stAction = stAction;
    pstCmd->m_ucLen++;

    fprintf(stderr,"\t解析完成,命令ID = %u\n",(unsigned)pstCmd->m_ucLen);

    return 1;
}


// speed set.
u8 ParseCmd_P(char * pCmdStr, CMD_ST *pstCmd)
{
    ACTION_ST stAction;
    if(pCmdStr == NULL)
    {
        return 0;
    }

    fprintf(stderr,"\t%s:\t开始解析\n",pCmdStr);

    if (HfnParseActionP(pCmdStr,&stAction) == false)
    {
        ERRINFO("P指令解析错误");
        return 0;
    }

    fprintf(stderr,"\t设置目标速度:%d\n",stAction.m_stActionSpeed.m_slSpeed);

    // 执行速度切换的动作.
    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stCond.m_ucCondtionType = COND_TYPE_ONCE;
    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stAction = stAction;
    pstCmd->m_ucLen++;

    fprintf(stderr,"\t解析完成,命令ID = %u\n",(unsigned)pstCmd->m_ucLen);

    return 1;
}


// 设置IO. / shM7.
// 信号名称 - shM7.
// 格式: setio = sh + pos + sigName
//             = sl + pos + sigName.
u8 ParseCmd_S(char * pCmdStr,  CMD_ST *pstCmd)
{
    static s8 s_ascSigBuf[40];
    ACTION_ST stAction;

    if (HfnParseActionS(pCmdStr,&stAction) == false)
    {
        ERRINFO("S命令解析错误: %s\n",pCmdStr);
        return false;
    }

    GetSigNameByID(stAction.m_stActionSig.m_ucRid,(char *)s_ascSigBuf);

    // sh/sl.
    fprintf(stderr,"\t设置信号:%s 为 %d,位置:%d\n",
            s_ascSigBuf,stAction.m_stActionSig.m_slSetVal,stAction.m_stActionSig.m_slPos);

    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stCond.m_ucCondtionType = COND_TYPE_ONCE;
    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stAction.m_iActionType = ACTION_TYPE_SIG;
    pstCmd->m_astNodeChain[pstCmd->m_ucLen].m_stAction = stAction;

    pstCmd->m_ucLen++;

    fprintf(stderr,"\t解析完成,命令ID = %u\n",(unsigned)pstCmd->m_ucLen);

    return 1;
}

void ActionToString(const ACTION_ST * pstAction, char * pStr)
{
    if (pstAction->m_iActionType == ACTION_TYPE_SPD)
    {
        sprintf(pStr,"设置运行速度为%d",pstAction->m_stActionSpeed.m_slSpeed);
    }
    else if (pstAction->m_iActionType == ACTION_TYPE_POS)
    {
        sprintf(pStr,"设置运行目标位置为%d",pstAction->m_stActionPos.m_slPos);
    }
    else
    {
        assert(0);
    }
}

// 查询信号.
// 根据查询条件执行动作.
// 格式:
// condAction = il + pos + sig + action.
//            = ih + pos + sig + action.
//            ih 230-20MA-p5
//            ih 230-20 MA - p5
//            op pos   sig - p5
u8 ParseCmd_I(char * pCmdStr, CMD_ST *pstCmd)
{
    static s8 s_ascSigBuf[40];
    static s8 s_ascPosBuf[40];
    static s8 s_ascActionBuf[40];

    u8 ucSigLevel = 0xFF;
    char * pEnd;
    char * pStart;
    char scBackup;
    CONDITION_POS_ST stPos;
    CONDITION_SIG_ST stSig;
    ACTION_ST   stAction;

    if(pCmdStr == NULL)
    { return 0;
    }

    fprintf(stderr,"\t%s:\t开始解析\n",pCmdStr);

    if (*pCmdStr != 'I' && *pCmdStr != 'i')
    {
        assert(0);
        return 0;
    }

    pCmdStr++;

    if (*pCmdStr == 'h' || *pCmdStr == 'H')
    {
        ucSigLevel = 1;
    }
    else if (*pCmdStr == 'l' || *pCmdStr == 'L')
    {
        ucSigLevel = 0;
    }  
    else
    {
        return 0; // command not recognized.
    }

    pCmdStr++;
    // 确认是否是位置,定位信号名.
    if (*pCmdStr == POS_PREFIX) // 使用的是指定位置的方式
    {
        pStart = pCmdStr + 1;
    }
    else
    {
        pStart = pCmdStr;
    }

    // 查找有效信号名称.
    if ((pEnd = strchr(pStart,'H')) == NULL
            &&(pEnd = strchr(pStart,'M')) == NULL) 
    {
        ERRINFO("未指定有效的信号名");
        return 0;
    }

    // 位置信号.
    scBackup = *pEnd;
    *pEnd = '\0';
    strcpy((char*)s_ascPosBuf,pCmdStr);
    *pEnd = scBackup;
    if (HfnGetPos((char*)s_ascPosBuf,&stPos) == false)
    {
        ERRINFO("未指定有效的信号名");
        return 0;
    }
    // 确认信号. 信号和动作之间的分隔符是'-'
    pStart = pEnd;
    if ((pEnd = strchr(pStart,'-')) == NULL)
    {
        ERRINFO("未指定有效动作");
        return 0;
    }

    scBackup = *pEnd;
    *pEnd = '\0';
    strcpy((char*)s_ascSigBuf,pStart);
    *pEnd = scBackup;

    if (HfnGetSig(pStart,&stSig) == false)
    {
        ERRINFO("未指定有效的信号名");
        return 0;
    }

    pStart = pEnd + 1; // 跳过分隔符.
    strcpy((char*)s_ascActionBuf,pStart);

    if (HfnGetAction((char*)s_ascActionBuf,&stAction) == false)
    {
        ERRINFO("动作字符串无法解析:%s",pStart);
        return 0;
    }

    // ih/il.
    ActionToString(&stAction,(char*)s_ascActionBuf);
    fprintf(stderr,"\t查询信号:%s ,位置:%d，若信号值为%d，执行动作: %s\n",
            s_ascSigBuf,stPos.m_slPos,ucSigLevel,s_ascActionBuf);

    // 为了兼容性考虑.需要将相关的单命令解析函数抽离出来,并适当组合.以适当匹配各情况
    // 比如这里可能是设置IO.也可能是停止.也可能是设置新的运行目标.

    pstCmd->m_ucLen++;

    fprintf(stderr,"\t解析完成,命令ID = %u\n",(unsigned)pstCmd->m_ucLen);

    return 1;
}

/*
 * 目前支持的命令如下.
 * 1. 考虑将命令写成列表的方式.
 * 2. 命令何时结束执行.命令结束执行条件. 执行了速度为0的命令.或运行范围已达到.
 * 3. 命令何时启动: 正确解析了命令.包含了速度设置( > 0). 是否结束则不做判断. 若未指定速度.或速度为0,则认为命令执行结束.
 * */
void ParseCmd(char * pCmdStr,CMD_ST *pstCmd)
{
    switch(*pCmdStr)
    {
        case 'R':
        case 'r':
            ParseCmd_R(pCmdStr,pstCmd);
            break;
        case 'S':
        case 's':
            ParseCmd_S(pCmdStr,pstCmd);
            break;
        case 'P':
        case 'p':
            ParseCmd_P(pCmdStr,pstCmd);
            break;
        case 'I':
        case 'i':
            ParseCmd_I(pCmdStr,pstCmd);
            break;
        default:
            fprintf(stderr,"undefined options/command\n");
            break;
    }
}

void SplitCmd(char * pCmd)
{
    char * pCur;

    if (pCmd == NULL)
    {
        return;
    }

    while(*pCmd != '\0')
    {
        pCur = strchr(pCmd,CMD_SEPARATOR);

        if (pCur != NULL)
        {
            *pCur = '\0';// end current command.
        }

        ParseCmd(pCmd,&g_stCmd);

        if (pCur == NULL)
        {
            break;
        }

        pCmd = pCur+1;
    }
}
