#include "pch/pch.h"
#include "Game/Game.h"

int main() 
{
	Game* game = Game::GetInstance();
	game->Start();
	return 0;
}