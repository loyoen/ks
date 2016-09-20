/**
 * @file main.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/31 11:18:02
 * @brief 
 *  
 **/
#include <iostream>
#include "CKServer.h"

using namespace ks;

int test_call_back(void* input, void* output)
{
    CPackage* pIn = (CPackage*)input;
    CPackage* pOut = (CPackage*)output;
    std::cout << pIn->GetData() << std::endl;
    //LOG_INFO("READ IN LENGTH = %d", pIn->GetLength());
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
    delete pServer;
    return 0;
}



















