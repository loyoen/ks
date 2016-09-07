/**
 * @file CKMemMgr.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 18:16:11
 * @brief 
 *  
 **/

#include "CKMemMgr.h"
#include "../log/KSLog.h"

namespace ks
{

CMemMgr* CMemMgr::m_pMemMgrInstance = NULL;

CMemMgr::CMemMgr()
{
    pthread_mutex_init(&m_MutexHead, NULL);
    pthread_mutex_init(&m_MutexTail, NULL);
}
CMemMgr::~CMemMgr()
{
    while(!m_cQueuePackage.empty())
    {
        CPackage* pPackage = m_cQueuePackage.front();
        m_cQueuePackage.pop();
        delete pPackage;
    }
    pthread_mutex_destroy(&m_MutexHead);
    pthread_mutex_destroy(&m_MutexTail);
}

void CMemMgr::Init(CConfig* pConfig)
{
    size_t iPackageNum = pConfig->GetPackageNum();
    size_t iPackageSize = pConfig->GetPackageSize();
    for(size_t i=0; i<iPackageNum; i++)
    {
        CPackage* pPackage = new CPackage(iPackageSize);
        pPackage->Init();
        Push(pPackage);
    }
}

void CMemMgr::Push(CPackage* pPackage)
{
    //lock
    pthread_mutex_lock(&m_MutexTail);
    m_cQueuePackage.push(pPackage);
    pthread_mutex_unlock(&m_MutexTail);
}
    
CPackage* CMemMgr::Pull()
{
    if(m_cQueuePackage.empty())
    {
        return NULL;
    }

    CPackage* pPackage = NULL;
    
    pthread_mutex_lock(&m_MutexHead);
    if(!m_cQueuePackage.empty())
    {
        pPackage = m_cQueuePackage.front();
        m_cQueuePackage.pop();
    }
    pthread_mutex_unlock(&m_MutexHead);
    
    if(NULL == pPackage)
    {
        LOG_ERROR("No package left");
    }
    return pPackage;
}

}

