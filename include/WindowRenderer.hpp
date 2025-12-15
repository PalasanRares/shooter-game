#ifndef _WINDOW_RENDERER_HPP_
#define _WINDOW_RENDERER_HPP_

#include <SDL3/SDL.h>
#include <string>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

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
    SDL_Renderer* getRenderer() const;
};

#endif
