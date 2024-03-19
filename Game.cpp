#include "Game.h"
#include "Square.h"
#include <iostream>

Game::Game()
{
    m_restartButton = Button(660, 440, 885, 507, INACTIVE);
    m_readyButton = Button(690, 167, 850, 350, INACTIVE);
    m_infoButton = Button(935, 28, 980, 80, ACTIVE);
    m_undoButton = Button(920, 520, 980, 580, ACTIVE);
    InitGrid();
}

Game::~Game()
{
    for(auto square : m_grid)
    {
        delete square;
    }
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL init success\n";

        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(m_window != nullptr) // window init success
        {
            std::cout << "window creation success\n";
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if(m_renderer != nullptr) // renderer init success
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

                TextureManager::Instance()->LoadImages(m_renderer);
                SoundManager::Instance()->LoadMusic("music/gamemusic.mp3", "gamemusic");
                SoundManager::Instance()->LoadChunk("music/clicksound.wav", "clicksound");
            }
            else
            {
                std::cout << "renderer init failed\n";
                return false;
            }
        }
        else
        {
            std::cout << "window init failed\n";
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false;
    }
    std::cout << "init success\n";
    m_running = true;
    return true;
}

void Game::InitGrid()
{
    m_grid = {new Square(50, 55),
              new Square(225, 55),
              new Square(390, 55),
              new Square(50, 225),
              new Square(225, 225),
              new Square(390, 225),
              new Square(50, 390),
              new Square(225, 390),
              new Square(390, 390)};
}

void Game::Clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

bool Game::IsRunning() const
{
    return Game::m_running;
}

