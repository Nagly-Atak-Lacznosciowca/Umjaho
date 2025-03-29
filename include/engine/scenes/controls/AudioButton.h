#ifndef UMJAHO_AUDIOBUTTON_H
#define UMJAHO_AUDIOBUTTON_H

#include "Button.h"

class AudioButton: public Button{
public:
    AudioButton(double x, double y, double width, double height, double zIndex,
           const std::function<void()> &action, float value);

    float value;
    bool activated = false;

    void render() override;
};

#endif //UMJAHO_AUDIOBUTTON_H
