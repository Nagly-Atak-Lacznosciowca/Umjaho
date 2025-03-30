#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "engine/scenes/Scene.h"

class Leaderboard : public Scene {
  public:
    Leaderboard(Uint64 time);

    Uint64 lastTime = 0;

    void logic() override;
    void handleEvent(SDL_Event* event) override;
};

#endif //LEADERBOARD_H
