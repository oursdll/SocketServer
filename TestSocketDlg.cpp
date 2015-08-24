// TestSocketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestSocket.h"
#include "TestSocketDlg.h"

#include "winsock2.h"

#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
const	UINT	WM_SOCKET_MSG=(WM_USER+7777);

BOOL			gm_bConnect;

BOOL			gm_bListen=FALSE;
CWinThread*		gm_pThread;
UINT			Thread_Listen(LPVOID pParam);

SOCKADDR_IN		gm_sockaddrServer;
SOCKET			gm_socketListen;
SOCKET			gm_socketClient;//[256];
int				gm_nClientNum;
int				gm_i;

CEdit*			gm_pEditState;
CEdit*			gm_pEditRecvNum;
CEdit*			gm_pEditDataRecv;
CString			gm_strEditData,gm_strDataRecv,gm_strtemp;
DWORD			gm_dwRecvNum=0;


union data
{
	int				pIntbuf[40000];
	short			pbuf[80000];
	char			pchbuf[160000];
} gm_data;

char gm_pSbuf[512];

HWND gm_hWnd;

UINT Thread_Listen(LPVOID pParam)
{
	gm_strEditData="";

	while(gm_bListen)
	{
		if(gm_socketClient==INVALID_SOCKET)
			gm_socketClient=accept(gm_socketListen,NULL,NULL);//(struct sockaddr far *)&gm_sockaddrServer,(int far *)sizeof(SOCKADDR_IN));
		
		if(gm_socketClient==INVALID_SOCKET)
		{
			continue;
		}		

		
		if(WSAAsyncSelect(gm_socketClient,gm_hWnd,WM_SOCKET_MSG,FD_CLOSE|FD_READ)!=0)
		{
			gm_socketClient=INVALID_SOCKET;
			continue;
		}

		gm_pEditState->SetWindowText("Connect");

		gm_bConnect=TRUE;

		gm_bListen=FALSE;

//		::SendMessage(gm_hWnd,WM_COMMAND,IDC_SENDDATA,NULL);


	}

	AfxEndThread(0);

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSocketDlg dialog

CTestSocketDlg::CTestSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSocketDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestSocketDlg)
	m_nRouteNum = 0;
	m_nSFrequency = 0;
	m_nFrequency = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	gm_nClientNum=0;

	m_iDNo=0;

	m_nRouteNum=16;

	m_nSFrequency=1000;

	m_nFrequency=10;


}

void CTestSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSocketDlg)
	DDX_Control(pDX, IDC_SENDNUM, m_CtrSendNum);
	DDX_Control(pDX, IDC_RECVNUM, m_CtrRecvNum);
	DDX_Control(pDX, IDC_SERVERINFO, m_CtrServerInfo);
	DDX_Control(pDX, IDC_DATASEND, m_CtrDataSend);
	DDX_Control(pDX, IDC_STATE, m_CtrState);
	DDX_Text(pDX, IDC_RN, m_nRouteNum);
	DDX_Text(pDX, IDC_SFREQUENCY, m_nSFrequency);
	DDX_Text(pDX, IDC_FREQUENCY, m_nFrequency);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestSocketDlg, CDialog)
	//{{AFX_MSG_MAP(CTestSocketDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEANUP, OnCleanup)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_AUTOSEND, OnAutosend)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSocketDlg message handlers

