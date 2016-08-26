/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file TaskHandler.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 10:34:53
 * @brief 
 *  
 **/




#ifndef  __TASKHANDLER_H_
#define  __TASKHANDLER_H_

#include "CKTaskMgr.h"
#include "../thread/Thread.h"

namespace ks
{

class CTaskHandler : public CThreadHandler
{
public:
    CTaskHandler();
    ~CTaskHandler();

    virtual int OnThreadProc();
};

}














#endif  //__TASKHANDLER_H_
