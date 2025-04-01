#include "game/Game.h"
#include "game/Event.h"

template <typename LevelClass>
LevelButton<LevelClass>::LevelButton(double x, double y, double width, double height, double angle, double zIndex,
                         SDL_Texture *texture, const std::string &text, SDL_Texture* image, int levelId): Button(x,y,width,height,angle, zIndex,texture,
                                                                                                                  nullptr), image(image), levelId(levelId) {
    if(!text.empty()){
		const auto scale = height / 600;
        this->text = new Text(0, 0, 0, height/8, angle, zIndex, text);
	    this->text->x = x + width/2 - this->text->width/2;
	    this->text->y = y + 50 * scale - this->text->height/2;
    }
	
	bestTime = nullptr;
	
	left = false;
	
	const auto scale = height / 600;
	bestTimeText =
	new Text(0,
	0,
	0,
	height / 8 / 2,
	angle,
	zIndex);
	
	const auto bestestTime = std::min_element(Game::playerTimes[levelId].begin(), Game::playerTimes[levelId].end(),
	[](const std::pair<Uint64, Uint64>& a, const std::pair<Uint64, Uint64>& b) {
		return a.first < b.first;
	});
	
	if (bestestTime != Game::playerTimes[levelId].end())
	{
		bestTime = new Uint64(bestestTime->first);
		
		const auto minutes = static_cast<int>((*bestTime)) / 6000;
		const auto seconds = static_cast<int>((*bestTime)) / 100 - minutes * 60;
		const auto milliseconds = static_cast<int>((*bestTime)) - seconds * 100 - minutes * 6000;
		
		bestTimeText->setContent(std::format("Best: {:02}:{:02}:{:02}", minutes, seconds, milliseconds));
		this->bestTimeText->x = x + width / 2 - this->bestTimeText->width / 2;
		this->bestTimeText->y = y + 550 * scale - this->bestTimeText->height / 2;
	}
};

template <typename LevelClass>
void LevelButton<LevelClass>::click(float x, float y) {
    SDL_PushEvent(new SDL_Event {
        .user = {
            .type = Event::CUSTOM_EVENT_PUSH_SCENE,
			.data1 = new LevelClass()
        }
	});
	
	left = true;
}

template <typename LevelClass>
void LevelButton<LevelClass>::render() {
    Button::render();
	
	const auto mapWidth = 390;
	const auto mapHeight = 390;
	
    SDL_RenderTexture(Game::renderer.SDLRenderer, this->image, nullptr,
                      new SDL_FRect{static_cast<float>(x + width/2 - (float)mapWidth/2), static_cast<float>(y + height/2 - (float)mapHeight/2), static_cast<float>(mapWidth), static_cast<float>(mapHeight)});
	
	if (left)
	{
		left = false;
		
		const auto bestestTime = std::min_element(Game::playerTimes[levelId].begin(), Game::playerTimes[levelId].end(),
		[](const std::pair<Uint64, Uint64> &a, const std::pair<Uint64, Uint64> &b)
		{
			return a.first < b.first;
		});
		
		if (bestestTime != Game::playerTimes[levelId].end())
		{
			if (bestTime == nullptr)
			{
				bestTime = new Uint64();
				*bestTime = bestestTime->first;
				
				const auto minutes = static_cast<int>((*bestTime)) / 6000;
				const auto seconds = static_cast<int>((*bestTime)) / 100 - minutes * 60;
				const auto milliseconds = static_cast<int>((*bestTime)) - seconds * 100 - minutes * 6000;
				
				const auto scale = height / 600;
				bestTimeText->setContent(std::format("Best: {:02}:{:02}:{:02}", minutes, seconds, milliseconds));
				this->bestTimeText->x = x + width / 2 - this->bestTimeText->width / 2;
				this->bestTimeText->y = y + 550 * scale - this->bestTimeText->height / 2;
			}
			
			if (bestestTime->first < *bestTime)
			{
				*bestTime = bestestTime->first;
				
				const auto minutes = static_cast<int>((*bestTime)) / 6000;
				const auto seconds = static_cast<int>((*bestTime)) / 100 - minutes * 60;
				const auto milliseconds = static_cast<int>((*bestTime)) - seconds * 100 - minutes * 6000;
				
				const auto scale = height / 600;
				bestTimeText->setContent(std::format("Best: {:02}:{:02}:{:02}", minutes, seconds, milliseconds));
				this->bestTimeText->x = x + width / 2 - this->bestTimeText->width / 2;
				this->bestTimeText->y = y + 550 * scale - this->bestTimeText->height / 2;
			}
		}
	}
	
	bestTimeText->render();
}

