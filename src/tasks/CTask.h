/**
 * @file CTask.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 10:51:16
 * @brief 
 *  
 **/




#ifndef  __CTASK_H_
#define  __CTASK_H_

#include "../memory/CKPackage.h"
#include "../epoll/KSEpollCtlBase.h"
#include <vector>

namespace ks
{

class CTask
{
public:
    virtual void Run() = 0;
    virtual void CallBack() = 0;
};

class CEchoTask : public CTask, public CEpollCtlBase
{
public:
    CEchoTask(int epfd, int fd);
    ~CEchoTask();

    virtual void Run();
    virtual void CallBack();

    virtual void AddPackage(CPackage* pPackage);

    int GetFd(){return m_iFd;}
    CPackage* GetOutPackage(){return m_OutPackage;}

public:
    std::vector<CPackage*>  m_Packages;
    CPackage*               m_OutPackage; 
};

class CIOTask : public CTask
{
public:
    CIOTask();
    ~CIOTask();

    virtual void Run(){};
    virtual void CallBack(){};

protected:
    void* m_pData;
    size_t m_iLen;
};

class CLogTask : public CIOTask
{
public:
    CLogTask(char* line);
    ~CLogTask();

    virtual void Run();
    virtual void CallBack();
};

class CReadTask : public CTask, public CEpollCtlBase
{
public:
    CReadTask(int epfd,int fd);
    ~CReadTask();

    virtual void Run();
    virtual void CallBack();
};

class CWriteTask : public CTask, public CEpollCtlBase
{
public:
    CWriteTask(CEchoTask* pTask, int epfd, int fd);
    ~CWriteTask();

    virtual void Run();
    virtual void CallBack();

private:
    CEchoTask*  m_pEchoTask;
};

}















#endif  //__CTASK_H_
