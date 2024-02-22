#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include <vector>
#include "Grid.h"
#include "Button.h"

class Game {
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

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	bool isPlayerOneOrTwo = true;
	bool isInfoClicked = false;
	std::vector<int> drawnShapes; //Holds the shapes we want to draw and redraws them everytime it renders
	Grid grid1 = Grid(55, 205, 55, 205); 
	Grid grid2 = Grid(225, 375, 55, 205);
	Grid grid3 = Grid(390, 540, 55, 205);
	Grid grid4 = Grid(55, 205, 225, 370); // vector ?
	Grid grid5 = Grid(225, 375, 225, 370); 
	Grid grid6 = Grid(390, 550, 225, 370);
	Grid grid7 = Grid(50, 205, 390, 550);
	Grid grid8 = Grid(225, 377, 390, 550);
	Grid grid9 = Grid(390, 550, 390, 550);
	Button readyButton = Button(674, 200, 820, 284);
	Button infoButton = Button(935, 28, 980, 80);

};
