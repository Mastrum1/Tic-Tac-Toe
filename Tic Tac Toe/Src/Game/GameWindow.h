#pragma once
#include "pch/pch.h"

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	static GameWindow* getInstance();

	void InitWindow();
	void Update();

	sf::RenderWindow& GetWindow();

	sf::Color& GetWindowColor();

private:

	sf::RenderWindow _window;

	sf::Color _windowColor;
};

