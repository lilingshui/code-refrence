#pragma once

#include <string>
#include <iostream>
using namespace std;

//�������з�ʽ��ȡ����MAC��ַ
class CUtil
{
public:
    CUtil();
    ~CUtil();
public:
    CString GetInitCode(CString strAppName);
    CString GetEncryptCode(CString strIniCode);
protected:
    string GetMacByCmd(string strMacPreFix);
    /* ת������ */
     char find_pos(char ch);
    /* Base64 ���� */
    string Base64_encode(const char* data, int data_len);
    /* Base64 ���� */
    string Base64_decode(const char* data, int data_len);
};