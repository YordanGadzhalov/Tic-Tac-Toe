#pragma once
#include "Game.h"
#include <map>
#include <string>
using namespace std;

class TextureManager
{
public:
    void LoadImages(SDL_Renderer* ren);

    bool LoadTexture(const char* fileName, string id, SDL_Renderer* ren);

    void DrawTexture(string id, int x, int y, int width, int height, SDL_Renderer* ren);

    static TextureManager* Instance()
    {
        if(m_instance == 0)
        {
            m_instance = new TextureManager();
            return m_instance;
        }
        return m_instance;
    }

    SDL_Texture* getTexture(string id);

private:
    map<string, SDL_Texture*> m_textureMap;
    TextureManager()
    {
    }
    static TextureManager* m_instance;
};
