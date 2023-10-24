#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <SDL3_image/SDL_image.h>

class Sprite {
private:
    SDL_Texture* texture;
    SDL_FRect source;
    SDL_RendererFlip flip;

public:
    Sprite(SDL_Texture* texture);
    Sprite(SDL_Texture* texture, SDL_FRect source);
    Sprite(SDL_Texture* texture, SDL_FRect source, SDL_RendererFlip flip);
    ~Sprite();

    SDL_Texture* getTexture();
    SDL_FRect* getSource();
    SDL_RendererFlip getFlip();

    void setTexture(SDL_Texture* texture);
    void setSource(SDL_FRect source);
    void setFlip(SDL_RendererFlip flip);
};

#endif
