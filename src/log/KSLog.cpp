/**
 * @file KSLog.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/09/06 14:22:10
 * @brief 
 *  
 **/

#include "KSLog.h"
#include "../config/CKConfig.h"
#include "../tasks/CKIOTaskMgr.h"
#include <stdarg.h>

namespace ks
{

CLogger* CLogger::m_pLoggerInstance = NULL;

CLogger::CLogger()
{
    m_level = LEVEL_ALL;
    m_pFileStream = NULL;
}
CLogger::~CLogger()
{
    if(m_pFileStream)
    {
        fclose(m_pFileStream);
    }
}

void CLogger::Init()
{
    CConfig* pConfig = CConfig::GetConfig();
    m_level = LogLevel(pConfig->GetIntValue("LogLevel"));
    m_sLogFilePath = pConfig->GetValue("LogFilePath");
    m_sLogFileName = GenerateLogName();
}

void CLogger::GetCurrentTime(char* line)
{
    time_t curTime;
    struct tm *pTimeInfo = NULL;
    time(&curTime);
    pTimeInfo = localtime(&curTime);
    sprintf(line, "%04d-%02d-%02d %02d:%02d:%02d", pTimeInfo->tm_year + 1990, pTimeInfo->tm_mon + 1, 
            pTimeInfo->tm_mday, pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
}

std::string CLogger::GenerateLogName()
{
    time_t curTime;
    struct tm *pTimeInfo = NULL;
    time(&curTime);
    pTimeInfo = localtime(&curTime);
    char strName[16] = {0};
    sprintf(strName, "%04d-%02d-%02d.log", pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday);
    return std::string(strName);
}

void CLogger::LogPrint(LogLevel level, const char* fmt, ...)
{
    CLogger* pLogger = CLogger::GetLogger();
    LogLevel curLevel = pLogger->GetLevel();
    if(level < curLevel)
    {
        return;
    }
    char* sLogLine = new char[MAX_STR_LINE];
    pLogger->GetCurrentTime(sLogLine);
    switch(curLevel)
    {
    case LEVEL_DEBUG:
        strcat(sLogLine, DEBUG_PREFIX);
        break;
    case LEVEL_INFO:
        strcat(sLogLine, INFO_PREFIX);
        break;
    case LEVEL_WARN:
        strcat(sLogLine, WARN_PREFIX);
        break;
    case LEVEL_ERROR:
        strcat(sLogLine, ERROR_PREFIX);
        break;
    case LEVEL_FATAL:
        strcat(sLogLine, FATAL_PREFIX);
        break;
    default:
        delete[] sLogLine;
        return;
    }
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    vsprintf(sLogLine + strlen(sLogLine), fmt, arg_ptr);
    va_end(arg_ptr);

    CIOTask* pTask = new CLogTask(sLogLine);
    CIOTaskMgr::GetTaskMgr()->AddTask(pTask);
}

void CLogger::Trace(void* data, int iLen)
{
    if(!m_pFileStream)
    {
        m_pFileStream = fopen((m_sLogFilePath + m_sLogFileName).c_str(), "a+");
        if(!m_pFileStream)
        {
            return;
        }
    }
    fprintf(m_pFileStream, "%s\n", (char*)data);
    fflush(m_pFileStream);
}

}



















