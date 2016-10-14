/**
 * @file CKServer.cpp
 * @author loyoen(com@gmail.com)
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
 , m_pReqTaskMgr(NULL)
 , m_pIOTaskMgr(NULL)
 , m_pLogger(NULL)
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
    if(NULL != m_pReqTaskMgr)
    {
        delete m_pReqTaskMgr;
        m_pReqTaskMgr = NULL;
    }
    if(NULL != m_pIOTaskMgr)
    {
        delete m_pIOTaskMgr;
        m_pIOTaskMgr = NULL;
    }
    if(NULL != m_pLogger)
    {
        delete m_pLogger;
        m_pLogger = NULL;
    }
}

void CKServer::Init()
{
    m_pConfig = CConfig::GetConfig();
    m_pMemMgr = CMemMgr::GetMemMgr();
    m_pThreadMgr = CThreadMgr::GetThreadMgr();
    m_pReqTaskMgr = CReqTaskMgr::GetReqTaskMgr();
    m_pIOTaskMgr = CIOTaskMgr::GetIOTaskMgr();
    m_pLogger = CLogger::GetLogger();


    m_pConfig->Init();
    m_pMemMgr->Init(m_pConfig);
    m_pThreadMgr->Init(m_pConfig);
    m_pReqTaskMgr->Init();
    m_pIOTaskMgr->Init();
    m_pLogger->Init();

    m_pThreadMgr->ActivateThreadPool();
}

void CKServer::Run()
{
    // epoll
    CThreadHandler* pHandler = new CEpollHandler(m_pConfig);
    CThread* pThread = new CThread(pHandler);
    //CThreadHandler* pHandler2= new CEpollHandler(m_pConfig);
    //CThread* pThread2= new CThread(pHandler2);
    
    pThread->Wait();
}

void CKServer::SetUserCallBackFunc(PtrFunc func)
{
    if(m_pReqTaskMgr == NULL)
    {
        m_pReqTaskMgr = CReqTaskMgr::GetReqTaskMgr();
    }
    m_pReqTaskMgr->SetUserCallBackFunc(func);
}

}

