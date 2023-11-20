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

private:
	int _id;
	SOCKET _socket = NULL; //Null if not connected

};
