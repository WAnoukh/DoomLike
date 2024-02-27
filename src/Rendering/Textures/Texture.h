#pragma once

#include <glad/glad.h>
#include <glm/detail/type_vec.hpp>

struct DLColor;

class Texture
{
public:
    Texture();
    
    void CreateBlankTexture(unsigned inWidth, unsigned inHeight, GLenum inFormat);
    void EditPixel(int inX, int inY, DLColor color, bool debug = false) const;

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
