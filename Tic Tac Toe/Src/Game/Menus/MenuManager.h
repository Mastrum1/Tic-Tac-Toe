#pragma once
#include "pch/pch.h"
#include "MainMenu.h"

class MenuManager : public MainMenu
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
