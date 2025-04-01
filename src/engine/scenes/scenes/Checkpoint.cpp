
#include "SDL3/SDL_render.h"
#include "engine/scenes/scenes/Checkpoint.h"
#include "game/entities/Car.h"

Checkpoint::Checkpoint(int id, double x, double y, double width, double height, double angle, double zIndex,
                       SDL_Texture *texture) : SceneElement(x, y, width, height, angle, zIndex, texture) {
    this->id = id;
    auto points = this->getPoints();
    this->center = new SDL_FPoint{(points[0].x + points[2].x) / 2, (points[0].y + points[2].y) / 2};
}

void Checkpoint::collide(SceneElement *element) {
    SceneElement::collide(element);
//    SDL_Log("Collision with Checkpoint %i", this->id);
    if (auto *car = dynamic_cast<Car*>(element)) {
        if (car->nextCheckpoint == this->id) {
            SDL_Log("Passed checkpoint: %i, next checkpoint: %i", this->id, (car->nextCheckpoint + 1) % car->totalCheckpoints);
            car->nextCheckpoint = (this->id + 1) % car->totalCheckpoints;
        }
    }
}
