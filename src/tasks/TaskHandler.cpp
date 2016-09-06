/**
 * @file TaskHandler.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 10:41:31
 * @brief 
 *  
 **/

#include "TaskHandler.h"
#include "CKTaskMgr.h"
#include <iostream>

namespace ks
{

CTaskHandler::CTaskHandler(CTaskMgr* pTaskMgr)
{
    m_bStoped = false;
    m_pTaskMgr = pTaskMgr;
}
CTaskHandler::~CTaskHandler()
{
}

int CTaskHandler::OnThreadProc()
{
    while(!m_bStoped)
    {
        CTask* pTask = m_pTaskMgr->GetTask();
        if(pTask != NULL)
        {
            pTask->Run();
            pTask->CallBack();
        }
        sleep(0);
    }
}




}
