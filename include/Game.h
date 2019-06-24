#pragma once

#include <string>
#include <memory>
#include <stack>

#define INCLUDE_SDL
#include "SDL_include.h"

#include "State.h"
#include "Board.h"

class Game {
public:
	~Game();
	static Game& GetInstance();
	int GetDeltaTime();
	void Run();
	int GetWidth();
	int GetHeight();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	void Push (State* state);
	static int width;
	static int height;

private:
	Game(const std::string &title, int width, int height);
	void CalculateDeltaTime();
	static Game* instance;
	int frameStart;
	int dt;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	std::stack<std::unique_ptr<State>> stateStack;
};

