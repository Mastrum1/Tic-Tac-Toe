#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Client.h"

int main() {
	Game game;
	Client client;
	game.Start();
	client.InitClient();

	return 0;
}