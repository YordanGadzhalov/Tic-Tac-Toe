#pragma once
#include <SDL_image.h>
#include "TextureManager.h"
#include <vector>
#include "Square.h"
#include "Button.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundManager.h"

enum GameState{P1WINS, P2WINS, DRAW, NOWINNER};

class Game : Square {
public:
    Game();
	~Game();
	bool init(const char* title, int xpos,
		int ypos, int width, int height, int flags);

    void Render();
    void HandleEvents();
    void Clean();
    bool IsRunning() const;
    bool IsGameOver();
    void RestartGame();
    void UndoLast();
    void HandleSquareEvent(Square& square, int index, int mouseX, int mouseY);
    void InitGrid();
    void DrawTextureXorO(int shape, int x, int y);
    void HoverShowTexture(int x, int y);
    // void SquareIsHovered(int mouseX, int mouseY);

private:
    SDL_Window* m_window = NULL;
    SDL_Renderer* m_renderer = NULL;
    int m_squareCounter;
    GameState m_result = NOWINNER;
    bool m_isSquareHovered = false;
    int m_lastSquareHoveredId;
    bool m_isPlayerDone = true;
    bool m_running;
    bool m_isPlayerOneOrTwo = true;
    bool m_isInfoClicked = false;
    std::vector<int> m_drawnShapes;
    std::vector<Square*> m_grid;
    Button m_restartButton;
    Button m_readyButton;
    Button m_infoButton;
    Button m_undoButton;


    using Point = std::pair<int,int>;
    std::vector<Point> m_shapePos = {
        //offset
            {65, 65},
            {240, 65},
            {410, 65},
            {65, 235},
            {240, 235},
            {410, 235},
            {65, 410},
            {240, 410},
            {410, 410}
    };

};

//members start with m_
//private functions start with lowercase
//public functions start with uppercase
//camelcase
