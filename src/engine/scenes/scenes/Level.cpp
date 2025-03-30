#include "engine/scenes/scenes/Level.h"
#include "game/Event.h"
#include "game/Game.h"
#include "engine/scenes/scenes/PauseMenu.h"
#include "game/entities/surfaces/Curb.h"
#include "game/entities/surfaces/Dirt.h"
#include "game/entities/surfaces/Ice.h"
#include "engine/scenes/Text.h"

Level::Level() {
    // Nitro counter label
    nitroCounterLabel = new Text(200, 815, 0, 50, 0, 0, "Nitro charges: ");
    contents.push_back(nitroCounterLabel);

    // Nitro counter
    nitroCounter = new Text(490, 815, 0, 50, 0, 0, "0/3");
    contents.push_back(nitroCounter);
}

void Level::logic() {
	
	const auto keyboardState = SDL_GetKeyboardState(nullptr);
	
    if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_LEFT});
    }
    else if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_ROTATE_RIGHT});
    }

    if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_FORWARD});
    }
    else if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_MOVE_BACKWARD});
    }

    if (keyboardState[SDL_SCANCODE_SPACE]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_NITRO_USE});
    }

    if (keyboardState[SDL_SCANCODE_E] || keyboardState[SDL_SCANCODE_X]) {
        SDL_PushEvent(new SDL_Event{Event::CUSTOM_EVENT_CAR_PLACE_OBSTACLE});
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

    // For each car check if it's on dirt or ice and use the appropriate method
    for (const auto& element : contents) {
        if (auto car = dynamic_cast<Car*>(element)) {
            bool onCurb = false, onDirt = false, onIce = false;
            for (const auto& surface : contents) {
                if (auto curb = dynamic_cast<Curb*>(surface)) {
                    if (Game::checkSurfaceIntersection(car, curb)) {
                        onCurb = true;
                    }
                }
                if (auto dirt = dynamic_cast<Dirt*>(surface)) {
                    if (Game::checkSurfaceIntersection(car, dirt)) {
                        onDirt = true;
                    }
                }
                if (auto ice = dynamic_cast<Ice*>(surface)) {
                    if (Game::checkSurfaceIntersection(car, ice)) {
                        onIce = true;
                    }
                }
            }
            if (!onCurb) car->leaveCurb();
            if (!onDirt) car->leaveDirt();
            if (!onIce) car->leaveIce();
        }
    }
}

void Level::handleEvent(SDL_Event* event) {
	Scene::handleEvent(event);
	
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
        case Event::CUSTOM_EVENT_CAR_NITRO_COLLECT: {
            nitroCounter->setContent(std::to_string(player->nitroCharges) + "/3");
            break;
        }
        case Event::CUSTOM_EVENT_CAR_NITRO_USE: {
            if(!player->nitroActive && player->nitroCharges >= Car::NEEDED_CHARGES){
                nitroCounter->setContent("0/3");
                player->acceleration *= Car::NITRO_MULTIPLIER;
                player->maxSpeed *= Car::NITRO_MULTIPLIER;
                player->nitroTimer = Car::NITRO_TIME;
                player->nitroActive = true;
            }
            break;
        }
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
				SDL_PushEvent(new SDL_Event {
					.user = {
						.type = Event::CUSTOM_EVENT_PUSH_SCENE,
						.data1 = new PauseMenu()
					}
				});
			break;

        case Event::CUSTOM_EVENT_CAR_PLACE_OBSTACLE:
            if(player->holdingObstacle != nullptr){
                player->holdingObstacle->x = (player->x + player->width/2 * SDL_sin(player->angle)) - 100 * SDL_sin(player->angle);
                player->holdingObstacle->y = (player->y + player->height/2 * SDL_cos(player->angle)) - 100 * SDL_cos(player->angle);
                player->holdingObstacle->angle = player->angle;
                this->contents.push_back(player->holdingObstacle);
                player->holdingObstacle = nullptr;
            }
        default:
            break;
    }
}