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

    // auto opponents = std::array<Bot*, 3>{
    //     new Bot(300, 100, 150, 50, 0.5),
    //     new Bot(1400, 200),
    //     new Bot(240, 700, 50, 100, 1.5)
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

    auto checkpoints = {
        new Checkpoint(0, 282, 653, 5, 123, 0, 0, nullptr),
        new Checkpoint(1, 195, 645, 5, 123, -0.3, 0, nullptr),
        new Checkpoint(2, 30, 574, 123, 5, 0, 0, nullptr),
        new Checkpoint(3, 152, 424, 5, 123, 0.2, 0, nullptr),
        new Checkpoint(4, 241, 410, 5, 123, 0.5, 0, nullptr),
        new Checkpoint(5, 270, 350, 123, 5, 0, 0, nullptr),
        new Checkpoint(6, 270, 210, 123, 5, 0, 0, nullptr),
        new Checkpoint(7, 385, 60, 5, 135, 0.6, 0, nullptr),
        new Checkpoint(8, 450, 30, 5, 123, 0, 0, nullptr),
        new Checkpoint(9, 685, 35, 5, 135, 0, 0, nullptr),

        new Checkpoint(10, 725, 223, 170, 5, 0, 0, nullptr),
        new Checkpoint(11, 727, 475, 170, 5, 0, 0, nullptr),
        new Checkpoint(12, 904, 485, 5, 125, 0, 0, nullptr),
        new Checkpoint(13, 1265, 490, 5, 125, 0, 0, nullptr),
        new Checkpoint(14, 1401, 480, 5, 125, 0.4, 0, nullptr),
        new Checkpoint(15, 1445, 420, 125, 5, 0, 0, nullptr),
        new Checkpoint(16, 1443, 275, 125, 5, 0, 0, nullptr),
        new Checkpoint(17, 1470, 141, 5, 125, -1, 0, nullptr),
        new Checkpoint(18, 1385, 95, 5, 125, 0, 0, nullptr),
        new Checkpoint(19, 1145, 96, 5, 125, 0, 0, nullptr),
        new Checkpoint(20, 1035, 194, 5, 130, 1, 0, nullptr),
        new Checkpoint(21, 1106, 323, 5, 130, -0.3, 0, nullptr),
        new Checkpoint(22, 1135, 465, 125, 5, 0, 0, nullptr),
        new Checkpoint(23, 1135, 635, 125, 5, 0, 0, nullptr),
        new Checkpoint(24, 1125, 648, 5, 125, 0.3, 0, nullptr),
        new Checkpoint(25, 904, 650, 5, 125, 0, 0, nullptr),
        new Checkpoint(26, 725, 625, 170, 5, 0, 0, nullptr),
        new Checkpoint(27, 700, 488, 5, 125, 0, 0, nullptr),
        new Checkpoint(28, 830, 600, 5, 170, -1, 0, nullptr),
        new Checkpoint(29, 555, 625, 125, 5, 0, 0, nullptr),
        new Checkpoint(30, 540, 653, 5, 125, 0, 0, nullptr),


    };
    this->checkpoints.insert(this->checkpoints.begin(), checkpoints);

    player.totalCheckpoints = this->checkpoints.size();

    for (const auto& checkpoint: checkpoints) {
        contents.push_back(checkpoint);
    }

    auto nitro1 = new Nitro(315, 111);
    auto nitro2 = new Nitro(852, 403);
    auto nitro3 = new Nitro(1467, 566);
    contents.push_back(nitro1);
    contents.push_back(nitro2);
    contents.push_back(nitro3);
}