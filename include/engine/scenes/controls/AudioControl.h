#ifndef UMJAHO_AUDIOCONTROL_H
#define UMJAHO_AUDIOCONTROL_H

#include "AudioButton.h"


class AudioControl: public Control{
public:
    AudioControl(double x, double y, double width, double height);
    ~AudioControl() override;
    Button* plusButton;
    Button* minusButton;
    AudioButton* volumeButtons[8] = {nullptr};

    float volume;

    void setVolume(float value);
    void volumeUp();
    void volumeDown();
    int getVolumeBarIndex();
    int getButtonCount();
    void render() override;

    void click(float x, float y) const override;
};

#endif //UMJAHO_AUDIOCONTROL_H
