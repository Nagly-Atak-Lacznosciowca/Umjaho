#include "engine/scenes/scenes/SettingsMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/AudioControl.h"
#include "game/Event.h"

void exitScene(){
	SDL_PushEvent(new SDL_Event {Event::CUSTOM_EVENT_POP_SCENE});
}

SettingsMenu::SettingsMenu() {
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

    auto button = new Button(100*scaleX, 50*scaleY, 200*scaleX, 50*scaleY, 0, 1, Game::textures.at("button.bmp"), exitScene, "Return");
	
	const float settingsX = 200.0f;
	const float labelGap = 10.0f;
	
	Text *audioLabel = new Text(settingsX * scaleX, 200*scaleY, 0, 50 * scaleY, 0, 1, "Volume");
	
    auto audioControl = new AudioControl((settingsX + labelGap + (float)audioLabel->width) * scaleX, 200*scaleY, 500*scaleX, 50*scaleY);

    contents.push_back(button);
	contents.push_back(audioLabel);
    contents.push_back(audioControl);
}

void SettingsMenu::logic()
{}

void SettingsMenu::handleEvent(SDL_Event *event) {
	Menu::handleEvent(event);
	
	switch (event->type)
	{
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
                exitScene();
			break;
	}
}

SettingsMenu::~SettingsMenu() {
    SDL_Log("Destruct settings");
}
