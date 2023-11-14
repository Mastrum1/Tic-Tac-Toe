#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Client.h"

int main() {
	Game game;
	Client client;
	client.InitClient();
	game.Start();
	game.setClient(&client);

	return 0;
}