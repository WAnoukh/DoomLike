#pragma once
#include "Rendering/Textures/Texture.h"

class Renderer 
{
public:
    virtual ~Renderer() = default;
    
    virtual void Render() = 0;

    virtual void Init();
    
    void SetRenderSize(unsigned int width, unsigned int height);
    
    [[nodiscard]] Texture& GetRenderedTexture();

    void DrawLine(int x1, int y1, int x2, int y2, DLColor color);
protected:
private:
    unsigned int renderHeight = 100;
    unsigned int renderWidth = 100;
    Texture renderedTexture = Texture();
};
