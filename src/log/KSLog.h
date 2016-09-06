/**
 * @file KSLog.h
 * @author loyoen(com@gmail.com)
 * @date 2016/09/06 11:20:05
 * @brief 
 *  
 **/




#ifndef  __KSLOG_H_
#define  __KSLOG_H_

#include <string>
#include <stdio.h>

namespace ks
{

static const int    MAX_STR_LINE    = 1024;
static const char*  DEBUG_PREFIX    = " DEBUG: ";
static const char*  INFO_PREFIX     = " INFO: ";
static const char*  WARN_PREFIX     = " WARN: ";
static const char*  ERROR_PREFIX    = " ERROR: ";
static const char*  FATAL_PREFIX    = " FATAL: ";

enum LogLevel
{
    LEVEL_ALL   = 0,
    LEVEL_DEBUG = 1,
    LEVEL_INFO  = 2,
    LEVEL_WARN  = 3,
    LEVEL_ERROR = 4,
    LEVEL_FATAL = 5,
    LEVEL_OFF   = 6,    
};

class CLogger
{
private:
    CLogger();
    static CLogger* m_pLoggerInstance;
    
    void GetCurrentTime(char* line);
    std::string GenerateLogName();

    std::string m_sLogFilePath;
    std::string m_sLogFileName;

    LogLevel m_level;
    FILE* m_pFileStream;

public:
    static CLogger* GetLogger()
    {
        if(NULL == m_pLoggerInstance)
        {
            m_pLoggerInstance = new CLogger();
        }
        return m_pLoggerInstance;
    }
    ~CLogger();
    void Init();

    void SetLevel(LogLevel level){m_level = level;}
    LogLevel GetLevel(){return m_level;}
    static void LogPrint(LogLevel level, const char* fmt, ...);
    void Trace(void* data, int iLen);    
};




}














#endif  //__KSLOG_H_
