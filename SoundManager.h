#pragma once
#include "Game.h"
#include <iostream>
#include <map>

class SoundManager
{
public:
    static SoundManager* Instance()
    {
        if(m_Instance == nullptr)
        {
            m_Instance = new SoundManager();
            return m_Instance;
        }
        return m_Instance;
    }
    bool LoadChunk(const char* fileName, std::string id);
    bool LoadMusic(const char* fileName, std::string id);
    void PlaySound(std::string id, int loop, int ms, int volume);
    void PlayMusic(std::string id, int loop, int ms = 0);
    void ChangeVolume(int change);

    void PlayClickSound();

private:
    static SoundManager* m_Instance;
    std::map<std::string, Mix_Chunk*> m_Sfxs;
    std::map<std::string, Mix_Music*> m_Music;
    SoundManager();
    ~SoundManager();
};
