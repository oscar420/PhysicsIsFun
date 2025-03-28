#include "Render.h"

Render::Render(FrameBuffer* fb) : framebuffer(fb) {
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = 128;
    bmi.bmiHeader.biHeight = -128;  // Negative for correct top-down rendering
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
}

void Render::Draw(HDC hdc)
{
    int scaleFactor = 20;  // Scale the image by 8x (16px → 128px)

    int width = framebuffer->get_width();
    int height = framebuffer->get_height();

    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;

    
    StretchDIBits(
        hdc,
        0, 0, width, height,       // Dest: full framebuffer
        0, 0, width, height,       // Src: full framebuffer
        framebuffer->get_pixels(),
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY
    );
    /*StretchDIBits(hdc,
                  150, 150, 16 * scaleFactor, 16 * scaleFactor,  // Destination (scaled)
                  0, 0, 128, 128,  // Source (original size)
                  framebuffer->GetPixels(), &bmi, DIB_RGB_COLORS, SRCCOPY);*/
}
