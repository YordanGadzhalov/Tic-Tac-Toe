#include "Game.h"
#include "Grid.h"
#include <iostream>



bool Game::init(const char* title, int xpos,
	int ypos, int width, int height, int flags) {
	drawnShapes.clear(); // clears vector
	

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
				TextureManager::Instance()->loadTexture("assets/ButtonStatic.png", "ButtonStatic", renderer);
				TextureManager::Instance()->loadTexture("assets/ButtonClicked.png", "startButtonClicked", renderer);
				TextureManager::Instance()->loadTexture("assets/ButtonInactive.png", "startButtonInactive", renderer);
				TextureManager::Instance()->loadTexture("assets/info2.png", "info2", renderer);
				TextureManager::Instance()->loadTexture("assets/ReadyButtonStatic.png", "ReadyStatic", renderer);
				TextureManager::Instance()->loadTexture("assets/ReadyButtonClicked.png", "ReadyClicked", renderer);
				TextureManager::Instance()->loadTexture("assets/text2.png", "text2", renderer);
				TextureManager::Instance()->loadTexture("assets/player1.png", "player1", renderer);
				TextureManager::Instance()->loadTexture("assets/player2.png", "player2", renderer);
				TextureManager::Instance()->loadTexture("assets/player1wins.png", "player1wins", renderer);
				TextureManager::Instance()->loadTexture("assets/player2wins.png", "player2wins", renderer);
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

	//Shows image of which player won
	if(playerOneWins) {
		TextureManager::Instance()->drawTexture("player1wins", 650, 50, 200, 31, renderer);
	}

	if(playerTwoWins) {
		TextureManager::Instance()->drawTexture("player2wins", 650, 50, 200, 29, renderer);
	}

	//Draws image of which player's turn it is
	if(isPlayerOneOrTwo) {
		TextureManager::Instance()->drawTexture("player1", 233, 7, 135, 22, renderer);
	}
	else {
		TextureManager::Instance()->drawTexture("player2", 233, 7, 135, 22, renderer);
	}

	//Shows info on the screen
	if(isInfoClicked) {
		TextureManager::Instance()->drawTexture("text2", 650, 100, 250, 358, renderer);
	}
	
	if(!isInfoClicked) {
		//TextureManager::Instance()->drawTexture("startButton2", 650, 350, 200, 206, renderer);
		TextureManager::Instance()->drawTexture("ReadyStatic", 665, 150, 220, 220, renderer);
		TextureManager::Instance()->drawTexture("ButtonStatic", 650, 430, 250, 80, renderer);
		if (startButton.getState() == CLICKED) {
			TextureManager::Instance()->drawTexture("startButtonClicked", 650, 430, 250, 80, renderer);
			SDL_Delay(200);
		}
		if (startButton.getState() == INACTIVE) {
			TextureManager::Instance()->drawTexture("startButtonInactive", 650, 430, 250, 80, renderer);
		}
		if (readyButton.getState() == CLICKED) {
			TextureManager::Instance()->drawTexture("ReadyClicked", 665, 150, 220, 220, renderer);
		}
	}
	

	//Draws the grid and the info button
	TextureManager::Instance()->drawTexture("grid2", 50, 50, 500, 501, renderer);
	TextureManager::Instance()->drawTexture("info2", 930, 20, 60, 60, renderer);
		
		//Draws O/X based on clicked grid and current player
		for (auto shape : drawnShapes) {
			if (shape == 1) {
				if (grid1.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 65, 65, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 65, 65, 125, 125, renderer);
				}
			}
			if (shape == 2) {
				if (grid2.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 240, 65, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 240, 65, 125, 125, renderer);
				}
			}
			if (shape == 3) {
				if (grid3.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 410, 65, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 410, 65, 125, 125, renderer);
				}
			}
			if (shape == 4) {
				if (grid4.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 65, 235, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 65, 235, 125, 125, renderer);
				}
			}
			if (shape == 5) {
				if (grid5.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 240, 235, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 240, 235, 125, 125, renderer);
				}
			}
			if (shape == 6) {
				if (grid6.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 410, 235, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 410, 235, 125, 125, renderer);
				}
			}
			if (shape == 7) {
				if (grid7.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 65, 410, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 65, 410, 125, 125, renderer);
				}
			}
			if (shape == 8) {
				if (grid8.getState() == O) {
					TextureManager::Instance()->drawTexture("circle2", 240, 410, 125, 125, renderer);
				}
				else {
					TextureManager::Instance()->drawTexture("Ximage2", 240, 410, 125, 125, renderer);
				}
			}
			if (shape == 9) {
				if (grid9.getState() == O) {
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
			if(!isGameOver()){
				startButton.setState(INACTIVE);
			}
			else {
				startButton.setState(STATIC);
			}

			if (startButton.contains(mouseX, mouseY)) {
				std::cout << "Start button clicked " << std::endl;
				startButton.setState(CLICKED);
				restartGame();
			}
				if (readyButton.contains(mouseX, mouseY)){
					std::cout << "READY CLICKED!" << std::endl;
					readyButton.setState(CLICKED);
					isPlayerOneOrTwo = !isPlayerOneOrTwo;
				}
				if (grid1.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(1);
					if (isPlayerOneOrTwo) {
						grid1.setState(O);
					}
					else {
						grid1.setState(X);
					}
					std::cout << "Grid 1 " << "STATE: " << grid1.getState() << std::endl;
					std::cout << "Grid 1 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid2.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(2);
					if (isPlayerOneOrTwo) {
						grid2.setState(O);
					}
					else {
						grid2.setState(X);
					}
					std::cout << "Grid 2 " << "STATE: " << grid2.getState() << std::endl;
					std::cout << "Grid 2 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid3.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(3);
					if (isPlayerOneOrTwo) {
						grid3.setState(O);
					}
					else {
						grid3.setState(X);
					}
					std::cout << "Grid 3 " << "STATE: " << grid3.getState() << std::endl;
					std::cout << "Grid 3 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid4.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(4);
					if (isPlayerOneOrTwo) {
						grid4.setState(O);
					}
					else {
						grid4.setState(X);
					}
					std::cout << "Grid 4 " << "STATE: " << grid4.getState() << std::endl;
					std::cout << "Grid 4 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid5.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(5);
					if (isPlayerOneOrTwo) {
						grid5.setState(O);
					}
					else {
						grid5.setState(X);
					}
					std::cout << "Grid 5 " << "STATE: " << grid5.getState() << std::endl;
					std::cout << "Grid 5 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid6.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(6);
					if (isPlayerOneOrTwo) {
						grid6.setState(O);
					}
					else {
						grid6.setState(X);
					}
					std::cout << "Grid 6 " << "STATE: " << grid6.getState() << std::endl;
					std::cout << "Grid 6 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid7.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(7);
					if (isPlayerOneOrTwo) {
						grid7.setState(O);
					}
					else {
						grid7.setState(X);
					}
					std::cout << "Grid 7 " << "STATE: " << grid7.getState() << std::endl;
					std::cout << "Grid 7 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid8.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(8);
					if (isPlayerOneOrTwo) {
						grid8.setState(O);
					}
					else {
						grid8.setState(X);
					}
					std::cout << "Grid 8 " << "STATE: " << grid8.getState() << std::endl;
					std::cout << "Grid 8 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}

				if (grid9.isInside(mouseX, mouseY)) {
					drawnShapes.push_back(9);
					if (isPlayerOneOrTwo) {
						grid9.setState(O);
					}
					else {
						grid9.setState(X);
					}
					std::cout << "Grid 9 " << "STATE: " << grid9.getState() << std::endl;
					std::cout << "Grid 9 " << "Player: " << isPlayerOneOrTwo << std::endl;
				}
				cout << "X: " << mouseX << "Y: " << mouseY << endl;
				/*std::cout << "Grid 1 " << "STATE: " << grid1.getState() << std::endl;
				std::cout << "Grid 2 " << "STATE: " << grid2.getState() << std::endl;   // Checking grid states between 0/1/2 - EMPTY/O/X
				std::cout << "Grid 3 " << "STATE: " << grid3.getState() << std::endl;*/
			}
		default:
			break;
			case SDL_MOUSEBUTTONUP:
				if (startButton.getState() == CLICKED) {
					startButton.setState(STATIC); // Returns the button state back to static
				}
				if (readyButton.getState() == CLICKED) {
					readyButton.setState(STATIC);
				}
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

bool Game::isGameOver()
{
	//Checking Horizontal winning condition for O
	if (grid1.getState() == O && grid2.getState() == O && grid3.getState() == O ||
		grid4.getState() == O && grid5.getState() == O && grid6.getState() == O ||
		grid7.getState() == O && grid8.getState() == O && grid9.getState() == O){
		return playerOneWins = true;
	}

	//Checking Vertical winning condition for O
	if (grid1.getState() == O && grid4.getState() == O && grid7.getState() == O ||
		grid2.getState() == O && grid5.getState() == O && grid8.getState() == O ||
		grid3.getState() == O && grid6.getState() == O && grid9.getState() == O) {
		return playerOneWins = true;
	}

	//Checking Diagonal winning condition for O
	if (grid1.getState() == O && grid5.getState() == O && grid9.getState() == O ||
		grid3.getState() == O && grid5.getState() == O && grid7.getState() == O) {
		return playerOneWins = true;
	}

	//Checking Horizontal winning condition for X
	if (grid1.getState() == X && grid2.getState() == X && grid3.getState() == X ||
		grid4.getState() == X && grid5.getState() == X && grid6.getState() == X ||
		grid7.getState() == X && grid8.getState() == X && grid9.getState() == X) {
		return playerTwoWins = true;
	}

	//Checking Vertical winning condition for X
	if (grid1.getState() == X && grid4.getState() == X && grid7.getState() == X ||
		grid2.getState() == X && grid5.getState() == X && grid8.getState() == X ||
		grid3.getState() == X && grid6.getState() == X && grid9.getState() == X) {
		return playerTwoWins = true;
	}

	//Checking Diagonal winning condition for X
	if (grid1.getState() == X && grid5.getState() == X && grid9.getState() == X ||
		grid3.getState() == X && grid5.getState() == X && grid7.getState() == X) {
		return playerTwoWins = true;
	}

	return false;
}

void Game::restartGame()
{
	grid1.setState(EMPTY);
	grid2.setState(EMPTY);
	grid3.setState(EMPTY);
	grid4.setState(EMPTY);
	grid5.setState(EMPTY);
	grid6.setState(EMPTY);
	grid7.setState(EMPTY);
	grid8.setState(EMPTY);
	grid9.setState(EMPTY);
	drawnShapes.clear(); // clears vector
	playerOneWins = false;
	playerTwoWins = false;
	isPlayerOneOrTwo = true;
}


Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}


Game::~Game() {}