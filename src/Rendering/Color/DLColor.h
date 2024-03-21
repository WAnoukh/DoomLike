#pragma once
#include "UI/Tools/WorldEditor/TWallNode.h"

struct DLColor
{
    DLColor(float r, float g, float b, float a = 1.0f);
    DLColor(int inR, int inG, int inB, int inA = 255);
    DLColor(unsigned char color[4]);
    DLColor(float shade);
    void ToUnsignedChar(unsigned char outColor[4]) const;
    void SetColor(float inR, float inG, float inB, float inA = 1.0f);
    void SetColor(float inGrey);
    static const DLColor WHITE;
    static const DLColor BLACK;
    static const DLColor GREY;
    static const DLColor RED;
    static const DLColor GREEN;
    static const DLColor BLUE;
    static const DLColor YELLOW;
    static const DLColor MAGENTA;
    static const DLColor CYAN;
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;
};

DLColor operator*(const DLColor& color, float scalar);

struct DLRawColor
{
    DLRawColor(unsigned char inR, unsigned char inG, unsigned char inB, unsigned char inA = 255);
    DLRawColor() = default;
    DLRawColor(unsigned char inColor[], size_t size = 4);
    DLRawColor(unsigned char inGrey);
    DLRawColor(const DLColor& color);
    void SetColor(float shade);
    void Divide(float scalar);
    unsigned char* ToUnsignedChar() const;
    static const DLRawColor WHITE;
    static const DLRawColor BLACK;
    static const DLRawColor GREY;
    static const DLRawColor RED;
    static const DLRawColor GREEN;
    static const DLRawColor BLUE;
    static const DLRawColor YELLOW;
    static const DLRawColor MAGENTA;
    static const DLRawColor CYAN;
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;
};




