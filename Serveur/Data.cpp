#include "Data.h"

Data::Data()
{
}

Data::~Data()
{
}

int Data::getID() {
	return _id;
}
void Data::setID(int value) {
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

SOCKET Data::getSocketClient1()
{
	return _socketClient1;
}
SOCKET Data::getSocketClient2()
{
	return _socketClient2;
}

void Data::setSocketClient1(SOCKET value)
{
	_socketClient1 = value;
}
void Data::setSocketClient2(SOCKET value)
{
	_socketClient2 = value;
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





