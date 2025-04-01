#include <utility>

#include "SDL3/SDL_render.h"
#include "engine/scenes/SceneElement.h"
#include "engine/scenes/controls/Button.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "game/Game.h"

Button::Button(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
               const std::function<void()> &action, const std::string &text) : Control(x, y, width, height, angle, zIndex, texture), action(action) {
    if(!text.empty()){
        this->text = new Text(0, y + height/2 - height/2 * 0.85, 0, height * 0.85, angle, zIndex, text);
	    this->text->x = x + width/2 - this->text->width/2;
    }
}

void Button::click(float x, float y) {
    if (action) action();
}

void Button::render() {
    SceneElement::render();
    if(text != nullptr){
        this->text->render();
    }
}

void Button::setText(const std::string &text) const {
    this->text->setContent(text);
    this->text->x = this->x + this->width/2 - this->text->width/2;
    this->text->y = this->y + this->height/2 - this->height/2 * 0.85;
    this->text->render();
}

Button::~Button() {
    delete text;
}



