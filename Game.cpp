#include "Game.h"
#include "Square.h"
#include <iostream>


bool Game::init(const char* title, int xpos,
	int ypos, int width, int height, int flags) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";

        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_window != 0) //window init success
		{
			std::cout << "window creation success\n";
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if (m_renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

                TextureManager::Instance()->LoadImages(m_renderer);

                SoundManager::Instance()->LoadMusic("music/gamemusic.mp3", "gamemusic");
                SoundManager::Instance()->LoadChunk("music/clicksound.wav", "clicksound");
                SoundManager::Instance()->PlayMainMusic();

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
    m_running = true;
	return true;
}

void Game::Render() {

    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    if (m_grid.at(0)->GetState() == m_grid.at(1)->GetState() && m_grid.at(1)->GetState() == m_grid.at(2)->GetState() && m_grid.at(0)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 50, 125, 540, 125);
	}
    else if (m_grid.at(3)->GetState() == m_grid.at(4)->GetState() && m_grid.at(4)->GetState() == m_grid.at(5)->GetState() && m_grid.at(3)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 50, 300, 540, 300);
	}
    else if (m_grid.at(6)->GetState() == m_grid.at(7)->GetState() && m_grid.at(7)->GetState() == m_grid.at(8)->GetState() && m_grid.at(6)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 50, 470, 540, 470);
	}
    else if (m_grid.at(0)->GetState() == m_grid.at(3)->GetState() && m_grid.at(3)->GetState() == m_grid.at(6)->GetState() && m_grid.at(0)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 130, 50, 130, 540);
	}
    else if (m_grid.at(1)->GetState() == m_grid.at(4)->GetState() && m_grid.at(4)->GetState() == m_grid.at(7)->GetState() && m_grid.at(1)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 300, 50, 300, 540);
	}
    else if (m_grid.at(2)->GetState() == m_grid.at(5)->GetState() && m_grid.at(5)->GetState() == m_grid.at(8)->GetState() && m_grid.at(2)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 465, 50, 465, 540);
	}
    else if (m_grid.at(0)->GetState() == m_grid.at(4)->GetState() && m_grid.at(4)->GetState() == m_grid.at(8)->GetState() && m_grid.at(0)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 90, 70, 500, 500);
	}
    else if (m_grid.at(2)->GetState() == m_grid.at(4)->GetState() && m_grid.at(4)->GetState() == m_grid.at(6)->GetState() && m_grid.at(2)->GetState() != EMPTY) {
        SDL_RenderDrawLine(m_renderer, 520, 70, 110, 500);
	}

    //Shows image of which player won
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    if(m_result == P1WINS) {
        TextureManager::Instance()->DrawTexture("player1wins", 670, 50, 200, 31, m_renderer);
	}
    if(m_result == P2WINS) {
        TextureManager::Instance()->DrawTexture("player2wins", 670, 50, 200, 29, m_renderer);
	}


    //Draws image of which player's turn it is
    if(m_isPlayerOneOrTwo) {
        TextureManager::Instance()->DrawTexture("player1", 233, 7, 135, 22, m_renderer);
	}
	else {
        TextureManager::Instance()->DrawTexture("player2", 233, 7, 135, 22, m_renderer);
	}

    if(m_isInfoClicked) {
        TextureManager::Instance()->DrawTexture("text2", 650, 100, 250, 358, m_renderer);
	}


    if(!m_isInfoClicked) {
        TextureManager::Instance()->DrawTexture("ReadyStatic", 665, 150, 220, 220, m_renderer);
        if(m_restartButton.getState() == INACTIVE) {
            TextureManager::Instance()->DrawTexture("restartButtonInactive", 650, 430, 250, 80, m_renderer);
		}
        if(m_restartButton.getState() == CLICKED){
            TextureManager::Instance()->DrawTexture("restartButtonClicked", 650, 430, 250, 80, m_renderer);
		}
        if(m_restartButton.getState() == ACTIVE) {
            TextureManager::Instance()->DrawTexture("ButtonActive", 650, 430, 250, 80, m_renderer);
		}
        if(m_readyButton.getState() == CLICKED) {
            TextureManager::Instance()->DrawTexture("ReadyClicked", 665, 150, 220, 220, m_renderer);
		}
        if(m_undoButton.getState() == ACTIVE) {
            TextureManager::Instance()->DrawTexture("undo1", 900, 500, 100, 100, m_renderer);
		}
        if(m_undoButton.getState() == INACTIVE){
            TextureManager::Instance()->DrawTexture("undo2", 900, 500, 100, 100, m_renderer);
        }
        if(m_undoButton.getState() == CLICKED) {
            TextureManager::Instance()->DrawTexture("undo2", 900, 500, 100, 100, m_renderer);
		}
        if(!IsGameOver() && m_counter == 9) {
            TextureManager::Instance()->DrawTexture("DRAW", 690, 20, 178, 103, m_renderer);
		}
	}

    TextureManager::Instance()->DrawTexture("grid2", 50, 50, 500, 501, m_renderer);
    TextureManager::Instance()->DrawTexture("info2", 930, 20, 60, 60, m_renderer);


    for (const auto shape : m_drawnShapes) {
			if (shape == 1) {
                DrawTextureXorO(shape, 65, 65);
			}
			if (shape == 2) {
                DrawTextureXorO(shape, 240, 65);
			}
			if (shape == 3) {
                DrawTextureXorO(shape, 410, 65);
			}
			if (shape == 4) {
                DrawTextureXorO(shape, 65, 235);
			}
			if (shape == 5) {
                DrawTextureXorO(shape, 240, 235);
			}
			if (shape == 6) {
                DrawTextureXorO(shape, 410, 235);
			}
			if (shape == 7) {
                DrawTextureXorO(shape, 65, 410);
			}
			if (shape == 8) {
                DrawTextureXorO(shape, 240, 410);
			}
			if (shape == 9) {
                DrawTextureXorO(shape, 410, 410);
			}
		}

        SDL_RenderPresent(m_renderer);
}

