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
    std::cout << "in callback" << std::endl;
    CPackage* pIn = (CPackage*)input;
    std::cout << "before get out memory" << std::endl;
    CMemBlock* pOutBlock = CMemMgr::GetMemMgr()->GetMemBodyMgr()->Pull(128);
    //std::cout << pIn->GetData() << std::endl;
    //LOG_INFO("READ IN LENGTH = %d", pIn->GetLength());
    std::cout << "after get out memory" << std::endl;
    int iLen = sprintf((char*)pOutBlock->GetData(), 
            "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);
    std::cout << "return len" << iLen << std::endl;
    pOutBlock->SetUsedSize(iLen);
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



















