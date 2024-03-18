//
// Created by asuka on 27.12.2023.
//
#include <algorithm>
#include <map>
#include <regex>
#include <utility>
#include "../../include/Utils/Utils.h"


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
//            std::cout << buffer << "\n";
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





std::tm *UtilClass::getCurrentLocalTime() {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* currentTimeTM = std::localtime(&currentTimeT);
    return currentTimeTM;}

template<typename T,typename K>
std::vector<T> UtilClass::getKeys(std::map<T, K> map) {
    std::vector<T> key;
    for(typename std::map<T,K>::iterator it = map.begin(); it != map.end(); ++it) {
        key.push_back(it->first);}
    return key;}
