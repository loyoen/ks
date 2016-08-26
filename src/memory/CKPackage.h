/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKPackage.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 17:54:44
 * @brief 
 *  
 **/




#ifndef  __CKPACKAGE_H_
#define  __CKPACKAGE_H_

namespace ks
{

class CPackage
{
public:
    CPackage(size_t length);
    ~CPackage();

    void Init();
    void Release();
    void SetFree(bool bIsFree);
    size_t GetLength();
    char* GetData();

private:
    size_t  m_iLength;
    bool    m_bIsFree;
    char*   m_pData;
};

}














#endif  //__CKPACKAGE_H_
