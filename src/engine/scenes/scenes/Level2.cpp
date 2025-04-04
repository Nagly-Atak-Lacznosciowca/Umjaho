#include "engine/scenes/scenes/Level2.h"

#include <math.h>

#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "engine/scenes/Text.h"
#include "game/entities/obstacles/Cone.h"
#include "game/entities/obstacles/Oil.h"
#include "game/entities/obstacles/SpeedBump.h"
#include "game/entities/obstacles/Water.h"
#include "game/entities/surfaces/Dirt.h"
#include "game/entities/MiddleLiner.h"
#include "game/entities/StraightMaster.h"

Level2::Level2() {
    SDL_Texture *backgroundTexture = Game::textures.at("track2.png");
    background = backgroundTexture;


    auto walls = std::array {
        new Barrier(233, 638, 304, 15), // 304 Wieliczka Miasto!!!!!!!!!!
        new Barrier(200, 778, 1000, 15),
        new Barrier(918, 613, 200, 40),
        new Barrier(664, 226, 62, 261),
        new Barrier(1259, 615, 158, 68),
        new Barrier(1258, 440, 110, 47),
        new Barrier(897, 613, 236, 25),
        new Barrier(475, 151, 141, 15),
        new Barrier(912, 463, 221, 24),
        new Barrier(1432, 291, 15, 119),
        new Barrier(1573, 277, 21, 171),
        new Barrier(1170, 219, 202, 20),
        new Barrier(1129, 70, 274, 22),
        new Barrier(894, 199, 18, 268),
        new Barrier(438, 10, 230, 15),
        new Barrier(681, 629, 45, 80),
        new Barrier(396, 227, 20, 157),
        new Barrier(217, 203, 53, 137),
        new Barrier(156, 379, 35, 43),
        new Barrier(4, 533, 28, 114),
        new Barrier(943, 253, 26, 83),
        new Barrier(508, 557, 45, 79),
        new Barrier(27, 593, 15, 80, 0.23),
        new Barrier(51, 650, 15, 80, 0.56),
        new Barrier(101, 700, 15, 80, 0.96),
        new Barrier(162, 732, 15, 80, 1.23),
        new Barrier(1565, 422, 15, 80, -0.23),
        new Barrier(1537, 479, 15, 80, -0.56),
        new Barrier(1485, 534, 15, 80, -0.96),
        new Barrier(1418, 570, 15, 80, -1.23),
        new Barrier(388, 354, 15, 80, -0.23),
        new Barrier(360, 411, 15, 80, -0.56),
        new Barrier(308, 469, 15, 80, -0.93),
        new Barrier(241, 502, 15, 80, -1.23),
        new Barrier(265, 128, 15, 80, -0.29),
        new Barrier(297, 70, 15, 80, -0.62),
        new Barrier(347, 17, 15, 80, -0.93),
        new Barrier(404, -10, 15, 80, -1.23),
        new Barrier(964, 191, 15, 80, -0.29),
        new Barrier(996, 133, 15, 80, -0.62),
        new Barrier(1046, 80, 15, 80, -0.93),
        new Barrier(1103, 53, 15, 80, -1.23),
        new Barrier(1561, 200, 15, 80, 0.29),
        new Barrier(1528, 131, 15, 80, 0.62),
        new Barrier(1483, 87, 15, 80, 0.93),
        new Barrier(1423, 57, 15, 80, 1.23),
        new Barrier(876, 122, 15, 80, 0.45),
        new Barrier(783, 18, 15, 100, 1.01),
        new Barrier(847, 71, 15, 100, 0.70),
        new Barrier(700, -20, 15, 100, 1.28),
        new Barrier(968, 326, 15, 80, 0.4),
        new Barrier(998, 375, 15, 80, 0.78),
        new Barrier(1043, 402, 15, 80, 1.2),
        new Barrier(726, 651, 15, 80, 0.4),
        new Barrier(764, 693, 15, 80, 0.84),
        new Barrier(835, 721, 15, 100, 1.27),
        new Barrier(1242, 367, 15, 80, 0.4),
        new Barrier(1205, 312, 15, 80, 0.78),
        new Barrier(1157, 283, 15, 80, 1.2),
        new Barrier(1243, 656, 15, 80, -0.4),
        new Barrier(1215, 696, 15, 80, -0.78),
        new Barrier(1168, 729, 15, 80, -1.2),
        new Barrier(666, 656, 15, 80, -0.4),
        new Barrier(638, 696, 15, 80, -0.78),
        new Barrier(591, 729, 15, 80, -1.2),
        new Barrier(32, 463, 15, 80, -0.4),
        new Barrier(63, 420, 15, 80, -0.78),
        new Barrier(116, 384, 15, 80, -1.28),
        new Barrier(552, 527, 15, 80, -0.4),
        new Barrier(583, 484, 15, 80, -0.78),
        new Barrier(636, 448, 15, 80, -1.23),
        new Barrier(243, 334, 15, 59, -0.45),
        new Barrier(207, 373, 15, 59, 0.45 - 1.5707),
        new Barrier(1420, 399, 15, 59, -0.45),
        new Barrier(1384, 438, 15, 59, 0.45 - 1.5707),
        new Barrier(1420, 241, 15, 57, 0.45),
        new Barrier(1387, 210, 15, 57, -0.45 + 1.5707),
        new Barrier(1105, 245, 15, 57, -0.45),
        new Barrier(1139, 210, 15, 57, 0.45 - 1.5707),
        new Barrier(1097, 282, 32, 32, -0.4),
        new Barrier(1103, 440, 15, 45, 1.3),
        new Barrier(408, 176, 15, 57, -0.45),
        new Barrier(446, 141, 15, 57, 0.45 - 1.5707),
        new Barrier(692, 170, 15, 65, 0.68),
        new Barrier(640, 132, 15, 75, -0.3 + 1.5707),
        new Barrier(203, 601, 15, 60, 1.07),
        new Barrier(170, 562, 15, 60, 0.4),
        new Barrier(182, 527, 15, 60, -1.3),
        new Barrier(694, 615, 15, 20, 0),
    };
    for (auto wall: walls) {
        contents.push_back(wall);
    }

    auto surfaces = std::array<Surface*, 12>{
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
        new Checkpoint(26, 830, 600, 5, 170, -1, 0, nullptr),
        new Checkpoint(27, 725, 625, 170, 5, 0, 0, nullptr),
        new Checkpoint(28, 700, 488, 5, 125, 0, 0, nullptr),
        new Checkpoint(29, 555, 625, 125, 5, 0, 0, nullptr),
        new Checkpoint(30, 540, 653, 5, 125, 0, 0, nullptr),


    };

    player = new Player(534, 657);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->SetTexture();

    this->checkpoints.insert(this->checkpoints.begin(), checkpoints);


    player->totalCheckpoints = this->checkpoints.size();


    auto obstacles = std::array<Obstacle*, 8>{
        new Cone(868, 205),
        new Cone(868, 235),
        new Cone(868, 265),
        new Oil(649, 495),
        new Oil(1151, 101),
        new Water(1400,464, 50, 30, 0.5),
        new SpeedBump(1080, 676, 60, 15, M_PI/2),

        new Barrier(690, 548, 250, 15, -0.68),
    };

    obstacles[7]->isCollidable = false;
    for (const auto& obstacle: obstacles){
        contents.push_back(obstacle);
    }

    nitroPositions = {{1100, 395}, {778, 521}, {532, 38}, {69, 478}};
    powerupPositions = {{275, 317}, {1080, 566}, {1106, 328}, {610, 507}};

    contents.push_back(player);


    auto bot = new MiddleLiner(333, 657, *this->player, this->opponents, this->contents, this->checkpoints);
    auto bot2 = new StraightMaster(353, 712, *this->player, this->opponents, this->contents, this->checkpoints);
    auto bot3 = new StraightMaster(436, 657, *this->player, this->opponents, this->contents, this->checkpoints);
    auto bot4 = new MiddleLiner(456, 721, *this->player, this->opponents, this->contents, this->checkpoints);

    bot->rayLength = 120;
    bot4->rayLength = 120;

    opponents.push_back(bot);
    opponents.push_back(bot2);
    opponents.push_back(bot3);
    opponents.push_back(bot4);

    opponents[0]->texture = Game::textures.at("car-purple-regular.png");
    opponents[0]->player = *player;
    opponents[0]->checkpoints = this->checkpoints;
    opponents[0]->totalCheckpoints = this->checkpoints.size();
    opponents[0]->isCollidable = true;
    opponents[0]->angle = SDL_PI_F / -2;

    opponents[1]->texture = Game::textures.at("car-orange-regular.png");
    opponents[1]->player = *player;
    opponents[1]->checkpoints = this->checkpoints;
    opponents[1]->totalCheckpoints = this->checkpoints.size();
    opponents[1]->isCollidable = true;
    opponents[1]->angle = SDL_PI_F / -2;

    opponents[2]->texture = Game::textures.at("car-red-regular.png");
    opponents[2]->player = *player;
    opponents[2]->checkpoints = this->checkpoints;
    opponents[2]->totalCheckpoints = this->checkpoints.size();
    opponents[2]->isCollidable = true;
    opponents[2]->angle = SDL_PI_F / -2;

    opponents[3]->texture = Game::textures.at("car-yellow-regular.png");
    opponents[3]->player = *player;
    opponents[3]->checkpoints = this->checkpoints;
    opponents[3]->totalCheckpoints = this->checkpoints.size();
    opponents[3]->isCollidable = true;
    opponents[3]->angle = SDL_PI_F / -2;
}