#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 128
#define MOVEMENT_SPEED 3
#define JUMP_SPEED 25
#define GRAVITY 1

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "WindowRenderer.hpp"
#include "Platform.hpp"
#include "Weapon.hpp"

#include "Transform.hpp"
#include "PhysicalBody.hpp"
#include "Animation.hpp"
#include "Collider.hpp"

enum PlayerState { IDLE = 0, RUNNING1 = 1, RUNNING2 = 2, JUMP = 3, FALLING = 4};

class Player {
private:
    Transform* transform;
    PhysicalBody* physicalBody;

    Animation* animation;
    Collider* collider;

    int state;
    int time;

    Weapon* weapon;

public:
    Player(WindowRenderer* windowRenderer, float x, float y);

    void render(WindowRenderer* windowRenderer, float mouseX, float mouseY);

    void handleEvent(SDL_Event* event);

    void move(Platform** platforms);

    void runningAnimation();

    int checkPlatformsCollision(Platform** platforms);

    Collider* getCollider();

    SDL_FlipMode getFlip();

    Weapon* getWeapon();
};

#endif