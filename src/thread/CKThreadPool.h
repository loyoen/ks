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
    SINGLETON(ThreadMgr)


public:

    void Init(CConfig* pConfig);
    bool ActivateThreadPool();
    void StopThreadPool();

private:
    size_t  m_iThreadNum;
    std::vector<CThread*>   m_Threads; 
};

}

#endif  //__CKTHREADPOOL_H_
