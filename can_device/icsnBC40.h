////////////////////////////////////////////////////////////////////////////////////
// neovi.h
// 4/23/2001
// Header file for using the neoVI API in C/C++
// Copyright Intrepid Control Systems, Inc. 2000-2001
// www.intrepidcs.com
////////////////////////////////////////////////////////////////////////////////////

// include the standard message data structures
#include        "icsSpyData.h"

// comment the following line out for Visual C++
#define		BORLANDC


//
// If borland c is defined we need to have "extern "c" added
// before each api call and a closing bracket after each api call
#ifdef BORLANDC
	#define BORLANDC_HEADER		extern "C" {
	#define BORLANDC_FOOTER		}
#else
	#define BORLANDC_HEADER	
	#define BORLANDC_FOOTER	
#endif


// OpenPort "OpenType" Argument Constants
#define		NEOVI_COMMTYPE_RS232				0
#define		NEOVI_COMMTYPE_USB_BULK				1
#define		NEOVI_COMMTYPE_USB_ISO_DONT_USE			2
#define		NEOVI_COMMTYPE_TCPIP				3

// Driver Type Constants
#define INTREPIDCS_DRIVER_STANDARD		0
#define	INTREPIDCS_DRIVER_TEST			1

// device Type IDs
#define INTREPIDCS_DEVICE_NEO4			0
#define INTREPIDCS_DEVICE_VCAN			1
#define INTREPIDCS_DEVICE_NEO6			2
#define INTREPIDCS_DEVICE_UNKNOWN		3

// Device IDs
#define NEODEVICE_BLUE = 1;
#define NEODEVICE_DW_VCAN = 4;
#define NEODEVICE_FIRE = 8;
#define NEODEVICE_VCAN3 = 16;
#define NEODEVICE_ANY = 65535;


#define SCRIPT_LOCATION_FLASH_MEM  0    //(Valid only on a neoVI Fire or neoVI Red)
#define SCRIPT_LOCATION_SDCARD  1    //(Valid only on a neoVI Fire or neoVI Red)
#define SCRIPT_LOCATION_VCAN3_MEM  2    //Valid only on a ValueCAN 3 device)

//device ID's
const int  NETID_DEVICE  = 0;
const int NETID_HSCAN = 1;
const int  NETID_MSCAN = 2;
const int  NETID_SWCAN = 3;
const int  NETID_LSFTCAN = 4;
const int  NETID_FORDSCP = 5;
const int  NETID_J1708 = 6;
const int  NETID_AUX = 7;
const int  NETID_JVPW = 8;
const int  NETID_ISO = 9;
const int  NETID_LIN = 9;
const int  NETID_ISOPIC= 10;
const int  NETID_MAIN51 = 11;
const int  NETID_SCI = 13;
const int  NETID_ISO2 = 14;
const int  NETID_FIRE_HSCAN1 = 41;
const int  NETID_FIRE_HSCAN2 = 42;
const int  NETID_FIRE_MSCAN1 = 43;
const int  NETID_FIRE_MSCAN2 = 44;
const int  NETID_FIRE_HSCAN3 = 44;
const int  NETID_FIRE_SWCAN = 45;
const int  NETID_FIRE_LSFT = 46;
const int  NETID_FIRE_LIN1 = 47;
const int  NETID_FIRE_LIN2 = 48;
const int  NETID_FIRE_LIN3 = 49;
const int  NETID_FIRE_LIN4 = 50;

