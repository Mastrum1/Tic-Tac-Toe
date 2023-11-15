#include "Server.h"

//____CLIENT 1 TURN______
//Client1 joue
//Read -> ID Joueur
//Read -> Coord
//Send -> Client2 = Client1's Coord
//Send -> Data = Grid + Client1's Coord

int Server::Init()
{
	
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "Erreur d'initialisation de WinSock : " << WSAGetLastError() << std::endl;
		return -1;
	}

	printf("WSA Initialized\n");

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(31350);

	printf("Socket creation pending...\n");

	if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	printf("Socket Created\n");

	socklen_t addrlen = sizeof(addr);

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	if (setsockopt(_server_fd, SOL_SOCKET,
		SO_REUSEADDR, &_opt,
		sizeof(_opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	printf("Set socket to port/address\n");

	printf("Binding pending...\n");

	if (bind(_server_fd, (struct sockaddr*)&addr,
		sizeof(addr))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	printf("Binded\n");

	Listener();
}

int Server::Listener()
{
	printf("Listening pending...\n");

	if (listen(_server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	printf("Listening\n");

retry:

	printf("Connexion validation pending...\n");

	if ((_new_socket = accept(_server_fd, (struct sockaddr*)&addr, &addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	printf("Connexion validated\n");

	_valread = recv(_new_socket, _buffer, 1024 - 1, 0);

	if (strcmp(_buffer, "Hugo") == 0)
	{
		printf("%s\n", _buffer);
		send(_new_socket, _hello, strlen(_hello), 0);
		printf("Sent\n");
	}

	if (strcmp(_buffer, "Jimmy") == 0)
	{
		printf("%s\n", _buffer);
		send(_new_socket, _hello2, strlen(_hello2), 0);
		printf("Sent\n");
	}

	if (strcmp(_buffer, "Exit") == 0)
	{
		closesocket(_new_socket);
		WSACleanup();
	}

	return 0;
}

