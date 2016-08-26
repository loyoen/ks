/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKPackage.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 18:01:37
 * @brief 
 *  
 **/
#include "CKPackage.h"
#include "CKMemMgr.h"

namespace ks
{

CPackage::CPackage(size_t length)
{
    m_iLength = length;
    m_bIsFree = true;
    m_pData = NULL;
}

CPackage::~CPackage()
{
    if(m_pData != NULL)
    {
        free(m_pData);
        m_pData = NULL;
    }
}

void CPackage::Init()
{
    m_pData = (char*)malloc(sizeof(char)*length);
}

void CPackage::SetFree(bool bIsFree)
{
    m_bIsFree = bIsFree;
}

size_t CPackage::GetLength()
{
    return m_iLength;
}

char* CPackage::GetData()
{
    return m_pData;
}

void CPackage::Release()
{
    m_bIsFree = true;
    CMemMgr* pMemMgr = CMemMgr::GetMemMgr();
    pMemMgr->Push(this);
}







}




















