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
