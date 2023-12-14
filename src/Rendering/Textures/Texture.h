#pragma once

#include <glad/glad.h>

struct DLColor;

class Texture
{
public:
    void CreateBlankTexture(unsigned inWidth, unsigned inHeight, GLenum inFormat);

    bool EditPixel(int inX, int inY, DLColor color);

    void GenerateOpenGlTexture();
    void SendDataToOpenGl();
    unsigned int GetTextureId() const;

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    void Fill(DLColor color);
    
private:
    unsigned char* data = nullptr;
    int width;
    int height;
    unsigned int textureID;
    GLenum format;
};
