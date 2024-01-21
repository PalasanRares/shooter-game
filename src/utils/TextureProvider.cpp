#include "TextureProvider.hpp"

TextureProvider* TextureProvider::instance = nullptr;

TextureProvider::TextureProvider() {
    windowRenderer = WindowRenderer::getInstance();

    weaponTexture = IMG_LoadTexture(windowRenderer->getRenderer(), "./sprites/Weapon.png");
}

TextureProvider* TextureProvider::getInstance() {
    if (instance == nullptr) {
        instance = new TextureProvider();
    }
    return instance;
}