#ifndef __DATA_PROC_H__
#define __DATA_PROC_H__

#include "CanDevice.h"
#include "string.h"

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16 ;
typedef unsigned int  u32;
typedef signed int s32;

#define BMU_CNT  10  //BMU数目
#define CELL_VCH 12 //电压通道
#define CELL_TCH 3  //温度通道

typedef enum tagDebugCanID
{    
    CAN_ID_GET_STATUS = 0x400,      // 下发ID, 上报ID = 下发ID + 1
    CAN_ID_SET_PARAM  = 0x402,
    CAN_ID_GET_PARAM  = 0x404,
    CAN_ID_CTRL_OUT   = 0x406,
    CAN_ID_GET_FIXED  = 0x408,
    CAN_ID_SET_DBG_INFO = 0x40A,
    CAN_ID_SET_PRD_INFO = 0x40C,
    CAN_ID_GET_PRD_INFO = 0x40E,
    CAN_ID_SET_PACK_INFO = 0x410, // 设置电池包的条码信息.
    CAN_ID_GET_PACK_INFO = 0x412, // 读取电池包的条码信息.
    
}DEBUG_CAN_ID_E;


typedef enum tagEnumBmu
{
    SIG_ID_BMU_SOFT_VERSION = 0x001,
	SIG_ID_BMU_HARD_VERSION = 0x002,
	SIG_ID_BMU_COMPILE_TIME = 0x003,
    SID_ID_BMU_PRODUCTINO_01= 0x004,
    // ....
    SID_ID_BMU_PRODUCTINO_10= 0x00D,
}BMU_SID_E;


