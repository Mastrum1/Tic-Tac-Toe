#pragma once

#include "Client/Messages/WindowMessage.h"
#include "nlohmann/json.hpp"

#pragma comment (lib, "Ws2_32.lib")

using json = nlohmann::json;




#define IP_ADRESS "10.1.170.19"
#define PORT 31350
#define WM_SOCKET (WM_USER + 1)

class Client
{
public: 
	Client();
	~Client();

	static Client* GetInstance();

	int InitClient();
	void Update();
	int ClientSendMessage(json message);
	void ClientReceiveMessage();
	int GetSocket() { return sockfd; };
	void CloseSocket() { closesocket(sockfd); WSACleanup(); };
	bool CheckPassport();
	void ReadPassport();
	void UpdatePassport(json pass);

	void setInstructions(int Cmd, int Type);

	void setMessage(json message);
	json getMessage();
private:
	
	//Server Connection
	WSADATA _wsaData;
	sockaddr_in _serverAdress;
	const char* _clientMessage = NULL;  //"GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n"
	char buffer[1024] = { 0 };

	json _passport;
	json _message;

	addrinfo* _result = NULL;
	addrinfo _hints;

	int valread, clienfd, sockfd;

	DWORD _adressInfo = NULL;
	WindowMessage _windowMessage;

};

