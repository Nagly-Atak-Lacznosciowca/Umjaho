#include "engine/scenes/scenes/Menu.h"
#include "game/Game.h"
#include "game/entity/Button.h"

Menu::Menu(const std::function<void()>& playButtonAction) {
    this->background = Game::textures.at("title.bmp");
    const float scaleX = 1600.0f / (float)(this->background->w);
    const float scaleY = 900.0f / (float)(this->background->h);

    auto *playButton = new Button(2304 * scaleX, 1168 * scaleY, 1280 * scaleX, 192 * scaleY, 0, 1, nullptr, playButtonAction);
    this->contents.push_back(playButton);
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
