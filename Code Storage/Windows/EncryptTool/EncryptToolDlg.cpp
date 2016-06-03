
// EncryptToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EncryptTool.h"
#include "EncryptToolDlg.h"
#include "afxdialogex.h"
#include "Util\Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEncryptToolDlg 对话框



CEncryptToolDlg::CEncryptToolDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CEncryptToolDlg::IDD, pParent)
    , m_strKey(_T(""))
    , m_strSerial(_T(""))
    ,m_strAppName(_T("COLLECT_DT"))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEncryptToolDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_KEY, m_strKey);
    DDX_Text(pDX, IDC_EDIT_SERIAL, m_strSerial);
}

BEGIN_MESSAGE_MAP(CEncryptToolDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(ID_GENERATE, &CEncryptToolDlg::OnBnClickedGenerate)
END_MESSAGE_MAP()


// CEncryptToolDlg 消息处理程序

BOOL CEncryptToolDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    CUtil util;
    m_strSerial = util.GetInitCode(m_strAppName);
    int nPos = m_strSerial.ReverseFind(_T('\r\n'));
    m_strSerial = m_strSerial.Left(nPos);

    UpdateData(FALSE);
    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEncryptToolDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
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
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEncryptToolDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CEncryptToolDlg::OnBnClickedGenerate()
{
    // TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
    int nPos = m_strSerial.ReverseFind(_T('\r\n'));
    int nLength = m_strSerial.GetLength();

    if (nPos < nLength - 3)
    {
        m_strSerial += _T("\r\n");
    }

    CUtil util;
    m_strKey = util.GetEncryptCode(m_strSerial);
    UpdateData(FALSE);
}