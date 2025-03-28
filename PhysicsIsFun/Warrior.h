#pragma once
#include "BMPImage.h"
#include "FrameBuffer.h"
#include "Physics.h"

class Warrior
{
public:

    Warrior(FrameBuffer* fb, uint32_t* pixels, int width, int height);
    
    void move(int dx, float deltaTime);
    
    void set_direction(int newDirection);
    
    void jump();
    
    void apply_force_and_module_position(float DeltaTime);

    void ApplyAirDrag();
    
    void Draw();
    
    int GetX() const { return x; }
    
    int GetY() const { return y; }

private:

    void CheckBoundries();

    int direction, jumpDirection, finalJumpXPosition;
    
    int x, y;  // Position
    
    int speed; // Movement speed

    int velocityY;    // Vertical velocity for jumping

    bool isJumping;   // Flag to check if in air
    
    FrameBuffer* framebuffer;
    
    uint32_t* spritePixels;
    
    int spriteWidth, spriteHeight;
    
};
