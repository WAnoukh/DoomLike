#include "Renderer.h"

void Renderer::SetRenderSize(const unsigned width, const unsigned height)
{
    renderWidth = width;
    renderHeight = height;
}

const Texture& Renderer::GetRenderedTexture() const
{
    return renderedTexture;
}

Texture& Renderer::GetRenderedTexture()
{
    return renderedTexture;
}
