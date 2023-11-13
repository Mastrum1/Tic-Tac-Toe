#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

#define IP_ADRESS "0.0.0.0"

class Client
{
public: 
	Client();
	~Client();

	int InitClient();
	int ClientSendMessage();
	void ClientRecieveMessage();

private:
	
	//Server Connection
	WSADATA _wsaData;
	sockaddr_in _serverAdress;
	const char* _clientMessage = NULL;
	char buffer[1024] = { 0 };


	addrinfo* _result = NULL;
	addrinfo _hints;

	int valread, clienfd, sockfd;

	DWORD _threadId = NULL;

};

