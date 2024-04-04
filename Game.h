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

    void UpdateView(const GridState& state);
    void Clean() const;
    void RestartGame();
    void Render();

    void HandleEvents();
    void HandleSquareEvent(Square& square, int index, int mouseX, int mouseY);
    void DrawTexture(const std::string& shapeID, int x, int y, int alpha);

    bool IsRunning() const;
    void IsSquareHovered(int mouseX, int mouseY);

private:
    std::pair<std::string, std::string> m_selectedShapes;
    GameLogic* m_gameLogic{nullptr};
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    bool m_homeScreen = true;
    bool m_running = true;
    bool m_isXSelected = false;
    bool m_isCircleSelected = false;
    int m_lastSquareHoveredId;
    bool m_isInfoClicked = false;
    std::vector<Square*> m_grid;
    Button m_okButton;
    Button m_circleSymbolButton;
    Button m_xSymbolButton;
    Button m_forwardButton;
    Button m_backButton;
    Button m_historyButton;
    Button m_restartButton;
    Button m_readyButton;
    Button m_infoButton;
    Button m_undoButton;
};

//members start with m_
//private functions start with lowercase
//public functions start with uppercase
//camelcase
