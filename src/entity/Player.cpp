#include "Player.hpp"

#include <stdlib.h>
#include <iostream>

#define PLAYER_ANIMATION_LENGTH 5

Player::Player(WindowRenderer* windowRenderer, float x, float y) {
    this->transform = new Transform(Vector2(x, y));

    this->physicalBody = new PhysicalBody(Vector2(0, 0));

    this->collider = new Collider(
        (SDL_FRect) { x, y, PLAYER_WIDTH, PLAYER_HEIGHT }
    );

    SDL_Texture* spritesheet = IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/PlayerSpritesheet.png");
    SDL_FRect* animationFrames = new SDL_FRect[PLAYER_ANIMATION_LENGTH];
    
    animationFrames[0] = (SDL_FRect) { 0, 128, 128, 128 };
    animationFrames[1] = (SDL_FRect) { 0, 0, 128, 128 };
    animationFrames[2] = (SDL_FRect) { 128, 0, 128, 128 };
    animationFrames[3] = (SDL_FRect) { 0, 256, 128, 128 };
    animationFrames[4] = (SDL_FRect) { 128, 256, 128, 128 };

    this->animation = new Animation(spritesheet, animationFrames, PLAYER_ANIMATION_LENGTH);

    state = IDLE;
    time = SDL_GetTicks();

    weapon = new Weapon(new Transform());
}

void Player::render(WindowRenderer* windowRenderer, float mouseX, float mouseY) {
    SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
    SDL_RenderRect(windowRenderer->getRenderer(), &collider->getShape());

    Vector2 currentPosition = transform->getPosition();

    SDL_FRect currentFrame = animation->getFrame(state);
    SDL_FRect destination;

    destination.x = currentPosition.x - currentFrame.w / 4; destination.y = currentPosition.y;
    destination.w = currentFrame.w; destination.h = currentFrame.h;

    SDL_RenderTextureRotated(
        windowRenderer->getRenderer(),
        (SDL_Texture*) animation->getSpritesheet(),
        &currentFrame,
        &destination,
        0,
        NULL,
        animation->getFlip()
    );
    
    // Update weapon coordinates based on current player position (TODO should be handled in move function later)
    float weaponRadius = 100;
    Vector2 weaponRotation = Vector2(
        mouseX - (currentPosition.x + currentFrame.w / 2), 
        mouseY - (currentPosition.y + currentFrame.h / 2)
    ).normalize();
    weapon->getTransform()->setRotation(weaponRotation);
    weapon->getTransform()->setPosition(Vector2(
        currentPosition.x + SDL_cos(weapon->getTransform()->getDegreesInRadians()) * weaponRadius,
        currentPosition.y + currentFrame.h / 4 + SDL_sin(weapon->getTransform()->getDegreesInRadians()) * weaponRadius
    ));

    // Draw the weapon
    SDL_FRect weaponDestination;
    weaponDestination.x = weapon->getTransform()->getPosition().x; weaponDestination.y = weapon->getTransform()->getPosition().y;
    weaponDestination.w = weapon->getSprite()->getSource()->w; weaponDestination.h = weapon->getSprite()->getSource()->h;
    SDL_RenderRect(windowRenderer->getRenderer(), &weaponDestination);
    SDL_RenderTextureRotated(windowRenderer->getRenderer(), weapon->getSprite()->getTexture(), weapon->getSprite()->getSource(), &weaponDestination, weapon->getTransform()->getDegrees(), nullptr, SDL_FLIP_NONE);
}

