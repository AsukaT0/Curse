//
// Created by asuka on 17.08.2023.
//

#ifndef DARLIGHT_SCLIENT_H
#define DARLIGHT_SCLIENT_H


#include <string>

class SClient {
public:
    void error(const std::string& message);
    [[maybe_unused]] std::string sendFunc(const std::string& host, int port, std::string message);
    [[maybe_unused]] std::string sendLocallyFunc(int port, const std::string& message);
};


#endif //DARLIGHT_SCLIENT_H
