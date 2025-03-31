#include "engine/scenes/scenes/Level3.h"

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

    currentLapLabel->setColor({0,0,0});
    currentLapText->setColor({0,0,0});
    lapLabel->setColor({0,0,0});

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

    Ice* surfaces[] = {
        new Ice(685, 455, 415, 125),
        new Ice(1080, 470, 120, 135, -0.3),
        new Ice(1113, 572, 454, 177),
        new Ice(1440, 400, 130, 171),
        new Ice(1192, 529, 43, 43)
    };

    for (const auto& surface : surfaces) {
        contents.push_back(surface);
    }

    contents.push_back(gate);
    contents.push_back(cone);
    contents.push_back(cone2);
    contents.push_back(speedbump);
    contents.push_back(water);
    contents.push_back(oil);

    nitroPositions = {{249, 305}, {1455, 670}, {1249, 524}, {69, 478}};

}