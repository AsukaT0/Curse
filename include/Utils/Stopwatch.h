//
// Created by asuka on 12.02.2024.
//

#ifndef MIRAAI_STOPWATCH_H
#define MIRAAI_STOPWATCH_H


#include <string>

class Stopwatch {
private:
    long long startTime;
public:
    void start();

    void stop(const std::string& label) const;
};


#endif //MIRAAI_STOPWATCH_H
