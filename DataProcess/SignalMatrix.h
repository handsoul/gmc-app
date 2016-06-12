#ifndef __SIGNALMATRIX_H__
#define __SIGNALMATRIX_H__

#include "DataProc.h"

typedef __int64 s64;

typedef unsigned __int64 u64;



// 告警故障类型根据捷威提供的通信协议来(告警最多分为3级, 1级最严重)
typedef enum tagAlarmNO
{
    ALM_NO_CHG_OCA_3 = 0,       // 0,充电电流过大3级告警
    ALM_NO_CHG_OCA_2,           // 1,充电电流过大2级告警
    ALM_NO_CHG_OCA_1,           // 2,充电电流过大1级告警
    ALM_NO_DIS_OCA_3,           // 3,放电电流过大3级告警
    ALM_NO_DIS_OCA_2,           // 4,放电电流过大2级告警
    ALM_NO_DIS_OCA_1,           // 5,放电电流过大1级告警
    ALM_NO_CELL_OVA_3,          // 6,单体电压过高3级告警
    ALM_NO_CELL_OVA_2,          // 7,单体电压过高3级告警
    ALM_NO_CELL_OVA_1,          // 8,单体电压过高3级告警
    ALM_NO_CELL_UVA_3,          // 9,单体电压过低3级告警
    ALM_NO_CELL_UVA_2,          // 10,单体电压过低2级告警
    ALM_NO_CELL_UVA_1,          // 11,单体电压过低1级告警
    ALM_NO_OTA_3,               // 12,温度过高3级告警
    ALM_NO_OTA_2,               // 13,温度过高2级告警
    ALM_NO_OTA_1,               // 14,温度过高1级告警
    ALM_NO_TEMP_DIFF_3,         // 15,温差过大3级告警
    ALM_NO_CELL_V_DIFF_3,       // 16,单体压差过大3级告警
    ALM_NO_CELL_V_DIFF_2,       // 17,单体压差过大2级告警
    ALM_NO_SOC_LOW_3,           // 18,SOC过低3级告警
    ALM_NO_SOC_LOW_2,           // 19,SOC过低2级告警
    ALM_NO_INS_RES_2,           // 20,绝缘故障2级告警
    ALM_NO_INS_RES_1,           // 21,绝缘故障1级告警
    ALM_NO_BATT_OVA_3,          // 22,总电压过高3级告警
    ALM_NO_BATT_OVA_2,          // 23,总电压过高2级告警
    ALM_NO_BATT_OVA_1,          // 24,总电压过高1级告警
    ALM_NO_UTA_3,               // 25,温度过低3级告警
    ALM_NO_UTA_2,               // 26,温度过低2级告警
    ALM_NO_EXT_COMM,            // 27,BMS外部(与车载充电机)通信故障
    ALM_NO_INT_COMM,            // 28,BMS内部(针对分布式的BCU/BMU间通信)通讯故障
    ALM_NO_HEATER,              // 29,加热回路故障
    ALM_NO_HV_MAIN_CON,         // 30,高压主接触器故障
    ALM_NO_SYS_HARD,            // 31,系统硬件故障
    ALM_NO_PRE_CHG_FAIL,        // 32,预充电失败故障

    ALARM_NUM,                  // 告警个数(种类)
    
}ALARM_NO_E;


typedef union tagBMS1UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullCheckSum      : 8;
        u64 m_ullCycleCounter  : 4;
        u64 m_ullReserved3_6   : 4;
        u64 m_ullMaxDCHCurrent : 14;

        u64 m_ullChargeRelayFault:1; // 充电继电器粘连故障.
        u64 m_ullRelayFault		: 1;  // 继电器粘连.

        u64 m_ullSlowChargeCmd : 2;
        u64 m_ullPreChRelayFB  : 1;
        u64 m_ullFastChRelayFB : 1;
        u64 m_ullPreChComplete : 1;
        u64 m_ullPreChFault    : 1;
        u64 m_ullWorkModeReq   : 2;

        u64 m_ullSOH           : 8; //SOH
        u64 m_ullSOC           : 8; //SOC

        u64 m_ullBMSAlarmLevel : 2;
        u64 m_ullBMSChargeSt   : 2;
        u64 m_ullNegRelayFB    : 1;
        u64 m_ullPosRelayFB    : 1;
        u64 m_ullHighVoltLoop  : 1; // 高压互锁信号  T02增加.
        u64 m_ullReserved1_1   : 1;

    }m_stBits;
    
}BMS1_UNRe;