//信号列表可能的值
//TODO: 添加EJ04相关代码.
typedef enum etagSigList
{

    SID_BMS_SOFTVERSION = 0x001,
    SID_BMS_HARDVERSION = 0x002,
    SID_BUILD_TIME = 0x003,

    
    SID_CELL_V_01_TO_03 = 0x100,    // 电芯电压, 2个字节无符号, 单位: mV
    SID_CELL_V_04_TO_06 = 0x101,
    SID_CELL_V_07_TO_09 = 0x102,
    SID_CELL_V_10_TO_12 = 0x103,
    SID_CELL_V_13_TO_15 = 0x104,
    SID_CELL_V_16_TO_18 = 0x105,
    SID_CELL_V_19_TO_21 = 0x106,
    SID_CELL_V_22_TO_24 = 0x107,    // mV
    SID_MAX_MIN_CELL_V  = 0x108,    // 最高最低电芯电压及编号(从1开始)
    SID_BATT_TOTAL_VOLT = 0x109,    // mV
    SID_BATT_CURR       = 0x10A,    // mA(充电为正, 放电为负)
    SID_BATT_SOC_SOH    = 0x10B,    // Soc% + Soh% + mAh(4字节)
    SID_INS_RES         = 0x10C,    // 正极(单位: kΩ) + 负极 + V/Ω(各2字节)
    SID_AUX_PWR_VOLT    = 0x10D,    // 辅助电源电压
    SID_CELL_T_01_TO_06 = 0x10E,    // 电芯温度(温度1个字节有符号, 单位: ℃)
    SID_MAX_MIN_CELL_T  = 0x10F,    // 最高最低电芯温度及编号(从1开始)
    SID_BMS_LTC_BAL_T   = 0x110,    // 单板温度(2) + LTC6803温度(2) + 均衡温度(2)
    SID_BMS_DIO_ST      = 0x111,    // 所有DI/DO的状态.

    SID_CP_DUTY_FREQ    = 0x112,    // CP(频率2字节Hz, 占空比1字节%)
    SID_CC_CC2_RES      = 0x113,    // 阻值(各2字节, 单位: Ω)
    SID_BUS_VOLT_BY_RES = 0x114,    // 母线电压(通过绝缘电阻计算),4字节.
    SID_BAL_STATUS      = 0x115,    // 均衡状态
    SID_ALARM_STATUS    = 0x116,    // 告警信息
    SID_POWRVOLT_5V     = 0x117,    // 显示5V电源电压值.
    SID_ST5_DUTY_FREQ   = 0x118,    // 碰撞信号.
    SID_INSRES_AD0      = 0x119,    // 绝缘AD数据-模式1.
    SID_INSRES_AD1      = 0x11A,    // 绝缘AD数据-模式2.
    SID_INSRES_AD2      = 0x11B,    // 绝缘AD数据-模式3.

    // 两个BMU的数据.
    SID_CELL_V_25_TO_V27	= 0x130,
    SID_CELL_V_28_TO_V30	= 0x131,
    SID_CELL_V_31_TO_V33	= 0x132,
    SID_CELL_V_34_TO_V36	= 0x133,
    SID_CELL_V_36_TO_V39	= 0x134,
    SID_CELL_V_40_TO_V42	= 0x135,

	SID_BMU_CELL_TEMP	= 0x136,	// BMU温度.(只记录电芯温度).


    // 设置校准系数
    SID_COEF_CELL_VB_01_TO_06 = 0x200,  // 电芯电压校准系数B
    SID_COEF_CELL_VB_07_TO_12 = 0x201,  // 电芯电压校准系数B
    SID_COEF_CELL_VB_13_TO_18 = 0x202,  // 电芯电压校准系数B
    SID_COEF_CELL_VB_19_TO_24 = 0x203,  // 电芯电压校准系数B
    SID_RTC_TIME              = 0x204,  // RTC时间设置.

    SID_COEF_CHG_CURR_K       = 0x205,  // 充电电流校准系数K
    SID_COEF_CHG_CURR_B       = 0x206,  // 充电电流校准系数B
    SID_COEF_DIS_CURR_K       = 0x207,  // 放电电流校准系数K
    SID_COEF_DIS_CURR_B       = 0x208,  // 放电电流校准系数B


    SID_RESTORE_SOC_VALUE     = 0x21F,  // 设置SOC.

    SID_COEF_AUXVOLT          = 0x220,  // 辅助电压.
    SID_COEF_PACKVOLT         = 0x221,  // 母线电压.

    //控制.

    SID_CTRL_DBG_MODE         = 0x300,  // 进入(0x01)/退出(0x00)调试模式
    SID_CTRL_RELAY_1          = 0x301,  // 继电器控制1(0: 断开, 1: 闭合, 0xFF: 不处理)
    SID_CTRL_RELAY_2          = 0x302,  // 继电器控制2
    SID_CTRL_FAN              = 0x303,  // 风扇控制
    SID_CTRL_BAL_01_06        = 0x304,  // 均衡控制1(0: 停止, 1: 启动, 0xFF: 不处理)
    SID_CTRL_BAL_07_12        = 0x305,  // 均衡控制2.
    SID_CTRL_BAL_13_18        = 0x306,  // 均衡控制3.
    SID_CTRL_BAL_19_24        = 0x307,  // 均衡控制4.
    SID_CTRL_KCP              = 0x308,  // S2控制.
    SID_CTRL_BAL_1_22         = 0x309,  // 均衡控制.
    SID_CTRL_PWR_LOCK         = 0x30A,  // 自锁控制.
	SID_CTRL_RELAY_DECT       = 0x30B,  // 高压检测.
	SID_CTRL_EXT_WDT_FEED     = 0x30C,  // 外部狗喂狗控制.

    // 设置调试信息
    SID_SET_DBG_MODE          = 0x400,  // 进入(0x01)/退出(0x00)调试模式
    SID_SET_CELL_V_01_TO_03   = 0x401,  // 调试设置电芯电压(mV, 2字节无符号)
    SID_SET_CELL_V_04_TO_06   = 0x402,  // 调试设置电芯电压
    SID_SET_CELL_V_07_TO_09   = 0x403,  // 调试设置电芯电压
    SID_SET_CELL_V_10_TO_12   = 0x404,  // 调试设置电芯电压
    SID_SET_CELL_V_01_TO_15   = 0x405,  // 调试设置电芯电压
    SID_SET_CELL_V_16_TO_18   = 0x406,  // 调试设置电芯电压
    SID_SET_CELL_V_19_TO_21   = 0x407,  // 调试设置电芯电压
    SID_SET_CELL_V_22_TO_24   = 0x408,  // 调试设置电芯电压
    SID_SET_BATT_CURR         = 0x409,  // 调试设置电池电流(mA, 4字节有符号)
    SID_SET_CELL_T            = 0x40A,  // 调试设置电池温度(℃, 1字节有符号)
    SID_SET_SOC_SOH           = 0x40B,  // 调试设置SOC/SOH百分比
    SID_SET_INS_RES           = 0x40C,  // 调试设置绝缘电阻(正极/负极各2字节无符号, kΩ)
    SID_SET_DI_IN_STATUS      = 0x40D,  // 调试设置INx信号(4bit表示1个INx信号, 0xF表示不处理)
    SID_SET_DI_RFB_STATUS     = 0x40E,  // 调试设置RFBx信号(4bit表示1个RFBx信号, 0xF表示不处理)    

    //固有信息.
    SID_PRODUCT_INFO_01       = 0x500,
    SID_PRODUCT_INFO_0A       = 0x509,
    // 电池包的条码信息.(6个字节 * 6 = 36字节).
    SID_PACK_SERIAL_INFO_01       = 0x580,
    SID_PACK_SERIAL_INFO_02       = 0x581,
    SID_PACK_SERIAL_INFO_03       = 0x582,
    SID_PACK_SERIAL_INFO_04       = 0x583,
    SID_PACK_SERIAL_INFO_05       = 0x584,
    SID_PACK_SERIAL_INFO_06       = 0x585,

}eSignal;


