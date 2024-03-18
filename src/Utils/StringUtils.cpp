//
// Created by asuka on 16.03.2024.
//

#include <regex>
#include "../../include/Utils/StringUtils.h"
template<typename T>
std::basic_string<T> StringUtils::uppercase(const std::basic_string<T> &s) {
    std::basic_string<T> s2 = s;
    std::transform(s2.begin(), s2.end(), s2.begin(),
                   [](const T v){ return static_cast<T>(std::toupper(v)); });
    return s2;}

template<typename T>
std::basic_string<T> StringUtils::lowercase(const std::basic_string<T> &s) {
    std::basic_string<T> s2 = s;
    std::transform(s2.begin(), s2.end(), s2.begin(),
                   [](const T v){ return static_cast<T>(std::tolower(v)); });
    return s2;
}
std::vector<std::string> StringUtils::split(const std::string &str, const std::string &delimiters) {
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    std::vector<std::string> vs;
    while (std::string::npos != pos || std::string::npos != lastPos){
        vs.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);}
    return vs;}

std::vector<std::string> StringUtils::split(const std::string &str, char delimiters) {
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    std::vector<std::string> vs;
    while (std::string::npos != pos || std::string::npos != lastPos){
        vs.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);}
    return vs;}

std::string StringUtils::replace(std::string input, const std::string &old_string, const std::string &new_string) {
    unsigned long index;
    while((index = input.find(old_string)) != std::string::npos){
        input.replace(index, old_string.length(), new_string);}
    return input;}

[[maybe_unused]] std::string StringUtils::replace_once(std::string input, const std::string &old_string, const std::string &new_string) {
    if(unsigned long index; (index = input.find(old_string)) != std::string::npos){
        input.replace(index, old_string.length(), new_string);}
    return input;}

std::string StringUtils::trim(std::string s) {
    s.erase(s.begin(),std::ranges::find_if(s,[](const int ch) { return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(),[](const int ch) { return !std::isspace(ch); }).base(),s.end());
    return s;}

std::string StringUtils::multiply_replace(std::string input, const std::vector<std::vector<std::string>> &replaceable) {
    std::string test = std::move(input);
    for(auto i:replaceable){
        test = replace(test,i[0],i[1]);}
    return std::move(test);
}
std::vector<std::string> StringUtils::matcherText(std::string patern, std::string text) {
    std::vector<std::string> ret;
    std::string  test_text = text;
    std::regex pattern(patern);
    std::smatch match;
    while(std::regex_search(test_text, match, pattern)) {
        std::string result = match.str();
        test_text = replace(test_text,result,"");
        ret.push_back(result);}
    return std::move(ret);}