typedef union tagBMS2UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {

        u64 m_ullCheckSum        :  8;
        u64 m_ullCycleCounter    :  4;
        u64 m_ullReserved3_4     :  4;
        u64 m_ullMaxCellVolt     : 13;
        u64 m_ullReserved2_3     :  3;
        u64 m_ullPackCurrent     : 16;
        u64 m_ullReserved1_3     :  3;
        u64 m_ullPackVolt        : 13;
    }m_stBits;
    
}BMS2_UNRe;

typedef union tagBMS3UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullCheckSum       :  8;
        u64 m_ullCycleCounter   :  4;
        u64 m_ullMaxChargeCurr  :  9;
        u64 m_ullReserved1_2    :  2;
        u64 m_ullMaxChargeVolt  : 12;
        u64 m_ullMinCellTemp    :  8;        
        u64 m_ullMaxCellTemp    :  8;
        u64 m_ullMinCellVolt    : 13;
        
    }m_stBits;
    
}BMS3_UNRe;

typedef union tagBMS4UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullCheckSum       :  8;
        u64 m_ullCycleCounter   :  4;
        u64 m_ullReserved1_12   : 12;
        u64 m_ullFaultCode      :  8; // 故障码.
        u64 m_ullContinueDischargePower    :  8; // 持续放电功率.
        u64 m_ullContinueChargePower    :  8; // 持续充电功率.
        u64 m_ullPeakDischargePower    :  8; // 峰值放电功率.
        u64 m_ullPeakChargePower    :  8; // 峰值充电功率
                
    }m_stBits;
    
}BMS4_UNRe;


typedef union tagONCUnRe
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullReserved_1_32  : 32;
        u64 m_ullACDCTempSt     :  1;
        u64 m_ullACDCVoltInputSt:  1;
        u64 m_ullACDCVoltOutputSt: 1;
        u64 m_ullACDCHardwareSt :  1;
        u64 m_ullACDCCommSt     :  1;
        u64 m_ullACDCWorkingMode:  2;        
        u64 m_ullReserved_2_1   :  1;
        u64 m_ullACDCOutputCurr :  8;
        u64 m_ullReserved_3_6   :  4;
		u64 m_ullACDCOutputVolt : 12;
        
    }m_stBits;    
}ONC_UnRe;

typedef union tagVCU1UnRe
{
    u8 m_aucDataBytes[8];

    struct
    {
        u64 m_ullReserved_1_12  : 12;
        u64 m_ullVCU_AuxRelayCmd:  1;
        u64 m_ullReserved_2_9   :  9;
        u64 m_ullVCU_KeyPosition:  2;
        u64 m_ullReserved_3_3   :  3;
        u64 m_ullVCU_MainRelayCmd: 1;
        u64 m_ullReserved_4_36  : 36;
    }m_stBits;
    
}VCU1_UnRe;

typedef union tagVCU2UnRe
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullReserved_1_32  : 32;
        u64 m_ullDrvMotorCurr   : 13;
        u64 m_ullReserved_2_8   :  8;
        u64 m_ullDrvMotorVolt   : 11;

    }m_stBits;
}VCU2_UnRe;


typedef union tagMCU3UnRe
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullReserved_1_16      : 16; // 保留位
        u64 m_ullDrvMotorPhaseCurr  : 16; // 精度0.01
        u64 m_ullDrvMotorCurr       : 16; // 精度0.01
        u64 m_ullDrvMotorVolt       : 16; // 精度0.01
	}m_stBits;

}MCU3_UnRe;


typedef enum tagSIGNAL_MATRIX_ID_E
{
    EID_BMS1 = 0x1A0,
    EID_BMS2 = 0x1A1,
    EID_BMS3 = 0x1A2,
    EID_BMS4 = 0x1A3,
    EID_ACDC = 0x370,
    EID_VCU1 = 0x101,
    EID_VCU2 = 0x102,
    EID_MCU3 = 0x107, // MCU报文.

    EID_JV_BMS1 = 0x210,
    EID_JV_BMS2 = 0x211,
    EID_JV_BMS3 = 0x212,

    EID_UDS_ID = 0x738, // 诊断CAN.

}SIGNAL_MATRIX_ID_E;


