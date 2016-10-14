/**
 * @file CKConfig.h
 * @author loyoen(com@gmail.com)
 * @date 2016/08/25 10:42:19
 * @brief 
 *  
 **/




#ifndef  __CKCONFIG_H_
#define  __CKCONFIG_H_

#include "../include/define.h"
#include <map>
#include <string>
#include <fstream>

namespace ks
{

#define COMMENT_CHAR '#'
typedef unsigned int size_t;

class CConfig
{
    SINGLETON(Config)

public:
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
};

}
#endif  //__CKCONFIG_H_
