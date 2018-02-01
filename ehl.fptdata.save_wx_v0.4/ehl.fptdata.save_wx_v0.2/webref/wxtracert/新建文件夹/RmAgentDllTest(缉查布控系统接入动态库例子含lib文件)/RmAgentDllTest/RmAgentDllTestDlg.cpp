// RmAgentDllTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RmAgentDllTest.h"
#include "RmAgentDllTestDlg.h"
#include ".\rmagentdlltestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CRmAgentDllTestDlg 对话框



CRmAgentDllTestDlg::CRmAgentDllTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRmAgentDllTestDlg::IDD, pParent)
	, m_kkbh(_T(""))
	, m_fxlx(_T(""))
	, m_cdh(0)
	, m_hostport(_T(""))
	, m_jkxlh(_T(""))
	, m_jkid(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);


	this->m_kkbh = "320200100166";// "140300100063";
    this->m_fxlx = "1";
	this->m_cdh = 1;
	m_hostport = "192.168.0.173:9080"; // "10.2.41.30:8080"; //  "10.196.80.70:9080";  // "10.40.34.3:9080";  // "10.98.222.47:9080"; // "10.61.251.12:80"; // "10.35.18.18:9080"; //  "10.2.41.30:8080"; // "10.97.47.16:9080"; //  "10.150.247.45:9080";  // "10.2.41.30:8080"; // "10.38.199.171:9080"; // "10.2.41.30:8080";  // "10.38.199.171:9080";  "10.61.132.7:80";// "61.177.142.154:9080";

	m_jkid = _T("62C01");

    m_jkxlh = _T("7A1E1D0C020703050F15020100020902000609010A0917ECE8356D72692E636E");


//	m_jkxlh = _T("7A1E1D0D06070305011502010002090200060904020A17E1B03F6D72692E636E");

//	m_jkxlh = _T("7A1E1D0A010703050A1502010002090200060904020C179395376D72692E636E");


	m_passinfo.hphm="川AS138R";
	m_passinfo.hpzl="02";
	m_passinfo.gcsj="2014-04-18 18:36:55";
	m_passinfo.clsd=93;
	m_passinfo.csys="J";
	m_passinfo.cllx="K33";
	m_passinfo.hpys="2";


	m_passinfo.tplj = "http://10.10.21.14:8008/cgi-bin/get/jcbksystem?vehicleaccessid=";
	m_passinfo.tp1="6826977&1.jpg";
}

void CRmAgentDllTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KKBH_EDIT, m_kkbh);
	DDX_Text(pDX, IDC_FXLX_EDIT, m_fxlx);
	DDX_Text(pDX, IDC_CDH_EDIT, m_cdh);
	DDV_MinMaxLong(pDX, m_cdh, 1, 100);
	DDX_Text(pDX, IDC_HOSTPORT_EDIT, m_hostport);
	DDX_Text(pDX, IDC_XLH_EDIT, m_jkxlh);
	DDX_Text(pDX, IDC_JKID_EDIT, m_jkid);
}

BEGIN_MESSAGE_MAP(CRmAgentDllTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUT_INIT, OnBnClickedButInit)
	ON_BN_CLICKED(IDC_BUT_PASS, OnBnClickedButPass)
	ON_BN_CLICKED(IDC_BUT_PICUP, OnBnClickedButPicup)
	ON_BN_CLICKED(IDC_BUT_LMT, OnBnClickedButLmt)
	ON_BN_CLICKED(IDC_BUT_Time, OnBnClickedButTime)
END_MESSAGE_MAP()


// CRmAgentDllTestDlg 消息处理程序

BOOL CRmAgentDllTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CRmAgentDllTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRmAgentDllTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CRmAgentDllTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRmAgentDllTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CRmAgentDllTestDlg::OnBnClickedButInit()
{
	this->UpdateData(true);

	CString info = _T("<info><jkid>");
	info += m_jkid;
	info += _T("</jkid><jkxlh>");
	info += m_jkxlh;
	info += _T("</jkxlh></info>");

	int ret = m_tmriAgent.InitTrans(this->m_kkbh,this->m_fxlx,this->m_cdh,info,m_hostport);
	
	char* buf= new char[10];
	MessageBox(itoa(ret,buf,10),0);	

}

void CRmAgentDllTestDlg::OnBnClickedButPass()
{
    this->UpdateData(true);

	CString tp1 = "ftp://jcbk:jcbk@10.2.44.52/bike.jpg";
	CString tp2 = tp1;
	CString tp3 = tp1;
	string wfdm = "0";
	long cwkc = 0;
	long ret = m_tmriAgent.WriteVehicleInfo(this->m_kkbh,this->m_fxlx,this->m_cdh
		,m_passinfo.hphm.c_str(),m_passinfo.hpzl.c_str(),m_passinfo.gcsj.c_str()
		,m_passinfo.clsd,0, wfdm.c_str(), cwkc,m_passinfo.hpys.c_str(),m_passinfo.cllx.c_str()
		,"","","","","",m_passinfo.csys.c_str(),m_passinfo.tplj.c_str(),m_passinfo.tp1.c_str(),m_passinfo.tp2.c_str(),m_passinfo.tp3.c_str(), "");
		char* buf=new char[10];
	MessageBox(itoa(ret,buf,10),0);
}

void CRmAgentDllTestDlg::OnBnClickedButPicup()
{
    this->UpdateData(true);

    tstring file = "E:\\tztp\\ipc.jpg";
	int ret = m_tmriAgent.SaveTzPicture(this->m_kkbh,this->m_fxlx,this->m_cdh,m_passinfo.hphm.c_str(),m_passinfo.gcsj.c_str(),file.c_str());
	char* buf=new char[10];
	MessageBox(itoa(ret,buf,10),0);
}

void CRmAgentDllTestDlg::OnBnClickedButLmt()
{
	int ret = m_tmriAgent.QueryLimitSpeed(this->m_kkbh,this->m_fxlx,this->m_cdh,"1");
	char* buf=new char[10];
	MessageBox(itoa(ret,buf,10),0);
}

void CRmAgentDllTestDlg::OnBnClickedButTime()
{
	const char * pret = m_tmriAgent.QuerySyncTime();;
	MessageBox(pret,0);
}
