// EncryptToolDlg.h : ͷ�ļ�
//
#pragma once

// CEncryptToolDlg �Ի���
class CEncryptToolDlg : public CDialogEx
{
// ����
public:
	CEncryptToolDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_ENCRYPTTOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
    afx_msg void OnBnClickedGenerate();

	// ���ɵ���Ϣӳ�亯��
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
