#include <memory>
#include <cstdio>

#include "TitleState.h"
#include "Game.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "GameObject.h"
#include "MapState.h"
#include "ConfigState.h"
#include "GameData.h"
#include "Music.h"

void TitleState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress('w') || input.IsKeyPress('a')) {
        if(this->selectedOption != 0) {
            this->selectedOption = Option(selectedOption - 1);
        }
    }
    if(input.IsKeyPress('s') || input.IsKeyPress('d')) {
        if(this->selectedOption != 3) {
            this->selectedOption = Option(selectedOption + 1);
        }
    }
    if(input.IsKeyPress(' ')) {
        switch(this->selectedOption) {
            case Continue:
                break;
            case NewGame:
                Game::GetInstance().Push(new MapState());
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
    std::shared_ptr<Sprite> bgSprite(new Sprite(*bgGO, IMG_PATH "/menu/fundo.png"));
    float bgScale = std::min((float)Game::width / bgSprite->GetWidth(),
     (float)Game::height / bgSprite->GetHeight());
    bgSprite->SetScale(bgScale, bgScale);
    Game::widthS = bgSprite->GetWidthS();
    Game::heightS = bgSprite->GetHeightS();
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);

    // Centraliza a camera no centro do fundo 
    float blackBarX = (float)Game::width - Game::widthS;
    float blackBarY = (float)Game::height - Game::heightS;
    Camera::pos = {-blackBarX / 2, -blackBarY / 2};

    GameObject *logoGO = new GameObject();
    std::shared_ptr<Sprite> logoSprite = std::shared_ptr<Sprite>(new Sprite(*logoGO, MENU_PATH "logo.png"));
    float logoScale = Game::widthS / 3.7f / logoSprite->GetWidth();
    logoSprite->SetScale(logoScale, logoScale);
    logoSprite->SetAngle(-10);
    logoGO->box.leftUp = {Game::widthS / 10.0f, Game::heightS / 10.0f};
    logoGO->AddComponent(logoSprite);
    this->AddObject(logoGO);

    GameObject *exitGO = new GameObject();
    std::shared_ptr<Sprite> exitSprite = std::shared_ptr<Sprite>(new Sprite(*exitGO, MENU_PATH "exit.png"));
    float optionScale = Game::widthS / 5 / exitSprite->GetWidth();
    exitSprite->SetScale(optionScale, optionScale);
    exitSprite->SetAngle(86);
    exitGO->AddComponent(exitSprite);
    exitGO->box.leftUp = {6.9f * Game::widthS / 10.0f, 3.7f * Game::heightS / 10.0f};
    this->AddObject(exitGO);

    GameObject *setupGO = new GameObject();
    std::shared_ptr<Sprite> setupSprite = std::shared_ptr<Sprite>(new Sprite(*setupGO, MENU_PATH "setup.png"));
    setupSprite->SetScale(optionScale, optionScale);
    setupSprite->SetAngle(38);
    setupGO->AddComponent(setupSprite);
    setupGO->box.leftUp = {6.3f * Game::widthS / 10.0f, 2 * Game::heightS / 10.0f};
    this->AddObject(setupGO);
  
    GameObject *newGameGO = new GameObject();
    std::shared_ptr<Sprite> newGameSprite = std::shared_ptr<Sprite>(new Sprite(*newGameGO, MENU_PATH "newGame.png"));
    newGameSprite->SetScale(optionScale, optionScale);
    newGameSprite->SetAngle(22);
    newGameGO->box.leftUp = {5 * Game::widthS / 10.0f, Game::heightS / 10.0f};
    newGameGO->AddComponent(newGameSprite);
    this->AddObject(newGameGO);

    GameObject *continueGO = new GameObject();
    std::shared_ptr<Sprite> continueSprite = std::shared_ptr<Sprite>(new Sprite(*continueGO, MENU_PATH "continue.png"));
    continueSprite->SetScale(optionScale, optionScale);
    continueSprite->SetAngle(-10);
    continueGO->box.leftUp = {4 * Game::widthS / 10.0f, Game::heightS / 10.0f};
    continueGO->AddComponent(continueSprite);
    this->AddObject(continueGO);
    
    this->lastOption = this->objectArray.size() - 1;
    // Toca musica do menu.
    this->music.Open(AUDIO_PATH "menu.ogg");
    this->music.Play(-1);
}

void TitleState::Render() {
    this->RenderArray();
    this->objectArray[this->lastOption - this->selectedOption]->Render();
}

void TitleState::Start() {
    this->selectedOption = Continue;
    this->LoadAssets();
    this->UpdateArray(0);
}

void TitleState::Pause() {
    this->music.Stop();
}

void TitleState::Resume() {
    this->music.Play(-1);
}