#ifndef UMJAHO_LEVEL_H
#define UMJAHO_LEVEL_H

#include "engine/scenes/Scene.h"
#include "game/entities/Player.h"
#include "game/entities/Opponent.h"
#include "engine/scenes/Text.h"
#include "engine/scenes/NitroBattery.h"

class Level: public Scene{
	public:
		Player *player = nullptr;
		Opponent* opponents[4] = {};
		NitroBattery *nitroCounter = nullptr;
		Uint64 startTime = 0;
		Uint64 lapStartTime = 0;
		int laps = 3;
		int currentLap = 0;
		Uint64 ticks = 0;
		Uint64 lapTimes[3] = {};
		Uint64 currentLapTime = 0;

		Level();
		
		void logic() override;
		void handleEvent(SDL_Event* event) override;

		void lap();
};

#endif //UMJAHO_LEVEL_H
