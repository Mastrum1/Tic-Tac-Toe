#include "pch/pch.h"
#include "Game.h"
#include "Client/Client.h"
#include "Client/Messages/WindowMessage.h"


Game::Game()
{
	_window = nullptr;
	_client = nullptr;

	if (!_grid.loadFromFile("Resources/Board.png")) std::cout << "load texture error.\n";
	if (!_xTex.loadFromFile("Resources/X_Piece.png")) std::cout << "load texture error.\n";
	if (!_oTex.loadFromFile("Resources/O_Piece.png")) std::cout << "load texture error.\n";
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_gridSprite.setTexture(_grid);
	//_gridSprite.setPosition(50, 50);
	//_gridSprite.setScale(sf::Vector2f(3.5, 3.5));
}

Game::~Game()
{
	assert(_client == nullptr);
	Quit();
}

Game* Game::GetInstance() 
{
	static Game instance;
	return &instance;
}

void Game::Start()
{
	_client = Client::GetInstance();
	_window = GameWindow::getInstance();
	_window->InitWindow();

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

	Update();

}

DWORD Game::ClientThread(void* param)
{
	Client* client = Client::GetInstance();
	client->InitClient();
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
			_menu.ShowMenu();
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
					ChangeGameState();
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

void Game::ChangeGameState()
{
	if (_menu.ClickMulti())
	{
		if (!_client->CheckPassport())
		{
			_menu.ShowNameMenu();
		}
		else CreateClientThread();
	}
	if (_menu.ClickMatchMake())
	{
		//Create match make message
		_client->setInstructions(MATCHMAKING_ID, REQUEST_ID);
		auto mes = _client->getMessage();
		mes["Msg"] = "Give me a game bitch";
		_client->setMessage(mes);
		Sleep(1000);
		_client->ClientSendMessage(mes);
	}
	else _menu.ClickSingle();

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
					if (_menu.getInMulti() && _client->getClientCanPlay())
					{
						//Create coordinate message
						_client->setInstructions(SET, REQUEST_ID);
						auto mes = _client->getMessage();
						mes["ID"] = _client->getID();
						mes["x"] = col;
						mes["y"] = row;
						_client->setMessage(mes);
						_client->ClientSendMessage(_client->getMessage());
						_client->setClientCanPlay(false);
					}
					else if (!_menu.getInMulti())
					{
						BotPlay();
					} 

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

	if (checkwin == PLAYER1_WIN) _gameMessage = sf::Text("You Won!", _arial, 30);
	else if (checkwin == PLAYER2_WIN) _gameMessage = sf::Text("You lost...", _arial, 30);
	else if (checkwin == DRAW) _gameMessage = sf::Text("Draw", _arial, 30);

	//_menu.ShowMainMenu(_gameMessage);
	_PlayerWon = true;
	if (_menu.getInMulti())
	{
		/*auto mes = _client->getMessages()->CreateNewMessage(SET, REQUEST_ID);
		mes["WinCondition"] = _PlayerWon;
		_client->ClientSendMessage(_client->getMessages()->FinalizeMessage(mes));*/
	}

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

void Game::Reset()
{
	_PlayerWon = false;
	if (_menu.getInMulti())
	{
		_client->CloseSocket();
	}

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

void Game::Quit()
{
	delete _client;
}

void Game::CreateClientThread()
{
	HANDLE Thread = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)ClientThread, 0, 0, NULL);
}

Client* Game::getClient()
{
	return _client;
}
