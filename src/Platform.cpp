#include "Platform.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <stdlib.h>

Platform::Platform(int x, int y) {
    collider.x = x; collider.y = y;
    collider.w = 128; collider.h = 64;

    sprite.x = 0; sprite.y = 0;
    sprite.w = 128; sprite.h = 64;
}

SDL_FRect Platform::getCollider() {
    return collider;
}

Platform** Platform::initLevel() {
    Platform** platforms = new Platform*[2];
    
    platforms[0] = new Platform(66, 256);

    platforms[1] = new Platform(367, 310);

    return platforms;
}

void Platform::renderPlatforms(WindowRenderer* windowRenderer, Platform** platforms) {
    SDL_Texture* sprite = IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Platform.png");
    if (sprite == NULL) {
        printf("%s", SDL_GetError());
    }
    for (int i = 0; i < 2; i++) {
        SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
        SDL_RenderRect(windowRenderer->getRenderer(), &platforms[i]->collider);

        SDL_RenderTexture(windowRenderer->getRenderer(), sprite, &platforms[i]->sprite, &platforms[i]->collider);    
    }
    SDL_DestroyTexture(sprite);
}
