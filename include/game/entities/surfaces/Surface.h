#ifndef SURFACE_H
#define SURFACE_H

#include "engine/scenes/SceneElement.h"
#include "game/entities/Car.h"

class Surface : public SceneElement {
    public:
        Surface(double x, double y, double width, double height, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
        ~Surface() override = default;

        void collide(SceneElement* element) override;
        virtual void action(Car* car);
};

#endif //SURFACE_H