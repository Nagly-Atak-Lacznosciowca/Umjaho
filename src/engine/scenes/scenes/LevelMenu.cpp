#include <stdexcept>

#include "engine/scenes/scenes/LevelMenu.h"
#include "game/Game.h"
#include "engine/scenes/scenes/Level1.h"
#include "engine/scenes/scenes/Level2.h"
#include "engine/scenes/scenes/Level3.h"
#include "engine/scenes/controls/LevelButton.h"
#include "game/Event.h"

void startLevel1() {
	SDL_PushEvent(new SDL_Event {
		.user = {
			.type = Event::CUSTOM_EVENT_PUSH_SCENE,
			.data1 = new Level1()
		}
	});
}

void startLevel2() {
	Game::sceneManager.pushScene(new Level2());
}

void startLevel3() {
	Game::sceneManager.pushScene(new Level3());
}

LevelMenu::LevelMenu() {
	this->background = Game::textures.at("level-menu.bmp");
	
	int *windowWidth = new int();
	int *windowHeight = new int();

	SDL_GetWindowSizeInPixels(Game::renderer.SDLWindow, windowWidth, windowHeight);

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
	
	auto returnButton = new Button(100*scaleX, 50*scaleY, 200*scaleX, 55*scaleY, 0, 1, Game::textures.at("button.bmp"), [] {SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});}, "Return");

	auto *level1Button = new LevelButton<Level1>((double)(gapX * 1 + blockWidth * 0) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("level-button.bmp"), "Level 1", Game::textures.at("track1.bmp"));
	auto *level2Button = new LevelButton<Level2>((double)(gapX * 2 + blockWidth * 1) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("level-button.bmp"), "Level 2", Game::textures.at("track2.bmp"));
	auto *level3Button = new LevelButton<Level3>((double)(gapX * 3 + blockWidth * 2) * scaleX, (double)gapY * scaleY, blockWidth * scaleX, blockHeight * scaleY, 0, 1, Game::textures.at("level-button.bmp"), "Level 3", Game::textures.at("track3.bmp"));
	
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
			if (event->key.scancode == SDL_SCANCODE_ESCAPE && event->key.repeat == false)
				SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
			break;
	}
}