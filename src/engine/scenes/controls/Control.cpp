#include <stdexcept>
#include "engine/scenes/controls/Control.h"

Control::Control(double x, double y, double width, double height, double angle, double zIndex, SDL_Texture *texture): SceneElement(x,y,width,height,angle,zIndex,texture) {}

void Control::click(float x, float y) {}