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
	void ClickEditName();
	bool ClickSaveName();

	void RemoveCharacter();
	void AddCharacter(sf::Event e);

	bool getInMulti();
	bool getIsMatchMaking();
	bool getIsMainMenuShowing();
	bool getIsMatchMakeShowing();
	bool getNeedsName();
	bool getIsChangingName();

	sf::Text getName();
	void setName( sf::Text name );

private:

	bool _isMenuShowing;
	bool _isMainMenuShowing;
	bool _needsName;
	bool _inMultiGame;
	bool _isMatchMaking;
	bool _isMatchMakeShowing;
	bool _isChangingName;

	GameWindow* _window;
};
