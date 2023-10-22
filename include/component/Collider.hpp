#ifndef _COLLIDER_HPP_
#define _COLLIDER_HPP_

#include "Vector2.hpp"

#include <SDL3/SDL.h>

class Collider {
private:
    SDL_FRect shape;
    bool isTrigger;

public:
    Collider(SDL_FRect shape);
    Collider(SDL_FRect shape, bool isTrigger);

    const SDL_FRect& getShape();

    void update(const Vector2& position);
};

#endif