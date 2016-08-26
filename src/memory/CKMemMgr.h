/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKMemMgr.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 11:08:42
 * @brief 
 *  
 **/




#ifndef  __CKMEMMGR_H_
#define  __CKMEMMGR_H_

#include "CKConfig.h"
#include "CKPackage.h"
#include <queue>

namespace ks
{

class CMemMgr
{
private:
    static CMemMgr* m_pMemMgrInstance = NULL;
    CMemMgr();

public:
    static CMemMgr* GetMemMgr()
    {
        if(NULL == m_pMemMgrInstance)
            m_pMemMgrInstance = new CMemMgr();
        return m_pMemMgrInstance;
    }
    ~CMemMgr();
    
    void MemInit(CConfig* pConfig);
    void Push(CPackage* pPackage);
    CPackage* Pull();

private:
    //std::queue<CSock*>      m_cQueueSock;       //head and tail lock LRU
    std::queue<CPackage*>   m_cQueuePackage;    //head and tail lock

};

}
#endif  //__CKMEMMGR_H_
