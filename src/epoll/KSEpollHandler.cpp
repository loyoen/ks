/**
 * @file KSEpollHandler.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/29 10:31:35
 * @brief 
 *  
 **/

#include "KSEpollHandler.h"
#include "../memory/CKMemMgr.h"
#include "../tasks/CKReqTaskMgr.h"
#include "../tasks/CKIOTaskMgr.h"
#include "../log/KSLog.h"
#include <iostream>

namespace ks
{

CEpollHandler::CEpollHandler(CConfig* pConfig)
{
    m_bStoped = false;
    if(pConfig != NULL)
    {
        m_iMaxEvents = pConfig->GetIntValue("MaxEvents");
        m_iPort = pConfig->GetIntValue("port");
    }
    m_pSockMgr = CSockMgr::GetSockMgr();
}
CEpollHandler::~CEpollHandler()
{
    if(m_pSockMgr != NULL)
    {
        delete m_pSockMgr;
        m_pSockMgr = NULL;
    }
}

int CEpollHandler::OnThreadProc()
{
    return StartEpoll();
}

void CEpollHandler::SetNonBlocking(int sockfd)
{
    int opts = fcntl(sockfd, F_GETFL);  
    if(opts < 0) 
    {  
        LOG_FATAL("fcntl(F_GETFL) SetNonBlocking Error");  
        exit(1);  
    }  
    opts = (opts | O_NONBLOCK);  
    if(fcntl(sockfd, F_SETFL, opts) < 0) 
    {  
        LOG_FATAL("fcntl(F_SETFL) SetNonBlocking Error");  
        exit(1);  
    }
}

int CEpollHandler::DoWait(epoll_event* events)
{
    m_iNfds = epoll_wait(m_iEpollFd, events, m_iMaxEvents, -1);
    if (m_iNfds == -1) 
    {  
        LOG_FATAL("epoll_pwait Error");  
        exit(EXIT_FAILURE);  
    }
    return m_iNfds;
}

void CEpollHandler::DoAccept()
{
    while ((m_iCurConnSock = accept(m_iFd,(struct sockaddr *) &m_remote, (size_t*)&m_addrlen)) > 0) 
    {  
        SetNonBlocking(m_iCurConnSock);  
        if (SetEpollAdd(m_iCurConnSock) == -1) 
        {  
            LOG_FATAL("epoll_ctl: add");  
            exit(EXIT_FAILURE);  
        }
        m_pSockMgr->AddSock(m_iCurConnSock); 
    }  
    if (m_iCurConnSock == -1) 
    {  
        if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)   
            LOG_ERROR("accept Error");  
    }
}

void CEpollHandler::DoRead(int fd)
{
    
    /*
    CReadTask* pTask = new CReadTask(m_iEpollFd,fd);
    CTaskMgr* pTaskMgr = CReqTaskMgr::GetTaskMgr();
    pTaskMgr->AddTask(pTask);
    */
    std::cout << "read from fd" << fd << std::endl;
    m_pSockMgr->Read(fd);

    
}

void CEpollHandler::DoWrite(void* data)
{        
    /*    
    CEchoTask* pEchoTask = (CEchoTask*)data;
    if(pEchoTask->GetOutPackage() == NULL)
        std::cout << "write no package" << std::endl;
    CWriteTask* pTask = new CWriteTask(pEchoTask, m_iEpollFd, pEchoTask->GetFd());
    CTaskMgr* pTaskMgr = CReqTaskMgr::GetTaskMgr();
    pTaskMgr->AddTask(pTask);
    */
    std::cout << "into write" << std::endl; 
    CEchoTask* pEchoTask = (CEchoTask*)data;
    char* buf = (char*)pEchoTask->GetOutBlock()->GetData();
    int nwrite = 0, data_size = pEchoTask->GetOutBlock()->GetUsedSize();  
    int n = data_size;
    int fd = pEchoTask->GetFd();
    std::cout << "outsize" << data_size << "fd = " << fd << std::endl;
    while (n > 0) 
    {  
        nwrite = write(fd, buf + data_size - n, n);  
        if (nwrite < n) 
        {  
            if (nwrite == -1 && errno != EAGAIN) 
            {  
                LOG_ERROR("write error");
                break;  
            }  
        }
        n -= nwrite;
    }
    std::cout << "write end" << std::endl;
    SetEpollIn(fd);
    delete pEchoTask;
    std::cout << "delete suc" << std::endl;
}

int CEpollHandler::StartEpoll()
{
    InitEnv();

    struct epoll_event *events = (struct epoll_event*)malloc(sizeof(struct epoll_event)*m_iMaxEvents);
    int fdIndex = 0, fd;
    std::cout << "start epoll" << std::endl;
    while(true)
    {  
        m_iNfds = DoWait(events);

        if (m_iNfds == -1) 
        {  
            LOG_FATAL("epoll_pwait");  
            exit(EXIT_FAILURE);  
        }  
        for (fdIndex = 0; fdIndex < m_iNfds; ++fdIndex) 
        {
            fd = events[fdIndex].data.fd;
            if (fd == m_iFd) 
            { 
                DoAccept();
                continue;  
            }    
            if (events[fdIndex].events & EPOLLIN) 
            {  
                DoRead(fd);
            }
            else if (events[fdIndex].events & EPOLLOUT) 
            {
                DoWrite(events[fdIndex].data.ptr);
            } 
        }  
    }

    free(events);
    return 0;  
}

void CEpollHandler::InitEnv()
{
    struct sockaddr_in local;  
  
    if( (m_iFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
        LOG_FATAL("sockfd\n");  
        exit(1);  
    }  

    SetNonBlocking(m_iFd);  
    
    bzero(&local, sizeof(local));  
    local.sin_family = AF_INET;  
    local.sin_addr.s_addr = htonl(INADDR_ANY);;  
    local.sin_port = htons(m_iPort);  
    if( bind(m_iFd, (struct sockaddr *) &local, sizeof(local)) < 0) {  
        LOG_FATAL("bind\n");  
        exit(1);  
    }  
    listen(m_iFd, 20);

    
    m_iEpollFd = epoll_create(m_iMaxEvents);
  
    m_pSockMgr->Init(m_iEpollFd);

    if (m_iEpollFd == -1) 
    {  
        LOG_FATAL("epoll_create");  
        exit(EXIT_FAILURE);  
    }  
    
    if (SetEpollAdd(m_iFd) == -1) 
    {  
        LOG_FATAL("epoll_ctl: listen_sock");  
        exit(EXIT_FAILURE);  
    }  
}

}
