/**
 * @file CTask.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 13:52:38
 * @brief 
 *  
 **/

#include "CTask.h"
#include "../memory/CKMemMgr.h"
#include "CKReqTaskMgr.h"
#include "../log/KSLog.h"

namespace ks
{

CEchoTask::CEchoTask(int epfd, int fd)
    : CEpollCtlBase(epfd, fd)
{
    m_OutPackage = NULL;
}
CEchoTask::~CEchoTask()
{
    for(int i=0; i<m_Packages.size();i++)
    {
        m_Packages[i]->Release();
    }
    m_Packages.clear();
    
    if(m_OutPackage != NULL)
    {
        m_OutPackage->Release();
        m_OutPackage = NULL;
    }
}

void CEchoTask::AddPackage(CPackage* pPackage)
{
    if(NULL != pPackage)
        m_Packages.push_back(pPackage);
}

void CEchoTask::Run()
{
    m_OutPackage = CMemMgr::GetMemMgr()->Pull();
    if(NULL == m_OutPackage)
    {
        perror("memory error");
        return;
    }
    (*CReqTaskMgr::GetTaskMgr()->GetUserCallBackFunc())(m_Packages[0], m_OutPackage);
}

void CEchoTask::CallBack()
{
    if (SetEpollOut(m_iFd, this) == -1) 
    {  
        perror("epoll_ctl: mod");  
    }
}

CIOTask::CIOTask()
{
    m_pData = NULL;
    m_iLen = 0;
}
CIOTask::~CIOTask()
{
}

CLogTask::CLogTask(char* line)
{
    m_pData = (void*)line;
    m_iLen = strlen(line);
}
CLogTask::~CLogTask()
{
}

void CLogTask::Run()
{
    CLogger* pLogger = CLogger::GetLogger();
    pLogger->Trace(m_pData, m_iLen);
}

void CLogTask::CallBack()
{
    delete this;
}

}
