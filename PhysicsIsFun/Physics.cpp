#include "Physics.h"

void Physics::ApplyGravity(Vector2& velocity) {
    velocity.y += 1.0f;  // Simulated gravity
}

void Physics::ApplyFriction(Vector2& velocity, float friction) {
    velocity.x *= friction;
    velocity.y *= friction;
}
