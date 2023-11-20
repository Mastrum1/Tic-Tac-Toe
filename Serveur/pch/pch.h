#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

#include "nlohmann/json.hpp"

// state of individual square
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

// Result of Game
#define PLAYER1_WIN 1
#define PLAYER2_WIN 2
#define DRAW 0

//for type of message
#define REQUEST_ID 1
#define NOTIFICATION_ID 2

// for command to server 
#define GET 1
#define SET 2