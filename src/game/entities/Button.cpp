#include <utility>

#include "SDL3/SDL_render.h"
#include "engine/scenes/SceneElement.h"
#include "game/entity/Button.h"

Button::Button(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
               const std::function<void()> &action, std::string text) : SceneElement(x, y, width, height, angle, zIndex, texture), action(action) {
    if(!text.empty()){
        this->text = new Text(x+width/3, y+height/4-2, width/3, height/2, angle, zIndex);
        this->text->setContent(std::move(text));
    }
}

void Button::click() const {
    if (action) action();
}

void Button::render() {
    SceneElement::render();
    if(text != nullptr){
        this->text->render();
    }
}



