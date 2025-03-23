#include "engine/scenes/SceneElement.h"
#include <functional>

class Button : public SceneElement {
public:
    std::function<void()> action;
    void click() const;

    Button(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
           const std::function<void()> &action);
};