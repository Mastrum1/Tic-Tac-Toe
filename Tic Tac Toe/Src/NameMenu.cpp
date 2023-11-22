#include "pch/pch.h"
#include "NameMenu.h"

NameMenu::NameMenu()
{
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_name = sf::Text("Enter Name", _arial, 30);

	_editNameButton = _name.getGlobalBounds();
}

NameMenu::~NameMenu()
{
}
