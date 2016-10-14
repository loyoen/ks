/**
 * @file define.h
 * @author loyoen(com@gmail.com)
 * @date 2016/10/12 15:17:20
 * @brief 
 *  
 **/




#ifndef  __DEFINE_H_
#define  __DEFINE_H_

namespace ks
{

#define SINGLETON(_class) private:\
                            static C##_class *m_p##_class##Instance;\
                            C##_class();\
                          public:\
                            static C##_class *Get##_class()\
                            {\
                                if(NULL == m_p##_class##Instance)\
                                    m_p##_class##Instance = new C##_class();\
                                return m_p##_class##Instance;\
                            }\
                            ~C##_class();

#define INITIALIZE(_class) C##_class* C##_class::m_p##_class##Instance = NULL;

typedef void* (*PtrFuncTwo)(void*, void*);
typedef void* (*PtrFunc)(void*);





}
#endif  //__DEFINE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
