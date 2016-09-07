/**
 * @file CKConfig.cpp
 * @author loyoen(com@gmail.com)
 * @date 2016/08/26 19:59:34
 * @brief 
 *  
 **/

#include "CKConfig.h"
#include "../log/KSLog.h"
#include <stdlib.h>

namespace ks
{

CConfig* CConfig::m_pConfigInstance = NULL;

CConfig::CConfig()
{
}
CConfig::~CConfig()
{
}

void CConfig::Init()
{
    bool bRet = ReadConfig("../config/ks.cfg");
    if(!bRet)
    {
        LOG_ERROR("read conf error");
    }
}

bool CConfig::IsSpace(char c)
{
    if(' ' == c || '\t' == c)
        return true;
    return false;
}

bool CConfig::IsCommentChar(char c)
{
    switch(c)
    {
    case COMMENT_CHAR:
        return true;
    default:
        return false;        
    }
}

void CConfig::Trim(std::string& str)
{
    if (str.empty()) {
        return;
    }
    int i, start_pos, end_pos;
    for (i = 0; i < str.size(); ++i) {
        if (!IsSpace(str[i])) {
            break;
        }
    }
    if (i == str.size()) { 
        str = "";
        return;
    }
    
    start_pos = i;
    
    for (i = str.size() - 1; i >= 0; --i) {
        if (!IsSpace(str[i])) {
            break;
        }
    }
    end_pos = i;
    
    str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool CConfig::AnalyseLine(const std::string & line, std::string & key, std::string & value)
{
    if (line.empty())
        return false;
    int start_pos = 0, end_pos = line.size() - 1, pos;
    if ((pos = line.find(COMMENT_CHAR)) != -1) {
        if (0 == pos) {  
            return false;
        }
        end_pos = pos - 1;
    }
    std::string new_line = line.substr(start_pos, start_pos + 1 - end_pos); 
    
    if ((pos = new_line.find('=')) == -1)
        return false;  
        
    key = new_line.substr(0, pos);
    value = new_line.substr(pos + 1, end_pos + 1- (pos + 1));
    
    Trim(key);
    if (key.empty()) {
        return false;
    }
    Trim(value);
    return true;
}

bool CConfig::ReadConfig(const std::string & filename)
{
    m_Dict.clear();
    std::ifstream infile(filename.c_str());
    if (!infile) {
        return false;
    }
    std::string line, key, value;
    while (std::getline(infile, line)) {
        if (AnalyseLine(line, key, value)) {
            m_Dict[key] = value;
        }
    }
    
    infile.close();
    return true;
}

size_t CConfig::GetThreadNum()
{
    return GetIntValue("ThreadNum", 10);
}

size_t CConfig::GetPackageNum()
{
    return GetIntValue("PackageNum", 1024);
}

size_t CConfig::GetPackageSize()
{
    return GetIntValue("PackageSize", 1024);
}


size_t CConfig::GetMaxSocketNum()
{
    return GetIntValue("MaxSocketNum", 1024);
}

std::string CConfig::GetValue(const std::string key)
{
    std::map<std::string, std::string>::iterator iter = m_Dict.find(key);
    if(iter != m_Dict.end())
        return iter->second.c_str();
    return "";
}

int CConfig::GetIntValue(const std::string key, int defaultValue)
{
    std::string value = GetValue(key);
    if("" == value)
        return defaultValue;
    return atoi(value.c_str());
}
}
