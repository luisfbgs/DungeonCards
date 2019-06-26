#include "Game.h"
#include "GameObject.h"
#include "Sprite.h"
#include "MapState.h"
#include "StageState.h"
#include "InputManager.h"

void MapState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, IMG_PATH "map.png"));
    float bgScale = std::min((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

    this->cursor = new GameObject();
    std::shared_ptr<Sprite> cursorSprite(new Sprite(*this->cursor, CURSOR_PATH "map.png"));
    float cursorScale = std::min((float)Game::GetInstance().GetWidth() / 10.0 / cursorSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / 10.0 / cursorSprite->GetHeight());
    cursorSprite->SetScale(cursorScale, cursorScale);
    this->cursor->AddComponent(cursorSprite);
    this->AddObject(this->cursor);
}

void MapState::Start() {
    this->stages = {
        {3, 8},
        {6, 7}
    };
    this->pos = 0;
    this->LoadAssets();
    this->cursor->box.leftUp = stages[0];
    this->cursor->box.leftUp.x *= this->cursor->box.w;
    this->cursor->box.leftUp.y *= this->cursor->box.h;
}

void MapState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress(' ')) {
        Game::GetInstance().Push(new StageState());
    }
    this->quitRequested |= input.IsKeyPress(ESCAPE_KEY) || input.QuitRequested();
}

void MapState::Render(){
    this->RenderArray();
}

void MapState::Pause(){
}

void MapState::Resume(){
}