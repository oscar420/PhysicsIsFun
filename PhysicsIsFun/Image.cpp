#include "Image.h"
#include <fstream>
#include <iostream>

#pragma pack(push, 1) // Ensure proper byte alignment
struct BMPHeader {
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetData;
};

struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

Image::Image(int w, int h) : width_(w), height_(h) {
    pixels_ = new uint32_t[width_ * height_];
}

Image::~Image() {
    delete[] pixels_;
}

bool Image::load_bmp(const std::string& filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open BMP file: " << filename.c_str() << std::endl;
        return false;
    }

    BMPHeader fileHeader;
    BMPInfoHeader infoHeader;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BMPHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (fileHeader.fileType != 0x4D42) { // "BM" in little-endian
        std::cerr << "Error: Not a valid BMP file!" << std::endl;
        return false;
    }

    width_ = infoHeader.width;
    height_ = abs(infoHeader.height);

    delete[] pixels_;
    pixels_ = new uint32_t[width_ * height_];

    int rowPadding = (4 - (width_ * 3) % 4) % 4; // BMP rows are aligned to 4 bytes
    file.seekg(fileHeader.offsetData, std::ios::beg);

    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            uint8_t b, g, r;
            file.read(reinterpret_cast<char*>(&b), 1);
            file.read(reinterpret_cast<char*>(&g), 1);
            file.read(reinterpret_cast<char*>(&r), 1);
            pixels_[(height_ - 1 - y) * width_ + x] = (0xFF << 24) | (r << 16) | (g << 8) | b;
        }
        file.ignore(rowPadding); // Skip padding bytes
    }

    file.close();
    return true;
}

uint32_t* Image::get_pixels() {
    return pixels_;
}

int Image::get_width() const { return width_; }
int Image::get_height() const { return height_; }