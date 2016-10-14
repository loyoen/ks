/**
 * @file CKServer.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/25 10:31:50
 * @brief 
 *  
 **/




#ifndef  __CKSERVER_H_
#define  __CKSERVER_H_

#include "./config/CKConfig.h"
#include "./memory/CKMemMgr.h"
#include "./thread/CKThreadPool.h"
#include "./tasks/CKReqTaskMgr.h"
#include "./tasks/CKIOTaskMgr.h"
#include "./epoll/KSEpollHandler.h"
#include "./log/KSLog.h"

namespace ks
{

class CKServer
{
public:
    CKServer();
    ~CKServer();
    
    void Init();
    void Run();
    void SetUserCallBackFunc(PtrFunc func);

private:
    CConfig*        m_pConfig;
    CMemMgr*        m_pMemMgr;
    CThreadMgr*     m_pThreadMgr;
    CReqTaskMgr*    m_pReqTaskMgr;
    CIOTaskMgr*     m_pIOTaskMgr;
    CLogger*        m_pLogger;
}; 

}
#endif  //__CKSERVER_H_

