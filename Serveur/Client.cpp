#include "Client.h"

Client::Client()
{
}

Client::~Client()
{
}

int Client::getID()
{
	return _id;
}
void Client::setID(int value)
{
	_id = value;
}

SOCKET Client::getSocket()
{
	return _socket;
}
void Client::setSocket(SOCKET value)
{
	_socket = value;
}
void Client::closeSocket()
{
	_socket = NULL;
}

std::string Client::getName()
{
	return _name;
}
void Client::setName(std::string value)
{
	_name = value;
}

bool Client::isInGame()
{
	return _inGame;
}

void Client::setInGame(bool value)
{
	_inGame = value;
}

int Client::getGameID()
{
	return _gameID;
}

void Client::setGameID(int value)
{
	_gameID = value;
}

void Client::resetGameID()
{
	_gameID = NULL;
}

int Client::getRoundCount()
{
	return _roundCount;
}
void Client::setRoundCount(int value)
{
	_roundCount = value;
}
void Client::addRoundCount()
{
	_roundCount++;
}

int Client::getRoundWin()
{
	return _roundWin;
}
void Client::setRoundWin(int value)
{
	_roundWin = value;
}
void Client::addRoundWin()
{
	_roundWin++;
}

int Client::getRoundLose()
{
	return _roundLose;
}
void Client::setRoundLose(int value)
{
	_roundLose = value;
}
void Client::addRoundLose()
{
	_roundLose++;
}