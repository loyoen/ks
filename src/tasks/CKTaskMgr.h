/**
 * @file CKTaskMgr.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/25 14:06:27
 * @brief 
 *  
 **/




#ifndef  __CKTASKMGR_H_
#define  __CKTASKMGR_H_

#include "CTask.h"
#include <queue>
#include <pthread.h>

namespace ks
{

class CTaskMgr
{
public:
    CTaskMgr();

    ~CTaskMgr();

    virtual void Init();
    void AddTask(CTask* pTask);
    CTask* GetTask();

private:
    std::queue<CTask*>  m_Tasks;

    pthread_mutex_t m_MutexHead;
    pthread_mutex_t m_MutexTail;
};

}

#endif  //__CKTASKMGR_H_
