#pragma once

#include <cstdint>

class FrameBuffer
{

public:
    
    FrameBuffer(int w, int h);
    
    ~FrameBuffer();

    void clear(uint32_t color) const;
    
    void set_pixel(int x, int y, uint32_t color) const;
    
    uint32_t* get_pixels() const;

    void resize(int newWidth, int newHeight);

    int get_width() const;

    int get_height() const;

private:
    
    uint32_t* pixels;
    
    int width, height;
    
};
