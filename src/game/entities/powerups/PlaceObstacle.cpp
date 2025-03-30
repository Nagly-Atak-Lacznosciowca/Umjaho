#include "game/entities/powerups/PlaceObstacle.h"
#include "game/Game.h"

PlaceObstacle::PlaceObstacle(double x, double y, Obstacle* obstacle, double width, double height, double angle, double zIndex): PowerUp(x,y,width,height,angle,zIndex, obstacle->texture), obstacle(obstacle){};


void PlaceObstacle::action(Player *player) {
    player->holdingObstacle = this->obstacle;
}
