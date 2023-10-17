#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#define BULLET_WIDTH 40;
#define BULLET_HEIGHT 20;

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Player.hpp"
#include "WindowRenderer.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"

class Bullet {
private:
    SDL_FRect collider;

    int xVelocity;

    Transform* transform;
    Sprite* sprite;

public:
    Bullet(Transform* transform, Sprite* sprite);

    bool move();

    void render(WindowRenderer* windowRenderer);
};

#endif