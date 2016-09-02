/**
 * @file KSEpollHandler.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/29 10:31:35
 * @brief 
 *  
 **/

#include "KSEpollHandler.h"
#include "../memory/CKMemMgr.h"
#include "../tasks/CKTaskMgr.h"
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
}
CEpollHandler::~CEpollHandler()
{
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
        perror("fcntl(F_GETFL)\n");  
        exit(1);  
    }  
    opts = (opts | O_NONBLOCK);  
    if(fcntl(sockfd, F_SETFL, opts) < 0) 
    {  
        perror("fcntl(F_SETFL)\n");  
        exit(1);  
    }
}

int CEpollHandler::DoWait(epoll_event* events)
{
    m_iNfds = epoll_wait(m_iEpollFd, events, m_iMaxEvents, -1);
    if (m_iNfds == -1) 
    {  
        perror("epoll_pwait");  
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
            perror("epoll_ctl: add");  
            exit(EXIT_FAILURE);  
        }  
    }  
    if (m_iCurConnSock == -1) 
    {  
        if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)   
            perror("accept");  
    }
}

void CEpollHandler::DoRead(int fd)
{
    int nindex = 0, nread = 0, nleft = 0;
    
    CMemMgr* pMemMgr = CMemMgr::GetMemMgr(); 
    CPackage* pPackage = NULL;
    char* readbuf = NULL;
    CTask* pTask = NULL;
    
    do
    {
        nindex = 0;
        nread = 0;
        pPackage = pMemMgr->Pull();
        if(NULL == pPackage)
            return;
        
        readbuf = (char*)pPackage->GetData();
        nleft = pPackage->GetInitLength();
        while ((nread = read(fd, readbuf + nindex, nleft)) > 0) 
        {  
            nindex += nread;
            nleft -= nread;
            if(0 == nleft)
                break;
        }

        if(nread == 0)
        {
            SetEpollDel(fd);
            close(fd);
            
            if(pTask != NULL)
                delete pTask;
            pPackage->Release();
            return;
        }

        if (nread == -1 && errno != EAGAIN) 
        {
            perror("read error");
            if(pTask != NULL)
                delete pTask;
            pPackage->Release();
            return;
        }

        pPackage->SetLength(nindex);
        
        if(NULL == pTask)
        {
            pTask = new CEchoTask(m_iEpollFd, fd);
        }
        pTask->AddPackage(pPackage);

        if(errno == EAGAIN)
        {
            break;
        }

    }while(true);
    
    CTaskMgr* pTaskMgr = CTaskMgr::GetTaskMgr();
    pTaskMgr->AddTask(pTask);
}

void CEpollHandler::DoWrite(char* data)
{                
    CEchoTask* pTask = (CEchoTask*)data;
    char* buf = pTask->GetOutPackage()->GetData();
    int nwrite = 0, data_size = pTask->GetOutPackage()->GetLength();  
    int n = data_size;
    int fd = pTask->GetFd();

    while (n > 0) 
    {  
        nwrite = write(fd, buf + data_size - n, n);  
        if (nwrite < n) 
        {  
            if (nwrite == -1 && errno != EAGAIN) 
            {  
                perror("write error");  
            }  
            break;  
        }  
        n -= nwrite;  
    }

    SetEpollIn(fd); 
    delete pTask;
}

int CEpollHandler::StartEpoll()
{
    InitEnv();

    struct epoll_event *events = (struct epoll_event*)malloc(sizeof(struct epoll_event)*m_iMaxEvents);
    int fdIndex = 0, fd;

    while(true)
    {  
        m_iNfds = DoWait(events);

        if (m_iNfds == -1) 
        {  
            perror("epoll_pwait");  
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
                DoWrite((char*)events[fdIndex].data.ptr);
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
        perror("sockfd\n");  
        exit(1);  
    }  

    SetNonBlocking(m_iFd);  
    
    bzero(&local, sizeof(local));  
    local.sin_family = AF_INET;  
    local.sin_addr.s_addr = htonl(INADDR_ANY);;  
    local.sin_port = htons(m_iPort);  
    if( bind(m_iFd, (struct sockaddr *) &local, sizeof(local)) < 0) {  
        perror("bind\n");  
        exit(1);  
    }  
    listen(m_iFd, 20);

    
    m_iEpollFd = epoll_create(m_iMaxEvents);  
    if (m_iEpollFd == -1) 
    {  
        perror("epoll_create");  
        exit(EXIT_FAILURE);  
    }  
    
    if (SetEpollAdd(m_iFd) == -1) 
    {  
        perror("epoll_ctl: listen_sock");  
        exit(EXIT_FAILURE);  
    }  
}

}
