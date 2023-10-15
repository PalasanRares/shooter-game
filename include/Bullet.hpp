#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#define BULLET_WIDTH 40;
#define BULLET_HEIGHT 20;

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Player.hpp"
#include "WindowRenderer.hpp"

class Bullet {
private:
    SDL_FRect collider;

    int xVelocity;

    SDL_FRect sprite;

    SDL_RendererFlip flip;

public:
    Bullet(int x, int y, SDL_RendererFlip flip);

    bool move();

    void render(WindowRenderer* windowRenderer);
};

#endif