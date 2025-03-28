#pragma once
#include <windows.h>
#include "FrameBuffer.h"

struct Pixel
{
    unsigned char r, g, b;
};

class Render
{
    
public:
    
    Render(FrameBuffer* fb);
    
    void Draw(HDC hdc);

private:
    
    HBITMAP hBitmap;
    
    BITMAPINFO bmi;
    
    FrameBuffer* framebuffer;
    
};
