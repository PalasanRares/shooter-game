#include <stdio.h>
#include <malloc.h>
#include <SDL2/SDL.h>

#include "App.h"
#include "Player.h"
#include "Bullet.h"

int main() {
    App* app = malloc(sizeof(App));
    initializeApp(app, 512, 512, "Shooter");
    if (app == NULL) {
        return 0;
    }
    Player* player = initializePlayer(25, 25);
    if (player == NULL) {
        return 0;
    }
    Bullet* bullet = NULL;

    int running = 1;
    while (running) {
        int time = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT :
                    running = 0;
                    break;
                case SDL_KEYDOWN :
                    if (event.key.keysym.sym == SDLK_z && bullet == NULL) {
                        bullet = initBullet(player->collider.x + 16, player->collider.y + 54, player->flip);
                    }
                    else {
                        handlePlayerEvent(&event, player);
                    }
                    break;
                case SDL_KEYUP :
                    handlePlayerEvent(&event, player);
                    break;
            }
        }

        if (clearScreen(app) == 0) {
            return 0;
        }

        movePlayer(player);
        if (renderPlayer(app, player) == 0) {
            return 0;
        }

        if (bullet != NULL) {
            if (moveBullet(bullet) == 0) {
                bullet = NULL;
            }
            if (bullet != NULL) {
                if (renderBullet(app, bullet) == 0) {
                return 0;
                }
            }
        }

        updateScreen(app);

        while (SDL_GetTicks() - time < 15) {
            SDL_Delay(15);
        }
    }
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
    free(app);
    free(player);
    return 1;
}