#include "Game/Menus/MenuManager.h"

MenuManager::MenuManager()
{
	_window = GameWindow::getInstance();
	_isMenuShowing = true;
	_isMainMenuShowing = true;
	_inMultiGame = false;
	_isMatchMaking = false;
}

MenuManager::~MenuManager()
{
}

bool MenuManager::isMenuShowing()
{
	return _isMenuShowing;
}

void MenuManager::HideMenu()
{
	_isMenuShowing = false;
}

void MenuManager::ShowNameMenu()
{
	_needsName = true;
}

void MenuManager::ShowMenu()
{
	_window->GetWindow().draw(_backGroundS);
	if (_isMainMenuShowing)
	{
		_window->GetWindow().draw(titleMessage);
		_window->GetWindow().draw(multiPlayerMessage);
		_window->GetWindow().draw(singlePlayerMessage);
	}
	else
	{
		_window->GetWindow().draw(matchMake);
	}
	
}

bool MenuManager::ClickMulti()
{
	if (multiPlayerMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		_inMultiGame = true;
		_isMainMenuShowing = false;

		_window->GetWindow().clear();
		return true;
	}
	else return false;
}

bool MenuManager::ClickSingle() 
{
	if (singlePlayerMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		HideMenu();
		return true;
	}
}

bool MenuManager::ClickMatchMake()
{
	if (matchMake.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		// add waiting screen menu
		_isMatchMaking = true;
		HideMenu();
		_window->GetWindow().clear();
		return true;
	}
	else return false;
}

bool MenuManager::getInMulti()
{
	return _inMultiGame;
}

bool MenuManager::getIsMatchMaking()
{
	return _isMatchMaking;
}
