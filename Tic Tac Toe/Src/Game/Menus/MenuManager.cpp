#include "Game/Menus/MenuManager.h"

MenuManager::MenuManager()
{
	_window = GameWindow::getInstance();
	_isMenuShowing = true;
}

MenuManager::~MenuManager()
{
}

bool MenuManager::isMenuShowing()
{
	return _isMenuShowing;
}

void MenuManager::ShowMenu()
{
	_isMenuShowing = true;
}

void MenuManager::HideMenu()
{
	_isMenuShowing = false;
}

void MenuManager::ShowMainMenu()
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
		HideMenu();
		return true;
	}
	else return false;
}

bool MenuManager::CheckClickSingle()
{
	if (singlePlayerMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		HideMenu();
		return true;
	}
	else return false;
}
