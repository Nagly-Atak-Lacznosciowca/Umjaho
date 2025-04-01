
#include "SDL3/SDL_render.h"
#include "engine/scenes/scenes/Checkpoint.h"

#include "engine/scenes/Text.h"
#include "engine/scenes/scenes/Leaderboard.h"
#include "engine/scenes/scenes/Level.h"
#include "game/Event.h"
#include "game/Game.h"
#include "game/entities/Car.h"
#include "game/entities/Player.h"

Checkpoint::Checkpoint(int id, double x, double y, double width, double height, double angle, double zIndex,
                       SDL_Texture *texture) : SceneElement(x, y, width, height, angle, zIndex, texture) {
    this->id = id;
    auto points = this->getPoints();
    this->center = new SDL_FPoint{(points[0].x + points[2].x) / 2, (points[0].y + points[2].y) / 2};
}

void lap(Player* player) {
    auto level = dynamic_cast<Level*>(Game::sceneManager.currentScene());
    auto &currentLap = level->currentLap;
    auto &startTime = level->startTime;
    auto &lapStartTime = level->lapStartTime;
    auto &ticks = level->ticks;
    auto &lapTimes = level->lapTimes;
    auto &laps = level->laps;
    auto &currentLapTime = level->currentLapTime;
    auto &lapLabel = level->lapLabel;
    auto &minutes = level->minutes;
    auto &seconds = level->seconds;
    auto &milliseconds = level->milliseconds;

    SDL_Log("current lap %d", currentLap);
    if (currentLap == 0) {
        startTime = ticks;
        lapStartTime = startTime;
        currentLap++;
    }
    else if (currentLap <= laps) {
        lapTimes[currentLap-1] = currentLapTime;
        auto lap = new Text(520 + (currentLap-1)*250, 830, 0, 30, 0,0, std::format("Lap {} Time: {:02}:{:02}:{:02}", currentLap, minutes, seconds, milliseconds));
        lapLabel->setContent(std::format("{}/3", currentLap));
        level->contents.push_back(lap);
        currentLap++;
        lapStartTime = ticks;
    }
    else {
        std::sort(lapTimes, lapTimes+3, std::less<Uint64>());
        auto fastestLap = lapTimes[0];
        SDL_PushEvent(new SDL_Event{
            .user = {
                .type = Event::Event::CUSTOM_EVENT_PUSH_SCENE,
                .data1 = new Leaderboard(startTime, ticks, level, fastestLap)
            }
        });
    }
}

void Checkpoint::collide(SceneElement *element) {
    SceneElement::collide(element);
//    SDL_Log("Collision with Checkpoint %i", this->id);
    if (auto *car = dynamic_cast<Car*>(element)) {
        SDL_Log("Standing on checkpoint %d", this->id);
        if (car->nextCheckpoint == this->id) {
            SDL_Log("Passed checkpoint: %i, next checkpoint: %i", this->id, (car->nextCheckpoint + 1) % car->totalCheckpoints);
            car->nextCheckpoint = (this->id + 1) % car->totalCheckpoints;
            if (car->nextCheckpoint == 1) {
                if (auto *player = dynamic_cast<Player*>(car)) {
                    SDL_Log("chujh");
                    lap(player);
                }
            }
        }
    }
}
