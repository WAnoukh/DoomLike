#pragma once

struct DLColor
{
    DLColor(float r, float g, float b, float a = 1.0f);
    DLColor(int inR, int inG, int inB, int inA = 255);
    DLColor(unsigned char color[4]);
    DLColor(float shade);
    void ToUnsignedChar(unsigned char outColor[4]) const;
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


