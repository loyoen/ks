/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Task.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 13:52:38
 * @brief 
 *  
 **/

#include "CTask.h"
#include "../memory/CKMemMgr.h"
#include "CKTaskMgr.h"
#include <sys/epoll.h>  
#include <fcntl.h>  
#include <iostream>

namespace ks
{

CEchoTask::CEchoTask(int epfd, int fd, int events)
{
    m_iEpollFd = epfd;
    m_iFd = fd;
    m_iEvents = events;
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
    
    (*CTaskMgr::GetTaskMgr()->GetUserCallBackFunc())(m_Packages[0], m_OutPackage);
}

void CEchoTask::CallBack()
{
    struct epoll_event ev;
    ev.data.fd = m_iFd;
    ev.events = m_iEvents | EPOLLOUT;
    ev.data.ptr = this;

    if (epoll_ctl(m_iEpollFd, EPOLL_CTL_MOD, m_iFd, &ev) == -1) 
    {  
        perror("epoll_ctl: mod");  
    }
}


}
