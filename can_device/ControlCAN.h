//ControlCAN.h@DSP Studio
//文件版本：v1.0.2.1

#if !defined(__CONTROL__CAN__H__)
#define __CONTROL__CAN__H__

//接口卡类型定义
#define VCI_USBCAN1		3
#define VCI_USBCAN2		4

//函数调用返回状态值
#define	STATUS_OK			1	//操作成功
#define STATUS_ERR			0	//操作失败
#define STATUS_ERR2			-1	//设备未打开


/*---------------------------兼容ZLG的及数据类型------------------------------*/
//首先定义需要用到的数据结构
//USB-CAN总线适配器板卡信息的数据类型。
typedef  struct  _VCI_BOARD_INFO{
		USHORT	hw_Version;
		USHORT	fw_Version;
		USHORT	dr_Version;
		USHORT	in_Version;
		USHORT	irq_Num;
		BYTE	can_Num;
		CHAR	str_Serial_Num[20];
		CHAR	str_hw_Type[40];
		USHORT	Reserved[4];
} VCI_BOARD_INFO,*PVCI_BOARD_INFO;

//定义CAN信息帧的数据类型。
typedef  struct  _VCI_CAN_OBJ{
	UINT	ID;
	UINT	TimeStamp;	 		 //时间标识
	BYTE	TimeFlag;			 //是否使用时间标识
	BYTE	SendType;			 //发送标志。保留，未用
	BYTE	RemoteFlag;			 //是否是远程帧
	BYTE	ExternFlag;			 //是否是扩展帧
	BYTE	DataLen;
	BYTE	Data[8];
	BYTE	Reserved[3];			//保留
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//定义CAN控制器状态的数据类型。
typedef struct _VCI_CAN_STATUS{
	UCHAR	ErrInterrupt;
	UCHAR	regMode;
	UCHAR	regStatus;
	UCHAR	regALCapture;
	UCHAR	regECCapture; 
	UCHAR	regEWLimit;
	UCHAR	regRECounter; 
	UCHAR	regTECounter;
	DWORD	Reserved;
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

//定义错误信息的数据类型。
typedef struct _ERR_INFO{
	UINT	ErrCode;
	BYTE	Passive_ErrData[3];
	BYTE	ArLost_ErrData;
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//定义初始化CAN的数据类型
typedef struct _INIT_CONFIG{
	DWORD	AccCode;
	DWORD	AccMask;
	DWORD	InitFlag;
	UCHAR	Filter;   //0,1接收所有帧。2标准帧滤波，3是扩展帧滤波。
	UCHAR	Timing0;
	UCHAR	Timing1;
	UCHAR	Mode;     //模式，0表示正常模式，1表示只听模式,2自测模式
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

//接下来定义要导入的函数类型
//根据ControlCAN.h中的函数声明定义函数指针类型
//////////////////////////////////////////////////////////////////////////
//兼容ZLG的函数
typedef DWORD (CALLBACK*  LPVCI_OpenDevice)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_CloseDevice)(DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_InitCan)(DWORD,DWORD,DWORD,PVCI_INIT_CONFIG);

typedef DWORD (CALLBACK*  LPVCI_ReadBoardInfo)(DWORD,DWORD,PVCI_BOARD_INFO);
typedef DWORD (CALLBACK*  LPVCI_ReadErrInfo)(DWORD,DWORD,DWORD,PVCI_ERR_INFO);
typedef DWORD (CALLBACK*  LPVCI_ReadCanStatus)(DWORD,DWORD,DWORD,PVCI_CAN_STATUS);

typedef DWORD (CALLBACK*  LPVCI_GetReference)(DWORD,DWORD,DWORD,DWORD,PVOID);
typedef DWORD (CALLBACK*  LPVCI_SetReference)(DWORD,DWORD,DWORD,DWORD,PVOID);

typedef ULONG (CALLBACK*  LPVCI_GetReceiveNum)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_ClearBuffer)(DWORD,DWORD,DWORD);

typedef DWORD (CALLBACK*  LPVCI_StartCAN)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_ResetCAN)(DWORD,DWORD,DWORD);

typedef ULONG (CALLBACK*  LPVCI_Transmit)(DWORD,DWORD,DWORD,PVCI_CAN_OBJ,ULONG);
typedef ULONG (CALLBACK*  LPVCI_Receive)(DWORD,DWORD,DWORD,PVCI_CAN_OBJ,ULONG,INT);

/*-------------------------其他函数及数据类型描述-----------------------------*/
//首先定义需要用到的数据结构
//USB-CAN总线适配器板卡信息的数据类型，该类型在VCI_FindUsbDevice函数中引用。
typedef  struct  _VCI_BOARD_INFO1{
		USHORT	hw_Version;
		USHORT	fw_Version;
		USHORT	dr_Version;
		USHORT	in_Version;
		USHORT	irq_Num;
		BYTE	can_Num;
                BYTE    reserved;
		CHAR	str_Serial_Num[8];
		CHAR	str_hw_Type[16];
		CHAR	str_USB_Serial[4][4];
} VCI_BOARD_INFO1,*PVCI_BOARD_INFO1;

//定义常规参数类型
typedef struct _REF_NORMAL{
	BYTE Mode;		 //工作模式
	BYTE Filter;		 //滤波方式
	DWORD AccCode;		//接收滤波验收码
	DWORD AccMask;		//接收滤波屏蔽码
	BYTE kBaudRate;		//波特率索引号，0-SelfDefine,1-5Kbps(未用),2-18依次为：10kbps,20kbps,40kbps,50kbps,80kbps,100kbps,125kbps,200kbps,250kbps,400kbps,500kbps,666kbps,800kbps,1000kbps,33.33kbps,66.66kbps,83.33kbps
	BYTE Timing0;
	BYTE Timing1;
	BYTE CANRX_EN;		//保留，未用
	BYTE UARTBAUD;		//保留，未用
}VCI_REF_NORMAL,*PVCI_REF_NORMAL;	

//定义波特率设置参数类型
typedef struct _BAUD_TYPE{
	DWORD Baud;		//存储波特率实际值
	BYTE SJW;		//同步跳转宽度，取值1-4
	BYTE BRP;		//预分频值，取值1-64
	BYTE SAM;		//采样点，取值0=采样一次，1=采样三次
	BYTE PHSEG2_SEL;	//相位缓冲段2选择位，取值0=由相位缓冲段1时间决定,1=可编程
	BYTE PRSEG;		//传播时间段，取值1-8
	BYTE PHSEG1;		//相位缓冲段1，取值1-8
	BYTE PHSEG2;		//相位缓冲段2，取值1-8
}VCI_BAUD_TYPE,*PVCI_BAUD_TYPE;

//定义Reference参数类型
typedef struct _REF_STRUCT{
	VCI_REF_NORMAL RefNormal;
	BYTE Reserved;
	VCI_BAUD_TYPE BaudType;
}VCI_REF_STRUCT,*PVCI_REF_STRUCT; 


//其他函数
typedef DWORD (CALLBACK*  LPVCI_GetReference2)(DWORD,DWORD,DWORD,DWORD,PVCI_REF_STRUCT);
typedef DWORD (CALLBACK*  LPVCI_SetReference2)(DWORD,DWORD,DWORD,DWORD,PVOID);
typedef DWORD (CALLBACK*  LPVCI_ResumeConfig)(DWORD,DWORD,DWORD);

typedef DWORD (CALLBACK*  LPVCI_ConnectDevice)(DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_UsbDeviceReset)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_FindUsbDevice)(PVCI_BOARD_INFO1);

#endif //#define __CONTROL__CAN__H__