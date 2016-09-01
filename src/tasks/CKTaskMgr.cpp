/**
 * @file ./tasks/CKTaskMgr.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 19:42:54
 * @brief 
 *  
 **/

#include "CKTaskMgr.h"
#include <iostream>

namespace ks
{

CTaskMgr* CTaskMgr::m_pTaskMgrInstance = NULL;

CTaskMgr::CTaskMgr()
{
    pthread_mutex_init(&m_MutexHead, NULL);
    pthread_mutex_init(&m_MutexTail, NULL);
}

CTaskMgr::~CTaskMgr()
{
    while(!m_Tasks.empty())
    {
        CTask* pTask = m_Tasks.front();
        m_Tasks.pop();
        delete pTask;
    }
    pthread_mutex_destroy(&m_MutexHead);
    pthread_mutex_destroy(&m_MutexTail);
}

void CTaskMgr::AddTask(CTask* pTask)
{
    if(pTask != NULL)
    {
        pthread_mutex_lock(&m_MutexTail);
        m_Tasks.push(pTask);
        pthread_mutex_unlock(&m_MutexTail);
    }
}

CTask* CTaskMgr::GetTask()
{
    if(m_Tasks.empty())
    {
        return NULL;
    }

    CTask *pTask = NULL;
    pthread_mutex_lock(&m_MutexHead);
    if(!m_Tasks.empty())
    {
        pTask = m_Tasks.front();
        m_Tasks.pop();
    }
    pthread_mutex_unlock(&m_MutexHead);
    return pTask;
}

void CTaskMgr::SetUserCallBackFunc(PtrFuncTwo func)
{
    m_UserCallBackFunc = func;
}

PtrFuncTwo CTaskMgr::GetUserCallBackFunc()
{
    return m_UserCallBackFunc;
}

}



















