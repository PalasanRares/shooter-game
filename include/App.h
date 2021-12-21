#ifndef _APP_H_
#define _APP_H_

#include <SDL2/SDL.h>

typedef struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
} App;

int initializeApp(App* app, int windowWidth, int windowHeight, char* windowTitle);

int clearScreen(App* app);

void updateScreen(App* app);

#endif