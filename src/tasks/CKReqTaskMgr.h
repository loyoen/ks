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
#include "../include/define.h"

namespace ks
{


class CReqTaskMgr : public CTaskMgr
{
    SINGLETON(ReqTaskMgr)

public:
    void Init();
    void SetUserCallBackFunc(PtrFunc func);
    PtrFunc GetUserCallBackFunc();

private:
    PtrFunc  m_UserCallBackFunc;    
};

}














#endif  //__CKREQTASKMGR_H_
