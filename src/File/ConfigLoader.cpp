#include "../../include/File/File.h"
#include "../../include/File/ConfigLoader.h"
#include "../../include/Utils/Utils.h"


#include <utility>

ConfigLoader::ConfigLoader(std::string data) {this->data = std::move(data);}
void ConfigLoader::loadFromPath(std::string path) {data = File(std::move(path)).read();}
void ConfigLoader::saveToPath(std::string path) {File(std::move(path)).write(data);}

std::vector<std::string> ConfigLoader::parseObj(const std::string &_data){
    std::string _data_ = _data;
    std::string subConfigData;
    if (_data_.substr(1, _data_.length() - 1).find('{') != std::string::npos){
        std::string insidePreData = _data_.substr(1, _data_.length() - 1);
        UL startObj = 0;
        UL endObj = 1;
        UL startLabel = -1;
        UL endLabel = -1;
        bool isFindColon = false;
        for(UL ii1 = 0;ii1 < insidePreData.length();ii1++){
            if(insidePreData[ii1] == '{'){
                startObj = ii1;}
            if(insidePreData[ii1] == '}'){
                endObj = ii1;
                break;}}
        if(insidePreData.find_first_of(',',endObj+1)<insidePreData.find_first_not_of(',',endObj+1)){
            endObj = insidePreData.find_first_of(',',endObj+1);}
        for(UL ii1 = startObj;ii1 > 0;ii1--){
            if(startLabel == -1&&endLabel == -1&&!isFindColon&&insidePreData[ii1] == ':'){isFindColon = true;}
            if(isFindColon && startLabel == -1 && insidePreData[ii1] == '\"'){startLabel = ii1;continue;}
            else if(!isFindColon && startLabel == -1 && insidePreData[ii1] == '\"'){break;}
            if(startLabel != -1 && insidePreData[ii1] == '\"'){endLabel = ii1;break;}}


        std::string insideSubData = insidePreData.substr(startObj,endObj-startObj+1);
        std::string labelSubData;
        if(startLabel != -1&&endLabel != -1) {
            labelSubData = insidePreData.substr(endLabel, startLabel - endLabel + 1);
        }
        if(!labelSubData.empty()){
            subConfigData = insidePreData.substr(endLabel,endObj-endLabel+1);
            if(subConfigData.ends_with(','))subConfigData = subConfigData.substr(0,subConfigData.length()-1);
            ConfigLoader subConfig(insideSubData);
            subConfig.parseConfig();
            fullData[labelSubData.substr(1,labelSubData.length()-2)] = subConfig;
            _data_ = UtilClass::replace(_data_, insidePreData.substr(endLabel, endObj - endLabel + 1), "");
        }
        else{
            return {
                    _data_,  insideSubData};}}
    return {_data_};}

void ConfigLoader::parseConfig(const std::string &_data) {
    std::string preData = UtilClass::trim(_data);
    preData = UtilClass::multiply_replace(preData.substr(0,preData.length()-1),{{"\t",""},{"\n",""}});
    while (preData.substr(1,preData.length()-2).find('{')!= std::string::npos){
        preData = parseObj(preData)[0];
        if(preData.find(",}")!=std::string::npos){
            preData = UtilClass::multiply_replace(preData, {{",}", "}"}});}}
    preData = UtilClass::multiply_replace(preData,{{"{",""},{"}",""}});
    parseValues(preData);
}

void ConfigLoader::parseConfig() {parseConfig(data);}

VALUE ConfigLoader::get(const std::string& key) {
    VALUE _data = fullData[key];
    return _data;}

void ConfigLoader::parseValues(const std::string &_data) {
    std::vector<std::string> tetete = UtilClass::split(_data,",");
    for(const std::string& kkk:tetete) {
        std::string key = UtilClass::trim(UtilClass::split(kkk, ":")[0]), value = UtilClass::trim(UtilClass::split(kkk, ":")[1]);
        key = key.substr(1,key.length()-2);
        if (value.starts_with("\"") && value.ends_with("\"")) {
            fullData[key] = std::string(value.substr(1, value.length() - 2));
        }
        else if (value == "true") {
            fullData[key] = bool(true);}
        else if (value == "false") {
            fullData[key] = bool(false);}
        else {
            try {fullData[key] = int(std::stoi(value));}
            catch (std::string error) { std::cout << error; }}}}

std::string ConfigLoader::getString(const std::string& key) {
    if (std::holds_alternative<std::string>(get(key))) {
        return std::get<std::string>(get(key));
    } else{
        std::cout << "Error: not found: " << key << "\n";
        return "";}
}

bool ConfigLoader::getBool(const std::string& key) {
    if (std::holds_alternative<bool>(get(key))) {
        return std::get<bool>(get(key));
    } else{
        std::cout << "Error: not found: " << key << "\n";
        return false;}
}

int ConfigLoader::getInt(const std::string& key) {
    if (std::holds_alternative<int>(get(key))) {
        return std::get<int>(get(key));
    } else{
        std::cout << "Error: not found: " << key << "\n";
        return 0;}}

ConfigLoader ConfigLoader::getSubConfig(const std::string& key) {
    if (std::holds_alternative<ConfigLoader>(get(key))) {
        return std::get<ConfigLoader>(get(key));
    } else{
        std::cout << "Error: not found: " << key << "\n";
        return {};}
}

std::vector<std::variant<int, bool, std::string, ConfigLoader>> ConfigLoader::getArray(const std::string& key) {
    if (std::holds_alternative<std::vector<std::variant<int, bool, std::string, ConfigLoader>>>(get(key))) {
        return std::get<std::vector<std::variant<int, bool, std::string, ConfigLoader>>>(get(key));
    } else{
        std::cout << "Error: not found: " << key << "\n";
        return {};}}