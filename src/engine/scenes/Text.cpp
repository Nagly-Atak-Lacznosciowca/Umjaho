#include <utility>

#include "engine/scenes/Text.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "game/Game.h"

Text::Text(double x, double y, double width, double height, double angle, double zIndex, const std::string& text) : SceneElement(x, y, width, height, angle, zIndex) {
	auto *textWidth = new int();
	auto *textHeight = new int();
	
	TTF_GetStringSize(Game::font, text.data(), text.length(), textWidth, textHeight);
	
	if (this->width == 0 && this->height == 0)
	{
		this->width = *textWidth;
		this->height = *textHeight;
	}
	else if (this->width == 0)
	{
		const auto scale = this->height / *textHeight;
		
		this->width = scale * *textWidth;
	}
	else if (this->height == 0)
	{
		const auto scale = this->width / *textWidth;
		
		this->height = scale * *textHeight;
	}
	
	delete textWidth;
	delete textHeight;
	
	this->setContent(text);
}

void Text::setContent(const std::string& text) {
	this->content = text;
	
	auto surface = TTF_RenderText_Shaded(Game::font, this->content.data(), content.length(), SDL_Color{255,255,255}, SDL_Color{255,255,255});
	
	surface = SDL_ScaleSurface(surface, (int)width, (int)height, SDL_SCALEMODE_LINEAR);
	
	this->texture = SDL_CreateTextureFromSurface(Game::renderer.SDLRenderer, surface);
	
	delete surface;
}