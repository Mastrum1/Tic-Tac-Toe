#include "Game.h"
#include "pch.h"


Game::Game()
{
	if (!_grid.loadFromFile("Resources/Board.png")) std::cout << "load texture error.\n";
	if (!_xTex.loadFromFile("Resources/X_Piece.png")) std::cout << "load texture error.\n";
	if (!_oTex.loadFromFile("Resources/O_Piece.png")) std::cout << "load texture error.\n";
	if (!_arial.loadFromFile("Resources/arial.ttf")) std::cout << "load font error.\n";

	_gridSprite.setTexture(_grid);
	_gridSprite.setPosition(50, 50);
	_gridSprite.setScale(sf::Vector2f(3.5, 3.5));
}

Game::~Game()
{
}

void Game::Start()
{
	_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tic Tac Toe");
	_window.setFramerateLimit(30);
	_client.InitClient();

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			_gridPieces[i][j].setSize(sf::Vector2f(150, 150));
			_gridPieces[i][j].setPosition(sf::Vector2f(110 + j * 210, 110 + i * 215));
			_boxAssinged[i][j] = EMPTY;
		}
	}

	while (_window.isOpen()) 
	{
		Handle();

		_window.clear(sf::Color::White);

		if (_menuShowing)
		{
			_window.draw(_gameMessage);
		}
		else
		{
			_window.draw(_gridSprite);

			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					_window.draw(_gridPieces[i][j]);
				}
			}
		}
		_window.display();
	}
}

void Game::Reset()
{
	_PlayerWon = false;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			_boxAssinged[i][j] = EMPTY;
			_gridPieces[i][j].setTexture(NULL);
		}
	}
	return;
}

void Game::Handle()
{
	sf::Event e;

	while (_window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
		{
			_window.close();
			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				if (_menuShowing)
				{
					if (_gameMessage.getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
					{
						_menuShowing = false;
						break;
					}
				}
				else
				{
					for (size_t i = 0; i < 3; i++)
					{
						for (size_t j = 0; j < 3; j++)
						{
							if (_gridPieces[i][j].getGlobalBounds().contains(sf::Mouse::getPosition(_window).x, sf::Mouse::getPosition(_window).y))
							{
								if (_boxAssinged[i][j] == EMPTY)
								{
									_boxAssinged[i][j] = PLAYER1;

									_gridPieces[i][j].setTexture(&_xTex);

									//Create coordinate message
									auto mes = _messages.CreateMessage(SET, REQUEST_ID);
									mes["x"] = i;
									mes["y"] = j;
									_client.ClientSendMessage(_messages.FinalizeMessage(mes));
									OnWin(CheckWin());

									break;
								}
							}
						}
					}
				}
			}
			break;
			
		}
		default:
			break;
		}

	}
}

int Game::CheckWin()
{
	/* Box id in grid i = row, j = column
	
		column | column | column
	row  0/0   |  0/1   |  0/2
	row  1/0   |  1/1   |  1/2
	row  2/0   |  2/1   |  2/2
	*/

	int sumPlayer1;
	int sumPlayer2;

	// Check win in rows [i][j]
	for (size_t i = 0; i < 3; i++)
	{
		sumPlayer1 = 0;
		sumPlayer2 = 0;
		for (size_t j = 0; j < 3; j++)
		{
			if (_boxAssinged[i][j] == PLAYER1)
			{
				sumPlayer1++;
			}if (_boxAssinged[i][j] == PLAYER2)
			{
				sumPlayer2++;
			}
		}
		if (sumPlayer1 == 3)
		{
			return PLAYER1_WIN;
		}
		if (sumPlayer2 == 3)
		{
			return PLAYER2_WIN;
		}
	}

	// Check win for column [j][i]
	for (size_t i = 0; i < 3; i++)
	{
		sumPlayer1 = 0;
		sumPlayer2 = 0;
		for (size_t j = 0; j < 3; j++)
		{
			if (_boxAssinged[j][i] == PLAYER1)
			{
				sumPlayer1++;
			}if (_boxAssinged[j][i] == PLAYER2)
			{
				sumPlayer2++;
			}
		}
		if (sumPlayer1 == 3)
		{
			return PLAYER1_WIN;
		}
		if (sumPlayer2 == 3)
		{
			return PLAYER2_WIN;
		}
	}

	sumPlayer1 = 0;
	sumPlayer2 = 0;

	// Check for left-right diagonal
	for (size_t i = 0; i < 3; i++)
	{

		if (_boxAssinged[i][i] == PLAYER1)
		{
			sumPlayer1++;
		}if (_boxAssinged[i][i] == PLAYER2)
		{
			sumPlayer2++;
		}
	}
	if (sumPlayer1 == 3)
	{
		return PLAYER1_WIN;
	}
	if (sumPlayer2 == 3)
	{
		return PLAYER2_WIN;
	}

	sumPlayer1 = 0;
	sumPlayer2 = 0;
	// Check for right-left diagonal
	for (size_t i = 0; i < 3; i++)
	{

		if (_boxAssinged[i][2-i] == PLAYER1)
		{
			sumPlayer1++;
		}if (_boxAssinged[i][2-i] == PLAYER2)
		{
			sumPlayer2++;
		}
	}
	if (sumPlayer1 == 3)
	{
		return PLAYER1_WIN;
	}
	if (sumPlayer2 == 3)
	{
		return PLAYER2_WIN;
	}

	// Check if 
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (_boxAssinged[i][j] == EMPTY)
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

	_menuShowing = true;
	_PlayerWon = true; 
	auto mes = _messages.CreateMessage(SET, REQUEST_ID);
	mes["WinCondition"] = _PlayerWon;
	_client.ClientSendMessage(_messages.FinalizeMessage(mes));

	OpenMenu();

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

void Game::OpenMenu()
{
	_gameMenu = _gameMessage.getGlobalBounds();

	_gameMessage.setOrigin(_gameMenu.left + _gameMenu.width / 2.0f, _gameMenu.top + _gameMenu.height / 2.0f);
	_gameMessage.setPosition(sf::Vector2f(400, 400));
	_gameMessage.setFillColor(sf::Color::Black);
}
