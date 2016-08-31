/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKServer.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 19:12:45
 * @brief 
 *  
 **/

#include "CKServer.h"
#include <iostream>

namespace ks
{
/*
void SetUserCallBack(void* param, int (*func)(void*, void*))
{
    CKServer* pServer = (CKServer*)param;
    pServer->SetUserCallBack(func);
}
*/

CKServer::CKServer()
 : m_pConfig(NULL)
 , m_pMemMgr(NULL)
 , m_pThreadMgr(NULL)
 , m_pTaskMgr(NULL)
{
}

CKServer::~CKServer()
{
    if(NULL != m_pConfig)
    {
        delete m_pConfig;
        m_pConfig = NULL;
    }
    if(NULL != m_pMemMgr)
    {
        delete m_pMemMgr;
        m_pMemMgr = NULL;
    }
    if(NULL != m_pThreadMgr)
    {
        delete m_pThreadMgr;
        m_pThreadMgr = NULL;
    }
    if(NULL != m_pTaskMgr)
    {
        delete m_pTaskMgr;
        m_pTaskMgr = NULL;
    }
}

void CKServer::Init()
{
    m_pConfig = CConfig::GetConfig();
    m_pMemMgr = CMemMgr::GetMemMgr();
    m_pThreadMgr = CThreadMgr::GetThreadMgr();
    m_pTaskMgr = CTaskMgr::GetTaskMgr();

    m_pConfig->Init();
    m_pMemMgr->Init(m_pConfig);
    m_pThreadMgr->Init(m_pConfig);
    m_pTaskMgr->Init();

    m_pThreadMgr->ActivateThreadPool();
}

void CKServer::Run()
{
    // epoll
    CThreadHandler* pHandler = new CEpollHandler(m_pConfig);
    CThread* pThread = new CThread(pHandler);
    pThread->Wait();
}

void CKServer::SetUserCallBackFunc(PtrFuncTwo func)
{
    if(m_pTaskMgr == NULL)
    {
        m_pTaskMgr = CTaskMgr::GetTaskMgr();
    }
    m_pTaskMgr->SetUserCallBackFunc(func);
}

}

