#include "Game.h"
#include "Square.h"
#include <iostream>


bool Game::init(const char* title, int xpos,
	int ypos, int width, int height, int flags) {

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

                TextureManager::Instance()->loadTexture("assets/gameover.png", "gameover", renderer);
				TextureManager::Instance()->loadTexture("assets/grid2.png", "grid2", renderer);
				TextureManager::Instance()->loadTexture("assets/Ximage2.png", "Ximage2", renderer);
				TextureManager::Instance()->loadTexture("assets/undo1.png", "undo1", renderer);
				TextureManager::Instance()->loadTexture("assets/undo2.png", "undo2", renderer);
				TextureManager::Instance()->loadTexture("assets/circle2.png", "circle2", renderer);
				TextureManager::Instance()->loadTexture("assets/ButtonActive.png", "ButtonActive", renderer);
				TextureManager::Instance()->loadTexture("assets/ButtonClicked.png", "restartButtonClicked", renderer);
				TextureManager::Instance()->loadTexture("assets/ButtonInactive.png", "restartButtonInactive", renderer);
				TextureManager::Instance()->loadTexture("assets/info2.png", "info2", renderer);
				TextureManager::Instance()->loadTexture("assets/ReadyButtonStatic.png", "ReadyStatic", renderer);
				TextureManager::Instance()->loadTexture("assets/ReadyButtonClicked.png", "ReadyClicked", renderer);
				TextureManager::Instance()->loadTexture("assets/text2.png", "text2", renderer);
				TextureManager::Instance()->loadTexture("assets/player1.png", "player1", renderer);
				TextureManager::Instance()->loadTexture("assets/player2.png", "player2", renderer);
				TextureManager::Instance()->loadTexture("assets/player1wins.png", "player1wins", renderer);
				TextureManager::Instance()->loadTexture("assets/player2wins.png", "player2wins", renderer);
				TextureManager::Instance()->loadTexture("assets/DRAW.png", "DRAW", renderer);
				SoundManager::Instance()->load("music/gamemusic.mp3", "gamemusic", 1);
				SoundManager::Instance()->load("music/clicksound.wav", "clicksound", 0);
				SoundManager::Instance()->playMainMusic();
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

void Game::render() {

	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    if (m_grid.at(0).getState() == m_grid.at(1).getState() && m_grid.at(1).getState() == m_grid.at(2).getState() && m_grid.at(0).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 50, 125, 540, 125);
	}
    else if (m_grid.at(3).getState() == m_grid.at(4).getState() && m_grid.at(4).getState() == m_grid.at(5).getState() && m_grid.at(3).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 50, 300, 540, 300);
	}
    else if (m_grid.at(6).getState() == m_grid.at(7).getState() && m_grid.at(7).getState() == m_grid.at(8).getState() && m_grid.at(6).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 50, 470, 540, 470);
	}
    else if (m_grid.at(0).getState() == m_grid.at(3).getState() && m_grid.at(3).getState() == m_grid.at(6).getState() && m_grid.at(0).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 130, 50, 130, 540);
	}
    else if (m_grid.at(1).getState() == m_grid.at(4).getState() && m_grid.at(4).getState() == m_grid.at(7).getState() && m_grid.at(1).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 300, 50, 300, 540);
	}
    else if (m_grid.at(2).getState() == m_grid.at(5).getState() && m_grid.at(5).getState() == m_grid.at(8).getState() && m_grid.at(2).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 465, 50, 465, 540);
	}
    else if (m_grid.at(0).getState() == m_grid.at(4).getState() && m_grid.at(4).getState() == m_grid.at(8).getState() && m_grid.at(0).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 90, 70, 500, 500);
	}
    else if (m_grid.at(2).getState() == m_grid.at(4).getState() && m_grid.at(4).getState() == m_grid.at(6).getState() && m_grid.at(2).getState() != EMPTY) {
		SDL_RenderDrawLine(renderer, 520, 70, 110, 500);
	}


	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    if(result == P1WINS) {
		TextureManager::Instance()->drawTexture("player1wins", 670, 50, 200, 31, renderer);
	}
    if(result == P2WINS) {
		TextureManager::Instance()->drawTexture("player2wins", 670, 50, 200, 29, renderer);
	}

	if(isPlayerOneOrTwo) {
		TextureManager::Instance()->drawTexture("player1", 233, 7, 135, 22, renderer);
	}
	else {
		TextureManager::Instance()->drawTexture("player2", 233, 7, 135, 22, renderer);
	}

	if(isInfoClicked) {
		TextureManager::Instance()->drawTexture("text2", 650, 100, 250, 358, renderer);
	}


	if(!isInfoClicked) {
		TextureManager::Instance()->drawTexture("ReadyStatic", 665, 150, 220, 220, renderer);
        if(restartButton.getState() == INACTIVE) {
			TextureManager::Instance()->drawTexture("restartButtonInactive", 650, 430, 250, 80, renderer);
		}
        if(restartButton.getState() == CLICKED){
			TextureManager::Instance()->drawTexture("restartButtonClicked", 650, 430, 250, 80, renderer);
		}
        if(restartButton.getState() == ACTIVE) {
			TextureManager::Instance()->drawTexture("ButtonActive", 650, 430, 250, 80, renderer);
		}
        if(readyButton.getState() == CLICKED) {
			TextureManager::Instance()->drawTexture("ReadyClicked", 665, 150, 220, 220, renderer);
		}
        if(undoButton.getState() == ACTIVE) {
            TextureManager::Instance()->drawTexture("undo1", 900, 500, 100, 100, renderer);
		}
        if(undoButton.getState() == INACTIVE){
            TextureManager::Instance()->drawTexture("undo2", 900, 500, 100, 100, renderer);
        }
        if(undoButton.getState() == CLICKED) {
			TextureManager::Instance()->drawTexture("undo2", 900, 500, 100, 100, renderer);
		}
        if(!isGameOver() && counter == 9) {
			TextureManager::Instance()->drawTexture("DRAW", 690, 20, 178, 103, renderer);
		}
	}

	TextureManager::Instance()->drawTexture("grid2", 50, 50, 500, 501, renderer);
	TextureManager::Instance()->drawTexture("info2", 930, 20, 60, 60, renderer);


        for (const auto shape : drawnShapes) {
			if (shape == 1) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 65, 65, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 65, 65, SIZE, SIZE, renderer);
				}
			}
			if (shape == 2) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 240, 65, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 240, 65, SIZE, SIZE, renderer);
				}
			}
			if (shape == 3) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 410, 65, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 410, 65, SIZE, SIZE, renderer);
				}
			}
			if (shape == 4) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 65, 235, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 65, 235, SIZE, SIZE, renderer);
				}
			}
			if (shape == 5) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 240, 235, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 240, 235, SIZE, SIZE, renderer);
				}
			}
			if (shape == 6) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 410, 235, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 410, 235, SIZE, SIZE, renderer);
				}
			}
			if (shape == 7) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 65, 410, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 65, 410, SIZE, SIZE, renderer);
				}
			}
			if (shape == 8) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 240, 410, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 240, 410, SIZE, SIZE, renderer);
				}
			}
			if (shape == 9) {
                if (m_grid.at(shape - 1).getState() == O) {
                    TextureManager::Instance()->drawTexture("circle2", 410, 410, SIZE, SIZE, renderer);
				}
				else {
                    TextureManager::Instance()->drawTexture("Ximage2", 410, 410, SIZE, SIZE, renderer);
				}
			}
		}

	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {

	SDL_Event event;
	int mouseX = 0;
	int mouseY = 0;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEMOTION:
			mouseX = event.button.x;
			mouseY = event.button.y;
			if (infoButton.contains(mouseX, mouseY)) {
                isInfoClicked = true;
			}
			else
			{
				isInfoClicked = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseX = event.button.x;
            mouseY = event.button.y;
            if (restartButton.contains(mouseX, mouseY) && restartButton.getState() == ACTIVE){
				std::cout << "Start button clicked " << std::endl;
				restartButton.setState(CLICKED);
				SoundManager::Instance()->playClickSound();
			}
            if (readyButton.contains(mouseX, mouseY) && readyButton.getState() != INACTIVE){
				std::cout << "READY CLICKED!" << std::endl;
				readyButton.setState(CLICKED);
				isPlayerDone = true;
				isPlayerOneOrTwo = !isPlayerOneOrTwo;
                std::cout << isPlayerOneOrTwo << std::endl;
				SoundManager::Instance()->playClickSound();
			}
            if (undoButton.contains(mouseX, mouseY) && !isGameOver() && counter != 9 && undoButton.getState() != INACTIVE) {
                undoButton.setState(CLICKED);
				SoundManager::Instance()->playClickSound();
			}
            handleSquareEvent(m_grid.at(0), 1, mouseX, mouseY);
            handleSquareEvent(m_grid.at(1), 2, mouseX, mouseY);
            handleSquareEvent(m_grid.at(2), 3, mouseX, mouseY);
            handleSquareEvent(m_grid.at(3), 4, mouseX, mouseY);
            handleSquareEvent(m_grid.at(4), 5, mouseX, mouseY);
            handleSquareEvent(m_grid.at(5), 6, mouseX, mouseY);
            handleSquareEvent(m_grid.at(6), 7, mouseX, mouseY);
            handleSquareEvent(m_grid.at(7), 8, mouseX, mouseY);
            handleSquareEvent(m_grid.at(8), 9, mouseX, mouseY);
			break;

		case SDL_MOUSEBUTTONUP:
            if (restartButton.getState() == CLICKED) {
                restartGame();
			}
			if (readyButton.getState() == CLICKED) {
                readyButton.setState(INACTIVE);
			}
			if (undoButton.getState() == CLICKED) {
                undoButton.setState(INACTIVE);
				undoLast();
			}
			break;

		default:
			break;
		}
	}
}

