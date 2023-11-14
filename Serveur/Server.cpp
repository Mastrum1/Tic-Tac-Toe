#include "Server.h"

int Server::Ping()
{

	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sockfd == INVALID_SOCKET)
	{
		std::cout << "Erreur de creation de socket : " << WSAGetLastError() << std::endl;
		return -1;
	}

	char buffer[4096] = { 0 };
	int readValue;
	readValue = recv(sockfd, buffer, 1024 - 1, 0);


	std::cout << readValue << std::endl;
	std::cout << "Message reçu : " << buffer << std::endl;
}
//____CLIENT 1 TURN______
//Client1 joue
//Read -> ID Joueur
//Read -> Coord
//Send -> Client2 = Client1's Coord
//Send -> Data = Grid + Client1's Coord