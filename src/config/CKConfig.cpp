/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKConfig.cpp
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/26 19:59:34
 * @brief 
 *  
 **/

#include "CKConfig.h"
#include <stdlib.h>

namespace ks
{

CConfig::CConfig()
{
}
CConfig::~CConfig()
{
}

void CConfig::Init()
{
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
        cout << "file open error" << endl;
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
    std::map<std::string, std::string>::iterator iter = m_Dict.find("ThreadNum");
    if(iter != m_Dict.end())
        return atoi(iter->second.c_str());
    return 10;
}
size_t CConfig::GetPackageNum()
{
    std::map<std::string, std::string>::iterator iter = m_Dict.find("PackageNum");
    if(iter != m_Dict.end())
        return atoi(iter->second.c_str());
    return 1024;
}

size_t CConfig::GetPackageSize()
{
    std::map<std::string, std::string>::iterator iter = m_Dict.find("PackageSize");
    if(iter != m_Dict.end())
        return atoi(iter->second.c_str());
    return 1024;
}


size_t CConfig::GetMaxSocketNum()
{
    std::map<std::string, std::string>::iterator iter = m_Dict.find("SocketNum");
    if(iter != m_Dict.end())
        return atoi(iter->second.c_str());
    return 1024;
}
