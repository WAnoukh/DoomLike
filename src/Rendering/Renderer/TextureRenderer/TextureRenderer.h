#pragma once
#include "Rendering/Renderer/Renderer.h"

class TextureRenderer : public Renderer
{
public:
    TextureRenderer(const char* inTexturePath) : texturePath(inTexturePath){}
    void Render() override;
    void Init() override
    {
        Texture& text = GetRenderedTexture();
        text.LoadFromFile(texturePath);
    }
private:
    const char* texturePath = nullptr;
};
