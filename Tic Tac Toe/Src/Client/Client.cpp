#include "pch/pch.h"

#include "Client.h"
#include "Messages/WindowMessage.h"


Client::Client()
{
}	

Client::~Client()
{
}

Client* Client::GetInstance()
{
	static Client instance;
	return &instance;
}

int Client::InitClient()
{
	//Todo add id of player (X or O)
	//  
	_windowMessage.WindowInit(GetModuleHandle(NULL));

	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
	{
		std::cout << "Erreur d'initialisation de WinSock : " << WSAGetLastError() << std::endl;
		return -1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (sockfd == INVALID_SOCKET)
	{
		std::cout << "Erreur de creation de socket : " << WSAGetLastError() << std::endl;
		return -1;
	}

	if (WSAAsyncSelect(sockfd, _windowMessage.GetHwnd(), WM_SOCKET, FD_READ | FD_CLOSE) == SOCKET_ERROR)
	{
		std::cout << "Failed to set async select : " << WSAGetLastError() << std::endl;
		return -1;
	}

	_serverAdress.sin_family = AF_INET;
	_serverAdress.sin_port = htons(PORT);
	inet_pton(AF_INET, IP_ADRESS, &_serverAdress.sin_addr);

	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_protocol = IPPROTO_TCP;

	_adressInfo = getaddrinfo(NULL, NULL, &_hints, &_result);

	if (_adressInfo <= 0)
	{
		std::cout << "Failed to convert adress : " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Adress works" << std::endl;
	connect(sockfd, (sockaddr*)&_serverAdress, sizeof(_serverAdress));
	std::cout << "Connection made" << std::endl;

	Update();
	
}

void Client::Update()
{
	_windowMessage.UpdateWindowMessage();

}

int Client::ClientSendMessage(std::string message)
{

	int sendError = send(sockfd,  message.c_str(), message.length(), 0);
	if (sendError == SOCKET_ERROR)
	{
		std::cout << "Failed to send message : " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Message sent" << std::endl;

}

int Client::ClientReceiveMessage()
{
	ZeroMemory(buffer, sizeof(buffer));
	int bytesReceived = recv(sockfd, buffer, sizeof(buffer), 0);
	if (buffer == "Connection Pending")
	{
		std::ifstream Passport("Resources/Passport.json");
		json yes = json::parse(Passport);
		std::string yess = yes.dump();
		send(sockfd, yess.c_str(), yess.size(), 0);
	}
	if (bytesReceived <= 0)
	{
		std::cout << "Connection closed" << std::endl;
		closesocket(sockfd);
		return 0;
	}
	std::cout << "Message received : " << buffer << std::endl;
}



