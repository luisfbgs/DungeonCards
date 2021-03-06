#include <string>
#include <assert.h>
#include "Sprite.h"
#include "Game.h"
#include "Camera.h"
#include "Vec2.h"
#include "Resources.h"
#include "Timer.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <iostream>

Sprite::~Sprite() {
}

Sprite::Sprite(std::shared_ptr<GameObject> associated, int frameCount, int frameTime, int msToSelfDestruct) : Component(associated) {
    this->scale = {1, 1};
    this->angle = 0;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->timeElapsed = 0;
    this->currentFrame = 0;
    this->msToSelfDestruct = msToSelfDestruct;
    this->hidden = false;
}

Sprite::Sprite(std::shared_ptr<GameObject> associated, const std::string &file, int frameCount, int frameTime, int msToSelfDestruct) : Component(associated) {
    this->scale = {1, 1};
    this->angle = 0;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->timeElapsed = 0;
    this->currentFrame = 0;
    this->msToSelfDestruct = msToSelfDestruct;
    this->hidden = false;
    this->Open(file);
}

void Sprite::Open(const std::string &file) {
    this->file = file;
    this->texture = Resources::GetImage(file.c_str());
    SDL_QueryTexture(this->texture.get(), nullptr, nullptr, &this->width, &this->height);
    this->width /= this->frameCount;
    this->SetClip(0, 0, this->width, this->height);
    this->associated->box = {this->associated->box.leftUp, (float)this->width, (float)this->height};
    this->associated->box.w *= this->scale.x;
    this->associated->box.h *= this->scale.y;
}

bool Sprite::IsOpen() {
    return this->texture != nullptr;
}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(float x, float y) {
    if(this->IsOpen() && !this->hidden) {
        x -= Camera::pos.x;
        y -= Camera::pos.y;
        SDL_Rect dstrect;
        dstrect.x = x;
        dstrect.y = y;
        dstrect.w = this->clipRect.w * this->scale.x;
        dstrect.h = this->clipRect.h * this->scale.y;
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture.get(), &this->clipRect, &dstrect, this->angle, nullptr, SDL_FLIP_NONE);
    }
}

void Sprite::Render() {
    this->Render(this->associated->box.leftUp.x, this->associated->box.leftUp.y);
}

void Sprite::Update(int dt) {
    this->timeElapsed += dt;
    if(this->msToSelfDestruct) {
        this->selfDestructCount.Update(dt);
        if(this->selfDestructCount.Get() >= this->msToSelfDestruct) {
            this->associated->RequestDelete();
            return;
        }
    }
    if(this->timeElapsed >= this->frameTime) {
        this->currentFrame++;
        this->currentFrame %= this->frameCount;
        this->timeElapsed -= this->frameTime;
    }
    this->SetClip(this->currentFrame * this->width, 0, this->width, this->height);
}

bool Sprite::Is(const std::string &type) {
    return type == "Sprite";
}

int Sprite::GetWidth() {
    return this->width;
}

int Sprite::GetHeight() {
    return this->height;
}

float Sprite::GetWidthS() {
    return this->width * this->scale.x;
}

float Sprite::GetHeightS() {
    return this->height * this->scale.y;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    this->associated->box.w /= this->scale.x;
    this->associated->box.h /= this->scale.y;
    this->scale = {scaleX, scaleY};
    this->associated->box.w *= this->scale.x;
    this->associated->box.h *= this->scale.y; 
}

Vec2 Sprite::GetScale() {
    return this->scale;
}

void Sprite::SetAngle(float angle) {
    this->angle = angle;
    this->associated->SetAngle(angle);
}

float Sprite::GetAngle() {
    return this->angle;
}

void Sprite::SetFrame(int frame) {
    this->currentFrame = frame;
}

void Sprite::SetFrameCount(int frameCount) {
    this->width *= this->frameCount;
    this->frameCount = frameCount;
    this->width /= this->frameCount;
}
