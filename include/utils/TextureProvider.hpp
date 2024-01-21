#ifndef _TEXTURE_PROVIDER_HPP_
#define _TEXTURE_PROVIDER_HPP_

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "WindowRenderer.hpp"

class TextureProvider {
private:
    static TextureProvider* instance;
    
    WindowRenderer* windowRenderer;

    TextureProvider();

public:
    static TextureProvider* getInstance();

    SDL_Texture* weaponTexture;
};

#endif