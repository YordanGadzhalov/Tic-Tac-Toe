#include "Game.h"
#include "Grid.h"
#include <iostream>

bool isAlreadyClicked; // to be made in Grid.h bool func


bool Game::init(const char* title, int xpos,
	int ypos, int width, int height, int flags) {
	drawnShapes.clear(); // clears vector
	//Coordinates of each grid 1-9
	

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) //window init success
		{
			std::cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				TextureManager::Instance()->loadTexture("assets/grid2.png", "grid2", renderer);
				TextureManager::Instance()->loadTexture("assets/Ximage2.png", "Ximage2", renderer);
				TextureManager::Instance()->loadTexture("assets/circle2.png", "circle2", renderer);
				TextureManager::Instance()->loadTexture("assets/startButton2.png", "startButton2", renderer);
				TextureManager::Instance()->loadTexture("assets/info2.png", "info2", renderer);
				TextureManager::Instance()->loadTexture("assets/ready2.png", "ready2", renderer);
				TextureManager::Instance()->loadTexture("assets/text2.png", "text2", renderer);
				TextureManager::Instance()->loadTexture("assets/player1.png", "player1", renderer);
				TextureManager::Instance()->loadTexture("assets/player2.png", "player2", renderer);
			}

			else {
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else {
			std::cout << "window init failed\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail\n";
		return false;
	}
	std::cout << "init success\n";
	running = true;
	return true;
}

//Draws the picture
void Game::render() {

	SDL_RenderClear(renderer);

	if (isPlayerOneOrTwo) {
		TextureManager::Instance()->drawTexture("player1", 233, 7, 135, 22, renderer);
	}
	else {
		TextureManager::Instance()->drawTexture("player2", 233, 7, 135, 22, renderer);
	}

	if (isInfoClicked) {
		TextureManager::Instance()->drawTexture("text2", 650, 100, 250, 358, renderer);
	}
	

	if (!isInfoClicked) {
		TextureManager::Instance()->drawTexture("startButton2", 650, 350, 200, 206, renderer);
		TextureManager::Instance()->drawTexture("ready2", 650, 150, 190, 170, renderer);
	}
	//TextureManager::Instance()->drawTexture("startButton2", 650, 350, 200, 206, renderer);
	TextureManager::Instance()->drawTexture("grid2", 50, 50, 500, 501, renderer);
	TextureManager::Instance()->drawTexture("info2", 930, 20, 60, 60, renderer);
	
		for (auto shape : drawnShapes) {
			if (shape == 1) {
				if (grid1.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 65, 65, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 65, 65, 125, 125, renderer);
				}
			}
			if (shape == 2) {
				if (grid2.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 240, 65, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 240, 65, 125, 125, renderer);
				}
			}
			if (shape == 3) {
				if (grid3.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 410, 65, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 410, 65, 125, 125, renderer);
				}
			}
			if (shape == 4) {
				if (grid4.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 65, 235, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 65, 235, 125, 125, renderer);
				}
			}
			if (shape == 5) {
				if (grid5.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 240, 235, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 240, 235, 125, 125, renderer);
				}
			}
			if (shape == 6) {
				if (grid6.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 410, 235, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 410, 235, 125, 125, renderer);
				}
			}
			if (shape == 7) {
				if (grid7.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 65, 410, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 65, 410, 125, 125, renderer);
				}
			}
			if (shape == 8) {
				if (grid8.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 240, 410, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 240, 410, 125, 125, renderer);
				}
			}
			if (shape == 9) {
				if (grid9.getXorO()) {
					TextureManager::Instance()->drawTexture("circle2", 410, 410, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 410, 410, 125, 125, renderer);
				}
			}
		}

	SDL_RenderPresent(renderer);
}

//Manages all events
void Game::handleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEMOTION:
			{
			int mouseX = event.button.x;
			int mouseY = event.button.y;
			if (infoButton.contains(mouseX, mouseY)) {
				isInfoClicked = true;
			}
			else
			{
				isInfoClicked = false;
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			int mouseX = event.button.x;
			int mouseY = event.button.y;
				if (readyButton.contains(mouseX, mouseY)){
					std::cout << "CLICKED!" << std::endl;
					isPlayerOneOrTwo = !isPlayerOneOrTwo;
				}
				if (grid1.isInside(mouseX, mouseY) && !isAlreadyClicked) {
					drawnShapes.push_back(1);
					isAlreadyClicked = true;
					grid1.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 1 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}
		

				if (grid2.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(2);
					grid2.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 1 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid3.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(3);
					grid3.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 3 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid4.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(4);
					grid4.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 4 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid5.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(5);
					grid5.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 5 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid6.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(6);
					grid6.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 6 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid7.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(7);
					grid7.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 7 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid8.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(8);
					grid8.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 8 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}


				if (grid9.isInside(mouseX, mouseY)) {

					drawnShapes.push_back(9);
					grid9.setXorO(isPlayerOneOrTwo);
					std::cout << "Grid 9 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}
				if (isGameOver()) {
					std::cout << "Game over!" << std::endl;
				}
				cout << "X: " << mouseX << "Y: " << mouseY << endl;
			}
		default:
			break;
		}
	}
}


void Game::clean() {
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


bool Game::isRunning() {
	return Game::running;
}
bool Game::isGameOver() {

	if (drawnShapes.size() <= 5) {
		return false;
	}

	// Player 1 wins
	if ((grid1.getXorO() && grid2.getXorO() && grid3.getXorO()) ||
		(grid4.getXorO() && grid5.getXorO() && grid6.getXorO()) ||
		(grid7.getXorO() && grid8.getXorO() && grid9.getXorO()) ||
		(grid2.getXorO() && grid5.getXorO() && grid8.getXorO()) ||
		(grid3.getXorO() && grid6.getXorO() && grid9.getXorO()) ||
		(grid1.getXorO() && grid5.getXorO() && grid9.getXorO()) ||
		(grid7.getXorO() && grid5.getXorO() && grid3.getXorO()) ||
		(grid1.getXorO() && grid4.getXorO() && grid7.getXorO())) {
		return true; 
	}

	// Player 2 wins
	if ((!grid1.getXorO() && !grid2.getXorO() && !grid3.getXorO()) ||
		(!grid4.getXorO() && !grid5.getXorO() && !grid6.getXorO()) ||
		(!grid7.getXorO() && !grid8.getXorO() && !grid9.getXorO()) ||
		(!grid2.getXorO() && !grid5.getXorO() && !grid8.getXorO()) ||
		(!grid3.getXorO() && !grid6.getXorO() && !grid9.getXorO()) ||
		(!grid1.getXorO() && !grid5.getXorO() && !grid9.getXorO()) ||
		(!grid7.getXorO() && !grid5.getXorO() && !grid3.getXorO()) ||
		(!grid1.getXorO() && !grid4.getXorO() && !grid7.getXorO())) {
		return true; 
	}

	if (drawnShapes.size() == 9) {
		return true;
	}

	return false;
}


Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}


Game::~Game() {}