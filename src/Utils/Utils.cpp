//
// Created by asuka on 27.12.2023.
//
#include <algorithm>
#include <map>
#include <regex>
#include <utility>
#include "../../include/Utils/Utils.h"

std::vector<std::string> UtilClass::split(const std::string &str, const std::string &delimiters) {
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    std::vector<std::string> vs;
    while (std::string::npos != pos || std::string::npos != lastPos){
        vs.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);}
    return vs;}

std::vector<std::string> UtilClass::split(const std::string &str, char delimiters) {
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    std::vector<std::string> vs;
    while (std::string::npos != pos || std::string::npos != lastPos){
        vs.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);}
    return vs;}

std::string UtilClass::replace(std::string input, const std::string &old_string, const std::string &new_string) {
    unsigned long index;
    while((index = input.find(old_string)) != std::string::npos){
        input.replace(index, old_string.length(), new_string);}
    return input;}

[[maybe_unused]] std::string UtilClass::replace_once(std::string input, const std::string &old_string, const std::string &new_string) {
    if(unsigned long index; (index = input.find(old_string)) != std::string::npos){
        input.replace(index, old_string.length(), new_string);}
    return input;}

std::string UtilClass::trim(std::string s) {
    s.erase(s.begin(),std::ranges::find_if(s,[](const int ch) { return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(),[](const int ch) { return !std::isspace(ch); }).base(),s.end());
    return s;}

std::vector<File> UtilClass::sortChilds(std::vector<File> arr) {
    std::sort(arr.begin(),arr.end(),[](const File &p1, const File &p2) {
        const std::string s1 = p1.getName();
        const std::string s2 = p2.getName();
        return s1 < s2;});
    return arr;}

void UtilClass::getDate(int &day, int &mouth, int &year) {
    const time_t now = time(nullptr);
    const tm* ltm = localtime(&now);
    day = ltm->tm_mday;
    mouth = 1 + ltm->tm_mon;
    year = 1900 + ltm->tm_year;}

std::string UtilClass::exec(const std::string &command) {
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {return "pipe open failed!";}
    while (!feof(pipe)) {
        sleep(1);
        if (char buffer[128]; fgets(buffer, 128, pipe) != nullptr){
            std::cout << buffer << "\n";
            result += buffer;}}
    pclose(pipe);
    return result;}

std::string UtilClass::exec(const std::string &command, const File &writeInto) {
    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {return "pipe open failed!";}
    while (!feof(pipe)) {
        sleep(1);
        if (char buffer[2048]; (fgets(buffer, 2048, pipe)) != nullptr){
            writeInto.write(buffer,true);}}
    pclose(pipe);
    return result;}


std::vector<File> UtilClass::sortChildsNum(std::vector<File> arr) {
    std::sort(arr.begin(),arr.end(),[](const File &p1, const File &p2) {
        const std::string s1 = p1.getName();
        const std::string s2 = p2.getName();

        std::regex regex("part-(\\d+)");
        std::smatch match1, match2;
        std::regex_search(s1, match1, regex);
        std::regex_search(s2, match2, regex);

        std::cout << match1[1] << "\n";
        std::cout << match2[1] << "\n";

        int partNumber1 = std::stoi(match1[0]);
        int partNumber2 = std::stoi(match2[0]);

        return partNumber1 < partNumber2;});
    return arr;}

std::string UtilClass::multiply_replace(std::string input, const std::vector<std::vector<std::string>> &replaceable) {
    std::string test = std::move(input);
    for(auto i:replaceable){
        test = replace(test,i[0],i[1]);}
    return std::move(test);
}

std::vector<std::string> UtilClass::matcherText(std::string patern, std::string text) {
    std::vector<std::string> ret;
    std::string  test_text = text;
    std::regex pattern(patern);
    std::smatch match;
    while(std::regex_search(test_text, match, pattern)) {
        std::string result = match.str();
        test_text = replace(test_text,result,"");
        ret.push_back(result);}
    return std::move(ret);}

template<typename T,typename K>
std::vector<T> UtilClass::getKeys(std::map<T, K> map) {
    std::vector<T> key;
    for(typename std::map<T,K>::iterator it = map.begin(); it != map.end(); ++it) {
        key.push_back(it->first);}
    return key;}
