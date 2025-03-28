#include "engine/scenes/scenes/SettingsMenu.h"
#include "game/entity/Button.h"
#include "game/Game.h"

void returnToMenu(){
    Game::sceneManager.popScene();
}

SettingsMenu::SettingsMenu() {
    this->background = Game::textures.at("level-menu.bmp");

    int *windowWidth = new int();
    int *windowHeight = new int();

    SDL_GetWindowSize(Game::renderer.SDLWindow, windowWidth, windowHeight);

    const int width = *windowWidth;
    const int height = *windowHeight;

    delete windowWidth;
    delete windowHeight;

    const float scaleX = (float)width / (float)this->background->w;
    const float scaleY = (float)height / (float)this->background->h;

    auto button = new Button(100*scaleX, 50*scaleY, 200*scaleX, 50*scaleY, 0, 1, Game::textures["button.bmp"], returnToMenu, "Return");

    contents.push_back(button);
}

void SettingsMenu::handleEvent(SDL_Event *event) {
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

            break;
        }
    }
}

void SettingsMenu::logic() {

}