void Player::handleEvent(SDL_Event* event) {
    Vector2 currentVelocity = physicalBody->getVelocity();
    if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.key) {
            case SDLK_A :
                if (currentVelocity.x < 0) {
                    currentVelocity = { 0, currentVelocity.y };
                    state = IDLE;
                }
                break;
            case SDLK_D :
                if (currentVelocity.x > 0) {
                    currentVelocity = { 0, currentVelocity.y };
                    state = IDLE;
                }
                break;
        }
        physicalBody->setVelocity(currentVelocity);
        return;
    }
    switch (event->key.key) {
        case SDLK_A :
            if (currentVelocity.x >= 0) {
                state = IDLE;
                time = 0;
            }
            currentVelocity = { -MOVEMENT_SPEED, currentVelocity.y };
            animation->setFlip(SDL_FLIP_HORIZONTAL);
            break;
        case SDLK_D :
            if (currentVelocity.x <= 0) {
                state = IDLE;
                time = 0;
            }
            currentVelocity = { MOVEMENT_SPEED, currentVelocity.y };
            animation->setFlip(SDL_FLIP_NONE);
            break;
        case SDLK_SPACE :
            if (currentVelocity.y == 0 && state != JUMP && state != FALLING) {
                currentVelocity = {currentVelocity.x, -JUMP_SPEED };
                state = JUMP;
            }
    }
    physicalBody->setVelocity(currentVelocity);
}

void Player::move(Platform** platforms) {
    Vector2 currentVelocity = physicalBody->getVelocity();
    Vector2 currentPosition = transform->getPosition();
    if (currentVelocity.x != 0) {
        runningAnimation();
    }

    currentPosition.x += currentVelocity.x;
    collider->update(currentPosition);

    if (currentVelocity.y > 0 && state == JUMP) {
        state = FALLING;
    }
    while (currentPosition.x < 0 || (currentPosition.x + PLAYER_WIDTH > 512) || (checkPlatformsCollision(platforms) && currentVelocity.y != 0)) {
        if (currentVelocity.x < 0) {
            currentPosition.x += 1;
        }
        else if (currentVelocity.x > 0) {
            currentPosition.x -= 1;
        }
        collider->update(currentPosition);
    }

    currentVelocity.y += GRAVITY;
    currentPosition.y += currentVelocity.y;
    collider->update(currentPosition);

    if((currentPosition.y < 0) || (currentPosition.y + PLAYER_HEIGHT >  512) || (checkPlatformsCollision(platforms))) {
        while ((currentPosition.y < 0) || (currentPosition.y + PLAYER_HEIGHT >  512) || (checkPlatformsCollision(platforms))) {
            if (currentVelocity.y > 0) {
                currentPosition.y -= 1;
            }
            else if (currentVelocity.y < 0) {
                currentPosition.y += 1;
            }
            collider->update(currentPosition);
        }
        currentVelocity.y = 0;
        if (state == JUMP || state == FALLING) {
            state = IDLE;
            time = 0;
        }
    }
    transform->setPosition(currentPosition);
    physicalBody->setVelocity(currentVelocity);
}

void Player::runningAnimation() {
    if (SDL_GetTicks() - time > 400 || physicalBody->getVelocity().x == 0) {
        if (state == IDLE) {
            state = RUNNING1;
        }
        else if (state == RUNNING1) {
            state = RUNNING2;
        }
        else if (state == RUNNING2) {
            state = RUNNING1;
        }
        time = SDL_GetTicks();
    }
}

int Player::checkPlatformsCollision(Platform** platforms) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    int found = 0;

    SDL_FRect colliderShape = collider->getShape();
    for (int i = 0; i < 2; i++) {
        leftA = colliderShape.x;
        rightA = colliderShape.x + colliderShape.w;
        topA = colliderShape.y;
        bottomA = colliderShape.y + colliderShape.h;
            
        leftB = platforms[i]->getCollider()->getShape().x;
        rightB = platforms[i]->getCollider()->getShape().x + platforms[i]->getCollider()->getShape().w;
        topB = platforms[i]->getCollider()->getShape().y;
        bottomB = platforms[i]->getCollider()->getShape().y + platforms[i]->getCollider()->getShape().h;

        if (bottomA > topB && topA < bottomB && rightA > leftB && leftA < rightB) {
            found = 1;
        }
    }
    return found;
}

Collider* Player::getCollider() {
    return collider;
}

SDL_FlipMode Player::getFlip() {
    return animation->getFlip();
}

Weapon* Player::getWeapon() {
    return weapon;
}