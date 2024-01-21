#include "Transform.hpp"

#include <cmath>

void Transform::recalculateDegrees() {
    degrees = atan(rotation.y / rotation.x) * 180.0f / M_PI;
    if (rotation.x < 0) degrees += 180.f;
}

Transform::Transform() : position(Vector2()), rotation(Vector2()), scale(Vector2()) {
    recalculateDegrees();
}

Transform::Transform(Vector2 position) : position(position), rotation(Vector2()), scale(Vector2()) {
    recalculateDegrees();
}

Transform::Transform(Vector2 position, Vector2 rotation, Vector2 scale) : position(position), rotation(rotation), scale(scale) {
    recalculateDegrees();
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

float Transform::getDegreesInRadians() {
    return degrees * M_PI / 180.f;
}

void Transform::setPosition(Vector2 position) {
    this->position = position;
}

void Transform::setRotation(Vector2 rotation) {
    this->rotation = rotation;
    recalculateDegrees();
}

void Transform::setScale(Vector2 scale) {
    this->scale = scale;
}

void Transform::movePosition(const Vector2& position) {
    this->position = this->position + position;
}