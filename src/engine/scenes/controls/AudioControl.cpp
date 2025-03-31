#include "engine/scenes/controls/AudioControl.h"
#include "game/Game.h"

int AudioControl::getVolumeBarIndex(){
    return (int)(volume*(float)getButtonCount())-1;
}

int AudioControl::getButtonCount(){
    return (int)(sizeof(this->volumeButtons) / sizeof(AudioButton*));
}

void AudioControl::volumeUp() {
#ifdef DEBUG
    SDL_Log("Volume up");
#endif
    this->setVolume(volumeButtons[std::min(getVolumeBarIndex()+1, getButtonCount()-1)]->value);
}

void AudioControl::volumeDown() {
#ifdef DEBUG
    SDL_Log("Volume down");
#endif
    // this->setVolume(volumeButtons[std::max(getVolumeBarIndex()-1, 0)]->value);
    if (getVolumeBarIndex() > 0) this->setVolume(volumeButtons[getVolumeBarIndex() - 1]->value);
    else this->setVolume(0);
}

void AudioControl::setVolume(float value) {
    this->volume = value;
    int index = getVolumeBarIndex();
    int buttonCount = getButtonCount();
    for (int i = 0; i < buttonCount; i++){
        if(i<=index){
            volumeButtons[i]->activated = true;
        }
        else{
            volumeButtons[i]->activated = false;
        }
    }
    Game::soundManager.setVolume(volume);
#ifdef DEBUG
    SDL_Log("Setting volume to %f up to bar at index %d", value, getVolumeBarIndex());
#endif
}

AudioControl::AudioControl(double x, double y, double width, double height): Control(x, y, width, height) {
#ifdef DEBUG
    SDL_Log("width - height = %f", width-height);
#endif

    this->plusButton = new Button(width - height+x, y, height, height, 0, 1, Game::textures.at("button.png"), [this] -> void{this->volumeUp();}, "+");
    this->minusButton = new Button(x, y, height, height, 0, 1, Game::textures.at("button.png"), [this] -> void{this->volumeDown();}, "-");

    const int buttonCount = getButtonCount();
    const double gap = 5;
    const double audioButtonWidth = (width - 2*height - (buttonCount+1)*gap)/buttonCount;
#ifdef DEBUG
    SDL_Log("Audio button width: %f", audioButtonWidth);
    SDL_Log("Button count: %d", buttonCount);
#endif
    for (int i = 0; i < buttonCount;i++){
        volumeButtons[i] = new AudioButton(height+i*audioButtonWidth+(i+1)*gap+x, y, audioButtonWidth, height, 1, nullptr, (float)(i+1)/(float)buttonCount);
        volumeButtons[i]->action = [this, i] -> void{
#ifdef DEBUG
			SDL_Log("Setting volume to: %f", this->volumeButtons[i]->value);
#endif
			setVolume(this->volumeButtons[i]->value);
		};
    }
    setVolume(Game::soundManager.getVolume());
}


void AudioControl::render() {
    SceneElement::render();
    plusButton->render();
    for(const auto& element: volumeButtons){
        element->render();
    }
    minusButton->render();
}

void AudioControl::click(float x, float y) const {
    for (const auto& button:volumeButtons) {
        if (x >= button->x && x <= button->x + button->width &&
            y >= button->y && y <= button->y + button->height) {
            button->click(x, y);
            return;
        }
    }
    if (x >= minusButton->x && x <= minusButton->x + minusButton->width &&
        y >= minusButton->y && y <= minusButton->y + minusButton->height) {
        minusButton->click(x, y);
    }
    else if (x >= plusButton->x && x <= plusButton->x + plusButton->width &&
         y >= plusButton->y && y <= plusButton->y + plusButton->height) {
        plusButton->click(x, y);
    }
}

AudioControl::~AudioControl() {
    delete minusButton;
    delete plusButton;
    for (const auto& button : volumeButtons){
        delete button;
    }
}
