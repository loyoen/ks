/**
 * @file CKMemMgr.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 18:16:11
 * @brief 
 *  
 **/

#include "CKMemMgr.h"
#include "../log/KSLog.h"
#include <iostream>

namespace ks
{

INITIALIZE(MemHeadMgr)

CMemHeadMgr::CMemHeadMgr()
{
    pthread_mutex_init(&m_MutexHead, NULL);
    pthread_mutex_init(&m_MutexTail, NULL);
}
CMemHeadMgr::~CMemHeadMgr()
{
    while(!m_qHeadPackages.empty())
    {
        CHeadPack* pPack = m_qHeadPackages.front();
        m_qHeadPackages.pop();
        delete pPack;
    }
    pthread_mutex_destroy(&m_MutexHead);
    pthread_mutex_destroy(&m_MutexTail);
}
void CMemHeadMgr::Init(int PackNum, int PackLength)
{
    for(size_t i=0; i<PackNum; i++)
    {
        CHeadPack* pHeadPack = new CHeadPack(PackLength);
        pHeadPack->Init();
        Push(pHeadPack);
    }
} 

void CMemHeadMgr::Push(CHeadPack* pPack)
{
    //lock
    pthread_mutex_lock(&m_MutexTail);
    m_qHeadPackages.push(pPack);
    pthread_mutex_unlock(&m_MutexTail);
}
    
CHeadPack* CMemHeadMgr::Pull()
{
    if(m_qHeadPackages.empty())
    {
        std::cout << "pull empty" << std::endl;
        return NULL;
    }

    CHeadPack* pPackage = NULL;
    
    pthread_mutex_lock(&m_MutexHead);
    if(!m_qHeadPackages.empty())
    {
        pPackage = m_qHeadPackages.front();
        m_qHeadPackages.pop();
    }
    pthread_mutex_unlock(&m_MutexHead);
    
    if(NULL == pPackage)
    {
        std::cout << "pull empty" << std::endl;
        LOG_ERROR("No package left");
    }
    return pPackage;
}

INITIALIZE(MemBodyMgr)

CMemBodyMgr::CMemBodyMgr()
{
    m_pBodyChain = NULL;
    m_pStartMemPos = NULL;
    pthread_mutex_init(&m_MutexChain, NULL);
}
CMemBodyMgr::~CMemBodyMgr()
{
    if(m_pStartMemPos != NULL)
    {
        free(m_pStartMemPos);
        m_pStartMemPos = NULL;
    }

    CBodyPack* pBodyPack = m_pBodyChain;
    while(pBodyPack != NULL)
    {
        CBodyPack* pNextPack = pBodyPack->GetNextBlock();
        delete pBodyPack;
        pBodyPack = pNextPack;
    }
    m_pBodyChain = NULL;
    pthread_mutex_destroy(&m_MutexChain);
}

void CMemBodyMgr::Init(size_t length)
{
    std::cout << "malloc length " << length << std::endl;
    m_pStartMemPos = (void*)malloc(length);
    m_pBodyChain = new CBodyPack(length);
    m_pBodyChain->Init(m_pStartMemPos, NULL, NULL);
    m_vFreeBlocks.push_back(m_pBodyChain);
}
void CMemBodyMgr::Push(CBodyPack* pBodyPack)
{
    //todo
    std::cout << "push mem start" << std::endl;
    pthread_mutex_lock(&m_MutexChain);

    if(pBodyPack == NULL)
        return;

    bool bIsCombine = false;
    CBodyPack* pCurBlock = pBodyPack;
    CBodyPack* pPreBlock = pBodyPack->GetPreBlock();
    CBodyPack* pNextBlock = pBodyPack->GetNextBlock();
    if(pPreBlock != NULL && pPreBlock->IsFree())
    {
        bIsCombine = true;
        pPreBlock->SetLength(pPreBlock->GetLength() + pBodyPack->GetLength());
        pPreBlock->SetNextBlock(pNextBlock);
        if(pNextBlock != NULL)
        {
            pNextBlock->SetPreBlock(pPreBlock);
        }
        pCurBlock = pPreBlock;
        delete pBodyPack;
        pBodyPack = NULL;
    }
    if(pNextBlock != NULL && pNextBlock->IsFree())
    {
        bIsCombine = true;
        pCurBlock->SetLength(pCurBlock->GetLength() + pNextBlock->GetLength());
        pCurBlock->SetNextBlock(pNextBlock->GetNextBlock());
        if(pNextBlock->GetNextBlock() != NULL)
        {
            pNextBlock->GetNextBlock()->SetPreBlock(pCurBlock);
        }
        delete pNextBlock;
        pNextBlock = NULL;
    }
    if(!bIsCombine)
    {
        pBodyPack->SetFree(true);
    }

    pthread_mutex_unlock(&m_MutexChain);
    std::cout << "push mem end" << std::endl;
}

CBodyPack* CMemBodyMgr::Pull(size_t length)
{ 
    //todo
    std::cout << "pull mem start" << std::endl;
    pthread_mutex_lock(&m_MutexChain);
    
    CBodyPack* pBodyPack = m_pBodyChain;
    CBodyPack* pResBlock = NULL;
    while(pBodyPack != NULL)
    {
        if(pBodyPack->IsFree() && pBodyPack->GetLength()>length)
        {
            CBodyPack* pNewBodyPack = new CBodyPack(pBodyPack->GetLength()-length);
            pNewBodyPack->Init(((char*)pBodyPack->GetData()) + (pBodyPack->GetLength()-length), 
                    pBodyPack, pBodyPack->GetNextBlock());
            pBodyPack->SetNextBlock(pNewBodyPack);
            pBodyPack->SetFree(false);
            pResBlock = pBodyPack;
            break;
        } 
        else if(pBodyPack->IsFree() && pBodyPack->GetLength()==length)
        {
            pBodyPack->SetFree(false);
            pResBlock = pBodyPack;
            break;
        }
        pBodyPack = pBodyPack->GetNextBlock();
    }
    pthread_mutex_unlock(&m_MutexChain);
    std::cout << "pull mem end" << std::endl;
    return pResBlock;
}


INITIALIZE(MemMgr)

CMemMgr::CMemMgr()
{
    m_pMemHeadMgr = NULL;
    m_pMemBodyMgr = NULL;
}
CMemMgr::~CMemMgr()
{
    if(m_pMemHeadMgr != NULL)
    {
        delete m_pMemHeadMgr;
        m_pMemHeadMgr = NULL;
    }
    if(m_pMemBodyMgr != NULL)
    {
        delete m_pMemBodyMgr;
        m_pMemBodyMgr = NULL;
    }
}

void CMemMgr::Init(CConfig* pConfig)
{
    size_t iHeadPackNum = pConfig->GetIntValue("HeadPackNum");
    size_t iHeadPackLength = pConfig->GetIntValue("HeadPackLength");
    size_t iBodySize = pConfig->GetIntValue("BodySize");
    m_pMemHeadMgr = CMemHeadMgr::GetMemHeadMgr();
    m_pMemHeadMgr->Init(iHeadPackNum, iHeadPackLength);
    m_pMemBodyMgr = CMemBodyMgr::GetMemBodyMgr();
    m_pMemBodyMgr->Init(iBodySize);
}


}

