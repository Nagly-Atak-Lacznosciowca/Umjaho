#include "engine/scenes/scenes/Level2.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "engine/scenes/Text.h"
#include "game/entities/surfaces/Dirt.h"

Level2::Level2() {

    SDL_Texture *backgroundTexture = Game::textures.at("track2.bmp");
    background = backgroundTexture;

//    auto dirt = new Dirt(200, 276, 400, 400, 0, 0, Game::textures.at("dirt.bmp"));
//    contents.push_back(dirt);

    player = new Player(550, 685);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->SetTexture();
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

    Dirt* surfaces[] = {
            new Dirt(35, 500, 120, 100),
            new Dirt(50, 575, 120, 100, 0.2),
            new Dirt(83, 450, 120, 100, -1),
            new Dirt(160, 430, 120, 100),
            new Dirt(250, 370, 120, 100, -0.8),
            new Dirt(271, 180, 120, 200),

            new Dirt(290, 100, 120, 100, -0.4),
            new Dirt(370, 50, 370, 100),
            new Dirt(705, 100, 140, 100, 0.5),

            new Dirt(730, 180, 170, 350),
            new Dirt(780, 480, 150, 100, 1),
            new Dirt(890, 485, 200, 130),


    };
    for (const auto& surface: surfaces){
        contents.push_back(surface);
    }

    auto nitro1 = new Nitro(315, 111);
    auto nitro2 = new Nitro(852, 403);
    auto nitro3 = new Nitro(1467, 566);
    contents.push_back(nitro1);
    contents.push_back(nitro2);
    contents.push_back(nitro3);
}