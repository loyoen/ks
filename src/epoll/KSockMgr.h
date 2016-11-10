 
/**
 * @file KSockMgr.h
 * @author loyoen(com@gmail.com)
 * @date 2016/10/13 10:03:38
 * @brief 
 *  
 **/




#ifndef  __KSOCKMGR_H_
#define  __KSOCKMGR_H_

#include "../include/define.h"
#include "../memory/CKMemMgr.h"
#include <map>

namespace ks
{
enum stats
{
    READ_HEAD   = 0,
    READ_BODY   = 1,
    READ_DONE   = 2,
};

class CSock
{
    enum stats
    {
        READ_HEAD   = 0,
        READ_BODY   = 1,
        READ_DONE   = 2,
    };
public:
    CSock(int fd);
    ~CSock();
    
    int Read();

private:
    int DoReadHead();
    int DoReadBody();

private:
    int m_iFd;
    int m_iIndexPos;
    int m_iContentLen;
    stats m_ReadStats;
    CHeadPack*  m_pHeadPack;
    CBodyPack*  m_pBodyPack;
};

class CSockMgr
{
    SINGLETON(SockMgr)
    
public:
    void    Init(int epoll_fd){m_iEpollFd = epoll_fd;}
    int     Read(int fd);
    void    CloseSock(int fd);
    void    AddSock(int fd); 

    int     GetEpollFd(){return m_iEpollFd;}
private:
    std::map<int, CSock*> m_mSocks;
    int m_iEpollFd;
};

}














#endif  //__KSOCKMGR_H_
