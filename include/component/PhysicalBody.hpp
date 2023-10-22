#ifndef _PHYSICAL_BODY_HPP_
#define _PHYSICAL_BODY_HPP_

#include "Vector2.hpp"

class PhysicalBody {
private:
    Vector2 velocity;
    int mass;
    bool isAffectedByGravity;

public:
    PhysicalBody();
    PhysicalBody(Vector2 velocity);
    PhysicalBody(Vector2 velocity, int mass, bool isAffectedByGravity);

    Vector2 getVelocity();

    void setVelocity(Vector2 velocity);
};

#endif