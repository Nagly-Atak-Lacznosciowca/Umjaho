#include "engine/scenes/scenes/PauseMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/Button.h"
#include "engine/scenes/scenes/SettingsMenu.h"
#include "game/Event.h"

void resume() {
	SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
}

void goToSettingsMenu() {
	SDL_PushEvent(new SDL_Event {
		.user = {
			.type = Event::CUSTOM_EVENT_PUSH_SCENE,
			.data1 = new SettingsMenu()
		}
	});
}

void exitTitle() {
	SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
	SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
	SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
}

void exitGame() {
	SDL_PushEvent(new SDL_Event{SDL_EVENT_QUIT});
}

PauseMenu::PauseMenu()
{
	this->background = Game::textures.at("pause-menu.bmp");
	
	int *windowWidth = new int();
	int *windowHeight = new int();
	
	SDL_GetWindowSizeInPixels(Game::renderer.SDLWindow, windowWidth, windowHeight);
	
	const int width = *windowWidth;
	const int height = *windowHeight;
	
	delete windowWidth;
	delete windowHeight;
	
	const float scaleX = (float)width / (float)this->background->w;
	const float scaleY = (float)height / (float)this->background->h;
	
	const auto textWidth = 100;
	const auto textHeight = 30;
	
	Text *pausedText = new Text(((float)this->background->w / 2 - (float)textWidth / 2) * scaleX, 120 * scaleY, textWidth * scaleX, textHeight * scaleY, 0, 1, "PAUSED");
	
	const auto buttonListY = 400;
	
	const auto buttonWidth = 200;
	const auto buttonHeight = 20;
	const auto gap = 10;
	
	auto *resumeButton = new Button(((float)this->background->w / 2 - (float)buttonWidth / 2) * scaleX, buttonListY + 0 * (gap + buttonHeight) * scaleY, buttonWidth * scaleX, buttonHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), resume, "Resume");
	auto *settingsButton = new Button(((float)this->background->w / 2 - (float)buttonWidth / 2) * scaleX, buttonListY + 1 * (gap + buttonHeight) * scaleY, buttonWidth * scaleX, buttonHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), goToSettingsMenu, "Settings");
	auto *exitTitleButton = new Button(((float)this->background->w / 2 - (float)buttonWidth / 2) * scaleX, buttonListY + 2 * (gap + buttonHeight) * scaleY, buttonWidth * scaleX, buttonHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), exitTitle, "Exit to title");
	auto *exitGameButton = new Button(((float)this->background->w / 2 - (float)buttonWidth / 2) * scaleX, buttonListY + 3 * (gap + buttonHeight) * scaleY, buttonWidth * scaleX, buttonHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), exitGame, "Exit to desktop");
	
	this->contents.push_back(pausedText);
	
	this->contents.push_back(resumeButton);
	this->contents.push_back(settingsButton);
	this->contents.push_back(exitTitleButton);
	this->contents.push_back(exitGameButton);
}

void PauseMenu::logic()
{}

void PauseMenu::handleEvent(SDL_Event *event) {
	Menu::handleEvent(event);
	
	switch (event->type)
	{
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE && event->key.repeat == false)
				SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
			break;
	}
}