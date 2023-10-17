#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "WindowRenderer.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Platform.hpp"

int main() {
    WindowRenderer* windowRenderer = new WindowRenderer(512, 512, "Shooter");
    Player* player = new Player(25, 25);
    Bullet* bullet = NULL;
    Platform** platforms = Platform::initLevel();
    if (platforms == NULL) {
        return 0;
    }

    int running = 1;
    while (running) {
        int time = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT :
                    running = 0;
                    break;
                case SDL_EVENT_KEY_DOWN :
                    if (event.key.keysym.sym == SDLK_z && bullet == NULL) {
                        bullet = new Bullet(
                            new Transform(Vector2(player->getCollider()->x + 16, player->getCollider()->y + 54)),
                            new Sprite(
                                IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Bullet.png"),
                                (SDL_FRect) { 0, 0, 0, 0 }
                            )
                        );
                    }
                    else {
                        player->handleEvent(&event);
                    }
                    break;
                case SDL_EVENT_KEY_UP :
                    player->handleEvent(&event);
                    break;
            }
        }

        windowRenderer->clear();

        Platform::renderPlatforms(windowRenderer, platforms);

        player->move(platforms);
        player->render(windowRenderer);

        if (bullet != NULL) {
            if (bullet->move()) {
                delete bullet;
            } else {
                bullet->render(windowRenderer);
            }
        }

        windowRenderer->draw();

        while (SDL_GetTicks() - time < 15) {
            SDL_Delay(15);
        }
    }
    SDL_DestroyWindow(windowRenderer->getWindow());
    SDL_DestroyRenderer(windowRenderer->getRenderer());
    delete windowRenderer;
    delete player;
    return 1;
}