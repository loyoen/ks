/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKServer.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 10:31:50
 * @brief 
 *  
 **/




#ifndef  __CKSERVER_H_
#define  __CKSERVER_H_

#include "CKConfig.h"
#include "CKMemMgr.h"
#include "CKThreadPool.h"

namespace ks
{

class CKServer
{
public:
    CKServer();
    ~CKServer();
    
    void Init();
    void Run();

private:
    CConfig*        m_pConfig;
    CMemMgr*        m_pMemMgr;
    CThreadMgr*     m_pThreadMgr;
    CKTaskMgr*      m_pTaskMgr;
}; 

}
#endif  //__CKSERVER_H_

