#include "engine/scenes/scenes/Level1.h"
#include "game/Event.h"
#include "game/Game.h"

Level1::Level1() {

    player = new Player(10, 10);
    player->texture = Game::textures.at("car-blue-regular.bmp");
    SDL_Log("gfdgdsfg %d", player->texture->w);

    opponent = new Opponent(300, 200);
    opponent->texture = Game::textures.at("car-red-regular.bmp");

    contents.push_back(player);
    contents.push_back(opponent);
}

void Level1::logic() {

    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]) {
        auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_LEFT};
        SDL_PushEvent(&custom_event);
    }
    else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]) {
        auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT};
        SDL_PushEvent(&custom_event);
    }

    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]) {
        auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_FORWARD};
        SDL_PushEvent(&custom_event);
    }
    else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S]) {
        auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD};
        SDL_PushEvent(&custom_event);
    }

    if (!Game::checkSpeedControls()) {
        player->decelerate();
    }
    if (!Game::checkTurnControls()) {
        player->straighten();
    }

    player->move();

    if (Game::checkElementCollision(player, opponent)) {
        SDL_Log("Car collision detected");
    }
}

void Level1::handleEvent(SDL_Event* event) {
    switch (event->type) {
        case Event::CUSTOM_EVENT_CAR_ROTATE_LEFT: {
            player->turnLeft();
            break;
        }
        case Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT: {
            player->turnRight();
            break;
        }

        case Event::CUSTOM_EVENT_CAR_MOVE_FORWARD: {
            player->accelerate();
            break;
        }
        case Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD: {
            if (player->speed > 0) player->brake();
            else player->reverse();
            break;
        }
        default:
            break;
    }
}



