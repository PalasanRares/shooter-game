#ifndef _BULLET_H_
#define _BULLET_H_

#define BULLET_WIDTH 40;
#define BULLET_HEIGHT 20;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Player.h"
#include "App.h"

typedef struct Bullet {
    SDL_Rect collider;

    int xVelocity;

    SDL_Rect sprite;

    int flip;

} Bullet;

Bullet* initBullet(int x, int y, int flip);

int moveBullet(Bullet* bullet);

int renderBullet(App* app, Bullet* bullet);

#endif