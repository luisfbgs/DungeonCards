#pragma once

#include <string>
#include <memory>
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#define INCLUDE_SDL
#include "SDL_include.h"

#define IMG_PATH "assets/img/"
#define PLAYER_PATH "assets/img/player/player"
#define ENEMY_PATH "assets/img/enemy/enemy"
#define EVENT_PATH "assets/img/event/event"
#define CURSOR_PATH "assets/img/cursor/"
#define TURN_PATH "assets/img/turn/"
#define MENU_PATH "assets/img/menu/"
#define COUNTER_PATH "assets/img/counter/"
#define STAGE_PATH "assets/img/stage/"
#define ANIMATION_PATH "assets/img/animation/"
#define LIFE_PATH "assets/img/life/life"
#define TIMER_PATH "assets/img/timer/"
#define SKILL_PATH "assets/img/skill/"

class Sprite : public Component{
public:
    Sprite();
    ~Sprite();
    Sprite(std::shared_ptr<GameObject> associated, const std::string &file, int frameCount = 1, int frameTime = 1, int msToSelfDestruct = 0);
    Sprite(std::shared_ptr<GameObject> associated, int frameCount = 1, int frameTime = 1, int msToSelfDestruct = 0);
    void SetScale(float scaleX, float scaleY); 
    Vec2 GetScale();
    void SetAngle(float angle);
    float GetAngle();
    void Open(const std::string &file);  
    void SetClip(int x, int y, int w, int h);
    void Render(float x, float y);
    void Render();
    void Update(int dt);
    bool Is(const std::string &type);
    int GetWidth();
    int GetHeight();
    float GetWidthS();
    float GetHeightS();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(int frameTime);
    bool hidden;

private:
    std::shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
    float angle;
    int frameCount;
    int currentFrame;
    int timeElapsed;
    int frameTime;
    int msToSelfDestruct;
    Timer selfDestructCount;
    std::string file;
};

