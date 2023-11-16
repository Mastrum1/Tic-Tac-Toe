#pragma once
#include "pch/pch.h"
#include "Client/Client.h"
#include "Client/Messages/MessageGenerator.h"

class Game
{
public: 
	Game();
	~Game();

	void Start();
	void Reset();
	void Handle();
	void UserPlay();
	int CheckWin();
	void OnWin(int checkwin);
	void BotPlay();
	void OpenMenu();

	void setMessages(MessageGenerator messages) {_messages = messages;}
private:
		
	sf::RenderWindow _window;

	sf::Texture _grid;
	sf::Texture _xTex;
	sf::Texture _oTex;

	sf::Sprite _gridSprite;

	sf::Font _arial;
	sf::Text _gameMessage;
	sf::FloatRect _gameMenu;


	sf::RectangleShape _gridPieces[3][3];
	int _boxAssinged[3][3];

	bool _menuShowing = false;
	bool _PlayerWon = false;

	Client _client;
	MessageGenerator _messages;
};

