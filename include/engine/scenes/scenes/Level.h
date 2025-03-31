#ifndef UMJAHO_LEVEL_H
#define UMJAHO_LEVEL_H

#include "engine/scenes/Scene.h"
#include "game/entities/Player.h"
#include "game/entities/Bot.h"
#include "engine/scenes/Text.h"
#include "Checkpoint.h"

class Level: public Scene {
	public:
		Player *player = nullptr;
        Text *nitroCounter = nullptr;
        std::vector<Bot *> opponents;

		Level();
        std::vector<Checkpoint*> checkpoints;

		void logic() override;
	    void handleEvent(SDL_Event* event) override;
        void render() override;
        void sceneElementLogic(SceneElement* element);
};

#endif //UMJAHO_LEVEL_H
