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
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			_boxAssigned[row][col] = EMPTY;
		}
	}

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

	if (connect(sockfd, (sockaddr*)&_serverAdress, sizeof(_serverAdress)))
	{
		std::cout << "Connection made" << std::endl;
	}

	Update();
	
}

void Client::Update()
{
	_windowMessage.UpdateWindowMessage();

}

int Client::ClientSendMessage(json message)
{
	std::string temp = message.dump();
	int sendError = send(sockfd, temp.c_str(), temp.length(), 0);
	if (sendError == SOCKET_ERROR)
	{
		std::cout << "Failed to send message : " << WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "Message sent" << std::endl;

}

void Client::ClientReceiveMessage()
{
	ZeroMemory(buffer, sizeof(buffer));
	int bytesReceived = recv(sockfd, buffer, sizeof(buffer), 0);
	buffer[bytesReceived] = 0;
	json data = json::parse(buffer);

	if (data["Type"] == NOTIFICATION_ID)
	{
		if (data["Cmd"] == CONNECTION_ID) // needs to be a request not notify
		{
			if (data["Msg"] == "Connection Pending")
			{
				setInstructions(CONNECTION_ID, REQUEST_ID);
				std::cout << _message << std::endl;
				std::string connectMessage = _message.dump();
				send(sockfd, connectMessage.c_str(), connectMessage.size(), 0);
				std::cout << _message << std::endl;
			}
			
		}
		if (data["Cmd"] == UPDATE_PASS)
		{
			UpdatePassport(data);
		}

		if (data["Cmd"] == SETTUP_PARTY)
		{
			//_partyID = 0;
			_gameID = data["ID"];
			_playerNum = data["Player"];
			if (_playerNum == 1)
			{
				clientCanPlay = true;

			}
			else clientCanPlay = false;
		}

		if (data["Cmd"] == PLAY)
		{
			clientCanPlay = true;
		}
	}	
	std::cout << "Message received : " << buffer << std::endl;
}

// check gamertag
bool Client::CheckPassport()
{
	ReadPassport();
	if (_passport["Name"] == NULL)
	{
		return false;
	}
	else return true;
}

void Client::ReadPassport()
{
	std::ifstream Passport("Passport.json");
	if (!Passport.is_open())
	{
		std::cout << "Failed to open passport" << std::endl;
		return;
	}
	else std::cout << "Passport opened" << std::endl;
	_passport = json::parse(Passport);
}

void Client::UpdatePassport(json msg)
{
	std::ofstream Passport("Passport.json");
	//pass.erase(1);
	json pass;
	
	pass["ID"] = msg["ID"];
	pass["Name"] = msg["Name"];

	Passport << pass;
}

void Client::setInstructions(int Cmd, int Type)
{
	_message.clear();
	_message["Cmd"] = Cmd;
	_message["Type"] = Type;
	if (Cmd == CONNECTION_ID || Cmd == MATCHMAKING_ID)
	{
		_message["ID"] = _passport["ID"];
		_message["Name"] = _passport["Name"];
	}
	if (Cmd == SET)
	{
		_message["ID"] = _gameID;
		_message["Player"] = _playerNum;
	}
}

void Client::setMessage(json message)
{
	_message = message;
}

json Client::getMessage()
{
	return _message;
}

json Client::getPassport()
{
	return _passport;
}

int Client::getID()
{
	return _gameID;
}

int Client::getPlayerNum()
{
	return _playerNum;
}

int Client::getBoxAssigned(int row, int col)
{
	return _boxAssigned[row][col];
}

void Client::setBoxAssigned(int row, int col, int state)
{
	_boxAssigned[row][col] = state;
}



