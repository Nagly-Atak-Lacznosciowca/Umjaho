#include "engine/scenes/scenes/Level1.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "game/entities/powerups/PlaceObstacle.h"
#include "engine/scenes/Text.h"

Level1::Level1() {

    SDL_Texture *backgroundTexture = Game::textures.at("track1.bmp");
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

    auto walls = std::array<Barrier*, 70>{
        new Barrier(20, 276, 13, 400),
        new Barrier(24, 220, 15, 64, -0.23),
        new Barrier(47, 144, 15, 84, -0.45),
        new Barrier(93, 77, 15, 84, -0.76),
        new Barrier(150, 30, 15, 84, -1.02),
        new Barrier(221, -4, 15, 84, -1.265),
        new Barrier(250, 17, 120, 15, 0),
        new Barrier(396, -10, 15, 100, 1.245),
        new Barrier(476, 31, 15, 100, 0.94),
        new Barrier(544, 102, 15, 100, 0.58),
        new Barrier(585, 190, 15, 100, 0.27),
        new Barrier(592, 258, 15, 60, 0.05),
        new Barrier(599, 307, 25, 25, 0.78),
        new Barrier(612, 322, 468, 15, 0),
        new Barrier(1076, 311, 60, 15, 0.35),
        new Barrier(1119, 280, 60, 15, 0.91),
        new Barrier(1157+3, 191-3, 15, 80, -0.078),
        new Barrier(200, 292, 15, 305, 0),
        new Barrier(225, 602, 736, 15, 0),
        new Barrier(1013, 640, 203, 15, 0),
        new Barrier(200, 782, 1150, 15, 0),
        new Barrier(1385, 225, 15, 288, 0),
        new Barrier(1568, 194, 15, 350, 0), // 194!!! 194 Krowodrza Górka P+R - Os. Pod Fortem referencja!!!!
        new Barrier(943, 504, 162, 15, 0),
        new Barrier(698, 467, 196, 15, 0),
        new Barrier(971, 571, 70, 70, 0.92),
        new Barrier(1191, 571, 70, 70, -0.92),
        new Barrier(658, 481, 70, 70, -0.92),
        new Barrier(867, 481, 70, 70, 0.92),
        new Barrier(1559, 528, 15, 80, -0.23),
        new Barrier(1531, 601, 15, 80, -0.51),
        new Barrier(1492, 653, 15, 80, -0.76),
        new Barrier(1432, 704, 15, 80, -1.02),
        new Barrier(1362, 737, 15, 80, -1.24),
        new Barrier(1336, 258, 15, 80, -0.23),
        new Barrier(1307, 331, 15, 80, -0.51),
        new Barrier(1264, 385, 15, 80, -0.76),
        new Barrier(1208, 430, 15, 80, -1.02),
        new Barrier(1136, 460, 15, 80, -1.30),
        new Barrier(29, 625, 15, 80, 0.36),
        new Barrier(67, 688, 15, 80, 0.70),
        new Barrier(110, 723, 15, 70, 1.02),
        new Barrier(156, 745, 15, 70, 1.30),
        new Barrier(29+395, 625-278, 15, 80, 0.36),
        new Barrier(67+395, 688-278, 15, 80, 0.70),
        new Barrier(110+395-5, 723-278, 15, 70, 1.0),
        new Barrier(156+395, 745-278, 15, 70, 1.30),
        new Barrier(590, 504, 100, 15, 0),
        new Barrier(1179, 115, 15, 80, -0.36),
        new Barrier(1216, 52, 15, 80, -0.70),
        new Barrier(1261, 20, 15, 70, -1.0),
        new Barrier(1303, -3, 15, 70, -1.30),
        new Barrier(1553, 115, 15, 80, 0.36),
        new Barrier(1524, 59, 15, 80, 0.70),
        new Barrier(1484, 24, 15, 70, 1.0),
        new Barrier(1430, -3, 15, 70, 1.30),
        new Barrier(1300, 20, 150, 15, 0),
        new Barrier(208, 581, 30, 30, -0.72),
        new Barrier(1337, 550, 15, 70, -0.92),
        new Barrier(1375, 508, 15, 60, -0.4),
        new Barrier(1286, 577, 15, 60, -1.45),
        new Barrier(1349, 216, 15, 45, -0.15),
        new Barrier(1356, 204, 25, 20, 0.7),
        new Barrier(1373, 198, 15, 35, 0.8),

        new Barrier(208, 246, 15, 50, -0.37),
        new Barrier(239, 203, 15, 57, -0.90),
        new Barrier(284, 186, 15, 50, -1.4),
        new Barrier(328, 188, 15, 50, 1.3),
        new Barrier(371, 208, 15, 60, 0.87),

        new Barrier(401, 252, 15, 100, 0.2),




        
        // new Barrier(10,500, 700, 8),
        // new Barrier(900,200, 300, 300, 0.6),
        // new Barrier(1250,500, 50, 500, -1.2)
    };
    for (auto wall: walls) {
        contents.push_back(wall);
    }

    auto nitro1 = new Nitro(315, 111);
    auto nitro2 = new Nitro(852, 403);
    auto nitro3 = new Nitro(1467, 566);

    auto place = new PlaceObstacle(100, 200, new Barrier(0,0));
    contents.push_back(nitro1);
    contents.push_back(nitro2);
    contents.push_back(nitro3);
    contents.push_back(place);

    auto text = new Text(215, 815);
    text->setContent("fhdggfds");
    text->width = 1200;
    contents.push_back(text);
}