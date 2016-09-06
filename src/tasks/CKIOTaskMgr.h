/**
 * @file CKIOTaskMgr.h
 * @author loyoen(com@gmail.com)
 * @date 2016/09/06 15:57:53
 * @brief 
 *  
 **/




#ifndef  __CKIOTASKMGR_H_
#define  __CKIOTASKMGR_H_

#include "CKTaskMgr.h"
#include "../thread/Thread.h"

namespace ks
{

class CIOTaskMgr : public CTaskMgr
{
private:
    static CIOTaskMgr* m_pTaskMgrInstance;
    CIOTaskMgr();
    CThread* m_pThread;

public:
    static CIOTaskMgr* GetTaskMgr()
    {
        if(NULL == m_pTaskMgrInstance)
            m_pTaskMgrInstance = new CIOTaskMgr();
        return m_pTaskMgrInstance;
    }

    ~CIOTaskMgr();
    void Init();
};

}














#endif  //__CKIOTASKMGR_H_
