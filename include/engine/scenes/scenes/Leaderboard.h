#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "Level.h"
#include "Menu.h"

class Leaderboard : public Menu {
  public:
    Leaderboard(Uint64 time, Uint64 ticks, Level* level, Uint64 fastestLap);

    Uint64 lastTime = 0;

    void logic() override;
    void handleEvent(SDL_Event* event) override;
};

#endif //LEADERBOARD_H
