#include "pch/pch.h"
#include "Game/Game.h"
#include "Game/GameWindow.h"

int main() {
	GameWindow* window = GameWindow::getInstance();
	window->InitWindow();
	Game game;
	game.Start();

	return 0;
}