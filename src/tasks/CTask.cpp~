/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file Task.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 13:52:38
 * @brief 
 *  
 **/

#include "Task.h"

namespace ks
{

CEchoTask::CEchoTask()
{
}
CEchoTask::~CEchoTask()
{
    for(int i=0; i<m_Packages.size();i++)
    {
        m_Packages->Release();
    }
    m_Packages.clear();
}

CEchoTask::AddPackage(CPackage* pPackage)
{
    if(NULL != pPackage)
        m_Packages.push_back(pPackage);
}

void CEchoTask::Run()
{
    
}

void CEchoTask::CallBack()
{
}


}
