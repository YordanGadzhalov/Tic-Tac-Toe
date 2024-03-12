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
