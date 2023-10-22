#ifndef _VECTOR_2_HPP_
#define _VECTOR_2_HPP_

struct Vector2 {
    float x, y;
    
    Vector2();
    Vector2(float x, float y);

    float magnitude();
    Vector2 normalize();

    Vector2 operator+(const Vector2& vector);
    Vector2 operator*(float number);
};

#endif