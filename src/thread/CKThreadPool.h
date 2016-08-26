/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKThreadPool.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 13:40:26
 * @brief 
 *  
 **/




#ifndef  __CKTHREADPOOL_H_
#define  __CKTHREADPOOL_H_

#include "CKConfig.h"
#include <vector>
namespace ks
{

class CThreadMgr
{
private:
    CThreadMgr();
    static CThreadMgr* m_pThreadMgrInstance = NULL;

public:
    static CThreadMgr* GetThreadMgr()
    {
        if(NULL == m_pThreadMgrInstance)
            m_pThreadMgrInstance = new CThreadMgr();
        return m_pThreadMgrInstance;
    }
    ~CThreadMgr();

    void Init(CConfig* pConfig, CThreadHandler* pHandler);
    bool ActivateThreadPool();
    void StopThreadPool();

private:
    size_t  m_iThreadNum;
    std::vector<CThread*>   m_Threads; 
    CThreadHandler*         m_pTaskHandler;
};

}

#endif  //__CKTHREADPOOL_H_
