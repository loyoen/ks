/**
 * @file CKPackage.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 17:54:44
 * @brief 
 *  
 **/




#ifndef  __CKPACKAGE_H_
#define  __CKPACKAGE_H_

namespace ks
{

typedef unsigned int size_t;

class CMemBlock
{
public:
    CMemBlock(size_t length);
    virtual ~CMemBlock();

    virtual void    Init(){}
    virtual void    Release(){};
    void            SetLength(size_t length){m_iLength = length;}
    void            SetUsedSize(size_t size){m_iUsedSize = size;}
    void            SetFree(bool isFree){m_bIsFree = isFree;}
    size_t          GetLength(){return m_iLength;}
    size_t          GetUsedSize(){return m_iUsedSize;}
    void*           GetData(){return m_pData;}
    bool            IsFree(){return m_bIsFree;}

protected:
    size_t          m_iLength;
    size_t          m_iUsedSize;
    void*           m_pData;
    bool            m_bIsFree;
};

class CHeadPack : public CMemBlock
{
public:
    CHeadPack(size_t length);
    ~CHeadPack();

    void    Init();
    void    Release();
};

class CBodyPack : public CMemBlock
{
public:
    CBodyPack(size_t length);
    ~CBodyPack();

    void    Init(void* pData, CBodyPack* preBlock, CBodyPack* nextBlock);
    void    Release();
    void    SetPreBlock(CBodyPack* pBodyPack){m_pPreBlock = pBodyPack;}
    void    SetNextBlock(CBodyPack* pBodyPack){m_pNextBlock = pBodyPack;}
    CBodyPack*  GetPreBlock(){return m_pPreBlock;}
    CBodyPack*  GetNextBlock(){return m_pNextBlock;}

private:
    CBodyPack*  m_pPreBlock;
    CBodyPack*  m_pNextBlock;
};

class CPackage
{
public:
    CPackage(CHeadPack* pHeadPack, CBodyPack* pBodyPack);
    ~CPackage();
    CHeadPack*  GetHeadPack(){return m_pHeadPack;}
    CBodyPack*  GetBodyPack(){return m_pBodyPack;}

private:
    CHeadPack*  m_pHeadPack;
    CBodyPack*  m_pBodyPack;
};

}














#endif  //__CKPACKAGE_H_
