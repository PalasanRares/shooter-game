#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "Vector2.hpp"

class Transform {
private:
    Vector2 position;
    Vector2 rotation;
    Vector2 scale;

public:
    Transform();
    Transform(Vector2 position);
    Transform(Vector2 position, Vector2 rotation, Vector2 scale);

    Vector2 getPosition();
    Vector2 getRotation();
    Vector2 getScale();

    void setPosition(Vector2 position);
    void setRotation(Vector2 rotation);
    void setScale(Vector2 scale);
};

#endif