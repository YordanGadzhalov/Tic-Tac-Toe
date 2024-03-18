#include "Game.h"
#include <iostream>
using namespace std;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[])
{
    Game game;
    game.init("Tic-Tac-Toe",
              SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED,
              WINDOW_WIDTH,
              WINDOW_HEIGHT,
              SDL_WINDOW_RESIZABLE);

    while(game.IsRunning())
    {
        game.HandleEvents();
        game.Render();
    }

    game.Clean();
    return 0;
}