//JV定义信号矩阵.
//JV信号矩阵中定义字节序和众泰不同.
typedef union tagJVBMS1UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullPackVolt       : 16;
        u64 m_ullPackCurr       : 16;
        u64 m_ullSOC            : 8;
        u64 m_ullSOH            : 8;
        u64 m_ullMaxDchCurrAllowed : 16;
    }m_stBits;

}JV_BMS1_UN;

typedef struct tagJV_BMS1_ST
{
        u16 m_usPackVolt;
        s16 m_ssPackCurr;
        u8  m_ucSOC;
        u8  m_ucSOH;
        u16 m_usMaxDchCurrAllowed;
            
}JV_BMS1_ST;


typedef union tagJVBMS2UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullMaxCellVolt    : 16;
        u64 m_ullMinCellVolt    : 16;
        u64 m_ullMaxTemp        : 8;
        u64 m_ullMinTemp        : 8;

        u64 m_ullPosRelaySt     : 1;
        u64 m_ullNegRelaySt     : 1;
        u64 m_ullPreChRelaySt   : 1;
        u64 m_ullFastChRelaySt  : 1;
        u64 m_ullPTCRelaySt     : 1;
        u64 m_ullHeatRelaySt    : 1;
        u64 m_ullInitDone       : 1;
        u64 m_ullPreChargeDone  : 1;

        u64 m_ullHVReq          : 4;
        u64 m_ullFaultLevel     : 4;
        
    }m_stBits;

}JV_BMS2_UN;

typedef struct tagJVBMS2_ST
{
    u16 m_usMaxCellVolt;
    u16 m_usMinCellVolt;
    s8  m_scMaxTemp;
    s8  m_scMinTemp;

    u8  m_ucPosRelaySt;
    u8  m_ucNegRelaySt;
    u8  m_ucPreChRelaySt;
    u8  m_ucFastChRelaySt;
    u8  m_ucPTCRelaySt;
    u8  m_ucHeatRelaySt;
    u8  m_ucInitDone;
    u8  m_ucPreChargeDone;

    u8  m_ucHVReq;
    u8  m_ucFaultLevel;
        
}JV_BMS2_ST;


typedef union tagJVBMS3UNRE
{
    u8 m_aucDataBytes[8];
    struct
    {
        u64 m_ullInsRes_UA1     : 1;
        u64 m_ullCellVolt_OA1   : 1;
        u64 m_ullCellVolt_UA1   : 1;
        u64 m_ullChgCurr_OA1    : 1;
        u64 m_ullDchCurr_OA1    : 1;
        u64 m_ullBattTemp_OA1   : 1;
        u64 m_ullBattVolt_OA1   : 1;
        u64 m_ullReserved_1_1   : 1;

        u64 m_ullONC_Com_A1     : 1;
        u64 m_ullBMU_Com_A1     : 1;
        u64 m_ullHeater_A1      : 1;
        u64 m_ullHVRelay_A1     : 1;
        u64 m_ullBMSHW_A1       : 1;
        u64 m_ullPreCh_A1       : 1;
        u64 m_ullReserved_2_2   : 2;

        u64 m_ullInsRes_UA2     : 1;
        u64 m_ullCellVolt_OA2   : 1;
        u64 m_ullCellVolt_UA2   : 1;
        u64 m_ullChgCurr_OA2    : 1;
        u64 m_ullDchCurr_OA2    : 1;
        u64 m_ullBattTemp_OA2   : 1;
        u64 m_ullBattVolt_OA2   : 1;
        u64 m_ullSOC_UA2        : 1;

        u64 m_ullTempDiff_OA3   : 1;
        u64 m_ullCellVolt_OA3   : 1;
        u64 m_ullCellVolt_UA3   : 1;
        u64 m_ullChgCurr_OA3    : 1;
        u64 m_ullDchCurr_OA3    : 1;
        u64 m_ullBattTemp_OA3   : 1;
        u64 m_ullBattVolt_OA3   : 1;
        u64 m_ullSOC_UA3        : 1;

        u64 m_ullBattTemp_UA2   : 1;
        u64 m_ullVoltDiff_OA2   : 1;
        u64 m_ullBattTemp_UA3   : 1;
        u64 m_ullVoltDiff_OA3   : 1;
        u64 m_ullACChargeSt     : 2;//交流电充电状态.
        u64 m_ullHeaterSt       : 2;

        u64 m_ullCCSigSt        : 2;
        u64 m_ullCP1SigSt       : 1;
        u64 m_ullCC2SigSt       : 1;
        u64 m_ullChargeModeReq  : 4;
        u64 m_ullChargeMode     : 4;

        u64 m_ullChargeReqVolt  : 8;//请求充电电压.
        u64 m_ullChargeReqCurr  : 8;//请求充电电流.
        
    }m_stBits;

}JV_BMS3_UN;


