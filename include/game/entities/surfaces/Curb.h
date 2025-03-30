#ifndef CURB_H
#define CURB_H
#include "game/entities/surfaces/Surface.h"

class Curb : public Surface {
    public:
        Curb(double x, double y, double width, double height, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
        ~Curb() override = default;

        void collide(SceneElement* element) override;
        void action(Car* car) override;
};

#endif //CURB_H
