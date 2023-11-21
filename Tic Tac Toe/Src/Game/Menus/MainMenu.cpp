#include "pch/pch.h"
#include "MainMenu.h"


MainMenu::MainMenu() 
{
	if (!_backGroundT.loadFromFile("Resources/Background.png")) std::cout << "load texture error.\n";
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_backGroundS.setTexture(_backGroundT);

	titleMessage = sf::Text("Welcome to Tic Tac Toe", _arial, 30);
	multiPlayerMessage = sf::Text("Multiplayer", _arial, 30);
	singlePlayerMessage = sf::Text("SinglePlayer", _arial, 30);

	playMessageButton = multiPlayerMessage.getGlobalBounds();
	customGameButton = singlePlayerMessage.getGlobalBounds();

	titleMessage.setPosition(sf::Vector2f(225, 250));
	titleMessage.setFillColor(sf::Color::Black);

	multiPlayerMessage.setPosition(sf::Vector2f(325, 475));
	multiPlayerMessage.setFillColor(sf::Color::Black);

	singlePlayerMessage.setPosition(sf::Vector2f(315, 400));
	singlePlayerMessage.setFillColor(sf::Color::Black);

}

MainMenu::~MainMenu()
{
}

