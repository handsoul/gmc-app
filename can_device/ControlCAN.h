//ControlCAN.h@DSP Studio
//�ļ��汾��v1.0.2.1

#if !defined(__CONTROL__CAN__H__)
#define __CONTROL__CAN__H__

//�ӿڿ����Ͷ���
#define VCI_USBCAN1		3
#define VCI_USBCAN2		4

//�������÷���״ֵ̬
#define	STATUS_OK			1	//�����ɹ�
#define STATUS_ERR			0	//����ʧ��
#define STATUS_ERR2			-1	//�豸δ��


/*---------------------------����ZLG�ļ���������------------------------------*/
//���ȶ�����Ҫ�õ������ݽṹ
//USB-CAN�����������忨��Ϣ���������͡�
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

//����CAN��Ϣ֡���������͡�
typedef  struct  _VCI_CAN_OBJ{
	UINT	ID;
	UINT	TimeStamp;	 		 //ʱ���ʶ
	BYTE	TimeFlag;			 //�Ƿ�ʹ��ʱ���ʶ
	BYTE	SendType;			 //���ͱ�־��������δ��
	BYTE	RemoteFlag;			 //�Ƿ���Զ��֡
	BYTE	ExternFlag;			 //�Ƿ�����չ֡
	BYTE	DataLen;
	BYTE	Data[8];
	BYTE	Reserved[3];			//����
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//����CAN������״̬���������͡�
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

//���������Ϣ���������͡�
typedef struct _ERR_INFO{
	UINT	ErrCode;
	BYTE	Passive_ErrData[3];
	BYTE	ArLost_ErrData;
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//�����ʼ��CAN����������
typedef struct _INIT_CONFIG{
	DWORD	AccCode;
	DWORD	AccMask;
	DWORD	InitFlag;
	UCHAR	Filter;   //0,1��������֡��2��׼֡�˲���3����չ֡�˲���
	UCHAR	Timing0;
	UCHAR	Timing1;
	UCHAR	Mode;     //ģʽ��0��ʾ����ģʽ��1��ʾֻ��ģʽ,2�Բ�ģʽ
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

//����������Ҫ����ĺ�������
//����ControlCAN.h�еĺ����������庯��ָ������
//////////////////////////////////////////////////////////////////////////
//����ZLG�ĺ���
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

/*-------------------------����������������������-----------------------------*/
//���ȶ�����Ҫ�õ������ݽṹ
//USB-CAN�����������忨��Ϣ���������ͣ���������VCI_FindUsbDevice���������á�
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

//���峣���������
typedef struct _REF_NORMAL{
	BYTE Mode;		 //����ģʽ
	BYTE Filter;		 //�˲���ʽ
	DWORD AccCode;		//�����˲�������
	DWORD AccMask;		//�����˲�������
	BYTE kBaudRate;		//�����������ţ�0-SelfDefine,1-5Kbps(δ��),2-18����Ϊ��10kbps,20kbps,40kbps,50kbps,80kbps,100kbps,125kbps,200kbps,250kbps,400kbps,500kbps,666kbps,800kbps,1000kbps,33.33kbps,66.66kbps,83.33kbps
	BYTE Timing0;
	BYTE Timing1;
	BYTE CANRX_EN;		//������δ��
	BYTE UARTBAUD;		//������δ��
}VCI_REF_NORMAL,*PVCI_REF_NORMAL;	

//���岨�������ò�������
typedef struct _BAUD_TYPE{
	DWORD Baud;		//�洢������ʵ��ֵ
	BYTE SJW;		//ͬ����ת��ȣ�ȡֵ1-4
	BYTE BRP;		//Ԥ��Ƶֵ��ȡֵ1-64
	BYTE SAM;		//�����㣬ȡֵ0=����һ�Σ�1=��������
	BYTE PHSEG2_SEL;	//��λ�����2ѡ��λ��ȡֵ0=����λ�����1ʱ�����,1=�ɱ��
	BYTE PRSEG;		//����ʱ��Σ�ȡֵ1-8
	BYTE PHSEG1;		//��λ�����1��ȡֵ1-8
	BYTE PHSEG2;		//��λ�����2��ȡֵ1-8
}VCI_BAUD_TYPE,*PVCI_BAUD_TYPE;

//����Reference��������
typedef struct _REF_STRUCT{
	VCI_REF_NORMAL RefNormal;
	BYTE Reserved;
	VCI_BAUD_TYPE BaudType;
}VCI_REF_STRUCT,*PVCI_REF_STRUCT; 


//��������
typedef DWORD (CALLBACK*  LPVCI_GetReference2)(DWORD,DWORD,DWORD,DWORD,PVCI_REF_STRUCT);
typedef DWORD (CALLBACK*  LPVCI_SetReference2)(DWORD,DWORD,DWORD,DWORD,PVOID);
typedef DWORD (CALLBACK*  LPVCI_ResumeConfig)(DWORD,DWORD,DWORD);

typedef DWORD (CALLBACK*  LPVCI_ConnectDevice)(DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_UsbDeviceReset)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_FindUsbDevice)(PVCI_BOARD_INFO1);

#endif //#define __CONTROL__CAN__H__