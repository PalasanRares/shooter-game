#include "Platform.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Platform* initPlatform(int x, int y) {
    Platform* platform = malloc(sizeof(Platform));
    if (platform == NULL) {
        return NULL;
    }

    platform->collider.x = x; platform->collider.y = y;
    platform->collider.w = 128; platform->collider.h = 64;

    platform->sprite.x = 0; platform->sprite.y = 0;
    platform->sprite.w = 128; platform->sprite.h = 64;

    return platform;

}

Platform** initLevel() {
    Platform** platforms = malloc(2 * sizeof(Platform*));
    if (platforms == NULL) {
        return NULL;
    }
    
    platforms[0] = initPlatform(66, 256);
    if (platforms[0] == NULL) {
        return NULL;
    }

    platforms[1] = initPlatform(367, 310);
    if (platforms[1] == NULL) {
        return NULL;
    }
    return platforms;
 
}

int renderPlatforms(App* app, Platform** platforms) {
    SDL_Texture* sprite = IMG_LoadTexture(app->renderer, "./sprites/Platform.png");
    if (sprite == NULL) {
        printf("%s", SDL_GetError());
        return 0;
    }
    for (int i = 0; i < 2; i++) {
        SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(app->renderer, &platforms[i]->collider);

        SDL_RenderCopy(app->renderer, sprite, &platforms[i]->sprite, &platforms[i]->collider);    
    }
    SDL_DestroyTexture(sprite);
    return 1;
}
