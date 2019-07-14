#pragma once
#include <memory>
#include <vector>

#include "State.h"
#include "GameObject.h"
#include "Vec2.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"


class CreditState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
    float LoadNames(std::vector<std::string>& whichOnes, SDL_Color color, float posX, float posY, float backgroundHeightS );
private:
    // Ideia: permitir navegar nas fotos dos programadores/artistas/músicos do game
    
    std::vector<std::string> artistas;
    std::vector<Vec2> artistasPos;

    std::vector<std::string> musicos;
    std::vector<Vec2> musicosPos;

    std::vector<std::string> programadores;
    std::vector<Vec2> programadoresPos;
};