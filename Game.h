#pragma once
#include <SDL_image.h>
#include "TextureManager.h"
#include <vector>
#include "Square.h"
#include "Button.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundManager.h"

enum GameState{
    P1WINS,
    P2WINS,
    DRAW,
    NOWINNER};

constexpr int UNUSED_SQUARE = -1;

class Game
{
public:
    Game();
    ~Game();
    bool init(const char* title, int xpos,
        int ypos, int width, int height, int flags);

    void Render();
    void HandleEvents();
    void Clean() const;
    bool IsRunning() const;
    void RestartGame();
    void UndoLast();
    void HandleSquareEvent(Square& square, int index, int mouseX, int mouseY);
    void InitGrid();
    void DrawTextureXorO(int shape, int x, int y);
    void HoverShowTexture(int x, int y);
    void AutoFillLastSquare();
    void IsSquareHovered(int mouseX, int mouseY);
    bool IsLastEmptySquare() const;
    bool CheckForWinner(SquareState state) const;
    bool IsGameOver();
    bool IsGameDraw() const;
    bool IsNoEmptySquares() const;


private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    GameState m_result = NOWINNER;
    int m_lastSquareHoveredId;
    bool m_isPlayerDone = true;
    bool m_running = true;
    bool m_isPlayerOneOrTwo = true;
    bool m_isInfoClicked = false;
    std::vector<int> m_drawnShapes;
    std::vector<Square*> m_grid;
    Button m_restartButton;
    Button m_readyButton;
    Button m_infoButton;
    Button m_undoButton;

};

//members start with m_
//private functions start with lowercase
//public functions start with uppercase
//camelcase
