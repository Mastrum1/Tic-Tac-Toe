#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>

#pragma comment (lib, "Ws2_32.lib")

#define PORT = 31350;
#define LOCALHOST = 127.0.0.1;

class Server
{
public:

	int Init();
	int Listener();

	sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);


private:

	int _server_fd, _new_socket;
	char _opt = 1;
	size_t _valread;
	char _buffer[1024] = { 0 };
	const char* _hello = "Oui";
	const char* _hello2 = "Non";
	bool _isListening = false;

};

