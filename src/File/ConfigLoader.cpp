#include "../../include/File/File.h"
#include "../../include/File/ConfigLoader.h"
#include "../../include/Utils/Utils.h"


#include <utility>
#include <string>
#include <algorithm>
std::vector<std::string> strings;
std::vector<std::string> arrays;
std::vector<std::string> configs;
bool checkOnluNum(std::string test){
    for(auto k:test){
        if(k != '0'&&k != '1'&&k != '2'&&k != '3'&&k != '4'&&k != '5'&&k != '6'&&k != '7'&&k != '8'&&k != '9'&&k != '-'&&k != '.')return false;}
    return true;}
bool checkOnluDig(std::string test){
    for(auto k:test){
        if(k != '0'&&k != '1'&&k != '2'&&k != '3'&&k != '4'&&k != '5'&&k != '6'&&k != '7'&&k != '8'&&k != '9'&&k != '-')return false;}
    return true;}



ConfigLoader::ConfigLoader(std::string data) {this->data = std::move(data);}
void ConfigLoader::loadFromPath(std::string path) {data = File(std::move(path)).read();}
void ConfigLoader::parseConfig(const std::string &_data) {
    std::string preData = restringer(_data);
    preData = preData.substr(1,preData.length()-2);
    preData = reconfigur(preData);
    preData = rearray(preData);
    preData = unstringer(preData);
    strings.clear();
    std::vector<std::string> dataParse = UtilClass::split(preData,",");
    for(std::string iData:dataParse){
        auto iDataSplit = UtilClass::split(iData,":");
        iDataSplit[0] = iDataSplit[0].substr(1,iDataSplit[0].length()-2);
        auto val = UtilClass::trim(iDataSplit[1]);
        if(val.find('`')!=std::string::npos){
            int numba = std::stoi(iDataSplit[1].substr(1,iDataSplit[1].length()-2));
            std::string dataConf = configs[numba];
            fullData[iDataSplit[0]] = ConfigLoader(configs[numba], true);
        }
        else if(val.find('|')!=std::string::npos){
            fullData[iDataSplit[0]] = unarray(std::stoi(iDataSplit[1].substr(1,iDataSplit[1].length()-2)));
        }
        else if(checkOnluDig(val)){fullData[iDataSplit[0]] = std::stoi(val);}
        else if(checkOnluNum(val)){fullData[iDataSplit[0]] = std::stof(val);}
        else if(val == "true"){fullData[iDataSplit[0]] = true;}
        else if(val == "false"){fullData[iDataSplit[0]] = false;}
        else{fullData[iDataSplit[0]] = iDataSplit[1].substr(1,iDataSplit[1].length()-2);}
    }
    configs.clear();
    arrays.clear();
}

void ConfigLoader::parseConfig() {
    parseConfig(data);}

VALUE ConfigLoader::get(const std::string& key) {
    VALUE _data = fullData[key];
    return _data;}


std::string ConfigLoader::getString(const std::string& key) {
    if (std::holds_alternative<std::string>(get(key))) {
        return std::get<std::string>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return "";}}

bool ConfigLoader::getBool(const std::string& key) {
    if (std::holds_alternative<bool>(get(key))) {
        return std::get<bool>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return false;}}

int ConfigLoader::getInt(const std::string& key) {
    if (std::holds_alternative<int>(get(key))) {
        return std::get<int>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return -1;}}

float ConfigLoader::getFloat(const std::string &key) {
    if (std::holds_alternative<float>(get(key))) {
        return std::get<float>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return -1;}}

ConfigLoader ConfigLoader::getSubConfig(const std::string& key) {
    if (std::holds_alternative<ConfigLoader>(get(key))) {
        return std::get<ConfigLoader>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return {};}}

std::vector<std::variant<int, float, bool, std::string, ConfigLoader>> ConfigLoader::getArray(const std::string& key) {
    if (std::holds_alternative<std::vector<std::variant<int, float, bool, std::string, ConfigLoader>>>(get(key))) {
        return std::move(std::get<std::vector<std::variant<int, float , bool, std::string, ConfigLoader>>>(get(key)));}
    else{std::cout << "Error:value not found: " << key << "\n";return {};}}



std::string ConfigLoader::getStringFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return "";}
    if (std::holds_alternative<std::string>(array[index])) {
        return std::get<std::string>(array[index]);}
    else{std::cout << "Error:value in array not found: " << index << "\n";return "";}}

bool ConfigLoader::getBoolFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return false;}
    if (std::holds_alternative<bool>(array[index])) {
        return std::get<bool>(array[index]);}
    else{std::cout << "Error:value in array not found: " << index << "\n";return false;}}

int ConfigLoader::getIntFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return -1;}
    if (std::holds_alternative<int>(array[index])) {
        return std::get<int>(array[index]);}
    else{std::cout << "Error:value in array not found: " << index << "\n";return -1;}}

