// DlgRegister.cpp : 实现文件
//

#include "stdafx.h"
#include "vc_2.h"
#include "DlgRegister.h"
#include "afxdialogex.h"


// CDlgRegister 对话框

IMPLEMENT_DYNAMIC(CDlgRegister, CDialogEx)

CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRegister::IDD, pParent)
{

}

CDlgRegister::~CDlgRegister()
{
}

void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRegister, CDialogEx)
END_MESSAGE_MAP()


// CDlgRegister 消息处理程序
