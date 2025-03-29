#include "engine/scenes/scenes/Level1.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "engine/scenes/Text.h"

Level1::Level1() {
    this->background = Game::textures.at("level1.bmp");

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

    auto text = new Text(100, 100);
    text->setContent("fhdggfds");
    contents.push_back(text);
}