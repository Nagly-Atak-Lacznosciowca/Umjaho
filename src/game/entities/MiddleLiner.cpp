#include "game/entities/MiddleLiner.h"
#include "math/Vec2.h"

void MiddleLiner::update() {
    updateRays();

    for (const auto content : contents) {
        if (dynamic_cast<Obstacle*>(content)) {
            checkRayCollision(rays, content);
        }
    }

    this->maxSpeed = 3.5;

    Vec2 vectorRays[7];
    Vec2 collidedVectorRays[7];

    for (int i = 0; i < 7; i++) {
        vectorRays[i] = {rays[i].direction.x - rays[i].origin.x, rays[i].direction.y - rays[i].origin.y};
    }

    if (rays[1].collides || rays[2].collides) {
//        decelerate();
        angle -= 0.03;
    }
    if (rays[4].collides || rays[5].collides) {
//        decelerate();
        angle += 0.03;
        // turnLeft();
    }
    if (rays[3].collides && speed > 2) {
        brake();
    }
    if (rays[1].collides && rays[2].collides && rays[3].collides && rays[4].collides && rays[5].collides) {
        speed = -speed;
    }
    else {
        accelerate();
    }

    accelerate();
    move();
}

double MiddleLiner::evaluateTurn(double testTurn) {
    return SDL_fabs(testTurn - angle);
}

bool MiddleLiner::isFacingCheckpoint() {
    Checkpoint* next = this->getNextCheckpoint();

    return false; // todo
}

double MiddleLiner::distanceToNextCheckpoint() {

}

Checkpoint* MiddleLiner::getNextCheckpoint() {
    return this->checkpoints[this->nextCheckpoint];
}

MiddleLiner::MiddleLiner(double x, double y, Player &player, std::vector<Bot *> &opponents,
                               std::vector<SceneElement *> &contents, std::vector<Checkpoint *> &checkpoints,
                               double zIndex, SDL_Texture *texture, double width, double length, double angle) : Bot(x, y, player, opponents, contents, checkpoints, zIndex, texture, width, length, angle) {
    this->rayLength = 150;
}
