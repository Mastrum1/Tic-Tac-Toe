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

	sf::Text _save;
	sf::FloatRect _saveButton;
	bool _isWriting;
};

