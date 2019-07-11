#pragma once

#include <string>
#include <memory>
#include "Component.h"
#include "GameObject.h"

#define INCLUDE_SDL_MIXER
#include<SDL_include.h>

class Sound : public Component {
public:
    ~Sound();
    Sound(std::shared_ptr<GameObject> associated);
    Sound(std::shared_ptr<GameObject> associated, std::string file);
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
    void Update(int dt);
    void Render();
    bool Is(const std::string &type);
    /// Toca um som 1 vez. Retorna o war_ptr do GameObject criado para tal.
    static std::weak_ptr<GameObject> PlaySound(std::string file);
private:
    std::shared_ptr<Mix_Chunk> chunk; 
    int channel;
    std::string file;
};