//icsSpyDataStatusBitfield
#define    icsSpyStatusGlobalError                      2 ^ 0
#define    icsSpyStatusTx                               2 ^ 1
#define    icsSpyStatusXtdFrame                         2 ^ 2
#define    icsSpyStatusRemoteFrame                      2 ^ 3
#define    icsSpyStatusErrCRCError                      2 ^ 4
#define    icsSpyStatusCANErrorPassive                  2 ^ 5
#define    icsSpyStatusErrIncompleteFrame               2 ^ 6
#define    icsSpyStatusErrLostArbitration               2 ^ 7
#define    icsSpyStatusErrUndefined                     2 ^ 8
#define    icsSpyStatusErrCANBusOff                     2 ^ 9
#define    icsSpyStatusErrCANErrorWarning               2 ^ 10
#define    icsSpyStatusBusShortedPlus                   2 ^ 11
#define    icsSpyStatusBusShortedGnd                    2 ^ 12
#define    icsSpyStatusCheckSumError                    2 ^ 13
#define    icsSpyStatusErrBadMessageBitTimeError        2 ^ 14
#define    icsSpyStatusIFRData                          2 ^ 15
#define    icsSpyStatusHardwareCommError                2 ^ 16
#define    icsSpyStatusExpectedLengthError              2 ^ 17
#define    icsSpyStatusIncomingNoMatch                  2 ^ 18
#define    icsSpyStatusBreak                            2 ^ 19
#define    icsSpyStatusAVT_VSIRecOverflow               2 ^ 20
#define    icsSpyStatusTestTrigger                      2 ^ 21
#define    icsSpyStatusAudioCommentType                 2 ^ 22
#define    icsSpyStatusGPSDataValue                     2 ^ 23
#define    icsSpyStatusAnalogDigitalInputValue          2 ^ 24
#define    icsSpyStatusTextCommentType                  2 ^ 25
#define    icsSpyStatusNetworkMessageType               2 ^ 26
#define    icsSpyStatusVSI_TxUnderRun           2 ^ 27
#define    icsSpyStatusVSI_IFR_CRCBit           2 ^ 28
#define    icsSpyStatusInitMessage              2 ^ 29
#define    icsSpyStatusHighSpeed                2 ^ 30


//icsSpyDataStatusBitfield2
#define    icsSpyStatusHasValue                 2 ^ 0
#define    icsSpyStatusValueIsBoolean           2 ^ 1
#define    icsSpyStatusHighVoltage              2 ^ 2
#define    icsSpyStatusLongMessage              2 ^ 3


// ISO15765 Status Flags
#define INTREPIDCS_15765_RX_ERR_GLOBAL			0x0001
#define INTREPIDCS_15765_RX_ERR_CFRX_EXP_FF		0x0002
#define INTREPIDCS_15765_RX_ERR_FCRX_EXP_FF		0x0004
#define INTREPIDCS_15765_RX_ERR_SFRX_EXP_CF		0x0008
#define INTREPIDCS_15765_RX_ERR_FFRX_EXP_CF		0x0010
#define INTREPIDCS_15765_RX_ERR_FCRX_EXP_CF		0x0020
#define	INTREPIDCS_15765_RX_ERR_CF_TIME_OUT		0x0040
#define	INTREPIDCS_15765_RX_COMPLETE			0x0080
#define	INTREPIDCS_15765_RX_IN_PROGRESS			0x0100
#define	INTREPIDCS_15765_RX_ERR_SEQ_ERR_CF		0x0200

// Configuration Array addresses
#define		NEO_CFG_MPIC_GENIO_SETUP


// EEPROM ADDRESSES
#define		NEOVI_MAINPICEE_FORDSCP_ADDR		63
#define		NEOVI_MAINPICEE_LBCC_NUM_LU1_ENTERIES	66
#define		NEOVI_MAINPICEE_LBCC_NUM_LU1_START	67
#define		NEOVI_MAINPICEE_LBCC_NUM_LU1_STOP	97
#define		NEOVI_ISOJEE_ISOMODE_BITFIELD		155

