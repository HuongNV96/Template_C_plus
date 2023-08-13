#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <vector>

static inline const std::string IP_V4_REGEX(R"((?:[0-9]{1,3}\.){3}[0-9]{1,3})");
static inline const std::string IP_V6_REGEX(R"((?:[0-9a-zA-Z]{4}\:){7}[0-9a-zA-Z]{4})");
static inline const std::string VN_PHONE_REGEX(R"(0|\+84\d+)");
static inline const std::string EMAIL_REGEX(R"(\w+@\w+\.{1,10}\w+)");

inline std::vector<std::string> regexScan(std::string regexString, std::string input) {
    std::vector<std::string> ret;
    std::regex pattern(regexString);
    std::smatch sm;
    
    std::string tmp = input;
    while(regex_search(tmp,sm,pattern))
    {
        regex_search(tmp,sm,pattern);
        for (unsigned i=0; i<sm.size(); ++i) {
            ret.push_back(sm[i])
        }
        tmp = sm.suffix();
    }
    return ret;
}