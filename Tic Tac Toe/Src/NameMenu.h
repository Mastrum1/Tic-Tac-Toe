#pragma once
class NameMenu
{
public:
	NameMenu();
	virtual ~NameMenu();

protected:

	sf::Font _arial;

	sf::Text _name;
	sf::FloatRect _editNameButton;

	bool _isWriting;
};

