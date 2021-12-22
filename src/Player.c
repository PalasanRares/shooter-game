#include "Player.h"

Player* initializePlayer(int x, int y) {
    Player* player = malloc(sizeof(Player));

    if (player == NULL) {
        return NULL;
    }

    player->xVelocity = 0;
    player->yVelocity = 0;

    player->collider.x = x;
    player->collider.y = y;
    player->collider.w = PLAYER_WIDTH;
    player->collider.h = PLAYER_HEIGHT;

    player->sprites[0].x = 0; player->sprites[0].y = 128;
    player->sprites[0].w = 128; player->sprites[0].h = 128;

    player->sprites[1].x = 0; player->sprites[1].y = 0;
    player->sprites[1].w = 128; player->sprites[1].h = 128;

    player->sprites[2].x = 128; player->sprites[2].y = 0;
    player->sprites[2].w = 128; player->sprites[2].h = 128;

    player->sprites[3].x = 0; player->sprites[3].y = 256;
    player->sprites[3].w = 128; player->sprites[3].h = 128;

    player->sprites[4].x = 128; player->sprites[4].y = 256;
    player->sprites[4].w = 128; player->sprites[4].h = 128;

    player->state = IDLE;
    player->flip = SDL_FLIP_NONE;
    player->time = SDL_GetTicks();

    return player;
}

int renderPlayer(App* app, Player* player) {
    SDL_Texture* spriteSheet = IMG_LoadTexture(app->renderer, "./sprites/PlayerSpritesheet.png");
    if (spriteSheet == NULL) {
        printf("%s", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(app->renderer, &player->collider);

    SDL_Rect* currentFrame = getPlayerFrame(player);
    SDL_Rect destination;
    destination.x = player->collider.x - player->collider.w / 2; destination.y = player->collider.y;
    destination.w = currentFrame->w; destination.h = currentFrame->h;

    SDL_RenderCopyEx(app->renderer, spriteSheet, currentFrame, &destination, 0, NULL, player->flip);

    SDL_DestroyTexture(spriteSheet);
    return 1;
}

SDL_Rect* getPlayerFrame(Player* player) {
    return &(player->sprites[player->state]);
}

void handlePlayerEvent(SDL_Event* event, Player* player) {
    if (event->type == SDL_KEYUP) {
        switch (event->key.keysym.sym) {
            case SDLK_LEFT :
                if (player->xVelocity < 0) {
                    player->xVelocity = 0;
                    player->state = IDLE;
                }
                break;
            case SDLK_RIGHT :
                if (player->xVelocity > 0) {
                    player->xVelocity = 0;
                    player->state = IDLE;
                }
                break;
        }
        return;
    }
    switch (event->key.keysym.sym) {
        case SDLK_LEFT :
            if (player->xVelocity >= 0) {
                player->state = IDLE;
                player->time = 0;
            }
            player->xVelocity = -MOVEMENT_SPEED;
            player->flip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_RIGHT :
            if (player->xVelocity <= 0) {
                player->state = IDLE;
                player->time = 0;
            }
            player->xVelocity = MOVEMENT_SPEED;
            player->flip = SDL_FLIP_NONE;
            break;
        case SDLK_SPACE :
            if (player->yVelocity == 0 && player->state != JUMP && player->state != FALLING) {
                player->yVelocity = -JUMP_SPEED;
                player->state = JUMP;
            }
    }
}

void movePlayer(Player* player, Platform** platforms) {
    if (player->xVelocity != 0) {
        runningPlayerAnimation(player);
    }

    player->collider.x += player->xVelocity;

    if (player->yVelocity > 0 && player->state == JUMP) {
        player->state = FALLING;
    }
    while (player->collider.x < 0 || (player->collider.x + PLAYER_WIDTH > 512) || (checkPlatformsCollision(player, platforms) && player->yVelocity != 0)) {
        if (player->xVelocity < 0) {
            player->collider.x += 1;
        }
        else if (player->xVelocity > 0) {
            player->collider.x -= 1;
        }
    }
    player->yVelocity += GRAVITY;
    player->collider.y += player->yVelocity;
    if((player->collider.y < 0) || (player->collider.y + PLAYER_HEIGHT >  512) || (checkPlatformsCollision(player, platforms))) {
        while ((player->collider.y < 0) || (player->collider.y + PLAYER_HEIGHT >  512) || (checkPlatformsCollision(player, platforms))) {
            if (player->yVelocity > 0) {
                player->collider.y -= 1;
            }
            else if (player->yVelocity < 0) {
                player->collider.y += 1;
            }
        }
        player->yVelocity = 0;
        if (player->state == JUMP || player->state == FALLING) {
            player->state = IDLE;
            player->time = 0;
        }
    }   
}

void runningPlayerAnimation(Player* player) {
    if (SDL_GetTicks() - player->time > 400 || player->xVelocity == 0) {
        if (player->state == IDLE) {
            player->state = RUNNING1;
        }
        else if (player->state == RUNNING1) {
            player->state = RUNNING2;
        }
        else if (player->state == RUNNING2) {
            player->state = RUNNING1;
        }
        player->time = SDL_GetTicks();
    }
}

int checkPlatformsCollision(Player* player, Platform** platforms) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    int found = 0;

    for (int i = 0; i < 2; i++) {
        leftA = player->collider.x;
        rightA = player->collider.x + player->collider.w;
        topA = player->collider.y;
        bottomA = player->collider.y + player->collider.h;
            
        leftB = platforms[i]->collider.x;
        rightB = platforms[i]->collider.x + platforms[i]->collider.w;
        topB = platforms[i]->collider.y;
        bottomB = platforms[i]->collider.y + platforms[i]->collider.h;

        if (bottomA > topB && topA < bottomB && rightA > leftB && leftA < rightB) {
            found = 1;
        }
    }
    return found;
}