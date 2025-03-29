#ifndef UMJAHO_CONTROL_H
#define UMJAHO_CONTROL_H

#include "engine/scenes/SceneElement.h"

class Control: public SceneElement{
public:
    Control(double x, double y, double width, double height, double angle = 0, double zIndex = 1, SDL_Texture* texture = nullptr);
    virtual ~Control() = default;
    virtual void click(float x, float y) const;
};

#endif //UMJAHO_CONTROL_H
