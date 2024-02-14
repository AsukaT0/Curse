//
// Created by asuka on 17.08.2023.
//

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../../../include/Net/Client/SClient.h"

void SClient::error(const std::string& message) {
    std::cerr << message << std::endl;
}
std::string SClient::sendFunc(const std::string& host, int port, std::string message) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        error("Error creating socket");
    }
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(host.c_str());

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    if ((connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)||
        (send(clientSocket, message.c_str(), message.size(), 0) < 0)||
        (recv(clientSocket, buffer, sizeof(buffer), 0) < 0)) {
            error("Error sclient");}
    close(clientSocket);
    return (std::string)buffer;
}

[[maybe_unused]] std::string SClient::sendLocallyFunc(int port, const std::string& message) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return "";}

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cout << "Connection Failed" << std::endl;
        return "";}

    if (send(client_socket, message.c_str(), message.size(), 0) < 0) {
        std::cout << "Send failed" << std::endl;
        return "";}

    char buffer[1024] = {0};
    std::string ireturnable;
    while(read(client_socket, buffer, 1024)>0){
        ireturnable += buffer;}

    close(client_socket);
    return ireturnable;
}
