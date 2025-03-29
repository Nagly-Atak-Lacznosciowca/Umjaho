#include <stdexcept>

#include "engine/scenes/scenes/LevelMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/Button.h"
#include "engine/scenes/scenes/Level1.h"

void startLevel1() {
	Game::sceneManager.pushScene(new Level1());
}

void startLevel2() {
	throw std::runtime_error("Not implemented");
}

void startLevel3() {
	throw std::runtime_error("Not implemented");
}

LevelMenu::LevelMenu() {
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
	
	const auto blockWidth = 400;
	const auto blockHeight = 600;
	
	const auto elementCount = 3;
	
	const auto gapX = (this->background->w - elementCount * blockWidth) / (elementCount + 1);
	const auto gapY = (this->background->h - blockHeight) / 2;

	auto *level1Button = new Button((double)(gapX * 1 + blockWidth * 0) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), startLevel1);
	auto *level2Button = new Button((double)(gapX * 2 + blockWidth * 1) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), startLevel2);
	auto *level3Button = new Button((double)(gapX * 3 + blockWidth * 2) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("button.bmp"), startLevel3);

	this->contents.push_back(level1Button);
	this->contents.push_back(level2Button);
	this->contents.push_back(level3Button);
}

void LevelMenu::logic()
{
}

void LevelMenu::handleEvent(SDL_Event *event) {
	switch (event->type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN: {
			if (event->button.button == SDL_BUTTON_LEFT) {
				float xPos, yPos;
				SDL_GetMouseState(&xPos, &yPos);
				
				for (const auto &sceneElement : this->contents) {
					if (auto *button = dynamic_cast<Button*>(sceneElement)) {
						if (xPos >= button->x && xPos <= button->x + button->width &&
						yPos >= button->y && yPos <= button->y + button->height) {
							button->click(xPos,yPos);
						}
					}
				}
			}
			
			break;
		}
	}
}