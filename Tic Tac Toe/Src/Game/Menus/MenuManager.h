#pragma once

#include "pch/pch.h"
#include "MainMenu.h"
#include "Game/GameWindow.h"

class MenuManager : public MainMenu
{
public:
	MenuManager();
	~MenuManager();

	bool isMenuShowing();
	
	void HideMenu();

	void ShowMenu();
	bool CheckClickMulti();
	void CheckClickSingle();

	bool getInMulti();

private:

	bool _isMenuShowing;

	bool _inMultiGame;

	GameWindow* _window;
};
