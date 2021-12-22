#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 128
#define MOVEMENT_SPEED 3
#define JUMP_SPEED 25
#define GRAVITY 1

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "App.h"
#include "Platform.h"

enum PlayerState { IDLE = 0, RUNNING1 = 1, RUNNING2 = 2, JUMP = 3, FALLING = 4};

typedef struct Player {
    int xVelocity, yVelocity;

    SDL_Rect sprites[5];

    SDL_Rect collider;

    int state;
    int flip;
    int time;

} Player;

Player* initializePlayer(int x, int y);

int renderPlayer(App* app, Player* player);

SDL_Rect* getPlayerFrame(Player* player);

void handlePlayerEvent(SDL_Event* event, Player* player);

void movePlayer(Player* player, Platform** platforms);

void runningPlayerAnimation(Player* player);

int checkPlatformsCollision(Player* player, Platform** platforms);

#endif