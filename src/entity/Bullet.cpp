#include <stdlib.h>
#include <iostream>

#include "Bullet.hpp"

Bullet::Bullet(Transform* transform, Sprite* sprite, float velocity) : transform(transform), sprite(sprite), velocity(velocity) {
    collider.x = transform->getPosition().x;
    collider.y = transform->getPosition().y;
    collider.w = BULLET_WIDTH;
    collider.h = BULLET_HEIGHT;

    sprite->setSource((SDL_FRect) { 0.0f, 0.0f, 40.0f, 20.0f });
    if (transform->getRotation().x < 0) {
        sprite->setFlip(SDL_FLIP_HORIZONTAL);
    }
}

Bullet::~Bullet() {
    delete transform;
    delete sprite;
}

bool Bullet::move() {
    collider.x += transform->getRotation().x * velocity;
    collider.y += transform->getRotation().y * velocity;
    if (collider.x < 0 || collider.x + collider.w > 512 || collider.y < 0 || collider.y + collider.h > 512) {
        return true;
    }
    return false;
}

void Bullet::render(WindowRenderer* windowRenderer) {
    SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
    SDL_RenderRect(windowRenderer->getRenderer(), &collider);

    SDL_FRect destination;
    destination.x = collider.x; destination.y = collider.y;
    destination.w = sprite->getSource()->w; destination.h = sprite->getSource()->h;

    SDL_RenderTextureRotated(windowRenderer->getRenderer(), sprite->getTexture(), sprite->getSource(), &destination, transform->getDegrees(), NULL, sprite->getFlip());
}
