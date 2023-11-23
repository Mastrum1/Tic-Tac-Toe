#include "pch/pch.h"
#include "NameMenu.h"

NameMenu::NameMenu()
{
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_name = sf::Text("Enter Name", _arial, 30);
	_save = sf::Text("Save", _arial, 30);

	_editNameButton = _name.getGlobalBounds();
	_saveButton = _save.getGlobalBounds();

	_name.setPosition(sf::Vector2f(350, 350));
	_name.setFillColor(sf::Color::Black);

	_save.setPosition(sf::Vector2f(SCREEN_WIDTH/2, 600));
	_save.setFillColor(sf::Color::Black);
}

NameMenu::~NameMenu()
{
}
