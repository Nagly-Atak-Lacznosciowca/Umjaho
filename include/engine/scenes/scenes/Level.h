#ifndef UMJAHO_LEVEL_H
#define UMJAHO_LEVEL_H

#include "engine/scenes/Scene.h"
#include "game/entities/Player.h"
#include "game/entities/Bot.h"
#include "Checkpoint.h"

class Level: public Scene {
	public:
		Player *player = nullptr;
		Bot* opponents[4] = {};
		std::vector<Checkpoint*> checkpoints;

	    Level() = default;
		
	    void logic() override;
	    void handleEvent(SDL_Event* event) override;
        void render() override;
};

#endif //UMJAHO_LEVEL_H
