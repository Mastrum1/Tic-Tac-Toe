#pragma once

#include "pch/pch.h"

class MainMenu
{
public:
	MainMenu();
	virtual ~MainMenu();

	bool IsMenuShowing();
	void HideMenu();

	sf::Text getPlayMessage() {
		return playMessage;
	}

	sf::Text getMainMessage() {
		return mainMessage;
	}

	sf::FloatRect getMessageButton() {
		return messageButton;
	}
protected:

	bool _menuShowing;

	sf::Font _arial;
	sf::Text playMessage;
	sf::Text mainMessage;
	sf::FloatRect messageButton;

};
