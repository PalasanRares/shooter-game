#include "Animation.hpp"

Animation::Animation(SDL_Texture* spritesheet, SDL_FRect* frames, int length) : spritesheet(spritesheet), frames(frames), length(length) {
    flip = SDL_FLIP_NONE;
};

Animation::~Animation() {
    SDL_DestroyTexture(spritesheet);
    delete spritesheet;
    delete[] frames;
}

const SDL_Texture* Animation::getSpritesheet() {
    return this->spritesheet;
}

SDL_FRect Animation::getFrame(int position) {
    return this->frames[position];
}

SDL_FlipMode Animation::getFlip() {
    return this->flip;
}

void Animation::setFlip(SDL_FlipMode newFlip) {
    this->flip = newFlip;
}
