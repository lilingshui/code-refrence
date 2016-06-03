// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "vc_2.h"

#include "MainFrm.h"
#include "DlgRegister.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
	ON_COMMAND(ID_GOOD, &CMainFrame::OnGood)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建一个视图以占用框架的工作区
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("未能创建视图窗口\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting

		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CFrameWnd::OnPaint()
}

//CString GetRegPasswd(CString &DirName) 
//{ 
//	//将用户名换算成15位注册码 
//	long Num1,Num2,Num3; 
//
//	char sn[16]={0}; 
//	CString p; 
//	int i,len; 
//
//	Num1=0; 
//	Num2=0; 
//	Num3=0; 
//
//	len=int(strlen(DirName)); 
//	if(len!=0) 
//	{ 
//		for( i=1;i<=len;i++) 
//		{ 
//			//第一步算法 
//			Num1=(long(Num1+(int(DirName[i-1])*i*i)*(i*sqrt(DirName[i-1])+1)))%100000; 
//			//第二步算法 
//			Num2=(Num2*i+(long(pow((int)DirName[i-1],2)*i)))%100000; 
//			//第三步算法 
//			Num3=(Num2+(long)sqrt(Num1))%100000; 
//		} 
//		//以下把三个算法结果分别生成5个字符，共有15个 
//		for(i=0;i<5;i++) 
//			sn[i]=(int)(Num1+31+i*i*i)%128; 
//		for(i=5;i<10;i++) 
//			sn[i]=(int)(Num2+31+i*i*i)%128; 
//		for(i=10;i<15;i++) 
//			sn[i]=(int)(Num3+31+i*i*i)%128; 
//		sn[15]=0; 
//		//以下循环把所有生成的字符转换为0---9，A---Z，a----z 
//		for(i=0;i<15;i++) 
//		{ 
//			while((sn[i]<'0' || sn[i]>'9') && (sn[i]<'A' || sn[i]>'Z') &&(sn[i]<'a' || sn[i]>'z') ) 
//			{ 
//				sn[i]=(sn[i]+31+7*i)%128; 
//			} 
//		} 
//		//赋值给一个CSTRING变量，用做函数返回值 
//		p.Format("%s",sn); 
//	} 
//	return p; 
//}



//检查软件是否注册的函数 

//BOOL GetRegFlag(void) 
//{ 
//	HKEY hKey = NULL; 
//	BYTE i; 
//
//	CString str; 
//	str.LoadString(IDS_REG_KEY);// IDS_REG_KEY为在注册表中的子目录字符串 
//
//	if (RegCreateKey(HKEY_CURRENT_USER, str, &hKey) != ERROR_SUCCESS) return false; 
//
//	DWORD cbA; 
//	cbA=sizeof(int); 
//	if( RegQueryValueEx(hKey, "SzMima",NULL,NULL, &i,&cbA) != ERROR_SUCCESS) 
//		return false; 
//
//	BYTE j=i; 
//	if(j==0)//0代表软件已经注册，可以正常使用 
//	{ 
//		RegCloseKey(hKey); 
//		return true; 
//	} 
//	else 
//	{ 
//		RegCloseKey(hKey); 
//		return false; 
//	} 
//
//	return false; 
//}; 
//设置软件已经注册标志的函数 搜索

//BOOL SetRegFlag(void) 
//{ 
//	HKEY hKey = NULL; 
//	BYTE i; 
//
//	CString str; 
//	str.LoadString(IDS_REG_KEY);// IDS_REG_KEY为在注册表中的子目录字符串 
//
//	if (RegCreateKey(HKEY_CURRENT_USER, str, &hKey) != ERROR_SUCCESS) return false; 
//
//	BYTE j=0;//0代表已经注册 
//	if(RegSetValueEx(hKey, "SzMima", 0, REG_BINARY, &j,4) != ERROR_SUCCESS) 
//	{ 
//		AfxMessageBox("设置注册表数据失败!"); 
//		return FALSE; 
//	} 
//	return false; 
//}; 


/*
以上三个函数即可实现软件注册机制，只需要在程序初始化的时候加入以下几句代码即可 
BOOL bReg= GetRegFlag (); 
if(!bReg) 
{ 
//在此加入限制功能或者拒绝是使用的代码 
} 
*/


//如果用户注册只需要加入以下代码即可 
//这是我的程序中的一个注册界面，输入用户名和注册码提交后检验注册码是否正确的代码 

/*

void CRegEdit::OnBnClickedOk() 
{ 
if(!UpdateData()) return;//取得编辑框的内容，并赋值到类变量中 
m_RegUser.TrimLeft();//m_RegUser是用户名 
m_RegUser.TrimRight(); 
if(m_RegUser.IsEmpty()) 
{ 
AfxMessageBox("用户名不能为空，请重新输入。"); 
GetDlgItem(IDC_REGUSER)->SetFocus(); 
return; 
} 
m_RegPasswd.TrimLeft();m_RegPasswd是注册码 
m_RegPasswd.TrimRight(); 
if(m_RegPasswd.IsEmpty()) 
{ 
AfxMessageBox("注册码不能为空，请重新输入。"); 
GetDlgItem(IDC_REGPASSWD)->SetFocus(); 
return; 
} 
CString Passwd; 
Passwd=GetRegPasswd(m_RegUser);//调用算法取得该用户名的注册码 
if(Passwd==m_RegPasswd)//与用户输入的注册进行比较 
{ 
SetRegFlag();//设置注册标志 
OnOK(); 
} 
else 
AfxMessageBox("注册码错误，请重新输入。"); 
UpdateData(false); 
} */

void CMainFrame::OnGood()
{
	CDlgRegister dlgRegister;
	dlgRegister.DoModal();
}
