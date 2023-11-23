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
			_boxAssignedSingle[row][col] = EMPTY;
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
			UpdateGrid();
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
				if (_menu.isMenuShowing() && _menu.getIsMainMenuShowing())
				{
					if (ChangeGameState())
					{
						break;
					}
				}
				if (_menu.isMenuShowing() && _menu.getIsMatchMakeShowing())
				{
					if (CreateGame())
					{
						break;
					}
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

bool Game::ChangeGameState()
{
	if (_menu.ClickMulti())
	{
		if (!_client->CheckPassport())
		{
			_menu.ShowNameMenu();
		}
		else CreateClientThread();
		return true;
	}
	if (_menu.ClickSingle())
	{
		return true;
	}
	else false;
}

bool Game::CreateGame()
{
	if (_menu.ClickMatchMake())
	{
		//Send match making message
		_client->setInstructions(MATCHMAKING_ID, REQUEST_ID);
		auto mes = _client->getMessage();
		mes["Msg"] = "Looking for Game";
		_client->setMessage(mes);
		_client->ClientSendMessage(_client->getMessage());
		std::cout << _client->getMessage() << std::endl;

		return true;
	}
	else return false;
}

void Game::UserPlay()
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (_gridPieces[row][col].getGlobalBounds().contains(sf::Mouse::getPosition(_window->GetWindow()).x, sf::Mouse::getPosition(_window->GetWindow()).y))
			{
				if (_client->getBoxAssigned(row, col) == EMPTY && _boxAssignedSingle[row][col] == EMPTY)
				{
					if (_menu.getInMulti() && _client->getClientCanPlay())
					{
						_client->setBoxAssigned(row, col, PLAYER1);

						if (_client->getPlayerNum() == 1)
						{
							_gridPieces[row][col].setTexture(&_xTex);
						}
						else _gridPieces[row][col].setTexture(&_oTex);

						//Send coordinate message
						_client->setInstructions(SET, REQUEST_ID);
						auto mes = _client->getMessage();
						mes["x"] = row;
						mes["y"] = col;
						_client->setMessage(mes);
						//_client->ClientSendMessage(_client->getMessage());

						_client->setClientCanPlay(false);
					}
					else if (!_menu.getInMulti())
					{
						_boxAssignedSingle[row][col] = PLAYER1;

						_gridPieces[row][col].setTexture(&_xTex);

						BotPlay();
					}
					OnWin(CheckWin());
				}
			}
		}
	}
}

void Game::UpdateGrid()
{
	if (_menu.getInMulti())
	{
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				if (_client->getBoxAssigned(row, col) == PLAYER2)
				{
					if (_client->getPlayerNum() == 1)
					{
						_gridPieces[row][col].setTexture(&_oTex);
					}
					else _gridPieces[row][col].setTexture(&_xTex);
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
		if ((_client->getBoxAssigned(i, 0) == PLAYER1 && _client->getBoxAssigned(i, 1) == PLAYER1 && _client->getBoxAssigned(i, 2) == PLAYER1) || 
			(_boxAssignedSingle[i][0] == PLAYER1 && _boxAssignedSingle[i][1] == PLAYER1 && _boxAssignedSingle[i][2] == PLAYER1))
		{
			return PLAYER1_WIN;
		}
		else if (_boxAssignedSingle[i][0] == PLAYER2 && _boxAssignedSingle[i][1] == PLAYER2 && _boxAssignedSingle[i][2] == PLAYER2)
		{
			return PLAYER2_WIN;
		}
	
		// check clolumns
		if ((_client->getBoxAssigned(0, i) == PLAYER1 && _client->getBoxAssigned(1, i) == PLAYER1 && _client->getBoxAssigned(2, i) == PLAYER1) ||
			(_boxAssignedSingle[0][i] == PLAYER1 && _boxAssignedSingle[1][i] == PLAYER1 && _boxAssignedSingle[2][i] == PLAYER1))
		{
			return PLAYER1_WIN;
		}
		else if (_boxAssignedSingle[0][i] == PLAYER2 && _boxAssignedSingle[1][i] == PLAYER2 && _boxAssignedSingle[2][i] == PLAYER2)
		{
			return PLAYER2_WIN;
		}

		// check left-right diagonal
		if ((_client->getBoxAssigned(0, 0) == PLAYER1 && _client->getBoxAssigned(1, 1) == PLAYER1 && _client->getBoxAssigned(2, 2) == PLAYER1) ||
			(_boxAssignedSingle[0][0] == PLAYER1 && _boxAssignedSingle[1][1] == PLAYER1 && _boxAssignedSingle[2][2] == PLAYER1))
		{
			return PLAYER1_WIN;
		}
		else if (_boxAssignedSingle[0][0] == PLAYER2 && _boxAssignedSingle[1][1] == PLAYER2 && _boxAssignedSingle[2][2] == PLAYER2)
		{
			return PLAYER2_WIN;
		}

		// check right-left diagonal
		if ((_client->getBoxAssigned(0, 2) == PLAYER1 && _client->getBoxAssigned(1, 1) == PLAYER1 && _client->getBoxAssigned(2, 0) == PLAYER1) ||
			(_boxAssignedSingle[0][2] == PLAYER1 && _boxAssignedSingle[1][1] == PLAYER1 && _boxAssignedSingle[2][0] == PLAYER1))
		{
			return PLAYER1_WIN;
		}
		else if (_boxAssignedSingle[0][2] == PLAYER2 && _boxAssignedSingle[1][1] == PLAYER2 && _boxAssignedSingle[2][0] == PLAYER2)
		{
			return PLAYER2_WIN;
		}
	}

	// Check if still able to play
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (_client->getBoxAssigned(row, col) == EMPTY && _boxAssignedSingle[row][col] == EMPTY)
			{
				return NOWIN;
			}
		}
	}

	return DRAW;
}

void Game::OnWin(int checkwin)
{
	if (_menu.getInMulti())
	{
		auto mes = _client->getMessage();
		mes["WinCondition"] = checkwin;
		_client->setMessage(mes);
		_client->ClientSendMessage(_client->getMessage());
		std::cout << _client->getMessage() << std::endl;
	}
	if (checkwin == NOWIN) { return; }

	if (checkwin == PLAYER1_WIN) _gameMessage = sf::Text("You Won!", _arial, 30);
	else if (checkwin == PLAYER2_WIN) _gameMessage = sf::Text("You lost...", _arial, 30);
	else if (checkwin == DRAW) _gameMessage = sf::Text("Draw", _arial, 30);

	_PlayerWon = true;

	// add Play again screen
	Reset();

	return;
}

void Game::BotPlay()
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (_boxAssignedSingle[row][col] == EMPTY)
			{
				_gridPieces[row][col].setTexture(&_oTex);
				_boxAssignedSingle[row][col] = PLAYER2;
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
			_boxAssignedSingle[row][col] = EMPTY;
			_client->setBoxAssigned(row, col, EMPTY);
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
