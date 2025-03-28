#pragma once

#include "FrameBuffer.h"
#include "Render.h"
#include "Image.h"
#include <unordered_set>
#include "Warrior.h"

class Game
{
    
public:

    Game();
    
    void Initialize(HWND hwnd);
    
    void draw_r(HDC hdc);

    void update() const;
    
    void handle_input() const;

    void key_down(int key);
    
    void key_up(int key);

    FrameBuffer framebuffer;
    
private:
    
    std::unordered_set<int> activeKeys;
    
    
    
    Render renderer;
    
    Image image;

    Warrior* player;
};
