#ifndef UMJAHO_PLACEOBSTACLE_H
#define UMJAHO_PLACEOBSTACLE_H

#include "PowerUp.h"

class PlaceObstacle: public PowerUp{
    public:
        Obstacle* obstacle;
        PlaceObstacle(double x, double y, Obstacle* obstacle = nullptr, double width = 40, double height = 40, double angle = 0, double zIndex = 1);
        void action(Player* player) override;
};

#endif //UMJAHO_PLACEOBSTACLE_H
