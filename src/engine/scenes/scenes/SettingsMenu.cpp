#include "engine/scenes/scenes/SettingsMenu.h"
#include "game/Game.h"
#include "engine/scenes/controls/AudioControl.h"
#include "game/Event.h"

Button* FPSButton = nullptr;

void exitScene(){
	SDL_PushEvent(new SDL_Event { Event::CUSTOM_EVENT_POP_SCENE });
}

void changeCarColor(std::string color) {
    Game::playerColor = color;
    SDL_PushEvent(new SDL_Event { Event::CUSTOM_EVENT_PLAYER_CHANGE_COLOR });
}

void switchFPS() {
	Game::showFPS = !Game::showFPS;
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

    auto returnButton = new Button(100*scaleX, 50*scaleY, 200*scaleX, 50*scaleY, 0, 1, Game::textures.at("button.bmp"), exitScene, "Return");
	
	const float settingsX = 200.0f;
	const float labelGap = 10.0f;
	
	Text *audioLabel = new Text(settingsX * scaleX, 200*scaleY, 0, 50 * scaleY, 0, 1, "Volume");
	
    auto audioControl = new AudioControl((settingsX + labelGap + (float)audioLabel->width) * scaleX, 200*scaleY, 500*scaleX, 50*scaleY);

    auto setCarColorBlueButton = new Button(200 * scaleX, 300 * scaleY, 100 * scaleX, 100 * scaleY, 0, 0, Game::textures.at("car-blue-regular.bmp"), []{ changeCarColor("blue"); }, "");
    auto setCarColorGreenButton = new Button(310 * scaleX, 300 * scaleY, 100 * scaleX, 100 * scaleY, 0, 0, Game::textures.at("car-green-regular.bmp"), []{ changeCarColor("green"); }, "");
    auto setCarColorOrangeButton = new Button(420 * scaleX, 300 * scaleY, 100 * scaleX, 100 * scaleY, 0, 0, Game::textures.at("car-orange-regular.bmp"), []{ changeCarColor("orange"); }, "");
    auto setCarColorPurpleButton = new Button(530 * scaleX, 300 * scaleY, 100 * scaleX, 100 * scaleY, 0, 0, Game::textures.at("car-purple-regular.bmp"), []{ changeCarColor("purple"); }, "");
    auto setCarColorRedButton = new Button(640 * scaleX, 300 * scaleY, 100 * scaleX, 100 * scaleY, 0, 0, Game::textures.at("car-red-regular.bmp"), []{ changeCarColor("red"); }, "");
    auto setCarColorYellowButton = new Button(750 * scaleX, 300 * scaleY, 100 * scaleX, 100 * scaleY, 0, 0, Game::textures.at("car-yellow-regular.bmp"), []{ changeCarColor("yellow"); }, "");
    currentCarColorLabel = new Text(200 * scaleX, 410 * scaleY, 0, 35, 0, 0, "Current car color: " + Game::playerColor);

    contents.push_back(returnButton);
    contents.push_back(audioLabel);
    contents.push_back(audioControl);
    contents.push_back(setCarColorBlueButton);
    contents.push_back(setCarColorGreenButton);
    contents.push_back(setCarColorOrangeButton);
    contents.push_back(setCarColorPurpleButton);
    contents.push_back(setCarColorRedButton);
    contents.push_back(setCarColorYellowButton);
    contents.push_back(currentCarColorLabel);

	Text *FPSLabel = new Text(settingsX * scaleX, 500*scaleY, 0, 50 * scaleY, 0, 1, "Show FPS");
	FPSButton = new Button((settingsX + labelGap + (float)FPSLabel->width) * scaleX, 500*scaleY, 100*scaleX, 50*scaleY, 0, 1, Game::textures.at("button.bmp"), [] {switchFPS();}, Game::showFPS ? "ON" : "OFF");

	contents.push_back(FPSLabel);
	contents.push_back(FPSButton);
}

void SettingsMenu::logic() {
	if (Game::showFPS) {
		if (FPSButton->text->content != "ON") {
			FPSButton->setText("ON");
		}
	}
	else {
		if (FPSButton->text->content != "OFF") {
			FPSButton->setText("OFF");
		}
	}
}

void SettingsMenu::handleEvent(SDL_Event *event) {
	Menu::handleEvent(event);
	
	switch (event->type) {
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_ESCAPE)
                exitScene();
			break;

        case Event::CUSTOM_EVENT_PLAYER_CHANGE_COLOR: {
#ifdef DEBUG
            SDL_Log(Game::playerColor.data());
#endif
            currentCarColorLabel->setContent("Current car color: " + Game::playerColor);
            break;
        }
	}
}

SettingsMenu::~SettingsMenu() {
#ifdef DEBUG
    SDL_Log("Destruct settings");
#endif
}
