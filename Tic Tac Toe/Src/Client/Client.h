#pragma once

#include "Messages/MessageGenerator.h"
#include "Client/Messages/WindowMessage.h"

#pragma comment (lib, "Ws2_32.lib")


#define IP_ADRESS "10.1.170.19"
#define PORT 31350
#define WM_SOCKET (WM_USER + 1)

class Client
{
public: 
	Client();
	~Client();

	static Client* GetInstance();

	void Connect();
	int InitClient();
	int ClientSendMessage(std::string message);
	int ClientReceiveMessage();
	int GetSocket() { return sockfd; };
	void CloseSocket() { closesocket(sockfd); WSACleanup(); };

	void setMessages(MessageGenerator* messages) { _messages = messages; }
	MessageGenerator* getMessages() { return _messages; }
	void close();
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
	WindowMessage _windowMessage;

};

