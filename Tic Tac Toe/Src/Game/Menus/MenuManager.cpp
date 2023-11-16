#include "Game/Menus/MenuManager.h"

MenuManager::MenuManager()
{
	_menuShowing = false;
}

MenuManager::~MenuManager()
{
}

bool MenuManager::IsMenuShowing()
{
	return _menuShowing;
}

void MenuManager::HideMenu()
{
	_menuShowing = false;
}

void MenuManager::ShowMenu(sf::Text message)
{
	messageButton = message.getGlobalBounds();

	message.setOrigin(messageButton.left + messageButton.width / 2.0f, messageButton.top + messageButton.height / 2.0f);
	message.setPosition(sf::Vector2f(400, 400));
	message.setFillColor(sf::Color::Black);

	_menuShowing = true;
}