void Game::HandleEvents()
{
    SDL_Event event;
    int mouseX = 0;
    int mouseY = 0;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_running = false;
                break;
            case SDL_MOUSEMOTION:
                mouseX = event.button.x;
                mouseY = event.button.y;
                if(m_infoButton.contains(mouseX, mouseY))
                {
                    m_isInfoClicked = true;
                }
                else
                {
                    m_isInfoClicked = false;
                }

                IsSquareHovered(mouseX, mouseY);

                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseX = event.button.x;
                mouseY = event.button.y;
                if(m_restartButton.contains(mouseX, mouseY) && m_restartButton.getState() == ACTIVE)
                {
                    m_restartButton.setState(CLICKED);
                    SoundManager::Instance()->PlayClickSound();
                }
                if(m_readyButton.contains(mouseX, mouseY) && m_readyButton.getState() != INACTIVE && !IsGameOver() &&
                   m_drawnShapes.size() != m_grid.size())
                {
                    m_readyButton.setState(CLICKED);
                    m_isPlayerDone = true;
                    m_undoButton.setState(INACTIVE);
                    m_isPlayerOneOrTwo = !m_isPlayerOneOrTwo;
                    SoundManager::Instance()->PlayClickSound();
                }
                if(m_undoButton.contains(mouseX, mouseY) && !IsGameOver() && m_drawnShapes.size() != m_grid.size() &&
                   m_undoButton.getState() != INACTIVE)
                {
                    m_undoButton.setState(CLICKED);
                    SoundManager::Instance()->PlayClickSound();
                }

                if(IsLastEmptySquare())
                {
                    AutoFillLastSquare();
                }

                for(int i = 0; i < m_grid.size(); i++)
                {
                    HandleSquareEvent(*m_grid.at(i), i + 1, mouseX, mouseY);
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if(m_restartButton.getState() == CLICKED)
                {
                    RestartGame();
                }
                if(m_readyButton.getState() == CLICKED)
                {
                    m_readyButton.setState(INACTIVE);
                }
                if(m_undoButton.getState() == CLICKED)
                {
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

void Game::Render()
{
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    if(m_grid.at(0)->GetState() == m_grid.at(1)->GetState() && m_grid.at(1)->GetState() == m_grid.at(2)->GetState() &&
       m_grid.at(0)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(0)->GetSquareCenterX(),
                           m_grid.at(0)->GetSquareCenterY(),
                           m_grid.at(2)->GetSquareCenterX(),
                           m_grid.at(2)->GetSquareCenterY());
    }
    else if(m_grid.at(3)->GetState() == m_grid.at(4)->GetState() &&
            m_grid.at(4)->GetState() == m_grid.at(5)->GetState() && m_grid.at(3)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(3)->GetSquareCenterX(),
                           m_grid.at(3)->GetSquareCenterY(),
                           m_grid.at(5)->GetSquareCenterX(),
                           m_grid.at(5)->GetSquareCenterY());
    }
    else if(m_grid.at(6)->GetState() == m_grid.at(7)->GetState() &&
            m_grid.at(7)->GetState() == m_grid.at(8)->GetState() && m_grid.at(6)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(6)->GetSquareCenterX(),
                           m_grid.at(6)->GetSquareCenterY(),
                           m_grid.at(8)->GetSquareCenterX(),
                           m_grid.at(8)->GetSquareCenterY());
    }
    else if(m_grid.at(0)->GetState() == m_grid.at(3)->GetState() &&
            m_grid.at(3)->GetState() == m_grid.at(6)->GetState() && m_grid.at(0)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(0)->GetSquareCenterX(),
                           m_grid.at(0)->GetSquareCenterY(),
                           m_grid.at(6)->GetSquareCenterX(),
                           m_grid.at(6)->GetSquareCenterY());
    }
    else if(m_grid.at(1)->GetState() == m_grid.at(4)->GetState() &&
            m_grid.at(4)->GetState() == m_grid.at(7)->GetState() && m_grid.at(1)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(1)->GetSquareCenterX(),
                           m_grid.at(1)->GetSquareCenterY(),
                           m_grid.at(7)->GetSquareCenterX(),
                           m_grid.at(7)->GetSquareCenterY());
    }
    else if(m_grid.at(2)->GetState() == m_grid.at(5)->GetState() &&
            m_grid.at(5)->GetState() == m_grid.at(8)->GetState() && m_grid.at(2)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(2)->GetSquareCenterX(),
                           m_grid.at(2)->GetSquareCenterY(),
                           m_grid.at(8)->GetSquareCenterX(),
                           m_grid.at(8)->GetSquareCenterY());
    }
    else if(m_grid.at(0)->GetState() == m_grid.at(4)->GetState() &&
            m_grid.at(4)->GetState() == m_grid.at(8)->GetState() && m_grid.at(0)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(0)->GetSquareCenterX(),
                           m_grid.at(0)->GetSquareCenterY(),
                           m_grid.at(8)->GetSquareCenterX(),
                           m_grid.at(8)->GetSquareCenterY());
    }
    else if(m_grid.at(2)->GetState() == m_grid.at(4)->GetState() &&
            m_grid.at(4)->GetState() == m_grid.at(6)->GetState() && m_grid.at(2)->GetState() != EMPTY)
    {
        SDL_RenderDrawLine(m_renderer,
                           m_grid.at(2)->GetSquareCenterX(),
                           m_grid.at(2)->GetSquareCenterY(),
                           m_grid.at(6)->GetSquareCenterX(),
                           m_grid.at(6)->GetSquareCenterY());
    }

    // Shows image of which player won
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    if(m_result == P1WINS)
    {
        TextureManager::Instance()->DrawTexture("player1wins", 670, 50, 200, 31, m_renderer);
    }
    if(m_result == P2WINS)
    {
        TextureManager::Instance()->DrawTexture("player2wins", 670, 50, 200, 29, m_renderer);
    }

    // Draws image of which player's turn it is
    if(m_isPlayerOneOrTwo)
    {
        TextureManager::Instance()->DrawTexture("player1", 233, 7, 135, 22, m_renderer);
    }
    else
    {
        TextureManager::Instance()->DrawTexture("player2", 233, 7, 135, 22, m_renderer);
    }

    if(m_isInfoClicked)
    {
        TextureManager::Instance()->DrawTexture("text2", 650, 100, 250, 358, m_renderer);
    }

    if(!m_isInfoClicked)
    {
        TextureManager::Instance()->DrawTexture("ReadyStatic", 665, 150, 220, 220, m_renderer);
        if(m_restartButton.getState() == INACTIVE)
        {
            TextureManager::Instance()->DrawTexture("restartButtonInactive", 650, 430, 250, 80, m_renderer);
        }
        if(m_restartButton.getState() == CLICKED)
        {
            TextureManager::Instance()->DrawTexture("restartButtonClicked", 650, 430, 250, 80, m_renderer);
        }
        if(m_restartButton.getState() == ACTIVE)
        {
            TextureManager::Instance()->DrawTexture("ButtonActive", 650, 430, 250, 80, m_renderer);
        }
        if(m_readyButton.getState() == CLICKED)
        {
            TextureManager::Instance()->DrawTexture("ReadyClicked", 665, 150, 220, 220, m_renderer);
        }
        if(m_undoButton.getState() == ACTIVE)
        {
            TextureManager::Instance()->DrawTexture("undo1", 900, 500, 100, 100, m_renderer);
        }
        if(m_undoButton.getState() == INACTIVE)
        {
            TextureManager::Instance()->DrawTexture("undo2", 900, 500, 100, 100, m_renderer);
        }
        if(m_undoButton.getState() == CLICKED)
        {
            TextureManager::Instance()->DrawTexture("undo2", 900, 500, 100, 100, m_renderer);
        }
        if(m_result == DRAW)
        {
            TextureManager::Instance()->DrawTexture("DRAW", 690, 20, 178, 103, m_renderer);
        }
    }

    TextureManager::Instance()->DrawTexture("grid2", 50, 50, 500, 501, m_renderer);
    TextureManager::Instance()->DrawTexture("info2", 930, 20, 60, 60, m_renderer);

    for(int i = 0; i < m_grid.size(); i++)
    {
        if(i == m_lastSquareHoveredId)
        {
            if(m_grid.at(i)->GetIsClicked() == false && m_readyButton.getState() == INACTIVE)
            {
                HoverShowTexture(m_grid.at(i)->GetShapePosX(), m_grid.at(i)->GetShapePosY());
            }
        }
    }

    for(const auto& shape : m_drawnShapes)
    {
        for(int i = 0; i < m_grid.size(); i++)
        {
            if(shape == i + 1)
            {
                DrawTextureXorO(shape, m_grid.at(i)->GetShapePosX(), m_grid.at(i)->GetShapePosY());
            }
        }
    }
    SDL_RenderPresent(m_renderer);
}

