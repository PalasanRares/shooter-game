#include <stdlib.h>

#include "Bullet.hpp"

Bullet::Bullet(Transform* transform, Sprite* sprite) : transform(transform), sprite(sprite) {
    collider.x = transform->getPosition().x;
    collider.y = transform->getPosition().y;
    collider.w = BULLET_WIDTH;
    collider.h = BULLET_HEIGHT;

    if (sprite->getFlip() == SDL_FLIP_NONE) {
        xVelocity = 6;
    }
    else {
        xVelocity = -6;
    }

    sprite->setSource((SDL_FRect) { 0.0f, 0.0f, 40.0f, 20.0f });
}

Bullet::~Bullet() {
    delete transform;
    delete sprite;
}

bool Bullet::move() {
    collider.x += xVelocity;
    if (collider.x < 0 || collider.x + collider.w > 512) {
        return true;
    }
    return false;
}

void Bullet::render(WindowRenderer* windowRenderer) {
    SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);

    SDL_FRect destination;
    destination.x = collider.x; destination.y = collider.y;
    destination.w = sprite->getSource()->w; destination.h = sprite->getSource()->h;

    SDL_RenderTextureRotated(windowRenderer->getRenderer(), sprite->getTexture(), sprite->getSource(), &destination, 0, NULL, sprite->getFlip());
}
