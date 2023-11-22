#include "Web.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>

SimpleHttpServer::SimpleHttpServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket\n";
        std::exit(EXIT_FAILURE);
    }

    // Set up server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Bind the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket\n";
        std::exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening for connections\n";
        std::exit(EXIT_FAILURE);
    }
}

SimpleHttpServer::~SimpleHttpServer() {

}

void SimpleHttpServer::start() {
    while (true) {
        // Accept a connection
        clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "Error accepting connection\n";
            continue;
        }

        // Handle the request
        handleRequest();
    }
}

std::string SimpleHttpServer::readHtmlFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file) {
        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    return "";
}

void SimpleHttpServer::handleRequest() {
    const int bufferSize = 4096;
    char buffer[bufferSize];
    std::memset(buffer, 0, sizeof(buffer));

    // Receive the HTTP request
    size_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead == -1) {
        std::cerr << "Error receiving data\n";
        return;
    }

    // Assume the request is a GET request
    std::string responseContent = readHtmlFile("index.html");
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: " + std::to_string(responseContent.size()) + "\r\n"
        "Content-Type: text/html\r\n"
        "\r\n" + responseContent;

    // Send the HTTP response
    size_t bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Error sending response\n";
    }
}