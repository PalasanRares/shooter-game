#include "WindowRenderer.hpp"
#include "Color.hpp"

#include <iostream>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512
#define WINDOW_TITLE "Shooter"

WindowRenderer* WindowRenderer::instance = nullptr;

WindowRenderer::WindowRenderer() : width(WINDOW_WIDTH), height(WINDOW_HEIGHT) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << SDL_GetError();
        throw;
    }
    window = SDL_CreateWindow(WINDOW_TITLE, width, height, 0);
    if (window == NULL) {
        std::cout << SDL_GetError();
        throw;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        std::cout << SDL_GetError();
        throw;
    }
}

WindowRenderer* WindowRenderer::getInstance() {
    if (instance == nullptr) {
        instance = new WindowRenderer();
    }
    return instance;
}

void WindowRenderer::clear() {
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a);
    if (SDL_RenderClear(renderer) != 0) {
        std::cout << SDL_GetError();
        return;
    }
}

void WindowRenderer::draw() {
    SDL_RenderPresent(renderer);
}

SDL_Window* WindowRenderer::getWindow() {
    return window;
}

SDL_Renderer* WindowRenderer::getRenderer() {
    return renderer;
}
