#include "Platform.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <stdlib.h>

#define PLATFORM_WIDTH 64
#define PLATFORM_HEIGHT 64

Platform::Platform(Transform* transform, Sprite* sprite) : transform(transform), sprite(sprite) {
    Vector2 position = transform->getPosition();
    collider = new Collider(
        (SDL_FRect) { position.x, position.y, PLATFORM_WIDTH * transform->getScale().x, PLATFORM_HEIGHT * transform->getScale().y }
    );

    sprite->setSource(
        (SDL_FRect) { 0, 0, PLATFORM_WIDTH, PLATFORM_HEIGHT}
    );
}

Sprite* Platform::getSprite() {
    return sprite;
}

Collider* Platform::getCollider() {
    return collider;
}

void Platform::renderPlatforms(WindowRenderer* windowRenderer, std::vector<Platform*> platforms) {
    for (Platform* platform : platforms) {
        SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
        SDL_RenderRect(windowRenderer->getRenderer(), &platform->getCollider()->getShape());

        SDL_FRect destination;
        destination.x = platform->transform->getPosition().x; destination.y = platform->transform->getPosition().y;
        destination.w = platform->sprite->getSource()->w * platform->transform->getScale().x; destination.h = platform->sprite->getSource()->h * platform->transform->getScale().y;

        SDL_RenderTexture(windowRenderer->getRenderer(), platform->sprite->getTexture(), platform->sprite->getSource(), &destination);    
    }
}
