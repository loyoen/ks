/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKMemMgr.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 18:16:11
 * @brief 
 *  
 **/

#include "CKMemMgr.h"

namespace ks
{

CMemMgr::CMemMgr()
{
}
CMemMgr::~CMemMgr()
{
    while(!m_cQueuePackage.empty())
    {
        CPackage* pPackage = m_cQueuePackage.front();
        m_cQueuePackage.pop();
        delete pPackage;
    }
}

void CMemMgr::MemInit(CConfig* pConfig)
{
    size_t iPackageNum = pConfig->GetPackageNum();
    size_t iPackageSize = pConfig->GetPackageSize();
    for(size_t i=0; i<iPackageNum; i++)
    {
        CPackage* pPackage = new CPackage(iPackageSize);
        Push(pPackage);
    }
}

void CMemMgr::Push(CPackage* pPackage)
{
    //lock
    m_cQueuePackage.push(pPackage);
}
    
CPackage* CMemMgr::Pull()
{
    //another lock
    if(m_cQueuePackage.empty())
        return NULL;

    CPackage* pPackage = m_cQueuePackage.front();
    m_cQueuePackage.pop();

    return pPackage;
}

}




















