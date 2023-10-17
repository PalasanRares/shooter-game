#include "Transform.hpp"

Transform::Transform() : position(Vector2()), rotation(Vector2()), scale(Vector2()) {}

Transform::Transform(Vector2 position) : position(position), rotation(Vector2()), scale(Vector2()) {}

Transform::Transform(Vector2 position, Vector2 rotation, Vector2 scale) : position(position), rotation(rotation), scale(scale) {}

Vector2 Transform::getPosition() {
    return position;
}

Vector2 Transform::getRotation() {
    return rotation;
}

Vector2 Transform::getScale() {
    return scale;
}

void Transform::setPosition(Vector2 position) {
    this->position = position;
}

void Transform::setRotation(Vector2 rotation) {
    this->rotation = rotation;
}

void Transform::setScale(Vector2 scale) {
    this->scale = scale;
}
