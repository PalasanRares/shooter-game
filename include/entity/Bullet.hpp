#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "Player.hpp"
#include "WindowRenderer.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"
#include "Collider.hpp"

class Bullet {
private:
    Transform* transform;
    Sprite* sprite;
    Collider* collider;

    float velocity;

public:
    Bullet(Transform* transform, Sprite* sprite, float velocity);
    ~Bullet();

    bool move();

    void render(WindowRenderer* windowRenderer);
};

#endif