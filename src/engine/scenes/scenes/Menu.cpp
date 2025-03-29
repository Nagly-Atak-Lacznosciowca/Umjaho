#include "engine/scenes/scenes/Menu.h"
#include "engine/scenes/controls/Button.h"

void Menu::logic() {}

void Menu::handleEvent(SDL_Event *event) {
	switch (event->type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event->button.button == SDL_BUTTON_LEFT) {
				float xPos, yPos;
				SDL_GetMouseState(&xPos, &yPos);
				
				for (const auto &sceneElement : this->contents) {
					if (auto *control = dynamic_cast<Control*>(sceneElement)) {
						if (xPos >= control->x && xPos <= control->x + control->width &&
						yPos >= control->y && yPos <= control->y + control->height) {
							control->click(xPos,yPos);
						}
					}
				}
			}
			
			break;
	}
}
