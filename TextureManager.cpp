#include "TextureManager.h"

bool TextureManager::LoadTexture(const char* fileName, std::string id, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(fileName); // Load the image

    if(tempSurface == 0)
        return false;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);

    if(tex != 0)
    {
        m_textureMap[id] = tex; // Insert the texture into the map to have a list of all images
        return true;
    }

    return false;
}

void TextureManager::LoadImages(SDL_Renderer* ren)
{
    LoadTexture("assets/gameover.png", "gameover", ren);
    LoadTexture("assets/grid2.png", "grid2", ren);
    LoadTexture("assets/Ximage2.png", "Ximage2", ren);
    LoadTexture("assets/undo1.png", "undo1", ren);
    LoadTexture("assets/undo2.png", "undo2", ren);
    LoadTexture("assets/circle2.png", "circle2", ren);
    LoadTexture("assets/ButtonActive.png", "ButtonActive", ren);
    LoadTexture("assets/ButtonClicked.png", "restartButtonClicked", ren);
    LoadTexture("assets/ButtonInactive.png", "restartButtonInactive", ren);
    LoadTexture("assets/info2.png", "info2", ren);
    LoadTexture("assets/ReadyButtonStatic.png", "ReadyStatic", ren);
    LoadTexture("assets/ReadyButtonClicked.png", "ReadyClicked", ren);
    LoadTexture("assets/text2.png", "text2", ren);
    LoadTexture("assets/player1.png", "player1", ren);
    LoadTexture("assets/player2.png", "player2", ren);
    LoadTexture("assets/player1wins.png", "player1wins", ren);
    LoadTexture("assets/player2wins.png", "player2wins", ren);
    LoadTexture("assets/DRAW.png", "DRAW", ren);
    LoadTexture("assets/backArrow.png", "backArrow", ren);
    LoadTexture("assets/forwardArrow.png", "forwardArrow", ren);
    LoadTexture("assets/historyButton.png", "historyButton", ren);
    LoadTexture("assets/gameHistory.png", "gameHistory", ren);
}

void TextureManager::DrawTexture(std::string id, int x, int y, int width, int height, SDL_Renderer* ren)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(ren, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

SDL_Texture* TextureManager::getTexture(std::string id)
{
    return m_textureMap[id];
}

TextureManager* TextureManager::m_instance = 0;
