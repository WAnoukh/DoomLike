#pragma once
#include "Rendering/Textures/Texture.h"

class Renderer
{
public:
    void SetRenderSize(unsigned int width, unsigned int height);
    virtual void Render() = 0;
    Texture& GetRenderedTexture();
private:
    unsigned int renderHeight = 100;
    unsigned int renderWidth = 100;
    Texture renderedTexture;
};
