#pragma once
#include "pch/pch.h"

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	sf::RenderWindow& GetWindow() {
		return _window;
	}

private:

	sf::RenderWindow _window;
};

