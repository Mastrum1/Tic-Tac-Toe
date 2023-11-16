#pragma once
#include "pch/pch.h"

class MenuManager
{
public:
	MenuManager();
	~MenuManager();

	bool IsMenuShowing();
	void HideMenu();

	void ShowMenu(sf::Text message);

private:

	bool _menuShowing;

	sf::FloatRect messageButton;
};
