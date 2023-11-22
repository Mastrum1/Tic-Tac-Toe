#pragma once
#include "Client/Client.h"
#include "Menus/MenuManager.h"
#include "Game/GameWindow.h"

class Client;
class GameWindow;

class Game
{
public: 
	Game();
	~Game();

	static Game* GetInstance();

	void Start();
	static DWORD ClientThread(void* param);
	void Update();
	void Reset();
	void Handle();
	bool ChangeGameState();
	bool CreateGame();
	void UserPlay();
	int CheckWin();
	void OnWin(int checkwin);
	void BotPlay();
	void Quit();

	void CreateClientThread();
	
	Client* getClient();

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

