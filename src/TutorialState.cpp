#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "TutorialState.h"
#include "Stages.h"
#include "InputManager.h"
#include "Sound.h"
#include <iostream>
using std::cout;
using std::endl;
const std::string TutorialState::prefix("exemplo");

void TutorialState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> bgSprite = std::make_shared<Sprite>(
        bgGO, TUTORIAL_PATH + prefix + std::to_string(this->curr) + ".png");
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);
}

void TutorialState::Start() {
    this->min_max_fileNumber = Vec2Int(2, 9);
    this->curr = min_max_fileNumber.x;    
    this->LoadAssets();
}

void TutorialState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress(LEFT_ARROW_KEY) || input.IsKeyPress('a')){
        this->PrevScreen();
    }
    else if(input.IsKeyPress(RIGHT_ARROW_KEY) || input.IsKeyPress('d')) {
        this->NextScreen();
    }
    this->quitRequested |= input.IsKeyPress(ESCAPE_KEY) || input.QuitRequested();
}

void TutorialState::Render(){
    this->RenderArray();
}

void TutorialState::Pause(){
}

void TutorialState::Resume(){
}
void TutorialState::NextScreen() {
    int old = this->curr;
    this->curr = std::min(this->curr+1, this->min_max_fileNumber.y);
    if (this->curr != old) {
        this->_UpdateBackground();
    }
}

void TutorialState::PrevScreen() {
    int old = this->curr;
    this->curr = std::max(this->curr-1, this->min_max_fileNumber.x);
    if (this->curr != old) {
        this->_UpdateBackground();
    }
}

void TutorialState::_UpdateBackground() {
    this->LoadAssets();
    cout << "OPA!, foi aberto\n";
}