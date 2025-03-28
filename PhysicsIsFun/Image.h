#pragma once

#include <cstdint>

#include "BMPImage.h"

class Image
{
public:

    Image(int w, int h);
    
    ~Image();

    bool load_bmp(const std::string& filename);

    int get_width() const;
    
    int get_height() const;
    
    uint32_t* get_pixels();

private:
    
    int width_;
    
    int height_;
    
    uint32_t* pixels_;
    
};
