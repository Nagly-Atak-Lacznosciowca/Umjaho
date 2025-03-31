#ifndef UMJAHO_VEC2_H
#define UMJAHO_VEC2_H

#include "SDL3/SDL_stdinc.h"
// we implemented this waaaaay too late xdxdxdxd
struct Vec2 {
    double x, y;

    inline Vec2 operator+(const Vec2& other) const { return {x + other.x, y + other.y}; }
    inline Vec2 operator-(const Vec2& other) const { return {x - other.x, y - other.y}; }
    inline Vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

    Vec2 normalize() const {
        double length = SDL_sqrt(x * x + y * y);
        return (length > 0) ? Vec2 {x / length, y / length} : Vec2{ 0, 0 };
    }

};

#endif //UMJAHO_VEC2_H
