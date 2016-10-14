/**
 * @file CKPackage.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 18:01:37
 * @brief 
 *  
 **/
#include "CKPackage.h"
#include "CKMemMgr.h"
#include <iostream>

namespace ks
{

CMemBlock::CMemBlock(size_t length)
 : m_iLength(length), m_iUsedSize(0)
 , m_pData(NULL), m_bIsFree(true)
{
}

CMemBlock::~CMemBlock()
{
}

CHeadPack::CHeadPack(size_t length)
 : CMemBlock(length)
{
}
CHeadPack::~CHeadPack()
{
    if(m_pData != NULL)
    {
        free(m_pData);
        m_pData = NULL;
    }
}

void CHeadPack::Init()
{
    m_pData = (void*)malloc(m_iLength);
}
void CHeadPack::Release()
{
    m_bIsFree = true;
    m_iUsedSize = 0;
    CMemMgr::GetMemMgr()->GetMemHeadMgr()->Push(this);
}

CBodyPack::CBodyPack(size_t length)
 : CMemBlock(length)
{
}
CBodyPack::~CBodyPack()
{
}

void CBodyPack::Init(void* pData, CBodyPack* preBlock, CBodyPack* nextBlock)
{
    m_pData = pData;
    m_pPreBlock = preBlock;
    m_pNextBlock = nextBlock;
}

void CBodyPack::Release()
{
    //todo
    m_bIsFree = true;
    m_iUsedSize = 0;
    CMemMgr* pMemMgr = CMemMgr::GetMemMgr();
    pMemMgr->GetMemBodyMgr()->Push(this);
}

CPackage::CPackage(CHeadPack* pHeadPack, CBodyPack* pBodyPack)
 : m_pHeadPack(pHeadPack), m_pBodyPack(pBodyPack) 
{
}

CPackage::~CPackage()
{
    if(m_pHeadPack != NULL)
        m_pHeadPack->Release();
    if(m_pBodyPack != NULL)
        m_pBodyPack->Release();
}


}




















