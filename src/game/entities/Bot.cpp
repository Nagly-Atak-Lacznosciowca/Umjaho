#include "game/entities/Bot.h"
#include "SDL3/SDL.h"
#include <cmath>

Bot::Bot(const double x, const double y, const double width, const double length, const double angle, const double zIndex, SDL_Texture* texture) : Car(
        x, y, 0, -1, width, length, angle, zIndex, texture) {}

void Bot::update() {
    if (!canMove) return;

    double bestTurn = 0.0;
    double bestScore = -1e9;

    for (double testTurn = -maxTurnAngle; testTurn <= maxTurnAngle; testTurn += maxTurnAngle / 5) {
        double score = evaluateTurn(0);
        if (score > bestScore) {
            bestScore = score;
            bestTurn = testTurn;
        }
    }

    turnAngle = bestTurn;

    if (std::abs(bestTurn) > maxTurnAngle / 2) {
        speed = std::max(speed - brakeStrength, 1.0);
    } else {
        speed = std::min(speed + acceleration, maxSpeed);
    }

    move();
}

double Bot::evaluateTurn(double testTurn) {
    double score = 0.0;

//    double futureAngle = angle + testTurn;
//    double futureX = x + cos(futureAngle) * speed;
//    double futureY = y + sin(futureAngle) * speed;
//
//    Vector2D target = waypoints[currentWaypoint];
//    double targetAngle = atan2(target.y - futureY, target.x - futureX);
//
//    double alignmentScore = 100 - fabs(futureAngle - targetAngle) * 10;
//    score += alignmentScore;
//
//    if (isObstacleNearby(futureX, futureY)) {
//        score -= 1000;
//    }

    return score;
}
