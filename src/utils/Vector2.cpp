#include "Vector2.hpp"

#include <cmath>

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::magnitude() {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::normalize() {
    return Vector2(x / magnitude(), y / magnitude());
}

Vector2 Vector2::operator+(const Vector2& vector) {
    return Vector2(x + vector.x, y + vector.y);
}

Vector2 Vector2::operator*(float number) {
    return Vector2(x * number, y * number);
}