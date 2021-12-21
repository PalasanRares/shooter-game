#include "Player.h"

Player* initializePlayer(int x, int y) {
    Player* player = malloc(sizeof(Player));

    if (player == NULL) {
        return NULL;
    }

    player->x = x;
    player->y = y;

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

    SDL_Rect* currentFrame = getFrame(player);
    SDL_Rect destination;
    destination.x = player->x; destination.y = player->y;
    destination.w = currentFrame->w; destination.h = currentFrame->h;

    SDL_RenderCopyEx(app->renderer, spriteSheet, currentFrame, &destination, 0, NULL, player->flip);

    SDL_DestroyTexture(spriteSheet);
    return 1;
}

SDL_Rect* getFrame(Player* player) {
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
                player->time = 0;
            }
            player->xVelocity = -MOVEMENT_SPEED;
            player->flip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_RIGHT :
            if (player->xVelocity <= 0) {
                player->time = 0;
            }
            player->xVelocity = MOVEMENT_SPEED;
            player->flip = SDL_FLIP_NONE;
            break;
    }
}

void movePlayer(Player* player) {
    if (player->xVelocity != 0) {
        runningAnimation(player);
    }
    player->x += player->xVelocity;
    player->y += player->yVelocity;
    player->collider.x = player->x;
    player->collider.y = player->y;
}

void runningAnimation(Player* player) {
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