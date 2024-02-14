//
// Created by asuka on 12.02.2024.
//

#include "../../include/Utils/Stopwatch.h"
#include <chrono>
#include <ctime>
#include <iostream>

void Stopwatch::start() {
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Stopwatch::stop(const std::string &label) const {
    long double endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();;
    std::time_t currentTimeInSeconds = endTime / 1000;
    std::tm* timeInfo = std::localtime(&currentTimeInSeconds);

    std::cout << label << ": "
        << ((timeInfo->tm_hour<10)?"0":"") << std::to_string(timeInfo->tm_hour) <<":"
        << ((timeInfo->tm_min<10)?"0":"") << std::to_string(timeInfo->tm_min) << ":"
        << ((timeInfo->tm_sec<10)?"0":"") << std::to_string(timeInfo->tm_sec) << "    "
        << ((timeInfo->tm_mday<10)?"0":"") << std::to_string(timeInfo->tm_mday) << "."
        << ((timeInfo->tm_mon+1<10)?"0":"") << std::to_string(timeInfo->tm_mon+1) << "."
        << std::to_string(timeInfo->tm_year+1900) << "\n"
        << "\tВремя прошло:" << endTime-startTime << "ms"  <<"\n";
}
