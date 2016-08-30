/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ../epoll/KSEpollHandler.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/29 09:40:07
 * @brief 
 *  
 **/




#ifndef  ____/EPOLL/KSEPOLLHANDLER_H_
#define  ____/EPOLL/KSEPOLLHANDLER_H_

#include "../thread/Thread.h"
#include "../config/CKConfig.h"

namespace ks
{

class CEpollHandler : public CThreadHandler
{
public:
    CEpollHandler(CConfig* pConfig);
    ~CEpollHandler();

    virtual int OnThreadProc();

private:
    void SetNonBlocking(int sockfd);
    void InitEnv();
    void StartEpoll();

    int DoWait();
    void DoAccept();
    void DoRead();
    void DoWrite();

private:
    size_t  m_iMaxEvents;
    size_t  m_iPort;
    int     m_iListenFd;
    int     m_iEpollFd;

    int     m_iNfds;
    int     m_iCurConnSock;

    struct sockaddr_in  m_local;
    struct sockaddr_in  m_remote;
    int     m_addrlen;
    struct epoll_event  m_ev;
};


}














#endif  //____/EPOLL/KSEPOLLHANDLER_H_
