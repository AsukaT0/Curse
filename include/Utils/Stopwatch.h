#ifndef MYLIBRARY_STOPWATCH_H
#define MYLIBRARY_STOPWATCH_H


#include <string>

class Stopwatch {
private:
    long long startTime;
public:
    void start();

    void stop(const std::string& label) const;
};


#endif //MYLIBRARY_STOPWATCH_H
