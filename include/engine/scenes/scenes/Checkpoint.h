#ifndef UMJAHO_CHECKPOINT_H
#define UMJAHO_CHECKPOINT_H

#include "engine/scenes/SceneElement.h"

class Checkpoint : public SceneElement {

public:
    Checkpoint(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture)
            : SceneElement(x, y, width, height, angle, zIndex, texture) {

    }
};

#endif //UMJAHO_CHECKPOINT_H
