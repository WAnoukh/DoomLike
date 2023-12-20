#pragma once
#include <list>

#include "Rendering/Color/DLColor.h"
#include "Rendering/Textures/Texture.h"

class Renderer 
{
public:
    virtual ~Renderer() = default;
    
    virtual void Render() = 0;

    virtual void Init();

    [[nodiscard]] Texture& GetRenderedTexture();

    [[nodiscard]] unsigned int GetRenderHeight() const;
    [[nodiscard]] unsigned int GetRenderWidth() const;

    void DrawLine(int x1, int y1, int x2, int y2, DLColor color);
    
protected:
private:
    Texture renderedTexture = Texture();
};
