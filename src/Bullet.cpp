#include <stdlib.h>

#include "Bullet.hpp"

Bullet::Bullet(int x, int y, SDL_RendererFlip flip) {
    collider.x = x;
    collider.y = y;
    collider.w = BULLET_WIDTH;
    collider.h = BULLET_HEIGHT;

    if (flip == SDL_FLIP_NONE) {
        xVelocity = 6;
    }
    else {
        xVelocity = -6;
    }

    sprite.x = 0;
    sprite.y = 0;
    sprite.w = 40;
    sprite.h = 20;

    flip = flip;
}

bool Bullet::move() {
    collider.x += xVelocity;
    if (collider.x < 0 || collider.x + collider.w > 512) {
        return true;
    }
    return false;
}

void Bullet::render(WindowRenderer* windowRenderer) {
    SDL_Texture* sprite = IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Bullet.png");
    if (sprite == NULL) {
        printf("%s", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);

    SDL_FRect destination;
    destination.x = collider.x; destination.y = collider.y;
    destination.w = this->sprite.w; destination.h = this->sprite.h;

    SDL_RenderTextureRotated(windowRenderer->getRenderer(), sprite, &this->sprite, &destination, 0, NULL, flip);
    
    SDL_DestroyTexture(sprite);
}
