#ifndef _WINDOW_RENDERER_HPP_
#define _WINDOW_RENDERER_HPP_

#include <SDL3/SDL.h>
#include <string>

class WindowRenderer {
private:
    static WindowRenderer* instance;

    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;

    WindowRenderer();

public:
    static WindowRenderer* getInstance();

    void clear();

    void draw();

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
};

#endif