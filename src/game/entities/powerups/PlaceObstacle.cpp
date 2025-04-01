#include "game/entities/powerups/PlaceObstacle.h"
#include "game/Game.h"
#include "game/entities/obstacles/Cone.h"
#include "game/entities/obstacles/Oil.h"
#include "game/entities/obstacles/Water.h"

PlaceObstacle::PlaceObstacle(double x, double y, Obstacle* obstacle, double width, double height, double angle, double zIndex): PowerUp(x,y,width,height,angle,zIndex, Game::textures.at("question_mark.png")), obstacle(obstacle) {
    if (obstacle == nullptr) {
        std::array<Obstacle*, 3> obstacles = {
            new Cone(x, y),
            new Water(x, y),
            new Oil(x, y)
        };
        this->obstacle = obstacles[rand() % 3];
    }
    else {
        this->obstacle = obstacle;
    }
};


void PlaceObstacle::action(Player *player) {
    player->heldObstacle = this->obstacle;
}
