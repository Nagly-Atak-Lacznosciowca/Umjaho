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
#include "game/entities/surfaces/Curb.h"
#include "game/entities/surfaces/Ice.h"
#include "game/entities/MiddleLiner.h"
#include "game/entities/StraightMaster.h"

Level3::Level3() {

    SDL_Texture *backgroundTexture = Game::textures.at("track3.png");
    background = backgroundTexture;

    SDL_Color textColor = SDL_Color { 0, 0, 0 };
    // nitroCounter->setColor(textColor);

    auto walls = std::array {
        new Barrier(233, 638, 570, 15),
        new Barrier(203, 777, 700, 15),
        new Barrier(1216, 743, 1502-1216, 15),
        new Barrier(1568, 137, 15, 648-137),
        new Barrier(1239, 85, 40, 441-85),
        new Barrier(942, 366, 1114-942, 455-366),
        new Barrier(942, 579, 1100-942, 775-579),
        new Barrier(582, 580, 817-582, 637-580),
        new Barrier(592, 373, 817-592, 456-373),
        new Barrier(518, 153, 533-518, 376-153),
        new Barrier(1405, 174, 1443-1405, 597-174),
        new Barrier(1254, 583, 1422-1254, 620-583),
        new Barrier(16, 160, 15, 615-160),
        new Barrier(234, 369, 381-234, 653-369),
        new Barrier(158, 383, 394-158, 580-383),
        new Barrier(205, 173, 393-205, 279-172),
        new Barrier(234, 155, 377-234, 173-155),
        new Barrier(205, 12, 403-205, 15),
        new Barrier(23, 583, 15, 80, 0.23),
        new Barrier(50, 646, 15, 80, 0.56),
        new Barrier(101, 698, 15, 80, 0.96),
        new Barrier(163, 731, 15, 80, 1.23),
        new Barrier(387, 385, 15, 80, 0.23),
        new Barrier(414, 448, 15, 80, 0.56),
        new Barrier(465, 500, 15, 80, 0.96),
        new Barrier(527, 533, 15, 80, 1.23),
        new Barrier(500+1239-510, 300+358-382, 15, 80, 0.23),
        new Barrier(500+1223-522, 300+290-378, 15, 80, 0.56),
        new Barrier(500+1125-471, 300+184-324, 15, 80, 0.96),
        new Barrier(500+1056-467, 300+162-335, 15, 80, 1.23),
        new Barrier(811, 273, 15, 80, -0.23),
        new Barrier(839, 213, 15, 80, -0.56),
        new Barrier(889, 161, 15, 80, -0.96),
        new Barrier(959, 126, 15, 80, -1.23),
        new Barrier(811-785, 273-143+5, 15, 80, -0.23),
        new Barrier(839-785, 213-143+5, 15, 80, -0.56),
        new Barrier(889-785, 161-143+5, 15, 80, -0.96),
        new Barrier(959-785, 126-143+5, 15, 80, -1.23),
        new Barrier(803, 343, 15, 30),
        new Barrier(994, 147, 80, 15),
        new Barrier(914+12, 656, 15, 80, -0.4),
        new Barrier(886+12, 696, 15, 80, -0.78),
        new Barrier(839+12, 729, 15, 80, -1.2),
        new Barrier(926+640-5, 656-34, 15, 80, -0.4),
        new Barrier(898+640-5, 696-34, 15, 80, -0.78),
        new Barrier(851+640-5+8, 729-34, 15, 80, -1.2),
        new Barrier(1279, 71, 15, 80, -0.4),
        new Barrier(1306, 25, 15, 80, -0.78),
        new Barrier(1353, -4, 15, 80, -1.2),
        new Barrier(1553, 71, 15, 80, 0.4),
        new Barrier(1524, 25, 15, 80, 0.78),
        new Barrier(1477, -4, 15, 80, 1.2),
        new Barrier(1553-1052, 70, 15, 80, 0.4),
        new Barrier(1524-1052, 24, 15, 80, 0.78),
        new Barrier(1477-1052, -5, 15, 80, 1.2),
        new Barrier(926-165+600+30, 656-193, 15, 80, -0.4),
        new Barrier(898-165+600+30, 696-193, 15, 80, -0.78),
        new Barrier(851-165+600+30, 729-193, 15, 80, -1.2),
        new Barrier(926-165+600+30+1113-1390-10, 656-193+617-464+582-619, 15, 120, 0.3),
        new Barrier(898-165+600+30+1146-1378, 696-193+697-540, 15, 80, 0.78),
        new Barrier(851-165+600+30+1236-1363, 729-193+743-585, 15, 80, 1.2),
        new Barrier(1396, 14, 60, 15, 0),
        new Barrier(203, 604, 15, 59, -0.45 + 1.5707),
        new Barrier(170, 571, 15, 57, 0.45),
        new Barrier(563, 405, 15, 59, -0.45 + 1.5707),
        new Barrier(530, 373, 15, 57, 0.45),
        new Barrier(204, 144, 15, 59, 0.45 - 1.5707),
        new Barrier(169, 181, 15, 57, -0.45),
        new Barrier(157, 231, 48, 49),
        new Barrier(1240, 583, 14, 26),
        new Barrier(989, 278, 15, 59, 0.45 - 1.5707),
        new Barrier(954, 315, 15, 57, -0.45),
        new Barrier(1052, 278, 15, 59, -0.45 + 1.5707),
        new Barrier(1088, 315, 15, 57, 0.45),
    };
    for (auto wall: walls) {
        contents.push_back(wall);
    }

    auto surfaces = std::array<Surface*, 17>{
        new Ice(685, 455, 415, 125),
        new Ice(1080, 470, 120, 135, -0.3),
        new Ice(1113, 572, 454, 177),
        new Ice(1440, 400, 130, 171),
        new Ice(1192, 529, 43, 43),
        new Ice(1302, 30, 400, 70, -0.2),
        new Ice (1198, 500, 250, 50, 0.6),
        new Ice (188, 280, 180, 20, 0),
        new Ice (188, 350, 200, 20, 0),
        new Ice (957, 285, 100, 100, 0.7),
        new Ice (1000, 285, 100, 100, -0.7),
        new Ice(820, 343, 40, 130, 0),
        new Ice(1439, 193, 40, 150, 0),
        new Curb(1439, 343, 30, 60, 0),
        new Curb(1540, 343, 30, 60, 0),
        new Curb(647, 651, 100, 30, 0),
        new Ice(378, 64, 250, 50, -0.8)
    };
    for (const auto& surface : surfaces) {
        contents.push_back(surface);
    }

    auto obstacles = std::array<Obstacle*, 12>{
        new Cone(774, 657),
        new Cone(387, 34),
        new Cone(414, 58),
        new Cone(1243, 554),
        new Cone(1119, 431),
        new Cone(1545, 311),
        new Gate(180, 283, 7, 90),
        new Oil(1318, 78),
        new Oil(336, 31),
        new SpeedBump(355, 300, 50, 13, M_PI/2),
        new Water(24, 248, 50, 30, M_PI/2),
        new Barrier(1065, 505, 250, 15, -0.77),
    };
    obstacles[11]->isCollidable = false;
    for (auto obstacle : obstacles) {
        contents.push_back(obstacle);
    }

    // NIE bawię się w żadną skalę
    // Pozdrawiam
    auto checkpoints = {
        new Checkpoint(0, 20+284-22, 30+719-116, 5, 200, 0, 0, nullptr),
        new Checkpoint(1, 20+235-22, 30+716-116, 5, 200, 0, 0, nullptr),
        new Checkpoint(2, 20+130-22, 30+669-130, 5, 200, -0.78, 0, nullptr),
        new Checkpoint(3, 20+89-22, 30+583-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(4, 20+89-22, 30+405-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(5, 20+96-22, 30+233-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(6, 112, 112-80, 5, 200, 0.78, 0, nullptr),
        new Checkpoint(7, 20+202-23, 30+209-353, 5, 600, 0, 0, nullptr),
        new Checkpoint(8, 20+367-23, 30+209-353, 5, 600, 0, 0, nullptr),
        new Checkpoint(9, 20+454-21, 30+175-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(10, 20+448-21, 30+389-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(11, 20+495-21, 30+469-130, 5, 200, -0.87, 0, nullptr),
        new Checkpoint(12, 20+588-21, 30+515-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(13, 20+803-21, 30+515-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(14, 20+948-22, 30+520-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(15, 20+1109-22, 30+509-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(16, 20+1173-22, 30+600-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(17, 20+1238-22, 30+683-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(18, 20+1432-22, 30+681-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(19, 20+1508-22, 30+610-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(20, 20+1520-22, 30+179-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(21, 20+1421-22, 30+84-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(22, 20+1290-22, 30+180-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(23, 20+1341-22, 30+440-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(24, 20+1251-22, 30+500-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(25, 20+1134-22, 30+428-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(26, 20+1163-22, 30+318-130, 5, 200, -1.3, 0, nullptr),
        new Checkpoint(27, 20+1030-22, 30+228-130, 5, 200, 0, 0, nullptr),
        new Checkpoint(28, 20+884-22, 30+313-130, 5, 200, 1.3, 0, nullptr),
        new Checkpoint(29, 20+880-22, 30+438-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(30, 20+879-22, 30+604-130, 5, 200, 1.57, 0, nullptr),
        new Checkpoint(31, 20+769-22, 30+719-130, 5, 200, 0, 0, nullptr),
    };
    this->checkpoints.insert(this->checkpoints.begin(), checkpoints);


    nitroPositions = {{249, 305}, {1455, 670}, {1249, 524}, {69, 478}};
    powerupPositions = {{331, 284}, {460, 88}, {1363, 395}, {708, 655}};


    player = new Player(536, 657);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->SetTexture();
    player->totalCheckpoints = this->checkpoints.size();
    contents.push_back(player);

    // auto opponents = std::array<Bot*, 3>{
    //     new Bot(300, 100, 150, 50, 0.5),
    //     new Bot(1400, 200),
    //     new Bot(240, 700, 50, 100, 1.5)
    currentLapLabel->setColor({0,0,0});
    currentLapText->setColor({0,0,0});
    lapLabel->setColor({0,0,0});

    auto bot = new MiddleLiner(335, 657, *this->player, this->opponents, this->contents, this->checkpoints);
    auto bot2 = new StraightMaster(355, 712, *this->player, this->opponents, this->contents, this->checkpoints);
    auto bot3 = new StraightMaster(436, 657, *this->player, this->opponents, this->contents, this->checkpoints);
    auto bot4 = new MiddleLiner(456, 712, *this->player, this->opponents, this->contents, this->checkpoints);

    bot->rayLength = 120;
    bot2->rayLength = 120;
    bot2->checkpointRayLength = 1500;
    bot->bounce = true;
    bot2->bounce = true;
    bot3->rayLength = 120;
    bot3->checkpointRayLength = 1500;
    bot3->bounce = true;
    bot4->rayLength = 120;
    bot4->bounce = true;

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

    opponents[2]->texture = Game::textures.at("car-red-regular.bmp");
    opponents[2]->player = *player;
    opponents[2]->checkpoints = this->checkpoints;
    opponents[2]->totalCheckpoints = this->checkpoints.size();
    opponents[2]->isCollidable = true;
    opponents[2]->angle = SDL_PI_F / -2;

    opponents[3]->texture = Game::textures.at("car-yellow-regular.bmp");
    opponents[3]->player = *player;
    opponents[3]->checkpoints = this->checkpoints;
    opponents[3]->totalCheckpoints = this->checkpoints.size();
    opponents[3]->isCollidable = true;
    opponents[3]->angle = SDL_PI_F / -2;
}