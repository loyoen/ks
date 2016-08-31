/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file KSEpollHandler.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/29 10:31:35
 * @brief 
 *  
 **/

#include "KSEpollHandler.h"
#include <sys/socket.h>  
#include <sys/wait.h>  
#include <netinet/in.h>  
#include <netinet/tcp.h>  
#include <sys/epoll.h>  
#include <sys/sendfile.h>  
#include <sys/stat.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <strings.h>  
#include <fcntl.h>  
#include <errno.h>   
 
namespace ks
{

CEpollHandler::CEpollHandler(CConfig* pConfig)
{
    m_bStoped = false;
    if(pConfig != NULL)
    {
        m_iMaxEvents = pConfig->GetIntValue("MAXEVENTS");
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

void CEpollHandler::SetNonBlocking(int scokfd)
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
    while ((m_iCurConnSock = accept(m_iListenFd,(struct sockaddr *) &m_remote,&m_addrlen)) > 0) 
    {  
        SetNonBlocking(m_iCurConnSock);  
        m_ev.events = EPOLLIN | EPOLLET;  
        m_ev.data.fd = m_iCurConnSock;  
        if (epoll_ctl(m_iEpollFd, EPOLL_CTL_ADD, m_iCurConnSock, &m_ev) == -1) 
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

void CEpollHandler::DoRead(struct epoll_event ev)
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
        if(NULL == pTask)
        {
            pTask = new CEchoTask(fd, ev.events);
        }

        readbuf = pPackage->GetData;
        nleft = pPackage->GetInitLength();

        while ((nread = read(ev.data.fd, readbuf + nindex, nleft)) > 0) 
        {  
            nindex += nread;
            nleft -= nread;
            if(0 == nleft)
                break;
        }
        if (nread == -1 && errno != EAGAIN) 
        {
            perror("read error");
            delete pTask;

            return;
        }

        pPackage->SetLength(nindex);

        pTask->AddPackage(pPackage);        

        if(errno == EAGAIN)
        {
            break;
        }

    }while(true)
    
    CTaskMgr* pTaskMgr = CTaskMgr::GetTaskMgr();
    pTaskMgr->AddTask(pTask);
}

void CEpollHandler::DoWrite(int fd, char* data)
{                
    /*
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);  
    int nwrite, data_size = strlen(buf);  
    n = data_size;  
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
    close(fd);
    */
    CPackage* pPackage = (CPackage*)data;
    char* buf = pPackage->GetData();
    sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\nHello World", 11);  
    int nwrite, data_size = strlen(buf);  
    int n = data_size;  
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
    close(fd);
}

void CEpollHandler::StartEpoll()
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
            if (fd == m_iListenFd) 
            {  
                DoAccept();
                continue;  
            }    
            if (events[fdIndex].events & EPOLLIN) 
            {  
                DoRead(events[fdIndex]);
            }
            else if (events[i].events & EPOLLOUT) 
            {
                DoWrite(fd, events[i].data.ptr);
            } 
        }  
    }

    free(events);
    return 0;  
}

void CEpollHandler::InitListenEnv()
{
    struct sockaddr_in local;  
  
    if( (m_iListenFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  
        perror("sockfd\n");  
        exit(1);  
    }  

    SetNonBlocking(m_iListenFd);  
    
    bzero(&local, sizeof(local));  
    local.sin_family = AF_INET;  
    local.sin_addr.s_addr = htonl(INADDR_ANY);;  
    local.sin_port = htons(m_iPort);  
    if( bind(m_iListenFd, (struct sockaddr *) &local, sizeof(local)) < 0) {  
        perror("bind\n");  
        exit(1);  
    }  
    listen(m_ListenFd, 20);

    
    m_iEpollFd = epoll_create(m_iMaxEvents);  
    if (m_iEpollFd == -1) 
    {  
        perror("epoll_create");  
        exit(EXIT_FAILURE);  
    }  
    
    struct epoll_event ev;
    ev.events = EPOLLIN|EPOLLET;  
    ev.data.fd = m_iListenFd;  
    if (epoll_ctl(m_iEpollFd, EPOLL_CTL_ADD, m_iListenFd, &ev) == -1) 
    {  
        perror("epoll_ctl: listen_sock");  
        exit(EXIT_FAILURE);  
    }  
}

}
