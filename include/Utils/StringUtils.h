//
// Created by asuka on 16.03.2024.
//

#ifndef MYLIBRARY_STRINGUTILS_H
#define MYLIBRARY_STRINGUTILS_H


#include <string>
#include <algorithm>
#include <vector>

class StringUtils {
public:
    template <typename T>
    std::basic_string<T> lowercase(const std::basic_string<T>& s);

    template <typename T>
    std::basic_string<T> uppercase(const std::basic_string<T>& s);
    static std::vector<std::string> split(const std::string& str, const std::string& delimiters = ".");
    static std::vector<std::string> split(const std::string& str, char delimiters = '.');
    static std::string replace(std::string input,const std::string& old_string,const std::string& new_string);
    static std::string multiply_replace(std::string input,const std::vector<std::vector<std::string>>&replaceable);
    static std::vector<std::string> matcherText(std::string patern,std::string text);
    [[maybe_unused]] static std::string replace_once(std::string input,const std::string& old_string,const std::string& new_string);
    static std::string trim(std::string s);
};



#endif //MYLIBRARY_STRINGUTILS_H
