#include "Platform.hpp"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <stdlib.h>

#define PLATFORM_WIDTH 128
#define PLATFORM_HEIGHT 64

Platform::Platform(Transform* transform, Sprite* sprite) : transform(transform), sprite(sprite) {
    Vector2 position = transform->getPosition();
    collider = new Collider(
        (SDL_FRect) { position.x, position.y, PLATFORM_WIDTH, PLATFORM_HEIGHT }
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

Platform** Platform::initLevel(WindowRenderer* windowRenderer) {
    Platform** platforms = new Platform*[2];
    
    platforms[0] = new Platform(
        new Transform(Vector2(66, 256)),
        new Sprite(IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Platform.png"))
    );
    platforms[1] = new Platform(
        new Transform(Vector2(367, 310)),
        new Sprite(IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Platform.png"))
    );

    return platforms;
}

void Platform::renderPlatforms(WindowRenderer* windowRenderer, Platform** platforms) {
    for (int i = 0; i < 2; i++) {
        SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
        SDL_RenderRect(windowRenderer->getRenderer(), &platforms[i]->getCollider()->getShape());

        SDL_FRect destination;
        destination.x = platforms[i]->transform->getPosition().x; destination.y = platforms[i]->transform->getPosition().y;
        destination.w = platforms[i]->sprite->getSource()->w; destination.h = platforms[i]->sprite->getSource()->h;

        SDL_RenderTexture(windowRenderer->getRenderer(), platforms[i]->sprite->getTexture(), platforms[i]->sprite->getSource(), &destination);    
    }
}
