//
// Created by asuka on 26.01.2024.
//

#ifndef MIRAAI_CONFIGLOADER_H
#define MIRAAI_CONFIGLOADER_H


#include <string>
#include <map>

class ConfigLoader {
private:
    std::map<std::string,std::string> data;
    std::string path;
public:
    explicit ConfigLoader(std::string path);
    void loadConfig();
    std::string get(const std::string& key);
};


#endif //MIRAAI_CONFIGLOADER_H
