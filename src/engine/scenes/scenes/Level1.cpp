#include "engine/scenes/scenes/Level1.h"

#include <math.h>

#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "game/entities/powerups/PlaceObstacle.h"
#include "engine/scenes/Text.h"
#include "game/entities/surfaces/Curb.h"
#include "game/entities/surfaces/FinishLine.h"

Level1::Level1() {

    SDL_Texture *backgroundTexture = Game::textures.at("track1.png");
    // SDL_SetTextureScaleMode(backgroundTexture, SDL_SCALEMODE_NEAREST);
    background = backgroundTexture;

    player = new Player(808, 622, 40, 80, 0, 1);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->SetTexture();
    contents.push_back(player);

    // auto opponents = std::array<Opponent*, 4>{
    //     new Opponent(665, 622, 40, 80, M_PI / -2),
    //     new Opponent(549, 700, 40, 80, M_PI / -2),
    //     new Opponent(521, 622, 40, 80, M_PI / -2),
    //     new Opponent(693, 700, 40, 80, M_PI / -2)
    // };
    // for (auto opponent: opponents) {
    //     opponent->texture = Game::textures.at("car-red-regular.png");
    //     contents.push_back(opponent);
    // }

    auto walls = std::array<Barrier*, 63>{
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
        new Barrier(225, 602, 1040, 15, 0),
        new Barrier(200, 782, 1150, 15, 0),
        new Barrier(1385, 225, 15, 288, 0),
        new Barrier(1568, 194, 15, 350, 0), // 194!!! 194 Krowodrza Górka P+R - Os. Pod Fortem referencja!!!!
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
        new Barrier(590, 504, 550, 15, 0),
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

    auto surfaces = std::array<Surface*, 6>{
        new Curb(691, 468, 206, 40),
        new Curb(1008, 614, 206, 40),
        new Curb(666, 478, 50, 50, 0.78),
        new Curb(872, 478, 50, 50, 0.78),
        new Curb(984, 593, 50, 50, 0.78),
        new Curb(1189, 594, 50, 50, 0.78),
    };
    for (auto surface: surfaces) {
        contents.push_back(surface);
    }

    nitroPositions = {{315, 111}, {852, 403}, {1467, 566}, {904, 640}, {1357, 154}};


    auto place = new PlaceObstacle(100, 200);
    contents.push_back(place);

    auto finishLine = new FinishLine(450, 620, 20, 160);

    contents.push_back(finishLine);

    // auto text = new Text(215, 815);
    // text->setContent("fhdggfds");
    // text->width = 1200;
    // contents.push_back(text);
}
