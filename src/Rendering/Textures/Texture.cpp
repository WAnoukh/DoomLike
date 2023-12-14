﻿#include "Texture.h"

#include <iostream>
#include <glad/glad.h>

#include "Rendering/Color/DLColor.h"

void Texture::CreateBlankTexture(unsigned inWidth, unsigned inHeight, GLenum inFormat)
{
    if(inFormat != GL_RGB && inFormat != GL_RGBA)
    {
        std::cout << "Texture format not supported" << std::endl;
        return;
    }

    int dataSize = inWidth * inHeight * (inFormat == GL_RGB ? 3 : 4);

    data = new unsigned char[dataSize];

    for (int i = 0; i < dataSize; i++)
    {
        data[i] = 255;
    }
    format = inFormat;
    width = inWidth;
    height = inHeight;

    unsigned char color[3]  = {255,0,0};
}

bool Texture::EditPixel(int inX, int inY, DLColor color)
{
    unsigned char colorArray[4];
    color.ToUnsignedChar(colorArray);
    if (inX < 0 || inX >= width || inY < 0 || inY >= height)
    {                                                                 
        return false;
    }
    unsigned int pixelSize = format == GL_RGB ? 3 : 4;
    data[(inX + inY * width) * (pixelSize) + 0] = colorArray[0];
    data[(inX + inY * width) * (pixelSize) + 1] = colorArray[1];
    data[(inX + inY * width) * (pixelSize) + 2] = colorArray[2];
    if (format == GL_RGBA)
    {
        data[(inX + inY * width) * (pixelSize) + 3] = colorArray[3];
    }
    return true;
}

void Texture::GenerateOpenGlTexture()
{
    glGenTextures(1, &textureID);
}

void Texture::SendDataToOpenGl()
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    //To change if we want to load from texture file
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

unsigned Texture::GetTextureId() const
{
    return textureID; 
}

void Texture::Fill(DLColor color)
{
    unsigned char colorArray[4];
    color.ToUnsignedChar(colorArray);
    const int pixelLength = format == GL_RGB ? 3 : 4;
    for (int i = 0; i < width * height; i++)
    {
        data[i * pixelLength + 0] = colorArray[0];
        data[i * pixelLength + 1] = colorArray[1];
        data[i * pixelLength + 2] = colorArray[2];
        if (format == GL_RGBA)
        {
            data[i * pixelLength + 3] = colorArray[3];
        }
    }
}
