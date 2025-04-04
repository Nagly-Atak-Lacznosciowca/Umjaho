#include "engine/scenes/scenes/Level.h"
#include "game/Event.h"
#include "game/Game.h"
#include "engine/scenes/scenes/PauseMenu.h"
#include "game/entities/surfaces/Curb.h"
#include "game/entities/surfaces/Dirt.h"
#include "game/entities/surfaces/Ice.h"
#include "engine/scenes/Text.h"
#include "engine/scenes/scenes/Leaderboard.h"
#include "game/entities/surfaces/FinishLine.h"
#include <algorithm>
#include <format>

#include "game/entities/powerups/Nitro.h"
#include "game/entities/powerups/PlaceObstacle.h"



Level::Level() {
    // Nitro counter
	
	int *windowWidth = new int();
	int *windowHeight = new int();
	
	SDL_GetWindowSizeInPixels(Game::renderer.SDLWindow, windowWidth, windowHeight);
	
	const float batteryScale = 1.0f/3.0f;
	
	const auto batteryX = 100;
	const auto batteryY = -20;
	
	const auto batteryWidth = 550;
	const auto batteryHeight = 200;
	
    nitroCounter = new NitroBattery(batteryX, batteryY + (float)*windowHeight - batteryHeight * batteryScale, batteryWidth * batteryScale, batteryHeight * batteryScale, 0, 1, 0);


    currentLapLabel = new Text(285, 830, 0, 30, 0, 0, "Current lap:");
    currentLapText = new Text(425, 830, 0, 30);

    lapLabel = new Text(1375, 830, 0, 30, 0,0, "0/3");
	
	delete windowWidth;
	delete windowHeight;
	
    contents.push_back(nitroCounter);
    contents.push_back(currentLapText);
    contents.push_back(currentLapLabel);
    contents.push_back(lapLabel);
    temporaryObstacles.clear();
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

    if (nitroPlaceInterval > 0) {
        nitroPlaceInterval--;
    }
    else {
        nitroPlaceInterval = 1000;
        if (player->nitroCharges < 3) {
            auto index = rand()%nitroPositions.size();
            auto pos = nitroPositions.at(index);
            contents.push_back(new Nitro(pos.first, pos.second));
        }
    }

    if (powerupPlaceInterval > 0) {
        powerupPlaceInterval--;
    }
    else {
        powerupPlaceInterval = 1000;
        auto index = rand()%powerupPositions.size();
        auto pos = powerupPositions.at(index);
        contents.push_back(new PlaceObstacle(pos.first, pos.second));
    }

    player->move();
    ticks++;
    currentLapTime = ticks - lapStartTime;

    minutes = static_cast<int>(currentLapTime) / 6000;
    seconds = static_cast<int>(currentLapTime) / 100 - minutes * 60;
    milliseconds = static_cast<int>(currentLapTime) - seconds * 100 - minutes * 6000;


    oss << minutes << ':' << seconds << ':' << milliseconds;

    currentLapText->setContent(oss.str());

    oss.str("");
    oss.clear();

    for (const auto& element : contents) {
        if (element != player) {
            if (Game::checkElementCollision(player, element)) {
                player->collide(element);
                element->collide(player);
            }
        }
        for (const auto &bot : opponents) {
            if (Game::checkElementCollision(element, bot)) {
                element->collide(bot);
                bot->collide(element);
            }
        }
    }

    for (const auto &checkpoint: checkpoints) {
        if (Game::checkElementCollision(checkpoint, player)) {
            checkpoint->collide(player);
        }
        for (const auto &element : opponents) {
            if (Game::checkElementCollision(checkpoint, element)) {
                checkpoint->collide(element);
            }
        }
    }

    for (const auto& element : contents) {
        this->sceneElementLogic(element);
    }

    for (const auto &item: opponents) {
        item->update();
        if (Game::checkElementCollision(player, item)) {
            player->collide(item);
            item->collide(player);
        }
    }
    for (auto& obstacle : temporaryObstacles) {
        obstacle->countdownToDestroy();
        SDL_Log("obstacle destroyed in %d", obstacle->timeToDestroy);
        if (obstacle->timeToDestroy <= 0) {
            auto iterator = std::find(temporaryObstacles.begin(), temporaryObstacles.end(), obstacle);
            temporaryObstacles.erase(iterator);
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
            nitroCounter->setState(this->player->nitroCharges);
            break;
        }
        case Event::CUSTOM_EVENT_CAR_NITRO_USE: {
            if(!player->nitroActive && player->nitroCharges >= Car::NEEDED_CHARGES){
	            nitroCounter->setState(0);
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
            if(player->heldObstacle != nullptr){
                player->heldObstacle->x = (player->x + player->width/2 * SDL_sin(player->angle)) - 100 * SDL_sin(player->angle);
                player->heldObstacle->y = (player->y + player->height/2 * SDL_cos(player->angle)) - 100 * SDL_cos(player->angle);
                player->heldObstacle->angle = player->angle;
                this->temporaryObstacles.push_back(player->heldObstacle);
                SDL_Log("obstacle destroyed in %d", player->heldObstacle->timeToDestroy);
                this->contents.push_back(player->heldObstacle);
                player->heldObstacle = nullptr;
            }
        default:
            break;
    }
}

void Level::render() {
    Scene::render();
    // for (const auto &item: this->checkpoints) {
    //     item->render();
    // }
    SDL_Log("rendering %d", this->player->nextCheckpoint);
    checkpoints[player->nextCheckpoint]->render();
    for (const auto &item: this->opponents) {
        item->render();
    }
}

void Level::sceneElementLogic(SceneElement* element) {
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