BOOL CTestSocketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	gm_hWnd=m_hWnd;

	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);

	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested=MAKEWORD(2,2);
	if(WSAStartup(wVersionRequested,&wsaData)!=0)
	{
		AfxMessageBox("Startup Socket failed!");
		exit(0);
	}

	if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();
		AfxMessageBox("Socket version error!");
		exit(0);
	}

	gm_socketListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(gm_socketListen==INVALID_SOCKET)
	{
		AfxMessageBox("Create socket failed!");
		exit(0);
	}

	int nPort=8000;

	gm_sockaddrServer.sin_family=AF_INET;
	gm_sockaddrServer.sin_addr.s_addr=htonl(INADDR_ANY);
	gm_sockaddrServer.sin_port=htons(nPort);	
	if(bind(gm_socketListen,(LPSOCKADDR)&gm_sockaddrServer,sizeof(struct sockaddr))==SOCKET_ERROR)
	{
		AfxMessageBox("Bind Socket failed!");
		exit(0);
	}

	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuf[256];

	if (gethostname(szBuf, sizeof(szBuf))==SOCKET_ERROR)
	{
		AfxMessageBox("gethostname() error!");
		exit(0);
	}

	LPHOSTENT lpHostEntry;
	lpHostEntry = gethostbyname(szBuf);

	CString str;

	str.Format("Server %s addr %s waiting on port %d ",
			szBuf, inet_ntoa(*(LPIN_ADDR)lpHostEntry->h_addr), nPort);
	m_CtrServerInfo.SetWindowText(str);

	


	if(listen(gm_socketListen,10)!=0)
	{
		AfxMessageBox("Listen failed!");
		exit(0);
	}

	gm_pEditState=(CEdit*)GetDlgItem(IDC_STATE);
	gm_pEditDataRecv=(CEdit*)GetDlgItem(IDC_DATARECV);

	gm_pEditRecvNum=(CEdit*)GetDlgItem(IDC_RECVNUM);
	m_CtrDataSend.SetWindowText("0123456789ABCDEDFHIJKLMNOPQRSTUVWXYZ");

	m_CtrState.SetWindowText("Listen......");
	gm_socketClient=INVALID_SOCKET;
	gm_bListen=TRUE;
	gm_bConnect=FALSE;
	gm_pThread=AfxBeginThread(&Thread_Listen,NULL);
	
//	SetTimer(1,500,NULL);


	gm_nCurPos=0;
	gm_nDataNum=0;
	

//	SetTimer(2,100,NULL);

	m_dSFrequency=m_nSFrequency;
	m_dFrequency=m_nFrequency;
	m_dCoeff=2.0/(m_dSFrequency/m_dFrequency);

	m_nPackTimes=m_nSFrequency/10;

	m_nPackSize= sizeof(int) *(m_nRouteNum*10+4);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestSocketDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSocketDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestSocketDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CTestSocketDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int m_SendpacketHead,m_SendpacketNum;
	m_SendpacketHead = 2;
	m_SendpacketNum = ((m_nPackSize*m_nPackTimes ) / 100);
	if(!gm_bConnect)
		return;

	for(m_i=0;m_i<(m_nPackTimes/100);m_i++)
	{
		m_nSA=(m_i*m_nPackSize)/4;
		gm_data.pIntbuf[m_nSA] = 0;
		gm_data.pIntbuf[m_nSA+1]=0x8fffffff;
		gm_data.pIntbuf[m_nSA+2]=m_iDNo/65536;
		gm_data.pIntbuf[m_nSA+3]=m_iDNo%65536;

		for(m_ii=0;m_ii<10;m_ii++)
		{
			for(m_j=0;m_j<m_nRouteNum;m_j++)
			{
				gm_data.pIntbuf[m_nSA+4+m_ii*m_nRouteNum+m_j]=3000*sin((m_iDNo*m_nPackTimes+m_i*10+m_ii)*m_dCoeff*3.1415926);
			}
		}

		gm_data.pIntbuf[m_nSA+4+m_nRouteNum*10]=0x0000;
		
	}

	m_iDNo=m_iDNo+1;

	m_strSendNum.Format("%d",m_iDNo);
	m_CtrSendNum.SetWindowText(m_strSendNum);
	_tcscpy(&gm_data.pchbuf[4], gm_data.pchbuf);	
	gm_data.pchbuf[0] = m_SendpacketNum;
	gm_data.pchbuf[1] = m_SendpacketNum >> 8;
	gm_data.pchbuf[2] = m_SendpacketNum >> 16;
	gm_data.pchbuf[3] = m_SendpacketNum >> 24;

	if(!send(gm_socketClient,&gm_data.pchbuf[0],(m_nPackSize*m_nPackTimes)/100+4,0)==SOCKET_ERROR)
	{
		AfxMessageBox("Send failed!");
	}


	
	CDialog::OnTimer(nIDEvent);
}

int NETBUFSIZE=8192;
char gm_pRbuf[1024];
unsigned char gm_pData[8192];
int gm_pi;
int gm_nDataLen;


