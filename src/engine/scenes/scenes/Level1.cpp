#include "engine/scenes/scenes/Level1.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entity/obstacles/Barrier.h"
#include "game/entity/powerups/Nitro.h"

Level1::Level1() {

    player = new Player(10, 10);
    player->texture = Game::textures.at("car-blue-regular.bmp");
    SDL_Log("gfdgdsfg %d", player->texture->w);
    contents.push_back(player);

    auto opponents = std::array<Opponent*, 3>{
        new Opponent(300, 100, 150, 50, 0.5),
        new Opponent(1400, 200),
        new Opponent(240, 700, 50, 100, 1.5)
    };
    for (auto opponent: opponents) {
        opponent->texture = Game::textures.at("car-red-regular.bmp");
        contents.push_back(opponent);
    }

    auto walls = std::array<Barrier*, 3>{
        new Barrier(10,500, 700, 8),
        new Barrier(900,200, 300, 300, 0.6),
        new Barrier(1250,500, 50, 500, -1.2)
    };
    for (auto wall: walls) {
        contents.push_back(wall);
    }
    auto nitro = new Nitro(100, 50);
    contents.push_back(nitro);
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
        SDL_Log("kurwaaaaaaaaaa");
    }

    SDL_Log("accel: %f maxSpeed: %f", player->acceleration, player->maxSpeed);

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



