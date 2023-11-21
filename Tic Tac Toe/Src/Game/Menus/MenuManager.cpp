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
	_window->GetWindow().draw(playMessage);
	_window->GetWindow().draw(customGameMessage);
}

void MenuManager::CheckClickPlay()
{
	if (playMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		HideMenu();
	}
	else return;
}

void MenuManager::CheckClickCustom()
{
	if (customGameMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		HideMenu();
	}
	else return;
}
