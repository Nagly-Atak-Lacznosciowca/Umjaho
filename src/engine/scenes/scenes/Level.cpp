#include "engine/scenes/scenes/Level.h"
#include "game/Event.h"
#include "game/Game.h"

void Level::logic() {

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

    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE]) {
        auto custom_event = SDL_Event{Event::CUSTOM_EVENT_CAR_NITRO};
        SDL_PushEvent(&custom_event);
    }

    if (!Game::checkSpeedControls()) {
        player->decelerate();
    }
    if (!Game::checkTurnControls()) {
        player->straighten();
    }
    if(player->nitroTimer > 0){
        player->accelerate();
        player->nitroTimer--;
        if(player->nitroTimer == 0){
            player->maxSpeed /= Car::NITRO_MULTIPLIER;
            player->acceleration /= Car::NITRO_MULTIPLIER;
            player->nitroActive = false;
            player->nitroCharges -= Car::NEEDED_CHARGES;
        }
    }

    player->move();

    for (const auto& element : contents) {
        if (element != player) {
            if (Game::checkElementCollision(player, element)) {
                player->collide(element);
                element->collide(player);
            }
        }
    }
}

void Level::handleEvent(SDL_Event* event) {
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
        case Event::CUSTOM_EVENT_CAR_NITRO: {
            if(!player->nitroActive && player->nitroCharges >= Car::NEEDED_CHARGES){
                player->acceleration *= Car::NITRO_MULTIPLIER;
                player->maxSpeed *= Car::NITRO_MULTIPLIER;
                player->nitroTimer = Car::NITRO_TIME;
                player->nitroActive = true;
            }
            break;
        }
        default:
            break;
    }
}