/**
 * @file CKMemMgr.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/25 11:08:42
 * @brief 
 *  
 **/




#ifndef  __CKMEMMGR_H_
#define  __CKMEMMGR_H_

#include "../config/CKConfig.h"
#include "CKPackage.h"
#include <queue>
#include <pthread.h>

namespace ks
{

class CMemMgr
{
private:
    static CMemMgr* m_pMemMgrInstance;
    CMemMgr();

public:
    static CMemMgr* GetMemMgr()
    {
        if(NULL == m_pMemMgrInstance)
            m_pMemMgrInstance = new CMemMgr();
        return m_pMemMgrInstance;
    }
    ~CMemMgr();
    
    void Init(CConfig* pConfig);
    void Push(CPackage* pPackage);
    CPackage* Pull();

private:
    std::queue<CPackage*>   m_cQueuePackage;    //head and tail lock
    pthread_mutex_t         m_MutexHead;
    pthread_mutex_t         m_MutexTail;
};

}
#endif  //__CKMEMMGR_H_
