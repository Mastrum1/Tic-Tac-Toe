#include "GameWindow.h"

GameWindow::GameWindow()
{
	_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tic Tac Toe");
	_window.setFramerateLimit(30);
}

GameWindow::~GameWindow()
{
}
