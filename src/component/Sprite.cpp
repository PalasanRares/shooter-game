#include "Sprite.hpp"

Sprite::Sprite(SDL_Texture* texture) : texture(texture), source((SDL_FRect) { 0, 0, 0, 0 }), flip(SDL_FLIP_NONE) {}

Sprite::Sprite(SDL_Texture* texture, SDL_FRect source) : texture(texture), source(source), flip(SDL_FLIP_NONE) {}

Sprite::Sprite(SDL_Texture* texture, SDL_FRect source, SDL_FlipMode flip) : texture(texture), source(source), flip(flip) {}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* Sprite::getTexture() {
    return texture;
}

SDL_FRect* Sprite::getSource() {
    return &source;
}

SDL_FlipMode Sprite::getFlip() {
    return flip;
}

void Sprite::setTexture(SDL_Texture* texture) {
    this->texture = texture;
}

void Sprite::setSource(SDL_FRect source) {
    this->source = source;
}

void Sprite::setFlip(SDL_FlipMode flip) {
    this->flip = flip;
}
