#pragma once

#include "pch/pch.h"
#include "MainMenu.h"
#include "NameMenu.h"
#include "Game/GameWindow.h"

class MenuManager : public MainMenu, NameMenu
{
public:
	MenuManager();
	virtual ~MenuManager();

	bool isMenuShowing();
	
	void HideMenu();

	void ShowMenu();
	bool CheckClickMulti();
	void CheckClickSingle();
	bool CheckClickMatchMake();

	bool getInMulti();

private:

	bool _isMenuShowing;
	bool _isMainMenuShowing;

	bool _inMultiGame;

	GameWindow* _window;
};
