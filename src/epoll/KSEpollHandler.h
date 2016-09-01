/**
 * @file ../epoll/KSEpollHandler.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/29 09:40:07
 * @brief 
 *  
 **/




#ifndef  KSEPOLLHANDLER_H_
#define  KSEPOLLHANDLER_H_

#include "../thread/Thread.h"
#include "../config/CKConfig.h"
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

class CEpollHandler : public CThreadHandler
{
public:
    CEpollHandler(CConfig* pConfig);
    ~CEpollHandler();

    virtual int OnThreadProc();

private:
    void SetNonBlocking(int sockfd);
    void InitEnv();
    int StartEpoll();

    int DoWait(epoll_event* events);
    void DoAccept();
    void DoRead(epoll_event& ev);
    void DoWrite(char* data);

private:
    size_t  m_iMaxEvents;
    size_t  m_iPort;
    int     m_iListenFd;
    int     m_iEpollFd;

    int     m_iNfds;
    int     m_iCurConnSock;

    sockaddr_in  m_local;
    sockaddr_in  m_remote;
    int     m_addrlen;
    epoll_event  m_ev;
};


}














#endif  //____/EPOLL/KSEPOLLHANDLER_H_
