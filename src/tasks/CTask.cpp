/**
 * @file CTask.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 13:52:38
 * @brief 
 *  
 **/

#include "CTask.h"
#include "../memory/CKMemMgr.h"
#include "CKReqTaskMgr.h"
#include "../log/KSLog.h"
#include <errno.h>   
#include <iostream>

namespace ks
{

CEchoTask::CEchoTask(int epfd, int fd)
    : CEpollCtlBase(epfd, fd)
{
    m_OutPackage = CMemMgr::GetMemMgr()->Pull();
    if(m_OutPackage == NULL)
    {
        std::cout << "no out package" << std::endl;
    }
}
CEchoTask::~CEchoTask()
{
    for(int i=0; i<m_Packages.size();i++)
    {
        m_Packages[i]->Release();
    }
    std::vector<CPackage*>().swap(m_Packages);
    //m_Packages.clear();
    
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
    if(NULL == m_OutPackage)
    {
        return;
    }
    (*CReqTaskMgr::GetTaskMgr()->GetUserCallBackFunc())(m_Packages[0], m_OutPackage);
}

void CEchoTask::CallBack()
{
    if(m_OutPackage == NULL)
    {
        std::cout << "no no no " << std::endl;
        delete this;
        return;
    }
    if (SetEpollOut(m_iFd, this) == -1) 
    {  
        perror("epoll_ctl: mod");  
    }
}

CIOTask::CIOTask()
{
    m_pData = NULL;
    m_iLen = 0;
}
CIOTask::~CIOTask()
{
}

CLogTask::CLogTask(char* line)
{
    m_pData = (void*)line;
    m_iLen = strlen(line);
}
CLogTask::~CLogTask()
{
}

void CLogTask::Run()
{
    CLogger* pLogger = CLogger::GetLogger();
    pLogger->Trace(m_pData, m_iLen);
}

void CLogTask::CallBack()
{
    delete this;
}

CReadTask::CReadTask(int epfd,int fd)
 : CEpollCtlBase(epfd,fd)
{
}
CReadTask::~CReadTask()
{
}

void CReadTask::Run()
{
    int nindex = 0, nread = 0, nleft = 0;
    
    CMemMgr* pMemMgr = CMemMgr::GetMemMgr(); 
    CPackage* pPackage = NULL;
    char* readbuf = NULL;
    CEchoTask* pTask = NULL;
    
    do
    {
        nindex = 0;
        nread = 0;
        pPackage = pMemMgr->Pull();
        if(NULL == pPackage)
        {
            std::cout << "read no package fd=" << m_iFd << std::endl;
            return;
        }
        readbuf = (char*)pPackage->GetData();
        nleft = pPackage->GetInitLength();
        while ((nread = read(m_iFd, readbuf + nindex, nleft)) > 0) 
        {  
            nindex += nread;
            nleft -= nread;
            if(0 == nleft)
                break;
        }

        if(nread == 0)
        {
            LOG_INFO("close fd");
            SetEpollDel(m_iFd);
            close(m_iFd);
            
            if(pTask != NULL)
                delete pTask;
            pPackage->Release();
            //std::cout << "nread = 0 fd = " << m_iFd << std::endl;
            return;
        }

        if (nread == -1 && errno != EAGAIN) 
        {
            LOG_ERROR("read error");
            if(pTask != NULL)
                delete pTask;
            pPackage->Release();
            std::cout << "read error fd=" << m_iFd << "err=" << errno << std::endl;
            return;
        }

        pPackage->SetLength(nindex);
        
        if(NULL == pTask)
        {
            pTask = new CEchoTask(m_iEpollFd, m_iFd);
        }
        pTask->AddPackage(pPackage);

        if(errno == EAGAIN)
        {
            break;
        }

    }while(true);
    //std::cout << "read end task" << std::endl;    
    CTaskMgr* pTaskMgr = CReqTaskMgr::GetTaskMgr();
    pTaskMgr->AddTask(pTask);
}

void CReadTask::CallBack()
{
    delete this;
}

CWriteTask::CWriteTask(CEchoTask* pTask, int epfd, int fd)
 : CEpollCtlBase(epfd,fd)
{
    m_pEchoTask = pTask;
}

CWriteTask::~CWriteTask()
{
    if(m_pEchoTask != NULL) 
    {
        delete m_pEchoTask;
        m_pEchoTask = NULL;
    }
}

void CWriteTask::Run()
{
    if(NULL == m_pEchoTask)
    {
        return;
    }

    
    CPackage* pOutPackage = m_pEchoTask->GetOutPackage();// == NULL ? m_pEchoTask->GetOutPackage() : m_pEchoTask->m_Packages[0];
    if(pOutPackage == NULL)
    {
        std::cout << "NO PACKAGE" << std::endl;
        std::cout << "INPUT PACKAGE NUM...." << m_pEchoTask->m_Packages.size() << std::endl;
        if(m_pEchoTask->m_Packages.size()==0)
            return;
        else
        {
            std::cout << m_pEchoTask->m_Packages[0]->GetLength() << std::endl;
        }
        return;
    }
    if(m_pEchoTask->m_Packages[0] == NULL)
    {
        std::cout << "NO PACKAGE two" << std::endl;
        std::cout << "INPUT PACKAGE NUM" << m_pEchoTask->m_Packages.size() << std::endl;
        return;
    }
    char* buf = pOutPackage->GetData();
    int nwrite = 0, data_size = pOutPackage->GetLength();  
    int n = data_size;
    int fd = m_pEchoTask->GetFd();

    while (n > 0) 
    {  
        nwrite = write(fd, buf + data_size - n, n);  
        if (nwrite == -1) 
        {  
            if (errno != EAGAIN) 
            {  
                LOG_ERROR("write error");
                break;  
            }
            else
            {
                LOG_ERROR("need write again");
                break;
            }    
        }  
        n -= nwrite;  
    }
    SetEpollIn(fd);
    //close(fd);
}

void CWriteTask::CallBack()
{
    delete this;
}

}
