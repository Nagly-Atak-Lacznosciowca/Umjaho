#include "engine/scenes/scenes/Level1.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/obstacles/Barrier.h"
#include "game/entities/powerups/Nitro.h"
#include "engine/scenes/Text.h"

Level1::Level1() {

    SDL_Texture *backgroundTexture = Game::textures.at("track1.bmp");
    this->background = backgroundTexture;

    player = new Player(550, 685);
    player->angle = SDL_PI_F / -2; // Start facing left
    player->texture = Game::textures.at("car-blue-regular.bmp");
    contents.push_back(player);

    auto walls = {
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
    };

    this->contents.insert(this->contents.end(), walls.begin(), walls.end());

    int width, height;

    SDL_GetWindowSize(Game::renderer.SDLWindow, &width, &height);

    const float scaleX = (float)width / (float)this->background->w;
    const float scaleY = (float)height / (float)this->background->h;

    auto checkpoints = {
        new Checkpoint(717 * scaleX, 989 * scaleY, 5 * scaleX, 262 * scaleY, 0, 0, nullptr),
        new Checkpoint(717 * scaleX, 989 * scaleY, 5 * scaleX, 262 * scaleY, 0, 0, nullptr),
        new Checkpoint(237 * scaleX, 935 * scaleY, 5 * scaleX, 272 * scaleY, -SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(180 * scaleX, 785 * scaleY, 5 * scaleX, 272 * scaleY, SDL_PI_F / 2, 0, nullptr),
        new Checkpoint(180 * scaleX, 345 * scaleY, 5 * scaleX, 272 * scaleY, SDL_PI_F / 2, 0, nullptr),
        new Checkpoint(280 * scaleX, 110 * scaleY, 5 * scaleX, 285 * scaleY, SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(700 * scaleX, 115 * scaleY, 5 * scaleX, 285 * scaleY, -SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(502 * scaleX, 50 * scaleY, 5 * scaleX, 278 * scaleY, 0, 0, nullptr),
        new Checkpoint(849 * scaleX, 480 * scaleY, 5 * scaleX, 279 * scaleY, -SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(1112 * scaleX, 538 * scaleY, 5 * scaleX, 217 * scaleY, 0, 0, nullptr),
        new Checkpoint(1730 * scaleX, 538 * scaleY, 5 * scaleX, 270 * scaleY, 0, 0, nullptr),
        new Checkpoint(1935 * scaleX, 450 * scaleY, 5 * scaleX, 279 * scaleY, SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(2025 * scaleX, 209 * scaleY, 5 * scaleX, 272 * scaleY, SDL_PI_F / 2, 0, nullptr),
        new Checkpoint(2085 * scaleX, 105 * scaleY, 5 * scaleX, 279 * scaleY, SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(2205 * scaleX, 53 * scaleY, 5 * scaleX, 270 * scaleY, 0, 0, nullptr),
        new Checkpoint(2320 * scaleX, 105 * scaleY, 5 * scaleX, 279 * scaleY, -SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(2365 * scaleX, 209 * scaleY, 5 * scaleX, 272 * scaleY, SDL_PI_F / 2, 0, nullptr),
        new Checkpoint(2365 * scaleX, 669 * scaleY, 5 * scaleX, 272 * scaleY, SDL_PI_F / 2, 0, nullptr),
        new Checkpoint(2302 * scaleX, 875 * scaleY, 5 * scaleX, 279 * scaleY, SDL_PI_F / 4, 0, nullptr),
        new Checkpoint(1933 * scaleX, 1042 * scaleY, 5 * scaleX, 210 * scaleY, 0, 0, nullptr),
        new Checkpoint(361 * scaleX, 989 * scaleY, 5 * scaleX, 262 * scaleY, 0, 0, nullptr),
        new Checkpoint(806 * scaleX, 294 * scaleY, 5 * scaleX, 272 * scaleY, SDL_PI_F / 2, 0, nullptr),
    };

    this->checkpoints.insert(this->checkpoints.begin(), checkpoints);

    auto nitros = {
        new Nitro(315, 111),
        new Nitro(852, 403),
        new Nitro(1467, 566),
    };

    this->contents.insert(contents.end(), nitros.begin(), nitros.end());

    auto text = new Text(215, 815);
    text->setContent("fhdggfds");
    text->width = 1200;
    contents.push_back(text);
}