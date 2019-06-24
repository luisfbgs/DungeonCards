#include <vector>
#include <memory>
#include <cstdio>

#include "Game.h"
#include "GameObject.h"
#include "ConfigState.h"
#include "Text.h"
#include "InputManager.h"

void ConfigState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, IMG_PATH "blank.png"));
    float bgScale = std::min((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

    SDL_Color color = {0, 0, 0, 0};
    float posY = (Game::height - bgSprite->GetHeightS()) / 2;
    for(auto res : this->resolutionList) {
        GameObject *resolutionGO = new GameObject();
        std::shared_ptr<Text> resText(new Text(*resolutionGO, std::string("assets/font/Call me maybe.ttf"),
         bgSprite->GetHeightS() / 10, Text::TextStyle::SOLID, std::to_string(res.first) + "x" + std::to_string(res.second), color));
        resolutionGO->AddComponent(resText);
        resolutionGO->box.leftUp = {0.0f, posY};
        posY += Game::height / 10.0;
        this->AddObject(resolutionGO);
    }
}

void ConfigState::Update(int dt) {
    InputManager &input = InputManager::GetInstance();
    if(input.QuitRequested() || input.IsKeyPress(ESCAPE_KEY)) {
        this->quitRequested = true;
    }
}

void ConfigState::Render() {
    this->RenderArray();
}

void ConfigState::Start() {
    this->resolution = {Game::width, Game::height};
    this->resolutionList = {
        {640, 480},
        {800, 600},
        {1200, 800},
        {1366, 768},
        {1400, 900},
        {1600, 900},
        {1920, 1080}
    };

    this->LoadAssets();
}

void ConfigState::Pause() {
    
}

void ConfigState::Resume() {
    
}