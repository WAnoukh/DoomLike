#include "DLColor.h"

DLColor::DLColor(float r, float g, float b, float a): r(r), g(g), b(b), a(a)
{}

DLColor::DLColor(int inR, int inG, int inB, int inA)
{
    r = static_cast<float>(inR) / 255.0f;
    g = static_cast<float>(inG) / 255.0f;
    b = static_cast<float>(inB) / 255.0f;
    a = static_cast<float>(inA) / 255.0f;
}

DLColor::DLColor(unsigned char color[4])
{
    r = static_cast<float>(color[0]) / 255.0f;
    g = static_cast<float>(color[1]) / 255.0f;
    b = static_cast<float>(color[2]) / 255.0f;
    a = static_cast<float>(color[3]) / 255.0f;
}

void DLColor::ToUnsignedChar(unsigned char outColor[4]) const
{
    outColor[0] = static_cast<unsigned char>(r * 255.0f);
    outColor[1] = static_cast<unsigned char>(g * 255.0f);
    outColor[2] = static_cast<unsigned char>(b * 255.0f);
    outColor[3] = static_cast<unsigned char>(a * 255.0f);
}
    
const DLColor DLColor::WHITE = DLColor(255, 255, 255);
const DLColor DLColor::BLACK = DLColor(0, 0, 0);
const DLColor DLColor::GREY = DLColor(128, 128, 128);
const DLColor DLColor::RED = DLColor(255, 0, 0);
const DLColor DLColor::GREEN = DLColor(0, 255, 0);
const DLColor DLColor::BLUE = DLColor(0, 0, 255);
const DLColor DLColor::YELLOW = DLColor(255, 255, 0);
const DLColor DLColor::MAGENTA = DLColor(255, 0, 255);
const DLColor DLColor::CYAN = DLColor(0, 255, 255);
    