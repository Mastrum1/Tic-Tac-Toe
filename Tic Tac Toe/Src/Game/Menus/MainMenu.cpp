#include "MainMenu.h"

MainMenu::MainMenu() 
{
	if (!_backGroundT.loadFromFile("Resources/Background.png")) std::cout << "load texture error.\n";
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_backGroundS.setTexture(_backGroundT);

	titleMessage = sf::Text("Welcome to Tic Tac Toe", _arial, 30);
	playMessage = sf::Text("Play", _arial, 30);
	customGameMessage = sf::Text("Custom Game", _arial, 30);

	playMessageButton = playMessage.getGlobalBounds();
	customGameButton = customGameMessage.getGlobalBounds();

	titleMessage.setPosition(sf::Vector2f(225, 200));
	titleMessage.setFillColor(sf::Color::Black);

	playMessage.setPosition(sf::Vector2f(350, 325));
	playMessage.setFillColor(sf::Color::Black);

	customGameMessage.setPosition(sf::Vector2f(285, 375));
	customGameMessage.setFillColor(sf::Color::Black);

}

MainMenu::~MainMenu()
{
}

