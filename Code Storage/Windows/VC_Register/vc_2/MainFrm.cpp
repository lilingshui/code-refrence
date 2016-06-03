// MainFrm.cpp : CMainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ����һ����ͼ��ռ�ÿ�ܵĹ�����
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("δ�ܴ�����ͼ����\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// ������ǰ�Ƶ���ͼ����
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// ����ͼ��һ�γ��Ը�����
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// ����ִ��Ĭ�ϴ���
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting

		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CFrameWnd::OnPaint()
}

//CString GetRegPasswd(CString &DirName) 
//{ 
//	//���û��������15λע���� 
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
//			//��һ���㷨 
//			Num1=(long(Num1+(int(DirName[i-1])*i*i)*(i*sqrt(DirName[i-1])+1)))%100000; 
//			//�ڶ����㷨 
//			Num2=(Num2*i+(long(pow((int)DirName[i-1],2)*i)))%100000; 
//			//�������㷨 
//			Num3=(Num2+(long)sqrt(Num1))%100000; 
//		} 
//		//���°������㷨����ֱ�����5���ַ�������15�� 
//		for(i=0;i<5;i++) 
//			sn[i]=(int)(Num1+31+i*i*i)%128; 
//		for(i=5;i<10;i++) 
//			sn[i]=(int)(Num2+31+i*i*i)%128; 
//		for(i=10;i<15;i++) 
//			sn[i]=(int)(Num3+31+i*i*i)%128; 
//		sn[15]=0; 
//		//����ѭ�����������ɵ��ַ�ת��Ϊ0---9��A---Z��a----z 
//		for(i=0;i<15;i++) 
//		{ 
//			while((sn[i]<'0' || sn[i]>'9') && (sn[i]<'A' || sn[i]>'Z') &&(sn[i]<'a' || sn[i]>'z') ) 
//			{ 
//				sn[i]=(sn[i]+31+7*i)%128; 
//			} 
//		} 
//		//��ֵ��һ��CSTRING������������������ֵ 
//		p.Format("%s",sn); 
//	} 
//	return p; 
//}



//�������Ƿ�ע��ĺ��� 

//BOOL GetRegFlag(void) 
//{ 
//	HKEY hKey = NULL; 
//	BYTE i; 
//
//	CString str; 
//	str.LoadString(IDS_REG_KEY);// IDS_REG_KEYΪ��ע����е���Ŀ¼�ַ��� 
//
//	if (RegCreateKey(HKEY_CURRENT_USER, str, &hKey) != ERROR_SUCCESS) return false; 
//
//	DWORD cbA; 
//	cbA=sizeof(int); 
//	if( RegQueryValueEx(hKey, "SzMima",NULL,NULL, &i,&cbA) != ERROR_SUCCESS) 
//		return false; 
//
//	BYTE j=i; 
//	if(j==0)//0��������Ѿ�ע�ᣬ��������ʹ�� 
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
//��������Ѿ�ע���־�ĺ��� ����

//BOOL SetRegFlag(void) 
//{ 
//	HKEY hKey = NULL; 
//	BYTE i; 
//
//	CString str; 
//	str.LoadString(IDS_REG_KEY);// IDS_REG_KEYΪ��ע����е���Ŀ¼�ַ��� 
//
//	if (RegCreateKey(HKEY_CURRENT_USER, str, &hKey) != ERROR_SUCCESS) return false; 
//
//	BYTE j=0;//0�����Ѿ�ע�� 
//	if(RegSetValueEx(hKey, "SzMima", 0, REG_BINARY, &j,4) != ERROR_SUCCESS) 
//	{ 
//		AfxMessageBox("����ע�������ʧ��!"); 
//		return FALSE; 
//	} 
//	return false; 
//}; 


/*
����������������ʵ�����ע����ƣ�ֻ��Ҫ�ڳ����ʼ����ʱ��������¼�����뼴�� 
BOOL bReg= GetRegFlag (); 
if(!bReg) 
{ 
//�ڴ˼������ƹ��ܻ��߾ܾ���ʹ�õĴ��� 
} 
*/


//����û�ע��ֻ��Ҫ�������´��뼴�� 
//�����ҵĳ����е�һ��ע����棬�����û�����ע�����ύ�����ע�����Ƿ���ȷ�Ĵ��� 

/*

void CRegEdit::OnBnClickedOk() 
{ 
if(!UpdateData()) return;//ȡ�ñ༭������ݣ�����ֵ��������� 
m_RegUser.TrimLeft();//m_RegUser���û��� 
m_RegUser.TrimRight(); 
if(m_RegUser.IsEmpty()) 
{ 
AfxMessageBox("�û�������Ϊ�գ����������롣"); 
GetDlgItem(IDC_REGUSER)->SetFocus(); 
return; 
} 
m_RegPasswd.TrimLeft();m_RegPasswd��ע���� 
m_RegPasswd.TrimRight(); 
if(m_RegPasswd.IsEmpty()) 
{ 
AfxMessageBox("ע���벻��Ϊ�գ����������롣"); 
GetDlgItem(IDC_REGPASSWD)->SetFocus(); 
return; 
} 
CString Passwd; 
Passwd=GetRegPasswd(m_RegUser);//�����㷨ȡ�ø��û�����ע���� 
if(Passwd==m_RegPasswd)//���û������ע����бȽ� 
{ 
SetRegFlag();//����ע���־ 
OnOK(); 
} 
else 
AfxMessageBox("ע����������������롣"); 
UpdateData(false); 
} */

void CMainFrame::OnGood()
{
	CDlgRegister dlgRegister;
	dlgRegister.DoModal();
}
