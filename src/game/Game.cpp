#include "game/Game.h"

Game::Game() : lastTick(0), deltaTime(0), renderer(Renderer()) {}

bool Game::checkSteering() {
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S];
}
