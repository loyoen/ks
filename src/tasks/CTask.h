/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CTask.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 10:51:16
 * @brief 
 *  
 **/




#ifndef  __CTASK_H_
#define  __CTASK_H_

#include "../memory/CKPackage.h"
#include <vector>

namespace ks
{

class CTask
{
public:
    virtual void Run() = 0;
    virtual void CallBack() = 0;
};

class CEchoTask : public CTask
{
public:
    CEchoTask(int fd, int events);
    ~CEchoTask();

    virtual void Run();
    virtual void CallBack();

    void AddPackage(CPackage* pPackage);

private:
    std::vector<CPackage*>  m_Packages;
    CPackage*               m_OutPackage; 
    int m_iFd;
};

}















#endif  //__CTASK_H_
