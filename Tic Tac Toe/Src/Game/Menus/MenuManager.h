#pragma once

#include "pch/pch.h"
#include "MainMenu.h"
#include "NameMenu.h"
#include "Game/GameWindow.h"

class GameWindow;

class MenuManager : public MainMenu, NameMenu
{
public:
	MenuManager();
	virtual ~MenuManager();

	bool isMenuShowing();
	
	void ShowMenu();
	void HideMenu();
	void ShowNameMenu();

	bool ClickMulti();
	bool ClickSingle();

	bool ClickMatchMake();

	bool getInMulti();
	bool getIsMatchMaking();
	bool getIsMainMenuShowing();
	bool getIsMatchMakeShowing();

private:

	bool _isMenuShowing;
	bool _isMainMenuShowing;
	bool _needsName;
	bool _inMultiGame;
	bool _isMatchMaking;
	bool _isMatchMakeShowing;

	GameWindow* _window;
};
