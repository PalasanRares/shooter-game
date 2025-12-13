#include <stdlib.h>
#include <iostream>

#include "Bullet.hpp"
#include "WindowRenderer.hpp"

#define BULLET_WIDTH 40.0f
#define BULLET_HEIGHT 20.0f

Bullet::Bullet(Transform* transform, Sprite* sprite, float velocity) : transform(transform), sprite(sprite), velocity(velocity) {
    Vector2 position = transform->getPosition();
    collider = new Collider(
        (SDL_FRect) { position.x, position.y, BULLET_WIDTH, BULLET_HEIGHT }
    );

    sprite->setSource(
        (SDL_FRect) { 0.0f, 0.0f, BULLET_WIDTH, BULLET_HEIGHT }
    );
}

Bullet::~Bullet() {
    delete transform;
    delete sprite;
    delete collider;
}

bool Bullet::move() {
    transform->movePosition(transform->getRotation() * velocity);
    collider->update(transform->getPosition());
    SDL_FRect colliderShape = collider->getShape();
    if (colliderShape.x < 0 || colliderShape.x + colliderShape.w > WINDOW_WIDTH || colliderShape.y < 0 || colliderShape.y + colliderShape.h > WINDOW_HEIGHT) {
        return true;
    }
    return false;
}

void Bullet::render(WindowRenderer* windowRenderer) {
    SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
    SDL_RenderRect(windowRenderer->getRenderer(), &collider->getShape());

    SDL_FRect destination;
    destination.x = transform->getPosition().x; destination.y = transform->getPosition().y;
    destination.w = sprite->getSource()->w; destination.h = sprite->getSource()->h;

    SDL_RenderTextureRotated(windowRenderer->getRenderer(), sprite->getTexture(), sprite->getSource(), &destination, transform->getDegrees(), NULL, sprite->getFlip());
}
