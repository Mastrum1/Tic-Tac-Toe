#pragma once

class MainMenu
{
public:
	MainMenu();
	virtual ~MainMenu();

protected:

	sf::Texture _backGroundT;
	sf::Sprite _backGroundS;

	sf::Font _arial;
	sf::Text titleMessage, playMessage, customGameMessage;
	sf::FloatRect playMessageButton, customGameButton;
};
