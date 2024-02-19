#ifndef MYLIBRARY_SCLIENT_H
#define MYLIBRARY_SCLIENT_H

#include <string>

class SClient {
public:
    void error(const std::string& message);
    [[maybe_unused]] std::string sendFunc(const std::string& host, int port, std::string message);
    [[maybe_unused]] std::string sendLocallyFunc(int port, const std::string& message);
};


#endif //MYLIBRARY_SCLIENT_H
