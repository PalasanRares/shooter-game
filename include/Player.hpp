#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 128
#define MOVEMENT_SPEED 3
#define JUMP_SPEED 25
#define GRAVITY 1

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "WindowRenderer.hpp"
#include "Platform.hpp"

enum PlayerState { IDLE = 0, RUNNING1 = 1, RUNNING2 = 2, JUMP = 3, FALLING = 4};

class Player {
private:
    int xVelocity, yVelocity;

    SDL_FRect sprites[5];
    SDL_FRect collider;

    int state;
    SDL_RendererFlip flip;
    int time;

public:
    Player(int x, int y);

    void render(WindowRenderer* windowRenderer);

    void handleEvent(SDL_Event* event);

    void move(Platform** platforms);

    void runningAnimation();

    int checkPlatformsCollision(Platform** platforms);

    SDL_FRect* getCollider();

    SDL_RendererFlip getFlip();
};

#endif