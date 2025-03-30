#include "engine/scenes/scenes/MainMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/Button.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/LevelMenu.h"
#include "engine/scenes/scenes/SettingsMenu.h"
#include "engine/scenes/scenes/Menu.h"
#include "engine/scenes/scenes/Credits.h"
#include "game/Event.h"

void MainMenu::goToLevelMenu() {
	SDL_PushEvent(new SDL_Event {
		.user = {
			.type = Event::CUSTOM_EVENT_PUSH_SCENE,
			.data1 = new LevelMenu()
		}
	});
}

void MainMenu::goToSettingsMenu(){
	SDL_PushEvent(new SDL_Event {
		.user = {
			.type = Event::CUSTOM_EVENT_PUSH_SCENE,
			.data1 = new SettingsMenu()
		}
	});
}

void MainMenu::goToCredits() {
	SDL_PushEvent(new SDL_Event {
		.user = {
			.type = Event::CUSTOM_EVENT_PUSH_SCENE,
			.data1 = new Credits()
		}
	});
}

void MainMenu::exitGame(){
    SDL_PushEvent(new SDL_Event{SDL_EVENT_QUIT});
}

MainMenu::MainMenu() {
    this->background = Game::textures.at("title.bmp");
	
	int *windowWidth = new int();
	int *windowHeight = new int();

	SDL_GetWindowSizeInPixels(Game::renderer.SDLWindow, windowWidth, windowHeight);

	const int width = *windowWidth;
	const int height = *windowHeight;

	delete windowWidth;
	delete windowHeight;

    const float scaleX = (float)width / (float)this->background->w;
    const float scaleY = (float)height / (float)this->background->h;

    auto *playButton = new Button(2304 * scaleX, 1168 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::goToLevelMenu);
    auto *settingsButton = new Button(2304 * scaleX, 1389 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::goToSettingsMenu);
	auto *creditsButton = new Button(2304 * scaleX, 1612 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::goToCredits);
    auto *exitButton = new Button(2304 * scaleX, 1838 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::exitGame);
	
    this->contents.push_back(playButton);
    this->contents.push_back(settingsButton);
	this->contents.push_back(creditsButton);
    this->contents.push_back(exitButton);
}

void MainMenu::logic()
{}

void MainMenu::handleEvent(SDL_Event *event) {
    Menu::handleEvent(event);
}
