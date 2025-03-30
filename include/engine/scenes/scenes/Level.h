#ifndef UMJAHO_LEVEL_H
#define UMJAHO_LEVEL_H

#include "engine/scenes/Scene.h"
#include "game/entities/Player.h"
#include "game/entities/Opponent.h"
#include "engine/scenes/Text.h"

class Level: public Scene{
	public:
		Player *player = nullptr;
		Opponent* opponents[4] = {};
		Text *nitroCounter = nullptr;

		Level();
		
		void logic() override;
		void handleEvent(SDL_Event* event) override;
};

#endif //UMJAHO_LEVEL_H
