#include "engine/scenes/scenes/Level2.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "engine/scenes/Text.h"

Level2::Level2() {

    SDL_Texture *backgroundTexture = Game::textures.at("track2.bmp");
    this->background = backgroundTexture;

    player = new Player(550, 685);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->texture = Game::textures.at("car-blue-regular.bmp");
    contents.push_back(player);

    // auto opponents = std::array<Opponent*, 3>{
    //     new Opponent(300, 100, 150, 50, 0.5),
    //     new Opponent(1400, 200),
    //     new Opponent(240, 700, 50, 100, 1.5)
    // };
    // for (auto opponent: opponents) {
    //     opponent->texture = Game::textures.at("car-red-regular.bmp");
    //     contents.push_back(opponent);
    // }

    // auto walls = std::array<Barrier*, 70>{};
    // for (auto wall: walls) {
    //     contents.push_back(wall);
    // }

    auto nitro1 = new Nitro(315, 111);
    auto nitro2 = new Nitro(852, 403);
    auto nitro3 = new Nitro(1467, 566);
    contents.push_back(nitro1);
    contents.push_back(nitro2);
    contents.push_back(nitro3);

    auto text = new Text(215, 815);
    text->setContent("fhdggfds");
    text->width = 1200;
    contents.push_back(text);
}