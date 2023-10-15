#ifndef _WINDOW_RENDERER_HPP_
#define _WINDOW_RENDERER_HPP_

#include <SDL3/SDL.h>
#include <string>

class WindowRenderer {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;

public:
    WindowRenderer(int width, int height, std::string title);

    void clear();

    void draw();

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
};

#endif