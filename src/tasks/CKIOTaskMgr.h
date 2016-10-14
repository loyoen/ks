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
#include "../include/define.h"

namespace ks
{

class CIOTaskMgr : public CTaskMgr
{
    SINGLETON(IOTaskMgr)

private:
    CThread* m_pThread;

public:
    void Init();
};

}














#endif  //__CKIOTASKMGR_H_
