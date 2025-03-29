#include "engine/scenes/scenes/MainMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/Button.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/LevelMenu.h"
#include "engine/scenes/scenes/SettingsMenu.h"
#include "engine/scenes/scenes/Menu.h"

void MainMenu::goToLevelMenu() {
	Game::sceneManager.pushScene(new LevelMenu());
}

void MainMenu::goToSettingsMenu(){
    Game::sceneManager.pushScene(new SettingsMenu());
}

void MainMenu::exitGame(){
    SDL_PushEvent(new SDL_Event{SDL_EVENT_QUIT});
}

MainMenu::MainMenu() {
    this->background = Game::textures.at("title.bmp");
	
	int *windowWidth = new int();
	int *windowHeight = new int();

	SDL_GetWindowSize(Game::renderer.SDLWindow, windowWidth, windowHeight);

	const int width = *windowWidth;
	const int height = *windowHeight;

	delete windowWidth;
	delete windowHeight;

    const float scaleX = (float)width / (float)this->background->w;
    const float scaleY = (float)height / (float)this->background->h;

    auto *playButton = new Button(2304 * scaleX, 1168 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::goToLevelMenu);
    auto *settingsButton = new Button(2304 * scaleX, 1389 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::goToSettingsMenu);
    auto *exitButton = new Button(2304 * scaleX, 1838 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, MainMenu::exitGame);
	
    this->contents.push_back(playButton);
    this->contents.push_back(settingsButton);
    this->contents.push_back(exitButton);
}

void MainMenu::logic()
{}

void MainMenu::handleEvent(SDL_Event *event) {
    Menu::handleEvent(event);
}
