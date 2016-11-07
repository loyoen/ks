/**
 * @file CKMemMgr.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/25 11:08:42
 * @brief 
 *  
 **/




#ifndef  __CKMEMMGR_H_
#define  __CKMEMMGR_H_

#include "../config/CKConfig.h"
#include "../include/define.h"
#include "CKPackage.h"
#include <queue>
#include <pthread.h>

namespace ks
{

class CMemHeadMgr
{
    SINGLETON(MemHeadMgr)

public:
    void Init(int PackNum, int PackLength);
    void Push(CHeadPack* pHeadPack);
    CHeadPack* Pull();

private:
    std::queue<CHeadPack*>  m_qHeadPackages;
    pthread_mutex_t         m_MutexHead;
    pthread_mutex_t         m_MutexTail;

};

class CMemBodyMgr
{
    SINGLETON(MemBodyMgr)

public:
    void Init(size_t length);
    void Push(CBodyPack* pBodyPack);
    CBodyPack* Pull(size_t length);
    
    //test
    void Display();
    void ReverseDisplay();

private:
    void*                   m_pStartMemPos;
    CBodyPack*              m_pBodyChain;
    std::vector<CBodyPack*> m_vFreeBlocks;
    pthread_mutex_t         m_MutexChain;
};

class CMemMgr
{
    SINGLETON(MemMgr)

public: 
    void Init(CConfig* pConfig);
    CMemHeadMgr*    GetMemHeadMgr(){return m_pMemHeadMgr;}
    CMemBodyMgr*    GetMemBodyMgr(){return m_pMemBodyMgr;}

private:
    CMemHeadMgr*    m_pMemHeadMgr;
    CMemBodyMgr*    m_pMemBodyMgr;
};

}
#endif  //__CKMEMMGR_H_
