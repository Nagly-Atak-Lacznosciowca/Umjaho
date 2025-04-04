#ifndef UMJAHO_CREDITS_H
#define UMJAHO_CREDITS_H

#include "engine/scenes/Scene.h"
#include "engine/sounds/SoundPlayback.h"

class Credits : public Scene {
	public:
		Credits();
		~Credits() override = default;
		
		void logic() override;
		void handleEvent(SDL_Event* event) override;
};

#endif //UMJAHO_CREDITS_H