float ConfigLoader::getFloatFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return -1;}
    if (std::holds_alternative<float>(getArray(key)[index])) {
        return std::get<float>(getArray(key)[index]);}
    else{
        std::cout << "Error:value in array not found: " << index << "\n";return -1;}}

ConfigLoader ConfigLoader::getSubConfigFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,float,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return {};}
    if (std::holds_alternative<ConfigLoader>(array[index])) {
        return std::get<ConfigLoader>(array[index]);}
    else{std::cout << "Error:value in array not found: " << index << "\n";return {};}}

std::string ConfigLoader::getData() {
    return data;
}

void ConfigLoader::finalize() {
    fullData.clear();
    std::map<std::string, VALUE>().swap(fullData);
    data.clear();
    data.shrink_to_fit();
}

std::map<std::string, VALUE > ConfigLoader::getFullData() {
    return fullData;}





std::string ConfigLoader::restringer(std::string _data) {
    std::string preData = std::move(_data);
    preData = UtilClass::trim(preData);
    preData = UtilClass::multiply_replace(preData,{{"\n",""},{"\t",""},{"\r",""}});
    reverse(preData.begin(), preData.end());
    while(preData.find('\"')!=std::string::npos){
        int first = preData.find_first_of('\"')+1;
        int last = preData.substr(first).find_first_of('\"');
        std::string tete = preData.substr(first-1,last+2);
        preData = UtilClass::replace(preData,tete,"_"+std::to_string(strings.size())+"_");
        strings.push_back(tete);
    }
    reverse(preData.begin(), preData.end());
    return preData;}

std::string ConfigLoader::reconfigur(std::string _data) {
    std::string preData = std::move(_data);
    while(preData.find('{')!=std::string::npos) {
        int Kount = 0;
        long long start = preData.find_first_of('{') + 1;
        long long end = 0;
        for (int ii1 = preData.find_first_of('{') + 1; ii1 < preData.length(); ii1++) {
            if (preData[ii1] == '{') { Kount += 1; }
            if (preData[ii1] == '}') {
                if (Kount == 0) {
                    end = ii1;
                    break;}
                else { Kount -= 1; }}}
        if (end != 0) {
            std::string tete = preData.substr(start - 1, end - start + 2);
            std::string reptete = preData.substr(start - 1, end - start + 2);
            tete = unstringer(tete);
            configs.push_back(tete);
            preData = UtilClass::replace(preData, reptete, "`" + std::to_string(configs.size() - 1) + "`");}}
    return preData;}


std::string ConfigLoader::unstringer(std::string _data) {
    std::string tete = _data;
    while (tete.find('_') != std::string::npos) {
        int first = tete.find_first_of('_');
        int last = tete.find_first_of('_', first + 1);
        std::string hehe = strings[std::stoi(tete.substr(first + 1, last - first - 1))];
        reverse(hehe.begin(), hehe.end());
        tete = UtilClass::replace(tete, tete.substr(first, last - first + 1),hehe);}
    return tete;}

std::string ConfigLoader::rearray(std::string _data) {
    std::string preData = std::move(_data);
    while(preData.find('[')!=std::string::npos) {
        int Kount = 0;
        long long start = preData.find_first_of('[') + 1;
        long long end = 0;
        for (int ii1 = preData.find_first_of('[') + 1; ii1 < preData.length(); ii1++) {
            if (preData[ii1] == '[') { Kount += 1; }
            if (preData[ii1] == ']') {
                if (Kount == 0) {
                    end = ii1;
                    break;}
                else { Kount -= 1; }}}
        if (end != 0) {
            std::string tete = preData.substr(start - 1, end - start + 2);
            std::string reptete = preData.substr(start - 1, end - start + 2);
            arrays.push_back(tete);
            preData = UtilClass::replace(preData, reptete, "|" + std::to_string(arrays.size() - 1) + "|");}}
    return preData;
}

std::vector<std::variant<int, float, bool, std::string, ConfigLoader>> ConfigLoader::unarray(int i) {
    std::vector<std::variant<int, float, bool, std::string, ConfigLoader>> returnable;
    std::vector<std::string> dataParse = UtilClass::split(arrays[i].substr(1,arrays[i].length()-2),",");
    for(std::string iData:dataParse){
        auto val = UtilClass::trim(iData);
        if(val.find('`')!=std::string::npos){
            ConfigLoader supConfig;
            supConfig.parseConfig(configs[std::stoi(val)]);
            returnable.emplace_back(supConfig);}
        else if(checkOnluDig(val)){returnable.emplace_back(std::stoi(val));}
        else if(checkOnluNum(val)){returnable.emplace_back(std::stof(val));}
        else if(val == "true"){returnable.emplace_back(true);}
        else if(val == "false"){returnable.emplace_back(false);}
        else{returnable.emplace_back(UtilClass::replace(val,"\"",""));}
    }
    return returnable;
}

ConfigLoader::ConfigLoader(std::string data, bool parsing) {
    this->data = std::move(data);
    if(parsing)parseConfig();
}