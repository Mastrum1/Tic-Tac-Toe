#pragma once
#include "SFML/Graphics.hpp"
#include "Client.h"

class Game
{
public: 
	Game();
	~Game();

	void Start();
	void Reset();
	void Handle();
	int CheckWin();
	void OnWin(int checkwin);
	void BotPlay();
	void OpenMenu();

	void setClient(Client* client) {
		_client = client;
	}
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

	Client* _client;
};

