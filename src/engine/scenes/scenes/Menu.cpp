#include "engine/scenes/scenes/Menu.h"
#include "game/Game.h"
#include "game/entity/Button.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/LevelMenu.h"
#include "engine/scenes/scenes/SettingsMenu.h"

void goToLevelMenu() {
	Game::sceneManager.pushScene(new LevelMenu());
}
void goToSettingsMenu(){
    Game::sceneManager.pushScene(new SettingsMenu());
}
void exitGame(){
    SDL_PushEvent(new SDL_Event{SDL_EVENT_QUIT});
}

Menu::Menu() {
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

    auto *playButton = new Button(2304 * scaleX, 1168 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, goToLevelMenu);
    auto *settingsButton = new Button(2304 * scaleX, 1389 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, goToSettingsMenu);
    auto *exitButton = new Button(2304 * scaleX, 1838 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, exitGame);
	
    this->contents.push_back(playButton);
    this->contents.push_back(settingsButton);
    this->contents.push_back(exitButton);
}

void Menu::logic() {
    // TODO: button hovers 

}

void Menu::handleEvent(SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            if (event->button.button == SDL_BUTTON_LEFT) {
                float xPos, yPos;
                SDL_GetMouseState(&xPos, &yPos);

                for (const auto &sceneElement : this->contents) {
                    if (auto *button = dynamic_cast<Button*>(sceneElement)) {
                        if (xPos >= button->x && xPos <= button->x + button->width &&
                            yPos >= button->y && yPos <= button->y + button->height) {
                            button->click();
                        }
                    }
                }
            }
        }
    }
} // this indentation sucks ass