// neoVI Error Constants ///////////////////////////////////////////////////////////
const unsigned long NEOVI_ERROR_DLL_TX_BUFFER_OVERFLOW = 0;
const unsigned long NEOVI_ERROR_DLL_ERROR_BUFFER_OVERFLOW = 1;
const unsigned long NEOVI_ERROR_DLL_USB_SEND_DATA_ERROR = 2;
const unsigned long NEOVI_ERROR_DLL_ISO_DATA_BUFFER_ALLOC = 3;
const unsigned long NEOVI_ERROR_DLL_ISO_DATA_READ_BUFFER = 4;
const unsigned long NEOVI_ERROR_DLL_ISO_DATA_ZERO_PACKETS =5;
const unsigned long NEOVI_ERROR_DLL_RX_MSG_BUFFER_OVERFLOW =6;
const unsigned long NEOVI_ERROR_DLL_STOP_ISO_STREAM =7;
const unsigned long NEOVI_ERROR_DLL_INVALID_NETID =8;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_RX_THREAD =9;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_TX_THREAD =10;
const unsigned long NEOVI_ERROR_DLL_MAIN_PIC_BUFFER_OVERFLOW =11;
const unsigned long NEOVI_ERROR_DLL_INVALID_DEVICE_RESPONSE =12;
const unsigned long NEOVI_ERROR_DLL_ISOTX_DATA_BUFFER_ALLOC =13;
const unsigned long NEOVI_ERROR_DLL_RX_CMD_BUFFER_OVERFLOW=14;
const unsigned long NEOVI_ERROR_DLL_RS232_RX_BUFFER_OVERFLOW=15;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_READCOMERR =16;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_READ=17;
const unsigned long NEOVI_ERROR_DLL_RS232_BUFFER_ALLOC=18;
const unsigned long NEOVI_ERROR_DLL_RS232_TX_BUFFER_OVERFLOW=19;
const unsigned long NEOVI_ERROR_DLL_RS232_MISC_ERROR=20;
const unsigned long NEOVI_ERROR_DLL_RS232_FIND_WRITE=21;
const unsigned long NEOVI_ERROR_DLL_RS232_FIND_BUFFER_ALLOC=22;
const unsigned long NEOVI_ERROR_DLL_RS232_FIND_CLEARCOMM=23;
const unsigned long NEOVI_ERROR_DLL_RS232_FIND_READCOMM=24;
const unsigned long NEOVI_ERROR_DLL_RS232_FIND_TIMEOUT=25;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_BREAK=26;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_FRAME=27;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_IOE=28;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_OVERRUN=29;
const unsigned long NEOVI_ERROR_DLL_RS232_ERR_PARITY=30;
const unsigned long NEOVI_ERROR_DLL_RS232_TXBUFFER_ALLOC=31; 
const unsigned long NEOVI_ERROR_DLL_USB_TX_RS232_ERROR=32;
const unsigned long NEOVI_ERROR_DLL_RS232_CREATE_FILE=33;
const unsigned long NEOVI_ERROR_DLL_RS232_GET_COMM_STATE=34;
const unsigned long NEOVI_ERROR_DLL_RS232_SET_COMM_STATE=35;
const unsigned long NEOVI_ERROR_DLL_RS232_START_COMM_RX_THREAD=36;
const unsigned long NEOVI_ERROR_DLL_RS232_START_COMM_TX_THREAD=37;
const unsigned long NEOVI_ERROR_DLL_SYNC_COUNT_ERR=38;
const unsigned long NEOVI_ERROR_DLL_RX_MSG_FRAME_ERR=39;
const unsigned long NEOVI_ERROR_DLL_RX_MSG_FIFO_OVER=40;
const unsigned long NEOVI_ERROR_DLL_RX_MSG_CHK_SUM_ERR=41;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_BULKIN_THREAD=42;
const unsigned long NEOVI_ERROR_DLL_BULKIN_ERR_READ=43;
const unsigned long NEOVI_ERROR_DLL_MAIN51_RX_FIFO_OVERFLOW=44;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW=45;
const unsigned long NEOVI_ERROR_DLL_MAIN51_DEV_FIFO_OVERFLOW=46;
const unsigned long NEOVI_ERROR_DLL_RESET_STATUS_CHANGED=47;
const unsigned long NEOVI_ERROR_DLL_ISO_LONG_CACHE_OVERFLOW=48;
const unsigned long NEOVI_ERROR_DLL_ISORX_LONG_BUFFER_ALLOC=49;
const unsigned long NEOVI_ERROR_DLL_J1708_LONG_CACHE_OVERFLOW=50;
const unsigned long NEOVI_ERROR_DLL_J1708_LONG_BUFFER_ALLOC=51;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_DEVICE =52;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_HSCAN =53;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_MSCAN =54;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_SWCAN =55;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_LSFTCAN =56;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_FORDSCP =57;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_J1708 =58;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_AUX =59;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_JVPW =60;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_ISO =61;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_ISOPIC =62;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_MAIN51 =63;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_FIFO_OVERFLOW_HOST =64;
const unsigned long NEOVI_ERROR_DLL_READ_ENTIRE_DEEPROM_ERROR =65;
const unsigned long  NEOVI_ERROR_DLL_WRITE_ENTIRE_DEEPROM_ERROR=66;
const unsigned long  NEOVI_ERROR_DLL_USB_PORT_ALREADY_OPEN=67;
const unsigned long  NEOVI_ERROR_DLL_JVPW_TX_REPORT_FIFO_ERR_IN=68;
const unsigned long  NEOVI_ERROR_DLL_ISOJ_TX_REPORT_FIFO_ERR_IN=69;
const unsigned long  NEOVI_ERROR_DLL_JVPW_TX_REPORT_FIFO_ERR_OUT=70;
const unsigned long  NEOVI_ERROR_DLL_ISOJ_TX_REPORT_FIFO_ERR_OUT=71;
const unsigned long  NEOVI_ERROR_DLL_MAIN51_TX_IN_FROM_HOST_FIFO=72;
const unsigned long  NEOVI_ERROR_DLL_MAIN51_TX_HOST_CHKSUM=73;
const unsigned long NEOVI_ERROR_DLL_ISOJ_TX_HOST_MISSED_BYTE=74;
const unsigned long NEOVI_ERROR_DLL_NEOVI_NO_RESPONSE=75;
const unsigned long NEOVI_ERROR_DLL_RX_SOCKET_FIFO_OVER=76;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_TXSOCKET_THREAD=77;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_RXSOCKET_THREAD=78;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_TXSOCKET_CLIENT_THREAD=78;
const unsigned long NEOVI_ERROR_DLL_PROBLEM_STOPPING_RXSOCKET_CLIENT_THREAD=79;
const unsigned long NEOVI_ERROR_DLL_TCP_CLIENT_TX=80;
const unsigned long NEOVI_ERROR_DLL_TCP_CLIENT_RX=81;
const unsigned long NEOVI_ERROR_DLL_TCP_CLIENT_RX_SOCK=82;
const unsigned long NEOVI_ERROR_DLL_UNABLE_CONNECT_TO_SRVR=83;
const unsigned long NEOVI_ERROR_DLL_UNABLE_CREATE_CLIENT_SOCK=84;
const unsigned long NEOVI_ERROR_DLL_UNABLE_WSASTARTUP=85;
const unsigned long NEOVI_ERROR_DLL_SOCK_CL_RD_BUFFER_ALLOC=86;
const unsigned long NEOVI_ERROR_DLL_SOCK_CL_TX_BUFFER_ALLOC=87;
const unsigned long NEOVI_ERROR_DLL_SOCK_SRVR_RX_BUFFER_ALLOC=88;
const unsigned long NEOVI_ERROR_DLL_SOCK_SRVR_TX_BUFFER_ALLOC=89;
const unsigned long NEOVI_ERROR_DLL_ILLEGAL_TX_NETWORK=90;
const unsigned long NEOVI_ERROR_DLL_MAIN51_TX_HOST_OVERRUN=91;
const unsigned long NEOVI_ERROR_DLL_OPEN_GET_COMM_TIMEOUT=92;
const unsigned long NEOVI_ERROR_DLL_OPEN_SET_COMM_TIMEOUT=93;
const unsigned long NEOVI_ERROR_DLL_OPEN_READ_DEVICE_TYPE=94;
const unsigned long NEOVI_ERROR_DLL_OPEN_READ_DEVICE_TYPE_TOUT=95;
const unsigned long NEOVI_ERROR_DLL_CLOSE_PURGE_COMM=96;
const unsigned long NEOVI_ERROR_DLL_TX_COM_FIFO_OVERFLOW=97;
const unsigned long NEOVI_ERROR_DLL_GET_USBSERIAL_DEVICES=98;


