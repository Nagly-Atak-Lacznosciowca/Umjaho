#include "game/entity/Car.h"

#include <cmath>

#include "game/Game.h"
#include "SDL3/SDL.h"
#include "engine/Renderer.h"
#include "array"

const double Car::WIDTH = 50;
const double Car::LENGTH = 100;
const double Car::NITRO_MULTIPLIER = 1.8;
const int Car::NEEDED_CHARGES = 3;
const int Car::NITRO_TIME = 500;

// length 3 array [dx, dy, dz]
void Car::move() {
    double vector[] = {
        this->x + this->speed * SDL_sin(this->angle),
        this->y + this->speed * SDL_cos(this->angle)
    };
    this->x = vector[0];
    this->y = vector[1];
}

Car::Car(const double x, const double y, const double width, const double length, const double angle, const double zIndex, SDL_Texture* texture) : SceneElement(x, y, width, length, angle, zIndex, texture) {
    isCollidable = true;
}

void Car::decelerate() {
    if (speed > 0) {
        speed -= acceleration / 1.5;
    }
    else if (speed < 0) {
        speed += acceleration / 1.5;
    }
    if (speed > -this->acceleration && speed < this->acceleration) {
        speed = 0;
    }
}

void Car::accelerate() {
    if (speed + acceleration < maxSpeed) {
        speed += acceleration;
    }
    else speed = maxSpeed;
}

void Car::brake() {
    speed -= brakeStrength;
}

void Car::reverse() {
    if (speed - acceleration/1.4 > -maxSpeed/2) {
        speed -= acceleration / 1.4;
    }
    else speed = -maxSpeed / 2;
}

void Car::turnLeft() {
    if (speed < maxSpeed/2) {
        maxTurnAngle = (SDL_fabs(speed) / (maxSpeed/2)) * 0.03;     // why tf is fabs double
    }
    else maxTurnAngle = 0.03;
    if (speed > 0) {
        if (turnAngle + turnGain < maxTurnAngle) {
            turnAngle += turnGain;
        }
        else turnAngle = maxTurnAngle;
        angle += turnAngle;
    }
    else if (speed < 0) {
        if (turnAngle - turnGain > -maxTurnAngle) {
            turnAngle -= turnGain;
        }
        else turnAngle = -maxTurnAngle;
        angle += turnAngle;
    }
    else {
        turnAngle = 0;
    }
}

void Car::turnRight() {
    if (speed < maxSpeed/2) {
        maxTurnAngle = (SDL_fabs(speed) / (maxSpeed/2)) * 0.03;
    }
    else maxTurnAngle = 0.03;
    if (speed > 0) {
        if (turnAngle - turnGain > -maxTurnAngle) {
            turnAngle -= turnGain;
        }
        else turnAngle = -maxTurnAngle;
        angle += turnAngle;
    }
    else if (speed < 0) {
        if (turnAngle + turnGain < maxTurnAngle) {
            turnAngle += turnGain;
        }
        else turnAngle = maxTurnAngle;
        angle += turnAngle;
    }
    else {
        turnAngle = 0;
    }
}

void Car::straighten() {
    if (turnAngle > 0) {
        if (turnAngle - turnGain > 0) {
            turnAngle -= turnGain;
        }
        else turnAngle = 0;
        angle += turnAngle;
    }
    else if (turnAngle < 0) {
        if (turnAngle + turnGain < 0) {
            turnAngle += turnGain;
        }
        else turnAngle = 0;
        angle += turnAngle;
    }
}