void CTestSocketDlg::NetParseData()
{
	gm_nCurPos=0;
	while((gm_nCurPos+6)<=gm_nDataNum)
	{
		m_nLen=gm_pRbuf[gm_nCurPos+2];
		m_nLen=m_nLen*256+gm_pRbuf[gm_nCurPos+3];
		if((gm_pData[gm_nCurPos]==0xFF)
			&&(gm_pData[gm_nCurPos+(m_nLen-2)]==0x00)&&(gm_pData[gm_nCurPos+(m_nLen-1)]==0x00))
		{
			if((gm_nCurPos+m_nLen)>gm_nDataNum)
				return;

			if(gm_pData[gm_nCurPos+1]==0x01)
			{
				SendDeviceInfo();	
				NetMoveData(m_nLen);
			}
			else if(gm_pData[gm_nCurPos+1]==0x02)
			{
				SendStateInfo();	
				NetMoveData(m_nLen);
				OnAutosend();
			}
			else if(gm_pData[gm_nCurPos+1]==0x0f)
			{
				if((gm_pData[gm_nCurPos+4]==0xff)&&(gm_pData[gm_nCurPos+5]==0xff))
				{
					OnAutosend();	
					NetMoveData(m_nLen);
				}
				else if((gm_pData[gm_nCurPos+4]==0x00)&&(gm_pData[gm_nCurPos+5]==0x00))
				{
					OnStop();	
					NetMoveData(m_nLen);
				}
			}

			
			
		}
		else
		{
			gm_nCurPos=gm_nCurPos+1;
			continue;
		}
	
	}		
}

void CTestSocketDlg::NetMoveData(int nMove)
{
/*
	for(gm_pi=(gm_nCurPos+gm_nPackSize);gm_pi<gm_nDataNum;gm_pi++)
	{
		gm_pData[gm_pi-(gm_nCurPos+gm_nPackSize)]=gm_pData[gm_pi];
	}
	gm_nDataNum=gm_nDataNum-(gm_nCurPos+gm_nPackSize);
	gm_nCurPos=0;
*/
	gm_nDataNum=gm_nDataNum-(gm_nCurPos+nMove);
	if(gm_nDataNum<0)
		gm_nDataNum=0;

	for(gm_pi=0;gm_pi<gm_nDataNum;gm_pi++)
	{
		gm_pData[gm_pi]=gm_pData[(gm_nCurPos+nMove)+gm_pi];
	}
	
	gm_nCurPos=0;	
}

BOOL CTestSocketDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_SOCKET_MSG)
    {
        if(WSAGETSELECTEVENT(pMsg->lParam) == FD_CLOSE)
        {
			m_CtrState.SetWindowText("Listen......");
			gm_socketClient=INVALID_SOCKET;
			gm_bListen=TRUE;
			gm_bConnect=FALSE;
			gm_pThread=AfxBeginThread(&Thread_Listen,NULL);
        }
		if(WSAGETSELECTEVENT(pMsg->lParam) == FD_READ)
        {
			gm_nDataLen=recv(gm_socketClient,&gm_pRbuf[0],1024,0);
			if(gm_nDataLen>0)
			{
				

				if((gm_nDataNum+gm_nDataLen)>=NETBUFSIZE)
				{
					gm_nDataNum=0;
					gm_nCurPos=0;
				}

				for(gm_pi=0;gm_pi<gm_nDataLen;gm_pi++)
					gm_pData[gm_nDataNum+gm_pi]=gm_pRbuf[gm_pi];

				gm_nDataNum=gm_nDataNum+gm_nDataLen;

							
				if(gm_nDataNum>=6)
					NetParseData();
					
				

			}

        }

        return TRUE;
    }


	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CTestSocketDlg::SendDeviceInfo()
{
	
	int p,i,j;

	
	CString strType="UB-16B";
	CString strResolution="0.5uv";
	short nRouteNum=m_nRouteNum;
	short nDataPackSize=m_nPackSize;
	short nPackSize=34;

	for(i=0;i<nPackSize;i++)
		gm_pSbuf[i]=0x00;

	gm_pSbuf[0]=0XFF;
	gm_pSbuf[1]=0X81;//发送放大器配置信息
	gm_pSbuf[2]=nPackSize/256;//包长度
	gm_pSbuf[3]=nPackSize%256;

	p=4;//放大器型号
	for(i=0;i<strType.GetLength();i++)
		gm_pSbuf[p+i]=strType.GetAt(i);

	p=14;//放大器序列号
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X00;
	gm_pSbuf[p+2]=0X00;
	gm_pSbuf[p+3]=0X00;

	p=18;//客户代码
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X00;
	gm_pSbuf[p+2]=0X00;
	gm_pSbuf[p+3]=0X00;

	p=22;//数据位数
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X10;

	p=24;//数据有效位数
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X10;

	p=26;//通道数
	gm_pSbuf[p+0]=nRouteNum/256;
	gm_pSbuf[p+1]=nRouteNum%256;

	p=28;//数据包长度
	gm_pSbuf[p+0]=nDataPackSize/256;
	gm_pSbuf[p+1]=nDataPackSize%256;

	p=30;//包采样次数
	gm_pSbuf[p+0]=nDataPackSize/256;
	gm_pSbuf[p+1]=nDataPackSize%256;


	
	p=32;//结束标志
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X00;

	if(send(gm_socketClient,&gm_pSbuf[0],nPackSize,0)==SOCKET_ERROR)
	{
		AfxMessageBox("Send info failed!");
		return FALSE;
	}

	return TRUE;
}