// Constants for describing error severity
const unsigned long icsspyErrCritical=0x10;
const unsigned long icsspyErrExclamation=0x30;
const unsigned long icsspyErrInformation=0x40;
const unsigned long icsspyErrQuestion=0x20;


typedef struct
{
    unsigned char Mode;
    unsigned char SetBaudrate;
    unsigned char Baudrate;
    unsigned char NetworkType;
    unsigned char TqSeg1;
    unsigned char TqSeg2;
    unsigned char TqProp;
    unsigned char TqSync;
    unsigned short BRP;
    unsigned short auto_baud;
} CAN_SETTINGS;

typedef struct
{
    unsigned short time_500us;
    unsigned short k;
    unsigned short l;
}ISO9141_KEYWORD2000__INIT_STEP;

typedef struct
{
    unsigned int Baudrate;
    unsigned short spbrg;
    unsigned short brgh;
    ISO9141_KEYWORD2000__INIT_STEP init_steps[16]; //See the ISO9141_KW2000__INIT_STEP structure
    unsigned char init_step_count;
    unsigned short p2_500us;
    unsigned short p3_500us;
    unsigned short p4_500us;
    unsigned short chksum_enabled;
} ISO9141_KW2000SETTINGS;


typedef struct
{
    unsigned char Mode;
    unsigned char SetBaudrate;
    unsigned char Baudrate;
    unsigned char NetworkType;
    unsigned char TqSeg1;
    unsigned char TqSeg2;
    unsigned char TqProp;
    unsigned char TqSync;
    unsigned short BRP;
    unsigned short high_speed_auto_switch;
    unsigned short auto_baud;
} SWCAN_SETTINGS;

