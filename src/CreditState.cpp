#include "CreditState.h"
#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Stages.h"
#include "InputManager.h"
#include "Sound.h"
#include "Text.h"

void CreditState::LoadAssets() {
    // Cria background e ajusta pro tamanho da janela
    std::shared_ptr<GameObject> bgGO = std::make_shared<GameObject>();
    std::shared_ptr<Sprite> bgSprite = std::make_shared<Sprite>(bgGO, IMG_PATH "MenuFundo.png");
    float bgScale = Game::widthS / bgSprite->GetWidth();
    bgSprite->SetScale(bgScale, bgScale);
    bgGO->AddComponent(bgSprite);
    this->AddObject(bgGO);


    float backgroundHeightS = bgSprite->GetHeightS();
    float posX = 6;
    float posY = (Game::height - backgroundHeightS) / 2;
    SDL_Color color = {200, 123, 50, 0};
    posY = this->LoadNames( this->artistas, color, posX, posY, backgroundHeightS );
    color = {0x84, 0x89, 0x80, 0};
    posY = this->LoadNames( this->programadores, color, posX, posY, backgroundHeightS );
    color = {0x1f, 0x89, 0x80, 0};
    this->LoadNames( this->musicos, color, posX, posY,  backgroundHeightS );

    posX = 70;
    posY = (Game::height - backgroundHeightS) / 2;
    std::vector<std::string> tmp = {
        "", ""
    };
    color = {0xc8, 0x7b, 0x32, 0}; tmp[0] = "Artistas";
    posY = this->LoadNames( tmp, color, posX, posY, backgroundHeightS );
    color = {0x84, 0x89, 0x80, 0}; tmp[0] = "Programadores";
    posY = this->LoadNames( tmp, color, posX, posY, backgroundHeightS );
    color = {0x1f, 0x89, 0x80, 0}; tmp[0] = "Musicos";
    this->LoadNames( tmp, color, posX, posY,  backgroundHeightS );
}

// Cada nome tem altura de 1 dehcimo do background.
float CreditState::LoadNames(std::vector<std::string>& whichOnes, SDL_Color color, float posX, float posY, float backgroundHeightS) {
    for(unsigned i = 0; i < whichOnes.size(); i++) {
        std::shared_ptr<GameObject> contribuidorGO(new GameObject());
        std::shared_ptr<Text> constribuidorText(
            new Text(contribuidorGO,
                        std::string("assets/font/Call_me_maybe.ttf"),
                        backgroundHeightS / 10,
                        Text::TextStyle::SOLID,
                        whichOnes[i],
                        color)
            );
        contribuidorGO->AddComponent(constribuidorText);
        contribuidorGO->box.leftUp = { ((float)Game::widthS / 100) * posX, posY};
        posY += backgroundHeightS / 10.0;
        this->AddObject(contribuidorGO);
    }
    return posY;
}

void CreditState::Start() {
    this->artistas = {
        "Renata Rinaldi",
        "Vitor Dias"
    };
    this->programadores = {
        "Leonardo Maffei",
        "Luis Gebrim"
    };
    this->musicos = {
        "Luis Guilherme",
        "Vinicius Sales"
    };
    this->artistasPos = {
        {3, 8},
        {3, 6}
    };
    this->LoadAssets();
}

void CreditState::Update(int dt) {
    (void)dt;
    InputManager &input = InputManager::GetInstance();
    this->quitRequested |= input.IsKeyPress(ESCAPE_KEY) || input.QuitRequested();
    GameData::quitAll |= input.QuitRequested();
}

void CreditState::Render(){
    this->RenderArray();
}

void CreditState::Pause(){
}

void CreditState::Resume(){
}