#include "game/entities/StraightMaster.h"

void StraightMaster::update() {
    Bot::update();
    // if (isFacingCheckpoint()) {
        // SDL_Log("Facing checkpoint!");
        // accelerate();
        // move();
    // }
}

double StraightMaster::evaluateTurn(double testTurn) {
    return SDL_fabs(testTurn - angle);
}

bool StraightMaster::isFacingCheckpoint() {
    Checkpoint* next = this->getNextCheckpoint();

    return false; // todo
}

double StraightMaster::distanceToNextCheckpoint() {

}

Checkpoint* StraightMaster::getNextCheckpoint() {
    return this->checkpoints[this->nextCheckpoint];
}

StraightMaster::StraightMaster(double x, double y, Player &player, std::vector<Bot *> &opponents,
                               std::vector<SceneElement *> &contents, std::vector<Checkpoint *> &checkpoints,
                               double zIndex, SDL_Texture *texture, double width, double length, double angle) : Bot(x, y, player, opponents, contents, checkpoints, zIndex, texture, width, length, angle) {

}
