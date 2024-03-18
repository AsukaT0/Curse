#include <iostream>
#include <thread>
#include <pwd.h>
#include "../File/File.h"
#include <map>
#ifndef MYLIBRARY_UTILCLASS_H

#define MYLIBRARY_UTILCLASS_H

class UtilClass{
public:

    static std::vector<File> sortChilds(std::vector<File> arr);
    static std::vector<File> sortChildsNum(std::vector<File> arr);

    static void getDate(int &day,int &mouth,int &year);

    static std::string exec(const std::string& command);
    static std::string exec(const std::string& command, const File &writeInto);

    template<typename T,typename K>
    static std::vector<T> getKeys(std::map<T,K> map);
    static std::tm* getCurrentLocalTime();

};
#endif //MYLIBRARY_UTILCLASS_H