typedef enum tagCommandSig
{
    CMD_GET_INHERENT_BATCH  = 0x40,
    CMD_GET_INHERENT_SINGLE = 0x41,
    CMD_GET_STATUS_BATCH    = 0x50,
    CMD_GET_STATUS_SINGLE   = 0x51,
    CMD_SET_PARAMS_BATCH    = 0x80,
    CMD_SET_PARAMS_SIGNLE   = 0x81,
    CMD_GET_PARAMS_BATCH    = 0x82,
    CMD_GET_PARAMS_SIGNLE   = 0x83,
}eCmdType;


typedef enum tagUdsSigID_E
{
    DBG_SID_CV_01_TO_02 = 0x000,
    DBG_SID_CV_03_TO_04 = 0x001,
    DBG_SID_CV_05_TO_06 = 0x002,
    DBG_SID_CV_07_TO_08 = 0x003,
    DBG_SID_CV_09_TO_10 = 0x004,
    DBG_SID_CV_10_TO_12 = 0x005,
    DBG_SID_CV_13_TO_14 = 0x006,
    DBG_SID_CV_15_TO_16 = 0x007,
    DBG_SID_CV_17_TO_18 = 0x008,
    DBG_SID_CV_19_TO_20 = 0x009,
    DBG_SID_CV_21_TO_22 = 0x00A,
    
    DBG_SID_T_01_TO_04  = 0x00B,
    DBG_SID_T_05_TO_08  = 0x00C,
    DBG_SID_T_09_TO_12  = 0x00D,  //

    DBG_SID_VOLT_VMAX_VID= 0x00E, // 最低电压发生位置及单体.
    DBG_SID_VOLT_VMIN_VID= 0x00F, // 最高电压发生位置及单体.
    DBG_SID_TEMP_EXTREME = 0x010, // 最低/最高温度发生位置/以及温度值.

    DBG_SID_PACKCURR    = 0x011,  // 电池总电流.
    DBG_SID_PACKVOLT    = 0x012,  // 电池总电压(单体累加).
    DBG_SID_PACKVOLT_RES= 0x013,  // 电池总电压(绝缘阻抗计算).
    DBG_SID_AUXVOLT     = 0x014,  // 辅助电瓶电压.
    DBG_SID_SOC_SOH     = 0x015,  // SOC/SOH
    DBG_SID_BATT_AH     = 0x016,  // 剩余电量.
    DBG_SID_INS_RES     = 0x017,  // 绝缘阻抗.
    DBG_SID_RES_OHM_VOLT= 0x018,  // 绝缘阻抗.
    DBG_SID_DIO_ST      = 0x019,  // 数字IO信号状态. KA0~KA6,RFB,ST
    DBG_SID_CP_DUTY_FREQ= 0x01A,  // CP占空比/频率.
    DBG_SID_CC_CC2_RES  = 0x01B,  // CC/CC2阻值.
    
    DBG_SID_RES_DETC_AD_1 = 0x01C,  // 电池绝缘采样ADC值.(3个模式-1)
    DBG_SID_RES_DETC_AD_2 = 0x01D,  // 电池绝缘采样ADC值.(3个模式-2)
    DBG_SID_RES_DETC_AD_3 = 0x01E,  // 电池绝缘采样ADC值.(3个模式-3)

    
    DBG_SID_SVER_INFO      = 0x01F, // 软件版本信息.
    DBG_SID_HVER_INFO      = 0x020, // 硬件版本信息.
    DBG_SID_BUILD_TIME     = 0x021, // 版本信息.

    DBG_SID_CV_23_24      = 0x022,
    // ...
    DBG_SID_CV_39_40      = 0x02A,

    // 温度信息.
    DBG_SID_T_BMU_01_04  = 0x02B, // BMU的温度信息.


    DBG_SID_CHG_TIMES    = 0x030,   // 充电次数
    DBG_SID_TOTAL_CHG_AH = 0x031,   // 累计充电AH数

    // 跳过一段.
    DBG_SID_USER_DEF1     = 0x040, // 自定义调试消息1.
    DBG_SID_USER_DEF2     = 0x041, // 自定义调试消息2.

    DBG_SIG_EEPROM_ERR    = 0x042,
    DBG_SIG_PCF8563_ERR   = 0x043,
    DBG_SIG_MCP3425_ERR   = 0x044,

    DBG_SIG_PWR_ON_TIMES  = 0x045,  // 单板上电次数
    DBG_SIG_PWR_ON_SEC    = 0x046,  // 单板上电累计时间秒数
    DBG_SIG_POS_FAULT_CNT = 0x047,  // 正极继电器故障计数
    DBG_SIG_NEG_FAULT_CNT = 0x048,  // 负极继电器故障计数
    DBG_SIG_ONC_FAULT_CNT = 0x049,  // 慢充继电器故障计数

    // 调试消息总数
    DBG_SIG_NUM, 
}UDS_SIG_ID_E;

