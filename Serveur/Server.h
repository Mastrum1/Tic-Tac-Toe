#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

#define PORT = 31350;
#define LOCALHOST = 127.0.0.1;

class Server
{
public:

	int Ping();

private:

	

};

