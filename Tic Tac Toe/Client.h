#pragma once
#include "pch.h"
#include "MessageGenerator.h"

#pragma comment (lib, "Ws2_32.lib")


#define IP_ADRESS "142.251.168.101"
#define PORT "80"

class Client
{
public: 
	Client();
	~Client();

	int InitClient();
	int ClientSendMessage(std::string message);
	void ClientRecieveMessage();
	void setMessages(MessageGenerator* messages) { _messages = messages; }

private:
	
	//Server Connection
	WSADATA _wsaData;
	sockaddr_in _serverAdress;
	const char* _clientMessage = NULL;  //"GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n"
	char buffer[1024] = { 0 };


	addrinfo* _result = NULL;
	addrinfo _hints;

	int valread, clienfd, sockfd;

	DWORD _adressInfo = NULL;
	MessageGenerator* _messages;

};

