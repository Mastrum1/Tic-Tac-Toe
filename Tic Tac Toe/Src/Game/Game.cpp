#include "pch/pch.h"
#include "Game.h"
#include "Client/Client.h"


Game::Game()
{
	_window = GameWindow::getInstance();

	if (!_grid.loadFromFile("Resources/Board.png")) std::cout << "load texture error.\n";
	if (!_xTex.loadFromFile("Resources/X_Piece.png")) std::cout << "load texture error.\n";
	if (!_oTex.loadFromFile("Resources/O_Piece.png")) std::cout << "load texture error.\n";
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_gridSprite.setTexture(_grid);
	//_gridSprite.setPosition(50, 50);
	//_gridSprite.setScale(sf::Vector2f(3.5, 3.5));
	_client = nullptr;
}

Game::~Game()
{
	assert(_client == nullptr);
	Quit();
}

void Game::Start()
{
	HANDLE Thread = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)ClientThread, 0, 0, NULL);

	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			_gridPieces[row][col].setSize(sf::Vector2f(120, 120));
			_gridPieces[row][col].setPosition(sf::Vector2f(190 + col * 150, 190 + row * 150));
			_gridPieces[row][col].setFillColor(_window->GetWindowColor());
			_boxAssinged[row][col] = EMPTY;
		}
	}
}

DWORD Game::ClientThread(void* param)
{
	Client* _client = Client::GetInstance();
	_client->InitClient();
	return 0;
}

void Game::Update()
{
	while (_window->GetWindow().isOpen()) 
	{
		Handle();

		_window->Update();

		if (_menu.isMenuShowing())
		{
			_menu.ShowMainMenu();
		}
		else
		{
			_window->GetWindow().draw(_gridSprite);

			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
				{
					_window->GetWindow().draw(_gridPieces[row][col]);
				}
			}
		}
		_window->GetWindow().display();
	}
}

void Game::Reset()
{
	_client->CloseSocket();
	_PlayerWon = false;
	_client->CloseSocket();
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			_boxAssinged[row][col] = EMPTY;
			_gridPieces[row][col].setTexture(NULL);
		}
	}
	return;
}

void Game::Handle()
{
	sf::Event e;

	while (_window->GetWindow().pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
		{
			_window->GetWindow().close();
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (_menu.isMenuShowing())
				{
					_menu.CheckClickPlay();
					_menu.CheckClickCustom();
					break;
				}
				else
				{
					UserPlay();
					break;
				}
			}
			break;
			
		}
		default:
			break;
		}

	}
}

void Game::UserPlay()
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (_gridPieces[row][col].getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
			{
				if (_boxAssinged[row][col] == EMPTY)
				{
					_boxAssinged[row][col] = PLAYER1;

					_gridPieces[row][col].setTexture(&_xTex);

					//Create coordinate message
					auto mes = _client->getMessages()->CreateNewMessage(SET, REQUEST_ID);
					mes["x"] = col;
					mes["y"] = row;
					_client->ClientSendMessage(_client->getMessages()->FinalizeMessage(mes));
					OnWin(CheckWin());
				}
			}
		}
	}
}

int Game::CheckWin()
{
	/* 
		column | column | column
	row  0/0   |  0/1   |  0/2
	row  1/0   |  1/1   |  1/2
	row  2/0   |  2/1   |  2/2
	*/

	for (size_t i = 0; i < 3; i++)
	{
		// check rows
		if (_boxAssinged[i][0] == PLAYER1 && _boxAssinged[i][1] == PLAYER1 && _boxAssinged[i][2] == PLAYER1)
		{
			return PLAYER1_WIN;
		}
		// check clolumns
		if (_boxAssinged[0][i] == PLAYER1 && _boxAssinged[1][i] == PLAYER1 && _boxAssinged[2][i] == PLAYER1)
		{
			return PLAYER1_WIN;
		}
		// check left-right diagonal
		if (_boxAssinged[0][0] == PLAYER1 && _boxAssinged[1][1] == PLAYER1 && _boxAssinged[2][2] == PLAYER1)
		{
			return PLAYER1_WIN;
		}
		// check right-left diagonal
		if (_boxAssinged[0][2] == PLAYER1 && _boxAssinged[1][1] == PLAYER1 && _boxAssinged[2][0] == PLAYER1)
		{
			return PLAYER1_WIN;
		}
	}

	// Check if still able to play
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (_boxAssinged[row][col] == EMPTY)
			{
				return EMPTY;
			}
		}
	}

	return DRAW;
}

void Game::OnWin(int checkwin)
{
	if (checkwin == EMPTY) { return; }

	if (checkwin == PLAYER1_WIN) _gameMessage = sf::Text("Player 1 Wins", _arial, 30);
	else if (checkwin == PLAYER2_WIN) _gameMessage = sf::Text("Player 2 Wins", _arial, 30);
	else if (checkwin == DRAW) _gameMessage = sf::Text("Draw", _arial, 30);

	//_menu.ShowMainMenu(_gameMessage);
	_PlayerWon = true; 
	auto mes = _client->getMessages()->CreateNewMessage(SET, REQUEST_ID);
	mes["WinCondition"] = _PlayerWon;
	_client->ClientSendMessage(_client->getMessages()->FinalizeMessage(mes));

	Reset();

	return;
}

void Game::BotPlay()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (_boxAssinged[i][j] == EMPTY)
			{
				_gridPieces[i][j].setTexture(&_oTex);
				_boxAssinged[i][j] = PLAYER2;
				return;
			}
		}
	}
}

void Game::Quit()
{
	delete _client;
}

Game* Game::GetInstance()
{
	static Game instance;
	return &instance;
}
