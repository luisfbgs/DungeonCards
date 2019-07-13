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
#include "Sound.h"
#include "CreditState.h"
#include <iostream>
#include "TutorialState.h"
#include "GameOverState.h"
#include "CongratsState.h"

using std::make_shared;

void TitleState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyPress('w') || input.IsKeyPress('a')) {
        Sound::PlaySound("cima.ogg");
        if(this->selectedOption != 0) {
            // Da uma abaixadinha na opção desselecionada 
            GameObject *topOption = this->objectArray[this->lastOption - this->selectedOption].get();
            topOption->box.leftUp += Vec2(0, Game::heightS / 15).Rotate(topOption->GetAngle());
           
            this->selectedOption = Option(selectedOption - 1);
           
            // Da uma levantadinha na opção selecionada 
            topOption = this->objectArray[this->lastOption - this->selectedOption].get();
            topOption->box.leftUp -= Vec2(0, Game::heightS / 15).Rotate(topOption->GetAngle());
           
            this->selectSprite->SetAngle(topOption->GetAngle());
            this->selectSpriteGO->box = topOption->box;
        }
    }
    if(input.IsKeyPress('s') || input.IsKeyPress('d')) {
        Sound::PlaySound("baixo.ogg");
        if(this->selectedOption != 3) {
            // Da uma abaixadinha na opção desselecionada 
            GameObject *topOption = this->objectArray[this->lastOption - this->selectedOption].get();
            topOption->box.leftUp += Vec2(0, Game::heightS / 15).Rotate(topOption->GetAngle());
           
            this->selectedOption = Option(selectedOption + 1);
           
            // Da uma levantadinha na opção selecionada 
            topOption = this->objectArray[this->lastOption - this->selectedOption].get();
            topOption->box.leftUp -= Vec2(0, Game::heightS / 15).Rotate(topOption->GetAngle());
           
            this->selectSprite->SetAngle(topOption->GetAngle());
            this->selectSpriteGO->box = topOption->box;
        }
    }
    if(input.IsKeyPress(' ')) {
        switch(this->selectedOption) {
            case Continue:
                break;
            case NewGame:
                GameData::playersCount = 4;
                Game::GetInstance().Push(make_shared<MapState>());
                break;
            case Options:
                Game::GetInstance().Push(make_shared<ConfigState>());
                break;
            case Quit:
                this->quitRequested = true;
                break;
        }
        if (!this->quitRequested) {
            Sound::PlaySound("confirmar.ogg");
        }
    }
    else if (input.IsKeyPress('c')) {
        Game::GetInstance().Push(make_shared<CreditState>());
    }
    else if (input.IsKeyPress('t')) {
        Game::GetInstance().Push(make_shared<TutorialState>());
    }
    else if (input.IsKeyPress('g')) {
        Game::GetInstance().Push(make_shared<GameOverState>());
    }
    else if (input.IsKeyPress('v')) {
        Game::GetInstance().Push(make_shared<CongratsState>());
    }
    // Verificar se o usuário deseja fechar o jogo
    this->quitRequested |= input.QuitRequested() || input.IsKeyPress(ESCAPE_KEY);
}


void TitleState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO(new GameObject());
    std::shared_ptr<Sprite> bgSprite(new Sprite(bgGO, IMG_PATH "/menu/fundo.png"));
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

    std::shared_ptr<GameObject> logoGO(new GameObject());
    std::shared_ptr<Sprite> logoSprite = std::shared_ptr<Sprite>(new Sprite(logoGO, MENU_PATH "logo.png"));
    float logoScale = Game::widthS / 3.7f / logoSprite->GetWidth();
    logoSprite->SetScale(logoScale, logoScale);
    logoSprite->SetAngle(-10);
    logoGO->box.leftUp = {Game::widthS / 10.0f, Game::heightS / 10.0f};
    logoGO->AddComponent(logoSprite);
    this->AddObject(logoGO);

    std::shared_ptr<GameObject> exitGO(new GameObject());
    std::shared_ptr<Sprite> exitSprite = std::shared_ptr<Sprite>(new Sprite(exitGO, MENU_PATH "exit.png"));
    float optionScale = Game::widthS / 5 / exitSprite->GetWidth();
    exitSprite->SetScale(optionScale, optionScale);
    exitSprite->SetAngle(80);
    exitGO->AddComponent(exitSprite);
    exitGO->box.leftUp = {6.9f * Game::widthS / 10.0f, 3.7f * Game::heightS / 10.0f};
    this->AddObject(exitGO);

    std::shared_ptr<GameObject> setupGO(new GameObject());
    std::shared_ptr<Sprite> setupSprite = std::shared_ptr<Sprite>(new Sprite(setupGO, MENU_PATH "setup.png"));
    setupSprite->SetScale(optionScale, optionScale);
    setupSprite->SetAngle(38);
    setupGO->AddComponent(setupSprite);
    setupGO->box.leftUp = {6.3f * Game::widthS / 10.0f, 2 * Game::heightS / 10.0f};
    this->AddObject(setupGO);
  
    std::shared_ptr<GameObject> newGameGO(new GameObject());
    std::shared_ptr<Sprite> newGameSprite = std::shared_ptr<Sprite>(new Sprite(newGameGO, MENU_PATH "newGame.png"));
    newGameSprite->SetScale(optionScale, optionScale);
    newGameSprite->SetAngle(22);
    newGameGO->box.leftUp = {5 * Game::widthS / 10.0f, Game::heightS / 10.0f};
    newGameGO->AddComponent(newGameSprite);
    this->AddObject(newGameGO);

    std::shared_ptr<GameObject> continueGO(new GameObject());
    std::shared_ptr<Sprite> continueSprite = std::shared_ptr<Sprite>(new Sprite(continueGO, MENU_PATH "continue.png"));
    continueSprite->SetScale(optionScale, optionScale);
    continueSprite->SetAngle(-10);
    continueGO->box.leftUp = {4 * Game::widthS / 10.0f, Game::heightS / 10.0f};
    continueGO->AddComponent(continueSprite);
    this->AddObject(continueGO);
    
    this->lastOption = this->objectArray.size() - 1;
    
    // Da uma levantadinha na opção selecionada 
    GameObject *topOption = this->objectArray[this->lastOption - this->selectedOption].get();
    topOption->box.leftUp -= Vec2(0, Game::heightS / 15).Rotate(topOption->GetAngle());
    
    // Coloca o sprite do seletor de opção na posição correta
    this->selectSpriteGO = std::shared_ptr<GameObject>(new GameObject());
    this->selectSprite = std::shared_ptr<Sprite>(new Sprite(selectSpriteGO, MENU_PATH "select.png"));
    float selectScale = continueSprite->GetHeightS() / this->selectSprite->GetHeightS();
    this->selectSprite->SetScale(selectScale, selectScale);
    this->selectSprite->SetAngle(continueGO->GetAngle());
    this->selectSpriteGO->AddComponent(this->selectSprite);
    this->selectSpriteGO->box = continueGO->box;
    this->AddObject(this->selectSpriteGO);
    
    // Toca musica do menu.
    this->music.Open(AUDIO_PATH "menu.ogg");
    this->music.Play(-1);
}

void TitleState::Render() {
    this->RenderArray();       
    this->objectArray[this->lastOption - this->selectedOption]->Render();
    this->selectSprite->Render();
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