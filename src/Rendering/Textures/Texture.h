#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/detail/type_vec.hpp>

#include "Rendering/Color/DLColor.h"

struct DLColor;

class Texture
{
public:
    Texture();
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    
    void CreateBlankTexture(unsigned inWidth, unsigned inHeight, GLenum inFormat);
    void EditPixel(int inX, int inY, const DLColor& color, bool debug = false) const;
    void EditPixel(int inX, int inY, const DLRawColor& color, bool debug = false) const;
    void EditColumnStrip(int inX, int inY, int inLength, const DLRawColor& color) const;
    DLRawColor GetPixelColor(int inX, int inY) const;

    void LoadFromFile(const char* path);

    void GenerateOpenGlTexture();
    void SendDataToOpenGl() const;
    unsigned int GetTextureId() const;

    glm::vec2 GetSize() const;
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    void Fill(DLColor color) const;
    
private:
    unsigned char* data = nullptr;
    int width = 32;
    int height = 32;
    unsigned int textureID = 0;
    GLenum format = GL_RGB;
};
