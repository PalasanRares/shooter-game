#include <stdio.h>
#include <malloc.h>
#include <SDL2/SDL.h>

#include "App.h"

int main() {
    App* app = malloc(sizeof(App));
    if (initializeApp(app, 512, 512, "Shooter") == 0) {
        return 0;
    }
    while (1) {
        int time = SDL_GetTicks();
        updateScreen(app);

        while (SDL_GetTicks() - time < 15) {
            SDL_Delay(15);
        }
    }
    SDL_DestroyWindow(app->window);
    SDL_DestroyRenderer(app->renderer);
    free(app);
    return 1;
}