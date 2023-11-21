#pragma once
class Client;
#include "Client/Client.h"
#include "Menus/MenuManager.h"
#include "Game/GameWindow.h"

class Game
{
public: 
	Game();
	~Game();

	void Start();
	void Update();
	void Reset();
	void Handle();
	void UserPlay();
	int CheckWin();
	void OnWin(int checkwin);
	void BotPlay();
	void Quit();

	static Game* GetInstance();

	Client* GetClient() { return _client; };

private:

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
	GameWindow* _window;
	MenuManager _menu;
};

