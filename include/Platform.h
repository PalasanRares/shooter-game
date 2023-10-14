#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "App.h"

typedef struct Platform {
    SDL_FRect collider;

    SDL_FRect sprite;

} Platform;

Platform* initPlatform(int x, int y);

Platform** initLevel();

int renderPlatforms(App* app, Platform** platforms);

#endif