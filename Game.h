#pragma once
#include <SDL_image.h>
#include "TextureManager.h"
#include <vector>
#include "Square.h"
#include "Button.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundManager.h"
#include "GameLogic.h"

constexpr int unused_Square = -1;

class Game
{
public:
    Game();
    ~Game();
    bool init(const char* title, int xpos,
              int ypos, int width, int height, int flags);
    void InitGrid();
    void InitGameLogic();

    void UpdateView();
    void Render();
    void HandleEvents();
    void Clean() const;
    bool IsRunning() const;
    void RestartGame();
    void HandleSquareEvent(Square& square, int index, int mouseX, int mouseY);
    void DrawTexture(const std::string& shapeID, int x, int y, int alpha);
    void IsSquareHovered(int mouseX, int mouseY);

private:
    GameLogic* m_gameLogic{nullptr};
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_running = true;
    int m_lastSquareHoveredId;
    bool m_isInfoClicked = false;
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
