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
	json getPassport();

	int getID();
	int getPlayerNum();
	int getBoxAssigned(int row, int col);
	void setBoxAssigned(int row, int col, int state);

	bool getClientCanPlay() { return clientCanPlay; };
	void setClientCanPlay(bool play) { clientCanPlay = play; };

	int getWinState() { return m_WinState; };
private:
	
	//Server Connection
	WSADATA _wsaData;
	sockaddr_in _serverAdress;
	const char* _clientMessage = NULL;  
	char buffer[1024] = { 0 };

	json _passport;
	json _message;

	int _gameID;
	int _playerNum;
	int m_WinState;

	int _boxAssigned[3][3];

	addrinfo* _result = NULL;
	addrinfo _hints;

	int valread, clienfd, sockfd;

	DWORD _adressInfo = NULL;
	WindowMessage _windowMessage;

	bool clientCanPlay = false;

};

