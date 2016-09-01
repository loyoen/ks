/**
 * @file main.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/31 11:18:02
 * @brief 
 *  
 **/

#include "CKServer.h"
#include <iostream>
using namespace ks;

int test_call_back(void* input, void* output)
{
    CPackage* pIn = (CPackage*)input;
    CPackage* pOut = (CPackage*)output;
    int iLen = sprintf(pOut->GetData(), 
            "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);
    pOut->SetLength(iLen);
    return 0;
}

int main()
{
    CKServer* pServer = new CKServer();
    pServer->Init();
    pServer->SetUserCallBackFunc(test_call_back);
    pServer->Run();
    return 0;
}



















