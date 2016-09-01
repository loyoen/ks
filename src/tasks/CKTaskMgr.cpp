/**
 * @file ./tasks/CKTaskMgr.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 19:42:54
 * @brief 
 *  
 **/

#include "CKTaskMgr.h"

namespace ks
{

CTaskMgr* CTaskMgr::m_pTaskMgrInstance = NULL;

CTaskMgr::CTaskMgr()
{
}
CTaskMgr::~CTaskMgr()
{
    while(!m_Tasks.empty())
    {
        CTask* pTask = m_Tasks.front();
        m_Tasks.pop();
        delete pTask;
    }
}

void CTaskMgr::AddTask(CTask* pTask)
{
    //lock
    if(pTask != NULL)
    {
        m_Tasks.push(pTask);
    }
}

CTask* CTaskMgr::GetTask()
{
    //lock
    if(m_Tasks.empty())
        return NULL;
    CTask* pTask = m_Tasks.front();
    m_Tasks.pop();
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



















