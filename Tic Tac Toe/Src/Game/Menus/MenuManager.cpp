#include "Game/Menus/MenuManager.h"

MenuManager::MenuManager()
{
	_window = GameWindow::getInstance();
	_isMenuShowing = true;
	_inMultiGame = false;
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

void MenuManager::ShowMenu()
{
	_window->GetWindow().draw(_backGroundS);
	_window->GetWindow().draw(titleMessage);
	_window->GetWindow().draw(multiPlayerMessage);
	_window->GetWindow().draw(singlePlayerMessage);
}

bool MenuManager::CheckClickMulti()
{
	if (multiPlayerMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		_inMultiGame = true;
		HideMenu();
		return true;
	}
	else return false;
}

void MenuManager::CheckClickSingle()
{
	if (singlePlayerMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		HideMenu();
	}
}

bool MenuManager::getInMulti()
{
	return _inMultiGame;
}
