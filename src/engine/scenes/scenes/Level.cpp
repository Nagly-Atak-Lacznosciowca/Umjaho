#include "engine/scenes/scenes/Level.h"
#include "game/Event.h"
#include "game/Game.h"
#include "engine/scenes/scenes/PauseMenu.h"

void Level::logic() {
	
    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_LEFT});
    }
    else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT});
    }

    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_FORWARD});
    }
    else if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN] || SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD});
    }

    if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_NITRO});
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
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
				Game::sceneManager.pushScene(new PauseMenu());
			break;
        default:
            break;
    }
}