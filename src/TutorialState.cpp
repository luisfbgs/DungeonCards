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
const std::string TutorialState::prefix("");

void TutorialState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> bgSprite = std::make_shared<Sprite>(
        bgGO, TUTORIAL_PATH + prefix + std::to_string(this->curr) + ".png"
    );
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);


    // Comum para as duas setas
    // Quer-se escala tal que caibam n setas empilhadas.]
    bool hasLeftArrow = this->curr > this->min_max_fileNumber.x;
    bool hasRightArrow = this->curr < this->min_max_fileNumber.y;
    if(hasLeftArrow || hasRightArrow) {
        int n = 8;
        // Verifica se precisa adicionar seta esquerda, e  adiciona-a caso necessario
        if(hasLeftArrow) {
            std::shared_ptr<GameObject> leftArrowGO = std::make_shared<GameObject>();
            std::shared_ptr<Sprite> leftArrowSprite = std::make_shared<Sprite>(
                leftArrowGO, TUTORIAL_PATH "arrow.png"
            );
            float arrowScale = (float)(Game::GetInstance().heightS)/(n * leftArrowSprite->GetHeight());
            leftArrowSprite->SetAngle(90);
            leftArrowGO->box.leftUp = {
                ((float)(Game::widthS)) * 0.1f,
                ((float)(Game::heightS)) * 0.83f
            };
            leftArrowSprite->SetScale(arrowScale,arrowScale);
            bgGO->AddComponent(leftArrowSprite);
            this->AddObject(leftArrowGO);
        }
        if (hasRightArrow) {
            std::shared_ptr<GameObject> rightArrowGO = std::make_shared<GameObject>();
            std::shared_ptr<Sprite> rightArrowSprite = std::make_shared<Sprite>(
                rightArrowGO, TUTORIAL_PATH "arrow.png"
            );
            float arrowScale = (float)(Game::GetInstance().heightS)/(n * rightArrowSprite->GetHeight());
            // Sprite eh o mesmo, muda soh a rotacao
            rightArrowSprite->SetAngle(-90);
            rightArrowGO->box.leftUp = {
                ((float)(Game::widthS)) * 0.87f,
                ((float)(Game::heightS)) * 0.83f
            };
            rightArrowSprite->SetScale(arrowScale,arrowScale);
            bgGO->AddComponent(rightArrowSprite);    
            this->AddObject(rightArrowGO);
        }

    }
}

void TutorialState::Start() {
    this->min_max_fileNumber = Vec2Int(1, 18);
    this->curr = min_max_fileNumber.x;    
    this->LoadAssets();
}

void TutorialState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress(LEFT_ARROW_KEY) || input.IsKeyPress('a')){
        if (this->curr > this->min_max_fileNumber.x)
            this->PrevScreen();
    }
    else if(input.IsKeyPress(RIGHT_ARROW_KEY) || input.IsKeyPress('d')) {
        if (this->curr < this->min_max_fileNumber.y)
            this->NextScreen();
    }
    this->quitRequested |= input.IsKeyPress(ESCAPE_KEY) || input.QuitRequested();
    GameData::quitAll |= input.QuitRequested();
}

void TutorialState::Render(){
    this->RenderArray();
}

void TutorialState::Pause(){
}

void TutorialState::Resume(){
}
void TutorialState::NextScreen() {
    this->curr += 1;
    this->_UpdateBackground();
}

void TutorialState::PrevScreen() {
    this->curr -= 1;
    this->_UpdateBackground();
}

void TutorialState::_UpdateBackground() {
    this->LoadAssets();
}