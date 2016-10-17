/**
 * @file KSockMgr.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/10/13 11:13:00
 * @brief 
 *  
 **/

#include "KSockMgr.h"
#include "../tasks/CKReqTaskMgr.h"
#include "../log/KSLog.h"
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
#include <iostream>

namespace ks
{

CSock::CSock(int fd)
 : m_iFd(fd)
{
    m_iIndexPos = 0;
    m_ReadStats = READ_HEAD;
    m_pHeadPack = NULL;//CMemMgr::GetMemMgr()->GetMemHeadMgr()->Pull();
    m_pBodyPack = NULL;
    m_iContentLen = 0;
}
CSock::~CSock()
{
}
#define HTTP
int CSock::DoReadHead()
{
    m_pHeadPack = CMemMgr::GetMemMgr()->GetMemHeadMgr()->Pull();
    int iTotalRead = 0;
    int iHeadLength = m_pHeadPack->GetLength();
    int nread = 0, nleft = iHeadLength - m_iIndexPos;
    while((nread = read(m_iFd, (char*)m_pHeadPack->GetData() + m_iIndexPos, nleft)) >0)
    {
        m_iIndexPos += nread;
        iTotalRead += nread;
        nleft -= nread;
        if(0 >= nleft)
        {
            break;
        }
    }
    if(0 == nread)
    {
        return iTotalRead;
    }
    else if(-1 == nread && 0 == iTotalRead)
    {
        return 0;
    }
#ifdef HTTP
    char* szData = (char*)m_pHeadPack->GetData();
    char* pHeadEnd = strstr(szData,"\r\n\r\n");
    if(pHeadEnd == NULL)
    {
        LOG_ERROR("READ HEAD AGAIN");
        return iTotalRead + DoReadHead();
    }
    
    int iHeadUsedSize = pHeadEnd + 4 - (char*)m_pHeadPack->GetData();
    
    m_pHeadPack->SetUsedSize(iHeadUsedSize);
    
    if(memcmp(szData, "POST ", 5) == 0)
    {
        char* pContentLen = strstr(szData, "Content-Length: ");
        if(pContentLen)
        {
            pContentLen += strlen("Content-Length: ");
            m_iContentLen = atoi(pContentLen);
        }
    }
    if(m_iContentLen > 0)
    {
        m_pBodyPack = CMemMgr::GetMemMgr()->GetMemBodyMgr()->Pull(m_iContentLen);
        memcpy(m_pBodyPack->GetData(), pHeadEnd+4, m_iIndexPos-iHeadUsedSize);
        m_iIndexPos = m_iIndexPos - iHeadUsedSize;
        m_ReadStats = READ_BODY;
        return iTotalRead + Read();
    }
    m_ReadStats = READ_HEAD;
    m_iIndexPos = 0; 
    CPackage* pPackage = new CPackage(m_pHeadPack, m_pBodyPack);
    CEchoTask* pTask = new CEchoTask(CSockMgr::GetSockMgr()->GetEpollFd(), m_iFd, pPackage);
    CReqTaskMgr::GetReqTaskMgr()->AddTask(pTask);


    return iTotalRead;
#else
    LOG_ERROR("not http");
#endif
}

int CSock::DoReadBody()
{
    int iTotalRead = 0;
    int nread = 0, nleft = m_iContentLen - m_iIndexPos;
    while((nread = read(m_iFd, (char*)m_pBodyPack->GetData() + m_iIndexPos, nleft)) > 0)
    {
        m_iIndexPos += nread;
        iTotalRead += nread;
        nleft -= nread;
        if(0 >= nleft)
        {
            break;
        }
    }
    if(0 == nread && nleft != 0)
    {
        return iTotalRead;
    }
    CPackage* pPackage = new CPackage(m_pHeadPack, m_pBodyPack);
    CEchoTask* pTask = new CEchoTask(CSockMgr::GetSockMgr()->GetEpollFd(), m_iFd, pPackage);
    CReqTaskMgr::GetReqTaskMgr()->AddTask(pTask);


    m_ReadStats = READ_HEAD;
    m_iIndexPos = 0;
    m_iContentLen = 0;
    //contine read because epoll ET
    return iTotalRead + Read(); 
}

int CSock::Read()
{
    int nread = 0;
    switch(m_ReadStats)
    {
    case READ_HEAD:
        std::cout << "read head" << std::endl;
        nread = DoReadHead();
        break;
    case READ_BODY:
        std::cout << "read body" << std::endl;
        nread = DoReadBody();
        break;
    default:
        std::cout << "read other" << std::endl;
        break;
    }

    std::cout << "nread = " << nread << std::endl;
    if(0 == nread)
    {
        int i= 1;
        //CSockMgr::GetSockMgr()->CloseSock(m_iFd);
    }
    return nread;
}

INITIALIZE(SockMgr)

CSockMgr::CSockMgr()
{
}
CSockMgr::~CSockMgr()
{
}
int CSockMgr::Read(int fd)
{
    std::map<int, CSock*>::iterator iter = m_mSocks.find(fd);
    if(iter != m_mSocks.end())
    {
        CSock* pSock = iter->second;
        return pSock->Read();
    }
    else
    {
        LOG_ERROR("THIS sock not in map");
        return -1;
    }
}
void CSockMgr::CloseSock(int fd)
{
    LOG_ERROR("CLOSE FD");
    close(fd);
    std::map<int, CSock*>::iterator iter = m_mSocks.find(fd);
    if(iter != m_mSocks.end())
    {
        delete iter->second;
        m_mSocks.erase(iter);
    }
}

void CSockMgr::AddSock(int fd)
{
    CSock* pSock = new CSock(fd);
    m_mSocks.insert(std::make_pair<int, CSock*>(fd, pSock));
}


}

















