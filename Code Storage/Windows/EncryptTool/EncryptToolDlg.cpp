
// EncryptToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EncryptTool.h"
#include "EncryptToolDlg.h"
#include "afxdialogex.h"
#include "Util\Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEncryptToolDlg �Ի���



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


// CEncryptToolDlg ��Ϣ�������

BOOL CEncryptToolDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    CUtil util;
    m_strSerial = util.GetInitCode(m_strAppName);
    int nPos = m_strSerial.ReverseFind(_T('\r\n'));
    m_strSerial = m_strSerial.Left(nPos);

    UpdateData(FALSE);
    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEncryptToolDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // ���ڻ��Ƶ��豸������

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // ʹͼ���ڹ����������о���
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // ����ͼ��
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CEncryptToolDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CEncryptToolDlg::OnBnClickedGenerate()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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