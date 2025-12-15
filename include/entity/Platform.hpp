#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

#include <vector>

#include "WindowRenderer.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Transform.hpp"

class Platform {
private:
    Transform* transform;
    Sprite* sprite;
    Collider* collider;

public:
    Platform(Transform* transform, Sprite* sprite);

    Sprite* getSprite();
    Collider* getCollider();

    static void renderPlatforms(WindowRenderer* windowRenderer, std::vector<Platform*> platforms);
};

#endif