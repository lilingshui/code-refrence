#include "stdafx.h"
#include "Util.h"
#include "MD5Crypt.h"

//命令行输出缓冲大小
const long MAX_COMMAND_SIZE = 10000;
//获取MAC命令行
char szFetCmd[] = "ipconfig /all";
//网卡MAC地址的前导信息
const string MAC_PRE_ENG = "Physical Address";
const string MAC_PRE_CHN = "物理地址";
const string MAC_BEGIN = ": ";

const string strLineBreak = "\r\n";
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 

CUtil::CUtil()
{

}

CUtil::~CUtil()
{

}

CString CUtil::GetInitCode(CString strAppName)
{
    CMD5Crypt md5;
    string strMac = GetMacByCmd(MAC_PRE_ENG);
    if (strMac.empty())
    {
        strMac = GetMacByCmd(MAC_PRE_CHN);
    }

    if (strMac.empty())
    {
        return CString(_T(""));
    }

    string strTemp = "";;
    string strResult = "";

    if (!strAppName.IsEmpty()) {
        strTemp = strAppName.GetBuffer(0);
        strAppName.ReleaseBuffer();
        strMac += strLineBreak;
    }

    long ipos;
    ipos = strMac.find(strLineBreak);

    while (ipos != string::npos)
    {
        strTemp = strMac.substr(0, ipos);
        CString strOutPut;
        CString strInput(strTemp.c_str());
        md5.GetMd5String(strOutPut, strInput);
        strTemp = strOutPut.GetBuffer(0);
        strOutPut.ReleaseBuffer();

        strTemp += strLineBreak;
        strResult += strTemp;
        strMac = strMac.substr(ipos + strLineBreak.length());
        ipos = strMac.find(strLineBreak);
    }

    return CString(strResult.c_str());
}

CString CUtil::GetEncryptCode(CString strIniCode)
{
    CMD5Crypt md5;
    string strTemp = "";;
    string strResult = "";
    string strMac = strIniCode.GetBuffer(0);
    strIniCode.ReleaseBuffer();

    long ipos;
    ipos = strMac.find(strLineBreak);

    while (ipos != string::npos)
    {
        strTemp = strMac.substr(0, ipos);
        //先进行base64加密，再进行md5加密
        strTemp = Base64_encode(strTemp.c_str(), strTemp.length());

        CString strOutPut;
        CString strInput(strTemp.c_str());
        md5.GetMd5String(strOutPut, strInput);

        strTemp = strOutPut.GetBuffer(0);
        strOutPut.ReleaseBuffer();

        strMac = strMac.substr(ipos + strLineBreak.length());
        ipos = strMac.find(strLineBreak);

        //如果是最后一行则不加换行符
        if (ipos != string::npos)
        {
            strTemp += strLineBreak;
        }

        strResult += strTemp;
    }

    return CString(strResult.c_str());
}

