#include "WindowRenderer.hpp"
#include "Color.hpp"

#include <iostream>

WindowRenderer::WindowRenderer(int width, int height, std::string title) : width(width), height(height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << SDL_GetError();
        throw;
    }
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (window == NULL) {
        std::cout << SDL_GetError();
        throw;
    }
    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::cout << SDL_GetError();
        throw;
    }
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
