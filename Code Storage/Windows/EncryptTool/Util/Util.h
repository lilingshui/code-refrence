#pragma once

#include <string>
#include <iostream>
using namespace std;

//用命令行方式获取网卡MAC地址
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
    /* 转换算子 */
     char find_pos(char ch);
    /* Base64 编码 */
    string Base64_encode(const char* data, int data_len);
    /* Base64 解码 */
    string Base64_decode(const char* data, int data_len);
};