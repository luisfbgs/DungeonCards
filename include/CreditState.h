#pragma once
#include <memory>
#include <vector>

#include "State.h"
#include "GameObject.h"
#include "Vec2.h"

class CreditState : public State {
public:
    void LoadAssets();
    void Update(int dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
private:
    int pos;
    // Ideia: permitir navegar nas fotos dos programadores/artistas/músicos do game
    std::shared_ptr<GameObject> cursor;
    
    std::vector<std::string> artistas;
    std::vector<Vec2> artistasPos;

    std::vector<std::string> musicos;
    std::vector<Vec2> musicosPos;

    std::vector<std::string> programadores;
    std::vector<Vec2> programadoresPos;
};