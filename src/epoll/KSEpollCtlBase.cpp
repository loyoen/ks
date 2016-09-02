/**
 * @file KSEpollCtlBase.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/09/02 16:42:59
 * @brief 
 *  
 **/

#include "KSEpollCtlBase.h"

namespace ks
{

CEpollCtlBase::CEpollCtlBase()
{
}

CEpollCtlBase::CEpollCtlBase(int epfd, int fd)
 : m_iEpollFd(epfd), m_iFd(fd)
{
}

int CEpollCtlBase::SetEpollIn(int fd)
{
    m_ev.events = EPOLLIN | EPOLLET;
    m_ev.data.fd = fd;
    return epoll_ctl(m_iEpollFd, EPOLL_CTL_MOD, fd, &m_ev);
}

int CEpollCtlBase::SetEpollOut(int fd, void* ptr)
{
    m_ev.events = EPOLLOUT | EPOLLET;
    m_ev.data.fd = fd;
    m_ev.data.ptr = ptr;
    return epoll_ctl(m_iEpollFd, EPOLL_CTL_MOD, fd, &m_ev);
}

int CEpollCtlBase::SetEpollAdd(int fd)
{
    m_ev.events = EPOLLIN | EPOLLET;
    m_ev.data.fd = fd;
    return epoll_ctl(m_iEpollFd, EPOLL_CTL_ADD, fd, &m_ev);
}

int CEpollCtlBase::SetEpollDel(int fd)
{
    m_ev.events = EPOLLIN | EPOLLET;
    m_ev.data.fd = fd;
    return epoll_ctl(m_iEpollFd, EPOLL_CTL_DEL, fd, &m_ev);
}





}
