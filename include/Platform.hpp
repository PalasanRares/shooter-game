#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#include "WindowRenderer.hpp"

class Platform {
private:
    SDL_FRect collider;
    SDL_FRect sprite;

public:
    Platform(int x, int y);

    SDL_FRect getCollider();

    static Platform** initLevel();

    static void renderPlatforms(WindowRenderer* windowRenderer, Platform** platforms);
};

#endif