typedef union tagCANID{

    u32 m_ulRawID : 29;
    struct {
    
        u8 m_ucCNTFlag      : 1;
        u8 m_ucReserved     : 6;
        u8 m_ucMasterFlag   : 1;
        u8 m_ucCommand      : 8;
        u8 m_ucSlaveAddr    : 8;
        u8 m_ucProtocol     : 5;

    }m_stBits;

}CANID_ST;

typedef struct tagBMU
{
    u16 m_ausCellVolt[CELL_VCH];
    u16 m_ausCellTemp[CELL_TCH];
    u16 m_usEqualization;//均衡配置
    u32 m_ulMsgCnt;//消息计数器.
    bool m_bUpdated;//数据刷新请求.
    u8 m_aus6803St[6];//6803的寄存器状态.
    u8 m_bUpdate6803;//6803更新请求.
    u8 m_aucProductInfo[8];//软件版本,硬件版本,偏移量,序列号.
}BMUInfoST;

typedef struct tagCfg
{
    u16 m_usCurr0_DCH_K;
    s16 m_ssCurr0_DCH_B;
    u16 m_usCurr0_CHG_K;
    s16 m_ssCurr0_CHG_B;
    u16 m_usCurr1_DCH_K;
    s16 m_ssCurr1_DCH_B;
    u16 m_usCurr1_CHG_K;
    s16 m_ssCurr1_CHG_B;

    u16 m_usPackVolt_K;
    s16 m_usPackVolt_B;

    u16 m_usAuxVolt_K;
    s16 m_ssAuxVolt_B;

    s8 m_scFanStart_Temp;
    s8 m_scFanStop_Temp;

} D608_Params_ST;

