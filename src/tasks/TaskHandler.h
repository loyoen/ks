/**
 * @file TaskHandler.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 10:34:53
 * @brief 
 *  
 **/




#ifndef  __TASKHANDLER_H_
#define  __TASKHANDLER_H_

#include "../thread/Thread.h"

namespace ks
{

class CTaskHandler : public CThreadHandler
{
public:
    CTaskHandler();
    ~CTaskHandler();

    virtual int OnThreadProc();
};

}














#endif  //__TASKHANDLER_H_
