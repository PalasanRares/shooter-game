#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

#include "WindowRenderer.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Platform.hpp"

int main() {
    WindowRenderer* windowRenderer = new WindowRenderer(512, 512, "Shooter");
    Player* player = new Player(25, 25);
    Bullet* bullet = NULL;
    Platform** platforms = Platform::initLevel(windowRenderer);

    float* mouseX;
    float* mouseY;
    int running = 1;
    while (running) {
        int startTime = SDL_GetPerformanceCounter();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT :
                    running = 0;
                    break;
                case SDL_EVENT_KEY_DOWN :
                    if (event.key.keysym.sym == SDLK_z && bullet == NULL) {
                        SDL_GetMouseState(mouseX, mouseY);
                        bullet = new Bullet(
                            new Transform(
                                Vector2(player->getCollider()->x + 16, player->getCollider()->y + 54),
                                Vector2(*mouseX - (player->getCollider()->x + 16.0f), *mouseY - (player->getCollider()->y + 54.0f)).normalize(),
                                Vector2(1, 1)
                            ),
                            new Sprite(IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Bullet.png")),
                            10
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
                bullet = NULL;
            } else {
                bullet->render(windowRenderer);
            }
        }

        windowRenderer->draw();

        int endTime = SDL_GetPerformanceCounter();
        float elapsedTime = (endTime - startTime) / (float) SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedTime));
    }
    SDL_DestroyWindow(windowRenderer->getWindow());
    SDL_DestroyRenderer(windowRenderer->getRenderer());
    delete windowRenderer;
    delete player;
    return 1;
}
