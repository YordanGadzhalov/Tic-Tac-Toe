#pragma once
#include <SDL_image.h>
#include "TextureManager.h"
#include <vector>
#include "Square.h"
#include "Button.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundManager.h"

enum GameState{P1WINS, P2WINS, DRAW, NOWINNER};

class Game : public Square {
public:
    Game();
	~Game();
	bool init(const char* title, int xpos,
		int ypos, int width, int height, int flags);

	void render();
	void handleEvents();
	void clean();
	bool isRunning();
    bool isGameOver();
	void restartGame();
	void undoLast();
    void handleGridEvent(Square& square, int index, int mouseX, int mouseY);
    void InitGrid();

private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
	int counter;
    GameState result = NOWINNER;
    bool isPlayerDone = true;
	bool running;
	bool isPlayerOneOrTwo = true;
	bool isInfoClicked = false;
    std::vector<int> drawnShapes;
    std::vector<Square> grid;
    Button restartButton = Button(660, 440, 885, 507, INACTIVE);
	Button readyButton = Button(690, 167, 850, 350, ACTIVE);
	Button infoButton = Button(935, 28, 980, 80, ACTIVE);
	Button undoButton = Button(920, 520, 980, 580, ACTIVE);
};
