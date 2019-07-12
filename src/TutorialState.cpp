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
        bgGO, TUTORIAL_PATH + prefix + std::to_string(this->curr) + ".png"
    );
    std::shared_ptr<GameObject> leftArrowGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> leftArrowSprite = std::make_shared<Sprite>(
        leftArrowGO, TUTORIAL_PATH "arrow.png"
    );
    std::shared_ptr<GameObject> rightArrowGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> rightArrowSprite = std::make_shared<Sprite>(
        rightArrowGO, TUTORIAL_PATH "arrow.png"
    );
    // Sprite eh o mesmo, muda soh a rotacao
    leftArrowSprite->SetAngle(90);
    rightArrowSprite->SetAngle(-90);
    float leftPadding = 0.1;
    leftArrowGO->box.leftUp = {
        ((float)(Game::widthS)) * 0.1,
        ((float)(Game::heightS)) * 0.83
    };
    rightArrowGO->box.leftUp = {
        ((float)(Game::widthS)) * 0.87,
        ((float)(Game::heightS)) * 0.83
    };

    // std::shared_ptr<Sprite> rightArrow = std::make_shared<Sprite>(
    //     bgGO, TUTORIAL_PATH "arrow.png"
    // );

    float bgScale = Game::widthS / bgSprite->GetWidth();

    bgSprite->SetScale(bgScale, bgScale);
    // Quer-se escala tal que caibam n setas empilhadas.]
    int n = 8;
    float arrowScale = (float)(Game::GetInstance().heightS)/(n * leftArrowSprite->GetHeight());

    leftArrowSprite->SetScale(arrowScale,arrowScale);
    rightArrowSprite->SetScale(arrowScale,arrowScale);

    // leftArrowSprite


    bgGO->AddComponent(bgSprite);
    bgGO->AddComponent(leftArrowSprite);
    bgGO->AddComponent(rightArrowSprite);
    
    this->AddObject(bgGO);
    this->AddObject(leftArrowGO);
    this->AddObject(rightArrowGO);

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