BOOL CTestSocketDlg::SendStateInfo()
{
	
	int p,i,j;

	
	CString strType="UB-16B";
	CString strResolution="0.5uv";
	short nRouteNum=m_nRouteNum;
	short nDataPackSize=m_nPackSize;
	short nPackSize=34;

	for(i=0;i<nPackSize;i++)
		gm_pSbuf[i]=0x00;

	gm_pSbuf[0]=0XFF;
	gm_pSbuf[1]=0X81;//发送放大器配置信息
	gm_pSbuf[2]=nPackSize/256;//包长度
	gm_pSbuf[3]=nPackSize%256;

	p=4;//放大器型号
	for(i=0;i<strType.GetLength();i++)
		gm_pSbuf[p+i]=strType.GetAt(i);

	p=14;//放大器序列号
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X00;
	gm_pSbuf[p+2]=0X00;
	gm_pSbuf[p+3]=0X00;

	p=18;//客户代码
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X00;
	gm_pSbuf[p+2]=0X00;
	gm_pSbuf[p+3]=0X00;

	p=22;//数据位数
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X10;

	p=24;//数据有效位数
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X10;

	p=26;//通道数
	gm_pSbuf[p+0]=nRouteNum/256;
	gm_pSbuf[p+1]=nRouteNum%256;

	p=28;//数据包长度
	gm_pSbuf[p+0]=nDataPackSize/256;
	gm_pSbuf[p+1]=nDataPackSize%256;

	p=30;//包采样次数
	gm_pSbuf[p+0]=nDataPackSize/256;
	gm_pSbuf[p+1]=nDataPackSize%256;


	
	p=32;//结束标志
	gm_pSbuf[p+0]=0X00;
	gm_pSbuf[p+1]=0X00;

	if(send(gm_socketClient,&gm_pSbuf[0],nPackSize,0)==SOCKET_ERROR)
	{
		AfxMessageBox("Send info failed!");
		return FALSE;
	}

	return TRUE;
}

void CTestSocketDlg::OnCleanup() 
{
	// TODO: Add your control notification handler code here
	gm_pEditDataRecv->SetWindowText("");
	m_CtrRecvNum.SetWindowText("0");
	gm_strEditData="";
	gm_dwRecvNum=0;
}

void CTestSocketDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	m_CtrDataSend.GetWindowText(m_strDataSend);
	INT DataSendlength = m_strDataSend.GetLength();
	//CString txtDatasendlength;
	//txtDatasendlength.Format("00%d", DataSendlength);
	//
	//_tcscpy(m_pbuf, (CString)DataSendlength);
	
	m_pbuf[0] = (byte)DataSendlength;
	m_pbuf[1] = (byte)(DataSendlength >> 8);
	m_pbuf[2] = (byte)(DataSendlength >> 16);
	m_pbuf[3] = (byte)(DataSendlength >> 24);
	_tcscpy(&m_pbuf[4],m_strDataSend);
	if(send(gm_socketClient,&m_pbuf[0],m_strDataSend.GetLength()+4,0)==SOCKET_ERROR)
	{
		AfxMessageBox("Send failed!");
		return;
	}
}


void CTestSocketDlg::OnApply() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_dSFrequency=m_nSFrequency;
	m_dFrequency=m_nFrequency;
	m_dCoeff=2.0/(m_dSFrequency/m_dFrequency);

	m_nPackTimes=m_nSFrequency/10;

	m_nPackSize=m_nRouteNum*20+8;


}

void CTestSocketDlg::OnAutosend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	m_dSFrequency=m_nSFrequency;
	m_dFrequency=m_nFrequency;
	m_dCoeff=2.0/(m_dSFrequency/m_dFrequency);

	m_nPackTimes=m_nSFrequency/10;

	m_nPackSize=m_nRouteNum*20+8;

	SetTimer(2,10,NULL);
}

void CTestSocketDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	KillTimer(2);
}
