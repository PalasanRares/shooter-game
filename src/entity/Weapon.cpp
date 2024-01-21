#include "Weapon.hpp"

#include "TextureProvider.hpp"

#define WEAPON_WIDTH 64
#define WEAPON_HEIGHT 64

Weapon::Weapon(Transform* transform) : transform(transform) {
    sprite = new Sprite(
        TextureProvider::getInstance()->weaponTexture,
        (SDL_FRect) { 0.f, 0.f, WEAPON_WIDTH, WEAPON_HEIGHT }
    );
}

Transform* Weapon::getTransform() {
    return transform;
}

Sprite* Weapon::getSprite() {
    return sprite;
}