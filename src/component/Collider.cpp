#include "Collider.hpp"

Collider::Collider(SDL_FRect shape) : shape(shape), isTrigger(false) {}

Collider::Collider(SDL_FRect shape, bool isTrigger) : shape(shape), isTrigger(isTrigger) {}

const SDL_FRect& Collider::getShape() {
    return shape;
}


void Collider::update(const Vector2& position) {
    shape.x = position.x;
    shape.y = position.y;
}