typedef struct tagCfgItem{

    u16 m_usAuxVolt_K;
    s16 m_ssAuxVolt_B;

}D609_Params_ST;

typedef struct tagProductInfo
{
    u8 BoardName[7]; //最多6字节,结束符1字节
    u8 ProductName[7];//最多6字节,结束符1字节
    u8 SerialNo[6];//产品序列号.年2 + 月1 + 日1 + 编号2.
    
}ProductInfo;

typedef struct tagCellExtremeInfo{

    u16 m_usMaxVolt;
    u16 m_usVMaxIdx;
    u16 m_usMinVolt;
    u16 m_usVMinIdx;
    u16 m_usVDiff;

    u16 m_usMaxTemp;
    u16 m_usTMaxIdx;
    u16 m_usMinTemp;
    u16 m_usTMinIdx;
    u16 m_usTDiff;

}CellExtremeInfoST;



#define CELL_NUM                40
#define CELL_T_NUM              10
#define BMS_T_NUM               2
#define LTC_T_NUM               2
#define BAL_T_NUM               2

// 定义充放电阀值(mA, 充电为负, 放电为正)
#define MIN_CHG_CURR            -1000
#define MIN_DIS_CURR            1000

// 定义电池的实际状态
#define BATT_STATUS_IDLE        0x00
#define BATT_STATUS_CHG         0x01
#define BATT_STATUS_DIS         0x02
#define BATT_STATUS_FULL        0x03

#define BATT_SOC_MAX            100     // SOC最大值

// 定义调试模式
#define DBG_MODE_SW             0x01    // 软件调试模式
#define DBG_MODE_HW             0x02    // 硬件调试模式

// 定义继电器状态
#define RELAY_ST_OPEN           0       // 断开(上电默认状态)
#define RELAY_ST_CLOSE          1       // 闭合

// 
#define RELAY_NUM               7       // 继电器数量(实际7个, 最后1个预留)

#define DI_IN_NUM               7       // 共7个IN信号.
#define DI_RFB_NUM              6       // 共6个RFB信号.

// 定义系统状态信息(对应通信协议上报的状态/告警)
typedef struct tagSysStatusInfo
{
    u8 m_aucRelaySt[RELAY_NUM];
}SYS_STATUS_INFO_ST;

//校准系数.
//
typedef struct tagBmsCfgParams
{
    s8 m_aucCellVoltOffset[CELL_NUM];

    u16  m_usChargeCurrK;
    s32  m_usChargeCurrB;
    u16  m_usDisChargeCurrK;
    s32  m_usDisChargeCurrB;

    u16  m_usAuxVoltK;
    s16  m_ssAuxVoltB;

    u16  m_usPackVoltK;
    s16  m_ssPackVoltB;
    
}BMS_CFG_PARAMS_ST;

