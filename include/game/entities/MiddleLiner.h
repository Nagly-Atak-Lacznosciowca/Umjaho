#ifndef UMJAHO_MIDDLELINER_H
#define UMJAHO_MIDDLELINER_H

#include "Bot.h"
class MiddleLiner : public Bot {
public:
    MiddleLiner(double x, double y, Player &player, std::vector<Bot *> &opponents,
                   std::vector<SceneElement *> &contents, std::vector<Checkpoint *> &checkpoints, double zIndex = 0,
                   SDL_Texture *texture = nullptr, double width = Car::WIDTH, double length = Car::LENGTH, double angle = 0);

private:
    void update() override;
    double evaluateTurn(double testTurn) override;

    double distanceToNextCheckpoint();

    bool isFacingCheckpoint();

    Checkpoint *getNextCheckpoint();
};

#endif //UMJAHO_MIDDLELINER_H
