#ifndef DIRT_H
#define DIRT_H

#include "game/entities/surfaces/Surface.h"

class Dirt : public Surface {
    public:
    Dirt(double x, double y, double width, double height, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
    ~Dirt() override = default;

    void collide(SceneElement* element) override;
    void action(Car* car) override;
};

#endif //DIRT_H
