#include <stdlib.h>

#include "Bullet.h"

Bullet* initBullet(int x, int y, int flip) {
    Bullet* bullet = malloc(sizeof(Bullet));
    if (bullet == NULL) {
        return NULL;
    }

    bullet->collider.x = x;
    bullet->collider.y = y;
    bullet->collider.w = BULLET_WIDTH;
    bullet->collider.h = BULLET_HEIGHT;

    if (flip == SDL_FLIP_NONE) {
        bullet->xVelocity = 6;
    }
    else {
        bullet->xVelocity = -6;
    }

    bullet->sprite.x = 0;
    bullet->sprite.y = 0;
    bullet->sprite.w = 40;
    bullet->sprite.h = 20;

    bullet->flip = flip;

    return bullet;
}

int moveBullet(Bullet* bullet) {
    bullet->collider.x += bullet->xVelocity;
    if (bullet->collider.x < 0 || bullet->collider.x + bullet->collider.w > 512) {
        free(bullet);
        return 0;
    }
    return 1;
}

int renderBullet(App* app, Bullet* bullet) {
    SDL_Texture* sprite = IMG_LoadTexture(app->renderer, "./sprites/Bullet.png");
    if (sprite == NULL) {
        printf("%s", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);

    SDL_FRect destination;
    destination.x = bullet->collider.x; destination.y = bullet->collider.y;
    destination.w = bullet->sprite.w; destination.h = bullet->sprite.h;

    SDL_RenderTextureRotated(app->renderer, sprite, &bullet->sprite, &destination, 0, NULL, bullet->flip);
    
    SDL_DestroyTexture(sprite);
    return 1;
}
