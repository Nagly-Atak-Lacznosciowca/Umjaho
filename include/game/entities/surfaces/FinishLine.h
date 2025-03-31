#ifndef FINISHLINE_H
#define FINISHLINE_H
#include "Surface.h"

class FinishLine: public Surface {
public:
    FinishLine(double x, double y, double width, double height, double angle = 0, double zIndex = 0, SDL_Texture* texture = nullptr);
    void action(Car* car) override;
    void collide(SceneElement* element) override;
};


#endif //FINISHLINE_H
