#pragma once
#include "Game.h"
#include <iostream>
#include <map>

using namespace std;

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
    bool LoadChunk(const char* fileName, string id);
    bool LoadMusic(const char* fileName, string id);
    void PlaySound(string id, int loop, int ms, int volume);
    void PlayMusic(string id, int loop, int ms = 0);
    void ChangeVolume(int change);

    void PlayClickSound();

private:
    static SoundManager* m_Instance;
    map<string, Mix_Chunk*> m_Sfxs;
    map<string, Mix_Music*> m_Music;
    SoundManager();
    ~SoundManager();
};
