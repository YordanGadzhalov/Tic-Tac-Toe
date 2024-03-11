#include "Game.h"
#include <iostream>
using namespace std;


Game* game = NULL;
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
	game = new Game();
	game->init("Tic-Tac-Toe",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_RESIZABLE);


	while (game->isRunning()) {
		game->handleEvents();
		game->render();
	}

	game->clean();
	return 0;
}
