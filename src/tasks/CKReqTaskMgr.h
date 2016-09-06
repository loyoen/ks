/**
 * @file CKReqTaskMgr.h
 * @author loyoen(com@gmail.com)
 * @date 2016/09/06 15:43:42
 * @brief 
 *  
 **/




#ifndef  __CKREQTASKMGR_H_
#define  __CKREQTASKMGR_H_

#include "CKTaskMgr.h"

namespace ks
{

typedef int (*PtrFuncTwo)(void*, void*);

class CReqTaskMgr : public CTaskMgr
{
private:
    CReqTaskMgr();
    static CReqTaskMgr* m_pTaskMgrInstance;

public:
    static CReqTaskMgr* GetTaskMgr()
    {
        if(NULL == m_pTaskMgrInstance)
            m_pTaskMgrInstance = new CReqTaskMgr();
        return m_pTaskMgrInstance;
    }

    ~CReqTaskMgr();
    void Init();
    void SetUserCallBackFunc(PtrFuncTwo func);
    PtrFuncTwo GetUserCallBackFunc();

private:
    PtrFuncTwo  m_UserCallBackFunc;    
};

}














#endif  //__CKREQTASKMGR_H_
