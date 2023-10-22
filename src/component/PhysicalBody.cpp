#include "PhysicalBody.hpp"

PhysicalBody::PhysicalBody() : velocity(Vector2()), mass(0), isAffectedByGravity(false) {}

PhysicalBody::PhysicalBody(Vector2 velocity) : velocity(velocity), mass(0), isAffectedByGravity(false) {}

PhysicalBody::PhysicalBody(Vector2 velocity, int mass, bool isAffectedByGravity) : velocity(velocity), mass(mass), isAffectedByGravity(isAffectedByGravity) {}

Vector2 PhysicalBody::getVelocity() {
    return velocity;
}

void PhysicalBody::setVelocity(Vector2 velocity) {
    this->velocity = velocity;
}
