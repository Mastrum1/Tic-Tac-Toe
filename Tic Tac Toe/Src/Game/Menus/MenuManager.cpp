#include "Game/Menus/MenuManager.h"

MenuManager::MenuManager()
{
	_window = GameWindow::getInstance();
	_isMenuShowing = true;
	_isMainMenuShowing = true;
	_inMultiGame = false;
	_isMatchMaking = false;
	_isMatchMakeShowing = false;
	_needsName = false;
	_isChangingName = true;
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
	_isMatchMakeShowing = false;
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
	else if (_isMatchMakeShowing)
	{
		_window->GetWindow().draw(matchMake);
	}
	else if (_needsName)
	{
		_window->GetWindow().draw(_name);
		_window->GetWindow().draw(_save);
	}
}

bool MenuManager::ClickMulti()
{
	if (multiPlayerMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		_inMultiGame = true;
		_isMainMenuShowing = false;
		_isMatchMakeShowing = true;
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
		_isMatchMakeShowing = false;
		HideMenu();
		_window->GetWindow().clear();
		return true;
	}
	else return false;
}

void MenuManager::ClickEditName()
{
	if (_name.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		_isChangingName = true;
	}
}

bool MenuManager::ClickSaveName()
{
	if (_save.getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
	{
		// add waiting screen menu
		_needsName = false;
		_isChangingName = false;
		_isMainMenuShowing = true;
		_window->GetWindow().clear();
		return true;
	}
	else return false;
}

void MenuManager::RemoveCharacter()
{
	_name.setString(_name.getString().substring(0, _name.getString().getSize() - 1));
}

void MenuManager::AddCharacter(sf::Event e)
{
	int val = 97 + e.text.unicode;
	if (val >= 97 && val < 123)
	{
		std::string test = _name.getString();
		test += (char)val;
		_name.setString(test);
	}
}

bool MenuManager::getInMulti()
{
	return _inMultiGame;
}

bool MenuManager::getIsMatchMaking()
{
	return _isMatchMaking;
}

bool MenuManager::getIsMainMenuShowing()
{
	return _isMainMenuShowing;
}

bool MenuManager::getIsMatchMakeShowing()
{
	return _isMatchMakeShowing;
}

bool MenuManager::getNeedsName()
{
	return _needsName;
}

bool MenuManager::getIsChangingName()
{
	return _isChangingName;
}

sf::Text MenuManager::getName()
{
	return _name;
}

void MenuManager::setName(sf::Text name)
{
	_name = name;
}