void Game::HandleSquareEvent(Square& square, int index, int mouseX, int mouseY)
{
    if(square.IsInside(mouseX, mouseY) && m_isPlayerDone == true && square.GetIsClicked() == false)
    {
        m_drawnShapes.push_back(index);
        m_isPlayerDone = false;
        m_readyButton.setState(ACTIVE);
        m_undoButton.setState(ACTIVE);
        square.SetIsClicked(true);
        if(m_isPlayerOneOrTwo)
        {
            square.SetState(O);
        }
        else
        {
            square.SetState(X);
        }
        m_restartButton.setState(ACTIVE);
    }
    IsGameOver();
}

bool Game::IsGameOver()
{
    // Checking Horizontal winning condition for O
    if(m_grid.at(0)->GetState() == O && m_grid.at(1)->GetState() == O && m_grid.at(2)->GetState() == O ||
       m_grid.at(3)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(5)->GetState() == O ||
       m_grid.at(6)->GetState() == O && m_grid.at(7)->GetState() == O && m_grid.at(8)->GetState() == O)
    {
        m_result = P1WINS;
        return true;
    }
    // Checking Vertical winning condition for O
    if(m_grid.at(0)->GetState() == O && m_grid.at(3)->GetState() == O && m_grid.at(6)->GetState() == O ||
       m_grid.at(1)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(7)->GetState() == O ||
       m_grid.at(2)->GetState() == O && m_grid.at(5)->GetState() == O && m_grid.at(8)->GetState() == O)
    {
        m_result = P1WINS;
        return true;
    }
    // Checking Diagonal winning condition for O
    if(m_grid.at(0)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(8)->GetState() == O ||
       m_grid.at(2)->GetState() == O && m_grid.at(4)->GetState() == O && m_grid.at(6)->GetState() == O)
    {
        m_result = P1WINS;
        return true;
    }
    // Checking Horizontal winning condition for X
    if(m_grid.at(0)->GetState() == X && m_grid.at(1)->GetState() == X && m_grid.at(2)->GetState() == X ||
       m_grid.at(3)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(5)->GetState() == X ||
       m_grid.at(6)->GetState() == X && m_grid.at(7)->GetState() == X && m_grid.at(8)->GetState() == X)
    {
        m_result = P2WINS;
        return true;
    }
    // Checking Vertical winning condition for X
    if(m_grid.at(0)->GetState() == X && m_grid.at(3)->GetState() == X && m_grid.at(6)->GetState() == X ||
       m_grid.at(1)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(7)->GetState() == X ||
       m_grid.at(2)->GetState() == X && m_grid.at(5)->GetState() == X && m_grid.at(8)->GetState() == X)
    {
        m_result = P2WINS;
        return true;
    }
    // Checking Diagonal winning condition for X
    if(m_grid.at(0)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(8)->GetState() == X ||
       m_grid.at(2)->GetState() == X && m_grid.at(4)->GetState() == X && m_grid.at(6)->GetState() == X)
    {
        m_result = P2WINS;
        return true;
    }

    for(int i = 0; i < m_grid.size(); i++)
    {
        if(m_grid.at(i)->GetState() != EMPTY && m_drawnShapes.size() == m_grid.size())
        {
            m_result = DRAW;
        }

        return false;
    }
    return false;
}

