#ifndef UMJAHO_NITROBATTERY_H
#define UMJAHO_NITROBATTERY_H

#include "engine/scenes/SceneElement.h"

class NitroBattery : public SceneElement {
	public:
		int state = 0;
		
		NitroBattery(double x, double y, double width, double height, double angle = 0, double zIndex = 0, int state = 0);
		~NitroBattery() = default;
		
		void setState(int value);
};

#endif //UMJAHO_NITROBATTERY_H
