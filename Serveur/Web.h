
#pragma once

#include <string>
#include "pch/pch.h"
class SimpleHttpServer {
public:
    SimpleHttpServer();
    ~SimpleHttpServer();

    void start();

private:
    int serverSocket;
    int clientSocket;

    struct sockaddr_in serverAddress;

    std::string readHtmlFile(const std::string& filename);
    void handleRequest();
};
