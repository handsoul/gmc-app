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

#define BMU_CNT  10  //BMU��Ŀ
#define CELL_VCH 12 //��ѹͨ��
#define CELL_TCH 3  //�¶�ͨ��

typedef enum tagDebugCanID
{    
    CAN_ID_GET_STATUS = 0x400,      // �·�ID, �ϱ�ID = �·�ID + 1
    CAN_ID_SET_PARAM  = 0x402,
    CAN_ID_GET_PARAM  = 0x404,
    CAN_ID_CTRL_OUT   = 0x406,
    CAN_ID_GET_FIXED  = 0x408,
    CAN_ID_SET_DBG_INFO = 0x40A,
    CAN_ID_SET_PRD_INFO = 0x40C,
    CAN_ID_GET_PRD_INFO = 0x40E,
    CAN_ID_SET_PACK_INFO = 0x410, // ���õ�ذ���������Ϣ.
    CAN_ID_GET_PACK_INFO = 0x412, // ��ȡ��ذ���������Ϣ.
    
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


//�ź��б���ܵ�ֵ
//TODO: ���EJ04��ش���.
typedef enum etagSigList
{

    SID_BMS_SOFTVERSION = 0x001,
    SID_BMS_HARDVERSION = 0x002,
    SID_BUILD_TIME = 0x003,

    
    SID_CELL_V_01_TO_03 = 0x100,    // ��о��ѹ, 2���ֽ��޷���, ��λ: mV
    SID_CELL_V_04_TO_06 = 0x101,
    SID_CELL_V_07_TO_09 = 0x102,
    SID_CELL_V_10_TO_12 = 0x103,
    SID_CELL_V_13_TO_15 = 0x104,
    SID_CELL_V_16_TO_18 = 0x105,
    SID_CELL_V_19_TO_21 = 0x106,
    SID_CELL_V_22_TO_24 = 0x107,    // mV
    SID_MAX_MIN_CELL_V  = 0x108,    // �����͵�о��ѹ�����(��1��ʼ)
    SID_BATT_TOTAL_VOLT = 0x109,    // mV
    SID_BATT_CURR       = 0x10A,    // mA(���Ϊ��, �ŵ�Ϊ��)
    SID_BATT_SOC_SOH    = 0x10B,    // Soc% + Soh% + mAh(4�ֽ�)
    SID_INS_RES         = 0x10C,    // ����(��λ: k��) + ���� + V/��(��2�ֽ�)
    SID_AUX_PWR_VOLT    = 0x10D,    // ������Դ��ѹ
    SID_CELL_T_01_TO_06 = 0x10E,    // ��о�¶�(�¶�1���ֽ��з���, ��λ: ��)
    SID_MAX_MIN_CELL_T  = 0x10F,    // �����͵�о�¶ȼ����(��1��ʼ)
    SID_BMS_LTC_BAL_T   = 0x110,    // �����¶�(2) + LTC6803�¶�(2) + �����¶�(2)
    SID_BMS_DIO_ST      = 0x111,    // ����DI/DO��״̬.

    SID_CP_DUTY_FREQ    = 0x112,    // CP(Ƶ��2�ֽ�Hz, ռ�ձ�1�ֽ�%)
    SID_CC_CC2_RES      = 0x113,    // ��ֵ(��2�ֽ�, ��λ: ��)
    SID_BUS_VOLT_BY_RES = 0x114,    // ĸ�ߵ�ѹ(ͨ����Ե�������),4�ֽ�.
    SID_BAL_STATUS      = 0x115,    // ����״̬
    SID_ALARM_STATUS    = 0x116,    // �澯��Ϣ
    SID_POWRVOLT_5V     = 0x117,    // ��ʾ5V��Դ��ѹֵ.
    SID_ST5_DUTY_FREQ   = 0x118,    // ��ײ�ź�.
    SID_INSRES_AD0      = 0x119,    // ��ԵAD����-ģʽ1.
    SID_INSRES_AD1      = 0x11A,    // ��ԵAD����-ģʽ2.
    SID_INSRES_AD2      = 0x11B,    // ��ԵAD����-ģʽ3.

    // ����BMU������.
    SID_CELL_V_25_TO_V27	= 0x130,
    SID_CELL_V_28_TO_V30	= 0x131,
    SID_CELL_V_31_TO_V33	= 0x132,
    SID_CELL_V_34_TO_V36	= 0x133,
    SID_CELL_V_36_TO_V39	= 0x134,
    SID_CELL_V_40_TO_V42	= 0x135,

	SID_BMU_CELL_TEMP	= 0x136,	// BMU�¶�.(ֻ��¼��о�¶�).


    // ����У׼ϵ��
    SID_COEF_CELL_VB_01_TO_06 = 0x200,  // ��о��ѹУ׼ϵ��B
    SID_COEF_CELL_VB_07_TO_12 = 0x201,  // ��о��ѹУ׼ϵ��B
    SID_COEF_CELL_VB_13_TO_18 = 0x202,  // ��о��ѹУ׼ϵ��B
    SID_COEF_CELL_VB_19_TO_24 = 0x203,  // ��о��ѹУ׼ϵ��B
    SID_RTC_TIME              = 0x204,  // RTCʱ������.

    SID_COEF_CHG_CURR_K       = 0x205,  // ������У׼ϵ��K
    SID_COEF_CHG_CURR_B       = 0x206,  // ������У׼ϵ��B
    SID_COEF_DIS_CURR_K       = 0x207,  // �ŵ����У׼ϵ��K
    SID_COEF_DIS_CURR_B       = 0x208,  // �ŵ����У׼ϵ��B


    SID_RESTORE_SOC_VALUE     = 0x21F,  // ����SOC.

    SID_COEF_AUXVOLT          = 0x220,  // ������ѹ.
    SID_COEF_PACKVOLT         = 0x221,  // ĸ�ߵ�ѹ.

    //����.

    SID_CTRL_DBG_MODE         = 0x300,  // ����(0x01)/�˳�(0x00)����ģʽ
    SID_CTRL_RELAY_1          = 0x301,  // �̵�������1(0: �Ͽ�, 1: �պ�, 0xFF: ������)
    SID_CTRL_RELAY_2          = 0x302,  // �̵�������2
    SID_CTRL_FAN              = 0x303,  // ���ȿ���
    SID_CTRL_BAL_01_06        = 0x304,  // �������1(0: ֹͣ, 1: ����, 0xFF: ������)
    SID_CTRL_BAL_07_12        = 0x305,  // �������2.
    SID_CTRL_BAL_13_18        = 0x306,  // �������3.
    SID_CTRL_BAL_19_24        = 0x307,  // �������4.
    SID_CTRL_KCP              = 0x308,  // S2����.
    SID_CTRL_BAL_1_22         = 0x309,  // �������.
    SID_CTRL_PWR_LOCK         = 0x30A,  // ��������.
	SID_CTRL_RELAY_DECT       = 0x30B,  // ��ѹ���.
	SID_CTRL_EXT_WDT_FEED     = 0x30C,  // �ⲿ��ι������.

    // ���õ�����Ϣ
    SID_SET_DBG_MODE          = 0x400,  // ����(0x01)/�˳�(0x00)����ģʽ
    SID_SET_CELL_V_01_TO_03   = 0x401,  // �������õ�о��ѹ(mV, 2�ֽ��޷���)
    SID_SET_CELL_V_04_TO_06   = 0x402,  // �������õ�о��ѹ
    SID_SET_CELL_V_07_TO_09   = 0x403,  // �������õ�о��ѹ
    SID_SET_CELL_V_10_TO_12   = 0x404,  // �������õ�о��ѹ
    SID_SET_CELL_V_01_TO_15   = 0x405,  // �������õ�о��ѹ
    SID_SET_CELL_V_16_TO_18   = 0x406,  // �������õ�о��ѹ
    SID_SET_CELL_V_19_TO_21   = 0x407,  // �������õ�о��ѹ
    SID_SET_CELL_V_22_TO_24   = 0x408,  // �������õ�о��ѹ
    SID_SET_BATT_CURR         = 0x409,  // �������õ�ص���(mA, 4�ֽ��з���)
    SID_SET_CELL_T            = 0x40A,  // �������õ���¶�(��, 1�ֽ��з���)
    SID_SET_SOC_SOH           = 0x40B,  // ��������SOC/SOH�ٷֱ�
    SID_SET_INS_RES           = 0x40C,  // �������þ�Ե����(����/������2�ֽ��޷���, k��)
    SID_SET_DI_IN_STATUS      = 0x40D,  // ��������INx�ź�(4bit��ʾ1��INx�ź�, 0xF��ʾ������)
    SID_SET_DI_RFB_STATUS     = 0x40E,  // ��������RFBx�ź�(4bit��ʾ1��RFBx�ź�, 0xF��ʾ������)    

    //������Ϣ.
    SID_PRODUCT_INFO_01       = 0x500,
    SID_PRODUCT_INFO_0A       = 0x509,
    // ��ذ���������Ϣ.(6���ֽ� * 6 = 36�ֽ�).
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

    DBG_SID_VOLT_VMAX_VID= 0x00E, // ��͵�ѹ����λ�ü�����.
    DBG_SID_VOLT_VMIN_VID= 0x00F, // ��ߵ�ѹ����λ�ü�����.
    DBG_SID_TEMP_EXTREME = 0x010, // ���/����¶ȷ���λ��/�Լ��¶�ֵ.

    DBG_SID_PACKCURR    = 0x011,  // ����ܵ���.
    DBG_SID_PACKVOLT    = 0x012,  // ����ܵ�ѹ(�����ۼ�).
    DBG_SID_PACKVOLT_RES= 0x013,  // ����ܵ�ѹ(��Ե�迹����).
    DBG_SID_AUXVOLT     = 0x014,  // ������ƿ��ѹ.
    DBG_SID_SOC_SOH     = 0x015,  // SOC/SOH
    DBG_SID_BATT_AH     = 0x016,  // ʣ�����.
    DBG_SID_INS_RES     = 0x017,  // ��Ե�迹.
    DBG_SID_RES_OHM_VOLT= 0x018,  // ��Ե�迹.
    DBG_SID_DIO_ST      = 0x019,  // ����IO�ź�״̬. KA0~KA6,RFB,ST
    DBG_SID_CP_DUTY_FREQ= 0x01A,  // CPռ�ձ�/Ƶ��.
    DBG_SID_CC_CC2_RES  = 0x01B,  // CC/CC2��ֵ.
    
    DBG_SID_RES_DETC_AD_1 = 0x01C,  // ��ؾ�Ե����ADCֵ.(3��ģʽ-1)
    DBG_SID_RES_DETC_AD_2 = 0x01D,  // ��ؾ�Ե����ADCֵ.(3��ģʽ-2)
    DBG_SID_RES_DETC_AD_3 = 0x01E,  // ��ؾ�Ե����ADCֵ.(3��ģʽ-3)

    
    DBG_SID_SVER_INFO      = 0x01F, // ����汾��Ϣ.
    DBG_SID_HVER_INFO      = 0x020, // Ӳ���汾��Ϣ.
    DBG_SID_BUILD_TIME     = 0x021, // �汾��Ϣ.

    DBG_SID_CV_23_24      = 0x022,
    // ...
    DBG_SID_CV_39_40      = 0x02A,

    // �¶���Ϣ.
    DBG_SID_T_BMU_01_04  = 0x02B, // BMU���¶���Ϣ.


    DBG_SID_CHG_TIMES    = 0x030,   // ������
    DBG_SID_TOTAL_CHG_AH = 0x031,   // �ۼƳ��AH��

    // ����һ��.
    DBG_SID_USER_DEF1     = 0x040, // �Զ��������Ϣ1.
    DBG_SID_USER_DEF2     = 0x041, // �Զ��������Ϣ2.

    DBG_SIG_EEPROM_ERR    = 0x042,
    DBG_SIG_PCF8563_ERR   = 0x043,
    DBG_SIG_MCP3425_ERR   = 0x044,

    DBG_SIG_PWR_ON_TIMES  = 0x045,  // �����ϵ����
    DBG_SIG_PWR_ON_SEC    = 0x046,  // �����ϵ��ۼ�ʱ������
    DBG_SIG_POS_FAULT_CNT = 0x047,  // �����̵������ϼ���
    DBG_SIG_NEG_FAULT_CNT = 0x048,  // �����̵������ϼ���
    DBG_SIG_ONC_FAULT_CNT = 0x049,  // ����̵������ϼ���

    // ������Ϣ����
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
    u16 m_usEqualization;//��������
    u32 m_ulMsgCnt;//��Ϣ������.
    bool m_bUpdated;//����ˢ������.
    u8 m_aus6803St[6];//6803�ļĴ���״̬.
    u8 m_bUpdate6803;//6803��������.
    u8 m_aucProductInfo[8];//����汾,Ӳ���汾,ƫ����,���к�.
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
    u8 BoardName[7]; //���6�ֽ�,������1�ֽ�
    u8 ProductName[7];//���6�ֽ�,������1�ֽ�
    u8 SerialNo[6];//��Ʒ���к�.��2 + ��1 + ��1 + ���2.
    
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

// �����ŵ緧ֵ(mA, ���Ϊ��, �ŵ�Ϊ��)
#define MIN_CHG_CURR            -1000
#define MIN_DIS_CURR            1000

// �����ص�ʵ��״̬
#define BATT_STATUS_IDLE        0x00
#define BATT_STATUS_CHG         0x01
#define BATT_STATUS_DIS         0x02
#define BATT_STATUS_FULL        0x03

#define BATT_SOC_MAX            100     // SOC���ֵ

// �������ģʽ
#define DBG_MODE_SW             0x01    // �������ģʽ
#define DBG_MODE_HW             0x02    // Ӳ������ģʽ

// ����̵���״̬
#define RELAY_ST_OPEN           0       // �Ͽ�(�ϵ�Ĭ��״̬)
#define RELAY_ST_CLOSE          1       // �պ�

// 
#define RELAY_NUM               7       // �̵�������(ʵ��7��, ���1��Ԥ��)

#define DI_IN_NUM               7       // ��7��IN�ź�.
#define DI_RFB_NUM              6       // ��6��RFB�ź�.

// ����ϵͳ״̬��Ϣ(��Ӧͨ��Э���ϱ���״̬/�澯)
typedef struct tagSysStatusInfo
{
    u8 m_aucRelaySt[RELAY_NUM];
}SYS_STATUS_INFO_ST;

//У׼ϵ��.
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

// BMS������Ϣ
typedef struct tagBmsRunInfo
{
    u32 m_ulBattVolt;               // ������ܵ�ѹ(��λ: mV)
    u32 m_ulBattVoltByRes;          // ������ܵ�ѹ(��λ: mV)
    u16 m_ausCellVolt[CELL_NUM];    // �����о��ѹ(��λ: mV)
    u16 m_usCellMaxVolt;            // �����о��ߵ�ѹ(��λ: mV)
    u16 m_usCellMinVolt;            // �����о��͵�ѹ(��λ: mV)
    u8  m_ucMaxVoltCellNO;          // ��ߵ�ѹ��о���(��0��ʼ)
    u8  m_ucMinVoltCellNO;          // ��͵�ѹ��о���(��0��ʼ)
    u32 m_ulCellVoltSum;            // �����о��ѹ��
    s32 m_slMcp3425Curr;            // MCP3425����ĵ���
    s32 m_slIna219Curr;             // INA219����ĵ���
    s32 m_slBattCurr;               // ������ܵ���(��λ: mA, ���Ϊ��, �ŵ�Ϊ��)
    s16 m_assCellTemp[CELL_T_NUM];  // ��о�¶�(����AD�ɼ�NTC)
    s16 m_ssCellMaxTemp;            // ��о����¶�
    s16 m_ssCellMinTemp;            // ��о����¶�
    u8  m_ucMaxTempNO;              // ����¶ȱ��(��0��ʼ)
    u8  m_ucMinTempNO;              // ����¶ȱ��(��0��ʼ)
    s16 m_assBmsTemp[BMS_T_NUM];    // BMS�¶�(����AD�ɼ�NTC)
    s16 m_assLtc6803Temp[LTC_T_NUM];// LTC6803оƬ�¶�(LTC6803�ɼ�)
    s16 m_assBalTemp[BAL_T_NUM];    // �����¶�(LTC6803�ɼ�)
    u32 m_ulBattSoc_mAh;            // ʣ������ֵ(��λ: mAh)
    u32 m_ulBattSoc_mASec;          // ʣ������ֵ(��λ: mASec)
    u8  m_ucBattSocPercent;         // ʣ�������ٷֱ�(��λ: 1%)
    u16 m_usBattSocGain100;         // ʣ������X100(��: 50%����洢5000)
    u8  m_ucBattSOH;                // ������(��λ: 1%)
    u8  m_ucBattStatus;             // ���״̬
    u8  m_ucCellBalStatus;          // ����״̬(��λ���, 0: δ����, 1: ���ھ���)
    u8  m_ucDebugMode;              // ����ģʽ
    s8  m_scDbgVoltDelta;           // ����ģʽ�µĵ�ѹ�仯��(ģ���ص�ѹ����/�½�����)
    u16 m_usAlarmStatus;            // �澯״̬(��λ���, 0: ����, 1: �澯)       
    u8  m_ucChgEnStatus;            // �������״̬(0: ��ֹ, 1: ����)
    u8  m_ucDisEnStatus;            // �ŵ�����״̬(0: ��ֹ, 1: ����), �������ƶ�·�ж�

    u16 m_usNtcPowerVolt;           // NTC(5V)��Դ��ѹ(��λ: mV)
    u16 m_usAuxPowerVolt;           // ����(12V)��Դ��ѹ(��λ: mV)
    u16 m_usCcRes;                  // CC(����)�ӿ���ֵ(��λ: ��)
    u16 m_usCc2Res;                 // CC2(���)�ӿ���ֵ(��λ: ��)
    u32 m_ulPosInsRes;
    u32 m_ulNegInsRes;
    u32 m_ulInsulatedRes;           // ��Ե�迹(��λ: ��)
    u32 m_ulInsResOhmPerVolt;       // ��Ե�迹

    u8 m_aucRelaySt[RELAY_NUM];     //�̵���״̬.
    u8 m_aucIN[DI_IN_NUM];
    u8 m_aucRFB[DI_RFB_NUM];

    u8 m_aucRelayHvSt[4];

    u8 m_ucS2Sts;

    u16 m_usCPFreq;
    u8  m_ucCPDuty;
    u16 m_usCCRes;
    u16 m_usCC2Res;

    u16 m_aucAlarmSt[17];//�澯״̬.

    s16 m_assBusBarAD[2];// ͭ�ŵ�ѹ.
    
}BMS_RUN_INFO_ST;

typedef struct tagStatisticsST
{
    s32 m_ulCurVal;     //��ǰֵ.
    s32 m_ulMaxVal;     //���ֵ.
    s32 m_ulMinVal;     //��Сֵ.
    u32 m_ulDiff;       //�����С��ֵ.
    s32 m_slMaxChange;  //�������.
    u32 m_ulChangeCnt;  //�仯����.
    s32 m_slLastChange; //�ϴ�����.
    bool m_bFirstUpdate;//�״θ�ֵ.
}StatisticsST;

typedef struct tagBMUStatST
{
    StatisticsST m_astData[15];//12·��ѹ, 3·�¶�.

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
    u8  m_ucKA_Pos;//�����̵���.
    u8  m_ucKA_Neg;//�����̵���.
    u8  m_ucKA_Pre;//Ԥ��̵���.

}A60DFSginal;

typedef struct tagBMSFaultType
{
    u8 m_ucFaultCode;
    const char * m_pscFaultType;//��������.
} BMSFault_ST;


typedef struct tagSimulationDataSt
{
    u16 m_ausCellVolt[CELL_NUM];//�����ѹ.
    s8  m_ascTemp[CELL_T_NUM];//����¶�
    s32 m_slBattCurr;//����.
    u8  m_ucSOC; //SOC,
    u8  m_ucSOH;
    u16 m_usInsResPos;//�迹.
    u16 m_usInsResNeg;//�迹.

    u8  m_aucDI_INSt[6];
    u8  m_aucDI_RFBSt[6];

}T01DBG_ST;

//��Ʒ��Ϣд��.
typedef struct tagProductInformation
{
    u8 m_aucProductName[12];        //�ַ���ʽ-��Ʒ�ͺ�T01
    u8 m_aucProductNo[12];          //�ַ���ʽ-��Ʒ���.ZY200001
    u8 m_aucBoardName[12];          //�ַ���ʽ-��������-EXBMS-BCU
    u8 m_aucProductSerialNo[12];    //�ַ���ʽ-��Ʒ���к�.140909001
    u8 m_aucProductHardVersion[6];  //Ӳ���汾��-��1����1����1.
    u8 m_aucProductSoftVersion[6];  //����汾��-��1����1����1.--����д��.
}BMS_PRODUCT_INFO_ST;


typedef union tagCanMsgIDUnion
{
    u32 m_ulMsgID;              // ��ϢID(���ͱ�ʾ)
    struct
    {
#if 1
        /**********************************************
        * CPU   ���ģʽ:���ݵĸ�λ���������ڴ�ĵ͵�ַ��
        * ��ַ  0x0000 0x0001 0x0002 0x0003
        * ����  0x11   0x22   0x33   0x44
        * ʵ��ֵ:0x11223344
        **********************************************/
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
#else


        /**********************************************
        * CPU   С��ģʽ:���ݵĸ�λ���������ڴ�ĸߵ�ַ��
        * ��ַ  0x0000 0x0001 0x0002 0x0003
        * ����  0x44   0x33   0x22   0x11
        * ʵ��ֵ:0x11223344
        **********************************************/
        //bits[0:7]                                                          �ڴ��ַ
        u32 m_btCntFlag : 1;    // [0]:     CNTλ(0: ���1֡, 1: ������1֡)
        u32 m_btRsv6V1  : 6;    // [1:6]:   ����λ(���1)              --->  0x0000
        u32 m_btMsgDir  : 1;    // [7]:     ��Ϣ����(0: S->M, 1: M->S)          |
        //bits[8:15]                                                            |
        u32 m_btCmdID   : 8;    // [8:15]:  ����ID                     --->  0x0001
		//bits[16:23]                                                           |
        u32 m_btDstAddr : 8;    // [16:23]: Ŀ��ڵ��ַ               --->  0x0002
        //bits[24:31]                                                           |
        u32 m_btProtoNO : 5;    // [24:28]: Э���(Э������)           --->  0x0003
        u32 m_btRsv3V0  : 3;    // [29:31]: ����λ(���0)
#endif
    }m_btMsgID;                 // ��ϢID(λ���ʾ)
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