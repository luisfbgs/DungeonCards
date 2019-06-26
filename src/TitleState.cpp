#include <memory>
#include <cstdio>

#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "GameObject.h"
#include "StageState.h"
#include "ConfigState.h"
#include "GameData.h"
#include "Music.h"

void TitleState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress('w')) {
        if(this->selectedOption != 0) {
            this->selectedOption = Option(selectedOption - 1);
            this->selectSprite->associated.box.leftUp.y -= this->selectSprite->GetHeightS();
        }
    }
    if(input.IsKeyPress('s')) {
        if(this->selectedOption != 3) {
            this->selectedOption = Option(selectedOption + 1);
            this->selectSprite->associated.box.leftUp.y += this->selectSprite->GetHeightS();
        }
    }
    if(input.IsKeyPress(' ')) {
        switch(this->selectedOption) {
            case Play:
                Game::GetInstance().Push(new StageState());
                break;
            case Options:
                Game::GetInstance().Push(new ConfigState());
                break;
            case Quit:
                this->quitRequested = true;
                break;
        }
    }
    // Verificar se o usuário deseja fechar o jogo
    this->quitRequested |= input.QuitRequested();
}

void TitleState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    GameObject *bgGO = new GameObject();
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, IMG_PATH "title.png"));
    float bgScale = std::min((float)Game::GetInstance().GetWidth() / bgSprite->GetWidth(),
     (float)Game::GetInstance().GetHeight() / bgSprite->GetHeight());
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

    // Centraliza a camera no centro do fundo 
    float blackBarX = (float)Game::GetInstance().GetWidth() - bgSprite->GetWidthS();
    float blackBarY = (float)Game::GetInstance().GetHeight() - bgSprite->GetHeightS();
    Camera::pos = {-blackBarX / 2, -blackBarY / 2};

    GameObject *selectGO = new GameObject();
    this->selectSprite = std::shared_ptr<Sprite>(new Sprite(*selectGO, IMG_PATH "circle.png"));
    float selectScale = bgSprite->GetWidthS() / 11 / this->selectSprite->GetWidth();
    this->selectSprite->SetScale(selectScale, selectScale);
    selectGO->box.leftUp = {bgSprite->GetWidthS() / 5.3f, bgSprite->GetHeightS() / 1.9f};
    selectGO->AddComponent(this->selectSprite);
    this->AddObject(selectGO);
    // Toca musica do menu.
    this->music.Open(AUDIO_PATH "menu.ogg");
    this->music.Play(-1);
}

void TitleState::Render() {
    this->RenderArray();
}

void TitleState::Start() {
    this->selectedOption = Play;
    this->LoadAssets();
    this->UpdateArray(0);
}

void TitleState::Pause() {
    this->music.Stop();
}

void TitleState::Resume() {
    this->music.Play(-1);
}