#include "MainMenu.h"

MainMenu::MainMenu() 
{
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";


	mainMessage = sf::Text("Welcome to Tic Tac Toe", _arial, 30);
	playMessage = sf::Text("Play", _arial, 30);

	messageButton = playMessage.getGlobalBounds();

	playMessage.setPosition(sf::Vector2f(375, 400));
	playMessage.setFillColor(sf::Color::Black);

	mainMessage.setPosition(sf::Vector2f(250, 200));
	mainMessage.setFillColor(sf::Color::Black);

	_menuShowing = true;
}

MainMenu::~MainMenu()
{
}

bool MainMenu::IsMenuShowing()
{
	return _menuShowing;
}

void MainMenu::HideMenu()
{
	_menuShowing = false;
}
