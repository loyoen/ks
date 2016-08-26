/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKConfig.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 10:42:19
 * @brief 
 *  
 **/




#ifndef  __CKCONFIG_H_
#define  __CKCONFIG_H_

namespace ks
{

typedef unsigned int size_t;

class CConfig
{
public:
    CConfig();
    ~CConfig();

    Init();

    size_t GetThreadNum();
    size_t GetPackageNum();
    size_t GetPackageSize();
    size_t GetMaxSocketNum();

private:
    size_t      m_iThreadNum;
    size_t      m_iPackageNum;
    size_t      m_iPackageSize;
    size_t      m_iMaxSocketNum;
};

}
#endif  //__CKCONFIG_H_
