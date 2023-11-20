#include "GameWindow.h"

GameWindow::GameWindow()
{
	_windowColor.r = 245;
	_windowColor.g = 152;
	_windowColor.b = 157;
}

GameWindow::~GameWindow()
{
}

GameWindow* GameWindow::getInstance()
{
	static GameWindow instance;
	return &instance;
}

void GameWindow::InitWindow()
{
	_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tic Tac Toe");
	_window.setFramerateLimit(30);
}

void GameWindow::Update()
{
	_window.clear(_windowColor);
}

sf::RenderWindow& GameWindow::GetWindow()
{
	return _window;
}

sf::Color& GameWindow::GetWindowColor()
{
	return _windowColor;
}
