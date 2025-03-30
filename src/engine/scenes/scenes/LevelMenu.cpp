#include <stdexcept>

#include "engine/scenes/scenes/LevelMenu.h"
#include "game/Game.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/controls/LevelButton.h"

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
	
	auto returnButton = new Button(100*scaleX, 50*scaleY, 200*scaleX, 55*scaleY, 0, 1, Game::textures.at("button.bmp"), [] {Game::sceneManager.popScene();}, "Return");

	auto *level1Button = new LevelButton((double)(gapX * 1 + blockWidth * 0) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("level-button.bmp"), new Level1, "Level 1", Game::textures.at("level1.bmp"));
	auto *level2Button = new LevelButton((double)(gapX * 2 + blockWidth * 1) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("level-button.bmp"), nullptr, "Level 2", nullptr);
	auto *level3Button = new LevelButton((double)(gapX * 3 + blockWidth * 2) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("level-button.bmp"), nullptr, "Level 3", nullptr);
	
	this->contents.push_back(returnButton);
	
	this->contents.push_back(level1Button);
	this->contents.push_back(level2Button);
	this->contents.push_back(level3Button);
}

void LevelMenu::logic()
{}

void LevelMenu::handleEvent(SDL_Event *event) {
	Menu::handleEvent(event);
	
	switch (event->type)
	{
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
				Game::sceneManager.popScene();
			break;
	}
}