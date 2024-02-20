#include "../../include/File/File.h"
#include "../../include/File/ConfigLoader.h"
#include "../../include/Utils/Utils.h"


#include <utility>
#include <algorithm>

ConfigLoader::ConfigLoader(std::string data) {this->data = std::move(data);}
void ConfigLoader::loadFromPath(std::string path) {data = File(std::move(path)).read();}
void ConfigLoader::saveToPath(std::string path) {File(std::move(path)).write(data);}

std::vector<std::string> ConfigLoader::preParseObj(const std::string &_data){
    std::string _data_ = _data;
    std::string subConfigData;
    if (_data_.substr(1, _data_.length() - 1).find('{') != std::string::npos){
        std::string insidePreData = _data_.substr(1, _data_.length() - 1);
        UL startObj = 0;
        UL endObj = 1;
        for(UL ii1 = 0;ii1 < insidePreData.length();ii1++){
            if(insidePreData[ii1] == '{'){
                startObj = ii1;}
            if(insidePreData[ii1] == '}'){
                endObj = ii1;
                break;}}
        if(insidePreData.find_first_of(',',endObj+1)<insidePreData.find_first_not_of(',',endObj+1)){
            endObj = insidePreData.find_first_of(',',endObj+1);}

        std::string insideSubData = insidePreData.substr(startObj,endObj-startObj+1);
        std::string labelSubData;
        prePrePreParse.push_back(insideSubData);
        _data_ = UtilClass::replace_once(_data_, insideSubData, "("+std::to_string((int)prePrePreParse.size()-1)+")");
        return {_data_};}
    return {_data_};}
std::vector<std::string> ConfigLoader::preParseArr(const std::string &_data){
    std::string _data_ = _data;
    std::string subConfigData;
    if (_data_.substr(1, _data_.length() - 1).find('[') != std::string::npos){
        std::string insidePreData = _data_.substr(1, _data_.length() - 1);
        UL startObj = 0;
        UL endObj = 1;
        for(UL ii1 = 0;ii1 < insidePreData.length();ii1++){
            if(insidePreData[ii1] == '['){
                startObj = ii1;}
            if(insidePreData[ii1] == ']'){
                endObj = ii1;
                break;}}
        if(insidePreData.find_first_of(',',endObj+1)<insidePreData.find_first_not_of(',',endObj+1)){
            endObj = insidePreData.find_first_of(',',endObj+1);}

        std::string insideSubData = insidePreData.substr(startObj,endObj-startObj);
        std::string labelSubData;
        prePrePreParse.push_back(insideSubData);
        _data_ = UtilClass::replace_once(_data_, insideSubData, "("+std::to_string((int)prePrePreParse.size()-1)+")");
        return {_data_};}
    return {_data_};}


void ConfigLoader::parseConfig(const std::string &_data) {
    std::string preData = UtilClass::trim(_data);
    preData = UtilClass::multiply_replace(preData.substr(0,preData.length()-1),{{"\t",""},{"\n",""}});
    while (preData.substr(1,preData.length()-2).find('{')!= std::string::npos){
        preData = preParseObj(preData)[0];
        if(preData.find(",}")!=std::string::npos){
            preData = UtilClass::multiply_replace(preData, {{",}", "}"}});}}
    while (preData.substr(1,preData.length()-2).find('[')!= std::string::npos){
        preData = preParseArr(preData)[0];
        if(preData.find(",]")!=std::string::npos){
            preData = UtilClass::multiply_replace(preData, {{",]", "]"}});}}
    preData = UtilClass::multiply_replace(preData,{{"[",""},{"]",""}});
    firstCicParse(preData);
}

void ConfigLoader::parseConfig() {parseConfig(data);}

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
    else{std::cout << "Error:value not found: " << key << "\n";return 0;}}

ConfigLoader ConfigLoader::getSubConfig(const std::string& key) {
    if (std::holds_alternative<ConfigLoader>(get(key))) {
        return std::get<ConfigLoader>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return {};}}

std::vector<std::variant<int, bool, std::string, ConfigLoader>> ConfigLoader::getArray(const std::string& key) {
    if (std::holds_alternative<std::vector<std::variant<int, bool, std::string, ConfigLoader>>>(get(key))) {
        return std::get<std::vector<std::variant<int, bool, std::string, ConfigLoader>>>(get(key));}
    else{std::cout << "Error:value not found: " << key << "\n";return {};}}

