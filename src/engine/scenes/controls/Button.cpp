#include <utility>

#include "SDL3/SDL_render.h"
#include "engine/scenes/SceneElement.h"
#include "engine/scenes/controls/Button.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "game/Game.h"

Button::Button(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture,
               const std::function<void()> &action, const std::string &text) : Control(x, y, width, height, angle, zIndex, texture), action(action) {
    if(!text.empty()){
		auto *textWidth = new int();
	    auto *textHeight = new int();
		
	    if (!TTF_GetStringSize(Game::font, text.data(), text.length(), textWidth, textHeight)) {
		    SDL_Log("Couldn't get string size: %s", SDL_GetError());
		}
		
        this->text = new Text(x + width/2 - (float)*textWidth/2, y + height/2 - (float)*textHeight/2, *textWidth, *textHeight, angle, zIndex, text);
		
		delete textWidth;
		delete textHeight;
    }
}

void Button::click(float x, float y) const {
    if (action) action();
}

void Button::render() {
    SceneElement::render();
    if(text != nullptr){
        this->text->render();
    }
}