void Game::handleSquareEvent(Square& grid, int index, int mouseX, int mouseY){
    if (grid.isInside(mouseX, mouseY) && !grid.getIsClicked() && isPlayerDone == true) {
        drawnShapes.push_back(index);
        isPlayerDone = false;
        counter++;
        readyButton.setState(ACTIVE);
        undoButton.setState(ACTIVE);
        grid.setIsClicked(true);
        if (isPlayerOneOrTwo) {
            grid.setState(O);
        }
        else
        {
            grid.setState(X);
        }
        // if ((counter > 4 && isGameOver()) || (counter == 9 && !isGameOver())) {
            restartButton.setState(ACTIVE);
        // }
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
    if (m_grid.at(0).getState() == O && m_grid.at(1).getState() == O && m_grid.at(2).getState() == O ||
        m_grid.at(3).getState() == O && m_grid.at(4).getState() == O && m_grid.at(5).getState() == O ||
        m_grid.at(6).getState() == O && m_grid.at(7).getState() == O && m_grid.at(8).getState() == O){
        result = P1WINS;
        return true;
    }
    //Checking Vertical winning condition for O
    if (m_grid.at(0).getState() == O && m_grid.at(3).getState() == O && m_grid.at(6).getState() == O ||
        m_grid.at(1).getState() == O && m_grid.at(4).getState() == O && m_grid.at(7).getState() == O ||
        m_grid.at(2).getState() == O && m_grid.at(5).getState() == O && m_grid.at(8).getState() == O) {
        result = P1WINS;
        return true;
    }
    //Checking Diagonal winning condition for O
    if (m_grid.at(0).getState() == O && m_grid.at(4).getState() == O && m_grid.at(8).getState() == O ||
        m_grid.at(2).getState() == O && m_grid.at(4).getState() == O && m_grid.at(6).getState() == O) {
        result = P1WINS;
        return true;
    }
    //Checking Horizontal winning condition for X
    if (m_grid.at(0).getState() == X && m_grid.at(1).getState() == X && m_grid.at(2).getState() == X ||
        m_grid.at(3).getState() == X && m_grid.at(4).getState() == X && m_grid.at(5).getState() == X ||
        m_grid.at(6).getState() == X && m_grid.at(7).getState() == X && m_grid.at(8).getState() == X){
        result = P2WINS;
        return true;
    }
    //Checking Vertical winning condition for O
    if (m_grid.at(0).getState() == X && m_grid.at(3).getState() == X && m_grid.at(6).getState() == X ||
        m_grid.at(1).getState() == X && m_grid.at(4).getState() == X && m_grid.at(7).getState() == X ||
        m_grid.at(2).getState() == X && m_grid.at(5).getState() == X && m_grid.at(8).getState() == X) {
        result = P2WINS;
        return true;
    }
    //Checking Diagonal winning condition for O
    if (m_grid.at(0).getState() == X && m_grid.at(4).getState() == X && m_grid.at(8).getState() == X ||
        m_grid.at(2).getState() == X && m_grid.at(4).getState() == X && m_grid.at(6).getState() == X) {
        result = P2WINS;
        return true;
    }
    return false;
}

void Game::restartGame()
{
    InitGrid();
	drawnShapes.clear(); // clears vector
	restartButton.setState(INACTIVE);
	readyButton.setState(ACTIVE);
    undoButton.setState(INACTIVE);
	isPlayerOneOrTwo = true;
	isPlayerDone = true;
    result = NOWINNER;
    counter = 0;
}


void Game::InitGrid(){
    m_grid = {
        Square(55, 205, 55, 205, EMPTY),
        Square(225, 375, 55, 205, EMPTY),
        Square(390, 540, 55, 205, EMPTY),
        Square(55, 205, 225, 370, EMPTY),
        Square(225, 375, 225, 370, EMPTY),
        Square(390, 550, 225, 370, EMPTY),
        Square(50, 205, 390, 550, EMPTY),
        Square(225, 377, 390, 550, EMPTY),
        Square(390, 550, 390, 550, EMPTY)
    };
}



void Game::undoLast()
{
	if (!drawnShapes.empty() && counter != 9) {
		int lastShape = drawnShapes.back();
		drawnShapes.pop_back();

        m_grid.at(lastShape - 1).clear();
        counter--;

		isPlayerDone = true;
        setIsClicked(false);
	}
}


Game::Game() {
    InitGrid();
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}




Game::~Game() {}
