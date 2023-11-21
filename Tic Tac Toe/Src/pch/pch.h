#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <processthreadsapi.h>
#include <WinUser.h>
#include <string>
#include <Windows.h>
#include <fstream>

//for screen size
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// state of individual square
#define EMPTY 0
#define PLAYER1 1
#define PLAYER2 2

// Result of Game
#define PLAYER1_WIN 3
#define PLAYER2_WIN 4
#define DRAW 5

//for type of message
#define REQUEST_ID 1
#define NOTIFICATION_ID 2

// for command to server 
#define GET 1
#define SET 2


