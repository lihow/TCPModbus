// ClientDlg.cpp : implementation file

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_port = _T("502");
	m_server_addr = _T("127.0.0.1");//10.64.15.102//127.0.0.1
	m_1 = 0;
	m_2 = 0;
	m_3 = 0;
	m_4 = 0;
	m_7 =255;
	m_data_addr = 30;
	m_data_num = 2;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_LIST_SEND, m_send);
	DDX_Control(pDX, IDC_LIST_RECEIVE, m_receive);
	DDX_Control(pDX, IDC_COMBO_COMMAND, m_cmdword);
	DDX_Text(pDX, IDC_EDIT_DATA_NUM, m_data_num);
	DDX_Text(pDX, IDC_EDIT_DATA_ADDR, m_data_addr);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Text(pDX, IDC_EDIT_SERVER_ADDR, m_server_addr);
	DDX_Text(pDX, IDC_EDIT_M1, m_1);
	DDX_Text(pDX, IDC_EDIT_M2, m_2);
	DDX_Text(pDX, IDC_EDIT_M3, m_3);
	DDX_Text(pDX, IDC_EDIT_M4, m_4);
	DDX_Text(pDX, IDC_EDIT_M7, m_7);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSEND, OnButtonsend)
	ON_BN_CLICKED(IDC_BUTTONJOIN, OnButtonjoin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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
	m_cmdword.SetCurSel(2);
	// TODO: Add extra initialization here
	//pMysocket = new CMysocket(this); //创建套接字对象
	//if (!pMysocket->Create()) //创建套接字
	/*{
		delete pMysocket;
		MessageBox("套接字创建失败.");
		return false;
	}*/
	flag = 0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnButtonsend() 
{
	UpdateData(true);
	// TODO: Add your control notification handler code here
	CString str,temp;
	int i = 0;
	unsigned char SendBuf[12] = {0};
	//检查错误
	if( pMysocket == NULL || flag == 0)
	{
		MessageBox("请先建立连接!");
		return;
	}
	if (m_server_addr.IsEmpty()|m_port.IsEmpty())
	{
		MessageBox("请检查服务器地址及端口号!");
		return;
	}

	//处理数据
	m_data_addr = ((m_data_addr-1) & 0xffff);
	m_data_addr_low = (unsigned char)((m_data_addr) & 0x00ff);
	m_data_addr_high = (unsigned char)(((m_data_addr)>>8) & 0x00ff);
	m_data_num = (m_data_num & 0xffff);
	m_data_num_low = (unsigned char)((m_data_num) & 0x00ff);
	m_data_num_high = (unsigned char)(((m_data_num)>>8) & 0x00ff);
	i = m_cmdword.GetCurSel();
	switch(i)
	{
	case 0:
		SendBuf[7] = 0x01;
		break;
	case 1:
		SendBuf[7] = 0x02;
		break;
	case 2:
		SendBuf[7] = 0x03;
		break;
	case 3:
		SendBuf[7] = 0x04;
		break;
	case 4:
		SendBuf[7] = 0x05;
		break;
	case 5:
		SendBuf[7] = 0x06;
		break;
	case 6:
		SendBuf[7] = 0x0f;
		break;
	case 7:
		SendBuf[7] = 0x10;
		break;
	case 8:
		SendBuf[7] = 0x14;
		break;
	case 9:
		SendBuf[7] = 0x15;
		break;
	case 10:
		SendBuf[7] = 0x16;
		break;
	case 11:
		SendBuf[7] = 0x17;
		break;
	case 12:
		SendBuf[7] = 0x2B;
		break;
	default:
		MessageBox("命令字错误！");
		break;
	}
	
	//生成Modbus格式数据
	SendBuf[0] = m_1;//事务元标识符,高字节在前,低字节在后
	SendBuf[1] = m_2;
	SendBuf[2] = m_3;//协议标识符,高字节在前,低字节在后
	SendBuf[3] = m_4;
	SendBuf[4] = 0x00;//后续字节长度,高字节在前,低字节在后
	SendBuf[5] = 0x06;
	SendBuf[6] = m_7;//单元标识符
	//SendBuf[7] = 0x03;//m_cmdword;//命令字
	SendBuf[8] = m_data_addr_high;//数据起始地址,高字节在前,低字节在后
	SendBuf[9] = m_data_addr_low;
	SendBuf[10] = m_data_num_high;//数据长度,高字节在前,低字节在后
	SendBuf[11] = m_data_num_low;
	
	int num = pMysocket->Send(SendBuf,12);

	//成功则显示发送的数据
	i = 0;
	while (i <= 11)
	{
		temp.Format("%02X",SendBuf[i]);
		str = str + temp + ' ';
		i++;
	}
	int getcount = m_send.GetCount();
	m_send.InsertString(m_send.GetCount(),str);

	m_receive.SetWindowText("");
	m_receive.SetFocus();
}

void CClientDlg::ReceiveData()
{
	unsigned char ReceiveBuf[200];
	//接收传来的数据
	int receive_data_num =  pMysocket->Receive(ReceiveBuf,200);
	int i=0,j=0;
	CString str,str1,temp;

	while (i < receive_data_num)
	{
		temp.Format("%02X",ReceiveBuf[i]);
		if( ReceiveBuf[i] == 0xff )
			j = i;
		str = str + temp + ' ';
		i++;
	}
	//将16进制数据添加到列表框中
	//int getcount = m_receive.GetCount();
	m_receive.InsertString(m_receive.GetCount(),str);
	
	//十六进制转十进制输出
	j = j + 3;
	while (j < receive_data_num)
	{
		int temp_num = (int)(ReceiveBuf[j]<<8);
		temp_num = temp_num + (int)ReceiveBuf[j+1];
		temp.Format("%d",temp_num);
		str1 = str1 + temp + ' ';
		j = j + 2;
	}
	//int getcount1 = m_receive.GetCount();
	m_receive.InsertString(m_receive.GetCount(),str1);
}

void CClientDlg::OnButtonjoin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString servername = m_server_addr; //获取服务器地址
	int port = atoi(m_port); //获取端口
	
	if(pMysocket != NULL)
	{
		//delete pMysocket;
		pMysocket = NULL;
	}
	pMysocket = new CMysocket(this); //创建套接字对象
	if (!pMysocket->Create()) //创建套接字
	{
		delete pMysocket;
		pMysocket = NULL;
		MessageBox("套接字创建失败.");
		return;
	}
	if (!pMysocket->Connect(servername,port)) //连接服务器
	{
		MessageBox("连接服务器失败!");
		return;
	}
	flag = 1;
	//成功则显示已连接
	CString str;
	str.Format("Modbus TCP/IP 设备 %s 端口 %s 已连接！",m_server_addr,m_port);
	int getcount = m_send.GetCount();
	m_send.InsertString(m_send.GetCount(),str);

}
