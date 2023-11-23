#include "Data.h"

Data::Data()
{
}

Data::~Data()
{
}

int Data::getID() 
{
	return _id;
}
void Data::setID(int value) 
{
	_id = value;
}

bool Data::isPrivate()
{
	return _isPrivate;
}
void Data::setPrivate(bool value)
{
	_isPrivate = value;
}

Client* Data::getClient1()
{
	return Client1;
}
Client* Data::getClient2()
{
	return Client2;
}

void Data::setClient1(Client* value)
{
	Client1 = value;
}
void Data::setClient2(Client* value)
{
	Client2 = value;
}

int Data::getGridCoord(int x, int y)
{
	return _grid[x][y];
}
void Data::setGridCoord(int x, int y, int value)
{
	_grid[x][y] = value;
}

bool Data::isStarted()
{
	return _started;
}
void Data::setStarted(bool value)
{
	_started = value;
}

int Data::getEnded()
{
	return _ended;
}
void Data::setEnded(int value)
{
	_ended = value;
}





