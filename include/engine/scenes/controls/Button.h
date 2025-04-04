#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "engine/scenes/Text.h"
#include "Control.h"

class Button : public Control {
public:
    std::function<void()> action;
    void click(float x, float y) override;
    Text* text = nullptr;

    Button(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
           const std::function<void()> &action, const std::string &text = "");
    ~Button() override;

    void render() override;
    void setText(const std::string &text) const;
};

#endif //BUTTON_H