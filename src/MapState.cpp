#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "MapState.h"
#include "Stages.h"
#include "InputManager.h"

void MapState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, IMG_PATH "map.png"));
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

    this->cursor = new GameObject();
    std::shared_ptr<Sprite> cursorSprite(new Sprite(*this->cursor, CURSOR_PATH "map.png"));
    float cursorScale = Game::heightS / 10 / cursorSprite->GetHeight();
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
        if(pos == 0) {
            Stages::InitStage1();
        }
        else if(GameData::stagesBeated >= 1){
            Stages::InitStage2();
        }
    }
    if(input.IsKeyPress('d')){
        this->pos = std::min((int)this->stages.size() - 1, pos + 1);
    }
    if(input.IsKeyPress('a')){
        this->pos = std::max(0, pos - 1);
    }

    this->cursor->box.leftUp = stages[this->pos];
    this->cursor->box.leftUp.x *= this->cursor->box.w;
    this->cursor->box.leftUp.y *= this->cursor->box.h;

    this->quitRequested |= input.IsKeyPress(ESCAPE_KEY) || input.QuitRequested();
}

void MapState::Render(){
    this->RenderArray();
}

void MapState::Pause(){
}

void MapState::Resume(){
}