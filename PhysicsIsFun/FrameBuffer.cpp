#include "FrameBuffer.h"
#include <cstring>

FrameBuffer::FrameBuffer(int w, int h) : width(w), height(h) {
    pixels = new uint32_t[width * height];
    clear(0xFFFFFFFF); // Default clear color (black)
}

FrameBuffer::~FrameBuffer() {
    delete[] pixels;
}

void FrameBuffer::clear(uint32_t color) const
{
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = color;
    }
}

void FrameBuffer::set_pixel(int x, int y, uint32_t color) const
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = color;
    }
}

uint32_t* FrameBuffer::get_pixels() const {
    return pixels;
}

void FrameBuffer::resize(int newWidth, int newHeight)
{
    if (pixels)
        delete[] pixels;

    width = newWidth;
    height = newHeight;
    pixels = new uint32_t[width * height];

    clear(0xFF000000);  // Make sure you clear right after allocation (black background)
}

int FrameBuffer::get_width() const
{
    return this->width;
}

int FrameBuffer::get_height() const
{
    return this->height;
}
