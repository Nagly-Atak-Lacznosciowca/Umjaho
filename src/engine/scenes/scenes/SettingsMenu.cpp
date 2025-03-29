#include "engine/scenes/scenes/SettingsMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/AudioControl.h"

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

    auto button = new Button(100*scaleX, 50*scaleY, 200*scaleX, 50*scaleY, 0, 1, Game::textures["button.bmp"], [] {Game::sceneManager.popScene();}, "Return");

    auto audioControl = new AudioControl(100*scaleX, 200*scaleY, 500*scaleX, 50*scaleY);


    contents.push_back(button);
    contents.push_back(audioControl);
}

void SettingsMenu::handleEvent(SDL_Event *event) {
    switch (event->type) {
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            if (event->button.button == SDL_BUTTON_LEFT) {
                float xPos, yPos;
                SDL_GetMouseState(&xPos, &yPos);

                for (const auto &sceneElement : this->contents) {
                    if (auto *control = dynamic_cast<Control*>(sceneElement)) {
                        if (xPos >= control->x && xPos <= control->x + control->width &&
                            yPos >= control->y && yPos <= control->y + control->height) {
                            SDL_Log("click %f %f", xPos, yPos);
                            control->click(xPos, yPos);
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
