/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file TaskHandler.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 10:41:31
 * @brief 
 *  
 **/

#include "TaskHandler.h"
#include "CKTaskMgr.h"
#include <iostream>

namespace ks
{

CTaskHandler::CTaskHandler()
{
    m_bStoped = false;
}
CTaskHandler::~CTaskHandler()
{
}

int CTaskHandler::OnThreadProc()
{
    CTaskMgr *pTaskMgr = CTaskMgr::GetTaskMgr();
    while(!m_bStoped)
    {
        CTask* pTask = pTaskMgr->GetTask();
        if(pTask != NULL)
        {
            pTask->Run();
            pTask->CallBack();
        }
        sleep(0);
    }
}




}


















