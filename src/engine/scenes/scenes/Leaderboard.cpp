#include "engine/scenes/scenes/Leaderboard.h"

#include <format>

#include "engine/scenes/Text.h"
#include "engine/scenes/controls/Button.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/Level2.h"
#include "game/Event.h"
#include "game/Game.h"


void exitToLevelMenu() {
    SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE });
    SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE });
}

Leaderboard::Leaderboard(Uint64 start, Uint64 ticks, Level* level, Uint64 fastestLap) {
    lastTime = (ticks - start);

    int levelNumber;

    if (dynamic_cast<Level1*>(level)) {
        levelNumber = 0;
    }
    else if (dynamic_cast<Level2*>(level)) {
        levelNumber = 1;
    }
    else {
        levelNumber = 2;
    }

    Game::playerTimes[levelNumber].push_back(lastTime);

    this->background = Game::textures.at("level-menu.bmp");


    int *windowWidth = new int();
    int *windowHeight = new int();

    SDL_GetWindowSizeInPixels(Game::renderer.SDLWindow, windowWidth, windowHeight);

    const int width = *windowWidth;
    const int height = *windowHeight;

    delete windowWidth;
    delete windowHeight;

    const float scaleX = (float)width / (float)this->background->w;
    const float scaleY = (float)height / (float)this->background->h;

    auto title = new Text(0, 10, 0, 40*scaleY, 0, 0, std::format("Leaderboard Level {}", levelNumber+1));
    title->x = static_cast<float>(width)/2 - (title->width/2);

    contents.push_back(title);

    for (int i = 0; i < Game::playerTimes[levelNumber].size(); i++) {
        Uint64 minutes = Game::playerTimes[levelNumber][i] / 6000;
        Uint64 seconds = Game::playerTimes[levelNumber][i] / 100;
        Uint64 milliseconds = Game::playerTimes[levelNumber][i] - seconds * 100 - minutes * 6000;
        auto text = new Text(0, 80 + i*70, 0, 30*scaleY, 0, 0, std::format("#{} Time: {:02} : {:02} : {:02}", i+1, minutes, seconds, milliseconds));
        text->x = static_cast<float>(width)/2 - (text->width/2);
        contents.push_back(text);
    }
    auto button = new Button(static_cast<float>(width)/2 - static_cast<float>(width)/8, 760*scaleY, static_cast<float>(width)/4, 50*scaleY, 0, 0, Game::textures.at("button.bmp"), exitToLevelMenu, "Return");
    contents.push_back(button);

}

void Leaderboard::handleEvent(SDL_Event* event) {
    Menu::handleEvent(event);
    switch (event->type) {
        case SDL_EVENT_KEY_DOWN:
            if (event->key.scancode == SDL_SCANCODE_ESCAPE) {
                exitToLevelMenu();
            }
            break;
        default:
            break;
    }
}

void Leaderboard::logic() {

}

