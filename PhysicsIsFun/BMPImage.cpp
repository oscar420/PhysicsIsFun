#include "BMPImage.h"
#include <vector>
#include <iostream>
#include <fstream>

bool BMPImage::LoadBMP(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    unsigned char header[54];
    file.read(reinterpret_cast<char*>(header), 54);

    width = *reinterpret_cast<int*>(&header[18]);
    height = *reinterpret_cast<int*>(&header[22]);

    int row_padded = (width * 3 + 3) & (~3);
    pixels.resize(width * height);

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            file.read(reinterpret_cast<char*>(&pixels[y * width + x]), 3);
        }
        file.ignore(row_padded - width * 3);
    }

    file.close();
    return true;
}