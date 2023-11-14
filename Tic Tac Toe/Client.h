#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

#define IP_ADRESS "142.251.168.101"
#define PORT "80"

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
	const char* _clientMessage = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
	char buffer[1024] = { 0 };


	addrinfo* _result = NULL;
	addrinfo _hints;

	int valread, clienfd, sockfd;

	DWORD _adressInfo = NULL;

};

