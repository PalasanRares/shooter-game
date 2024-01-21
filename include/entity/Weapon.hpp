#ifndef _WEAPON_HPP_
#define _WEAPON_HPP_

#include "Transform.hpp"
#include "Sprite.hpp"

class Weapon {
private:
    Transform* transform;
    Sprite* sprite;

public:
    Weapon(Transform* transform);

    Transform* getTransform();
    Sprite* getSprite();
};

#endif