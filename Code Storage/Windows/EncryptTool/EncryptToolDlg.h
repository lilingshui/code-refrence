// EncryptToolDlg.h : 头文件
//
#pragma once

// CEncryptToolDlg 对话框
class CEncryptToolDlg : public CDialogEx
{
// 构造
public:
	CEncryptToolDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_ENCRYPTTOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
    afx_msg void OnBnClickedGenerate();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
    CString     m_strKey;
    CString     m_strSerial;
    CString     m_strAppName;
    HICON       m_hIcon;
};
