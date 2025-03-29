#include "engine/scenes/controls/LevelButton.h"
#include "game/Game.h"

LevelButton::LevelButton(double x, double y, double width, double height, double angle, double zIndex,
                         SDL_Texture *texture, Level *level, const std::string &text, SDL_Texture* image): Button(x,y,width,height,angle, zIndex,texture,
                                                                                                                  nullptr), level(level), image(image) {
    if(!text.empty()){
        auto *textWidth = new int();
        auto *textHeight = new int();

        if (!TTF_GetStringSize(Game::font, text.data(), text.length(), textWidth, textHeight)) {
            SDL_Log("Couldn't get string size: %s", SDL_GetError());
        }

        this->text = new Text(x + width/2 - (float)*textWidth/2, y + height/5 - (float)*textHeight/2, *textWidth, *textHeight, angle, zIndex, text);

        delete textWidth;
        delete textHeight;
    }
};

void LevelButton::click(float x, float y) const {
    if(level!= nullptr){
        Game::sceneManager.pushScene(this->level);
    }
}

void LevelButton::render() {
    Button::render();
    SDL_RenderTexture(Game::renderer.SDLRenderer, this->image, nullptr,
                      new SDL_FRect{static_cast<float>(x+width/4), static_cast<float>(y + height/3), (float)width/2, (float)width/2});
}