string CUtil::GetMacByCmd(string strMacPreFix)
{
    string strOut = "";
    SECURITY_ATTRIBUTES sa;
    HANDLE hReadPipe, hWritePipe;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    //创建管道
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0))
    {
        return strOut;
    }

    STARTUPINFO si;//控制命令行窗口信息
    PROCESS_INFORMATION pi;//返回进程信息

    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hWritePipe;
    si.hStdOutput = hWritePipe;
    si.wShowWindow = SW_HIDE; //隐藏命令行窗口
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

    //创建获取命令行进程
    if (!CreateProcess(NULL, szFetCmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(hWritePipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(hReadPipe);
        hWritePipe = NULL;
        hReadPipe = NULL;
        pi.hProcess = NULL;
        pi.hThread = NULL;
        return strOut;
    }

    char szBuffer[MAX_COMMAND_SIZE+1]; //放置命令行输出缓冲区
    string strTemp = "";
    string strBuffer = "";

    WaitForSingleObject (pi.hProcess, INFINITE);
    unsigned long count;
    CloseHandle(hWritePipe);
    hWritePipe = NULL;
    memset(szBuffer, 0x00, sizeof(szBuffer));

    if (!ReadFile(hReadPipe, szBuffer, MAX_COMMAND_SIZE, &count, 0)) 
    {
        CloseHandle(hWritePipe);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(hReadPipe);
        hWritePipe = NULL;
        hReadPipe = NULL;
        pi.hProcess = NULL;
        pi.hThread = NULL;
        return strOut;
    }

    //CFile file("E:\\work\\VisualC++\\EncryptTool\\Debug\\mac.lg",CFile::modeRead);

    //char *pBuf;
    //int iLen=file.GetLength();
    //pBuf =new char[iLen + 1];
    //file.Read(pBuf, iLen);
    //pBuf[iLen]=0;
    //file.Close();
    //strBuffer += pBuf;

    strBuffer = szBuffer;
    long ipos, iSubPos, beginPos;
    ipos = strBuffer.find(strMacPreFix);

    while (ipos != string::npos)
    {
        strBuffer = strBuffer.substr( ipos + strMacPreFix.length());
        beginPos = strBuffer.find(MAC_BEGIN);
        strBuffer = strBuffer.substr( beginPos + MAC_BEGIN.length());
        iSubPos = strBuffer.find(strLineBreak);

        if (string::npos != iSubPos)
        {
            strTemp += strBuffer.substr(0, iSubPos);
            strTemp += strLineBreak;
            strBuffer = strBuffer.substr(iSubPos);
        }
        else
        {
            break;
        }

        ipos = strBuffer.find(strMacPreFix);
    }

    //去掉中间的“00-50-EB-0F-27-82”中间的'-'得到0050EB0F2782
    int nLength = strTemp.length();
    for(int i=0; i < nLength; i++)
    {
        if(strTemp[i] != '-')
        {
            strOut += strTemp[i];
        }
    }

    //关闭所有的句柄
    if (hWritePipe)
    {
        CloseHandle(hWritePipe);
    }
    if (pi.hProcess)
    {
        CloseHandle(pi.hProcess);
    }
    if (pi.hThread)
    {
        CloseHandle(pi.hThread);
    }
    if (hReadPipe)
    {
        CloseHandle(hReadPipe);
    }

    return strOut;
}
/* Base64 编码 */
string CUtil::Base64_encode(const char* data, int data_len)
{
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3;
    temp = data_len % 3;
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = new char[ret_len];

    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        {
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            f++; 
        } 
    } 
    *f = '\0';

    string strResult = ret;
    delete [] ret;
    ret = NULL;
    return strResult;
}

/* 转换算子 */
char CUtil::find_pos(char ch)
{
    char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
    return (ptr - base);
}

/* Base64 解码 */
string CUtil::Base64_decode(const char *data, int data_len) 
{ 
    int ret_len = (data_len / 4) * 3; 
    int equal_count = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    int temp = 0;
    int prepare = 0; 
    int i = 0; 
    if (*(data + data_len - 1) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 2) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 3) == '=') 
    {//seems impossible 
        equal_count += 1; 
    } 
    switch (equal_count) 
    { 
    case 0: 
        ret_len += 4;//3 + 1 [1 for NULL] 
        break; 
    case 1: 
        ret_len += 4;//Ceil((6*3)/8)+1 
        break; 
    case 2: 
        ret_len += 3;//Ceil((6*2)/8)+1 
        break; 
    case 3: 
        ret_len += 2;//Ceil((6*1)/8)+1 
        break; 
    }

    ret = new char[ret_len];
    memset(ret, 0, ret_len);
    f = ret; 
    while (tmp < (data_len - equal_count)) 
    { 
        temp = 0; 
        prepare = 0; 
        while (temp < 4) 
        { 
            if (tmp >= (data_len - equal_count)) 
            { 
                break; 
            } 
            prepare = (prepare << 6) | (find_pos(data[tmp])); 
            temp++; 
            tmp++; 
        } 
        prepare = prepare << ((4-temp) * 6); 
        for (i=0; i<3 ;i++ ) 
        { 
            if (i == temp) 
            { 
                break; 
            } 
            *f = (char)((prepare>>((2-i)*8)) & 0xFF); 
            f++; 
        } 
    } 
    *f = '\0';

    string strResult = ret;
    delete [] ret;
    ret = NULL;
    return strResult;
}