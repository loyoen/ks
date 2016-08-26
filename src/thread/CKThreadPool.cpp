/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKThreadPool.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 10:10:08
 * @brief 
 *  
 **/

namespace ks
{

CThreadMgr::CThreadMgr()
{
    m_iThreadNum = 0;
    m_pThreadHandler = NULL;
}

CThreadMgr::~CThreadMgr()
{
    for(int i=0;i<m_Threads.size();i++)
    {
        delete m_Threads[i];
    }
    m_Threads.clear();
}

void CThreadMgr::Init(CConfig* pConfig, CThreadHandler* pHandler)
{
    if (NULL == pConfig)
        return;
    m_iThreadNum = pConfig->GetThreadNum();
    m_pTaskHandler = pHandler;
}

bool CThreadMgr::ActivateThreadPool()
{
    for(int index=0; index<m_iThreadNum; index++)
    {
        CThread* pThread = new CThread(m_pThreadHandler);
        m_Threads.push_back(pThread);
    }
}

void CThreadMgr::StopThreadPool()
{
    for(int i=0; i<m_Threads.size(); i++)
    {
        m_Threads[i].Stop();
    }
}














}
