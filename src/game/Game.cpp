#include "game/Game.h"

Game::Game() : lastTick(0), deltaTime(0), renderer(Renderer()) {}

bool Game::checkSpeedControls() {
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S];
}

bool Game::checkTurnControls() {
    return SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]
        || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D];
}

// TO DO support rotated cars
bool Game::checkCarCollision(Car *car1, Car *car2) {
    return car1->x < car2->x + car2->length
        && car1->x + car1->length > car2->x
        && car1->y < car2->y + car2->width
        && car1->y + car1->width > car2->y;
}