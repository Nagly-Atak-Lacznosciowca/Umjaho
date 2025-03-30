#ifndef UMJAHO_CHECKPOINT_H
#define UMJAHO_CHECKPOINT_H

#include "engine/scenes/SceneElement.h"

class Checkpoint : public SceneElement {

public:
    int id;
    Checkpoint(int id, double x, double y, double width, double height, double angle, double zIndex,
               SDL_Texture *texture);

    void collide(SceneElement *element) override;
};

#endif //UMJAHO_CHECKPOINT_H
