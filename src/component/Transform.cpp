#include "Transform.hpp"

#include <cmath>

#define PI 3.14159265f

Transform::Transform() : position(Vector2()), rotation(Vector2()), scale(Vector2()) {
    degrees = atan(rotation.y / rotation.x) * 180.0f / PI;
}

Transform::Transform(Vector2 position) : position(position), rotation(Vector2()), scale(Vector2()) {
    degrees = atan(rotation.y / rotation.x) * 180.0f / PI;
}

Transform::Transform(Vector2 position, Vector2 rotation, Vector2 scale) : position(position), rotation(rotation), scale(scale) {
    degrees = atan(rotation.y / rotation.x) * 180.0f / PI;
}

Vector2 Transform::getPosition() {
    return position;
}

Vector2 Transform::getRotation() {
    return rotation;
}

Vector2 Transform::getScale() {
    return scale;
}

float Transform::getDegrees() {
    return degrees;
}

void Transform::setPosition(Vector2 position) {
    this->position = position;
}

void Transform::setRotation(Vector2 rotation) {
    this->rotation = rotation;
    degrees = atan(rotation.y / rotation.x) * 180.0f / PI;
}

void Transform::setScale(Vector2 scale) {
    this->scale = scale;
}
