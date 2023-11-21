#pragma once

#include "pch/pch.h"
#include "MainMenu.h"
#include "Game/GameWindow.h"

class GameMenu;

class MenuManager : public MainMenu
{
public:
	MenuManager();
	~MenuManager();

	bool isMenuShowing();
	
	void ShowMenu();
	void HideMenu();

	void ShowMainMenu();
	bool CheckClickMulti();
	bool CheckClickSingle();

private:

	bool _isMenuShowing;

	GameWindow* _window;
};
