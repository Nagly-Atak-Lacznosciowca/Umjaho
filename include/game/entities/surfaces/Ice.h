#ifndef ICE_H
#define ICE_H

#include "game/entities/surfaces/Surface.h"

class Ice : public Surface {
    public:
    Ice(double x, double y, double width, double height, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
    ~Ice() override = default;

    void collide(SceneElement* element) override;
    void action(Car* car) override;
};

#endif //ICE_H
