#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include <SDL3/SDL.h>

class Animation {
private:
    SDL_Texture* spritesheet;
    SDL_FRect* frames;
    int length;
    SDL_FlipMode flip;

public:
    Animation(SDL_Texture* spritesheet, SDL_FRect* frames, int length);
    ~Animation();

    const SDL_Texture* getSpritesheet();
    
    SDL_FRect getFrame(int position);
    SDL_FlipMode getFlip();

    void setFlip(SDL_FlipMode newFlip);
};

#endif