typedef  struct tagJVBMS3_ST
{
        u8  m_ucInsRes_UA1;
        u8   m_ucCellVolt_OA1;
        u8  m_ucCellVolt_UA1;
        u8  m_ucChgCurr_OA1;
        u8  m_ucDchCurr_OA1;
        u8  m_ucBattTemp_OA1;
        u8  m_ucBattVolt_OA1;
        u8  m_ucReserved_1_1;

        u8  m_ucONC_Com_A1;
        u8  m_ucBMU_Com_A1;
        u8  m_ucHeater_A1;
        u8  m_ucHVRelay_A1;
        u8  m_ucBMSHW_A1;
        u8  m_ucPreCh_A1;

        u8  m_ucInsRes_UA2;
        u8  m_ucCellVolt_OA2;
        u8  m_ucCellVolt_UA2;
        u8  m_ucChgCurr_OA2;
        u8  m_ucDchCurr_OA2;
        u8  m_ucBattTemp_OA2;
        u8  m_ucBattVolt_OA2;
        u8  m_ucSOC_UA2;

        u8  m_ucTempDiff_OA3;
        u8  m_ucCellVolt_OA3;
        u8  m_ucCellVolt_UA3;
        u8  m_ucChgCurr_OA3;
        u8  m_ucDchCurr_OA3;
        u8  m_ucBattTemp_OA3;
        u8  m_ucBattVolt_OA3;
        u8  m_ucSOC_UA3;

        u8  m_ucBattTemp_UA2;
        u8  m_ucVoltDiff_OA2;
        u8  m_ucBattTemp_UA3;
        u8  m_ucVoltDiff_OA3;
        u8  m_ucACChargeSt;
        u8  m_ucHeaterSt;

        u8  m_ucCCSigSt;
        u8  m_ucCP1SigSt;
        u8  m_ucCC2SigSt;
        u8  m_ucChargeModeReq;
        u8  m_ucChargeMode;

        u8  m_ucChargeReqVolt;
        u8  m_ucChargeReqCurr;
        
}JV_BMS3_ST;

//T01信号矩阵.
typedef struct tagT01SignalMatrixST
{
    u8 m_aucT01Update[8];

    BMS1_UNRe m_unBMS1;
    BMS2_UNRe m_unBMS2;
    BMS3_UNRe m_unBMS3;
    BMS4_UNRe m_unBMS4;

    ONC_UnRe  m_unONC;
    VCU1_UnRe m_unVCU1;
    VCU2_UnRe m_unVCU2;

    MCU3_UnRe m_unMCU3; // T02增加的报文.
    
    
    u8 m_aucJVUpdate[3];
    
    JV_BMS1_UN m_unJvBMS1;
    JV_BMS2_UN m_unJvBMS2;
    JV_BMS3_UN m_unJvBMS3;

    JV_BMS1_ST m_stJvBMS1;
    JV_BMS2_ST m_stJvBMS2;
    JV_BMS3_ST m_stJvBMS3;

}T01SignalMatrixST;


typedef struct tagA60SignalMatrixST
{
    BMS1_UNRe m_unBMS1;
    BMS3_UNRe m_unBMS3;
    //BMS4_UNRe m_unBMS4;
    //A60BMS5_UNRe m_unBMS5;
    //BMS6_UNRe m_unBMS6;

    u16 m_usCurrAD0;
    u16 m_usCurrAD1;
    
}A60SignalMatrixST;

bool SaveA60EJ04(A60SignalMatrixST & stSigMatrix );

#endif