typedef struct _LIN_SETTINGS
{
    unsigned int Baudrate;
    unsigned short spbrg;
    unsigned short brgh;
    unsigned char MasterResistor;
    unsigned char Mode;
} LIN_SETTINGS;

typedef struct 
{ 
    CAN_SETTINGS can1;   
    CAN_SETTINGS can2;
    CAN_SETTINGS can3;
    CAN_SETTINGS can4;
    SWCAN_SETTINGS swcan;    
    CAN_SETTINGS lsftcan;
    LIN_SETTINGS lin1;      
    LIN_SETTINGS lin2;
    LIN_SETTINGS lin3;
    LIN_SETTINGS lin4;
    unsigned short cgi_enable;
    unsigned short cgi_baud;
    unsigned short cgi_tx_ifs_bit_times;
    unsigned short cgi_rx_ifs_bit_times;
    unsigned short cgi_chksum_enable;
    unsigned short network_enables;
    unsigned short network_enabled_on_boot;
    unsigned short pwm_man_timeout;
    unsigned short pwr_man_enable;
    unsigned short misc_io_initial_ddr;
    unsigned short misc_io_initial_latch;
    unsigned short misc_io_analog_enable;
    unsigned short misc_io_report_period;
    unsigned short misc_io_on_report_events;
    unsigned short ain_sample_period;
    unsigned short ain_threshold;
    unsigned short iso15765_separation_time_offset; 
    unsigned short iso9141_kwp_enable;
    ISO9141_KW2000SETTINGS iso9141_kwp_settings; 
	unsigned short perf_en;
	unsigned short iso_parity;
	unsigned short iso_msg_termination;
	unsigned short iso_tester_pullup_enable;
	unsigned short network_enables_2;
	ISO9141_KW2000SETTINGS iso9141_kwp_settings2;
	unsigned short iso_parity_2;
	unsigned short iso_msg_termination_2;
	ISO9141_KW2000SETTINGS iso9141_kwp_settings_3;
	unsigned short iso_parity_3;
	unsigned short iso_msg_termination_3;
	ISO9141_KW2000SETTINGS iso9141_kwp_settings_4;
	unsigned short iso_parity_4;
}SFireSettings; 


typedef struct 
{
    CAN_SETTINGS can1;
    CAN_SETTINGS can2;
    unsigned short  network_enables;
    unsigned short network_enabled_on_boot;
    short iso15765_separation_time_offset;
    unsigned short perf_en;
    unsigned short misc_io_initial_ddr;
    unsigned short misc_io_initial_latch;
    unsigned short misc_io_report_period;
    unsigned short misc_io_on_report_events;
} SVCAN3Settings;


