#include "pch/pch.h"
#include "Game/Game.h"
#include "Client/Messages/WindowMessage.h"

int main() 
{
	GameWindow* window = GameWindow::getInstance();
	window->InitWindow();
	Game* game = Game::GetInstance();
	game->Start();
	game->Update();
	return 0;
}