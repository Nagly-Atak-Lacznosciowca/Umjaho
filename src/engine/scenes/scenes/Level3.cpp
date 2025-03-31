#include "engine/scenes/scenes/Level3.h"

#include <math.h>

#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/obstacles/Cone.h"
#include "game/entities/obstacles/SpeedBump.h"
#include "game/entities/obstacles/Water.h"
#include "game/entities/obstacles/Oil.h"
#include "game/entities/obstacles/Gate.h"
#include "game/entities/powerups/Nitro.h"
#include "engine/scenes/Text.h"
#include "game/entities/surfaces/Ice.h"

Level3::Level3() {

    SDL_Texture *backgroundTexture = Game::textures.at("track3.png");
    background = backgroundTexture;

    SDL_Color textColor = SDL_Color { 0, 0, 0 };
    // nitroCounter->setColor(textColor);

    // auto ice = new Ice(200, 276, 400, 400, 0, 0, Game::textures.at("ice.png"));
    // contents.push_back(ice);

    player = new Player(536, 657, 30, 60, 0, 1);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->SetTexture();
    contents.push_back(player);

    // auto opponents = std::array<Opponent*, 4>{
    //     new Opponent(335, 657, 30, 60, M_PI / -2),
    //     new Opponent(355, 712, 30, 60, M_PI / -2),
    //     new Opponent(435, 657, 30, 60, M_PI / -2),
    //     new Opponent(455, 712, 30, 60, M_PI / -2)
    // };
    // for (auto opponent: opponents) {
    //     opponent->texture = Game::textures.at("car-red-regular.png");
    //     contents.push_back(opponent);
    // }

    // auto walls = std::array<Barrier*, 70>{};
    // for (auto wall: walls) {
    //     contents.push_back(wall);
    // }

    auto cone = new Cone(1000, 500, 25, 25, 0, 0, Game::textures.at("cone.png"));
    auto cone2 = new Cone(1200, 500, 25, 25, 0, 0, Game::textures.at("cone.png"));
    auto speedbump = new SpeedBump(800, 300, 65, 18, 0, 0, Game::textures.at("speedbump.png"));
    auto water = new Water(600, 700, 100, 25, 0, 0, Game::textures.at("water.png"));
    auto oil = new Oil(1000, 700, 100, 25, 0, 0, Game::textures.at("oil.png"));
    auto gate = new Gate(180, 283, 7, 90, 0, 0, Game::textures.at("gate-closed.png"));

    contents.push_back(gate);
    contents.push_back(cone);
    contents.push_back(cone2);
    contents.push_back(speedbump);
    contents.push_back(water);
    contents.push_back(oil);

    auto nitro1 = new Nitro(315, 111);
    auto nitro2 = new Nitro(852, 403);
    auto nitro3 = new Nitro(1467, 566);
    contents.push_back(nitro1);
    contents.push_back(nitro2);
    contents.push_back(nitro3);
}