// BMS运行信息
typedef struct tagBmsRunInfo
{
    u32 m_ulBattVolt;               // 电池组总电压(单位: mV)
    u32 m_ulBattVoltByRes;          // 电池组总电压(单位: mV)
    u16 m_ausCellVolt[CELL_NUM];    // 单体电芯电压(单位: mV)
    u16 m_usCellMaxVolt;            // 单体电芯最高电压(单位: mV)
    u16 m_usCellMinVolt;            // 单体电芯最低电压(单位: mV)
    u8  m_ucMaxVoltCellNO;          // 最高电压电芯编号(从0开始)
    u8  m_ucMinVoltCellNO;          // 最低电压电芯编号(从0开始)
    u32 m_ulCellVoltSum;            // 单体电芯电压和
    s32 m_slMcp3425Curr;            // MCP3425测出的电流
    s32 m_slIna219Curr;             // INA219测出的电流
    s32 m_slBattCurr;               // 电池组总电流(单位: mA, 充电为正, 放电为负)
    s16 m_assCellTemp[CELL_T_NUM];  // 电芯温度(单板AD采集NTC)
    s16 m_ssCellMaxTemp;            // 电芯最高温度
    s16 m_ssCellMinTemp;            // 电芯最低温度
    u8  m_ucMaxTempNO;              // 最高温度编号(从0开始)
    u8  m_ucMinTempNO;              // 最低温度编号(从0开始)
    s16 m_assBmsTemp[BMS_T_NUM];    // BMS温度(单板AD采集NTC)
    s16 m_assLtc6803Temp[LTC_T_NUM];// LTC6803芯片温度(LTC6803采集)
    s16 m_assBalTemp[BAL_T_NUM];    // 均衡温度(LTC6803采集)
    u32 m_ulBattSoc_mAh;            // 剩余容量值(单位: mAh)
    u32 m_ulBattSoc_mASec;          // 剩余容量值(单位: mASec)
    u8  m_ucBattSocPercent;         // 剩余容量百分比(单位: 1%)
    u16 m_usBattSocGain100;         // 剩余容量X100(如: 50%这里存储5000)
    u8  m_ucBattSOH;                // 健康度(单位: 1%)
    u8  m_ucBattStatus;             // 电池状态
    u8  m_ucCellBalStatus;          // 均衡状态(按位组合, 0: 未均衡, 1: 正在均衡)
    u8  m_ucDebugMode;              // 调试模式
    s8  m_scDbgVoltDelta;           // 调试模式下的电压变化率(模拟电池电压上升/下降过程)
    u16 m_usAlarmStatus;            // 告警状态(按位组合, 0: 正常, 1: 告警)       
    u8  m_ucChgEnStatus;            // 充电允许状态(0: 禁止, 1: 允许)
    u8  m_ucDisEnStatus;            // 放电允许状态(0: 禁止, 1: 允许), 用来控制短路中断

    u16 m_usNtcPowerVolt;           // NTC(5V)电源电压(单位: mV)
    u16 m_usAuxPowerVolt;           // 辅助(12V)电源电压(单位: mV)
    u16 m_usCcRes;                  // CC(慢充)接口阻值(单位: Ω)
    u16 m_usCc2Res;                 // CC2(快充)接口阻值(单位: Ω)
    u32 m_ulPosInsRes;
    u32 m_ulNegInsRes;
    u32 m_ulInsulatedRes;           // 绝缘阻抗(单位: Ω)
    u32 m_ulInsResOhmPerVolt;       // 绝缘阻抗

    u8 m_aucRelaySt[RELAY_NUM];     //继电器状态.
    u8 m_aucIN[DI_IN_NUM];
    u8 m_aucRFB[DI_RFB_NUM];

    u8 m_aucRelayHvSt[4];

    u8 m_ucS2Sts;

    u16 m_usCPFreq;
    u8  m_ucCPDuty;
    u16 m_usCCRes;
    u16 m_usCC2Res;

    u16 m_aucAlarmSt[17];//告警状态.

    s16 m_assBusBarAD[2];// 铜排电压.
    
}BMS_RUN_INFO_ST;

typedef struct tagStatisticsST
{
    s32 m_ulCurVal;     //当前值.
    s32 m_ulMaxVal;     //最大值.
    s32 m_ulMinVal;     //最小值.
    u32 m_ulDiff;       //最大最小差值.
    s32 m_slMaxChange;  //最大跳变.
    u32 m_ulChangeCnt;  //变化次数.
    s32 m_slLastChange; //上次跳变.
    bool m_bFirstUpdate;//首次赋值.
}StatisticsST;

typedef struct tagBMUStatST
{
    StatisticsST m_astData[15];//12路电压, 3路温度.

    u8 m_ucBmuId;//bmuID.

}BMUStatST;

typedef struct tagA60DFSt
{
    u16 m_usPackVolt;
    s16 m_ssPackCurrent;
    u16 m_usMaxCellVolt;
    u16 m_usMinCellVolt;
    u16 m_usAvgCellVolt;
    u16 m_usSOC;
    u16 m_usInsulationRes;
    u8  m_ucMaxCellTemp;
    u8  m_ucMinCellTemp;
    u8  m_ucKA_Pos;//正极继电器.
    u8  m_ucKA_Neg;//负极继电器.
    u8  m_ucKA_Pre;//预充继电器.

}A60DFSginal;

