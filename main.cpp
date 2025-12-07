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
    WindowRenderer* windowRenderer = WindowRenderer::getInstance();
    Player* player = new Player(25, 25);
    Bullet* bullet = NULL;
    Platform** platforms = Platform::initLevel(windowRenderer);

    float mouseX, mouseY;
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
                    if (event.key.key == SDLK_Z && bullet == nullptr) {
                        SDL_GetMouseState(&mouseX, &mouseY);
                        bullet = new Bullet(
                            new Transform(
                                Vector2(player->getWeapon()->getTransform()->getPosition().x + 16, player->getWeapon()->getTransform()->getPosition().y + 16),
                                Vector2(mouseX - (player->getCollider()->x + 36.0f), mouseY - (player->getCollider()->y + 64.0f)).normalize(),
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
        SDL_GetMouseState(&mouseX, &mouseY);
        player->render(windowRenderer, mouseX, mouseY);

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
        SDL_Delay(SDL_floor(16.666f - elapsedTime));
    }
    SDL_DestroyWindow(windowRenderer->getWindow());
    SDL_DestroyRenderer(windowRenderer->getRenderer());
    delete windowRenderer;
    delete player;
    return 1;
}