typedef struct // matching C structure
    {
	unsigned long StatusValue;  // 4
	unsigned long StatusMask;  // 4
	unsigned long Status2Value;  // 4
	unsigned long Status2Mask;  // 4
	unsigned long Header;	// 4
	unsigned long HeaderMask;  // 4
	unsigned long MiscData; // 4
	unsigned long MiscDataMask;  // 4
	unsigned long ByteDataMSB;	// 4
	unsigned long ByteDataLSB;	// 4
	unsigned long ByteDataMaskMSB;  // 4
	unsigned long ByteDataMaskLSB;  // 4
	unsigned long HeaderLength; // 4 
	unsigned long ByteDataLength; // 4
	unsigned long NetworkID;	// 4
	unsigned short FrameMaster;	// 2
	unsigned char bUseArbIdRangeFilter;
	unsigned char bStuff2;
	unsigned long ExpectedLength;
	unsigned long NodeID;
	}  spyFilterLong;

typedef struct
{
	unsigned long DeviceType;
	int Handle;
	int NumberOfClients;
	int SerialNumber;
	int MaxAllowedClients;
}NeoDevice;

// Constants used to calculate the timestamp
const double NEOVI_TIMESTAMP_2 = 0.1048576;
const double NEOVI_TIMESTAMP_1 = 0.0000016;

// Constants used to calculate the timestamp
const double NEOVI6_VCAN_TIMESTAMP_2 = 0.065536;
const double NEOVI6_VCAN_TIMESTAMP_1 = 0.000001;

// Win32 DLL prototypes
typedef int  (__stdcall *FINDNEODEVICES)(unsigned long DeviceTypes, NeoDevice *pNeoDevice, int *pNumDevices);
typedef int  (__stdcall *OPENNEODEVICE)(NeoDevice *pNeoDevice, int *hObject, unsigned char *bNetworkIDs, int bConfigRead, int bSyncToPC);
typedef int  (__stdcall *CLOSEPORT)(int hObject, int *pNumberOfErrors); 
typedef void (__stdcall *FREEOBJECT)(int hObject);

//Message Functions
typedef int  (__stdcall *GETMESSAGES)(int hObject, icsSpyMessage *pMsg, int * pNumberOfMessages, int * pNumberOfErrors); 
typedef int  (__stdcall *TXMESSAGES)(int hObject, icsSpyMessage *pMsg, int lNetworkID, int lNumMessages); 
typedef int  (__stdcall *WAITFORRXMSGS)(int hObject, unsigned int iTimeOut);
typedef int  (__stdcall *ENABLERXQUEUE)(int hObject, int iEnable);
typedef int  (__stdcall *GETTSFORMSG)(int hObject, icsSpyMessage *pMsg, double *pTimeStamp);
typedef void (__stdcall *GETISO15765STATUS)(int hObject, int lNetwork, int lClearTxStatus, 
											int lClearRxStatus, int *lTxStatus, int *lRxStatus);

typedef void (__stdcall *SETISO15765RXPARMS)(int hObject, int lNetwork, int lEnable, 
			                                spyFilterLong *pFF_CFMsgFilter, icsSpyMessage *pTxMsg, 
											int lCFTimeOutMs, int lFlowCBlockSize,
											int lUsesExtendedAddressing, int lUseHardwareIfPresent);

//Device Functions
typedef int (__stdcall *GETCONFIG)(int hObject, unsigned char * pData, int * lNumBytes);
typedef int (__stdcall *SENDCONFIG)(int hObject, unsigned char * pData, int lNumBytes); 
typedef int (__stdcall *GETFIRESETTINGS)(int hObject, SFireSettings *pSettings, int iNumBytes);
typedef int (__stdcall *SETFIRESETTINGS)(int hObject, SFireSettings *pSettings, int iNumBytes, int bSaveToEEPROM);
typedef int (__stdcall *GETVCAN3SETTINGS)(int hObject, SVCAN3Settings *pSettings, int iNumBytes);
typedef int (__stdcall *SETVCAN3SETTINGS)(int hObject, SVCAN3Settings *pSettings, int iNumBytes, int bSaveToEEPROM);
typedef int (__stdcall *SETBITRATE)(int hObject, int BitRate, int NetworkID);
typedef int (__stdcall *GETDEVICEPARMS)(int hObject, char *pParameter, char *pValues, short ValuesLength);
typedef int (__stdcall *SETDEVICEPARMS)(int hObject, char *pParmValue, int *pErrorIndex, int bSaveToEEPROM);

