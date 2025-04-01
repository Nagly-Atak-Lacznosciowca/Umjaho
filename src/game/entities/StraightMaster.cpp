#include "game/entities/StraightMaster.h"
#include "math/Vec2.h"

void StraightMaster::update() {
    updateRays();

//    auto angleToRotate = Game::calculateAngleToPoint(this, checkpoints[this->nextCheckpoint]->center);

//    SDL_Log("angleDiff bot nigga: %f", Game::calculateAngleToPoint(this, checkpoints[this->nextCheckpoint]->center));

    for (const auto content : contents) {
        if (dynamic_cast<Obstacle*>(content)) {
            checkRayCollision(rays, content);
        }
    }
//    for (const auto checkpoint : checkpoints) {
//        checkRayCollision(rays, checkpoint);
//    }

    Vec2 vectorRays[7];
    Vec2 collidedVectorRays[7];

    for (int i = 0; i < 7; i++) {
        vectorRays[i] = {rays[i].direction.x - rays[i].origin.x, rays[i].direction.y - rays[i].origin.y};
    }
//
    if (rays[1].collides || rays[2].collides) {
//        decelerate();
        angle -= 0.03;
    }
    if (rays[4].collides || rays[5].collides) {
//        decelerate();
        angle += 0.03;
        // turnLeft();
    }
    if (rays[3].collides && speed > 1.5) {
        decelerate();
        decelerate();
        decelerate();
        brake();
    }
    if (bounce && rays[1].collides && rays[2].collides && rays[3].collides && rays[4].collides && rays[5].collides) {
        speed = -speed;
    }
    else {
        accelerate();
    }
//
//    if (angleToRotate > 0.05) {
//        this->angle -= 0.03;
//    }
//    else if (angleToRotate < -0.05) {
//        this->angle += 0.03;
//    }

    accelerate();
    accelerate();
    move();
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
