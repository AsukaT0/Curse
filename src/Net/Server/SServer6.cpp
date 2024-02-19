#include <sys/socket.h>
#include <netinet/in.h>
#include "../../../include/File/File.h"
#include "../../../include/Net/Server/SServer6.h"
#include "../../../include/Controllers/SqliteController.h"
#include "../../../include/Utils/SwitcherString.h"
#include "../../../include/Utils/Utils.h"

[[maybe_unused]] void SServer6::start(const int type, const int port,const std::function<void(const int server_fd)>& doing) {
    int server_fd;
    sockaddr_in6 address{};
    address.sin6_family = AF_INET6;
    address.sin6_addr = in6addr_any;
    address.sin6_port = htons(port);
    constexpr int opt = 1;
    if((server_fd = socket(AF_INET6, SOCK_STREAM, 0)) < 0||
       setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,sizeof(opt))||
       bind(server_fd, reinterpret_cast<sockaddr *>(&address),sizeof(address))< 0||
       listen(server_fd, 3) < 0){exit(EXIT_FAILURE);}
    int new_socket;
    switch (type) {
        case 0:
            if ((new_socket = accept(server_fd, nullptr, nullptr))
                < 0) {
                perror("accept");
                exit(EXIT_FAILURE);}
            doing(new_socket);
            break;
        case 1:
            while (true){
                if ((new_socket = accept(server_fd, nullptr, nullptr))
                    < 0) {
                    perror("accept");
                    exit(EXIT_FAILURE);}
                doing(new_socket);}
        default:
            if ((new_socket = accept(server_fd, nullptr, nullptr))
                < 0) {
                perror("accept");
                exit(EXIT_FAILURE);}
            doing(new_socket);
            break;}
    shutdown(server_fd, SHUT_RDWR);
}

