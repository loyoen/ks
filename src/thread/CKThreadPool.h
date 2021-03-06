/**
 * @file CKThreadPool.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/25 13:40:26
 * @brief 
 *  
 **/




#ifndef  __CKTHREADPOOL_H_
#define  __CKTHREADPOOL_H_

#include "../config/CKConfig.h"
#include "Thread.h"
#include <vector>
namespace ks
{

class CThreadMgr
{
private:
    CThreadMgr();
    static CThreadMgr* m_pThreadMgrInstance;

public:
    static CThreadMgr* GetThreadMgr()
    {
        if(NULL == m_pThreadMgrInstance)
            m_pThreadMgrInstance = new CThreadMgr();
        return m_pThreadMgrInstance;
    }
    ~CThreadMgr();

    void Init(CConfig* pConfig);
    bool ActivateThreadPool();
    void StopThreadPool();

private:
    size_t  m_iThreadNum;
    std::vector<CThread*>   m_Threads; 
};

}

#endif  //__CKTHREADPOOL_H_
