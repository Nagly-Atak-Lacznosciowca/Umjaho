#include <utility>

#include "engine/scenes/Text.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "game/Game.h"

// Text class. 
// Set initial width or height to 0 to compute it dynamically based on supplied text.
Text::Text(double x, double y, double width, double height, double angle, double zIndex, const std::string& text, const SDL_Color color) : SceneElement(x, y, width, height, angle, zIndex) {
	dynamicWidth = width == 0;
	dynamicHeight = height == 0;
	this->setColor(color);
	this->setContent(text);
}

void Text::setContent(const std::string& text) {
	this->content = text;
	this->updateSurface();
}

void Text::setColor(const SDL_Color color) {
	this->color = color;
	this->updateSurface();
}

void Text::updateSurface() {
	auto *textWidth = new int();
	auto *textHeight = new int();

	TTF_GetStringSize(Game::font, content.data(), content.length(), textWidth, textHeight);

	if (dynamicWidth && dynamicHeight) {
		this->width = *textWidth;
		this->height = *textHeight;
	} else if (dynamicWidth) {
		const auto scale = this->height / *textHeight;
		this->width = scale * *textWidth;
	} else if (dynamicHeight) {
		const auto scale = this->width / *textWidth;
		this->height = scale * *textHeight;
	}

	auto surface = TTF_RenderText_Shaded(Game::font, content.data(), content.length(), color, color);
	// surface = SDL_ScaleSurface(surface, (int)width, (int)height, SDL_SCALEMODE_LINEAR); // this lags the whole game :(
	this->texture = SDL_CreateTextureFromSurface(Game::renderer.SDLRenderer, surface);
	SDL_SetTextureScaleMode(this->texture, SDL_SCALEMODE_LINEAR);

	delete textWidth;
	delete textHeight;
	SDL_DestroySurface(surface);
}

Text::~Text() {
	SDL_DestroyTexture(texture);
}