typedef struct tagBMSFaultType
{
    u8 m_ucFaultCode;
    const char * m_pscFaultType;//故障类型.
} BMSFault_ST;


typedef struct tagSimulationDataSt
{
    u16 m_ausCellVolt[CELL_NUM];//单体电压.
    s8  m_ascTemp[CELL_T_NUM];//电池温度
    s32 m_slBattCurr;//电流.
    u8  m_ucSOC; //SOC,
    u8  m_ucSOH;
    u16 m_usInsResPos;//阻抗.
    u16 m_usInsResNeg;//阻抗.

    u8  m_aucDI_INSt[6];
    u8  m_aucDI_RFBSt[6];

}T01DBG_ST;

//产品信息写入.
typedef struct tagProductInformation
{
    u8 m_aucProductName[12];        //字符方式-产品型号T01
    u8 m_aucProductNo[12];          //字符方式-产品编号.ZY200001
    u8 m_aucBoardName[12];          //字符方式-单板名称-EXBMS-BCU
    u8 m_aucProductSerialNo[12];    //字符方式-产品序列号.140909001
    u8 m_aucProductHardVersion[6];  //硬件版本号-主1、次1、次1.
    u8 m_aucProductSoftVersion[6];  //软件版本号-主1、次1、次1.--不可写入.
}BMS_PRODUCT_INFO_ST;


typedef union tagCanMsgIDUnion
{
    u32 m_ulMsgID;              // 消息ID(整型表示)
    struct
    {
#if 1
        /**********************************************
        * CPU   大端模式:数据的高位，保存在内存的低地址中
        * 地址  0x0000 0x0001 0x0002 0x0003
        * 数据  0x11   0x22   0x33   0x44
        * 实际值:0x11223344
        **********************************************/
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
#else


        /**********************************************
        * CPU   小端模式:数据的高位，保存在内存的高地址中
        * 地址  0x0000 0x0001 0x0002 0x0003
        * 数据  0x44   0x33   0x22   0x11
        * 实际值:0x11223344
        **********************************************/
        //bits[0:7]                                                          内存地址
        u32 m_btCntFlag : 1;    // [0]:     CNT位(0: 最后1帧, 1: 还有下1帧)
        u32 m_btRsv6V1  : 6;    // [1:6]:   保留位(填充1)              --->  0x0000
        u32 m_btMsgDir  : 1;    // [7]:     消息方向(0: S->M, 1: M->S)          |
        //bits[8:15]                                                            |
        u32 m_btCmdID   : 8;    // [8:15]:  命令ID                     --->  0x0001
		//bits[16:23]                                                           |
        u32 m_btDstAddr : 8;    // [16:23]: 目标节点地址               --->  0x0002
        //bits[24:31]                                                           |
        u32 m_btProtoNO : 5;    // [24:28]: 协议号(协议类型)           --->  0x0003
        u32 m_btRsv3V0  : 3;    // [29:31]: 保留位(填充0)
#endif
    }m_btMsgID;                 // 消息ID(位域表示)
}CAN_MSG_ID_UN;




void CloseCurrentFile(void);
void UpdateStatistics(StatisticsST & stData, s32 slNewValue);
bool SaveCanMsg(CanMsgST & stMsg, bool isRcvMsg);

bool SavT01Record(BMS_RUN_INFO_ST & stInfo );

struct tagT01SignalMatrixST;
#define GET_HEADER(aucData , ucResult, usSignal)\
    {\
        ucResult = (aucData[0] & 0xF0)>>4;\
        usSignal = (aucData[0] & 0x0F);\
        usSignal <<= 8;\
        usSignal += aucData[1];\
    }

#define GetU16(ucByteHigh, ucBytesLow)\
    ((((u16)ucByteHigh)<<8) + ucBytesLow)

#define GetU32(ucBytesHH, ucBytesHL, ucBytesLH, ucBytesLL)\
    (u32)( ((((u32)ucBytesHH)&0xFF) << 24)| \
           ((((u32)ucBytesHL)&0xFF) << 16)| \
           ((((u32)ucBytesLH)&0xFF) <<  8)| \
           ((((u32)ucBytesLL)&0xFF) <<  0))

#endif