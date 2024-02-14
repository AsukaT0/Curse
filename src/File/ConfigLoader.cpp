//
// Created by asuka on 26.01.2024.
//


#include "../../include/File/Archiver.h"
#include "../../include/File/File.h"
#include "../../include/File/ConfigLoader.h"
#include "../../include/Utils/Utils.h"

#include <utility>

ConfigLoader::ConfigLoader(std::string path) {
    this->path = std::move(path);
}

void ConfigLoader::loadConfig() {
    std::string startData = File(path).read();
    std::string preData = UtilClass::trim(UtilClass::replace(UtilClass::replace(UtilClass::replace(UtilClass::replace(startData, "\t", ""), "}", ""), "{", ""), "\"", ""));
    preData = preData.substr(0,preData.size()-1);
    auto preDataList = UtilClass::split(preData, ",\n");
    for(const std::string& i:preDataList){
        std::vector<std::string> keyValue = UtilClass::split(i, ":");
        data.emplace(keyValue[0],keyValue[1]);}}

std::string ConfigLoader::get(const std::string& key) {
    return data[key];}