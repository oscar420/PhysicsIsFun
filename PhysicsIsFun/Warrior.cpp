#include "Warrior.h"

#include <iostream>

constexpr float GRAVITY = 1300.0f;       // Acceleration downward (pixels/sec²)
constexpr float JUMP_FORCE = 300.0f;    // Initial upward velocity
constexpr float MOVE_SPEED = 200.0f;    // Sideways speed during jump
constexpr float GROUND_Y = 500.0f;
constexpr float X_LIMIT = 950.0f;

// Screen-space ground level
#define AIR_DRAG 5   // the air drag resistance force level

Warrior::Warrior(FrameBuffer* fb, uint32_t* pixels, int width, int height)
    : x(100), y(GROUND_Y), speed(200), framebuffer(fb),
    spritePixels(pixels), spriteWidth(width),
    spriteHeight(height), jumpDirection(0),
    direction(0) {}

void Warrior::move(int dx, float deltaTime)
{
    if (!isJumping)
    {
        this->direction = dx;
        x += dx * speed * deltaTime;

        this->CheckBoundries();
    }
}

void Warrior::set_direction(int newDirection)
{
    this->direction = newDirection;
}

void Warrior::jump() {
    if (!isJumping && y == GROUND_Y)
    {  // ✅ Allow jumping only if on the ground
        velocityY = -JUMP_FORCE;
        isJumping = true;
        this->jumpDirection = this->direction;
    }
}

void Warrior::apply_force_and_module_position(float DeltaTime)
{
    if (!isJumping) return;

    // Apply gravity (pulls down, increases Y)
    velocityY += GRAVITY * DeltaTime;

    // Apply horizontal movement based on jump direction (-1, 0, or 1)
    x += jumpDirection * MOVE_SPEED * DeltaTime;

    // Update vertical position (Y increases = falling down)
    y += velocityY * DeltaTime;

    // Landing check
    if (y >= GROUND_Y)
    {
        y = GROUND_Y;
        velocityY = 0;
        isJumping = false;
    }

    this->CheckBoundries();
}

void Warrior::Draw()
{
    // Draw the hero image and scale it size
    for (int i = 0; i < spriteHeight; i++)
    {
        for (int j = 0; j < spriteWidth; j++)
        {
            int scale = 2;
            uint32_t color = spritePixels[i * spriteWidth + j];

            for (int dy = 0; dy < scale; ++dy)
            {
                for (int dx = 0; dx < scale; ++dx)
                {
                    framebuffer->set_pixel(x + j * scale + dx, y + i * scale + dy, color);
                }
            }
        }
    }
}

void Warrior::CheckBoundries()
{
    if (x < 0) x = 0;
    if (x > X_LIMIT) x = X_LIMIT;
    if (y < 0) y = 0;
}