void Game::HandleEvents() {

	SDL_Event event;
	int mouseX = 0;
	int mouseY = 0;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
            m_running = false;
			break;
		case SDL_MOUSEMOTION:
			mouseX = event.button.x;
			mouseY = event.button.y;
            if (m_infoButton.contains(mouseX, mouseY)) {
                m_isInfoClicked = true;
			}
			else
			{
                m_isInfoClicked = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseX = event.button.x;
            mouseY = event.button.y;
            if (m_restartButton.contains(mouseX, mouseY) && m_restartButton.getState() == ACTIVE){
				std::cout << "Start button clicked " << std::endl;
                m_restartButton.setState(CLICKED);
                SoundManager::Instance()->PlayClickSound();
			}
            if (m_readyButton.contains(mouseX, mouseY) && m_readyButton.getState() != INACTIVE && !IsGameOver() && m_counter != 9){
				std::cout << "READY CLICKED!" << std::endl;
                m_readyButton.setState(CLICKED);
                m_isPlayerDone = true;
                m_isPlayerOneOrTwo = !m_isPlayerOneOrTwo;
                std::cout << m_isPlayerOneOrTwo << std::endl;
                SoundManager::Instance()->PlayClickSound();
			}
            if (m_undoButton.contains(mouseX, mouseY) && !IsGameOver() && m_counter != 9 && m_undoButton.getState() != INACTIVE) {
                m_undoButton.setState(CLICKED);
                SoundManager::Instance()->PlayClickSound();
			}
            HandleSquareEvent(*m_grid.at(0), 1, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(1), 2, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(2), 3, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(3), 4, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(4), 5, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(5), 6, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(6), 7, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(7), 8, mouseX, mouseY);
            HandleSquareEvent(*m_grid.at(8), 9, mouseX, mouseY);
			break;

		case SDL_MOUSEBUTTONUP:
            if (m_restartButton.getState() == CLICKED) {
                RestartGame();
			}
            if (m_readyButton.getState() == CLICKED) {
                m_readyButton.setState(INACTIVE);
			}
            if (m_undoButton.getState() == CLICKED) {
                m_readyButton.setState(INACTIVE);
                m_undoButton.setState(INACTIVE);
                UndoLast();
			}
			break;

		default:
			break;
		}
	}
}

void Game::HandleSquareEvent(Square& grid, int index, int mouseX, int mouseY){
    if (grid.IsInside(mouseX, mouseY) && !grid.GetIsClicked() && m_isPlayerDone == true) {
        m_drawnShapes.push_back(index);
        m_isPlayerDone = false;
        m_counter++;
        m_readyButton.setState(ACTIVE);
        m_undoButton.setState(ACTIVE);
        grid.SetIsClicked(true);
        if (m_isPlayerOneOrTwo) {
            grid.SetState(O);
        }
        else
        {
            grid.SetState(X);
        }
        m_restartButton.setState(ACTIVE);
    }
}

void Game::Clean() {
	std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}


