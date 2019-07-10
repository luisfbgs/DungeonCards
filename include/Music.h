#pragma once

#include <string>
#include <memory>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define AUDIO_PATH "assets/audio/"

class Music {
public:
    Music();
    Music(std::string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 0);
    void Open(std::string file);
    bool IsOpen();
    bool IsPlaying() {
        return Mix_PlayingMusic();
    }
private:
    std::shared_ptr<Mix_Music> music;
};