void Game::RestartGame()
{
    InitGrid();
    m_drawnShapes.clear();
    m_restartButton.setState(INACTIVE);
    m_readyButton.setState(INACTIVE);
    m_undoButton.setState(INACTIVE);
    m_isPlayerOneOrTwo = true;
    m_isPlayerDone = true;
    m_result = NOWINNER;
}

void Game::IsSquareHovered(int mouseX, int mouseY)
{
    for(int i = 0; i < m_grid.size(); i++)
    {
        if(m_grid.at(i)->IsInside(mouseX, mouseY))
        {
            m_lastSquareHoveredId = i;
            break;
        }
        else
        {
            m_lastSquareHoveredId = UNUSED_SQUARE;
        }
    }
}

void Game::DrawTextureXorO(int shape, int x, int y)
{
    if(m_grid.at(shape - 1)->GetState() == O)
    {
        TextureManager::Instance()->DrawTexture("circle2", x, y, Square::SHAPE_SIZE, Square::SHAPE_SIZE, m_renderer);
    }
    else
    {
        TextureManager::Instance()->DrawTexture("Ximage2", x, y, Square::SHAPE_SIZE, Square::SHAPE_SIZE, m_renderer);
    }
}

void Game::AutoFillLastSquare()
{
    if(!IsGameOver())
    {
        for(int i = 0; i < m_grid.size(); i++)
        {
            if(m_grid.at(i)->GetState() == EMPTY)
            {
                m_drawnShapes.push_back(i + 1);
                if(m_isPlayerOneOrTwo)
                {
                    m_grid.at(i)->SetState(O);
                }
                else
                {
                    m_grid.at(i)->SetState(X);
                }
            }
        }
    }
}

bool Game::IsLastEmptySquare()
{
    return (m_drawnShapes.size() == m_grid.size() - 1);
}

void Game::HoverShowTexture(int x, int y)
{
    if(m_isPlayerOneOrTwo)
    {
        SDL_SetTextureAlphaMod(TextureManager::Instance()->getTexture("circle2"), 100);
        TextureManager::Instance()->DrawTexture("circle2", x, y, Square::SHAPE_SIZE, Square::SHAPE_SIZE, m_renderer);
        SDL_SetTextureAlphaMod(TextureManager::Instance()->getTexture("circle2"), 255);
    }
    else
    {
        SDL_SetTextureAlphaMod(TextureManager::Instance()->getTexture("Ximage2"), 100);
        TextureManager::Instance()->DrawTexture("Ximage2", x, y, Square::SHAPE_SIZE, Square::SHAPE_SIZE, m_renderer);
        SDL_SetTextureAlphaMod(TextureManager::Instance()->getTexture("Ximage2"), 255);
    }
}

void Game::UndoLast()
{
    if(!m_drawnShapes.empty() && m_drawnShapes.size() != m_grid.size())
    {
        int lastShape = m_drawnShapes.back();
        m_drawnShapes.pop_back();

        m_grid.at(lastShape - 1)->Clear();

        m_isPlayerDone = true;
        for(const auto& square : m_grid)
        {
            square->SetIsClicked(false);
        }
    }
}
