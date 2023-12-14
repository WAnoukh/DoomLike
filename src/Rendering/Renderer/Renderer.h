#pragma once
#include "Rendering/Textures/Texture.h"

class Renderer 
{
public:
    virtual ~Renderer() = default;
    
    virtual void Render() = 0;
    
    void SetRenderSize(unsigned int width, unsigned int height);
    [[nodiscard]] const Texture& GetRenderedTexture() const;
protected:
    [[nodiscard]] Texture& GetRenderedTexture();
private:
    unsigned int renderHeight = 100;
    unsigned int renderWidth = 100;
    Texture renderedTexture = Texture();
};
