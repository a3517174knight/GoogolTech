// CompareOutPutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CompareOutPut.h"
#include "CompareOutPutDlg.h"
#include "gts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(lib,"gts.lib")

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCompareOutPutDlg dialog




CCompareOutPutDlg::CCompareOutPutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompareOutPutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompareOutPutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCompareOutPutDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CCompareOutPutDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_1CRD, &CCompareOutPutDlg::OnBnClickedButton1crd)
	ON_BN_CLICKED(IDC_BUTTON_2CRD, &CCompareOutPutDlg::OnBnClickedButton2crd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CCompareOutPutDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CCompareOutPutDlg message handlers

BOOL CCompareOutPutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(1,10,NULL);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCompareOutPutDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCompareOutPutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCompareOutPutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCompareOutPutDlg::OnBnClickedButtonOpen()
{
	short rtn;
	rtn = GT_Open(0);							 // ���˶�������
	rtn = GT_Reset(0);							 // ��λ�˶�������
	rtn = GT_LoadConfig(0,"test.cfg");			 // ���ؿ����������ļ�
	rtn = GT_ClrSts(0, 1, 4);					 // ���1~4�����״̬
	for(short i=1;i<=4;++i)
	{
		rtn = GT_AxisOn(0, i);					 // ʹ���˶���
	}
	rtn = GT_ZeroPos(0, 1, 4);
}

void CCompareOutPutDlg::OnBnClickedButton1crd()
{
	short rtn;
	short AXIS = 1;
	T2DComparePrm prm;
	rtn = GT_2DCompareMode(0,0,COMPARE2D_MODE_1D);   //ʹ�ö�άλ�ñȽϵ�1άģʽ
	prm.encx = 1;			//1άģʽʱ�����ֵû���ã����Ǳ�����һ����0ֵ
	prm.ency = 1;			//��1����Ϊ�Ƚ�Դ
	prm.maxerr = 3;			//������pulse
	prm.outputType = 0;		//�������
	prm.source = 1;			//�ⲿ���������
	prm.startLevel = 0;		//���ó�ʼ��ƽ
	prm.threshold = 0;		//���ŵ������ֵ���û�������ģ�ȡ0
	prm.time = 500;			//�������us
	rtn = GT_2DCompareSetPrm(0,0,&prm);
	//rtn = GT_2DCompareMode(0,1,COMPARE2D_MODE_1D);	//ʹ�ö�άλ�ñȽϵ�1άģʽ

	T2DCompareData databuf[5];
	databuf[0].px = 0;
	databuf[0].py = 10000;
	databuf[1].px = 0;
	databuf[1].py = 20000;
	rtn = GT_2DCompareData(0,0,2,databuf,0); //���ñȽ����ݣ�ֻ������y�����ݣ�x������ȡ0

	rtn = GT_2DCompareStart(0,0);

	//��λ�˶�
	TTrapPrm trap;
	rtn = GT_PrfTrap(0,AXIS);					//���óɵ�λģʽ
	rtn = GT_GetTrapPrm(0,AXIS, &trap);			//��ȡ��λ�˶�����
	trap.acc = 0.25;
	trap.dec = 0.125;
	trap.smoothTime = 25;						
	rtn = GT_SetTrapPrm(0,AXIS, &trap);			// ���õ�λ�˶�����
	rtn = GT_SetPos(0,AXIS, 20000L);			// ����AXIS���Ŀ��λ��
	rtn = GT_SetVel(0,AXIS, 50);				// ����AXIS���Ŀ���ٶ�
	rtn = GT_Update(0,1<<(AXIS-1));				// ����AXIS����˶�
}

void CCompareOutPutDlg::OnBnClickedButton2crd()
{
	short rtn;
	T2DCompareData databuf[3] ;					//��άλ�ñȽ��������
	T2DComparePrm prm;							//��άλ�ñȽ��������
	rtn = GT_2DCompareClear(0, 0);              //��ն�άλ�ñȽ��������
	rtn = GT_2DCompareMode(0, 0,				//ͨ���� 0�� HSIO0 ͨ���� 1�� HSIO1
		COMPARE2D_MODE_2D);						//������ά�Ƚ����ģ�飬Ϊ��άλ�ñȽϷ�ʽ
	prm.encx=1;     							//1�����Ƚ���x
	prm.ency=2;     							//2�����Ƚ���y
	prm.maxerr=300; 							 //����������(��λ:pulse)
	prm.outputType=0;							 //�������: 0����;1��ƽ
	prm.source=1;   							 //�Ƚ�Դ:0�滮,1������
	prm.startLevel=0;							 //��ʼ��ƽ�Ƿ�ת��0��λ��ƽ��1��ת
	prm.threshold=0;							 //�����㷨��ֵ
	prm.time=500;   							 //�������(��λus)
	rtn = GT_2DCompareSetPrm(0, 0,                 //ͨ���� 0�� HSIO0 ͨ���� 1�� HSIO1
		&prm);                                   
	databuf[0].px = 10000;                       //��һ�Ƚϵ�(10000,10000)
	databuf[0].py = 10000;
	databuf[1].px = 20000;                       //�ڶ��Ƚϵ�(20000,20000)
	databuf[1].py = 20000;
	databuf[2].px = 35000;                       //�����Ƚϵ�(35000,50000)
	databuf[2].py = 35000;
	rtn = GT_2DCompareData(0, 0,		// ͨ��0
		3,					// ��Ҫ���бȽϵ����ݸ���
		databuf,			// ���������ַ
		0);					// ʹ��FIFO0
	rtn = GT_2DCompareStart(0, 0);   //����λ�ñȽ����

	//��������ϵ
	long space;
	TCrdPrm crdPrm;
	memset(&crdPrm,0,sizeof(crdPrm));
	crdPrm.dimension = 2;              			 // ������ά������ϵ
	crdPrm.synVelMax = 500;            			 // ����ϵ�����ϳ��ٶ���: 500 pulse/ms
	crdPrm.synAccMax = 2;              			 // ����ϵ�����ϳɼ��ٶ���: 2 pulse/ms^2
	crdPrm.evenTime = 0;               			 // ����ϵ����С����ʱ��Ϊ0
	crdPrm.profile[0] = 1;             			 // �滮��1��Ӧ��X��                       
	crdPrm.profile[1] = 2;             			 // �滮��2��Ӧ��Y��                     
	crdPrm.setOriginFlag = 1;          			 // ��Ҫ���üӹ�����ϵԭ��λ��
	crdPrm.originPos[0] = 0;           			 // �ӹ�����ϵԭ��λ����(0,0)�������������ϵԭ���غ�
	crdPrm.originPos[1] = 0;
	rtn = GT_SetCrdPrm(0, 1, &crdPrm);
	rtn = GT_CrdClear(0, 1, 0);          		 // ���������ݴ�������ϵ1��FIFO0�У�����Ҫ��������˻������е�����
	rtn = GT_LnXY(0, 
		1,							   			 // �ò岹�ε�����ϵ������ϵ1
		10000, 10000,				   			 // �ò岹�ε��յ�����(30000, 30000)
		100,						   			 // �ò岹�ε�Ŀ���ٶȣ�100pulse/ms
		0.1,						   			 // �岹�εļ��ٶȣ�0.1pulse/ms^2
		100,									 // �յ��ٶ�Ϊ100
		0);						 	   			 // ������ϵ1��FIFO0���������ݸ�ֱ�߲岹����
	rtn = GT_LnXY(0, 1, 35000, 35000, 100,
		0.1, 0, 0);
	rtn = GT_CrdSpace(0, 1, &space, 0);			// ��ѯ����ϵ1��FIFO0��ʣ��Ŀռ�
	rtn = GT_CrdStart(0, 1, 0);					// ��������ϵ1��FIFO0�Ĳ岹�˶�
}

void CCompareOutPutDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	short rtn;
	short pStatus, pFifo, pFifoCount, pBufCount;
	long pCount;
	double prfPos[4];
	CString strTemp;
	rtn = GT_GetPrfPos(0,1,prfPos,4,NULL);           // ��1~4��Ĺ滮λ��
	rtn = GT_2DCompareStatus(0, 0, &pStatus, &pCount, &pFifo, &pFifoCount, 0);

	strTemp.Format(_T("%.3f"),prfPos[0]);
	SetDlgItemText(IDC_STATIC_PRFPOS_X,strTemp);
	strTemp.Format(_T("%.3f"),prfPos[1]);
	SetDlgItemText(IDC_STATIC_PRFPOS_Y,strTemp);

	if (pStatus==0 &&(prfPos[0]||prfPos[1]!=0)){ strTemp.Format(_T("���ڱȽ�")); }
	else if(pStatus==1) {strTemp.Format(_T("�Ƚ����"));}
	else {strTemp.Format(_T("δ���бȽ�"));}
	SetDlgItemText(IDC_STATIC_Status,strTemp);

	strTemp.Format(_T("%ld"),pCount);
	SetDlgItemText(IDC_STATIC_Count,strTemp);

	CDialog::OnTimer(nIDEvent);
}

void CCompareOutPutDlg::OnBnClickedButtonReset()
{
	short rtn;
	rtn = GT_Reset(0);
}