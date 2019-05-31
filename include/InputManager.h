#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <unordered_map>
#include <unordered_set>

#define INCLUDE_SDL
#include "SDL_include.h"

#define LEFT_ARROW_KEY     SDLK_LEFT
#define RIGHT_ARROW_KEY    SDLK_RIGHT
#define UP_ARROW_KEY       SDLK_UP
#define DOWN_ARROW_KEY     SDLK_DOWN
#define ESCAPE_KEY         SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON  SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

class InputManager {
public:
    void Update();
    bool IsKeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    int GetMouseX();
    int GetMouseY();
    bool QuitRequested();
    std::unordered_set<int> GetAllKeys();
    static InputManager& GetInstance();

private:
    std::unordered_set<int> pressedKeys;
    InputManager();
    ~InputManager();
    bool mouseState[6];
    int mouseUpdate[6];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
};

#endif