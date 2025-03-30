#include "engine/scenes/scenes/Leaderboard.h"

#include <format>

#include "engine/scenes/Text.h"
#include "game/Game.h"

Leaderboard::Leaderboard(Uint64 time) {
    lastTime = (SDL_GetTicks() - time) / 1000;

    this->background = Game::textures.at("level-menu.bmp");

    const auto title = new Text(100, 10, 0, 20, 0, 0, std::format("Ukończygfłeś w {}", lastTime));

    contents.push_back(title);
}

void Leaderboard::handleEvent(SDL_Event* event) {

}

void Leaderboard::logic() {

}

