#include "Client.h"


Client::Client()
{
}	

Client::~Client()
{
}

int Client::InitClient()
{
	//Todo add id of player (X or O)
	//  
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

	_serverAdress.sin_family = AF_INET;
	_serverAdress.sin_port = htons(80);
	inet_pton(AF_INET, IP_ADRESS, &_serverAdress.sin_addr);

	_hints.ai_family = AF_INET;
	_hints.ai_socktype = SOCK_STREAM;
	_hints.ai_protocol = IPPROTO_TCP;
}

int Client::ClientSendMessage(std::string message)
{
	_adressInfo = getaddrinfo(NULL, NULL, &_hints, &_result);

	if (_adressInfo <= 0)
	{
		std::cout << "Failed to convert adress : " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Adress works" << std::endl;
	if (connect(sockfd, (sockaddr*)&_serverAdress, sizeof(_serverAdress)) == SOCKET_ERROR)
	{
		std::cout << "Connection error : " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Connection made" << std::endl;

	int sendError = send(sockfd,  message.c_str(), message.length(), 0);
	if (sendError == SOCKET_ERROR)
	{
		std::cout << "Failed to send message : " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Message sent" << std::endl;
	ClientRecieveMessage();

}

void Client::ClientRecieveMessage()
{
	valread = recv(sockfd, buffer, 1024 - 1, 0);
	std::cout << valread << std::endl;
	std::cout << "Message reçu : " << buffer << std::endl;

	//Close socket
	closesocket(sockfd);
	WSACleanup();
}

