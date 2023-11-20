#pragma once

#include "Client/Messages/MessageGenerator.h"
#include "Menus/MenuManager.h"
#include "Client/Messages/WindowMessage.h"
class Client;

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
	void Quit();

	static Game* GetInstance();
	WindowMessage* GetWindowMessage() { return &_windowMessage; }
	Client* GetClient() { return _client; };
	void setMessages(MessageGenerator messages) {_messages = messages;}

private:
		
	sf::RenderWindow _window;

	sf::Texture _grid;
	sf::Texture _xTex;
	sf::Texture _oTex;

	sf::Sprite _gridSprite;

	sf::Font _arial;
	sf::Text _gameMessage;

	sf::RectangleShape _gridPieces[3][3];
	int _boxAssinged[3][3];

	bool _PlayerWon = false;

	Client* _client;
	MessageGenerator _messages;
	MenuManager _menu;


	WindowMessage _windowMessage;
};

