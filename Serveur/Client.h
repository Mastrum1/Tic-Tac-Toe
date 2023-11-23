#pragma once
#include "pch/pch.h"

class Client
{
public:
	Client();
	~Client();

	int getID();
	void setID(int value);

	SOCKET getSocket();
	void setSocket(SOCKET value);
	void closeSocket();

	std::string getName();
	void setName(std::string value);

	bool isInGame();
	void setInGame(bool value);

	int getRoundCount();
	void setRoundCount(int value);
	void addRoundCount();

	int getRoundWin();
	void setRoundWin(int value);
	void addRoundWin();

	int getRoundLose();
	void setRoundLose(int value);
	void addRoundLose();

private:
	int _id;
	SOCKET _socket = NULL; //Null if not connected
	std::string _name;

	int _roundCount = 0;
	int _roundWin = 0;
	int _roundLose = 0;
};
