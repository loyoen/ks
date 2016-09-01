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

class CPackage
{
public:
    CPackage(size_t length);
    ~CPackage();

    void Init();
    void Release();
    void SetFree(bool bIsFree);
    size_t GetLength();
    size_t GetInitLength();
    void SetLength(size_t length);
    char* GetData();

private:
    size_t  m_iInitLength;
    size_t  m_iLength;
    bool    m_bIsFree;
    char*   m_pData;
};

}














#endif  //__CKPACKAGE_H_
