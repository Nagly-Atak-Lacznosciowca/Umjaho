#include "game/entity/Car.h"
#include "SDL3/SDL.h"
#include "engine/Renderer.h"
#include "array"

const double Car::WIDTH = 50;
const double Car::LENGTH = 100;

// length 3 array [dx, dy, dz]
void Car::move() {
    double vector[] = {
        this->x + this->speed * SDL_cos(-this->angle),    // Formula for vector rotation or something
        this->y + this->speed * SDL_sin(-this->angle)    // Beware of the minus sign :(((
    };
    this->x = vector[0];
    this->y = vector[1];
}

Car::Car(const double x, const double y, const double width, const double length, const double angle, const double zIndex, SDL_Texture* texture) : SceneElement(x, y, width, length, angle, zIndex, texture) {}

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