#include "Player.hpp"

#include <stdlib.h>

Player::Player(int x, int y) {
    xVelocity = 0;
    yVelocity = 0;

    collider.x = x;
    collider.y = y;
    collider.w = PLAYER_WIDTH;
    collider.h = PLAYER_HEIGHT;

    sprites[0].x = 0; sprites[0].y = 128;
    sprites[0].w = 128; sprites[0].h = 128;

    sprites[1].x = 0; sprites[1].y = 0;
    sprites[1].w = 128; sprites[1].h = 128;

    sprites[2].x = 128; sprites[2].y = 0;
    sprites[2].w = 128; sprites[2].h = 128;

    sprites[3].x = 0; sprites[3].y = 256;
    sprites[3].w = 128; sprites[3].h = 128;

    sprites[4].x = 128; sprites[4].y = 256;
    sprites[4].w = 128; sprites[4].h = 128;

    state = IDLE;
    flip = SDL_FLIP_NONE;
    time = SDL_GetTicks();
}

void Player::render(WindowRenderer* windowRenderer) {
    SDL_Texture* spriteSheet = IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/PlayerSpritesheet.png");
    if (spriteSheet == NULL) {
        printf("%s", SDL_GetError());
        return;
    }

    SDL_SetRenderDrawColor(windowRenderer->getRenderer(), 255, 0, 0, 255);
    SDL_RenderRect(windowRenderer->getRenderer(), &collider);

    SDL_FRect* currentFrame = &sprites[state];
    SDL_FRect destination;
    destination.x = collider.x - collider.w / 2; destination.y = collider.y;
    destination.w = currentFrame->w; destination.h = currentFrame->h;

    SDL_RenderTextureRotated(windowRenderer->getRenderer(), spriteSheet, currentFrame, &destination, 0, NULL, flip);

    SDL_DestroyTexture(spriteSheet);
}

void Player::handleEvent(SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_UP) {
        switch (event->key.keysym.sym) {
            case SDLK_LEFT :
                if (xVelocity < 0) {
                    xVelocity = 0;
                    state = IDLE;
                }
                break;
            case SDLK_RIGHT :
                if (xVelocity > 0) {
                    xVelocity = 0;
                    state = IDLE;
                }
                break;
        }
        return;
    }
    switch (event->key.keysym.sym) {
        case SDLK_LEFT :
            if (xVelocity >= 0) {
                state = IDLE;
                time = 0;
            }
            xVelocity = -MOVEMENT_SPEED;
            flip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_RIGHT :
            if (xVelocity <= 0) {
                state = IDLE;
                time = 0;
            }
            xVelocity = MOVEMENT_SPEED;
            flip = SDL_FLIP_NONE;
            break;
        case SDLK_SPACE :
            if (yVelocity == 0 && state != JUMP && state != FALLING) {
                yVelocity = -JUMP_SPEED;
                state = JUMP;
            }
    }
}

void Player::move(Platform** platforms) {
    if (xVelocity != 0) {
        runningAnimation();
    }

    collider.x += xVelocity;

    if (yVelocity > 0 && state == JUMP) {
        state = FALLING;
    }
    while (collider.x < 0 || (collider.x + PLAYER_WIDTH > 512) || (checkPlatformsCollision(platforms) && yVelocity != 0)) {
        if (xVelocity < 0) {
            collider.x += 1;
        }
        else if (xVelocity > 0) {
            collider.x -= 1;
        }
    }
    yVelocity += GRAVITY;
    collider.y += yVelocity;
    if((collider.y < 0) || (collider.y + PLAYER_HEIGHT >  512) || (checkPlatformsCollision(platforms))) {
        while ((collider.y < 0) || (collider.y + PLAYER_HEIGHT >  512) || (checkPlatformsCollision(platforms))) {
            if (yVelocity > 0) {
                collider.y -= 1;
            }
            else if (yVelocity < 0) {
                collider.y += 1;
            }
        }
        yVelocity = 0;
        if (state == JUMP || state == FALLING) {
            state = IDLE;
            time = 0;
        }
    }   
}

void Player::runningAnimation() {
    if (SDL_GetTicks() - time > 400 || xVelocity == 0) {
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

    for (int i = 0; i < 2; i++) {
        leftA = collider.x;
        rightA = collider.x + collider.w;
        topA = collider.y;
        bottomA = collider.y + collider.h;
            
        leftB = platforms[i]->getCollider().x;
        rightB = platforms[i]->getCollider().x + platforms[i]->getCollider().w;
        topB = platforms[i]->getCollider().y;
        bottomB = platforms[i]->getCollider().y + platforms[i]->getCollider().h;

        if (bottomA > topB && topA < bottomB && rightA > leftB && leftA < rightB) {
            found = 1;
        }
    }
    return found;
}

SDL_FRect* Player::getCollider() {
    return &collider;
}

SDL_RendererFlip Player::getFlip() {
    return flip;
}