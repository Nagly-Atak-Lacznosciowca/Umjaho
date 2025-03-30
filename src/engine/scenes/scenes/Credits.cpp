#include "engine/scenes/scenes/Credits.h"
#include "game/Game.h"
#include "engine/scenes/controls/Button.h"
#include "game/Event.h"

int height;

Credits::Credits()
{
	this->background = Game::textures.at("pause-menu.bmp");
	
	int *windowWidth = new int();
	int *windowHeight = new int();
	
	SDL_GetWindowSize(Game::renderer.SDLWindow, windowWidth, windowHeight);
	
	const int width = *windowWidth;
	height = *windowHeight;
	
	delete windowWidth;
	delete windowHeight;
	
	const float scaleX = (float)width / (float)this->background->w;
	const float scaleY = (float)height / (float)this->background->h;
	
	std::pair<std::string, std::string> credits[] = {
		{"Audio desgin", "Ja"},
		{"Glupi chuj", "nie Ja"},
		{"Kupiec", "też nie Ja"},
		{"Reszta", "znowu Ja"}
	};
	
	const double creditCount = (double)sizeof(credits) / sizeof(std::pair<std::string, std::string>);
	
	const double headerHeight = 20;
	const double headerGap = 5;
	
	const double textHeight = 15;
	const double textGap = 20;
	
	for (int i = 0; i < sizeof(credits) / sizeof(std::pair<std::string, std::string>); i++) {
		auto *header = new Text(0, (i * headerHeight + i * headerGap + i * textHeight + i * textGap) * scaleY, 0, headerHeight * scaleY, 0, 1, credits[i].first);
		header->x = (double)width / 2 - header->width / 2;
		auto *text = new Text(0, ((i + 1) * headerHeight + (i + 1) * headerGap + i * textHeight + i * textGap) * scaleY, 0, textHeight * scaleY, 0, 1, credits[i].second);
		text->x = (double)width / 2 - text->width / 2;
		
		this->contents.push_back(header);
		this->contents.push_back(text);
	}
	
	for (auto &text : this->contents) {
		text->y -= creditCount * (headerHeight + headerGap + textHeight + textGap) * scaleY;
	}
}

void Credits::logic()
{
	for (auto &text : this->contents) {
		text->y += 0.5f;
	}
	
	if ((*this->contents.begin())->y >= height + 100) {
		SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
	}
}

void Credits::handleEvent(SDL_Event *event) {
	Scene::handleEvent(event);
	
	switch (event->type)
	{
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
				SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
			break;
	}
}