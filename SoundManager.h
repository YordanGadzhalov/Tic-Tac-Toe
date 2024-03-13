#pragma once
#include <iostream>
#include <map>
#include "Game.h"

using namespace std;

class SoundManager {

public:
    static SoundManager* Instance() {
        if (m_Instance == 0) {
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
    void PauseOrPlay();
    void ChangeVolumeSfx(string id, int c);
    void SetMusicPosition(double pos);
    void PlayClickSound();
    void PlayMainMusic();

private:
    static SoundManager* m_Instance;
    map<string, Mix_Chunk*> m_Sfxs;
    map<string, Mix_Music*> m_Music;
    SoundManager();
    ~SoundManager();
};
