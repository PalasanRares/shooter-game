#include "App.h"

int initializeApp(App* app, int windowWidth, int windowHeight, char* windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("%s", SDL_GetError());
        return 0;
    }
    app->window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    if (app->window == NULL) {
        printf("%s", SDL_GetError());
        return 0;
    }
    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);
    if (app->renderer == NULL) {
        printf("%s", SDL_GetError());
        return 0;
    }
    app->width = windowWidth;
    app->height = windowHeight;
    return 1;
}

int clearScreen(App* app) {
    if (SDL_RenderClear(app->renderer) != 0) {
        printf("%s", SDL_GetError());
        return 0;
    }
    return 1;
}

void updateScreen(App* app) {
    SDL_RenderPresent(app->renderer);
}