//Error Functions
typedef int (__stdcall *GETLASTAPIERROR)(int hObject, unsigned long *pErrorNumber);
typedef int (__stdcall *GETERRMSGS)(int hObject, int * pErrorMsgs, int * pNumberOfErrors);
typedef int (__stdcall *GETERRORINFO)(int lErrorNumber,char *szErrorDescriptionShort,  char *szErrorDescriptionLong,int * lMaxLengthShort,int * lMaxLengthLong,int * lErrorSeverity,int * lRestartNeeded);


//General Utility Functions
typedef int (__stdcall *VALIDATEHOBJECT)(int hObject);
typedef int (__stdcall *GETDLLVERSION)(void);
typedef int (__stdcall *GETSERIALNUMBER)(int hObject, unsigned int *iSerialNumber);
typedef int (__stdcall *STARTSOCKSERVER)(int hObject, int iPort);
typedef int (__stdcall *STOPSOCKSERVER)(int hObject);

//CoreMini Script functions
typedef int  (__stdcall *SCRIPTSTART)(int hObject, int iLocation);  
typedef int  (__stdcall *SCRIPTSTOP)(int hObject);  
typedef int  (__stdcall *SCRIPTLOAD)(int hObject, byte bin, unsigned long len_bytes, int iLocation);
////typedef int  (__stdcall *SCRIPTLOAD)(int hObject, const char *bin, unsigned long len_bytes, int iLocation);
typedef int  (__stdcall *SCRIPTCLEAR)(int hObject, int iLocation);
typedef int  (__stdcall *SCRIPTSTARTFBLOCK)(int hObject,unsigned int fb_index);
typedef int  (__stdcall *SCRIPTGETFBLOCKSTATUS)(int hObject, unsigned int fb_index, int *piRunStatus);
typedef int  (__stdcall *SCRIPTSTOPFBLOCK)(int hObject,unsigned int fb_index);
typedef int  (__stdcall *SCRIPTGETSCRIPTSTATUS)(int hObject, int *piStatus);
typedef int  (__stdcall *SCRIPTREADAPPSIGNAL)(int hObject, unsigned int iIndex, double *dValue);
typedef int  (__stdcall *SCRIPTWRITEAPPSIGNAL)(int hObject, unsigned int iIndex, double dValue);
typedef int  (__stdcall *SCRIPTREADRXMESSAGE)(int hObject, unsigned int iIndex,
											  icsSpyMessage *pRxMessageMask, icsSpyMessage *pRxMessageValue);
typedef int  (__stdcall *SCRIPTREADTXMESSAGE)(int hObject, unsigned int iIndex, icsSpyMessage *pTxMessage);
typedef int  (__stdcall *SCRIPTWRITERXMESSAGE)(int hObject, unsigned int iIndex,
											   const icsSpyMessage *pRxMessageMask, const icsSpyMessage *pRxMessageValue);
typedef int  (__stdcall *SCRIPTWRITETXMESSAGE)(int hObject, unsigned int iIndex, const icsSpyMessage *pTxMessage);
//typedef int  (__stdcall *SCRIPTREADISO15765TXMESSAGE)(int hObject, unsigned int iIndex, stCM_ISO157652_TxMessage *pTxMessage);
//typedef int  (__stdcall *SCRIPTWRITEISO15765TXMESSAGE)(int hObject, unsigned int iIndex, const stCM_ISO157652_TxMessage *pTxMessage);


//Deprecated (but still suppored in the DLL)
typedef int  (__stdcall *OPENPORTEX)(int lPortSerialNumber, int lPortType, int lDriverType, 
					                 int lIPAddressMSB, int lIPAddressLSBOrBaudRate,int bConfigRead, 
				                     unsigned char * bNetworkID, int * hObject);
typedef int  (__stdcall *OPENPORT)(int lPortNumber, int lPortType, int lDriverType, 
					               unsigned char *bNetworkID, unsigned char *bSCPIDs,  int * hObject);
typedef int (__stdcall *ENABLENETWORKCOM)(int hObject, int Enable);
typedef int (__stdcall *FINDCOMDEVICES)(int lDriverType,  int lGetSerialNumbers, int lStopAtFirst, int lUSBCommOnly,
							            int *p_lDeviceTypes, int *p_lComPorts, int *p_lSerialNumbers, int *lNumDevices); 

