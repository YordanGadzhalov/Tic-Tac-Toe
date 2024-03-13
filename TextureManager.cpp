#include "TextureManager.h"

bool TextureManager::LoadTexture(const char* fileName,
    string id, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(fileName); //Load the image

    if (tempSurface == 0)
        return false; // something went wrong


    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);


    if (tex != 0) {
        m_textureMap[id] = tex;  // Insert the texture into the map to have a list of all images
        return true;
    }

    return false; // something went wrong
}


void TextureManager::LoadImages(SDL_Renderer* ren){
    Instance()->LoadTexture("assets/gameover.png", "gameover", ren);
    Instance()->LoadTexture("assets/grid2.png", "grid2", ren);
    Instance()->LoadTexture("assets/Ximage2.png", "Ximage2", ren);
    Instance()->LoadTexture("assets/undo1.png", "undo1", ren);
    Instance()->LoadTexture("assets/undo2.png", "undo2", ren);
    Instance()->LoadTexture("assets/circle2.png", "circle2", ren);
    Instance()->LoadTexture("assets/ButtonActive.png", "ButtonActive", ren);
    Instance()->LoadTexture("assets/ButtonClicked.png", "restartButtonClicked", ren);
    Instance()->LoadTexture("assets/ButtonInactive.png", "restartButtonInactive", ren);
    Instance()->LoadTexture("assets/info2.png", "info2", ren);
    Instance()->LoadTexture("assets/ReadyButtonStatic.png", "ReadyStatic", ren);
    Instance()->LoadTexture("assets/ReadyButtonClicked.png", "ReadyClicked", ren);
    Instance()->LoadTexture("assets/text2.png", "text2", ren);
    Instance()->LoadTexture("assets/player1.png", "player1", ren);
    Instance()->LoadTexture("assets/player2.png", "player2", ren);
    Instance()->LoadTexture("assets/player1wins.png", "player1wins", ren);
    Instance()->LoadTexture("assets/player2wins.png", "player2wins", ren);
    Instance()->LoadTexture("assets/DRAW.png", "DRAW", ren);
}



void TextureManager::DrawTexture(string id, int x, int y,
    int width, int height, SDL_Renderer* ren,
    SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(ren, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);

}


TextureManager* TextureManager::m_instance = 0;