void Car::collide(SceneElement* element) {
    if(!element->isCollidable){
        return;
    }
    if (auto intersection = Game::checkElementCollision(this, element)) {

        double absoluteAngle1 = SDL_fmod(this->angle, 2 * M_PI);
        double absoluteAngle2 = SDL_fmod(element->angle, 2 * M_PI);
        while (absoluteAngle1 < 0) absoluteAngle1 += 2 * M_PI;
        while (absoluteAngle2 < 0) absoluteAngle2 += 2 * M_PI;

        auto normal = SDL_FPoint{
            static_cast<float>(intersection->x - (this->x + this->width / 2)),
            static_cast<float>(intersection->y - (this->y + this->height / 2))
        };
        auto length = SDL_sqrtf(normal.x * normal.x + normal.y * normal.y);
        normal.x /= length;
        normal.y /= length;

        auto reverse = SDL_FPoint{
            static_cast<float>((this->speed > 0 ? -this->speed : this->speed) * normal.x),
            static_cast<float>((this->speed > 0 ? -this->speed : this->speed) * normal.y)
        };

        double angleDiff = absoluteAngle1 - absoluteAngle2;
        while (angleDiff < 0) angleDiff += 2 * M_PI;        // Makes it 'absolute' but not reversed

        if (lastCollidedWall == 0) {
            return;
        }

        // Range of angles where we add value in order to straighten for the height wall - variable for readability
        bool inHeightSlideRange = (angleDiff > 0 && angleDiff < M_PI/4)
                               || (angleDiff > 7*M_PI/4 && angleDiff < 2*M_PI)
                               || (angleDiff > 3*M_PI/4 && angleDiff < 5*M_PI/4);
        // Same but for the width wall
        bool inWidthSlideRange = (angleDiff > M_PI/4 && angleDiff < 3*M_PI/4)
                              || (angleDiff > 5*M_PI/4 && angleDiff < 7*M_PI/4);

        // REACTION A
        // The car is colliding with height and close to parallel to it -> it slides along it
        if ((this->lastCollidedWall == 2 || this->lastCollidedWall == 4) && inHeightSlideRange) {
            this->x += reverse.x;
            this->y += reverse.y;

            if ((angleDiff > 0 && angleDiff < M_PI/2) || (angleDiff > M_PI && angleDiff < 3*M_PI/2)) {
                this->angle -= 0.05;
            }
            else this->angle += 0.05;

            SDL_Log("Colliding height (slide) at %f %f\nAngle1 %f, Angle2 %f\nAngle diff %f", intersection->x, intersection->y, this->angle, element->angle, angleDiff);
            return;
        }
        // Same for width
        if ((this->lastCollidedWall == 1 || this->lastCollidedWall == 3) && inWidthSlideRange) {
            this->x += reverse.x;
            this->y += reverse.y;

            if ((angleDiff > 0 && angleDiff < M_PI/2) || (angleDiff > M_PI && angleDiff < 3*M_PI/2)) {
                this->angle += 0.05;
            }
            else this->angle -= 0.05;

            SDL_Log("Colliding width (slide) at %f %f\nAngle1 %f, Angle2 %f\nAngle diff %f", intersection->x, intersection->y, this->angle, element->angle, angleDiff);
            return;
        }


        // To prevent penetrating
        while (Game::checkElementCollision(this, element)) {
            this->x -= normal.x;
            this->y -= normal.y;
        }
        this->speed = 0;

        bool perpendicularToHeight = ((angleDiff > M_PI/2-0.1 && angleDiff < M_PI/2+0.1) || (angleDiff > 3*M_PI/2-0.1 && angleDiff < 3*M_PI/2+0.1));
        bool perpendicularToWidth = ((angleDiff < 0.1 || angleDiff > 2*M_PI-0.1) || (angleDiff > M_PI-0.1 && angleDiff < M_PI+0.1));

        // REACTION B
        // Car is colliding with height, not perpendicular to it and not turning -> stops and slowly turns towards perpendicular
        if ((lastCollidedWall == 2 || lastCollidedWall == 4) && !(perpendicularToHeight || Game::checkTurnControls())) {
            if ((angleDiff > 0 && angleDiff < M_PI/2) || (angleDiff > M_PI && angleDiff < 3*M_PI/2)) {
                this->angle += 0.05;
            }
            else {
                this->angle -= 0.05;
            }
            angleDiff = SDL_fmod(this->angle, 2 * M_PI) - absoluteAngle2;
            while (angleDiff < 0) angleDiff += 2 * M_PI;
        }
        // Same for width
        if ((lastCollidedWall == 1 || lastCollidedWall == 3) && !(perpendicularToWidth || Game::checkTurnControls())) {
            if ((angleDiff > 0 && angleDiff < M_PI/2) || (angleDiff > M_PI && angleDiff < 3*M_PI/2)) {
                this->angle -= 0.05;
            }
            else {
                this->angle += 0.05;
            }
            angleDiff = SDL_fmod(this->angle, 2 * M_PI) - absoluteAngle2;
            while (angleDiff < 0) angleDiff += 2 * M_PI;
        }

        SDL_Log("Colliding %s (halt) on %f %f\nAngle1 %f, Angle2 %f\nAngle diff %f", this->lastCollidedWall == 2 || this->lastCollidedWall == 4 ? "height" : "width", intersection->x, intersection->y, this->angle, element->angle, angleDiff);
    }
}