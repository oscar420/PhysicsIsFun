#pragma once

struct Vector2
{
    float x, y;

    Vector2(float x_ = 0, float y_ = 0) : x(x_), y(y_) {}
};

class Physics
{
    
public:
    static void ApplyGravity(Vector2& velocity);
    static void ApplyFriction(Vector2& velocity, float friction);
    
};
