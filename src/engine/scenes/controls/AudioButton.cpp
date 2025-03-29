#include "engine/scenes/controls/AudioButton.h"
#include "game/Game.h"

AudioButton::AudioButton(double x, double y, double width, double height, double zIndex,
                         const std::function<void()> &action, float value) : Button(x,y,width,height,0,zIndex, nullptr, action), value(value) {};

void AudioButton::render() {
    auto rect = new SDL_FRect{ static_cast<float>(this->x),
                           static_cast<float>(this->y),
                           static_cast<float>(this->width),
                           static_cast<float>(this->height) };
    if(this->activated){
        SDL_RenderFillRect(Game::renderer.SDLRenderer, rect);
    }
    else{
        SDL_RenderRect(Game::renderer.SDLRenderer, rect);
    }
}
