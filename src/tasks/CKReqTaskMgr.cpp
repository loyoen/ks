/**
 * @file CKReqTaskMgr.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/09/06 15:52:19
 * @brief 
 *  
 **/

#include "CKReqTaskMgr.h"

namespace ks
{

CReqTaskMgr* CReqTaskMgr::m_pTaskMgrInstance = NULL;

CReqTaskMgr::CReqTaskMgr()
{
}

CReqTaskMgr::~CReqTaskMgr()
{
}

void CReqTaskMgr::Init()
{
    CTaskMgr::Init();
}

void CReqTaskMgr::SetUserCallBackFunc(PtrFunc func)
{
    m_UserCallBackFunc = func;
}

PtrFunc CReqTaskMgr::GetUserCallBackFunc()
{
    return m_UserCallBackFunc;
}

}


















