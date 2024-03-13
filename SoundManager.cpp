#include "SoundManager.h"
#include <iostream>

using namespace std;

SoundManager::SoundManager() {
    Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 4096);
}

SoundManager::~SoundManager(){
    for (auto& pair : m_Music) {
        Mix_FreeMusic(pair.second);
    }
    m_Music.clear();

    for (auto& pair : m_Sfxs) {
        Mix_FreeChunk(pair.second);
    }
    m_Sfxs.clear();
}

bool SoundManager::LoadChunk(const char* fileName, string id) {
    Mix_Chunk* chunk = Mix_LoadWAV(fileName);
    if (chunk == 0) {
        cout << "Could not load sfx" << Mix_GetError() << endl;
        return false;
    }
    m_Sfxs[id] = chunk;
    return true;
}


bool SoundManager::LoadMusic(const char* fileName, string id) {
    Mix_Music* music = Mix_LoadMUS(fileName);
    if (music == 0) {
        cout << "Could not load music" << Mix_GetError() << endl;
        return false;
    }
    m_Music[id] = music;
    return true;
}


void SoundManager::PlayMusic(string id, int loop, int ms) {
    Mix_FadeInMusic(m_Music[id], loop, ms);
}

void SoundManager::PlaySound(string id, int loop, int ms, int volume) {
    Mix_VolumeChunk(m_Sfxs[id], volume);
    Mix_FadeInChannel(-1, m_Sfxs[id], loop, ms);
}

void SoundManager::ChangeVolume(int c) {
    int currentVolume = Mix_VolumeMusic(-1);
    cout << currentVolume << " " << Mix_VolumeMusic(-1) << endl;
    currentVolume += c;
    Mix_VolumeMusic(currentVolume);
}

void SoundManager::PlayClickSound() {
    SoundManager::Instance()->PlaySound("clicksound", 0, 0, 5);
}



SoundManager* SoundManager::m_Instance = 0;
