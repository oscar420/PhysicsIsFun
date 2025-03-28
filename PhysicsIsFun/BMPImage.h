#pragma once

#include <vector>
#include "Render.h"

class BMPImage
{
    
public:

    int width, height;
    std::vector<Pixel> pixels;

    bool LoadBMP(const char* filename);
    
};
