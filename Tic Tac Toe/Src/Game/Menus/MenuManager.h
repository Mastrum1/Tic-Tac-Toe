#pragma once
#include "pch/pch.h"
#include "MainMenu.h"
#include "Game/GameWindow.h"

class MenuManager : public MainMenu
{
public:
	MenuManager();
	~MenuManager();

	void ShowMainMenu();

private:

	GameWindow* _window;
};
