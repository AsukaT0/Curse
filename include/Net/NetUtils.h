//
// Created by asuka on 08.03.2024.
//

#ifndef MYLIBRARY_NETUTILS_H
#define MYLIBRARY_NETUTILS_H


#include <cstdio>
#include <string>

class NetUtils {
protected:
    static size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* output);
public:
    static std::string download_page(std::string url,std::string useropt);
    static std::string download_page(std::string url);
};


#endif //MYLIBRARY_NETUTILS_H
