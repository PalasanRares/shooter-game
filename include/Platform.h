#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include "App.h"

typedef struct Platform {
    SDL_Rect collider;

    SDL_Rect sprite;

} Platform;

Platform* initPlatform(int x, int y);

Platform** initLevel();

int renderPlatforms(App* app, Platform** platforms);

#endif