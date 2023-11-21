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
	sf::Text titleMessage, multiPlayerMessage, singlePlayerMessage;
	sf::FloatRect playMessageButton, customGameButton;
};
