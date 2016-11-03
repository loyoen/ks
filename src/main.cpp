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

void* test_call_back(void* input)
{
    CPackage* pIn = (CPackage*)input;
    CMemBlock* pOutBlock = CMemMgr::GetMemMgr()->GetMemBodyMgr()->Pull(128);
    int iLen = sprintf((char*)pOutBlock->GetData(), 
            "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);
    pOutBlock->SetUsedSize(iLen);
    if(iLen != 50)
        std::cout << iLen << std::endl;
    return pOutBlock;
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



















