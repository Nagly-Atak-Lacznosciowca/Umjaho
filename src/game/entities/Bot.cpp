#include "game/entities/Bot.h"
#include "SDL3/SDL.h"
#include <cmath>

Bot::Bot(const double x, const double y, const double width, const double length, const double angle, const double zIndex, SDL_Texture* texture) : Car(
        x, y, 0, -1, width, length, angle, zIndex, texture) {}

//double Bot::evaluateTurn(double testTurn) {
//    double score = 0.0;
//
//    double futureAngle = angle + testTurn;
//    double futureX = x + cos(futureAngle) * speed;
//    double futureY = y + sin(futureAngle) * speed;
//
//    Vector2D target = nextCheckpoint;
//    double targetAngle = atan2(target.y - futureY, target.x - futureX);
//
//    double alignmentScore = 100 - fabs(futureAngle - targetAngle) * 10;
//    score += alignmentScore;
//
//    if (isObstacleNearby(futureX, futureY)) {
//        score -= 1000;
//    }
//
//    return score;
//}
