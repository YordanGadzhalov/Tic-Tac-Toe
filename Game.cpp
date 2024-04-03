#include "Game.h"
#include "Square.h"
#include <iostream>

Game::Game()
{
    m_restartButton = Button(660, 440, 885, 507, INACTIVE);
    m_readyButton = Button(690, 167, 850, 350, INACTIVE);
    m_infoButton = Button(935, 28, 980, 80, ACTIVE);
    m_undoButton = Button(920, 520, 980, 580, ACTIVE);
    m_historyButton = Button(940, 100, 985, 145, INACTIVE);
    m_forwardButton = Button(550, 560, 580, 590, INACTIVE);
    m_backButton = Button(28, 560, 60, 590, INACTIVE);
    InitGrid();
    InitGameLogic();
}

Game::~Game()
{
    for(auto square : m_grid)
    {
        delete square;
    }
    delete m_gameLogic;
    m_gameLogic = nullptr;
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

void Game::InitGameLogic()
{
    m_gameLogic = new GameLogic(
        [this](const GridState& state)
        {
            UpdateView(state);
        });
}

void Game::UpdateView(const GridState& state)
{
    for(int i = 0; i < m_grid.size(); i++)
    {
        const auto playerID = state.at(i);
        if(playerID != NONE)
        {
            m_grid.at(i)->SetSymbol(m_gameLogic->GetPlayer(playerID).GetShapeId());
        }
        else
        {
            m_grid.at(i)->SetSymbol();
            m_grid.at(i)->SetIsClicked(false);
        }
    }
}

void Game::Clean() const
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

bool Game::IsRunning() const
{
    return m_running;
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

                if(m_forwardButton.contains(mouseX, mouseY))
                {
                    m_gameLogic->ForwardHistory();
                }
                if(m_backButton.contains(mouseX, mouseY))
                {
                    m_gameLogic->BackwardHistory();
                }
                if(m_historyButton.contains(mouseX, mouseY) && m_gameLogic->IsGameOver())
                {
                    m_gameLogic->ToggleHistoryMode();
                    if(m_gameLogic->GetHistoryMode())
                    {
                        m_restartButton.setState(INACTIVE);
                    }
                    else
                    {
                        m_restartButton.setState(ACTIVE);
                    }
                }
                if(m_restartButton.contains(mouseX, mouseY) && m_restartButton.getState() == ACTIVE)
                {
                    m_restartButton.setState(CLICKED);
                    SoundManager::Instance()->PlayClickSound();
                }

                if(m_readyButton.contains(mouseX, mouseY) && m_readyButton.getState() != INACTIVE &&
                   !m_gameLogic->IsGameOver())
                {
                    m_readyButton.setState(CLICKED);
                    m_undoButton.setState(INACTIVE);
                    m_gameLogic->SwitchPlayers();
                    SoundManager::Instance()->PlayClickSound();
                }

                if(m_undoButton.contains(mouseX, mouseY) && !m_gameLogic->IsGameOver() &&
                   m_undoButton.getState() != INACTIVE)
                {
                    m_undoButton.setState(CLICKED);
                    m_gameLogic->Undo();
                    SoundManager::Instance()->PlayClickSound();
                }

                for(int i = 0; i < m_grid.size(); i++)
                {
                    HandleSquareEvent(*m_grid.at(i), i, mouseX, mouseY);
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

    auto isHistoryMode = m_gameLogic->GetHistoryMode();
    auto result = m_gameLogic->GetWinner();

    if(m_gameLogic->IsGameOver() && result.winner != NONE && isHistoryMode == false)
    {
        const auto startSquare = m_grid.at(m_gameLogic->GetWinner().line.first);
        const auto endSquare = m_grid.at(m_gameLogic->GetWinner().line.second);
        SDL_RenderDrawLine(m_renderer,
                           startSquare->GetSquareCenterX(),
                           startSquare->GetSquareCenterY(),
                           endSquare->GetSquareCenterX(),
                           endSquare->GetSquareCenterY());
    }

    // Shows image of which player won
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    if(result.winner == PLAYER_1 && isHistoryMode == false)
    {
        TextureManager::Instance()->DrawTexture("player1wins", 670, 50, 200, 31, m_renderer);
    }
    if(result.winner == PLAYER_2 && isHistoryMode == false)
    {
        TextureManager::Instance()->DrawTexture("player2wins", 670, 50, 200, 29, m_renderer);
    }
    if(m_gameLogic->IsGameOver() && m_gameLogic->GetWinner().winner == NONE && isHistoryMode == false)
    {
        TextureManager::Instance()->DrawTexture("DRAW", 690, 20, 178, 103, m_renderer);
    }

    if(isHistoryMode)
    {
        TextureManager::Instance()->DrawTexture("gameHistory", 480, 15, 380, 55, m_renderer);
    }

    // Draws image of which player's turn it is
    if(m_gameLogic->GetCurrentPlayer().GetId() == PLAYER_1 && isHistoryMode == false)
    {
        TextureManager::Instance()->DrawTexture("player1", 233, 7, 135, 22, m_renderer);
    }
    if(m_gameLogic->GetCurrentPlayer().GetId() == PLAYER_2 && isHistoryMode == false)
    {
        TextureManager::Instance()->DrawTexture("player2", 233, 7, 135, 22, m_renderer);
    }

    if(m_isInfoClicked)
    {
        TextureManager::Instance()->DrawTexture("text2", 650, 100, 250, 358, m_renderer);
    }
    else
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
    }

    if(isHistoryMode == true)
    {
        TextureManager::Instance()->DrawTexture("backArrow", 20, 550, 48, 48, m_renderer);
        TextureManager::Instance()->DrawTexture("forwardArrow", 540, 550, 48, 48, m_renderer);
    }
    if(m_gameLogic->IsGameOver())
    {
        TextureManager::Instance()->DrawTexture("historyButton", 930, 90, 64, 64, m_renderer);
    }
    TextureManager::Instance()->DrawTexture("grid2", 50, 50, 500, 501, m_renderer);
    TextureManager::Instance()->DrawTexture("info2", 930, 20, 60, 60, m_renderer);

    for(int i = 0; i < m_grid.size(); i++)
    {
        if(i == m_lastSquareHoveredId)
        {
            if(m_grid.at(i)->GetIsClicked() == false && !m_gameLogic->HasCurrentPlayerTurn())
            {
                auto shapeID = m_gameLogic->GetCurrentPlayer().GetShapeId();
                DrawTexture(shapeID, m_grid.at(i)->GetShapePosX(), m_grid.at(i)->GetShapePosY(), 100);
            }
        }
    }

    for(int i = 0; i < m_grid.size(); i++)
    {
        auto shapeID = m_grid.at(i)->GetSymbol();
        if(!shapeID.empty())
        {
            DrawTexture(shapeID, m_grid.at(i)->GetShapePosX(), m_grid.at(i)->GetShapePosY(), 255);
        }
    }

    SDL_RenderPresent(m_renderer);
}

void Game::HandleSquareEvent(Square& square, int index, int mouseX, int mouseY)
{
    if(square.IsInside(mouseX, mouseY) && !m_gameLogic->HasCurrentPlayerTurn() && square.GetIsClicked() == false)
    {
        m_gameLogic->SetGridPositionState(index);
        m_readyButton.setState(ACTIVE);
        m_undoButton.setState(ACTIVE);
        square.SetIsClicked(true);
        m_restartButton.setState(ACTIVE);
    }
    m_gameLogic->IsGameOver();
}

void Game::RestartGame()
{
    InitGrid();
    for(const auto& square : m_grid)
    {
        square->Clear();
    }
    m_restartButton.setState(INACTIVE);
    m_readyButton.setState(INACTIVE);
    m_undoButton.setState(INACTIVE);
    m_historyButton.setState(INACTIVE);
    m_gameLogic->Reset();
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
            m_lastSquareHoveredId = unused_Square;
        }
    }
}

void Game::DrawTexture(const std::string& shapeID, int x, int y, int alpha)
{
    SDL_SetTextureAlphaMod(TextureManager::Instance()->getTexture(shapeID), alpha);
    TextureManager::Instance()->DrawTexture(shapeID, x, y, Square::SHAPE_SIZE, Square::SHAPE_SIZE, m_renderer);
    SDL_SetTextureAlphaMod(TextureManager::Instance()->getTexture(shapeID), 255);
}
