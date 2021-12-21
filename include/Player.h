#ifndef _PLAYER_H_
#define _PLAYER_H_
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 64
#define MOVEMENT_SPEED 3

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "App.h"

enum PlayerState { IDLE = 0, RUNNING1 = 1, RUNNING2 = 2 };

typedef struct Player {
    int x, y;
    int xVelocity, yVelocity;

    SDL_Rect sprites[3];

    SDL_Rect collider;

    int state;
    int flip;
    int time;

} Player;

Player* initializePlayer(int x, int y);

int renderPlayer(App* app, Player* player);

SDL_Rect* getFrame(Player* player);

void handlePlayerEvent(SDL_Event* event, Player* player);

void movePlayer(Player* player);

void runningAnimation(Player* player);

#endif