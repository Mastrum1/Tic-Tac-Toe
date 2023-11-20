#pragma once
#include "pch/pch.h"

class Data
{
public:
	Data();
	~Data();

	int getID();
	void setID(int value);

	bool isPrivate();
	void setPrivate(bool value);

	SOCKET getSocketClient1();
	SOCKET getSocketClient2();

	void setSocketClient1(SOCKET value);
	void setSocketClient2(SOCKET value);

	int getGridCoord(int x, int y);
	void setGridCoord(int x, int y, int value);

	bool isStarted();
	void setStarted(bool value);

	int getEnded();
	void setEnded(int value);

private:
	int _id;
	bool _isPrivate; // false = public match, true = private match

	SOCKET _socketClient1;
	SOCKET _socketClient2;
	
	int _grid[3][3] = { 0 };

	bool _started = false;

	int _ended = -1; // -1 = not ended, 0 = draw, 1 = player 1 win, 2 = player 2 win
	
};

