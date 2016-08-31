/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Thread.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 16:39:37
 * @brief 
 *  
 **/




#ifndef  __THREAD_H_
#define  __THREAD_H_

#include <pthread.h>

namespace ks
{

class CThreadHandler
{
public:
    virtual int OnThreadProc() = 0;
    void Stop(){m_bStoped=true;}
    bool IsStop(){return m_bStoped;}
protected:
    bool    m_bStoped;
};

class CThread
{
public:
    CThread(CThreadHandler* pHandler);
    ~CThread();

    int Start();
    void Stop();
    bool IsStop();
    void Wait();

public:
    int OnThreadProc();

protected:
    CThreadHandler*  m_pHandler;
    pthread_t       m_iThreadId;
};

}

#endif  //__THREAD_H_
