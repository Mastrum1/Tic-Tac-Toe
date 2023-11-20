#include "pch/pch.h"
#include "Game/Game.h"
#include "Client/Messages/WindowMessage.h"

int main() {
	Game* game = Game::GetInstance();
	game->Start();
	game->Update();
	return 0;
}