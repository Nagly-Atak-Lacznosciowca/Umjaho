#include "engine/scenes/SceneElement.h"
#include <functional>
#include "engine/scenes/Text.h"

class Button : public SceneElement {
public:
    std::function<void()> action;
    void click() const;
    Text* text = nullptr;


    Button(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
           const std::function<void()> &action, std::string text = "");

    void render() override;
};