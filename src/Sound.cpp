#include<string>
#include <iostream>
#include "Sound.h"
#include "GameObject.h"
#include "Resources.h"
#include "Game.h"
#ifndef AUDIO_PATH
#define AUDIO_PATH "assets/audio/"
#endif
using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

Sound::~Sound() {
    std::cout << "this->file! " << this->file << std::endl;
}

Sound::Sound(std::shared_ptr<GameObject> associated) : Component(associated) {
    this->chunk = nullptr;
    this->channel = -1;
}

Sound::Sound(std::shared_ptr<GameObject> associated, std::string file) : Sound(associated) {
    this->file = file;
    this->Open(file);
}

void Sound::Play(int times) {
    if(this->chunk != nullptr && this->channel == -1) {
        this->channel = Mix_PlayChannel(-1, this->chunk.get(), times - 1);
    }
}

void Sound::Stop() {
    if(this->channel != -1) {
        Mix_HaltChannel(this->channel);
        this->channel = -1;
    }
}

void Sound::Open(std::string file) {
    this->chunk = Resources::GetSound(file.c_str());
}

bool Sound::IsOpen() {
    return this->chunk != nullptr;
}

void Sound::Update(int dt) {
    (void)dt;
    if ( ! Mix_Playing( this->channel ) ) {
        cout << "NDA NADA DNA\n";
        abort();
        this->associated->RequestDelete();
    }
    abort();
}

void Sound::Render() {}

bool Sound::Is(const std::string &type) {
    return type == "Sound";
}

weak_ptr<GameObject> Sound::PlaySound(std::string file) {
    std::shared_ptr<GameObject> GO = std::make_shared<GameObject>();
    std::shared_ptr<Sound> sound = make_shared<Sound>(GO, AUDIO_PATH + file );
    sound->Play();
    return Game::GetInstance().GetCurrentState().AddObject(GO);
}