void ConfigLoader::firstCicParse(const std::string &_data) {
    std::string preData = UtilClass::multiply_replace(_data, {{")(", "),("},{"{",""},{"}",""}});
    std::vector<std::string> key_val = UtilClass::split(preData,",");
    for(auto k:key_val){
        auto key = UtilClass::replace(UtilClass::trim(UtilClass::split(k,":")[0]),"\"","");
        auto val = UtilClass::trim(UtilClass::split(k,":")[1]);
        if(val.find('(')!=std::string::npos){
            UL startRep = val.find('(')+1;
            UL endRep = val.find(')',startRep);
            int vecIndex = std::stoi(val.substr(startRep,endRep-startRep));
            val = UtilClass::replace(val, "("+std::to_string(vecIndex)+")",prePrePreParse[vecIndex]);}
        if(val.find('{')!=std::string::npos){
            while(val.find('(')!=std::string::npos){
                UL startRep = val.find('(')+1;
                UL endRep = val.find(')',startRep);
                int vecIndex = std::stoi(val.substr(startRep,endRep-startRep));
                val = UtilClass::replace(val, "("+std::to_string(vecIndex)+")",prePrePreParse[vecIndex]);}
            ConfigLoader subConfig(val);
            subConfig.parseConfig();
            fullData[key] = subConfig;}
        else if(val.find('[')!=std::string::npos){fullData[key] = parseArr(val);}
        else{
            if(std::all_of(val.begin(), val.end(), [](char c) {return std::isdigit(c);})){fullData[key] = std::stoi(val);}
            else if(val == "true"){fullData[key] = true;}
            else if(val == "false"){fullData[key] = false;}
            else{fullData[key] = UtilClass::replace(val,"\"","");}}}}

std::vector<std::variant<int, bool, std::string, ConfigLoader>> ConfigLoader::parseArr(const std::string &_data) {
    std::vector<std::variant<int, bool, std::string, ConfigLoader>> out;
    std::string preData = UtilClass::multiply_replace(_data,{{")(","),("}});
    preData = preData.substr(1,preData.find_last_of(']')-1);
    std::vector<std::string> valArr = UtilClass::split(preData,",");
    for(std::string val:valArr){
        if(val.find('(')!=std::string::npos){
            while(val.find('(')!=std::string::npos){
                UL startRep = val.find('(')+1;
                UL endRep = val.find(')',startRep);
                int vecIndex = std::stoi(val.substr(startRep,endRep-startRep));
                val = UtilClass::replace(val, "("+std::to_string(vecIndex)+")",prePrePreParse[vecIndex]);}
            ConfigLoader subConfig(val);
            subConfig.parseConfig();
            out.emplace_back(subConfig);}
        else if(std::all_of(val.begin(), val.end(), [](char c) {return std::isdigit(c);})){out.emplace_back(std::stoi(val));}
        else if(val == "true"){out.emplace_back(true);}
        else if(val == "false"){out.emplace_back(false);}
        else{out.emplace_back(UtilClass::replace(val,"\"",""));}}
    return out;}

std::string ConfigLoader::getStringFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return "";}
    if (std::holds_alternative<std::string>(array[index])) {
        return std::get<std::string>(array[index]);}
    else{std::cout << "Error:value in array not found: " << key << "\n";return "";}}

bool ConfigLoader::getBooFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return false;}
    if (std::holds_alternative<bool>(array[index])) {
        return std::get<bool>(array[index]);}
    else{std::cout << "Error:value in array not found: " << key << "\n";return false;}}

int ConfigLoader::getIntFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return -1;}
    if (std::holds_alternative<int>(array[index])) {
        return std::get<int>(array[index]);}
    else{std::cout << "Error:value in array not found: " << key << "\n";return -1;}}

ConfigLoader ConfigLoader::getSubConfigFromArr(const std::string &key, int index) {
    std::vector<std::variant<int,bool,std::string,ConfigLoader>> array = getArray(key);
    if(array.empty()){return {};}
    if (std::holds_alternative<ConfigLoader>(array[index])) {
        return std::get<ConfigLoader>(array[index]);}
    else{std::cout << "Error:value in array not found: " << key << "\n";return {};}}
