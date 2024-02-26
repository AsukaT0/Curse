#ifndef MYLIBRARY_SSERVER6_H
#define MYLIBRARY_SSERVER6_H

#include <functional>

class SServer6{
    static File modifier;
    static int FHFJ;
    static long size;



public:
    [[maybe_unused]] static int INFINITY_SOCKET;
    [[maybe_unused]] static int ONCE_SOCKET;
        [[maybe_unused]] static void start(int type, int port, const std::function<void(const int server_fd)>& doing);
};

#endif