/**
 * @file KSNetBase.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/09/02 16:11:19
 * @brief 
 *  
 **/




#ifndef  __KSEPOLLCTLBASE_H_
#define  __KSEPOLLCTLBASE_H_

#include <sys/epoll.h>

namespace ks
{

class CEpollCtlBase
{
protected:
    int             m_iFd;
    int             m_iEpollFd;
    epoll_event     m_ev;

public:

    CEpollCtlBase();
    CEpollCtlBase(int epfd, int fd);

    virtual int SetEpollIn(int fd);
    virtual int SetEpollOut(int fd, void* ptr);
    virtual int SetEpollAdd(int fd);
    virtual int SetEpollDel(int fd);

};

}















#endif  //__KSEPOLLCTLBASE_H_
