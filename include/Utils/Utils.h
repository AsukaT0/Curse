#include <iostream>
#include <thread>
#include <pwd.h>
#include "../File/File.h"
#include <map>
#ifndef MYLIBRARY_UTILCLASS_H

#define MYLIBRARY_UTILCLASS_H

class UtilClass{
public:
    static std::vector<std::string> split(const std::string& str, const std::string& delimiters = ".");
    static std::vector<std::string> split(const std::string& str, char delimiters = '.');
    static std::string replace(std::string input,const std::string& old_string,const std::string& new_string);
    static std::string multiply_replace(std::string input,const std::vector<std::vector<std::string>>&replaceable);

    [[maybe_unused]] static std::string replace_once(std::string input,const std::string& old_string,const std::string& new_string);
    static std::string trim(std::string s);
    static std::vector<File> sortChilds(std::vector<File> arr);
    static std::vector<File> sortChildsNum(std::vector<File> arr);

    static void getDate(int &day,int &mouth,int &year);

    static std::string exec(const std::string& command);
    static std::string exec(const std::string& command, const File &writeInto);

    template<typename T>
    static std::vector<T> getKeys(std::map<T,T> map);
};
#endif //MYLIBRARY_UTILCLASS_H
