/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Thread.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 16:48:51
 * @brief 
 *  
 **/

#include "Thread.h"

namespace ks
{

CThread::CThread(CThreadHandler* pHandler)
: m_pHandler(pHandler)
{
    Start();
}    

CThread::~CThread()
{
}

void* ThreadProc(void* lpParameter)
{
    CThread* pThread = (CThread*)lpParameter;
    pThread->OnThreadProc();
} 

int CThread::Start()
{
    int ret = -1;
    do
    {
        ret = pthread_create(&m_iThreadId, NULL, ThreadProc, this);
    }while(false);
    return ret;
}

void CThread::Wait()
{
    pthread_join(m_iThreadId, NULL);
}

void CThread::Stop()
{
    if(NULL == m_pHandler)
        return;
    m_pHandler->Stop();
}

bool CThread::IsStop()
{
    if(NULL == m_pHandler)
        return true;
    return m_pHandler->IsStop();
}

int CThread::OnThreadProc()
{
    if(NULL == m_pHandler)
        return -1;
    return m_pHandler->OnThreadProc();
}








}
