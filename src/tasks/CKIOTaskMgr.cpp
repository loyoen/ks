/**
 * @file CKIOTaskMgr.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/09/06 17:53:27
 * @brief 
 *  
 **/

#include "CKIOTaskMgr.h"
#include "TaskHandler.h"

namespace ks
{

INITIALIZE(IOTaskMgr)

CIOTaskMgr::CIOTaskMgr()
{
    m_pThread = NULL;
}
CIOTaskMgr::~CIOTaskMgr()
{
    if(NULL != m_pThread)
    {
        m_pThread->Stop();
        m_pThread->Wait();
        delete m_pThread;
        m_pThread = NULL;
    }
}

void CIOTaskMgr::Init()
{
    CTaskMgr::Init();

    CThreadHandler* pHandler = new CTaskHandler(this);
    m_pThread = new CThread(pHandler);
}

}



















