/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file main.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/31 11:18:02
 * @brief 
 *  
 **/

#include "CKServer.h"

using namespace ks;

int test_call_back(void* input, void* output)
{
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



