bool Game::IsRunning() const {
    return Game::m_running;
}

bool Game::IsGameOver()
{
    //Checking Horizontal winning condition for O
    if (m_grid.at(0)->GetState() == O && m_grid.at(1)->GetState() == O && m_grid.at(2)->GetState() == O ||
        m_grid.at(3)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(5)->GetState() == O ||
        m_grid.at(6)->GetState() == O && m_grid.at(7)->GetState() == O && m_grid.at(8)->GetState() == O){
        m_result = P1WINS;
        return true;
    }
    //Checking Vertical winning condition for O
    if (m_grid.at(0)->GetState() == O && m_grid.at(3)->GetState() == O && m_grid.at(6)->GetState() == O ||
        m_grid.at(1)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(7)->GetState() == O ||
        m_grid.at(2)->GetState() == O && m_grid.at(5)->GetState() == O && m_grid.at(8)->GetState() == O) {
        m_result = P1WINS;
        return true;
    }
    //Checking Diagonal winning condition for O
    if (m_grid.at(0)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(8)->GetState() == O ||
        m_grid.at(2)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(6)->GetState() == O) {
        m_result = P1WINS;
        return true;
    }
    //Checking Horizontal winning condition for X
    if (m_grid.at(0)->GetState() == X && m_grid.at(1)->GetState() == X && m_grid.at(2)->GetState() == X ||
        m_grid.at(3)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(5)->GetState() == X ||
        m_grid.at(6)->GetState() == X && m_grid.at(7)->GetState() == X && m_grid.at(8)->GetState() == X){
        m_result = P2WINS;
        return true;
    }
    //Checking Vertical winning condition for X
    if (m_grid.at(0)->GetState() == X && m_grid.at(3)->GetState() == X && m_grid.at(6)->GetState() == X ||
        m_grid.at(1)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(7)->GetState() == X ||
        m_grid.at(2)->GetState() == X && m_grid.at(5)->GetState() == X && m_grid.at(8)->GetState() == X) {
        m_result = P2WINS;
        return true;
    }
    //Checking Diagonal winning condition for X
    if (m_grid.at(0)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(8)->GetState() == X ||
        m_grid.at(2)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(6)->GetState() == X) {
        m_result = P2WINS;
        return true;
    }

    return false;
}

void Game::RestartGame()
{
    InitGrid();
    m_drawnShapes.clear(); // clears vector
    m_restartButton.setState(INACTIVE);
    m_readyButton.setState(INACTIVE);
    m_undoButton.setState(INACTIVE);
    m_isPlayerOneOrTwo = true;
    m_isPlayerDone = true;
    m_result = NOWINNER;
    m_counter = 0;
}


void Game::InitGrid(){
    m_grid = {
        new Square(55, 205, 55, 205, EMPTY),
        new Square(225, 375, 55, 205, EMPTY),
        new Square(390, 540, 55, 205, EMPTY),
        new Square(55, 205, 225, 370, EMPTY),
        new Square(225, 375, 225, 370, EMPTY),
        new Square(390, 550, 225, 370, EMPTY),
        new Square(50, 205, 390, 550, EMPTY),
        new Square(225, 377, 390, 550, EMPTY),
        new Square(390, 550, 390, 550, EMPTY)
    };
}


void Game::DrawTextureXorO(int shape, int x, int y)
{
    if (m_grid.at(shape - 1)->GetState() == O) {
        TextureManager::Instance()->DrawTexture("circle2", x, y, SIZE, SIZE, m_renderer);
    }
    else {
        TextureManager::Instance()->DrawTexture("Ximage2", x, y, SIZE, SIZE, m_renderer);
    }
}


void Game::UndoLast()
{
    if (!m_drawnShapes.empty() && m_counter != 9) {
        int lastShape = m_drawnShapes.back();
        m_drawnShapes.pop_back();

        m_grid.at(lastShape - 1)->Clear();
        m_counter--;

        m_isPlayerDone = true;
        SetIsClicked(false);
	}
}


Game::Game() {
    m_restartButton = Button(660, 440, 885, 507, INACTIVE);
    m_readyButton = Button(690, 167, 850, 350, INACTIVE);
    m_infoButton = Button(935, 28, 980, 80, ACTIVE);
    m_undoButton = Button(920, 520, 980, 580, ACTIVE);
    InitGrid();
    Game::m_window = NULL;
    Game::m_renderer = NULL;
    Game::m_running = true;
}




Game::~Game() {
    for (auto square : m_grid){
        delete square;
    }
}
