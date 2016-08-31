/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file CKConfig.h
 * @author luoyongen(com@baidu.com)
 * @date 2016/08/25 10:42:19
 * @brief 
 *  
 **/




#ifndef  __CKCONFIG_H_
#define  __CKCONFIG_H_

#include <map>
#include <string>
#include <fstream>

namespace ks
{

#define COMMENT_CHAR '#'
typedef unsigned int size_t;

class CConfig
{
public:
    CConfig();
    ~CConfig();
    
    static CConfig* GetConfig()
    {
        if(m_pConfigInstance == NULL)
        {
            m_pConfigInstance = new CConfig();
        }
        return m_pConfigInstance;
    }

    void Init();

    size_t GetThreadNum();
    size_t GetPackageNum();
    size_t GetPackageSize();
    size_t GetMaxSocketNum();

    int GetIntValue(const std::string key, int defaultValue = 0);
    std::string GetValue(const std::string key);

private:
    bool IsSpace(char c);
    bool IsCommentChar(char c);
    void Trim(std::string& str);
    bool AnalyseLine(const std::string& line, std::string& key, std::string& value);
    bool ReadConfig(const std::string& filename); 

    std::map<std::string, std::string> m_Dict;

    static CConfig* m_pConfigInstance;
};

}
#endif  //__CKCONFIG_H_
