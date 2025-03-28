#include "engine/scenes/Text.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "game/Game.h"

Text::Text(double x, double y, double width, double height, double angle, double zIndex) : SceneElement(x,y,width,height,angle,zIndex) {
    const auto surface = TTF_RenderText_Solid(Game::font, this->content.data(), content.length(), SDL_Color{255,255,255});
    this->texture = SDL_CreateTextureFromSurface(Game::renderer.SDLRenderer, surface);
    delete surface;
}

void Text::setContent(std::string text) {
    this->content = text;
    auto surface = TTF_RenderText_Solid(Game::font, content.data(), content.length(), SDL_Color{255,255,255});
    this->texture = SDL_CreateTextureFromSurface(Game::renderer.SDLRenderer, surface);
    delete surface;
    this->render();
}