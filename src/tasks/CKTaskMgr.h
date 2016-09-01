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

typedef int (*PtrFuncTwo)(void*, void*);

class CTaskMgr
{
private:
    CTaskMgr();
    static CTaskMgr* m_pTaskMgrInstance;

public:
    static CTaskMgr* GetTaskMgr()
    {
        if(NULL == m_pTaskMgrInstance)
            m_pTaskMgrInstance = new CTaskMgr();
        return m_pTaskMgrInstance;
    }

    ~CTaskMgr();

    void Init(){}
    void AddTask(CTask* pTask);
    CTask* GetTask();

    void SetUserCallBackFunc(PtrFuncTwo func);
    PtrFuncTwo GetUserCallBackFunc();
private:
    std::queue<CTask*>  m_Tasks;
    PtrFuncTwo  m_UserCallBackFunc;

    pthread_mutex_t m_MutexHead;
    pthread_mutex_t m_MutexTail;
};

}

#endif  //__CKTASKMGR_H_
