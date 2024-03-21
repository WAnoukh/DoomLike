#include "DLColor.h"

#include <algorithm>

#include "imgui_impl_opengl3_loader.h"
#include "UI/Tools/WorldEditor/TWallNode.h"

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

DLColor::DLColor(float shade)
{
    r = shade;
    g = shade;
    b = shade;
    a = 1.0f;
}

void DLColor::ToUnsignedChar(unsigned char outColor[4]) const
{
    outColor[0] = static_cast<unsigned char>(r * 255.0f);
    outColor[1] = static_cast<unsigned char>(g * 255.0f);
    outColor[2] = static_cast<unsigned char>(b * 255.0f);
    outColor[3] = static_cast<unsigned char>(a * 255.0f);
}

void DLColor::SetColor(float inR, float inG, float inB, float inA)
{
    r = inR;
    g = inG;
    b = inB;
    a = inA;
}

void DLColor::SetColor(float inGrey)
{
    r = inGrey;
    g = inGrey;
    b = inGrey;
}

DLColor operator*(const DLColor& color, float scalar)
{
    DLColor color1(std::clamp(color.r * scalar, 0.0f, 1.0f),
                      std::clamp(color.g * scalar, 0.0f, 1.0f),
                     std::clamp(color.b * scalar, 0.0f, 1.0f),
                     color.a);
    return color1;
}

DLRawColor::DLRawColor(unsigned char inR, unsigned char inG, unsigned char inB, unsigned char inA)
{
    r = inR;
    g = inG;
    b = inB;
    a = inA;
}

DLRawColor::DLRawColor(unsigned char inColor[], size_t size)
{
    if (size == 4)
    {
        r = inColor[0];
        g = inColor[1];
        b = inColor[2];
        a = inColor[3];
        return;
    }
    else if (size == 3)
    {
        r = inColor[0];
        g = inColor[1];
        b = inColor[2];
        a = 255;
        return;
    }
    else if (size == 2)
    {
        r = inColor[0];
        g = inColor[1];
        b = 0;
        a = 255;
        return;
    }
    else if (size == 1)
    {
        r = inColor[0];
        g = 0;
        b = 0;
        a = 255;
        return;
    }
    else
    {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }
}

DLRawColor::DLRawColor(unsigned char inGrey)
{
    r = inGrey;
    g = inGrey;
    b = inGrey;
    a = 255;
}

DLRawColor::DLRawColor(const DLColor& color)
{
    r = static_cast<unsigned char>(color.r * 255.0f);
    g = static_cast<unsigned char>(color.g * 255.0f);
    b = static_cast<unsigned char>(color.b * 255.0f);
    a = static_cast<unsigned char>(color.a * 255.0f);
}

void DLRawColor::SetColor(float shade)
{
    r = static_cast<unsigned char>(shade * 255.0f);
    g = static_cast<unsigned char>(shade * 255.0f);
    b = static_cast<unsigned char>(shade * 255.0f);
}

void DLRawColor::Divide(float scalar)
{
    r/= scalar;
    g/= scalar;
    b/= scalar;
}

unsigned char* DLRawColor::ToUnsignedChar() const
{
    return new unsigned char[4]{r, g, b, a};
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

const DLRawColor DLRawColor::WHITE = DLRawColor(255, 255, 255);
const DLRawColor DLRawColor::BLACK = DLRawColor(0, 0, 0);
const DLRawColor DLRawColor::GREY = DLRawColor(128, 128, 128);
const DLRawColor DLRawColor::RED = DLRawColor(255, 0, 0);
const DLRawColor DLRawColor::GREEN = DLRawColor(0, 255, 0);
const DLRawColor DLRawColor::BLUE = DLRawColor(0, 0, 255);
const DLRawColor DLRawColor::YELLOW = DLRawColor(255, 255, 0);
const DLRawColor DLRawColor::MAGENTA = DLRawColor(255, 0, 255);
const DLRawColor DLRawColor::CYAN = DLRawColor(0, 255, 255);