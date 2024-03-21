#include "Texture.h"

#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/detail/type_vec2.hpp>

#include "Rendering/Color/DLColor.h"


Texture::Texture()
{
    CreateBlankTexture(width,height,format);
}

Texture::~Texture()
{
    delete[] data;
}

void Texture::CreateBlankTexture(unsigned inWidth, unsigned inHeight, GLenum inFormat)
{
    if(inFormat != GL_RGB && inFormat != GL_RGBA)
    {
        std::cout << "Texture format not supported" << std::endl;
        return;
    }

    int dataSize = inWidth * inHeight * (inFormat == GL_RGB ? 3 : 4);

    delete[] data;
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

void Texture::EditPixel(int inX, int inY, const DLColor& color, bool debug) const
{
    DLRawColor rawColor = DLRawColor(color);
    EditPixel(inX, inY, rawColor, debug);
}

void Texture::EditPixel(int inX, int inY, const DLRawColor& color, bool debug) const
{
    if (inX < 0 || inX >= width || inY < 0 || inY >= height)
    {
        if(debug)
        {
            std::cout << "Texture::EditPixel : Pixel out of bounds "<< inX << "," << inY << std::endl;
        }
        return;
    }
    const unsigned char* colorArray = reinterpret_cast<const unsigned char*>(&color);
    unsigned int pixelSize = format == GL_RGB ? 3 : 4;
    data[(inX + inY * width) * (pixelSize) + 0] = colorArray[0];
    data[(inX + inY * width) * (pixelSize) + 1] = colorArray[1];
    data[(inX + inY * width) * (pixelSize) + 2] = colorArray[2];
    if (format == GL_RGBA)
    {
        data[(inX + inY * width) * (pixelSize) + 3] = colorArray[3];
    }
    return;
}

void Texture::EditColumnStrip(int inX, int inY, int inLength, const DLRawColor& color) const
{
    if (inX < 0 || inX >= width || inY < 0 || inY >= height || inY + inLength >= height)
    {
        return;
    }
    const unsigned char* colorArray = reinterpret_cast<const unsigned char*>(&color);
    unsigned int pixelSize = format == GL_RGB ? 3 : 4;
    size_t pixelPos = (inX + inY * width) * (pixelSize);
    for (int i = 0; i < inLength; i++)
    {
        data[pixelPos + 0] = colorArray[0];
        data[pixelPos + 1] = colorArray[1];
        data[pixelPos + 2] = colorArray[2];
        if (format == GL_RGBA)
        {
            data[pixelPos + 3] = colorArray[3];
        }
        pixelPos += width * pixelSize;
    }
}


DLRawColor Texture::GetPixelColor(int inX, int inY) const
{
    return DLRawColor(&data[(inX + inY * width) *(format == GL_RGBA ? 4 : 3)], format == GL_RGBA ? 4 : 3);
}

void Texture::LoadFromFile(const char* path)
{
    GenerateOpenGlTexture();
    glBindTexture(GL_TEXTURE_2D, textureID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int nrChannels;
    data = stbi_load(path, &width, &height, &nrChannels, 0);
    format = nrChannels == 3 ? GL_RGB : GL_RGBA;
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Texture::GenerateOpenGlTexture()
{
    if(textureID != 0)
    {
        glDeleteTextures(1, &textureID);
    }
    glGenTextures(1, &textureID);
}

void Texture::SendDataToOpenGl() const
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    //To change if we want to load from texture file
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

unsigned int Texture::GetTextureId() const
{
    return textureID; 
}

glm::vec2 Texture::GetSize() const
{
    return glm::vec2(width, height);
}

void Texture::Fill(DLColor color) const
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
