/**
 * @file TaskHandler.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 10:34:53
 * @brief 
 *  
 **/




#ifndef  __TASKHANDLER_H_
#define  __TASKHANDLER_H_

#include "../thread/Thread.h"
#include "CKTaskMgr.h"

namespace ks
{

class CTaskHandler : public CThreadHandler
{
public:
    CTaskHandler(CTaskMgr* pTaskMgr);
    ~CTaskHandler();

    virtual int OnThreadProc();

private:
    CTaskMgr* m_pTaskMgr;
};

}














#endif  //__TASKHANDLER_H_
